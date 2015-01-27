%{
package main

import (
	"cmd/internal/asm"
	"cmd/internal/obj"
	. "cmd/internal/obj/arm64"
)
%}

%union
{
	sym *asm.Sym
	lval int64
	dval float64
	sval string
	addr obj.Addr
}

%left	'|'
%left	'^'
%left	'&'
%left	'<' '>'
%left	'+' '-'
%left	'*' '/' '%'
%token	<lval>	LTYPE0 LTYPE1 LTYPE2 LTYPE3 LTYPE4 LTYPE5
%token	<lval>	LTYPE6 LTYPE7 LTYPE8 LTYPE9 LTYPEA
%token	<lval>	LTYPEB LTYPEC LTYPED LTYPEE LTYPEF
%token	<lval>	LTYPEG LTYPEH LTYPEI LTYPEJ LTYPEK
%token	<lval>	LTYPEL LTYPEM LTYPEN LTYPEO LTYPEP LTYPEQ
%token	<lval>	LTYPER LTYPES LTYPET LTYPEU LTYPEV LTYPEW LTYPEX LTYPEY LTYPEZ
%token	<lval>	LMOVK LDMB LSTXR
%token	<lval>	LCONST LSP LSB LFP LPC
%token	<lval>	LR LREG LF LFREG LV LVREG LC LCREG LFCR LFCSEL
%token	<lval>	LCOND LS LAT LEXT LSPR LSPREG LVTYPE
%token	<lval>	LPCDAT LFUNCDAT LSCHED
%token	<dval>	LFCONST
%token	<sval>	LSCONST
%token	<sym>	LNAME LLAB LVAR
%type	<lval>	con expr pointer offset sreg spreg
%type	<lval>	scon indexreg vset vreglist
%type	<addr>	addr rel reg freg vreg shift fcon frcon extreg vlane vaddr
%type	<addr>	imm ximm name oreg nireg ioreg imsr spr cond sysarg
%%
prog:
|	prog line

line:
|	LNAME ':'
	{
		$1 = asm.labellookup($1);
		if($1.Type == LLAB && $1.Value != int64(asm.PC))
			yyerror("redeclaration of %s", $1.Labelname);
		$1.Type = LLAB;
		$1.Value = int64(asm.PC);
	}
	line
|	LNAME '=' expr ';'
	{
		$1.Type = LVAR;
		$1.Value = $3;
	}
|	LVAR '=' expr ';'
	{
		if($1.Value != $3)
			yyerror("redeclaration of %s", $1->name);
		$1.Value = $3;
	}
|	LSCHED ';'
	{
		nosched = int($1);
	}
|	';'
|	inst ';'
|	error ';'

inst:
/*
 * ERET
 */
	LTYPE0 comma
	{
		outcode(int($1), &nullgen, NREG, &nullgen);
	}
/*
 * ADD
 */
|	LTYPE1 imsr ',' spreg ',' reg
	{
		outcode(int($1), &$2, $4, &$6);
	}
|	LTYPE1 imsr ',' spreg ','
	{
		outcode(int($1), &$2, $4, &nullgen);
	}
|	LTYPE1 imsr ',' reg
	{
		outcode(int($1), &$2, NREG, &$4);
	}
/*
 * CLS
 */
|	LTYPE2 imsr ',' reg
	{
		outcode(int($1), &$2, NREG, &$4);
	}
/*
 * MOV
 */
|	LTYPE3 addr ',' addr
	{
		outcode(int($1), &$2, NREG, &$4);
	}
/*
 * MOVK
 */
|	LMOVK imm ',' reg
	{
		outcode(int($1), &$2, NREG, &$4);
	}
|	LMOVK imm '<' '<' con ',' reg
	{
		var a obj.Addr
		a = nullgen;
		a.Type_ = D_CONST;
		a.Offset = $5;
		outgcode(int($1), &$2, NREG, &a, &$7);
	}
/*
 * B/BL
 */
|	LTYPE4 comma rel
	{
		outcode(int($1), &nullgen, NREG, &$3);
	}
|	LTYPE4 comma nireg
	{
		outcode(int($1), &nullgen, NREG, &$3);
	}
/*
 * BEQ
 */
|	LTYPE5 comma rel
	{
		outcode(int($1), &nullgen, NREG, &$3);
	}
/*
 * SVC
 */
|	LTYPE6 comma addr
	{
		outcode(int($1), &nullgen, NREG, &$3);
	}
