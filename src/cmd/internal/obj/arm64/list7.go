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

func Pconv(p *obj.Prog) string {
	var str string
	var fp string

	var a int

	a = int(p.As)
	switch a {
	default:
		if p.Reg == NREG && p.From3.Type == obj.TYPE_NONE && p.To3.Type == obj.TYPE_NONE {
			str = fmt.Sprintf("%.5d (%v)\t%v\t%v,%v", p.Pc, p.Line(), Aconv(a), Dconv(p, 0, &p.From), Dconv(p, 0, &p.To))
		} else if p.From.Type != D_FREG {
			str = fmt.Sprintf("%.5d (%v)\t%v\t%v", p.Pc, p.Line(), Aconv(a), Dconv(p, 0, &p.From))
			if p.From3.Type != obj.TYPE_NONE {
				str += fmt.Sprintf(",%v", Dconv(p, 0, &p.From3))
			}
			if p.Reg != NREG {
				str += fmt.Sprintf(",R%d", p.Reg)
			}
			if p.To3.Type != obj.TYPE_NONE {
				str += fmt.Sprintf(",%v,%v", Dconv(p, 0, &p.To), Dconv(p, 0, &p.To3))
			} else {

				str += fmt.Sprintf(",%v", Dconv(p, 0, &p.To))
			}
		} else {

			str = fmt.Sprintf("%.5d (%v)\t%v\t%v,F%d,%v", p.Pc, p.Line(), Aconv(a), Dconv(p, 0, &p.From), p.Reg, Dconv(p, 0, &p.To))
		}

	case ATEXT:
		if p.Reg != 0 {
			str = fmt.Sprintf("%.5d (%v)\t%v\t%v,%d,%v", p.Pc, p.Line(), Aconv(a), Dconv(p, 0, &p.From), p.Reg, Dconv(p, fmtLong, &p.To))
		} else {

			str = fmt.Sprintf("%.5d (%v)\t%v\t%v,%v", p.Pc, p.Line(), Aconv(a), Dconv(p, 0, &p.From), Dconv(p, fmtLong, &p.To))
		}

	case AGLOBL:
		if p.Reg != 0 {
			str = fmt.Sprintf("%.5d (%v)\t%v\t%v,%d,%v", p.Pc, p.Line(), Aconv(a), Dconv(p, 0, &p.From), p.Reg, Dconv(p, 0, &p.To))
		} else {

			str = fmt.Sprintf("%.5d (%v)\t%v\t%v,%v", p.Pc, p.Line(), Aconv(a), Dconv(p, 0, &p.From), Dconv(p, 0, &p.To))
		}

	case ADATA,
		AINIT,
		ADYNT:
		str = fmt.Sprintf("%.5d (%v)\t%v\t%v/%d,%v", p.Pc, p.Line(), Aconv(a), Dconv(p, 0, &p.From), p.Reg, Dconv(p, 0, &p.To))
		break
	}

	if p.Spadj != 0 {
		fp += fmt.Sprintf("%s # spadj=%d", str, p.Spadj)
		return fp
	}
	fp += str
	return fp
}

func Aconv(a int) string {
	var s string
	var fp string

	s = "???"
	if a >= AXXX && a < ALAST && Anames[a] != "" {
		s = Anames[a]
	}
	fp += s
	return fp
}

