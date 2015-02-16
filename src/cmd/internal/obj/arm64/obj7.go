// cmd/7l/noop.c, cmd/7l/obj.c, cmd/ld/pass.c from Vita Nuova.
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
	"cmd/internal/obj/arm"
	"encoding/binary"
	"fmt"
	"log"
	"math"
)

var zprg = obj.Prog{
	As:  AGOK,
	Reg: NREG,
	From: obj.Addr{
		Name: D_NONE,
		Type: D_NONE,
		Reg:  NREG,
	},
	From3: obj.Addr{
		Name: D_NONE,
		Type: D_NONE,
		Reg:  NREG,
	},
	To: obj.Addr{
		Name: D_NONE,
		Type: D_NONE,
		Reg:  NREG,
	},
	To3: obj.Addr{
		Name: D_NONE,
		Type: D_NONE,
		Reg:  NREG,
	},
}

func symtype(a *obj.Addr) int {
	return int(a.Name)
}

func isdata(p *obj.Prog) bool {
	return p.As == ADATA || p.As == AGLOBL
}

func iscall(p *obj.Prog) bool {
	return p.As == ABL
}

func datasize(p *obj.Prog) int {
	return int(p.Reg)
}

func textflag(p *obj.Prog) int {
	return int(p.Reg)
}

func settextflag(p *obj.Prog, f int) {
	p.Reg = uint8(f)
}

var complements = []int16{
	AADD:  ASUB,
	AADDW: ASUBW,
	ASUB:  AADD,
	ASUBW: AADDW,
	ACMP:  ACMN,
	ACMPW: ACMNW,
	ACMN:  ACMP,
	ACMNW: ACMPW,
}

func progedit(ctxt *obj.Link, p *obj.Prog) {
	var literal string
	var s *obj.LSym

	p.From.Class = 0
	p.To.Class = 0

	// Rewrite BR/BL to symbol as D_BRANCH.
	switch p.As {

	case AB,
		ABL,
		ARETURN,
		ADUFFZERO,
		ADUFFCOPY:
		if p.To.Sym != nil {
			p.To.Type = D_BRANCH
		}
		break
	}

	// Rewrite float constants to values stored in memory.
	switch p.As {

	case AFMOVS:
		if p.From.Type == D_FCONST {
			var i32 uint32
			var f32 float32
			f32 = float32(p.From.U.Dval)
			i32 = math.Float32bits(f32)
			literal = fmt.Sprintf("$f32.%08x", uint32(i32))
			s = obj.Linklookup(ctxt, literal, 0)
			s.Size = 4
			p.From.Type = D_OREG
			p.From.Sym = s
			p.From.Name = D_EXTERN
			p.From.Offset = 0
		}

	case AFMOVD:
		if p.From.Type == D_FCONST {
			var i64 uint64
			i64 = math.Float64bits(p.From.U.Dval)
			literal = fmt.Sprintf("$f64.%016x", uint64(i64))
			s = obj.Linklookup(ctxt, literal, 0)
			s.Size = 8
			p.From.Type = D_OREG
			p.From.Sym = s
			p.From.Name = D_EXTERN
			p.From.Offset = 0
		}

		break
	}

	// Rewrite negative immediates as positive immediates with
	// complementary instruction.
	switch p.As {

	case AADD,
		AADDW,
		ASUB,
		ASUBW,
		ACMP,
		ACMPW,
		ACMN,
		ACMNW:
		if p.From.Type == D_CONST && p.From.Offset < 0 {
			p.From.Offset = -p.From.Offset
			p.As = complements[p.As]
		}

		break
	}
}

func follow(ctxt *obj.Link, s *obj.LSym) {
	var firstp *obj.Prog
	var lastp *obj.Prog

	ctxt.Cursym = s

	firstp = ctxt.NewProg()
	lastp = firstp
	xfol(ctxt, s.Text, &lastp)
	lastp.Link = nil
	s.Text = firstp.Link
}

