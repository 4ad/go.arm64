// From Plan 9's 7l/list.c and 7l/sub.c.

#include <u.h>
#include <libc.h>
#include <bio.h>
#include <link.h>
#include "../cmd/7l/7.out.h"

enum
{
	STRINGSZ = 200,
};

static int Pconv(Fmt*);
static int Aconv(Fmt*);
static int Dconv(Fmt*);
static int Mconv(Fmt*);
static int Rconv(Fmt*);
static int DSconv(Fmt*);
static int DRconv(Fmt*);

static char *strcond[16] = {
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
	"NV"
};

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

#pragma	varargck	type	"$"	char*
#pragma	varargck	type	"M"	Addr*

void
listinit7(void)
{
	fmtinstall('A', Aconv);
	fmtinstall('D', Dconv);
	fmtinstall('P', Pconv);
	fmtinstall('R', Rconv);

	// for liblink internal use
	fmtinstall('^', DRconv);

	// for internal use
	fmtinstall('$', DSconv);
	fmtinstall('M', Mconv);
}

static Prog*	bigP;

static int
Pconv(Fmt *fp)
{
	char str[STRINGSZ];
	char *s;
	Prog *p;
	int a;
	p = va_arg(fp->args, Prog*);
	bigP = p;
	a = p->as;
	switch(a) {
	default:
		s = str;
		if(p->reg == NREG && p->from3.type == D_NONE && p->to3.type == D_NONE)
			sprint(s, "%.5lld (%L)	%A	%D,%D", p->pc, p->lineno, a, &p->from, &p->to);
		else if(p->from.type != D_FREG) {
			sprint(s, "%.5lld (%L)	%A	%D", p->pc, p->lineno, a, &p->from);
			if(p->from3.type != D_NONE)
				sprint(strchr(s, 0), ",%D", &p->from3);
			if(p->reg != NREG)
				sprint(strchr(s, 0), ",R%d", p->reg);
			if(p->to3.type != D_NONE)
				sprint(strchr(s, 0), ",%D,%D", &p->to, &p->to3);
			else
				sprint(strchr(s, 0), ",%D", &p->to);
		} else
			sprint(s, "%.5lld (%L)	%A	%D,F%d,%D", p->pc, p->lineno, a, &p->from, p->reg, &p->to);
		break;
	case ATEXT:
		if(p->reg != 0)
			sprint(str, "%.5lld (%L)	%A	%D,%d,%lD", p->pc, p->lineno, a, &p->from, p->reg, &p->to);
		else
			sprint(str, "%.5lld (%L)	%A	%D,%lD", p->pc, p->lineno, a, &p->from, &p->to);
		break;
	case AGLOBL:
		if(p->reg != 0)
			sprint(str, "%.5lld (%L)	%A	%D,%d,%D", p->pc, p->lineno, a, &p->from, p->reg, &p->to);
		else
			sprint(str, "%.5lld (%L)	%A	%D,%D", p->pc, p->lineno, a, &p->from, &p->to);
		break;
	case ADATA:
	case AINIT:
	case ADYNT:
		sprint(str, "%.5lld (%L)	%A	%D/%d,%D", p->pc, p->lineno, a, &p->from, p->reg, &p->to);
		break;
	}
	return fmtstrcpy(fp, str);
}

static int
Aconv(Fmt *fp)
{
	char *s;
	int a;
	a = va_arg(fp->args, int);
	s = "???";
	if(a >= AXXX && a < ALAST && anames7[a])
		s = anames7[a];
	return fmtstrcpy(fp, s);
}

