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
)

/*
 * internal class codes for different constant classes:
 * they partition the constant/offset range into disjoint ranges that
 * are somehow treated specially by one or more load/store instructions.
 */
var autoclass = []int{C_PSAUTO, C_NSAUTO, C_NPAUTO, C_PSAUTO, C_PPAUTO, C_UAUTO4K, C_UAUTO8K, C_UAUTO16K, C_UAUTO32K, C_UAUTO64K, C_LAUTO}

var oregclass = []int{C_ZOREG, C_NSOREG, C_NPOREG, C_PSOREG, C_PPOREG, C_UOREG4K, C_UOREG8K, C_UOREG16K, C_UOREG32K, C_UOREG64K, C_LOREG}

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
	switch a.Type {
	case obj.TYPE_NONE:
		return C_NONE

	case obj.TYPE_REG:
		switch {
		case a.Reg == REGSP:
			return C_RSP
		case REG_R0 <= a.Reg && a.Reg <= REG_R31:
			return C_REG
		case REG_F0 <= a.Reg && a.Reg <= REG_F31:
			return C_FREG
		case REG_V0 <= a.Reg && a.Reg <= REG_V31:
			return C_VREG
		case a.Reg&REG_EXT != 0:
			return C_EXTREG
		case a.Reg >= REG_SPECIAL:
			return C_SPR
		}
		return C_GOK

	case obj.TYPE_REGREG:
		return C_PAIR

	case obj.TYPE_SHIFT:
		return C_SHIFT

	case obj.TYPE_MEM:
		switch a.Name {
		case obj.NAME_EXTERN,
			obj.NAME_STATIC:
			if a.Sym == nil {
				break
			}
			ctxt.Instoffset = a.Offset
			if a.Sym != nil { // use relocation
				return C_ADDR
			}
			return C_LEXT

		case obj.NAME_AUTO:
			ctxt.Instoffset = int64(ctxt.Autosize) + a.Offset
			return autoclass[constclass(ctxt.Instoffset)]

		case obj.NAME_PARAM:
			ctxt.Instoffset = int64(ctxt.Autosize) + a.Offset + 8
			return autoclass[constclass(ctxt.Instoffset)]

		case obj.TYPE_NONE:
			ctxt.Instoffset = a.Offset
			return oregclass[constclass(ctxt.Instoffset)]
		}
		return C_GOK

	case obj.TYPE_FCONST:
		return C_FCON

	case obj.TYPE_TEXTSIZE:
		return C_TEXTSIZE

	case obj.TYPE_CONST,
		obj.TYPE_ADDR:
		switch a.Name {
		case obj.TYPE_NONE:
			ctxt.Instoffset = a.Offset
			if a.Reg == REGSP {
				goto aconsize
			}
			v := ctxt.Instoffset
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

			t := movcon(v)
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

		case obj.NAME_EXTERN,
			obj.NAME_STATIC:
			s := a.Sym
			if s == nil {
				break
			}
			ctxt.Instoffset = a.Offset
			return C_VCONADDR

		case obj.NAME_AUTO:
			ctxt.Instoffset = int64(ctxt.Autosize) + a.Offset
			goto aconsize

		case obj.NAME_PARAM:
			ctxt.Instoffset = int64(ctxt.Autosize) + a.Offset + 8
			goto aconsize
		}
		return C_GOK

	aconsize:
		if isaddcon(ctxt.Instoffset) != 0 {
			return C_AACON
		}
		return C_LACON

	case obj.TYPE_BRANCH:
		return C_SBRA
	}

	return C_GOK
}
