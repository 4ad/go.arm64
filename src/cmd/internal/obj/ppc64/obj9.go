// cmd/9l/noop.c, cmd/9l/pass.c, cmd/9l/span.c from Vita Nuova.
//
//	Copyright © 1994-1999 Lucent Technologies Inc.  All rights reserved.
//	Portions Copyright © 1995-1997 C H Forsyth (forsyth@terzarima.net)
//	Portions Copyright © 1997-1999 Vita Nuova Limited
//	Portions Copyright © 2000-2008 Vita Nuova Holdings Limited (www.vitanuova.com)
//	Portions Copyright © 2004,2006 Bruce Ellis
//	Portions Copyright © 2005-2007 C H Forsyth (forsyth@terzarima.net)
//	Revisions Copyright © 2000-2008 Lucent Technologies Inc. and others
//	Portions Copyright © 2009 The Go Authors.  All rights reserved.
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

package ppc64

import (
	"cmd/internal/obj"
	"encoding/binary"
	"fmt"
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

func progedit(ctxt *obj.Link, p *obj.Prog) {
	var literal string
	var s *obj.LSym

	p.From.Class = 0
	p.To.Class = 0

	// Rewrite BR/BL to symbol as D_BRANCH.
	switch p.As {

	case ABR,
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
			literal = fmt.Sprintf("$f32.%08x", i32)
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
			literal = fmt.Sprintf("$f64.%016x", i64)
			s = obj.Linklookup(ctxt, literal, 0)
			s.Size = 8
			p.From.Type = D_OREG
			p.From.Sym = s
			p.From.Name = D_EXTERN
			p.From.Offset = 0
		}

		// Put >32-bit constants in memory and load them
	case AMOVD:
		if p.From.Type == D_CONST && p.From.Name == D_NONE && p.From.Reg == NREG && int64(int32(p.From.Offset)) != p.From.Offset {

			literal = fmt.Sprintf("$i64.%016x", uint64(p.From.Offset))
			s = obj.Linklookup(ctxt, literal, 0)
			s.Size = 8
			p.From.Type = D_OREG
			p.From.Sym = s
			p.From.Name = D_EXTERN
			p.From.Offset = 0
		}
	}

	// Rewrite SUB constants into ADD.
	switch p.As {

	case ASUBC:
		if p.From.Type == D_CONST {
			p.From.Offset = -p.From.Offset
			p.As = AADDC
		}

	case ASUBCCC:
		if p.From.Type == D_CONST {
			p.From.Offset = -p.From.Offset
			p.As = AADDCCC
		}

	case ASUB:
		if p.From.Type == D_CONST {
			p.From.Offset = -p.From.Offset
			p.As = AADD
		}

		break
	}
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
	var p1 *obj.Prog
	var p2 *obj.Prog
	var q1 *obj.Prog
	var o int
	var mov int
	var aoffset int
	var textstksiz int64
	var textarg int64
	var autosize int32

	if ctxt.Symmorestack[0] == nil {
		ctxt.Symmorestack[0] = obj.Linklookup(ctxt, "runtime.morestack", 0)
		ctxt.Symmorestack[1] = obj.Linklookup(ctxt, "runtime.morestack_noctxt", 0)
	}

	// TODO(minux): add morestack short-cuts with small fixed frame-size.
	ctxt.Cursym = cursym

	if cursym.Text == nil || cursym.Text.Link == nil {
		return
	}

	p = cursym.Text
	parsetextconst(p.To.Offset, &textstksiz, &textarg)

	cursym.Args = int32(p.To.Offset >> 32)
	cursym.Locals = int32(textstksiz)

	/*
	 * find leaf subroutines
	 * strip NOPs
	 * expand RET
	 * expand BECOME pseudo
	 */
	if ctxt.Debugvlog != 0 {

		fmt.Fprintf(ctxt.Bso, "%5.2f noops\n", obj.Cputime())
	}
	obj.Bflush(ctxt.Bso)

	q = nil
	for p = cursym.Text; p != nil; p = p.Link {
		switch p.As {
		/* too hard, just leave alone */
		case ATEXT:
			q = p

			p.Mark |= LABEL | LEAF | SYNC
			if p.Link != nil {
				p.Link.Mark |= LABEL
			}

		case ANOR:
			q = p
			if p.To.Type == D_REG {
				if p.To.Reg == REGZERO {
					p.Mark |= LABEL | SYNC
				}
			}

		case ALWAR,
			ASTWCCC,
			AECIWX,
			AECOWX,
			AEIEIO,
			AICBI,
			AISYNC,
			ATLBIE,
			ATLBIEL,
			ASLBIA,
			ASLBIE,
			ASLBMFEE,
			ASLBMFEV,
			ASLBMTE,
			ADCBF,
			ADCBI,
			ADCBST,
			ADCBT,
			ADCBTST,
			ADCBZ,
			ASYNC,
			ATLBSYNC,
			APTESYNC,
			ATW,
			AWORD,
			ARFI,
			ARFCI,
			ARFID,
			AHRFID:
			q = p
			p.Mark |= LABEL | SYNC
			continue

		case AMOVW,
			AMOVWZ,
			AMOVD:
			q = p
			switch p.From.Type {
			case D_MSR,
				D_SPR,
				D_FPSCR,
				D_CREG,
				D_DCR:
				p.Mark |= LABEL | SYNC
			}

			switch p.To.Type {
			case D_MSR,
				D_SPR,
				D_FPSCR,
				D_CREG,
				D_DCR:
				p.Mark |= LABEL | SYNC
			}

			continue

		case AFABS,
			AFABSCC,
			AFADD,
			AFADDCC,
			AFCTIW,
			AFCTIWCC,
			AFCTIWZ,
			AFCTIWZCC,
			AFDIV,
			AFDIVCC,
			AFMADD,
			AFMADDCC,
			AFMOVD,
			AFMOVDU,
			/* case AFMOVDS: */
			AFMOVS,
			AFMOVSU,

			/* case AFMOVSD: */
			AFMSUB,
			AFMSUBCC,
			AFMUL,
			AFMULCC,
			AFNABS,
			AFNABSCC,
			AFNEG,
			AFNEGCC,
			AFNMADD,
			AFNMADDCC,
			AFNMSUB,
			AFNMSUBCC,
			AFRSP,
			AFRSPCC,
			AFSUB,
			AFSUBCC:
			q = p

			p.Mark |= FLOAT
			continue

		case ABL,
			ABCL,
			ADUFFZERO,
			ADUFFCOPY:
			cursym.Text.Mark &^= LEAF
			fallthrough

		case ABC,
			ABEQ,
			ABGE,
			ABGT,
			ABLE,
			ABLT,
			ABNE,
			ABR,
			ABVC,
			ABVS:
			p.Mark |= BRANCH
			q = p
			q1 = p.Pcond
			if q1 != nil {
				for q1.As == ANOP {
					q1 = q1.Link
					p.Pcond = q1
				}

				if !(q1.Mark&LEAF != 0) {
					q1.Mark |= LABEL
				}
			} else {

				p.Mark |= LABEL
			}
			q1 = p.Link
			if q1 != nil {
				q1.Mark |= LABEL
			}
			continue

		case AFCMPO,
			AFCMPU:
			q = p
			p.Mark |= FCMP | FLOAT
			continue

		case ARETURN:
			q = p
			if p.Link != nil {
				p.Link.Mark |= LABEL
			}
			continue

		case ANOP:
			q1 = p.Link
			q.Link = q1 /* q is non-nop */
			q1.Mark |= p.Mark
			continue

		default:
			q = p
			continue
		}
	}

	autosize = 0
	for p = cursym.Text; p != nil; p = p.Link {
		o = int(p.As)
		switch o {
		case ATEXT:
			mov = AMOVD
			aoffset = 0
			autosize = int32(textstksiz + 8)
			if (p.Mark&LEAF != 0) && autosize <= 8 {
				autosize = 0
			} else if autosize&4 != 0 {
				autosize += 4
			}
			p.To.Offset = int64(uint64(p.To.Offset)&(0xffffffff<<32) | uint64(uint32(autosize-8)))

			if !(p.Reg&obj.NOSPLIT != 0) {
				p = stacksplit(ctxt, p, autosize, bool2int(!(cursym.Text.Reg&obj.NEEDCTXT != 0))) // emit split check
			}

			q = p

			if autosize != 0 {
				/* use MOVDU to adjust R1 when saving R31, if autosize is small */
				if !(cursym.Text.Mark&LEAF != 0) && autosize >= -BIG && autosize <= BIG {

					mov = AMOVDU
					aoffset = int(-autosize)
				} else {

					q = obj.Appendp(ctxt, p)
					q.As = AADD
					q.Lineno = p.Lineno
					q.From.Type = D_CONST
					q.From.Offset = int64(-autosize)
					q.To.Type = D_REG
					q.To.Reg = REGSP
					q.Spadj = +autosize
				}
			} else if !(cursym.Text.Mark&LEAF != 0) {
				if ctxt.Debugvlog != 0 {
					fmt.Fprintf(ctxt.Bso, "save suppressed in: %s\n", cursym.Name)
					obj.Bflush(ctxt.Bso)
				}

				cursym.Text.Mark |= LEAF
			}

			if cursym.Text.Mark&LEAF != 0 {
				cursym.Leaf = 1
				break
			}

			q = obj.Appendp(ctxt, q)
			q.As = AMOVD
			q.Lineno = p.Lineno
			q.From.Type = D_SPR
			q.From.Offset = D_LR
			q.To.Type = D_REG
			q.To.Reg = REGTMP

			q = obj.Appendp(ctxt, q)
			q.As = int16(mov)
			q.Lineno = p.Lineno
			q.From.Type = D_REG
			q.From.Reg = REGTMP
			q.To.Type = D_OREG
			q.To.Offset = int64(aoffset)
			q.To.Reg = REGSP
			if q.As == AMOVDU {
				q.Spadj = int32(-aoffset)
			}

			if cursym.Text.Reg&obj.WRAPPER != 0 {
				// if(g->panic != nil && g->panic->argp == FP) g->panic->argp = bottom-of-frame
				//
				//	MOVD g_panic(g), R3
				//	CMP R0, R3
				//	BEQ end
				//	MOVD panic_argp(R3), R4
				//	ADD $(autosize+8), R1, R5
				//	CMP R4, R5
				//	BNE end
				//	ADD $8, R1, R6
				//	MOVD R6, panic_argp(R3)
				// end:
				//	NOP
				//
				// The NOP is needed to give the jumps somewhere to land.
				// It is a liblink NOP, not a ppc64 NOP: it encodes to 0 instruction bytes.

				q = obj.Appendp(ctxt, q)

				q.As = AMOVD
				q.From.Type = D_OREG
				q.From.Reg = REGG
				q.From.Offset = 4 * int64(ctxt.Arch.Ptrsize) // G.panic
				q.To.Type = D_REG
				q.To.Reg = 3

				q = obj.Appendp(ctxt, q)
				q.As = ACMP
				q.From.Type = D_REG
				q.From.Reg = 0
				q.To.Type = D_REG
				q.To.Reg = 3

				q = obj.Appendp(ctxt, q)
				q.As = ABEQ
				q.To.Type = D_BRANCH
				p1 = q

				q = obj.Appendp(ctxt, q)
				q.As = AMOVD
				q.From.Type = D_OREG
				q.From.Reg = 3
				q.From.Offset = 0 // Panic.argp
				q.To.Type = D_REG
				q.To.Reg = 4

				q = obj.Appendp(ctxt, q)
				q.As = AADD
				q.From.Type = D_CONST
				q.From.Offset = int64(autosize) + 8
				q.Reg = REGSP
				q.To.Type = D_REG
				q.To.Reg = 5

				q = obj.Appendp(ctxt, q)
				q.As = ACMP
				q.From.Type = D_REG
				q.From.Reg = 4
				q.To.Type = D_REG
				q.To.Reg = 5

				q = obj.Appendp(ctxt, q)
				q.As = ABNE
				q.To.Type = D_BRANCH
				p2 = q

				q = obj.Appendp(ctxt, q)
				q.As = AADD
				q.From.Type = D_CONST
				q.From.Offset = 8
				q.Reg = REGSP
				q.To.Type = D_REG
				q.To.Reg = 6

				q = obj.Appendp(ctxt, q)
				q.As = AMOVD
				q.From.Type = D_REG
				q.From.Reg = 6
				q.To.Type = D_OREG
				q.To.Reg = 3
				q.To.Offset = 0 // Panic.argp

				q = obj.Appendp(ctxt, q)

				q.As = ANOP
				p1.Pcond = q
				p2.Pcond = q
			}

		case ARETURN:
			if p.From.Type == D_CONST {
				ctxt.Diag("using BECOME (%v) is not supported!", p)
				break
			}

			if p.To.Sym != nil { // retjmp
				p.As = ABR
				p.To.Type = D_BRANCH
				break
			}

			if cursym.Text.Mark&LEAF != 0 {
				if !(autosize != 0) {
					p.As = ABR
					p.From = zprg.From
					p.To.Type = D_SPR
					p.To.Offset = D_LR
					p.Mark |= BRANCH
					break
				}

				p.As = AADD
				p.From.Type = D_CONST
				p.From.Offset = int64(autosize)
				p.To.Type = D_REG
				p.To.Reg = REGSP
				p.Spadj = -autosize

				q = ctxt.Arch.Prg()
				q.As = ABR
				q.Lineno = p.Lineno
				q.To.Type = D_SPR
				q.To.Offset = D_LR
				q.Mark |= BRANCH
				q.Spadj = +autosize

				q.Link = p.Link
				p.Link = q
				break
			}

			p.As = AMOVD
			p.From.Type = D_OREG
			p.From.Offset = 0
			p.From.Reg = REGSP
			p.To.Type = D_REG
			p.To.Reg = REGTMP

			q = ctxt.Arch.Prg()
			q.As = AMOVD
			q.Lineno = p.Lineno
			q.From.Type = D_REG
			q.From.Reg = REGTMP
			q.To.Type = D_SPR
			q.To.Offset = D_LR

			q.Link = p.Link
			p.Link = q
			p = q

			if false {
				// Debug bad returns
				q = ctxt.Arch.Prg()

				q.As = AMOVD
				q.Lineno = p.Lineno
				q.From.Type = D_OREG
				q.From.Offset = 0
				q.From.Reg = REGTMP
				q.To.Type = D_REG
				q.To.Reg = REGTMP

				q.Link = p.Link
				p.Link = q
				p = q
			}

			if autosize != 0 {
				q = ctxt.Arch.Prg()
				q.As = AADD
				q.Lineno = p.Lineno
				q.From.Type = D_CONST
				q.From.Offset = int64(autosize)
				q.To.Type = D_REG
				q.To.Reg = REGSP
				q.Spadj = -autosize

				q.Link = p.Link
				p.Link = q
			}

			q1 = ctxt.Arch.Prg()
			q1.As = ABR
			q1.Lineno = p.Lineno
			q1.To.Type = D_SPR
			q1.To.Offset = D_LR
			q1.Mark |= BRANCH
			q1.Spadj = +autosize

			q1.Link = q.Link
			q.Link = q1

		case AADD:
			if p.To.Type == D_REG && p.To.Reg == REGSP && p.From.Type == D_CONST {
				p.Spadj = int32(-p.From.Offset)
			}
			break
		}
	}
}