|	LTYPE6
	{
		outcode(int($1), &nullgen, NREG, &nullgen);
	}
/*
 * CMP
 */
|	LTYPE7 imsr ',' spreg comma
	{
		outcode(int($1), &$2, $4, &nullgen);
	}
/*
 * CBZ
 */
|	LTYPE8 reg ',' rel
	{
		outcode(int($1), &$2, NREG, &$4);
	}
/*
 * CSET
 */
|	LTYPER cond ',' reg
	{
		outcode(int($1), &$2, NREG, &$4);
	}
/*
 * CSEL/CINC/CNEG/CINV
 */
|	LTYPES cond ',' reg ',' reg ',' reg
	{
		outgcode(int($1), &$2, $6.Reg, &$4, &$8);
	}
|	LTYPES cond ',' reg ',' reg
	{
		outcode(int($1), &$2, $4.Reg, &$6);
	}
/*
 * TBZ
 */
|	LTYPET imm ',' reg ',' rel
	{
		outcode(int($1), &$2, $4.Reg, &$6);
	}
/*
 * CCMN
 */
|	LTYPEU cond ',' imsr ',' reg ',' imm comma
	{
		outgcode(int($1), &$2, $6.Reg, &$4, &$8);
	}
/*
 * ADR
 */
|	LTYPEV rel ',' reg
	{
		outcode(int($1), &$2, NREG, &$4);
	}
|	LTYPEV '$' name ',' reg
	{
		outcode(int($1), &$3, NREG, &$5);
	}
/*
 * BFM/BFI
 */
|	LTYPEY imm ',' imm ',' spreg ',' reg
	{
		outgcode(int($1), &$2, $6, &$4, &$8);
	}
/*
 * EXTR
 */
|	LTYPEP imm ',' reg ',' spreg ',' reg
	{
		outgcode(int($1), &$2, $6, &$4, &$8);
	}
/*
 * RET/RETURN
 */
|	LTYPEA comma
	{
		outcode(int($1), &nullgen, NREG, &nullgen);
	}
|	LTYPEA reg
	{
		outcode(int($1), &nullgen, NREG, &$2);
	}
/*
 * NOP
 */
|	LTYPEQ comma
	{
		outcode(int($1), &nullgen, NREG, &nullgen);
	}
|	LTYPEQ reg comma
	{
		outcode(int($1), &$2, NREG, &nullgen);
	}
|	LTYPEQ freg comma
	{
		outcode(int($1), &$2, NREG, &nullgen);
	}
|	LTYPEQ ',' reg
	{
		outcode(int($1), &nullgen, NREG, &$3);
	}
|	LTYPEQ ',' freg
	{
		outcode(int($1), &nullgen, NREG, &$3);
	}
/*
 * TEXT/GLOBL
 */
|       LTYPEB name ',' imm
	{
		asm.Settext($2.Sym);
		outcode(int($1), &$2, NREG, &$4);
	}
|       LTYPEB name ',' con ',' imm
	{
		asm.Settext($2.Sym);
		$6.Offset &= 0xffffffff;
		$6.Offset |= -obj.ArgsSizeUnknown << 32;
		outcode(int($1), &$2, int($4), &$6);
	}
|       LTYPEB name ',' con ',' imm '-' con
	{
		asm.Settext($2.Sym);
		$6.Offset &= 0xffffffff;
		$6.Offset |= ($8 & 0xffffffff) << 32;
		outcode(int($1), &$2, int($4), &$6);
	}
/*
 * DATA
 */
|	LTYPEC name '/' con ',' ximm
	{
		outcode(int($1), &$2, $4, &$6);
	}
/*
 * CASE
 */
|	LTYPED reg ',' reg
	{
		outcode(int($1), &$2, NREG, &$4);
	}
/*
 * word
 */
|	LTYPEH comma ximm
	{
		outcode(int($1), &nullgen, NREG, &$3);
	}
/*
 * PCDATA
 */
|	LPCDAT imm ',' imm
	{
		if $2.Type != D_CONST || $4.Type != D_CONST {
			yyerror("arguments to PCDATA must be integer constants")
		}
		outcode(int($1), &$2, NREG, &$4);
	}
/*
 * FUNCDATA
 */