static int
Dconv(Fmt *fp)
{
	char str[STRINGSZ];
	char *op;
	Addr *a;
	int32 v;
	static char *extop[] = {".UB", ".UH", ".UW", ".UX", ".SB", ".SH", ".SW", ".SX"};

	a = va_arg(fp->args, Addr*);
	if(fp->flags & FmtLong) {
		if(a->type == D_CONST)
			sprint(str, "$%d-%d", (int32)a->offset, (int32)(a->offset>>32));
		else {
			// ATEXT dst is not constant
			sprint(str, "!!%D", a);
		}
		goto ret;
	}

	switch(a->type) {
	default:
		sprint(str, "GOK-type(%d)", a->type);
		break;
	case D_NONE:
		str[0] = 0;
		if(a->name != D_NONE || a->reg != NREG || a->sym != nil)
			sprint(str, "%M(R%d)(NONE)", a, a->reg);
		break;
	case D_CONST:
		if(a->reg == NREG || a->reg == REGZERO)
			sprint(str, "$%M", a);
		else
			sprint(str, "$%M(R%d)", a, a->reg);
		break;
	case D_SHIFT:
		v = a->offset;
		op = &"<<>>->@>"[(((((v >> 22)) & 3)) << 1)];
		sprint(str, "R%ld%c%c%ld", ((v >> 16)) & 0x1F, op[0], op[1], ((v >> 10)) & 0x3F);
		if(a->reg != NREG)
			sprint(str + strlen(str), "(R%d)", a->reg);
		break;
	case D_OCONST:
		sprint(str, "$*$%M", a);
		if(a->reg != NREG)
			sprint(str, "%M(R%d)(CONST)", a, a->reg);
		break;
	case D_OREG:
		if(a->reg != NREG)
			sprint(str, "%M(R%d)", a, a->reg);
		else
			sprint(str, "%M", a);
		break;
	case D_XPRE:
		if(a->reg != NREG)
			sprint(str, "%M(R%d)!", a, a->reg);
		else
			sprint(str, "%M!", a);
		break;
	case D_XPOST:
		if(a->reg != NREG)
			sprint(str, "(R%d)%M!", a->reg, a);
		else
			sprint(str, "%M!", a);
		break;
	case D_EXTREG:
		v = a->offset;
		if(v & ((7 << 10)))
			snprint(str, sizeof ((str)), "R%ld%s<<%ld", ((v >> 16)) & 31, extop[((v >> 13)) & 7], ((v >> 10)) & 7);
		else
			snprint(str, sizeof ((str)), "R%ld%s", ((v >> 16)) & 31, extop[((v >> 13)) & 7]);
		break;
	case D_ROFF:
		v = a->offset;
		if(v & ((1 << 16)))
			snprint(str, sizeof ((str)), "(R%d)[R%ld%s]", a->reg, v & 31, extop[((v >> 8)) & 7]);
		else
			snprint(str, sizeof ((str)), "(R%d)(R%ld%s)", a->reg, v & 31, extop[((v >> 8)) & 7]);
		break;
	case D_REG:
		sprint(str, "R%d", a->reg);
		if(a->name != D_NONE || a->sym != nil)
			sprint(str, "%M(R%d)(REG)", a, a->reg);
		break;
	case D_SP:
		if(a->name != D_NONE || a->sym != nil)
			sprint(str, "%M(R%d)(REG)", a, a->reg);
		else
			strcpy(str, "SP");
		break;
	case D_COND:
		strcpy(str, strcond[a->reg & 0xF]);
		break;
	case D_FREG:
		sprint(str, "F%d", a->reg);
		if(a->name != D_NONE || a->sym != nil)
			sprint(str, "%M(R%d)(REG)", a, a->reg);
		break;
	case D_SPR:
		switch(a->offset) {
		case D_FPSR:
			sprint(str, "FPSR");
			break;
		case D_FPCR:
			sprint(str, "FPCR");
			break;
		case D_NZCV:
			sprint(str, "NZCV");
			break;
		default:
			sprint(str, "SPR(%#llux)", a->offset);
			break;
		}
		if(a->name != D_NONE || a->sym != nil)
			sprint(str, "%M(SPR%lld)(REG)", a, a->offset);
		break;
	case D_BRANCH: /* botch */
		if(bigP->pcond != nil) {
			v = bigP->pcond->pc;
			if(a->sym != nil)
				sprint(str, "%s+%#.5lux(BRANCH)", a->sym->name, v);
			else
				sprint(str, "%.5lux(BRANCH)", v);
		} else
			if(a->sym != nil)
				sprint(str, "%s+%lld(APC)", a->sym->name, a->offset);
			else
				sprint(str, "%lld(APC)", a->offset);
		break;
	case D_FCONST:
		sprint(str, "$%.17g", a->u.dval);
		break;
	case D_SCONST:
		sprint(str, "$\"%$\"", a->u.sval);
		break;
	}
ret:
	return fmtstrcpy(fp, str);
}

static int
Mconv(Fmt *fp)
{
	char str[STRINGSZ];
	Addr *a;
	LSym *s;
	a = va_arg(fp->args, Addr*);
	s = a->sym;
	switch(a->name) {
	default:
		sprint(str, "GOK-name(%d)", a->name);
		break;
	case D_NONE:
		sprint(str, "%lld", a->offset);
		break;
	case D_EXTERN:
		if(s == nil)
			sprint(str, "%lld(SB)", a->offset);
		else
			sprint(str, "%s+%lld(SB)", s->name, a->offset);
		break;
	case D_STATIC:
		if(s == nil)
			sprint(str, "<>+%lld(SB)", a->offset);
		else
			sprint(str, "%s<>+%lld(SB)", s->name, a->offset);
		break;
	case D_AUTO:
		if(s == nil)
			sprint(str, "%lld(SP)", a->offset);
		else
			sprint(str, "%s-%lld(SP)", s->name, -a->offset);
		break;
	case D_PARAM:
		if(s == nil)
			sprint(str, "%lld(FP)", a->offset);
		else
			sprint(str, "%s+%lld(FP)", s->name, a->offset);
		break;
	}
	return fmtstrcpy(fp, str);
}

static int
Rconv(Fmt *fp)
{
	int r;
	char str[STRINGSZ];
	r = va_arg(fp->args, int);
	sprint(str, "R%d", r);
	return fmtstrcpy(fp, str);
}

static int
DRconv(Fmt *fp)
{
        char *s;
        int a;

        a = va_arg(fp->args, int);
        s = "C_??";
        if(a >= C_NONE && a <= C_NCLASS)
                s = cnames7[a];
        return fmtstrcpy(fp, s);
}

static int
DSconv(Fmt *fp)
{
	int i;
	int c;
	char str[STRINGSZ];
	char *p;
	char *a;
	a = va_arg(fp->args, char*);
	p = str;
	for(i = 0; i < sizeof(int32); i++) {
		c = a[i] & 0xff;
		if(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9' || c == ' ' || c == '%') {
			*p++ = c;
			continue;
		}
		*p++ = '\\';
		switch(c) {
		case 0:
			*p++ = 'z';
			continue;
		case '\\':
		case '"':
			*p++ = c;
			continue;
		case '\n':
			*p++ = 'n';
			continue;
		case '\t':
			*p++ = 't';
			continue;
		}
		*p++ = ((c >> 6)) + '0';
		*p++ = ((((c >> 3)) & 7)) + '0';
		*p++ = ((c & 7)) + '0';
	}
	*p = 0;
	return fmtstrcpy(fp, str);

}
