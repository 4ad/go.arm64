// cmd/7l/asm.c, cmd/7l/asmout.c, cmd/7l/optab.c, cmd/7l/span.c, cmd/ld/sub.c, cmd/ld/mod.c, from Vita Nuova.
// https://code.google.com/p/ken-cc/source/browse/
//
// 	Copyright © 1994-1999 Lucent Technologies Inc.  All rights reserved.
// 	Portions Copyright © 1995-1997 C H Forsyth (forsyth@terzarima.net)
// 	Portions Copyright © 1997-1999 Vita Nuova Limited
// 	Portions Copyright © 2000-2007 Vita Nuova Holdings Limited (www.vitanuova.com)
// 	Portions Copyright © 2004,2006 Bruce Ellis
// 	Portions Copyright © 2005-2007 C H Forsyth (forsyth@terzarima.net)
// 	Revisions Copyright © 2000-2007 Lucent Technologies Inc. and others
// 	Portions Copyright © 2009 The Go Authors.  All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

package arm64

import (
	"cmd/internal/obj"
	"fmt"
	"log"
	"math"
	"sort"
)

const (
	FuncAlign = 16
)

type Mask struct {
	s uint8
	e uint8
	r uint8
	v uint64
}

type Optab struct {
	as    uint16
	a1    uint8
	a2    uint8
	a3    uint8
	type_ int8
	size  int8
	param int8
	flag  int8
}

type Oprang struct {
	start []Optab
	stop  []Optab
}

type Opcross [32][2][32]uint8

var oprange [ALAST]Oprang

var opcross [8]Opcross

var repop [ALAST]uint8

var xcmp [C_NCLASS][C_NCLASS]uint8

const (
	S32     = 0 << 31
	S64     = 1 << 31
	Sbit    = 1 << 29
	LSL0_32 = 2 << 13
	LSL0_64 = 3 << 13
)

func OPDP2(x uint32) uint32 {
	return 0<<30 | 0<<29 | 0xd6<<21 | x<<10
}

func OPDP3(sf uint32, op54 uint32, op31 uint32, o0 uint32) uint32 {
	return sf<<31 | op54<<29 | 0x1B<<24 | op31<<21 | o0<<15
}

func OPBcc(x uint32) uint32 {
	return 0x2A<<25 | 0<<24 | 0<<4 | x&15
}

func OPBLR(x uint32) uint32 {
	/* x=0, JMP; 1, CALL; 2, RET */
	return 0x6B<<25 | 0<<23 | x<<21 | 0x1F<<16 | 0<<10
}

func SYSOP(l uint32, op0 uint32, op1 uint32, crn uint32, crm uint32, op2 uint32, rt uint32) uint32 {
	return 0x354<<22 | l<<21 | op0<<19 | op1<<16 | crn<<12 | crm<<8 | op2<<5 | rt
}

func SYSHINT(x uint32) uint32 {
	return SYSOP(0, 0, 3, 2, 0, x, 0x1F)
}

func LDSTR12U(sz uint32, v uint32, opc uint32) uint32 {
	return sz<<30 | 7<<27 | v<<26 | 1<<24 | opc<<22
}

func LDSTR9S(sz uint32, v uint32, opc uint32) uint32 {
	return sz<<30 | 7<<27 | v<<26 | 0<<24 | opc<<22
}

func LD2STR(o uint32) uint32 {
	return o &^ (3 << 22)
}

func LDSTX(sz uint32, o2 uint32, l uint32, o1 uint32, o0 uint32) uint32 {
	return sz<<30 | 0x8<<24 | o2<<23 | l<<22 | o1<<21 | o0<<15
}

func FPCMP(m uint32, s uint32, type_ uint32, op uint32, op2 uint32) uint32 {
	return m<<31 | s<<29 | 0x1E<<24 | type_<<22 | 1<<21 | op<<14 | 8<<10 | op2
}

func FPCCMP(m uint32, s uint32, type_ uint32, op uint32) uint32 {
	return m<<31 | s<<29 | 0x1E<<24 | type_<<22 | 1<<21 | 1<<10 | op<<4
}

func FPOP1S(m uint32, s uint32, type_ uint32, op uint32) uint32 {
	return m<<31 | s<<29 | 0x1E<<24 | type_<<22 | 1<<21 | op<<15 | 0x10<<10
}

func FPOP2S(m uint32, s uint32, type_ uint32, op uint32) uint32 {
	return m<<31 | s<<29 | 0x1E<<24 | type_<<22 | 1<<21 | op<<12 | 2<<10
}

func FPCVTI(sf uint32, s uint32, type_ uint32, rmode uint32, op uint32) uint32 {
	return sf<<31 | s<<29 | 0x1E<<24 | type_<<22 | 1<<21 | rmode<<19 | op<<16 | 0<<10
}

func ADR(p uint32, o uint32, rt uint32) uint32 {
	return p<<31 | (o&3)<<29 | 0x10<<24 | ((o>>2)&0x7FFFF)<<5 | rt
}

func OPBIT(x uint32) uint32 {
	return 1<<30 | 0<<29 | 0xD6<<21 | 0<<16 | x<<10
}

const (
	LFROM = 1 << 0
	LTO   = 1 << 1
	LPOOL = 1 << 2
)

var optab = []Optab{
	/* struct Optab:
	OPCODE,       from, prog->reg, to,             type,size,param,flag */
	Optab{ATEXT, C_LEXT, C_NONE, C_VCON, 0, 0, 0, 0},
	Optab{ATEXT, C_LEXT, C_REG, C_VCON, 0, 0, 0, 0},
	Optab{ATEXT, C_ADDR, C_NONE, C_VCON, 0, 0, 0, 0},
	Optab{ATEXT, C_ADDR, C_REG, C_VCON, 0, 0, 0, 0},

	/* arithmetic operations */
	Optab{AADD, C_REG, C_REG, C_REG, 1, 4, 0, 0},
	Optab{AADD, C_REG, C_NONE, C_REG, 1, 4, 0, 0},
	Optab{AADC, C_REG, C_REG, C_REG, 1, 4, 0, 0},
	Optab{AADC, C_REG, C_NONE, C_REG, 1, 4, 0, 0},
	Optab{ANEG, C_REG, C_NONE, C_REG, 25, 4, 0, 0},
	Optab{ANGC, C_REG, C_NONE, C_REG, 17, 4, 0, 0},
	Optab{ACMP, C_REG, C_RSP, C_NONE, 1, 4, 0, 0},
	Optab{AADD, C_ADDCON, C_RSP, C_RSP, 2, 4, 0, 0},
	Optab{AADD, C_ADDCON, C_NONE, C_RSP, 2, 4, 0, 0},
	Optab{ACMP, C_ADDCON, C_RSP, C_NONE, 2, 4, 0, 0},
	Optab{AADD, C_MBCON, C_RSP, C_RSP, 2, 4, 0, 0},
	Optab{AADD, C_MBCON, C_NONE, C_RSP, 2, 4, 0, 0},
	Optab{ACMP, C_MBCON, C_RSP, C_NONE, 2, 4, 0, 0},
	Optab{AADD, C_VCON, C_REG, C_REG, 13, 8, 0, LFROM},
	Optab{AADD, C_VCON, C_NONE, C_REG, 13, 8, 0, LFROM},
	Optab{ACMP, C_VCON, C_REG, C_NONE, 13, 8, 0, LFROM},
	Optab{AADD, C_SHIFT, C_REG, C_REG, 3, 4, 0, 0},
	Optab{AADD, C_SHIFT, C_NONE, C_REG, 3, 4, 0, 0},
	Optab{AMVN, C_SHIFT, C_NONE, C_REG, 3, 4, 0, 0},
	Optab{ACMP, C_SHIFT, C_REG, C_NONE, 3, 4, 0, 0},
	Optab{ANEG, C_SHIFT, C_NONE, C_REG, 26, 4, 0, 0},
	Optab{AADD, C_REG, C_RSP, C_RSP, 27, 4, 0, 0},
	Optab{AADD, C_REG, C_NONE, C_RSP, 27, 4, 0, 0},
	Optab{AADD, C_EXTREG, C_RSP, C_RSP, 27, 4, 0, 0},
	Optab{AADD, C_EXTREG, C_NONE, C_RSP, 27, 4, 0, 0},
	Optab{AMVN, C_EXTREG, C_NONE, C_RSP, 27, 4, 0, 0},
	Optab{ACMP, C_EXTREG, C_RSP, C_NONE, 27, 4, 0, 0},
	Optab{AADD, C_REG, C_REG, C_REG, 1, 4, 0, 0},
	Optab{AADD, C_REG, C_NONE, C_REG, 1, 4, 0, 0},

	/* logical operations */
	Optab{AAND, C_REG, C_REG, C_REG, 1, 4, 0, 0},
	Optab{AAND, C_REG, C_NONE, C_REG, 1, 4, 0, 0},
	Optab{ABIC, C_REG, C_REG, C_REG, 1, 4, 0, 0},
	Optab{ABIC, C_REG, C_NONE, C_REG, 1, 4, 0, 0},
	Optab{AAND, C_BITCON, C_REG, C_REG, 53, 4, 0, 0},
	Optab{AAND, C_BITCON, C_NONE, C_REG, 53, 4, 0, 0},
	Optab{ABIC, C_BITCON, C_REG, C_REG, 53, 4, 0, 0},
	Optab{ABIC, C_BITCON, C_NONE, C_REG, 53, 4, 0, 0},
	Optab{AAND, C_VCON, C_REG, C_REG, 28, 8, 0, LFROM},
	Optab{AAND, C_VCON, C_NONE, C_REG, 28, 8, 0, LFROM},
	Optab{ABIC, C_VCON, C_REG, C_REG, 28, 8, 0, LFROM},
	Optab{ABIC, C_VCON, C_NONE, C_REG, 28, 8, 0, LFROM},
	Optab{AAND, C_SHIFT, C_REG, C_REG, 3, 4, 0, 0},
	Optab{AAND, C_SHIFT, C_NONE, C_REG, 3, 4, 0, 0},
	Optab{ABIC, C_SHIFT, C_REG, C_REG, 3, 4, 0, 0},
	Optab{ABIC, C_SHIFT, C_NONE, C_REG, 3, 4, 0, 0},
	Optab{AMOV, C_RSP, C_NONE, C_RSP, 24, 4, 0, 0},
	Optab{AMVN, C_REG, C_NONE, C_REG, 24, 4, 0, 0},
	Optab{AMOVB, C_REG, C_NONE, C_REG, 45, 4, 0, 0},
	Optab{AMOVBU, C_REG, C_NONE, C_REG, 45, 4, 0, 0},
	Optab{AMOVH, C_REG, C_NONE, C_REG, 45, 4, 0, 0}, /* also MOVHU */
	Optab{AMOVW, C_REG, C_NONE, C_REG, 45, 4, 0, 0}, /* also MOVWU */
	/* TO DO: MVN C_SHIFT */

	/* MOVs that become MOVK/MOVN/MOVZ/ADD/SUB/OR */
	Optab{AMOVW, C_MOVCON, C_NONE, C_REG, 32, 4, 0, 0},
	Optab{AMOV, C_MOVCON, C_NONE, C_REG, 32, 4, 0, 0},

	//	{ AMOVW,		C_ADDCON,	C_NONE,	C_REG,		2, 4, 0 },
	//	{ AMOV,		C_ADDCON,	C_NONE,	C_REG,		2, 4, 0 },
	//	{ AMOVW,		C_BITCON,	C_NONE,	C_REG,		53, 4, 0 },
	//	{ AMOV,		C_BITCON,	C_NONE,	C_REG,		53, 4, 0 },

	Optab{AMOVK, C_VCON, C_NONE, C_REG, 33, 4, 0, 0},
	Optab{AMOV, C_AECON, C_NONE, C_REG, 4, 4, REGSB, 0},
	Optab{AMOV, C_AACON, C_NONE, C_REG, 4, 4, REGSP, 0},
	Optab{ASDIV, C_REG, C_NONE, C_REG, 1, 4, 0, 0},
	Optab{ASDIV, C_REG, C_REG, C_REG, 1, 4, 0, 0},
	Optab{AB, C_NONE, C_NONE, C_SBRA, 5, 4, 0, 0},
	Optab{ABL, C_NONE, C_NONE, C_SBRA, 5, 4, 0, 0},
	Optab{AB, C_NONE, C_NONE, C_ZOREG, 6, 4, 0, 0},
	Optab{ABL, C_NONE, C_NONE, C_REG, 6, 4, 0, 0},
	Optab{ABL, C_NONE, C_NONE, C_ZOREG, 6, 4, 0, 0},
	Optab{ARET, C_NONE, C_NONE, C_REG, 6, 4, 0, 0},
	Optab{ARET, C_NONE, C_NONE, C_ZOREG, 6, 4, 0, 0},
	Optab{AADRP, C_SBRA, C_NONE, C_REG, 60, 4, 0, 0},
	Optab{AADR, C_SBRA, C_NONE, C_REG, 61, 4, 0, 0},
	Optab{ABFM, C_VCON, C_REG, C_REG, 42, 4, 0, 0},
	Optab{ABFI, C_VCON, C_REG, C_REG, 43, 4, 0, 0},
	Optab{AEXTR, C_VCON, C_REG, C_REG, 44, 4, 0, 0},
	Optab{ASXTB, C_REG, C_NONE, C_REG, 45, 4, 0, 0},
	Optab{ACLS, C_REG, C_NONE, C_REG, 46, 4, 0, 0},
	Optab{ABEQ, C_NONE, C_NONE, C_SBRA, 7, 4, 0, 0},
	Optab{ALSL, C_VCON, C_REG, C_REG, 8, 4, 0, 0},
	Optab{ALSL, C_VCON, C_NONE, C_REG, 8, 4, 0, 0},
	Optab{ALSL, C_REG, C_NONE, C_REG, 9, 4, 0, 0},
	Optab{ALSL, C_REG, C_REG, C_REG, 9, 4, 0, 0},
	Optab{ASVC, C_NONE, C_NONE, C_VCON, 10, 4, 0, 0},
	Optab{ASVC, C_NONE, C_NONE, C_NONE, 10, 4, 0, 0},
	Optab{ADWORD, C_NONE, C_NONE, C_VCON, 11, 8, 0, 0},
	Optab{ADWORD, C_NONE, C_NONE, C_LEXT, 11, 8, 0, 0},
	Optab{ADWORD, C_NONE, C_NONE, C_ADDR, 11, 8, 0, 0},
	Optab{ADWORD, C_NONE, C_NONE, C_LACON, 11, 8, 0, 0},
	Optab{AWORD, C_NONE, C_NONE, C_LCON, 14, 4, 0, 0},
	Optab{AWORD, C_NONE, C_NONE, C_LEXT, 14, 4, 0, 0},
	Optab{AWORD, C_NONE, C_NONE, C_ADDR, 14, 4, 0, 0},
	Optab{AMOVW, C_VCON, C_NONE, C_REG, 12, 4, 0, LFROM},
	Optab{AMOV, C_VCON, C_NONE, C_REG, 12, 4, 0, LFROM},
	Optab{AMOVB, C_REG, C_NONE, C_ADDR, 64, 8, 0, LTO},
	Optab{AMOVBU, C_REG, C_NONE, C_ADDR, 64, 8, 0, LTO},
	Optab{AMOVH, C_REG, C_NONE, C_ADDR, 64, 8, 0, LTO},
	Optab{AMOVW, C_REG, C_NONE, C_ADDR, 64, 8, 0, LTO},
	Optab{AMOV, C_REG, C_NONE, C_ADDR, 64, 8, 0, LTO},
	Optab{AMOVB, C_ADDR, C_NONE, C_REG, 65, 8, 0, LFROM},
	Optab{AMOVBU, C_ADDR, C_NONE, C_REG, 65, 8, 0, LFROM},
	Optab{AMOVH, C_ADDR, C_NONE, C_REG, 65, 8, 0, LFROM},
	Optab{AMOVW, C_ADDR, C_NONE, C_REG, 65, 8, 0, LFROM},
	Optab{AMOV, C_ADDR, C_NONE, C_REG, 65, 8, 0, LFROM},
	Optab{AMUL, C_REG, C_REG, C_REG, 15, 4, 0, 0},
	Optab{AMUL, C_REG, C_NONE, C_REG, 15, 4, 0, 0},
	Optab{AMADD, C_REG, C_REG, C_REG, 15, 4, 0, 0},
	Optab{AREM, C_REG, C_REG, C_REG, 16, 8, 0, 0},
	Optab{AREM, C_REG, C_NONE, C_REG, 16, 8, 0, 0},
	Optab{ACSEL, C_COND, C_REG, C_REG, 18, 4, 0, 0}, /* from3 optional */
	Optab{ACSET, C_COND, C_NONE, C_REG, 18, 4, 0, 0},
	Optab{ACCMN, C_COND, C_REG, C_VCON, 19, 4, 0, 0}, /* from3 either C_REG or C_VCON */

	/* scaled 12-bit unsigned displacement store */
	Optab{AMOVB, C_REG, C_NONE, C_SEXT1, 20, 4, REGSB, 0},    //
	Optab{AMOVB, C_REG, C_NONE, C_UAUTO4K, 20, 4, REGSP, 0},  //
	Optab{AMOVB, C_REG, C_NONE, C_UOREG4K, 20, 4, 0, 0},      //
	Optab{AMOVBU, C_REG, C_NONE, C_SEXT1, 20, 4, REGSB, 0},   //
	Optab{AMOVBU, C_REG, C_NONE, C_UAUTO4K, 20, 4, REGSP, 0}, //
	Optab{AMOVBU, C_REG, C_NONE, C_UOREG4K, 20, 4, 0, 0},     //

	Optab{AMOVH, C_REG, C_NONE, C_SEXT2, 20, 4, REGSB, 0},   //
	Optab{AMOVH, C_REG, C_NONE, C_UAUTO8K, 20, 4, REGSP, 0}, //
	Optab{AMOVH, C_REG, C_NONE, C_ZOREG, 20, 4, 0, 0},       //
	Optab{AMOVH, C_REG, C_NONE, C_UOREG8K, 20, 4, 0, 0},     //

	Optab{AMOVW, C_REG, C_NONE, C_SEXT4, 20, 4, REGSB, 0},    //
	Optab{AMOVW, C_REG, C_NONE, C_UAUTO16K, 20, 4, REGSP, 0}, //
	Optab{AMOVW, C_REG, C_NONE, C_ZOREG, 20, 4, 0, 0},        //
	Optab{AMOVW, C_REG, C_NONE, C_UOREG16K, 20, 4, 0, 0},     //

	/* unscaled 9-bit signed displacement store */
	Optab{AMOVB, C_REG, C_NONE, C_NSAUTO, 20, 4, REGSP, 0},  //
	Optab{AMOVB, C_REG, C_NONE, C_NSOREG, 20, 4, 0, 0},      //
	Optab{AMOVBU, C_REG, C_NONE, C_NSAUTO, 20, 4, REGSP, 0}, //
	Optab{AMOVBU, C_REG, C_NONE, C_NSOREG, 20, 4, 0, 0},     //

	Optab{AMOVH, C_REG, C_NONE, C_NSAUTO, 20, 4, REGSP, 0}, //
	Optab{AMOVH, C_REG, C_NONE, C_NSOREG, 20, 4, 0, 0},     //
	Optab{AMOVW, C_REG, C_NONE, C_NSAUTO, 20, 4, REGSP, 0}, //
	Optab{AMOVW, C_REG, C_NONE, C_NSOREG, 20, 4, 0, 0},     //

	Optab{AMOV, C_REG, C_NONE, C_SEXT8, 20, 4, REGSB, 0},
	Optab{AMOV, C_REG, C_NONE, C_UAUTO32K, 20, 4, REGSP, 0},
	Optab{AMOV, C_REG, C_NONE, C_ZOREG, 20, 4, 0, 0},
	Optab{AMOV, C_REG, C_NONE, C_UOREG32K, 20, 4, 0, 0},
	Optab{AMOV, C_REG, C_NONE, C_NSOREG, 20, 4, 0, 0},     //
	Optab{AMOV, C_REG, C_NONE, C_NSAUTO, 20, 4, REGSP, 0}, //

	/* short displacement load */
	Optab{AMOVB, C_SEXT1, C_NONE, C_REG, 21, 4, REGSB, 0},   //
	Optab{AMOVB, C_UAUTO4K, C_NONE, C_REG, 21, 4, REGSP, 0}, //
	Optab{AMOVB, C_NSAUTO, C_NONE, C_REG, 21, 4, REGSP, 0},  //
	Optab{AMOVB, C_ZOREG, C_NONE, C_REG, 21, 4, 0, 0},       //
	Optab{AMOVB, C_UOREG4K, C_NONE, C_REG, 21, 4, REGSP, 0}, //
	Optab{AMOVB, C_NSOREG, C_NONE, C_REG, 21, 4, REGSP, 0},  //

	Optab{AMOVBU, C_SEXT1, C_NONE, C_REG, 21, 4, REGSB, 0},   //
	Optab{AMOVBU, C_UAUTO4K, C_NONE, C_REG, 21, 4, REGSP, 0}, //
	Optab{AMOVBU, C_NSAUTO, C_NONE, C_REG, 21, 4, REGSP, 0},  //
	Optab{AMOVBU, C_ZOREG, C_NONE, C_REG, 21, 4, 0, 0},       //
	Optab{AMOVBU, C_UOREG4K, C_NONE, C_REG, 21, 4, REGSP, 0}, //
	Optab{AMOVBU, C_NSOREG, C_NONE, C_REG, 21, 4, REGSP, 0},  //

	Optab{AMOVH, C_SEXT2, C_NONE, C_REG, 21, 4, REGSB, 0},   //
	Optab{AMOVH, C_UAUTO8K, C_NONE, C_REG, 21, 4, REGSP, 0}, //
	Optab{AMOVH, C_NSAUTO, C_NONE, C_REG, 21, 4, REGSP, 0},  //
	Optab{AMOVH, C_ZOREG, C_NONE, C_REG, 21, 4, 0, 0},       //
	Optab{AMOVH, C_UOREG8K, C_NONE, C_REG, 21, 4, REGSP, 0}, //
	Optab{AMOVH, C_NSOREG, C_NONE, C_REG, 21, 4, REGSP, 0},  //

	Optab{AMOVW, C_SEXT4, C_NONE, C_REG, 21, 4, REGSB, 0},    //
	Optab{AMOVW, C_UAUTO16K, C_NONE, C_REG, 21, 4, REGSP, 0}, //
	Optab{AMOVW, C_NSAUTO, C_NONE, C_REG, 21, 4, REGSP, 0},   //
	Optab{AMOVW, C_ZOREG, C_NONE, C_REG, 21, 4, 0, 0},        //
	Optab{AMOVW, C_UOREG16K, C_NONE, C_REG, 21, 4, REGSP, 0}, //
	Optab{AMOVW, C_NSOREG, C_NONE, C_REG, 21, 4, REGSP, 0},   //

	Optab{AMOV, C_SEXT8, C_NONE, C_REG, 21, 4, REGSB, 0},
	Optab{AMOV, C_UAUTO32K, C_NONE, C_REG, 21, 4, REGSP, 0},
	Optab{AMOV, C_NSAUTO, C_NONE, C_REG, 21, 4, REGSP, 0},
	Optab{AMOV, C_ZOREG, C_NONE, C_REG, 21, 4, 0, 0},
	Optab{AMOV, C_UOREG32K, C_NONE, C_REG, 21, 4, REGSP, 0},
	Optab{AMOV, C_NSOREG, C_NONE, C_REG, 21, 4, REGSP, 0},

	/* long displacement store */
	Optab{AMOVB, C_REG, C_NONE, C_LEXT, 30, 8, REGSB, 0},   //
	Optab{AMOVB, C_REG, C_NONE, C_LAUTO, 30, 8, REGSP, 0},  //
	Optab{AMOVB, C_REG, C_NONE, C_LOREG, 30, 8, 0, 0},      //
	Optab{AMOVBU, C_REG, C_NONE, C_LEXT, 30, 8, REGSB, 0},  //
	Optab{AMOVBU, C_REG, C_NONE, C_LAUTO, 30, 8, REGSP, 0}, //
	Optab{AMOVBU, C_REG, C_NONE, C_LOREG, 30, 8, 0, 0},     //
	Optab{AMOVH, C_REG, C_NONE, C_LEXT, 30, 8, REGSB, 0},   //
	Optab{AMOVH, C_REG, C_NONE, C_LAUTO, 30, 8, REGSP, 0},  //
	Optab{AMOVH, C_REG, C_NONE, C_LOREG, 30, 8, 0, 0},      //
	Optab{AMOVW, C_REG, C_NONE, C_LEXT, 30, 8, REGSB, 0},   //
	Optab{AMOVW, C_REG, C_NONE, C_LAUTO, 30, 8, REGSP, 0},  //
	Optab{AMOVW, C_REG, C_NONE, C_LOREG, 30, 8, 0, 0},      //
	Optab{AMOV, C_REG, C_NONE, C_LEXT, 30, 8, REGSB, 0},    //
	Optab{AMOV, C_REG, C_NONE, C_LAUTO, 30, 8, REGSP, 0},   //
	Optab{AMOV, C_REG, C_NONE, C_LOREG, 30, 8, 0, 0},       //

	/* long displacement load */
	Optab{AMOVB, C_LEXT, C_NONE, C_REG, 31, 8, REGSB, 0},   //
	Optab{AMOVB, C_LAUTO, C_NONE, C_REG, 31, 8, REGSP, 0},  //
	Optab{AMOVB, C_LOREG, C_NONE, C_REG, 31, 8, 0, 0},      //
	Optab{AMOVB, C_LOREG, C_NONE, C_REG, 31, 8, 0, 0},      //
	Optab{AMOVBU, C_LEXT, C_NONE, C_REG, 31, 8, REGSB, 0},  //
	Optab{AMOVBU, C_LAUTO, C_NONE, C_REG, 31, 8, REGSP, 0}, //
	Optab{AMOVBU, C_LOREG, C_NONE, C_REG, 31, 8, 0, 0},     //
	Optab{AMOVBU, C_LOREG, C_NONE, C_REG, 31, 8, 0, 0},     //
	Optab{AMOVH, C_LEXT, C_NONE, C_REG, 31, 8, REGSB, 0},   //
	Optab{AMOVH, C_LAUTO, C_NONE, C_REG, 31, 8, REGSP, 0},  //
	Optab{AMOVH, C_LOREG, C_NONE, C_REG, 31, 8, 0, 0},      //
	Optab{AMOVH, C_LOREG, C_NONE, C_REG, 31, 8, 0, 0},      //
	Optab{AMOVW, C_LEXT, C_NONE, C_REG, 31, 8, REGSB, 0},   //
	Optab{AMOVW, C_LAUTO, C_NONE, C_REG, 31, 8, REGSP, 0},  //
	Optab{AMOVW, C_LOREG, C_NONE, C_REG, 31, 8, 0, 0},      //
	Optab{AMOVW, C_LOREG, C_NONE, C_REG, 31, 8, 0, 0},      //
	Optab{AMOV, C_LEXT, C_NONE, C_REG, 31, 8, REGSB, 0},    //
	Optab{AMOV, C_LAUTO, C_NONE, C_REG, 31, 8, REGSP, 0},   //
	Optab{AMOV, C_LOREG, C_NONE, C_REG, 31, 8, 0, 0},       //
	Optab{AMOV, C_LOREG, C_NONE, C_REG, 31, 8, 0, 0},       //

	/* load long effective stack address (load int32 offset and add) */
	Optab{AMOV, C_LACON, C_NONE, C_REG, 34, 8, REGSP, LFROM}, //

	/* pre/post-indexed load (unscaled, signed 9-bit offset) */
	Optab{AMOV, C_XPOST, C_NONE, C_REG, 22, 4, 0, 0},
	Optab{AMOVW, C_XPOST, C_NONE, C_REG, 22, 4, 0, 0},
	Optab{AMOVH, C_XPOST, C_NONE, C_REG, 22, 4, 0, 0},
	Optab{AMOVB, C_XPOST, C_NONE, C_REG, 22, 4, 0, 0},
	Optab{AMOVBU, C_XPOST, C_NONE, C_REG, 22, 4, 0, 0},
	Optab{AFMOVS, C_XPOST, C_NONE, C_FREG, 22, 4, 0, 0},
	Optab{AFMOVD, C_XPOST, C_NONE, C_FREG, 22, 4, 0, 0},
	Optab{AMOV, C_XPRE, C_NONE, C_REG, 22, 4, 0, 0},
	Optab{AMOVW, C_XPRE, C_NONE, C_REG, 22, 4, 0, 0},
	Optab{AMOVH, C_XPRE, C_NONE, C_REG, 22, 4, 0, 0},
	Optab{AMOVB, C_XPRE, C_NONE, C_REG, 22, 4, 0, 0},
	Optab{AMOVBU, C_XPRE, C_NONE, C_REG, 22, 4, 0, 0},
	Optab{AFMOVS, C_XPRE, C_NONE, C_FREG, 22, 4, 0, 0},
	Optab{AFMOVD, C_XPRE, C_NONE, C_FREG, 22, 4, 0, 0},

	/* pre/post-indexed store (unscaled, signed 9-bit offset) */
	Optab{AMOV, C_REG, C_NONE, C_XPOST, 23, 4, 0, 0},
	Optab{AMOVW, C_REG, C_NONE, C_XPOST, 23, 4, 0, 0},
	Optab{AMOVH, C_REG, C_NONE, C_XPOST, 23, 4, 0, 0},
	Optab{AMOVB, C_REG, C_NONE, C_XPOST, 23, 4, 0, 0},
	Optab{AMOVBU, C_REG, C_NONE, C_XPOST, 23, 4, 0, 0},
	Optab{AFMOVS, C_FREG, C_NONE, C_XPOST, 23, 4, 0, 0},
	Optab{AFMOVD, C_FREG, C_NONE, C_XPOST, 23, 4, 0, 0},
	Optab{AMOV, C_REG, C_NONE, C_XPRE, 23, 4, 0, 0},
	Optab{AMOVW, C_REG, C_NONE, C_XPRE, 23, 4, 0, 0},
	Optab{AMOVH, C_REG, C_NONE, C_XPRE, 23, 4, 0, 0},
	Optab{AMOVB, C_REG, C_NONE, C_XPRE, 23, 4, 0, 0},
	Optab{AMOVBU, C_REG, C_NONE, C_XPRE, 23, 4, 0, 0},
	Optab{AFMOVS, C_FREG, C_NONE, C_XPRE, 23, 4, 0, 0},
	Optab{AFMOVD, C_FREG, C_NONE, C_XPRE, 23, 4, 0, 0},

	/* special */
	Optab{AMOV, C_SPR, C_NONE, C_REG, 35, 4, 0, 0},
	Optab{AMRS, C_SPR, C_NONE, C_REG, 35, 4, 0, 0},
	Optab{AMOV, C_REG, C_NONE, C_SPR, 36, 4, 0, 0},
	Optab{AMSR, C_REG, C_NONE, C_SPR, 36, 4, 0, 0},
	Optab{AMOV, C_VCON, C_NONE, C_SPR, 37, 4, 0, 0},
	Optab{AMSR, C_VCON, C_NONE, C_SPR, 37, 4, 0, 0},
	Optab{AERET, C_NONE, C_NONE, C_NONE, 41, 4, 0, 0},
	Optab{AFMOVS, C_FREG, C_NONE, C_SEXT4, 20, 4, REGSB, 0},
	Optab{AFMOVS, C_FREG, C_NONE, C_UAUTO16K, 20, 4, REGSP, 0},
	Optab{AFMOVS, C_FREG, C_NONE, C_NSAUTO, 20, 4, REGSP, 0},
	Optab{AFMOVS, C_FREG, C_NONE, C_ZOREG, 20, 4, 0, 0},
	Optab{AFMOVS, C_FREG, C_NONE, C_UOREG16K, 20, 4, 0, 0},
	Optab{AFMOVS, C_FREG, C_NONE, C_NSOREG, 20, 4, 0, 0},
	Optab{AFMOVD, C_FREG, C_NONE, C_SEXT8, 20, 4, REGSB, 0},
	Optab{AFMOVD, C_FREG, C_NONE, C_UAUTO32K, 20, 4, REGSP, 0},
	Optab{AFMOVD, C_FREG, C_NONE, C_NSAUTO, 20, 4, REGSP, 0},
	Optab{AFMOVD, C_FREG, C_NONE, C_ZOREG, 20, 4, 0, 0},
	Optab{AFMOVD, C_FREG, C_NONE, C_UOREG32K, 20, 4, 0, 0},
	Optab{AFMOVD, C_FREG, C_NONE, C_NSOREG, 20, 4, 0, 0},
	Optab{AFMOVS, C_SEXT4, C_NONE, C_FREG, 21, 4, REGSB, 0},
	Optab{AFMOVS, C_UAUTO16K, C_NONE, C_FREG, 21, 4, REGSP, 0},
	Optab{AFMOVS, C_NSAUTO, C_NONE, C_FREG, 21, 4, REGSP, 0},
	Optab{AFMOVS, C_ZOREG, C_NONE, C_FREG, 21, 4, 0, 0},
	Optab{AFMOVS, C_UOREG16K, C_NONE, C_FREG, 21, 4, 0, 0},
	Optab{AFMOVS, C_NSOREG, C_NONE, C_FREG, 21, 4, 0, 0},
	Optab{AFMOVD, C_SEXT8, C_NONE, C_FREG, 21, 4, REGSB, 0},
	Optab{AFMOVD, C_UAUTO32K, C_NONE, C_FREG, 21, 4, REGSP, 0},
	Optab{AFMOVD, C_NSAUTO, C_NONE, C_FREG, 21, 4, REGSP, 0},
	Optab{AFMOVD, C_ZOREG, C_NONE, C_FREG, 21, 4, 0, 0},
	Optab{AFMOVD, C_UOREG32K, C_NONE, C_FREG, 21, 4, 0, 0},
	Optab{AFMOVD, C_NSOREG, C_NONE, C_FREG, 21, 4, 0, 0},
	Optab{AFMOVS, C_FREG, C_NONE, C_LEXT, 30, 8, REGSB, LTO},
	Optab{AFMOVS, C_FREG, C_NONE, C_LAUTO, 30, 8, REGSP, LTO},
	Optab{AFMOVS, C_FREG, C_NONE, C_LOREG, 30, 8, 0, LTO},
	Optab{AFMOVS, C_LEXT, C_NONE, C_FREG, 31, 8, REGSB, LFROM},
	Optab{AFMOVS, C_LAUTO, C_NONE, C_FREG, 31, 8, REGSP, LFROM},
	Optab{AFMOVS, C_LOREG, C_NONE, C_FREG, 31, 8, 0, LFROM},
	Optab{AFMOVS, C_FREG, C_NONE, C_ADDR, 64, 8, 0, LTO},
	Optab{AFMOVS, C_ADDR, C_NONE, C_FREG, 65, 8, 0, LFROM},
	Optab{AFMOVD, C_FREG, C_NONE, C_ADDR, 64, 8, 0, LTO},
	Optab{AFMOVD, C_ADDR, C_NONE, C_FREG, 65, 8, 0, LFROM},
	Optab{AFADDS, C_FREG, C_NONE, C_FREG, 54, 4, 0, 0},
	Optab{AFADDS, C_FREG, C_REG, C_FREG, 54, 4, 0, 0},
	Optab{AFADDS, C_FCON, C_NONE, C_FREG, 54, 4, 0, 0},
	Optab{AFADDS, C_FCON, C_REG, C_FREG, 54, 4, 0, 0},
	Optab{AFMOVS, C_FCON, C_NONE, C_FREG, 54, 4, 0, 0},
	Optab{AFMOVS, C_FREG, C_NONE, C_FREG, 54, 4, 0, 0},
	Optab{AFMOVD, C_FCON, C_NONE, C_FREG, 54, 4, 0, 0},
	Optab{AFMOVD, C_FREG, C_NONE, C_FREG, 54, 4, 0, 0},
	Optab{AFCVTZSD, C_FREG, C_NONE, C_REG, 29, 4, 0, 0},
	Optab{ASCVTFD, C_REG, C_NONE, C_FREG, 29, 4, 0, 0},
	Optab{AFCMPS, C_FREG, C_REG, C_NONE, 56, 4, 0, 0},
	Optab{AFCMPS, C_FCON, C_REG, C_NONE, 56, 4, 0, 0},
	Optab{AFCCMPS, C_COND, C_REG, C_VCON, 57, 4, 0, 0},
	Optab{AFCSELD, C_COND, C_REG, C_FREG, 18, 4, 0, 0},
	Optab{AFCVTSD, C_FREG, C_NONE, C_FREG, 29, 4, 0, 0},
	Optab{ACASE, C_REG, C_NONE, C_REG, 62, 4 * 4, 0, 0},
	Optab{ABCASE, C_NONE, C_NONE, C_SBRA, 63, 4, 0, 0},
	Optab{ACLREX, C_NONE, C_NONE, C_VCON, 38, 4, 0, 0},
	Optab{ACLREX, C_NONE, C_NONE, C_NONE, 38, 4, 0, 0},
	Optab{ACBZ, C_REG, C_NONE, C_SBRA, 39, 4, 0, 0},
	Optab{ATBZ, C_VCON, C_REG, C_SBRA, 40, 4, 0, 0},
	Optab{ASYS, C_VCON, C_NONE, C_NONE, 50, 4, 0, 0},
	Optab{ASYS, C_VCON, C_REG, C_NONE, 50, 4, 0, 0},
	Optab{ASYSL, C_VCON, C_NONE, C_REG, 50, 4, 0, 0},
	Optab{ADMB, C_VCON, C_NONE, C_NONE, 51, 4, 0, 0},
	Optab{AHINT, C_VCON, C_NONE, C_NONE, 52, 4, 0, 0},
	Optab{ALDAR, C_ZOREG, C_NONE, C_REG, 58, 4, 0, 0},
	Optab{ALDXR, C_ZOREG, C_NONE, C_REG, 58, 4, 0, 0},
	Optab{ALDAXR, C_ZOREG, C_NONE, C_REG, 58, 4, 0, 0},
	Optab{ALDXP, C_ZOREG, C_REG, C_REG, 58, 4, 0, 0},
	Optab{ASTLR, C_REG, C_NONE, C_ZOREG, 66, 4, 0, 0},  // to3=C_NONE
	Optab{ASTXR, C_REG, C_NONE, C_ZOREG, 59, 4, 0, 0},  // to3=C_REG
	Optab{ASTLXR, C_REG, C_NONE, C_ZOREG, 59, 4, 0, 0}, // to3=C_REG
	Optab{ASTXP, C_REG, C_NONE, C_ZOREG, 59, 4, 0, 0},  // to3=C_REG

	Optab{AAESD, C_VREG, C_NONE, C_VREG, 29, 4, 0, 0},
	Optab{ASHA1C, C_VREG, C_REG, C_VREG, 1, 4, 0, 0},
	Optab{AUNDEF, C_NONE, C_NONE, C_NONE, 90, 4, 0, 0},
	Optab{AUSEFIELD, C_ADDR, C_NONE, C_NONE, 0, 0, 0, 0},
	Optab{APCDATA, C_VCON, C_NONE, C_VCON, 0, 0, 0, 0},
	Optab{AFUNCDATA, C_VCON, C_NONE, C_ADDR, 0, 0, 0, 0},
	Optab{ADUFFZERO, C_NONE, C_NONE, C_SBRA, 5, 4, 0, 0}, // same as AB/ABL
	Optab{ADUFFCOPY, C_NONE, C_NONE, C_SBRA, 5, 4, 0, 0}, // same as AB/ABL

	Optab{AXXX, C_NONE, C_NONE, C_NONE, 0, 4, 0, 0},
}

/*
 * internal class codes for different constant classes:
 * they partition the constant/offset range into disjoint ranges that
 * are somehow treated specially by one or more load/store instructions.
 */
var autoclass = []int{C_PSAUTO, C_NSAUTO, C_NPAUTO, C_PSAUTO, C_PPAUTO, C_UAUTO4K, C_UAUTO8K, C_UAUTO16K, C_UAUTO32K, C_UAUTO64K, C_LAUTO}

var oregclass = []int{C_ZOREG, C_NSOREG, C_NPOREG, C_PSOREG, C_PPOREG, C_UOREG4K, C_UOREG8K, C_UOREG16K, C_UOREG32K, C_UOREG64K, C_LOREG}

/*
 * valid pstate field values, and value to use in instruction
 */
var pstatefield = []struct {
	a uint32
	b uint32
}{
	struct {
		a uint32
		b uint32
	}{D_SPSel, 0<<16 | 4<<12 | 5<<5},
	struct {
		a uint32
		b uint32
	}{D_DAIFSet, 3<<16 | 4<<12 | 6<<5},
	struct {
		a uint32
		b uint32
	}{D_DAIFClr, 3<<16 | 4<<12 | 7<<5},
}

var pool struct {
	start uint32
	size  uint32
}

func prasm(p *obj.Prog) {
	fmt.Printf("%v\n", p)
}

func span7(ctxt *obj.Link, cursym *obj.LSym) {
	var p *obj.Prog
	var o *Optab
	var m int
	var bflag int
	var i int
	var c int32
	var psz int32
	var out [6]uint32
	var bp []byte

	p = cursym.Text
	if p == nil || p.Link == nil { // handle external functions and ELF section symbols
		return
	}
	ctxt.Cursym = cursym
	ctxt.Autosize = int32(p.To.Offset&0xffffffff) + 8

	if oprange[AAND].start == nil {
		buildop(ctxt)
	}

	bflag = 0
	c = 0
	p.Pc = int64(c)
	for p = p.Link; p != nil; p = p.Link {
		ctxt.Curp = p
		if p.As == ADWORD && (c&7) != 0 {
			c += 4
		}
		p.Pc = int64(c)
		if p.From.Type == D_CONST && p.From.Offset == 0 {
			p.From.Reg = REGZERO
		}
		if p.To.Type == D_CONST && p.To.Offset == 0 {
			p.To.Reg = REGZERO
		}
		o = oplook(ctxt, p)
		m = int(o.size)
		if m == 0 {
			if p.As != ANOP && p.As != AFUNCDATA && p.As != APCDATA {
				ctxt.Diag("zero-width instruction\n%v", p)
			}
			continue
		}

		switch o.flag & (LFROM | LTO) {
		case LFROM:
			addpool(ctxt, p, &p.From)

		case LTO:
			addpool(ctxt, p, &p.To)
			break
		}

		if p.As == AB || p.As == ARET || p.As == AERET || p.As == ARETURN { /* TO DO: other unconditional operations */
			checkpool(ctxt, p, 0)
		}
		c += int32(m)
		if ctxt.Blitrl != nil {
			checkpool(ctxt, p, 1)
		}
	}

	cursym.Size = int64(c)

	/*
	 * if any procedure is large enough to
	 * generate a large SBRA branch, then
	 * generate extra passes putting branches
	 * around jmps to fix. this is rare.
	 */
	for bflag != 0 {

		if ctxt.Debugvlog != 0 {
			fmt.Fprintf(ctxt.Bso, "%5.2f span1\n", obj.Cputime())
		}
		bflag = 0
		c = 0
		for p = cursym.Text; p != nil; p = p.Link {
			if p.As == ADWORD && (c&7) != 0 {
				c += 4
			}
			p.Pc = int64(c)
			o = oplook(ctxt, p)

			/* very large branches
			if(o->type == 6 && p->cond) {
				otxt = p->cond->pc - c;
				if(otxt < 0)
					otxt = -otxt;
				if(otxt >= (1L<<17) - 10) {
					q = ctxt->arch->prg();
					q->link = p->link;
					p->link = q;
					q->as = AB;
					q->to.type = D_BRANCH;
					q->cond = p->cond;
					p->cond = q;
					q = ctxt->arch->prg();
					q->link = p->link;
					p->link = q;
					q->as = AB;
					q->to.type = D_BRANCH;
					q->cond = q->link->link;
					bflag = 1;
				}
			}
			*/
			m = int(o.size)

			if m == 0 {
				if p.As != ANOP && p.As != AFUNCDATA && p.As != APCDATA {
					ctxt.Diag("zero-width instruction\n%v", p)
				}
				continue
			}

			c += int32(m)
		}
	}

	c += -c & (FuncAlign - 1)
	cursym.Size = int64(c)

	/*
	 * lay out the code, emitting code and data relocations.
	 */
	if ctxt.Tlsg == nil {

		ctxt.Tlsg = obj.Linklookup(ctxt, "runtime.tlsg", 0)
	}
	obj.Symgrow(ctxt, cursym, cursym.Size)
	bp = cursym.P
	psz = 0
	for p = cursym.Text.Link; p != nil; p = p.Link {
		ctxt.Pc = p.Pc
		ctxt.Curp = p
		o = oplook(ctxt, p)

		// need to align DWORDs on 8-byte boundary. The ISA doesn't
		// require it, but the various 64-bit loads we generate assume it.
		if o.as == ADWORD && psz%8 != 0 {

			bp[3] = 0
			bp[2] = bp[3]
			bp[1] = bp[2]
			bp[0] = bp[1]
			bp = bp[4:]
			psz += 4
		}

		if int(o.size) > 4*len(out) {
			log.Fatalf("out array in span7 is too small, need at least %d for %v", o.size/4, p)
		}
		asmout(ctxt, p, o, out[:])
		for i = 0; i < int(o.size/4); i++ {
			ctxt.Arch.ByteOrder.PutUint32(bp, out[i])
			bp = bp[4:]
			psz += 4
		}
	}
}

/*
 * when the first reference to the literal pool threatens
 * to go out of range of a 1Mb PC-relative offset
 * drop the pool now, and branch round it.
 */
func checkpool(ctxt *obj.Link, p *obj.Prog, skip int) {

	if pool.size >= 0xffff0 || !(ispcdisp(int32(p.Pc+4+int64(pool.size)-int64(pool.start)+8)) != 0) {
		flushpool(ctxt, p, skip)
	} else if p.Link == nil {
		flushpool(ctxt, p, 2)
	}
}

func flushpool(ctxt *obj.Link, p *obj.Prog, skip int) {
	var q *obj.Prog
	if ctxt.Blitrl != nil {
		if skip != 0 {
			if ctxt.Debugvlog != 0 && skip == 1 {
				fmt.Printf("note: flush literal pool at %#x: len=%d ref=%x\n", uint64(p.Pc+4), pool.size, pool.start)
			}
			q = ctxt.NewProg()
			q.As = AB
			q.To.Type = D_BRANCH
			q.Pcond = p.Link
			q.Link = ctxt.Blitrl
			q.Lineno = p.Lineno
			ctxt.Blitrl = q
		} else if p.Pc+int64(pool.size)-int64(pool.start) < 1024*1024 {
			return
		}
		ctxt.Elitrl.Link = p.Link
		p.Link = ctxt.Blitrl

		// BUG(minux): how to correctly handle line number for constant pool entries?
		// for now, we set line number to the last instruction preceding them at least
		// this won't bloat the .debug_line tables
		for ctxt.Blitrl != nil {

			ctxt.Blitrl.Lineno = p.Lineno
			ctxt.Blitrl = ctxt.Blitrl.Link
		}

		ctxt.Blitrl = nil /* BUG: should refer back to values until out-of-range */
		ctxt.Elitrl = nil
		pool.size = 0
		pool.start = 0
	}
}

/*
 * TO DO: hash
 */
func addpool(ctxt *obj.Link, p *obj.Prog, a *obj.Addr) {

	var q *obj.Prog
	var t obj.Prog
	var c int
	var sz int
	c = aclass(ctxt, a)
	t = *ctxt.NewProg()
	t.As = AWORD
	sz = 4

	// MOVW foo(SB), R is actually
	//	MOV addr, REGTEMP
	//	MOVW REGTEMP, R
	// where addr is the address of the DWORD containing the address of foo.
	if p.As == AMOV || c == C_ADDR || c == C_VCON {

		t.As = ADWORD
		sz = 8
	}

	switch c {
	// TODO(aram): remove.
	default:
		if a.Name != D_EXTERN {

			fmt.Printf("addpool: %v in %v shouldn't go to default case\n", DRconv(c), p)
		}

		t.To.Offset = a.Offset
		t.To.Sym = a.Sym
		t.To.Type = a.Type
		t.To.Name = a.Name

		/* This is here to work around a bug where we generate negative
		operands that match C_MOVCON, but we use them with
		instructions that only accept unsigned immediates. This
		will cause oplook to return a variant of the instruction
		that loads the negative constant from memory, rather than
		using the immediate form. Because of that load, we get here,
		so we need to know what to do with C_MOVCON.

		The correct fix is to use the "negation" instruction variant,
		e.g. CMN $1, R instead of CMP $-1, R, or SUB $1, R instead
		of ADD $-1, R. */
	case C_MOVCON,

		/* This is here because MOV uint12<<12, R is disabled in optab.
		Because of this, we need to load the constant from memory. */
		C_ADDCON,

		/* These are here because they are disabled in optab.
		Because of this, we need to load the constant from memory. */
		C_BITCON,
		C_ABCON,
		C_PSAUTO,
		C_PPAUTO,
		C_UAUTO4K,
		C_UAUTO8K,
		C_UAUTO16K,
		C_UAUTO32K,
		C_UAUTO64K,
		C_NSAUTO,
		C_NPAUTO,
		C_LAUTO,
		C_PPOREG,
		C_PSOREG,
		C_UOREG4K,
		C_UOREG8K,
		C_UOREG16K,
		C_UOREG32K,
		C_UOREG64K,
		C_NSOREG,
		C_NPOREG,
		C_LOREG,
		C_LACON,
		C_LCON,
		C_VCON:
		if a.Name == D_EXTERN {

			fmt.Printf("addpool: %v in %v needs reloc\n", DRconv(c), p)
		}

		t.To.Type = D_CONST
		t.To.Offset = ctxt.Instoffset
		break
	}

	for q = ctxt.Blitrl; q != nil; q = q.Link { /* could hash on t.t0.offset */
		if q.To == t.To {
			p.Pcond = q
			return
		}
	}

	q = ctxt.NewProg()
	*q = t
	q.Pc = int64(pool.size)
	if ctxt.Blitrl == nil {
		ctxt.Blitrl = q
		pool.start = uint32(p.Pc)
	} else {

		ctxt.Elitrl.Link = q
	}
	ctxt.Elitrl = q
	pool.size = -pool.size & (FuncAlign - 1)
	pool.size += uint32(sz)
	p.Pcond = q
}

func regoff(ctxt *obj.Link, a *obj.Addr) uint32 {
	ctxt.Instoffset = 0
	aclass(ctxt, a)
	return uint32(ctxt.Instoffset)
}

func ispcdisp(v int32) int {
	/* pc-relative addressing will reach? */
	return bool2int(v >= -0xfffff && v <= 0xfffff && (v&3) == 0)
}

func isaddcon(v int64) int {
	/* uimm12 or uimm24? */
	if v < 0 {

		return 0
	}
	if (v & 0xFFF) == 0 {
		v >>= 12
	}
	return bool2int(v <= 0xFFF)
}

func isbitcon(v uint64) int {
	/*  fancy bimm32 or bimm64? */
	return bool2int(findmask(v) != nil || (v>>32) == 0 && findmask(v|(v<<32)) != nil)
}

/*
 * return appropriate index into tables above
 */
func constclass(l int64) int {

	if l == 0 {
		return 0
	}
	if l < 0 {
		if l >= -256 {
			return 1
		}
		if l >= -512 && (l&7) == 0 {
			return 2
		}
		return 10
	}

	if l <= 255 {
		return 3
	}
	if l <= 504 && (l&7) == 0 {
		return 4
	}
	if l <= 4095 {
		return 5
	}
	if l <= 8190 && (l&1) == 0 {
		return 6
	}
	if l <= 16380 && (l&3) == 0 {
		return 7
	}
	if l <= 32760 && (l&7) == 0 {
		return 8
	}
	if l <= 65520 && (l&0xF) == 0 {
		return 9
	}
	return 10
}

/*
 * given an offset v and a class c (see above)
 * return the offset value to use in the instruction,
 * scaled if necessary
 */
func offsetshift(ctxt *obj.Link, v int64, c int) int64 {

	var vs int64
	var s int
	var shifts = []int{0, 1, 2, 3, 4}
	s = 0
	if c >= C_SEXT1 && c <= C_SEXT16 {
		s = shifts[c-C_SEXT1]
	} else if c >= C_UAUTO4K && c <= C_UAUTO64K {
		s = shifts[c-C_UAUTO4K]
	} else if c >= C_UOREG4K && c <= C_UOREG64K {
		s = shifts[c-C_UOREG4K]
	}
	vs = v >> uint(s)
	if vs<<uint(s) != v {
		ctxt.Diag("odd offset: %d\n%v", v, ctxt.Curp)
	}
	return vs
}

/*
 * if v contains a single 16-bit value aligned
 * on a 16-bit field, and thus suitable for movk/movn,
 * return the field index 0 to 3; otherwise return -1
 */
func movcon(v int64) int {

	var s int
	for s = 0; s < 64; s += 16 {
		if (uint64(v) &^ (uint64(0xFFFF) << uint(s))) == 0 {
			return s / 16
		}
	}
	return -1
}

func aclass(ctxt *obj.Link, a *obj.Addr) int {
	var v int64
	var s *obj.LSym
	var t int
	ctxt.Instoffset = 0
	switch a.Type {
	case D_NONE:
		return C_NONE

	case D_REG:
		return C_REG

	case D_VREG:
		return C_VREG

	case D_SP:
		return C_RSP

	case D_COND:
		return C_COND

	case D_SHIFT:
		return C_SHIFT

	case D_EXTREG:
		return C_EXTREG

	case D_ROFF:
		return C_ROFF

	case D_XPOST:
		return C_XPOST

	case D_XPRE:
		return C_XPRE

	case D_FREG:
		return C_FREG

	case D_OREG:
		switch a.Name {
		case D_EXTERN,
			D_STATIC:
			if a.Sym == nil {
				break
			}
			ctxt.Instoffset = a.Offset
			if a.Sym != nil { // use relocation
				return C_ADDR
			}
			return C_LEXT

		case D_AUTO:
			ctxt.Instoffset = int64(ctxt.Autosize) + a.Offset
			return autoclass[constclass(ctxt.Instoffset)]

		case D_PARAM:
			ctxt.Instoffset = int64(ctxt.Autosize) + a.Offset + 8
			return autoclass[constclass(ctxt.Instoffset)]

		case D_NONE:
			ctxt.Instoffset = a.Offset
			return oregclass[constclass(ctxt.Instoffset)]
		}

		return C_GOK

	case D_SPR:
		return C_SPR

	case D_OCONST:
		switch a.Name {
		case D_EXTERN,
			D_STATIC:
			if a.Sym == nil {
				break
			}
			ctxt.Instoffset = a.Offset
			if a.Sym != nil { // use relocation
				return C_ADDR
			}
			return C_VCON
		}

		return C_GOK

	case D_FCONST:
		return C_FCON

	case D_CONST:
		switch a.Name {
		case D_NONE:
			ctxt.Instoffset = a.Offset
			if a.Reg != NREG && a.Reg != REGZERO {
				goto aconsize
			}
			v = ctxt.Instoffset
			if v == 0 {
				return C_ZCON
			}
			if isaddcon(v) != 0 {
				if v <= 0xFFF {
					return C_ADDCON0
				}
				if isbitcon(uint64(v)) != 0 {
					return C_ABCON
				}
				return C_ADDCON
			}

			t = movcon(v)
			if t >= 0 {
				if isbitcon(uint64(v)) != 0 {
					return C_MBCON
				}
				return C_MOVCON
			}

			t = movcon(^v)
			if t >= 0 {
				if isbitcon(uint64(v)) != 0 {
					return C_MBCON
				}
				return C_MOVCON
			}

			if isbitcon(uint64(v)) != 0 {
				return C_BITCON
			}
			return C_VCON

		case D_EXTERN,
			D_STATIC:
			s = a.Sym
			if s == nil {
				break
			}
			ctxt.Instoffset = a.Offset
			return C_VCONADDR

		case D_AUTO:
			ctxt.Instoffset = int64(ctxt.Autosize) + a.Offset
			goto aconsize

		case D_PARAM:
			ctxt.Instoffset = int64(ctxt.Autosize) + a.Offset + 8
			goto aconsize
		}

		return C_GOK

	aconsize:
		if isaddcon(ctxt.Instoffset) != 0 {
			return C_AACON
		}
		return C_LACON

	case D_BRANCH:
		return C_SBRA
	}

	return C_GOK
}

func oplook(ctxt *obj.Link, p *obj.Prog) *Optab {
	var a1 int
	var a2 int
	var a3 int
	var r int
	var c1 []byte
	var c2 []byte
	var c3 []byte
	var o []Optab
	var e []Optab
	a1 = int(p.Optab)
	if a1 != 0 {
		return &optab[a1-1:][0]
	}
	a1 = int(p.From.Class)
	if a1 == 0 {
		a1 = aclass(ctxt, &p.From) + 1
		p.From.Class = int8(a1)
	}

	a1--
	a3 = int(p.To.Class)
	if a3 == 0 {
		a3 = aclass(ctxt, &p.To) + 1
		p.To.Class = int8(a3)
	}

	a3--
	a2 = C_NONE
	if p.Reg != NREG {
		a2 = C_REG
	}
	r = int(p.As)
	o = oprange[r].start
	if o == nil {
		a1 = int(opcross[repop[r]][a1][a2][a3])
		if a1 != 0 {
			p.Optab = uint16(a1 + 1)
			return &optab[a1:][0]
		}

		o = oprange[r].stop /* just generate an error */
	}

	if false {
		fmt.Printf("oplook %v %d %d %d\n", Aconv(int(p.As)), a1, a2, a3)
		fmt.Printf("\t\t%d %d\n", p.From.Type, p.To.Type)
	}

	e = oprange[r].stop
	c1 = xcmp[a1][:]
	c2 = xcmp[a2][:]
	c3 = xcmp[a3][:]
	for ; -cap(o) < -cap(e); o = o[1:] {
		if int(o[0].a2) == a2 || c2[o[0].a2] != 0 {
			if c1[o[0].a1] != 0 {
				if c3[o[0].a3] != 0 {
					p.Optab = uint16((-cap(o) + cap(optab)) + 1)
					return &o[0]
				}
			}
		}
	}

	ctxt.Diag("illegal combination %v %v %v %v, %d %d", p, DRconv(a1), DRconv(a2), DRconv(a3), p.From.Type, p.To.Type)
	prasm(p)
	if o == nil {
		o = optab
	}
	return &o[0]
}

func cmp(a int, b int) bool {
	if a == b {
		return true
	}
	switch a {
	case C_RSP:
		if b == C_REG {
			return true
		}

	case C_REG:
		if b == C_ZCON {
			return true
		}

	case C_ADDCON0:
		if b == C_ZCON {
			return true
		}

	case C_ADDCON:
		if b == C_ZCON || b == C_ADDCON0 || b == C_ABCON {
			return true
		}

	case C_BITCON:
		if b == C_ABCON || b == C_MBCON {
			return true
		}

	case C_MOVCON:
		if b == C_MBCON || b == C_ZCON || b == C_ADDCON0 {
			return true
		}

	case C_LCON:
		if b == C_ZCON || b == C_BITCON || b == C_ADDCON || b == C_ADDCON0 || b == C_ABCON || b == C_MBCON || b == C_MOVCON {
			return true
		}

	case C_VCON:
		if b == C_VCONADDR {
			return true
		} else {

			return cmp(C_LCON, b)
		}
		fallthrough

	case C_LACON:
		if b == C_AACON {
			return true
		}

	case C_SEXT2:
		if b == C_SEXT1 {
			return true
		}

	case C_SEXT4:
		if b == C_SEXT1 || b == C_SEXT2 {
			return true
		}

	case C_SEXT8:
		if b >= C_SEXT1 && b <= C_SEXT4 {
			return true
		}

	case C_SEXT16:
		if b >= C_SEXT1 && b <= C_SEXT8 {
			return true
		}

	case C_LEXT:
		if b >= C_SEXT1 && b <= C_SEXT16 {
			return true
		}

	case C_PPAUTO:
		if b == C_PSAUTO {
			return true
		}

	case C_UAUTO4K:
		if b == C_PSAUTO || b == C_PPAUTO {
			return true
		}

	case C_UAUTO8K:
		return cmp(C_UAUTO4K, b)

	case C_UAUTO16K:
		return cmp(C_UAUTO8K, b)

	case C_UAUTO32K:
		return cmp(C_UAUTO16K, b)

	case C_UAUTO64K:
		return cmp(C_UAUTO32K, b)

	case C_NPAUTO:
		return cmp(C_NSAUTO, b)

	case C_LAUTO:
		return cmp(C_NPAUTO, b) || cmp(C_UAUTO64K, b)

	case C_PSOREG:
		if b == C_ZOREG {
			return true
		}

	case C_PPOREG:
		if b == C_ZOREG || b == C_PSOREG {
			return true
		}

	case C_UOREG4K:
		if b == C_ZOREG || b == C_PSAUTO || b == C_PSOREG || b == C_PPAUTO || b == C_PPOREG {
			return true
		}

	case C_UOREG8K:
		return cmp(C_UOREG4K, b)

	case C_UOREG16K:
		return cmp(C_UOREG8K, b)

	case C_UOREG32K:
		return cmp(C_UOREG16K, b)

	case C_UOREG64K:
		return cmp(C_UOREG32K, b)

	case C_NPOREG:
		return cmp(C_NSOREG, b)

	case C_LOREG:
		return cmp(C_NPOREG, b) || cmp(C_UOREG64K, b)

	case C_LBRA:
		if b == C_SBRA {
			return true
		}
		break
	}

	return false
}

type ocmp []Optab

func (x ocmp) Len() int {
	return len(x)
}

func (x ocmp) Swap(i, j int) {
	x[i], x[j] = x[j], x[i]
}

func (x ocmp) Less(i, j int) bool {
	var p1 *Optab
	var p2 *Optab
	var n int
	p1 = &x[i]
	p2 = &x[j]
	n = int(p1.as) - int(p2.as)
	if n != 0 {
		return n < 0
	}
	n = int(p1.a1) - int(p2.a1)
	if n != 0 {
		return n < 0
	}
	n = int(p1.a2) - int(p2.a2)
	if n != 0 {
		return n < 0
	}
	n = int(p1.a3) - int(p2.a3)
	if n != 0 {
		return n < 0
	}
	return false
}

func buildop(ctxt *obj.Link) {
	var i int
	var n int
	var r int
	var t Oprang
	for i = 0; i < C_GOK; i++ {
		for n = 0; n < C_GOK; n++ {
			if cmp(n, i) {
				xcmp[i][n] = 1
			}
		}
	}
	for n = 0; optab[n].as != AXXX; n++ {

	}
	sort.Sort(ocmp(optab[:n]))
	for i = 0; i < n; i++ {
		r = int(optab[i].as)
		oprange[r].start = optab[i:]
		for int(optab[i].as) == r {
			i++
		}
		oprange[r].stop = optab[i:]
		i--
		t = oprange[r]
		switch r {
		default:
			ctxt.Diag("unknown op in build: %v", Aconv(r))
			log.Fatalf("bad code")

		case AXXX:
			break

		case AADD:
			oprange[AADDS] = t
			oprange[ASUB] = t
			oprange[ASUBS] = t
			oprange[AADDW] = t
			oprange[AADDSW] = t
			oprange[ASUBW] = t
			oprange[ASUBSW] = t

		case AAND: /* logical immediate, logical shifted register */
			oprange[AANDS] = t

			oprange[AANDSW] = t
			oprange[AANDW] = t
			oprange[AEOR] = t
			oprange[AEORW] = t
			oprange[AORR] = t
			oprange[AORRW] = t

		case ABIC: /* only logical shifted register */
			oprange[ABICS] = t

			oprange[ABICSW] = t
			oprange[ABICW] = t
			oprange[AEON] = t
			oprange[AEONW] = t
			oprange[AORN] = t
			oprange[AORNW] = t

		case ANEG:
			oprange[ANEGS] = t
			oprange[ANEGSW] = t
			oprange[ANEGW] = t

		case AADC: /* rn=Rd */
			oprange[AADCW] = t

			oprange[AADCS] = t
			oprange[AADCSW] = t
			oprange[ASBC] = t
			oprange[ASBCW] = t
			oprange[ASBCS] = t
			oprange[ASBCSW] = t

		case ANGC: /* rn=REGZERO */
			oprange[ANGCW] = t

			oprange[ANGCS] = t
			oprange[ANGCSW] = t

		case ACMP:
			oprange[ACMPW] = t
			oprange[ACMN] = t
			oprange[ACMNW] = t

		case ATST:
			oprange[ATSTW] = t

			/* register/register, and shifted */
		case AMVN:
			oprange[AMVNW] = t

		case AMOVK:
			oprange[AMOVKW] = t
			oprange[AMOVN] = t
			oprange[AMOVNW] = t
			oprange[AMOVZ] = t
			oprange[AMOVZW] = t

		case ABEQ:
			oprange[ABNE] = t
			oprange[ABCS] = t
			oprange[ABHS] = t
			oprange[ABCC] = t
			oprange[ABLO] = t
			oprange[ABMI] = t
			oprange[ABPL] = t
			oprange[ABVS] = t
			oprange[ABVC] = t
			oprange[ABHI] = t
			oprange[ABLS] = t
			oprange[ABGE] = t
			oprange[ABLT] = t
			oprange[ABGT] = t
			oprange[ABLE] = t

		case ALSL:
			oprange[ALSLW] = t
			oprange[ALSR] = t
			oprange[ALSRW] = t
			oprange[AASR] = t
			oprange[AASRW] = t
			oprange[AROR] = t
			oprange[ARORW] = t

		case ACLS:
			oprange[ACLSW] = t
			oprange[ACLZ] = t
			oprange[ACLZW] = t
			oprange[ARBIT] = t
			oprange[ARBITW] = t
			oprange[AREV] = t
			oprange[AREVW] = t
			oprange[AREV16] = t
			oprange[AREV16W] = t
			oprange[AREV32] = t

		case ASDIV:
			oprange[ASDIVW] = t
			oprange[AUDIV] = t
			oprange[AUDIVW] = t
			oprange[ACRC32B] = t
			oprange[ACRC32CB] = t
			oprange[ACRC32CH] = t
			oprange[ACRC32CW] = t
			oprange[ACRC32CX] = t
			oprange[ACRC32H] = t
			oprange[ACRC32W] = t
			oprange[ACRC32X] = t

		case AMADD:
			oprange[AMADDW] = t
			oprange[AMSUB] = t
			oprange[AMSUBW] = t
			oprange[ASMADDL] = t
			oprange[ASMSUBL] = t
			oprange[AUMADDL] = t
			oprange[AUMSUBL] = t

		case AREM:
			oprange[AREMW] = t
			oprange[AUREM] = t
			oprange[AUREMW] = t

		case AMUL:
			oprange[AMULW] = t
			oprange[AMNEG] = t
			oprange[AMNEGW] = t
			oprange[ASMNEGL] = t
			oprange[ASMULL] = t
			oprange[ASMULH] = t
			oprange[AUMNEGL] = t
			oprange[AUMULH] = t
			oprange[AUMULL] = t

		case AMOVB:
			oprange[AMOVBU] = t

		case AMOVH:
			oprange[AMOVHU] = t

		case AMOVW:
			oprange[AMOVWU] = t

		case ABFM:
			oprange[ABFMW] = t
			oprange[ASBFM] = t
			oprange[ASBFMW] = t
			oprange[AUBFM] = t
			oprange[AUBFMW] = t

		case ABFI:
			oprange[ABFIW] = t
			oprange[ABFXIL] = t
			oprange[ABFXILW] = t
			oprange[ASBFIZ] = t
			oprange[ASBFIZW] = t
			oprange[ASBFX] = t
			oprange[ASBFXW] = t
			oprange[AUBFIZ] = t
			oprange[AUBFIZW] = t
			oprange[AUBFX] = t
			oprange[AUBFXW] = t

		case AEXTR:
			oprange[AEXTRW] = t

		case ASXTB:
			oprange[ASXTBW] = t
			oprange[ASXTH] = t
			oprange[ASXTHW] = t
			oprange[ASXTW] = t
			oprange[AUXTB] = t
			oprange[AUXTH] = t
			oprange[AUXTW] = t
			oprange[AUXTBW] = t
			oprange[AUXTHW] = t

		case ACCMN:
			oprange[ACCMNW] = t
			oprange[ACCMP] = t
			oprange[ACCMPW] = t

		case ACSEL:
			oprange[ACSELW] = t
			oprange[ACSINC] = t
			oprange[ACSINCW] = t
			oprange[ACSINV] = t
			oprange[ACSINVW] = t
			oprange[ACSNEG] = t
			oprange[ACSNEGW] = t

			// aliases Rm=Rn, !cond
			oprange[ACINC] = t

			oprange[ACINCW] = t
			oprange[ACINV] = t
			oprange[ACINVW] = t
			oprange[ACNEG] = t
			oprange[ACNEGW] = t

			// aliases, Rm=Rn=REGZERO, !cond
		case ACSET:
			oprange[ACSETW] = t

			oprange[ACSETM] = t
			oprange[ACSETMW] = t

		case AMOV,
			AMOVBU,
			AB,
			ABL,
			AWORD,
			ADWORD,
			ARET,
			ATEXT,
			ACASE,
			ABCASE:
			break

		case AERET:
			oprange[ANOP] = t
			oprange[AWFE] = t
			oprange[AWFI] = t
			oprange[AYIELD] = t
			oprange[ASEV] = t
			oprange[ASEVL] = t
			oprange[ADRPS] = t

		case ACBZ:
			oprange[ACBZW] = t
			oprange[ACBNZ] = t
			oprange[ACBNZW] = t

		case ATBZ:
			oprange[ATBNZ] = t

		case AADR,
			AADRP:
			break

		case ACLREX:
			break

		case ASVC:
			oprange[AHLT] = t
			oprange[AHVC] = t
			oprange[ASMC] = t
			oprange[ABRK] = t
			oprange[ADCPS1] = t
			oprange[ADCPS2] = t
			oprange[ADCPS3] = t

		case AFADDS:
			oprange[AFADDD] = t
			oprange[AFSUBS] = t
			oprange[AFSUBD] = t
			oprange[AFMULS] = t
			oprange[AFMULD] = t
			oprange[AFNMULS] = t
			oprange[AFNMULD] = t
			oprange[AFDIVS] = t
			oprange[AFMAXD] = t
			oprange[AFMAXS] = t
			oprange[AFMIND] = t
			oprange[AFMINS] = t
			oprange[AFMAXNMD] = t
			oprange[AFMAXNMS] = t
			oprange[AFMINNMD] = t
			oprange[AFMINNMS] = t
			oprange[AFDIVD] = t

		case AFCVTSD:
			oprange[AFCVTDS] = t
			oprange[AFABSD] = t
			oprange[AFABSS] = t
			oprange[AFNEGD] = t
			oprange[AFNEGS] = t
			oprange[AFSQRTD] = t
			oprange[AFSQRTS] = t
			oprange[AFRINTNS] = t
			oprange[AFRINTND] = t
			oprange[AFRINTPS] = t
			oprange[AFRINTPD] = t
			oprange[AFRINTMS] = t
			oprange[AFRINTMD] = t
			oprange[AFRINTZS] = t
			oprange[AFRINTZD] = t
			oprange[AFRINTAS] = t
			oprange[AFRINTAD] = t
			oprange[AFRINTXS] = t
			oprange[AFRINTXD] = t
			oprange[AFRINTIS] = t
			oprange[AFRINTID] = t
			oprange[AFCVTDH] = t
			oprange[AFCVTHS] = t
			oprange[AFCVTHD] = t
			oprange[AFCVTSH] = t

		case AFCMPS:
			oprange[AFCMPD] = t
			oprange[AFCMPES] = t
			oprange[AFCMPED] = t

		case AFCCMPS:
			oprange[AFCCMPD] = t
			oprange[AFCCMPES] = t
			oprange[AFCCMPED] = t

		case AFCSELD:
			oprange[AFCSELS] = t

		case AFMOVS,
			AFMOVD:
			break

		case AFCVTZSD:
			oprange[AFCVTZSDW] = t
			oprange[AFCVTZSS] = t
			oprange[AFCVTZSSW] = t
			oprange[AFCVTZUD] = t
			oprange[AFCVTZUDW] = t
			oprange[AFCVTZUS] = t
			oprange[AFCVTZUSW] = t

		case ASCVTFD:
			oprange[ASCVTFS] = t
			oprange[ASCVTFWD] = t
			oprange[ASCVTFWS] = t
			oprange[AUCVTFD] = t
			oprange[AUCVTFS] = t
			oprange[AUCVTFWD] = t
			oprange[AUCVTFWS] = t

		case ASYS:
			oprange[AAT] = t
			oprange[ADC] = t
			oprange[AIC] = t
			oprange[ATLBI] = t

		case ASYSL,
			AHINT:
			break

		case ADMB:
			oprange[ADSB] = t
			oprange[AISB] = t

		case AMRS,
			AMSR:
			break

		case ALDAR:
			oprange[ALDARW] = t
			fallthrough

		case ALDXR:
			oprange[ALDXRB] = t
			oprange[ALDXRH] = t
			oprange[ALDXRW] = t

		case ALDAXR:
			oprange[ALDAXRW] = t

		case ALDXP:
			oprange[ALDXPW] = t

		case ASTLR:
			oprange[ASTLRW] = t

		case ASTXR:
			oprange[ASTXRB] = t
			oprange[ASTXRH] = t
			oprange[ASTXRW] = t

		case ASTLXR:
			oprange[ASTLXRW] = t

		case ASTXP:
			oprange[ASTXPW] = t

		case AAESD:
			oprange[AAESE] = t
			oprange[AAESMC] = t
			oprange[AAESIMC] = t
			oprange[ASHA1H] = t
			oprange[ASHA1SU1] = t
			oprange[ASHA256SU0] = t

		case ASHA1C:
			oprange[ASHA1P] = t
			oprange[ASHA1M] = t
			oprange[ASHA1SU0] = t
			oprange[ASHA256H] = t
			oprange[ASHA256H2] = t
			oprange[ASHA256SU1] = t

		case AUNDEF,
			AUSEFIELD,
			AFUNCDATA,
			APCDATA,
			ADUFFZERO,
			ADUFFCOPY:
			break
		}
	}
}

func chipfloat7(ctxt *obj.Link, e float64) int {
	var n int
	var h1 uint32
	var l uint32
	var h uint32
	var ei uint64

	ei = math.Float64bits(e)
	l = uint32(int32(ei))
	h = uint32(int32(ei >> 32))

	if l != 0 || h&0xffff != 0 {
		goto no
	}
	h1 = h & 0x7fc00000
	if h1 != 0x40000000 && h1 != 0x3fc00000 {
		goto no
	}
	n = 0

	// sign bit (a)
	if h&0x80000000 != 0 {

		n |= 1 << 7
	}

	// exp sign bit (b)
	if h1 == 0x3fc00000 {

		n |= 1 << 6
	}

	// rest of exp and mantissa (cd-efgh)
	n |= int((h >> 16) & 0x3f)

	//print("match %.8lux %.8lux %d\n", l, h, n);
	return n

no:
	return -1
}

func asmout(ctxt *obj.Link, p *obj.Prog, o *Optab, out []uint32) {
	var o1 uint32
	var o2 uint32
	var o3 uint32
	var o4 uint32
	var o5 uint32
	var v int32
	var hi int32
	var u uint32
	var d int64
	var r int
	var s int
	var rf int
	var rt int
	var ra int
	var nzcv int
	var cond int
	var i int
	var as int
	var mask *Mask
	var rel *obj.Reloc
	var lastcase *obj.Prog

	o1 = 0
	o2 = 0
	o3 = 0
	o4 = 0
	o5 = 0
	if false { /*debug['P']*/
		fmt.Printf("%x: %v\ttype %d\n", uint32(p.Pc), p, o.type_)
	}
	switch o.type_ {
	default:
		ctxt.Diag("unknown asm %d", o.type_)
		prasm(p)

	case 0: /* pseudo ops */
		break

	case 1: /* op Rm,[Rn],Rd; default Rn=Rd -> op Rm<<0,[Rn,]Rd (shifted register) */
		o1 = oprrr(ctxt, int(p.As))

		rf = int(p.From.Reg)
		rt = int(p.To.Reg)
		r = int(p.Reg)
		if p.To.Type == D_NONE {
			rt = REGZERO
		}
		if r == NREG {
			r = rt
		}
		o1 |= (uint32(rf) << 16) | (uint32(r) << 5) | uint32(rt)

	case 2: /* add/sub $(uimm12|uimm24)[,R],R; cmp $(uimm12|uimm24),R */
		o1 = opirr(ctxt, int(p.As))

		rt = int(p.To.Reg)
		if p.To.Type == D_NONE {
			if (o1 & Sbit) == 0 {
				ctxt.Diag("ineffective ZR destination\n%v", p)
			}
			rt = REGZERO
		}

		r = int(p.Reg)
		if r == NREG {
			r = rt
		}
		v = int32(regoff(ctxt, &p.From))
		o1 = oaddi(int32(o1), v, r, rt)

	case 3: /* op R<<n[,R],R (shifted register) */
		o1 = oprrr(ctxt, int(p.As))

		o1 |= uint32(p.From.Offset) /* includes reg, op, etc */
		rt = int(p.To.Reg)
		if p.To.Type == D_NONE {
			rt = REGZERO
		}
		r = int(p.Reg)
		if p.As == AMVN || p.As == AMVNW {
			r = REGZERO
		} else if r == NREG {
			r = rt
		}
		o1 |= (uint32(r) << 5) | uint32(rt)

	case 4: /* mov $addcon, R; mov $recon, R; mov $racon, R */
		o1 = opirr(ctxt, int(p.As))

		rt = int(p.To.Reg)
		r = int(o.param)
		if r == 0 {
			r = REGZERO
		}
		v = int32(regoff(ctxt, &p.From))
		if (v & 0xFFF000) != 0 {
			v >>= 12
			o1 |= 1 << 22 /* shift, by 12 */
		}

		o1 |= ((uint32(v) & 0xFFF) << 10) | (uint32(r) << 5) | uint32(rt)

	case 5: /* b s; bl s */
		o1 = opbra(ctxt, int(p.As))

		if p.To.Sym == nil {
			o1 |= uint32(brdist(ctxt, p, 0, 26, 2))
			break
		}

		rel = obj.Addrel(ctxt.Cursym)
		rel.Off = int32(ctxt.Pc)
		rel.Siz = 4
		rel.Sym = p.To.Sym
		rel.Add = int64(o1) | (p.To.Offset>>2)&0x3ffffff
		rel.Type = obj.R_CALLARM64

	case 6: /* b ,O(R); bl ,O(R) */
		o1 = opbrr(ctxt, int(p.As))

		o1 |= uint32(p.To.Reg) << 5
		rel = obj.Addrel(ctxt.Cursym)
		rel.Off = int32(ctxt.Pc)
		rel.Siz = 0
		rel.Type = obj.R_CALLIND

	case 7: /* beq s */
		o1 = opbra(ctxt, int(p.As))

		o1 |= uint32(brdist(ctxt, p, 0, 19, 2) << 5)

	case 8: /* lsl $c,[R],R -> ubfm $(W-1)-c,$(-c MOD (W-1)),Rn,Rd */
		rt = int(p.To.Reg)

		rf = int(p.Reg)
		if rf == NREG {
			rf = rt
		}
		v = int32(p.From.Offset)
		switch p.As {
		case AASR:
			o1 = opbfm(ctxt, ASBFM, int(v), 63, rf, rt)

		case AASRW:
			o1 = opbfm(ctxt, ASBFMW, int(v), 31, rf, rt)

		case ALSL:
			o1 = opbfm(ctxt, AUBFM, int((64-v)&63), int(63-v), rf, rt)

		case ALSLW:
			o1 = opbfm(ctxt, AUBFMW, int((32-v)&31), int(31-v), rf, rt)

		case ALSR:
			o1 = opbfm(ctxt, AUBFM, int(v), 63, rf, rt)

		case ALSRW:
			o1 = opbfm(ctxt, AUBFMW, int(v), 31, rf, rt)

		case AROR:
			o1 = opextr(ctxt, AEXTR, v, rf, rf, rt)

		case ARORW:
			o1 = opextr(ctxt, AEXTRW, v, rf, rf, rt)

		default:
			ctxt.Diag("bad shift $con\n%v", ctxt.Curp)
			break
		}

	case 9: /* lsl Rm,[Rn],Rd -> lslv Rm, Rn, Rd */
		o1 = oprrr(ctxt, int(p.As))

		r = int(p.Reg)
		if r == NREG {
			r = int(p.To.Reg)
		}
		o1 |= (uint32(p.From.Reg) << 16) | (uint32(r) << 5) | uint32(p.To.Reg)

	case 10: /* brk/hvc/.../svc [$con] */
		o1 = opimm(ctxt, int(p.As))

		if p.To.Type != D_NONE {
			o1 |= uint32((p.To.Offset & 0xffff) << 5)
		}

	case 11: /* dword */
		aclass(ctxt, &p.To)

		o1 = uint32(ctxt.Instoffset)
		o2 = uint32(ctxt.Instoffset >> 32)
		if p.To.Sym != nil {
			rel = obj.Addrel(ctxt.Cursym)
			rel.Off = int32(ctxt.Pc)
			rel.Siz = 8
			rel.Sym = p.To.Sym
			rel.Add = p.To.Offset
			rel.Type = obj.R_ADDR
			o2 = 0
			o1 = o2
		}

	case 12: /* movT $vcon, reg */
		o1 = omovlit(ctxt, int(p.As), p, &p.From, int(p.To.Reg))

	case 13: /* addop $vcon, [R], R (64 bit literal); cmp $lcon,R -> addop $lcon,R, ZR */
		o1 = omovlit(ctxt, AMOV, p, &p.From, REGTMP)

		if !(o1 != 0) {
			break
		}
		rt = int(p.To.Reg)
		if p.To.Type == D_NONE {
			rt = REGZERO
		}
		r = int(p.Reg)
		if r == NREG {
			r = rt
		}
		if p.To.Type != D_NONE && (p.To.Reg == REGSP || r == REGSP) {
			o2 = opxrrr(ctxt, int(p.As))
			o2 |= REGTMP << 16
			o2 |= LSL0_64
		} else {

			o2 = oprrr(ctxt, int(p.As))
			o2 |= REGTMP << 16 /* shift is 0 */
		}

		o2 |= uint32(r) << 5
		o2 |= uint32(rt)

	case 14: /* word */
		if aclass(ctxt, &p.To) == C_ADDR {

			ctxt.Diag("address constant needs DWORD\n%v", p)
		}
		o1 = uint32(ctxt.Instoffset)
		if p.To.Sym != nil {
			// This case happens with words generated
			// in the PC stream as part of the literal pool.
			rel = obj.Addrel(ctxt.Cursym)

			rel.Off = int32(ctxt.Pc)
			rel.Siz = 4
			rel.Sym = p.To.Sym
			rel.Add = p.To.Offset
			rel.Type = obj.R_ADDR
			o1 = 0
		}

	case 15: /* mul/mneg/umulh/umull r,[r,]r; madd/msub Rm,Rn,Ra,Rd */
		o1 = oprrr(ctxt, int(p.As))

		rf = int(p.From.Reg)
		rt = int(p.To.Reg)
		if p.From3.Type == D_REG {
			r = int(p.From3.Reg)
			ra = int(p.Reg)
			if ra == NREG {
				ra = REGZERO
			}
		} else {

			r = int(p.Reg)
			if r == NREG {
				r = rt
			}
			ra = REGZERO
		}

		o1 |= (uint32(rf) << 16) | (uint32(ra) << 10) | (uint32(r) << 5) | uint32(rt)

	case 16: /* XremY R[,R],R -> XdivY; XmsubY */
		o1 = oprrr(ctxt, int(p.As))

		rf = int(p.From.Reg)
		rt = int(p.To.Reg)
		r = int(p.Reg)
		if r == NREG {
			r = rt
		}
		o1 |= (uint32(rf) << 16) | (uint32(r) << 5) | REGTMP
		o2 = oprrr(ctxt, AMSUBW)
		o2 |= o1 & (1 << 31) /* same size */
		o2 |= (uint32(rf) << 16) | (uint32(r) << 10) | (REGTMP << 5) | uint32(rt)

	case 17: /* op Rm,[Rn],Rd; default Rn=ZR */
		o1 = oprrr(ctxt, int(p.As))

		rf = int(p.From.Reg)
		rt = int(p.To.Reg)
		r = int(p.Reg)
		if p.To.Type == D_NONE {
			rt = REGZERO
		}
		if r == NREG {
			r = REGZERO
		}
		o1 |= (uint32(rf) << 16) | (uint32(r) << 5) | uint32(rt)

	case 18: /* csel cond,Rn,Rm,Rd; cinc/cinv/cneg cond,Rn,Rd; cset cond,Rd */
		o1 = oprrr(ctxt, int(p.As))

		cond = int(p.From.Reg)
		r = int(p.Reg)
		if r != NREG {
			if p.From3.Type == D_NONE {
				/* CINC/CINV/CNEG */
				rf = r

				cond ^= 1
			} else {

				rf = int(p.From3.Reg) /* CSEL */
			}
		} else {

			/* CSET */
			if p.From3.Type != D_NONE {

				ctxt.Diag("invalid combination\n%v", p)
			}
			rf = REGZERO
			r = rf
			cond ^= 1
		}

		rt = int(p.To.Reg)
		o1 |= (uint32(r) << 16) | (uint32(cond) << 12) | (uint32(rf) << 5) | uint32(rt)

	case 19: /* CCMN cond, (Rm|uimm5),Rn, uimm4 -> ccmn Rn,Rm,uimm4,cond */
		nzcv = int(p.To.Offset)

		cond = int(p.From.Reg)
		if p.From3.Type == D_REG {
			o1 = oprrr(ctxt, int(p.As))
			rf = int(p.From3.Reg) /* Rm */
		} else {

			o1 = opirr(ctxt, int(p.As))
			rf = int(p.From3.Offset & 0x1F)
		}

		o1 |= (uint32(rf) << 16) | (uint32(cond) << 12) | (uint32(p.Reg) << 5) | uint32(nzcv)

	case 20: /* movT R,O(R) -> strT */
		v = int32(regoff(ctxt, &p.To))

		r = int(p.To.Reg)
		if r == NREG {
			r = int(o.param)
		}
		if v < 0 { /* unscaled 9-bit signed */
			o1 = olsr9s(ctxt, int32(opstr9(ctxt, int(p.As))), v, r, int(p.From.Reg))
		} else {

			v = int32(offsetshift(ctxt, int64(v), int(o.a3)))
			o1 = olsr12u(ctxt, int32(opstr12(ctxt, int(p.As))), v, r, int(p.From.Reg))
		}

	case 21: /* movT O(R),R -> ldrT */
		v = int32(regoff(ctxt, &p.From))

		r = int(p.From.Reg)
		if r == NREG {
			r = int(o.param)
		}
		if v < 0 { /* unscaled 9-bit signed */
			o1 = olsr9s(ctxt, int32(opldr9(ctxt, int(p.As))), v, r, int(p.To.Reg))
		} else {

			v = int32(offsetshift(ctxt, int64(v), int(o.a1)))

			//print("offset=%lld v=%ld a1=%d\n", instoffset, v, o->a1);
			o1 = olsr12u(ctxt, int32(opldr12(ctxt, int(p.As))), v, r, int(p.To.Reg))
		}

	case 22: /* movT (R)O!,R; movT O(R)!, R -> ldrT */
		v = int32(p.From.Offset)

		if v < -256 || v > 255 {
			ctxt.Diag("offset out of range\n%v", p)
		}
		o1 = opldrpp(ctxt, int(p.As))
		if p.From.Type == D_XPOST {
			o1 |= 1 << 10
		} else {

			o1 |= 3 << 10
		}
		o1 |= ((uint32(v) & 0x1FF) << 12) | (uint32(p.From.Reg) << 5) | uint32(p.To.Reg)

	case 23: /* movT R,(R)O!; movT O(R)!, R -> strT */
		v = int32(p.To.Offset)

		if v < -256 || v > 255 {
			ctxt.Diag("offset out of range\n%v", p)
		}
		o1 = LD2STR(opldrpp(ctxt, int(p.As)))
		if p.To.Type == D_XPOST {
			o1 |= 1 << 10
		} else {

			o1 |= 3 << 10
		}
		o1 |= ((uint32(v) & 0x1FF) << 12) | (uint32(p.To.Reg) << 5) | uint32(p.From.Reg)

	case 24: /* mov/mvn Rs,Rd -> add $0,Rs,Rd or orr Rs,ZR,Rd */
		rf = int(p.From.Reg)

		rt = int(p.To.Reg)
		s = bool2int(rf == REGSP || rt == REGSP)
		if p.As == AMVN || p.As == AMVNW {
			if s != 0 {
				ctxt.Diag("illegal SP reference\n%v", p)
			}
			o1 = oprrr(ctxt, int(p.As))
			o1 |= (uint32(rf) << 16) | (REGZERO << 5) | uint32(rt)
		} else if s != 0 {
			o1 = opirr(ctxt, int(p.As))
			o1 |= (uint32(rf) << 5) | uint32(rt)
		} else {

			o1 = oprrr(ctxt, int(p.As))
			o1 |= (uint32(rf) << 16) | (REGZERO << 5) | uint32(rt)
		}

	case 25: /* negX Rs, Rd -> subX Rs<<0, ZR, Rd */
		o1 = oprrr(ctxt, int(p.As))

		rf = int(p.From.Reg)
		rt = int(p.To.Reg)
		o1 |= (uint32(rf) << 16) | (REGZERO << 5) | uint32(rt)

	case 26: /* negX Rm<<s, Rd -> subX Rm<<s, ZR, Rd */
		o1 = oprrr(ctxt, int(p.As))

		o1 |= uint32(p.From.Offset) /* includes reg, op, etc */
		rt = int(p.To.Reg)
		o1 |= (REGZERO << 5) | uint32(rt)

	case 27: /* op Rm<<n[,Rn],Rd (extended register) */
		o1 = opxrrr(ctxt, int(p.As))

		if p.From.Type == D_EXTREG {
			o1 |= uint32(p.From.Offset) /* includes reg, op, etc */
		} else {

			o1 |= uint32(p.From.Reg) << 16
		}
		rt = int(p.To.Reg)
		if p.To.Type == D_NONE {
			rt = REGZERO
		}
		r = int(p.Reg)
		if r == NREG {
			r = rt
		}
		o1 |= (uint32(r) << 5) | uint32(rt)

	case 28: /* logop $vcon, [R], R (64 bit literal) */
		o1 = omovlit(ctxt, AMOV, p, &p.From, REGTMP)

		if !(o1 != 0) {
			break
		}
		r = int(p.Reg)
		if r == NREG {
			r = int(p.To.Reg)
		}
		o2 = oprrr(ctxt, int(p.As))
		o2 |= REGTMP << 16 /* shift is 0 */
		o2 |= uint32(r) << 5
		o2 |= uint32(p.To.Reg)

	case 29: /* op Rn, Rd */
		o1 = oprrr(ctxt, int(p.As))

		o1 |= uint32(p.From.Reg)<<5 | uint32(p.To.Reg)

	case 30: /* movT R,L(R) -> strT */
		s = movesize(int(o.as))

		if s < 0 {
			ctxt.Diag("unexpected long move, op %v tab %v\n%v", Aconv(int(p.As)), Aconv(int(o.as)), p)
		}
		v = int32(regoff(ctxt, &p.To))
		if v < 0 {
			ctxt.Diag("negative large offset\n%v", p)
		}
		if (v & ((1 << uint(s)) - 1)) != 0 {
			ctxt.Diag("misaligned offset\n%v", p)
		}
		hi = v - (v & (0xFFF << uint(s)))
		if (hi & 0xFFF) != 0 {
			ctxt.Diag("internal: miscalculated offset %d [%d]\n%v", v, s, p)
		}

		//fprint(2, "v=%ld (%#lux) s=%d hi=%ld (%#lux) v'=%ld (%#lux)\n", v, v, s, hi, hi, ((v-hi)>>s)&0xFFF, ((v-hi)>>s)&0xFFF);
		r = int(p.To.Reg)

		if r == NREG {
			r = int(o.param)
		}
		o1 = oaddi(int32(opirr(ctxt, AADD)), hi, r, REGTMP)
		o2 = olsr12u(ctxt, int32(opstr12(ctxt, int(p.As))), ((v-hi)>>uint(s))&0xFFF, REGTMP, int(p.From.Reg))

	case 31: /* movT L(R), R -> ldrT */
		s = movesize(int(o.as))

		if s < 0 {
			ctxt.Diag("unexpected long move, op %v tab %v\n%v", Aconv(int(p.As)), Aconv(int(o.as)), p)
		}
		v = int32(regoff(ctxt, &p.From))
		if v < 0 {
			ctxt.Diag("negative large offset\n%v", p)
		}
		if (v & ((1 << uint(s)) - 1)) != 0 {
			ctxt.Diag("misaligned offset\n%v", p)
		}
		hi = v - (v & (0xFFF << uint(s)))
		if (hi & 0xFFF) != 0 {
			ctxt.Diag("internal: miscalculated offset %d [%d]\n%v", v, s, p)
		}

		//fprint(2, "v=%ld (%#lux) s=%d hi=%ld (%#lux) v'=%ld (%#lux)\n", v, v, s, hi, hi, ((v-hi)>>s)&0xFFF, ((v-hi)>>s)&0xFFF);
		r = int(p.From.Reg)

		if r == NREG {
			r = int(o.param)
		}
		o1 = oaddi(int32(opirr(ctxt, AADD)), hi, r, REGTMP)
		o2 = olsr12u(ctxt, int32(opldr12(ctxt, int(p.As))), ((v-hi)>>uint(s))&0xFFF, REGTMP, int(p.To.Reg))

	case 32: /* mov $con, R -> movz/movn */
		r = 32

		if p.As == AMOV {
			r = 64
		}
		d = p.From.Offset
		s = movcon(d)
		if s < 0 || s >= r {
			d = ^d
			s = movcon(d)
			if s < 0 || s >= r {
				ctxt.Diag("impossible move wide: %#x\n%v", uint64(p.From.Offset), p)
			}
			if p.As == AMOV {
				o1 = opirr(ctxt, AMOVN)
			} else {

				o1 = opirr(ctxt, AMOVNW)
			}
		} else {

			if p.As == AMOV {
				o1 = opirr(ctxt, AMOVZ)
			} else {

				o1 = opirr(ctxt, AMOVZW)
			}
		}

		rt = int(p.To.Reg)
		o1 |= uint32((((d >> uint(s*16)) & 0xFFFF) << 5) | int64((uint32(s)&3)<<21) | int64(rt))

	case 33: /* movk $uimm16 << pos */
		o1 = opirr(ctxt, int(p.As))

		d = p.From.Offset
		if (d >> 16) != 0 {
			ctxt.Diag("requires uimm16\n%v", p)
		}
		s = 0
		if p.From3.Type != D_NONE {
			if p.From3.Type != D_CONST {
				ctxt.Diag("missing bit position\n%v", p)
			}
			s = int(p.From3.Offset / 16)
			if (s*16&0xF) != 0 || s >= 4 || (o1&S64) == 0 && s >= 2 {
				ctxt.Diag("illegal bit position\n%v", p)
			}
		}

		rt = int(p.To.Reg)
		o1 |= uint32(((d & 0xFFFF) << 5) | int64((uint32(s)&3)<<21) | int64(rt))

	case 34: /* mov $lacon,R */
		o1 = omovlit(ctxt, AMOV, p, &p.From, REGTMP)

		if !(o1 != 0) {
			break
		}
		o2 = opxrrr(ctxt, AADD)
		o2 |= REGTMP << 16
		o2 |= LSL0_64
		r = int(p.From.Reg)
		if r == NREG {
			r = int(o.param)
		}
		o2 |= uint32(r) << 5
		o2 |= uint32(p.To.Reg)

	case 35: /* mov SPR,R -> mrs */
		o1 = oprrr(ctxt, AMRS)

		v = int32(p.From.Offset)
		if (o1 & uint32(v&^(3<<19))) != 0 {
			ctxt.Diag("MRS register value overlap\n%v", p)
		}
		o1 |= uint32(v)
		o1 |= uint32(p.To.Reg)

	case 36: /* mov R,SPR */
		o1 = oprrr(ctxt, AMSR)

		v = int32(p.To.Offset)
		if (o1 & uint32(v&^(3<<19))) != 0 {
			ctxt.Diag("MSR register value overlap\n%v", p)
		}
		o1 |= uint32(v)
		o1 |= uint32(p.From.Reg)

	case 37: /* mov $con,PSTATEfield -> MSR [immediate] */
		if (uint64(p.From.Offset) &^ uint64(0xF)) != 0 {

			ctxt.Diag("illegal immediate for PSTATE field\n%v", p)
		}
		o1 = opirr(ctxt, AMSR)
		o1 |= uint32((p.From.Offset & 0xF) << 8) /* Crm */
		v = 0
		for i = 0; i < len(pstatefield); i++ {
			if int64(pstatefield[i].a) == p.To.Offset {
				v = int32(pstatefield[i].b)
				break
			}
		}

		if v == 0 {
			ctxt.Diag("illegal PSTATE field for immediate move\n%v", p)
		}
		o1 |= uint32(v)

	case 38: /* clrex [$imm] */
		o1 = opimm(ctxt, int(p.As))

		if p.To.Type == D_NONE {
			o1 |= 0xF << 8
		} else {

			o1 |= uint32((p.To.Offset & 0xF) << 8)
		}

	case 39: /* cbz R, rel */
		o1 = opirr(ctxt, int(p.As))

		o1 |= uint32(p.From.Reg)
		o1 |= uint32(brdist(ctxt, p, 0, 19, 2) << 5)

	case 40: /* tbz */
		o1 = opirr(ctxt, int(p.As))

		v = int32(p.From.Offset)
		if v < 0 || v > 63 {
			ctxt.Diag("illegal bit number\n%v", p)
		}
		o1 |= ((uint32(v) & 0x20) << (31 - 5)) | ((uint32(v) & 0x1F) << 19)
		o1 |= uint32(brdist(ctxt, p, 0, 14, 2) << 5)
		o1 |= uint32(p.Reg)

	case 41: /* eret, nop, others with no operands */
		o1 = op0(ctxt, int(p.As))

	case 42: /* bfm R,r,s,R */
		o1 = opbfm(ctxt, int(p.As), int(p.From.Offset), int(p.From3.Offset), int(p.Reg), int(p.To.Reg))

	case 43: /* bfm aliases */
		r = int(p.From.Offset)

		s = int(p.From3.Offset)
		rf = int(p.Reg)
		rt = int(p.To.Reg)
		if rf == NREG {
			rf = rt
		}
		switch p.As {
		case ABFI:
			o1 = opbfm(ctxt, ABFM, 64-r, s-1, rf, rt)

		case ABFIW:
			o1 = opbfm(ctxt, ABFMW, 32-r, s-1, rf, rt)

		case ABFXIL:
			o1 = opbfm(ctxt, ABFM, r, r+s-1, rf, rt)

		case ABFXILW:
			o1 = opbfm(ctxt, ABFMW, r, r+s-1, rf, rt)

		case ASBFIZ:
			o1 = opbfm(ctxt, ASBFM, 64-r, s-1, rf, rt)

		case ASBFIZW:
			o1 = opbfm(ctxt, ASBFMW, 32-r, s-1, rf, rt)

		case ASBFX:
			o1 = opbfm(ctxt, ASBFM, r, r+s-1, rf, rt)

		case ASBFXW:
			o1 = opbfm(ctxt, ASBFMW, r, r+s-1, rf, rt)

		case AUBFIZ:
			o1 = opbfm(ctxt, AUBFM, 64-r, s-1, rf, rt)

		case AUBFIZW:
			o1 = opbfm(ctxt, AUBFMW, 32-r, s-1, rf, rt)

		case AUBFX:
			o1 = opbfm(ctxt, AUBFM, r, r+s-1, rf, rt)

		case AUBFXW:
			o1 = opbfm(ctxt, AUBFMW, r, r+s-1, rf, rt)

		default:
			ctxt.Diag("bad bfm alias\n%v", ctxt.Curp)
			break
		}

	case 44: /* extr $b, Rn, Rm, Rd */
		o1 = opextr(ctxt, int(p.As), int32(p.From.Offset), int(p.From3.Reg), int(p.Reg), int(p.To.Reg))

	case 45: /* sxt/uxt[bhw] R,R; movT R,R -> sxtT R,R */
		rf = int(p.From.Reg)

		rt = int(p.To.Reg)
		as = int(p.As)
		if rf == REGZERO {
			as = AMOVWU /* clearer in disassembly */
		}
		switch as {
		case AMOVB,
			ASXTB:
			o1 = opbfm(ctxt, ASBFM, 0, 7, rf, rt)

		case AMOVH,
			ASXTH:
			o1 = opbfm(ctxt, ASBFM, 0, 15, rf, rt)

		case AMOVW,
			ASXTW:
			o1 = opbfm(ctxt, ASBFM, 0, 31, rf, rt)

		case AMOVBU,
			AUXTB:
			o1 = opbfm(ctxt, AUBFM, 0, 7, rf, rt)

		case AMOVHU,
			AUXTH:
			o1 = opbfm(ctxt, AUBFM, 0, 15, rf, rt)

		case AMOVWU:
			o1 = oprrr(ctxt, as) | (uint32(rf) << 16) | (REGZERO << 5) | uint32(rt)

		case AUXTW:
			o1 = opbfm(ctxt, AUBFM, 0, 31, rf, rt)

		case ASXTBW:
			o1 = opbfm(ctxt, ASBFMW, 0, 7, rf, rt)

		case ASXTHW:
			o1 = opbfm(ctxt, ASBFMW, 0, 15, rf, rt)

		case AUXTBW:
			o1 = opbfm(ctxt, AUBFMW, 0, 7, rf, rt)

		case AUXTHW:
			o1 = opbfm(ctxt, AUBFMW, 0, 15, rf, rt)

		default:
			ctxt.Diag("bad sxt %v", Aconv(as))
			break
		}

	case 46: /* cls */
		o1 = opbit(ctxt, int(p.As))

		o1 |= uint32(p.From.Reg) << 5
		o1 |= uint32(p.To.Reg)

	case 47: /* movT R,V(R) -> strT (huge offset) */
		o1 = omovlit(ctxt, AMOVW, p, &p.To, REGTMP)

		if !(o1 != 0) {
			break
		}
		r = int(p.To.Reg)
		if r == NREG {
			r = int(o.param)
		}
		o2 = olsxrr(ctxt, int(p.As), REGTMP, r, int(p.From.Reg))

	case 48: /* movT V(R), R -> ldrT (huge offset) */
		o1 = omovlit(ctxt, AMOVW, p, &p.From, REGTMP)

		if !(o1 != 0) {
			break
		}
		r = int(p.From.Reg)
		if r == NREG {
			r = int(o.param)
		}
		o2 = olsxrr(ctxt, int(p.As), REGTMP, r, int(p.To.Reg))

	case 50: /* sys/sysl */
		o1 = opirr(ctxt, int(p.As))

		if (p.From.Offset &^ int64(SYSARG4(0x7, 0xF, 0xF, 0x7))) != 0 {
			ctxt.Diag("illegal SYS argument\n%v", p)
		}
		o1 |= uint32(p.From.Offset)
		if p.To.Type == D_REG {
			o1 |= uint32(p.To.Reg)
		} else if p.Reg != NREG {
			o1 |= uint32(p.Reg)
		} else {

			o1 |= 0x1F
		}

	case 51: /* dmb */
		o1 = opirr(ctxt, int(p.As))

		if p.From.Type == D_CONST {
			o1 |= uint32((p.From.Offset & 0xF) << 8)
		}

	case 52: /* hint */
		o1 = opirr(ctxt, int(p.As))

		o1 |= uint32((p.From.Offset & 0x7F) << 5)

	case 53: /* and/or/eor/bic/... $bimmN, Rn, Rd -> op (N,r,s), Rn, Rd */
		as = int(p.As)

		rt = int(p.To.Reg)
		r = int(p.Reg)
		if r == NREG {
			r = rt
		}
		if as == AMOV {
			as = AORR
			r = REGZERO
		} else if as == AMOVW {
			as = AORRW
			r = REGZERO
		}

		o1 = opirr(ctxt, as)
		if o1&S64 != 0 {
			s = 64
		} else {

			s = 32
		}
		mask = findmask(uint64(p.From.Offset))
		if mask == nil {
			mask = findmask(uint64(p.From.Offset) | (uint64(p.From.Offset) << 32))
		}
		if mask != nil {
			o1 |= ((uint32(mask.r) & (uint32(s) - 1)) << 16) | (((uint32(mask.s) - 1) & (uint32(s) - 1)) << 10)
			if s == 64 {
				if mask.e == 64 && (uint64(p.From.Offset)>>32) != 0 {
					o1 |= 1 << 22
				}
			} else {

				u = uint32(uint64(p.From.Offset) >> 32)
				if u != 0 && u != 0xFFFFFFFF {
					ctxt.Diag("mask needs 64 bits %#x\n%v", uint64(p.From.Offset), p)
				}
			}
		} else {

			ctxt.Diag("invalid mask %#x\n%v", uint64(p.From.Offset), p) /* probably shouldn't happen */
		}
		o1 |= (uint32(r) << 5) | uint32(rt)

	case 54: /* floating point arith */
		o1 = oprrr(ctxt, int(p.As))

		if p.From.Type == D_FCONST {
			rf = chipfloat7(ctxt, p.From.U.Dval)
			if rf < 0 || true {
				ctxt.Diag("invalid floating-point immediate\n%v", p)
				rf = 0
			}

			rf |= (1 << 3)
		} else {

			rf = int(p.From.Reg)
		}
		rt = int(p.To.Reg)
		r = int(p.Reg)
		if (o1&(0x1F<<24)) == (0x1E<<24) && (o1&(1<<11)) == 0 { /* monadic */
			r = rf
			rf = 0
		} else if r == NREG {
			r = rt
		}
		o1 |= (uint32(rf) << 16) | (uint32(r) << 5) | uint32(rt)

	case 56: /* floating point compare */
		o1 = oprrr(ctxt, int(p.As))

		if p.From.Type == D_FCONST {
			o1 |= 8 /* zero */
			rf = 0
		} else {

			rf = int(p.From.Reg)
		}
		rt = int(p.Reg)
		o1 |= uint32(rf)<<16 | uint32(rt)<<5

	case 57: /* floating point conditional compare */
		o1 = oprrr(ctxt, int(p.As))

		cond = int(p.From.Reg)
		nzcv = int(p.To.Offset)
		if nzcv&^0xF != 0 {
			ctxt.Diag("implausible condition\n%v", p)
		}
		rf = int(p.Reg)
		if p.From3.Type != D_FREG {
			ctxt.Diag("illegal FCCMP\n%v", p)
		}
		rt = int(p.From3.Reg)
		o1 |= uint32(rf)<<16 | uint32(cond)<<12 | uint32(rt)<<5 | uint32(nzcv)

	case 58: /* ldar/ldxr/ldaxr */
		o1 = opload(ctxt, int(p.As))

		o1 |= 0x1F << 16
		o1 |= uint32(p.From.Reg) << 5
		if p.Reg != NREG {
			o1 |= uint32(p.Reg) << 10
		} else {

			o1 |= 0x1F << 10
		}
		o1 |= uint32(p.To.Reg)

	case 59: /* stxr/stlxr */
		o1 = opstore(ctxt, int(p.As))

		o1 |= uint32(p.To3.Reg) << 16
		if p.From3.Type != D_NONE {
			o1 |= uint32(p.From3.Reg) << 10
		} else {

			o1 |= 0x1F << 10
		}
		o1 |= uint32(p.To.Reg) << 5
		o1 |= uint32(p.From.Reg)

	case 60: /* adrp label,r */
		d = brdist(ctxt, p, 12, 21, 0)

		o1 = ADR(1, uint32(d), uint32(p.To.Reg))

	case 61: /* adr label, r */
		d = brdist(ctxt, p, 0, 21, 0)

		o1 = ADR(0, uint32(d), uint32(p.To.Reg))

	case 62: /* case Rv, Rt -> adr tab, Rt; movw Rt[R<<2], Rl; add Rt, Rl; br (Rl) */
		o1 = ADR(0, 4*4, uint32(p.To.Reg))                                                                                                                     /* adr 4(pc), Rt */
		o2 = (2 << 30) | (7 << 27) | (2 << 22) | (1 << 21) | (3 << 13) | (1 << 12) | (2 << 10) | (uint32(p.From.Reg) << 16) | (uint32(p.To.Reg) << 5) | REGTMP /* movw Rt[Rv<<2], REGTMP */
		o3 = oprrr(ctxt, AADD) | (uint32(p.To.Reg) << 16) | (REGTMP << 5) | REGTMP                                                                             /* add Rt, REGTMP */
		o4 = (0x6b << 25) | (0x1F << 16) | (REGTMP << 5)                                                                                                       /* br (REGTMP) */
		lastcase = p

	case 63: /* bcase */
		if lastcase == nil {

			ctxt.Diag("missing CASE\n%v", p)
			break
		}

		if p.Pcond != nil {
			o1 = uint32(p.Pcond.Pc - (lastcase.Pc + 4*4))
			ctxt.Diag("FIXME: some relocation needed in bcase\n%v", p)
		}

		/* reloc ops */
	case 64: /* movT R,addr */
		o1 = omovlit(ctxt, AMOV, p, &p.To, REGTMP)

		if !(o1 != 0) {
			break
		}
		o2 = olsr12u(ctxt, int32(opstr12(ctxt, int(p.As))), 0, REGTMP, int(p.From.Reg))

	case 65: /* movT addr,R */
		o1 = omovlit(ctxt, AMOV, p, &p.From, REGTMP)

		if !(o1 != 0) {
			break
		}
		o2 = olsr12u(ctxt, int32(opldr12(ctxt, int(p.As))), 0, REGTMP, int(p.To.Reg))
        case 66: /* stlr/stlrw */
                o1 = opstore(ctxt, int(p.As))

                o1 |= 0x1F << 16
                o1 |= uint32(p.From.Reg) << 5
                if p.Reg != NREG {
                        o1 |= uint32(p.Reg) << 10
                } else {

                        o1 |= 0x1F << 10
                }
                o1 |= uint32(p.To.Reg)


		// This is supposed to be something that stops execution.
	// It's not supposed to be reached, ever, but if it is, we'd
	// like to be able to tell how we got there.  Assemble as
	// 0xbea71700 which is guaranteed to raise undefined instruction
	// exception.
	case 90:
		o1 = 0xbea71700

		break
	}

	out[0] = o1
	out[1] = o2
	out[2] = o3
	out[3] = o4
	out[4] = o5
	return
}

/*
 * basic Rm op Rn -> Rd (using shifted register with 0)
 * also op Rn -> Rt
 * also Rm*Rn op Ra -> Rd
 */
func oprrr(ctxt *obj.Link, a int) uint32 {

	switch a {
	case AADC:
		return S64 | 0<<30 | 0<<29 | 0xd0<<21 | 0<<10

	case AADCW:
		return S32 | 0<<30 | 0<<29 | 0xd0<<21 | 0<<10

	case AADCS:
		return S64 | 0<<30 | 1<<29 | 0xd0<<21 | 0<<10

	case AADCSW:
		return S32 | 0<<30 | 1<<29 | 0xd0<<21 | 0<<10

	case ANGC,
		ASBC:
		return S64 | 1<<30 | 0<<29 | 0xd0<<21 | 0<<10

	case ANGCS,
		ASBCS:
		return S64 | 1<<30 | 1<<29 | 0xd0<<21 | 0<<10

	case ANGCW,
		ASBCW:
		return S32 | 1<<30 | 0<<29 | 0xd0<<21 | 0<<10

	case ANGCSW,
		ASBCSW:
		return S32 | 1<<30 | 1<<29 | 0xd0<<21 | 0<<10

	case AADD:
		return S64 | 0<<30 | 0<<29 | 0x0b<<24 | 0<<22 | 0<<21 | 0<<10

	case AADDW:
		return S32 | 0<<30 | 0<<29 | 0x0b<<24 | 0<<22 | 0<<21 | 0<<10

	case ACMN,
		AADDS:
		return S64 | 0<<30 | 1<<29 | 0x0b<<24 | 0<<22 | 0<<21 | 0<<10

	case ACMNW,
		AADDSW:
		return S32 | 0<<30 | 1<<29 | 0x0b<<24 | 0<<22 | 0<<21 | 0<<10

	case ASUB:
		return S64 | 1<<30 | 0<<29 | 0x0b<<24 | 0<<22 | 0<<21 | 0<<10

	case ASUBW:
		return S32 | 1<<30 | 0<<29 | 0x0b<<24 | 0<<22 | 0<<21 | 0<<10

	case ACMP,
		ASUBS:
		return S64 | 1<<30 | 1<<29 | 0x0b<<24 | 0<<22 | 0<<21 | 0<<10

	case ACMPW,
		ASUBSW:
		return S32 | 1<<30 | 1<<29 | 0x0b<<24 | 0<<22 | 0<<21 | 0<<10

	case AAND:
		return S64 | 0<<29 | 0xA<<24

	case AANDW:
		return S32 | 0<<29 | 0xA<<24

	case AMOV,
		AORR:
		return S64 | 1<<29 | 0xA<<24

		//	case AMOVW:
	case AMOVWU,
		AORRW:
		return S32 | 1<<29 | 0xA<<24

	case AEOR:
		return S64 | 2<<29 | 0xA<<24

	case AEORW:
		return S32 | 2<<29 | 0xA<<24

	case AANDS:
		return S64 | 3<<29 | 0xA<<24

	case AANDSW:
		return S32 | 3<<29 | 0xA<<24

	case ABIC:
		return S64 | 0<<29 | 0xA<<24 | 1<<21

	case ABICW:
		return S32 | 0<<29 | 0xA<<24 | 1<<21

	case ABICS:
		return S64 | 3<<29 | 0xA<<24 | 1<<21

	case ABICSW:
		return S32 | 3<<29 | 0xA<<24 | 1<<21

	case AEON:
		return S64 | 2<<29 | 0xA<<24 | 1<<21

	case AEONW:
		return S32 | 2<<29 | 0xA<<24 | 1<<21

	case AMVN,
		AORN:
		return S64 | 1<<29 | 0xA<<24 | 1<<21

	case AMVNW,
		AORNW:
		return S32 | 1<<29 | 0xA<<24 | 1<<21

	case AASR:
		return S64 | OPDP2(10) /* also ASRV */

	case AASRW:
		return S32 | OPDP2(10)

	case ALSL:
		return S64 | OPDP2(8)

	case ALSLW:
		return S32 | OPDP2(8)

	case ALSR:
		return S64 | OPDP2(9)

	case ALSRW:
		return S32 | OPDP2(9)

	case AROR:
		return S64 | OPDP2(11)

	case ARORW:
		return S32 | OPDP2(11)

	case ACCMN:
		return S64 | 0<<30 | 1<<29 | 0xD2<<21 | 0<<11 | 0<<10 | 0<<4 /* cond<<12 | nzcv<<0 */

	case ACCMNW:
		return S32 | 0<<30 | 1<<29 | 0xD2<<21 | 0<<11 | 0<<10 | 0<<4

	case ACCMP:
		return S64 | 1<<30 | 1<<29 | 0xD2<<21 | 0<<11 | 0<<10 | 0<<4 /* imm5<<16 | cond<<12 | nzcv<<0 */

	case ACCMPW:
		return S32 | 1<<30 | 1<<29 | 0xD2<<21 | 0<<11 | 0<<10 | 0<<4

	case ACRC32B:
		return S32 | OPDP2(16)

	case ACRC32H:
		return S32 | OPDP2(17)

	case ACRC32W:
		return S32 | OPDP2(18)

	case ACRC32X:
		return S64 | OPDP2(19)

	case ACRC32CB:
		return S32 | OPDP2(20)

	case ACRC32CH:
		return S32 | OPDP2(21)

	case ACRC32CW:
		return S32 | OPDP2(22)

	case ACRC32CX:
		return S64 | OPDP2(23)

	case ACSEL:
		return S64 | 0<<30 | 0<<29 | 0xD4<<21 | 0<<11 | 0<<10

	case ACSELW:
		return S32 | 0<<30 | 0<<29 | 0xD4<<21 | 0<<11 | 0<<10

	case ACSET:
		return S64 | 0<<30 | 0<<29 | 0xD4<<21 | 0<<11 | 1<<10

	case ACSETW:
		return S32 | 0<<30 | 0<<29 | 0xD4<<21 | 0<<11 | 1<<10

	case ACSETM:
		return S64 | 1<<30 | 0<<29 | 0xD4<<21 | 0<<11 | 0<<10

	case ACSETMW:
		return S32 | 1<<30 | 0<<29 | 0xD4<<21 | 0<<11 | 0<<10

	case ACINC,
		ACSINC:
		return S64 | 0<<30 | 0<<29 | 0xD4<<21 | 0<<11 | 1<<10

	case ACINCW,
		ACSINCW:
		return S32 | 0<<30 | 0<<29 | 0xD4<<21 | 0<<11 | 1<<10

	case ACINV,
		ACSINV:
		return S64 | 1<<30 | 0<<29 | 0xD4<<21 | 0<<11 | 0<<10

	case ACINVW,
		ACSINVW:
		return S32 | 1<<30 | 0<<29 | 0xD4<<21 | 0<<11 | 0<<10

	case ACNEG,
		ACSNEG:
		return S64 | 1<<30 | 0<<29 | 0xD4<<21 | 0<<11 | 1<<10

	case ACNEGW,
		ACSNEGW:
		return S32 | 1<<30 | 0<<29 | 0xD4<<21 | 0<<11 | 1<<10

	case AMUL,
		AMADD:
		return S64 | 0<<29 | 0x1B<<24 | 0<<21 | 0<<15

	case AMULW,
		AMADDW:
		return S32 | 0<<29 | 0x1B<<24 | 0<<21 | 0<<15

	case AMNEG,
		AMSUB:
		return S64 | 0<<29 | 0x1B<<24 | 0<<21 | 1<<15

	case AMNEGW,
		AMSUBW:
		return S32 | 0<<29 | 0x1B<<24 | 0<<21 | 1<<15

	case AMRS:
		return SYSOP(1, 2, 0, 0, 0, 0, 0)

	case AMSR:
		return SYSOP(0, 2, 0, 0, 0, 0, 0)

	case ANEG:
		return S64 | 1<<30 | 0<<29 | 0xB<<24 | 0<<21

	case ANEGW:
		return S32 | 1<<30 | 0<<29 | 0xB<<24 | 0<<21

	case ANEGS:
		return S64 | 1<<30 | 1<<29 | 0xB<<24 | 0<<21

	case ANEGSW:
		return S32 | 1<<30 | 1<<29 | 0xB<<24 | 0<<21

	case AREM,
		ASDIV:
		return S64 | OPDP2(3)

	case AREMW,
		ASDIVW:
		return S32 | OPDP2(3)

	case ASMULL,
		ASMADDL:
		return OPDP3(1, 0, 1, 0)

	case ASMNEGL,
		ASMSUBL:
		return OPDP3(1, 0, 1, 1)

	case ASMULH:
		return OPDP3(1, 0, 2, 0)

	case AUMULL,
		AUMADDL:
		return OPDP3(1, 0, 5, 0)

	case AUMNEGL,
		AUMSUBL:
		return OPDP3(1, 0, 5, 1)

	case AUMULH:
		return OPDP3(1, 0, 6, 0)

	case AUREM,
		AUDIV:
		return S64 | OPDP2(2)

	case AUREMW,
		AUDIVW:
		return S32 | OPDP2(2)

	case AAESE:
		return 0x4E<<24 | 2<<20 | 8<<16 | 4<<12 | 2<<10

	case AAESD:
		return 0x4E<<24 | 2<<20 | 8<<16 | 5<<12 | 2<<10

	case AAESMC:
		return 0x4E<<24 | 2<<20 | 8<<16 | 6<<12 | 2<<10

	case AAESIMC:
		return 0x4E<<24 | 2<<20 | 8<<16 | 7<<12 | 2<<10

	case ASHA1C:
		return 0x5E<<24 | 0<<12

	case ASHA1P:
		return 0x5E<<24 | 1<<12

	case ASHA1M:
		return 0x5E<<24 | 2<<12

	case ASHA1SU0:
		return 0x5E<<24 | 3<<12

	case ASHA256H:
		return 0x5E<<24 | 4<<12

	case ASHA256H2:
		return 0x5E<<24 | 5<<12

	case ASHA256SU1:
		return 0x5E<<24 | 6<<12

	case ASHA1H:
		return 0x5E<<24 | 2<<20 | 8<<16 | 0<<12 | 2<<10

	case ASHA1SU1:
		return 0x5E<<24 | 2<<20 | 8<<16 | 1<<12 | 2<<10

	case ASHA256SU0:
		return 0x5E<<24 | 2<<20 | 8<<16 | 2<<12 | 2<<10

	case AFCVTZSD:
		return FPCVTI(1, 0, 1, 3, 0)

	case AFCVTZSDW:
		return FPCVTI(0, 0, 1, 3, 0)

	case AFCVTZSS:
		return FPCVTI(1, 0, 0, 3, 0)

	case AFCVTZSSW:
		return FPCVTI(0, 0, 0, 3, 0)

	case AFCVTZUD:
		return FPCVTI(1, 0, 1, 3, 1)

	case AFCVTZUDW:
		return FPCVTI(0, 0, 1, 3, 1)

	case AFCVTZUS:
		return FPCVTI(1, 0, 0, 3, 1)

	case AFCVTZUSW:
		return FPCVTI(0, 0, 0, 3, 1)

	case ASCVTFD:
		return FPCVTI(1, 0, 1, 0, 2)

	case ASCVTFS:
		return FPCVTI(1, 0, 0, 0, 2)

	case ASCVTFWD:
		return FPCVTI(0, 0, 1, 0, 2)

	case ASCVTFWS:
		return FPCVTI(0, 0, 0, 0, 2)

	case AUCVTFD:
		return FPCVTI(1, 0, 1, 0, 3)

	case AUCVTFS:
		return FPCVTI(1, 0, 0, 0, 3)

	case AUCVTFWD:
		return FPCVTI(0, 0, 1, 0, 3)

	case AUCVTFWS:
		return FPCVTI(0, 0, 0, 0, 3)

	case AFADDS:
		return FPOP2S(0, 0, 0, 2)

	case AFADDD:
		return FPOP2S(0, 0, 1, 2)

	case AFSUBS:
		return FPOP2S(0, 0, 0, 3)

	case AFSUBD:
		return FPOP2S(0, 0, 1, 3)

	case AFMULS:
		return FPOP2S(0, 0, 0, 0)

	case AFMULD:
		return FPOP2S(0, 0, 1, 0)

	case AFDIVS:
		return FPOP2S(0, 0, 0, 1)

	case AFDIVD:
		return FPOP2S(0, 0, 1, 1)

	case AFMAXS:
		return FPOP2S(0, 0, 0, 4)

	case AFMINS:
		return FPOP2S(0, 0, 0, 5)

	case AFMAXD:
		return FPOP2S(0, 0, 1, 4)

	case AFMIND:
		return FPOP2S(0, 0, 1, 5)

	case AFMAXNMS:
		return FPOP2S(0, 0, 0, 6)

	case AFMAXNMD:
		return FPOP2S(0, 0, 1, 6)

	case AFMINNMS:
		return FPOP2S(0, 0, 0, 7)

	case AFMINNMD:
		return FPOP2S(0, 0, 1, 7)

	case AFNMULS:
		return FPOP2S(0, 0, 0, 8)

	case AFNMULD:
		return FPOP2S(0, 0, 1, 8)

	case AFCMPS:
		return FPCMP(0, 0, 0, 0, 0)

	case AFCMPD:
		return FPCMP(0, 0, 1, 0, 0)

	case AFCMPES:
		return FPCMP(0, 0, 0, 0, 16)

	case AFCMPED:
		return FPCMP(0, 0, 1, 0, 16)

	case AFCCMPS:
		return FPCCMP(0, 0, 0, 0)

	case AFCCMPD:
		return FPCCMP(0, 0, 1, 0)

	case AFCCMPES:
		return FPCCMP(0, 0, 0, 1)

	case AFCCMPED:
		return FPCCMP(0, 0, 1, 1)

	case AFCSELS:
		return 0x1E<<24 | 0<<22 | 1<<21 | 3<<10

	case AFCSELD:
		return 0x1E<<24 | 1<<22 | 1<<21 | 3<<10

	case AFMOVS:
		return FPOP1S(0, 0, 0, 0)

	case AFABSS:
		return FPOP1S(0, 0, 0, 1)

	case AFNEGS:
		return FPOP1S(0, 0, 0, 2)

	case AFSQRTS:
		return FPOP1S(0, 0, 0, 3)

	case AFCVTSD:
		return FPOP1S(0, 0, 0, 5)

	case AFCVTSH:
		return FPOP1S(0, 0, 0, 7)

	case AFRINTNS:
		return FPOP1S(0, 0, 0, 8)

	case AFRINTPS:
		return FPOP1S(0, 0, 0, 9)

	case AFRINTMS:
		return FPOP1S(0, 0, 0, 10)

	case AFRINTZS:
		return FPOP1S(0, 0, 0, 11)

	case AFRINTAS:
		return FPOP1S(0, 0, 0, 12)

	case AFRINTXS:
		return FPOP1S(0, 0, 0, 14)

	case AFRINTIS:
		return FPOP1S(0, 0, 0, 15)

	case AFMOVD:
		return FPOP1S(0, 0, 1, 0)

	case AFABSD:
		return FPOP1S(0, 0, 1, 1)

	case AFNEGD:
		return FPOP1S(0, 0, 1, 2)

	case AFSQRTD:
		return FPOP1S(0, 0, 1, 3)

	case AFCVTDS:
		return FPOP1S(0, 0, 1, 4)

	case AFCVTDH:
		return FPOP1S(0, 0, 1, 7)

	case AFRINTND:
		return FPOP1S(0, 0, 1, 8)

	case AFRINTPD:
		return FPOP1S(0, 0, 1, 9)

	case AFRINTMD:
		return FPOP1S(0, 0, 1, 10)

	case AFRINTZD:
		return FPOP1S(0, 0, 1, 11)

	case AFRINTAD:
		return FPOP1S(0, 0, 1, 12)

	case AFRINTXD:
		return FPOP1S(0, 0, 1, 14)

	case AFRINTID:
		return FPOP1S(0, 0, 1, 15)

	case AFCVTHS:
		return FPOP1S(0, 0, 3, 4)

	case AFCVTHD:
		return FPOP1S(0, 0, 3, 5)
	}

	ctxt.Diag("bad rrr %d %v", a, Aconv(a))
	prasm(ctxt.Curp)
	return 0
}

/*
 * imm -> Rd
 * imm op Rn -> Rd
 */
func opirr(ctxt *obj.Link, a int) uint32 {

	switch a {
	/* op $addcon, Rn, Rd */
	case AMOV,
		AADD:
		return S64 | 0<<30 | 0<<29 | 0x11<<24

	case ACMN,
		AADDS:
		return S64 | 0<<30 | 1<<29 | 0x11<<24

	case AMOVW,
		AADDW:
		return S32 | 0<<30 | 0<<29 | 0x11<<24

	case ACMNW,
		AADDSW:
		return S32 | 0<<30 | 1<<29 | 0x11<<24

	case ASUB:
		return S64 | 1<<30 | 0<<29 | 0x11<<24

	case ACMP,
		ASUBS:
		return S64 | 1<<30 | 1<<29 | 0x11<<24

	case ASUBW:
		return S32 | 1<<30 | 0<<29 | 0x11<<24

	case ACMPW,
		ASUBSW:
		return S32 | 1<<30 | 1<<29 | 0x11<<24

		/* op $imm(SB), Rd; op label, Rd */
	case AADR:
		return 0<<31 | 0x10<<24

	case AADRP:
		return 1<<31 | 0x10<<24

		/* op $bimm, Rn, Rd */
	case AAND:
		return S64 | 0<<29 | 0x24<<23

	case AANDW:
		return S32 | 0<<29 | 0x24<<23 | 0<<22

	case AORR:
		return S64 | 1<<29 | 0x24<<23

	case AORRW:
		return S32 | 1<<29 | 0x24<<23 | 0<<22

	case AEOR:
		return S64 | 2<<29 | 0x24<<23

	case AEORW:
		return S32 | 2<<29 | 0x24<<23 | 0<<22

	case AANDS:
		return S64 | 3<<29 | 0x24<<23

	case AANDSW:
		return S32 | 3<<29 | 0x24<<23 | 0<<22

	case AASR:
		return S64 | 0<<29 | 0x26<<23 /* alias of SBFM */

	case AASRW:
		return S32 | 0<<29 | 0x26<<23 | 0<<22

		/* op $width, $lsb, Rn, Rd */
	case ABFI:
		return S64 | 2<<29 | 0x26<<23 | 1<<22
		/* alias of BFM */

	case ABFIW:
		return S32 | 2<<29 | 0x26<<23 | 0<<22

		/* op $imms, $immr, Rn, Rd */
	case ABFM:
		return S64 | 1<<29 | 0x26<<23 | 1<<22

	case ABFMW:
		return S32 | 1<<29 | 0x26<<23 | 0<<22

	case ASBFM:
		return S64 | 0<<29 | 0x26<<23 | 1<<22

	case ASBFMW:
		return S32 | 0<<29 | 0x26<<23 | 0<<22

	case AUBFM:
		return S64 | 2<<29 | 0x26<<23 | 1<<22

	case AUBFMW:
		return S32 | 2<<29 | 0x26<<23 | 0<<22

	case ABFXIL:
		return S64 | 1<<29 | 0x26<<23 | 1<<22 /* alias of BFM */

	case ABFXILW:
		return S32 | 1<<29 | 0x26<<23 | 0<<22

	case AEXTR:
		return S64 | 0<<29 | 0x27<<23 | 1<<22 | 0<<21

	case AEXTRW:
		return S32 | 0<<29 | 0x27<<23 | 0<<22 | 0<<21

	case ACBNZ:
		return S64 | 0x1A<<25 | 1<<24

	case ACBNZW:
		return S32 | 0x1A<<25 | 1<<24

	case ACBZ:
		return S64 | 0x1A<<25 | 0<<24

	case ACBZW:
		return S32 | 0x1A<<25 | 0<<24

	case ACCMN:
		return S64 | 0<<30 | 1<<29 | 0xD2<<21 | 1<<11 | 0<<10 | 0<<4 /* imm5<<16 | cond<<12 | nzcv<<0 */

	case ACCMNW:
		return S32 | 0<<30 | 1<<29 | 0xD2<<21 | 1<<11 | 0<<10 | 0<<4

	case ACCMP:
		return S64 | 1<<30 | 1<<29 | 0xD2<<21 | 1<<11 | 0<<10 | 0<<4 /* imm5<<16 | cond<<12 | nzcv<<0 */

	case ACCMPW:
		return S32 | 1<<30 | 1<<29 | 0xD2<<21 | 1<<11 | 0<<10 | 0<<4

	case AMOVK:
		return S64 | 3<<29 | 0x25<<23

	case AMOVKW:
		return S32 | 3<<29 | 0x25<<23

	case AMOVN:
		return S64 | 0<<29 | 0x25<<23

	case AMOVNW:
		return S32 | 0<<29 | 0x25<<23

	case AMOVZ:
		return S64 | 2<<29 | 0x25<<23

	case AMOVZW:
		return S32 | 2<<29 | 0x25<<23

	case AMSR:
		return SYSOP(0, 0, 0, 4, 0, 0, 0x1F) /* MSR (immediate) */

	case AAT,
		ADC,
		AIC,
		ATLBI,
		ASYS:
		return SYSOP(0, 1, 0, 0, 0, 0, 0)

	case ASYSL:
		return SYSOP(1, 1, 0, 0, 0, 0, 0)

	case ATBZ:
		return 0x36 << 24

	case ATBNZ:
		return 0x37 << 24

	case ADSB:
		return SYSOP(0, 0, 3, 3, 0, 4, 0x1F)

	case ADMB:
		return SYSOP(0, 0, 3, 3, 0, 5, 0x1F)

	case AISB:
		return SYSOP(0, 0, 3, 3, 0, 6, 0x1F)

	case AHINT:
		return SYSOP(0, 0, 3, 2, 0, 0, 0x1F)
	}

	ctxt.Diag("bad irr %v", Aconv(a))
	prasm(ctxt.Curp)
	return 0
}

func opbit(ctxt *obj.Link, a int) uint32 {
	switch a {
	case ACLS:
		return S64 | OPBIT(5)

	case ACLSW:
		return S32 | OPBIT(5)

	case ACLZ:
		return S64 | OPBIT(4)

	case ACLZW:
		return S32 | OPBIT(4)

	case ARBIT:
		return S64 | OPBIT(0)

	case ARBITW:
		return S32 | OPBIT(0)

	case AREV:
		return S64 | OPBIT(3)

	case AREVW:
		return S32 | OPBIT(2)

	case AREV16:
		return S64 | OPBIT(1)

	case AREV16W:
		return S32 | OPBIT(1)

	case AREV32:
		return S64 | OPBIT(2)

	default:
		ctxt.Diag("bad bit op\n%v", ctxt.Curp)
		return 0
	}
}

/*
 * add/subtract extended register
 */
func opxrrr(ctxt *obj.Link, a int) uint32 {

	switch a {
	case AADD:
		return S64 | 0<<30 | 0<<29 | 0x0b<<24 | 0<<22 | 1<<21 | LSL0_64

	case AADDW:
		return S32 | 0<<30 | 0<<29 | 0x0b<<24 | 0<<22 | 1<<21 | LSL0_32

	case ACMN,
		AADDS:
		return S64 | 0<<30 | 1<<29 | 0x0b<<24 | 0<<22 | 1<<21 | LSL0_64

	case ACMNW,
		AADDSW:
		return S32 | 0<<30 | 1<<29 | 0x0b<<24 | 0<<22 | 1<<21 | LSL0_32

	case ASUB:
		return S64 | 1<<30 | 0<<29 | 0x0b<<24 | 0<<22 | 1<<21 | LSL0_64

	case ASUBW:
		return S32 | 1<<30 | 0<<29 | 0x0b<<24 | 0<<22 | 1<<21 | LSL0_32

	case ACMP,
		ASUBS:
		return S64 | 1<<30 | 1<<29 | 0x0b<<24 | 0<<22 | 1<<21 | LSL0_64

	case ACMPW,
		ASUBSW:
		return S32 | 1<<30 | 1<<29 | 0x0b<<24 | 0<<22 | 1<<21 | LSL0_32
	}

	ctxt.Diag("bad opxrrr %v\n%v", Aconv(a), ctxt.Curp)
	return 0
}

func opimm(ctxt *obj.Link, a int) uint32 {
	switch a {
	case ASVC:
		return 0xD4<<24 | 0<<21 | 1 /* imm16<<5 */

	case AHVC:
		return 0xD4<<24 | 0<<21 | 2

	case ASMC:
		return 0xD4<<24 | 0<<21 | 3

	case ABRK:
		return 0xD4<<24 | 1<<21 | 0

	case AHLT:
		return 0xD4<<24 | 2<<21 | 0

	case ADCPS1:
		return 0xD4<<24 | 5<<21 | 1

	case ADCPS2:
		return 0xD4<<24 | 5<<21 | 2

	case ADCPS3:
		return 0xD4<<24 | 5<<21 | 3

	case ACLREX:
		return SYSOP(0, 0, 3, 3, 0, 2, 0x1F)
	}

	ctxt.Diag("bad imm %v", Aconv(a))
	prasm(ctxt.Curp)
	return 0
}

func brdist(ctxt *obj.Link, p *obj.Prog, preshift int, flen int, shift int) int64 {
	var v int64
	var t int64
	v = 0
	t = 0
	if p.Pcond != nil {
		v = (p.Pcond.Pc >> uint(preshift)) - (ctxt.Pc >> uint(preshift))
		if (v & ((1 << uint(shift)) - 1)) != 0 {
			ctxt.Diag("misaligned label\n%v", p)
		}
		v >>= uint(shift)
		t = int64(1) << uint(flen-1)
		if v < -t || v >= t {
			ctxt.Diag("branch too far\n%v", p)
		}
	}

	return v & ((t << 1) - 1)
}

/*
 * pc-relative branches
 */
func opbra(ctxt *obj.Link, a int) uint32 {

	switch a {
	case ABEQ:
		return OPBcc(0x0)

	case ABNE:
		return OPBcc(0x1)

	case ABCS:
		return OPBcc(0x2)

	case ABHS:
		return OPBcc(0x2)

	case ABCC:
		return OPBcc(0x3)

	case ABLO:
		return OPBcc(0x3)

	case ABMI:
		return OPBcc(0x4)

	case ABPL:
		return OPBcc(0x5)

	case ABVS:
		return OPBcc(0x6)

	case ABVC:
		return OPBcc(0x7)

	case ABHI:
		return OPBcc(0x8)

	case ABLS:
		return OPBcc(0x9)

	case ABGE:
		return OPBcc(0xa)

	case ABLT:
		return OPBcc(0xb)

	case ABGT:
		return OPBcc(0xc)

	case ABLE:
		return OPBcc(0xd) /* imm19<<5 | cond */

	case ADUFFZERO,
		AB:
		return 0<<31 | 5<<26 /* imm26 */

	case ABL:
		return 1<<31 | 5<<26
	}

	ctxt.Diag("bad bra %v", Aconv(a))
	prasm(ctxt.Curp)
	return 0
}

func opbrr(ctxt *obj.Link, a int) uint32 {
	switch a {
	case ABL:
		return OPBLR(1) /* BLR */

	case AB:
		return OPBLR(0) /* BR */

	case ARET:
		return OPBLR(2) /* RET */
	}

	ctxt.Diag("bad brr %v", Aconv(a))
	prasm(ctxt.Curp)
	return 0
}

func op0(ctxt *obj.Link, a int) uint32 {
	switch a {
	case ADRPS:
		return 0x6B<<25 | 5<<21 | 0x1F<<16 | 0x1F<<5

	case AERET:
		return 0x6B<<25 | 4<<21 | 0x1F<<16 | 0<<10 | 0x1F<<5

	case ANOP:
		return SYSHINT(0)

	case AYIELD:
		return SYSHINT(1)

	case AWFE:
		return SYSHINT(2)

	case AWFI:
		return SYSHINT(3)

	case ASEV:
		return SYSHINT(4)

	case ASEVL:
		return SYSHINT(5)
	}

	ctxt.Diag("bad op0 %v", Aconv(a))
	prasm(ctxt.Curp)
	return 0
}

/*
 * register offset
 */
func opload(ctxt *obj.Link, a int) uint32 {

	switch a {
	case ALDAR:
		return LDSTX(3, 1, 1, 0, 1) | 0x1F<<10

	case ALDARW:
		return LDSTX(2, 1, 1, 0, 1) | 0x1F<<10

	case ALDARB:
		return LDSTX(0, 1, 1, 0, 1) | 0x1F<<10

	case ALDARH:
		return LDSTX(1, 1, 1, 0, 1) | 0x1F<<10

	case ALDAXP:
		return LDSTX(3, 0, 1, 1, 1)

	case ALDAXPW:
		return LDSTX(2, 0, 1, 1, 1)

	case ALDAXR:
		return LDSTX(3, 0, 1, 0, 1) | 0x1F<<10

	case ALDAXRW:
		return LDSTX(2, 0, 1, 0, 1) | 0x1F<<10

	case ALDAXRB:
		return LDSTX(0, 0, 1, 0, 1) | 0x1F<<10

	case ALDAXRH:
		return LDSTX(1, 0, 1, 0, 1) | 0x1F<<10

	case ALDXR:
		return LDSTX(3, 0, 1, 0, 0) | 0x1F<<10

	case ALDXRB:
		return LDSTX(0, 0, 1, 0, 0) | 0x1F<<10

	case ALDXRH:
		return LDSTX(1, 0, 1, 0, 0) | 0x1F<<10

	case ALDXRW:
		return LDSTX(2, 0, 1, 0, 0) | 0x1F<<10

	case ALDXP:
		return LDSTX(3, 0, 1, 1, 0)

	case ALDXPW:
		return LDSTX(2, 0, 1, 1, 0)

	case AMOVNP:
		return S64 | 0<<30 | 5<<27 | 0<<26 | 0<<23 | 1<<22

	case AMOVNPW:
		return S32 | 0<<30 | 5<<27 | 0<<26 | 0<<23 | 1<<22
	}

	ctxt.Diag("bad opload %v\n%v", Aconv(a), ctxt.Curp)
	return 0
}

func opstore(ctxt *obj.Link, a int) uint32 {
	switch a {
	case ASTLR:
		return LDSTX(3, 1, 0, 0, 1) | 0x1F<<10

	case ASTLRB:
		return LDSTX(0, 1, 0, 0, 1) | 0x1F<<10

	case ASTLRH:
		return LDSTX(1, 1, 0, 0, 1) | 0x1F<<10

	case ASTLP:
		return LDSTX(3, 0, 0, 1, 1)

	case ASTLPW:
		return LDSTX(2, 0, 0, 1, 1)

	case ASTLRW:
		return LDSTX(2, 1, 0, 0, 1) | 0x1F<<10

	case ASTLXP:
		return LDSTX(2, 0, 0, 1, 1)

	case ASTLXPW:
		return LDSTX(3, 0, 0, 1, 1)

	case ASTLXR:
		return LDSTX(3, 0, 0, 0, 1) | 0x1F<<10

	case ASTLXRB:
		return LDSTX(0, 0, 0, 0, 1) | 0x1F<<10

	case ASTLXRH:
		return LDSTX(1, 0, 0, 0, 1) | 0x1F<<10

	case ASTLXRW:
		return LDSTX(2, 0, 0, 0, 1) | 0x1F<<10

	case ASTXR:
		return LDSTX(3, 0, 0, 0, 0) | 0x1F<<10

	case ASTXRB:
		return LDSTX(0, 0, 0, 0, 0) | 0x1F<<10

	case ASTXRH:
		return LDSTX(1, 0, 0, 0, 0) | 0x1F<<10

	case ASTXP:
		return LDSTX(3, 0, 0, 1, 0)

	case ASTXPW:
		return LDSTX(2, 0, 0, 1, 0)

	case ASTXRW:
		return LDSTX(2, 0, 0, 0, 0) | 0x1F<<10

	case AMOVNP:
		return S64 | 0<<30 | 5<<27 | 0<<26 | 0<<23 | 1<<22

	case AMOVNPW:
		return S32 | 0<<30 | 5<<27 | 0<<26 | 0<<23 | 1<<22
	}

	ctxt.Diag("bad opstore %v\n%v", Aconv(a), ctxt.Curp)
	return 0
}

/*
 * load/store register (unsigned immediate) C3.3.13
 *	these produce 64-bit values (when there's an option)
 */
func olsr12u(ctxt *obj.Link, o int32, v int32, b int, r int) uint32 {

	if v < 0 || v >= (1<<12) {
		ctxt.Diag("offset out of range: %d\n%v", v, ctxt.Curp)
	}
	o |= (v & 0xFFF) << 10
	o |= int32(b) << 5
	o |= int32(r)
	return uint32(o)
}

func opldr12(ctxt *obj.Link, a int) uint32 {
	switch a {
	case AMOV:
		return LDSTR12U(3, 0, 1) /* imm12<<10 | Rn<<5 | Rt */

	case AMOVW:
		return LDSTR12U(2, 0, 2)

	case AMOVWU:
		return LDSTR12U(2, 0, 1)

	case AMOVH:
		return LDSTR12U(1, 0, 2)

	case AMOVHU:
		return LDSTR12U(1, 0, 1)

	case AMOVB:
		return LDSTR12U(0, 0, 2)

	case AMOVBU:
		return LDSTR12U(0, 0, 1)

	case AFMOVS:
		return LDSTR12U(2, 1, 1)

	case AFMOVD:
		return LDSTR12U(3, 1, 1)
	}

	ctxt.Diag("bad opldr12 %v\n%v", Aconv(a), ctxt.Curp)
	return 0
}

func opstr12(ctxt *obj.Link, a int) uint32 {
	return LD2STR(opldr12(ctxt, a))
}

/*
 * load/store register (unscaled immediate) C3.3.12
 */
func olsr9s(ctxt *obj.Link, o int32, v int32, b int, r int) uint32 {

	if v < -256 || v > 255 {
		ctxt.Diag("offset out of range: %d\n%v", v, ctxt.Curp)
	}
	o |= (v & 0x1FF) << 12
	o |= int32(b) << 5
	o |= int32(r)
	return uint32(o)
}

func opldr9(ctxt *obj.Link, a int) uint32 {
	switch a {
	case AMOV:
		return LDSTR9S(3, 0, 1) /* simm9<<12 | Rn<<5 | Rt */

	case AMOVW:
		return LDSTR9S(2, 0, 2)

	case AMOVWU:
		return LDSTR9S(2, 0, 1)

	case AMOVH:
		return LDSTR9S(1, 0, 2)

	case AMOVHU:
		return LDSTR9S(1, 0, 1)

	case AMOVB:
		return LDSTR9S(0, 0, 2)

	case AMOVBU:
		return LDSTR9S(0, 0, 1)

	case AFMOVS:
		return LDSTR9S(2, 1, 1)

	case AFMOVD:
		return LDSTR9S(3, 1, 1)
	}

	ctxt.Diag("bad opldr9 %v\n%v", Aconv(a), ctxt.Curp)
	return 0
}

func opstr9(ctxt *obj.Link, a int) uint32 {
	return LD2STR(opldr9(ctxt, a))
}

func opldrpp(ctxt *obj.Link, a int) uint32 {
	switch a {
	case AMOV:
		return 3<<30 | 7<<27 | 0<<26 | 0<<24 | 1<<22 /* simm9<<12 | Rn<<5 | Rt */

	case AMOVW:
		return 2<<30 | 7<<27 | 0<<26 | 0<<24 | 2<<22

	case AMOVWU:
		return 2<<30 | 7<<27 | 0<<26 | 0<<24 | 1<<22

	case AMOVH:
		return 1<<30 | 7<<27 | 0<<26 | 0<<24 | 2<<22

	case AMOVHU:
		return 1<<30 | 7<<27 | 0<<26 | 0<<24 | 1<<22

	case AMOVB:
		return 0<<30 | 7<<27 | 0<<26 | 0<<24 | 2<<22

	case AMOVBU:
		return 0<<30 | 7<<27 | 0<<26 | 0<<24 | 1<<22
	}

	ctxt.Diag("bad opldr %v\n%v", Aconv(a), ctxt.Curp)
	return 0
}

/*
 * load/store register (extended register)
 */
func olsxrr(ctxt *obj.Link, as int, rt int, r1 int, r2 int) uint32 {

	ctxt.Diag("need load/store extended register\n%v", ctxt.Curp)
	return 0xffffffff
}

func oaddi(o1 int32, v int32, r int, rt int) uint32 {
	if (v & 0xFFF000) != 0 {
		v >>= 12
		o1 |= 1 << 22
	}

	o1 |= ((v & 0xFFF) << 10) | (int32(r) << 5) | int32(rt)
	return uint32(o1)
}

/*
 * load a a literal value into dr
 */
func omovlit(ctxt *obj.Link, as int, p *obj.Prog, a *obj.Addr, dr int) uint32 {

	var v int32
	var o1 int32
	var w int
	var fp int
	if p.Pcond == nil { /* not in literal pool */
		aclass(ctxt, a)
		fmt.Fprintf(ctxt.Bso, "omovlit add %d (%#x)\n", ctxt.Instoffset, uint64(ctxt.Instoffset))

		/* TO DO: could be clever, and use general constant builder */
		o1 = int32(opirr(ctxt, AADD))

		v = int32(ctxt.Instoffset)
		if v != 0 && (v&0xFFF) == 0 {
			v >>= 12
			o1 |= 1 << 22 /* shift, by 12 */
		}

		o1 |= ((v & 0xFFF) << 10) | (REGZERO << 5) | int32(dr)
	} else {

		fp = 0
		w = 0 /* default: 32 bit, unsigned */
		switch as {
		case AFMOVS:
			fp = 1

		case AFMOVD:
			fp = 1
			w = 1 /* 64 bit simd&fp */

		case AMOV:
			if p.Pcond.As == ADWORD {
				w = 1 /* 64 bit */
			} else if p.Pcond.To.Offset < 0 {
				w = 2 /* sign extend */
			}

		case AMOVB,
			AMOVH,
			AMOVW:
			w = 2 /* 32 bit, sign-extended to 64 */
			break
		}

		v = int32(brdist(ctxt, p, 0, 19, 2))
		o1 = (int32(w) << 30) | (int32(fp) << 26) | (3 << 27)
		o1 |= (v & 0x7FFFF) << 5
		o1 |= int32(dr)
	}

	return uint32(o1)
}

func opbfm(ctxt *obj.Link, a int, r int, s int, rf int, rt int) uint32 {
	var o uint32
	var c uint32
	o = opirr(ctxt, a)
	if (o & (1 << 31)) == 0 {
		c = 32
	} else {

		c = 64
	}
	if r < 0 || uint32(r) >= c {
		ctxt.Diag("illegal bit number\n%v", ctxt.Curp)
	}
	o |= (uint32(r) & 0x3F) << 16
	if s < 0 || uint32(s) >= c {
		ctxt.Diag("illegal bit number\n%v", ctxt.Curp)
	}
	o |= (uint32(s) & 0x3F) << 10
	o |= (uint32(rf) << 5) | uint32(rt)
	return o
}

func opextr(ctxt *obj.Link, a int, v int32, rn int, rm int, rt int) uint32 {
	var o uint32
	var c uint32
	o = opirr(ctxt, a)
	if (o & (1 << 31)) != 0 {
		c = 63
	} else {

		c = 31
	}
	if v < 0 || uint32(v) > c {
		ctxt.Diag("illegal bit number\n%v", ctxt.Curp)
	}
	o |= uint32(v) << 10
	o |= uint32(rn) << 5
	o |= uint32(rm) << 16
	o |= uint32(rt)
	return o
}

/*
 * size in log2(bytes)
 */
func movesize(a int) int {

	switch a {
	case AMOV:
		return 3

	case AMOVW,
		AMOVWU:
		return 2

	case AMOVH,
		AMOVHU:
		return 1

	case AMOVB,
		AMOVBU:
		return 0

	case AFMOVS:
		return 2

	case AFMOVD:
		return 3

	default:
		return -1
	}
}

var bitmasks = []Mask{
	Mask{1, 64, 0, 0x00000000000001},
	Mask{1, 64, 63, 0x00000000000002},
	Mask{2, 64, 0, 0x00000000000003},
	Mask{1, 64, 62, 0x00000000000004},
	Mask{2, 64, 63, 0x00000000000006},
	Mask{3, 64, 0, 0x00000000000007},
	Mask{1, 64, 61, 0x00000000000008},
	Mask{2, 64, 62, 0x0000000000000c},
	Mask{3, 64, 63, 0x0000000000000e},
	Mask{4, 64, 0, 0x0000000000000f},
	Mask{1, 64, 60, 0x00000000000010},
	Mask{2, 64, 61, 0x00000000000018},
	Mask{3, 64, 62, 0x0000000000001c},
	Mask{4, 64, 63, 0x0000000000001e},
	Mask{5, 64, 0, 0x0000000000001f},
	Mask{1, 64, 59, 0x00000000000020},
	Mask{2, 64, 60, 0x00000000000030},
	Mask{3, 64, 61, 0x00000000000038},
	Mask{4, 64, 62, 0x0000000000003c},
	Mask{5, 64, 63, 0x0000000000003e},
	Mask{6, 64, 0, 0x0000000000003f},
	Mask{1, 64, 58, 0x00000000000040},
	Mask{2, 64, 59, 0x00000000000060},
	Mask{3, 64, 60, 0x00000000000070},
	Mask{4, 64, 61, 0x00000000000078},
	Mask{5, 64, 62, 0x0000000000007c},
	Mask{6, 64, 63, 0x0000000000007e},
	Mask{7, 64, 0, 0x0000000000007f},
	Mask{1, 64, 57, 0x00000000000080},
	Mask{2, 64, 58, 0x000000000000c0},
	Mask{3, 64, 59, 0x000000000000e0},
	Mask{4, 64, 60, 0x000000000000f0},
	Mask{5, 64, 61, 0x000000000000f8},
	Mask{6, 64, 62, 0x000000000000fc},
	Mask{7, 64, 63, 0x000000000000fe},
	Mask{8, 64, 0, 0x000000000000ff},
	Mask{1, 64, 56, 0x00000000000100},
	Mask{2, 64, 57, 0x00000000000180},
	Mask{3, 64, 58, 0x000000000001c0},
	Mask{4, 64, 59, 0x000000000001e0},
	Mask{5, 64, 60, 0x000000000001f0},
	Mask{6, 64, 61, 0x000000000001f8},
	Mask{7, 64, 62, 0x000000000001fc},
	Mask{8, 64, 63, 0x000000000001fe},
	Mask{9, 64, 0, 0x000000000001ff},
	Mask{1, 64, 55, 0x00000000000200},
	Mask{2, 64, 56, 0x00000000000300},
	Mask{3, 64, 57, 0x00000000000380},
	Mask{4, 64, 58, 0x000000000003c0},
	Mask{5, 64, 59, 0x000000000003e0},
	Mask{6, 64, 60, 0x000000000003f0},
	Mask{7, 64, 61, 0x000000000003f8},
	Mask{8, 64, 62, 0x000000000003fc},
	Mask{9, 64, 63, 0x000000000003fe},
	Mask{10, 64, 0, 0x000000000003ff},
	Mask{1, 64, 54, 0x00000000000400},
	Mask{2, 64, 55, 0x00000000000600},
	Mask{3, 64, 56, 0x00000000000700},
	Mask{4, 64, 57, 0x00000000000780},
	Mask{5, 64, 58, 0x000000000007c0},
	Mask{6, 64, 59, 0x000000000007e0},
	Mask{7, 64, 60, 0x000000000007f0},
	Mask{8, 64, 61, 0x000000000007f8},
	Mask{9, 64, 62, 0x000000000007fc},
	Mask{10, 64, 63, 0x000000000007fe},
	Mask{11, 64, 0, 0x000000000007ff},
	Mask{1, 64, 53, 0x00000000000800},
	Mask{2, 64, 54, 0x00000000000c00},
	Mask{3, 64, 55, 0x00000000000e00},
	Mask{4, 64, 56, 0x00000000000f00},
	Mask{5, 64, 57, 0x00000000000f80},
	Mask{6, 64, 58, 0x00000000000fc0},
	Mask{7, 64, 59, 0x00000000000fe0},
	Mask{8, 64, 60, 0x00000000000ff0},
	Mask{9, 64, 61, 0x00000000000ff8},
	Mask{10, 64, 62, 0x00000000000ffc},
	Mask{11, 64, 63, 0x00000000000ffe},
	Mask{12, 64, 0, 0x00000000000fff},
	Mask{1, 64, 52, 0x00000000001000},
	Mask{2, 64, 53, 0x00000000001800},
	Mask{3, 64, 54, 0x00000000001c00},
	Mask{4, 64, 55, 0x00000000001e00},
	Mask{5, 64, 56, 0x00000000001f00},
	Mask{6, 64, 57, 0x00000000001f80},
	Mask{7, 64, 58, 0x00000000001fc0},
	Mask{8, 64, 59, 0x00000000001fe0},
	Mask{9, 64, 60, 0x00000000001ff0},
	Mask{10, 64, 61, 0x00000000001ff8},
	Mask{11, 64, 62, 0x00000000001ffc},
	Mask{12, 64, 63, 0x00000000001ffe},
	Mask{13, 64, 0, 0x00000000001fff},
	Mask{1, 64, 51, 0x00000000002000},
	Mask{2, 64, 52, 0x00000000003000},
	Mask{3, 64, 53, 0x00000000003800},
	Mask{4, 64, 54, 0x00000000003c00},
	Mask{5, 64, 55, 0x00000000003e00},
	Mask{6, 64, 56, 0x00000000003f00},
	Mask{7, 64, 57, 0x00000000003f80},
	Mask{8, 64, 58, 0x00000000003fc0},
	Mask{9, 64, 59, 0x00000000003fe0},
	Mask{10, 64, 60, 0x00000000003ff0},
	Mask{11, 64, 61, 0x00000000003ff8},
	Mask{12, 64, 62, 0x00000000003ffc},
	Mask{13, 64, 63, 0x00000000003ffe},
	Mask{14, 64, 0, 0x00000000003fff},
	Mask{1, 64, 50, 0x00000000004000},
	Mask{2, 64, 51, 0x00000000006000},
	Mask{3, 64, 52, 0x00000000007000},
	Mask{4, 64, 53, 0x00000000007800},
	Mask{5, 64, 54, 0x00000000007c00},
	Mask{6, 64, 55, 0x00000000007e00},
	Mask{7, 64, 56, 0x00000000007f00},
	Mask{8, 64, 57, 0x00000000007f80},
	Mask{9, 64, 58, 0x00000000007fc0},
	Mask{10, 64, 59, 0x00000000007fe0},
	Mask{11, 64, 60, 0x00000000007ff0},
	Mask{12, 64, 61, 0x00000000007ff8},
	Mask{13, 64, 62, 0x00000000007ffc},
	Mask{14, 64, 63, 0x00000000007ffe},
	Mask{15, 64, 0, 0x00000000007fff},
	Mask{1, 64, 49, 0x00000000008000},
	Mask{2, 64, 50, 0x0000000000c000},
	Mask{3, 64, 51, 0x0000000000e000},
	Mask{4, 64, 52, 0x0000000000f000},
	Mask{5, 64, 53, 0x0000000000f800},
	Mask{6, 64, 54, 0x0000000000fc00},
	Mask{7, 64, 55, 0x0000000000fe00},
	Mask{8, 64, 56, 0x0000000000ff00},
	Mask{9, 64, 57, 0x0000000000ff80},
	Mask{10, 64, 58, 0x0000000000ffc0},
	Mask{11, 64, 59, 0x0000000000ffe0},
	Mask{12, 64, 60, 0x0000000000fff0},
	Mask{13, 64, 61, 0x0000000000fff8},
	Mask{14, 64, 62, 0x0000000000fffc},
	Mask{15, 64, 63, 0x0000000000fffe},
	Mask{16, 64, 0, 0x0000000000ffff},
	Mask{1, 64, 48, 0x00000000010000},
	Mask{2, 64, 49, 0x00000000018000},
	Mask{3, 64, 50, 0x0000000001c000},
	Mask{4, 64, 51, 0x0000000001e000},
	Mask{5, 64, 52, 0x0000000001f000},
	Mask{6, 64, 53, 0x0000000001f800},
	Mask{7, 64, 54, 0x0000000001fc00},
	Mask{8, 64, 55, 0x0000000001fe00},
	Mask{9, 64, 56, 0x0000000001ff00},
	Mask{10, 64, 57, 0x0000000001ff80},
	Mask{11, 64, 58, 0x0000000001ffc0},
	Mask{12, 64, 59, 0x0000000001ffe0},
	Mask{13, 64, 60, 0x0000000001fff0},
	Mask{14, 64, 61, 0x0000000001fff8},
	Mask{15, 64, 62, 0x0000000001fffc},
	Mask{16, 64, 63, 0x0000000001fffe},
	Mask{17, 64, 0, 0x0000000001ffff},
	Mask{1, 64, 47, 0x00000000020000},
	Mask{2, 64, 48, 0x00000000030000},
	Mask{3, 64, 49, 0x00000000038000},
	Mask{4, 64, 50, 0x0000000003c000},
	Mask{5, 64, 51, 0x0000000003e000},
	Mask{6, 64, 52, 0x0000000003f000},
	Mask{7, 64, 53, 0x0000000003f800},
	Mask{8, 64, 54, 0x0000000003fc00},
	Mask{9, 64, 55, 0x0000000003fe00},
	Mask{10, 64, 56, 0x0000000003ff00},
	Mask{11, 64, 57, 0x0000000003ff80},
	Mask{12, 64, 58, 0x0000000003ffc0},
	Mask{13, 64, 59, 0x0000000003ffe0},
	Mask{14, 64, 60, 0x0000000003fff0},
	Mask{15, 64, 61, 0x0000000003fff8},
	Mask{16, 64, 62, 0x0000000003fffc},
	Mask{17, 64, 63, 0x0000000003fffe},
	Mask{18, 64, 0, 0x0000000003ffff},
	Mask{1, 64, 46, 0x00000000040000},
	Mask{2, 64, 47, 0x00000000060000},
	Mask{3, 64, 48, 0x00000000070000},
	Mask{4, 64, 49, 0x00000000078000},
	Mask{5, 64, 50, 0x0000000007c000},
	Mask{6, 64, 51, 0x0000000007e000},
	Mask{7, 64, 52, 0x0000000007f000},
	Mask{8, 64, 53, 0x0000000007f800},
	Mask{9, 64, 54, 0x0000000007fc00},
	Mask{10, 64, 55, 0x0000000007fe00},
	Mask{11, 64, 56, 0x0000000007ff00},
	Mask{12, 64, 57, 0x0000000007ff80},
	Mask{13, 64, 58, 0x0000000007ffc0},
	Mask{14, 64, 59, 0x0000000007ffe0},
	Mask{15, 64, 60, 0x0000000007fff0},
	Mask{16, 64, 61, 0x0000000007fff8},
	Mask{17, 64, 62, 0x0000000007fffc},
	Mask{18, 64, 63, 0x0000000007fffe},
	Mask{19, 64, 0, 0x0000000007ffff},
	Mask{1, 64, 45, 0x00000000080000},
	Mask{2, 64, 46, 0x000000000c0000},
	Mask{3, 64, 47, 0x000000000e0000},
	Mask{4, 64, 48, 0x000000000f0000},
	Mask{5, 64, 49, 0x000000000f8000},
	Mask{6, 64, 50, 0x000000000fc000},
	Mask{7, 64, 51, 0x000000000fe000},
	Mask{8, 64, 52, 0x000000000ff000},
	Mask{9, 64, 53, 0x000000000ff800},
	Mask{10, 64, 54, 0x000000000ffc00},
	Mask{11, 64, 55, 0x000000000ffe00},
	Mask{12, 64, 56, 0x000000000fff00},
	Mask{13, 64, 57, 0x000000000fff80},
	Mask{14, 64, 58, 0x000000000fffc0},
	Mask{15, 64, 59, 0x000000000fffe0},
	Mask{16, 64, 60, 0x000000000ffff0},
	Mask{17, 64, 61, 0x000000000ffff8},
	Mask{18, 64, 62, 0x000000000ffffc},
	Mask{19, 64, 63, 0x000000000ffffe},
	Mask{20, 64, 0, 0x000000000fffff},
	Mask{1, 64, 44, 0x00000000100000},
	Mask{2, 64, 45, 0x00000000180000},
	Mask{3, 64, 46, 0x000000001c0000},
	Mask{4, 64, 47, 0x000000001e0000},
	Mask{5, 64, 48, 0x000000001f0000},
	Mask{6, 64, 49, 0x000000001f8000},
	Mask{7, 64, 50, 0x000000001fc000},
	Mask{8, 64, 51, 0x000000001fe000},
	Mask{9, 64, 52, 0x000000001ff000},
	Mask{10, 64, 53, 0x000000001ff800},
	Mask{11, 64, 54, 0x000000001ffc00},
	Mask{12, 64, 55, 0x000000001ffe00},
	Mask{13, 64, 56, 0x000000001fff00},
	Mask{14, 64, 57, 0x000000001fff80},
	Mask{15, 64, 58, 0x000000001fffc0},
	Mask{16, 64, 59, 0x000000001fffe0},
	Mask{17, 64, 60, 0x000000001ffff0},
	Mask{18, 64, 61, 0x000000001ffff8},
	Mask{19, 64, 62, 0x000000001ffffc},
	Mask{20, 64, 63, 0x000000001ffffe},
	Mask{21, 64, 0, 0x000000001fffff},
	Mask{1, 64, 43, 0x00000000200000},
	Mask{2, 64, 44, 0x00000000300000},
	Mask{3, 64, 45, 0x00000000380000},
	Mask{4, 64, 46, 0x000000003c0000},
	Mask{5, 64, 47, 0x000000003e0000},
	Mask{6, 64, 48, 0x000000003f0000},
	Mask{7, 64, 49, 0x000000003f8000},
	Mask{8, 64, 50, 0x000000003fc000},
	Mask{9, 64, 51, 0x000000003fe000},
	Mask{10, 64, 52, 0x000000003ff000},
	Mask{11, 64, 53, 0x000000003ff800},
	Mask{12, 64, 54, 0x000000003ffc00},
	Mask{13, 64, 55, 0x000000003ffe00},
	Mask{14, 64, 56, 0x000000003fff00},
	Mask{15, 64, 57, 0x000000003fff80},
	Mask{16, 64, 58, 0x000000003fffc0},
	Mask{17, 64, 59, 0x000000003fffe0},
	Mask{18, 64, 60, 0x000000003ffff0},
	Mask{19, 64, 61, 0x000000003ffff8},
	Mask{20, 64, 62, 0x000000003ffffc},
	Mask{21, 64, 63, 0x000000003ffffe},
	Mask{22, 64, 0, 0x000000003fffff},
	Mask{1, 64, 42, 0x00000000400000},
	Mask{2, 64, 43, 0x00000000600000},
	Mask{3, 64, 44, 0x00000000700000},
	Mask{4, 64, 45, 0x00000000780000},
	Mask{5, 64, 46, 0x000000007c0000},
	Mask{6, 64, 47, 0x000000007e0000},
	Mask{7, 64, 48, 0x000000007f0000},
	Mask{8, 64, 49, 0x000000007f8000},
	Mask{9, 64, 50, 0x000000007fc000},
	Mask{10, 64, 51, 0x000000007fe000},
	Mask{11, 64, 52, 0x000000007ff000},
	Mask{12, 64, 53, 0x000000007ff800},
	Mask{13, 64, 54, 0x000000007ffc00},
	Mask{14, 64, 55, 0x000000007ffe00},
	Mask{15, 64, 56, 0x000000007fff00},
	Mask{16, 64, 57, 0x000000007fff80},
	Mask{17, 64, 58, 0x000000007fffc0},
	Mask{18, 64, 59, 0x000000007fffe0},
	Mask{19, 64, 60, 0x000000007ffff0},
	Mask{20, 64, 61, 0x000000007ffff8},
	Mask{21, 64, 62, 0x000000007ffffc},
	Mask{22, 64, 63, 0x000000007ffffe},
	Mask{23, 64, 0, 0x000000007fffff},
	Mask{1, 64, 41, 0x00000000800000},
	Mask{2, 64, 42, 0x00000000c00000},
	Mask{3, 64, 43, 0x00000000e00000},
	Mask{4, 64, 44, 0x00000000f00000},
	Mask{5, 64, 45, 0x00000000f80000},
	Mask{6, 64, 46, 0x00000000fc0000},
	Mask{7, 64, 47, 0x00000000fe0000},
	Mask{8, 64, 48, 0x00000000ff0000},
	Mask{9, 64, 49, 0x00000000ff8000},
	Mask{10, 64, 50, 0x00000000ffc000},
	Mask{11, 64, 51, 0x00000000ffe000},
	Mask{12, 64, 52, 0x00000000fff000},
	Mask{13, 64, 53, 0x00000000fff800},
	Mask{14, 64, 54, 0x00000000fffc00},
	Mask{15, 64, 55, 0x00000000fffe00},
	Mask{16, 64, 56, 0x00000000ffff00},
	Mask{17, 64, 57, 0x00000000ffff80},
	Mask{18, 64, 58, 0x00000000ffffc0},
	Mask{19, 64, 59, 0x00000000ffffe0},
	Mask{20, 64, 60, 0x00000000fffff0},
	Mask{21, 64, 61, 0x00000000fffff8},
	Mask{22, 64, 62, 0x00000000fffffc},
	Mask{23, 64, 63, 0x00000000fffffe},
	Mask{24, 64, 0, 0x00000000ffffff},
	Mask{1, 64, 40, 0x00000001000000},
	Mask{2, 64, 41, 0x00000001800000},
	Mask{3, 64, 42, 0x00000001c00000},
	Mask{4, 64, 43, 0x00000001e00000},
	Mask{5, 64, 44, 0x00000001f00000},
	Mask{6, 64, 45, 0x00000001f80000},
	Mask{7, 64, 46, 0x00000001fc0000},
	Mask{8, 64, 47, 0x00000001fe0000},
	Mask{9, 64, 48, 0x00000001ff0000},
	Mask{10, 64, 49, 0x00000001ff8000},
	Mask{11, 64, 50, 0x00000001ffc000},
	Mask{12, 64, 51, 0x00000001ffe000},
	Mask{13, 64, 52, 0x00000001fff000},
	Mask{14, 64, 53, 0x00000001fff800},
	Mask{15, 64, 54, 0x00000001fffc00},
	Mask{16, 64, 55, 0x00000001fffe00},
	Mask{17, 64, 56, 0x00000001ffff00},
	Mask{18, 64, 57, 0x00000001ffff80},
	Mask{19, 64, 58, 0x00000001ffffc0},
	Mask{20, 64, 59, 0x00000001ffffe0},
	Mask{21, 64, 60, 0x00000001fffff0},
	Mask{22, 64, 61, 0x00000001fffff8},
	Mask{23, 64, 62, 0x00000001fffffc},
	Mask{24, 64, 63, 0x00000001fffffe},
	Mask{25, 64, 0, 0x00000001ffffff},
	Mask{1, 64, 39, 0x00000002000000},
	Mask{2, 64, 40, 0x00000003000000},
	Mask{3, 64, 41, 0x00000003800000},
	Mask{4, 64, 42, 0x00000003c00000},
	Mask{5, 64, 43, 0x00000003e00000},
	Mask{6, 64, 44, 0x00000003f00000},
	Mask{7, 64, 45, 0x00000003f80000},
	Mask{8, 64, 46, 0x00000003fc0000},
	Mask{9, 64, 47, 0x00000003fe0000},
	Mask{10, 64, 48, 0x00000003ff0000},
	Mask{11, 64, 49, 0x00000003ff8000},
	Mask{12, 64, 50, 0x00000003ffc000},
	Mask{13, 64, 51, 0x00000003ffe000},
	Mask{14, 64, 52, 0x00000003fff000},
	Mask{15, 64, 53, 0x00000003fff800},
	Mask{16, 64, 54, 0x00000003fffc00},
	Mask{17, 64, 55, 0x00000003fffe00},
	Mask{18, 64, 56, 0x00000003ffff00},
	Mask{19, 64, 57, 0x00000003ffff80},
	Mask{20, 64, 58, 0x00000003ffffc0},
	Mask{21, 64, 59, 0x00000003ffffe0},
	Mask{22, 64, 60, 0x00000003fffff0},
	Mask{23, 64, 61, 0x00000003fffff8},
	Mask{24, 64, 62, 0x00000003fffffc},
	Mask{25, 64, 63, 0x00000003fffffe},
	Mask{26, 64, 0, 0x00000003ffffff},
	Mask{1, 64, 38, 0x00000004000000},
	Mask{2, 64, 39, 0x00000006000000},
	Mask{3, 64, 40, 0x00000007000000},
	Mask{4, 64, 41, 0x00000007800000},
	Mask{5, 64, 42, 0x00000007c00000},
	Mask{6, 64, 43, 0x00000007e00000},
	Mask{7, 64, 44, 0x00000007f00000},
	Mask{8, 64, 45, 0x00000007f80000},
	Mask{9, 64, 46, 0x00000007fc0000},
	Mask{10, 64, 47, 0x00000007fe0000},
	Mask{11, 64, 48, 0x00000007ff0000},
	Mask{12, 64, 49, 0x00000007ff8000},
	Mask{13, 64, 50, 0x00000007ffc000},
	Mask{14, 64, 51, 0x00000007ffe000},
	Mask{15, 64, 52, 0x00000007fff000},
	Mask{16, 64, 53, 0x00000007fff800},
	Mask{17, 64, 54, 0x00000007fffc00},
	Mask{18, 64, 55, 0x00000007fffe00},
	Mask{19, 64, 56, 0x00000007ffff00},
	Mask{20, 64, 57, 0x00000007ffff80},
	Mask{21, 64, 58, 0x00000007ffffc0},
	Mask{22, 64, 59, 0x00000007ffffe0},
	Mask{23, 64, 60, 0x00000007fffff0},
	Mask{24, 64, 61, 0x00000007fffff8},
	Mask{25, 64, 62, 0x00000007fffffc},
	Mask{26, 64, 63, 0x00000007fffffe},
	Mask{27, 64, 0, 0x00000007ffffff},
	Mask{1, 64, 37, 0x00000008000000},
	Mask{2, 64, 38, 0x0000000c000000},
	Mask{3, 64, 39, 0x0000000e000000},
	Mask{4, 64, 40, 0x0000000f000000},
	Mask{5, 64, 41, 0x0000000f800000},
	Mask{6, 64, 42, 0x0000000fc00000},
	Mask{7, 64, 43, 0x0000000fe00000},
	Mask{8, 64, 44, 0x0000000ff00000},
	Mask{9, 64, 45, 0x0000000ff80000},
	Mask{10, 64, 46, 0x0000000ffc0000},
	Mask{11, 64, 47, 0x0000000ffe0000},
	Mask{12, 64, 48, 0x0000000fff0000},
	Mask{13, 64, 49, 0x0000000fff8000},
	Mask{14, 64, 50, 0x0000000fffc000},
	Mask{15, 64, 51, 0x0000000fffe000},
	Mask{16, 64, 52, 0x0000000ffff000},
	Mask{17, 64, 53, 0x0000000ffff800},
	Mask{18, 64, 54, 0x0000000ffffc00},
	Mask{19, 64, 55, 0x0000000ffffe00},
	Mask{20, 64, 56, 0x0000000fffff00},
	Mask{21, 64, 57, 0x0000000fffff80},
	Mask{22, 64, 58, 0x0000000fffffc0},
	Mask{23, 64, 59, 0x0000000fffffe0},
	Mask{24, 64, 60, 0x0000000ffffff0},
	Mask{25, 64, 61, 0x0000000ffffff8},
	Mask{26, 64, 62, 0x0000000ffffffc},
	Mask{27, 64, 63, 0x0000000ffffffe},
	Mask{28, 64, 0, 0x0000000fffffff},
	Mask{1, 64, 36, 0x00000010000000},
	Mask{2, 64, 37, 0x00000018000000},
	Mask{3, 64, 38, 0x0000001c000000},
	Mask{4, 64, 39, 0x0000001e000000},
	Mask{5, 64, 40, 0x0000001f000000},
	Mask{6, 64, 41, 0x0000001f800000},
	Mask{7, 64, 42, 0x0000001fc00000},
	Mask{8, 64, 43, 0x0000001fe00000},
	Mask{9, 64, 44, 0x0000001ff00000},
	Mask{10, 64, 45, 0x0000001ff80000},
	Mask{11, 64, 46, 0x0000001ffc0000},
	Mask{12, 64, 47, 0x0000001ffe0000},
	Mask{13, 64, 48, 0x0000001fff0000},
	Mask{14, 64, 49, 0x0000001fff8000},
	Mask{15, 64, 50, 0x0000001fffc000},
	Mask{16, 64, 51, 0x0000001fffe000},
	Mask{17, 64, 52, 0x0000001ffff000},
	Mask{18, 64, 53, 0x0000001ffff800},
	Mask{19, 64, 54, 0x0000001ffffc00},
	Mask{20, 64, 55, 0x0000001ffffe00},
	Mask{21, 64, 56, 0x0000001fffff00},
	Mask{22, 64, 57, 0x0000001fffff80},
	Mask{23, 64, 58, 0x0000001fffffc0},
	Mask{24, 64, 59, 0x0000001fffffe0},
	Mask{25, 64, 60, 0x0000001ffffff0},
	Mask{26, 64, 61, 0x0000001ffffff8},
	Mask{27, 64, 62, 0x0000001ffffffc},
	Mask{28, 64, 63, 0x0000001ffffffe},
	Mask{29, 64, 0, 0x0000001fffffff},
	Mask{1, 64, 35, 0x00000020000000},
	Mask{2, 64, 36, 0x00000030000000},
	Mask{3, 64, 37, 0x00000038000000},
	Mask{4, 64, 38, 0x0000003c000000},
	Mask{5, 64, 39, 0x0000003e000000},
	Mask{6, 64, 40, 0x0000003f000000},
	Mask{7, 64, 41, 0x0000003f800000},
	Mask{8, 64, 42, 0x0000003fc00000},
	Mask{9, 64, 43, 0x0000003fe00000},
	Mask{10, 64, 44, 0x0000003ff00000},
	Mask{11, 64, 45, 0x0000003ff80000},
	Mask{12, 64, 46, 0x0000003ffc0000},
	Mask{13, 64, 47, 0x0000003ffe0000},
	Mask{14, 64, 48, 0x0000003fff0000},
	Mask{15, 64, 49, 0x0000003fff8000},
	Mask{16, 64, 50, 0x0000003fffc000},
	Mask{17, 64, 51, 0x0000003fffe000},
	Mask{18, 64, 52, 0x0000003ffff000},
	Mask{19, 64, 53, 0x0000003ffff800},
	Mask{20, 64, 54, 0x0000003ffffc00},
	Mask{21, 64, 55, 0x0000003ffffe00},
	Mask{22, 64, 56, 0x0000003fffff00},
	Mask{23, 64, 57, 0x0000003fffff80},
	Mask{24, 64, 58, 0x0000003fffffc0},
	Mask{25, 64, 59, 0x0000003fffffe0},
	Mask{26, 64, 60, 0x0000003ffffff0},
	Mask{27, 64, 61, 0x0000003ffffff8},
	Mask{28, 64, 62, 0x0000003ffffffc},
	Mask{29, 64, 63, 0x0000003ffffffe},
	Mask{30, 64, 0, 0x0000003fffffff},
	Mask{1, 64, 34, 0x00000040000000},
	Mask{2, 64, 35, 0x00000060000000},
	Mask{3, 64, 36, 0x00000070000000},
	Mask{4, 64, 37, 0x00000078000000},
	Mask{5, 64, 38, 0x0000007c000000},
	Mask{6, 64, 39, 0x0000007e000000},
	Mask{7, 64, 40, 0x0000007f000000},
	Mask{8, 64, 41, 0x0000007f800000},
	Mask{9, 64, 42, 0x0000007fc00000},
	Mask{10, 64, 43, 0x0000007fe00000},
	Mask{11, 64, 44, 0x0000007ff00000},
	Mask{12, 64, 45, 0x0000007ff80000},
	Mask{13, 64, 46, 0x0000007ffc0000},
	Mask{14, 64, 47, 0x0000007ffe0000},
	Mask{15, 64, 48, 0x0000007fff0000},
	Mask{16, 64, 49, 0x0000007fff8000},
	Mask{17, 64, 50, 0x0000007fffc000},
	Mask{18, 64, 51, 0x0000007fffe000},
	Mask{19, 64, 52, 0x0000007ffff000},
	Mask{20, 64, 53, 0x0000007ffff800},
	Mask{21, 64, 54, 0x0000007ffffc00},
	Mask{22, 64, 55, 0x0000007ffffe00},
	Mask{23, 64, 56, 0x0000007fffff00},
	Mask{24, 64, 57, 0x0000007fffff80},
	Mask{25, 64, 58, 0x0000007fffffc0},
	Mask{26, 64, 59, 0x0000007fffffe0},
	Mask{27, 64, 60, 0x0000007ffffff0},
	Mask{28, 64, 61, 0x0000007ffffff8},
	Mask{29, 64, 62, 0x0000007ffffffc},
	Mask{30, 64, 63, 0x0000007ffffffe},
	Mask{31, 64, 0, 0x0000007fffffff},
	Mask{1, 64, 33, 0x00000080000000},
	Mask{2, 64, 34, 0x000000c0000000},
	Mask{3, 64, 35, 0x000000e0000000},
	Mask{4, 64, 36, 0x000000f0000000},
	Mask{5, 64, 37, 0x000000f8000000},
	Mask{6, 64, 38, 0x000000fc000000},
	Mask{7, 64, 39, 0x000000fe000000},
	Mask{8, 64, 40, 0x000000ff000000},
	Mask{9, 64, 41, 0x000000ff800000},
	Mask{10, 64, 42, 0x000000ffc00000},
	Mask{11, 64, 43, 0x000000ffe00000},
	Mask{12, 64, 44, 0x000000fff00000},
	Mask{13, 64, 45, 0x000000fff80000},
	Mask{14, 64, 46, 0x000000fffc0000},
	Mask{15, 64, 47, 0x000000fffe0000},
	Mask{16, 64, 48, 0x000000ffff0000},
	Mask{17, 64, 49, 0x000000ffff8000},
	Mask{18, 64, 50, 0x000000ffffc000},
	Mask{19, 64, 51, 0x000000ffffe000},
	Mask{20, 64, 52, 0x000000fffff000},
	Mask{21, 64, 53, 0x000000fffff800},
	Mask{22, 64, 54, 0x000000fffffc00},
	Mask{23, 64, 55, 0x000000fffffe00},
	Mask{24, 64, 56, 0x000000ffffff00},
	Mask{25, 64, 57, 0x000000ffffff80},
	Mask{26, 64, 58, 0x000000ffffffc0},
	Mask{27, 64, 59, 0x000000ffffffe0},
	Mask{28, 64, 60, 0x000000fffffff0},
	Mask{29, 64, 61, 0x000000fffffff8},
	Mask{30, 64, 62, 0x000000fffffffc},
	Mask{31, 64, 63, 0x000000fffffffe},
	Mask{32, 64, 0, 0x000000ffffffff},
	Mask{1, 64, 32, 0x00000100000000},
	Mask{1, 32, 0, 0x00000100000001},
	Mask{2, 64, 33, 0x00000180000000},
	Mask{3, 64, 34, 0x000001c0000000},
	Mask{4, 64, 35, 0x000001e0000000},
	Mask{5, 64, 36, 0x000001f0000000},
	Mask{6, 64, 37, 0x000001f8000000},
	Mask{7, 64, 38, 0x000001fc000000},
	Mask{8, 64, 39, 0x000001fe000000},
	Mask{9, 64, 40, 0x000001ff000000},
	Mask{10, 64, 41, 0x000001ff800000},
	Mask{11, 64, 42, 0x000001ffc00000},
	Mask{12, 64, 43, 0x000001ffe00000},
	Mask{13, 64, 44, 0x000001fff00000},
	Mask{14, 64, 45, 0x000001fff80000},
	Mask{15, 64, 46, 0x000001fffc0000},
	Mask{16, 64, 47, 0x000001fffe0000},
	Mask{17, 64, 48, 0x000001ffff0000},
	Mask{18, 64, 49, 0x000001ffff8000},
	Mask{19, 64, 50, 0x000001ffffc000},
	Mask{20, 64, 51, 0x000001ffffe000},
	Mask{21, 64, 52, 0x000001fffff000},
	Mask{22, 64, 53, 0x000001fffff800},
	Mask{23, 64, 54, 0x000001fffffc00},
	Mask{24, 64, 55, 0x000001fffffe00},
	Mask{25, 64, 56, 0x000001ffffff00},
	Mask{26, 64, 57, 0x000001ffffff80},
	Mask{27, 64, 58, 0x000001ffffffc0},
	Mask{28, 64, 59, 0x000001ffffffe0},
	Mask{29, 64, 60, 0x000001fffffff0},
	Mask{30, 64, 61, 0x000001fffffff8},
	Mask{31, 64, 62, 0x000001fffffffc},
	Mask{32, 64, 63, 0x000001fffffffe},
	Mask{33, 64, 0, 0x000001ffffffff},
	Mask{1, 64, 31, 0x00000200000000},
	Mask{1, 32, 31, 0x00000200000002},
	Mask{2, 64, 32, 0x00000300000000},
	Mask{2, 32, 0, 0x00000300000003},
	Mask{3, 64, 33, 0x00000380000000},
	Mask{4, 64, 34, 0x000003c0000000},
	Mask{5, 64, 35, 0x000003e0000000},
	Mask{6, 64, 36, 0x000003f0000000},
	Mask{7, 64, 37, 0x000003f8000000},
	Mask{8, 64, 38, 0x000003fc000000},
	Mask{9, 64, 39, 0x000003fe000000},
	Mask{10, 64, 40, 0x000003ff000000},
	Mask{11, 64, 41, 0x000003ff800000},
	Mask{12, 64, 42, 0x000003ffc00000},
	Mask{13, 64, 43, 0x000003ffe00000},
	Mask{14, 64, 44, 0x000003fff00000},
	Mask{15, 64, 45, 0x000003fff80000},
	Mask{16, 64, 46, 0x000003fffc0000},
	Mask{17, 64, 47, 0x000003fffe0000},
	Mask{18, 64, 48, 0x000003ffff0000},
	Mask{19, 64, 49, 0x000003ffff8000},
	Mask{20, 64, 50, 0x000003ffffc000},
	Mask{21, 64, 51, 0x000003ffffe000},
	Mask{22, 64, 52, 0x000003fffff000},
	Mask{23, 64, 53, 0x000003fffff800},
	Mask{24, 64, 54, 0x000003fffffc00},
	Mask{25, 64, 55, 0x000003fffffe00},
	Mask{26, 64, 56, 0x000003ffffff00},
	Mask{27, 64, 57, 0x000003ffffff80},
	Mask{28, 64, 58, 0x000003ffffffc0},
	Mask{29, 64, 59, 0x000003ffffffe0},
	Mask{30, 64, 60, 0x000003fffffff0},
	Mask{31, 64, 61, 0x000003fffffff8},
	Mask{32, 64, 62, 0x000003fffffffc},
	Mask{33, 64, 63, 0x000003fffffffe},
	Mask{34, 64, 0, 0x000003ffffffff},
	Mask{1, 64, 30, 0x00000400000000},
	Mask{1, 32, 30, 0x00000400000004},
	Mask{2, 64, 31, 0x00000600000000},
	Mask{2, 32, 31, 0x00000600000006},
	Mask{3, 64, 32, 0x00000700000000},
	Mask{3, 32, 0, 0x00000700000007},
	Mask{4, 64, 33, 0x00000780000000},
	Mask{5, 64, 34, 0x000007c0000000},
	Mask{6, 64, 35, 0x000007e0000000},
	Mask{7, 64, 36, 0x000007f0000000},
	Mask{8, 64, 37, 0x000007f8000000},
	Mask{9, 64, 38, 0x000007fc000000},
	Mask{10, 64, 39, 0x000007fe000000},
	Mask{11, 64, 40, 0x000007ff000000},
	Mask{12, 64, 41, 0x000007ff800000},
	Mask{13, 64, 42, 0x000007ffc00000},
	Mask{14, 64, 43, 0x000007ffe00000},
	Mask{15, 64, 44, 0x000007fff00000},
	Mask{16, 64, 45, 0x000007fff80000},
	Mask{17, 64, 46, 0x000007fffc0000},
	Mask{18, 64, 47, 0x000007fffe0000},
	Mask{19, 64, 48, 0x000007ffff0000},
	Mask{20, 64, 49, 0x000007ffff8000},
	Mask{21, 64, 50, 0x000007ffffc000},
	Mask{22, 64, 51, 0x000007ffffe000},
	Mask{23, 64, 52, 0x000007fffff000},
	Mask{24, 64, 53, 0x000007fffff800},
	Mask{25, 64, 54, 0x000007fffffc00},
	Mask{26, 64, 55, 0x000007fffffe00},
	Mask{27, 64, 56, 0x000007ffffff00},
	Mask{28, 64, 57, 0x000007ffffff80},
	Mask{29, 64, 58, 0x000007ffffffc0},
	Mask{30, 64, 59, 0x000007ffffffe0},
	Mask{31, 64, 60, 0x000007fffffff0},
	Mask{32, 64, 61, 0x000007fffffff8},
	Mask{33, 64, 62, 0x000007fffffffc},
	Mask{34, 64, 63, 0x000007fffffffe},
	Mask{35, 64, 0, 0x000007ffffffff},
	Mask{1, 64, 29, 0x00000800000000},
	Mask{1, 32, 29, 0x00000800000008},
	Mask{2, 64, 30, 0x00000c00000000},
	Mask{2, 32, 30, 0x00000c0000000c},
	Mask{3, 64, 31, 0x00000e00000000},
	Mask{3, 32, 31, 0x00000e0000000e},
	Mask{4, 64, 32, 0x00000f00000000},
	Mask{4, 32, 0, 0x00000f0000000f},
	Mask{5, 64, 33, 0x00000f80000000},
	Mask{6, 64, 34, 0x00000fc0000000},
	Mask{7, 64, 35, 0x00000fe0000000},
	Mask{8, 64, 36, 0x00000ff0000000},
	Mask{9, 64, 37, 0x00000ff8000000},
	Mask{10, 64, 38, 0x00000ffc000000},
	Mask{11, 64, 39, 0x00000ffe000000},
	Mask{12, 64, 40, 0x00000fff000000},
	Mask{13, 64, 41, 0x00000fff800000},
	Mask{14, 64, 42, 0x00000fffc00000},
	Mask{15, 64, 43, 0x00000fffe00000},
	Mask{16, 64, 44, 0x00000ffff00000},
	Mask{17, 64, 45, 0x00000ffff80000},
	Mask{18, 64, 46, 0x00000ffffc0000},
	Mask{19, 64, 47, 0x00000ffffe0000},
	Mask{20, 64, 48, 0x00000fffff0000},
	Mask{21, 64, 49, 0x00000fffff8000},
	Mask{22, 64, 50, 0x00000fffffc000},
	Mask{23, 64, 51, 0x00000fffffe000},
	Mask{24, 64, 52, 0x00000ffffff000},
	Mask{25, 64, 53, 0x00000ffffff800},
	Mask{26, 64, 54, 0x00000ffffffc00},
	Mask{27, 64, 55, 0x00000ffffffe00},
	Mask{28, 64, 56, 0x00000fffffff00},
	Mask{29, 64, 57, 0x00000fffffff80},
	Mask{30, 64, 58, 0x00000fffffffc0},
	Mask{31, 64, 59, 0x00000fffffffe0},
	Mask{32, 64, 60, 0x00000ffffffff0},
	Mask{33, 64, 61, 0x00000ffffffff8},
	Mask{34, 64, 62, 0x00000ffffffffc},
	Mask{35, 64, 63, 0x00000ffffffffe},
	Mask{36, 64, 0, 0x00000fffffffff},
	Mask{1, 64, 28, 0x00001000000000},
	Mask{1, 32, 28, 0x00001000000010},
	Mask{2, 64, 29, 0x00001800000000},
	Mask{2, 32, 29, 0x00001800000018},
	Mask{3, 64, 30, 0x00001c00000000},
	Mask{3, 32, 30, 0x00001c0000001c},
	Mask{4, 64, 31, 0x00001e00000000},
	Mask{4, 32, 31, 0x00001e0000001e},
	Mask{5, 64, 32, 0x00001f00000000},
	Mask{5, 32, 0, 0x00001f0000001f},
	Mask{6, 64, 33, 0x00001f80000000},
	Mask{7, 64, 34, 0x00001fc0000000},
	Mask{8, 64, 35, 0x00001fe0000000},
	Mask{9, 64, 36, 0x00001ff0000000},
	Mask{10, 64, 37, 0x00001ff8000000},
	Mask{11, 64, 38, 0x00001ffc000000},
	Mask{12, 64, 39, 0x00001ffe000000},
	Mask{13, 64, 40, 0x00001fff000000},
	Mask{14, 64, 41, 0x00001fff800000},
	Mask{15, 64, 42, 0x00001fffc00000},
	Mask{16, 64, 43, 0x00001fffe00000},
	Mask{17, 64, 44, 0x00001ffff00000},
	Mask{18, 64, 45, 0x00001ffff80000},
	Mask{19, 64, 46, 0x00001ffffc0000},
	Mask{20, 64, 47, 0x00001ffffe0000},
	Mask{21, 64, 48, 0x00001fffff0000},
	Mask{22, 64, 49, 0x00001fffff8000},
	Mask{23, 64, 50, 0x00001fffffc000},
	Mask{24, 64, 51, 0x00001fffffe000},
	Mask{25, 64, 52, 0x00001ffffff000},
	Mask{26, 64, 53, 0x00001ffffff800},
	Mask{27, 64, 54, 0x00001ffffffc00},
	Mask{28, 64, 55, 0x00001ffffffe00},
	Mask{29, 64, 56, 0x00001fffffff00},
	Mask{30, 64, 57, 0x00001fffffff80},
	Mask{31, 64, 58, 0x00001fffffffc0},
	Mask{32, 64, 59, 0x00001fffffffe0},
	Mask{33, 64, 60, 0x00001ffffffff0},
	Mask{34, 64, 61, 0x00001ffffffff8},
	Mask{35, 64, 62, 0x00001ffffffffc},
	Mask{36, 64, 63, 0x00001ffffffffe},
	Mask{37, 64, 0, 0x00001fffffffff},
	Mask{1, 64, 27, 0x00002000000000},
	Mask{1, 32, 27, 0x00002000000020},
	Mask{2, 64, 28, 0x00003000000000},
	Mask{2, 32, 28, 0x00003000000030},
	Mask{3, 64, 29, 0x00003800000000},
	Mask{3, 32, 29, 0x00003800000038},
	Mask{4, 64, 30, 0x00003c00000000},
	Mask{4, 32, 30, 0x00003c0000003c},
	Mask{5, 64, 31, 0x00003e00000000},
	Mask{5, 32, 31, 0x00003e0000003e},
	Mask{6, 64, 32, 0x00003f00000000},
	Mask{6, 32, 0, 0x00003f0000003f},
	Mask{7, 64, 33, 0x00003f80000000},
	Mask{8, 64, 34, 0x00003fc0000000},
	Mask{9, 64, 35, 0x00003fe0000000},
	Mask{10, 64, 36, 0x00003ff0000000},
	Mask{11, 64, 37, 0x00003ff8000000},
	Mask{12, 64, 38, 0x00003ffc000000},
	Mask{13, 64, 39, 0x00003ffe000000},
	Mask{14, 64, 40, 0x00003fff000000},
	Mask{15, 64, 41, 0x00003fff800000},
	Mask{16, 64, 42, 0x00003fffc00000},
	Mask{17, 64, 43, 0x00003fffe00000},
	Mask{18, 64, 44, 0x00003ffff00000},
	Mask{19, 64, 45, 0x00003ffff80000},
	Mask{20, 64, 46, 0x00003ffffc0000},
	Mask{21, 64, 47, 0x00003ffffe0000},
	Mask{22, 64, 48, 0x00003fffff0000},
	Mask{23, 64, 49, 0x00003fffff8000},
	Mask{24, 64, 50, 0x00003fffffc000},
	Mask{25, 64, 51, 0x00003fffffe000},
	Mask{26, 64, 52, 0x00003ffffff000},
	Mask{27, 64, 53, 0x00003ffffff800},
	Mask{28, 64, 54, 0x00003ffffffc00},
	Mask{29, 64, 55, 0x00003ffffffe00},
	Mask{30, 64, 56, 0x00003fffffff00},
	Mask{31, 64, 57, 0x00003fffffff80},
	Mask{32, 64, 58, 0x00003fffffffc0},
	Mask{33, 64, 59, 0x00003fffffffe0},
	Mask{34, 64, 60, 0x00003ffffffff0},
	Mask{35, 64, 61, 0x00003ffffffff8},
	Mask{36, 64, 62, 0x00003ffffffffc},
	Mask{37, 64, 63, 0x00003ffffffffe},
	Mask{38, 64, 0, 0x00003fffffffff},
	Mask{1, 64, 26, 0x00004000000000},
	Mask{1, 32, 26, 0x00004000000040},
	Mask{2, 64, 27, 0x00006000000000},
	Mask{2, 32, 27, 0x00006000000060},
	Mask{3, 64, 28, 0x00007000000000},
	Mask{3, 32, 28, 0x00007000000070},
	Mask{4, 64, 29, 0x00007800000000},
	Mask{4, 32, 29, 0x00007800000078},
	Mask{5, 64, 30, 0x00007c00000000},
	Mask{5, 32, 30, 0x00007c0000007c},
	Mask{6, 64, 31, 0x00007e00000000},
	Mask{6, 32, 31, 0x00007e0000007e},
	Mask{7, 64, 32, 0x00007f00000000},
	Mask{7, 32, 0, 0x00007f0000007f},
	Mask{8, 64, 33, 0x00007f80000000},
	Mask{9, 64, 34, 0x00007fc0000000},
	Mask{10, 64, 35, 0x00007fe0000000},
	Mask{11, 64, 36, 0x00007ff0000000},
	Mask{12, 64, 37, 0x00007ff8000000},
	Mask{13, 64, 38, 0x00007ffc000000},
	Mask{14, 64, 39, 0x00007ffe000000},
	Mask{15, 64, 40, 0x00007fff000000},
	Mask{16, 64, 41, 0x00007fff800000},
	Mask{17, 64, 42, 0x00007fffc00000},
	Mask{18, 64, 43, 0x00007fffe00000},
	Mask{19, 64, 44, 0x00007ffff00000},
	Mask{20, 64, 45, 0x00007ffff80000},
	Mask{21, 64, 46, 0x00007ffffc0000},
	Mask{22, 64, 47, 0x00007ffffe0000},
	Mask{23, 64, 48, 0x00007fffff0000},
	Mask{24, 64, 49, 0x00007fffff8000},
	Mask{25, 64, 50, 0x00007fffffc000},
	Mask{26, 64, 51, 0x00007fffffe000},
	Mask{27, 64, 52, 0x00007ffffff000},
	Mask{28, 64, 53, 0x00007ffffff800},
	Mask{29, 64, 54, 0x00007ffffffc00},
	Mask{30, 64, 55, 0x00007ffffffe00},
	Mask{31, 64, 56, 0x00007fffffff00},
	Mask{32, 64, 57, 0x00007fffffff80},
	Mask{33, 64, 58, 0x00007fffffffc0},
	Mask{34, 64, 59, 0x00007fffffffe0},
	Mask{35, 64, 60, 0x00007ffffffff0},
	Mask{36, 64, 61, 0x00007ffffffff8},
	Mask{37, 64, 62, 0x00007ffffffffc},
	Mask{38, 64, 63, 0x00007ffffffffe},
	Mask{39, 64, 0, 0x00007fffffffff},
	Mask{1, 64, 25, 0x00008000000000},
	Mask{1, 32, 25, 0x00008000000080},
	Mask{2, 64, 26, 0x0000c000000000},
	Mask{2, 32, 26, 0x0000c0000000c0},
	Mask{3, 64, 27, 0x0000e000000000},
	Mask{3, 32, 27, 0x0000e0000000e0},
	Mask{4, 64, 28, 0x0000f000000000},
	Mask{4, 32, 28, 0x0000f0000000f0},
	Mask{5, 64, 29, 0x0000f800000000},
	Mask{5, 32, 29, 0x0000f8000000f8},
	Mask{6, 64, 30, 0x0000fc00000000},
	Mask{6, 32, 30, 0x0000fc000000fc},
	Mask{7, 64, 31, 0x0000fe00000000},
	Mask{7, 32, 31, 0x0000fe000000fe},
	Mask{8, 64, 32, 0x0000ff00000000},
	Mask{8, 32, 0, 0x0000ff000000ff},
	Mask{9, 64, 33, 0x0000ff80000000},
	Mask{10, 64, 34, 0x0000ffc0000000},
	Mask{11, 64, 35, 0x0000ffe0000000},
	Mask{12, 64, 36, 0x0000fff0000000},
	Mask{13, 64, 37, 0x0000fff8000000},
	Mask{14, 64, 38, 0x0000fffc000000},
	Mask{15, 64, 39, 0x0000fffe000000},
	Mask{16, 64, 40, 0x0000ffff000000},
	Mask{17, 64, 41, 0x0000ffff800000},
	Mask{18, 64, 42, 0x0000ffffc00000},
	Mask{19, 64, 43, 0x0000ffffe00000},
	Mask{20, 64, 44, 0x0000fffff00000},
	Mask{21, 64, 45, 0x0000fffff80000},
	Mask{22, 64, 46, 0x0000fffffc0000},
	Mask{23, 64, 47, 0x0000fffffe0000},
	Mask{24, 64, 48, 0x0000ffffff0000},
	Mask{25, 64, 49, 0x0000ffffff8000},
	Mask{26, 64, 50, 0x0000ffffffc000},
	Mask{27, 64, 51, 0x0000ffffffe000},
	Mask{28, 64, 52, 0x0000fffffff000},
	Mask{29, 64, 53, 0x0000fffffff800},
	Mask{30, 64, 54, 0x0000fffffffc00},
	Mask{31, 64, 55, 0x0000fffffffe00},
	Mask{32, 64, 56, 0x0000ffffffff00},
	Mask{33, 64, 57, 0x0000ffffffff80},
	Mask{34, 64, 58, 0x0000ffffffffc0},
	Mask{35, 64, 59, 0x0000ffffffffe0},
	Mask{36, 64, 60, 0x0000fffffffff0},
	Mask{37, 64, 61, 0x0000fffffffff8},
	Mask{38, 64, 62, 0x0000fffffffffc},
	Mask{39, 64, 63, 0x0000fffffffffe},
	Mask{40, 64, 0, 0x0000ffffffffff},
	Mask{1, 64, 24, 0x00010000000000},
	Mask{1, 32, 24, 0x00010000000100},
	Mask{2, 64, 25, 0x00018000000000},
	Mask{2, 32, 25, 0x00018000000180},
	Mask{3, 64, 26, 0x0001c000000000},
	Mask{3, 32, 26, 0x0001c0000001c0},
	Mask{4, 64, 27, 0x0001e000000000},
	Mask{4, 32, 27, 0x0001e0000001e0},
	Mask{5, 64, 28, 0x0001f000000000},
	Mask{5, 32, 28, 0x0001f0000001f0},
	Mask{6, 64, 29, 0x0001f800000000},
	Mask{6, 32, 29, 0x0001f8000001f8},
	Mask{7, 64, 30, 0x0001fc00000000},
	Mask{7, 32, 30, 0x0001fc000001fc},
	Mask{8, 64, 31, 0x0001fe00000000},
	Mask{8, 32, 31, 0x0001fe000001fe},
	Mask{9, 64, 32, 0x0001ff00000000},
	Mask{9, 32, 0, 0x0001ff000001ff},
	Mask{10, 64, 33, 0x0001ff80000000},
	Mask{11, 64, 34, 0x0001ffc0000000},
	Mask{12, 64, 35, 0x0001ffe0000000},
	Mask{13, 64, 36, 0x0001fff0000000},
	Mask{14, 64, 37, 0x0001fff8000000},
	Mask{15, 64, 38, 0x0001fffc000000},
	Mask{16, 64, 39, 0x0001fffe000000},
	Mask{17, 64, 40, 0x0001ffff000000},
	Mask{18, 64, 41, 0x0001ffff800000},
	Mask{19, 64, 42, 0x0001ffffc00000},
	Mask{20, 64, 43, 0x0001ffffe00000},
	Mask{21, 64, 44, 0x0001fffff00000},
	Mask{22, 64, 45, 0x0001fffff80000},
	Mask{23, 64, 46, 0x0001fffffc0000},
	Mask{24, 64, 47, 0x0001fffffe0000},
	Mask{25, 64, 48, 0x0001ffffff0000},
	Mask{26, 64, 49, 0x0001ffffff8000},
	Mask{27, 64, 50, 0x0001ffffffc000},
	Mask{28, 64, 51, 0x0001ffffffe000},
	Mask{29, 64, 52, 0x0001fffffff000},
	Mask{30, 64, 53, 0x0001fffffff800},
	Mask{31, 64, 54, 0x0001fffffffc00},
	Mask{32, 64, 55, 0x0001fffffffe00},
	Mask{33, 64, 56, 0x0001ffffffff00},
	Mask{34, 64, 57, 0x0001ffffffff80},
	Mask{35, 64, 58, 0x0001ffffffffc0},
	Mask{36, 64, 59, 0x0001ffffffffe0},
	Mask{37, 64, 60, 0x0001fffffffff0},
	Mask{38, 64, 61, 0x0001fffffffff8},
	Mask{39, 64, 62, 0x0001fffffffffc},
	Mask{40, 64, 63, 0x0001fffffffffe},
	Mask{41, 64, 0, 0x0001ffffffffff},
	Mask{1, 64, 23, 0x00020000000000},
	Mask{1, 32, 23, 0x00020000000200},
	Mask{2, 64, 24, 0x00030000000000},
	Mask{2, 32, 24, 0x00030000000300},
	Mask{3, 64, 25, 0x00038000000000},
	Mask{3, 32, 25, 0x00038000000380},
	Mask{4, 64, 26, 0x0003c000000000},
	Mask{4, 32, 26, 0x0003c0000003c0},
	Mask{5, 64, 27, 0x0003e000000000},
	Mask{5, 32, 27, 0x0003e0000003e0},
	Mask{6, 64, 28, 0x0003f000000000},
	Mask{6, 32, 28, 0x0003f0000003f0},
	Mask{7, 64, 29, 0x0003f800000000},
	Mask{7, 32, 29, 0x0003f8000003f8},
	Mask{8, 64, 30, 0x0003fc00000000},
	Mask{8, 32, 30, 0x0003fc000003fc},
	Mask{9, 64, 31, 0x0003fe00000000},
	Mask{9, 32, 31, 0x0003fe000003fe},
	Mask{10, 64, 32, 0x0003ff00000000},
	Mask{10, 32, 0, 0x0003ff000003ff},
	Mask{11, 64, 33, 0x0003ff80000000},
	Mask{12, 64, 34, 0x0003ffc0000000},
	Mask{13, 64, 35, 0x0003ffe0000000},
	Mask{14, 64, 36, 0x0003fff0000000},
	Mask{15, 64, 37, 0x0003fff8000000},
	Mask{16, 64, 38, 0x0003fffc000000},
	Mask{17, 64, 39, 0x0003fffe000000},
	Mask{18, 64, 40, 0x0003ffff000000},
	Mask{19, 64, 41, 0x0003ffff800000},
	Mask{20, 64, 42, 0x0003ffffc00000},
	Mask{21, 64, 43, 0x0003ffffe00000},
	Mask{22, 64, 44, 0x0003fffff00000},
	Mask{23, 64, 45, 0x0003fffff80000},
	Mask{24, 64, 46, 0x0003fffffc0000},
	Mask{25, 64, 47, 0x0003fffffe0000},
	Mask{26, 64, 48, 0x0003ffffff0000},
	Mask{27, 64, 49, 0x0003ffffff8000},
	Mask{28, 64, 50, 0x0003ffffffc000},
	Mask{29, 64, 51, 0x0003ffffffe000},
	Mask{30, 64, 52, 0x0003fffffff000},
	Mask{31, 64, 53, 0x0003fffffff800},
	Mask{32, 64, 54, 0x0003fffffffc00},
	Mask{33, 64, 55, 0x0003fffffffe00},
	Mask{34, 64, 56, 0x0003ffffffff00},
	Mask{35, 64, 57, 0x0003ffffffff80},
	Mask{36, 64, 58, 0x0003ffffffffc0},
	Mask{37, 64, 59, 0x0003ffffffffe0},
	Mask{38, 64, 60, 0x0003fffffffff0},
	Mask{39, 64, 61, 0x0003fffffffff8},
	Mask{40, 64, 62, 0x0003fffffffffc},
	Mask{41, 64, 63, 0x0003fffffffffe},
	Mask{42, 64, 0, 0x0003ffffffffff},
	Mask{1, 64, 22, 0x00040000000000},
	Mask{1, 32, 22, 0x00040000000400},
	Mask{2, 64, 23, 0x00060000000000},
	Mask{2, 32, 23, 0x00060000000600},
	Mask{3, 64, 24, 0x00070000000000},
	Mask{3, 32, 24, 0x00070000000700},
	Mask{4, 64, 25, 0x00078000000000},
	Mask{4, 32, 25, 0x00078000000780},
	Mask{5, 64, 26, 0x0007c000000000},
	Mask{5, 32, 26, 0x0007c0000007c0},
	Mask{6, 64, 27, 0x0007e000000000},
	Mask{6, 32, 27, 0x0007e0000007e0},
	Mask{7, 64, 28, 0x0007f000000000},
	Mask{7, 32, 28, 0x0007f0000007f0},
	Mask{8, 64, 29, 0x0007f800000000},
	Mask{8, 32, 29, 0x0007f8000007f8},
	Mask{9, 64, 30, 0x0007fc00000000},
	Mask{9, 32, 30, 0x0007fc000007fc},
	Mask{10, 64, 31, 0x0007fe00000000},
	Mask{10, 32, 31, 0x0007fe000007fe},
	Mask{11, 64, 32, 0x0007ff00000000},
	Mask{11, 32, 0, 0x0007ff000007ff},
	Mask{12, 64, 33, 0x0007ff80000000},
	Mask{13, 64, 34, 0x0007ffc0000000},
	Mask{14, 64, 35, 0x0007ffe0000000},
	Mask{15, 64, 36, 0x0007fff0000000},
	Mask{16, 64, 37, 0x0007fff8000000},
	Mask{17, 64, 38, 0x0007fffc000000},
	Mask{18, 64, 39, 0x0007fffe000000},
	Mask{19, 64, 40, 0x0007ffff000000},
	Mask{20, 64, 41, 0x0007ffff800000},
	Mask{21, 64, 42, 0x0007ffffc00000},
	Mask{22, 64, 43, 0x0007ffffe00000},
	Mask{23, 64, 44, 0x0007fffff00000},
	Mask{24, 64, 45, 0x0007fffff80000},
	Mask{25, 64, 46, 0x0007fffffc0000},
	Mask{26, 64, 47, 0x0007fffffe0000},
	Mask{27, 64, 48, 0x0007ffffff0000},
	Mask{28, 64, 49, 0x0007ffffff8000},
	Mask{29, 64, 50, 0x0007ffffffc000},
	Mask{30, 64, 51, 0x0007ffffffe000},
	Mask{31, 64, 52, 0x0007fffffff000},
	Mask{32, 64, 53, 0x0007fffffff800},
	Mask{33, 64, 54, 0x0007fffffffc00},
	Mask{34, 64, 55, 0x0007fffffffe00},
	Mask{35, 64, 56, 0x0007ffffffff00},
	Mask{36, 64, 57, 0x0007ffffffff80},
	Mask{37, 64, 58, 0x0007ffffffffc0},
	Mask{38, 64, 59, 0x0007ffffffffe0},
	Mask{39, 64, 60, 0x0007fffffffff0},
	Mask{40, 64, 61, 0x0007fffffffff8},
	Mask{41, 64, 62, 0x0007fffffffffc},
	Mask{42, 64, 63, 0x0007fffffffffe},
	Mask{43, 64, 0, 0x0007ffffffffff},
	Mask{1, 64, 21, 0x00080000000000},
	Mask{1, 32, 21, 0x00080000000800},
	Mask{2, 64, 22, 0x000c0000000000},
	Mask{2, 32, 22, 0x000c0000000c00},
	Mask{3, 64, 23, 0x000e0000000000},
	Mask{3, 32, 23, 0x000e0000000e00},
	Mask{4, 64, 24, 0x000f0000000000},
	Mask{4, 32, 24, 0x000f0000000f00},
	Mask{5, 64, 25, 0x000f8000000000},
	Mask{5, 32, 25, 0x000f8000000f80},
	Mask{6, 64, 26, 0x000fc000000000},
	Mask{6, 32, 26, 0x000fc000000fc0},
	Mask{7, 64, 27, 0x000fe000000000},
	Mask{7, 32, 27, 0x000fe000000fe0},
	Mask{8, 64, 28, 0x000ff000000000},
	Mask{8, 32, 28, 0x000ff000000ff0},
	Mask{9, 64, 29, 0x000ff800000000},
	Mask{9, 32, 29, 0x000ff800000ff8},
	Mask{10, 64, 30, 0x000ffc00000000},
	Mask{10, 32, 30, 0x000ffc00000ffc},
	Mask{11, 64, 31, 0x000ffe00000000},
	Mask{11, 32, 31, 0x000ffe00000ffe},
	Mask{12, 64, 32, 0x000fff00000000},
	Mask{12, 32, 0, 0x000fff00000fff},
	Mask{13, 64, 33, 0x000fff80000000},
	Mask{14, 64, 34, 0x000fffc0000000},
	Mask{15, 64, 35, 0x000fffe0000000},
	Mask{16, 64, 36, 0x000ffff0000000},
	Mask{17, 64, 37, 0x000ffff8000000},
	Mask{18, 64, 38, 0x000ffffc000000},
	Mask{19, 64, 39, 0x000ffffe000000},
	Mask{20, 64, 40, 0x000fffff000000},
	Mask{21, 64, 41, 0x000fffff800000},
	Mask{22, 64, 42, 0x000fffffc00000},
	Mask{23, 64, 43, 0x000fffffe00000},
	Mask{24, 64, 44, 0x000ffffff00000},
	Mask{25, 64, 45, 0x000ffffff80000},
	Mask{26, 64, 46, 0x000ffffffc0000},
	Mask{27, 64, 47, 0x000ffffffe0000},
	Mask{28, 64, 48, 0x000fffffff0000},
	Mask{29, 64, 49, 0x000fffffff8000},
	Mask{30, 64, 50, 0x000fffffffc000},
	Mask{31, 64, 51, 0x000fffffffe000},
	Mask{32, 64, 52, 0x000ffffffff000},
	Mask{33, 64, 53, 0x000ffffffff800},
	Mask{34, 64, 54, 0x000ffffffffc00},
	Mask{35, 64, 55, 0x000ffffffffe00},
	Mask{36, 64, 56, 0x000fffffffff00},
	Mask{37, 64, 57, 0x000fffffffff80},
	Mask{38, 64, 58, 0x000fffffffffc0},
	Mask{39, 64, 59, 0x000fffffffffe0},
	Mask{40, 64, 60, 0x000ffffffffff0},
	Mask{41, 64, 61, 0x000ffffffffff8},
	Mask{42, 64, 62, 0x000ffffffffffc},
	Mask{43, 64, 63, 0x000ffffffffffe},
	Mask{44, 64, 0, 0x000fffffffffff},
	Mask{1, 64, 20, 0x00100000000000},
	Mask{1, 32, 20, 0x00100000001000},
	Mask{2, 64, 21, 0x00180000000000},
	Mask{2, 32, 21, 0x00180000001800},
	Mask{3, 64, 22, 0x001c0000000000},
	Mask{3, 32, 22, 0x001c0000001c00},
	Mask{4, 64, 23, 0x001e0000000000},
	Mask{4, 32, 23, 0x001e0000001e00},
	Mask{5, 64, 24, 0x001f0000000000},
	Mask{5, 32, 24, 0x001f0000001f00},
	Mask{6, 64, 25, 0x001f8000000000},
	Mask{6, 32, 25, 0x001f8000001f80},
	Mask{7, 64, 26, 0x001fc000000000},
	Mask{7, 32, 26, 0x001fc000001fc0},
	Mask{8, 64, 27, 0x001fe000000000},
	Mask{8, 32, 27, 0x001fe000001fe0},
	Mask{9, 64, 28, 0x001ff000000000},
	Mask{9, 32, 28, 0x001ff000001ff0},
	Mask{10, 64, 29, 0x001ff800000000},
	Mask{10, 32, 29, 0x001ff800001ff8},
	Mask{11, 64, 30, 0x001ffc00000000},
	Mask{11, 32, 30, 0x001ffc00001ffc},
	Mask{12, 64, 31, 0x001ffe00000000},
	Mask{12, 32, 31, 0x001ffe00001ffe},
	Mask{13, 64, 32, 0x001fff00000000},
	Mask{13, 32, 0, 0x001fff00001fff},
	Mask{14, 64, 33, 0x001fff80000000},
	Mask{15, 64, 34, 0x001fffc0000000},
	Mask{16, 64, 35, 0x001fffe0000000},
	Mask{17, 64, 36, 0x001ffff0000000},
	Mask{18, 64, 37, 0x001ffff8000000},
	Mask{19, 64, 38, 0x001ffffc000000},
	Mask{20, 64, 39, 0x001ffffe000000},
	Mask{21, 64, 40, 0x001fffff000000},
	Mask{22, 64, 41, 0x001fffff800000},
	Mask{23, 64, 42, 0x001fffffc00000},
	Mask{24, 64, 43, 0x001fffffe00000},
	Mask{25, 64, 44, 0x001ffffff00000},
	Mask{26, 64, 45, 0x001ffffff80000},
	Mask{27, 64, 46, 0x001ffffffc0000},
	Mask{28, 64, 47, 0x001ffffffe0000},
	Mask{29, 64, 48, 0x001fffffff0000},
	Mask{30, 64, 49, 0x001fffffff8000},
	Mask{31, 64, 50, 0x001fffffffc000},
	Mask{32, 64, 51, 0x001fffffffe000},
	Mask{33, 64, 52, 0x001ffffffff000},
	Mask{34, 64, 53, 0x001ffffffff800},
	Mask{35, 64, 54, 0x001ffffffffc00},
	Mask{36, 64, 55, 0x001ffffffffe00},
	Mask{37, 64, 56, 0x001fffffffff00},
	Mask{38, 64, 57, 0x001fffffffff80},
	Mask{39, 64, 58, 0x001fffffffffc0},
	Mask{40, 64, 59, 0x001fffffffffe0},
	Mask{41, 64, 60, 0x001ffffffffff0},
	Mask{42, 64, 61, 0x001ffffffffff8},
	Mask{43, 64, 62, 0x001ffffffffffc},
	Mask{44, 64, 63, 0x001ffffffffffe},
	Mask{45, 64, 0, 0x001fffffffffff},
	Mask{1, 64, 19, 0x00200000000000},
	Mask{1, 32, 19, 0x00200000002000},
	Mask{2, 64, 20, 0x00300000000000},
	Mask{2, 32, 20, 0x00300000003000},
	Mask{3, 64, 21, 0x00380000000000},
	Mask{3, 32, 21, 0x00380000003800},
	Mask{4, 64, 22, 0x003c0000000000},
	Mask{4, 32, 22, 0x003c0000003c00},
	Mask{5, 64, 23, 0x003e0000000000},
	Mask{5, 32, 23, 0x003e0000003e00},
	Mask{6, 64, 24, 0x003f0000000000},
	Mask{6, 32, 24, 0x003f0000003f00},
	Mask{7, 64, 25, 0x003f8000000000},
	Mask{7, 32, 25, 0x003f8000003f80},
	Mask{8, 64, 26, 0x003fc000000000},
	Mask{8, 32, 26, 0x003fc000003fc0},
	Mask{9, 64, 27, 0x003fe000000000},
	Mask{9, 32, 27, 0x003fe000003fe0},
	Mask{10, 64, 28, 0x003ff000000000},
	Mask{10, 32, 28, 0x003ff000003ff0},
	Mask{11, 64, 29, 0x003ff800000000},
	Mask{11, 32, 29, 0x003ff800003ff8},
	Mask{12, 64, 30, 0x003ffc00000000},
	Mask{12, 32, 30, 0x003ffc00003ffc},
	Mask{13, 64, 31, 0x003ffe00000000},
	Mask{13, 32, 31, 0x003ffe00003ffe},
	Mask{14, 64, 32, 0x003fff00000000},
	Mask{14, 32, 0, 0x003fff00003fff},
	Mask{15, 64, 33, 0x003fff80000000},
	Mask{16, 64, 34, 0x003fffc0000000},
	Mask{17, 64, 35, 0x003fffe0000000},
	Mask{18, 64, 36, 0x003ffff0000000},
	Mask{19, 64, 37, 0x003ffff8000000},
	Mask{20, 64, 38, 0x003ffffc000000},
	Mask{21, 64, 39, 0x003ffffe000000},
	Mask{22, 64, 40, 0x003fffff000000},
	Mask{23, 64, 41, 0x003fffff800000},
	Mask{24, 64, 42, 0x003fffffc00000},
	Mask{25, 64, 43, 0x003fffffe00000},
	Mask{26, 64, 44, 0x003ffffff00000},
	Mask{27, 64, 45, 0x003ffffff80000},
	Mask{28, 64, 46, 0x003ffffffc0000},
	Mask{29, 64, 47, 0x003ffffffe0000},
	Mask{30, 64, 48, 0x003fffffff0000},
	Mask{31, 64, 49, 0x003fffffff8000},
	Mask{32, 64, 50, 0x003fffffffc000},
	Mask{33, 64, 51, 0x003fffffffe000},
	Mask{34, 64, 52, 0x003ffffffff000},
	Mask{35, 64, 53, 0x003ffffffff800},
	Mask{36, 64, 54, 0x003ffffffffc00},
	Mask{37, 64, 55, 0x003ffffffffe00},
	Mask{38, 64, 56, 0x003fffffffff00},
	Mask{39, 64, 57, 0x003fffffffff80},
	Mask{40, 64, 58, 0x003fffffffffc0},
	Mask{41, 64, 59, 0x003fffffffffe0},
	Mask{42, 64, 60, 0x003ffffffffff0},
	Mask{43, 64, 61, 0x003ffffffffff8},
	Mask{44, 64, 62, 0x003ffffffffffc},
	Mask{45, 64, 63, 0x003ffffffffffe},
	Mask{46, 64, 0, 0x003fffffffffff},
	Mask{1, 64, 18, 0x00400000000000},
	Mask{1, 32, 18, 0x00400000004000},
	Mask{2, 64, 19, 0x00600000000000},
	Mask{2, 32, 19, 0x00600000006000},
	Mask{3, 64, 20, 0x00700000000000},
	Mask{3, 32, 20, 0x00700000007000},
	Mask{4, 64, 21, 0x00780000000000},
	Mask{4, 32, 21, 0x00780000007800},
	Mask{5, 64, 22, 0x007c0000000000},
	Mask{5, 32, 22, 0x007c0000007c00},
	Mask{6, 64, 23, 0x007e0000000000},
	Mask{6, 32, 23, 0x007e0000007e00},
	Mask{7, 64, 24, 0x007f0000000000},
	Mask{7, 32, 24, 0x007f0000007f00},
	Mask{8, 64, 25, 0x007f8000000000},
	Mask{8, 32, 25, 0x007f8000007f80},
	Mask{9, 64, 26, 0x007fc000000000},
	Mask{9, 32, 26, 0x007fc000007fc0},
	Mask{10, 64, 27, 0x007fe000000000},
	Mask{10, 32, 27, 0x007fe000007fe0},
	Mask{11, 64, 28, 0x007ff000000000},
	Mask{11, 32, 28, 0x007ff000007ff0},
	Mask{12, 64, 29, 0x007ff800000000},
	Mask{12, 32, 29, 0x007ff800007ff8},
	Mask{13, 64, 30, 0x007ffc00000000},
	Mask{13, 32, 30, 0x007ffc00007ffc},
	Mask{14, 64, 31, 0x007ffe00000000},
	Mask{14, 32, 31, 0x007ffe00007ffe},
	Mask{15, 64, 32, 0x007fff00000000},
	Mask{15, 32, 0, 0x007fff00007fff},
	Mask{16, 64, 33, 0x007fff80000000},
	Mask{17, 64, 34, 0x007fffc0000000},
	Mask{18, 64, 35, 0x007fffe0000000},
	Mask{19, 64, 36, 0x007ffff0000000},
	Mask{20, 64, 37, 0x007ffff8000000},
	Mask{21, 64, 38, 0x007ffffc000000},
	Mask{22, 64, 39, 0x007ffffe000000},
	Mask{23, 64, 40, 0x007fffff000000},
	Mask{24, 64, 41, 0x007fffff800000},
	Mask{25, 64, 42, 0x007fffffc00000},
	Mask{26, 64, 43, 0x007fffffe00000},
	Mask{27, 64, 44, 0x007ffffff00000},
	Mask{28, 64, 45, 0x007ffffff80000},
	Mask{29, 64, 46, 0x007ffffffc0000},
	Mask{30, 64, 47, 0x007ffffffe0000},
	Mask{31, 64, 48, 0x007fffffff0000},
	Mask{32, 64, 49, 0x007fffffff8000},
	Mask{33, 64, 50, 0x007fffffffc000},
	Mask{34, 64, 51, 0x007fffffffe000},
	Mask{35, 64, 52, 0x007ffffffff000},
	Mask{36, 64, 53, 0x007ffffffff800},
	Mask{37, 64, 54, 0x007ffffffffc00},
	Mask{38, 64, 55, 0x007ffffffffe00},
	Mask{39, 64, 56, 0x007fffffffff00},
	Mask{40, 64, 57, 0x007fffffffff80},
	Mask{41, 64, 58, 0x007fffffffffc0},
	Mask{42, 64, 59, 0x007fffffffffe0},
	Mask{43, 64, 60, 0x007ffffffffff0},
	Mask{44, 64, 61, 0x007ffffffffff8},
	Mask{45, 64, 62, 0x007ffffffffffc},
	Mask{46, 64, 63, 0x007ffffffffffe},
	Mask{47, 64, 0, 0x007fffffffffff},
	Mask{1, 64, 17, 0x00800000000000},
	Mask{1, 32, 17, 0x00800000008000},
	Mask{2, 64, 18, 0x00c00000000000},
	Mask{2, 32, 18, 0x00c0000000c000},
	Mask{3, 64, 19, 0x00e00000000000},
	Mask{3, 32, 19, 0x00e0000000e000},
	Mask{4, 64, 20, 0x00f00000000000},
	Mask{4, 32, 20, 0x00f0000000f000},
	Mask{5, 64, 21, 0x00f80000000000},
	Mask{5, 32, 21, 0x00f8000000f800},
	Mask{6, 64, 22, 0x00fc0000000000},
	Mask{6, 32, 22, 0x00fc000000fc00},
	Mask{7, 64, 23, 0x00fe0000000000},
	Mask{7, 32, 23, 0x00fe000000fe00},
	Mask{8, 64, 24, 0x00ff0000000000},
	Mask{8, 32, 24, 0x00ff000000ff00},
	Mask{9, 64, 25, 0x00ff8000000000},
	Mask{9, 32, 25, 0x00ff800000ff80},
	Mask{10, 64, 26, 0x00ffc000000000},
	Mask{10, 32, 26, 0x00ffc00000ffc0},
	Mask{11, 64, 27, 0x00ffe000000000},
	Mask{11, 32, 27, 0x00ffe00000ffe0},
	Mask{12, 64, 28, 0x00fff000000000},
	Mask{12, 32, 28, 0x00fff00000fff0},
	Mask{13, 64, 29, 0x00fff800000000},
	Mask{13, 32, 29, 0x00fff80000fff8},
	Mask{14, 64, 30, 0x00fffc00000000},
	Mask{14, 32, 30, 0x00fffc0000fffc},
	Mask{15, 64, 31, 0x00fffe00000000},
	Mask{15, 32, 31, 0x00fffe0000fffe},
	Mask{16, 64, 32, 0x00ffff00000000},
	Mask{16, 32, 0, 0x00ffff0000ffff},
	Mask{17, 64, 33, 0x00ffff80000000},
	Mask{18, 64, 34, 0x00ffffc0000000},
	Mask{19, 64, 35, 0x00ffffe0000000},
	Mask{20, 64, 36, 0x00fffff0000000},
	Mask{21, 64, 37, 0x00fffff8000000},
	Mask{22, 64, 38, 0x00fffffc000000},
	Mask{23, 64, 39, 0x00fffffe000000},
	Mask{24, 64, 40, 0x00ffffff000000},
	Mask{25, 64, 41, 0x00ffffff800000},
	Mask{26, 64, 42, 0x00ffffffc00000},
	Mask{27, 64, 43, 0x00ffffffe00000},
	Mask{28, 64, 44, 0x00fffffff00000},
	Mask{29, 64, 45, 0x00fffffff80000},
	Mask{30, 64, 46, 0x00fffffffc0000},
	Mask{31, 64, 47, 0x00fffffffe0000},
	Mask{32, 64, 48, 0x00ffffffff0000},
	Mask{33, 64, 49, 0x00ffffffff8000},
	Mask{34, 64, 50, 0x00ffffffffc000},
	Mask{35, 64, 51, 0x00ffffffffe000},
	Mask{36, 64, 52, 0x00fffffffff000},
	Mask{37, 64, 53, 0x00fffffffff800},
	Mask{38, 64, 54, 0x00fffffffffc00},
	Mask{39, 64, 55, 0x00fffffffffe00},
	Mask{40, 64, 56, 0x00ffffffffff00},
	Mask{41, 64, 57, 0x00ffffffffff80},
	Mask{42, 64, 58, 0x00ffffffffffc0},
	Mask{43, 64, 59, 0x00ffffffffffe0},
	Mask{44, 64, 60, 0x00fffffffffff0},
	Mask{45, 64, 61, 0x00fffffffffff8},
	Mask{46, 64, 62, 0x00fffffffffffc},
	Mask{47, 64, 63, 0x00fffffffffffe},
	Mask{48, 64, 0, 0x00ffffffffffff},
	Mask{1, 64, 16, 0x01000000000000},
	Mask{1, 32, 16, 0x01000000010000},
	Mask{1, 16, 0, 0x01000100010001},
	Mask{2, 64, 17, 0x01800000000000},
	Mask{2, 32, 17, 0x01800000018000},
	Mask{3, 64, 18, 0x01c00000000000},
	Mask{3, 32, 18, 0x01c0000001c000},
	Mask{4, 64, 19, 0x01e00000000000},
	Mask{4, 32, 19, 0x01e0000001e000},
	Mask{5, 64, 20, 0x01f00000000000},
	Mask{5, 32, 20, 0x01f0000001f000},
	Mask{6, 64, 21, 0x01f80000000000},
	Mask{6, 32, 21, 0x01f8000001f800},
	Mask{7, 64, 22, 0x01fc0000000000},
	Mask{7, 32, 22, 0x01fc000001fc00},
	Mask{8, 64, 23, 0x01fe0000000000},
	Mask{8, 32, 23, 0x01fe000001fe00},
	Mask{9, 64, 24, 0x01ff0000000000},
	Mask{9, 32, 24, 0x01ff000001ff00},
	Mask{10, 64, 25, 0x01ff8000000000},
	Mask{10, 32, 25, 0x01ff800001ff80},
	Mask{11, 64, 26, 0x01ffc000000000},
	Mask{11, 32, 26, 0x01ffc00001ffc0},
	Mask{12, 64, 27, 0x01ffe000000000},
	Mask{12, 32, 27, 0x01ffe00001ffe0},
	Mask{13, 64, 28, 0x01fff000000000},
	Mask{13, 32, 28, 0x01fff00001fff0},
	Mask{14, 64, 29, 0x01fff800000000},
	Mask{14, 32, 29, 0x01fff80001fff8},
	Mask{15, 64, 30, 0x01fffc00000000},
	Mask{15, 32, 30, 0x01fffc0001fffc},
	Mask{16, 64, 31, 0x01fffe00000000},
	Mask{16, 32, 31, 0x01fffe0001fffe},
	Mask{17, 64, 32, 0x01ffff00000000},
	Mask{17, 32, 0, 0x01ffff0001ffff},
	Mask{18, 64, 33, 0x01ffff80000000},
	Mask{19, 64, 34, 0x01ffffc0000000},
	Mask{20, 64, 35, 0x01ffffe0000000},
	Mask{21, 64, 36, 0x01fffff0000000},
	Mask{22, 64, 37, 0x01fffff8000000},
	Mask{23, 64, 38, 0x01fffffc000000},
	Mask{24, 64, 39, 0x01fffffe000000},
	Mask{25, 64, 40, 0x01ffffff000000},
	Mask{26, 64, 41, 0x01ffffff800000},
	Mask{27, 64, 42, 0x01ffffffc00000},
	Mask{28, 64, 43, 0x01ffffffe00000},
	Mask{29, 64, 44, 0x01fffffff00000},
	Mask{30, 64, 45, 0x01fffffff80000},
	Mask{31, 64, 46, 0x01fffffffc0000},
	Mask{32, 64, 47, 0x01fffffffe0000},
	Mask{33, 64, 48, 0x01ffffffff0000},
	Mask{34, 64, 49, 0x01ffffffff8000},
	Mask{35, 64, 50, 0x01ffffffffc000},
	Mask{36, 64, 51, 0x01ffffffffe000},
	Mask{37, 64, 52, 0x01fffffffff000},
	Mask{38, 64, 53, 0x01fffffffff800},
	Mask{39, 64, 54, 0x01fffffffffc00},
	Mask{40, 64, 55, 0x01fffffffffe00},
	Mask{41, 64, 56, 0x01ffffffffff00},
	Mask{42, 64, 57, 0x01ffffffffff80},
	Mask{43, 64, 58, 0x01ffffffffffc0},
	Mask{44, 64, 59, 0x01ffffffffffe0},
	Mask{45, 64, 60, 0x01fffffffffff0},
	Mask{46, 64, 61, 0x01fffffffffff8},
	Mask{47, 64, 62, 0x01fffffffffffc},
	Mask{48, 64, 63, 0x01fffffffffffe},
	Mask{49, 64, 0, 0x01ffffffffffff},
	Mask{1, 64, 15, 0x02000000000000},
	Mask{1, 32, 15, 0x02000000020000},
	Mask{1, 16, 15, 0x02000200020002},
	Mask{2, 64, 16, 0x03000000000000},
	Mask{2, 32, 16, 0x03000000030000},
	Mask{2, 16, 0, 0x03000300030003},
	Mask{3, 64, 17, 0x03800000000000},
	Mask{3, 32, 17, 0x03800000038000},
	Mask{4, 64, 18, 0x03c00000000000},
	Mask{4, 32, 18, 0x03c0000003c000},
	Mask{5, 64, 19, 0x03e00000000000},
	Mask{5, 32, 19, 0x03e0000003e000},
	Mask{6, 64, 20, 0x03f00000000000},
	Mask{6, 32, 20, 0x03f0000003f000},
	Mask{7, 64, 21, 0x03f80000000000},
	Mask{7, 32, 21, 0x03f8000003f800},
	Mask{8, 64, 22, 0x03fc0000000000},
	Mask{8, 32, 22, 0x03fc000003fc00},
	Mask{9, 64, 23, 0x03fe0000000000},
	Mask{9, 32, 23, 0x03fe000003fe00},
	Mask{10, 64, 24, 0x03ff0000000000},
	Mask{10, 32, 24, 0x03ff000003ff00},
	Mask{11, 64, 25, 0x03ff8000000000},
	Mask{11, 32, 25, 0x03ff800003ff80},
	Mask{12, 64, 26, 0x03ffc000000000},
	Mask{12, 32, 26, 0x03ffc00003ffc0},
	Mask{13, 64, 27, 0x03ffe000000000},
	Mask{13, 32, 27, 0x03ffe00003ffe0},
	Mask{14, 64, 28, 0x03fff000000000},
	Mask{14, 32, 28, 0x03fff00003fff0},
	Mask{15, 64, 29, 0x03fff800000000},
	Mask{15, 32, 29, 0x03fff80003fff8},
	Mask{16, 64, 30, 0x03fffc00000000},
	Mask{16, 32, 30, 0x03fffc0003fffc},
	Mask{17, 64, 31, 0x03fffe00000000},
	Mask{17, 32, 31, 0x03fffe0003fffe},
	Mask{18, 64, 32, 0x03ffff00000000},
	Mask{18, 32, 0, 0x03ffff0003ffff},
	Mask{19, 64, 33, 0x03ffff80000000},
	Mask{20, 64, 34, 0x03ffffc0000000},
	Mask{21, 64, 35, 0x03ffffe0000000},
	Mask{22, 64, 36, 0x03fffff0000000},
	Mask{23, 64, 37, 0x03fffff8000000},
	Mask{24, 64, 38, 0x03fffffc000000},
	Mask{25, 64, 39, 0x03fffffe000000},
	Mask{26, 64, 40, 0x03ffffff000000},
	Mask{27, 64, 41, 0x03ffffff800000},
	Mask{28, 64, 42, 0x03ffffffc00000},
	Mask{29, 64, 43, 0x03ffffffe00000},
	Mask{30, 64, 44, 0x03fffffff00000},
	Mask{31, 64, 45, 0x03fffffff80000},
	Mask{32, 64, 46, 0x03fffffffc0000},
	Mask{33, 64, 47, 0x03fffffffe0000},
	Mask{34, 64, 48, 0x03ffffffff0000},
	Mask{35, 64, 49, 0x03ffffffff8000},
	Mask{36, 64, 50, 0x03ffffffffc000},
	Mask{37, 64, 51, 0x03ffffffffe000},
	Mask{38, 64, 52, 0x03fffffffff000},
	Mask{39, 64, 53, 0x03fffffffff800},
	Mask{40, 64, 54, 0x03fffffffffc00},
	Mask{41, 64, 55, 0x03fffffffffe00},
	Mask{42, 64, 56, 0x03ffffffffff00},
	Mask{43, 64, 57, 0x03ffffffffff80},
	Mask{44, 64, 58, 0x03ffffffffffc0},
	Mask{45, 64, 59, 0x03ffffffffffe0},
	Mask{46, 64, 60, 0x03fffffffffff0},
	Mask{47, 64, 61, 0x03fffffffffff8},
	Mask{48, 64, 62, 0x03fffffffffffc},
	Mask{49, 64, 63, 0x03fffffffffffe},
	Mask{50, 64, 0, 0x03ffffffffffff},
	Mask{1, 64, 14, 0x04000000000000},
	Mask{1, 32, 14, 0x04000000040000},
	Mask{1, 16, 14, 0x04000400040004},
	Mask{2, 64, 15, 0x06000000000000},
	Mask{2, 32, 15, 0x06000000060000},
	Mask{2, 16, 15, 0x06000600060006},
	Mask{3, 64, 16, 0x07000000000000},
	Mask{3, 32, 16, 0x07000000070000},
	Mask{3, 16, 0, 0x07000700070007},
	Mask{4, 64, 17, 0x07800000000000},
	Mask{4, 32, 17, 0x07800000078000},
	Mask{5, 64, 18, 0x07c00000000000},
	Mask{5, 32, 18, 0x07c0000007c000},
	Mask{6, 64, 19, 0x07e00000000000},
	Mask{6, 32, 19, 0x07e0000007e000},
	Mask{7, 64, 20, 0x07f00000000000},
	Mask{7, 32, 20, 0x07f0000007f000},
	Mask{8, 64, 21, 0x07f80000000000},
	Mask{8, 32, 21, 0x07f8000007f800},
	Mask{9, 64, 22, 0x07fc0000000000},
	Mask{9, 32, 22, 0x07fc000007fc00},
	Mask{10, 64, 23, 0x07fe0000000000},
	Mask{10, 32, 23, 0x07fe000007fe00},
	Mask{11, 64, 24, 0x07ff0000000000},
	Mask{11, 32, 24, 0x07ff000007ff00},
	Mask{12, 64, 25, 0x07ff8000000000},
	Mask{12, 32, 25, 0x07ff800007ff80},
	Mask{13, 64, 26, 0x07ffc000000000},
	Mask{13, 32, 26, 0x07ffc00007ffc0},
	Mask{14, 64, 27, 0x07ffe000000000},
	Mask{14, 32, 27, 0x07ffe00007ffe0},
	Mask{15, 64, 28, 0x07fff000000000},
	Mask{15, 32, 28, 0x07fff00007fff0},
	Mask{16, 64, 29, 0x07fff800000000},
	Mask{16, 32, 29, 0x07fff80007fff8},
	Mask{17, 64, 30, 0x07fffc00000000},
	Mask{17, 32, 30, 0x07fffc0007fffc},
	Mask{18, 64, 31, 0x07fffe00000000},
	Mask{18, 32, 31, 0x07fffe0007fffe},
	Mask{19, 64, 32, 0x07ffff00000000},
	Mask{19, 32, 0, 0x07ffff0007ffff},
	Mask{20, 64, 33, 0x07ffff80000000},
	Mask{21, 64, 34, 0x07ffffc0000000},
	Mask{22, 64, 35, 0x07ffffe0000000},
	Mask{23, 64, 36, 0x07fffff0000000},
	Mask{24, 64, 37, 0x07fffff8000000},
	Mask{25, 64, 38, 0x07fffffc000000},
	Mask{26, 64, 39, 0x07fffffe000000},
	Mask{27, 64, 40, 0x07ffffff000000},
	Mask{28, 64, 41, 0x07ffffff800000},
	Mask{29, 64, 42, 0x07ffffffc00000},
	Mask{30, 64, 43, 0x07ffffffe00000},
	Mask{31, 64, 44, 0x07fffffff00000},
	Mask{32, 64, 45, 0x07fffffff80000},
	Mask{33, 64, 46, 0x07fffffffc0000},
	Mask{34, 64, 47, 0x07fffffffe0000},
	Mask{35, 64, 48, 0x07ffffffff0000},
	Mask{36, 64, 49, 0x07ffffffff8000},
	Mask{37, 64, 50, 0x07ffffffffc000},
	Mask{38, 64, 51, 0x07ffffffffe000},
	Mask{39, 64, 52, 0x07fffffffff000},
	Mask{40, 64, 53, 0x07fffffffff800},
	Mask{41, 64, 54, 0x07fffffffffc00},
	Mask{42, 64, 55, 0x07fffffffffe00},
	Mask{43, 64, 56, 0x07ffffffffff00},
	Mask{44, 64, 57, 0x07ffffffffff80},
	Mask{45, 64, 58, 0x07ffffffffffc0},
	Mask{46, 64, 59, 0x07ffffffffffe0},
	Mask{47, 64, 60, 0x07fffffffffff0},
	Mask{48, 64, 61, 0x07fffffffffff8},
	Mask{49, 64, 62, 0x07fffffffffffc},
	Mask{50, 64, 63, 0x07fffffffffffe},
	Mask{51, 64, 0, 0x07ffffffffffff},
	Mask{1, 64, 13, 0x08000000000000},
	Mask{1, 32, 13, 0x08000000080000},
	Mask{1, 16, 13, 0x08000800080008},
	Mask{2, 64, 14, 0x0c000000000000},
	Mask{2, 32, 14, 0x0c0000000c0000},
	Mask{2, 16, 14, 0x0c000c000c000c},
	Mask{3, 64, 15, 0x0e000000000000},
	Mask{3, 32, 15, 0x0e0000000e0000},
	Mask{3, 16, 15, 0x0e000e000e000e},
	Mask{4, 64, 16, 0x0f000000000000},
	Mask{4, 32, 16, 0x0f0000000f0000},
	Mask{4, 16, 0, 0x0f000f000f000f},
	Mask{5, 64, 17, 0x0f800000000000},
	Mask{5, 32, 17, 0x0f8000000f8000},
	Mask{6, 64, 18, 0x0fc00000000000},
	Mask{6, 32, 18, 0x0fc000000fc000},
	Mask{7, 64, 19, 0x0fe00000000000},
	Mask{7, 32, 19, 0x0fe000000fe000},
	Mask{8, 64, 20, 0x0ff00000000000},
	Mask{8, 32, 20, 0x0ff000000ff000},
	Mask{9, 64, 21, 0x0ff80000000000},
	Mask{9, 32, 21, 0x0ff800000ff800},
	Mask{10, 64, 22, 0x0ffc0000000000},
	Mask{10, 32, 22, 0x0ffc00000ffc00},
	Mask{11, 64, 23, 0x0ffe0000000000},
	Mask{11, 32, 23, 0x0ffe00000ffe00},
	Mask{12, 64, 24, 0x0fff0000000000},
	Mask{12, 32, 24, 0x0fff00000fff00},
	Mask{13, 64, 25, 0x0fff8000000000},
	Mask{13, 32, 25, 0x0fff80000fff80},
	Mask{14, 64, 26, 0x0fffc000000000},
	Mask{14, 32, 26, 0x0fffc0000fffc0},
	Mask{15, 64, 27, 0x0fffe000000000},
	Mask{15, 32, 27, 0x0fffe0000fffe0},
	Mask{16, 64, 28, 0x0ffff000000000},
	Mask{16, 32, 28, 0x0ffff0000ffff0},
	Mask{17, 64, 29, 0x0ffff800000000},
	Mask{17, 32, 29, 0x0ffff8000ffff8},
	Mask{18, 64, 30, 0x0ffffc00000000},
	Mask{18, 32, 30, 0x0ffffc000ffffc},
	Mask{19, 64, 31, 0x0ffffe00000000},
	Mask{19, 32, 31, 0x0ffffe000ffffe},
	Mask{20, 64, 32, 0x0fffff00000000},
	Mask{20, 32, 0, 0x0fffff000fffff},
	Mask{21, 64, 33, 0x0fffff80000000},
	Mask{22, 64, 34, 0x0fffffc0000000},
	Mask{23, 64, 35, 0x0fffffe0000000},
	Mask{24, 64, 36, 0x0ffffff0000000},
	Mask{25, 64, 37, 0x0ffffff8000000},
	Mask{26, 64, 38, 0x0ffffffc000000},
	Mask{27, 64, 39, 0x0ffffffe000000},
	Mask{28, 64, 40, 0x0fffffff000000},
	Mask{29, 64, 41, 0x0fffffff800000},
	Mask{30, 64, 42, 0x0fffffffc00000},
	Mask{31, 64, 43, 0x0fffffffe00000},
	Mask{32, 64, 44, 0x0ffffffff00000},
	Mask{33, 64, 45, 0x0ffffffff80000},
	Mask{34, 64, 46, 0x0ffffffffc0000},
	Mask{35, 64, 47, 0x0ffffffffe0000},
	Mask{36, 64, 48, 0x0fffffffff0000},
	Mask{37, 64, 49, 0x0fffffffff8000},
	Mask{38, 64, 50, 0x0fffffffffc000},
	Mask{39, 64, 51, 0x0fffffffffe000},
	Mask{40, 64, 52, 0x0ffffffffff000},
	Mask{41, 64, 53, 0x0ffffffffff800},
	Mask{42, 64, 54, 0x0ffffffffffc00},
	Mask{43, 64, 55, 0x0ffffffffffe00},
	Mask{44, 64, 56, 0x0fffffffffff00},
	Mask{45, 64, 57, 0x0fffffffffff80},
	Mask{46, 64, 58, 0x0fffffffffffc0},
	Mask{47, 64, 59, 0x0fffffffffffe0},
	Mask{48, 64, 60, 0x0ffffffffffff0},
	Mask{49, 64, 61, 0x0ffffffffffff8},
	Mask{50, 64, 62, 0x0ffffffffffffc},
	Mask{51, 64, 63, 0x0ffffffffffffe},
	Mask{52, 64, 0, 0x0fffffffffffff},
	Mask{1, 64, 12, 0x10000000000000},
	Mask{1, 32, 12, 0x10000000100000},
	Mask{1, 16, 12, 0x10001000100010},
	Mask{2, 64, 13, 0x18000000000000},
	Mask{2, 32, 13, 0x18000000180000},
	Mask{2, 16, 13, 0x18001800180018},
	Mask{3, 64, 14, 0x1c000000000000},
	Mask{3, 32, 14, 0x1c0000001c0000},
	Mask{3, 16, 14, 0x1c001c001c001c},
	Mask{4, 64, 15, 0x1e000000000000},
	Mask{4, 32, 15, 0x1e0000001e0000},
	Mask{4, 16, 15, 0x1e001e001e001e},
	Mask{5, 64, 16, 0x1f000000000000},
	Mask{5, 32, 16, 0x1f0000001f0000},
	Mask{5, 16, 0, 0x1f001f001f001f},
	Mask{6, 64, 17, 0x1f800000000000},
	Mask{6, 32, 17, 0x1f8000001f8000},
	Mask{7, 64, 18, 0x1fc00000000000},
	Mask{7, 32, 18, 0x1fc000001fc000},
	Mask{8, 64, 19, 0x1fe00000000000},
	Mask{8, 32, 19, 0x1fe000001fe000},
	Mask{9, 64, 20, 0x1ff00000000000},
	Mask{9, 32, 20, 0x1ff000001ff000},
	Mask{10, 64, 21, 0x1ff80000000000},
	Mask{10, 32, 21, 0x1ff800001ff800},
	Mask{11, 64, 22, 0x1ffc0000000000},
	Mask{11, 32, 22, 0x1ffc00001ffc00},
	Mask{12, 64, 23, 0x1ffe0000000000},
	Mask{12, 32, 23, 0x1ffe00001ffe00},
	Mask{13, 64, 24, 0x1fff0000000000},
	Mask{13, 32, 24, 0x1fff00001fff00},
	Mask{14, 64, 25, 0x1fff8000000000},
	Mask{14, 32, 25, 0x1fff80001fff80},
	Mask{15, 64, 26, 0x1fffc000000000},
	Mask{15, 32, 26, 0x1fffc0001fffc0},
	Mask{16, 64, 27, 0x1fffe000000000},
	Mask{16, 32, 27, 0x1fffe0001fffe0},
	Mask{17, 64, 28, 0x1ffff000000000},
	Mask{17, 32, 28, 0x1ffff0001ffff0},
	Mask{18, 64, 29, 0x1ffff800000000},
	Mask{18, 32, 29, 0x1ffff8001ffff8},
	Mask{19, 64, 30, 0x1ffffc00000000},
	Mask{19, 32, 30, 0x1ffffc001ffffc},
	Mask{20, 64, 31, 0x1ffffe00000000},
	Mask{20, 32, 31, 0x1ffffe001ffffe},
	Mask{21, 64, 32, 0x1fffff00000000},
	Mask{21, 32, 0, 0x1fffff001fffff},
	Mask{22, 64, 33, 0x1fffff80000000},
	Mask{23, 64, 34, 0x1fffffc0000000},
	Mask{24, 64, 35, 0x1fffffe0000000},
	Mask{25, 64, 36, 0x1ffffff0000000},
	Mask{26, 64, 37, 0x1ffffff8000000},
	Mask{27, 64, 38, 0x1ffffffc000000},
	Mask{28, 64, 39, 0x1ffffffe000000},
	Mask{29, 64, 40, 0x1fffffff000000},
	Mask{30, 64, 41, 0x1fffffff800000},
	Mask{31, 64, 42, 0x1fffffffc00000},
	Mask{32, 64, 43, 0x1fffffffe00000},
	Mask{33, 64, 44, 0x1ffffffff00000},
	Mask{34, 64, 45, 0x1ffffffff80000},
	Mask{35, 64, 46, 0x1ffffffffc0000},
	Mask{36, 64, 47, 0x1ffffffffe0000},
	Mask{37, 64, 48, 0x1fffffffff0000},
	Mask{38, 64, 49, 0x1fffffffff8000},
	Mask{39, 64, 50, 0x1fffffffffc000},
	Mask{40, 64, 51, 0x1fffffffffe000},
	Mask{41, 64, 52, 0x1ffffffffff000},
	Mask{42, 64, 53, 0x1ffffffffff800},
	Mask{43, 64, 54, 0x1ffffffffffc00},
	Mask{44, 64, 55, 0x1ffffffffffe00},
	Mask{45, 64, 56, 0x1fffffffffff00},
	Mask{46, 64, 57, 0x1fffffffffff80},
	Mask{47, 64, 58, 0x1fffffffffffc0},
	Mask{48, 64, 59, 0x1fffffffffffe0},
	Mask{49, 64, 60, 0x1ffffffffffff0},
	Mask{50, 64, 61, 0x1ffffffffffff8},
	Mask{51, 64, 62, 0x1ffffffffffffc},
	Mask{52, 64, 63, 0x1ffffffffffffe},
	Mask{53, 64, 0, 0x1fffffffffffff},
	Mask{1, 64, 11, 0x20000000000000},
	Mask{1, 32, 11, 0x20000000200000},
	Mask{1, 16, 11, 0x20002000200020},
	Mask{2, 64, 12, 0x30000000000000},
	Mask{2, 32, 12, 0x30000000300000},
	Mask{2, 16, 12, 0x30003000300030},
	Mask{3, 64, 13, 0x38000000000000},
	Mask{3, 32, 13, 0x38000000380000},
	Mask{3, 16, 13, 0x38003800380038},
	Mask{4, 64, 14, 0x3c000000000000},
	Mask{4, 32, 14, 0x3c0000003c0000},
	Mask{4, 16, 14, 0x3c003c003c003c},
	Mask{5, 64, 15, 0x3e000000000000},
	Mask{5, 32, 15, 0x3e0000003e0000},
	Mask{5, 16, 15, 0x3e003e003e003e},
	Mask{6, 64, 16, 0x3f000000000000},
	Mask{6, 32, 16, 0x3f0000003f0000},
	Mask{6, 16, 0, 0x3f003f003f003f},
	Mask{7, 64, 17, 0x3f800000000000},
	Mask{7, 32, 17, 0x3f8000003f8000},
	Mask{8, 64, 18, 0x3fc00000000000},
	Mask{8, 32, 18, 0x3fc000003fc000},
	Mask{9, 64, 19, 0x3fe00000000000},
	Mask{9, 32, 19, 0x3fe000003fe000},
	Mask{10, 64, 20, 0x3ff00000000000},
	Mask{10, 32, 20, 0x3ff000003ff000},
	Mask{11, 64, 21, 0x3ff80000000000},
	Mask{11, 32, 21, 0x3ff800003ff800},
	Mask{12, 64, 22, 0x3ffc0000000000},
	Mask{12, 32, 22, 0x3ffc00003ffc00},
	Mask{13, 64, 23, 0x3ffe0000000000},
	Mask{13, 32, 23, 0x3ffe00003ffe00},
	Mask{14, 64, 24, 0x3fff0000000000},
	Mask{14, 32, 24, 0x3fff00003fff00},
	Mask{15, 64, 25, 0x3fff8000000000},
	Mask{15, 32, 25, 0x3fff80003fff80},
	Mask{16, 64, 26, 0x3fffc000000000},
	Mask{16, 32, 26, 0x3fffc0003fffc0},
	Mask{17, 64, 27, 0x3fffe000000000},
	Mask{17, 32, 27, 0x3fffe0003fffe0},
	Mask{18, 64, 28, 0x3ffff000000000},
	Mask{18, 32, 28, 0x3ffff0003ffff0},
	Mask{19, 64, 29, 0x3ffff800000000},
	Mask{19, 32, 29, 0x3ffff8003ffff8},
	Mask{20, 64, 30, 0x3ffffc00000000},
	Mask{20, 32, 30, 0x3ffffc003ffffc},
	Mask{21, 64, 31, 0x3ffffe00000000},
	Mask{21, 32, 31, 0x3ffffe003ffffe},
	Mask{22, 64, 32, 0x3fffff00000000},
	Mask{22, 32, 0, 0x3fffff003fffff},
	Mask{23, 64, 33, 0x3fffff80000000},
	Mask{24, 64, 34, 0x3fffffc0000000},
	Mask{25, 64, 35, 0x3fffffe0000000},
	Mask{26, 64, 36, 0x3ffffff0000000},
	Mask{27, 64, 37, 0x3ffffff8000000},
	Mask{28, 64, 38, 0x3ffffffc000000},
	Mask{29, 64, 39, 0x3ffffffe000000},
	Mask{30, 64, 40, 0x3fffffff000000},
	Mask{31, 64, 41, 0x3fffffff800000},
	Mask{32, 64, 42, 0x3fffffffc00000},
	Mask{33, 64, 43, 0x3fffffffe00000},
	Mask{34, 64, 44, 0x3ffffffff00000},
	Mask{35, 64, 45, 0x3ffffffff80000},
	Mask{36, 64, 46, 0x3ffffffffc0000},
	Mask{37, 64, 47, 0x3ffffffffe0000},
	Mask{38, 64, 48, 0x3fffffffff0000},
	Mask{39, 64, 49, 0x3fffffffff8000},
	Mask{40, 64, 50, 0x3fffffffffc000},
	Mask{41, 64, 51, 0x3fffffffffe000},
	Mask{42, 64, 52, 0x3ffffffffff000},
	Mask{43, 64, 53, 0x3ffffffffff800},
	Mask{44, 64, 54, 0x3ffffffffffc00},
	Mask{45, 64, 55, 0x3ffffffffffe00},
	Mask{46, 64, 56, 0x3fffffffffff00},
	Mask{47, 64, 57, 0x3fffffffffff80},
	Mask{48, 64, 58, 0x3fffffffffffc0},
	Mask{49, 64, 59, 0x3fffffffffffe0},
	Mask{50, 64, 60, 0x3ffffffffffff0},
	Mask{51, 64, 61, 0x3ffffffffffff8},
	Mask{52, 64, 62, 0x3ffffffffffffc},
	Mask{53, 64, 63, 0x3ffffffffffffe},
	Mask{54, 64, 0, 0x3fffffffffffff},
	Mask{1, 64, 10, 0x40000000000000},
	Mask{1, 32, 10, 0x40000000400000},
	Mask{1, 16, 10, 0x40004000400040},
	Mask{2, 64, 11, 0x60000000000000},
	Mask{2, 32, 11, 0x60000000600000},
	Mask{2, 16, 11, 0x60006000600060},
	Mask{3, 64, 12, 0x70000000000000},
	Mask{3, 32, 12, 0x70000000700000},
	Mask{3, 16, 12, 0x70007000700070},
	Mask{4, 64, 13, 0x78000000000000},
	Mask{4, 32, 13, 0x78000000780000},
	Mask{4, 16, 13, 0x78007800780078},
	Mask{5, 64, 14, 0x7c000000000000},
	Mask{5, 32, 14, 0x7c0000007c0000},
	Mask{5, 16, 14, 0x7c007c007c007c},
	Mask{6, 64, 15, 0x7e000000000000},
	Mask{6, 32, 15, 0x7e0000007e0000},
	Mask{6, 16, 15, 0x7e007e007e007e},
	Mask{7, 64, 16, 0x7f000000000000},
	Mask{7, 32, 16, 0x7f0000007f0000},
	Mask{7, 16, 0, 0x7f007f007f007f},
	Mask{8, 64, 17, 0x7f800000000000},
	Mask{8, 32, 17, 0x7f8000007f8000},
	Mask{9, 64, 18, 0x7fc00000000000},
	Mask{9, 32, 18, 0x7fc000007fc000},
	Mask{10, 64, 19, 0x7fe00000000000},
	Mask{10, 32, 19, 0x7fe000007fe000},
	Mask{11, 64, 20, 0x7ff00000000000},
	Mask{11, 32, 20, 0x7ff000007ff000},
	Mask{12, 64, 21, 0x7ff80000000000},
	Mask{12, 32, 21, 0x7ff800007ff800},
	Mask{13, 64, 22, 0x7ffc0000000000},
	Mask{13, 32, 22, 0x7ffc00007ffc00},
	Mask{14, 64, 23, 0x7ffe0000000000},
	Mask{14, 32, 23, 0x7ffe00007ffe00},
	Mask{15, 64, 24, 0x7fff0000000000},
	Mask{15, 32, 24, 0x7fff00007fff00},
	Mask{16, 64, 25, 0x7fff8000000000},
	Mask{16, 32, 25, 0x7fff80007fff80},
	Mask{17, 64, 26, 0x7fffc000000000},
	Mask{17, 32, 26, 0x7fffc0007fffc0},
	Mask{18, 64, 27, 0x7fffe000000000},
	Mask{18, 32, 27, 0x7fffe0007fffe0},
	Mask{19, 64, 28, 0x7ffff000000000},
	Mask{19, 32, 28, 0x7ffff0007ffff0},
	Mask{20, 64, 29, 0x7ffff800000000},
	Mask{20, 32, 29, 0x7ffff8007ffff8},
	Mask{21, 64, 30, 0x7ffffc00000000},
	Mask{21, 32, 30, 0x7ffffc007ffffc},
	Mask{22, 64, 31, 0x7ffffe00000000},
	Mask{22, 32, 31, 0x7ffffe007ffffe},
	Mask{23, 64, 32, 0x7fffff00000000},
	Mask{23, 32, 0, 0x7fffff007fffff},
	Mask{24, 64, 33, 0x7fffff80000000},
	Mask{25, 64, 34, 0x7fffffc0000000},
	Mask{26, 64, 35, 0x7fffffe0000000},
	Mask{27, 64, 36, 0x7ffffff0000000},
	Mask{28, 64, 37, 0x7ffffff8000000},
	Mask{29, 64, 38, 0x7ffffffc000000},
	Mask{30, 64, 39, 0x7ffffffe000000},
	Mask{31, 64, 40, 0x7fffffff000000},
	Mask{32, 64, 41, 0x7fffffff800000},
	Mask{33, 64, 42, 0x7fffffffc00000},
	Mask{34, 64, 43, 0x7fffffffe00000},
	Mask{35, 64, 44, 0x7ffffffff00000},
	Mask{36, 64, 45, 0x7ffffffff80000},
	Mask{37, 64, 46, 0x7ffffffffc0000},
	Mask{38, 64, 47, 0x7ffffffffe0000},
	Mask{39, 64, 48, 0x7fffffffff0000},
	Mask{40, 64, 49, 0x7fffffffff8000},
	Mask{41, 64, 50, 0x7fffffffffc000},
	Mask{42, 64, 51, 0x7fffffffffe000},
	Mask{43, 64, 52, 0x7ffffffffff000},
	Mask{44, 64, 53, 0x7ffffffffff800},
	Mask{45, 64, 54, 0x7ffffffffffc00},
	Mask{46, 64, 55, 0x7ffffffffffe00},
	Mask{47, 64, 56, 0x7fffffffffff00},
	Mask{48, 64, 57, 0x7fffffffffff80},
	Mask{49, 64, 58, 0x7fffffffffffc0},
	Mask{50, 64, 59, 0x7fffffffffffe0},
	Mask{51, 64, 60, 0x7ffffffffffff0},
	Mask{52, 64, 61, 0x7ffffffffffff8},
	Mask{53, 64, 62, 0x7ffffffffffffc},
	Mask{54, 64, 63, 0x7ffffffffffffe},
	Mask{55, 64, 0, 0x7fffffffffffff},
	Mask{1, 64, 9, 0x80000000000000},
	Mask{1, 32, 9, 0x80000000800000},
	Mask{1, 16, 9, 0x80008000800080},
	Mask{2, 64, 10, 0xc0000000000000},
	Mask{2, 32, 10, 0xc0000000c00000},
	Mask{2, 16, 10, 0xc000c000c000c0},
	Mask{3, 64, 11, 0xe0000000000000},
	Mask{3, 32, 11, 0xe0000000e00000},
	Mask{3, 16, 11, 0xe000e000e000e0},
	Mask{4, 64, 12, 0xf0000000000000},
	Mask{4, 32, 12, 0xf0000000f00000},
	Mask{4, 16, 12, 0xf000f000f000f0},
	Mask{5, 64, 13, 0xf8000000000000},
	Mask{5, 32, 13, 0xf8000000f80000},
	Mask{5, 16, 13, 0xf800f800f800f8},
	Mask{6, 64, 14, 0xfc000000000000},
	Mask{6, 32, 14, 0xfc000000fc0000},
	Mask{6, 16, 14, 0xfc00fc00fc00fc},
	Mask{7, 64, 15, 0xfe000000000000},
	Mask{7, 32, 15, 0xfe000000fe0000},
	Mask{7, 16, 15, 0xfe00fe00fe00fe},
	Mask{8, 64, 16, 0xff000000000000},
	Mask{8, 32, 16, 0xff000000ff0000},
	Mask{8, 16, 0, 0xff00ff00ff00ff},
	Mask{9, 64, 17, 0xff800000000000},
	Mask{9, 32, 17, 0xff800000ff8000},
	Mask{10, 64, 18, 0xffc00000000000},
	Mask{10, 32, 18, 0xffc00000ffc000},
	Mask{11, 64, 19, 0xffe00000000000},
	Mask{11, 32, 19, 0xffe00000ffe000},
	Mask{12, 64, 20, 0xfff00000000000},
	Mask{12, 32, 20, 0xfff00000fff000},
	Mask{13, 64, 21, 0xfff80000000000},
	Mask{13, 32, 21, 0xfff80000fff800},
	Mask{14, 64, 22, 0xfffc0000000000},
	Mask{14, 32, 22, 0xfffc0000fffc00},
	Mask{15, 64, 23, 0xfffe0000000000},
	Mask{15, 32, 23, 0xfffe0000fffe00},
	Mask{16, 64, 24, 0xffff0000000000},
	Mask{16, 32, 24, 0xffff0000ffff00},
	Mask{17, 64, 25, 0xffff8000000000},
	Mask{17, 32, 25, 0xffff8000ffff80},
	Mask{18, 64, 26, 0xffffc000000000},
	Mask{18, 32, 26, 0xffffc000ffffc0},
	Mask{19, 64, 27, 0xffffe000000000},
	Mask{19, 32, 27, 0xffffe000ffffe0},
	Mask{20, 64, 28, 0xfffff000000000},
	Mask{20, 32, 28, 0xfffff000fffff0},
	Mask{21, 64, 29, 0xfffff800000000},
	Mask{21, 32, 29, 0xfffff800fffff8},
	Mask{22, 64, 30, 0xfffffc00000000},
	Mask{22, 32, 30, 0xfffffc00fffffc},
	Mask{23, 64, 31, 0xfffffe00000000},
	Mask{23, 32, 31, 0xfffffe00fffffe},
	Mask{24, 64, 32, 0xffffff00000000},
	Mask{24, 32, 0, 0xffffff00ffffff},
	Mask{25, 64, 33, 0xffffff80000000},
	Mask{26, 64, 34, 0xffffffc0000000},
	Mask{27, 64, 35, 0xffffffe0000000},
	Mask{28, 64, 36, 0xfffffff0000000},
	Mask{29, 64, 37, 0xfffffff8000000},
	Mask{30, 64, 38, 0xfffffffc000000},
	Mask{31, 64, 39, 0xfffffffe000000},
	Mask{32, 64, 40, 0xffffffff000000},
	Mask{33, 64, 41, 0xffffffff800000},
	Mask{34, 64, 42, 0xffffffffc00000},
	Mask{35, 64, 43, 0xffffffffe00000},
	Mask{36, 64, 44, 0xfffffffff00000},
	Mask{37, 64, 45, 0xfffffffff80000},
	Mask{38, 64, 46, 0xfffffffffc0000},
	Mask{39, 64, 47, 0xfffffffffe0000},
	Mask{40, 64, 48, 0xffffffffff0000},
	Mask{41, 64, 49, 0xffffffffff8000},
	Mask{42, 64, 50, 0xffffffffffc000},
	Mask{43, 64, 51, 0xffffffffffe000},
	Mask{44, 64, 52, 0xfffffffffff000},
	Mask{45, 64, 53, 0xfffffffffff800},
	Mask{46, 64, 54, 0xfffffffffffc00},
	Mask{47, 64, 55, 0xfffffffffffe00},
	Mask{48, 64, 56, 0xffffffffffff00},
	Mask{49, 64, 57, 0xffffffffffff80},
	Mask{50, 64, 58, 0xffffffffffffc0},
	Mask{51, 64, 59, 0xffffffffffffe0},
	Mask{52, 64, 60, 0xfffffffffffff0},
	Mask{53, 64, 61, 0xfffffffffffff8},
	Mask{54, 64, 62, 0xfffffffffffffc},
	Mask{55, 64, 63, 0xfffffffffffffe},
	Mask{56, 64, 0, 0xffffffffffffff},
	Mask{1, 64, 8, 0x100000000000000},
	Mask{1, 32, 8, 0x100000001000000},
	Mask{1, 16, 8, 0x100010001000100},
	Mask{1, 8, 0, 0x101010101010101},
	Mask{2, 64, 9, 0x180000000000000},
	Mask{2, 32, 9, 0x180000001800000},
	Mask{2, 16, 9, 0x180018001800180},
	Mask{3, 64, 10, 0x1c0000000000000},
	Mask{3, 32, 10, 0x1c0000001c00000},
	Mask{3, 16, 10, 0x1c001c001c001c0},
	Mask{4, 64, 11, 0x1e0000000000000},
	Mask{4, 32, 11, 0x1e0000001e00000},
	Mask{4, 16, 11, 0x1e001e001e001e0},
	Mask{5, 64, 12, 0x1f0000000000000},
	Mask{5, 32, 12, 0x1f0000001f00000},
	Mask{5, 16, 12, 0x1f001f001f001f0},
	Mask{6, 64, 13, 0x1f8000000000000},
	Mask{6, 32, 13, 0x1f8000001f80000},
	Mask{6, 16, 13, 0x1f801f801f801f8},
	Mask{7, 64, 14, 0x1fc000000000000},
	Mask{7, 32, 14, 0x1fc000001fc0000},
	Mask{7, 16, 14, 0x1fc01fc01fc01fc},
	Mask{8, 64, 15, 0x1fe000000000000},
	Mask{8, 32, 15, 0x1fe000001fe0000},
	Mask{8, 16, 15, 0x1fe01fe01fe01fe},
	Mask{9, 64, 16, 0x1ff000000000000},
	Mask{9, 32, 16, 0x1ff000001ff0000},
	Mask{9, 16, 0, 0x1ff01ff01ff01ff},
	Mask{10, 64, 17, 0x1ff800000000000},
	Mask{10, 32, 17, 0x1ff800001ff8000},
	Mask{11, 64, 18, 0x1ffc00000000000},
	Mask{11, 32, 18, 0x1ffc00001ffc000},
	Mask{12, 64, 19, 0x1ffe00000000000},
	Mask{12, 32, 19, 0x1ffe00001ffe000},
	Mask{13, 64, 20, 0x1fff00000000000},
	Mask{13, 32, 20, 0x1fff00001fff000},
	Mask{14, 64, 21, 0x1fff80000000000},
	Mask{14, 32, 21, 0x1fff80001fff800},
	Mask{15, 64, 22, 0x1fffc0000000000},
	Mask{15, 32, 22, 0x1fffc0001fffc00},
	Mask{16, 64, 23, 0x1fffe0000000000},
	Mask{16, 32, 23, 0x1fffe0001fffe00},
	Mask{17, 64, 24, 0x1ffff0000000000},
	Mask{17, 32, 24, 0x1ffff0001ffff00},
	Mask{18, 64, 25, 0x1ffff8000000000},
	Mask{18, 32, 25, 0x1ffff8001ffff80},
	Mask{19, 64, 26, 0x1ffffc000000000},
	Mask{19, 32, 26, 0x1ffffc001ffffc0},
	Mask{20, 64, 27, 0x1ffffe000000000},
	Mask{20, 32, 27, 0x1ffffe001ffffe0},
	Mask{21, 64, 28, 0x1fffff000000000},
	Mask{21, 32, 28, 0x1fffff001fffff0},
	Mask{22, 64, 29, 0x1fffff800000000},
	Mask{22, 32, 29, 0x1fffff801fffff8},
	Mask{23, 64, 30, 0x1fffffc00000000},
	Mask{23, 32, 30, 0x1fffffc01fffffc},
	Mask{24, 64, 31, 0x1fffffe00000000},
	Mask{24, 32, 31, 0x1fffffe01fffffe},
	Mask{25, 64, 32, 0x1ffffff00000000},
	Mask{25, 32, 0, 0x1ffffff01ffffff},
	Mask{26, 64, 33, 0x1ffffff80000000},
	Mask{27, 64, 34, 0x1ffffffc0000000},
	Mask{28, 64, 35, 0x1ffffffe0000000},
	Mask{29, 64, 36, 0x1fffffff0000000},
	Mask{30, 64, 37, 0x1fffffff8000000},
	Mask{31, 64, 38, 0x1fffffffc000000},
	Mask{32, 64, 39, 0x1fffffffe000000},
	Mask{33, 64, 40, 0x1ffffffff000000},
	Mask{34, 64, 41, 0x1ffffffff800000},
	Mask{35, 64, 42, 0x1ffffffffc00000},
	Mask{36, 64, 43, 0x1ffffffffe00000},
	Mask{37, 64, 44, 0x1fffffffff00000},
	Mask{38, 64, 45, 0x1fffffffff80000},
	Mask{39, 64, 46, 0x1fffffffffc0000},
	Mask{40, 64, 47, 0x1fffffffffe0000},
	Mask{41, 64, 48, 0x1ffffffffff0000},
	Mask{42, 64, 49, 0x1ffffffffff8000},
	Mask{43, 64, 50, 0x1ffffffffffc000},
	Mask{44, 64, 51, 0x1ffffffffffe000},
	Mask{45, 64, 52, 0x1fffffffffff000},
	Mask{46, 64, 53, 0x1fffffffffff800},
	Mask{47, 64, 54, 0x1fffffffffffc00},
	Mask{48, 64, 55, 0x1fffffffffffe00},
	Mask{49, 64, 56, 0x1ffffffffffff00},
	Mask{50, 64, 57, 0x1ffffffffffff80},
	Mask{51, 64, 58, 0x1ffffffffffffc0},
	Mask{52, 64, 59, 0x1ffffffffffffe0},
	Mask{53, 64, 60, 0x1fffffffffffff0},
	Mask{54, 64, 61, 0x1fffffffffffff8},
	Mask{55, 64, 62, 0x1fffffffffffffc},
	Mask{56, 64, 63, 0x1fffffffffffffe},
	Mask{57, 64, 0, 0x1ffffffffffffff},
	Mask{1, 64, 7, 0x200000000000000},
	Mask{1, 32, 7, 0x200000002000000},
	Mask{1, 16, 7, 0x200020002000200},
	Mask{1, 8, 7, 0x202020202020202},
	Mask{2, 64, 8, 0x300000000000000},
	Mask{2, 32, 8, 0x300000003000000},
	Mask{2, 16, 8, 0x300030003000300},
	Mask{2, 8, 0, 0x303030303030303},
	Mask{3, 64, 9, 0x380000000000000},
	Mask{3, 32, 9, 0x380000003800000},
	Mask{3, 16, 9, 0x380038003800380},
	Mask{4, 64, 10, 0x3c0000000000000},
	Mask{4, 32, 10, 0x3c0000003c00000},
	Mask{4, 16, 10, 0x3c003c003c003c0},
	Mask{5, 64, 11, 0x3e0000000000000},
	Mask{5, 32, 11, 0x3e0000003e00000},
	Mask{5, 16, 11, 0x3e003e003e003e0},
	Mask{6, 64, 12, 0x3f0000000000000},
	Mask{6, 32, 12, 0x3f0000003f00000},
	Mask{6, 16, 12, 0x3f003f003f003f0},
	Mask{7, 64, 13, 0x3f8000000000000},
	Mask{7, 32, 13, 0x3f8000003f80000},
	Mask{7, 16, 13, 0x3f803f803f803f8},
	Mask{8, 64, 14, 0x3fc000000000000},
	Mask{8, 32, 14, 0x3fc000003fc0000},
	Mask{8, 16, 14, 0x3fc03fc03fc03fc},
	Mask{9, 64, 15, 0x3fe000000000000},
	Mask{9, 32, 15, 0x3fe000003fe0000},
	Mask{9, 16, 15, 0x3fe03fe03fe03fe},
	Mask{10, 64, 16, 0x3ff000000000000},
	Mask{10, 32, 16, 0x3ff000003ff0000},
	Mask{10, 16, 0, 0x3ff03ff03ff03ff},
	Mask{11, 64, 17, 0x3ff800000000000},
	Mask{11, 32, 17, 0x3ff800003ff8000},
	Mask{12, 64, 18, 0x3ffc00000000000},
	Mask{12, 32, 18, 0x3ffc00003ffc000},
	Mask{13, 64, 19, 0x3ffe00000000000},
	Mask{13, 32, 19, 0x3ffe00003ffe000},
	Mask{14, 64, 20, 0x3fff00000000000},
	Mask{14, 32, 20, 0x3fff00003fff000},
	Mask{15, 64, 21, 0x3fff80000000000},
	Mask{15, 32, 21, 0x3fff80003fff800},
	Mask{16, 64, 22, 0x3fffc0000000000},
	Mask{16, 32, 22, 0x3fffc0003fffc00},
	Mask{17, 64, 23, 0x3fffe0000000000},
	Mask{17, 32, 23, 0x3fffe0003fffe00},
	Mask{18, 64, 24, 0x3ffff0000000000},
	Mask{18, 32, 24, 0x3ffff0003ffff00},
	Mask{19, 64, 25, 0x3ffff8000000000},
	Mask{19, 32, 25, 0x3ffff8003ffff80},
	Mask{20, 64, 26, 0x3ffffc000000000},
	Mask{20, 32, 26, 0x3ffffc003ffffc0},
	Mask{21, 64, 27, 0x3ffffe000000000},
	Mask{21, 32, 27, 0x3ffffe003ffffe0},
	Mask{22, 64, 28, 0x3fffff000000000},
	Mask{22, 32, 28, 0x3fffff003fffff0},
	Mask{23, 64, 29, 0x3fffff800000000},
	Mask{23, 32, 29, 0x3fffff803fffff8},
	Mask{24, 64, 30, 0x3fffffc00000000},
	Mask{24, 32, 30, 0x3fffffc03fffffc},
	Mask{25, 64, 31, 0x3fffffe00000000},
	Mask{25, 32, 31, 0x3fffffe03fffffe},
	Mask{26, 64, 32, 0x3ffffff00000000},
	Mask{26, 32, 0, 0x3ffffff03ffffff},
	Mask{27, 64, 33, 0x3ffffff80000000},
	Mask{28, 64, 34, 0x3ffffffc0000000},
	Mask{29, 64, 35, 0x3ffffffe0000000},
	Mask{30, 64, 36, 0x3fffffff0000000},
	Mask{31, 64, 37, 0x3fffffff8000000},
	Mask{32, 64, 38, 0x3fffffffc000000},
	Mask{33, 64, 39, 0x3fffffffe000000},
	Mask{34, 64, 40, 0x3ffffffff000000},
	Mask{35, 64, 41, 0x3ffffffff800000},
	Mask{36, 64, 42, 0x3ffffffffc00000},
	Mask{37, 64, 43, 0x3ffffffffe00000},
	Mask{38, 64, 44, 0x3fffffffff00000},
	Mask{39, 64, 45, 0x3fffffffff80000},
	Mask{40, 64, 46, 0x3fffffffffc0000},
	Mask{41, 64, 47, 0x3fffffffffe0000},
	Mask{42, 64, 48, 0x3ffffffffff0000},
	Mask{43, 64, 49, 0x3ffffffffff8000},
	Mask{44, 64, 50, 0x3ffffffffffc000},
	Mask{45, 64, 51, 0x3ffffffffffe000},
	Mask{46, 64, 52, 0x3fffffffffff000},
	Mask{47, 64, 53, 0x3fffffffffff800},
	Mask{48, 64, 54, 0x3fffffffffffc00},
	Mask{49, 64, 55, 0x3fffffffffffe00},
	Mask{50, 64, 56, 0x3ffffffffffff00},
	Mask{51, 64, 57, 0x3ffffffffffff80},
	Mask{52, 64, 58, 0x3ffffffffffffc0},
	Mask{53, 64, 59, 0x3ffffffffffffe0},
	Mask{54, 64, 60, 0x3fffffffffffff0},
	Mask{55, 64, 61, 0x3fffffffffffff8},
	Mask{56, 64, 62, 0x3fffffffffffffc},
	Mask{57, 64, 63, 0x3fffffffffffffe},
	Mask{58, 64, 0, 0x3ffffffffffffff},
	Mask{1, 64, 6, 0x400000000000000},
	Mask{1, 32, 6, 0x400000004000000},
	Mask{1, 16, 6, 0x400040004000400},
	Mask{1, 8, 6, 0x404040404040404},
	Mask{2, 64, 7, 0x600000000000000},
	Mask{2, 32, 7, 0x600000006000000},
	Mask{2, 16, 7, 0x600060006000600},
	Mask{2, 8, 7, 0x606060606060606},
	Mask{3, 64, 8, 0x700000000000000},
	Mask{3, 32, 8, 0x700000007000000},
	Mask{3, 16, 8, 0x700070007000700},
	Mask{3, 8, 0, 0x707070707070707},
	Mask{4, 64, 9, 0x780000000000000},
	Mask{4, 32, 9, 0x780000007800000},
	Mask{4, 16, 9, 0x780078007800780},
	Mask{5, 64, 10, 0x7c0000000000000},
	Mask{5, 32, 10, 0x7c0000007c00000},
	Mask{5, 16, 10, 0x7c007c007c007c0},
	Mask{6, 64, 11, 0x7e0000000000000},
	Mask{6, 32, 11, 0x7e0000007e00000},
	Mask{6, 16, 11, 0x7e007e007e007e0},
	Mask{7, 64, 12, 0x7f0000000000000},
	Mask{7, 32, 12, 0x7f0000007f00000},
	Mask{7, 16, 12, 0x7f007f007f007f0},
	Mask{8, 64, 13, 0x7f8000000000000},
	Mask{8, 32, 13, 0x7f8000007f80000},
	Mask{8, 16, 13, 0x7f807f807f807f8},
	Mask{9, 64, 14, 0x7fc000000000000},
	Mask{9, 32, 14, 0x7fc000007fc0000},
	Mask{9, 16, 14, 0x7fc07fc07fc07fc},
	Mask{10, 64, 15, 0x7fe000000000000},
	Mask{10, 32, 15, 0x7fe000007fe0000},
	Mask{10, 16, 15, 0x7fe07fe07fe07fe},
	Mask{11, 64, 16, 0x7ff000000000000},
	Mask{11, 32, 16, 0x7ff000007ff0000},
	Mask{11, 16, 0, 0x7ff07ff07ff07ff},
	Mask{12, 64, 17, 0x7ff800000000000},
	Mask{12, 32, 17, 0x7ff800007ff8000},
	Mask{13, 64, 18, 0x7ffc00000000000},
	Mask{13, 32, 18, 0x7ffc00007ffc000},
	Mask{14, 64, 19, 0x7ffe00000000000},
	Mask{14, 32, 19, 0x7ffe00007ffe000},
	Mask{15, 64, 20, 0x7fff00000000000},
	Mask{15, 32, 20, 0x7fff00007fff000},
	Mask{16, 64, 21, 0x7fff80000000000},
	Mask{16, 32, 21, 0x7fff80007fff800},
	Mask{17, 64, 22, 0x7fffc0000000000},
	Mask{17, 32, 22, 0x7fffc0007fffc00},
	Mask{18, 64, 23, 0x7fffe0000000000},
	Mask{18, 32, 23, 0x7fffe0007fffe00},
	Mask{19, 64, 24, 0x7ffff0000000000},
	Mask{19, 32, 24, 0x7ffff0007ffff00},
	Mask{20, 64, 25, 0x7ffff8000000000},
	Mask{20, 32, 25, 0x7ffff8007ffff80},
	Mask{21, 64, 26, 0x7ffffc000000000},
	Mask{21, 32, 26, 0x7ffffc007ffffc0},
	Mask{22, 64, 27, 0x7ffffe000000000},
	Mask{22, 32, 27, 0x7ffffe007ffffe0},
	Mask{23, 64, 28, 0x7fffff000000000},
	Mask{23, 32, 28, 0x7fffff007fffff0},
	Mask{24, 64, 29, 0x7fffff800000000},
	Mask{24, 32, 29, 0x7fffff807fffff8},
	Mask{25, 64, 30, 0x7fffffc00000000},
	Mask{25, 32, 30, 0x7fffffc07fffffc},
	Mask{26, 64, 31, 0x7fffffe00000000},
	Mask{26, 32, 31, 0x7fffffe07fffffe},
	Mask{27, 64, 32, 0x7ffffff00000000},
	Mask{27, 32, 0, 0x7ffffff07ffffff},
	Mask{28, 64, 33, 0x7ffffff80000000},
	Mask{29, 64, 34, 0x7ffffffc0000000},
	Mask{30, 64, 35, 0x7ffffffe0000000},
	Mask{31, 64, 36, 0x7fffffff0000000},
	Mask{32, 64, 37, 0x7fffffff8000000},
	Mask{33, 64, 38, 0x7fffffffc000000},
	Mask{34, 64, 39, 0x7fffffffe000000},
	Mask{35, 64, 40, 0x7ffffffff000000},
	Mask{36, 64, 41, 0x7ffffffff800000},
	Mask{37, 64, 42, 0x7ffffffffc00000},
	Mask{38, 64, 43, 0x7ffffffffe00000},
	Mask{39, 64, 44, 0x7fffffffff00000},
	Mask{40, 64, 45, 0x7fffffffff80000},
	Mask{41, 64, 46, 0x7fffffffffc0000},
	Mask{42, 64, 47, 0x7fffffffffe0000},
	Mask{43, 64, 48, 0x7ffffffffff0000},
	Mask{44, 64, 49, 0x7ffffffffff8000},
	Mask{45, 64, 50, 0x7ffffffffffc000},
	Mask{46, 64, 51, 0x7ffffffffffe000},
	Mask{47, 64, 52, 0x7fffffffffff000},
	Mask{48, 64, 53, 0x7fffffffffff800},
	Mask{49, 64, 54, 0x7fffffffffffc00},
	Mask{50, 64, 55, 0x7fffffffffffe00},
	Mask{51, 64, 56, 0x7ffffffffffff00},
	Mask{52, 64, 57, 0x7ffffffffffff80},
	Mask{53, 64, 58, 0x7ffffffffffffc0},
	Mask{54, 64, 59, 0x7ffffffffffffe0},
	Mask{55, 64, 60, 0x7fffffffffffff0},
	Mask{56, 64, 61, 0x7fffffffffffff8},
	Mask{57, 64, 62, 0x7fffffffffffffc},
	Mask{58, 64, 63, 0x7fffffffffffffe},
	Mask{59, 64, 0, 0x7ffffffffffffff},
	Mask{1, 64, 5, 0x800000000000000},
	Mask{1, 32, 5, 0x800000008000000},
	Mask{1, 16, 5, 0x800080008000800},
	Mask{1, 8, 5, 0x808080808080808},
	Mask{2, 64, 6, 0xc00000000000000},
	Mask{2, 32, 6, 0xc0000000c000000},
	Mask{2, 16, 6, 0xc000c000c000c00},
	Mask{2, 8, 6, 0xc0c0c0c0c0c0c0c},
	Mask{3, 64, 7, 0xe00000000000000},
	Mask{3, 32, 7, 0xe0000000e000000},
	Mask{3, 16, 7, 0xe000e000e000e00},
	Mask{3, 8, 7, 0xe0e0e0e0e0e0e0e},
	Mask{4, 64, 8, 0xf00000000000000},
	Mask{4, 32, 8, 0xf0000000f000000},
	Mask{4, 16, 8, 0xf000f000f000f00},
	Mask{4, 8, 0, 0xf0f0f0f0f0f0f0f},
	Mask{5, 64, 9, 0xf80000000000000},
	Mask{5, 32, 9, 0xf8000000f800000},
	Mask{5, 16, 9, 0xf800f800f800f80},
	Mask{6, 64, 10, 0xfc0000000000000},
	Mask{6, 32, 10, 0xfc000000fc00000},
	Mask{6, 16, 10, 0xfc00fc00fc00fc0},
	Mask{7, 64, 11, 0xfe0000000000000},
	Mask{7, 32, 11, 0xfe000000fe00000},
	Mask{7, 16, 11, 0xfe00fe00fe00fe0},
	Mask{8, 64, 12, 0xff0000000000000},
	Mask{8, 32, 12, 0xff000000ff00000},
	Mask{8, 16, 12, 0xff00ff00ff00ff0},
	Mask{9, 64, 13, 0xff8000000000000},
	Mask{9, 32, 13, 0xff800000ff80000},
	Mask{9, 16, 13, 0xff80ff80ff80ff8},
	Mask{10, 64, 14, 0xffc000000000000},
	Mask{10, 32, 14, 0xffc00000ffc0000},
	Mask{10, 16, 14, 0xffc0ffc0ffc0ffc},
	Mask{11, 64, 15, 0xffe000000000000},
	Mask{11, 32, 15, 0xffe00000ffe0000},
	Mask{11, 16, 15, 0xffe0ffe0ffe0ffe},
	Mask{12, 64, 16, 0xfff000000000000},
	Mask{12, 32, 16, 0xfff00000fff0000},
	Mask{12, 16, 0, 0xfff0fff0fff0fff},
	Mask{13, 64, 17, 0xfff800000000000},
	Mask{13, 32, 17, 0xfff80000fff8000},
	Mask{14, 64, 18, 0xfffc00000000000},
	Mask{14, 32, 18, 0xfffc0000fffc000},
	Mask{15, 64, 19, 0xfffe00000000000},
	Mask{15, 32, 19, 0xfffe0000fffe000},
	Mask{16, 64, 20, 0xffff00000000000},
	Mask{16, 32, 20, 0xffff0000ffff000},
	Mask{17, 64, 21, 0xffff80000000000},
	Mask{17, 32, 21, 0xffff8000ffff800},
	Mask{18, 64, 22, 0xffffc0000000000},
	Mask{18, 32, 22, 0xffffc000ffffc00},
	Mask{19, 64, 23, 0xffffe0000000000},
	Mask{19, 32, 23, 0xffffe000ffffe00},
	Mask{20, 64, 24, 0xfffff0000000000},
	Mask{20, 32, 24, 0xfffff000fffff00},
	Mask{21, 64, 25, 0xfffff8000000000},
	Mask{21, 32, 25, 0xfffff800fffff80},
	Mask{22, 64, 26, 0xfffffc000000000},
	Mask{22, 32, 26, 0xfffffc00fffffc0},
	Mask{23, 64, 27, 0xfffffe000000000},
	Mask{23, 32, 27, 0xfffffe00fffffe0},
	Mask{24, 64, 28, 0xffffff000000000},
	Mask{24, 32, 28, 0xffffff00ffffff0},
	Mask{25, 64, 29, 0xffffff800000000},
	Mask{25, 32, 29, 0xffffff80ffffff8},
	Mask{26, 64, 30, 0xffffffc00000000},
	Mask{26, 32, 30, 0xffffffc0ffffffc},
	Mask{27, 64, 31, 0xffffffe00000000},
	Mask{27, 32, 31, 0xffffffe0ffffffe},
	Mask{28, 64, 32, 0xfffffff00000000},
	Mask{28, 32, 0, 0xfffffff0fffffff},
	Mask{29, 64, 33, 0xfffffff80000000},
	Mask{30, 64, 34, 0xfffffffc0000000},
	Mask{31, 64, 35, 0xfffffffe0000000},
	Mask{32, 64, 36, 0xffffffff0000000},
	Mask{33, 64, 37, 0xffffffff8000000},
	Mask{34, 64, 38, 0xffffffffc000000},
	Mask{35, 64, 39, 0xffffffffe000000},
	Mask{36, 64, 40, 0xfffffffff000000},
	Mask{37, 64, 41, 0xfffffffff800000},
	Mask{38, 64, 42, 0xfffffffffc00000},
	Mask{39, 64, 43, 0xfffffffffe00000},
	Mask{40, 64, 44, 0xffffffffff00000},
	Mask{41, 64, 45, 0xffffffffff80000},
	Mask{42, 64, 46, 0xffffffffffc0000},
	Mask{43, 64, 47, 0xffffffffffe0000},
	Mask{44, 64, 48, 0xfffffffffff0000},
	Mask{45, 64, 49, 0xfffffffffff8000},
	Mask{46, 64, 50, 0xfffffffffffc000},
	Mask{47, 64, 51, 0xfffffffffffe000},
	Mask{48, 64, 52, 0xffffffffffff000},
	Mask{49, 64, 53, 0xffffffffffff800},
	Mask{50, 64, 54, 0xffffffffffffc00},
	Mask{51, 64, 55, 0xffffffffffffe00},
	Mask{52, 64, 56, 0xfffffffffffff00},
	Mask{53, 64, 57, 0xfffffffffffff80},
	Mask{54, 64, 58, 0xfffffffffffffc0},
	Mask{55, 64, 59, 0xfffffffffffffe0},
	Mask{56, 64, 60, 0xffffffffffffff0},
	Mask{57, 64, 61, 0xffffffffffffff8},
	Mask{58, 64, 62, 0xffffffffffffffc},
	Mask{59, 64, 63, 0xffffffffffffffe},
	Mask{60, 64, 0, 0xfffffffffffffff},
	Mask{1, 64, 4, 0x1000000000000000},
	Mask{1, 32, 4, 0x1000000010000000},
	Mask{1, 16, 4, 0x1000100010001000},
	Mask{1, 8, 4, 0x1010101010101010},
	Mask{1, 4, 0, 0x1111111111111111},
	Mask{2, 64, 5, 0x1800000000000000},
	Mask{2, 32, 5, 0x1800000018000000},
	Mask{2, 16, 5, 0x1800180018001800},
	Mask{2, 8, 5, 0x1818181818181818},
	Mask{3, 64, 6, 0x1c00000000000000},
	Mask{3, 32, 6, 0x1c0000001c000000},
	Mask{3, 16, 6, 0x1c001c001c001c00},
	Mask{3, 8, 6, 0x1c1c1c1c1c1c1c1c},
	Mask{4, 64, 7, 0x1e00000000000000},
	Mask{4, 32, 7, 0x1e0000001e000000},
	Mask{4, 16, 7, 0x1e001e001e001e00},
	Mask{4, 8, 7, 0x1e1e1e1e1e1e1e1e},
	Mask{5, 64, 8, 0x1f00000000000000},
	Mask{5, 32, 8, 0x1f0000001f000000},
	Mask{5, 16, 8, 0x1f001f001f001f00},
	Mask{5, 8, 0, 0x1f1f1f1f1f1f1f1f},
	Mask{6, 64, 9, 0x1f80000000000000},
	Mask{6, 32, 9, 0x1f8000001f800000},
	Mask{6, 16, 9, 0x1f801f801f801f80},
	Mask{7, 64, 10, 0x1fc0000000000000},
	Mask{7, 32, 10, 0x1fc000001fc00000},
	Mask{7, 16, 10, 0x1fc01fc01fc01fc0},
	Mask{8, 64, 11, 0x1fe0000000000000},
	Mask{8, 32, 11, 0x1fe000001fe00000},
	Mask{8, 16, 11, 0x1fe01fe01fe01fe0},
	Mask{9, 64, 12, 0x1ff0000000000000},
	Mask{9, 32, 12, 0x1ff000001ff00000},
	Mask{9, 16, 12, 0x1ff01ff01ff01ff0},
	Mask{10, 64, 13, 0x1ff8000000000000},
	Mask{10, 32, 13, 0x1ff800001ff80000},
	Mask{10, 16, 13, 0x1ff81ff81ff81ff8},
	Mask{11, 64, 14, 0x1ffc000000000000},
	Mask{11, 32, 14, 0x1ffc00001ffc0000},
	Mask{11, 16, 14, 0x1ffc1ffc1ffc1ffc},
	Mask{12, 64, 15, 0x1ffe000000000000},
	Mask{12, 32, 15, 0x1ffe00001ffe0000},
	Mask{12, 16, 15, 0x1ffe1ffe1ffe1ffe},
	Mask{13, 64, 16, 0x1fff000000000000},
	Mask{13, 32, 16, 0x1fff00001fff0000},
	Mask{13, 16, 0, 0x1fff1fff1fff1fff},
	Mask{14, 64, 17, 0x1fff800000000000},
	Mask{14, 32, 17, 0x1fff80001fff8000},
	Mask{15, 64, 18, 0x1fffc00000000000},
	Mask{15, 32, 18, 0x1fffc0001fffc000},
	Mask{16, 64, 19, 0x1fffe00000000000},
	Mask{16, 32, 19, 0x1fffe0001fffe000},
	Mask{17, 64, 20, 0x1ffff00000000000},
	Mask{17, 32, 20, 0x1ffff0001ffff000},
	Mask{18, 64, 21, 0x1ffff80000000000},
	Mask{18, 32, 21, 0x1ffff8001ffff800},
	Mask{19, 64, 22, 0x1ffffc0000000000},
	Mask{19, 32, 22, 0x1ffffc001ffffc00},
	Mask{20, 64, 23, 0x1ffffe0000000000},
	Mask{20, 32, 23, 0x1ffffe001ffffe00},
	Mask{21, 64, 24, 0x1fffff0000000000},
	Mask{21, 32, 24, 0x1fffff001fffff00},
	Mask{22, 64, 25, 0x1fffff8000000000},
	Mask{22, 32, 25, 0x1fffff801fffff80},
	Mask{23, 64, 26, 0x1fffffc000000000},
	Mask{23, 32, 26, 0x1fffffc01fffffc0},
	Mask{24, 64, 27, 0x1fffffe000000000},
	Mask{24, 32, 27, 0x1fffffe01fffffe0},
	Mask{25, 64, 28, 0x1ffffff000000000},
	Mask{25, 32, 28, 0x1ffffff01ffffff0},
	Mask{26, 64, 29, 0x1ffffff800000000},
	Mask{26, 32, 29, 0x1ffffff81ffffff8},
	Mask{27, 64, 30, 0x1ffffffc00000000},
	Mask{27, 32, 30, 0x1ffffffc1ffffffc},
	Mask{28, 64, 31, 0x1ffffffe00000000},
	Mask{28, 32, 31, 0x1ffffffe1ffffffe},
	Mask{29, 64, 32, 0x1fffffff00000000},
	Mask{29, 32, 0, 0x1fffffff1fffffff},
	Mask{30, 64, 33, 0x1fffffff80000000},
	Mask{31, 64, 34, 0x1fffffffc0000000},
	Mask{32, 64, 35, 0x1fffffffe0000000},
	Mask{33, 64, 36, 0x1ffffffff0000000},
	Mask{34, 64, 37, 0x1ffffffff8000000},
	Mask{35, 64, 38, 0x1ffffffffc000000},
	Mask{36, 64, 39, 0x1ffffffffe000000},
	Mask{37, 64, 40, 0x1fffffffff000000},
	Mask{38, 64, 41, 0x1fffffffff800000},
	Mask{39, 64, 42, 0x1fffffffffc00000},
	Mask{40, 64, 43, 0x1fffffffffe00000},
	Mask{41, 64, 44, 0x1ffffffffff00000},
	Mask{42, 64, 45, 0x1ffffffffff80000},
	Mask{43, 64, 46, 0x1ffffffffffc0000},
	Mask{44, 64, 47, 0x1ffffffffffe0000},
	Mask{45, 64, 48, 0x1fffffffffff0000},
	Mask{46, 64, 49, 0x1fffffffffff8000},
	Mask{47, 64, 50, 0x1fffffffffffc000},
	Mask{48, 64, 51, 0x1fffffffffffe000},
	Mask{49, 64, 52, 0x1ffffffffffff000},
	Mask{50, 64, 53, 0x1ffffffffffff800},
	Mask{51, 64, 54, 0x1ffffffffffffc00},
	Mask{52, 64, 55, 0x1ffffffffffffe00},
	Mask{53, 64, 56, 0x1fffffffffffff00},
	Mask{54, 64, 57, 0x1fffffffffffff80},
	Mask{55, 64, 58, 0x1fffffffffffffc0},
	Mask{56, 64, 59, 0x1fffffffffffffe0},
	Mask{57, 64, 60, 0x1ffffffffffffff0},
	Mask{58, 64, 61, 0x1ffffffffffffff8},
	Mask{59, 64, 62, 0x1ffffffffffffffc},
	Mask{60, 64, 63, 0x1ffffffffffffffe},
	Mask{61, 64, 0, 0x1fffffffffffffff},
	Mask{1, 64, 3, 0x2000000000000000},
	Mask{1, 32, 3, 0x2000000020000000},
	Mask{1, 16, 3, 0x2000200020002000},
	Mask{1, 8, 3, 0x2020202020202020},
	Mask{1, 4, 3, 0x2222222222222222},
	Mask{2, 64, 4, 0x3000000000000000},
	Mask{2, 32, 4, 0x3000000030000000},
	Mask{2, 16, 4, 0x3000300030003000},
	Mask{2, 8, 4, 0x3030303030303030},
	Mask{2, 4, 0, 0x3333333333333333},
	Mask{3, 64, 5, 0x3800000000000000},
	Mask{3, 32, 5, 0x3800000038000000},
	Mask{3, 16, 5, 0x3800380038003800},
	Mask{3, 8, 5, 0x3838383838383838},
	Mask{4, 64, 6, 0x3c00000000000000},
	Mask{4, 32, 6, 0x3c0000003c000000},
	Mask{4, 16, 6, 0x3c003c003c003c00},
	Mask{4, 8, 6, 0x3c3c3c3c3c3c3c3c},
	Mask{5, 64, 7, 0x3e00000000000000},
	Mask{5, 32, 7, 0x3e0000003e000000},
	Mask{5, 16, 7, 0x3e003e003e003e00},
	Mask{5, 8, 7, 0x3e3e3e3e3e3e3e3e},
	Mask{6, 64, 8, 0x3f00000000000000},
	Mask{6, 32, 8, 0x3f0000003f000000},
	Mask{6, 16, 8, 0x3f003f003f003f00},
	Mask{6, 8, 0, 0x3f3f3f3f3f3f3f3f},
	Mask{7, 64, 9, 0x3f80000000000000},
	Mask{7, 32, 9, 0x3f8000003f800000},
	Mask{7, 16, 9, 0x3f803f803f803f80},
	Mask{8, 64, 10, 0x3fc0000000000000},
	Mask{8, 32, 10, 0x3fc000003fc00000},
	Mask{8, 16, 10, 0x3fc03fc03fc03fc0},
	Mask{9, 64, 11, 0x3fe0000000000000},
	Mask{9, 32, 11, 0x3fe000003fe00000},
	Mask{9, 16, 11, 0x3fe03fe03fe03fe0},
	Mask{10, 64, 12, 0x3ff0000000000000},
	Mask{10, 32, 12, 0x3ff000003ff00000},
	Mask{10, 16, 12, 0x3ff03ff03ff03ff0},
	Mask{11, 64, 13, 0x3ff8000000000000},
	Mask{11, 32, 13, 0x3ff800003ff80000},
	Mask{11, 16, 13, 0x3ff83ff83ff83ff8},
	Mask{12, 64, 14, 0x3ffc000000000000},
	Mask{12, 32, 14, 0x3ffc00003ffc0000},
	Mask{12, 16, 14, 0x3ffc3ffc3ffc3ffc},
	Mask{13, 64, 15, 0x3ffe000000000000},
	Mask{13, 32, 15, 0x3ffe00003ffe0000},
	Mask{13, 16, 15, 0x3ffe3ffe3ffe3ffe},
	Mask{14, 64, 16, 0x3fff000000000000},
	Mask{14, 32, 16, 0x3fff00003fff0000},
	Mask{14, 16, 0, 0x3fff3fff3fff3fff},
	Mask{15, 64, 17, 0x3fff800000000000},
	Mask{15, 32, 17, 0x3fff80003fff8000},
	Mask{16, 64, 18, 0x3fffc00000000000},
	Mask{16, 32, 18, 0x3fffc0003fffc000},
	Mask{17, 64, 19, 0x3fffe00000000000},
	Mask{17, 32, 19, 0x3fffe0003fffe000},
	Mask{18, 64, 20, 0x3ffff00000000000},
	Mask{18, 32, 20, 0x3ffff0003ffff000},
	Mask{19, 64, 21, 0x3ffff80000000000},
	Mask{19, 32, 21, 0x3ffff8003ffff800},
	Mask{20, 64, 22, 0x3ffffc0000000000},
	Mask{20, 32, 22, 0x3ffffc003ffffc00},
	Mask{21, 64, 23, 0x3ffffe0000000000},
	Mask{21, 32, 23, 0x3ffffe003ffffe00},
	Mask{22, 64, 24, 0x3fffff0000000000},
	Mask{22, 32, 24, 0x3fffff003fffff00},
	Mask{23, 64, 25, 0x3fffff8000000000},
	Mask{23, 32, 25, 0x3fffff803fffff80},
	Mask{24, 64, 26, 0x3fffffc000000000},
	Mask{24, 32, 26, 0x3fffffc03fffffc0},
	Mask{25, 64, 27, 0x3fffffe000000000},
	Mask{25, 32, 27, 0x3fffffe03fffffe0},
	Mask{26, 64, 28, 0x3ffffff000000000},
	Mask{26, 32, 28, 0x3ffffff03ffffff0},
	Mask{27, 64, 29, 0x3ffffff800000000},
	Mask{27, 32, 29, 0x3ffffff83ffffff8},
	Mask{28, 64, 30, 0x3ffffffc00000000},
	Mask{28, 32, 30, 0x3ffffffc3ffffffc},
	Mask{29, 64, 31, 0x3ffffffe00000000},
	Mask{29, 32, 31, 0x3ffffffe3ffffffe},
	Mask{30, 64, 32, 0x3fffffff00000000},
	Mask{30, 32, 0, 0x3fffffff3fffffff},
	Mask{31, 64, 33, 0x3fffffff80000000},
	Mask{32, 64, 34, 0x3fffffffc0000000},
	Mask{33, 64, 35, 0x3fffffffe0000000},
	Mask{34, 64, 36, 0x3ffffffff0000000},
	Mask{35, 64, 37, 0x3ffffffff8000000},
	Mask{36, 64, 38, 0x3ffffffffc000000},
	Mask{37, 64, 39, 0x3ffffffffe000000},
	Mask{38, 64, 40, 0x3fffffffff000000},
	Mask{39, 64, 41, 0x3fffffffff800000},
	Mask{40, 64, 42, 0x3fffffffffc00000},
	Mask{41, 64, 43, 0x3fffffffffe00000},
	Mask{42, 64, 44, 0x3ffffffffff00000},
	Mask{43, 64, 45, 0x3ffffffffff80000},
	Mask{44, 64, 46, 0x3ffffffffffc0000},
	Mask{45, 64, 47, 0x3ffffffffffe0000},
	Mask{46, 64, 48, 0x3fffffffffff0000},
	Mask{47, 64, 49, 0x3fffffffffff8000},
	Mask{48, 64, 50, 0x3fffffffffffc000},
	Mask{49, 64, 51, 0x3fffffffffffe000},
	Mask{50, 64, 52, 0x3ffffffffffff000},
	Mask{51, 64, 53, 0x3ffffffffffff800},
	Mask{52, 64, 54, 0x3ffffffffffffc00},
	Mask{53, 64, 55, 0x3ffffffffffffe00},
	Mask{54, 64, 56, 0x3fffffffffffff00},
	Mask{55, 64, 57, 0x3fffffffffffff80},
	Mask{56, 64, 58, 0x3fffffffffffffc0},
	Mask{57, 64, 59, 0x3fffffffffffffe0},
	Mask{58, 64, 60, 0x3ffffffffffffff0},
	Mask{59, 64, 61, 0x3ffffffffffffff8},
	Mask{60, 64, 62, 0x3ffffffffffffffc},
	Mask{61, 64, 63, 0x3ffffffffffffffe},
	Mask{62, 64, 0, 0x3fffffffffffffff},
	Mask{1, 64, 2, 0x4000000000000000},
	Mask{1, 32, 2, 0x4000000040000000},
	Mask{1, 16, 2, 0x4000400040004000},
	Mask{1, 8, 2, 0x4040404040404040},
	Mask{1, 4, 2, 0x4444444444444444},
	Mask{1, 2, 0, 0x5555555555555555},
	Mask{2, 64, 3, 0x6000000000000000},
	Mask{2, 32, 3, 0x6000000060000000},
	Mask{2, 16, 3, 0x6000600060006000},
	Mask{2, 8, 3, 0x6060606060606060},
	Mask{2, 4, 3, 0x6666666666666666},
	Mask{3, 64, 4, 0x7000000000000000},
	Mask{3, 32, 4, 0x7000000070000000},
	Mask{3, 16, 4, 0x7000700070007000},
	Mask{3, 8, 4, 0x7070707070707070},
	Mask{3, 4, 0, 0x7777777777777777},
	Mask{4, 64, 5, 0x7800000000000000},
	Mask{4, 32, 5, 0x7800000078000000},
	Mask{4, 16, 5, 0x7800780078007800},
	Mask{4, 8, 5, 0x7878787878787878},
	Mask{5, 64, 6, 0x7c00000000000000},
	Mask{5, 32, 6, 0x7c0000007c000000},
	Mask{5, 16, 6, 0x7c007c007c007c00},
	Mask{5, 8, 6, 0x7c7c7c7c7c7c7c7c},
	Mask{6, 64, 7, 0x7e00000000000000},
	Mask{6, 32, 7, 0x7e0000007e000000},
	Mask{6, 16, 7, 0x7e007e007e007e00},
	Mask{6, 8, 7, 0x7e7e7e7e7e7e7e7e},
	Mask{7, 64, 8, 0x7f00000000000000},
	Mask{7, 32, 8, 0x7f0000007f000000},
	Mask{7, 16, 8, 0x7f007f007f007f00},
	Mask{7, 8, 0, 0x7f7f7f7f7f7f7f7f},
	Mask{8, 64, 9, 0x7f80000000000000},
	Mask{8, 32, 9, 0x7f8000007f800000},
	Mask{8, 16, 9, 0x7f807f807f807f80},
	Mask{9, 64, 10, 0x7fc0000000000000},
	Mask{9, 32, 10, 0x7fc000007fc00000},
	Mask{9, 16, 10, 0x7fc07fc07fc07fc0},
	Mask{10, 64, 11, 0x7fe0000000000000},
	Mask{10, 32, 11, 0x7fe000007fe00000},
	Mask{10, 16, 11, 0x7fe07fe07fe07fe0},
	Mask{11, 64, 12, 0x7ff0000000000000},
	Mask{11, 32, 12, 0x7ff000007ff00000},
	Mask{11, 16, 12, 0x7ff07ff07ff07ff0},
	Mask{12, 64, 13, 0x7ff8000000000000},
	Mask{12, 32, 13, 0x7ff800007ff80000},
	Mask{12, 16, 13, 0x7ff87ff87ff87ff8},
	Mask{13, 64, 14, 0x7ffc000000000000},
	Mask{13, 32, 14, 0x7ffc00007ffc0000},
	Mask{13, 16, 14, 0x7ffc7ffc7ffc7ffc},
	Mask{14, 64, 15, 0x7ffe000000000000},
	Mask{14, 32, 15, 0x7ffe00007ffe0000},
	Mask{14, 16, 15, 0x7ffe7ffe7ffe7ffe},
	Mask{15, 64, 16, 0x7fff000000000000},
	Mask{15, 32, 16, 0x7fff00007fff0000},
	Mask{15, 16, 0, 0x7fff7fff7fff7fff},
	Mask{16, 64, 17, 0x7fff800000000000},
	Mask{16, 32, 17, 0x7fff80007fff8000},
	Mask{17, 64, 18, 0x7fffc00000000000},
	Mask{17, 32, 18, 0x7fffc0007fffc000},
	Mask{18, 64, 19, 0x7fffe00000000000},
	Mask{18, 32, 19, 0x7fffe0007fffe000},
	Mask{19, 64, 20, 0x7ffff00000000000},
	Mask{19, 32, 20, 0x7ffff0007ffff000},
	Mask{20, 64, 21, 0x7ffff80000000000},
	Mask{20, 32, 21, 0x7ffff8007ffff800},
	Mask{21, 64, 22, 0x7ffffc0000000000},
	Mask{21, 32, 22, 0x7ffffc007ffffc00},
	Mask{22, 64, 23, 0x7ffffe0000000000},
	Mask{22, 32, 23, 0x7ffffe007ffffe00},
	Mask{23, 64, 24, 0x7fffff0000000000},
	Mask{23, 32, 24, 0x7fffff007fffff00},
	Mask{24, 64, 25, 0x7fffff8000000000},
	Mask{24, 32, 25, 0x7fffff807fffff80},
	Mask{25, 64, 26, 0x7fffffc000000000},
	Mask{25, 32, 26, 0x7fffffc07fffffc0},
	Mask{26, 64, 27, 0x7fffffe000000000},
	Mask{26, 32, 27, 0x7fffffe07fffffe0},
	Mask{27, 64, 28, 0x7ffffff000000000},
	Mask{27, 32, 28, 0x7ffffff07ffffff0},
	Mask{28, 64, 29, 0x7ffffff800000000},
	Mask{28, 32, 29, 0x7ffffff87ffffff8},
	Mask{29, 64, 30, 0x7ffffffc00000000},
	Mask{29, 32, 30, 0x7ffffffc7ffffffc},
	Mask{30, 64, 31, 0x7ffffffe00000000},
	Mask{30, 32, 31, 0x7ffffffe7ffffffe},
	Mask{31, 64, 32, 0x7fffffff00000000},
	Mask{31, 32, 0, 0x7fffffff7fffffff},
	Mask{32, 64, 33, 0x7fffffff80000000},
	Mask{33, 64, 34, 0x7fffffffc0000000},
	Mask{34, 64, 35, 0x7fffffffe0000000},
	Mask{35, 64, 36, 0x7ffffffff0000000},
	Mask{36, 64, 37, 0x7ffffffff8000000},
	Mask{37, 64, 38, 0x7ffffffffc000000},
	Mask{38, 64, 39, 0x7ffffffffe000000},
	Mask{39, 64, 40, 0x7fffffffff000000},
	Mask{40, 64, 41, 0x7fffffffff800000},
	Mask{41, 64, 42, 0x7fffffffffc00000},
	Mask{42, 64, 43, 0x7fffffffffe00000},
	Mask{43, 64, 44, 0x7ffffffffff00000},
	Mask{44, 64, 45, 0x7ffffffffff80000},
	Mask{45, 64, 46, 0x7ffffffffffc0000},
	Mask{46, 64, 47, 0x7ffffffffffe0000},
	Mask{47, 64, 48, 0x7fffffffffff0000},
	Mask{48, 64, 49, 0x7fffffffffff8000},
	Mask{49, 64, 50, 0x7fffffffffffc000},
	Mask{50, 64, 51, 0x7fffffffffffe000},
	Mask{51, 64, 52, 0x7ffffffffffff000},
	Mask{52, 64, 53, 0x7ffffffffffff800},
	Mask{53, 64, 54, 0x7ffffffffffffc00},
	Mask{54, 64, 55, 0x7ffffffffffffe00},
	Mask{55, 64, 56, 0x7fffffffffffff00},
	Mask{56, 64, 57, 0x7fffffffffffff80},
	Mask{57, 64, 58, 0x7fffffffffffffc0},
	Mask{58, 64, 59, 0x7fffffffffffffe0},
	Mask{59, 64, 60, 0x7ffffffffffffff0},
	Mask{60, 64, 61, 0x7ffffffffffffff8},
	Mask{61, 64, 62, 0x7ffffffffffffffc},
	Mask{62, 64, 63, 0x7ffffffffffffffe},
	Mask{63, 64, 0, 0x7fffffffffffffff},
	Mask{1, 64, 1, 0x8000000000000000},
	Mask{2, 64, 1, 0x8000000000000001},
	Mask{3, 64, 1, 0x8000000000000003},
	Mask{4, 64, 1, 0x8000000000000007},
	Mask{5, 64, 1, 0x800000000000000f},
	Mask{6, 64, 1, 0x800000000000001f},
	Mask{7, 64, 1, 0x800000000000003f},
	Mask{8, 64, 1, 0x800000000000007f},
	Mask{9, 64, 1, 0x80000000000000ff},
	Mask{10, 64, 1, 0x80000000000001ff},
	Mask{11, 64, 1, 0x80000000000003ff},
	Mask{12, 64, 1, 0x80000000000007ff},
	Mask{13, 64, 1, 0x8000000000000fff},
	Mask{14, 64, 1, 0x8000000000001fff},
	Mask{15, 64, 1, 0x8000000000003fff},
	Mask{16, 64, 1, 0x8000000000007fff},
	Mask{17, 64, 1, 0x800000000000ffff},
	Mask{18, 64, 1, 0x800000000001ffff},
	Mask{19, 64, 1, 0x800000000003ffff},
	Mask{20, 64, 1, 0x800000000007ffff},
	Mask{21, 64, 1, 0x80000000000fffff},
	Mask{22, 64, 1, 0x80000000001fffff},
	Mask{23, 64, 1, 0x80000000003fffff},
	Mask{24, 64, 1, 0x80000000007fffff},
	Mask{25, 64, 1, 0x8000000000ffffff},
	Mask{26, 64, 1, 0x8000000001ffffff},
	Mask{27, 64, 1, 0x8000000003ffffff},
	Mask{28, 64, 1, 0x8000000007ffffff},
	Mask{29, 64, 1, 0x800000000fffffff},
	Mask{30, 64, 1, 0x800000001fffffff},
	Mask{31, 64, 1, 0x800000003fffffff},
	Mask{32, 64, 1, 0x800000007fffffff},
	Mask{1, 32, 1, 0x8000000080000000},
	Mask{33, 64, 1, 0x80000000ffffffff},
	Mask{2, 32, 1, 0x8000000180000001},
	Mask{34, 64, 1, 0x80000001ffffffff},
	Mask{3, 32, 1, 0x8000000380000003},
	Mask{35, 64, 1, 0x80000003ffffffff},
	Mask{4, 32, 1, 0x8000000780000007},
	Mask{36, 64, 1, 0x80000007ffffffff},
	Mask{5, 32, 1, 0x8000000f8000000f},
	Mask{37, 64, 1, 0x8000000fffffffff},
	Mask{6, 32, 1, 0x8000001f8000001f},
	Mask{38, 64, 1, 0x8000001fffffffff},
	Mask{7, 32, 1, 0x8000003f8000003f},
	Mask{39, 64, 1, 0x8000003fffffffff},
	Mask{8, 32, 1, 0x8000007f8000007f},
	Mask{40, 64, 1, 0x8000007fffffffff},
	Mask{9, 32, 1, 0x800000ff800000ff},
	Mask{41, 64, 1, 0x800000ffffffffff},
	Mask{10, 32, 1, 0x800001ff800001ff},
	Mask{42, 64, 1, 0x800001ffffffffff},
	Mask{11, 32, 1, 0x800003ff800003ff},
	Mask{43, 64, 1, 0x800003ffffffffff},
	Mask{12, 32, 1, 0x800007ff800007ff},
	Mask{44, 64, 1, 0x800007ffffffffff},
	Mask{13, 32, 1, 0x80000fff80000fff},
	Mask{45, 64, 1, 0x80000fffffffffff},
	Mask{14, 32, 1, 0x80001fff80001fff},
	Mask{46, 64, 1, 0x80001fffffffffff},
	Mask{15, 32, 1, 0x80003fff80003fff},
	Mask{47, 64, 1, 0x80003fffffffffff},
	Mask{16, 32, 1, 0x80007fff80007fff},
	Mask{48, 64, 1, 0x80007fffffffffff},
	Mask{1, 16, 1, 0x8000800080008000},
	Mask{17, 32, 1, 0x8000ffff8000ffff},
	Mask{49, 64, 1, 0x8000ffffffffffff},
	Mask{2, 16, 1, 0x8001800180018001},
	Mask{18, 32, 1, 0x8001ffff8001ffff},
	Mask{50, 64, 1, 0x8001ffffffffffff},
	Mask{3, 16, 1, 0x8003800380038003},
	Mask{19, 32, 1, 0x8003ffff8003ffff},
	Mask{51, 64, 1, 0x8003ffffffffffff},
	Mask{4, 16, 1, 0x8007800780078007},
	Mask{20, 32, 1, 0x8007ffff8007ffff},
	Mask{52, 64, 1, 0x8007ffffffffffff},
	Mask{5, 16, 1, 0x800f800f800f800f},
	Mask{21, 32, 1, 0x800fffff800fffff},
	Mask{53, 64, 1, 0x800fffffffffffff},
	Mask{6, 16, 1, 0x801f801f801f801f},
	Mask{22, 32, 1, 0x801fffff801fffff},
	Mask{54, 64, 1, 0x801fffffffffffff},
	Mask{7, 16, 1, 0x803f803f803f803f},
	Mask{23, 32, 1, 0x803fffff803fffff},
	Mask{55, 64, 1, 0x803fffffffffffff},
	Mask{8, 16, 1, 0x807f807f807f807f},
	Mask{24, 32, 1, 0x807fffff807fffff},
	Mask{56, 64, 1, 0x807fffffffffffff},
	Mask{1, 8, 1, 0x8080808080808080},
	Mask{9, 16, 1, 0x80ff80ff80ff80ff},
	Mask{25, 32, 1, 0x80ffffff80ffffff},
	Mask{57, 64, 1, 0x80ffffffffffffff},
	Mask{2, 8, 1, 0x8181818181818181},
	Mask{10, 16, 1, 0x81ff81ff81ff81ff},
	Mask{26, 32, 1, 0x81ffffff81ffffff},
	Mask{58, 64, 1, 0x81ffffffffffffff},
	Mask{3, 8, 1, 0x8383838383838383},
	Mask{11, 16, 1, 0x83ff83ff83ff83ff},
	Mask{27, 32, 1, 0x83ffffff83ffffff},
	Mask{59, 64, 1, 0x83ffffffffffffff},
	Mask{4, 8, 1, 0x8787878787878787},
	Mask{12, 16, 1, 0x87ff87ff87ff87ff},
	Mask{28, 32, 1, 0x87ffffff87ffffff},
	Mask{60, 64, 1, 0x87ffffffffffffff},
	Mask{1, 4, 1, 0x8888888888888888},
	Mask{5, 8, 1, 0x8f8f8f8f8f8f8f8f},
	Mask{13, 16, 1, 0x8fff8fff8fff8fff},
	Mask{29, 32, 1, 0x8fffffff8fffffff},
	Mask{61, 64, 1, 0x8fffffffffffffff},
	Mask{2, 4, 1, 0x9999999999999999},
	Mask{6, 8, 1, 0x9f9f9f9f9f9f9f9f},
	Mask{14, 16, 1, 0x9fff9fff9fff9fff},
	Mask{30, 32, 1, 0x9fffffff9fffffff},
	Mask{62, 64, 1, 0x9fffffffffffffff},
	Mask{1, 2, 1, 0xaaaaaaaaaaaaaaaa},
	Mask{3, 4, 1, 0xbbbbbbbbbbbbbbbb},
	Mask{7, 8, 1, 0xbfbfbfbfbfbfbfbf},
	Mask{15, 16, 1, 0xbfffbfffbfffbfff},
	Mask{31, 32, 1, 0xbfffffffbfffffff},
	Mask{63, 64, 1, 0xbfffffffffffffff},
	Mask{2, 64, 2, 0xc000000000000000},
	Mask{3, 64, 2, 0xc000000000000001},
	Mask{4, 64, 2, 0xc000000000000003},
	Mask{5, 64, 2, 0xc000000000000007},
	Mask{6, 64, 2, 0xc00000000000000f},
	Mask{7, 64, 2, 0xc00000000000001f},
	Mask{8, 64, 2, 0xc00000000000003f},
	Mask{9, 64, 2, 0xc00000000000007f},
	Mask{10, 64, 2, 0xc0000000000000ff},
	Mask{11, 64, 2, 0xc0000000000001ff},
	Mask{12, 64, 2, 0xc0000000000003ff},
	Mask{13, 64, 2, 0xc0000000000007ff},
	Mask{14, 64, 2, 0xc000000000000fff},
	Mask{15, 64, 2, 0xc000000000001fff},
	Mask{16, 64, 2, 0xc000000000003fff},
	Mask{17, 64, 2, 0xc000000000007fff},
	Mask{18, 64, 2, 0xc00000000000ffff},
	Mask{19, 64, 2, 0xc00000000001ffff},
	Mask{20, 64, 2, 0xc00000000003ffff},
	Mask{21, 64, 2, 0xc00000000007ffff},
	Mask{22, 64, 2, 0xc0000000000fffff},
	Mask{23, 64, 2, 0xc0000000001fffff},
	Mask{24, 64, 2, 0xc0000000003fffff},
	Mask{25, 64, 2, 0xc0000000007fffff},
	Mask{26, 64, 2, 0xc000000000ffffff},
	Mask{27, 64, 2, 0xc000000001ffffff},
	Mask{28, 64, 2, 0xc000000003ffffff},
	Mask{29, 64, 2, 0xc000000007ffffff},
	Mask{30, 64, 2, 0xc00000000fffffff},
	Mask{31, 64, 2, 0xc00000001fffffff},
	Mask{32, 64, 2, 0xc00000003fffffff},
	Mask{33, 64, 2, 0xc00000007fffffff},
	Mask{2, 32, 2, 0xc0000000c0000000},
	Mask{34, 64, 2, 0xc0000000ffffffff},
	Mask{3, 32, 2, 0xc0000001c0000001},
	Mask{35, 64, 2, 0xc0000001ffffffff},
	Mask{4, 32, 2, 0xc0000003c0000003},
	Mask{36, 64, 2, 0xc0000003ffffffff},
	Mask{5, 32, 2, 0xc0000007c0000007},
	Mask{37, 64, 2, 0xc0000007ffffffff},
	Mask{6, 32, 2, 0xc000000fc000000f},
	Mask{38, 64, 2, 0xc000000fffffffff},
	Mask{7, 32, 2, 0xc000001fc000001f},
	Mask{39, 64, 2, 0xc000001fffffffff},
	Mask{8, 32, 2, 0xc000003fc000003f},
	Mask{40, 64, 2, 0xc000003fffffffff},
	Mask{9, 32, 2, 0xc000007fc000007f},
	Mask{41, 64, 2, 0xc000007fffffffff},
	Mask{10, 32, 2, 0xc00000ffc00000ff},
	Mask{42, 64, 2, 0xc00000ffffffffff},
	Mask{11, 32, 2, 0xc00001ffc00001ff},
	Mask{43, 64, 2, 0xc00001ffffffffff},
	Mask{12, 32, 2, 0xc00003ffc00003ff},
	Mask{44, 64, 2, 0xc00003ffffffffff},
	Mask{13, 32, 2, 0xc00007ffc00007ff},
	Mask{45, 64, 2, 0xc00007ffffffffff},
	Mask{14, 32, 2, 0xc0000fffc0000fff},
	Mask{46, 64, 2, 0xc0000fffffffffff},
	Mask{15, 32, 2, 0xc0001fffc0001fff},
	Mask{47, 64, 2, 0xc0001fffffffffff},
	Mask{16, 32, 2, 0xc0003fffc0003fff},
	Mask{48, 64, 2, 0xc0003fffffffffff},
	Mask{17, 32, 2, 0xc0007fffc0007fff},
	Mask{49, 64, 2, 0xc0007fffffffffff},
	Mask{2, 16, 2, 0xc000c000c000c000},
	Mask{18, 32, 2, 0xc000ffffc000ffff},
	Mask{50, 64, 2, 0xc000ffffffffffff},
	Mask{3, 16, 2, 0xc001c001c001c001},
	Mask{19, 32, 2, 0xc001ffffc001ffff},
	Mask{51, 64, 2, 0xc001ffffffffffff},
	Mask{4, 16, 2, 0xc003c003c003c003},
	Mask{20, 32, 2, 0xc003ffffc003ffff},
	Mask{52, 64, 2, 0xc003ffffffffffff},
	Mask{5, 16, 2, 0xc007c007c007c007},
	Mask{21, 32, 2, 0xc007ffffc007ffff},
	Mask{53, 64, 2, 0xc007ffffffffffff},
	Mask{6, 16, 2, 0xc00fc00fc00fc00f},
	Mask{22, 32, 2, 0xc00fffffc00fffff},
	Mask{54, 64, 2, 0xc00fffffffffffff},
	Mask{7, 16, 2, 0xc01fc01fc01fc01f},
	Mask{23, 32, 2, 0xc01fffffc01fffff},
	Mask{55, 64, 2, 0xc01fffffffffffff},
	Mask{8, 16, 2, 0xc03fc03fc03fc03f},
	Mask{24, 32, 2, 0xc03fffffc03fffff},
	Mask{56, 64, 2, 0xc03fffffffffffff},
	Mask{9, 16, 2, 0xc07fc07fc07fc07f},
	Mask{25, 32, 2, 0xc07fffffc07fffff},
	Mask{57, 64, 2, 0xc07fffffffffffff},
	Mask{2, 8, 2, 0xc0c0c0c0c0c0c0c0},
	Mask{10, 16, 2, 0xc0ffc0ffc0ffc0ff},
	Mask{26, 32, 2, 0xc0ffffffc0ffffff},
	Mask{58, 64, 2, 0xc0ffffffffffffff},
	Mask{3, 8, 2, 0xc1c1c1c1c1c1c1c1},
	Mask{11, 16, 2, 0xc1ffc1ffc1ffc1ff},
	Mask{27, 32, 2, 0xc1ffffffc1ffffff},
	Mask{59, 64, 2, 0xc1ffffffffffffff},
	Mask{4, 8, 2, 0xc3c3c3c3c3c3c3c3},
	Mask{12, 16, 2, 0xc3ffc3ffc3ffc3ff},
	Mask{28, 32, 2, 0xc3ffffffc3ffffff},
	Mask{60, 64, 2, 0xc3ffffffffffffff},
	Mask{5, 8, 2, 0xc7c7c7c7c7c7c7c7},
	Mask{13, 16, 2, 0xc7ffc7ffc7ffc7ff},
	Mask{29, 32, 2, 0xc7ffffffc7ffffff},
	Mask{61, 64, 2, 0xc7ffffffffffffff},
	Mask{2, 4, 2, 0xcccccccccccccccc},
	Mask{6, 8, 2, 0xcfcfcfcfcfcfcfcf},
	Mask{14, 16, 2, 0xcfffcfffcfffcfff},
	Mask{30, 32, 2, 0xcfffffffcfffffff},
	Mask{62, 64, 2, 0xcfffffffffffffff},
	Mask{3, 4, 2, 0xdddddddddddddddd},
	Mask{7, 8, 2, 0xdfdfdfdfdfdfdfdf},
	Mask{15, 16, 2, 0xdfffdfffdfffdfff},
	Mask{31, 32, 2, 0xdfffffffdfffffff},
	Mask{63, 64, 2, 0xdfffffffffffffff},
	Mask{3, 64, 3, 0xe000000000000000},
	Mask{4, 64, 3, 0xe000000000000001},
	Mask{5, 64, 3, 0xe000000000000003},
	Mask{6, 64, 3, 0xe000000000000007},
	Mask{7, 64, 3, 0xe00000000000000f},
	Mask{8, 64, 3, 0xe00000000000001f},
	Mask{9, 64, 3, 0xe00000000000003f},
	Mask{10, 64, 3, 0xe00000000000007f},
	Mask{11, 64, 3, 0xe0000000000000ff},
	Mask{12, 64, 3, 0xe0000000000001ff},
	Mask{13, 64, 3, 0xe0000000000003ff},
	Mask{14, 64, 3, 0xe0000000000007ff},
	Mask{15, 64, 3, 0xe000000000000fff},
	Mask{16, 64, 3, 0xe000000000001fff},
	Mask{17, 64, 3, 0xe000000000003fff},
	Mask{18, 64, 3, 0xe000000000007fff},
	Mask{19, 64, 3, 0xe00000000000ffff},
	Mask{20, 64, 3, 0xe00000000001ffff},
	Mask{21, 64, 3, 0xe00000000003ffff},
	Mask{22, 64, 3, 0xe00000000007ffff},
	Mask{23, 64, 3, 0xe0000000000fffff},
	Mask{24, 64, 3, 0xe0000000001fffff},
	Mask{25, 64, 3, 0xe0000000003fffff},
	Mask{26, 64, 3, 0xe0000000007fffff},
	Mask{27, 64, 3, 0xe000000000ffffff},
	Mask{28, 64, 3, 0xe000000001ffffff},
	Mask{29, 64, 3, 0xe000000003ffffff},
	Mask{30, 64, 3, 0xe000000007ffffff},
	Mask{31, 64, 3, 0xe00000000fffffff},
	Mask{32, 64, 3, 0xe00000001fffffff},
	Mask{33, 64, 3, 0xe00000003fffffff},
	Mask{34, 64, 3, 0xe00000007fffffff},
	Mask{3, 32, 3, 0xe0000000e0000000},
	Mask{35, 64, 3, 0xe0000000ffffffff},
	Mask{4, 32, 3, 0xe0000001e0000001},
	Mask{36, 64, 3, 0xe0000001ffffffff},
	Mask{5, 32, 3, 0xe0000003e0000003},
	Mask{37, 64, 3, 0xe0000003ffffffff},
	Mask{6, 32, 3, 0xe0000007e0000007},
	Mask{38, 64, 3, 0xe0000007ffffffff},
	Mask{7, 32, 3, 0xe000000fe000000f},
	Mask{39, 64, 3, 0xe000000fffffffff},
	Mask{8, 32, 3, 0xe000001fe000001f},
	Mask{40, 64, 3, 0xe000001fffffffff},
	Mask{9, 32, 3, 0xe000003fe000003f},
	Mask{41, 64, 3, 0xe000003fffffffff},
	Mask{10, 32, 3, 0xe000007fe000007f},
	Mask{42, 64, 3, 0xe000007fffffffff},
	Mask{11, 32, 3, 0xe00000ffe00000ff},
	Mask{43, 64, 3, 0xe00000ffffffffff},
	Mask{12, 32, 3, 0xe00001ffe00001ff},
	Mask{44, 64, 3, 0xe00001ffffffffff},
	Mask{13, 32, 3, 0xe00003ffe00003ff},
	Mask{45, 64, 3, 0xe00003ffffffffff},
	Mask{14, 32, 3, 0xe00007ffe00007ff},
	Mask{46, 64, 3, 0xe00007ffffffffff},
	Mask{15, 32, 3, 0xe0000fffe0000fff},
	Mask{47, 64, 3, 0xe0000fffffffffff},
	Mask{16, 32, 3, 0xe0001fffe0001fff},
	Mask{48, 64, 3, 0xe0001fffffffffff},
	Mask{17, 32, 3, 0xe0003fffe0003fff},
	Mask{49, 64, 3, 0xe0003fffffffffff},
	Mask{18, 32, 3, 0xe0007fffe0007fff},
	Mask{50, 64, 3, 0xe0007fffffffffff},
	Mask{3, 16, 3, 0xe000e000e000e000},
	Mask{19, 32, 3, 0xe000ffffe000ffff},
	Mask{51, 64, 3, 0xe000ffffffffffff},
	Mask{4, 16, 3, 0xe001e001e001e001},
	Mask{20, 32, 3, 0xe001ffffe001ffff},
	Mask{52, 64, 3, 0xe001ffffffffffff},
	Mask{5, 16, 3, 0xe003e003e003e003},
	Mask{21, 32, 3, 0xe003ffffe003ffff},
	Mask{53, 64, 3, 0xe003ffffffffffff},
	Mask{6, 16, 3, 0xe007e007e007e007},
	Mask{22, 32, 3, 0xe007ffffe007ffff},
	Mask{54, 64, 3, 0xe007ffffffffffff},
	Mask{7, 16, 3, 0xe00fe00fe00fe00f},
	Mask{23, 32, 3, 0xe00fffffe00fffff},
	Mask{55, 64, 3, 0xe00fffffffffffff},
	Mask{8, 16, 3, 0xe01fe01fe01fe01f},
	Mask{24, 32, 3, 0xe01fffffe01fffff},
	Mask{56, 64, 3, 0xe01fffffffffffff},
	Mask{9, 16, 3, 0xe03fe03fe03fe03f},
	Mask{25, 32, 3, 0xe03fffffe03fffff},
	Mask{57, 64, 3, 0xe03fffffffffffff},
	Mask{10, 16, 3, 0xe07fe07fe07fe07f},
	Mask{26, 32, 3, 0xe07fffffe07fffff},
	Mask{58, 64, 3, 0xe07fffffffffffff},
	Mask{3, 8, 3, 0xe0e0e0e0e0e0e0e0},
	Mask{11, 16, 3, 0xe0ffe0ffe0ffe0ff},
	Mask{27, 32, 3, 0xe0ffffffe0ffffff},
	Mask{59, 64, 3, 0xe0ffffffffffffff},
	Mask{4, 8, 3, 0xe1e1e1e1e1e1e1e1},
	Mask{12, 16, 3, 0xe1ffe1ffe1ffe1ff},
	Mask{28, 32, 3, 0xe1ffffffe1ffffff},
	Mask{60, 64, 3, 0xe1ffffffffffffff},
	Mask{5, 8, 3, 0xe3e3e3e3e3e3e3e3},
	Mask{13, 16, 3, 0xe3ffe3ffe3ffe3ff},
	Mask{29, 32, 3, 0xe3ffffffe3ffffff},
	Mask{61, 64, 3, 0xe3ffffffffffffff},
	Mask{6, 8, 3, 0xe7e7e7e7e7e7e7e7},
	Mask{14, 16, 3, 0xe7ffe7ffe7ffe7ff},
	Mask{30, 32, 3, 0xe7ffffffe7ffffff},
	Mask{62, 64, 3, 0xe7ffffffffffffff},
	Mask{3, 4, 3, 0xeeeeeeeeeeeeeeee},
	Mask{7, 8, 3, 0xefefefefefefefef},
	Mask{15, 16, 3, 0xefffefffefffefff},
	Mask{31, 32, 3, 0xefffffffefffffff},
	Mask{63, 64, 3, 0xefffffffffffffff},
	Mask{4, 64, 4, 0xf000000000000000},
	Mask{5, 64, 4, 0xf000000000000001},
	Mask{6, 64, 4, 0xf000000000000003},
	Mask{7, 64, 4, 0xf000000000000007},
	Mask{8, 64, 4, 0xf00000000000000f},
	Mask{9, 64, 4, 0xf00000000000001f},
	Mask{10, 64, 4, 0xf00000000000003f},
	Mask{11, 64, 4, 0xf00000000000007f},
	Mask{12, 64, 4, 0xf0000000000000ff},
	Mask{13, 64, 4, 0xf0000000000001ff},
	Mask{14, 64, 4, 0xf0000000000003ff},
	Mask{15, 64, 4, 0xf0000000000007ff},
	Mask{16, 64, 4, 0xf000000000000fff},
	Mask{17, 64, 4, 0xf000000000001fff},
	Mask{18, 64, 4, 0xf000000000003fff},
	Mask{19, 64, 4, 0xf000000000007fff},
	Mask{20, 64, 4, 0xf00000000000ffff},
	Mask{21, 64, 4, 0xf00000000001ffff},
	Mask{22, 64, 4, 0xf00000000003ffff},
	Mask{23, 64, 4, 0xf00000000007ffff},
	Mask{24, 64, 4, 0xf0000000000fffff},
	Mask{25, 64, 4, 0xf0000000001fffff},
	Mask{26, 64, 4, 0xf0000000003fffff},
	Mask{27, 64, 4, 0xf0000000007fffff},
	Mask{28, 64, 4, 0xf000000000ffffff},
	Mask{29, 64, 4, 0xf000000001ffffff},
	Mask{30, 64, 4, 0xf000000003ffffff},
	Mask{31, 64, 4, 0xf000000007ffffff},
	Mask{32, 64, 4, 0xf00000000fffffff},
	Mask{33, 64, 4, 0xf00000001fffffff},
	Mask{34, 64, 4, 0xf00000003fffffff},
	Mask{35, 64, 4, 0xf00000007fffffff},
	Mask{4, 32, 4, 0xf0000000f0000000},
	Mask{36, 64, 4, 0xf0000000ffffffff},
	Mask{5, 32, 4, 0xf0000001f0000001},
	Mask{37, 64, 4, 0xf0000001ffffffff},
	Mask{6, 32, 4, 0xf0000003f0000003},
	Mask{38, 64, 4, 0xf0000003ffffffff},
	Mask{7, 32, 4, 0xf0000007f0000007},
	Mask{39, 64, 4, 0xf0000007ffffffff},
	Mask{8, 32, 4, 0xf000000ff000000f},
	Mask{40, 64, 4, 0xf000000fffffffff},
	Mask{9, 32, 4, 0xf000001ff000001f},
	Mask{41, 64, 4, 0xf000001fffffffff},
	Mask{10, 32, 4, 0xf000003ff000003f},
	Mask{42, 64, 4, 0xf000003fffffffff},
	Mask{11, 32, 4, 0xf000007ff000007f},
	Mask{43, 64, 4, 0xf000007fffffffff},
	Mask{12, 32, 4, 0xf00000fff00000ff},
	Mask{44, 64, 4, 0xf00000ffffffffff},
	Mask{13, 32, 4, 0xf00001fff00001ff},
	Mask{45, 64, 4, 0xf00001ffffffffff},
	Mask{14, 32, 4, 0xf00003fff00003ff},
	Mask{46, 64, 4, 0xf00003ffffffffff},
	Mask{15, 32, 4, 0xf00007fff00007ff},
	Mask{47, 64, 4, 0xf00007ffffffffff},
	Mask{16, 32, 4, 0xf0000ffff0000fff},
	Mask{48, 64, 4, 0xf0000fffffffffff},
	Mask{17, 32, 4, 0xf0001ffff0001fff},
	Mask{49, 64, 4, 0xf0001fffffffffff},
	Mask{18, 32, 4, 0xf0003ffff0003fff},
	Mask{50, 64, 4, 0xf0003fffffffffff},
	Mask{19, 32, 4, 0xf0007ffff0007fff},
	Mask{51, 64, 4, 0xf0007fffffffffff},
	Mask{4, 16, 4, 0xf000f000f000f000},
	Mask{20, 32, 4, 0xf000fffff000ffff},
	Mask{52, 64, 4, 0xf000ffffffffffff},
	Mask{5, 16, 4, 0xf001f001f001f001},
	Mask{21, 32, 4, 0xf001fffff001ffff},
	Mask{53, 64, 4, 0xf001ffffffffffff},
	Mask{6, 16, 4, 0xf003f003f003f003},
	Mask{22, 32, 4, 0xf003fffff003ffff},
	Mask{54, 64, 4, 0xf003ffffffffffff},
	Mask{7, 16, 4, 0xf007f007f007f007},
	Mask{23, 32, 4, 0xf007fffff007ffff},
	Mask{55, 64, 4, 0xf007ffffffffffff},
	Mask{8, 16, 4, 0xf00ff00ff00ff00f},
	Mask{24, 32, 4, 0xf00ffffff00fffff},
	Mask{56, 64, 4, 0xf00fffffffffffff},
	Mask{9, 16, 4, 0xf01ff01ff01ff01f},
	Mask{25, 32, 4, 0xf01ffffff01fffff},
	Mask{57, 64, 4, 0xf01fffffffffffff},
	Mask{10, 16, 4, 0xf03ff03ff03ff03f},
	Mask{26, 32, 4, 0xf03ffffff03fffff},
	Mask{58, 64, 4, 0xf03fffffffffffff},
	Mask{11, 16, 4, 0xf07ff07ff07ff07f},
	Mask{27, 32, 4, 0xf07ffffff07fffff},
	Mask{59, 64, 4, 0xf07fffffffffffff},
	Mask{4, 8, 4, 0xf0f0f0f0f0f0f0f0},
	Mask{12, 16, 4, 0xf0fff0fff0fff0ff},
	Mask{28, 32, 4, 0xf0fffffff0ffffff},
	Mask{60, 64, 4, 0xf0ffffffffffffff},
	Mask{5, 8, 4, 0xf1f1f1f1f1f1f1f1},
	Mask{13, 16, 4, 0xf1fff1fff1fff1ff},
	Mask{29, 32, 4, 0xf1fffffff1ffffff},
	Mask{61, 64, 4, 0xf1ffffffffffffff},
	Mask{6, 8, 4, 0xf3f3f3f3f3f3f3f3},
	Mask{14, 16, 4, 0xf3fff3fff3fff3ff},
	Mask{30, 32, 4, 0xf3fffffff3ffffff},
	Mask{62, 64, 4, 0xf3ffffffffffffff},
	Mask{7, 8, 4, 0xf7f7f7f7f7f7f7f7},
	Mask{15, 16, 4, 0xf7fff7fff7fff7ff},
	Mask{31, 32, 4, 0xf7fffffff7ffffff},
	Mask{63, 64, 4, 0xf7ffffffffffffff},
	Mask{5, 64, 5, 0xf800000000000000},
	Mask{6, 64, 5, 0xf800000000000001},
	Mask{7, 64, 5, 0xf800000000000003},
	Mask{8, 64, 5, 0xf800000000000007},
	Mask{9, 64, 5, 0xf80000000000000f},
	Mask{10, 64, 5, 0xf80000000000001f},
	Mask{11, 64, 5, 0xf80000000000003f},
	Mask{12, 64, 5, 0xf80000000000007f},
	Mask{13, 64, 5, 0xf8000000000000ff},
	Mask{14, 64, 5, 0xf8000000000001ff},
	Mask{15, 64, 5, 0xf8000000000003ff},
	Mask{16, 64, 5, 0xf8000000000007ff},
	Mask{17, 64, 5, 0xf800000000000fff},
	Mask{18, 64, 5, 0xf800000000001fff},
	Mask{19, 64, 5, 0xf800000000003fff},
	Mask{20, 64, 5, 0xf800000000007fff},
	Mask{21, 64, 5, 0xf80000000000ffff},
	Mask{22, 64, 5, 0xf80000000001ffff},
	Mask{23, 64, 5, 0xf80000000003ffff},
	Mask{24, 64, 5, 0xf80000000007ffff},
	Mask{25, 64, 5, 0xf8000000000fffff},
	Mask{26, 64, 5, 0xf8000000001fffff},
	Mask{27, 64, 5, 0xf8000000003fffff},
	Mask{28, 64, 5, 0xf8000000007fffff},
	Mask{29, 64, 5, 0xf800000000ffffff},
	Mask{30, 64, 5, 0xf800000001ffffff},
	Mask{31, 64, 5, 0xf800000003ffffff},
	Mask{32, 64, 5, 0xf800000007ffffff},
	Mask{33, 64, 5, 0xf80000000fffffff},
	Mask{34, 64, 5, 0xf80000001fffffff},
	Mask{35, 64, 5, 0xf80000003fffffff},
	Mask{36, 64, 5, 0xf80000007fffffff},
	Mask{5, 32, 5, 0xf8000000f8000000},
	Mask{37, 64, 5, 0xf8000000ffffffff},
	Mask{6, 32, 5, 0xf8000001f8000001},
	Mask{38, 64, 5, 0xf8000001ffffffff},
	Mask{7, 32, 5, 0xf8000003f8000003},
	Mask{39, 64, 5, 0xf8000003ffffffff},
	Mask{8, 32, 5, 0xf8000007f8000007},
	Mask{40, 64, 5, 0xf8000007ffffffff},
	Mask{9, 32, 5, 0xf800000ff800000f},
	Mask{41, 64, 5, 0xf800000fffffffff},
	Mask{10, 32, 5, 0xf800001ff800001f},
	Mask{42, 64, 5, 0xf800001fffffffff},
	Mask{11, 32, 5, 0xf800003ff800003f},
	Mask{43, 64, 5, 0xf800003fffffffff},
	Mask{12, 32, 5, 0xf800007ff800007f},
	Mask{44, 64, 5, 0xf800007fffffffff},
	Mask{13, 32, 5, 0xf80000fff80000ff},
	Mask{45, 64, 5, 0xf80000ffffffffff},
	Mask{14, 32, 5, 0xf80001fff80001ff},
	Mask{46, 64, 5, 0xf80001ffffffffff},
	Mask{15, 32, 5, 0xf80003fff80003ff},
	Mask{47, 64, 5, 0xf80003ffffffffff},
	Mask{16, 32, 5, 0xf80007fff80007ff},
	Mask{48, 64, 5, 0xf80007ffffffffff},
	Mask{17, 32, 5, 0xf8000ffff8000fff},
	Mask{49, 64, 5, 0xf8000fffffffffff},
	Mask{18, 32, 5, 0xf8001ffff8001fff},
	Mask{50, 64, 5, 0xf8001fffffffffff},
	Mask{19, 32, 5, 0xf8003ffff8003fff},
	Mask{51, 64, 5, 0xf8003fffffffffff},
	Mask{20, 32, 5, 0xf8007ffff8007fff},
	Mask{52, 64, 5, 0xf8007fffffffffff},
	Mask{5, 16, 5, 0xf800f800f800f800},
	Mask{21, 32, 5, 0xf800fffff800ffff},
	Mask{53, 64, 5, 0xf800ffffffffffff},
	Mask{6, 16, 5, 0xf801f801f801f801},
	Mask{22, 32, 5, 0xf801fffff801ffff},
	Mask{54, 64, 5, 0xf801ffffffffffff},
	Mask{7, 16, 5, 0xf803f803f803f803},
	Mask{23, 32, 5, 0xf803fffff803ffff},
	Mask{55, 64, 5, 0xf803ffffffffffff},
	Mask{8, 16, 5, 0xf807f807f807f807},
	Mask{24, 32, 5, 0xf807fffff807ffff},
	Mask{56, 64, 5, 0xf807ffffffffffff},
	Mask{9, 16, 5, 0xf80ff80ff80ff80f},
	Mask{25, 32, 5, 0xf80ffffff80fffff},
	Mask{57, 64, 5, 0xf80fffffffffffff},
	Mask{10, 16, 5, 0xf81ff81ff81ff81f},
	Mask{26, 32, 5, 0xf81ffffff81fffff},
	Mask{58, 64, 5, 0xf81fffffffffffff},
	Mask{11, 16, 5, 0xf83ff83ff83ff83f},
	Mask{27, 32, 5, 0xf83ffffff83fffff},
	Mask{59, 64, 5, 0xf83fffffffffffff},
	Mask{12, 16, 5, 0xf87ff87ff87ff87f},
	Mask{28, 32, 5, 0xf87ffffff87fffff},
	Mask{60, 64, 5, 0xf87fffffffffffff},
	Mask{5, 8, 5, 0xf8f8f8f8f8f8f8f8},
	Mask{13, 16, 5, 0xf8fff8fff8fff8ff},
	Mask{29, 32, 5, 0xf8fffffff8ffffff},
	Mask{61, 64, 5, 0xf8ffffffffffffff},
	Mask{6, 8, 5, 0xf9f9f9f9f9f9f9f9},
	Mask{14, 16, 5, 0xf9fff9fff9fff9ff},
	Mask{30, 32, 5, 0xf9fffffff9ffffff},
	Mask{62, 64, 5, 0xf9ffffffffffffff},
	Mask{7, 8, 5, 0xfbfbfbfbfbfbfbfb},
	Mask{15, 16, 5, 0xfbfffbfffbfffbff},
	Mask{31, 32, 5, 0xfbfffffffbffffff},
	Mask{63, 64, 5, 0xfbffffffffffffff},
	Mask{6, 64, 6, 0xfc00000000000000},
	Mask{7, 64, 6, 0xfc00000000000001},
	Mask{8, 64, 6, 0xfc00000000000003},
	Mask{9, 64, 6, 0xfc00000000000007},
	Mask{10, 64, 6, 0xfc0000000000000f},
	Mask{11, 64, 6, 0xfc0000000000001f},
	Mask{12, 64, 6, 0xfc0000000000003f},
	Mask{13, 64, 6, 0xfc0000000000007f},
	Mask{14, 64, 6, 0xfc000000000000ff},
	Mask{15, 64, 6, 0xfc000000000001ff},
	Mask{16, 64, 6, 0xfc000000000003ff},
	Mask{17, 64, 6, 0xfc000000000007ff},
	Mask{18, 64, 6, 0xfc00000000000fff},
	Mask{19, 64, 6, 0xfc00000000001fff},
	Mask{20, 64, 6, 0xfc00000000003fff},
	Mask{21, 64, 6, 0xfc00000000007fff},
	Mask{22, 64, 6, 0xfc0000000000ffff},
	Mask{23, 64, 6, 0xfc0000000001ffff},
	Mask{24, 64, 6, 0xfc0000000003ffff},
	Mask{25, 64, 6, 0xfc0000000007ffff},
	Mask{26, 64, 6, 0xfc000000000fffff},
	Mask{27, 64, 6, 0xfc000000001fffff},
	Mask{28, 64, 6, 0xfc000000003fffff},
	Mask{29, 64, 6, 0xfc000000007fffff},
	Mask{30, 64, 6, 0xfc00000000ffffff},
	Mask{31, 64, 6, 0xfc00000001ffffff},
	Mask{32, 64, 6, 0xfc00000003ffffff},
	Mask{33, 64, 6, 0xfc00000007ffffff},
	Mask{34, 64, 6, 0xfc0000000fffffff},
	Mask{35, 64, 6, 0xfc0000001fffffff},
	Mask{36, 64, 6, 0xfc0000003fffffff},
	Mask{37, 64, 6, 0xfc0000007fffffff},
	Mask{6, 32, 6, 0xfc000000fc000000},
	Mask{38, 64, 6, 0xfc000000ffffffff},
	Mask{7, 32, 6, 0xfc000001fc000001},
	Mask{39, 64, 6, 0xfc000001ffffffff},
	Mask{8, 32, 6, 0xfc000003fc000003},
	Mask{40, 64, 6, 0xfc000003ffffffff},
	Mask{9, 32, 6, 0xfc000007fc000007},
	Mask{41, 64, 6, 0xfc000007ffffffff},
	Mask{10, 32, 6, 0xfc00000ffc00000f},
	Mask{42, 64, 6, 0xfc00000fffffffff},
	Mask{11, 32, 6, 0xfc00001ffc00001f},
	Mask{43, 64, 6, 0xfc00001fffffffff},
	Mask{12, 32, 6, 0xfc00003ffc00003f},
	Mask{44, 64, 6, 0xfc00003fffffffff},
	Mask{13, 32, 6, 0xfc00007ffc00007f},
	Mask{45, 64, 6, 0xfc00007fffffffff},
	Mask{14, 32, 6, 0xfc0000fffc0000ff},
	Mask{46, 64, 6, 0xfc0000ffffffffff},
	Mask{15, 32, 6, 0xfc0001fffc0001ff},
	Mask{47, 64, 6, 0xfc0001ffffffffff},
	Mask{16, 32, 6, 0xfc0003fffc0003ff},
	Mask{48, 64, 6, 0xfc0003ffffffffff},
	Mask{17, 32, 6, 0xfc0007fffc0007ff},
	Mask{49, 64, 6, 0xfc0007ffffffffff},
	Mask{18, 32, 6, 0xfc000ffffc000fff},
	Mask{50, 64, 6, 0xfc000fffffffffff},
	Mask{19, 32, 6, 0xfc001ffffc001fff},
	Mask{51, 64, 6, 0xfc001fffffffffff},
	Mask{20, 32, 6, 0xfc003ffffc003fff},
	Mask{52, 64, 6, 0xfc003fffffffffff},
	Mask{21, 32, 6, 0xfc007ffffc007fff},
	Mask{53, 64, 6, 0xfc007fffffffffff},
	Mask{6, 16, 6, 0xfc00fc00fc00fc00},
	Mask{22, 32, 6, 0xfc00fffffc00ffff},
	Mask{54, 64, 6, 0xfc00ffffffffffff},
	Mask{7, 16, 6, 0xfc01fc01fc01fc01},
	Mask{23, 32, 6, 0xfc01fffffc01ffff},
	Mask{55, 64, 6, 0xfc01ffffffffffff},
	Mask{8, 16, 6, 0xfc03fc03fc03fc03},
	Mask{24, 32, 6, 0xfc03fffffc03ffff},
	Mask{56, 64, 6, 0xfc03ffffffffffff},
	Mask{9, 16, 6, 0xfc07fc07fc07fc07},
	Mask{25, 32, 6, 0xfc07fffffc07ffff},
	Mask{57, 64, 6, 0xfc07ffffffffffff},
	Mask{10, 16, 6, 0xfc0ffc0ffc0ffc0f},
	Mask{26, 32, 6, 0xfc0ffffffc0fffff},
	Mask{58, 64, 6, 0xfc0fffffffffffff},
	Mask{11, 16, 6, 0xfc1ffc1ffc1ffc1f},
	Mask{27, 32, 6, 0xfc1ffffffc1fffff},
	Mask{59, 64, 6, 0xfc1fffffffffffff},
	Mask{12, 16, 6, 0xfc3ffc3ffc3ffc3f},
	Mask{28, 32, 6, 0xfc3ffffffc3fffff},
	Mask{60, 64, 6, 0xfc3fffffffffffff},
	Mask{13, 16, 6, 0xfc7ffc7ffc7ffc7f},
	Mask{29, 32, 6, 0xfc7ffffffc7fffff},
	Mask{61, 64, 6, 0xfc7fffffffffffff},
	Mask{6, 8, 6, 0xfcfcfcfcfcfcfcfc},
	Mask{14, 16, 6, 0xfcfffcfffcfffcff},
	Mask{30, 32, 6, 0xfcfffffffcffffff},
	Mask{62, 64, 6, 0xfcffffffffffffff},
	Mask{7, 8, 6, 0xfdfdfdfdfdfdfdfd},
	Mask{15, 16, 6, 0xfdfffdfffdfffdff},
	Mask{31, 32, 6, 0xfdfffffffdffffff},
	Mask{63, 64, 6, 0xfdffffffffffffff},
	Mask{7, 64, 7, 0xfe00000000000000},
	Mask{8, 64, 7, 0xfe00000000000001},
	Mask{9, 64, 7, 0xfe00000000000003},
	Mask{10, 64, 7, 0xfe00000000000007},
	Mask{11, 64, 7, 0xfe0000000000000f},
	Mask{12, 64, 7, 0xfe0000000000001f},
	Mask{13, 64, 7, 0xfe0000000000003f},
	Mask{14, 64, 7, 0xfe0000000000007f},
	Mask{15, 64, 7, 0xfe000000000000ff},
	Mask{16, 64, 7, 0xfe000000000001ff},
	Mask{17, 64, 7, 0xfe000000000003ff},
	Mask{18, 64, 7, 0xfe000000000007ff},
	Mask{19, 64, 7, 0xfe00000000000fff},
	Mask{20, 64, 7, 0xfe00000000001fff},
	Mask{21, 64, 7, 0xfe00000000003fff},
	Mask{22, 64, 7, 0xfe00000000007fff},
	Mask{23, 64, 7, 0xfe0000000000ffff},
	Mask{24, 64, 7, 0xfe0000000001ffff},
	Mask{25, 64, 7, 0xfe0000000003ffff},
	Mask{26, 64, 7, 0xfe0000000007ffff},
	Mask{27, 64, 7, 0xfe000000000fffff},
	Mask{28, 64, 7, 0xfe000000001fffff},
	Mask{29, 64, 7, 0xfe000000003fffff},
	Mask{30, 64, 7, 0xfe000000007fffff},
	Mask{31, 64, 7, 0xfe00000000ffffff},
	Mask{32, 64, 7, 0xfe00000001ffffff},
	Mask{33, 64, 7, 0xfe00000003ffffff},
	Mask{34, 64, 7, 0xfe00000007ffffff},
	Mask{35, 64, 7, 0xfe0000000fffffff},
	Mask{36, 64, 7, 0xfe0000001fffffff},
	Mask{37, 64, 7, 0xfe0000003fffffff},
	Mask{38, 64, 7, 0xfe0000007fffffff},
	Mask{7, 32, 7, 0xfe000000fe000000},
	Mask{39, 64, 7, 0xfe000000ffffffff},
	Mask{8, 32, 7, 0xfe000001fe000001},
	Mask{40, 64, 7, 0xfe000001ffffffff},
	Mask{9, 32, 7, 0xfe000003fe000003},
	Mask{41, 64, 7, 0xfe000003ffffffff},
	Mask{10, 32, 7, 0xfe000007fe000007},
	Mask{42, 64, 7, 0xfe000007ffffffff},
	Mask{11, 32, 7, 0xfe00000ffe00000f},
	Mask{43, 64, 7, 0xfe00000fffffffff},
	Mask{12, 32, 7, 0xfe00001ffe00001f},
	Mask{44, 64, 7, 0xfe00001fffffffff},
	Mask{13, 32, 7, 0xfe00003ffe00003f},
	Mask{45, 64, 7, 0xfe00003fffffffff},
	Mask{14, 32, 7, 0xfe00007ffe00007f},
	Mask{46, 64, 7, 0xfe00007fffffffff},
	Mask{15, 32, 7, 0xfe0000fffe0000ff},
	Mask{47, 64, 7, 0xfe0000ffffffffff},
	Mask{16, 32, 7, 0xfe0001fffe0001ff},
	Mask{48, 64, 7, 0xfe0001ffffffffff},
	Mask{17, 32, 7, 0xfe0003fffe0003ff},
	Mask{49, 64, 7, 0xfe0003ffffffffff},
	Mask{18, 32, 7, 0xfe0007fffe0007ff},
	Mask{50, 64, 7, 0xfe0007ffffffffff},
	Mask{19, 32, 7, 0xfe000ffffe000fff},
	Mask{51, 64, 7, 0xfe000fffffffffff},
	Mask{20, 32, 7, 0xfe001ffffe001fff},
	Mask{52, 64, 7, 0xfe001fffffffffff},
	Mask{21, 32, 7, 0xfe003ffffe003fff},
	Mask{53, 64, 7, 0xfe003fffffffffff},
	Mask{22, 32, 7, 0xfe007ffffe007fff},
	Mask{54, 64, 7, 0xfe007fffffffffff},
	Mask{7, 16, 7, 0xfe00fe00fe00fe00},
	Mask{23, 32, 7, 0xfe00fffffe00ffff},
	Mask{55, 64, 7, 0xfe00ffffffffffff},
	Mask{8, 16, 7, 0xfe01fe01fe01fe01},
	Mask{24, 32, 7, 0xfe01fffffe01ffff},
	Mask{56, 64, 7, 0xfe01ffffffffffff},
	Mask{9, 16, 7, 0xfe03fe03fe03fe03},
	Mask{25, 32, 7, 0xfe03fffffe03ffff},
	Mask{57, 64, 7, 0xfe03ffffffffffff},
	Mask{10, 16, 7, 0xfe07fe07fe07fe07},
	Mask{26, 32, 7, 0xfe07fffffe07ffff},
	Mask{58, 64, 7, 0xfe07ffffffffffff},
	Mask{11, 16, 7, 0xfe0ffe0ffe0ffe0f},
	Mask{27, 32, 7, 0xfe0ffffffe0fffff},
	Mask{59, 64, 7, 0xfe0fffffffffffff},
	Mask{12, 16, 7, 0xfe1ffe1ffe1ffe1f},
	Mask{28, 32, 7, 0xfe1ffffffe1fffff},
	Mask{60, 64, 7, 0xfe1fffffffffffff},
	Mask{13, 16, 7, 0xfe3ffe3ffe3ffe3f},
	Mask{29, 32, 7, 0xfe3ffffffe3fffff},
	Mask{61, 64, 7, 0xfe3fffffffffffff},
	Mask{14, 16, 7, 0xfe7ffe7ffe7ffe7f},
	Mask{30, 32, 7, 0xfe7ffffffe7fffff},
	Mask{62, 64, 7, 0xfe7fffffffffffff},
	Mask{7, 8, 7, 0xfefefefefefefefe},
	Mask{15, 16, 7, 0xfefffefffefffeff},
	Mask{31, 32, 7, 0xfefffffffeffffff},
	Mask{63, 64, 7, 0xfeffffffffffffff},
	Mask{8, 64, 8, 0xff00000000000000},
	Mask{9, 64, 8, 0xff00000000000001},
	Mask{10, 64, 8, 0xff00000000000003},
	Mask{11, 64, 8, 0xff00000000000007},
	Mask{12, 64, 8, 0xff0000000000000f},
	Mask{13, 64, 8, 0xff0000000000001f},
	Mask{14, 64, 8, 0xff0000000000003f},
	Mask{15, 64, 8, 0xff0000000000007f},
	Mask{16, 64, 8, 0xff000000000000ff},
	Mask{17, 64, 8, 0xff000000000001ff},
	Mask{18, 64, 8, 0xff000000000003ff},
	Mask{19, 64, 8, 0xff000000000007ff},
	Mask{20, 64, 8, 0xff00000000000fff},
	Mask{21, 64, 8, 0xff00000000001fff},
	Mask{22, 64, 8, 0xff00000000003fff},
	Mask{23, 64, 8, 0xff00000000007fff},
	Mask{24, 64, 8, 0xff0000000000ffff},
	Mask{25, 64, 8, 0xff0000000001ffff},
	Mask{26, 64, 8, 0xff0000000003ffff},
	Mask{27, 64, 8, 0xff0000000007ffff},
	Mask{28, 64, 8, 0xff000000000fffff},
	Mask{29, 64, 8, 0xff000000001fffff},
	Mask{30, 64, 8, 0xff000000003fffff},
	Mask{31, 64, 8, 0xff000000007fffff},
	Mask{32, 64, 8, 0xff00000000ffffff},
	Mask{33, 64, 8, 0xff00000001ffffff},
	Mask{34, 64, 8, 0xff00000003ffffff},
	Mask{35, 64, 8, 0xff00000007ffffff},
	Mask{36, 64, 8, 0xff0000000fffffff},
	Mask{37, 64, 8, 0xff0000001fffffff},
	Mask{38, 64, 8, 0xff0000003fffffff},
	Mask{39, 64, 8, 0xff0000007fffffff},
	Mask{8, 32, 8, 0xff000000ff000000},
	Mask{40, 64, 8, 0xff000000ffffffff},
	Mask{9, 32, 8, 0xff000001ff000001},
	Mask{41, 64, 8, 0xff000001ffffffff},
	Mask{10, 32, 8, 0xff000003ff000003},
	Mask{42, 64, 8, 0xff000003ffffffff},
	Mask{11, 32, 8, 0xff000007ff000007},
	Mask{43, 64, 8, 0xff000007ffffffff},
	Mask{12, 32, 8, 0xff00000fff00000f},
	Mask{44, 64, 8, 0xff00000fffffffff},
	Mask{13, 32, 8, 0xff00001fff00001f},
	Mask{45, 64, 8, 0xff00001fffffffff},
	Mask{14, 32, 8, 0xff00003fff00003f},
	Mask{46, 64, 8, 0xff00003fffffffff},
	Mask{15, 32, 8, 0xff00007fff00007f},
	Mask{47, 64, 8, 0xff00007fffffffff},
	Mask{16, 32, 8, 0xff0000ffff0000ff},
	Mask{48, 64, 8, 0xff0000ffffffffff},
	Mask{17, 32, 8, 0xff0001ffff0001ff},
	Mask{49, 64, 8, 0xff0001ffffffffff},
	Mask{18, 32, 8, 0xff0003ffff0003ff},
	Mask{50, 64, 8, 0xff0003ffffffffff},
	Mask{19, 32, 8, 0xff0007ffff0007ff},
	Mask{51, 64, 8, 0xff0007ffffffffff},
	Mask{20, 32, 8, 0xff000fffff000fff},
	Mask{52, 64, 8, 0xff000fffffffffff},
	Mask{21, 32, 8, 0xff001fffff001fff},
	Mask{53, 64, 8, 0xff001fffffffffff},
	Mask{22, 32, 8, 0xff003fffff003fff},
	Mask{54, 64, 8, 0xff003fffffffffff},
	Mask{23, 32, 8, 0xff007fffff007fff},
	Mask{55, 64, 8, 0xff007fffffffffff},
	Mask{8, 16, 8, 0xff00ff00ff00ff00},
	Mask{24, 32, 8, 0xff00ffffff00ffff},
	Mask{56, 64, 8, 0xff00ffffffffffff},
	Mask{9, 16, 8, 0xff01ff01ff01ff01},
	Mask{25, 32, 8, 0xff01ffffff01ffff},
	Mask{57, 64, 8, 0xff01ffffffffffff},
	Mask{10, 16, 8, 0xff03ff03ff03ff03},
	Mask{26, 32, 8, 0xff03ffffff03ffff},
	Mask{58, 64, 8, 0xff03ffffffffffff},
	Mask{11, 16, 8, 0xff07ff07ff07ff07},
	Mask{27, 32, 8, 0xff07ffffff07ffff},
	Mask{59, 64, 8, 0xff07ffffffffffff},
	Mask{12, 16, 8, 0xff0fff0fff0fff0f},
	Mask{28, 32, 8, 0xff0fffffff0fffff},
	Mask{60, 64, 8, 0xff0fffffffffffff},
	Mask{13, 16, 8, 0xff1fff1fff1fff1f},
	Mask{29, 32, 8, 0xff1fffffff1fffff},
	Mask{61, 64, 8, 0xff1fffffffffffff},
	Mask{14, 16, 8, 0xff3fff3fff3fff3f},
	Mask{30, 32, 8, 0xff3fffffff3fffff},
	Mask{62, 64, 8, 0xff3fffffffffffff},
	Mask{15, 16, 8, 0xff7fff7fff7fff7f},
	Mask{31, 32, 8, 0xff7fffffff7fffff},
	Mask{63, 64, 8, 0xff7fffffffffffff},
	Mask{9, 64, 9, 0xff80000000000000},
	Mask{10, 64, 9, 0xff80000000000001},
	Mask{11, 64, 9, 0xff80000000000003},
	Mask{12, 64, 9, 0xff80000000000007},
	Mask{13, 64, 9, 0xff8000000000000f},
	Mask{14, 64, 9, 0xff8000000000001f},
	Mask{15, 64, 9, 0xff8000000000003f},
	Mask{16, 64, 9, 0xff8000000000007f},
	Mask{17, 64, 9, 0xff800000000000ff},
	Mask{18, 64, 9, 0xff800000000001ff},
	Mask{19, 64, 9, 0xff800000000003ff},
	Mask{20, 64, 9, 0xff800000000007ff},
	Mask{21, 64, 9, 0xff80000000000fff},
	Mask{22, 64, 9, 0xff80000000001fff},
	Mask{23, 64, 9, 0xff80000000003fff},
	Mask{24, 64, 9, 0xff80000000007fff},
	Mask{25, 64, 9, 0xff8000000000ffff},
	Mask{26, 64, 9, 0xff8000000001ffff},
	Mask{27, 64, 9, 0xff8000000003ffff},
	Mask{28, 64, 9, 0xff8000000007ffff},
	Mask{29, 64, 9, 0xff800000000fffff},
	Mask{30, 64, 9, 0xff800000001fffff},
	Mask{31, 64, 9, 0xff800000003fffff},
	Mask{32, 64, 9, 0xff800000007fffff},
	Mask{33, 64, 9, 0xff80000000ffffff},
	Mask{34, 64, 9, 0xff80000001ffffff},
	Mask{35, 64, 9, 0xff80000003ffffff},
	Mask{36, 64, 9, 0xff80000007ffffff},
	Mask{37, 64, 9, 0xff8000000fffffff},
	Mask{38, 64, 9, 0xff8000001fffffff},
	Mask{39, 64, 9, 0xff8000003fffffff},
	Mask{40, 64, 9, 0xff8000007fffffff},
	Mask{9, 32, 9, 0xff800000ff800000},
	Mask{41, 64, 9, 0xff800000ffffffff},
	Mask{10, 32, 9, 0xff800001ff800001},
	Mask{42, 64, 9, 0xff800001ffffffff},
	Mask{11, 32, 9, 0xff800003ff800003},
	Mask{43, 64, 9, 0xff800003ffffffff},
	Mask{12, 32, 9, 0xff800007ff800007},
	Mask{44, 64, 9, 0xff800007ffffffff},
	Mask{13, 32, 9, 0xff80000fff80000f},
	Mask{45, 64, 9, 0xff80000fffffffff},
	Mask{14, 32, 9, 0xff80001fff80001f},
	Mask{46, 64, 9, 0xff80001fffffffff},
	Mask{15, 32, 9, 0xff80003fff80003f},
	Mask{47, 64, 9, 0xff80003fffffffff},
	Mask{16, 32, 9, 0xff80007fff80007f},
	Mask{48, 64, 9, 0xff80007fffffffff},
	Mask{17, 32, 9, 0xff8000ffff8000ff},
	Mask{49, 64, 9, 0xff8000ffffffffff},
	Mask{18, 32, 9, 0xff8001ffff8001ff},
	Mask{50, 64, 9, 0xff8001ffffffffff},
	Mask{19, 32, 9, 0xff8003ffff8003ff},
	Mask{51, 64, 9, 0xff8003ffffffffff},
	Mask{20, 32, 9, 0xff8007ffff8007ff},
	Mask{52, 64, 9, 0xff8007ffffffffff},
	Mask{21, 32, 9, 0xff800fffff800fff},
	Mask{53, 64, 9, 0xff800fffffffffff},
	Mask{22, 32, 9, 0xff801fffff801fff},
	Mask{54, 64, 9, 0xff801fffffffffff},
	Mask{23, 32, 9, 0xff803fffff803fff},
	Mask{55, 64, 9, 0xff803fffffffffff},
	Mask{24, 32, 9, 0xff807fffff807fff},
	Mask{56, 64, 9, 0xff807fffffffffff},
	Mask{9, 16, 9, 0xff80ff80ff80ff80},
	Mask{25, 32, 9, 0xff80ffffff80ffff},
	Mask{57, 64, 9, 0xff80ffffffffffff},
	Mask{10, 16, 9, 0xff81ff81ff81ff81},
	Mask{26, 32, 9, 0xff81ffffff81ffff},
	Mask{58, 64, 9, 0xff81ffffffffffff},
	Mask{11, 16, 9, 0xff83ff83ff83ff83},
	Mask{27, 32, 9, 0xff83ffffff83ffff},
	Mask{59, 64, 9, 0xff83ffffffffffff},
	Mask{12, 16, 9, 0xff87ff87ff87ff87},
	Mask{28, 32, 9, 0xff87ffffff87ffff},
	Mask{60, 64, 9, 0xff87ffffffffffff},
	Mask{13, 16, 9, 0xff8fff8fff8fff8f},
	Mask{29, 32, 9, 0xff8fffffff8fffff},
	Mask{61, 64, 9, 0xff8fffffffffffff},
	Mask{14, 16, 9, 0xff9fff9fff9fff9f},
	Mask{30, 32, 9, 0xff9fffffff9fffff},
	Mask{62, 64, 9, 0xff9fffffffffffff},
	Mask{15, 16, 9, 0xffbfffbfffbfffbf},
	Mask{31, 32, 9, 0xffbfffffffbfffff},
	Mask{63, 64, 9, 0xffbfffffffffffff},
	Mask{10, 64, 10, 0xffc0000000000000},
	Mask{11, 64, 10, 0xffc0000000000001},
	Mask{12, 64, 10, 0xffc0000000000003},
	Mask{13, 64, 10, 0xffc0000000000007},
	Mask{14, 64, 10, 0xffc000000000000f},
	Mask{15, 64, 10, 0xffc000000000001f},
	Mask{16, 64, 10, 0xffc000000000003f},
	Mask{17, 64, 10, 0xffc000000000007f},
	Mask{18, 64, 10, 0xffc00000000000ff},
	Mask{19, 64, 10, 0xffc00000000001ff},
	Mask{20, 64, 10, 0xffc00000000003ff},
	Mask{21, 64, 10, 0xffc00000000007ff},
	Mask{22, 64, 10, 0xffc0000000000fff},
	Mask{23, 64, 10, 0xffc0000000001fff},
	Mask{24, 64, 10, 0xffc0000000003fff},
	Mask{25, 64, 10, 0xffc0000000007fff},
	Mask{26, 64, 10, 0xffc000000000ffff},
	Mask{27, 64, 10, 0xffc000000001ffff},
	Mask{28, 64, 10, 0xffc000000003ffff},
	Mask{29, 64, 10, 0xffc000000007ffff},
	Mask{30, 64, 10, 0xffc00000000fffff},
	Mask{31, 64, 10, 0xffc00000001fffff},
	Mask{32, 64, 10, 0xffc00000003fffff},
	Mask{33, 64, 10, 0xffc00000007fffff},
	Mask{34, 64, 10, 0xffc0000000ffffff},
	Mask{35, 64, 10, 0xffc0000001ffffff},
	Mask{36, 64, 10, 0xffc0000003ffffff},
	Mask{37, 64, 10, 0xffc0000007ffffff},
	Mask{38, 64, 10, 0xffc000000fffffff},
	Mask{39, 64, 10, 0xffc000001fffffff},
	Mask{40, 64, 10, 0xffc000003fffffff},
	Mask{41, 64, 10, 0xffc000007fffffff},
	Mask{10, 32, 10, 0xffc00000ffc00000},
	Mask{42, 64, 10, 0xffc00000ffffffff},
	Mask{11, 32, 10, 0xffc00001ffc00001},
	Mask{43, 64, 10, 0xffc00001ffffffff},
	Mask{12, 32, 10, 0xffc00003ffc00003},
	Mask{44, 64, 10, 0xffc00003ffffffff},
	Mask{13, 32, 10, 0xffc00007ffc00007},
	Mask{45, 64, 10, 0xffc00007ffffffff},
	Mask{14, 32, 10, 0xffc0000fffc0000f},
	Mask{46, 64, 10, 0xffc0000fffffffff},
	Mask{15, 32, 10, 0xffc0001fffc0001f},
	Mask{47, 64, 10, 0xffc0001fffffffff},
	Mask{16, 32, 10, 0xffc0003fffc0003f},
	Mask{48, 64, 10, 0xffc0003fffffffff},
	Mask{17, 32, 10, 0xffc0007fffc0007f},
	Mask{49, 64, 10, 0xffc0007fffffffff},
	Mask{18, 32, 10, 0xffc000ffffc000ff},
	Mask{50, 64, 10, 0xffc000ffffffffff},
	Mask{19, 32, 10, 0xffc001ffffc001ff},
	Mask{51, 64, 10, 0xffc001ffffffffff},
	Mask{20, 32, 10, 0xffc003ffffc003ff},
	Mask{52, 64, 10, 0xffc003ffffffffff},
	Mask{21, 32, 10, 0xffc007ffffc007ff},
	Mask{53, 64, 10, 0xffc007ffffffffff},
	Mask{22, 32, 10, 0xffc00fffffc00fff},
	Mask{54, 64, 10, 0xffc00fffffffffff},
	Mask{23, 32, 10, 0xffc01fffffc01fff},
	Mask{55, 64, 10, 0xffc01fffffffffff},
	Mask{24, 32, 10, 0xffc03fffffc03fff},
	Mask{56, 64, 10, 0xffc03fffffffffff},
	Mask{25, 32, 10, 0xffc07fffffc07fff},
	Mask{57, 64, 10, 0xffc07fffffffffff},
	Mask{10, 16, 10, 0xffc0ffc0ffc0ffc0},
	Mask{26, 32, 10, 0xffc0ffffffc0ffff},
	Mask{58, 64, 10, 0xffc0ffffffffffff},
	Mask{11, 16, 10, 0xffc1ffc1ffc1ffc1},
	Mask{27, 32, 10, 0xffc1ffffffc1ffff},
	Mask{59, 64, 10, 0xffc1ffffffffffff},
	Mask{12, 16, 10, 0xffc3ffc3ffc3ffc3},
	Mask{28, 32, 10, 0xffc3ffffffc3ffff},
	Mask{60, 64, 10, 0xffc3ffffffffffff},
	Mask{13, 16, 10, 0xffc7ffc7ffc7ffc7},
	Mask{29, 32, 10, 0xffc7ffffffc7ffff},
	Mask{61, 64, 10, 0xffc7ffffffffffff},
	Mask{14, 16, 10, 0xffcfffcfffcfffcf},
	Mask{30, 32, 10, 0xffcfffffffcfffff},
	Mask{62, 64, 10, 0xffcfffffffffffff},
	Mask{15, 16, 10, 0xffdfffdfffdfffdf},
	Mask{31, 32, 10, 0xffdfffffffdfffff},
	Mask{63, 64, 10, 0xffdfffffffffffff},
	Mask{11, 64, 11, 0xffe0000000000000},
	Mask{12, 64, 11, 0xffe0000000000001},
	Mask{13, 64, 11, 0xffe0000000000003},
	Mask{14, 64, 11, 0xffe0000000000007},
	Mask{15, 64, 11, 0xffe000000000000f},
	Mask{16, 64, 11, 0xffe000000000001f},
	Mask{17, 64, 11, 0xffe000000000003f},
	Mask{18, 64, 11, 0xffe000000000007f},
	Mask{19, 64, 11, 0xffe00000000000ff},
	Mask{20, 64, 11, 0xffe00000000001ff},
	Mask{21, 64, 11, 0xffe00000000003ff},
	Mask{22, 64, 11, 0xffe00000000007ff},
	Mask{23, 64, 11, 0xffe0000000000fff},
	Mask{24, 64, 11, 0xffe0000000001fff},
	Mask{25, 64, 11, 0xffe0000000003fff},
	Mask{26, 64, 11, 0xffe0000000007fff},
	Mask{27, 64, 11, 0xffe000000000ffff},
	Mask{28, 64, 11, 0xffe000000001ffff},
	Mask{29, 64, 11, 0xffe000000003ffff},
	Mask{30, 64, 11, 0xffe000000007ffff},
	Mask{31, 64, 11, 0xffe00000000fffff},
	Mask{32, 64, 11, 0xffe00000001fffff},
	Mask{33, 64, 11, 0xffe00000003fffff},
	Mask{34, 64, 11, 0xffe00000007fffff},
	Mask{35, 64, 11, 0xffe0000000ffffff},
	Mask{36, 64, 11, 0xffe0000001ffffff},
	Mask{37, 64, 11, 0xffe0000003ffffff},
	Mask{38, 64, 11, 0xffe0000007ffffff},
	Mask{39, 64, 11, 0xffe000000fffffff},
	Mask{40, 64, 11, 0xffe000001fffffff},
	Mask{41, 64, 11, 0xffe000003fffffff},
	Mask{42, 64, 11, 0xffe000007fffffff},
	Mask{11, 32, 11, 0xffe00000ffe00000},
	Mask{43, 64, 11, 0xffe00000ffffffff},
	Mask{12, 32, 11, 0xffe00001ffe00001},
	Mask{44, 64, 11, 0xffe00001ffffffff},
	Mask{13, 32, 11, 0xffe00003ffe00003},
	Mask{45, 64, 11, 0xffe00003ffffffff},
	Mask{14, 32, 11, 0xffe00007ffe00007},
	Mask{46, 64, 11, 0xffe00007ffffffff},
	Mask{15, 32, 11, 0xffe0000fffe0000f},
	Mask{47, 64, 11, 0xffe0000fffffffff},
	Mask{16, 32, 11, 0xffe0001fffe0001f},
	Mask{48, 64, 11, 0xffe0001fffffffff},
	Mask{17, 32, 11, 0xffe0003fffe0003f},
	Mask{49, 64, 11, 0xffe0003fffffffff},
	Mask{18, 32, 11, 0xffe0007fffe0007f},
	Mask{50, 64, 11, 0xffe0007fffffffff},
	Mask{19, 32, 11, 0xffe000ffffe000ff},
	Mask{51, 64, 11, 0xffe000ffffffffff},
	Mask{20, 32, 11, 0xffe001ffffe001ff},
	Mask{52, 64, 11, 0xffe001ffffffffff},
	Mask{21, 32, 11, 0xffe003ffffe003ff},
	Mask{53, 64, 11, 0xffe003ffffffffff},
	Mask{22, 32, 11, 0xffe007ffffe007ff},
	Mask{54, 64, 11, 0xffe007ffffffffff},
	Mask{23, 32, 11, 0xffe00fffffe00fff},
	Mask{55, 64, 11, 0xffe00fffffffffff},
	Mask{24, 32, 11, 0xffe01fffffe01fff},
	Mask{56, 64, 11, 0xffe01fffffffffff},
	Mask{25, 32, 11, 0xffe03fffffe03fff},
	Mask{57, 64, 11, 0xffe03fffffffffff},
	Mask{26, 32, 11, 0xffe07fffffe07fff},
	Mask{58, 64, 11, 0xffe07fffffffffff},
	Mask{11, 16, 11, 0xffe0ffe0ffe0ffe0},
	Mask{27, 32, 11, 0xffe0ffffffe0ffff},
	Mask{59, 64, 11, 0xffe0ffffffffffff},
	Mask{12, 16, 11, 0xffe1ffe1ffe1ffe1},
	Mask{28, 32, 11, 0xffe1ffffffe1ffff},
	Mask{60, 64, 11, 0xffe1ffffffffffff},
	Mask{13, 16, 11, 0xffe3ffe3ffe3ffe3},
	Mask{29, 32, 11, 0xffe3ffffffe3ffff},
	Mask{61, 64, 11, 0xffe3ffffffffffff},
	Mask{14, 16, 11, 0xffe7ffe7ffe7ffe7},
	Mask{30, 32, 11, 0xffe7ffffffe7ffff},
	Mask{62, 64, 11, 0xffe7ffffffffffff},
	Mask{15, 16, 11, 0xffefffefffefffef},
	Mask{31, 32, 11, 0xffefffffffefffff},
	Mask{63, 64, 11, 0xffefffffffffffff},
	Mask{12, 64, 12, 0xfff0000000000000},
	Mask{13, 64, 12, 0xfff0000000000001},
	Mask{14, 64, 12, 0xfff0000000000003},
	Mask{15, 64, 12, 0xfff0000000000007},
	Mask{16, 64, 12, 0xfff000000000000f},
	Mask{17, 64, 12, 0xfff000000000001f},
	Mask{18, 64, 12, 0xfff000000000003f},
	Mask{19, 64, 12, 0xfff000000000007f},
	Mask{20, 64, 12, 0xfff00000000000ff},
	Mask{21, 64, 12, 0xfff00000000001ff},
	Mask{22, 64, 12, 0xfff00000000003ff},
	Mask{23, 64, 12, 0xfff00000000007ff},
	Mask{24, 64, 12, 0xfff0000000000fff},
	Mask{25, 64, 12, 0xfff0000000001fff},
	Mask{26, 64, 12, 0xfff0000000003fff},
	Mask{27, 64, 12, 0xfff0000000007fff},
	Mask{28, 64, 12, 0xfff000000000ffff},
	Mask{29, 64, 12, 0xfff000000001ffff},
	Mask{30, 64, 12, 0xfff000000003ffff},
	Mask{31, 64, 12, 0xfff000000007ffff},
	Mask{32, 64, 12, 0xfff00000000fffff},
	Mask{33, 64, 12, 0xfff00000001fffff},
	Mask{34, 64, 12, 0xfff00000003fffff},
	Mask{35, 64, 12, 0xfff00000007fffff},
	Mask{36, 64, 12, 0xfff0000000ffffff},
	Mask{37, 64, 12, 0xfff0000001ffffff},
	Mask{38, 64, 12, 0xfff0000003ffffff},
	Mask{39, 64, 12, 0xfff0000007ffffff},
	Mask{40, 64, 12, 0xfff000000fffffff},
	Mask{41, 64, 12, 0xfff000001fffffff},
	Mask{42, 64, 12, 0xfff000003fffffff},
	Mask{43, 64, 12, 0xfff000007fffffff},
	Mask{12, 32, 12, 0xfff00000fff00000},
	Mask{44, 64, 12, 0xfff00000ffffffff},
	Mask{13, 32, 12, 0xfff00001fff00001},
	Mask{45, 64, 12, 0xfff00001ffffffff},
	Mask{14, 32, 12, 0xfff00003fff00003},
	Mask{46, 64, 12, 0xfff00003ffffffff},
	Mask{15, 32, 12, 0xfff00007fff00007},
	Mask{47, 64, 12, 0xfff00007ffffffff},
	Mask{16, 32, 12, 0xfff0000ffff0000f},
	Mask{48, 64, 12, 0xfff0000fffffffff},
	Mask{17, 32, 12, 0xfff0001ffff0001f},
	Mask{49, 64, 12, 0xfff0001fffffffff},
	Mask{18, 32, 12, 0xfff0003ffff0003f},
	Mask{50, 64, 12, 0xfff0003fffffffff},
	Mask{19, 32, 12, 0xfff0007ffff0007f},
	Mask{51, 64, 12, 0xfff0007fffffffff},
	Mask{20, 32, 12, 0xfff000fffff000ff},
	Mask{52, 64, 12, 0xfff000ffffffffff},
	Mask{21, 32, 12, 0xfff001fffff001ff},
	Mask{53, 64, 12, 0xfff001ffffffffff},
	Mask{22, 32, 12, 0xfff003fffff003ff},
	Mask{54, 64, 12, 0xfff003ffffffffff},
	Mask{23, 32, 12, 0xfff007fffff007ff},
	Mask{55, 64, 12, 0xfff007ffffffffff},
	Mask{24, 32, 12, 0xfff00ffffff00fff},
	Mask{56, 64, 12, 0xfff00fffffffffff},
	Mask{25, 32, 12, 0xfff01ffffff01fff},
	Mask{57, 64, 12, 0xfff01fffffffffff},
	Mask{26, 32, 12, 0xfff03ffffff03fff},
	Mask{58, 64, 12, 0xfff03fffffffffff},
	Mask{27, 32, 12, 0xfff07ffffff07fff},
	Mask{59, 64, 12, 0xfff07fffffffffff},
	Mask{12, 16, 12, 0xfff0fff0fff0fff0},
	Mask{28, 32, 12, 0xfff0fffffff0ffff},
	Mask{60, 64, 12, 0xfff0ffffffffffff},
	Mask{13, 16, 12, 0xfff1fff1fff1fff1},
	Mask{29, 32, 12, 0xfff1fffffff1ffff},
	Mask{61, 64, 12, 0xfff1ffffffffffff},
	Mask{14, 16, 12, 0xfff3fff3fff3fff3},
	Mask{30, 32, 12, 0xfff3fffffff3ffff},
	Mask{62, 64, 12, 0xfff3ffffffffffff},
	Mask{15, 16, 12, 0xfff7fff7fff7fff7},
	Mask{31, 32, 12, 0xfff7fffffff7ffff},
	Mask{63, 64, 12, 0xfff7ffffffffffff},
	Mask{13, 64, 13, 0xfff8000000000000},
	Mask{14, 64, 13, 0xfff8000000000001},
	Mask{15, 64, 13, 0xfff8000000000003},
	Mask{16, 64, 13, 0xfff8000000000007},
	Mask{17, 64, 13, 0xfff800000000000f},
	Mask{18, 64, 13, 0xfff800000000001f},
	Mask{19, 64, 13, 0xfff800000000003f},
	Mask{20, 64, 13, 0xfff800000000007f},
	Mask{21, 64, 13, 0xfff80000000000ff},
	Mask{22, 64, 13, 0xfff80000000001ff},
	Mask{23, 64, 13, 0xfff80000000003ff},
	Mask{24, 64, 13, 0xfff80000000007ff},
	Mask{25, 64, 13, 0xfff8000000000fff},
	Mask{26, 64, 13, 0xfff8000000001fff},
	Mask{27, 64, 13, 0xfff8000000003fff},
	Mask{28, 64, 13, 0xfff8000000007fff},
	Mask{29, 64, 13, 0xfff800000000ffff},
	Mask{30, 64, 13, 0xfff800000001ffff},
	Mask{31, 64, 13, 0xfff800000003ffff},
	Mask{32, 64, 13, 0xfff800000007ffff},
	Mask{33, 64, 13, 0xfff80000000fffff},
	Mask{34, 64, 13, 0xfff80000001fffff},
	Mask{35, 64, 13, 0xfff80000003fffff},
	Mask{36, 64, 13, 0xfff80000007fffff},
	Mask{37, 64, 13, 0xfff8000000ffffff},
	Mask{38, 64, 13, 0xfff8000001ffffff},
	Mask{39, 64, 13, 0xfff8000003ffffff},
	Mask{40, 64, 13, 0xfff8000007ffffff},
	Mask{41, 64, 13, 0xfff800000fffffff},
	Mask{42, 64, 13, 0xfff800001fffffff},
	Mask{43, 64, 13, 0xfff800003fffffff},
	Mask{44, 64, 13, 0xfff800007fffffff},
	Mask{13, 32, 13, 0xfff80000fff80000},
	Mask{45, 64, 13, 0xfff80000ffffffff},
	Mask{14, 32, 13, 0xfff80001fff80001},
	Mask{46, 64, 13, 0xfff80001ffffffff},
	Mask{15, 32, 13, 0xfff80003fff80003},
	Mask{47, 64, 13, 0xfff80003ffffffff},
	Mask{16, 32, 13, 0xfff80007fff80007},
	Mask{48, 64, 13, 0xfff80007ffffffff},
	Mask{17, 32, 13, 0xfff8000ffff8000f},
	Mask{49, 64, 13, 0xfff8000fffffffff},
	Mask{18, 32, 13, 0xfff8001ffff8001f},
	Mask{50, 64, 13, 0xfff8001fffffffff},
	Mask{19, 32, 13, 0xfff8003ffff8003f},
	Mask{51, 64, 13, 0xfff8003fffffffff},
	Mask{20, 32, 13, 0xfff8007ffff8007f},
	Mask{52, 64, 13, 0xfff8007fffffffff},
	Mask{21, 32, 13, 0xfff800fffff800ff},
	Mask{53, 64, 13, 0xfff800ffffffffff},
	Mask{22, 32, 13, 0xfff801fffff801ff},
	Mask{54, 64, 13, 0xfff801ffffffffff},
	Mask{23, 32, 13, 0xfff803fffff803ff},
	Mask{55, 64, 13, 0xfff803ffffffffff},
	Mask{24, 32, 13, 0xfff807fffff807ff},
	Mask{56, 64, 13, 0xfff807ffffffffff},
	Mask{25, 32, 13, 0xfff80ffffff80fff},
	Mask{57, 64, 13, 0xfff80fffffffffff},
	Mask{26, 32, 13, 0xfff81ffffff81fff},
	Mask{58, 64, 13, 0xfff81fffffffffff},
	Mask{27, 32, 13, 0xfff83ffffff83fff},
	Mask{59, 64, 13, 0xfff83fffffffffff},
	Mask{28, 32, 13, 0xfff87ffffff87fff},
	Mask{60, 64, 13, 0xfff87fffffffffff},
	Mask{13, 16, 13, 0xfff8fff8fff8fff8},
	Mask{29, 32, 13, 0xfff8fffffff8ffff},
	Mask{61, 64, 13, 0xfff8ffffffffffff},
	Mask{14, 16, 13, 0xfff9fff9fff9fff9},
	Mask{30, 32, 13, 0xfff9fffffff9ffff},
	Mask{62, 64, 13, 0xfff9ffffffffffff},
	Mask{15, 16, 13, 0xfffbfffbfffbfffb},
	Mask{31, 32, 13, 0xfffbfffffffbffff},
	Mask{63, 64, 13, 0xfffbffffffffffff},
	Mask{14, 64, 14, 0xfffc000000000000},
	Mask{15, 64, 14, 0xfffc000000000001},
	Mask{16, 64, 14, 0xfffc000000000003},
	Mask{17, 64, 14, 0xfffc000000000007},
	Mask{18, 64, 14, 0xfffc00000000000f},
	Mask{19, 64, 14, 0xfffc00000000001f},
	Mask{20, 64, 14, 0xfffc00000000003f},
	Mask{21, 64, 14, 0xfffc00000000007f},
	Mask{22, 64, 14, 0xfffc0000000000ff},
	Mask{23, 64, 14, 0xfffc0000000001ff},
	Mask{24, 64, 14, 0xfffc0000000003ff},
	Mask{25, 64, 14, 0xfffc0000000007ff},
	Mask{26, 64, 14, 0xfffc000000000fff},
	Mask{27, 64, 14, 0xfffc000000001fff},
	Mask{28, 64, 14, 0xfffc000000003fff},
	Mask{29, 64, 14, 0xfffc000000007fff},
	Mask{30, 64, 14, 0xfffc00000000ffff},
	Mask{31, 64, 14, 0xfffc00000001ffff},
	Mask{32, 64, 14, 0xfffc00000003ffff},
	Mask{33, 64, 14, 0xfffc00000007ffff},
	Mask{34, 64, 14, 0xfffc0000000fffff},
	Mask{35, 64, 14, 0xfffc0000001fffff},
	Mask{36, 64, 14, 0xfffc0000003fffff},
	Mask{37, 64, 14, 0xfffc0000007fffff},
	Mask{38, 64, 14, 0xfffc000000ffffff},
	Mask{39, 64, 14, 0xfffc000001ffffff},
	Mask{40, 64, 14, 0xfffc000003ffffff},
	Mask{41, 64, 14, 0xfffc000007ffffff},
	Mask{42, 64, 14, 0xfffc00000fffffff},
	Mask{43, 64, 14, 0xfffc00001fffffff},
	Mask{44, 64, 14, 0xfffc00003fffffff},
	Mask{45, 64, 14, 0xfffc00007fffffff},
	Mask{14, 32, 14, 0xfffc0000fffc0000},
	Mask{46, 64, 14, 0xfffc0000ffffffff},
	Mask{15, 32, 14, 0xfffc0001fffc0001},
	Mask{47, 64, 14, 0xfffc0001ffffffff},
	Mask{16, 32, 14, 0xfffc0003fffc0003},
	Mask{48, 64, 14, 0xfffc0003ffffffff},
	Mask{17, 32, 14, 0xfffc0007fffc0007},
	Mask{49, 64, 14, 0xfffc0007ffffffff},
	Mask{18, 32, 14, 0xfffc000ffffc000f},
	Mask{50, 64, 14, 0xfffc000fffffffff},
	Mask{19, 32, 14, 0xfffc001ffffc001f},
	Mask{51, 64, 14, 0xfffc001fffffffff},
	Mask{20, 32, 14, 0xfffc003ffffc003f},
	Mask{52, 64, 14, 0xfffc003fffffffff},
	Mask{21, 32, 14, 0xfffc007ffffc007f},
	Mask{53, 64, 14, 0xfffc007fffffffff},
	Mask{22, 32, 14, 0xfffc00fffffc00ff},
	Mask{54, 64, 14, 0xfffc00ffffffffff},
	Mask{23, 32, 14, 0xfffc01fffffc01ff},
	Mask{55, 64, 14, 0xfffc01ffffffffff},
	Mask{24, 32, 14, 0xfffc03fffffc03ff},
	Mask{56, 64, 14, 0xfffc03ffffffffff},
	Mask{25, 32, 14, 0xfffc07fffffc07ff},
	Mask{57, 64, 14, 0xfffc07ffffffffff},
	Mask{26, 32, 14, 0xfffc0ffffffc0fff},
	Mask{58, 64, 14, 0xfffc0fffffffffff},
	Mask{27, 32, 14, 0xfffc1ffffffc1fff},
	Mask{59, 64, 14, 0xfffc1fffffffffff},
	Mask{28, 32, 14, 0xfffc3ffffffc3fff},
	Mask{60, 64, 14, 0xfffc3fffffffffff},
	Mask{29, 32, 14, 0xfffc7ffffffc7fff},
	Mask{61, 64, 14, 0xfffc7fffffffffff},
	Mask{14, 16, 14, 0xfffcfffcfffcfffc},
	Mask{30, 32, 14, 0xfffcfffffffcffff},
	Mask{62, 64, 14, 0xfffcffffffffffff},
	Mask{15, 16, 14, 0xfffdfffdfffdfffd},
	Mask{31, 32, 14, 0xfffdfffffffdffff},
	Mask{63, 64, 14, 0xfffdffffffffffff},
	Mask{15, 64, 15, 0xfffe000000000000},
	Mask{16, 64, 15, 0xfffe000000000001},
	Mask{17, 64, 15, 0xfffe000000000003},
	Mask{18, 64, 15, 0xfffe000000000007},
	Mask{19, 64, 15, 0xfffe00000000000f},
	Mask{20, 64, 15, 0xfffe00000000001f},
	Mask{21, 64, 15, 0xfffe00000000003f},
	Mask{22, 64, 15, 0xfffe00000000007f},
	Mask{23, 64, 15, 0xfffe0000000000ff},
	Mask{24, 64, 15, 0xfffe0000000001ff},
	Mask{25, 64, 15, 0xfffe0000000003ff},
	Mask{26, 64, 15, 0xfffe0000000007ff},
	Mask{27, 64, 15, 0xfffe000000000fff},
	Mask{28, 64, 15, 0xfffe000000001fff},
	Mask{29, 64, 15, 0xfffe000000003fff},
	Mask{30, 64, 15, 0xfffe000000007fff},
	Mask{31, 64, 15, 0xfffe00000000ffff},
	Mask{32, 64, 15, 0xfffe00000001ffff},
	Mask{33, 64, 15, 0xfffe00000003ffff},
	Mask{34, 64, 15, 0xfffe00000007ffff},
	Mask{35, 64, 15, 0xfffe0000000fffff},
	Mask{36, 64, 15, 0xfffe0000001fffff},
	Mask{37, 64, 15, 0xfffe0000003fffff},
	Mask{38, 64, 15, 0xfffe0000007fffff},
	Mask{39, 64, 15, 0xfffe000000ffffff},
	Mask{40, 64, 15, 0xfffe000001ffffff},
	Mask{41, 64, 15, 0xfffe000003ffffff},
	Mask{42, 64, 15, 0xfffe000007ffffff},
	Mask{43, 64, 15, 0xfffe00000fffffff},
	Mask{44, 64, 15, 0xfffe00001fffffff},
	Mask{45, 64, 15, 0xfffe00003fffffff},
	Mask{46, 64, 15, 0xfffe00007fffffff},
	Mask{15, 32, 15, 0xfffe0000fffe0000},
	Mask{47, 64, 15, 0xfffe0000ffffffff},
	Mask{16, 32, 15, 0xfffe0001fffe0001},
	Mask{48, 64, 15, 0xfffe0001ffffffff},
	Mask{17, 32, 15, 0xfffe0003fffe0003},
	Mask{49, 64, 15, 0xfffe0003ffffffff},
	Mask{18, 32, 15, 0xfffe0007fffe0007},
	Mask{50, 64, 15, 0xfffe0007ffffffff},
	Mask{19, 32, 15, 0xfffe000ffffe000f},
	Mask{51, 64, 15, 0xfffe000fffffffff},
	Mask{20, 32, 15, 0xfffe001ffffe001f},
	Mask{52, 64, 15, 0xfffe001fffffffff},
	Mask{21, 32, 15, 0xfffe003ffffe003f},
	Mask{53, 64, 15, 0xfffe003fffffffff},
	Mask{22, 32, 15, 0xfffe007ffffe007f},
	Mask{54, 64, 15, 0xfffe007fffffffff},
	Mask{23, 32, 15, 0xfffe00fffffe00ff},
	Mask{55, 64, 15, 0xfffe00ffffffffff},
	Mask{24, 32, 15, 0xfffe01fffffe01ff},
	Mask{56, 64, 15, 0xfffe01ffffffffff},
	Mask{25, 32, 15, 0xfffe03fffffe03ff},
	Mask{57, 64, 15, 0xfffe03ffffffffff},
	Mask{26, 32, 15, 0xfffe07fffffe07ff},
	Mask{58, 64, 15, 0xfffe07ffffffffff},
	Mask{27, 32, 15, 0xfffe0ffffffe0fff},
	Mask{59, 64, 15, 0xfffe0fffffffffff},
	Mask{28, 32, 15, 0xfffe1ffffffe1fff},
	Mask{60, 64, 15, 0xfffe1fffffffffff},
	Mask{29, 32, 15, 0xfffe3ffffffe3fff},
	Mask{61, 64, 15, 0xfffe3fffffffffff},
	Mask{30, 32, 15, 0xfffe7ffffffe7fff},
	Mask{62, 64, 15, 0xfffe7fffffffffff},
	Mask{15, 16, 15, 0xfffefffefffefffe},
	Mask{31, 32, 15, 0xfffefffffffeffff},
	Mask{63, 64, 15, 0xfffeffffffffffff},
	Mask{16, 64, 16, 0xffff000000000000},
	Mask{17, 64, 16, 0xffff000000000001},
	Mask{18, 64, 16, 0xffff000000000003},
	Mask{19, 64, 16, 0xffff000000000007},
	Mask{20, 64, 16, 0xffff00000000000f},
	Mask{21, 64, 16, 0xffff00000000001f},
	Mask{22, 64, 16, 0xffff00000000003f},
	Mask{23, 64, 16, 0xffff00000000007f},
	Mask{24, 64, 16, 0xffff0000000000ff},
	Mask{25, 64, 16, 0xffff0000000001ff},
	Mask{26, 64, 16, 0xffff0000000003ff},
	Mask{27, 64, 16, 0xffff0000000007ff},
	Mask{28, 64, 16, 0xffff000000000fff},
	Mask{29, 64, 16, 0xffff000000001fff},
	Mask{30, 64, 16, 0xffff000000003fff},
	Mask{31, 64, 16, 0xffff000000007fff},
	Mask{32, 64, 16, 0xffff00000000ffff},
	Mask{33, 64, 16, 0xffff00000001ffff},
	Mask{34, 64, 16, 0xffff00000003ffff},
	Mask{35, 64, 16, 0xffff00000007ffff},
	Mask{36, 64, 16, 0xffff0000000fffff},
	Mask{37, 64, 16, 0xffff0000001fffff},
	Mask{38, 64, 16, 0xffff0000003fffff},
	Mask{39, 64, 16, 0xffff0000007fffff},
	Mask{40, 64, 16, 0xffff000000ffffff},
	Mask{41, 64, 16, 0xffff000001ffffff},
	Mask{42, 64, 16, 0xffff000003ffffff},
	Mask{43, 64, 16, 0xffff000007ffffff},
	Mask{44, 64, 16, 0xffff00000fffffff},
	Mask{45, 64, 16, 0xffff00001fffffff},
	Mask{46, 64, 16, 0xffff00003fffffff},
	Mask{47, 64, 16, 0xffff00007fffffff},
	Mask{16, 32, 16, 0xffff0000ffff0000},
	Mask{48, 64, 16, 0xffff0000ffffffff},
	Mask{17, 32, 16, 0xffff0001ffff0001},
	Mask{49, 64, 16, 0xffff0001ffffffff},
	Mask{18, 32, 16, 0xffff0003ffff0003},
	Mask{50, 64, 16, 0xffff0003ffffffff},
	Mask{19, 32, 16, 0xffff0007ffff0007},
	Mask{51, 64, 16, 0xffff0007ffffffff},
	Mask{20, 32, 16, 0xffff000fffff000f},
	Mask{52, 64, 16, 0xffff000fffffffff},
	Mask{21, 32, 16, 0xffff001fffff001f},
	Mask{53, 64, 16, 0xffff001fffffffff},
	Mask{22, 32, 16, 0xffff003fffff003f},
	Mask{54, 64, 16, 0xffff003fffffffff},
	Mask{23, 32, 16, 0xffff007fffff007f},
	Mask{55, 64, 16, 0xffff007fffffffff},
	Mask{24, 32, 16, 0xffff00ffffff00ff},
	Mask{56, 64, 16, 0xffff00ffffffffff},
	Mask{25, 32, 16, 0xffff01ffffff01ff},
	Mask{57, 64, 16, 0xffff01ffffffffff},
	Mask{26, 32, 16, 0xffff03ffffff03ff},
	Mask{58, 64, 16, 0xffff03ffffffffff},
	Mask{27, 32, 16, 0xffff07ffffff07ff},
	Mask{59, 64, 16, 0xffff07ffffffffff},
	Mask{28, 32, 16, 0xffff0fffffff0fff},
	Mask{60, 64, 16, 0xffff0fffffffffff},
	Mask{29, 32, 16, 0xffff1fffffff1fff},
	Mask{61, 64, 16, 0xffff1fffffffffff},
	Mask{30, 32, 16, 0xffff3fffffff3fff},
	Mask{62, 64, 16, 0xffff3fffffffffff},
	Mask{31, 32, 16, 0xffff7fffffff7fff},
	Mask{63, 64, 16, 0xffff7fffffffffff},
	Mask{17, 64, 17, 0xffff800000000000},
	Mask{18, 64, 17, 0xffff800000000001},
	Mask{19, 64, 17, 0xffff800000000003},
	Mask{20, 64, 17, 0xffff800000000007},
	Mask{21, 64, 17, 0xffff80000000000f},
	Mask{22, 64, 17, 0xffff80000000001f},
	Mask{23, 64, 17, 0xffff80000000003f},
	Mask{24, 64, 17, 0xffff80000000007f},
	Mask{25, 64, 17, 0xffff8000000000ff},
	Mask{26, 64, 17, 0xffff8000000001ff},
	Mask{27, 64, 17, 0xffff8000000003ff},
	Mask{28, 64, 17, 0xffff8000000007ff},
	Mask{29, 64, 17, 0xffff800000000fff},
	Mask{30, 64, 17, 0xffff800000001fff},
	Mask{31, 64, 17, 0xffff800000003fff},
	Mask{32, 64, 17, 0xffff800000007fff},
	Mask{33, 64, 17, 0xffff80000000ffff},
	Mask{34, 64, 17, 0xffff80000001ffff},
	Mask{35, 64, 17, 0xffff80000003ffff},
	Mask{36, 64, 17, 0xffff80000007ffff},
	Mask{37, 64, 17, 0xffff8000000fffff},
	Mask{38, 64, 17, 0xffff8000001fffff},
	Mask{39, 64, 17, 0xffff8000003fffff},
	Mask{40, 64, 17, 0xffff8000007fffff},
	Mask{41, 64, 17, 0xffff800000ffffff},
	Mask{42, 64, 17, 0xffff800001ffffff},
	Mask{43, 64, 17, 0xffff800003ffffff},
	Mask{44, 64, 17, 0xffff800007ffffff},
	Mask{45, 64, 17, 0xffff80000fffffff},
	Mask{46, 64, 17, 0xffff80001fffffff},
	Mask{47, 64, 17, 0xffff80003fffffff},
	Mask{48, 64, 17, 0xffff80007fffffff},
	Mask{17, 32, 17, 0xffff8000ffff8000},
	Mask{49, 64, 17, 0xffff8000ffffffff},
	Mask{18, 32, 17, 0xffff8001ffff8001},
	Mask{50, 64, 17, 0xffff8001ffffffff},
	Mask{19, 32, 17, 0xffff8003ffff8003},
	Mask{51, 64, 17, 0xffff8003ffffffff},
	Mask{20, 32, 17, 0xffff8007ffff8007},
	Mask{52, 64, 17, 0xffff8007ffffffff},
	Mask{21, 32, 17, 0xffff800fffff800f},
	Mask{53, 64, 17, 0xffff800fffffffff},
	Mask{22, 32, 17, 0xffff801fffff801f},
	Mask{54, 64, 17, 0xffff801fffffffff},
	Mask{23, 32, 17, 0xffff803fffff803f},
	Mask{55, 64, 17, 0xffff803fffffffff},
	Mask{24, 32, 17, 0xffff807fffff807f},
	Mask{56, 64, 17, 0xffff807fffffffff},
	Mask{25, 32, 17, 0xffff80ffffff80ff},
	Mask{57, 64, 17, 0xffff80ffffffffff},
	Mask{26, 32, 17, 0xffff81ffffff81ff},
	Mask{58, 64, 17, 0xffff81ffffffffff},
	Mask{27, 32, 17, 0xffff83ffffff83ff},
	Mask{59, 64, 17, 0xffff83ffffffffff},
	Mask{28, 32, 17, 0xffff87ffffff87ff},
	Mask{60, 64, 17, 0xffff87ffffffffff},
	Mask{29, 32, 17, 0xffff8fffffff8fff},
	Mask{61, 64, 17, 0xffff8fffffffffff},
	Mask{30, 32, 17, 0xffff9fffffff9fff},
	Mask{62, 64, 17, 0xffff9fffffffffff},
	Mask{31, 32, 17, 0xffffbfffffffbfff},
	Mask{63, 64, 17, 0xffffbfffffffffff},
	Mask{18, 64, 18, 0xffffc00000000000},
	Mask{19, 64, 18, 0xffffc00000000001},
	Mask{20, 64, 18, 0xffffc00000000003},
	Mask{21, 64, 18, 0xffffc00000000007},
	Mask{22, 64, 18, 0xffffc0000000000f},
	Mask{23, 64, 18, 0xffffc0000000001f},
	Mask{24, 64, 18, 0xffffc0000000003f},
	Mask{25, 64, 18, 0xffffc0000000007f},
	Mask{26, 64, 18, 0xffffc000000000ff},
	Mask{27, 64, 18, 0xffffc000000001ff},
	Mask{28, 64, 18, 0xffffc000000003ff},
	Mask{29, 64, 18, 0xffffc000000007ff},
	Mask{30, 64, 18, 0xffffc00000000fff},
	Mask{31, 64, 18, 0xffffc00000001fff},
	Mask{32, 64, 18, 0xffffc00000003fff},
	Mask{33, 64, 18, 0xffffc00000007fff},
	Mask{34, 64, 18, 0xffffc0000000ffff},
	Mask{35, 64, 18, 0xffffc0000001ffff},
	Mask{36, 64, 18, 0xffffc0000003ffff},
	Mask{37, 64, 18, 0xffffc0000007ffff},
	Mask{38, 64, 18, 0xffffc000000fffff},
	Mask{39, 64, 18, 0xffffc000001fffff},
	Mask{40, 64, 18, 0xffffc000003fffff},
	Mask{41, 64, 18, 0xffffc000007fffff},
	Mask{42, 64, 18, 0xffffc00000ffffff},
	Mask{43, 64, 18, 0xffffc00001ffffff},
	Mask{44, 64, 18, 0xffffc00003ffffff},
	Mask{45, 64, 18, 0xffffc00007ffffff},
	Mask{46, 64, 18, 0xffffc0000fffffff},
	Mask{47, 64, 18, 0xffffc0001fffffff},
	Mask{48, 64, 18, 0xffffc0003fffffff},
	Mask{49, 64, 18, 0xffffc0007fffffff},
	Mask{18, 32, 18, 0xffffc000ffffc000},
	Mask{50, 64, 18, 0xffffc000ffffffff},
	Mask{19, 32, 18, 0xffffc001ffffc001},
	Mask{51, 64, 18, 0xffffc001ffffffff},
	Mask{20, 32, 18, 0xffffc003ffffc003},
	Mask{52, 64, 18, 0xffffc003ffffffff},
	Mask{21, 32, 18, 0xffffc007ffffc007},
	Mask{53, 64, 18, 0xffffc007ffffffff},
	Mask{22, 32, 18, 0xffffc00fffffc00f},
	Mask{54, 64, 18, 0xffffc00fffffffff},
	Mask{23, 32, 18, 0xffffc01fffffc01f},
	Mask{55, 64, 18, 0xffffc01fffffffff},
	Mask{24, 32, 18, 0xffffc03fffffc03f},
	Mask{56, 64, 18, 0xffffc03fffffffff},
	Mask{25, 32, 18, 0xffffc07fffffc07f},
	Mask{57, 64, 18, 0xffffc07fffffffff},
	Mask{26, 32, 18, 0xffffc0ffffffc0ff},
	Mask{58, 64, 18, 0xffffc0ffffffffff},
	Mask{27, 32, 18, 0xffffc1ffffffc1ff},
	Mask{59, 64, 18, 0xffffc1ffffffffff},
	Mask{28, 32, 18, 0xffffc3ffffffc3ff},
	Mask{60, 64, 18, 0xffffc3ffffffffff},
	Mask{29, 32, 18, 0xffffc7ffffffc7ff},
	Mask{61, 64, 18, 0xffffc7ffffffffff},
	Mask{30, 32, 18, 0xffffcfffffffcfff},
	Mask{62, 64, 18, 0xffffcfffffffffff},
	Mask{31, 32, 18, 0xffffdfffffffdfff},
	Mask{63, 64, 18, 0xffffdfffffffffff},
	Mask{19, 64, 19, 0xffffe00000000000},
	Mask{20, 64, 19, 0xffffe00000000001},
	Mask{21, 64, 19, 0xffffe00000000003},
	Mask{22, 64, 19, 0xffffe00000000007},
	Mask{23, 64, 19, 0xffffe0000000000f},
	Mask{24, 64, 19, 0xffffe0000000001f},
	Mask{25, 64, 19, 0xffffe0000000003f},
	Mask{26, 64, 19, 0xffffe0000000007f},
	Mask{27, 64, 19, 0xffffe000000000ff},
	Mask{28, 64, 19, 0xffffe000000001ff},
	Mask{29, 64, 19, 0xffffe000000003ff},
	Mask{30, 64, 19, 0xffffe000000007ff},
	Mask{31, 64, 19, 0xffffe00000000fff},
	Mask{32, 64, 19, 0xffffe00000001fff},
	Mask{33, 64, 19, 0xffffe00000003fff},
	Mask{34, 64, 19, 0xffffe00000007fff},
	Mask{35, 64, 19, 0xffffe0000000ffff},
	Mask{36, 64, 19, 0xffffe0000001ffff},
	Mask{37, 64, 19, 0xffffe0000003ffff},
	Mask{38, 64, 19, 0xffffe0000007ffff},
	Mask{39, 64, 19, 0xffffe000000fffff},
	Mask{40, 64, 19, 0xffffe000001fffff},
	Mask{41, 64, 19, 0xffffe000003fffff},
	Mask{42, 64, 19, 0xffffe000007fffff},
	Mask{43, 64, 19, 0xffffe00000ffffff},
	Mask{44, 64, 19, 0xffffe00001ffffff},
	Mask{45, 64, 19, 0xffffe00003ffffff},
	Mask{46, 64, 19, 0xffffe00007ffffff},
	Mask{47, 64, 19, 0xffffe0000fffffff},
	Mask{48, 64, 19, 0xffffe0001fffffff},
	Mask{49, 64, 19, 0xffffe0003fffffff},
	Mask{50, 64, 19, 0xffffe0007fffffff},
	Mask{19, 32, 19, 0xffffe000ffffe000},
	Mask{51, 64, 19, 0xffffe000ffffffff},
	Mask{20, 32, 19, 0xffffe001ffffe001},
	Mask{52, 64, 19, 0xffffe001ffffffff},
	Mask{21, 32, 19, 0xffffe003ffffe003},
	Mask{53, 64, 19, 0xffffe003ffffffff},
	Mask{22, 32, 19, 0xffffe007ffffe007},
	Mask{54, 64, 19, 0xffffe007ffffffff},
	Mask{23, 32, 19, 0xffffe00fffffe00f},
	Mask{55, 64, 19, 0xffffe00fffffffff},
	Mask{24, 32, 19, 0xffffe01fffffe01f},
	Mask{56, 64, 19, 0xffffe01fffffffff},
	Mask{25, 32, 19, 0xffffe03fffffe03f},
	Mask{57, 64, 19, 0xffffe03fffffffff},
	Mask{26, 32, 19, 0xffffe07fffffe07f},
	Mask{58, 64, 19, 0xffffe07fffffffff},
	Mask{27, 32, 19, 0xffffe0ffffffe0ff},
	Mask{59, 64, 19, 0xffffe0ffffffffff},
	Mask{28, 32, 19, 0xffffe1ffffffe1ff},
	Mask{60, 64, 19, 0xffffe1ffffffffff},
	Mask{29, 32, 19, 0xffffe3ffffffe3ff},
	Mask{61, 64, 19, 0xffffe3ffffffffff},
	Mask{30, 32, 19, 0xffffe7ffffffe7ff},
	Mask{62, 64, 19, 0xffffe7ffffffffff},
	Mask{31, 32, 19, 0xffffefffffffefff},
	Mask{63, 64, 19, 0xffffefffffffffff},
	Mask{20, 64, 20, 0xfffff00000000000},
	Mask{21, 64, 20, 0xfffff00000000001},
	Mask{22, 64, 20, 0xfffff00000000003},
	Mask{23, 64, 20, 0xfffff00000000007},
	Mask{24, 64, 20, 0xfffff0000000000f},
	Mask{25, 64, 20, 0xfffff0000000001f},
	Mask{26, 64, 20, 0xfffff0000000003f},
	Mask{27, 64, 20, 0xfffff0000000007f},
	Mask{28, 64, 20, 0xfffff000000000ff},
	Mask{29, 64, 20, 0xfffff000000001ff},
	Mask{30, 64, 20, 0xfffff000000003ff},
	Mask{31, 64, 20, 0xfffff000000007ff},
	Mask{32, 64, 20, 0xfffff00000000fff},
	Mask{33, 64, 20, 0xfffff00000001fff},
	Mask{34, 64, 20, 0xfffff00000003fff},
	Mask{35, 64, 20, 0xfffff00000007fff},
	Mask{36, 64, 20, 0xfffff0000000ffff},
	Mask{37, 64, 20, 0xfffff0000001ffff},
	Mask{38, 64, 20, 0xfffff0000003ffff},
	Mask{39, 64, 20, 0xfffff0000007ffff},
	Mask{40, 64, 20, 0xfffff000000fffff},
	Mask{41, 64, 20, 0xfffff000001fffff},
	Mask{42, 64, 20, 0xfffff000003fffff},
	Mask{43, 64, 20, 0xfffff000007fffff},
	Mask{44, 64, 20, 0xfffff00000ffffff},
	Mask{45, 64, 20, 0xfffff00001ffffff},
	Mask{46, 64, 20, 0xfffff00003ffffff},
	Mask{47, 64, 20, 0xfffff00007ffffff},
	Mask{48, 64, 20, 0xfffff0000fffffff},
	Mask{49, 64, 20, 0xfffff0001fffffff},
	Mask{50, 64, 20, 0xfffff0003fffffff},
	Mask{51, 64, 20, 0xfffff0007fffffff},
	Mask{20, 32, 20, 0xfffff000fffff000},
	Mask{52, 64, 20, 0xfffff000ffffffff},
	Mask{21, 32, 20, 0xfffff001fffff001},
	Mask{53, 64, 20, 0xfffff001ffffffff},
	Mask{22, 32, 20, 0xfffff003fffff003},
	Mask{54, 64, 20, 0xfffff003ffffffff},
	Mask{23, 32, 20, 0xfffff007fffff007},
	Mask{55, 64, 20, 0xfffff007ffffffff},
	Mask{24, 32, 20, 0xfffff00ffffff00f},
	Mask{56, 64, 20, 0xfffff00fffffffff},
	Mask{25, 32, 20, 0xfffff01ffffff01f},
	Mask{57, 64, 20, 0xfffff01fffffffff},
	Mask{26, 32, 20, 0xfffff03ffffff03f},
	Mask{58, 64, 20, 0xfffff03fffffffff},
	Mask{27, 32, 20, 0xfffff07ffffff07f},
	Mask{59, 64, 20, 0xfffff07fffffffff},
	Mask{28, 32, 20, 0xfffff0fffffff0ff},
	Mask{60, 64, 20, 0xfffff0ffffffffff},
	Mask{29, 32, 20, 0xfffff1fffffff1ff},
	Mask{61, 64, 20, 0xfffff1ffffffffff},
	Mask{30, 32, 20, 0xfffff3fffffff3ff},
	Mask{62, 64, 20, 0xfffff3ffffffffff},
	Mask{31, 32, 20, 0xfffff7fffffff7ff},
	Mask{63, 64, 20, 0xfffff7ffffffffff},
	Mask{21, 64, 21, 0xfffff80000000000},
	Mask{22, 64, 21, 0xfffff80000000001},
	Mask{23, 64, 21, 0xfffff80000000003},
	Mask{24, 64, 21, 0xfffff80000000007},
	Mask{25, 64, 21, 0xfffff8000000000f},
	Mask{26, 64, 21, 0xfffff8000000001f},
	Mask{27, 64, 21, 0xfffff8000000003f},
	Mask{28, 64, 21, 0xfffff8000000007f},
	Mask{29, 64, 21, 0xfffff800000000ff},
	Mask{30, 64, 21, 0xfffff800000001ff},
	Mask{31, 64, 21, 0xfffff800000003ff},
	Mask{32, 64, 21, 0xfffff800000007ff},
	Mask{33, 64, 21, 0xfffff80000000fff},
	Mask{34, 64, 21, 0xfffff80000001fff},
	Mask{35, 64, 21, 0xfffff80000003fff},
	Mask{36, 64, 21, 0xfffff80000007fff},
	Mask{37, 64, 21, 0xfffff8000000ffff},
	Mask{38, 64, 21, 0xfffff8000001ffff},
	Mask{39, 64, 21, 0xfffff8000003ffff},
	Mask{40, 64, 21, 0xfffff8000007ffff},
	Mask{41, 64, 21, 0xfffff800000fffff},
	Mask{42, 64, 21, 0xfffff800001fffff},
	Mask{43, 64, 21, 0xfffff800003fffff},
	Mask{44, 64, 21, 0xfffff800007fffff},
	Mask{45, 64, 21, 0xfffff80000ffffff},
	Mask{46, 64, 21, 0xfffff80001ffffff},
	Mask{47, 64, 21, 0xfffff80003ffffff},
	Mask{48, 64, 21, 0xfffff80007ffffff},
	Mask{49, 64, 21, 0xfffff8000fffffff},
	Mask{50, 64, 21, 0xfffff8001fffffff},
	Mask{51, 64, 21, 0xfffff8003fffffff},
	Mask{52, 64, 21, 0xfffff8007fffffff},
	Mask{21, 32, 21, 0xfffff800fffff800},
	Mask{53, 64, 21, 0xfffff800ffffffff},
	Mask{22, 32, 21, 0xfffff801fffff801},
	Mask{54, 64, 21, 0xfffff801ffffffff},
	Mask{23, 32, 21, 0xfffff803fffff803},
	Mask{55, 64, 21, 0xfffff803ffffffff},
	Mask{24, 32, 21, 0xfffff807fffff807},
	Mask{56, 64, 21, 0xfffff807ffffffff},
	Mask{25, 32, 21, 0xfffff80ffffff80f},
	Mask{57, 64, 21, 0xfffff80fffffffff},
	Mask{26, 32, 21, 0xfffff81ffffff81f},
	Mask{58, 64, 21, 0xfffff81fffffffff},
	Mask{27, 32, 21, 0xfffff83ffffff83f},
	Mask{59, 64, 21, 0xfffff83fffffffff},
	Mask{28, 32, 21, 0xfffff87ffffff87f},
	Mask{60, 64, 21, 0xfffff87fffffffff},
	Mask{29, 32, 21, 0xfffff8fffffff8ff},
	Mask{61, 64, 21, 0xfffff8ffffffffff},
	Mask{30, 32, 21, 0xfffff9fffffff9ff},
	Mask{62, 64, 21, 0xfffff9ffffffffff},
	Mask{31, 32, 21, 0xfffffbfffffffbff},
	Mask{63, 64, 21, 0xfffffbffffffffff},
	Mask{22, 64, 22, 0xfffffc0000000000},
	Mask{23, 64, 22, 0xfffffc0000000001},
	Mask{24, 64, 22, 0xfffffc0000000003},
	Mask{25, 64, 22, 0xfffffc0000000007},
	Mask{26, 64, 22, 0xfffffc000000000f},
	Mask{27, 64, 22, 0xfffffc000000001f},
	Mask{28, 64, 22, 0xfffffc000000003f},
	Mask{29, 64, 22, 0xfffffc000000007f},
	Mask{30, 64, 22, 0xfffffc00000000ff},
	Mask{31, 64, 22, 0xfffffc00000001ff},
	Mask{32, 64, 22, 0xfffffc00000003ff},
	Mask{33, 64, 22, 0xfffffc00000007ff},
	Mask{34, 64, 22, 0xfffffc0000000fff},
	Mask{35, 64, 22, 0xfffffc0000001fff},
	Mask{36, 64, 22, 0xfffffc0000003fff},
	Mask{37, 64, 22, 0xfffffc0000007fff},
	Mask{38, 64, 22, 0xfffffc000000ffff},
	Mask{39, 64, 22, 0xfffffc000001ffff},
	Mask{40, 64, 22, 0xfffffc000003ffff},
	Mask{41, 64, 22, 0xfffffc000007ffff},
	Mask{42, 64, 22, 0xfffffc00000fffff},
	Mask{43, 64, 22, 0xfffffc00001fffff},
	Mask{44, 64, 22, 0xfffffc00003fffff},
	Mask{45, 64, 22, 0xfffffc00007fffff},
	Mask{46, 64, 22, 0xfffffc0000ffffff},
	Mask{47, 64, 22, 0xfffffc0001ffffff},
	Mask{48, 64, 22, 0xfffffc0003ffffff},
	Mask{49, 64, 22, 0xfffffc0007ffffff},
	Mask{50, 64, 22, 0xfffffc000fffffff},
	Mask{51, 64, 22, 0xfffffc001fffffff},
	Mask{52, 64, 22, 0xfffffc003fffffff},
	Mask{53, 64, 22, 0xfffffc007fffffff},
	Mask{22, 32, 22, 0xfffffc00fffffc00},
	Mask{54, 64, 22, 0xfffffc00ffffffff},
	Mask{23, 32, 22, 0xfffffc01fffffc01},
	Mask{55, 64, 22, 0xfffffc01ffffffff},
	Mask{24, 32, 22, 0xfffffc03fffffc03},
	Mask{56, 64, 22, 0xfffffc03ffffffff},
	Mask{25, 32, 22, 0xfffffc07fffffc07},
	Mask{57, 64, 22, 0xfffffc07ffffffff},
	Mask{26, 32, 22, 0xfffffc0ffffffc0f},
	Mask{58, 64, 22, 0xfffffc0fffffffff},
	Mask{27, 32, 22, 0xfffffc1ffffffc1f},
	Mask{59, 64, 22, 0xfffffc1fffffffff},
	Mask{28, 32, 22, 0xfffffc3ffffffc3f},
	Mask{60, 64, 22, 0xfffffc3fffffffff},
	Mask{29, 32, 22, 0xfffffc7ffffffc7f},
	Mask{61, 64, 22, 0xfffffc7fffffffff},
	Mask{30, 32, 22, 0xfffffcfffffffcff},
	Mask{62, 64, 22, 0xfffffcffffffffff},
	Mask{31, 32, 22, 0xfffffdfffffffdff},
	Mask{63, 64, 22, 0xfffffdffffffffff},
	Mask{23, 64, 23, 0xfffffe0000000000},
	Mask{24, 64, 23, 0xfffffe0000000001},
	Mask{25, 64, 23, 0xfffffe0000000003},
	Mask{26, 64, 23, 0xfffffe0000000007},
	Mask{27, 64, 23, 0xfffffe000000000f},
	Mask{28, 64, 23, 0xfffffe000000001f},
	Mask{29, 64, 23, 0xfffffe000000003f},
	Mask{30, 64, 23, 0xfffffe000000007f},
	Mask{31, 64, 23, 0xfffffe00000000ff},
	Mask{32, 64, 23, 0xfffffe00000001ff},
	Mask{33, 64, 23, 0xfffffe00000003ff},
	Mask{34, 64, 23, 0xfffffe00000007ff},
	Mask{35, 64, 23, 0xfffffe0000000fff},
	Mask{36, 64, 23, 0xfffffe0000001fff},
	Mask{37, 64, 23, 0xfffffe0000003fff},
	Mask{38, 64, 23, 0xfffffe0000007fff},
	Mask{39, 64, 23, 0xfffffe000000ffff},
	Mask{40, 64, 23, 0xfffffe000001ffff},
	Mask{41, 64, 23, 0xfffffe000003ffff},
	Mask{42, 64, 23, 0xfffffe000007ffff},
	Mask{43, 64, 23, 0xfffffe00000fffff},
	Mask{44, 64, 23, 0xfffffe00001fffff},
	Mask{45, 64, 23, 0xfffffe00003fffff},
	Mask{46, 64, 23, 0xfffffe00007fffff},
	Mask{47, 64, 23, 0xfffffe0000ffffff},
	Mask{48, 64, 23, 0xfffffe0001ffffff},
	Mask{49, 64, 23, 0xfffffe0003ffffff},
	Mask{50, 64, 23, 0xfffffe0007ffffff},
	Mask{51, 64, 23, 0xfffffe000fffffff},
	Mask{52, 64, 23, 0xfffffe001fffffff},
	Mask{53, 64, 23, 0xfffffe003fffffff},
	Mask{54, 64, 23, 0xfffffe007fffffff},
	Mask{23, 32, 23, 0xfffffe00fffffe00},
	Mask{55, 64, 23, 0xfffffe00ffffffff},
	Mask{24, 32, 23, 0xfffffe01fffffe01},
	Mask{56, 64, 23, 0xfffffe01ffffffff},
	Mask{25, 32, 23, 0xfffffe03fffffe03},
	Mask{57, 64, 23, 0xfffffe03ffffffff},
	Mask{26, 32, 23, 0xfffffe07fffffe07},
	Mask{58, 64, 23, 0xfffffe07ffffffff},
	Mask{27, 32, 23, 0xfffffe0ffffffe0f},
	Mask{59, 64, 23, 0xfffffe0fffffffff},
	Mask{28, 32, 23, 0xfffffe1ffffffe1f},
	Mask{60, 64, 23, 0xfffffe1fffffffff},
	Mask{29, 32, 23, 0xfffffe3ffffffe3f},
	Mask{61, 64, 23, 0xfffffe3fffffffff},
	Mask{30, 32, 23, 0xfffffe7ffffffe7f},
	Mask{62, 64, 23, 0xfffffe7fffffffff},
	Mask{31, 32, 23, 0xfffffefffffffeff},
	Mask{63, 64, 23, 0xfffffeffffffffff},
	Mask{24, 64, 24, 0xffffff0000000000},
	Mask{25, 64, 24, 0xffffff0000000001},
	Mask{26, 64, 24, 0xffffff0000000003},
	Mask{27, 64, 24, 0xffffff0000000007},
	Mask{28, 64, 24, 0xffffff000000000f},
	Mask{29, 64, 24, 0xffffff000000001f},
	Mask{30, 64, 24, 0xffffff000000003f},
	Mask{31, 64, 24, 0xffffff000000007f},
	Mask{32, 64, 24, 0xffffff00000000ff},
	Mask{33, 64, 24, 0xffffff00000001ff},
	Mask{34, 64, 24, 0xffffff00000003ff},
	Mask{35, 64, 24, 0xffffff00000007ff},
	Mask{36, 64, 24, 0xffffff0000000fff},
	Mask{37, 64, 24, 0xffffff0000001fff},
	Mask{38, 64, 24, 0xffffff0000003fff},
	Mask{39, 64, 24, 0xffffff0000007fff},
	Mask{40, 64, 24, 0xffffff000000ffff},
	Mask{41, 64, 24, 0xffffff000001ffff},
	Mask{42, 64, 24, 0xffffff000003ffff},
	Mask{43, 64, 24, 0xffffff000007ffff},
	Mask{44, 64, 24, 0xffffff00000fffff},
	Mask{45, 64, 24, 0xffffff00001fffff},
	Mask{46, 64, 24, 0xffffff00003fffff},
	Mask{47, 64, 24, 0xffffff00007fffff},
	Mask{48, 64, 24, 0xffffff0000ffffff},
	Mask{49, 64, 24, 0xffffff0001ffffff},
	Mask{50, 64, 24, 0xffffff0003ffffff},
	Mask{51, 64, 24, 0xffffff0007ffffff},
	Mask{52, 64, 24, 0xffffff000fffffff},
	Mask{53, 64, 24, 0xffffff001fffffff},
	Mask{54, 64, 24, 0xffffff003fffffff},
	Mask{55, 64, 24, 0xffffff007fffffff},
	Mask{24, 32, 24, 0xffffff00ffffff00},
	Mask{56, 64, 24, 0xffffff00ffffffff},
	Mask{25, 32, 24, 0xffffff01ffffff01},
	Mask{57, 64, 24, 0xffffff01ffffffff},
	Mask{26, 32, 24, 0xffffff03ffffff03},
	Mask{58, 64, 24, 0xffffff03ffffffff},
	Mask{27, 32, 24, 0xffffff07ffffff07},
	Mask{59, 64, 24, 0xffffff07ffffffff},
	Mask{28, 32, 24, 0xffffff0fffffff0f},
	Mask{60, 64, 24, 0xffffff0fffffffff},
	Mask{29, 32, 24, 0xffffff1fffffff1f},
	Mask{61, 64, 24, 0xffffff1fffffffff},
	Mask{30, 32, 24, 0xffffff3fffffff3f},
	Mask{62, 64, 24, 0xffffff3fffffffff},
	Mask{31, 32, 24, 0xffffff7fffffff7f},
	Mask{63, 64, 24, 0xffffff7fffffffff},
	Mask{25, 64, 25, 0xffffff8000000000},
	Mask{26, 64, 25, 0xffffff8000000001},
	Mask{27, 64, 25, 0xffffff8000000003},
	Mask{28, 64, 25, 0xffffff8000000007},
	Mask{29, 64, 25, 0xffffff800000000f},
	Mask{30, 64, 25, 0xffffff800000001f},
	Mask{31, 64, 25, 0xffffff800000003f},
	Mask{32, 64, 25, 0xffffff800000007f},
	Mask{33, 64, 25, 0xffffff80000000ff},
	Mask{34, 64, 25, 0xffffff80000001ff},
	Mask{35, 64, 25, 0xffffff80000003ff},
	Mask{36, 64, 25, 0xffffff80000007ff},
	Mask{37, 64, 25, 0xffffff8000000fff},
	Mask{38, 64, 25, 0xffffff8000001fff},
	Mask{39, 64, 25, 0xffffff8000003fff},
	Mask{40, 64, 25, 0xffffff8000007fff},
	Mask{41, 64, 25, 0xffffff800000ffff},
	Mask{42, 64, 25, 0xffffff800001ffff},
	Mask{43, 64, 25, 0xffffff800003ffff},
	Mask{44, 64, 25, 0xffffff800007ffff},
	Mask{45, 64, 25, 0xffffff80000fffff},
	Mask{46, 64, 25, 0xffffff80001fffff},
	Mask{47, 64, 25, 0xffffff80003fffff},
	Mask{48, 64, 25, 0xffffff80007fffff},
	Mask{49, 64, 25, 0xffffff8000ffffff},
	Mask{50, 64, 25, 0xffffff8001ffffff},
	Mask{51, 64, 25, 0xffffff8003ffffff},
	Mask{52, 64, 25, 0xffffff8007ffffff},
	Mask{53, 64, 25, 0xffffff800fffffff},
	Mask{54, 64, 25, 0xffffff801fffffff},
	Mask{55, 64, 25, 0xffffff803fffffff},
	Mask{56, 64, 25, 0xffffff807fffffff},
	Mask{25, 32, 25, 0xffffff80ffffff80},
	Mask{57, 64, 25, 0xffffff80ffffffff},
	Mask{26, 32, 25, 0xffffff81ffffff81},
	Mask{58, 64, 25, 0xffffff81ffffffff},
	Mask{27, 32, 25, 0xffffff83ffffff83},
	Mask{59, 64, 25, 0xffffff83ffffffff},
	Mask{28, 32, 25, 0xffffff87ffffff87},
	Mask{60, 64, 25, 0xffffff87ffffffff},
	Mask{29, 32, 25, 0xffffff8fffffff8f},
	Mask{61, 64, 25, 0xffffff8fffffffff},
	Mask{30, 32, 25, 0xffffff9fffffff9f},
	Mask{62, 64, 25, 0xffffff9fffffffff},
	Mask{31, 32, 25, 0xffffffbfffffffbf},
	Mask{63, 64, 25, 0xffffffbfffffffff},
	Mask{26, 64, 26, 0xffffffc000000000},
	Mask{27, 64, 26, 0xffffffc000000001},
	Mask{28, 64, 26, 0xffffffc000000003},
	Mask{29, 64, 26, 0xffffffc000000007},
	Mask{30, 64, 26, 0xffffffc00000000f},
	Mask{31, 64, 26, 0xffffffc00000001f},
	Mask{32, 64, 26, 0xffffffc00000003f},
	Mask{33, 64, 26, 0xffffffc00000007f},
	Mask{34, 64, 26, 0xffffffc0000000ff},
	Mask{35, 64, 26, 0xffffffc0000001ff},
	Mask{36, 64, 26, 0xffffffc0000003ff},
	Mask{37, 64, 26, 0xffffffc0000007ff},
	Mask{38, 64, 26, 0xffffffc000000fff},
	Mask{39, 64, 26, 0xffffffc000001fff},
	Mask{40, 64, 26, 0xffffffc000003fff},
	Mask{41, 64, 26, 0xffffffc000007fff},
	Mask{42, 64, 26, 0xffffffc00000ffff},
	Mask{43, 64, 26, 0xffffffc00001ffff},
	Mask{44, 64, 26, 0xffffffc00003ffff},
	Mask{45, 64, 26, 0xffffffc00007ffff},
	Mask{46, 64, 26, 0xffffffc0000fffff},
	Mask{47, 64, 26, 0xffffffc0001fffff},
	Mask{48, 64, 26, 0xffffffc0003fffff},
	Mask{49, 64, 26, 0xffffffc0007fffff},
	Mask{50, 64, 26, 0xffffffc000ffffff},
	Mask{51, 64, 26, 0xffffffc001ffffff},
	Mask{52, 64, 26, 0xffffffc003ffffff},
	Mask{53, 64, 26, 0xffffffc007ffffff},
	Mask{54, 64, 26, 0xffffffc00fffffff},
	Mask{55, 64, 26, 0xffffffc01fffffff},
	Mask{56, 64, 26, 0xffffffc03fffffff},
	Mask{57, 64, 26, 0xffffffc07fffffff},
	Mask{26, 32, 26, 0xffffffc0ffffffc0},
	Mask{58, 64, 26, 0xffffffc0ffffffff},
	Mask{27, 32, 26, 0xffffffc1ffffffc1},
	Mask{59, 64, 26, 0xffffffc1ffffffff},
	Mask{28, 32, 26, 0xffffffc3ffffffc3},
	Mask{60, 64, 26, 0xffffffc3ffffffff},
	Mask{29, 32, 26, 0xffffffc7ffffffc7},
	Mask{61, 64, 26, 0xffffffc7ffffffff},
	Mask{30, 32, 26, 0xffffffcfffffffcf},
	Mask{62, 64, 26, 0xffffffcfffffffff},
	Mask{31, 32, 26, 0xffffffdfffffffdf},
	Mask{63, 64, 26, 0xffffffdfffffffff},
	Mask{27, 64, 27, 0xffffffe000000000},
	Mask{28, 64, 27, 0xffffffe000000001},
	Mask{29, 64, 27, 0xffffffe000000003},
	Mask{30, 64, 27, 0xffffffe000000007},
	Mask{31, 64, 27, 0xffffffe00000000f},
	Mask{32, 64, 27, 0xffffffe00000001f},
	Mask{33, 64, 27, 0xffffffe00000003f},
	Mask{34, 64, 27, 0xffffffe00000007f},
	Mask{35, 64, 27, 0xffffffe0000000ff},
	Mask{36, 64, 27, 0xffffffe0000001ff},
	Mask{37, 64, 27, 0xffffffe0000003ff},
	Mask{38, 64, 27, 0xffffffe0000007ff},
	Mask{39, 64, 27, 0xffffffe000000fff},
	Mask{40, 64, 27, 0xffffffe000001fff},
	Mask{41, 64, 27, 0xffffffe000003fff},
	Mask{42, 64, 27, 0xffffffe000007fff},
	Mask{43, 64, 27, 0xffffffe00000ffff},
	Mask{44, 64, 27, 0xffffffe00001ffff},
	Mask{45, 64, 27, 0xffffffe00003ffff},
	Mask{46, 64, 27, 0xffffffe00007ffff},
	Mask{47, 64, 27, 0xffffffe0000fffff},
	Mask{48, 64, 27, 0xffffffe0001fffff},
	Mask{49, 64, 27, 0xffffffe0003fffff},
	Mask{50, 64, 27, 0xffffffe0007fffff},
	Mask{51, 64, 27, 0xffffffe000ffffff},
	Mask{52, 64, 27, 0xffffffe001ffffff},
	Mask{53, 64, 27, 0xffffffe003ffffff},
	Mask{54, 64, 27, 0xffffffe007ffffff},
	Mask{55, 64, 27, 0xffffffe00fffffff},
	Mask{56, 64, 27, 0xffffffe01fffffff},
	Mask{57, 64, 27, 0xffffffe03fffffff},
	Mask{58, 64, 27, 0xffffffe07fffffff},
	Mask{27, 32, 27, 0xffffffe0ffffffe0},
	Mask{59, 64, 27, 0xffffffe0ffffffff},
	Mask{28, 32, 27, 0xffffffe1ffffffe1},
	Mask{60, 64, 27, 0xffffffe1ffffffff},
	Mask{29, 32, 27, 0xffffffe3ffffffe3},
	Mask{61, 64, 27, 0xffffffe3ffffffff},
	Mask{30, 32, 27, 0xffffffe7ffffffe7},
	Mask{62, 64, 27, 0xffffffe7ffffffff},
	Mask{31, 32, 27, 0xffffffefffffffef},
	Mask{63, 64, 27, 0xffffffefffffffff},
	Mask{28, 64, 28, 0xfffffff000000000},
	Mask{29, 64, 28, 0xfffffff000000001},
	Mask{30, 64, 28, 0xfffffff000000003},
	Mask{31, 64, 28, 0xfffffff000000007},
	Mask{32, 64, 28, 0xfffffff00000000f},
	Mask{33, 64, 28, 0xfffffff00000001f},
	Mask{34, 64, 28, 0xfffffff00000003f},
	Mask{35, 64, 28, 0xfffffff00000007f},
	Mask{36, 64, 28, 0xfffffff0000000ff},
	Mask{37, 64, 28, 0xfffffff0000001ff},
	Mask{38, 64, 28, 0xfffffff0000003ff},
	Mask{39, 64, 28, 0xfffffff0000007ff},
	Mask{40, 64, 28, 0xfffffff000000fff},
	Mask{41, 64, 28, 0xfffffff000001fff},
	Mask{42, 64, 28, 0xfffffff000003fff},
	Mask{43, 64, 28, 0xfffffff000007fff},
	Mask{44, 64, 28, 0xfffffff00000ffff},
	Mask{45, 64, 28, 0xfffffff00001ffff},
	Mask{46, 64, 28, 0xfffffff00003ffff},
	Mask{47, 64, 28, 0xfffffff00007ffff},
	Mask{48, 64, 28, 0xfffffff0000fffff},
	Mask{49, 64, 28, 0xfffffff0001fffff},
	Mask{50, 64, 28, 0xfffffff0003fffff},
	Mask{51, 64, 28, 0xfffffff0007fffff},
	Mask{52, 64, 28, 0xfffffff000ffffff},
	Mask{53, 64, 28, 0xfffffff001ffffff},
	Mask{54, 64, 28, 0xfffffff003ffffff},
	Mask{55, 64, 28, 0xfffffff007ffffff},
	Mask{56, 64, 28, 0xfffffff00fffffff},
	Mask{57, 64, 28, 0xfffffff01fffffff},
	Mask{58, 64, 28, 0xfffffff03fffffff},
	Mask{59, 64, 28, 0xfffffff07fffffff},
	Mask{28, 32, 28, 0xfffffff0fffffff0},
	Mask{60, 64, 28, 0xfffffff0ffffffff},
	Mask{29, 32, 28, 0xfffffff1fffffff1},
	Mask{61, 64, 28, 0xfffffff1ffffffff},
	Mask{30, 32, 28, 0xfffffff3fffffff3},
	Mask{62, 64, 28, 0xfffffff3ffffffff},
	Mask{31, 32, 28, 0xfffffff7fffffff7},
	Mask{63, 64, 28, 0xfffffff7ffffffff},
	Mask{29, 64, 29, 0xfffffff800000000},
	Mask{30, 64, 29, 0xfffffff800000001},
	Mask{31, 64, 29, 0xfffffff800000003},
	Mask{32, 64, 29, 0xfffffff800000007},
	Mask{33, 64, 29, 0xfffffff80000000f},
	Mask{34, 64, 29, 0xfffffff80000001f},
	Mask{35, 64, 29, 0xfffffff80000003f},
	Mask{36, 64, 29, 0xfffffff80000007f},
	Mask{37, 64, 29, 0xfffffff8000000ff},
	Mask{38, 64, 29, 0xfffffff8000001ff},
	Mask{39, 64, 29, 0xfffffff8000003ff},
	Mask{40, 64, 29, 0xfffffff8000007ff},
	Mask{41, 64, 29, 0xfffffff800000fff},
	Mask{42, 64, 29, 0xfffffff800001fff},
	Mask{43, 64, 29, 0xfffffff800003fff},
	Mask{44, 64, 29, 0xfffffff800007fff},
	Mask{45, 64, 29, 0xfffffff80000ffff},
	Mask{46, 64, 29, 0xfffffff80001ffff},
	Mask{47, 64, 29, 0xfffffff80003ffff},
	Mask{48, 64, 29, 0xfffffff80007ffff},
	Mask{49, 64, 29, 0xfffffff8000fffff},
	Mask{50, 64, 29, 0xfffffff8001fffff},
	Mask{51, 64, 29, 0xfffffff8003fffff},
	Mask{52, 64, 29, 0xfffffff8007fffff},
	Mask{53, 64, 29, 0xfffffff800ffffff},
	Mask{54, 64, 29, 0xfffffff801ffffff},
	Mask{55, 64, 29, 0xfffffff803ffffff},
	Mask{56, 64, 29, 0xfffffff807ffffff},
	Mask{57, 64, 29, 0xfffffff80fffffff},
	Mask{58, 64, 29, 0xfffffff81fffffff},
	Mask{59, 64, 29, 0xfffffff83fffffff},
	Mask{60, 64, 29, 0xfffffff87fffffff},
	Mask{29, 32, 29, 0xfffffff8fffffff8},
	Mask{61, 64, 29, 0xfffffff8ffffffff},
	Mask{30, 32, 29, 0xfffffff9fffffff9},
	Mask{62, 64, 29, 0xfffffff9ffffffff},
	Mask{31, 32, 29, 0xfffffffbfffffffb},
	Mask{63, 64, 29, 0xfffffffbffffffff},
	Mask{30, 64, 30, 0xfffffffc00000000},
	Mask{31, 64, 30, 0xfffffffc00000001},
	Mask{32, 64, 30, 0xfffffffc00000003},
	Mask{33, 64, 30, 0xfffffffc00000007},
	Mask{34, 64, 30, 0xfffffffc0000000f},
	Mask{35, 64, 30, 0xfffffffc0000001f},
	Mask{36, 64, 30, 0xfffffffc0000003f},
	Mask{37, 64, 30, 0xfffffffc0000007f},
	Mask{38, 64, 30, 0xfffffffc000000ff},
	Mask{39, 64, 30, 0xfffffffc000001ff},
	Mask{40, 64, 30, 0xfffffffc000003ff},
	Mask{41, 64, 30, 0xfffffffc000007ff},
	Mask{42, 64, 30, 0xfffffffc00000fff},
	Mask{43, 64, 30, 0xfffffffc00001fff},
	Mask{44, 64, 30, 0xfffffffc00003fff},
	Mask{45, 64, 30, 0xfffffffc00007fff},
	Mask{46, 64, 30, 0xfffffffc0000ffff},
	Mask{47, 64, 30, 0xfffffffc0001ffff},
	Mask{48, 64, 30, 0xfffffffc0003ffff},
	Mask{49, 64, 30, 0xfffffffc0007ffff},
	Mask{50, 64, 30, 0xfffffffc000fffff},
	Mask{51, 64, 30, 0xfffffffc001fffff},
	Mask{52, 64, 30, 0xfffffffc003fffff},
	Mask{53, 64, 30, 0xfffffffc007fffff},
	Mask{54, 64, 30, 0xfffffffc00ffffff},
	Mask{55, 64, 30, 0xfffffffc01ffffff},
	Mask{56, 64, 30, 0xfffffffc03ffffff},
	Mask{57, 64, 30, 0xfffffffc07ffffff},
	Mask{58, 64, 30, 0xfffffffc0fffffff},
	Mask{59, 64, 30, 0xfffffffc1fffffff},
	Mask{60, 64, 30, 0xfffffffc3fffffff},
	Mask{61, 64, 30, 0xfffffffc7fffffff},
	Mask{30, 32, 30, 0xfffffffcfffffffc},
	Mask{62, 64, 30, 0xfffffffcffffffff},
	Mask{31, 32, 30, 0xfffffffdfffffffd},
	Mask{63, 64, 30, 0xfffffffdffffffff},
	Mask{31, 64, 31, 0xfffffffe00000000},
	Mask{32, 64, 31, 0xfffffffe00000001},
	Mask{33, 64, 31, 0xfffffffe00000003},
	Mask{34, 64, 31, 0xfffffffe00000007},
	Mask{35, 64, 31, 0xfffffffe0000000f},
	Mask{36, 64, 31, 0xfffffffe0000001f},
	Mask{37, 64, 31, 0xfffffffe0000003f},
	Mask{38, 64, 31, 0xfffffffe0000007f},
	Mask{39, 64, 31, 0xfffffffe000000ff},
	Mask{40, 64, 31, 0xfffffffe000001ff},
	Mask{41, 64, 31, 0xfffffffe000003ff},
	Mask{42, 64, 31, 0xfffffffe000007ff},
	Mask{43, 64, 31, 0xfffffffe00000fff},
	Mask{44, 64, 31, 0xfffffffe00001fff},
	Mask{45, 64, 31, 0xfffffffe00003fff},
	Mask{46, 64, 31, 0xfffffffe00007fff},
	Mask{47, 64, 31, 0xfffffffe0000ffff},
	Mask{48, 64, 31, 0xfffffffe0001ffff},
	Mask{49, 64, 31, 0xfffffffe0003ffff},
	Mask{50, 64, 31, 0xfffffffe0007ffff},
	Mask{51, 64, 31, 0xfffffffe000fffff},
	Mask{52, 64, 31, 0xfffffffe001fffff},
	Mask{53, 64, 31, 0xfffffffe003fffff},
	Mask{54, 64, 31, 0xfffffffe007fffff},
	Mask{55, 64, 31, 0xfffffffe00ffffff},
	Mask{56, 64, 31, 0xfffffffe01ffffff},
	Mask{57, 64, 31, 0xfffffffe03ffffff},
	Mask{58, 64, 31, 0xfffffffe07ffffff},
	Mask{59, 64, 31, 0xfffffffe0fffffff},
	Mask{60, 64, 31, 0xfffffffe1fffffff},
	Mask{61, 64, 31, 0xfffffffe3fffffff},
	Mask{62, 64, 31, 0xfffffffe7fffffff},
	Mask{31, 32, 31, 0xfffffffefffffffe},
	Mask{63, 64, 31, 0xfffffffeffffffff},
	Mask{32, 64, 32, 0xffffffff00000000},
	Mask{33, 64, 32, 0xffffffff00000001},
	Mask{34, 64, 32, 0xffffffff00000003},
	Mask{35, 64, 32, 0xffffffff00000007},
	Mask{36, 64, 32, 0xffffffff0000000f},
	Mask{37, 64, 32, 0xffffffff0000001f},
	Mask{38, 64, 32, 0xffffffff0000003f},
	Mask{39, 64, 32, 0xffffffff0000007f},
	Mask{40, 64, 32, 0xffffffff000000ff},
	Mask{41, 64, 32, 0xffffffff000001ff},
	Mask{42, 64, 32, 0xffffffff000003ff},
	Mask{43, 64, 32, 0xffffffff000007ff},
	Mask{44, 64, 32, 0xffffffff00000fff},
	Mask{45, 64, 32, 0xffffffff00001fff},
	Mask{46, 64, 32, 0xffffffff00003fff},
	Mask{47, 64, 32, 0xffffffff00007fff},
	Mask{48, 64, 32, 0xffffffff0000ffff},
	Mask{49, 64, 32, 0xffffffff0001ffff},
	Mask{50, 64, 32, 0xffffffff0003ffff},
	Mask{51, 64, 32, 0xffffffff0007ffff},
	Mask{52, 64, 32, 0xffffffff000fffff},
	Mask{53, 64, 32, 0xffffffff001fffff},
	Mask{54, 64, 32, 0xffffffff003fffff},
	Mask{55, 64, 32, 0xffffffff007fffff},
	Mask{56, 64, 32, 0xffffffff00ffffff},
	Mask{57, 64, 32, 0xffffffff01ffffff},
	Mask{58, 64, 32, 0xffffffff03ffffff},
	Mask{59, 64, 32, 0xffffffff07ffffff},
	Mask{60, 64, 32, 0xffffffff0fffffff},
	Mask{61, 64, 32, 0xffffffff1fffffff},
	Mask{62, 64, 32, 0xffffffff3fffffff},
	Mask{63, 64, 32, 0xffffffff7fffffff},
	Mask{33, 64, 33, 0xffffffff80000000},
	Mask{34, 64, 33, 0xffffffff80000001},
	Mask{35, 64, 33, 0xffffffff80000003},
	Mask{36, 64, 33, 0xffffffff80000007},
	Mask{37, 64, 33, 0xffffffff8000000f},
	Mask{38, 64, 33, 0xffffffff8000001f},
	Mask{39, 64, 33, 0xffffffff8000003f},
	Mask{40, 64, 33, 0xffffffff8000007f},
	Mask{41, 64, 33, 0xffffffff800000ff},
	Mask{42, 64, 33, 0xffffffff800001ff},
	Mask{43, 64, 33, 0xffffffff800003ff},
	Mask{44, 64, 33, 0xffffffff800007ff},
	Mask{45, 64, 33, 0xffffffff80000fff},
	Mask{46, 64, 33, 0xffffffff80001fff},
	Mask{47, 64, 33, 0xffffffff80003fff},
	Mask{48, 64, 33, 0xffffffff80007fff},
	Mask{49, 64, 33, 0xffffffff8000ffff},
	Mask{50, 64, 33, 0xffffffff8001ffff},
	Mask{51, 64, 33, 0xffffffff8003ffff},
	Mask{52, 64, 33, 0xffffffff8007ffff},
	Mask{53, 64, 33, 0xffffffff800fffff},
	Mask{54, 64, 33, 0xffffffff801fffff},
	Mask{55, 64, 33, 0xffffffff803fffff},
	Mask{56, 64, 33, 0xffffffff807fffff},
	Mask{57, 64, 33, 0xffffffff80ffffff},
	Mask{58, 64, 33, 0xffffffff81ffffff},
	Mask{59, 64, 33, 0xffffffff83ffffff},
	Mask{60, 64, 33, 0xffffffff87ffffff},
	Mask{61, 64, 33, 0xffffffff8fffffff},
	Mask{62, 64, 33, 0xffffffff9fffffff},
	Mask{63, 64, 33, 0xffffffffbfffffff},
	Mask{34, 64, 34, 0xffffffffc0000000},
	Mask{35, 64, 34, 0xffffffffc0000001},
	Mask{36, 64, 34, 0xffffffffc0000003},
	Mask{37, 64, 34, 0xffffffffc0000007},
	Mask{38, 64, 34, 0xffffffffc000000f},
	Mask{39, 64, 34, 0xffffffffc000001f},
	Mask{40, 64, 34, 0xffffffffc000003f},
	Mask{41, 64, 34, 0xffffffffc000007f},
	Mask{42, 64, 34, 0xffffffffc00000ff},
	Mask{43, 64, 34, 0xffffffffc00001ff},
	Mask{44, 64, 34, 0xffffffffc00003ff},
	Mask{45, 64, 34, 0xffffffffc00007ff},
	Mask{46, 64, 34, 0xffffffffc0000fff},
	Mask{47, 64, 34, 0xffffffffc0001fff},
	Mask{48, 64, 34, 0xffffffffc0003fff},
	Mask{49, 64, 34, 0xffffffffc0007fff},
	Mask{50, 64, 34, 0xffffffffc000ffff},
	Mask{51, 64, 34, 0xffffffffc001ffff},
	Mask{52, 64, 34, 0xffffffffc003ffff},
	Mask{53, 64, 34, 0xffffffffc007ffff},
	Mask{54, 64, 34, 0xffffffffc00fffff},
	Mask{55, 64, 34, 0xffffffffc01fffff},
	Mask{56, 64, 34, 0xffffffffc03fffff},
	Mask{57, 64, 34, 0xffffffffc07fffff},
	Mask{58, 64, 34, 0xffffffffc0ffffff},
	Mask{59, 64, 34, 0xffffffffc1ffffff},
	Mask{60, 64, 34, 0xffffffffc3ffffff},
	Mask{61, 64, 34, 0xffffffffc7ffffff},
	Mask{62, 64, 34, 0xffffffffcfffffff},
	Mask{63, 64, 34, 0xffffffffdfffffff},
	Mask{35, 64, 35, 0xffffffffe0000000},
	Mask{36, 64, 35, 0xffffffffe0000001},
	Mask{37, 64, 35, 0xffffffffe0000003},
	Mask{38, 64, 35, 0xffffffffe0000007},
	Mask{39, 64, 35, 0xffffffffe000000f},
	Mask{40, 64, 35, 0xffffffffe000001f},
	Mask{41, 64, 35, 0xffffffffe000003f},
	Mask{42, 64, 35, 0xffffffffe000007f},
	Mask{43, 64, 35, 0xffffffffe00000ff},
	Mask{44, 64, 35, 0xffffffffe00001ff},
	Mask{45, 64, 35, 0xffffffffe00003ff},
	Mask{46, 64, 35, 0xffffffffe00007ff},
	Mask{47, 64, 35, 0xffffffffe0000fff},
	Mask{48, 64, 35, 0xffffffffe0001fff},
	Mask{49, 64, 35, 0xffffffffe0003fff},
	Mask{50, 64, 35, 0xffffffffe0007fff},
	Mask{51, 64, 35, 0xffffffffe000ffff},
	Mask{52, 64, 35, 0xffffffffe001ffff},
	Mask{53, 64, 35, 0xffffffffe003ffff},
	Mask{54, 64, 35, 0xffffffffe007ffff},
	Mask{55, 64, 35, 0xffffffffe00fffff},
	Mask{56, 64, 35, 0xffffffffe01fffff},
	Mask{57, 64, 35, 0xffffffffe03fffff},
	Mask{58, 64, 35, 0xffffffffe07fffff},
	Mask{59, 64, 35, 0xffffffffe0ffffff},
	Mask{60, 64, 35, 0xffffffffe1ffffff},
	Mask{61, 64, 35, 0xffffffffe3ffffff},
	Mask{62, 64, 35, 0xffffffffe7ffffff},
	Mask{63, 64, 35, 0xffffffffefffffff},
	Mask{36, 64, 36, 0xfffffffff0000000},
	Mask{37, 64, 36, 0xfffffffff0000001},
	Mask{38, 64, 36, 0xfffffffff0000003},
	Mask{39, 64, 36, 0xfffffffff0000007},
	Mask{40, 64, 36, 0xfffffffff000000f},
	Mask{41, 64, 36, 0xfffffffff000001f},
	Mask{42, 64, 36, 0xfffffffff000003f},
	Mask{43, 64, 36, 0xfffffffff000007f},
	Mask{44, 64, 36, 0xfffffffff00000ff},
	Mask{45, 64, 36, 0xfffffffff00001ff},
	Mask{46, 64, 36, 0xfffffffff00003ff},
	Mask{47, 64, 36, 0xfffffffff00007ff},
	Mask{48, 64, 36, 0xfffffffff0000fff},
	Mask{49, 64, 36, 0xfffffffff0001fff},
	Mask{50, 64, 36, 0xfffffffff0003fff},
	Mask{51, 64, 36, 0xfffffffff0007fff},
	Mask{52, 64, 36, 0xfffffffff000ffff},
	Mask{53, 64, 36, 0xfffffffff001ffff},
	Mask{54, 64, 36, 0xfffffffff003ffff},
	Mask{55, 64, 36, 0xfffffffff007ffff},
	Mask{56, 64, 36, 0xfffffffff00fffff},
	Mask{57, 64, 36, 0xfffffffff01fffff},
	Mask{58, 64, 36, 0xfffffffff03fffff},
	Mask{59, 64, 36, 0xfffffffff07fffff},
	Mask{60, 64, 36, 0xfffffffff0ffffff},
	Mask{61, 64, 36, 0xfffffffff1ffffff},
	Mask{62, 64, 36, 0xfffffffff3ffffff},
	Mask{63, 64, 36, 0xfffffffff7ffffff},
	Mask{37, 64, 37, 0xfffffffff8000000},
	Mask{38, 64, 37, 0xfffffffff8000001},
	Mask{39, 64, 37, 0xfffffffff8000003},
	Mask{40, 64, 37, 0xfffffffff8000007},
	Mask{41, 64, 37, 0xfffffffff800000f},
	Mask{42, 64, 37, 0xfffffffff800001f},
	Mask{43, 64, 37, 0xfffffffff800003f},
	Mask{44, 64, 37, 0xfffffffff800007f},
	Mask{45, 64, 37, 0xfffffffff80000ff},
	Mask{46, 64, 37, 0xfffffffff80001ff},
	Mask{47, 64, 37, 0xfffffffff80003ff},
	Mask{48, 64, 37, 0xfffffffff80007ff},
	Mask{49, 64, 37, 0xfffffffff8000fff},
	Mask{50, 64, 37, 0xfffffffff8001fff},
	Mask{51, 64, 37, 0xfffffffff8003fff},
	Mask{52, 64, 37, 0xfffffffff8007fff},
	Mask{53, 64, 37, 0xfffffffff800ffff},
	Mask{54, 64, 37, 0xfffffffff801ffff},
	Mask{55, 64, 37, 0xfffffffff803ffff},
	Mask{56, 64, 37, 0xfffffffff807ffff},
	Mask{57, 64, 37, 0xfffffffff80fffff},
	Mask{58, 64, 37, 0xfffffffff81fffff},
	Mask{59, 64, 37, 0xfffffffff83fffff},
	Mask{60, 64, 37, 0xfffffffff87fffff},
	Mask{61, 64, 37, 0xfffffffff8ffffff},
	Mask{62, 64, 37, 0xfffffffff9ffffff},
	Mask{63, 64, 37, 0xfffffffffbffffff},
	Mask{38, 64, 38, 0xfffffffffc000000},
	Mask{39, 64, 38, 0xfffffffffc000001},
	Mask{40, 64, 38, 0xfffffffffc000003},
	Mask{41, 64, 38, 0xfffffffffc000007},
	Mask{42, 64, 38, 0xfffffffffc00000f},
	Mask{43, 64, 38, 0xfffffffffc00001f},
	Mask{44, 64, 38, 0xfffffffffc00003f},
	Mask{45, 64, 38, 0xfffffffffc00007f},
	Mask{46, 64, 38, 0xfffffffffc0000ff},
	Mask{47, 64, 38, 0xfffffffffc0001ff},
	Mask{48, 64, 38, 0xfffffffffc0003ff},
	Mask{49, 64, 38, 0xfffffffffc0007ff},
	Mask{50, 64, 38, 0xfffffffffc000fff},
	Mask{51, 64, 38, 0xfffffffffc001fff},
	Mask{52, 64, 38, 0xfffffffffc003fff},
	Mask{53, 64, 38, 0xfffffffffc007fff},
	Mask{54, 64, 38, 0xfffffffffc00ffff},
	Mask{55, 64, 38, 0xfffffffffc01ffff},
	Mask{56, 64, 38, 0xfffffffffc03ffff},
	Mask{57, 64, 38, 0xfffffffffc07ffff},
	Mask{58, 64, 38, 0xfffffffffc0fffff},
	Mask{59, 64, 38, 0xfffffffffc1fffff},
	Mask{60, 64, 38, 0xfffffffffc3fffff},
	Mask{61, 64, 38, 0xfffffffffc7fffff},
	Mask{62, 64, 38, 0xfffffffffcffffff},
	Mask{63, 64, 38, 0xfffffffffdffffff},
	Mask{39, 64, 39, 0xfffffffffe000000},
	Mask{40, 64, 39, 0xfffffffffe000001},
	Mask{41, 64, 39, 0xfffffffffe000003},
	Mask{42, 64, 39, 0xfffffffffe000007},
	Mask{43, 64, 39, 0xfffffffffe00000f},
	Mask{44, 64, 39, 0xfffffffffe00001f},
	Mask{45, 64, 39, 0xfffffffffe00003f},
	Mask{46, 64, 39, 0xfffffffffe00007f},
	Mask{47, 64, 39, 0xfffffffffe0000ff},
	Mask{48, 64, 39, 0xfffffffffe0001ff},
	Mask{49, 64, 39, 0xfffffffffe0003ff},
	Mask{50, 64, 39, 0xfffffffffe0007ff},
	Mask{51, 64, 39, 0xfffffffffe000fff},
	Mask{52, 64, 39, 0xfffffffffe001fff},
	Mask{53, 64, 39, 0xfffffffffe003fff},
	Mask{54, 64, 39, 0xfffffffffe007fff},
	Mask{55, 64, 39, 0xfffffffffe00ffff},
	Mask{56, 64, 39, 0xfffffffffe01ffff},
	Mask{57, 64, 39, 0xfffffffffe03ffff},
	Mask{58, 64, 39, 0xfffffffffe07ffff},
	Mask{59, 64, 39, 0xfffffffffe0fffff},
	Mask{60, 64, 39, 0xfffffffffe1fffff},
	Mask{61, 64, 39, 0xfffffffffe3fffff},
	Mask{62, 64, 39, 0xfffffffffe7fffff},
	Mask{63, 64, 39, 0xfffffffffeffffff},
	Mask{40, 64, 40, 0xffffffffff000000},
	Mask{41, 64, 40, 0xffffffffff000001},
	Mask{42, 64, 40, 0xffffffffff000003},
	Mask{43, 64, 40, 0xffffffffff000007},
	Mask{44, 64, 40, 0xffffffffff00000f},
	Mask{45, 64, 40, 0xffffffffff00001f},
	Mask{46, 64, 40, 0xffffffffff00003f},
	Mask{47, 64, 40, 0xffffffffff00007f},
	Mask{48, 64, 40, 0xffffffffff0000ff},
	Mask{49, 64, 40, 0xffffffffff0001ff},
	Mask{50, 64, 40, 0xffffffffff0003ff},
	Mask{51, 64, 40, 0xffffffffff0007ff},
	Mask{52, 64, 40, 0xffffffffff000fff},
	Mask{53, 64, 40, 0xffffffffff001fff},
	Mask{54, 64, 40, 0xffffffffff003fff},
	Mask{55, 64, 40, 0xffffffffff007fff},
	Mask{56, 64, 40, 0xffffffffff00ffff},
	Mask{57, 64, 40, 0xffffffffff01ffff},
	Mask{58, 64, 40, 0xffffffffff03ffff},
	Mask{59, 64, 40, 0xffffffffff07ffff},
	Mask{60, 64, 40, 0xffffffffff0fffff},
	Mask{61, 64, 40, 0xffffffffff1fffff},
	Mask{62, 64, 40, 0xffffffffff3fffff},
	Mask{63, 64, 40, 0xffffffffff7fffff},
	Mask{41, 64, 41, 0xffffffffff800000},
	Mask{42, 64, 41, 0xffffffffff800001},
	Mask{43, 64, 41, 0xffffffffff800003},
	Mask{44, 64, 41, 0xffffffffff800007},
	Mask{45, 64, 41, 0xffffffffff80000f},
	Mask{46, 64, 41, 0xffffffffff80001f},
	Mask{47, 64, 41, 0xffffffffff80003f},
	Mask{48, 64, 41, 0xffffffffff80007f},
	Mask{49, 64, 41, 0xffffffffff8000ff},
	Mask{50, 64, 41, 0xffffffffff8001ff},
	Mask{51, 64, 41, 0xffffffffff8003ff},
	Mask{52, 64, 41, 0xffffffffff8007ff},
	Mask{53, 64, 41, 0xffffffffff800fff},
	Mask{54, 64, 41, 0xffffffffff801fff},
	Mask{55, 64, 41, 0xffffffffff803fff},
	Mask{56, 64, 41, 0xffffffffff807fff},
	Mask{57, 64, 41, 0xffffffffff80ffff},
	Mask{58, 64, 41, 0xffffffffff81ffff},
	Mask{59, 64, 41, 0xffffffffff83ffff},
	Mask{60, 64, 41, 0xffffffffff87ffff},
	Mask{61, 64, 41, 0xffffffffff8fffff},
	Mask{62, 64, 41, 0xffffffffff9fffff},
	Mask{63, 64, 41, 0xffffffffffbfffff},
	Mask{42, 64, 42, 0xffffffffffc00000},
	Mask{43, 64, 42, 0xffffffffffc00001},
	Mask{44, 64, 42, 0xffffffffffc00003},
	Mask{45, 64, 42, 0xffffffffffc00007},
	Mask{46, 64, 42, 0xffffffffffc0000f},
	Mask{47, 64, 42, 0xffffffffffc0001f},
	Mask{48, 64, 42, 0xffffffffffc0003f},
	Mask{49, 64, 42, 0xffffffffffc0007f},
	Mask{50, 64, 42, 0xffffffffffc000ff},
	Mask{51, 64, 42, 0xffffffffffc001ff},
	Mask{52, 64, 42, 0xffffffffffc003ff},
	Mask{53, 64, 42, 0xffffffffffc007ff},
	Mask{54, 64, 42, 0xffffffffffc00fff},
	Mask{55, 64, 42, 0xffffffffffc01fff},
	Mask{56, 64, 42, 0xffffffffffc03fff},
	Mask{57, 64, 42, 0xffffffffffc07fff},
	Mask{58, 64, 42, 0xffffffffffc0ffff},
	Mask{59, 64, 42, 0xffffffffffc1ffff},
	Mask{60, 64, 42, 0xffffffffffc3ffff},
	Mask{61, 64, 42, 0xffffffffffc7ffff},
	Mask{62, 64, 42, 0xffffffffffcfffff},
	Mask{63, 64, 42, 0xffffffffffdfffff},
	Mask{43, 64, 43, 0xffffffffffe00000},
	Mask{44, 64, 43, 0xffffffffffe00001},
	Mask{45, 64, 43, 0xffffffffffe00003},
	Mask{46, 64, 43, 0xffffffffffe00007},
	Mask{47, 64, 43, 0xffffffffffe0000f},
	Mask{48, 64, 43, 0xffffffffffe0001f},
	Mask{49, 64, 43, 0xffffffffffe0003f},
	Mask{50, 64, 43, 0xffffffffffe0007f},
	Mask{51, 64, 43, 0xffffffffffe000ff},
	Mask{52, 64, 43, 0xffffffffffe001ff},
	Mask{53, 64, 43, 0xffffffffffe003ff},
	Mask{54, 64, 43, 0xffffffffffe007ff},
	Mask{55, 64, 43, 0xffffffffffe00fff},
	Mask{56, 64, 43, 0xffffffffffe01fff},
	Mask{57, 64, 43, 0xffffffffffe03fff},
	Mask{58, 64, 43, 0xffffffffffe07fff},
	Mask{59, 64, 43, 0xffffffffffe0ffff},
	Mask{60, 64, 43, 0xffffffffffe1ffff},
	Mask{61, 64, 43, 0xffffffffffe3ffff},
	Mask{62, 64, 43, 0xffffffffffe7ffff},
	Mask{63, 64, 43, 0xffffffffffefffff},
	Mask{44, 64, 44, 0xfffffffffff00000},
	Mask{45, 64, 44, 0xfffffffffff00001},
	Mask{46, 64, 44, 0xfffffffffff00003},
	Mask{47, 64, 44, 0xfffffffffff00007},
	Mask{48, 64, 44, 0xfffffffffff0000f},
	Mask{49, 64, 44, 0xfffffffffff0001f},
	Mask{50, 64, 44, 0xfffffffffff0003f},
	Mask{51, 64, 44, 0xfffffffffff0007f},
	Mask{52, 64, 44, 0xfffffffffff000ff},
	Mask{53, 64, 44, 0xfffffffffff001ff},
	Mask{54, 64, 44, 0xfffffffffff003ff},
	Mask{55, 64, 44, 0xfffffffffff007ff},
	Mask{56, 64, 44, 0xfffffffffff00fff},
	Mask{57, 64, 44, 0xfffffffffff01fff},
	Mask{58, 64, 44, 0xfffffffffff03fff},
	Mask{59, 64, 44, 0xfffffffffff07fff},
	Mask{60, 64, 44, 0xfffffffffff0ffff},
	Mask{61, 64, 44, 0xfffffffffff1ffff},
	Mask{62, 64, 44, 0xfffffffffff3ffff},
	Mask{63, 64, 44, 0xfffffffffff7ffff},
	Mask{45, 64, 45, 0xfffffffffff80000},
	Mask{46, 64, 45, 0xfffffffffff80001},
	Mask{47, 64, 45, 0xfffffffffff80003},
	Mask{48, 64, 45, 0xfffffffffff80007},
	Mask{49, 64, 45, 0xfffffffffff8000f},
	Mask{50, 64, 45, 0xfffffffffff8001f},
	Mask{51, 64, 45, 0xfffffffffff8003f},
	Mask{52, 64, 45, 0xfffffffffff8007f},
	Mask{53, 64, 45, 0xfffffffffff800ff},
	Mask{54, 64, 45, 0xfffffffffff801ff},
	Mask{55, 64, 45, 0xfffffffffff803ff},
	Mask{56, 64, 45, 0xfffffffffff807ff},
	Mask{57, 64, 45, 0xfffffffffff80fff},
	Mask{58, 64, 45, 0xfffffffffff81fff},
	Mask{59, 64, 45, 0xfffffffffff83fff},
	Mask{60, 64, 45, 0xfffffffffff87fff},
	Mask{61, 64, 45, 0xfffffffffff8ffff},
	Mask{62, 64, 45, 0xfffffffffff9ffff},
	Mask{63, 64, 45, 0xfffffffffffbffff},
	Mask{46, 64, 46, 0xfffffffffffc0000},
	Mask{47, 64, 46, 0xfffffffffffc0001},
	Mask{48, 64, 46, 0xfffffffffffc0003},
	Mask{49, 64, 46, 0xfffffffffffc0007},
	Mask{50, 64, 46, 0xfffffffffffc000f},
	Mask{51, 64, 46, 0xfffffffffffc001f},
	Mask{52, 64, 46, 0xfffffffffffc003f},
	Mask{53, 64, 46, 0xfffffffffffc007f},
	Mask{54, 64, 46, 0xfffffffffffc00ff},
	Mask{55, 64, 46, 0xfffffffffffc01ff},
	Mask{56, 64, 46, 0xfffffffffffc03ff},
	Mask{57, 64, 46, 0xfffffffffffc07ff},
	Mask{58, 64, 46, 0xfffffffffffc0fff},
	Mask{59, 64, 46, 0xfffffffffffc1fff},
	Mask{60, 64, 46, 0xfffffffffffc3fff},
	Mask{61, 64, 46, 0xfffffffffffc7fff},
	Mask{62, 64, 46, 0xfffffffffffcffff},
	Mask{63, 64, 46, 0xfffffffffffdffff},
	Mask{47, 64, 47, 0xfffffffffffe0000},
	Mask{48, 64, 47, 0xfffffffffffe0001},
	Mask{49, 64, 47, 0xfffffffffffe0003},
	Mask{50, 64, 47, 0xfffffffffffe0007},
	Mask{51, 64, 47, 0xfffffffffffe000f},
	Mask{52, 64, 47, 0xfffffffffffe001f},
	Mask{53, 64, 47, 0xfffffffffffe003f},
	Mask{54, 64, 47, 0xfffffffffffe007f},
	Mask{55, 64, 47, 0xfffffffffffe00ff},
	Mask{56, 64, 47, 0xfffffffffffe01ff},
	Mask{57, 64, 47, 0xfffffffffffe03ff},
	Mask{58, 64, 47, 0xfffffffffffe07ff},
	Mask{59, 64, 47, 0xfffffffffffe0fff},
	Mask{60, 64, 47, 0xfffffffffffe1fff},
	Mask{61, 64, 47, 0xfffffffffffe3fff},
	Mask{62, 64, 47, 0xfffffffffffe7fff},
	Mask{63, 64, 47, 0xfffffffffffeffff},
	Mask{48, 64, 48, 0xffffffffffff0000},
	Mask{49, 64, 48, 0xffffffffffff0001},
	Mask{50, 64, 48, 0xffffffffffff0003},
	Mask{51, 64, 48, 0xffffffffffff0007},
	Mask{52, 64, 48, 0xffffffffffff000f},
	Mask{53, 64, 48, 0xffffffffffff001f},
	Mask{54, 64, 48, 0xffffffffffff003f},
	Mask{55, 64, 48, 0xffffffffffff007f},
	Mask{56, 64, 48, 0xffffffffffff00ff},
	Mask{57, 64, 48, 0xffffffffffff01ff},
	Mask{58, 64, 48, 0xffffffffffff03ff},
	Mask{59, 64, 48, 0xffffffffffff07ff},
	Mask{60, 64, 48, 0xffffffffffff0fff},
	Mask{61, 64, 48, 0xffffffffffff1fff},
	Mask{62, 64, 48, 0xffffffffffff3fff},
	Mask{63, 64, 48, 0xffffffffffff7fff},
	Mask{49, 64, 49, 0xffffffffffff8000},
	Mask{50, 64, 49, 0xffffffffffff8001},
	Mask{51, 64, 49, 0xffffffffffff8003},
	Mask{52, 64, 49, 0xffffffffffff8007},
	Mask{53, 64, 49, 0xffffffffffff800f},
	Mask{54, 64, 49, 0xffffffffffff801f},
	Mask{55, 64, 49, 0xffffffffffff803f},
	Mask{56, 64, 49, 0xffffffffffff807f},
	Mask{57, 64, 49, 0xffffffffffff80ff},
	Mask{58, 64, 49, 0xffffffffffff81ff},
	Mask{59, 64, 49, 0xffffffffffff83ff},
	Mask{60, 64, 49, 0xffffffffffff87ff},
	Mask{61, 64, 49, 0xffffffffffff8fff},
	Mask{62, 64, 49, 0xffffffffffff9fff},
	Mask{63, 64, 49, 0xffffffffffffbfff},
	Mask{50, 64, 50, 0xffffffffffffc000},
	Mask{51, 64, 50, 0xffffffffffffc001},
	Mask{52, 64, 50, 0xffffffffffffc003},
	Mask{53, 64, 50, 0xffffffffffffc007},
	Mask{54, 64, 50, 0xffffffffffffc00f},
	Mask{55, 64, 50, 0xffffffffffffc01f},
	Mask{56, 64, 50, 0xffffffffffffc03f},
	Mask{57, 64, 50, 0xffffffffffffc07f},
	Mask{58, 64, 50, 0xffffffffffffc0ff},
	Mask{59, 64, 50, 0xffffffffffffc1ff},
	Mask{60, 64, 50, 0xffffffffffffc3ff},
	Mask{61, 64, 50, 0xffffffffffffc7ff},
	Mask{62, 64, 50, 0xffffffffffffcfff},
	Mask{63, 64, 50, 0xffffffffffffdfff},
	Mask{51, 64, 51, 0xffffffffffffe000},
	Mask{52, 64, 51, 0xffffffffffffe001},
	Mask{53, 64, 51, 0xffffffffffffe003},
	Mask{54, 64, 51, 0xffffffffffffe007},
	Mask{55, 64, 51, 0xffffffffffffe00f},
	Mask{56, 64, 51, 0xffffffffffffe01f},
	Mask{57, 64, 51, 0xffffffffffffe03f},
	Mask{58, 64, 51, 0xffffffffffffe07f},
	Mask{59, 64, 51, 0xffffffffffffe0ff},
	Mask{60, 64, 51, 0xffffffffffffe1ff},
	Mask{61, 64, 51, 0xffffffffffffe3ff},
	Mask{62, 64, 51, 0xffffffffffffe7ff},
	Mask{63, 64, 51, 0xffffffffffffefff},
	Mask{52, 64, 52, 0xfffffffffffff000},
	Mask{53, 64, 52, 0xfffffffffffff001},
	Mask{54, 64, 52, 0xfffffffffffff003},
	Mask{55, 64, 52, 0xfffffffffffff007},
	Mask{56, 64, 52, 0xfffffffffffff00f},
	Mask{57, 64, 52, 0xfffffffffffff01f},
	Mask{58, 64, 52, 0xfffffffffffff03f},
	Mask{59, 64, 52, 0xfffffffffffff07f},
	Mask{60, 64, 52, 0xfffffffffffff0ff},
	Mask{61, 64, 52, 0xfffffffffffff1ff},
	Mask{62, 64, 52, 0xfffffffffffff3ff},
	Mask{63, 64, 52, 0xfffffffffffff7ff},
	Mask{53, 64, 53, 0xfffffffffffff800},
	Mask{54, 64, 53, 0xfffffffffffff801},
	Mask{55, 64, 53, 0xfffffffffffff803},
	Mask{56, 64, 53, 0xfffffffffffff807},
	Mask{57, 64, 53, 0xfffffffffffff80f},
	Mask{58, 64, 53, 0xfffffffffffff81f},
	Mask{59, 64, 53, 0xfffffffffffff83f},
	Mask{60, 64, 53, 0xfffffffffffff87f},
	Mask{61, 64, 53, 0xfffffffffffff8ff},
	Mask{62, 64, 53, 0xfffffffffffff9ff},
	Mask{63, 64, 53, 0xfffffffffffffbff},
	Mask{54, 64, 54, 0xfffffffffffffc00},
	Mask{55, 64, 54, 0xfffffffffffffc01},
	Mask{56, 64, 54, 0xfffffffffffffc03},
	Mask{57, 64, 54, 0xfffffffffffffc07},
	Mask{58, 64, 54, 0xfffffffffffffc0f},
	Mask{59, 64, 54, 0xfffffffffffffc1f},
	Mask{60, 64, 54, 0xfffffffffffffc3f},
	Mask{61, 64, 54, 0xfffffffffffffc7f},
	Mask{62, 64, 54, 0xfffffffffffffcff},
	Mask{63, 64, 54, 0xfffffffffffffdff},
	Mask{55, 64, 55, 0xfffffffffffffe00},
	Mask{56, 64, 55, 0xfffffffffffffe01},
	Mask{57, 64, 55, 0xfffffffffffffe03},
	Mask{58, 64, 55, 0xfffffffffffffe07},
	Mask{59, 64, 55, 0xfffffffffffffe0f},
	Mask{60, 64, 55, 0xfffffffffffffe1f},
	Mask{61, 64, 55, 0xfffffffffffffe3f},
	Mask{62, 64, 55, 0xfffffffffffffe7f},
	Mask{63, 64, 55, 0xfffffffffffffeff},
	Mask{56, 64, 56, 0xffffffffffffff00},
	Mask{57, 64, 56, 0xffffffffffffff01},
	Mask{58, 64, 56, 0xffffffffffffff03},
	Mask{59, 64, 56, 0xffffffffffffff07},
	Mask{60, 64, 56, 0xffffffffffffff0f},
	Mask{61, 64, 56, 0xffffffffffffff1f},
	Mask{62, 64, 56, 0xffffffffffffff3f},
	Mask{63, 64, 56, 0xffffffffffffff7f},
	Mask{57, 64, 57, 0xffffffffffffff80},
	Mask{58, 64, 57, 0xffffffffffffff81},
	Mask{59, 64, 57, 0xffffffffffffff83},
	Mask{60, 64, 57, 0xffffffffffffff87},
	Mask{61, 64, 57, 0xffffffffffffff8f},
	Mask{62, 64, 57, 0xffffffffffffff9f},
	Mask{63, 64, 57, 0xffffffffffffffbf},
	Mask{58, 64, 58, 0xffffffffffffffc0},
	Mask{59, 64, 58, 0xffffffffffffffc1},
	Mask{60, 64, 58, 0xffffffffffffffc3},
	Mask{61, 64, 58, 0xffffffffffffffc7},
	Mask{62, 64, 58, 0xffffffffffffffcf},
	Mask{63, 64, 58, 0xffffffffffffffdf},
	Mask{59, 64, 59, 0xffffffffffffffe0},
	Mask{60, 64, 59, 0xffffffffffffffe1},
	Mask{61, 64, 59, 0xffffffffffffffe3},
	Mask{62, 64, 59, 0xffffffffffffffe7},
	Mask{63, 64, 59, 0xffffffffffffffef},
	Mask{60, 64, 60, 0xfffffffffffffff0},
	Mask{61, 64, 60, 0xfffffffffffffff1},
	Mask{62, 64, 60, 0xfffffffffffffff3},
	Mask{63, 64, 60, 0xfffffffffffffff7},
	Mask{61, 64, 61, 0xfffffffffffffff8},
	Mask{62, 64, 61, 0xfffffffffffffff9},
	Mask{63, 64, 61, 0xfffffffffffffffb},
	Mask{62, 64, 62, 0xfffffffffffffffc},
	Mask{63, 64, 62, 0xfffffffffffffffd},
	Mask{63, 64, 63, 0xfffffffffffffffe},
}

func findmask(v uint64) *Mask {
	var top int
	var bot int
	var mid int
	var m *Mask

	bot = 0
	top = len(bitmasks)
	for bot < top {
		mid = (bot + top) / 2
		m = &bitmasks[mid]
		if v == m.v {
			return m
		}
		if v < m.v {
			top = mid
		} else {

			bot = mid + 1
		}
	}

	return nil
}