func Dconv(p *obj.Prog, flag int, a *obj.Addr) string {
	var str string
	var op string
	var fp string

	var v int32
	var extop = []string{".UB", ".UH", ".UW", ".UX", ".SB", ".SH", ".SW", ".SX"}

	if flag&fmtLong != 0 /*untyped*/ {
		if a.Type == D_CONST {
			str = fmt.Sprintf("$%d-%d", int32(a.Offset), int32(a.Offset>>32))
		} else {

			// ATEXT dst is not constant
			str = fmt.Sprintf("!!%v", Dconv(p, 0, a))
		}

		goto ret
	}

	switch a.Type {
	default:
		str = fmt.Sprintf("GOK-type(%d)", a.Type)

	case obj.TYPE_NONE:
		str = ""
		if a.Name != obj.NAME_NONE || a.Reg != NREG || a.Sym != nil {
			str = fmt.Sprintf("%v(R%d)(NONE)", Mconv(a), a.Reg)
		}

	case D_CONST:
		if a.Reg == NREG || a.Reg == REGZERO && a.Offset == 0 {
			str = fmt.Sprintf("$%v", Mconv(a))
		} else {

			str = fmt.Sprintf("$%v(R%d)", Mconv(a), a.Reg)
		}

	case D_SHIFT:
		v = int32(a.Offset)
		op = string("<<>>->@>"[((v>>22)&3)<<1])
		str = fmt.Sprintf("R%d%c%c%d", (v>>16)&0x1F, op[0], op[1], (v>>10)&0x3F)
		if a.Reg != NREG {
			str += fmt.Sprintf("(R%d)", a.Reg)
		}

	case D_OCONST:
		str = fmt.Sprintf("$*$%v", Mconv(a))
		if a.Reg != NREG {
			str = fmt.Sprintf("%v(R%d)(CONST)", Mconv(a), a.Reg)
		}

	case D_OREG:
		if a.Reg != NREG {
			str = fmt.Sprintf("%v(R%d)", Mconv(a), a.Reg)
		} else {

			str = fmt.Sprintf("%v", Mconv(a))
		}

	case D_XPRE:
		if a.Reg != NREG {
			str = fmt.Sprintf("%v(R%d)!", Mconv(a), a.Reg)
		} else {

			str = fmt.Sprintf("%v!", Mconv(a))
		}

	case D_XPOST:
		if a.Reg != NREG {
			str = fmt.Sprintf("(R%d)%v!", a.Reg, Mconv(a))
		} else {

			str = fmt.Sprintf("%v!", Mconv(a))
		}

	case D_EXTREG:
		v = int32(a.Offset)
		if v&(7<<10) != 0 {
			str = fmt.Sprintf("R%d%s<<%d", (v>>16)&31, extop[(v>>13)&7], (v>>10)&7)
		} else {

			str = fmt.Sprintf("R%d%s", (v>>16)&31, extop[(v>>13)&7])
		}

	case D_ROFF:
		v = int32(a.Offset)
		if v&(1<<16) != 0 {
			str = fmt.Sprintf("(R%d)[R%d%s]", a.Reg, v&31, extop[(v>>8)&7])
		} else {

			str = fmt.Sprintf("(R%d)(R%d%s)", a.Reg, v&31, extop[(v>>8)&7])
		}

	case D_REG:
		str = fmt.Sprintf("R%d", a.Reg)
		if a.Name != obj.NAME_NONE || a.Sym != nil {
			str = fmt.Sprintf("%v(R%d)(REG)", Mconv(a), a.Reg)
		}

	case D_PAIR:
		str = fmt.Sprintf("(R%d, R%d)", a.Reg, a.Offset)

	case D_SP:
		if a.Name != obj.NAME_NONE || a.Sym != nil {
			str = fmt.Sprintf("%v(R%d)(REG)", Mconv(a), a.Reg)
		} else {

			str = "SP"
		}

	case D_COND:
		str = strcond[a.Reg&0xF]

	case D_FREG:
		str = fmt.Sprintf("F%d", a.Reg)
		if a.Name != obj.NAME_NONE || a.Sym != nil {
			str = fmt.Sprintf("%v(R%d)(REG)", Mconv(a), a.Reg)
		}

	case D_SPR:
		switch a.Offset {
		case D_FPSR:
			str = fmt.Sprintf("FPSR")

		case D_FPCR:
			str = fmt.Sprintf("FPCR")

		case D_NZCV:
			str = fmt.Sprintf("NZCV")

		default:
			str = fmt.Sprintf("SPR(%#x)", uint64(a.Offset))
			break
		}

		if a.Name != obj.NAME_NONE || a.Sym != nil {
			str = fmt.Sprintf("%v(SPR%d)(REG)", Mconv(a), a.Offset)
		}

	case obj.TYPE_BRANCH: /* botch */
		if p.Pcond != nil {

			v = int32(p.Pcond.Pc)
			if a.Sym != nil {
				str = fmt.Sprintf("%s+%#.5x(BRANCH)", a.Sym.Name, uint32(v))
			} else {

				str = fmt.Sprintf("%.5x(BRANCH)", uint32(v))
			}
		} else if a.Sym != nil {
			str = fmt.Sprintf("%s+%d(PC)", a.Sym.Name, a.Offset)
		} else {

			str = fmt.Sprintf("%d(PC)", a.Offset)
		}

	case D_FCONST:
		str = fmt.Sprintf("$%.17g", a.U.Dval)

	case D_SCONST:
		str = fmt.Sprintf("$\"%q\"", a.U.Sval)
		break
	}

ret:
	fp += str
	return fp
}

func Mconv(a *obj.Addr) string {
	var str string
	var fp string

	var s *obj.LSym

	s = a.Sym
	switch a.Name {
	default:
		str = fmt.Sprintf("GOK-name(%d)", a.Name)

	case obj.NAME_NONE:
		str = fmt.Sprintf("%d", a.Offset)

	case obj.NAME_EXTERN:
		if s == nil {
			str = fmt.Sprintf("%d(SB)", a.Offset)
		} else {

			str = fmt.Sprintf("%s+%d(SB)", s.Name, a.Offset)
		}

	case D_STATIC:
		if s == nil {
			str = fmt.Sprintf("<>+%d(SB)", a.Offset)
		} else {

			str = fmt.Sprintf("%s<>+%d(SB)", s.Name, a.Offset)
		}

	case D_AUTO:
		if s == nil {
			str = fmt.Sprintf("%d(SP)", a.Offset)
		} else {

			str = fmt.Sprintf("%s-%d(SP)", s.Name, -a.Offset)
		}

	case D_PARAM:
		if s == nil {
			str = fmt.Sprintf("%d(FP)", a.Offset)
		} else {

			str = fmt.Sprintf("%s+%d(FP)", s.Name, a.Offset)
		}
		break
	}

	fp += str
	return fp
}

func Rconv(r int) string {
	var fp string

	var str string

	str = fmt.Sprintf("R%d", r)
	fp += str
	return fp
}

func DRconv(a int) string {
	var s string
	var fp string

	s = "C_??"
	if a >= C_NONE && a <= C_NCLASS {
		s = cnames7[a]
	}
	fp += s
	return fp
}
