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

#include <u.h>
#include <libc.h>
#include <bio.h>
#include <link.h>
#include "../cmd/7l/7.out.h"
#include "../runtime/stack.h"

void addstacksplit(Link*, LSym*);
static void nocache(Prog*);
static int relinv(int);
static void xfol(Link *, Prog *, Prog **);
static void follow(Link *, LSym *);

static Prog zprg = {
	.as = AGOK,
	.reg = NREG,
	.from = {
		.name = D_NONE,
		.type = D_NONE,
		.reg = NREG,
	},
	.from3 = {
		.name = D_NONE,
		.type = D_NONE,
		.reg = NREG,
	},
	.to = {
		.name = D_NONE,
		.type = D_NONE,
		.reg = NREG,
	},
	.to3 = {
		.name = D_NONE,
		.type = D_NONE,
		.reg = NREG,
	},
};

static int
symtype(Addr *a)
{
	return a->name;
}

static int
isdata(Prog *p)
{
	return p->as == ADATA || p->as == AGLOBL;
}

static int
iscall(Prog *p)
{
	return p->as == ABL;
}

static int
datasize(Prog *p)
{
	return p->reg;
}

static int
textflag(Prog *p)
{
	return p->reg;
}

static void
settextflag(Prog *p, int f)
{
	p->reg = f;
}

static short complements[] = {
	[AADD]	= ASUB,
	[AADDW]	= ASUBW,
	[ASUB]	= AADD,
	[ASUBW]	= AADDW,
	[ACMP]	= ACMN,
	[ACMPW]	= ACMNW,
	[ACMN]	= ACMP,
	[ACMNW]	= ACMPW,
};

static void
progedit(Link *ctxt, Prog *p)
{
	char literal[64];
	LSym *s;

	USED(ctxt);

	p->from.class = 0;
	p->to.class = 0;

	// Rewrite BR/BL to symbol as D_BRANCH.
	switch(p->as) {
	case AB:
	case ABL:
	case ARETURN:
	case ADUFFZERO:
	case ADUFFCOPY:
		if(p->to.sym != nil)
			p->to.type = D_BRANCH;
		break;
	}

	// Rewrite float constants to values stored in memory.
	switch(p->as) {
	case AFMOVS:
		if(p->from.type == D_FCONST) {
			uint32 i32;
			float32 f32;
			f32 = p->from.u.dval;
			memmove(&i32, &f32, 4);
			sprint(literal, "$f32.%08ux", (uint32)i32);
			s = linklookup(ctxt, literal, 0);
			s->size = 4;
			p->from.type = D_OREG;
			p->from.sym = s;
			p->from.name = D_EXTERN;
			p->from.offset = 0;
		}
		break;
	case AFMOVD:
		if(p->from.type == D_FCONST) {
			uint64 i64;
			memmove(&i64, &p->from.u.dval, 8);
			sprint(literal, "$f64.%016llux", (uvlong)i64);
			s = linklookup(ctxt, literal, 0);
			s->size = 8;
			p->from.type = D_OREG;
			p->from.sym = s;
			p->from.name = D_EXTERN;
			p->from.offset = 0;
		}
		break;
	}

	// Rewrite negative immediates as positive immediates with
	// complementary instruction.
	switch(p->as) {
	case AADD:
	case AADDW:
	case ASUB:
	case ASUBW:
	case ACMP:
	case ACMPW:
	case ACMN:
	case ACMNW:
		if(p->from.type == D_CONST && p->from.offset < 0) {
			p->from.offset = -p->from.offset;
			p->as = complements[p->as];
		}
		break;
	}
}

static void
follow(Link *ctxt, LSym *s)
{
	Prog *firstp, *lastp;

	ctxt->cursym = s;

	firstp = ctxt->arch->prg();
	lastp = firstp;
	xfol(ctxt, s->text, &lastp);
	lastp->link = nil;
	s->text = firstp->link;
}

static int
relinv(int a)
{
	switch(a) {
	case ABEQ:	return ABNE;
	case ABNE:	return ABEQ;
	case ABCS:	return ABCC;
	case ABHS:	return ABLO;
	case ABCC:	return ABCS;
	case ABLO:	return ABHS;
	case ABMI:	return ABPL;
	case ABPL:	return ABMI;
	case ABVS:	return ABVC;
	case ABVC:	return ABVS;
	case ABHI:	return ABLS;
	case ABLS:	return ABHI;
	case ABGE:	return ABLT;
	case ABLT:	return ABGE;
	case ABGT:	return ABLE;
	case ABLE:	return ABGT;
	}
	sysfatal("unknown relation: %s", anames5[a]);
	return 0;
}

