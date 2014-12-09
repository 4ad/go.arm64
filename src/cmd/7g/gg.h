// Copyright 2014 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef	EXTERN
#define	EXTERN	extern
#endif

#include "../gc/go.h"
#include "../9l/9.out.h"

// TODO(minux): Remove when no longer used.
#define noimpl sysfatal("%s not implemented (%s:%d).", __func__, __FILE__, __LINE__)

#define TEXTFLAG reg

EXTERN	int32	dynloc;
EXTERN	uchar	reg[NREG+NFREG];
EXTERN	int32	pcloc;		// instruction counter
EXTERN	Strlit	emptystring;
EXTERN	Prog	zprog;
EXTERN	Node*	newproc;
EXTERN	Node*	deferproc;
EXTERN	Node*	deferreturn;
EXTERN	Node*	panicindex;
EXTERN	Node*	panicslice;
EXTERN	Node*	panicdiv;
EXTERN	Node*	throwreturn;
extern	vlong	unmappedzero;

/*
 * ggen.c
 */
void	compile(Node*);
void	gen(Node*);
Node*	lookdot(Node*, Node*, int);
void	cgen_as(Node*, Node*);
void	cgen_callmeth(Node*, int);
void	cgen_callinter(Node*, Node*, int);
void	cgen_proc(Node*, int);
void	cgen_callret(Node*, Node*);
void	cgen_div(int, Node*, Node*, Node*);
void	cgen_hmul(Node*, Node*, Node*);
void	cgen_shift(int, int, Node*, Node*, Node*);
void	cgen_dcl(Node*);
int	needconvert(Type*, Type*);
void	genconv(Type*, Type*);
void	allocparams(void);
void	checklabels(void);
void	ginscall(Node*, int);
int	gen_as_init(Node*);

/*
 * cgen.c
 */
void	agen(Node*, Node*);
void	agenr(Node*, Node*, Node*);
void	cgenr(Node*, Node*, Node*);
void	igen(Node*, Node*, Node*);
vlong	fieldoffset(Type*, Node*);
void	sgen(Node*, Node*, int64);
void	gmove(Node*, Node*);
Prog*	gins(int, Node*, Node*);
void	naddr(Node*, Addr*, int);
void	cgen_aret(Node*, Node*);
int	componentgen(Node*, Node*);

/*
 * gsubr.c
 */
void	clearp(Prog*);
Prog*	gbranch(int, Type*, int);
Prog*	prog(int);
void	gconv(int, int);
int	conv2pt(Type*);
vlong	convvtox(vlong, int);
void	fnparam(Type*, int, int);
Prog*	gop(int, Node*, Node*, Node*);
int	optoas(int, Type*);
void	ginit(void);
void	gclean(void);
void	regalloc(Node*, Type*, Node*);
void	regfree(Node*);
Node*	nodarg(Type*, int);
void	nodreg(Node*, Type*, int);
void	nodindreg(Node*, Type*, int);
void	ginscon(int, vlong, Node*);
void	ginscon2(int, Node*, vlong);
void	buildtxt(void);
Plist*	newplist(void);
int	isfat(Type*);
void	sudoclean(void);
int	sudoaddable(int, Node*, Addr*);
void	afunclit(Addr*, Node*);
void	nodfconst(Node*, Type*, Mpflt*);
void	gtrack(Sym*);
void	fixlargeoffset(Node *n);

/*
 * cplx.c
 */
int	complexop(Node*, Node*);
void	complexmove(Node*, Node*);
void	complexgen(Node*, Node*);

/*
 * gobj.c
 */
void	datastring(char*, int, Addr*);
void	datagostring(Strlit*, Addr*);

/*
 * list.c
 */
void	listinit(void);

void	zaddr(Biobuf*, Addr*, int, int);