/*
// instruction scheduling
	if(debug['Q'] == 0)
		return;

	curtext = nil;
	q = nil;	// p - 1
	q1 = firstp;	// top of block
	o = 0;		// count of instructions
	for(p = firstp; p != nil; p = p1) {
		p1 = p->link;
		o++;
		if(p->mark & NOSCHED){
			if(q1 != p){
				sched(q1, q);
			}
			for(; p != nil; p = p->link){
				if(!(p->mark & NOSCHED))
					break;
				q = p;
			}
			p1 = p;
			q1 = p;
			o = 0;
			continue;
		}
		if(p->mark & (LABEL|SYNC)) {
			if(q1 != p)
				sched(q1, q);
			q1 = p;
			o = 1;
		}
		if(p->mark & (BRANCH|SYNC)) {
			sched(q1, p);
			q1 = p1;
			o = 0;
		}
		if(o >= NSCHED) {
			sched(q1, p);
			q1 = p1;
			o = 0;
		}
		q = p;
	}
*/
func stacksplit(ctxt *obj.Link, p *obj.Prog, framesize int32, noctxt int) *obj.Prog {

	var q *obj.Prog
	var q1 *obj.Prog

	// MOVD	g_stackguard(g), R3
	p = obj.Appendp(ctxt, p)

	p.As = AMOVD
	p.From.Type = D_OREG
	p.From.Reg = REGG
	p.From.Offset = 2 * int64(ctxt.Arch.Ptrsize) // G.stackguard0
	if ctxt.Cursym.Cfunc != 0 {
		p.From.Offset = 3 * int64(ctxt.Arch.Ptrsize) // G.stackguard1
	}
	p.To.Type = D_REG
	p.To.Reg = 3

	q = nil
	if framesize <= obj.StackSmall {
		// small stack: SP < stackguard
		//	CMP	stackguard, SP
		p = obj.Appendp(ctxt, p)

		p.As = ACMPU
		p.From.Type = D_REG
		p.From.Reg = 3
		p.To.Type = D_REG
		p.To.Reg = REGSP
	} else if framesize <= obj.StackBig {
		// large stack: SP-framesize < stackguard-StackSmall
		//	ADD $-framesize, SP, R4
		//	CMP stackguard, R4
		p = obj.Appendp(ctxt, p)

		p.As = AADD
		p.From.Type = D_CONST
		p.From.Offset = int64(-framesize)
		p.Reg = REGSP
		p.To.Type = D_REG
		p.To.Reg = 4

		p = obj.Appendp(ctxt, p)
		p.As = ACMPU
		p.From.Type = D_REG
		p.From.Reg = 3
		p.To.Type = D_REG
		p.To.Reg = 4
	} else {

		// Such a large stack we need to protect against wraparound.
		// If SP is close to zero:
		//	SP-stackguard+StackGuard <= framesize + (StackGuard-StackSmall)
		// The +StackGuard on both sides is required to keep the left side positive:
		// SP is allowed to be slightly below stackguard. See stack.h.
		//
		// Preemption sets stackguard to StackPreempt, a very large value.
		// That breaks the math above, so we have to check for that explicitly.
		//	// stackguard is R3
		//	CMP	R3, $StackPreempt
		//	BEQ	label-of-call-to-morestack
		//	ADD	$StackGuard, SP, R4
		//	SUB	R3, R4
		//	MOVD	$(framesize+(StackGuard-StackSmall)), R31
		//	CMPU	R31, R4
		p = obj.Appendp(ctxt, p)

		p.As = ACMP
		p.From.Type = D_REG
		p.From.Reg = 3
		p.To.Type = D_CONST
		p.To.Offset = obj.StackPreempt

		p = obj.Appendp(ctxt, p)
		q = p
		p.As = ABEQ
		p.To.Type = D_BRANCH

		p = obj.Appendp(ctxt, p)
		p.As = AADD
		p.From.Type = D_CONST
		p.From.Offset = obj.StackGuard
		p.Reg = REGSP
		p.To.Type = D_REG
		p.To.Reg = 4

		p = obj.Appendp(ctxt, p)
		p.As = ASUB
		p.From.Type = D_REG
		p.From.Reg = 3
		p.To.Type = D_REG
		p.To.Reg = 4

		p = obj.Appendp(ctxt, p)
		p.As = AMOVD
		p.From.Type = D_CONST
		p.From.Offset = int64(framesize) + obj.StackGuard - obj.StackSmall
		p.To.Type = D_REG
		p.To.Reg = REGTMP

		p = obj.Appendp(ctxt, p)
		p.As = ACMPU
		p.From.Type = D_REG
		p.From.Reg = REGTMP
		p.To.Type = D_REG
		p.To.Reg = 4
	}

	// q1: BLT	done
	p = obj.Appendp(ctxt, p)
	q1 = p

	p.As = ABLT
	p.To.Type = D_BRANCH

	// MOVD	LR, R5
	p = obj.Appendp(ctxt, p)

	p.As = AMOVD
	p.From.Type = D_SPR
	p.From.Offset = D_LR
	p.To.Type = D_REG
	p.To.Reg = 5
	if q != nil {
		q.Pcond = p
	}

	// BL	runtime.morestack(SB)
	p = obj.Appendp(ctxt, p)

	p.As = ABL
	p.To.Type = D_BRANCH
	if ctxt.Cursym.Cfunc != 0 {
		p.To.Sym = obj.Linklookup(ctxt, "runtime.morestackc", 0)
	} else {

		p.To.Sym = ctxt.Symmorestack[noctxt]
	}

	// BR	start
	p = obj.Appendp(ctxt, p)

	p.As = ABR
	p.To.Type = D_BRANCH
	p.Pcond = ctxt.Cursym.Text.Link

	// placeholder for q1's jump target
	p = obj.Appendp(ctxt, p)

	p.As = ANOP // zero-width place holder
	q1.Pcond = p

	return p
}