static void
xfol(Link *ctxt, Prog *p, Prog **last)
{
	Prog *q;
	Prog *r;
	int a;
	int i;
loop:
	if(p == nil)
		return;
	a = p->as;
	if(a == AB) {
		q = p->pcond;
		if(q != nil) {
			p->mark |= FOLL;
			p = q;
			if(!((p->mark & FOLL)))
				goto loop;
		}
	}
	if(p->mark & FOLL) {
		for(i = 0, q = p; i < 4; i++, q = q->link) {
			if(q == *last || q == nil)
				break;
			a = q->as;
			if(a == ANOP) {
				i--;
				continue;
			}
			if(a == AB || a == ARETURN || a == ARET || a == AERET)
				goto copy;
			if(q->pcond == nil || ((q->pcond->mark & FOLL)))
				continue;
			if(a != ABEQ && a != ABNE)
				continue;
		copy:
			for(;;) {
				r = ctxt->arch->prg();
				*r = *p;
				if(!((r->mark & FOLL)))
					print("cant happen 1\n");
				r->mark |= FOLL;
				if(p != q) {
					p = p->link;
					(*last)->link = r;
					*last = r;
					continue;
				}
				(*last)->link = r;
				*last = r;
				if(a == AB || a == ARETURN || a == ARET || a == AERET)
					return;
				if(a == ABNE)
					r->as = ABEQ;
				else
					r->as = ABNE;
				r->pcond = p->link;
				r->link = p->pcond;
				if(!((r->link->mark & FOLL)))
					xfol(ctxt, r->link, last);
				if(!((r->pcond->mark & FOLL)))
					print("cant happen 2\n");
				return;
			}
		}
		a = AB;
		q = ctxt->arch->prg();
		q->as = a;
		q->lineno = p->lineno;
		q->to.type = D_BRANCH;
		q->to.offset = p->pc;
		q->pcond = p;
		p = q;
	}
	p->mark |= FOLL;
	(*last)->link = p;
	*last = p;
	if(a == AB || a == ARETURN || a == ARET || a == AERET)
		return;
	if(p->pcond != nil)
		if(a != ABL && p->link != nil) {
			q = brchain(ctxt, p->link);
			if(a != ATEXT && a != ABCASE)
				if(q != nil && ((q->mark & FOLL))) {
					p->as = relinv(a);
					p->link = p->pcond;
					p->pcond = q;
				}
			xfol(ctxt, p->link, last);
			q = brchain(ctxt, p->pcond);
			if(q == nil)
				q = p->pcond;
			if(q->mark & FOLL) {
				p->pcond = q;
				return;
			}
			p = q;
			goto loop;
		}
	p = p->link;
	goto loop;

}

static void
parsetextconst(vlong arg, vlong *textstksiz, vlong *textarg)
{
	*textstksiz = arg & 0xffffffffLL;
	if(*textstksiz & 0x80000000LL)
		*textstksiz = -(-*textstksiz & 0xffffffffLL);

	*textarg = (arg >> 32) & 0xffffffffLL;
	if(*textarg & 0x80000000LL)
		*textarg = 0;
	*textarg = (*textarg+7) & ~7LL;
}

