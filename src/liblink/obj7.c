// From noop.c obj.c pass.c 

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
};

// Prog.mark
enum
{
	FOLL = 1<<0,
	LABEL = 1<<1,
	LEAF = 1<<2,
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
	case ARET:
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
			int32 i32;
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
			int64 i64;
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

	// Rewrite SUB constants into ADD.
	switch(p->as) {
	case ASUBS:
		if(p->from.type == D_CONST) {
			p->from.offset = -p->from.offset;
			p->as = AADDS;
		}
		break;

	case ASUB:
		if(p->from.type == D_CONST) {
			p->from.offset = -p->from.offset;
			p->as = AADD;
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
			if(a == AB || a == ARET || a == AERET)
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
				if(a == AB || a == ARET || a == AERET)
					return;
				r->as = a == ABNE ? ABEQ : ABNE;
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
	if(a == AB || a == ARET || a == AERET)
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
	Prog *q1;
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
		Bprint(ctxt->bso, "%5.2f addstacksplit\n", cputime());
	Bflush(ctxt->bso);
	q = nil;
	for(p = cursym->text; p != nil; p = p->link) {
		switch(p->as) {
		case ATEXT:
			p->mark |= LEAF;
			break;
		case ARET:
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
			if(p->to.offset < 0)
				ctxt->autosize = 0;
			else
				ctxt->autosize = p->to.offset + 8;
			if(((cursym->text->mark & LEAF)) && ctxt->autosize <= 8)
				ctxt->autosize = 0;
			else
				if(ctxt->autosize & ((16 - 1)))
					ctxt->autosize += 16 - ((ctxt->autosize & ((16 - 1))));
			p->to.offset = ctxt->autosize - 8;
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
			q->link = q1;
			break;
		case ARET:
			nocache(p);
			if(p->from.type == D_CONST) {
				ctxt->diag("using BECOME (%P) is not supported!", p);
				break;
			}
			if(cursym->text->mark & LEAF) {
				if(ctxt->autosize != 0) {
					p->as = AADD;
					p->from.type = D_CONST;
					p->from.offset = ctxt->autosize;
					p->to.type = D_REG;
					p->to.reg = REGSP;
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
				if(ctxt->autosize > aoffset) {
					q = ctxt->arch->prg();
					q->as = AADD;
					q->from.type = D_CONST;
					q->from.offset = ctxt->autosize - aoffset;
					q->to.type = D_REG;
					q->to.reg = REGSP;
					q->link = p->link;
					p->link = q;
					p = q;
				}
			}
			if(p->as != ARET) {
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
	.ARET = ARET,
	.ATEXT = ATEXT,
	.ATYPE = ATYPE,
	.AUSEFIELD = AUSEFIELD,
};