func relinv(a int) int {
	switch a {
	case ABEQ:
		return ABNE
	case ABNE:
		return ABEQ
	case ABCS:
		return ABCC
	case ABHS:
		return ABLO
	case ABCC:
		return ABCS
	case ABLO:
		return ABHS
	case ABMI:
		return ABPL
	case ABPL:
		return ABMI
	case ABVS:
		return ABVC
	case ABVC:
		return ABVS
	case ABHI:
		return ABLS
	case ABLS:
		return ABHI
	case ABGE:
		return ABLT
	case ABLT:
		return ABGE
	case ABGT:
		return ABLE
	case ABLE:
		return ABGT
	}

	log.Fatalf("unknown relation: %s", arm.Anames5[a])
	return 0
}

func xfol(ctxt *obj.Link, p *obj.Prog, last **obj.Prog) {
	var q *obj.Prog
	var r *obj.Prog
	var a int
	var i int

loop:
	if p == nil {
		return
	}
	a = int(p.As)
	if a == AB {
		q = p.Pcond
		if q != nil {
			p.Mark |= FOLL
			p = q
			if !(p.Mark&FOLL != 0) {
				goto loop
			}
		}
	}

	if p.Mark&FOLL != 0 {
		i = 0
		q = p
		for ; i < 4; (func() { i++; q = q.Link })() {
			if q == *last || q == nil {
				break
			}
			a = int(q.As)
			if a == ANOP {
				i--
				continue
			}

			if a == AB || a == ARETURN || a == ARET || a == AERET {
				goto copy
			}
			if q.Pcond == nil || (q.Pcond.Mark&FOLL != 0) {
				continue
			}
			if a != ABEQ && a != ABNE {
				continue
			}

		copy:
			for {
				r = ctxt.NewProg()
				*r = *p
				if !(r.Mark&FOLL != 0) {
					fmt.Printf("cant happen 1\n")
				}
				r.Mark |= FOLL
				if p != q {
					p = p.Link
					(*last).Link = r
					*last = r
					continue
				}

				(*last).Link = r
				*last = r
				if a == AB || a == ARETURN || a == ARET || a == AERET {
					return
				}
				if a == ABNE {
					r.As = ABEQ
				} else {

					r.As = ABNE
				}
				r.Pcond = p.Link
				r.Link = p.Pcond
				if !(r.Link.Mark&FOLL != 0) {
					xfol(ctxt, r.Link, last)
				}
				if !(r.Pcond.Mark&FOLL != 0) {
					fmt.Printf("cant happen 2\n")
				}
				return
			}
		}

		a = AB
		q = ctxt.NewProg()
		q.As = int16(a)
		q.Lineno = p.Lineno
		q.To.Type = D_BRANCH
		q.To.Offset = p.Pc
		q.Pcond = p
		p = q
	}

	p.Mark |= FOLL
	(*last).Link = p
	*last = p
	if a == AB || a == ARETURN || a == ARET || a == AERET {
		return
	}
	if p.Pcond != nil {
		if a != ABL && p.Link != nil {
			q = obj.Brchain(ctxt, p.Link)
			if a != ATEXT && a != ABCASE {
				if q != nil && (q.Mark&FOLL != 0) {
					p.As = int16(relinv(a))
					p.Link = p.Pcond
					p.Pcond = q
				}
			}

			xfol(ctxt, p.Link, last)
			q = obj.Brchain(ctxt, p.Pcond)
			if q == nil {
				q = p.Pcond
			}
			if q.Mark&FOLL != 0 {
				p.Pcond = q
				return
			}

			p = q
			goto loop
		}
	}

	p = p.Link
	goto loop
}

func parsetextconst(arg int64, textstksiz *int64, textarg *int64) {
	*textstksiz = arg & 0xffffffff
	if *textstksiz&0x80000000 != 0 {
		*textstksiz = -(-*textstksiz & 0xffffffff)
	}

	*textarg = (arg >> 32) & 0xffffffff
	if *textarg&0x80000000 != 0 {
		*textarg = 0
	}
	*textarg = (*textarg + 7) &^ 7
}

