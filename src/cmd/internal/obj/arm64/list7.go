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
	if a >= obj.AXXX && a < ALAST && Anames[a] != "" {
		s = Anames[a]
	}
	fp += s
	return fp
}

func Rconv(r int) string {
	switch {
	case r == 0:
		return "NONE"
	case REGSP:
		return "RSP"
	case REG_R0 <= r && r <= REG_R30:
		return fmt.Sprintf("R%d", r-REG_R0)
	case REG_R31:
		return "ZR"
	case REG_F0 <= r && r <= REG_F31:
		return fmt.Sprintf("F%d", r-REG_F0)
	case REG_V0 <= r && r <= REG_V31:
		return fmt.Sprintf("V%d", r-REG_F0)
	case r >= REG_SPECIAL:
		return "REG_SPECIAL" // TODO(aram)
	}
	return fmt.Sprintf("badreg(%d)", r)
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