func follow(ctxt *obj.Link, s *obj.LSym) {
	var firstp *obj.Prog
	var lastp *obj.Prog

	ctxt.Cursym = s

	firstp = ctxt.Arch.Prg()
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

	case ABGE:
		return ABLT
	case ABLT:
		return ABGE

	case ABGT:
		return ABLE
	case ABLE:
		return ABGT

	case ABVC:
		return ABVS
	case ABVS:
		return ABVC
	}

	return 0
}

func xfol(ctxt *obj.Link, p *obj.Prog, last **obj.Prog) {
	var q *obj.Prog
	var r *obj.Prog
	var a int
	var b int
	var i int

loop:
	if p == nil {
		return
	}
	a = int(p.As)
	if a == ABR {
		q = p.Pcond
		if (p.Mark&NOSCHED != 0) || q != nil && (q.Mark&NOSCHED != 0) {
			p.Mark |= FOLL
			(*last).Link = p
			*last = p
			p = p.Link
			xfol(ctxt, p, last)
			p = q
			if p != nil && !(p.Mark&FOLL != 0) {
				goto loop
			}
			return
		}

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
			if q == *last || (q.Mark&NOSCHED != 0) {
				break
			}
			b = 0 /* set */
			a = int(q.As)
			if a == ANOP {
				i--
				continue
			}

			if a == ABR || a == ARETURN || a == ARFI || a == ARFCI || a == ARFID || a == AHRFID {
				goto copy
			}
			if !(q.Pcond != nil) || (q.Pcond.Mark&FOLL != 0) {
				continue
			}
			b = relinv(a)
			if !(b != 0) {
				continue
			}

		copy:
			for {
				r = ctxt.Arch.Prg()
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
				if a == ABR || a == ARETURN || a == ARFI || a == ARFCI || a == ARFID || a == AHRFID {
					return
				}
				r.As = int16(b)
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

		a = ABR
		q = ctxt.Arch.Prg()
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
	if a == ABR || a == ARETURN || a == ARFI || a == ARFCI || a == ARFID || a == AHRFID {
		if p.Mark&NOSCHED != 0 {
			p = p.Link
			goto loop
		}

		return
	}

	if p.Pcond != nil {
		if a != ABL && p.Link != nil {
			xfol(ctxt, p.Link, last)
			p = p.Pcond
			if p == nil || (p.Mark&FOLL != 0) {
				return
			}
			goto loop
		}
	}

	p = p.Link
	goto loop
}

func prg() *obj.Prog {
	var p *obj.Prog

	p = new(obj.Prog)
	*p = zprg
	return p
}

var Linkppc64 = obj.LinkArch{
	ByteOrder:     binary.BigEndian,
	Pconv:         Pconv,
	Name:          "ppc64",
	Thechar:       '9',
	Endian:        obj.BigEndian,
	Addstacksplit: addstacksplit,
	Assemble:      span9,
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
	AJMP:          ABR,
	ANOP:          ANOP,
	APCDATA:       APCDATA,
	ARET:          ARETURN,
	ATEXT:         ATEXT,
	ATYPE:         ATYPE,
	AUSEFIELD:     AUSEFIELD,
}

var Linkppc64le = obj.LinkArch{
	ByteOrder:     binary.LittleEndian,
	Pconv:         Pconv,
	Name:          "ppc64le",
	Thechar:       '9',
	Endian:        obj.LittleEndian,
	Addstacksplit: addstacksplit,
	Assemble:      span9,
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
	AJMP:          ABR,
	ANOP:          ANOP,
	APCDATA:       APCDATA,
	ARET:          ARETURN,
	ATEXT:         ATEXT,
	ATYPE:         ATYPE,
	AUSEFIELD:     AUSEFIELD,
}