|	LFUNCDAT imm ',' addr
	{
		if $2.Type != D_CONST {
			yyerror("index for FUNCDATA must be integer constant")
		}
		if $4.Type != D_EXTERN && $4.Type != D_STATIC && $4.Type != D_OREG {
			yyerror("value for FUNCDATA must be symbol reference")
		}
 		outcode(int($1), &$2, NREG, &$4);
	}
/*
 * floating-point
 */
|	LTYPEI freg ',' freg
	{
		outcode(int($1), &$2, NREG, &$4);
	}
/*
 * FADDD
 */
|	LTYPEK frcon ',' freg
	{
		outcode(int($1), &$2, NREG, &$4);
	}
|	LTYPEK frcon ',' freg ',' freg
	{
		outcode(int($1), &$2, $4.Reg, &$6);
	}
/*
 * FCMP
 */
|	LTYPEL frcon ',' freg comma
	{
		outcode(int($1), &$2, $4.Reg, &nullgen);
	}
/*
 * FCCMP
 */
|	LTYPEF cond ',' freg ',' freg ',' imm comma
	{
		outgcode(int($1), &$2, $6.Reg, &$4, &$8);
	}
/*
 * FMULA
 */
|	LTYPE9 freg ',' freg ',' freg ',' freg comma
	{
		outgcode(int($1), &$2, $4.Reg, &$6, &$8);
	}
/*
 * FCSEL
 */
|	LFCSEL cond ',' freg ',' freg ',' freg
	{
		outgcode(int($1), &$2, $6.Reg, &$4, &$8);
	}
/*
 * SIMD
 */
|	LTYPEW vaddr ',' vaddr
	{
		outcode(int($1), &$2, NREG, &$4);
	}
|	LTYPEW vaddr ',' vaddr ',' vaddr
	{
		outcode(int($1), &$2, $4.Reg, &$6);
	}
/*
 * MOVP/MOVNP
 */
|	LTYPEJ addr ',' sreg ',' addr
	{
		outcode(int($1), &$2, $4, &$6);
	}
/*
 * MADD Rn,Rm,Ra,Rd
 */
|	LTYPEM reg ',' reg ',' sreg ',' reg
	{
		outgcode(int($1), &$2, $6, &$4, &$8);
	}
/*
 * SYS/SYSL
 */
|	LTYPEN sysarg
	{
		outcode(int($1), &$2, NREG, &nullgen);
	}
|	LTYPEN reg ',' sysarg
	{
		outcode(int($1), &$4, $2.Reg, &nullgen);
	}
|	LTYPEO sysarg ',' reg
	{
		outcode(int($1), &$2, NREG, &$4);
	}
/*
 * DMB, HINT
 */
|	LDMB imm
	{
		outcode(int($1), &$2, NREG, &nullgen);
	}
/*
 * STXR
 */
|	LSTXR reg ',' addr ',' reg
	{
		outtcode(int($1), &$2, &$4, &$6);
	}
/*
 * END
 */
|	LTYPEE comma
	{
		outcode(int($1), &nullgen, NREG, &nullgen);
	}

cond:
	LCOND
	{
		$$ = nullgen;
		$$.Type_ = D_COND;
		$$.Reg = $1;
	}

comma:
|	',' comma

sysarg:
	con ',' con ',' con ',' con
	{
		$$ = nullgen;
		$$.Type_ = D_CONST;
		$$.Offset = SYSARG4($1, $3, $5, $7);
	}
|	imm

rel:
	con '(' LPC ')'
	{
		$$ = nullgen;
		$$.Type_ = D_BRANCH;
		$$.Offset = $1 + int64(asm.PC);
	}
|	LNAME offset
	{
		$1 = asm.labellookup($1);
		$$ = nullgen;
		if(pass == 2 && $1.Type != LLAB)
			yyerror("undefined label: %s", $1.Labelname);
		$$.Type_ = D_BRANCH;
		$$.Offset = $1.Value + $2;
	}

ximm:	'$' con
	{
		$$ = nullgen;
		$$.Type_ = D_CONST;
		$$.Offset = $2;
	}
|	'$' oreg
	{
		$$ = $2;
		$$.Type_ = D_CONST;
	}
|	'$' '*' '$' oreg
	{
		$$ = $4;
		$$.Type_ = D_OCONST;
	}
|	'$' LSCONST
	{
		$$ = nullgen;
		$$.Type_ = D_SCONST;
		memmove($$.u.sval, $2, sizeof($$.u.sval));
	}
|	fcon

fcon:
	'$' LFCONST
	{
		$$ = nullgen;
		$$.Type_ = D_FCONST;
		$$.u.dval = $2;
	}
