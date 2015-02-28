// cmd/7l/list.c and cmd/7l/sub.c from Vita Nuova.
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
)

const (
	STRINGSZ = 200
)

var strcond = [16]string{
	"EQ",
	"NE",
	"HS",
	"LO",
	"MI",
	"PL",
	"VS",
	"VC",
	"HI",
	"LS",
	"GE",
	"LT",
	"GT",
	"LE",
	"AL",
	"NV",
}

//
// Format conversions
//	%A int		Opcodes (instruction mnemonics)
//
//	%D Addr*	Addresses (instruction operands)
//		Flags: "%lD": seperate the high and low words of a constant by "-"
//
//	%P Prog*	Instructions
//
//	%R int		Registers
//
//	%$ char*	String constant addresses (for internal use only)
//      %^ int          C_* classes (for liblink internal use)

var bigP *obj.Prog

func Pconv(p *obj.Prog) (s string) {
	defer func() {
		if p.Spadj != 0 {
			s = fmt.Sprintf("%s # spadj=%d", s, p.Spadj)
		}
	}()

	suffix := ""
	switch p.Scond {
	case C_XPOST:
		suffix = ".P"
	case C_XPRE:
		suffix = ".W"
	}
	a := int(p.As)
	switch a {
	case obj.ATEXT, obj.AGLOBL:
		return fmt.Sprintf("%.5d (%v)\t%v\t%v,%d,%v", p.Pc, p.Line(), Aconv(a), obj.Dconv(p, &p.From), p.From3.Offset, obj.Dconv(p, &p.To))

	case obj.ADATA:
		return fmt.Sprintf("%.5d (%v)\t%v\t%v/%d,%v", p.Pc, p.Line(), Aconv(a), obj.Dconv(p, &p.From), p.From3.Offset, obj.Dconv(p, &p.To))
	}

	if p.Reg == 0 && p.From3.Type == obj.TYPE_NONE && p.To3.Type == obj.TYPE_NONE {
		return fmt.Sprintf("%.5d (%v)\t%v%s\t%v,%v", p.Pc, p.Line(), Aconv(a), suffix, obj.Dconv(p, &p.From), obj.Dconv(p, &p.To))
	}
	s = fmt.Sprintf("%.5d (%v)\t%v%s\t%v", p.Pc, p.Line(), Aconv(a), suffix, obj.Dconv(p, &p.From))
	if p.From3.Type != obj.TYPE_NONE {
		s += fmt.Sprintf(",%v", obj.Dconv(p, &p.From3))
	}
	if p.Reg != 0 {
		s += fmt.Sprintf(",%v", Rconv(int(p.Reg)))
	}
	if p.To3.Type != obj.TYPE_NONE {
		s += fmt.Sprintf(",%v,%v", obj.Dconv(p, &p.To), obj.Dconv(p, &p.To3))
	} else {
		s += fmt.Sprintf(",%v", obj.Dconv(p, &p.To))
	}
	return s
}

func Aconv(a int) string {
	if a >= obj.AXXX && a < ALAST {
		return Anames[a]
	}
	return "???"
}

func init() {
	obj.RegisterRegister(obj.RBaseARM64, REG_SPECIAL+1024, Rconv)
}

func Rconv(r int) string {
	switch {
	case REG_R0 <= r && r <= REG_R30:
		return fmt.Sprintf("R%d", r-REG_R0)
	case r == REG_R31:
		return "ZR"
	case REG_F0 <= r && r <= REG_F31:
		return fmt.Sprintf("F%d", r-REG_F0)
	case REG_V0 <= r && r <= REG_V31:
		return fmt.Sprintf("V%d", r-REG_F0)
	case r == REGSP:
		return "RSP"
	case r == REG_DAIF:
		return "DAIF"
	case r == REG_NZCV:
		return "NZCV"
	case r == REG_FPSR:
		return "FPSR"
	case r == REG_FPCR:
		return "FPCR"
	case r == REG_SPSR_EL1:
		return "SPSR_EL1"
	case r == REG_ELR_EL1:
		return "ELR_EL1"
	case r == REG_SPSR_EL2:
		return "SPSR_EL2"
	case r == REG_ELR_EL2:
		return "ELR_EL2"
	case r == REG_CurrentEL:
		return "CurrentEL"
	case r == REG_SP_EL0:
		return "SP_EL0"
	case r == REG_SPSel:
		return "SPSel"
	case r == REG_DAIFSet:
		return "DAIFSet"
	case r == REG_DAIFClr:
		return "DAIFClr"
	}
	return fmt.Sprintf("badreg(%d)", r)
}

func DRconv(a int) string {
	if a >= C_NONE && a <= C_NCLASS {
		return cnames7[a]
	}
	return "C_??"
}