void
addstacksplit(Link *ctxt, LSym *cursym)
{
	Prog *p;
	Prog *q;
	Prog *q1, *q2;
	int o;
	vlong textstksiz, textarg;
	int32 aoffset;

	if(ctxt->symmorestack[0] == nil) {
		ctxt->symmorestack[0] = linklookup(ctxt, "runtime.morestack", 0);
		ctxt->symmorestack[1] = linklookup(ctxt, "runtime.morestack_noctxt", 0);
	}

	ctxt->cursym = cursym;

	if(cursym->text == nil || cursym->text->link == nil)
		return;				

	p = cursym->text;
	parsetextconst(p->to.offset, &textstksiz, &textarg);
	aoffset = textstksiz;
	if(aoffset < 0)
		aoffset = 0;
	
	cursym->args = p->to.offset>>32;
	cursym->locals = textstksiz;

	/*
	 * find leaf subroutines
	 * strip NOPs
	 * expand RET
	 */
	if(ctxt->debugvlog)
		Bprint(ctxt->bso, "%5.2f noops\n", cputime());
	Bflush(ctxt->bso);
	q = nil;
	for(p = cursym->text; p != nil; p = p->link) {
		switch(p->as) {
		case ATEXT:
			p->mark |= LEAF;
			break;
		case ARETURN:
			break;
		case ANOP:
			q1 = p->link;
			q->link = q1; /* q is non-nop */
			q1->mark |= p->mark;
			continue;
		case ABL:
		case ADUFFZERO:
		case ADUFFCOPY:
			cursym->text->mark &= ~LEAF;
		case ACBNZ:
		case ACBZ:
		case ACBNZW:
		case ACBZW:
		case ATBZ:
		case ATBNZ:
		case ABCASE:
		case AB:
		case ABEQ:
		case ABNE:
		case ABCS:
		case ABHS:
		case ABCC:
		case ABLO:
		case ABMI:
		case ABPL:
		case ABVS:
		case ABVC:
		case ABHI:
		case ABLS:
		case ABGE:
		case ABLT:
		case ABGT:
		case ABLE:
		case AADR: /* strange */
		case AADRP:
			q1 = p->pcond;
			if(q1 != nil) {
				while(q1->as == ANOP) {
					q1 = q1->link;
					p->pcond = q1;
				}
			}
			break;
		}
		q = p;
	}
	for(p = cursym->text; p != nil; p = p->link) {
		o = p->as;
		switch(o) {
		case ATEXT:
			cursym->text = p;
			if(textstksiz < 0)
				ctxt->autosize = 0;
			else
				ctxt->autosize = textstksiz + 8;
			if(((cursym->text->mark & LEAF)) && ctxt->autosize <= 8)
				ctxt->autosize = 0;
			else
				if(ctxt->autosize & ((16 - 1)))
					ctxt->autosize += 16 - ((ctxt->autosize & ((16 - 1))));
			p->to.offset = ((uint64)p->to.offset & (0xffffffffull<<32)) | (uint32)(ctxt->autosize-8);
			if(ctxt->autosize == 0 && !((cursym->text->mark & LEAF))) {
				if(ctxt->debugvlog)
					Bprint(ctxt->bso, "save suppressed in: %s\n", cursym->text->from.sym->name);
				Bflush(ctxt->bso);
				cursym->text->mark |= LEAF;
			}
			aoffset = ctxt->autosize;
			if(aoffset > 0xF0)
				aoffset = 0xF0;
			if(cursym->text->mark & LEAF) {
				cursym->leaf = 1;
				if(ctxt->autosize == 0)
					break;
				aoffset = 0;
			}
			q = p;
			if(ctxt->autosize > aoffset) {
				q = ctxt->arch->prg();
				q->as = ASUB;
				q->lineno = p->lineno;
				q->from.type = D_CONST;
				q->from.offset = ctxt->autosize - aoffset;
				q->to.type = D_REG;
				q->to.reg = REGSP;
				q->spadj = q->from.offset;
				q->link = p->link;
				p->link = q;
				if(cursym->text->mark & LEAF)
					break;
			}
			q1 = ctxt->arch->prg();
			q1->as = AMOV;
			q1->lineno = p->lineno;
			q1->from.type = D_REG;
			q1->from.reg = REGLINK;
			q1->to.type = D_XPRE;
			q1->to.offset = -aoffset;
			q1->to.reg = REGSP;
			q1->link = q->link;
			q1->spadj = aoffset;
			q->link = q1;

			if(cursym->text->reg & WRAPPER) {
				// if(g->panic != nil && g->panic->argp == FP) g->panic->argp = bottom-of-frame
				//
				//	MOV g_panic(g), R1
				//	CMP $0, R1
				//	BEQ end
				//	MOV panic_argp(R0), R2
				//	ADD $(autosize+8), RSP, R3
				//	CMP R2, R3
				//	BNE end
				//	ADD $8, RSP, R4
				//	MOVD R4, panic_argp(R1)
				// end:
				//	NOP
				//
				// The NOP is needed to give the jumps somewhere to land.
				// It is a liblink NOP, not a ARM64 NOP: it encodes to 0 instruction bytes.
				q = q1;
				q = appendp(ctxt, q);
				q->as = AMOV;
				q->from.type = D_OREG;
				q->from.reg = REGG;
				q->from.offset = 4*ctxt->arch->ptrsize; // G.panic
				q->to.type = D_REG;
				q->to.reg = 1;

				q = appendp(ctxt, q);
				q->as = ACMP;
				q->from.type = D_CONST;
				q->from.offset = 0;
				q->reg = 1;

				q = appendp(ctxt, q);
				q->as = ABEQ;
				q->to.type = D_BRANCH;
				q1 = q;

				q = appendp(ctxt, q);
				q->as = AMOV;
				q->from.type = D_OREG;
				q->from.reg = 1;
				q->from.offset = 0; // Panic.argp
				q->to.type = D_REG;
				q->to.reg = 2;

				q = appendp(ctxt, q);
				q->as = AADD;
				q->from.type = D_CONST;
				q->from.offset = ctxt->autosize+8;
				q->reg = REGSP;
				q->to.type = D_REG;
				q->to.reg = 3;

				q = appendp(ctxt, q);
				q->as = ACMP;
				q->from.type = D_REG;
				q->from.reg = 2;
				q->reg = 3;

				q = appendp(ctxt, q);
				q->as = ABNE;
				q->to.type = D_BRANCH;
				q2 = q;

				q = appendp(ctxt, q);
				q->as = AADD;
				q->from.type = D_CONST;
				q->from.offset = 8;
				q->reg = REGSP;
				q->to.type = D_REG;
				q->to.reg = 4;

				q = appendp(ctxt, q);
				q->as = AMOV;
				q->from.type = D_REG;
				q->from.reg = 4;
				q->to.type = D_OREG;
				q->to.reg = 1;
				q->to.offset = 0; // Panic.argp

				q = appendp(ctxt, q);
				q->as = ANOP;
				q1->pcond = q;
				q2->pcond = q;
			}
			break;
		case ARETURN:
			nocache(p);
			if(p->from.type == D_CONST) {
				ctxt->diag("using BECOME (%P) is not supported!", p);
				break;
			}
			if(p->to.sym) { // retjmp
				p->as = AB;
				p->to.type = D_BRANCH;
				break;
			}
			if(cursym->text->mark & LEAF) {
				if(ctxt->autosize != 0) {
					p->as = AADD;
					p->from.type = D_CONST;
					p->from.offset = ctxt->autosize;
					p->to.type = D_REG;
					p->to.reg = REGSP;
					p->spadj = -ctxt->autosize;
				}
			} else {
				/* want write-back pre-indexed SP+autosize -> SP, loading REGLINK*/
				aoffset = ctxt->autosize;
				if(aoffset > 0xF0)
					aoffset = 0xF0;
				p->as = AMOV;
				p->from.type = D_XPOST;
				p->from.offset = aoffset;
				p->from.reg = REGSP;
				p->to.type = D_REG;
				p->to.reg = REGLINK;
				p->spadj = -aoffset;
				if(ctxt->autosize > aoffset) {
					q = ctxt->arch->prg();
					q->as = AADD;
					q->from.type = D_CONST;
					q->from.offset = ctxt->autosize - aoffset;
					q->to.type = D_REG;
					q->to.reg = REGSP;
					q->link = p->link;
					q->spadj = -q->from.offset;
					q->lineno = p->lineno;
					p->link = q;
					p = q;
				}
			}
			if(p->as != ARETURN) {
				q = ctxt->arch->prg();
				q->lineno = p->lineno;
				q->link = p->link;
				p->link = q;
				p = q;
			}
			p->as = ARET;
			p->lineno = p->lineno;
			p->to.type = D_OREG;
			p->to.offset = 0;
			p->to.reg = REGLINK;
			p->spadj = +ctxt->autosize;
			break;
		case AADD:
		case ASUB:
			if(p->to.type == D_SP && p->to.reg == REGSP && p->from.type == D_CONST)
				if (p->as == AADD)
					p->spadj = -p->from.offset;
				else
					p->spadj = +p->from.offset;
			break;
		}
	}
}