|	'$' '-' LFCONST
	{
		$$ = nullgen;
		$$.Type_ = D_FCONST;
		$$.u.dval = -$3;
	}

addr:
	reg
|	ximm
|	LFCR
	{
		$$ = nullgen;
		$$.Type_ = D_SPR;
		$$.Offset = $1;
	}
|	con
	{
		$$ = nullgen;
		$$.Type_ = D_OREG;
		$$.Offset = $1;
	}
|	oreg
|	freg
|	vreg
|	spr

nireg:
	'(' sreg ')'
	{
		$$ = nullgen;
		$$.Type_ = D_OREG;
		$$.Reg = $2;
		$$.Offset = 0;
	}
|	name
	{
		$$ = $1;
		if($1.Name != D_EXTERN && $1.Name != D_STATIC) {
		}
	}

oreg:
	name
|	name '(' sreg ')'
	{
		$$ = $1;
		$$.Type_ = D_OREG;
		$$.Reg = $3;
	}
|	ioreg

ioreg:
	'(' sreg ')'
	{
		$$ = nullgen;
		$$.Type_ = D_OREG;
		$$.Reg = $2;
		$$.Offset = 0;
	}
|	con '(' sreg ')'
	{
		$$ = nullgen;
		$$.Type_ = D_OREG;
		$$.Reg = $3;
		$$.Offset = $1;
	}
|	con '(' sreg ')' '!'
	{
		$$ = nullgen;
		$$.Type_ = D_XPRE;
		$$.Reg = $3;
		$$.Offset = $1;
	}
|	'(' sreg ')' con '!'
	{
		$$ = nullgen;
		$$.Type_ = D_XPOST;
		$$.Reg = $2;
		$$.Offset = $4;
	}
|	'(' sreg ')' '(' indexreg ')'
	{
		$$ = nullgen;
		$$.Type_ = D_ROFF;
		$$.Reg = $2;
		$$.scale = $5 & 0x1f;
		$$.Offset = $5;
	}
|	'(' sreg ')' '[' indexreg ']'
	{
		$$ = nullgen;
		$$.Type_ = D_ROFF;
		$$.Reg = $2;
		$$.scale = $5 & 0x1f;
		$$.Offset = $5 | (1<<16);
	}

imsr:
	imm
|	shift
|	extreg

imm:	'$' con
	{
		$$ = nullgen;
		$$.Type_ = D_CONST;
		$$.Offset = $2;
	}

reg:
	sreg
	{
		$$ = nullgen;
		$$.Type_ = D_REG;
		$$.Reg = $1;
	}
|	LSP
	{
		$$ = nullgen;
		$$.Type_ = D_SP;
		$$.Reg = REGSP;
	}

shift:
	sreg '<' '<' scon
	{
		$$ = nullgen;
		$$.Type_ = D_SHIFT;
		$$.Offset = ($1 << 16) | ($4 << 10) | (0 << 22);
	}
|	sreg '>' '>' scon
	{
		$$ = nullgen;
		$$.Type_ = D_SHIFT;
		$$.Offset = (($1&0x1F) << 16) | ($4 << 10) | (1 << 22);
	}
|	sreg '-' '>' scon
	{
		$$ = nullgen;
		$$.Type_ = D_SHIFT;
		$$.Offset = ($1 << 16) | ($4 << 10) | (2 << 22);
	}
|	sreg LAT '>' scon
	{
		$$ = nullgen;
		$$.Type_ = D_SHIFT;
		$$.Offset = ($1 << 16) | ($4 << 10) | (3 << 22);
	}

extreg:
	sreg
	{
		$$ = nullgen;
		$$.Type_ = D_REG;
		$$.Reg = $1;
	}
|	sreg LEXT
	{
		$$ = nullgen;
		$$.Type_ = D_EXTREG;
		$$.Reg = $1;
		$$.Offset = ($1 << 16) | ($2 << 13);
	}
|	sreg LEXT '<' '<' con
	{
		if($5 < 0 || $5 > 4)
			yyerror("shift value out of range");
		$$ = nullgen;
		$$.Type_ = D_EXTREG;
		$$.Reg = $1;
		$$.Offset = ($1 << 16) | ($2 << 13) | ($5 << 10);
	}

indexreg:
	sreg
	{
		$$ = (3 << 8) | $1;
	}