func addstacksplit(ctxt *obj.Link, cursym *obj.LSym) {
	var p *obj.Prog
	var q *obj.Prog
	var q1 *obj.Prog
	var o int
	var textstksiz int64
	var textarg int64
	var aoffset int32

	if ctxt.Symmorestack[0] == nil {
		ctxt.Symmorestack[0] = obj.Linklookup(ctxt, "runtime.morestack", 0)
		ctxt.Symmorestack[1] = obj.Linklookup(ctxt, "runtime.morestack_noctxt", 0)
	}

	ctxt.Cursym = cursym

	if cursym.Text == nil || cursym.Text.Link == nil {
		return
	}

	p = cursym.Text
	parsetextconst(p.To.Offset, &textstksiz, &textarg)
	aoffset = int32(textstksiz)
	if aoffset < 0 {
		aoffset = 0
	}

	cursym.Args = int32(p.To.Offset >> 32)
	cursym.Locals = int32(textstksiz)

	/*
	 * find leaf subroutines
	 * strip NOPs
	 * expand RET
	 */
	if ctxt.Debugvlog != 0 {

		fmt.Fprintf(ctxt.Bso, "%5.2f noops\n", obj.Cputime())
	}
	obj.Bflush(ctxt.Bso)
	q = nil
	for p = cursym.Text; p != nil; p = p.Link {
		switch p.As {
		case ATEXT:
			p.Mark |= LEAF

		case ARETURN:
			break

		case ANOP:
			q1 = p.Link
			q.Link = q1 /* q is non-nop */
			q1.Mark |= p.Mark
			continue

		case ABL,
			ADUFFZERO,
			ADUFFCOPY:
			cursym.Text.Mark &^= LEAF
			fallthrough

		case ACBNZ,
			ACBZ,
			ACBNZW,
			ACBZW,
			ATBZ,
			ATBNZ,
			ABCASE,
			AB,
			ABEQ,
			ABNE,
			ABCS,
			ABHS,
			ABCC,
			ABLO,
			ABMI,
			ABPL,
			ABVS,
			ABVC,
			ABHI,
			ABLS,
			ABGE,
			ABLT,
			ABGT,
			ABLE,
			AADR, /* strange */
			AADRP:
			q1 = p.Pcond

			if q1 != nil {
				for q1.As == ANOP {
					q1 = q1.Link
					p.Pcond = q1
				}
			}

			break
		}

		q = p
	}

	for p = cursym.Text; p != nil; p = p.Link {
		o = int(p.As)
		switch o {
		case ATEXT:
			cursym.Text = p
			if textstksiz < 0 {
				ctxt.Autosize = 0
			} else {

				ctxt.Autosize = int32(textstksiz + 8)
			}
			if (cursym.Text.Mark&LEAF != 0) && ctxt.Autosize <= 8 {
				ctxt.Autosize = 0
			} else if ctxt.Autosize&(16-1) != 0 {
				ctxt.Autosize += 16 - (ctxt.Autosize & (16 - 1))
			}
			p.To.Offset = int64(uint64(p.To.Offset)&(0xffffffff<<32) | uint64(uint32(ctxt.Autosize-8)))
			if ctxt.Autosize == 0 && !(cursym.Text.Mark&LEAF != 0) {
				if ctxt.Debugvlog != 0 {
					fmt.Fprintf(ctxt.Bso, "save suppressed in: %s\n", cursym.Text.From.Sym.Name)
				}
				obj.Bflush(ctxt.Bso)
				cursym.Text.Mark |= LEAF
			}

			aoffset = ctxt.Autosize
			if aoffset > 0xF0 {
				aoffset = 0xF0
			}
			if cursym.Text.Mark&LEAF != 0 {
				cursym.Leaf = 1
				if ctxt.Autosize == 0 {
					break
				}
				aoffset = 0
			}

			q = p
			if ctxt.Autosize > aoffset {
				q = ctxt.NewProg()
				q.As = ASUB
				q.Lineno = p.Lineno
				q.From.Type = D_CONST
				q.From.Offset = int64(ctxt.Autosize) - int64(aoffset)
				q.To.Type = D_REG
				q.To.Reg = REGSP
				q.Spadj = int32(q.From.Offset)
				q.Link = p.Link
				p.Link = q
				if cursym.Text.Mark&LEAF != 0 {
					break
				}
			}

			q1 = ctxt.NewProg()
			q1.As = AMOV
			q1.Lineno = p.Lineno
			q1.From.Type = D_REG
			q1.From.Reg = REGLINK
			q1.To.Type = D_XPRE
			q1.To.Offset = int64(-aoffset)
			q1.To.Reg = REGSP
			q1.Link = q.Link
			q1.Spadj = aoffset
			q.Link = q1

		case ARETURN:
			nocache(p)
			if p.From.Type == D_CONST {
				ctxt.Diag("using BECOME (%v) is not supported!", p)
				break
			}

			if p.To.Sym != nil { // retjmp
				p.As = AB
				p.To.Type = D_BRANCH
				break
			}

			if cursym.Text.Mark&LEAF != 0 {
				if ctxt.Autosize != 0 {
					p.As = AADD
					p.From.Type = D_CONST
					p.From.Offset = int64(ctxt.Autosize)
					p.To.Type = D_REG
					p.To.Reg = REGSP
					p.Spadj = -ctxt.Autosize
				}
			} else {

				/* want write-back pre-indexed SP+autosize -> SP, loading REGLINK*/
				aoffset = ctxt.Autosize

				if aoffset > 0xF0 {
					aoffset = 0xF0
				}
				p.As = AMOV
				p.From.Type = D_XPOST
				p.From.Offset = int64(aoffset)
				p.From.Reg = REGSP
				p.To.Type = D_REG
				p.To.Reg = REGLINK
				p.Spadj = -aoffset
				if ctxt.Autosize > aoffset {
					q = ctxt.NewProg()
					q.As = AADD
					q.From.Type = D_CONST
					q.From.Offset = int64(ctxt.Autosize) - int64(aoffset)
					q.To.Type = D_REG
					q.To.Reg = REGSP
					q.Link = p.Link
					q.Spadj = int32(-q.From.Offset)
					q.Lineno = p.Lineno
					p.Link = q
					p = q
				}
			}

			if p.As != ARETURN {
				q = ctxt.NewProg()
				q.Lineno = p.Lineno
				q.Link = p.Link
				p.Link = q
				p = q
			}

			p.As = ARET
			p.Lineno = p.Lineno
			p.To.Type = D_OREG
			p.To.Offset = 0
			p.To.Reg = REGLINK
			p.Spadj = +ctxt.Autosize

		case AADD,
			ASUB:
			if p.To.Type == D_SP && p.To.Reg == REGSP && p.From.Type == D_CONST {
				if p.As == AADD {
					p.Spadj = int32(-p.From.Offset)
				} else {

					p.Spadj = int32(+p.From.Offset)
				}
			}
			break
		}
	}
}

