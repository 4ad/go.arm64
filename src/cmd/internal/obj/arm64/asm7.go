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

	case D_PAIR:
		return C_PAIR

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
			if a.Reg == REGSP && ctxt.Instoffset != 0 {
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