static void
nocache(Prog *p)
{
	p->optab = 0;
	p->from.class = 0;
	p->to.class = 0;
}

static Prog*
prg(void)
{
	Prog *p;

	p = emallocz(sizeof(*p));
	*p = zprg;
	return p;
}

LinkArch linkarm64 = {
	.name = "arm64",
	.thechar = '7',
	.endian = LittleEndian,

	.addstacksplit = addstacksplit,
	.assemble = span7,
	.datasize = datasize,
	.follow = follow,
	.iscall = iscall,
	.isdata = isdata,
	.prg = prg,
	.progedit = progedit,
	.settextflag = settextflag,
	.symtype = symtype,
	.textflag = textflag,

	.minlc = 4,
	.ptrsize = 8,
	.regsize = 8,

	.D_ADDR = D_ADDR,
	.D_AUTO = D_AUTO,
	.D_BRANCH = D_BRANCH,
	.D_CONST = D_CONST,
	.D_EXTERN = D_EXTERN,
	.D_FCONST = D_FCONST,
	.D_NONE = D_NONE,
	.D_PARAM = D_PARAM,
	.D_SCONST = D_SCONST,
	.D_STATIC = D_STATIC,
	.D_OREG = D_OREG,

	.ACALL = ABL,
	.ADATA = ADATA,
	.AEND = AEND,
	.AFUNCDATA = AFUNCDATA,
	.AGLOBL = AGLOBL,
	.AJMP = AB,
	.ANOP = ANOP,
	.APCDATA = APCDATA,
	.ARET = ARETURN,
	.ATEXT = ATEXT,
	.ATYPE = ATYPE,
	.AUSEFIELD = AUSEFIELD,
};