|	sreg LEXT
	{
		$$ = ($2 << 8) | $1;
	}

scon:
	con
	{
		if($$ < 0 || $$ >= 64)
			yyerror("shift value out of range");
		$$ = $1&0x3F;
	}

sreg:
	LREG
|	LR '(' expr ')'
	{
		if($3 < 0 || $3 >= NREG)
			print("register value out of range\n");
		$$ = $3;
	}

spreg:
	sreg
|	LSP
	{
		$$ = REGSP;
	}

spr:
	LSPREG
	{
		$$ = nullgen;
		$$.Type_ = D_SPR;
		$$.Offset = $1;
	}
|	LSPR '(' con ')'
	{
		$$ = nullgen;
		$$.Type_ = $1;
		$$.Offset = $3;
	}

frcon:
	freg
|	fcon

freg:
	LFREG
	{
		$$ = nullgen;
		$$.Type_ = D_FREG;
		$$.Reg = $1;
	}
|	LF '(' con ')'
	{
		$$ = nullgen;
		$$.Type_ = D_FREG;
		$$.Reg = $3;
	}

vaddr:
	oreg
|	vreg
|	vlane
|	vset
	{
		$$ = nullgen;
		$$.Type_ = D_VSET;
		$$.Offset = $1;
	}

vlane:
	vreg '[' con ']'
	{
		$$.Type_ = D_VLANE;
		$$.Offset = $3;
	}
|	vset '[' con ']'
	{
		$$.Type_ = D_VLANE;
		$$.Offset = $3;
	}

vset:
	'{' vreglist '}'
	{
		$$ = $2;
	}

vreglist:
	vreg
	{
		$$ = 1 << $1.Reg;
	}
|	vreg '-' vreg
	{
		int i;
		$$=0;
		for(i=$1.Reg; i<=$3.Reg; i++)
			$$ |= 1<<i;
		for(i=$3.Reg; i<=$1.Reg; i++)
			$$ |= 1<<i;
	}
|	vreg comma vreglist
	{
		$$ = (1<<$1.Reg) | $3;
	}

vreg:
	LVREG
	{
		$$ = nullgen;
		$$.Type_ = D_VREG;
		$$.Reg = $1;
		/* TO DO: slice */
	}
|	LV '(' con ')'
	{
		$$ = nullgen;
		$$.Type_ = D_VREG;
		$$.Reg = $3;
	}

name:
	con '(' pointer ')'
	{
		$$ = nullgen;
		$$.Type_ = D_OREG;
		$$.Name = $3;
		$$.Sym = nil;
		$$.Offset = $1;
	}
|	LNAME offset '(' pointer ')'
	{
		$$ = nullgen;
		$$.Type_ = D_OREG;
		$$.Name = $4;
		$$.Sym = linklookup(ctxt, $1->name, 0);
		$$.Offset = $2;
	}
|	LNAME '<' '>' offset '(' LSB ')'
	{
		$$ = nullgen;
		$$.Type_ = D_OREG;
		$$.Name = D_STATIC;
		$$.Sym = linklookup(ctxt, $1->name, 0);
		$$.Offset = $4;
	}

offset:
	{
		$$ = 0;
	}
|	'+' con
	{
		$$ = $2;
	}
|	'-' con
	{
		$$ = -$2;
	}

pointer:
	LSB
|	LSP
|	LFP

con:
	LCONST
|	LVAR
	{
		$$ = $1.Value;
	}
|	'-' con
	{
		$$ = -$2;
	}
|	'+' con
	{
		$$ = $2;
	}
|	'~' con
	{
		$$ = ~$2;
	}
|	'(' expr ')'
	{
		$$ = $2;
	}

expr:
	con
|	expr '+' expr
	{
		$$ = $1 + $3;
	}
|	expr '-' expr
	{
		$$ = $1 - $3;
	}
|	expr '*' expr
	{
		$$ = $1 * $3;
	}
|	expr '/' expr
	{
		$$ = $1 / $3;
	}
|	expr '%' expr
	{
		$$ = $1 % $3;
	}
|	expr '<' '<' expr
	{
		$$ = $1 << $4;
	}
|	expr '>' '>' expr
	{
		$$ = $1 >> $4;
	}
|	expr '&' expr
	{
		$$ = $1 & $3;
	}
|	expr '^' expr
	{
		$$ = $1 ^ $3;
	}
|	expr '|' expr
	{
		$$ = $1 | $3;
	}