func nocache(p *obj.Prog) {
	p.Optab = 0
	p.From.Class = 0
	p.To.Class = 0
}

func prg() *obj.Prog {
	p := zprg
	return &p
}

var Linkarm64 = obj.LinkArch{
	ByteOrder:     binary.LittleEndian,
	Pconv:         Pconv,
	Name:          "arm64",
	Thechar:       '7',
	Endian:        obj.LittleEndian,
	Addstacksplit: addstacksplit,
	Assemble:      span7,
	Datasize:      datasize,
	Follow:        follow,
	Iscall:        iscall,
	Isdata:        isdata,
	Prg:           prg,
	Progedit:      progedit,
	Settextflag:   settextflag,
	Symtype:       symtype,
	Textflag:      textflag,
	Minlc:         4,
	Ptrsize:       8,
	Regsize:       8,
	D_ADDR:        D_ADDR,
	D_AUTO:        D_AUTO,
	D_BRANCH:      D_BRANCH,
	D_CONST:       D_CONST,
	D_EXTERN:      D_EXTERN,
	D_FCONST:      D_FCONST,
	D_NONE:        D_NONE,
	D_PARAM:       D_PARAM,
	D_SCONST:      D_SCONST,
	D_STATIC:      D_STATIC,
	D_OREG:        D_OREG,
	ACALL:         ABL,
	ADATA:         ADATA,
	AEND:          AEND,
	AFUNCDATA:     AFUNCDATA,
	AGLOBL:        AGLOBL,
	AJMP:          AB,
	ANOP:          ANOP,
	APCDATA:       APCDATA,
	ARET:          ARETURN,
	ATEXT:         ATEXT,
	ATYPE:         ATYPE,
	AUSEFIELD:     AUSEFIELD,
}
