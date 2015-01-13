// Inferno utils/6l/l.h
// http://code.google.com/p/inferno-os/source/browse/utils/6l/l.h
//
//	Copyright © 1994-1999 Lucent Technologies Inc.  All rights reserved.
//	Portions Copyright © 1995-1997 C H Forsyth (forsyth@terzarima.net)
//	Portions Copyright © 1997-1999 Vita Nuova Limited
//	Portions Copyright © 2000-2007 Vita Nuova Holdings Limited (www.vitanuova.com)
//	Portions Copyright © 2004,2006 Bruce Ellis
//	Portions Copyright © 2005-2007 C H Forsyth (forsyth@terzarima.net)
//	Revisions Copyright © 2000-2007 Lucent Technologies Inc. and others
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

#include	<u.h>
#include	<libc.h>
#include	<bio.h>
#include	<link.h>
#include	"6.out.h"

#ifndef	EXTERN
#define	EXTERN	extern
#endif

enum
{
	thechar = '6',
	MaxAlign = 32,	// max data alignment
	
	// Loop alignment constants:
	// want to align loop entry to LoopAlign-byte boundary,
	// and willing to insert at most MaxLoopPad bytes of NOP to do so.
	// We define a loop entry as the target of a backward jump.
	//
	// gcc uses MaxLoopPad = 10 for its 'generic x86-64' config,
	// and it aligns all jump targets, not just backward jump targets.
	//
	// As of 6/1/2012, the effect of setting MaxLoopPad = 10 here
	// is very slight but negative, so the alignment is disabled by
	// setting MaxLoopPad = 0. The code is here for reference and
	// for future experiments.
	// 
	LoopAlign = 16,
	MaxLoopPad = 0,

	FuncAlign = 16
};

EXTERN	int	PtrSize;
EXTERN	int	IntSize;
EXTERN	int	RegSize;

#define	P		((Prog*)0)
#define	S		((LSym*)0)
enum
{
	MINLC		= 1,
};

#pragma	varargck	type	"I"	uchar*

EXTERN	LSym*	datap;
EXTERN	int	debug[128];
EXTERN	char	literal[32];
EXTERN	int32	lcsize;
EXTERN	char*	rpath;
EXTERN	int32	spsize;
EXTERN	LSym*	symlist;
EXTERN	int32	symsize;

int	Iconv(Fmt *fp);
void	adddynlib(char *lib);
void	adddynrel(LSym *s, Reloc *r);
void	adddynrela(LSym *rela, LSym *s, Reloc *r);
void	adddynsym(Link *ctxt, LSym *s);
int	archreloc(Reloc *r, LSym *s, vlong *val);
vlong	archrelocvariant(Reloc *r, LSym *s, vlong t);
void	asmb(void);
int	elfreloc1(Reloc *r, vlong sectoff);
void	elfsetupplt(void);
void	listinit(void);
int	machoreloc1(Reloc *r, vlong sectoff);
vlong	rnd(vlong v, vlong r);

/* Native is little-endian */
#define	LPUT(a)	lputl(a)
#define	WPUT(a)	wputl(a)
#define	VPUT(a)	vputl(a)

/* Used by ../ld/dwarf.c */
enum
{
	DWARFREGSP = 7
};
