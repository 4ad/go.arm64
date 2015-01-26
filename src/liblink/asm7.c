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

#include <u.h>
#include <libc.h>
#include <bio.h>
#include <link.h>
#include "../cmd/7l/7.out.h"

enum
{
	FuncAlign = 16
};

typedef	struct	Mask	Mask;
typedef	struct	Optab	Optab;
typedef	struct	Oprang	Oprang;
typedef	uchar	Opcross[32][2][32];

struct	Optab
{
	ushort	as;
	uchar	a1;
	uchar	a2;
	uchar	a3;
	char	type;
	char	size;
	char	param;
	char	flag;
};
struct	Oprang
{
	Optab*	start;
	Optab*	stop;
};
struct	Mask
{
	uchar	s;
	uchar	e;
	uchar	r;
	uvlong	v;
};

static Oprang	oprange[ALAST];
static Opcross	opcross[8];
static uchar	repop[ALAST];
static	uchar	xcmp[C_NCLASS][C_NCLASS];

static void checkpool(Link*, Prog*, int);
static void flushpool(Link*, Prog*, int);
static void addpool(Link*, Prog*, Addr*);
static uint32 regoff(Link*, Addr*);
static int ispcdisp(int32);
static int isaddcon(vlong);
static int isbitcon(uvlong);
static int constclass(vlong);
static vlong offsetshift(Link*, vlong, int);
static int movcon(vlong);
static int aclass(Link*, Addr*);
static Optab *oplook(Link*, Prog*);
static int cmp(int, int);
static int ocmp(const void*, const void*);
void buildop(Link*);
int chipfloat7(Link*, float64);
void asmout(Link*, Prog*, Optab*, uint32 *);
static uint32 oprrr(Link*, int);
static uint32 opirr(Link*, int);
static uint32 opbit(Link*, int);
static uint32 opxrrr(Link*, int);
static uint32 opimm(Link*, int);
static vlong brdist(Link*, Prog*, int, int, int);
static uint32 opbra(Link*, int);
static uint32 opbrr(Link*, int);
static uint32 op0(Link*, int);
static uint32 opload(Link*, int);
static uint32 opstore(Link*, int);
static uint32 olsr12u(Link*, int32, int32, int, int);
static uint32 opldr12(Link*, int);
static uint32 opstr12(Link*, int);
static uint32 olsr9s(Link*, int32, int32, int, int);
static uint32 opldr9(Link*, int);
static uint32 opstr9(Link *, int);
static uint32 opldrpp(Link*, int);
static uint32 olsxrr(Link*, int, int, int, int);
static uint32 oaddi(int32, int32, int, int);
static uint32 omovlit(Link*, int, Prog*, Addr*, int);
static uint32 opbfm(Link*, int, int, int, int, int);
static uint32 opextr(Link*, int, int32, int, int, int);
static int movesize(int);
static void prasm(Prog*);
static Mask* findmask(uvlong v);

enum {
	S32 = 0U<<31,
	S64 = 1U<<31,
	Sbit = 1U<<29,
	LSL0_32 = 2<<13,
	LSL0_64 = 3<<13,
};

static uint32
OPDP2(uint32 x)
{
	return (0<<30 | 0 << 29 | 0xd6<<21 | (x)<<10);
}

static uint32
OPDP3(uint32 sf, uint32 op54, uint32 op31, uint32 o0)
{
	return ((sf)<<31 | (op54)<<29 | 0x1B<<24 | (op31)<<21 | (o0)<<15);
}

static uint32
OPBcc(uint32 x)
{
	return (0x2A<<25 | 0<<24 | 0<<4 | ((x)&15));
}

static uint32
OPBLR(uint32 x)
{
	/* x=0, JMP; 1, CALL; 2, RET */
	return (0x6B<<25 | 0<<23 | (x)<<21 | 0x1F<<16 | 0<<10);
}

static uint32
SYSOP(uint32 l, uint32 op0, uint32 op1, uint32 crn, uint32 crm, uint32 op2 , uint32 rt)
{
	return (0x354<<22 | (l)<<21 | (op0)<<19 | (op1)<<16 | (crn)<<12 | (crm)<<8 | (op2)<<5 | (rt));
}

static uint32
SYSHINT(uint32 x)
{
	return SYSOP(0,0,3,2,0,(x),0x1F);
}

static uint32
LDSTR12U(uint32 sz, uint32 v, uint32 opc)
{
	return ((sz)<<30 | 7<<27 | (v)<<26 | 1<<24 | (opc)<<22);
}

static uint32
LDSTR9S(uint32 sz, uint32 v, uint32 opc)
{
	return ((sz)<<30 | 7<<27 | (v)<<26 | 0<<24 | (opc)<<22);
}

static uint32
LD2STR(uint32 o)
{
	return ((o) & ~(3<<22));
}

static uint32
LDSTX(uint32 sz, uint32 o2, uint32 l, uint32 o1, uint32 o0)
{
	return ((sz)<<30 | 0x8<<24 | (o2)<<23 | (l)<<22 | (o1)<<21 | (o0)<<15);
}

static uint32
FPCMP(uint32 m, uint32 s, uint32 type, uint32 op, uint32 op2)
{
	return ((m)<<31 | (s)<<29 | 0x1E<<24 | (type)<<22 | 1<<21 | (op)<<14 | 8<<10 | (op2));
}

static uint32
FPCCMP(uint32 m, uint32 s, uint32 type, uint32 op)
{
	return ((m)<<31 | (s)<<29 | 0x1E<<24 | (type)<<22 | 1<<21 | 1<<10 | (op)<<4);
}

static uint32
FPOP1S(uint32 m, uint32 s, uint32 type, uint32 op)
{
	return ((m)<<31 | (s)<<29 | 0x1E<<24 | (type)<<22 | 1<<21 | (op)<<15 | 0x10<<10);
}

static uint32
FPOP2S(uint32 m, uint32 s, uint32 type, uint32 op)
{
	return ((m)<<31 | (s)<<29 | 0x1E<<24 | (type)<<22 | 1<<21 | (op)<<12 | 2<<10);
}

static uint32
FPCVTI(uint32 sf, uint32 s, uint32 type, uint32 rmode, uint32 op)
{
	return ((sf)<<31 | (s)<<29 | 0x1E<<24 | (type)<<22 | 1<<21 | (rmode)<<19 | (op)<<16 | 0<<10);
}

static uint32
ADR(uint32 p, uint32 o, uint32 rt)
{
	return ((p)<<31 | ((o)&3)<<29 | (0x10<<24) | (((o>>2)&0x7FFFF)<<5) | (rt));
}

static uint32
OPBIT(uint32 x)
{
	return (1<<30 | 0<<29 | 0xD6<<21 | 0<<16 | (x)<<10);
}

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

enum
{
	LFROM	= 1<<0,
	LTO	= 1<<1,
	LPOOL	= 1<<2,
};

static Optab optab[] = {
        /* struct Optab:
          OPCODE,       from, prog->reg, to,             type,size,param,flag */
	{ ATEXT,	C_LEXT,	C_NONE,	C_VCON, 	 0, 0, 0 },
	{ ATEXT,	C_LEXT,	C_REG,	C_VCON, 	 0, 0, 0 },
	{ ATEXT,	C_ADDR,	C_NONE,	C_VCON, 	 0, 0, 0 },
	{ ATEXT,	C_ADDR,	C_REG,	C_VCON, 	 0, 0, 0 },

	/* arithmetic operations */
	{ AADD,		C_REG,	C_REG,	C_REG,		 1, 4, 0 },
	{ AADD,		C_REG,	C_NONE,	C_REG,		 1, 4, 0 },
	{ AADC,		C_REG,	C_REG,	C_REG,		 1, 4, 0 },
	{ AADC,		C_REG,	C_NONE,	C_REG,		 1, 4, 0 },
	{ ANEG,		C_REG,	C_NONE,	C_REG,		25, 4, 0 },
	{ ANGC,		C_REG,	C_NONE,	C_REG,		17, 4, 0 },
	{ ACMP,		C_REG,	C_RSP,	C_NONE,		 1, 4, 0 },

	{ AADD,		C_ADDCON,	C_RSP,	C_RSP,		 2, 4, 0 },
	{ AADD,		C_ADDCON,	C_NONE,	C_RSP,		 2, 4, 0 },
	{ ACMP,		C_ADDCON,	C_RSP,	C_NONE,		 2, 4, 0 },
	{ AADD,		C_MBCON,	C_RSP,	C_RSP,		 2, 4, 0 },
	{ AADD,		C_MBCON,	C_NONE,	C_RSP,		 2, 4, 0 },
	{ ACMP,		C_MBCON,	C_RSP,	C_NONE,		 2, 4, 0 },

	{ AADD,		C_VCON,	C_REG,	C_REG,		13, 8, 0,	LFROM },
	{ AADD,		C_VCON,	C_NONE,	C_REG,		13, 8, 0,	LFROM },
	{ ACMP,		C_VCON,	C_REG,	C_NONE,		13, 8, 0,	LFROM },
	{ AADD,		C_ADDR,	C_REG,	C_REG,		13, 8, 0,	LFROM },
	{ AADD,		C_ADDR,	C_NONE,	C_REG,		13, 8, 0,	LFROM },
	{ ACMP,		C_ADDR,	C_REG,	C_NONE,		13, 8, 0,	LFROM },

	{ AADD,		C_SHIFT,C_REG,	C_REG,		 3, 4, 0 },
	{ AADD,		C_SHIFT,C_NONE,	C_REG,		 3, 4, 0 },
	{ AMVN,		C_SHIFT,C_NONE,	C_REG,		 3, 4, 0 },
	{ ACMP,		C_SHIFT,C_REG,	C_NONE,		 3, 4, 0 },
	{ ANEG,		C_SHIFT,C_NONE,	C_REG,		26, 4, 0 },

	{ AADD,		C_REG,	C_RSP,	C_RSP,		27, 4, 0 },
	{ AADD,		C_REG,	C_NONE,	C_RSP,		27, 4, 0 },
	{ AADD,		C_EXTREG,C_RSP,	C_RSP,		27, 4, 0 },
	{ AADD,		C_EXTREG,C_NONE,	C_RSP,		27, 4, 0 },
	{ AMVN,		C_EXTREG,C_NONE,	C_RSP,		27, 4, 0 },
	{ ACMP,		C_EXTREG,C_RSP,	C_NONE,		27, 4, 0 },

	{ AADD,		C_REG,	C_REG,	C_REG,		 1, 4, 0 },
	{ AADD,		C_REG,	C_NONE,	C_REG,		 1, 4, 0 },

	/* logical operations */
	{ AAND,		C_REG,	C_REG,	C_REG,		 1, 4, 0 },
	{ AAND,		C_REG,	C_NONE,	C_REG,		 1, 4, 0 },
	{ ABIC,		C_REG,	C_REG,	C_REG,		 1, 4, 0 },
	{ ABIC,		C_REG,	C_NONE,	C_REG,		 1, 4, 0 },

	{ AAND,		C_BITCON,	C_REG,	C_REG,		53, 4, 0 },
	{ AAND,		C_BITCON,	C_NONE,	C_REG,		53, 4, 0 },
	{ ABIC,		C_BITCON,	C_REG,	C_REG,		53, 4, 0 },
	{ ABIC,		C_BITCON,	C_NONE,	C_REG,		53, 4, 0 },

	{ AAND,		C_VCON,	C_REG,	C_REG,		28, 8, 0,	LFROM },
	{ AAND,		C_VCON,	C_NONE,	C_REG,		28, 8, 0,	LFROM },
	{ ABIC,		C_VCON,	C_REG,	C_REG,		28, 8, 0,	LFROM },
	{ ABIC,		C_VCON,	C_NONE,	C_REG,		28, 8, 0,	LFROM },
	{ AAND,		C_ADDR,	C_REG,	C_REG,		28, 8, 0,	LFROM },
	{ AAND,		C_ADDR,	C_NONE,	C_REG,		28, 8, 0,	LFROM },
	{ ABIC,		C_ADDR,	C_REG,	C_REG,		28, 8, 0,	LFROM },
	{ ABIC,		C_ADDR,	C_NONE,	C_REG,		28, 8, 0,	LFROM },

	{ AAND,		C_SHIFT,C_REG,	C_REG,		 3, 4, 0 },
	{ AAND,		C_SHIFT,C_NONE,	C_REG,		 3, 4, 0 },
	{ ABIC,		C_SHIFT,C_REG,	C_REG,		 3, 4, 0 },
	{ ABIC,		C_SHIFT,C_NONE,	C_REG,		 3, 4, 0 },

	{ AMOV,		C_RSP,	C_NONE,	C_RSP,		24, 4, 0 },
	{ AMVN,		C_REG,	C_NONE,	C_REG,		24, 4, 0 },
	{ AMOVB,		C_REG,	C_NONE,	C_REG,		45, 4, 0 },
	{ AMOVBU,	C_REG,	C_NONE,	C_REG,		45, 4, 0 },
	{ AMOVH,		C_REG,	C_NONE,	C_REG,		45, 4, 0 },	/* also MOVHU */
	{ AMOVW,		C_REG,	C_NONE,	C_REG,		45, 4, 0 },	/* also MOVWU */
	/* TO DO: MVN C_SHIFT */

	/* MOVs that become MOVK/MOVN/MOVZ/ADD/SUB/OR */
	{ AMOVW,		C_MOVCON,	C_NONE,	C_REG,		32, 4, 0 },
	{ AMOV,		C_MOVCON,	C_NONE,	C_REG,		32, 4, 0 },
//	{ AMOVW,		C_ADDCON,	C_NONE,	C_REG,		2, 4, 0 },
//	{ AMOV,		C_ADDCON,	C_NONE,	C_REG,		2, 4, 0 },
	{ AMOVW,		C_BITCON,	C_NONE,	C_REG,		53, 4, 0 },
	{ AMOV,		C_BITCON,	C_NONE,	C_REG,		53, 4, 0 },

	{ AMOVK,		C_VCON,	C_NONE,	C_REG,			33, 4, 0 },

	{ AMOV,	C_AECON,C_NONE,	C_REG,		 4, 4, REGSB },
	{ AMOV,	C_AACON,C_NONE,	C_REG,		 4, 4, REGSP },

	{ ASDIV,	C_REG,	C_NONE,	C_REG,		1, 4, 0 },
	{ ASDIV,	C_REG,	C_REG,	C_REG,		1, 4, 0 },

	{ AB,		C_NONE,	C_NONE,	C_SBRA,		 5, 4, 0 },
	{ ABL,	C_NONE,	C_NONE,	C_SBRA,		 5, 4, 0 },

	{ AB,		C_NONE,	C_NONE,	C_ZOREG,	 	6, 4, 0 },
	{ ABL,	C_NONE,	C_NONE,	C_REG,	 	6, 4, 0 },
	{ ABL,	C_NONE,	C_NONE,	C_ZOREG,	 	6, 4, 0 },
	{ ARET,	C_NONE,	C_NONE,	C_REG,		6, 4, 0 },
	{ ARET,	C_NONE, C_NONE, C_ZOREG,		6, 4, 0 },

	{ AADRP,	C_SBRA,	C_NONE,	C_REG,		60, 4, 0 },
	{ AADR,	C_SBRA,	C_NONE,	C_REG,		61, 4, 0 },

	{ ABFM,	C_VCON, C_REG, C_REG,		42, 4, 0 },
	{ ABFI,	C_VCON, C_REG, C_REG,		43, 4, 0 },

	{ AEXTR,	C_VCON, C_REG, C_REG,		44, 4, 0 },
	{ ASXTB,	C_REG,	C_NONE,	C_REG,	45, 4, 0 },
	{ ACLS,	C_REG,	C_NONE,	C_REG,	46, 4, 0 },

	{ ABEQ,	C_NONE,	C_NONE,	C_SBRA,		 7, 4, 0 },

	{ ALSL,		C_VCON,	C_REG,	C_REG,		 8, 4, 0 },
	{ ALSL,		C_VCON,	C_NONE,	C_REG,		 8, 4, 0 },

	{ ALSL,		C_REG,	C_NONE,	C_REG,		 9, 4, 0 },
	{ ALSL,		C_REG,	C_REG,	C_REG,		 9, 4, 0 },

	{ ASVC,		C_NONE,	C_NONE,	C_VCON,		10, 4, 0 },
	{ ASVC,		C_NONE,	C_NONE,	C_NONE,		10, 4, 0 },

	{ ADWORD,	C_NONE,	C_NONE,	C_VCON,		11, 8, 0 },
	{ ADWORD,	C_NONE,	C_NONE,	C_LEXT,		11, 8, 0 },
	{ ADWORD,	C_NONE,	C_NONE,	C_ADDR,		11, 8, 0 },
	{ ADWORD,	C_NONE,	C_NONE,	C_LACON,		11, 8, 0 },	

	{ AWORD,	C_NONE,	C_NONE,	C_LCON,		14, 4, 0 },
	{ AWORD,	C_NONE,	C_NONE,	C_LEXT,		14, 4, 0 },
	{ AWORD,	C_NONE,	C_NONE,	C_ADDR,		14, 4, 0 },

	{ AMOVW,	C_VCON,	C_NONE,	C_REG,		12, 4, 0,	LFROM },
	{ AMOV,	C_VCON,	C_NONE,	C_REG,		12, 4, 0,	LFROM },
	{ AMOV,	C_ADDR,	C_NONE,	C_REG,		12, 4, 0,	LFROM },

	{ AMOVB,	C_REG,	C_NONE,	C_ADDR,		64, 8, 0,	LTO },
	{ AMOVBU,	C_REG,	C_NONE,	C_ADDR,		64, 8, 0,	LTO },
	{ AMOVH,	C_REG,	C_NONE,	C_ADDR,		64, 8, 0,	LTO },
	{ AMOVW,	C_REG,	C_NONE,	C_ADDR,		64, 8, 0,	LTO },
	{ AMOV,	C_REG,	C_NONE,	C_ADDR,		64, 8, 0,	LTO },
	{ AMOVB,	C_ADDR,	C_NONE,	C_REG,		65, 8, 0,	LFROM },
	{ AMOVBU,	C_ADDR,	C_NONE,	C_REG,		65, 8, 0,	LFROM },
	{ AMOVH,	C_ADDR,	C_NONE,	C_REG,		65, 8, 0,	LFROM },
	{ AMOVW,	C_ADDR,	C_NONE,	C_REG,		65, 8, 0,	LFROM },
	{ AMOV,	C_ADDR,	C_NONE,	C_REG,		65, 8, 0,	LFROM },

	{ AMUL,		C_REG,	C_REG,	C_REG,		15, 4, 0 },
	{ AMUL,		C_REG,	C_NONE,	C_REG,		15, 4, 0 },
	{ AMADD,		C_REG,	C_REG,	C_REG,		15, 4, 0 },

	{ AREM,		C_REG,	C_REG,	C_REG,		16, 8, 0 },
	{ AREM,		C_REG,	C_NONE,	C_REG,		16, 8, 0 },

	{ ACSEL,		C_COND,	C_REG,	C_REG,		18, 4, 0 },	/* from3 optional */
	{ ACSET,		C_COND,	C_NONE,	C_REG,		18, 4, 0 },

	{ ACCMN,		C_COND,	C_REG,	C_VCON,		19, 4, 0 },	/* from3 either C_REG or C_VCON */

	/* scaled 12-bit unsigned displacement store */

	{ AMOVB,	C_REG,	C_NONE,	C_SEXT1,		20, 4, REGSB },  // 
	{ AMOVB,	C_REG,	C_NONE,	C_UAUTO4K,	20, 4, REGSP },  // 
	{ AMOVB,	C_REG,	C_NONE,	C_UOREG4K,		20, 4, 0 },  // 
	{ AMOVBU,	C_REG,	C_NONE,	C_SEXT1,		20, 4, REGSB },  // 
	{ AMOVBU,	C_REG,	C_NONE,	C_UAUTO4K,	20, 4, REGSP },  // 
	{ AMOVBU,	C_REG,	C_NONE,	C_UOREG4K,		20, 4, 0 },  // 

	{ AMOVH,	C_REG,	C_NONE,	C_SEXT2,		20, 4, REGSB },  //
	{ AMOVH,	C_REG,	C_NONE,	C_UAUTO8K,	20,	4, REGSP },	//
	{ AMOVH,	C_REG,	C_NONE,	C_ZOREG,		20, 4, 0 },  // 
	{ AMOVH,	C_REG,	C_NONE,	C_UOREG8K,	20,	4, 0 },	//

	{ AMOVW,	C_REG,	C_NONE,	C_SEXT4,		20, 4, REGSB },  //
	{ AMOVW,	C_REG,	C_NONE,	C_UAUTO16K,	20,	4, REGSP },	//
	{ AMOVW,	C_REG,	C_NONE,	C_ZOREG,		20, 4, 0 },  // 
	{ AMOVW,	C_REG,	C_NONE,	C_UOREG16K,	20,	4, 0 },	//

	/* unscaled 9-bit signed displacement store */
	{ AMOVB,	C_REG,	C_NONE,	C_NSAUTO,	20, 4, REGSP },  // 
	{ AMOVB,	C_REG,	C_NONE,	C_NSOREG,	20, 4, 0 },  // 
	{ AMOVBU,	C_REG,	C_NONE,	C_NSAUTO,	20, 4, REGSP },  // 
	{ AMOVBU,	C_REG,	C_NONE,	C_NSOREG,	20, 4, 0 },  // 

	{ AMOVH,	C_REG,	C_NONE,	C_NSAUTO,	20,	4, REGSP },	//
	{ AMOVH,	C_REG,	C_NONE,	C_NSOREG,	20,	4, 0 },	//
	{ AMOVW,	C_REG,	C_NONE,	C_NSAUTO,	20,	4, REGSP },	//
	{ AMOVW,	C_REG,	C_NONE,	C_NSOREG,	20,	4, 0 },	//

	{ AMOV,	C_REG,	C_NONE,	C_SEXT8,		20, 4, REGSB },
	{ AMOV,	C_REG,	C_NONE,	C_UAUTO32K,	20,	4, REGSP },
	{ AMOV,	C_REG,	C_NONE,	C_ZOREG,		20, 4, 0 },
	{ AMOV,	C_REG,	C_NONE,	C_UOREG32K,	20,	4, 0 },

	{ AMOV,	C_REG,	C_NONE,	C_NSOREG,	20,	4, 0 },	//
	{ AMOV,	C_REG,	C_NONE,	C_NSAUTO,	20,	4, REGSP },	//

	/* short displacement load */

	{ AMOVB,	C_SEXT1,	C_NONE,	C_REG,		21, 4, REGSB },  // 
	{ AMOVB,	C_UAUTO4K,C_NONE,	C_REG,		21, 4, REGSP },  // 
	{ AMOVB,	C_NSAUTO,C_NONE,	C_REG,	21, 4, REGSP },  // 
	{ AMOVB,	C_ZOREG,C_NONE,	C_REG,		21, 4, 0 },  // 
	{ AMOVB,	C_UOREG4K,C_NONE,	C_REG,		21, 4, REGSP },  // 
	{ AMOVB,	C_NSOREG,C_NONE,	C_REG,	21, 4, REGSP },  // 

	{ AMOVBU,	C_SEXT1,	C_NONE,	C_REG,		21, 4, REGSB },  // 
	{ AMOVBU,	C_UAUTO4K,C_NONE,	C_REG,		21, 4, REGSP },  // 
	{ AMOVBU,	C_NSAUTO,C_NONE,	C_REG,	21, 4, REGSP },  // 
	{ AMOVBU,	C_ZOREG,C_NONE,	C_REG,		21, 4, 0 },  // 
	{ AMOVBU,	C_UOREG4K,C_NONE,	C_REG,		21, 4, REGSP },  // 
	{ AMOVBU,	C_NSOREG,C_NONE,	C_REG,	21, 4, REGSP },  // 

	{ AMOVH,	C_SEXT2,	C_NONE,	C_REG,		21, 4, REGSB },  // 
	{ AMOVH,	C_UAUTO8K,C_NONE,	C_REG,		21, 4, REGSP },  // 
	{ AMOVH,	C_NSAUTO,C_NONE,	C_REG,	21, 4, REGSP },  // 
	{ AMOVH,	C_ZOREG,C_NONE,	C_REG,		21, 4, 0 },  // 
	{ AMOVH,	C_UOREG8K,C_NONE,	C_REG,		21, 4, REGSP },  // 
	{ AMOVH,	C_NSOREG,C_NONE,	C_REG,	21, 4, REGSP },  // 

	{ AMOVW,	C_SEXT4,	C_NONE,	C_REG,		21, 4, REGSB },  // 
	{ AMOVW,	C_UAUTO16K,C_NONE,	C_REG,		21, 4, REGSP },  // 
	{ AMOVW,	C_NSAUTO,C_NONE,	C_REG,	21, 4, REGSP },  // 
	{ AMOVW,	C_ZOREG,C_NONE,	C_REG,		21, 4, 0 },  // 
	{ AMOVW,	C_UOREG16K,C_NONE,	C_REG,		21, 4, REGSP },  // 
	{ AMOVW,	C_NSOREG,C_NONE,	C_REG,	21, 4, REGSP },  // 

	{ AMOV,	C_SEXT8,	C_NONE,	C_REG,		21, 4, REGSB },
	{ AMOV,	C_UAUTO32K,C_NONE,	C_REG,		21, 4, REGSP },
	{ AMOV,	C_NSAUTO,C_NONE,	C_REG,	21, 4, REGSP },
	{ AMOV,	C_ZOREG,C_NONE,	C_REG,		21, 4, 0 },
	{ AMOV,	C_UOREG32K,C_NONE,	C_REG,		21, 4, REGSP },
	{ AMOV,	C_NSOREG,C_NONE,	C_REG,	21, 4, REGSP },

	/* long displacement store */
	{ AMOVB,	C_REG,	C_NONE,	C_LEXT,		30, 8, REGSB },  // 
	{ AMOVB,	C_REG,	C_NONE,	C_LAUTO,	30, 8, REGSP },  // 
	{ AMOVB,	C_REG,	C_NONE,	C_LOREG,	30, 8, 0 },  // 
	{ AMOVBU,	C_REG,	C_NONE,	C_LEXT,		30, 8, REGSB },  // 
	{ AMOVBU,	C_REG,	C_NONE,	C_LAUTO,	30, 8, REGSP },  // 
	{ AMOVBU,	C_REG,	C_NONE,	C_LOREG,	30, 8, 0 },  // 
	{ AMOVH,	C_REG,	C_NONE,	C_LEXT,		30, 8, REGSB },  // 
	{ AMOVH,	C_REG,	C_NONE,	C_LAUTO,	30, 8, REGSP },  // 
	{ AMOVH,	C_REG,	C_NONE,	C_LOREG,	30, 8, 0 },  // 
	{ AMOVW,	C_REG,	C_NONE,	C_LEXT,		30, 8, REGSB },  // 
	{ AMOVW,	C_REG,	C_NONE,	C_LAUTO,	30, 8, REGSP },  // 
	{ AMOVW,	C_REG,	C_NONE,	C_LOREG,	30, 8, 0 },  // 
	{ AMOV,	C_REG,	C_NONE,	C_LEXT,		30, 8, REGSB },  // 
	{ AMOV,	C_REG,	C_NONE,	C_LAUTO,	30, 8, REGSP },  // 
	{ AMOV,	C_REG,	C_NONE,	C_LOREG,	30, 8, 0 },  // 

	/* long displacement load */
	{ AMOVB,		C_LEXT,	C_NONE,	C_REG,		31, 8, REGSB },  // 
	{ AMOVB,		C_LAUTO,C_NONE,	C_REG,		31, 8, REGSP },  // 
	{ AMOVB,		C_LOREG,C_NONE,	C_REG,		31, 8, 0 },  // 
	{ AMOVB,		C_LOREG,C_NONE,	C_REG,		31, 8, 0 },	//
	{ AMOVBU,		C_LEXT,	C_NONE,	C_REG,		31, 8, REGSB },  // 
	{ AMOVBU,		C_LAUTO,C_NONE,	C_REG,		31, 8, REGSP },  // 
	{ AMOVBU,		C_LOREG,C_NONE,	C_REG,		31, 8, 0 },  // 
	{ AMOVBU,		C_LOREG,C_NONE,	C_REG,		31, 8, 0 },	//
	{ AMOVH,		C_LEXT,	C_NONE,	C_REG,		31, 8, REGSB },  // 
	{ AMOVH,		C_LAUTO,C_NONE,	C_REG,		31, 8, REGSP },  // 
	{ AMOVH,		C_LOREG,C_NONE,	C_REG,		31, 8, 0 },  // 
	{ AMOVH,		C_LOREG,C_NONE,	C_REG,		31, 8, 0 },	//
	{ AMOVW,		C_LEXT,	C_NONE,	C_REG,		31, 8, REGSB },  // 
	{ AMOVW,		C_LAUTO,C_NONE,	C_REG,		31, 8, REGSP },  // 
	{ AMOVW,		C_LOREG,C_NONE,	C_REG,		31, 8, 0 },  // 
	{ AMOVW,		C_LOREG,C_NONE,	C_REG,		31, 8, 0 },	//
	{ AMOV,		C_LEXT,	C_NONE,	C_REG,		31, 8, REGSB },  // 
	{ AMOV,		C_LAUTO,C_NONE,	C_REG,		31, 8, REGSP },  // 
	{ AMOV,		C_LOREG,C_NONE,	C_REG,		31, 8, 0 },  // 
	{ AMOV,		C_LOREG,C_NONE,	C_REG,		31, 8, 0 },	//

	/* load long effective stack address (load int32 offset and add) */
	{ AMOV,		C_LACON,C_NONE,	C_REG,		34, 8, REGSP,	LFROM },  //

	/* pre/post-indexed load (unscaled, signed 9-bit offset) */
	{ AMOV,		C_XPOST,	C_NONE,	C_REG,		22, 4, 0 },
	{ AMOVW, 	C_XPOST,	C_NONE,	C_REG,		22, 4, 0 },
	{ AMOVH,		C_XPOST,	C_NONE,	C_REG,		22, 4, 0 },
	{ AMOVB, 		C_XPOST,	C_NONE,	C_REG,		22, 4, 0 },
	{ AMOVBU, 	C_XPOST,	C_NONE, C_REG,		22, 4, 0 },
	{ AFMOVS, 	C_XPOST,	C_NONE,	C_FREG,	22, 4, 0 },
	{ AFMOVD, 	C_XPOST,	C_NONE,	C_FREG,	22, 4, 0 },

	{ AMOV,		C_XPRE,	C_NONE,	C_REG,		22, 4, 0 },
	{ AMOVW, 	C_XPRE,	C_NONE,	C_REG,		22, 4, 0 },
	{ AMOVH,		C_XPRE,	C_NONE,	C_REG,		22, 4, 0 },
	{ AMOVB, 		C_XPRE,	C_NONE,	C_REG,		22, 4, 0 },
	{ AMOVBU, 	C_XPRE,	C_NONE, C_REG,		22, 4, 0 },
	{ AFMOVS, 	C_XPRE,	C_NONE,	C_FREG,	22, 4, 0 },
	{ AFMOVD, 	C_XPRE,	C_NONE,	C_FREG,	22, 4, 0 },

	/* pre/post-indexed store (unscaled, signed 9-bit offset) */
	{ AMOV,		C_REG,	C_NONE,	C_XPOST,		23, 4, 0 },
	{ AMOVW,		C_REG,	C_NONE,	C_XPOST,		23, 4, 0 },
	{ AMOVH,		C_REG,	C_NONE,	C_XPOST,		23, 4, 0 },
	{ AMOVB,		C_REG,	C_NONE, C_XPOST,		23, 4, 0 },
	{ AMOVBU, 	C_REG,	C_NONE, C_XPOST,		23, 4, 0 },
	{ AFMOVS, 	C_FREG,	C_NONE,	C_XPOST,		23, 4, 0 },
	{ AFMOVD, 	C_FREG,	C_NONE,	C_XPOST,		23, 4, 0 },

	{ AMOV,		C_REG,	C_NONE,	C_XPRE,		23, 4, 0 },
	{ AMOVW,		C_REG,	C_NONE,	C_XPRE,		23, 4, 0 },
	{ AMOVH,		C_REG,	C_NONE,	C_XPRE,		23, 4, 0 },
	{ AMOVB,		C_REG,	C_NONE, C_XPRE,		23, 4, 0 },
	{ AMOVBU, 	C_REG,	C_NONE, C_XPRE,		23, 4, 0 },
	{ AFMOVS, 	C_FREG,	C_NONE,	C_XPRE,		23, 4, 0 },
	{ AFMOVD, 	C_FREG,	C_NONE,	C_XPRE,		23, 4, 0 },

	/* special */
	{ AMOV,		C_SPR,	C_NONE,	C_REG,		35, 4, 0 },
	{ AMRS,		C_SPR,	C_NONE,	C_REG,		35, 4, 0 },

	{ AMOV,		C_REG,	C_NONE,	C_SPR,		36, 4, 0 },
	{ AMSR,		C_REG,	C_NONE,	C_SPR,		36, 4, 0 },

	{ AMOV,		C_VCON,	C_NONE,	C_SPR,		37, 4, 0 },
	{ AMSR,		C_VCON,	C_NONE,	C_SPR,		37, 4, 0 },

	{ AERET,		C_NONE,	C_NONE,	C_NONE,		41, 4, 0 },

	{ AFMOVS,	C_FREG,	C_NONE,	C_SEXT4,		20, 4, REGSB },
	{ AFMOVS,	C_FREG,	C_NONE,	C_UAUTO16K,	20, 4, REGSP },
	{ AFMOVS,	C_FREG,	C_NONE,	C_NSAUTO,	20, 4, REGSP },
	{ AFMOVS,	C_FREG,	C_NONE,	C_ZOREG,		20, 4, 0 },
	{ AFMOVS,	C_FREG,	C_NONE,	C_UOREG16K,	20, 4, 0 },
	{ AFMOVS,	C_FREG,	C_NONE,	C_NSOREG,	20, 4, 0 },

	{ AFMOVD,	C_FREG,	C_NONE,	C_SEXT8,		20, 4, REGSB },
	{ AFMOVD,	C_FREG,	C_NONE,	C_UAUTO32K,	20, 4, REGSP },
	{ AFMOVD,	C_FREG,	C_NONE,	C_NSAUTO,	20, 4, REGSP },
	{ AFMOVD,	C_FREG,	C_NONE,	C_ZOREG,		20, 4, 0 },
	{ AFMOVD,	C_FREG,	C_NONE,	C_UOREG32K,	20, 4, 0 }, 
	{ AFMOVD,	C_FREG,	C_NONE,	C_NSOREG,	20, 4, 0 },

	{ AFMOVS,	C_SEXT4,	C_NONE,	C_FREG,		21, 4, REGSB },
	{ AFMOVS,	C_UAUTO16K,C_NONE,	C_FREG,		21, 4, REGSP },
	{ AFMOVS,	C_NSAUTO,C_NONE,	C_FREG,		21, 4, REGSP },
	{ AFMOVS,	C_ZOREG,C_NONE,	C_FREG,		21, 4, 0 },
	{ AFMOVS,	C_UOREG16K,C_NONE,	C_FREG,		21, 4, 0 },
	{ AFMOVS,	C_NSOREG,C_NONE,	C_FREG,		21, 4, 0 },

	{ AFMOVD,	C_SEXT8,	C_NONE,	C_FREG,		21, 4, REGSB },
	{ AFMOVD,	C_UAUTO32K,C_NONE,	C_FREG,		21, 4, REGSP },
	{ AFMOVD,	C_NSAUTO,C_NONE,	C_FREG,		21, 4, REGSP },
	{ AFMOVD,	C_ZOREG,C_NONE,	C_FREG,		21, 4, 0 },
	{ AFMOVD,	C_UOREG32K,C_NONE,	C_FREG,		21, 4, 0 },
	{ AFMOVD,	C_NSOREG,C_NONE,	C_FREG,		21, 4, 0 },

	{ AFMOVS,	C_FREG,	C_NONE,	C_LEXT,		30, 8, REGSB,	LTO },
	{ AFMOVS,	C_FREG,	C_NONE,	C_LAUTO,	30, 8, REGSP,	LTO },
	{ AFMOVS,	C_FREG,	C_NONE,	C_LOREG,	30, 8, 0,	LTO },

	{ AFMOVS,	C_LEXT,	C_NONE,	C_FREG,		31, 8, REGSB,	LFROM },
	{ AFMOVS,	C_LAUTO,C_NONE,	C_FREG,		31, 8, REGSP,	LFROM },
	{ AFMOVS,	C_LOREG,C_NONE,	C_FREG,		31, 8, 0,	LFROM },

	{ AFMOVS,	C_FREG,	C_NONE,	C_ADDR,		64, 8, 0,	LTO },
	{ AFMOVS,	C_ADDR,	C_NONE,	C_FREG,		65, 8, 0,	LFROM },
	{ AFMOVD,	C_FREG,	C_NONE,	C_ADDR,		64, 8, 0,	LTO },
	{ AFMOVD,	C_ADDR,	C_NONE,	C_FREG,		65, 8, 0,	LFROM },

	{ AFADDS,		C_FREG,	C_NONE,	C_FREG,		54, 4, 0 },
	{ AFADDS,		C_FREG,	C_REG,	C_FREG,		54, 4, 0 },
	{ AFADDS,		C_FCON,	C_NONE,	C_FREG,		54, 4, 0 },
	{ AFADDS,		C_FCON,	C_REG,	C_FREG,		54, 4, 0 },

	{ AFMOVS,	C_FCON,	C_NONE,	C_FREG,		54, 4, 0 },
	{ AFMOVS,	C_FREG, C_NONE, C_FREG,		54, 4, 0 },
	{ AFMOVD,	C_FCON,	C_NONE,	C_FREG,		54, 4, 0 },
	{ AFMOVD,	C_FREG, C_NONE, C_FREG,		54, 4, 0 },

	{ AFCVTZSD,	C_FREG,	C_NONE,	C_REG,		29, 4, 0 },
	{ ASCVTFD,	C_REG,	C_NONE,	C_FREG,		29, 4, 0 },

	{ AFCMPS,		C_FREG,	C_REG,	C_NONE,		56, 4, 0 },
	{ AFCMPS,		C_FCON,	C_REG,	C_NONE,		56, 4, 0 },

	{ AFCCMPS,	C_COND,	C_REG,	C_VCON,		57, 4, 0 },

	{ AFCSELD,	C_COND,	C_REG,	C_FREG,		18, 4, 0 },

	{ AFCVTSD,	C_FREG,	C_NONE,	C_FREG,		29, 4, 0 },

	{ ACASE,	C_REG,	C_NONE,	C_REG,		62, 4*4, 0 },
	{ ABCASE,	C_NONE, C_NONE, C_SBRA,		63, 4, 0 },

	{ ACLREX,		C_NONE,	C_NONE,	C_VCON,		38, 4, 0 },
	{ ACLREX,		C_NONE,	C_NONE,	C_NONE,		38, 4, 0 },

	{ ACBZ,		C_REG,	C_NONE,	C_SBRA,		39, 4, 0 },
	{ ATBZ,		C_VCON,	C_REG,	C_SBRA,		40, 4, 0 },

	{ ASYS,		C_VCON,	C_NONE,	C_NONE,		50, 4, 0 },
	{ ASYS,		C_VCON,	C_REG,	C_NONE,		50, 4, 0 },
	{ ASYSL,		C_VCON,	C_NONE,	C_REG,		50, 4, 0 },

	{ ADMB,		C_VCON,	C_NONE, 	C_NONE,		51, 4, 0 },
	{ AHINT,		C_VCON,	C_NONE,	C_NONE,		52, 4, 0 },

	{ ALDAR,		C_ZOREG,	C_NONE,	C_REG,		58, 4, 0 },
	{ ALDXR,		C_ZOREG,	C_NONE,	C_REG,		58, 4, 0 },
	{ ALDAXR,		C_ZOREG,	C_NONE,	C_REG,		58, 4, 0 },
	{ ALDXP,		C_ZOREG,	C_REG,	C_REG,		58, 4, 0 },
	{ ASTLR,		C_REG,	C_NONE,	C_ZOREG,		59, 4, 0 },	// to3=C_NONE
	{ ASTXR,		C_REG,	C_NONE,	C_ZOREG,		59, 4, 0 }, // to3=C_REG
	{ ASTLXR,		C_REG,	C_NONE,	C_ZOREG,		59, 4, 0 }, // to3=C_REG
	{ ASTXP,		C_REG, C_NONE,	C_ZOREG,		59, 4, 0 }, // to3=C_REG

	{ AAESD,	C_VREG,	C_NONE,	C_VREG,	29, 4, 0 },
	{ ASHA1C,	C_VREG,	C_REG,	C_VREG,	1, 4, 0 },

	{ AUNDEF,		C_NONE,	C_NONE,	C_NONE,		90, 4, 0 },

	{ AUSEFIELD,	C_ADDR,	C_NONE,	C_NONE, 	 0, 0, 0 },
	{ APCDATA,	C_VCON,	C_NONE,	C_VCON,		0, 0, 0 },
	{ AFUNCDATA,	C_VCON,	C_NONE,	C_ADDR,	0, 0, 0 },
	
	{ ADUFFZERO,	C_NONE,	C_NONE,	C_SBRA,		 5, 4, 0 },	// same as AB/ABL
	{ ADUFFCOPY,	C_NONE,	C_NONE,	C_SBRA,		 5, 4, 0 },	// same as AB/ABL

	{ AXXX,		C_NONE,	C_NONE,	C_NONE,		 0, 4, 0 },
};

/*
 * internal class codes for different constant classes:
 * they partition the constant/offset range into disjoint ranges that
 * are somehow treated specially by one or more load/store instructions.
 */
static int	autoclass[] = {C_PSAUTO, C_NSAUTO, C_NPAUTO, C_PSAUTO, C_PPAUTO, C_UAUTO4K, C_UAUTO8K, C_UAUTO16K, C_UAUTO32K, C_UAUTO64K, C_LAUTO};
static int	oregclass[] = {C_ZOREG, C_NSOREG, C_NPOREG, C_PSOREG, C_PPOREG, C_UOREG4K, C_UOREG8K, C_UOREG16K, C_UOREG32K, C_UOREG64K, C_LOREG};

/*
 * valid pstate field values, and value to use in instruction
 */
struct{
	ulong	a;
	ulong	b;
} pstatefield[] = {
	{ D_SPSel,		(0<<16) | (4<<12) | (5<<5) },
	{ D_DAIFSet,	(3<<16) | (4<<12) | (6<<5) },
	{ D_DAIFClr,	(3<<16) | (4<<12) | (7<<5) },
};

static struct {
	ulong	start;
	ulong	size;
} pool;

static void
prasm(Prog *p)
{
	print("%P\n", p);
}

void
span7(Link *ctxt, LSym *cursym)
{
	Prog *p;
	Optab *o;
	int m, bflag, i, j;
	int32 c, psz;
	uint32 out[6];
	uchar *bp, *cast;
	
	p = cursym->text;
	if(p == nil || p->link == nil) // handle external functions and ELF section symbols
		return;
	ctxt->cursym = cursym;
	ctxt->autosize = (int32)(p->to.offset & 0xffffffffll) + 8;

	if(oprange[AAND].start == nil)
 		buildop(ctxt);

	bflag = 0;
	c = 0;	
	p->pc = c;
	for(p = p->link; p != nil; p = p->link) {
		ctxt->curp = p;
		if(p->as == ADWORD && ((c & 7)) != 0)
			c += 4;
		p->pc = c;
		if (p->from.type == D_CONST && p->from.offset == 0)
			p->from.reg = REGZERO;
		if (p->to.type == D_CONST && p->to.offset == 0)
			p->to.reg = REGZERO;
		o = oplook(ctxt, p);
		m = o->size;
		if(m == 0) {
			if(p->as != ANOP && p->as != AFUNCDATA && p->as != APCDATA)
				ctxt->diag("zero-width instruction\n%P", p);
			continue;
		}
		switch(o->flag & ((LFROM | LTO))) {
		case LFROM:
			addpool(ctxt, p, &p->from);
			break;
		case LTO:
			addpool(ctxt, p, &p->to);
			break;
		}
		if(p->as == AB || p->as == ARET || p->as == AERET || p->as == ARETURN) /* TO DO: other unconditional operations */
			checkpool(ctxt, p, 0);
		c += m;
		if(ctxt->blitrl)
			checkpool(ctxt, p, 1);
	}
	cursym->size = c;
	/*
	 * if any procedure is large enough to
	 * generate a large SBRA branch, then
	 * generate extra passes putting branches
	 * around jmps to fix. this is rare.
	 */
	while(bflag) {
		if(ctxt->debugvlog)
			Bprint(ctxt->bso, "%5.2f span1\n", cputime());
		bflag = 0;
		c = 0;
		for(p = cursym->text; p != nil; p = p->link) {
			if(p->as == ADWORD && ((c & 7)) != 0)
				c += 4;
			p->pc = c;
			o = oplook(ctxt, p);
			/* very large branches
						if(o->type == 6 && p->cond) {
							otxt = p->cond->pc - c;
							if(otxt < 0)
								otxt = -otxt;
							if(otxt >= (1L<<17) - 10) {
								q = ctxt->arch->prg();
								q->link = p->link;
								p->link = q;
								q->as = AB;
								q->to.type = D_BRANCH;
								q->cond = p->cond;
								p->cond = q;
								q = ctxt->arch->prg();
								q->link = p->link;
								p->link = q;
								q->as = AB;
								q->to.type = D_BRANCH;
								q->cond = q->link->link;
								bflag = 1;
							}
						}
			 */
			m = o->size;
			if(m == 0) {
				if(p->as != ANOP && p->as != AFUNCDATA && p->as != APCDATA)
					ctxt->diag("zero-width instruction\n%P", p);
				continue;
			}
			c += m;
		}
	}
	c += -c&(FuncAlign-1);
	cursym->size = c;
	/*
	 * lay out the code, emitting code and data relocations.
	 */
	if(ctxt->tlsg == nil)
		ctxt->tlsg = linklookup(ctxt, "runtime.tlsg", 0);
	symgrow(ctxt, cursym, cursym->size);
	bp = cursym->p;
	psz = 0;
	for(p = cursym->text->link; p != nil; p = p->link) {
		ctxt->pc = p->pc;
		ctxt->curp = p;
		o = oplook(ctxt, p);
		// need to align DWORDs on 8-byte boundary. The ISA doesn't
		// require it, but the various 64-bit loads we generate assume it.
		if(o->as == ADWORD && psz % 8 != 0) {
			bp[0] = bp[1] = bp[2] = bp[3] = 0;
			bp += 4;
			psz += 4;
		}
		if(o->size > 4*nelem(out))
			sysfatal("out array in span7 is too small, need at least %d for %P", o->size/4, p);
		asmout(ctxt, p, o, out);
		for(i=0; i<o->size/4; i++) {
			cast = (uchar*)&out[i];
			for(j=0; j<4; j++, psz++)
				*bp++ = cast[inuxi4[j]];
		}
	}
}

/*
 * when the first reference to the literal pool threatens
 * to go out of range of a 1Mb PC-relative offset
 * drop the pool now, and branch round it.
 */
static void
checkpool(Link *ctxt, Prog *p, int skip)
{
	if(pool.size >= 0xffff0 || !ispcdisp(p->pc + 4 + pool.size - pool.start + 8))
		flushpool(ctxt, p, skip);
	else
		if(p->link == nil)
			flushpool(ctxt, p, 2);
}

static void
flushpool(Link *ctxt, Prog *p, int skip)
{
	Prog *q;
	if(ctxt->blitrl) {
		if(skip) {
			if(ctxt->debugvlog && skip == 1)
				print("note: flush literal pool at %#llux: len=%lud ref=%lux\n", p->pc + 4, pool.size, pool.start);
			q = ctxt->arch->prg();
			q->as = AB;
			q->to.type = D_BRANCH;
			q->pcond = p->link;
			q->link = ctxt->blitrl;
			ctxt->blitrl = q;
		} else
			if(p->pc + pool.size - pool.start < 1024 * 1024)
				return;
		ctxt->elitrl->link = p->link;
		p->link = ctxt->blitrl;
		ctxt->blitrl = 0; /* BUG: should refer back to values until out-of-range */
		ctxt->elitrl = 0;
		pool.size = 0;
		pool.start = 0;
	}
}

/*
 * TO DO: hash
 */
static void
addpool(Link *ctxt, Prog *p, Addr *a)
{
	Prog *q;
	Prog t;
	int c;
	int sz;
	c = aclass(ctxt, a);
	t = zprg;
	t.as = AWORD;
	sz = 4;
	// MOVW foo(SB), R is actually
	//	MOV addr, REGTEMP
	//	MOVW REGTEMP, R
	// where addr is the address of the DWORD containing the address of foo.
	if(p->as == AMOV || c == C_ADDR || c == C_VCON) {
		t.as = ADWORD;
		sz = 8;
	}
	switch(c) {
	default:
		// TODO(aram): remove.
		if(a->name != D_EXTERN) {
			print("addpool: %^ in %P shouldn't go to default case\n", c, p);
		}
		t.to.offset = a->offset;
		t.to.sym = a->sym;
		t.to.type = a->type;
		t.to.name = a->name;
		t.to3.type = D_NONE;
		break;

	/* This is here to work around a bug where we generate negative
	operands that match C_MOVCON, but we use them with
	instructions that only accept unsigned immediates. This
	will cause oplook to return a variant of the instruction
	that loads the negative constant from memory, rather than
	using the immediate form. Because of that load, we get here,
	so we need to know what to do with C_MOVCON.
	
	The correct fix is to use the "negation" instruction variant,
	e.g. CMN $0, R instead of CMP $-1, R, or SUB $1, R instead
	of ADD $-1, R. */
	case C_MOVCON:

	/* This is here because MOV uint12<<12, R is disabled in optab.
	Because of this, we need to load the constant from memory. */
	case C_ADDCON:

	case C_PSAUTO:
	case C_PPAUTO:
	case C_UAUTO4K:
	case C_UAUTO8K:
	case C_UAUTO16K:
	case C_UAUTO32K:
	case C_UAUTO64K:
	case C_NSAUTO:
	case C_NPAUTO:
	case C_LAUTO:
	case C_PPOREG:
	case C_PSOREG:
	case C_UOREG4K:
	case C_UOREG8K:
	case C_UOREG16K:
	case C_UOREG32K:
	case C_UOREG64K:
	case C_NSOREG:
	case C_NPOREG:
	case C_LOREG:
	case C_LACON:
	case C_LCON:
	case C_VCON:
		if(a->name == D_EXTERN) {
			print("addpool: %^ in %P needs reloc\n", c, p);
		}
		t.to.type = D_CONST;
		t.to.offset = ctxt->instoffset;
		t.to3.type = D_NONE;
		break;
	}
	for(q = ctxt->blitrl; q != nil; q = q->link) /* could hash on t.t0.offset */
		if(memcmp(&q->to, &t.to, sizeof(t.to)) == 0) {
			p->pcond = q;
			return;
		}
	q = ctxt->arch->prg();
	*q = t;
	q->pc = pool.size;
	if(ctxt->blitrl == nil) {
		ctxt->blitrl = q;
		pool.start = p->pc;
	} else
		ctxt->elitrl->link = q;
	ctxt->elitrl = q;
	pool.size = -pool.size&(FuncAlign-1);
	pool.size += sz;
	p->pcond = q;
}

static uint32
regoff(Link *ctxt, Addr *a)
{
	ctxt->instoffset = 0;
	aclass(ctxt, a);
	return ctxt->instoffset;
}

static int
ispcdisp(int32 v)
{
	/* pc-relative addressing will reach? */
	return v >= -0xfffff && v <= 0xfffff && ((v & 3)) == 0;
}

static int
isaddcon(vlong v)
{
	/* uimm12 or uimm24? */
	if(v < 0)
		return 0;
	if(((v & 0xFFF)) == 0)
		v >>= 12;
	return v <= 0xFFF;
}

static int
isbitcon(uvlong v)
{
	/*  fancy bimm32 or bimm64? */
	return findmask(v) != nil || ((v >> 32)) == 0 && findmask(v | ((v << 32))) != nil;
}

/*
 * return appropriate index into tables above
 */
static int
constclass(vlong l)
{
	if(l == 0)
		return 0;
	if(l < 0) {
		if(l >= -256)
			return 1;
		if(l >= -512 && ((l & 7)) == 0)
			return 2;
		return 10;
	}
	if(l <= 255)
		return 3;
	if(l <= 504 && ((l & 7)) == 0)
		return 4;
	if(l <= 4095)
		return 5;
	if(l <= 8190 && ((l & 1)) == 0)
		return 6;
	if(l <= 16380 && ((l & 3)) == 0)
		return 7;
	if(l <= 32760 && ((l & 7)) == 0)
		return 8;
	if(l <= 65520 && ((l & 0xF)) == 0)
		return 9;
	return 10;
}

/*
 * given an offset v and a class c (see above)
 * return the offset value to use in the instruction,
 * scaled if necessary
 */
static vlong
offsetshift(Link *ctxt, vlong v, int c)
{
	vlong vs;
	int s;
	static int shifts[] = {0, 1, 2, 3, 4};
	s = 0;
	if(c >= C_SEXT1 && c <= C_SEXT16)
		s = shifts[c - C_SEXT1];
	else
		if(c >= C_UAUTO4K && c <= C_UAUTO64K)
			s = shifts[c - C_UAUTO4K];
		else
			if(c >= C_UOREG4K && c <= C_UOREG64K)
				s = shifts[c - C_UOREG4K];
	vs = v >> s;
	if(vs << s != v)
		ctxt->diag("odd offset: %lld\n%P", v, ctxt->curp);
	return vs;
}

/*
 * if v contains a single 16-bit value aligned
 * on a 16-bit field, and thus suitable for movk/movn,
 * return the field index 0 to 3; otherwise return -1
 */
static int
movcon(vlong v)
{
	int s;
	for(s = 0; s < 64; s += 16)
		if(((v & ~(((uvlong)0xFFFF << s)))) == 0)
			return s / 16;
	return -1;
}

static int
aclass(Link *ctxt, Addr *a)
{
	vlong v;
	LSym *s;
	int t;
	ctxt->instoffset = 0;
	switch(a->type) {
	case D_NONE:
		return C_NONE;
	case D_REG:
		return C_REG;
	case D_VREG:
		return C_VREG;
	case D_SP:
		return C_RSP;
	case D_COND:
		return C_COND;
	case D_SHIFT:
		return C_SHIFT;
	case D_EXTREG:
		return C_EXTREG;
	case D_ROFF:
		return C_ROFF;
	case D_XPOST:
		return C_XPOST;
	case D_XPRE:
		return C_XPRE;
	case D_FREG:
		return C_FREG;
	case D_OREG:
		switch(a->name) {
		case D_EXTERN:
		case D_STATIC:
			if(a->sym == nil)
				break;
			ctxt->instoffset = a->offset;
			if(a->sym != nil) // use relocation
				return C_ADDR;
			return C_LEXT;
		case D_AUTO:
			ctxt->instoffset = ctxt->autosize + a->offset;
			return autoclass[constclass(ctxt->instoffset)];
		case D_PARAM:
			ctxt->instoffset = ctxt->autosize + a->offset + 8;
			return autoclass[constclass(ctxt->instoffset)];
		case D_NONE:
			ctxt->instoffset = a->offset;
			return oregclass[constclass(ctxt->instoffset)];
		}
		return C_GOK;
	case D_SPR:
		return C_SPR;
	case D_OCONST:
		switch(a->name) {
		case D_EXTERN:
		case D_STATIC:
			if(a->sym == nil)
				break;
			ctxt->instoffset = a->offset;
			if(a->sym != nil) // use relocation
				return C_ADDR;
			return C_VCON;
		}
		return C_GOK;
	case D_FCONST:
		return C_FCON;
	case D_CONST:
		switch(a->name) {
		case D_NONE:
			ctxt->instoffset = a->offset;
			if(a->reg != NREG && a->reg != REGZERO)
				goto aconsize;
			v = ctxt->instoffset;
			if(v == 0)
				return C_ZCON;
			if(isaddcon(v)) {
				if(v <= 0xFFF)
					return C_ADDCON0;
				if(isbitcon(v))
					return C_ABCON;
				return C_ADDCON;
			}
			t = movcon(v);
			if(t >= 0) {
				if(isbitcon(v))
					return C_MBCON;
				return C_MOVCON;
			}
			t = movcon(~v);
			if(t >= 0) {
				if(isbitcon(v))
					return C_MBCON;
				return C_MOVCON;
			}
			if(isbitcon(v))
				return C_BITCON;
			return C_VCON;
		case D_EXTERN:
		case D_STATIC:
			s = a->sym;
			if(s == nil)
				break;
			ctxt->instoffset = a->offset;
			return C_ADDR;
		case D_AUTO:
			ctxt->instoffset = ctxt->autosize + a->offset;
			goto aconsize;
		case D_PARAM:
			ctxt->instoffset = ctxt->autosize + a->offset + 8;
			goto aconsize;
		}
		return C_GOK;

	aconsize:
		if(isaddcon(ctxt->instoffset))
			return C_AACON;
		return C_LACON;

	case D_BRANCH:
		return C_SBRA;
	}
	return C_GOK;
}

static Optab*
oplook(Link *ctxt, Prog *p)
{
	int a1;
	int a2;
	int a3;
	int r;
	uchar *c1;
	uchar *c2;
	uchar *c3;
	Optab *o;
	Optab *e;
	a1 = p->optab;
	if(a1)
		return optab + ((a1 - 1));
	a1 = p->from.class;
	if(a1 == 0) {
		a1 = aclass(ctxt, &p->from) + 1;
		p->from.class = a1;
	}
	a1--;
	a3 = p->to.class;
	if(a3 == 0) {
		a3 = aclass(ctxt, &p->to) + 1;
		p->to.class = a3;
	}
	a3--;
	a2 = C_NONE;
	if(p->reg != NREG)
		a2 = C_REG;
	r = p->as;
	o = oprange[r].start;
	if(o == 0) {
		a1 = (int)opcross[repop[r]][a1][a2][a3];
		if(a1) {
			p->optab = a1 + 1;
			return optab + a1;
		}
		o = oprange[r].stop; /* just generate an error */
	}
	if(0) {
		print("oplook %A %d %d %d\n", (int)p->as, a1, a2, a3);
		print("		%d %d\n", p->from.type, p->to.type);
	}
	e = oprange[r].stop;
	c1 = xcmp[a1];
	c2 = xcmp[a2];
	c3 = xcmp[a3];
	for(; o < e; o++)
		if(o->a2 == a2 || c2[o->a2])
			if(c1[o->a1])
				if(c3[o->a3]) {
					p->optab = ((o - optab)) + 1;
					return o;
				}
	ctxt->diag("illegal combination %P %^ %^ %^, %d %d",
                p, a1, a2, a3, p->from.type, p->to.type);
	prasm(p);
	if(o == 0)
		o = optab;
	return o;
}

static int
cmp(int a, int b)
{
	if(a == b)
		return 1;
	switch(a) {
	case C_RSP:
		if(b == C_REG)
			return 1;
		break;
	case C_REG:
		if(b == C_ZCON)
			return 1;
		break;
	case C_ADDCON0:
		if(b == C_ZCON)
			return 1;
		break;
	case C_ADDCON:
		if(b == C_ZCON || b == C_ADDCON0 || b == C_ABCON)
			return 1;
		break;
	case C_BITCON:
		if(b == C_ABCON || b == C_MBCON)
			return 1;
		break;
	case C_MOVCON:
		if(b == C_MBCON || b == C_ZCON || b == C_ADDCON0)
			return 1;
		break;
	case C_LCON:
		if(b == C_ZCON || b == C_BITCON || b == C_ADDCON || b == C_ADDCON0 || b == C_ABCON || b == C_MBCON || b == C_MOVCON)
			return 1;
		break;
	case C_VCON:
		return cmp(C_LCON, b);
	case C_LACON:
		if(b == C_AACON)
			return 1;
		break;
	case C_SEXT2:
		if(b == C_SEXT1)
			return 1;
		break;
	case C_SEXT4:
		if(b == C_SEXT1 || b == C_SEXT2)
			return 1;
		break;
	case C_SEXT8:
		if(b >= C_SEXT1 && b <= C_SEXT4)
			return 1;
		break;
	case C_SEXT16:
		if(b >= C_SEXT1 && b <= C_SEXT8)
			return 1;
		break;
	case C_LEXT:
		if(b >= C_SEXT1 && b <= C_SEXT16)
			return 1;
		break;
	case C_PPAUTO:
		if(b == C_PSAUTO)
			return 1;
		break;
	case C_UAUTO4K:
		if(b == C_PSAUTO || b == C_PPAUTO)
			return 1;
		break;
	case C_UAUTO8K:
		return cmp(C_UAUTO4K, b);
	case C_UAUTO16K:
		return cmp(C_UAUTO8K, b);
	case C_UAUTO32K:
		return cmp(C_UAUTO16K, b);
	case C_UAUTO64K:
		return cmp(C_UAUTO32K, b);
	case C_NPAUTO:
		return cmp(C_NSAUTO, b);
	case C_LAUTO:
		return cmp(C_NPAUTO, b) || cmp(C_UAUTO64K, b);
	case C_PSOREG:
		if(b == C_ZOREG)
			return 1;
		break;
	case C_PPOREG:
		if(b == C_ZOREG || b == C_PSOREG)
			return 1;
		break;
	case C_UOREG4K:
		if(b == C_ZOREG || b == C_PSAUTO || b == C_PSOREG || b == C_PPAUTO || b == C_PPOREG)
			return 1;
		break;
	case C_UOREG8K:
		return cmp(C_UOREG4K, b);
	case C_UOREG16K:
		return cmp(C_UOREG8K, b);
	case C_UOREG32K:
		return cmp(C_UOREG16K, b);
	case C_UOREG64K:
		return cmp(C_UOREG32K, b);
	case C_NPOREG:
		return cmp(C_NSOREG, b);
	case C_LOREG:
		return cmp(C_NPOREG, b) || cmp(C_UOREG64K, b);
	case C_LBRA:
		if(b == C_SBRA)
			return 1;
		break;
	}
	return 0;
}

static int
ocmp(const void  *a1, const void  *a2)
{
	Optab *p1;
	Optab *p2;
	int n;
	p1 = (Optab*)a1;
	p2 = (Optab*)a2;
	n = p1->as - p2->as;
	if(n)
		return n;
	n = p1->a1 - p2->a1;
	if(n)
		return n;
	n = p1->a2 - p2->a2;
	if(n)
		return n;
	n = p1->a3 - p2->a3;
	if(n)
		return n;
	return 0;
}

void
buildop(Link *ctxt)
{
	int i;
	int n;
	int r;
	Oprang t;
	for(i = 0; i < C_GOK; i++)
		for(n = 0; n < C_GOK; n++)
			xcmp[i][n] = cmp(n, i);
	for(n = 0; optab[n].as != AXXX; n++)
		;
	qsort(optab, n, sizeof(optab[0]), ocmp);
	for(i = 0; i < n; i++) {
		r = optab[i].as;
		oprange[r].start = optab + i;
		while(optab[i].as == r)
			i++;
		oprange[r].stop = optab + i;
		i--;
		t = oprange[r];
		switch(r) {
		default:
			ctxt->diag("unknown op in build: %A", r);
			sysfatal("bad code");
		case AXXX:
			break;
		case AADD:
			oprange[AADDS] = t;
			oprange[ASUB] = t;
			oprange[ASUBS] = t;
			oprange[AADDW] = t;
			oprange[AADDSW] = t;
			oprange[ASUBW] = t;
			oprange[ASUBSW] = t;
			break;
		case AAND: /* logical immediate, logical shifted register */
			oprange[AANDS] = t;
			oprange[AANDSW] = t;
			oprange[AANDW] = t;
			oprange[AEOR] = t;
			oprange[AEORW] = t;
			oprange[AORR] = t;
			oprange[AORRW] = t;
			break;
		case ABIC: /* only logical shifted register */
			oprange[ABICS] = t;
			oprange[ABICSW] = t;
			oprange[ABICW] = t;
			oprange[AEON] = t;
			oprange[AEONW] = t;
			oprange[AORN] = t;
			oprange[AORNW] = t;
			break;
		case ANEG:
			oprange[ANEGS] = t;
			oprange[ANEGSW] = t;
			oprange[ANEGW] = t;
			break;
		case AADC: /* rn=Rd */
			oprange[AADCW] = t;
			oprange[AADCS] = t;
			oprange[AADCSW] = t;
			oprange[ASBC] = t;
			oprange[ASBCW] = t;
			oprange[ASBCS] = t;
			oprange[ASBCSW] = t;
			break;
		case ANGC: /* rn=REGZERO */
			oprange[ANGCW] = t;
			oprange[ANGCS] = t;
			oprange[ANGCSW] = t;
			break;
		case ACMP:
			oprange[ACMPW] = t;
			oprange[ACMN] = t;
			oprange[ACMNW] = t;
			break;
		case ATST:
			oprange[ATSTW] = t;
			break;
		/* register/register, and shifted */
		case AMVN:
			oprange[AMVNW] = t;
			break;
		case AMOVK:
			oprange[AMOVKW] = t;
			oprange[AMOVN] = t;
			oprange[AMOVNW] = t;
			oprange[AMOVZ] = t;
			oprange[AMOVZW] = t;
			break;
		case ABEQ:
			oprange[ABNE] = t;
			oprange[ABCS] = t;
			oprange[ABHS] = t;
			oprange[ABCC] = t;
			oprange[ABLO] = t;
			oprange[ABMI] = t;
			oprange[ABPL] = t;
			oprange[ABVS] = t;
			oprange[ABVC] = t;
			oprange[ABHI] = t;
			oprange[ABLS] = t;
			oprange[ABGE] = t;
			oprange[ABLT] = t;
			oprange[ABGT] = t;
			oprange[ABLE] = t;
			break;
		case ALSL:
			oprange[ALSLW] = t;
			oprange[ALSR] = t;
			oprange[ALSRW] = t;
			oprange[AASR] = t;
			oprange[AASRW] = t;
			oprange[AROR] = t;
			oprange[ARORW] = t;
			break;
		case ACLS:
			oprange[ACLSW] = t;
			oprange[ACLZ] = t;
			oprange[ACLZW] = t;
			oprange[ARBIT] = t;
			oprange[ARBITW] = t;
			oprange[AREV] = t;
			oprange[AREVW] = t;
			oprange[AREV16] = t;
			oprange[AREV16W] = t;
			oprange[AREV32] = t;
			break;
		case ASDIV:
			oprange[ASDIVW] = t;
			oprange[AUDIV] = t;
			oprange[AUDIVW] = t;
			oprange[ACRC32B] = t;
			oprange[ACRC32CB] = t;
			oprange[ACRC32CH] = t;
			oprange[ACRC32CW] = t;
			oprange[ACRC32CX] = t;
			oprange[ACRC32H] = t;
			oprange[ACRC32W] = t;
			oprange[ACRC32X] = t;
			break;
		case AMADD:
			oprange[AMADDW] = t;
			oprange[AMSUB] = t;
			oprange[AMSUBW] = t;
			oprange[ASMADDL] = t;
			oprange[ASMSUBL] = t;
			oprange[AUMADDL] = t;
			oprange[AUMSUBL] = t;
			break;
		case AREM:
			oprange[AREMW] = t;
			oprange[AUREM] = t;
			oprange[AUREMW] = t;
			break;
		case AMUL:
			oprange[AMULW] = t;
			oprange[AMNEG] = t;
			oprange[AMNEGW] = t;
			oprange[ASMNEGL] = t;
			oprange[ASMULL] = t;
			oprange[ASMULH] = t;
			oprange[AUMNEGL] = t;
			oprange[AUMULH] = t;
			oprange[AUMULL] = t;
			break;
		case AMOVB:
			oprange[AMOVBU] = t;
			break;
		case AMOVH:
			oprange[AMOVHU] = t;
			break;
		case AMOVW:
			oprange[AMOVWU] = t;
			break;
		case ABFM:
			oprange[ABFMW] = t;
			oprange[ASBFM] = t;
			oprange[ASBFMW] = t;
			oprange[AUBFM] = t;
			oprange[AUBFMW] = t;
			break;
		case ABFI:
			oprange[ABFIW] = t;
			oprange[ABFXIL] = t;
			oprange[ABFXILW] = t;
			oprange[ASBFIZ] = t;
			oprange[ASBFIZW] = t;
			oprange[ASBFX] = t;
			oprange[ASBFXW] = t;
			oprange[AUBFIZ] = t;
			oprange[AUBFIZW] = t;
			oprange[AUBFX] = t;
			oprange[AUBFXW] = t;
			break;
		case AEXTR:
			oprange[AEXTRW] = t;
			break;
		case ASXTB:
			oprange[ASXTBW] = t;
			oprange[ASXTH] = t;
			oprange[ASXTHW] = t;
			oprange[ASXTW] = t;
			oprange[AUXTB] = t;
			oprange[AUXTH] = t;
			oprange[AUXTW] = t;
			oprange[AUXTBW] = t;
			oprange[AUXTHW] = t;
			break;
		case ACCMN:
			oprange[ACCMNW] = t;
			oprange[ACCMP] = t;
			oprange[ACCMPW] = t;
			break;
		case ACSEL:
			oprange[ACSELW] = t;
			oprange[ACSINC] = t;
			oprange[ACSINCW] = t;
			oprange[ACSINV] = t;
			oprange[ACSINVW] = t;
			oprange[ACSNEG] = t;
			oprange[ACSNEGW] = t;
			// aliases Rm=Rn, !cond
			oprange[ACINC] = t;
			oprange[ACINCW] = t;
			oprange[ACINV] = t;
			oprange[ACINVW] = t;
			oprange[ACNEG] = t;
			oprange[ACNEGW] = t;
			break;
		// aliases, Rm=Rn=REGZERO, !cond
		case ACSET:
			oprange[ACSETW] = t;
			oprange[ACSETM] = t;
			oprange[ACSETMW] = t;
			break;
		case AMOV:
		case AMOVBU:
		case AB:
		case ABL:
		case AWORD:
		case ADWORD:
		case ARET:
		case ATEXT:
		case ACASE:
		case ABCASE:
			break;
		case AERET:
			oprange[ANOP] = t;
			oprange[AWFE] = t;
			oprange[AWFI] = t;
			oprange[AYIELD] = t;
			oprange[ASEV] = t;
			oprange[ASEVL] = t;
			oprange[ADRPS] = t;
			break;
		case ACBZ:
			oprange[ACBZW] = t;
			oprange[ACBNZ] = t;
			oprange[ACBNZW] = t;
			break;
		case ATBZ:
			oprange[ATBNZ] = t;
			break;
		case AADR:
		case AADRP:
			break;
		case ACLREX:
			break;
		case ASVC:
			oprange[AHLT] = t;
			oprange[AHVC] = t;
			oprange[ASMC] = t;
			oprange[ABRK] = t;
			oprange[ADCPS1] = t;
			oprange[ADCPS2] = t;
			oprange[ADCPS3] = t;
			break;
		case AFADDS:
			oprange[AFADDD] = t;
			oprange[AFSUBS] = t;
			oprange[AFSUBD] = t;
			oprange[AFMULS] = t;
			oprange[AFMULD] = t;
			oprange[AFNMULS] = t;
			oprange[AFNMULD] = t;
			oprange[AFDIVS] = t;
			oprange[AFMAXD] = t;
			oprange[AFMAXS] = t;
			oprange[AFMIND] = t;
			oprange[AFMINS] = t;
			oprange[AFMAXNMD] = t;
			oprange[AFMAXNMS] = t;
			oprange[AFMINNMD] = t;
			oprange[AFMINNMS] = t;
			oprange[AFDIVD] = t;
			break;
		case AFCVTSD:
			oprange[AFCVTDS] = t;
			oprange[AFABSD] = t;
			oprange[AFABSS] = t;
			oprange[AFNEGD] = t;
			oprange[AFNEGS] = t;
			oprange[AFSQRTD] = t;
			oprange[AFSQRTS] = t;
			oprange[AFRINTNS] = t;
			oprange[AFRINTND] = t;
			oprange[AFRINTPS] = t;
			oprange[AFRINTPD] = t;
			oprange[AFRINTMS] = t;
			oprange[AFRINTMD] = t;
			oprange[AFRINTZS] = t;
			oprange[AFRINTZD] = t;
			oprange[AFRINTAS] = t;
			oprange[AFRINTAD] = t;
			oprange[AFRINTXS] = t;
			oprange[AFRINTXD] = t;
			oprange[AFRINTIS] = t;
			oprange[AFRINTID] = t;
			oprange[AFCVTDH] = t;
			oprange[AFCVTHS] = t;
			oprange[AFCVTHD] = t;
			oprange[AFCVTSH] = t;
			break;
		case AFCMPS:
			oprange[AFCMPD] = t;
			oprange[AFCMPES] = t;
			oprange[AFCMPED] = t;
			break;
		case AFCCMPS:
			oprange[AFCCMPD] = t;
			oprange[AFCCMPES] = t;
			oprange[AFCCMPED] = t;
			break;
		case AFCSELD:
			oprange[AFCSELS] = t;
			break;
		case AFMOVS:
		case AFMOVD:
			break;
		case AFCVTZSD:
			oprange[AFCVTZSDW] = t;
			oprange[AFCVTZSS] = t;
			oprange[AFCVTZSSW] = t;
			oprange[AFCVTZUD] = t;
			oprange[AFCVTZUDW] = t;
			oprange[AFCVTZUS] = t;
			oprange[AFCVTZUSW] = t;
			break;
		case ASCVTFD:
			oprange[ASCVTFS] = t;
			oprange[ASCVTFWD] = t;
			oprange[ASCVTFWS] = t;
			oprange[AUCVTFD] = t;
			oprange[AUCVTFS] = t;
			oprange[AUCVTFWD] = t;
			oprange[AUCVTFWS] = t;
			break;
		case ASYS:
			oprange[AAT] = t;
			oprange[ADC] = t;
			oprange[AIC] = t;
			oprange[ATLBI] = t;
			break;
		case ASYSL:
		case AHINT:
			break;
		case ADMB:
			oprange[ADSB] = t;
			oprange[AISB] = t;
			break;
		case AMRS:
		case AMSR:
			break;
		case ALDAR:
			oprange[ALDARW] = t;
		case ALDXR:
			oprange[ALDXRB] = t;
			oprange[ALDXRH] = t;
			oprange[ALDXRW] = t;
			break;
		case ALDAXR:
			oprange[ALDAXRW] = t;
			break;
		case ALDXP:
			oprange[ALDXPW] = t;
			break;
		case ASTLR:
			oprange[ASTLRW] = t;
			break;
		case ASTXR:
			oprange[ASTXRB] = t;
			oprange[ASTXRH] = t;
			oprange[ASTXRW] = t;
			break;
		case ASTLXR:
			oprange[ASTLXRW] = t;
			break;
		case ASTXP:
			oprange[ASTXPW] = t;
			break;
		case AAESD:
			oprange[AAESE] = t;
			oprange[AAESMC] = t;
			oprange[AAESIMC] = t;
			oprange[ASHA1H] = t;
			oprange[ASHA1SU1] = t;
			oprange[ASHA256SU0] = t;
			break;
		case ASHA1C:
			oprange[ASHA1P] = t;
			oprange[ASHA1M] = t;
			oprange[ASHA1SU0] = t;
			oprange[ASHA256H] = t;
			oprange[ASHA256H2] = t;
			oprange[ASHA256SU1] = t;
			break;
		case AUNDEF:
		case AUSEFIELD:
		case AFUNCDATA:
		case APCDATA:
		case ADUFFZERO:
		case ADUFFCOPY:
			break;
		}
	}
}

int
chipfloat7(Link *ctxt, float64 e)
{
	int n;
	ulong h1;
	uint32 l, h;
	uint64 ei;

	USED(ctxt);

	memmove(&ei, &e, 8);
	l = (int32)ei;
	h = (int32)(ei>>32);

	if(l != 0 || (h&0xffff) != 0)
		goto no;
	h1 = h & 0x7fc00000u;
	if(h1 != 0x40000000u && h1 != 0x3fc00000u)
		goto no;
	n = 0;

	// sign bit (a)
	if(h & 0x80000000u)
		n |= 1<<7;

	// exp sign bit (b)
	if(h1 == 0x3fc00000u)
		n |= 1<<6;

	// rest of exp and mantissa (cd-efgh)
	n |= (h >> 16) & 0x3f;

//print("match %.8lux %.8lux %d\n", l, h, n);
	return n;

no:
	return -1;
}

void
asmout(Link *ctxt, Prog *p, Optab *o, uint32 *out)
{
	uint32 o1, o2, o3, o4, o5;
	int32 v, hi;
	ulong u;
	vlong d;
	int r, s, rf, rt, ra, nzcv, cond, i, as;
	Mask *mask;
	Reloc *rel;
	static Prog *lastcase;

	o1 = 0;
	o2 = 0;
	o3 = 0;
	o4 = 0;
	o5 = 0;
	switch(o->type) {
	default:
		ctxt->diag("unknown asm %d", o->type);
		prasm(p);
		break;
	case 0: /* pseudo ops */
		break;
	case 1: /* op Rm,[Rn],Rd; default Rn=Rd -> op Rm<<0,[Rn,]Rd (shifted register) */
		o1 = oprrr(ctxt, p->as);
		rf = p->from.reg;
		rt = p->to.reg;
		r = p->reg;
		if(p->to.type == D_NONE)
			rt = REGZERO;
		if(r == NREG)
			r = rt;
		o1 |= ((rf << 16)) | ((r << 5)) | rt;
		break;
	case 2: /* add/sub $(uimm12|uimm24)[,R],R; cmp $(uimm12|uimm24),R */
		o1 = opirr(ctxt, p->as);
		rt = p->to.reg;
		if(p->to.type == D_NONE) {
			if(((o1 & Sbit)) == 0)
				ctxt->diag("ineffective ZR destination\n%P", p);
			rt = REGZERO;
		}
		r = p->reg;
		if(r == NREG)
			r = rt;
		v = regoff(ctxt, &p->from);
		o1 = oaddi(o1, v, r, rt);
		break;
	case 3: /* op R<<n[,R],R (shifted register) */
		o1 = oprrr(ctxt, p->as);
		o1 |= p->from.offset; /* includes reg, op, etc */
		rt = p->to.reg;
		if(p->to.type == D_NONE)
			rt = REGZERO;
		r = p->reg;
		if(p->as == AMVN || p->as == AMVNW)
			r = REGZERO;
		else
			if(r == NREG)
				r = rt;
		o1 |= ((r << 5)) | rt;
		break;
	case 4: /* mov $addcon, R; mov $recon, R; mov $racon, R */
		o1 = opirr(ctxt, p->as);
		rt = p->to.reg;
		r = o->param;
		if(r == 0)
			r = REGZERO;
		v = regoff(ctxt, &p->from);
		if(((v & 0xFFF000)) != 0) {
			v >>= 12;
			o1 |= 1 << 22; /* shift, by 12 */
		}
		o1 |= ((((v & 0xFFF)) << 10)) | ((r << 5)) | rt;
		break;
	case 5: /* b s; bl s */
		o1 = opbra(ctxt, p->as);
		if(p->to.sym == nil) {
			o1 |= brdist(ctxt, p, 0, 26, 2);
			break;
		}
		rel = addrel(ctxt->cursym);
		rel->off = ctxt->pc;
		rel->siz = 4;
		rel->sym = p->to.sym;
		rel->add = o1 | ((p->to.offset>>2) & 0x3ffffff);
		rel->type = R_CALLARM64;
		break;
	case 6: /* b ,O(R); bl ,O(R) */
		o1 = opbrr(ctxt, p->as);
		o1 |= p->to.reg << 5;
		rel = addrel(ctxt->cursym);
		rel->off = ctxt->pc;
		rel->siz = 0;
		rel->type = R_CALLIND;
		break;
	case 7: /* beq s */
		o1 = opbra(ctxt, p->as);
		o1 |= brdist(ctxt, p, 0, 19, 2) << 5;
		break;
	case 8: /* lsl $c,[R],R -> ubfm $(W-1)-c,$(-c MOD (W-1)),Rn,Rd */
		rt = p->to.reg;
		rf = p->reg;
		if(rf == NREG)
			rf = rt;
		v = p->from.offset;
		switch(p->as) {
		case AASR:
			o1 = opbfm(ctxt, ASBFM, v, 63, rf, rt);
			break;
		case AASRW:
			o1 = opbfm(ctxt, ASBFMW, v, 31, rf, rt);
			break;
		case ALSL:
			o1 = opbfm(ctxt, AUBFM, ((64 - v)) & 63, 63 - v, rf, rt);
			break;
		case ALSLW:
			o1 = opbfm(ctxt, AUBFMW, ((32 - v)) & 31, 31 - v, rf, rt);
			break;
		case ALSR:
			o1 = opbfm(ctxt, AUBFM, v, 63, rf, rt);
			break;
		case ALSRW:
			o1 = opbfm(ctxt, AUBFMW, v, 31, rf, rt);
			break;
		case AROR:
			o1 = opextr(ctxt, AEXTR, v, rf, rf, rt);
			break;
		case ARORW:
			o1 = opextr(ctxt, AEXTRW, v, rf, rf, rt);
			break;
		default:
			ctxt->diag("bad shift $con\n%P", ctxt->curp);
			break;
		}
		break;
	case 9: /* lsl Rm,[Rn],Rd -> lslv Rm, Rn, Rd */
		o1 = oprrr(ctxt, p->as);
		r = p->reg;
		if(r == NREG)
			r = p->to.reg;
		o1 |= ((p->from.reg << 16)) | ((r << 5)) | p->to.reg;
		break;
	case 10: /* brk/hvc/.../svc [$con] */
		o1 = opimm(ctxt, p->as);
		if(p->to.type != D_NONE)
			o1 |= ((p->to.offset & 0xffff)) << 5;
		break;
	case 11: /* dword */
		aclass(ctxt, &p->to);
		o1 = ctxt->instoffset;
		o2 = ctxt->instoffset >> 32;
		if(p->to.sym != nil) {
			rel = addrel(ctxt->cursym);
			rel->off = ctxt->pc;
			rel->siz = 8;
			rel->sym = p->to.sym;
			rel->add = p->to.offset;
			rel->type = R_ADDR;
			o1 = o2 = 0;
		}
		break;
	case 12: /* movT $vcon, reg */
		o1 = omovlit(ctxt, p->as, p, &p->from, p->to.reg);
		break;
	case 13: /* addop $vcon, [R], R (64 bit literal); cmp $lcon,R -> addop $lcon,R, ZR */
		o1 = omovlit(ctxt, AMOV, p, &p->from, REGTMP);
		if(!o1)
			break;
		rt = p->to.reg;
		if(p->to.type == D_NONE)
			rt = REGZERO;
		r = p->reg;
		if(r == NREG)
			r = rt;
		if(p->to.type != D_NONE && ((p->to.reg == REGSP || r == REGSP))) {
			o2 = opxrrr(ctxt, p->as);
			o2 |= REGTMP << 16;
			o2 |= LSL0_64;
		} else {
			o2 = oprrr(ctxt, p->as);
			o2 |= REGTMP << 16; /* shift is 0 */
		}
		o2 |= r << 5;
		o2 |= rt;
		break;
	case 14: /* word */
		if(aclass(ctxt, &p->to) == C_ADDR)
			ctxt->diag("address constant needs DWORD\n%P", p);
		o1 = ctxt->instoffset;
		if(p->to.sym != nil) {
			// This case happens with words generated
			// in the PC stream as part of the literal pool.
			rel = addrel(ctxt->cursym);
			rel->off = ctxt->pc;
			rel->siz = 4;
			rel->sym = p->to.sym;
			rel->add = p->to.offset;
			rel->type = R_ADDR;
			o1 = 0;
		}
		break;
	case 15: /* mul/mneg/umulh/umull r,[r,]r; madd/msub Rm,Rn,Ra,Rd */
		o1 = oprrr(ctxt, p->as);
		rf = p->from.reg;
		rt = p->to.reg;
		if(p->from3.type == D_REG) {
			r = p->from3.reg;
			ra = p->reg;
			if(ra == NREG)
				ra = REGZERO;
		} else {
			r = p->reg;
			if(r == NREG)
				r = rt;
			ra = REGZERO;
		}
		o1 |= ((rf << 16)) | ((ra << 10)) | ((r << 5)) | rt;
		break;
	case 16: /* XremY R[,R],R -> XdivY; XmsubY */
		o1 = oprrr(ctxt, p->as);
		rf = p->from.reg;
		rt = p->to.reg;
		r = p->reg;
		if(r == NREG)
			r = rt;
		o1 |= ((rf << 16)) | ((r << 5)) | REGTMP;
		o2 = oprrr(ctxt, AMSUBW);
		o2 |= o1 & ((1 << 31u)); /* same size */
		o2 |= ((rf << 16)) | ((r << 10)) | ((REGTMP << 5)) | rt;
		break;
	case 17: /* op Rm,[Rn],Rd; default Rn=ZR */
		o1 = oprrr(ctxt, p->as);
		rf = p->from.reg;
		rt = p->to.reg;
		r = p->reg;
		if(p->to.type == D_NONE)
			rt = REGZERO;
		if(r == NREG)
			r = REGZERO;
		o1 |= ((rf << 16)) | ((r << 5)) | rt;
		break;
	case 18: /* csel cond,Rn,Rm,Rd; cinc/cinv/cneg cond,Rn,Rd; cset cond,Rd */
		o1 = oprrr(ctxt, p->as);
		cond = p->from.reg;
		r = p->reg;
		if(r != NREG) {
			if(p->from3.type == D_NONE) {
				/* CINC/CINV/CNEG */
				rf = r;
				cond ^= 1;
			} else
				rf = p->from3.reg; /* CSEL */
		} else {
			/* CSET */
			if(p->from3.type != D_NONE)
				ctxt->diag("invalid combination\n%P", p);
			r = rf = REGZERO;
			cond ^= 1;
		}
		rt = p->to.reg;
		o1 |= ((r << 16)) | ((cond << 12)) | ((rf << 5)) | rt;
		break;
	case 19: /* CCMN cond, (Rm|uimm5),Rn, uimm4 -> ccmn Rn,Rm,uimm4,cond */
		nzcv = p->to.offset;
		cond = p->from.reg;
		if(p->from3.type == D_REG) {
			o1 = oprrr(ctxt, p->as);
			rf = p->from3.reg; /* Rm */
		} else {
			o1 = opirr(ctxt, p->as);
			rf = p->from3.offset & 0x1F;
		}
		o1 |= ((rf << 16)) | ((cond << 12)) | ((p->reg << 5)) | nzcv;
		break;
	case 20: /* movT R,O(R) -> strT */
		v = regoff(ctxt, &p->to);
		r = p->to.reg;
		if(r == NREG)
			r = o->param;
		if(v < 0) { /* unscaled 9-bit signed */
			o1 = olsr9s(ctxt, opstr9(ctxt, p->as), v, r, p->from.reg);
		} else {
			v = offsetshift(ctxt, v, o->a3);
			o1 = olsr12u(ctxt, opstr12(ctxt, p->as), v, r, p->from.reg);
		}
		break;
	case 21: /* movT O(R),R -> ldrT */
		v = regoff(ctxt, &p->from);
		r = p->from.reg;
		if(r == NREG)
			r = o->param;
		if(v < 0) { /* unscaled 9-bit signed */
			o1 = olsr9s(ctxt, opldr9(ctxt, p->as), v, r, p->to.reg);
		} else {
			v = offsetshift(ctxt, v, o->a1);
			//print("offset=%lld v=%ld a1=%d\n", instoffset, v, o->a1);
			o1 = olsr12u(ctxt, opldr12(ctxt, p->as), v, r, p->to.reg);
		}
		break;
	case 22: /* movT (R)O!,R; movT O(R)!, R -> ldrT */
		v = p->from.offset;
		if(v < -256 || v > 255)
			ctxt->diag("offset out of range\n%P", p);
		o1 = opldrpp(ctxt, p->as);
		if(p->from.type == D_XPOST)
			o1 |= 1 << 10;
		else
			o1 |= 3 << 10;
		o1 |= ((((v & 0x1FF)) << 12)) | ((p->from.reg << 5)) | p->to.reg;
		break;
	case 23: /* movT R,(R)O!; movT O(R)!, R -> strT */
		v = p->to.offset;
		if(v < -256 || v > 255)
			ctxt->diag("offset out of range\n%P", p);
		o1 = LD2STR(opldrpp(ctxt, p->as));
		if(p->to.type == D_XPOST)
			o1 |= 1 << 10;
		else
			o1 |= 3 << 10;
		o1 |= ((((v & 0x1FF)) << 12)) | ((p->to.reg << 5)) | p->from.reg;
		break;
	case 24: /* mov/mvn Rs,Rd -> add $0,Rs,Rd or orr Rs,ZR,Rd */
		rf = p->from.reg;
		rt = p->to.reg;
		s = rf == REGSP || rt == REGSP;
		if(p->as == AMVN || p->as == AMVNW) {
			if(s)
				ctxt->diag("illegal SP reference\n%P", p);
			o1 = oprrr(ctxt, p->as);
			o1 |= ((rf << 16)) | ((REGZERO << 5)) | rt;
		} else
			if(s) {
				o1 = opirr(ctxt, p->as);
				o1 |= ((rf << 5)) | rt;
			} else {
				o1 = oprrr(ctxt, p->as);
				o1 |= ((rf << 16)) | ((REGZERO << 5)) | rt;
			}
		break;
	case 25: /* negX Rs, Rd -> subX Rs<<0, ZR, Rd */
		o1 = oprrr(ctxt, p->as);
		rf = p->from.reg;
		rt = p->to.reg;
		o1 |= ((rf << 16)) | ((REGZERO << 5)) | rt;
		break;
	case 26: /* negX Rm<<s, Rd -> subX Rm<<s, ZR, Rd */
		o1 = oprrr(ctxt, p->as);
		o1 |= p->from.offset; /* includes reg, op, etc */
		rt = p->to.reg;
		o1 |= ((REGZERO << 5)) | rt;
		break;
	case 27: /* op Rm<<n[,Rn],Rd (extended register) */
		o1 = opxrrr(ctxt, p->as);
		if(p->from.type == D_EXTREG)
			o1 |= p->from.offset; /* includes reg, op, etc */
		else
			o1 |= p->from.reg << 16;
		rt = p->to.reg;
		if(p->to.type == D_NONE)
			rt = REGZERO;
		r = p->reg;
		if(r == NREG)
			r = rt;
		o1 |= ((r << 5)) | rt;
		break;
	case 28: /* logop $vcon, [R], R (64 bit literal) */
		o1 = omovlit(ctxt, AMOV, p, &p->from, REGTMP);
		if(!o1)
			break;
		r = p->reg;
		if(r == NREG)
			r = p->to.reg;
		o2 = oprrr(ctxt, p->as);
		o2 |= REGTMP << 16; /* shift is 0 */
		o2 |= r << 5;
		o2 |= p->to.reg;
		break;
	case 29: /* op Rn, Rd */
		o1 = oprrr(ctxt, p->as);
		o1 |= p->from.reg << 5 | p->to.reg;
		break;
	case 30: /* movT R,L(R) -> strT */
		s = movesize(o->as);
		if(s < 0)
			ctxt->diag("unexpected long move, op %A tab %A\n%P", p->as, o->as, p);
		v = regoff(ctxt, &p->to);
		if(v < 0)
			ctxt->diag("negative large offset\n%P", p);
		if(((v & ((((1 << s)) - 1)))) != 0)
			ctxt->diag("misaligned offset\n%P", p);
		hi = v - ((v & ((0xFFF << s))));
		if(((hi & 0xFFF)) != 0)
			ctxt->diag("internal: miscalculated offset %ld [%d]\n%P", v, s, p);
		//fprint(2, "v=%ld (%#lux) s=%d hi=%ld (%#lux) v'=%ld (%#lux)\n", v, v, s, hi, hi, ((v-hi)>>s)&0xFFF, ((v-hi)>>s)&0xFFF);
		r = p->to.reg;
		if(r == NREG)
			r = o->param;
		o1 = oaddi(opirr(ctxt, AADD), hi, r, REGTMP);
		o2 = olsr12u(ctxt, opstr12(ctxt, p->as), ((((v - hi)) >> s)) & 0xFFF, REGTMP, p->from.reg);
		break;
	case 31: /* movT L(R), R -> ldrT */
		s = movesize(o->as);
		if(s < 0)
			ctxt->diag("unexpected long move, op %A tab %A\n%P", p->as, o->as, p);
		v = regoff(ctxt, &p->from);
		if(v < 0)
			ctxt->diag("negative large offset\n%P", p);
		if(((v & ((((1 << s)) - 1)))) != 0)
			ctxt->diag("misaligned offset\n%P", p);
		hi = v - ((v & ((0xFFF << s))));
		if(((hi & 0xFFF)) != 0)
			ctxt->diag("internal: miscalculated offset %ld [%d]\n%P", v, s, p);
		//fprint(2, "v=%ld (%#lux) s=%d hi=%ld (%#lux) v'=%ld (%#lux)\n", v, v, s, hi, hi, ((v-hi)>>s)&0xFFF, ((v-hi)>>s)&0xFFF);
		r = p->from.reg;
		if(r == NREG)
			r = o->param;
		o1 = oaddi(opirr(ctxt, AADD), hi, r, REGTMP);
		o2 = olsr12u(ctxt, opldr12(ctxt, p->as), ((((v - hi)) >> s)) & 0xFFF, REGTMP, p->to.reg);
		break;
	case 32: /* mov $con, R -> movz/movn */
		r = 32;
		if(p->as == AMOV)
			r = 64;
		d = p->from.offset;
		s = movcon(d);
		if(s < 0 || s >= r) {
			d = ~d;
			s = movcon(d);
			if(s < 0 || s >= r)
				ctxt->diag("impossible move wide: %#llux\n%P", p->from.offset, p);
			if(p->as == AMOV)
				o1 = opirr(ctxt, AMOVN);
			else
				o1 = opirr(ctxt, AMOVNW);
		} else {
			if(p->as == AMOV)
				o1 = opirr(ctxt, AMOVZ);
			else
				o1 = opirr(ctxt, AMOVZW);
		}
		rt = p->to.reg;
		o1 |= ((((((d >> ((s * 16)))) & 0xFFFF)) << 5)) | ((((s & 3)) << 21)) | rt;
		break;
	case 33: /* movk $uimm16 << pos */
		o1 = opirr(ctxt, p->as);
		d = p->from.offset;
		if(((d >> 16)) != 0)
			ctxt->diag("requires uimm16\n%P", p);
		s = 0;
		if(p->from3.type != D_NONE) {
			if(p->from3.type != D_CONST)
				ctxt->diag("missing bit position\n%P", p);
			s = p->from3.offset/16;
			if(((s*16 & 0xF)) != 0 || s >= 4 || ((o1 & S64)) == 0 && s >= 2)
				ctxt->diag("illegal bit position\n%P", p);
		}
		rt = p->to.reg;
		o1 |= ((((d & 0xFFFF)) << 5)) | ((((s & 3)) << 21)) | rt;
		break;
	case 34: /* mov $lacon,R */
		o1 = omovlit(ctxt, AMOV, p, &p->from, REGTMP);
		if(!o1)
			break;
		o2 = opxrrr(ctxt, AADD);
		o2 |= REGTMP << 16;
		o2 |= LSL0_64;
		r = p->from.reg;
		if(r == NREG)
			r = o->param;
		o2 |= r << 5;
		o2 |= p->to.reg;
		break;
	case 35: /* mov SPR,R -> mrs */
		o1 = oprrr(ctxt, AMRS);
		v = p->from.offset;
		if(((o1 & ((v & ~((3 << 19)))))) != 0)
			ctxt->diag("MRS register value overlap\n%P", p);
		o1 |= v;
		o1 |= p->to.reg;
		break;
	case 36: /* mov R,SPR */
		o1 = oprrr(ctxt, AMSR);
		v = p->to.offset;
		if(((o1 & ((v & ~((3 << 19)))))) != 0)
			ctxt->diag("MSR register value overlap\n%P", p);
		o1 |= v;
		o1 |= p->from.reg;
		break;
	case 37: /* mov $con,PSTATEfield -> MSR [immediate] */
		if(((p->from.offset & ~(uvlong)0xF)) != 0)
			ctxt->diag("illegal immediate for PSTATE field\n%P", p);
		o1 = opirr(ctxt, AMSR);
		o1 |= ((p->from.offset & 0xF)) << 8; /* Crm */
		v = 0;
		for(i = 0; i < nelem(pstatefield); i++)
			if(pstatefield[i].a == p->to.offset) {
				v = pstatefield[i].b;
				break;
			}
		if(v == 0)
			ctxt->diag("illegal PSTATE field for immediate move\n%P", p);
		o1 |= v;
		break;
	case 38: /* clrex [$imm] */
		o1 = opimm(ctxt, p->as);
		if(p->to.type == D_NONE)
			o1 |= 0xF << 8;
		else
			o1 |= ((p->to.offset & 0xF)) << 8;
		break;
	case 39: /* cbz R, rel */
		o1 = opirr(ctxt, p->as);
		o1 |= p->from.reg;
		o1 |= brdist(ctxt, p, 0, 19, 2) << 5;
		break;
	case 40: /* tbz */
		o1 = opirr(ctxt, p->as);
		v = p->from.offset;
		if(v < 0 || v > 63)
			ctxt->diag("illegal bit number\n%P", p);
		o1 |= ((((v & 0x20)) << ((31 - 5)))) | ((((v & 0x1F)) << 19));
		o1 |= brdist(ctxt, p, 0, 14, 2) << 5;
		o1 |= p->reg;
		break;
	case 41: /* eret, nop, others with no operands */
		o1 = op0(ctxt, p->as);
		break;
	case 42: /* bfm R,r,s,R */
		o1 = opbfm(ctxt, p->as, p->from.offset, p->from3.offset, p->reg, p->to.reg);
		break;
	case 43: /* bfm aliases */
		r = p->from.offset;
		s = p->from3.offset;
		rf = p->reg;
		rt = p->to.reg;
		if(rf == NREG)
			rf = rt;
		switch(p->as) {
		case ABFI:
			o1 = opbfm(ctxt, ABFM, 64 - r, s - 1, rf, rt);
			break;
		case ABFIW:
			o1 = opbfm(ctxt, ABFMW, 32 - r, s - 1, rf, rt);
			break;
		case ABFXIL:
			o1 = opbfm(ctxt, ABFM, r, r + s - 1, rf, rt);
			break;
		case ABFXILW:
			o1 = opbfm(ctxt, ABFMW, r, r + s - 1, rf, rt);
			break;
		case ASBFIZ:
			o1 = opbfm(ctxt, ASBFM, 64 - r, s - 1, rf, rt);
			break;
		case ASBFIZW:
			o1 = opbfm(ctxt, ASBFMW, 32 - r, s - 1, rf, rt);
			break;
		case ASBFX:
			o1 = opbfm(ctxt, ASBFM, r, r + s - 1, rf, rt);
			break;
		case ASBFXW:
			o1 = opbfm(ctxt, ASBFMW, r, r + s - 1, rf, rt);
			break;
		case AUBFIZ:
			o1 = opbfm(ctxt, AUBFM, 64 - r, s - 1, rf, rt);
			break;
		case AUBFIZW:
			o1 = opbfm(ctxt, AUBFMW, 32 - r, s - 1, rf, rt);
			break;
		case AUBFX:
			o1 = opbfm(ctxt, AUBFM, r, r + s - 1, rf, rt);
			break;
		case AUBFXW:
			o1 = opbfm(ctxt, AUBFMW, r, r + s - 1, rf, rt);
			break;
		default:
			ctxt->diag("bad bfm alias\n%P", ctxt->curp);
			break;
		}
		break;
	case 44: /* extr $b, Rn, Rm, Rd */
		o1 = opextr(ctxt, p->as, p->from.offset, p->from3.reg, p->reg, p->to.reg);
		break;
	case 45: /* sxt/uxt[bhw] R,R; movT R,R -> sxtT R,R */
		rf = p->from.reg;
		rt = p->to.reg;
		as = p->as;
		if(rf == REGZERO)
			as = AMOVWU; /* clearer in disassembly */
		switch(as) {
		case AMOVB:
		case ASXTB:
			o1 = opbfm(ctxt, ASBFM, 0, 7, rf, rt);
			break;
		case AMOVH:
		case ASXTH:
			o1 = opbfm(ctxt, ASBFM, 0, 15, rf, rt);
			break;
		case AMOVW:
		case ASXTW:
			o1 = opbfm(ctxt, ASBFM, 0, 31, rf, rt);
			break;
		case AMOVBU:
		case AUXTB:
			o1 = opbfm(ctxt, AUBFM, 0, 7, rf, rt);
			break;
		case AMOVHU:
		case AUXTH:
			o1 = opbfm(ctxt, AUBFM, 0, 15, rf, rt);
			break;
		case AMOVWU:
			o1 = oprrr(ctxt, as) | ((rf << 16)) | ((REGZERO << 5)) | rt;
			break;
		case AUXTW:
			o1 = opbfm(ctxt, AUBFM, 0, 31, rf, rt);
			break;
		case ASXTBW:
			o1 = opbfm(ctxt, ASBFMW, 0, 7, rf, rt);
			break;
		case ASXTHW:
			o1 = opbfm(ctxt, ASBFMW, 0, 15, rf, rt);
			break;
		case AUXTBW:
			o1 = opbfm(ctxt, AUBFMW, 0, 7, rf, rt);
			break;
		case AUXTHW:
			o1 = opbfm(ctxt, AUBFMW, 0, 15, rf, rt);
			break;
		default:
			ctxt->diag("bad sxt %A", as);
			break;
		}
		break;
	case 46: /* cls */
		o1 = opbit(ctxt, p->as);
		o1 |= p->from.reg << 5;
		o1 |= p->to.reg;
		break;
	case 47: /* movT R,V(R) -> strT (huge offset) */
		o1 = omovlit(ctxt, AMOVW, p, &p->to, REGTMP);
		if(!o1)
			break;
		r = p->to.reg;
		if(r == NREG)
			r = o->param;
		o2 = olsxrr(ctxt, p->as, REGTMP, r, p->from.reg);
		break;
	case 48: /* movT V(R), R -> ldrT (huge offset) */
		o1 = omovlit(ctxt, AMOVW, p, &p->from, REGTMP);
		if(!o1)
			break;
		r = p->from.reg;
		if(r == NREG)
			r = o->param;
		o2 = olsxrr(ctxt, p->as, REGTMP, r, p->to.reg);
		break;
	case 50: /* sys/sysl */
		o1 = opirr(ctxt, p->as);
		if(((p->from.offset & ~SYSARG4(0x7, 0xF, 0xF, 0x7))) != 0)
			ctxt->diag("illegal SYS argument\n%P", p);
		o1 |= p->from.offset;
		if(p->to.type == D_REG)
			o1 |= p->to.reg;
		else
			if(p->reg != NREG)
				o1 |= p->reg;
			else
				o1 |= 0x1F;
		break;
	case 51: /* dmb */
		o1 = opirr(ctxt, p->as);
		if(p->from.type == D_CONST)
			o1 |= ((p->from.offset & 0xF)) << 8;
		break;
	case 52: /* hint */
		o1 = opirr(ctxt, p->as);
		o1 |= ((p->from.offset & 0x7F)) << 5;
		break;
	case 53: /* and/or/eor/bic/... $bimmN, Rn, Rd -> op (N,r,s), Rn, Rd */
		as = p->as;
		rt = p->to.reg;
		r = p->reg;
		if(r == NREG)
			r = rt;
		if(as == AMOV) {
			as = AORR;
			r = REGZERO;
		} else
			if(as == AMOVW) {
				as = AORRW;
				r = REGZERO;
			}
		o1 = opirr(ctxt, as);
		if(o1 & S64)
			s = 64;
		else
			s = 32;
		mask = findmask(p->from.offset);
		if(mask == nil)
			mask = findmask(p->from.offset | ((p->from.offset << 32)));
		if(mask != nil) {
			o1 |= ((((mask->r & ((s - 1)))) << 16)) | ((((((mask->s - 1)) & ((s - 1)))) << 10));
			if(s == 64) {
				if(mask->e == 64 && (((uvlong)p->from.offset >> 32)) != 0)
					o1 |= 1 << 22;
			} else {
				u = (uvlong)p->from.offset >> 32;
				if(u != 0 && u != 0xFFFFFFFF)
					ctxt->diag("mask needs 64 bits %#llux\n%P", p->from.offset, p);
			}
		} else
			ctxt->diag("invalid mask %#llux\n%P", p->from.offset, p); /* probably shouldn't happen */
		o1 |= ((r << 5)) | rt;
		break;
	case 54: /* floating point arith */
		o1 = oprrr(ctxt, p->as);
		if(p->from.type == D_FCONST) {
			rf = chipfloat7(ctxt, p->from.u.dval);
			if(rf < 0 || 1) {
				ctxt->diag("invalid floating-point immediate\n%P", p);
				rf = 0;
			}
			rf |= ((1 << 3));
		} else
			rf = p->from.reg;
		rt = p->to.reg;
		r = p->reg;
		if(((o1 & ((0x1F << 24)))) == ((0x1E << 24)) && ((o1 & ((1 << 11)))) == 0) { /* monadic */
			r = rf;
			rf = 0;
		} else
			if(r == NREG)
				r = rt;
		o1 |= ((rf << 16)) | ((r << 5)) | rt;
		break;
	case 56: /* floating point compare */
		o1 = oprrr(ctxt, p->as);
		if(p->from.type == D_FCONST) {
			o1 |= 8; /* zero */
			rf = 0;
		} else
			rf = p->from.reg;
		rt = p->reg;
		o1 |= rf << 16 | rt << 5;
		break;
	case 57: /* floating point conditional compare */
		o1 = oprrr(ctxt, p->as);
		cond = p->from.reg;
		nzcv = p->to.offset;
		if(nzcv & ~0xF)
			ctxt->diag("implausible condition\n%P", p);
		rf = p->reg;
		if(p->from3.type != D_FREG)
			ctxt->diag("illegal FCCMP\n%P", p);
		rt = p->from3.reg;
		o1 |= rf << 16 | cond << 12 | rt << 5 | nzcv;
		break;
	case 58: /* ldar/ldxr/ldaxr */
		o1 = opload(ctxt, p->as);
		o1 |= 0x1F << 16;
		o1 |= p->from.reg << 5;
		if(p->reg != NREG)
			o1 |= p->reg << 10;
		else
			o1 |= 0x1F << 10;
		o1 |= p->to.reg;
		break;
	case 59: /* stxr/stlxr */
		o1 = opstore(ctxt, p->as);
		o1 |= p->to3.reg << 16;
		if(p->from3.type != D_NONE)
			o1 |= p->from3.reg << 10;
		else
			o1 |= 0x1F << 10;
		o1 |= p->to.reg << 5;
		o1 |= p->from.reg;
		break;
	case 60: /* adrp label,r */
		d = brdist(ctxt, p, 12, 21, 0);
		o1 = ADR(1, d, p->to.reg);
		break;
	case 61: /* adr label, r */
		d = brdist(ctxt, p, 0, 21, 0);
		o1 = ADR(0, d, p->to.reg);
		break;
	case 62: /* case Rv, Rt -> adr tab, Rt; movw Rt[R<<2], Rl; add Rt, Rl; br (Rl) */
		o1 = ADR(0, 4 * 4, p->to.reg); /* adr 4(pc), Rt */
		o2 = ((2 << 30)) | ((7 << 27)) | ((2 << 22)) | ((1 << 21)) | ((3 << 13)) | ((1 << 12)) | ((2 << 10)) | ((p->from.reg << 16)) | ((p->to.reg << 5)) | REGTMP; /* movw Rt[Rv<<2], REGTMP */
		o3 = oprrr(ctxt, AADD) | ((p->to.reg << 16)) | ((REGTMP << 5)) | REGTMP; /* add Rt, REGTMP */
		o4 = ((0x6b << 25)) | ((0x1F << 16)) | ((REGTMP << 5)); /* br (REGTMP) */
		lastcase = p;
		break;
	case 63: /* bcase */
		if(lastcase == nil) {
			ctxt->diag("missing CASE\n%P", p);
			break;
		}
		if(p->pcond != nil) {
			o1 = p->pcond->pc - ((lastcase->pc + 4 * 4));
			ctxt->diag("FIXME: some relocation needed in bcase\n%P", p);
		}
		break;
	/* reloc ops */
	case 64: /* movT R,addr */
		o1 = omovlit(ctxt, AMOV, p, &p->to, REGTMP);
		if(!o1)
			break;
		o2 = olsr12u(ctxt, opstr12(ctxt,p->as), 0, REGTMP, p->from.reg);
		break;
	case 65: /* movT addr,R */
		o1 = omovlit(ctxt, AMOV, p, &p->from, REGTMP);
		if(!o1)
			break;
		o2 = olsr12u(ctxt, opldr12(ctxt, p->as), 0, REGTMP, p->to.reg);
		break;
	case 90:
		// This is supposed to be something that stops execution.
		// It's not supposed to be reached, ever, but if it is, we'd
		// like to be able to tell how we got there.  Assemble as
		// 0xbea71700 which is guaranteed to raise undefined instruction
		// exception.
		o1 = 0xbea71700u;
		break;
	}
	out[0] = o1;
	out[1] = o2;
	out[2] = o3;
	out[3] = o4;
	out[4] = o5;
	return;
}

/*
 * basic Rm op Rn -> Rd (using shifted register with 0)
 * also op Rn -> Rt
 * also Rm*Rn op Ra -> Rd
 */
static uint32
oprrr(Link *ctxt, int a)
{
	switch(a) {
	case AADC:
		return S64 | 0 << 30 | 0 << 29 | 0xd0 << 21 | 0 << 10;
	case AADCW:
		return S32 | 0 << 30 | 0 << 29 | 0xd0 << 21 | 0 << 10;
	case AADCS:
		return S64 | 0 << 30 | 1 << 29 | 0xd0 << 21 | 0 << 10;
	case AADCSW:
		return S32 | 0 << 30 | 1 << 29 | 0xd0 << 21 | 0 << 10;
	case ANGC:
	case ASBC:
		return S64 | 1 << 30 | 0 << 29 | 0xd0 << 21 | 0 << 10;
	case ANGCS:
	case ASBCS:
		return S64 | 1 << 30 | 1 << 29 | 0xd0 << 21 | 0 << 10;
	case ANGCW:
	case ASBCW:
		return S32 | 1 << 30 | 0 << 29 | 0xd0 << 21 | 0 << 10;
	case ANGCSW:
	case ASBCSW:
		return S32 | 1 << 30 | 1 << 29 | 0xd0 << 21 | 0 << 10;
	case AADD:
		return S64 | 0 << 30 | 0 << 29 | 0x0b << 24 | 0 << 22 | 0 << 21 | 0 << 10;
	case AADDW:
		return S32 | 0 << 30 | 0 << 29 | 0x0b << 24 | 0 << 22 | 0 << 21 | 0 << 10;
	case ACMN:
	case AADDS:
		return S64 | 0 << 30 | 1 << 29 | 0x0b << 24 | 0 << 22 | 0 << 21 | 0 << 10;
	case ACMNW:
	case AADDSW:
		return S32 | 0 << 30 | 1 << 29 | 0x0b << 24 | 0 << 22 | 0 << 21 | 0 << 10;
	case ASUB:
		return S64 | 1 << 30 | 0 << 29 | 0x0b << 24 | 0 << 22 | 0 << 21 | 0 << 10;
	case ASUBW:
		return S32 | 1 << 30 | 0 << 29 | 0x0b << 24 | 0 << 22 | 0 << 21 | 0 << 10;
	case ACMP:
	case ASUBS:
		return S64 | 1 << 30 | 1 << 29 | 0x0b << 24 | 0 << 22 | 0 << 21 | 0 << 10;
	case ACMPW:
	case ASUBSW:
		return S32 | 1 << 30 | 1 << 29 | 0x0b << 24 | 0 << 22 | 0 << 21 | 0 << 10;
	case AAND:
		return S64 | 0 << 29 | 0xA << 24;
	case AANDW:
		return S32 | 0 << 29 | 0xA << 24;
	case AMOV:
	case AORR:
		return S64 | 1 << 29 | 0xA << 24;
	//	case AMOVW:
	case AMOVWU:
	case AORRW:
		return S32 | 1 << 29 | 0xA << 24;
	case AEOR:
		return S64 | 2 << 29 | 0xA << 24;
	case AEORW:
		return S32 | 2 << 29 | 0xA << 24;
	case AANDS:
		return S64 | 3 << 29 | 0xA << 24;
	case AANDSW:
		return S32 | 3 << 29 | 0xA << 24;
	case ABIC:
		return S64 | 0 << 29 | 0xA << 24 | 1 << 21;
	case ABICW:
		return S32 | 0 << 29 | 0xA << 24 | 1 << 21;
	case ABICS:
		return S64 | 3 << 29 | 0xA << 24 | 1 << 21;
	case ABICSW:
		return S32 | 3 << 29 | 0xA << 24 | 1 << 21;
	case AEON:
		return S64 | 2 << 29 | 0xA << 24 | 1 << 21;
	case AEONW:
		return S32 | 2 << 29 | 0xA << 24 | 1 << 21;
	case AMVN:
	case AORN:
		return S64 | 1 << 29 | 0xA << 24 | 1 << 21;
	case AMVNW:
	case AORNW:
		return S32 | 1 << 29 | 0xA << 24 | 1 << 21;
	case AASR:
		return S64 | OPDP2(10); /* also ASRV */
	case AASRW:
		return S32 | OPDP2(10);
	case ALSL:
		return S64 | OPDP2(8);
	case ALSLW:
		return S32 | OPDP2(8);
	case ALSR:
		return S64 | OPDP2(9);
	case ALSRW:
		return S32 | OPDP2(9);
	case AROR:
		return S64 | OPDP2(11);
	case ARORW:
		return S32 | OPDP2(11);
	case ACCMN:
		return S64 | 0 << 30 | 1 << 29 | 0xD2 << 21 | 0 << 11 | 0 << 10 | 0 << 4; /* cond<<12 | nzcv<<0 */
	case ACCMNW:
		return S32 | 0 << 30 | 1 << 29 | 0xD2 << 21 | 0 << 11 | 0 << 10 | 0 << 4;
	case ACCMP:
		return S64 | 1 << 30 | 1 << 29 | 0xD2 << 21 | 0 << 11 | 0 << 10 | 0 << 4; /* imm5<<16 | cond<<12 | nzcv<<0 */
	case ACCMPW:
		return S32 | 1 << 30 | 1 << 29 | 0xD2 << 21 | 0 << 11 | 0 << 10 | 0 << 4;
	case ACRC32B:
		return S32 | OPDP2(16);
	case ACRC32H:
		return S32 | OPDP2(17);
	case ACRC32W:
		return S32 | OPDP2(18);
	case ACRC32X:
		return S64 | OPDP2(19);
	case ACRC32CB:
		return S32 | OPDP2(20);
	case ACRC32CH:
		return S32 | OPDP2(21);
	case ACRC32CW:
		return S32 | OPDP2(22);
	case ACRC32CX:
		return S64 | OPDP2(23);
	case ACSEL:
		return S64 | 0 << 30 | 0 << 29 | 0xD4 << 21 | 0 << 11 | 0 << 10;
	case ACSELW:
		return S32 | 0 << 30 | 0 << 29 | 0xD4 << 21 | 0 << 11 | 0 << 10;
	case ACSET:
		return S64 | 0 << 30 | 0 << 29 | 0xD4 << 21 | 0 << 11 | 1 << 10;
	case ACSETW:
		return S32 | 0 << 30 | 0 << 29 | 0xD4 << 21 | 0 << 11 | 1 << 10;
	case ACSETM:
		return S64 | 1 << 30 | 0 << 29 | 0xD4 << 21 | 0 << 11 | 0 << 10;
	case ACSETMW:
		return S32 | 1 << 30 | 0 << 29 | 0xD4 << 21 | 0 << 11 | 0 << 10;
	case ACINC:
	case ACSINC:
		return S64 | 0 << 30 | 0 << 29 | 0xD4 << 21 | 0 << 11 | 1 << 10;
	case ACINCW:
	case ACSINCW:
		return S32 | 0 << 30 | 0 << 29 | 0xD4 << 21 | 0 << 11 | 1 << 10;
	case ACINV:
	case ACSINV:
		return S64 | 1 << 30 | 0 << 29 | 0xD4 << 21 | 0 << 11 | 0 << 10;
	case ACINVW:
	case ACSINVW:
		return S32 | 1 << 30 | 0 << 29 | 0xD4 << 21 | 0 << 11 | 0 << 10;
	case ACNEG:
	case ACSNEG:
		return S64 | 1 << 30 | 0 << 29 | 0xD4 << 21 | 0 << 11 | 1 << 10;
	case ACNEGW:
	case ACSNEGW:
		return S32 | 1 << 30 | 0 << 29 | 0xD4 << 21 | 0 << 11 | 1 << 10;
	case AMUL:
	case AMADD:
		return S64 | 0 << 29 | 0x1B << 24 | 0 << 21 | 0 << 15;
	case AMULW:
	case AMADDW:
		return S32 | 0 << 29 | 0x1B << 24 | 0 << 21 | 0 << 15;
	case AMNEG:
	case AMSUB:
		return S64 | 0 << 29 | 0x1B << 24 | 0 << 21 | 1 << 15;
	case AMNEGW:
	case AMSUBW:
		return S32 | 0 << 29 | 0x1B << 24 | 0 << 21 | 1 << 15;
	case AMRS:
		return SYSOP(1, 2, 0, 0, 0, 0, 0);
	case AMSR:
		return SYSOP(0, 2, 0, 0, 0, 0, 0);
	case ANEG:
		return S64 | 1 << 30 | 0 << 29 | 0xB << 24 | 0 << 21;
	case ANEGW:
		return S32 | 1 << 30 | 0 << 29 | 0xB << 24 | 0 << 21;
	case ANEGS:
		return S64 | 1 << 30 | 1 << 29 | 0xB << 24 | 0 << 21;
	case ANEGSW:
		return S32 | 1 << 30 | 1 << 29 | 0xB << 24 | 0 << 21;
	case AREM:
	case ASDIV:
		return S64 | OPDP2(3);
	case AREMW:
	case ASDIVW:
		return S32 | OPDP2(3);
	case ASMULL:
	case ASMADDL:
		return OPDP3(1, 0, 1, 0);
	case ASMNEGL:
	case ASMSUBL:
		return OPDP3(1, 0, 1, 1);
	case ASMULH:
		return OPDP3(1, 0, 2, 0);
	case AUMULL:
	case AUMADDL:
		return OPDP3(1, 0, 5, 0);
	case AUMNEGL:
	case AUMSUBL:
		return OPDP3(1, 0, 5, 1);
	case AUMULH:
		return OPDP3(1, 0, 6, 0);
	case AUREM:
	case AUDIV:
		return S64 | OPDP2(2);
	case AUREMW:
	case AUDIVW:
		return S32 | OPDP2(2);
	case AAESE:
		return 0x4E << 24 | 2 << 20 | 8 << 16 | 4 << 12 | 2 << 10;
	case AAESD:
		return 0x4E << 24 | 2 << 20 | 8 << 16 | 5 << 12 | 2 << 10;
	case AAESMC:
		return 0x4E << 24 | 2 << 20 | 8 << 16 | 6 << 12 | 2 << 10;
	case AAESIMC:
		return 0x4E << 24 | 2 << 20 | 8 << 16 | 7 << 12 | 2 << 10;
	case ASHA1C:
		return 0x5E << 24 | 0 << 12;
	case ASHA1P:
		return 0x5E << 24 | 1 << 12;
	case ASHA1M:
		return 0x5E << 24 | 2 << 12;
	case ASHA1SU0:
		return 0x5E << 24 | 3 << 12;
	case ASHA256H:
		return 0x5E << 24 | 4 << 12;
	case ASHA256H2:
		return 0x5E << 24 | 5 << 12;
	case ASHA256SU1:
		return 0x5E << 24 | 6 << 12;
	case ASHA1H:
		return 0x5E << 24 | 2 << 20 | 8 << 16 | 0 << 12 | 2 << 10;
	case ASHA1SU1:
		return 0x5E << 24 | 2 << 20 | 8 << 16 | 1 << 12 | 2 << 10;
	case ASHA256SU0:
		return 0x5E << 24 | 2 << 20 | 8 << 16 | 2 << 12 | 2 << 10;
	case AFCVTZSD:
		return FPCVTI(1, 0, 1, 3, 0);
	case AFCVTZSDW:
		return FPCVTI(0, 0, 1, 3, 0);
	case AFCVTZSS:
		return FPCVTI(1, 0, 0, 3, 0);
	case AFCVTZSSW:
		return FPCVTI(0, 0, 0, 3, 0);
	case AFCVTZUD:
		return FPCVTI(1, 0, 1, 3, 1);
	case AFCVTZUDW:
		return FPCVTI(0, 0, 1, 3, 1);
	case AFCVTZUS:
		return FPCVTI(1, 0, 0, 3, 1);
	case AFCVTZUSW:
		return FPCVTI(0, 0, 0, 3, 1);
	case ASCVTFD:
		return FPCVTI(1, 0, 1, 0, 2);
	case ASCVTFS:
		return FPCVTI(1, 0, 0, 0, 2);
	case ASCVTFWD:
		return FPCVTI(0, 0, 1, 0, 2);
	case ASCVTFWS:
		return FPCVTI(0, 0, 0, 0, 2);
	case AUCVTFD:
		return FPCVTI(1, 0, 1, 0, 3);
	case AUCVTFS:
		return FPCVTI(1, 0, 0, 0, 3);
	case AUCVTFWD:
		return FPCVTI(0, 0, 1, 0, 3);
	case AUCVTFWS:
		return FPCVTI(0, 0, 0, 0, 3);
	case AFADDS:
		return FPOP2S(0, 0, 0, 2);
	case AFADDD:
		return FPOP2S(0, 0, 1, 2);
	case AFSUBS:
		return FPOP2S(0, 0, 0, 3);
	case AFSUBD:
		return FPOP2S(0, 0, 1, 3);
	case AFMULS:
		return FPOP2S(0, 0, 0, 0);
	case AFMULD:
		return FPOP2S(0, 0, 1, 0);
	case AFDIVS:
		return FPOP2S(0, 0, 0, 1);
	case AFDIVD:
		return FPOP2S(0, 0, 1, 1);
	case AFMAXS:
		return FPOP2S(0, 0, 0, 4);
	case AFMINS:
		return FPOP2S(0, 0, 0, 5);
	case AFMAXD:
		return FPOP2S(0, 0, 1, 4);
	case AFMIND:
		return FPOP2S(0, 0, 1, 5);
	case AFMAXNMS:
		return FPOP2S(0, 0, 0, 6);
	case AFMAXNMD:
		return FPOP2S(0, 0, 1, 6);
	case AFMINNMS:
		return FPOP2S(0, 0, 0, 7);
	case AFMINNMD:
		return FPOP2S(0, 0, 1, 7);
	case AFNMULS:
		return FPOP2S(0, 0, 0, 8);
	case AFNMULD:
		return FPOP2S(0, 0, 1, 8);
	case AFCMPS:
		return FPCMP(0, 0, 0, 0, 0);
	case AFCMPD:
		return FPCMP(0, 0, 1, 0, 0);
	case AFCMPES:
		return FPCMP(0, 0, 0, 0, 16);
	case AFCMPED:
		return FPCMP(0, 0, 1, 0, 16);
	case AFCCMPS:
		return FPCCMP(0, 0, 0, 0);
	case AFCCMPD:
		return FPCCMP(0, 0, 1, 0);
	case AFCCMPES:
		return FPCCMP(0, 0, 0, 1);
	case AFCCMPED:
		return FPCCMP(0, 0, 1, 1);
	case AFCSELS:
		return 0x1E << 24 | 0 << 22 | 1 << 21 | 3 << 10;
	case AFCSELD:
		return 0x1E << 24 | 1 << 22 | 1 << 21 | 3 << 10;
	case AFMOVS:
		return FPOP1S(0, 0, 0, 0);
	case AFABSS:
		return FPOP1S(0, 0, 0, 1);
	case AFNEGS:
		return FPOP1S(0, 0, 0, 2);
	case AFSQRTS:
		return FPOP1S(0, 0, 0, 3);
	case AFCVTSD:
		return FPOP1S(0, 0, 0, 5);
	case AFCVTSH:
		return FPOP1S(0, 0, 0, 7);
	case AFRINTNS:
		return FPOP1S(0, 0, 0, 8);
	case AFRINTPS:
		return FPOP1S(0, 0, 0, 9);
	case AFRINTMS:
		return FPOP1S(0, 0, 0, 10);
	case AFRINTZS:
		return FPOP1S(0, 0, 0, 11);
	case AFRINTAS:
		return FPOP1S(0, 0, 0, 12);
	case AFRINTXS:
		return FPOP1S(0, 0, 0, 14);
	case AFRINTIS:
		return FPOP1S(0, 0, 0, 15);
	case AFMOVD:
		return FPOP1S(0, 0, 1, 0);
	case AFABSD:
		return FPOP1S(0, 0, 1, 1);
	case AFNEGD:
		return FPOP1S(0, 0, 1, 2);
	case AFSQRTD:
		return FPOP1S(0, 0, 1, 3);
	case AFCVTDS:
		return FPOP1S(0, 0, 1, 4);
	case AFCVTDH:
		return FPOP1S(0, 0, 1, 7);
	case AFRINTND:
		return FPOP1S(0, 0, 1, 8);
	case AFRINTPD:
		return FPOP1S(0, 0, 1, 9);
	case AFRINTMD:
		return FPOP1S(0, 0, 1, 10);
	case AFRINTZD:
		return FPOP1S(0, 0, 1, 11);
	case AFRINTAD:
		return FPOP1S(0, 0, 1, 12);
	case AFRINTXD:
		return FPOP1S(0, 0, 1, 14);
	case AFRINTID:
		return FPOP1S(0, 0, 1, 15);
	case AFCVTHS:
		return FPOP1S(0, 0, 3, 4);
	case AFCVTHD:
		return FPOP1S(0, 0, 3, 5);
	}
	ctxt->diag("bad rrr %d %A", a, a);
	prasm(ctxt->curp);
	return 0;
}

/*
 * imm -> Rd
 * imm op Rn -> Rd
 */
static uint32
opirr(Link *ctxt, int a)
{
	switch(a) {
	/* op $addcon, Rn, Rd */
	case AMOV:
	case AADD:
		return S64 | 0 << 30 | 0 << 29 | 0x11 << 24;
	case ACMN:
	case AADDS:
		return S64 | 0 << 30 | 1 << 29 | 0x11 << 24;
	case AMOVW:
	case AADDW:
		return S32 | 0 << 30 | 0 << 29 | 0x11 << 24;
	case ACMNW:
	case AADDSW:
		return S32 | 0 << 30 | 1 << 29 | 0x11 << 24;
	case ASUB:
		return S64 | 1 << 30 | 0 << 29 | 0x11 << 24;
	case ACMP:
	case ASUBS:
		return S64 | 1 << 30 | 1 << 29 | 0x11 << 24;
	case ASUBW:
		return S32 | 1 << 30 | 0 << 29 | 0x11 << 24;
	case ACMPW:
	case ASUBSW:
		return S32 | 1 << 30 | 1 << 29 | 0x11 << 24;
	/* op $imm(SB), Rd; op label, Rd */
	case AADR:
		return 0 << 31 | 0x10 << 24;
	case AADRP:
		return 1 << 31 | 0x10 << 24;
	/* op $bimm, Rn, Rd */
	case AAND:
		return S64 | 0 << 29 | 0x24 << 23;
	case AANDW:
		return S32 | 0 << 29 | 0x24 << 23 | 0 << 22;
	case AORR:
		return S64 | 1 << 29 | 0x24 << 23;
	case AORRW:
		return S32 | 1 << 29 | 0x24 << 23 | 0 << 22;
	case AEOR:
		return S64 | 2 << 29 | 0x24 << 23;
	case AEORW:
		return S32 | 2 << 29 | 0x24 << 23 | 0 << 22;
	case AANDS:
		return S64 | 3 << 29 | 0x24 << 23;
	case AANDSW:
		return S32 | 3 << 29 | 0x24 << 23 | 0 << 22;
	case AASR:
		return S64 | 0 << 29 | 0x26 << 23; /* alias of SBFM */
	case AASRW:
		return S32 | 0 << 29 | 0x26 << 23 | 0 << 22;
	/* op $width, $lsb, Rn, Rd */
	case ABFI:
		return S64 | 2 << 29 | 0x26 << 23 | 1 << 22; /* alias of BFM */
	case ABFIW:
		return S32 | 2 << 29 | 0x26 << 23 | 0 << 22;
	/* op $imms, $immr, Rn, Rd */
	case ABFM:
		return S64 | 1 << 29 | 0x26 << 23 | 1 << 22;
	case ABFMW:
		return S32 | 1 << 29 | 0x26 << 23 | 0 << 22;
	case ASBFM:
		return S64 | 0 << 29 | 0x26 << 23 | 1 << 22;
	case ASBFMW:
		return S32 | 0 << 29 | 0x26 << 23 | 0 << 22;
	case AUBFM:
		return S64 | 2 << 29 | 0x26 << 23 | 1 << 22;
	case AUBFMW:
		return S32 | 2 << 29 | 0x26 << 23 | 0 << 22;
	case ABFXIL:
		return S64 | 1 << 29 | 0x26 << 23 | 1 << 22; /* alias of BFM */
	case ABFXILW:
		return S32 | 1 << 29 | 0x26 << 23 | 0 << 22;
	case AEXTR:
		return S64 | 0 << 29 | 0x27 << 23 | 1 << 22 | 0 << 21;
	case AEXTRW:
		return S32 | 0 << 29 | 0x27 << 23 | 0 << 22 | 0 << 21;
	case ACBNZ:
		return S64 | 0x1A << 25 | 1 << 24;
	case ACBNZW:
		return S32 | 0x1A << 25 | 1 << 24;
	case ACBZ:
		return S64 | 0x1A << 25 | 0 << 24;
	case ACBZW:
		return S32 | 0x1A << 25 | 0 << 24;
	case ACCMN:
		return S64 | 0 << 30 | 1 << 29 | 0xD2 << 21 | 1 << 11 | 0 << 10 | 0 << 4; /* imm5<<16 | cond<<12 | nzcv<<0 */
	case ACCMNW:
		return S32 | 0 << 30 | 1 << 29 | 0xD2 << 21 | 1 << 11 | 0 << 10 | 0 << 4;
	case ACCMP:
		return S64 | 1 << 30 | 1 << 29 | 0xD2 << 21 | 1 << 11 | 0 << 10 | 0 << 4; /* imm5<<16 | cond<<12 | nzcv<<0 */
	case ACCMPW:
		return S32 | 1 << 30 | 1 << 29 | 0xD2 << 21 | 1 << 11 | 0 << 10 | 0 << 4;
	case AMOVK:
		return S64 | 3 << 29 | 0x25 << 23;
	case AMOVKW:
		return S32 | 3 << 29 | 0x25 << 23;
	case AMOVN:
		return S64 | 0 << 29 | 0x25 << 23;
	case AMOVNW:
		return S32 | 0 << 29 | 0x25 << 23;
	case AMOVZ:
		return S64 | 2 << 29 | 0x25 << 23;
	case AMOVZW:
		return S32 | 2 << 29 | 0x25 << 23;
	case AMSR:
		return SYSOP(0, 0, 0, 4, 0, 0, 0x1F); /* MSR (immediate) */
	case AAT:
	case ADC:
	case AIC:
	case ATLBI:
	case ASYS:
		return SYSOP(0, 1, 0, 0, 0, 0, 0);
	case ASYSL:
		return SYSOP(1, 1, 0, 0, 0, 0, 0);
	case ATBZ:
		return 0x36 << 24;
	case ATBNZ:
		return 0x37 << 24;
	case ADSB:
		return SYSOP(0, 0, 3, 3, 0, 4, 0x1F);
	case ADMB:
		return SYSOP(0, 0, 3, 3, 0, 5, 0x1F);
	case AISB:
		return SYSOP(0, 0, 3, 3, 0, 6, 0x1F);
	case AHINT:
		return SYSOP(0, 0, 3, 2, 0, 0, 0x1F);
	}
	ctxt->diag("bad irr %A", a);
	prasm(ctxt->curp);
	return 0;
}

static uint32
opbit(Link *ctxt, int a)
{
	switch(a) {
	case ACLS:
		return S64 | OPBIT(5);
	case ACLSW:
		return S32 | OPBIT(5);
	case ACLZ:
		return S64 | OPBIT(4);
	case ACLZW:
		return S32 | OPBIT(4);
	case ARBIT:
		return S64 | OPBIT(0);
	case ARBITW:
		return S32 | OPBIT(0);
	case AREV:
		return S64 | OPBIT(3);
	case AREVW:
		return S32 | OPBIT(2);
	case AREV16:
		return S64 | OPBIT(1);
	case AREV16W:
		return S32 | OPBIT(1);
	case AREV32:
		return S64 | OPBIT(2);
	default:
		ctxt->diag("bad bit op\n%P", ctxt->curp);
		return 0;
	}
}

/*
 * add/subtract extended register
 */
static uint32
opxrrr(Link *ctxt, int a)
{
	switch(a) {
	case AADD:
		return S64 | 0 << 30 | 0 << 29 | 0x0b << 24 | 0 << 22 | 1 << 21 | LSL0_64;
	case AADDW:
		return S32 | 0 << 30 | 0 << 29 | 0x0b << 24 | 0 << 22 | 1 << 21 | LSL0_32;
	case ACMN:
	case AADDS:
		return S64 | 0 << 30 | 1 << 29 | 0x0b << 24 | 0 << 22 | 1 << 21 | LSL0_64;
	case ACMNW:
	case AADDSW:
		return S32 | 0 << 30 | 1 << 29 | 0x0b << 24 | 0 << 22 | 1 << 21 | LSL0_32;
	case ASUB:
		return S64 | 1 << 30 | 0 << 29 | 0x0b << 24 | 0 << 22 | 1 << 21 | LSL0_64;
	case ASUBW:
		return S32 | 1 << 30 | 0 << 29 | 0x0b << 24 | 0 << 22 | 1 << 21 | LSL0_32;
	case ACMP:
	case ASUBS:
		return S64 | 1 << 30 | 1 << 29 | 0x0b << 24 | 0 << 22 | 1 << 21 | LSL0_64;
	case ACMPW:
	case ASUBSW:
		return S32 | 1 << 30 | 1 << 29 | 0x0b << 24 | 0 << 22 | 1 << 21 | LSL0_32;
	}
	ctxt->diag("bad opxrrr %A\n%P", a, ctxt->curp);
	return 0;
}

static uint32
opimm(Link *ctxt, int a)
{
	switch(a) {
	case ASVC:
		return 0xD4 << 24 | 0 << 21 | 1; /* imm16<<5 */
	case AHVC:
		return 0xD4 << 24 | 0 << 21 | 2;
	case ASMC:
		return 0xD4 << 24 | 0 << 21 | 3;
	case ABRK:
		return 0xD4 << 24 | 1 << 21 | 0;
	case AHLT:
		return 0xD4 << 24 | 2 << 21 | 0;
	case ADCPS1:
		return 0xD4 << 24 | 5 << 21 | 1;
	case ADCPS2:
		return 0xD4 << 24 | 5 << 21 | 2;
	case ADCPS3:
		return 0xD4 << 24 | 5 << 21 | 3;
	case ACLREX:
		return SYSOP(0, 0, 3, 3, 0, 2, 0x1F);
	}
	ctxt->diag("bad imm %A", a);
	prasm(ctxt->curp);
	return 0;
}

static vlong
brdist(Link *ctxt, Prog *p, int preshift, int flen, int shift)
{
	vlong v;
	vlong t;
	v = 0;
	t = 0;
	if(p->pcond) {
		v = ((p->pcond->pc >> preshift)) - ((ctxt->pc >> preshift));
		if(((v & ((((1 << shift)) - 1)))) != 0)
			ctxt->diag("misaligned label\n%P", p);
		v >>= shift;
		t = (vlong)1 << ((flen - 1));
		if(v < -t || v >= t)
			ctxt->diag("branch too far\n%P", p);
	}
	return v & ((((t << 1)) - 1));	
}

/*
 * pc-relative branches
 */
static uint32
opbra(Link *ctxt, int a)
{
	switch(a) {
	case ABEQ:
		return OPBcc(0x0);
	case ABNE:
		return OPBcc(0x1);
	case ABCS:
		return OPBcc(0x2);
	case ABHS:
		return OPBcc(0x2);
	case ABCC:
		return OPBcc(0x3);
	case ABLO:
		return OPBcc(0x3);
	case ABMI:
		return OPBcc(0x4);
	case ABPL:
		return OPBcc(0x5);
	case ABVS:
		return OPBcc(0x6);
	case ABVC:
		return OPBcc(0x7);
	case ABHI:
		return OPBcc(0x8);
	case ABLS:
		return OPBcc(0x9);
	case ABGE:
		return OPBcc(0xa);
	case ABLT:
		return OPBcc(0xb);
	case ABGT:
		return OPBcc(0xc);
	case ABLE:
		return OPBcc(0xd); /* imm19<<5 | cond */
	case ADUFFZERO:
	case AB:
		return 0 << 31 | 5 << 26; /* imm26 */
	case ABL:
		return 1 << 31 | 5 << 26;
	}
	ctxt->diag("bad bra %A", a);
	prasm(ctxt->curp);
	return 0;
}

static uint32
opbrr(Link *ctxt, int a)
{
	switch(a) {
	case ABL:
		return OPBLR(1); /* BLR */
	case AB:
		return OPBLR(0); /* BR */
	case ARET:
		return OPBLR(2); /* RET */
	}
	ctxt->diag("bad brr %A", a);
	prasm(ctxt->curp);
	return 0;
}

static uint32
op0(Link *ctxt, int a)
{
	switch(a) {
	case ADRPS:
		return 0x6B << 25 | 5 << 21 | 0x1F << 16 | 0x1F << 5;
	case AERET:
		return 0x6B << 25 | 4 << 21 | 0x1F << 16 | 0 << 10 | 0x1F << 5;
	case ANOP:
		return SYSHINT(0);
	case AYIELD:
		return SYSHINT(1);
	case AWFE:
		return SYSHINT(2);
	case AWFI:
		return SYSHINT(3);
	case ASEV:
		return SYSHINT(4);
	case ASEVL:
		return SYSHINT(5);
	}
	ctxt->diag("bad op0 %A", a);
	prasm(ctxt->curp);
	return 0;
}

/*
 * register offset
 */
static uint32
opload(Link *ctxt, int a)
{
	switch(a) {
	case ALDAR:
		return LDSTX(3, 1, 1, 0, 1) | 0x1F << 10;
	case ALDARW:
		return LDSTX(2, 1, 1, 0, 1) | 0x1F << 10;
	case ALDARB:
		return LDSTX(0, 1, 1, 0, 1) | 0x1F << 10;
	case ALDARH:
		return LDSTX(1, 1, 1, 0, 1) | 0x1F << 10;
	case ALDAXP:
		return LDSTX(3, 0, 1, 1, 1);
	case ALDAXPW:
		return LDSTX(2, 0, 1, 1, 1);
	case ALDAXR:
		return LDSTX(3, 0, 1, 0, 1) | 0x1F << 10;
	case ALDAXRW:
		return LDSTX(2, 1, 1, 0, 1) | 0x1F << 10;
	case ALDAXRB:
		return LDSTX(0, 0, 1, 0, 1) | 0x1F << 10;
	case ALDAXRH:
		return LDSTX(1, 0, 1, 0, 1) | 0x1F << 10;
	case ALDXR:
		return LDSTX(3, 0, 1, 0, 0) | 0x1F << 10;
	case ALDXRB:
		return LDSTX(0, 0, 1, 0, 0) | 0x1F << 10;
	case ALDXRH:
		return LDSTX(1, 0, 1, 0, 0) | 0x1F << 10;
	case ALDXRW:
		return LDSTX(2, 0, 1, 0, 0) | 0x1F << 10;
	case ALDXP:
		return LDSTX(3, 0, 1, 1, 0);
	case ALDXPW:
		return LDSTX(2, 0, 1, 1, 0);
	case AMOVNP:
		return S64 | 0 << 30 | 5 << 27 | 0 << 26 | 0 << 23 | 1 << 22;
	case AMOVNPW:
		return S32 | 0 << 30 | 5 << 27 | 0 << 26 | 0 << 23 | 1 << 22;
	}
	ctxt->diag("bad opload %A\n%P", a, ctxt->curp);
	return 0;
}

static uint32
opstore(Link *ctxt, int a)
{
	switch(a) {
	case ASTLR:
		return LDSTX(3, 1, 0, 0, 1) | 0x1F << 10;
	case ASTLRB:
		return LDSTX(0, 1, 0, 0, 1) | 0x1F << 10;
	case ASTLRH:
		return LDSTX(1, 1, 0, 0, 1) | 0x1F << 10;
	case ASTLP:
		return LDSTX(3, 0, 0, 1, 1);
	case ASTLPW:
		return LDSTX(2, 0, 0, 1, 1);
	case ASTLRW:
		return LDSTX(2, 1, 0, 0, 1) | 0x1F << 10;
	case ASTLXP:
		return LDSTX(2, 0, 0, 1, 1);
	case ASTLXPW:
		return LDSTX(3, 0, 0, 1, 1);
	case ASTLXR:
		return LDSTX(3, 0, 0, 0, 1) | 0x1F << 10;
	case ASTLXRB:
		return LDSTX(0, 0, 0, 0, 1) | 0x1F << 10;
	case ASTLXRH:
		return LDSTX(1, 0, 0, 0, 1) | 0x1F << 10;
	case ASTLXRW:
		return LDSTX(2, 0, 0, 0, 1) | 0x1F << 10;
	case ASTXR:
		return LDSTX(3, 0, 0, 0, 0) | 0x1F << 10;
	case ASTXRB:
		return LDSTX(0, 0, 0, 0, 0) | 0x1F << 10;
	case ASTXRH:
		return LDSTX(1, 0, 0, 0, 0) | 0x1F << 10;
	case ASTXP:
		return LDSTX(3, 0, 0, 1, 0);
	case ASTXPW:
		return LDSTX(2, 0, 0, 1, 0);
	case ASTXRW:
		return LDSTX(2, 0, 0, 0, 0) | 0x1F << 10;
	case AMOVNP:
		return S64 | 0 << 30 | 5 << 27 | 0 << 26 | 0 << 23 | 1 << 22;
	case AMOVNPW:
		return S32 | 0 << 30 | 5 << 27 | 0 << 26 | 0 << 23 | 1 << 22;
	}
	ctxt->diag("bad opstore %A\n%P", a, ctxt->curp);
	return 0;
}

/*
 * load/store register (unsigned immediate) C3.3.13
 *	these produce 64-bit values (when there's an option)
 */
static uint32
olsr12u(Link *ctxt, int32 o, int32 v, int b, int r)
{
	if(v < 0 || v >= ((1 << 12)))
		ctxt->diag("offset out of range: %ld\n%P", v, ctxt->curp);
	o |= ((v & 0xFFF)) << 10;
	o |= b << 5;
	o |= r;
	return o;
}

static uint32
opldr12(Link *ctxt, int a)
{
	switch(a) {
	case AMOV:
		return LDSTR12U(3, 0, 1); /* imm12<<10 | Rn<<5 | Rt */
	case AMOVW:
		return LDSTR12U(2, 0, 2);
	case AMOVWU:
		return LDSTR12U(2, 0, 1);
	case AMOVH:
		return LDSTR12U(1, 0, 2);
	case AMOVHU:
		return LDSTR12U(1, 0, 1);
	case AMOVB:
		return LDSTR12U(0, 0, 2);
	case AMOVBU:
		return LDSTR12U(0, 0, 1);
	case AFMOVS:
		return LDSTR12U(2, 1, 1);
	case AFMOVD:
		return LDSTR12U(3, 1, 1);
	}
	ctxt->diag("bad opldr12 %A\n%P", a, ctxt->curp);
	return 0;
}

static uint32
opstr12(Link *ctxt, int a)
{
	return LD2STR(opldr12(ctxt, a));
}

/* 
 * load/store register (unscaled immediate) C3.3.12
 */
static uint32
olsr9s(Link *ctxt, int32 o, int32 v, int b, int r)
{
	if(v < -256 || v > 255)
		ctxt->diag("offset out of range: %ld\n%P", v, ctxt->curp);
	o |= ((v & 0x1FF)) << 12;
	o |= b << 5;
	o |= r;
	return o;
}

static uint32
opldr9(Link *ctxt, int a)
{
	switch(a) {
	case AMOV:
		return LDSTR9S(3, 0, 1); /* simm9<<12 | Rn<<5 | Rt */
	case AMOVW:
		return LDSTR9S(2, 0, 2);
	case AMOVWU:
		return LDSTR9S(2, 0, 1);
	case AMOVH:
		return LDSTR9S(1, 0, 2);
	case AMOVHU:
		return LDSTR9S(1, 0, 1);
	case AMOVB:
		return LDSTR9S(0, 0, 2);
	case AMOVBU:
		return LDSTR9S(0, 0, 1);
	case AFMOVS:
		return LDSTR9S(2, 1, 1);
	case AFMOVD:
		return LDSTR9S(3, 1, 1);
	}
	ctxt->diag("bad opldr9 %A\n%P", a, ctxt->curp);
	return 0;
}

static uint32
opstr9(Link *ctxt, int a)
{
	return LD2STR(opldr9(ctxt, a));
}

static uint32
opldrpp(Link *ctxt, int a)
{
	switch(a) {
	case AMOV:
		return 3 << 30 | 7 << 27 | 0 << 26 | 0 << 24 | 1 << 22; /* simm9<<12 | Rn<<5 | Rt */
	case AMOVW:
		return 2 << 30 | 7 << 27 | 0 << 26 | 0 << 24 | 2 << 22;
	case AMOVWU:
		return 2 << 30 | 7 << 27 | 0 << 26 | 0 << 24 | 1 << 22;
	case AMOVH:
		return 1 << 30 | 7 << 27 | 0 << 26 | 0 << 24 | 2 << 22;
	case AMOVHU:
		return 1 << 30 | 7 << 27 | 0 << 26 | 0 << 24 | 1 << 22;
	case AMOVB:
		return 0 << 30 | 7 << 27 | 0 << 26 | 0 << 24 | 2 << 22;
	case AMOVBU:
		return 0 << 30 | 7 << 27 | 0 << 26 | 0 << 24 | 1 << 22;
	}
	ctxt->diag("bad opldr %A\n%P", a, ctxt->curp);
	return 0;
}

/*
 * load/store register (extended register)
 */
static uint32
olsxrr(Link *ctxt, int as, int rt, int r1, int r2)
{
	USED(as);
	USED(rt);
	USED(r1);
	USED(r2);
	ctxt->diag("need load/store extended register\n%P", ctxt->curp);
	return 0xffffffffu;
}

static uint32
oaddi(int32 o1, int32 v, int r, int rt)
{
	if(((v & 0xFFF000)) != 0) {
		v >>= 12;
		o1 |= 1 << 22;
	}
	o1 |= ((((v & 0xFFF)) << 10)) | ((r << 5)) | rt;
	return o1;
}

/*
 * load a a literal value into dr
 */
static uint32
omovlit(Link *ctxt, int as, Prog *p, Addr *a, int dr)
{
	int32 v;
	int32 o1;
	int w;
	int fp;
	if(p->pcond == nil) { /* not in literal pool */
		aclass(ctxt, a);
		Bprint(ctxt->bso, "omovlit add %lld (%#llux)\n", ctxt->instoffset, ctxt->instoffset);
		/* TO DO: could be clever, and use general constant builder */
		o1 = opirr(ctxt, AADD);
		v = ctxt->instoffset;
		if(v != 0 && ((v & 0xFFF)) == 0) {
			v >>= 12;
			o1 |= 1 << 22; /* shift, by 12 */
		}
		o1 |= ((((v & 0xFFF)) << 10)) | ((REGZERO << 5)) | dr;
	} else {
		fp = 0;
		w = 0; /* default: 32 bit, unsigned */
		switch(as) {
		case AFMOVS:
			fp = 1;
			break;
		case AFMOVD:
			fp = 1;
			w = 1; /* 64 bit simd&fp */
			break;
		case AMOV:
			if(p->pcond->as == ADWORD)
				w = 1; /* 64 bit */
			else
				if(p->pcond->to.offset < 0)
					w = 2; /* sign extend */
			break;
		case AMOVB:
		case AMOVH:
		case AMOVW:
			w = 2; /* 32 bit, sign-extended to 64 */
			break;
		}
		v = brdist(ctxt, p, 0, 19, 2);
		o1 = ((w << 30)) | ((fp << 26)) | ((3 << 27));
		o1 |= ((v & 0x7FFFF)) << 5;
		o1 |= dr;
	}
	return o1;
}

static uint32
opbfm(Link *ctxt, int a, int r, int s, int rf, int rt)
{
	uint32 o;
	uint32 c;
	o = opirr(ctxt, a);
	if(((o & ((1 << 31)))) == 0)
		c = 32;
	else
		c = 64;
	if(r < 0 || r >= c)
		ctxt->diag("illegal bit number\n%P", ctxt->curp);
	o |= ((r & 0x3F)) << 16;
	if(s < 0 || s >= c)
		ctxt->diag("illegal bit number\n%P", ctxt->curp);
	o |= ((s & 0x3F)) << 10;
	o |= ((rf << 5)) | rt;
	return o;
}

static uint32
opextr(Link *ctxt, int a, int32 v, int rn, int rm, int rt)
{
	uint32 o;
	uint32 c;
	o = opirr(ctxt, a);
	if(((o & ((1 << 31)))) != 0)
		c = 63;
	else
		c = 31;
	if(v < 0 || v > c)
		ctxt->diag("illegal bit number\n%P", ctxt->curp);
	o |= v << 10;
	o |= rn << 5;
	o |= rm << 16;
	o |= rt;
	return o;
}

/*
 * size in log2(bytes)
 */
static int
movesize(int a)
{
	switch(a) {
	case AMOV:
		return 3;
	case AMOVW:
	case AMOVWU:
		return 2;
	case AMOVH:
	case AMOVHU:
		return 1;
	case AMOVB:
	case AMOVBU:
		return 0;
	case AFMOVS:
		return 2;
	case AFMOVD:
		return 3;
	default:
		return -1;
	}
}

static Mask bitmasks[] = {
	{ 1,	64,	0,	0x00000000000001ULL },
	{ 1,	64,	63,	0x00000000000002ULL },
	{ 2,	64,	0,	0x00000000000003ULL },
	{ 1,	64,	62,	0x00000000000004ULL },
	{ 2,	64,	63,	0x00000000000006ULL },
	{ 3,	64,	0,	0x00000000000007ULL },
	{ 1,	64,	61,	0x00000000000008ULL },
	{ 2,	64,	62,	0x0000000000000cULL },
	{ 3,	64,	63,	0x0000000000000eULL },
	{ 4,	64,	0,	0x0000000000000fULL },
	{ 1,	64,	60,	0x00000000000010ULL },
	{ 2,	64,	61,	0x00000000000018ULL },
	{ 3,	64,	62,	0x0000000000001cULL },
	{ 4,	64,	63,	0x0000000000001eULL },
	{ 5,	64,	0,	0x0000000000001fULL },
	{ 1,	64,	59,	0x00000000000020ULL },
	{ 2,	64,	60,	0x00000000000030ULL },
	{ 3,	64,	61,	0x00000000000038ULL },
	{ 4,	64,	62,	0x0000000000003cULL },
	{ 5,	64,	63,	0x0000000000003eULL },
	{ 6,	64,	0,	0x0000000000003fULL },
	{ 1,	64,	58,	0x00000000000040ULL },
	{ 2,	64,	59,	0x00000000000060ULL },
	{ 3,	64,	60,	0x00000000000070ULL },
	{ 4,	64,	61,	0x00000000000078ULL },
	{ 5,	64,	62,	0x0000000000007cULL },
	{ 6,	64,	63,	0x0000000000007eULL },
	{ 7,	64,	0,	0x0000000000007fULL },
	{ 1,	64,	57,	0x00000000000080ULL },
	{ 2,	64,	58,	0x000000000000c0ULL },
	{ 3,	64,	59,	0x000000000000e0ULL },
	{ 4,	64,	60,	0x000000000000f0ULL },
	{ 5,	64,	61,	0x000000000000f8ULL },
	{ 6,	64,	62,	0x000000000000fcULL },
	{ 7,	64,	63,	0x000000000000feULL },
	{ 8,	64,	0,	0x000000000000ffULL },
	{ 1,	64,	56,	0x00000000000100ULL },
	{ 2,	64,	57,	0x00000000000180ULL },
	{ 3,	64,	58,	0x000000000001c0ULL },
	{ 4,	64,	59,	0x000000000001e0ULL },
	{ 5,	64,	60,	0x000000000001f0ULL },
	{ 6,	64,	61,	0x000000000001f8ULL },
	{ 7,	64,	62,	0x000000000001fcULL },
	{ 8,	64,	63,	0x000000000001feULL },
	{ 9,	64,	0,	0x000000000001ffULL },
	{ 1,	64,	55,	0x00000000000200ULL },
	{ 2,	64,	56,	0x00000000000300ULL },
	{ 3,	64,	57,	0x00000000000380ULL },
	{ 4,	64,	58,	0x000000000003c0ULL },
	{ 5,	64,	59,	0x000000000003e0ULL },
	{ 6,	64,	60,	0x000000000003f0ULL },
	{ 7,	64,	61,	0x000000000003f8ULL },
	{ 8,	64,	62,	0x000000000003fcULL },
	{ 9,	64,	63,	0x000000000003feULL },
	{ 10,	64,	0,	0x000000000003ffULL },
	{ 1,	64,	54,	0x00000000000400ULL },
	{ 2,	64,	55,	0x00000000000600ULL },
	{ 3,	64,	56,	0x00000000000700ULL },
	{ 4,	64,	57,	0x00000000000780ULL },
	{ 5,	64,	58,	0x000000000007c0ULL },
	{ 6,	64,	59,	0x000000000007e0ULL },
	{ 7,	64,	60,	0x000000000007f0ULL },
	{ 8,	64,	61,	0x000000000007f8ULL },
	{ 9,	64,	62,	0x000000000007fcULL },
	{ 10,	64,	63,	0x000000000007feULL },
	{ 11,	64,	0,	0x000000000007ffULL },
	{ 1,	64,	53,	0x00000000000800ULL },
	{ 2,	64,	54,	0x00000000000c00ULL },
	{ 3,	64,	55,	0x00000000000e00ULL },
	{ 4,	64,	56,	0x00000000000f00ULL },
	{ 5,	64,	57,	0x00000000000f80ULL },
	{ 6,	64,	58,	0x00000000000fc0ULL },
	{ 7,	64,	59,	0x00000000000fe0ULL },
	{ 8,	64,	60,	0x00000000000ff0ULL },
	{ 9,	64,	61,	0x00000000000ff8ULL },
	{ 10,	64,	62,	0x00000000000ffcULL },
	{ 11,	64,	63,	0x00000000000ffeULL },
	{ 12,	64,	0,	0x00000000000fffULL },
	{ 1,	64,	52,	0x00000000001000ULL },
	{ 2,	64,	53,	0x00000000001800ULL },
	{ 3,	64,	54,	0x00000000001c00ULL },
	{ 4,	64,	55,	0x00000000001e00ULL },
	{ 5,	64,	56,	0x00000000001f00ULL },
	{ 6,	64,	57,	0x00000000001f80ULL },
	{ 7,	64,	58,	0x00000000001fc0ULL },
	{ 8,	64,	59,	0x00000000001fe0ULL },
	{ 9,	64,	60,	0x00000000001ff0ULL },
	{ 10,	64,	61,	0x00000000001ff8ULL },
	{ 11,	64,	62,	0x00000000001ffcULL },
	{ 12,	64,	63,	0x00000000001ffeULL },
	{ 13,	64,	0,	0x00000000001fffULL },
	{ 1,	64,	51,	0x00000000002000ULL },
	{ 2,	64,	52,	0x00000000003000ULL },
	{ 3,	64,	53,	0x00000000003800ULL },
	{ 4,	64,	54,	0x00000000003c00ULL },
	{ 5,	64,	55,	0x00000000003e00ULL },
	{ 6,	64,	56,	0x00000000003f00ULL },
	{ 7,	64,	57,	0x00000000003f80ULL },
	{ 8,	64,	58,	0x00000000003fc0ULL },
	{ 9,	64,	59,	0x00000000003fe0ULL },
	{ 10,	64,	60,	0x00000000003ff0ULL },
	{ 11,	64,	61,	0x00000000003ff8ULL },
	{ 12,	64,	62,	0x00000000003ffcULL },
	{ 13,	64,	63,	0x00000000003ffeULL },
	{ 14,	64,	0,	0x00000000003fffULL },
	{ 1,	64,	50,	0x00000000004000ULL },
	{ 2,	64,	51,	0x00000000006000ULL },
	{ 3,	64,	52,	0x00000000007000ULL },
	{ 4,	64,	53,	0x00000000007800ULL },
	{ 5,	64,	54,	0x00000000007c00ULL },
	{ 6,	64,	55,	0x00000000007e00ULL },
	{ 7,	64,	56,	0x00000000007f00ULL },
	{ 8,	64,	57,	0x00000000007f80ULL },
	{ 9,	64,	58,	0x00000000007fc0ULL },
	{ 10,	64,	59,	0x00000000007fe0ULL },
	{ 11,	64,	60,	0x00000000007ff0ULL },
	{ 12,	64,	61,	0x00000000007ff8ULL },
	{ 13,	64,	62,	0x00000000007ffcULL },
	{ 14,	64,	63,	0x00000000007ffeULL },
	{ 15,	64,	0,	0x00000000007fffULL },
	{ 1,	64,	49,	0x00000000008000ULL },
	{ 2,	64,	50,	0x0000000000c000ULL },
	{ 3,	64,	51,	0x0000000000e000ULL },
	{ 4,	64,	52,	0x0000000000f000ULL },
	{ 5,	64,	53,	0x0000000000f800ULL },
	{ 6,	64,	54,	0x0000000000fc00ULL },
	{ 7,	64,	55,	0x0000000000fe00ULL },
	{ 8,	64,	56,	0x0000000000ff00ULL },
	{ 9,	64,	57,	0x0000000000ff80ULL },
	{ 10,	64,	58,	0x0000000000ffc0ULL },
	{ 11,	64,	59,	0x0000000000ffe0ULL },
	{ 12,	64,	60,	0x0000000000fff0ULL },
	{ 13,	64,	61,	0x0000000000fff8ULL },
	{ 14,	64,	62,	0x0000000000fffcULL },
	{ 15,	64,	63,	0x0000000000fffeULL },
	{ 16,	64,	0,	0x0000000000ffffULL },
	{ 1,	64,	48,	0x00000000010000ULL },
	{ 2,	64,	49,	0x00000000018000ULL },
	{ 3,	64,	50,	0x0000000001c000ULL },
	{ 4,	64,	51,	0x0000000001e000ULL },
	{ 5,	64,	52,	0x0000000001f000ULL },
	{ 6,	64,	53,	0x0000000001f800ULL },
	{ 7,	64,	54,	0x0000000001fc00ULL },
	{ 8,	64,	55,	0x0000000001fe00ULL },
	{ 9,	64,	56,	0x0000000001ff00ULL },
	{ 10,	64,	57,	0x0000000001ff80ULL },
	{ 11,	64,	58,	0x0000000001ffc0ULL },
	{ 12,	64,	59,	0x0000000001ffe0ULL },
	{ 13,	64,	60,	0x0000000001fff0ULL },
	{ 14,	64,	61,	0x0000000001fff8ULL },
	{ 15,	64,	62,	0x0000000001fffcULL },
	{ 16,	64,	63,	0x0000000001fffeULL },
	{ 17,	64,	0,	0x0000000001ffffULL },
	{ 1,	64,	47,	0x00000000020000ULL },
	{ 2,	64,	48,	0x00000000030000ULL },
	{ 3,	64,	49,	0x00000000038000ULL },
	{ 4,	64,	50,	0x0000000003c000ULL },
	{ 5,	64,	51,	0x0000000003e000ULL },
	{ 6,	64,	52,	0x0000000003f000ULL },
	{ 7,	64,	53,	0x0000000003f800ULL },
	{ 8,	64,	54,	0x0000000003fc00ULL },
	{ 9,	64,	55,	0x0000000003fe00ULL },
	{ 10,	64,	56,	0x0000000003ff00ULL },
	{ 11,	64,	57,	0x0000000003ff80ULL },
	{ 12,	64,	58,	0x0000000003ffc0ULL },
	{ 13,	64,	59,	0x0000000003ffe0ULL },
	{ 14,	64,	60,	0x0000000003fff0ULL },
	{ 15,	64,	61,	0x0000000003fff8ULL },
	{ 16,	64,	62,	0x0000000003fffcULL },
	{ 17,	64,	63,	0x0000000003fffeULL },
	{ 18,	64,	0,	0x0000000003ffffULL },
	{ 1,	64,	46,	0x00000000040000ULL },
	{ 2,	64,	47,	0x00000000060000ULL },
	{ 3,	64,	48,	0x00000000070000ULL },
	{ 4,	64,	49,	0x00000000078000ULL },
	{ 5,	64,	50,	0x0000000007c000ULL },
	{ 6,	64,	51,	0x0000000007e000ULL },
	{ 7,	64,	52,	0x0000000007f000ULL },
	{ 8,	64,	53,	0x0000000007f800ULL },
	{ 9,	64,	54,	0x0000000007fc00ULL },
	{ 10,	64,	55,	0x0000000007fe00ULL },
	{ 11,	64,	56,	0x0000000007ff00ULL },
	{ 12,	64,	57,	0x0000000007ff80ULL },
	{ 13,	64,	58,	0x0000000007ffc0ULL },
	{ 14,	64,	59,	0x0000000007ffe0ULL },
	{ 15,	64,	60,	0x0000000007fff0ULL },
	{ 16,	64,	61,	0x0000000007fff8ULL },
	{ 17,	64,	62,	0x0000000007fffcULL },
	{ 18,	64,	63,	0x0000000007fffeULL },
	{ 19,	64,	0,	0x0000000007ffffULL },
	{ 1,	64,	45,	0x00000000080000ULL },
	{ 2,	64,	46,	0x000000000c0000ULL },
	{ 3,	64,	47,	0x000000000e0000ULL },
	{ 4,	64,	48,	0x000000000f0000ULL },
	{ 5,	64,	49,	0x000000000f8000ULL },
	{ 6,	64,	50,	0x000000000fc000ULL },
	{ 7,	64,	51,	0x000000000fe000ULL },
	{ 8,	64,	52,	0x000000000ff000ULL },
	{ 9,	64,	53,	0x000000000ff800ULL },
	{ 10,	64,	54,	0x000000000ffc00ULL },
	{ 11,	64,	55,	0x000000000ffe00ULL },
	{ 12,	64,	56,	0x000000000fff00ULL },
	{ 13,	64,	57,	0x000000000fff80ULL },
	{ 14,	64,	58,	0x000000000fffc0ULL },
	{ 15,	64,	59,	0x000000000fffe0ULL },
	{ 16,	64,	60,	0x000000000ffff0ULL },
	{ 17,	64,	61,	0x000000000ffff8ULL },
	{ 18,	64,	62,	0x000000000ffffcULL },
	{ 19,	64,	63,	0x000000000ffffeULL },
	{ 20,	64,	0,	0x000000000fffffULL },
	{ 1,	64,	44,	0x00000000100000ULL },
	{ 2,	64,	45,	0x00000000180000ULL },
	{ 3,	64,	46,	0x000000001c0000ULL },
	{ 4,	64,	47,	0x000000001e0000ULL },
	{ 5,	64,	48,	0x000000001f0000ULL },
	{ 6,	64,	49,	0x000000001f8000ULL },
	{ 7,	64,	50,	0x000000001fc000ULL },
	{ 8,	64,	51,	0x000000001fe000ULL },
	{ 9,	64,	52,	0x000000001ff000ULL },
	{ 10,	64,	53,	0x000000001ff800ULL },
	{ 11,	64,	54,	0x000000001ffc00ULL },
	{ 12,	64,	55,	0x000000001ffe00ULL },
	{ 13,	64,	56,	0x000000001fff00ULL },
	{ 14,	64,	57,	0x000000001fff80ULL },
	{ 15,	64,	58,	0x000000001fffc0ULL },
	{ 16,	64,	59,	0x000000001fffe0ULL },
	{ 17,	64,	60,	0x000000001ffff0ULL },
	{ 18,	64,	61,	0x000000001ffff8ULL },
	{ 19,	64,	62,	0x000000001ffffcULL },
	{ 20,	64,	63,	0x000000001ffffeULL },
	{ 21,	64,	0,	0x000000001fffffULL },
	{ 1,	64,	43,	0x00000000200000ULL },
	{ 2,	64,	44,	0x00000000300000ULL },
	{ 3,	64,	45,	0x00000000380000ULL },
	{ 4,	64,	46,	0x000000003c0000ULL },
	{ 5,	64,	47,	0x000000003e0000ULL },
	{ 6,	64,	48,	0x000000003f0000ULL },
	{ 7,	64,	49,	0x000000003f8000ULL },
	{ 8,	64,	50,	0x000000003fc000ULL },
	{ 9,	64,	51,	0x000000003fe000ULL },
	{ 10,	64,	52,	0x000000003ff000ULL },
	{ 11,	64,	53,	0x000000003ff800ULL },
	{ 12,	64,	54,	0x000000003ffc00ULL },
	{ 13,	64,	55,	0x000000003ffe00ULL },
	{ 14,	64,	56,	0x000000003fff00ULL },
	{ 15,	64,	57,	0x000000003fff80ULL },
	{ 16,	64,	58,	0x000000003fffc0ULL },
	{ 17,	64,	59,	0x000000003fffe0ULL },
	{ 18,	64,	60,	0x000000003ffff0ULL },
	{ 19,	64,	61,	0x000000003ffff8ULL },
	{ 20,	64,	62,	0x000000003ffffcULL },
	{ 21,	64,	63,	0x000000003ffffeULL },
	{ 22,	64,	0,	0x000000003fffffULL },
	{ 1,	64,	42,	0x00000000400000ULL },
	{ 2,	64,	43,	0x00000000600000ULL },
	{ 3,	64,	44,	0x00000000700000ULL },
	{ 4,	64,	45,	0x00000000780000ULL },
	{ 5,	64,	46,	0x000000007c0000ULL },
	{ 6,	64,	47,	0x000000007e0000ULL },
	{ 7,	64,	48,	0x000000007f0000ULL },
	{ 8,	64,	49,	0x000000007f8000ULL },
	{ 9,	64,	50,	0x000000007fc000ULL },
	{ 10,	64,	51,	0x000000007fe000ULL },
	{ 11,	64,	52,	0x000000007ff000ULL },
	{ 12,	64,	53,	0x000000007ff800ULL },
	{ 13,	64,	54,	0x000000007ffc00ULL },
	{ 14,	64,	55,	0x000000007ffe00ULL },
	{ 15,	64,	56,	0x000000007fff00ULL },
	{ 16,	64,	57,	0x000000007fff80ULL },
	{ 17,	64,	58,	0x000000007fffc0ULL },
	{ 18,	64,	59,	0x000000007fffe0ULL },
	{ 19,	64,	60,	0x000000007ffff0ULL },
	{ 20,	64,	61,	0x000000007ffff8ULL },
	{ 21,	64,	62,	0x000000007ffffcULL },
	{ 22,	64,	63,	0x000000007ffffeULL },
	{ 23,	64,	0,	0x000000007fffffULL },
	{ 1,	64,	41,	0x00000000800000ULL },
	{ 2,	64,	42,	0x00000000c00000ULL },
	{ 3,	64,	43,	0x00000000e00000ULL },
	{ 4,	64,	44,	0x00000000f00000ULL },
	{ 5,	64,	45,	0x00000000f80000ULL },
	{ 6,	64,	46,	0x00000000fc0000ULL },
	{ 7,	64,	47,	0x00000000fe0000ULL },
	{ 8,	64,	48,	0x00000000ff0000ULL },
	{ 9,	64,	49,	0x00000000ff8000ULL },
	{ 10,	64,	50,	0x00000000ffc000ULL },
	{ 11,	64,	51,	0x00000000ffe000ULL },
	{ 12,	64,	52,	0x00000000fff000ULL },
	{ 13,	64,	53,	0x00000000fff800ULL },
	{ 14,	64,	54,	0x00000000fffc00ULL },
	{ 15,	64,	55,	0x00000000fffe00ULL },
	{ 16,	64,	56,	0x00000000ffff00ULL },
	{ 17,	64,	57,	0x00000000ffff80ULL },
	{ 18,	64,	58,	0x00000000ffffc0ULL },
	{ 19,	64,	59,	0x00000000ffffe0ULL },
	{ 20,	64,	60,	0x00000000fffff0ULL },
	{ 21,	64,	61,	0x00000000fffff8ULL },
	{ 22,	64,	62,	0x00000000fffffcULL },
	{ 23,	64,	63,	0x00000000fffffeULL },
	{ 24,	64,	0,	0x00000000ffffffULL },
	{ 1,	64,	40,	0x00000001000000ULL },
	{ 2,	64,	41,	0x00000001800000ULL },
	{ 3,	64,	42,	0x00000001c00000ULL },
	{ 4,	64,	43,	0x00000001e00000ULL },
	{ 5,	64,	44,	0x00000001f00000ULL },
	{ 6,	64,	45,	0x00000001f80000ULL },
	{ 7,	64,	46,	0x00000001fc0000ULL },
	{ 8,	64,	47,	0x00000001fe0000ULL },
	{ 9,	64,	48,	0x00000001ff0000ULL },
	{ 10,	64,	49,	0x00000001ff8000ULL },
	{ 11,	64,	50,	0x00000001ffc000ULL },
	{ 12,	64,	51,	0x00000001ffe000ULL },
	{ 13,	64,	52,	0x00000001fff000ULL },
	{ 14,	64,	53,	0x00000001fff800ULL },
	{ 15,	64,	54,	0x00000001fffc00ULL },
	{ 16,	64,	55,	0x00000001fffe00ULL },
	{ 17,	64,	56,	0x00000001ffff00ULL },
	{ 18,	64,	57,	0x00000001ffff80ULL },
	{ 19,	64,	58,	0x00000001ffffc0ULL },
	{ 20,	64,	59,	0x00000001ffffe0ULL },
	{ 21,	64,	60,	0x00000001fffff0ULL },
	{ 22,	64,	61,	0x00000001fffff8ULL },
	{ 23,	64,	62,	0x00000001fffffcULL },
	{ 24,	64,	63,	0x00000001fffffeULL },
	{ 25,	64,	0,	0x00000001ffffffULL },
	{ 1,	64,	39,	0x00000002000000ULL },
	{ 2,	64,	40,	0x00000003000000ULL },
	{ 3,	64,	41,	0x00000003800000ULL },
	{ 4,	64,	42,	0x00000003c00000ULL },
	{ 5,	64,	43,	0x00000003e00000ULL },
	{ 6,	64,	44,	0x00000003f00000ULL },
	{ 7,	64,	45,	0x00000003f80000ULL },
	{ 8,	64,	46,	0x00000003fc0000ULL },
	{ 9,	64,	47,	0x00000003fe0000ULL },
	{ 10,	64,	48,	0x00000003ff0000ULL },
	{ 11,	64,	49,	0x00000003ff8000ULL },
	{ 12,	64,	50,	0x00000003ffc000ULL },
	{ 13,	64,	51,	0x00000003ffe000ULL },
	{ 14,	64,	52,	0x00000003fff000ULL },
	{ 15,	64,	53,	0x00000003fff800ULL },
	{ 16,	64,	54,	0x00000003fffc00ULL },
	{ 17,	64,	55,	0x00000003fffe00ULL },
	{ 18,	64,	56,	0x00000003ffff00ULL },
	{ 19,	64,	57,	0x00000003ffff80ULL },
	{ 20,	64,	58,	0x00000003ffffc0ULL },
	{ 21,	64,	59,	0x00000003ffffe0ULL },
	{ 22,	64,	60,	0x00000003fffff0ULL },
	{ 23,	64,	61,	0x00000003fffff8ULL },
	{ 24,	64,	62,	0x00000003fffffcULL },
	{ 25,	64,	63,	0x00000003fffffeULL },
	{ 26,	64,	0,	0x00000003ffffffULL },
	{ 1,	64,	38,	0x00000004000000ULL },
	{ 2,	64,	39,	0x00000006000000ULL },
	{ 3,	64,	40,	0x00000007000000ULL },
	{ 4,	64,	41,	0x00000007800000ULL },
	{ 5,	64,	42,	0x00000007c00000ULL },
	{ 6,	64,	43,	0x00000007e00000ULL },
	{ 7,	64,	44,	0x00000007f00000ULL },
	{ 8,	64,	45,	0x00000007f80000ULL },
	{ 9,	64,	46,	0x00000007fc0000ULL },
	{ 10,	64,	47,	0x00000007fe0000ULL },
	{ 11,	64,	48,	0x00000007ff0000ULL },
	{ 12,	64,	49,	0x00000007ff8000ULL },
	{ 13,	64,	50,	0x00000007ffc000ULL },
	{ 14,	64,	51,	0x00000007ffe000ULL },
	{ 15,	64,	52,	0x00000007fff000ULL },
	{ 16,	64,	53,	0x00000007fff800ULL },
	{ 17,	64,	54,	0x00000007fffc00ULL },
	{ 18,	64,	55,	0x00000007fffe00ULL },
	{ 19,	64,	56,	0x00000007ffff00ULL },
	{ 20,	64,	57,	0x00000007ffff80ULL },
	{ 21,	64,	58,	0x00000007ffffc0ULL },
	{ 22,	64,	59,	0x00000007ffffe0ULL },
	{ 23,	64,	60,	0x00000007fffff0ULL },
	{ 24,	64,	61,	0x00000007fffff8ULL },
	{ 25,	64,	62,	0x00000007fffffcULL },
	{ 26,	64,	63,	0x00000007fffffeULL },
	{ 27,	64,	0,	0x00000007ffffffULL },
	{ 1,	64,	37,	0x00000008000000ULL },
	{ 2,	64,	38,	0x0000000c000000ULL },
	{ 3,	64,	39,	0x0000000e000000ULL },
	{ 4,	64,	40,	0x0000000f000000ULL },
	{ 5,	64,	41,	0x0000000f800000ULL },
	{ 6,	64,	42,	0x0000000fc00000ULL },
	{ 7,	64,	43,	0x0000000fe00000ULL },
	{ 8,	64,	44,	0x0000000ff00000ULL },
	{ 9,	64,	45,	0x0000000ff80000ULL },
	{ 10,	64,	46,	0x0000000ffc0000ULL },
	{ 11,	64,	47,	0x0000000ffe0000ULL },
	{ 12,	64,	48,	0x0000000fff0000ULL },
	{ 13,	64,	49,	0x0000000fff8000ULL },
	{ 14,	64,	50,	0x0000000fffc000ULL },
	{ 15,	64,	51,	0x0000000fffe000ULL },
	{ 16,	64,	52,	0x0000000ffff000ULL },
	{ 17,	64,	53,	0x0000000ffff800ULL },
	{ 18,	64,	54,	0x0000000ffffc00ULL },
	{ 19,	64,	55,	0x0000000ffffe00ULL },
	{ 20,	64,	56,	0x0000000fffff00ULL },
	{ 21,	64,	57,	0x0000000fffff80ULL },
	{ 22,	64,	58,	0x0000000fffffc0ULL },
	{ 23,	64,	59,	0x0000000fffffe0ULL },
	{ 24,	64,	60,	0x0000000ffffff0ULL },
	{ 25,	64,	61,	0x0000000ffffff8ULL },
	{ 26,	64,	62,	0x0000000ffffffcULL },
	{ 27,	64,	63,	0x0000000ffffffeULL },
	{ 28,	64,	0,	0x0000000fffffffULL },
	{ 1,	64,	36,	0x00000010000000ULL },
	{ 2,	64,	37,	0x00000018000000ULL },
	{ 3,	64,	38,	0x0000001c000000ULL },
	{ 4,	64,	39,	0x0000001e000000ULL },
	{ 5,	64,	40,	0x0000001f000000ULL },
	{ 6,	64,	41,	0x0000001f800000ULL },
	{ 7,	64,	42,	0x0000001fc00000ULL },
	{ 8,	64,	43,	0x0000001fe00000ULL },
	{ 9,	64,	44,	0x0000001ff00000ULL },
	{ 10,	64,	45,	0x0000001ff80000ULL },
	{ 11,	64,	46,	0x0000001ffc0000ULL },
	{ 12,	64,	47,	0x0000001ffe0000ULL },
	{ 13,	64,	48,	0x0000001fff0000ULL },
	{ 14,	64,	49,	0x0000001fff8000ULL },
	{ 15,	64,	50,	0x0000001fffc000ULL },
	{ 16,	64,	51,	0x0000001fffe000ULL },
	{ 17,	64,	52,	0x0000001ffff000ULL },
	{ 18,	64,	53,	0x0000001ffff800ULL },
	{ 19,	64,	54,	0x0000001ffffc00ULL },
	{ 20,	64,	55,	0x0000001ffffe00ULL },
	{ 21,	64,	56,	0x0000001fffff00ULL },
	{ 22,	64,	57,	0x0000001fffff80ULL },
	{ 23,	64,	58,	0x0000001fffffc0ULL },
	{ 24,	64,	59,	0x0000001fffffe0ULL },
	{ 25,	64,	60,	0x0000001ffffff0ULL },
	{ 26,	64,	61,	0x0000001ffffff8ULL },
	{ 27,	64,	62,	0x0000001ffffffcULL },
	{ 28,	64,	63,	0x0000001ffffffeULL },
	{ 29,	64,	0,	0x0000001fffffffULL },
	{ 1,	64,	35,	0x00000020000000ULL },
	{ 2,	64,	36,	0x00000030000000ULL },
	{ 3,	64,	37,	0x00000038000000ULL },
	{ 4,	64,	38,	0x0000003c000000ULL },
	{ 5,	64,	39,	0x0000003e000000ULL },
	{ 6,	64,	40,	0x0000003f000000ULL },
	{ 7,	64,	41,	0x0000003f800000ULL },
	{ 8,	64,	42,	0x0000003fc00000ULL },
	{ 9,	64,	43,	0x0000003fe00000ULL },
	{ 10,	64,	44,	0x0000003ff00000ULL },
	{ 11,	64,	45,	0x0000003ff80000ULL },
	{ 12,	64,	46,	0x0000003ffc0000ULL },
	{ 13,	64,	47,	0x0000003ffe0000ULL },
	{ 14,	64,	48,	0x0000003fff0000ULL },
	{ 15,	64,	49,	0x0000003fff8000ULL },
	{ 16,	64,	50,	0x0000003fffc000ULL },
	{ 17,	64,	51,	0x0000003fffe000ULL },
	{ 18,	64,	52,	0x0000003ffff000ULL },
	{ 19,	64,	53,	0x0000003ffff800ULL },
	{ 20,	64,	54,	0x0000003ffffc00ULL },
	{ 21,	64,	55,	0x0000003ffffe00ULL },
	{ 22,	64,	56,	0x0000003fffff00ULL },
	{ 23,	64,	57,	0x0000003fffff80ULL },
	{ 24,	64,	58,	0x0000003fffffc0ULL },
	{ 25,	64,	59,	0x0000003fffffe0ULL },
	{ 26,	64,	60,	0x0000003ffffff0ULL },
	{ 27,	64,	61,	0x0000003ffffff8ULL },
	{ 28,	64,	62,	0x0000003ffffffcULL },
	{ 29,	64,	63,	0x0000003ffffffeULL },
	{ 30,	64,	0,	0x0000003fffffffULL },
	{ 1,	64,	34,	0x00000040000000ULL },
	{ 2,	64,	35,	0x00000060000000ULL },
	{ 3,	64,	36,	0x00000070000000ULL },
	{ 4,	64,	37,	0x00000078000000ULL },
	{ 5,	64,	38,	0x0000007c000000ULL },
	{ 6,	64,	39,	0x0000007e000000ULL },
	{ 7,	64,	40,	0x0000007f000000ULL },
	{ 8,	64,	41,	0x0000007f800000ULL },
	{ 9,	64,	42,	0x0000007fc00000ULL },
	{ 10,	64,	43,	0x0000007fe00000ULL },
	{ 11,	64,	44,	0x0000007ff00000ULL },
	{ 12,	64,	45,	0x0000007ff80000ULL },
	{ 13,	64,	46,	0x0000007ffc0000ULL },
	{ 14,	64,	47,	0x0000007ffe0000ULL },
	{ 15,	64,	48,	0x0000007fff0000ULL },
	{ 16,	64,	49,	0x0000007fff8000ULL },
	{ 17,	64,	50,	0x0000007fffc000ULL },
	{ 18,	64,	51,	0x0000007fffe000ULL },
	{ 19,	64,	52,	0x0000007ffff000ULL },
	{ 20,	64,	53,	0x0000007ffff800ULL },
	{ 21,	64,	54,	0x0000007ffffc00ULL },
	{ 22,	64,	55,	0x0000007ffffe00ULL },
	{ 23,	64,	56,	0x0000007fffff00ULL },
	{ 24,	64,	57,	0x0000007fffff80ULL },
	{ 25,	64,	58,	0x0000007fffffc0ULL },
	{ 26,	64,	59,	0x0000007fffffe0ULL },
	{ 27,	64,	60,	0x0000007ffffff0ULL },
	{ 28,	64,	61,	0x0000007ffffff8ULL },
	{ 29,	64,	62,	0x0000007ffffffcULL },
	{ 30,	64,	63,	0x0000007ffffffeULL },
	{ 31,	64,	0,	0x0000007fffffffULL },
	{ 1,	64,	33,	0x00000080000000ULL },
	{ 2,	64,	34,	0x000000c0000000ULL },
	{ 3,	64,	35,	0x000000e0000000ULL },
	{ 4,	64,	36,	0x000000f0000000ULL },
	{ 5,	64,	37,	0x000000f8000000ULL },
	{ 6,	64,	38,	0x000000fc000000ULL },
	{ 7,	64,	39,	0x000000fe000000ULL },
	{ 8,	64,	40,	0x000000ff000000ULL },
	{ 9,	64,	41,	0x000000ff800000ULL },
	{ 10,	64,	42,	0x000000ffc00000ULL },
	{ 11,	64,	43,	0x000000ffe00000ULL },
	{ 12,	64,	44,	0x000000fff00000ULL },
	{ 13,	64,	45,	0x000000fff80000ULL },
	{ 14,	64,	46,	0x000000fffc0000ULL },
	{ 15,	64,	47,	0x000000fffe0000ULL },
	{ 16,	64,	48,	0x000000ffff0000ULL },
	{ 17,	64,	49,	0x000000ffff8000ULL },
	{ 18,	64,	50,	0x000000ffffc000ULL },
	{ 19,	64,	51,	0x000000ffffe000ULL },
	{ 20,	64,	52,	0x000000fffff000ULL },
	{ 21,	64,	53,	0x000000fffff800ULL },
	{ 22,	64,	54,	0x000000fffffc00ULL },
	{ 23,	64,	55,	0x000000fffffe00ULL },
	{ 24,	64,	56,	0x000000ffffff00ULL },
	{ 25,	64,	57,	0x000000ffffff80ULL },
	{ 26,	64,	58,	0x000000ffffffc0ULL },
	{ 27,	64,	59,	0x000000ffffffe0ULL },
	{ 28,	64,	60,	0x000000fffffff0ULL },
	{ 29,	64,	61,	0x000000fffffff8ULL },
	{ 30,	64,	62,	0x000000fffffffcULL },
	{ 31,	64,	63,	0x000000fffffffeULL },
	{ 32,	64,	0,	0x000000ffffffffULL },
	{ 1,	64,	32,	0x00000100000000ULL },
	{ 1,	32,	0,	0x00000100000001ULL },
	{ 2,	64,	33,	0x00000180000000ULL },
	{ 3,	64,	34,	0x000001c0000000ULL },
	{ 4,	64,	35,	0x000001e0000000ULL },
	{ 5,	64,	36,	0x000001f0000000ULL },
	{ 6,	64,	37,	0x000001f8000000ULL },
	{ 7,	64,	38,	0x000001fc000000ULL },
	{ 8,	64,	39,	0x000001fe000000ULL },
	{ 9,	64,	40,	0x000001ff000000ULL },
	{ 10,	64,	41,	0x000001ff800000ULL },
	{ 11,	64,	42,	0x000001ffc00000ULL },
	{ 12,	64,	43,	0x000001ffe00000ULL },
	{ 13,	64,	44,	0x000001fff00000ULL },
	{ 14,	64,	45,	0x000001fff80000ULL },
	{ 15,	64,	46,	0x000001fffc0000ULL },
	{ 16,	64,	47,	0x000001fffe0000ULL },
	{ 17,	64,	48,	0x000001ffff0000ULL },
	{ 18,	64,	49,	0x000001ffff8000ULL },
	{ 19,	64,	50,	0x000001ffffc000ULL },
	{ 20,	64,	51,	0x000001ffffe000ULL },
	{ 21,	64,	52,	0x000001fffff000ULL },
	{ 22,	64,	53,	0x000001fffff800ULL },
	{ 23,	64,	54,	0x000001fffffc00ULL },
	{ 24,	64,	55,	0x000001fffffe00ULL },
	{ 25,	64,	56,	0x000001ffffff00ULL },
	{ 26,	64,	57,	0x000001ffffff80ULL },
	{ 27,	64,	58,	0x000001ffffffc0ULL },
	{ 28,	64,	59,	0x000001ffffffe0ULL },
	{ 29,	64,	60,	0x000001fffffff0ULL },
	{ 30,	64,	61,	0x000001fffffff8ULL },
	{ 31,	64,	62,	0x000001fffffffcULL },
	{ 32,	64,	63,	0x000001fffffffeULL },
	{ 33,	64,	0,	0x000001ffffffffULL },
	{ 1,	64,	31,	0x00000200000000ULL },
	{ 1,	32,	31,	0x00000200000002ULL },
	{ 2,	64,	32,	0x00000300000000ULL },
	{ 2,	32,	0,	0x00000300000003ULL },
	{ 3,	64,	33,	0x00000380000000ULL },
	{ 4,	64,	34,	0x000003c0000000ULL },
	{ 5,	64,	35,	0x000003e0000000ULL },
	{ 6,	64,	36,	0x000003f0000000ULL },
	{ 7,	64,	37,	0x000003f8000000ULL },
	{ 8,	64,	38,	0x000003fc000000ULL },
	{ 9,	64,	39,	0x000003fe000000ULL },
	{ 10,	64,	40,	0x000003ff000000ULL },
	{ 11,	64,	41,	0x000003ff800000ULL },
	{ 12,	64,	42,	0x000003ffc00000ULL },
	{ 13,	64,	43,	0x000003ffe00000ULL },
	{ 14,	64,	44,	0x000003fff00000ULL },
	{ 15,	64,	45,	0x000003fff80000ULL },
	{ 16,	64,	46,	0x000003fffc0000ULL },
	{ 17,	64,	47,	0x000003fffe0000ULL },
	{ 18,	64,	48,	0x000003ffff0000ULL },
	{ 19,	64,	49,	0x000003ffff8000ULL },
	{ 20,	64,	50,	0x000003ffffc000ULL },
	{ 21,	64,	51,	0x000003ffffe000ULL },
	{ 22,	64,	52,	0x000003fffff000ULL },
	{ 23,	64,	53,	0x000003fffff800ULL },
	{ 24,	64,	54,	0x000003fffffc00ULL },
	{ 25,	64,	55,	0x000003fffffe00ULL },
	{ 26,	64,	56,	0x000003ffffff00ULL },
	{ 27,	64,	57,	0x000003ffffff80ULL },
	{ 28,	64,	58,	0x000003ffffffc0ULL },
	{ 29,	64,	59,	0x000003ffffffe0ULL },
	{ 30,	64,	60,	0x000003fffffff0ULL },
	{ 31,	64,	61,	0x000003fffffff8ULL },
	{ 32,	64,	62,	0x000003fffffffcULL },
	{ 33,	64,	63,	0x000003fffffffeULL },
	{ 34,	64,	0,	0x000003ffffffffULL },
	{ 1,	64,	30,	0x00000400000000ULL },
	{ 1,	32,	30,	0x00000400000004ULL },
	{ 2,	64,	31,	0x00000600000000ULL },
	{ 2,	32,	31,	0x00000600000006ULL },
	{ 3,	64,	32,	0x00000700000000ULL },
	{ 3,	32,	0,	0x00000700000007ULL },
	{ 4,	64,	33,	0x00000780000000ULL },
	{ 5,	64,	34,	0x000007c0000000ULL },
	{ 6,	64,	35,	0x000007e0000000ULL },
	{ 7,	64,	36,	0x000007f0000000ULL },
	{ 8,	64,	37,	0x000007f8000000ULL },
	{ 9,	64,	38,	0x000007fc000000ULL },
	{ 10,	64,	39,	0x000007fe000000ULL },
	{ 11,	64,	40,	0x000007ff000000ULL },
	{ 12,	64,	41,	0x000007ff800000ULL },
	{ 13,	64,	42,	0x000007ffc00000ULL },
	{ 14,	64,	43,	0x000007ffe00000ULL },
	{ 15,	64,	44,	0x000007fff00000ULL },
	{ 16,	64,	45,	0x000007fff80000ULL },
	{ 17,	64,	46,	0x000007fffc0000ULL },
	{ 18,	64,	47,	0x000007fffe0000ULL },
	{ 19,	64,	48,	0x000007ffff0000ULL },
	{ 20,	64,	49,	0x000007ffff8000ULL },
	{ 21,	64,	50,	0x000007ffffc000ULL },
	{ 22,	64,	51,	0x000007ffffe000ULL },
	{ 23,	64,	52,	0x000007fffff000ULL },
	{ 24,	64,	53,	0x000007fffff800ULL },
	{ 25,	64,	54,	0x000007fffffc00ULL },
	{ 26,	64,	55,	0x000007fffffe00ULL },
	{ 27,	64,	56,	0x000007ffffff00ULL },
	{ 28,	64,	57,	0x000007ffffff80ULL },
	{ 29,	64,	58,	0x000007ffffffc0ULL },
	{ 30,	64,	59,	0x000007ffffffe0ULL },
	{ 31,	64,	60,	0x000007fffffff0ULL },
	{ 32,	64,	61,	0x000007fffffff8ULL },
	{ 33,	64,	62,	0x000007fffffffcULL },
	{ 34,	64,	63,	0x000007fffffffeULL },
	{ 35,	64,	0,	0x000007ffffffffULL },
	{ 1,	64,	29,	0x00000800000000ULL },
	{ 1,	32,	29,	0x00000800000008ULL },
	{ 2,	64,	30,	0x00000c00000000ULL },
	{ 2,	32,	30,	0x00000c0000000cULL },
	{ 3,	64,	31,	0x00000e00000000ULL },
	{ 3,	32,	31,	0x00000e0000000eULL },
	{ 4,	64,	32,	0x00000f00000000ULL },
	{ 4,	32,	0,	0x00000f0000000fULL },
	{ 5,	64,	33,	0x00000f80000000ULL },
	{ 6,	64,	34,	0x00000fc0000000ULL },
	{ 7,	64,	35,	0x00000fe0000000ULL },
	{ 8,	64,	36,	0x00000ff0000000ULL },
	{ 9,	64,	37,	0x00000ff8000000ULL },
	{ 10,	64,	38,	0x00000ffc000000ULL },
	{ 11,	64,	39,	0x00000ffe000000ULL },
	{ 12,	64,	40,	0x00000fff000000ULL },
	{ 13,	64,	41,	0x00000fff800000ULL },
	{ 14,	64,	42,	0x00000fffc00000ULL },
	{ 15,	64,	43,	0x00000fffe00000ULL },
	{ 16,	64,	44,	0x00000ffff00000ULL },
	{ 17,	64,	45,	0x00000ffff80000ULL },
	{ 18,	64,	46,	0x00000ffffc0000ULL },
	{ 19,	64,	47,	0x00000ffffe0000ULL },
	{ 20,	64,	48,	0x00000fffff0000ULL },
	{ 21,	64,	49,	0x00000fffff8000ULL },
	{ 22,	64,	50,	0x00000fffffc000ULL },
	{ 23,	64,	51,	0x00000fffffe000ULL },
	{ 24,	64,	52,	0x00000ffffff000ULL },
	{ 25,	64,	53,	0x00000ffffff800ULL },
	{ 26,	64,	54,	0x00000ffffffc00ULL },
	{ 27,	64,	55,	0x00000ffffffe00ULL },
	{ 28,	64,	56,	0x00000fffffff00ULL },
	{ 29,	64,	57,	0x00000fffffff80ULL },
	{ 30,	64,	58,	0x00000fffffffc0ULL },
	{ 31,	64,	59,	0x00000fffffffe0ULL },
	{ 32,	64,	60,	0x00000ffffffff0ULL },
	{ 33,	64,	61,	0x00000ffffffff8ULL },
	{ 34,	64,	62,	0x00000ffffffffcULL },
	{ 35,	64,	63,	0x00000ffffffffeULL },
	{ 36,	64,	0,	0x00000fffffffffULL },
	{ 1,	64,	28,	0x00001000000000ULL },
	{ 1,	32,	28,	0x00001000000010ULL },
	{ 2,	64,	29,	0x00001800000000ULL },
	{ 2,	32,	29,	0x00001800000018ULL },
	{ 3,	64,	30,	0x00001c00000000ULL },
	{ 3,	32,	30,	0x00001c0000001cULL },
	{ 4,	64,	31,	0x00001e00000000ULL },
	{ 4,	32,	31,	0x00001e0000001eULL },
	{ 5,	64,	32,	0x00001f00000000ULL },
	{ 5,	32,	0,	0x00001f0000001fULL },
	{ 6,	64,	33,	0x00001f80000000ULL },
	{ 7,	64,	34,	0x00001fc0000000ULL },
	{ 8,	64,	35,	0x00001fe0000000ULL },
	{ 9,	64,	36,	0x00001ff0000000ULL },
	{ 10,	64,	37,	0x00001ff8000000ULL },
	{ 11,	64,	38,	0x00001ffc000000ULL },
	{ 12,	64,	39,	0x00001ffe000000ULL },
	{ 13,	64,	40,	0x00001fff000000ULL },
	{ 14,	64,	41,	0x00001fff800000ULL },
	{ 15,	64,	42,	0x00001fffc00000ULL },
	{ 16,	64,	43,	0x00001fffe00000ULL },
	{ 17,	64,	44,	0x00001ffff00000ULL },
	{ 18,	64,	45,	0x00001ffff80000ULL },
	{ 19,	64,	46,	0x00001ffffc0000ULL },
	{ 20,	64,	47,	0x00001ffffe0000ULL },
	{ 21,	64,	48,	0x00001fffff0000ULL },
	{ 22,	64,	49,	0x00001fffff8000ULL },
	{ 23,	64,	50,	0x00001fffffc000ULL },
	{ 24,	64,	51,	0x00001fffffe000ULL },
	{ 25,	64,	52,	0x00001ffffff000ULL },
	{ 26,	64,	53,	0x00001ffffff800ULL },
	{ 27,	64,	54,	0x00001ffffffc00ULL },
	{ 28,	64,	55,	0x00001ffffffe00ULL },
	{ 29,	64,	56,	0x00001fffffff00ULL },
	{ 30,	64,	57,	0x00001fffffff80ULL },
	{ 31,	64,	58,	0x00001fffffffc0ULL },
	{ 32,	64,	59,	0x00001fffffffe0ULL },
	{ 33,	64,	60,	0x00001ffffffff0ULL },
	{ 34,	64,	61,	0x00001ffffffff8ULL },
	{ 35,	64,	62,	0x00001ffffffffcULL },
	{ 36,	64,	63,	0x00001ffffffffeULL },
	{ 37,	64,	0,	0x00001fffffffffULL },
	{ 1,	64,	27,	0x00002000000000ULL },
	{ 1,	32,	27,	0x00002000000020ULL },
	{ 2,	64,	28,	0x00003000000000ULL },
	{ 2,	32,	28,	0x00003000000030ULL },
	{ 3,	64,	29,	0x00003800000000ULL },
	{ 3,	32,	29,	0x00003800000038ULL },
	{ 4,	64,	30,	0x00003c00000000ULL },
	{ 4,	32,	30,	0x00003c0000003cULL },
	{ 5,	64,	31,	0x00003e00000000ULL },
	{ 5,	32,	31,	0x00003e0000003eULL },
	{ 6,	64,	32,	0x00003f00000000ULL },
	{ 6,	32,	0,	0x00003f0000003fULL },
	{ 7,	64,	33,	0x00003f80000000ULL },
	{ 8,	64,	34,	0x00003fc0000000ULL },
	{ 9,	64,	35,	0x00003fe0000000ULL },
	{ 10,	64,	36,	0x00003ff0000000ULL },
	{ 11,	64,	37,	0x00003ff8000000ULL },
	{ 12,	64,	38,	0x00003ffc000000ULL },
	{ 13,	64,	39,	0x00003ffe000000ULL },
	{ 14,	64,	40,	0x00003fff000000ULL },
	{ 15,	64,	41,	0x00003fff800000ULL },
	{ 16,	64,	42,	0x00003fffc00000ULL },
	{ 17,	64,	43,	0x00003fffe00000ULL },
	{ 18,	64,	44,	0x00003ffff00000ULL },
	{ 19,	64,	45,	0x00003ffff80000ULL },
	{ 20,	64,	46,	0x00003ffffc0000ULL },
	{ 21,	64,	47,	0x00003ffffe0000ULL },
	{ 22,	64,	48,	0x00003fffff0000ULL },
	{ 23,	64,	49,	0x00003fffff8000ULL },
	{ 24,	64,	50,	0x00003fffffc000ULL },
	{ 25,	64,	51,	0x00003fffffe000ULL },
	{ 26,	64,	52,	0x00003ffffff000ULL },
	{ 27,	64,	53,	0x00003ffffff800ULL },
	{ 28,	64,	54,	0x00003ffffffc00ULL },
	{ 29,	64,	55,	0x00003ffffffe00ULL },
	{ 30,	64,	56,	0x00003fffffff00ULL },
	{ 31,	64,	57,	0x00003fffffff80ULL },
	{ 32,	64,	58,	0x00003fffffffc0ULL },
	{ 33,	64,	59,	0x00003fffffffe0ULL },
	{ 34,	64,	60,	0x00003ffffffff0ULL },
	{ 35,	64,	61,	0x00003ffffffff8ULL },
	{ 36,	64,	62,	0x00003ffffffffcULL },
	{ 37,	64,	63,	0x00003ffffffffeULL },
	{ 38,	64,	0,	0x00003fffffffffULL },
	{ 1,	64,	26,	0x00004000000000ULL },
	{ 1,	32,	26,	0x00004000000040ULL },
	{ 2,	64,	27,	0x00006000000000ULL },
	{ 2,	32,	27,	0x00006000000060ULL },
	{ 3,	64,	28,	0x00007000000000ULL },
	{ 3,	32,	28,	0x00007000000070ULL },
	{ 4,	64,	29,	0x00007800000000ULL },
	{ 4,	32,	29,	0x00007800000078ULL },
	{ 5,	64,	30,	0x00007c00000000ULL },
	{ 5,	32,	30,	0x00007c0000007cULL },
	{ 6,	64,	31,	0x00007e00000000ULL },
	{ 6,	32,	31,	0x00007e0000007eULL },
	{ 7,	64,	32,	0x00007f00000000ULL },
	{ 7,	32,	0,	0x00007f0000007fULL },
	{ 8,	64,	33,	0x00007f80000000ULL },
	{ 9,	64,	34,	0x00007fc0000000ULL },
	{ 10,	64,	35,	0x00007fe0000000ULL },
	{ 11,	64,	36,	0x00007ff0000000ULL },
	{ 12,	64,	37,	0x00007ff8000000ULL },
	{ 13,	64,	38,	0x00007ffc000000ULL },
	{ 14,	64,	39,	0x00007ffe000000ULL },
	{ 15,	64,	40,	0x00007fff000000ULL },
	{ 16,	64,	41,	0x00007fff800000ULL },
	{ 17,	64,	42,	0x00007fffc00000ULL },
	{ 18,	64,	43,	0x00007fffe00000ULL },
	{ 19,	64,	44,	0x00007ffff00000ULL },
	{ 20,	64,	45,	0x00007ffff80000ULL },
	{ 21,	64,	46,	0x00007ffffc0000ULL },
	{ 22,	64,	47,	0x00007ffffe0000ULL },
	{ 23,	64,	48,	0x00007fffff0000ULL },
	{ 24,	64,	49,	0x00007fffff8000ULL },
	{ 25,	64,	50,	0x00007fffffc000ULL },
	{ 26,	64,	51,	0x00007fffffe000ULL },
	{ 27,	64,	52,	0x00007ffffff000ULL },
	{ 28,	64,	53,	0x00007ffffff800ULL },
	{ 29,	64,	54,	0x00007ffffffc00ULL },
	{ 30,	64,	55,	0x00007ffffffe00ULL },
	{ 31,	64,	56,	0x00007fffffff00ULL },
	{ 32,	64,	57,	0x00007fffffff80ULL },
	{ 33,	64,	58,	0x00007fffffffc0ULL },
	{ 34,	64,	59,	0x00007fffffffe0ULL },
	{ 35,	64,	60,	0x00007ffffffff0ULL },
	{ 36,	64,	61,	0x00007ffffffff8ULL },
	{ 37,	64,	62,	0x00007ffffffffcULL },
	{ 38,	64,	63,	0x00007ffffffffeULL },
	{ 39,	64,	0,	0x00007fffffffffULL },
	{ 1,	64,	25,	0x00008000000000ULL },
	{ 1,	32,	25,	0x00008000000080ULL },
	{ 2,	64,	26,	0x0000c000000000ULL },
	{ 2,	32,	26,	0x0000c0000000c0ULL },
	{ 3,	64,	27,	0x0000e000000000ULL },
	{ 3,	32,	27,	0x0000e0000000e0ULL },
	{ 4,	64,	28,	0x0000f000000000ULL },
	{ 4,	32,	28,	0x0000f0000000f0ULL },
	{ 5,	64,	29,	0x0000f800000000ULL },
	{ 5,	32,	29,	0x0000f8000000f8ULL },
	{ 6,	64,	30,	0x0000fc00000000ULL },
	{ 6,	32,	30,	0x0000fc000000fcULL },
	{ 7,	64,	31,	0x0000fe00000000ULL },
	{ 7,	32,	31,	0x0000fe000000feULL },
	{ 8,	64,	32,	0x0000ff00000000ULL },
	{ 8,	32,	0,	0x0000ff000000ffULL },
	{ 9,	64,	33,	0x0000ff80000000ULL },
	{ 10,	64,	34,	0x0000ffc0000000ULL },
	{ 11,	64,	35,	0x0000ffe0000000ULL },
	{ 12,	64,	36,	0x0000fff0000000ULL },
	{ 13,	64,	37,	0x0000fff8000000ULL },
	{ 14,	64,	38,	0x0000fffc000000ULL },
	{ 15,	64,	39,	0x0000fffe000000ULL },
	{ 16,	64,	40,	0x0000ffff000000ULL },
	{ 17,	64,	41,	0x0000ffff800000ULL },
	{ 18,	64,	42,	0x0000ffffc00000ULL },
	{ 19,	64,	43,	0x0000ffffe00000ULL },
	{ 20,	64,	44,	0x0000fffff00000ULL },
	{ 21,	64,	45,	0x0000fffff80000ULL },
	{ 22,	64,	46,	0x0000fffffc0000ULL },
	{ 23,	64,	47,	0x0000fffffe0000ULL },
	{ 24,	64,	48,	0x0000ffffff0000ULL },
	{ 25,	64,	49,	0x0000ffffff8000ULL },
	{ 26,	64,	50,	0x0000ffffffc000ULL },
	{ 27,	64,	51,	0x0000ffffffe000ULL },
	{ 28,	64,	52,	0x0000fffffff000ULL },
	{ 29,	64,	53,	0x0000fffffff800ULL },
	{ 30,	64,	54,	0x0000fffffffc00ULL },
	{ 31,	64,	55,	0x0000fffffffe00ULL },
	{ 32,	64,	56,	0x0000ffffffff00ULL },
	{ 33,	64,	57,	0x0000ffffffff80ULL },
	{ 34,	64,	58,	0x0000ffffffffc0ULL },
	{ 35,	64,	59,	0x0000ffffffffe0ULL },
	{ 36,	64,	60,	0x0000fffffffff0ULL },
	{ 37,	64,	61,	0x0000fffffffff8ULL },
	{ 38,	64,	62,	0x0000fffffffffcULL },
	{ 39,	64,	63,	0x0000fffffffffeULL },
	{ 40,	64,	0,	0x0000ffffffffffULL },
	{ 1,	64,	24,	0x00010000000000ULL },
	{ 1,	32,	24,	0x00010000000100ULL },
	{ 2,	64,	25,	0x00018000000000ULL },
	{ 2,	32,	25,	0x00018000000180ULL },
	{ 3,	64,	26,	0x0001c000000000ULL },
	{ 3,	32,	26,	0x0001c0000001c0ULL },
	{ 4,	64,	27,	0x0001e000000000ULL },
	{ 4,	32,	27,	0x0001e0000001e0ULL },
	{ 5,	64,	28,	0x0001f000000000ULL },
	{ 5,	32,	28,	0x0001f0000001f0ULL },
	{ 6,	64,	29,	0x0001f800000000ULL },
	{ 6,	32,	29,	0x0001f8000001f8ULL },
	{ 7,	64,	30,	0x0001fc00000000ULL },
	{ 7,	32,	30,	0x0001fc000001fcULL },
	{ 8,	64,	31,	0x0001fe00000000ULL },
	{ 8,	32,	31,	0x0001fe000001feULL },
	{ 9,	64,	32,	0x0001ff00000000ULL },
	{ 9,	32,	0,	0x0001ff000001ffULL },
	{ 10,	64,	33,	0x0001ff80000000ULL },
	{ 11,	64,	34,	0x0001ffc0000000ULL },
	{ 12,	64,	35,	0x0001ffe0000000ULL },
	{ 13,	64,	36,	0x0001fff0000000ULL },
	{ 14,	64,	37,	0x0001fff8000000ULL },
	{ 15,	64,	38,	0x0001fffc000000ULL },
	{ 16,	64,	39,	0x0001fffe000000ULL },
	{ 17,	64,	40,	0x0001ffff000000ULL },
	{ 18,	64,	41,	0x0001ffff800000ULL },
	{ 19,	64,	42,	0x0001ffffc00000ULL },
	{ 20,	64,	43,	0x0001ffffe00000ULL },
	{ 21,	64,	44,	0x0001fffff00000ULL },
	{ 22,	64,	45,	0x0001fffff80000ULL },
	{ 23,	64,	46,	0x0001fffffc0000ULL },
	{ 24,	64,	47,	0x0001fffffe0000ULL },
	{ 25,	64,	48,	0x0001ffffff0000ULL },
	{ 26,	64,	49,	0x0001ffffff8000ULL },
	{ 27,	64,	50,	0x0001ffffffc000ULL },
	{ 28,	64,	51,	0x0001ffffffe000ULL },
	{ 29,	64,	52,	0x0001fffffff000ULL },
	{ 30,	64,	53,	0x0001fffffff800ULL },
	{ 31,	64,	54,	0x0001fffffffc00ULL },
	{ 32,	64,	55,	0x0001fffffffe00ULL },
	{ 33,	64,	56,	0x0001ffffffff00ULL },
	{ 34,	64,	57,	0x0001ffffffff80ULL },
	{ 35,	64,	58,	0x0001ffffffffc0ULL },
	{ 36,	64,	59,	0x0001ffffffffe0ULL },
	{ 37,	64,	60,	0x0001fffffffff0ULL },
	{ 38,	64,	61,	0x0001fffffffff8ULL },
	{ 39,	64,	62,	0x0001fffffffffcULL },
	{ 40,	64,	63,	0x0001fffffffffeULL },
	{ 41,	64,	0,	0x0001ffffffffffULL },
	{ 1,	64,	23,	0x00020000000000ULL },
	{ 1,	32,	23,	0x00020000000200ULL },
	{ 2,	64,	24,	0x00030000000000ULL },
	{ 2,	32,	24,	0x00030000000300ULL },
	{ 3,	64,	25,	0x00038000000000ULL },
	{ 3,	32,	25,	0x00038000000380ULL },
	{ 4,	64,	26,	0x0003c000000000ULL },
	{ 4,	32,	26,	0x0003c0000003c0ULL },
	{ 5,	64,	27,	0x0003e000000000ULL },
	{ 5,	32,	27,	0x0003e0000003e0ULL },
	{ 6,	64,	28,	0x0003f000000000ULL },
	{ 6,	32,	28,	0x0003f0000003f0ULL },
	{ 7,	64,	29,	0x0003f800000000ULL },
	{ 7,	32,	29,	0x0003f8000003f8ULL },
	{ 8,	64,	30,	0x0003fc00000000ULL },
	{ 8,	32,	30,	0x0003fc000003fcULL },
	{ 9,	64,	31,	0x0003fe00000000ULL },
	{ 9,	32,	31,	0x0003fe000003feULL },
	{ 10,	64,	32,	0x0003ff00000000ULL },
	{ 10,	32,	0,	0x0003ff000003ffULL },
	{ 11,	64,	33,	0x0003ff80000000ULL },
	{ 12,	64,	34,	0x0003ffc0000000ULL },
	{ 13,	64,	35,	0x0003ffe0000000ULL },
	{ 14,	64,	36,	0x0003fff0000000ULL },
	{ 15,	64,	37,	0x0003fff8000000ULL },
	{ 16,	64,	38,	0x0003fffc000000ULL },
	{ 17,	64,	39,	0x0003fffe000000ULL },
	{ 18,	64,	40,	0x0003ffff000000ULL },
	{ 19,	64,	41,	0x0003ffff800000ULL },
	{ 20,	64,	42,	0x0003ffffc00000ULL },
	{ 21,	64,	43,	0x0003ffffe00000ULL },
	{ 22,	64,	44,	0x0003fffff00000ULL },
	{ 23,	64,	45,	0x0003fffff80000ULL },
	{ 24,	64,	46,	0x0003fffffc0000ULL },
	{ 25,	64,	47,	0x0003fffffe0000ULL },
	{ 26,	64,	48,	0x0003ffffff0000ULL },
	{ 27,	64,	49,	0x0003ffffff8000ULL },
	{ 28,	64,	50,	0x0003ffffffc000ULL },
	{ 29,	64,	51,	0x0003ffffffe000ULL },
	{ 30,	64,	52,	0x0003fffffff000ULL },
	{ 31,	64,	53,	0x0003fffffff800ULL },
	{ 32,	64,	54,	0x0003fffffffc00ULL },
	{ 33,	64,	55,	0x0003fffffffe00ULL },
	{ 34,	64,	56,	0x0003ffffffff00ULL },
	{ 35,	64,	57,	0x0003ffffffff80ULL },
	{ 36,	64,	58,	0x0003ffffffffc0ULL },
	{ 37,	64,	59,	0x0003ffffffffe0ULL },
	{ 38,	64,	60,	0x0003fffffffff0ULL },
	{ 39,	64,	61,	0x0003fffffffff8ULL },
	{ 40,	64,	62,	0x0003fffffffffcULL },
	{ 41,	64,	63,	0x0003fffffffffeULL },
	{ 42,	64,	0,	0x0003ffffffffffULL },
	{ 1,	64,	22,	0x00040000000000ULL },
	{ 1,	32,	22,	0x00040000000400ULL },
	{ 2,	64,	23,	0x00060000000000ULL },
	{ 2,	32,	23,	0x00060000000600ULL },
	{ 3,	64,	24,	0x00070000000000ULL },
	{ 3,	32,	24,	0x00070000000700ULL },
	{ 4,	64,	25,	0x00078000000000ULL },
	{ 4,	32,	25,	0x00078000000780ULL },
	{ 5,	64,	26,	0x0007c000000000ULL },
	{ 5,	32,	26,	0x0007c0000007c0ULL },
	{ 6,	64,	27,	0x0007e000000000ULL },
	{ 6,	32,	27,	0x0007e0000007e0ULL },
	{ 7,	64,	28,	0x0007f000000000ULL },
	{ 7,	32,	28,	0x0007f0000007f0ULL },
	{ 8,	64,	29,	0x0007f800000000ULL },
	{ 8,	32,	29,	0x0007f8000007f8ULL },
	{ 9,	64,	30,	0x0007fc00000000ULL },
	{ 9,	32,	30,	0x0007fc000007fcULL },
	{ 10,	64,	31,	0x0007fe00000000ULL },
	{ 10,	32,	31,	0x0007fe000007feULL },
	{ 11,	64,	32,	0x0007ff00000000ULL },
	{ 11,	32,	0,	0x0007ff000007ffULL },
	{ 12,	64,	33,	0x0007ff80000000ULL },
	{ 13,	64,	34,	0x0007ffc0000000ULL },
	{ 14,	64,	35,	0x0007ffe0000000ULL },
	{ 15,	64,	36,	0x0007fff0000000ULL },
	{ 16,	64,	37,	0x0007fff8000000ULL },
	{ 17,	64,	38,	0x0007fffc000000ULL },
	{ 18,	64,	39,	0x0007fffe000000ULL },
	{ 19,	64,	40,	0x0007ffff000000ULL },
	{ 20,	64,	41,	0x0007ffff800000ULL },
	{ 21,	64,	42,	0x0007ffffc00000ULL },
	{ 22,	64,	43,	0x0007ffffe00000ULL },
	{ 23,	64,	44,	0x0007fffff00000ULL },
	{ 24,	64,	45,	0x0007fffff80000ULL },
	{ 25,	64,	46,	0x0007fffffc0000ULL },
	{ 26,	64,	47,	0x0007fffffe0000ULL },
	{ 27,	64,	48,	0x0007ffffff0000ULL },
	{ 28,	64,	49,	0x0007ffffff8000ULL },
	{ 29,	64,	50,	0x0007ffffffc000ULL },
	{ 30,	64,	51,	0x0007ffffffe000ULL },
	{ 31,	64,	52,	0x0007fffffff000ULL },
	{ 32,	64,	53,	0x0007fffffff800ULL },
	{ 33,	64,	54,	0x0007fffffffc00ULL },
	{ 34,	64,	55,	0x0007fffffffe00ULL },
	{ 35,	64,	56,	0x0007ffffffff00ULL },
	{ 36,	64,	57,	0x0007ffffffff80ULL },
	{ 37,	64,	58,	0x0007ffffffffc0ULL },
	{ 38,	64,	59,	0x0007ffffffffe0ULL },
	{ 39,	64,	60,	0x0007fffffffff0ULL },
	{ 40,	64,	61,	0x0007fffffffff8ULL },
	{ 41,	64,	62,	0x0007fffffffffcULL },
	{ 42,	64,	63,	0x0007fffffffffeULL },
	{ 43,	64,	0,	0x0007ffffffffffULL },
	{ 1,	64,	21,	0x00080000000000ULL },
	{ 1,	32,	21,	0x00080000000800ULL },
	{ 2,	64,	22,	0x000c0000000000ULL },
	{ 2,	32,	22,	0x000c0000000c00ULL },
	{ 3,	64,	23,	0x000e0000000000ULL },
	{ 3,	32,	23,	0x000e0000000e00ULL },
	{ 4,	64,	24,	0x000f0000000000ULL },
	{ 4,	32,	24,	0x000f0000000f00ULL },
	{ 5,	64,	25,	0x000f8000000000ULL },
	{ 5,	32,	25,	0x000f8000000f80ULL },
	{ 6,	64,	26,	0x000fc000000000ULL },
	{ 6,	32,	26,	0x000fc000000fc0ULL },
	{ 7,	64,	27,	0x000fe000000000ULL },
	{ 7,	32,	27,	0x000fe000000fe0ULL },
	{ 8,	64,	28,	0x000ff000000000ULL },
	{ 8,	32,	28,	0x000ff000000ff0ULL },
	{ 9,	64,	29,	0x000ff800000000ULL },
	{ 9,	32,	29,	0x000ff800000ff8ULL },
	{ 10,	64,	30,	0x000ffc00000000ULL },
	{ 10,	32,	30,	0x000ffc00000ffcULL },
	{ 11,	64,	31,	0x000ffe00000000ULL },
	{ 11,	32,	31,	0x000ffe00000ffeULL },
	{ 12,	64,	32,	0x000fff00000000ULL },
	{ 12,	32,	0,	0x000fff00000fffULL },
	{ 13,	64,	33,	0x000fff80000000ULL },
	{ 14,	64,	34,	0x000fffc0000000ULL },
	{ 15,	64,	35,	0x000fffe0000000ULL },
	{ 16,	64,	36,	0x000ffff0000000ULL },
	{ 17,	64,	37,	0x000ffff8000000ULL },
	{ 18,	64,	38,	0x000ffffc000000ULL },
	{ 19,	64,	39,	0x000ffffe000000ULL },
	{ 20,	64,	40,	0x000fffff000000ULL },
	{ 21,	64,	41,	0x000fffff800000ULL },
	{ 22,	64,	42,	0x000fffffc00000ULL },
	{ 23,	64,	43,	0x000fffffe00000ULL },
	{ 24,	64,	44,	0x000ffffff00000ULL },
	{ 25,	64,	45,	0x000ffffff80000ULL },
	{ 26,	64,	46,	0x000ffffffc0000ULL },
	{ 27,	64,	47,	0x000ffffffe0000ULL },
	{ 28,	64,	48,	0x000fffffff0000ULL },
	{ 29,	64,	49,	0x000fffffff8000ULL },
	{ 30,	64,	50,	0x000fffffffc000ULL },
	{ 31,	64,	51,	0x000fffffffe000ULL },
	{ 32,	64,	52,	0x000ffffffff000ULL },
	{ 33,	64,	53,	0x000ffffffff800ULL },
	{ 34,	64,	54,	0x000ffffffffc00ULL },
	{ 35,	64,	55,	0x000ffffffffe00ULL },
	{ 36,	64,	56,	0x000fffffffff00ULL },
	{ 37,	64,	57,	0x000fffffffff80ULL },
	{ 38,	64,	58,	0x000fffffffffc0ULL },
	{ 39,	64,	59,	0x000fffffffffe0ULL },
	{ 40,	64,	60,	0x000ffffffffff0ULL },
	{ 41,	64,	61,	0x000ffffffffff8ULL },
	{ 42,	64,	62,	0x000ffffffffffcULL },
	{ 43,	64,	63,	0x000ffffffffffeULL },
	{ 44,	64,	0,	0x000fffffffffffULL },
	{ 1,	64,	20,	0x00100000000000ULL },
	{ 1,	32,	20,	0x00100000001000ULL },
	{ 2,	64,	21,	0x00180000000000ULL },
	{ 2,	32,	21,	0x00180000001800ULL },
	{ 3,	64,	22,	0x001c0000000000ULL },
	{ 3,	32,	22,	0x001c0000001c00ULL },
	{ 4,	64,	23,	0x001e0000000000ULL },
	{ 4,	32,	23,	0x001e0000001e00ULL },
	{ 5,	64,	24,	0x001f0000000000ULL },
	{ 5,	32,	24,	0x001f0000001f00ULL },
	{ 6,	64,	25,	0x001f8000000000ULL },
	{ 6,	32,	25,	0x001f8000001f80ULL },
	{ 7,	64,	26,	0x001fc000000000ULL },
	{ 7,	32,	26,	0x001fc000001fc0ULL },
	{ 8,	64,	27,	0x001fe000000000ULL },
	{ 8,	32,	27,	0x001fe000001fe0ULL },
	{ 9,	64,	28,	0x001ff000000000ULL },
	{ 9,	32,	28,	0x001ff000001ff0ULL },
	{ 10,	64,	29,	0x001ff800000000ULL },
	{ 10,	32,	29,	0x001ff800001ff8ULL },
	{ 11,	64,	30,	0x001ffc00000000ULL },
	{ 11,	32,	30,	0x001ffc00001ffcULL },
	{ 12,	64,	31,	0x001ffe00000000ULL },
	{ 12,	32,	31,	0x001ffe00001ffeULL },
	{ 13,	64,	32,	0x001fff00000000ULL },
	{ 13,	32,	0,	0x001fff00001fffULL },
	{ 14,	64,	33,	0x001fff80000000ULL },
	{ 15,	64,	34,	0x001fffc0000000ULL },
	{ 16,	64,	35,	0x001fffe0000000ULL },
	{ 17,	64,	36,	0x001ffff0000000ULL },
	{ 18,	64,	37,	0x001ffff8000000ULL },
	{ 19,	64,	38,	0x001ffffc000000ULL },
	{ 20,	64,	39,	0x001ffffe000000ULL },
	{ 21,	64,	40,	0x001fffff000000ULL },
	{ 22,	64,	41,	0x001fffff800000ULL },
	{ 23,	64,	42,	0x001fffffc00000ULL },
	{ 24,	64,	43,	0x001fffffe00000ULL },
	{ 25,	64,	44,	0x001ffffff00000ULL },
	{ 26,	64,	45,	0x001ffffff80000ULL },
	{ 27,	64,	46,	0x001ffffffc0000ULL },
	{ 28,	64,	47,	0x001ffffffe0000ULL },
	{ 29,	64,	48,	0x001fffffff0000ULL },
	{ 30,	64,	49,	0x001fffffff8000ULL },
	{ 31,	64,	50,	0x001fffffffc000ULL },
	{ 32,	64,	51,	0x001fffffffe000ULL },
	{ 33,	64,	52,	0x001ffffffff000ULL },
	{ 34,	64,	53,	0x001ffffffff800ULL },
	{ 35,	64,	54,	0x001ffffffffc00ULL },
	{ 36,	64,	55,	0x001ffffffffe00ULL },
	{ 37,	64,	56,	0x001fffffffff00ULL },
	{ 38,	64,	57,	0x001fffffffff80ULL },
	{ 39,	64,	58,	0x001fffffffffc0ULL },
	{ 40,	64,	59,	0x001fffffffffe0ULL },
	{ 41,	64,	60,	0x001ffffffffff0ULL },
	{ 42,	64,	61,	0x001ffffffffff8ULL },
	{ 43,	64,	62,	0x001ffffffffffcULL },
	{ 44,	64,	63,	0x001ffffffffffeULL },
	{ 45,	64,	0,	0x001fffffffffffULL },
	{ 1,	64,	19,	0x00200000000000ULL },
	{ 1,	32,	19,	0x00200000002000ULL },
	{ 2,	64,	20,	0x00300000000000ULL },
	{ 2,	32,	20,	0x00300000003000ULL },
	{ 3,	64,	21,	0x00380000000000ULL },
	{ 3,	32,	21,	0x00380000003800ULL },
	{ 4,	64,	22,	0x003c0000000000ULL },
	{ 4,	32,	22,	0x003c0000003c00ULL },
	{ 5,	64,	23,	0x003e0000000000ULL },
	{ 5,	32,	23,	0x003e0000003e00ULL },
	{ 6,	64,	24,	0x003f0000000000ULL },
	{ 6,	32,	24,	0x003f0000003f00ULL },
	{ 7,	64,	25,	0x003f8000000000ULL },
	{ 7,	32,	25,	0x003f8000003f80ULL },
	{ 8,	64,	26,	0x003fc000000000ULL },
	{ 8,	32,	26,	0x003fc000003fc0ULL },
	{ 9,	64,	27,	0x003fe000000000ULL },
	{ 9,	32,	27,	0x003fe000003fe0ULL },
	{ 10,	64,	28,	0x003ff000000000ULL },
	{ 10,	32,	28,	0x003ff000003ff0ULL },
	{ 11,	64,	29,	0x003ff800000000ULL },
	{ 11,	32,	29,	0x003ff800003ff8ULL },
	{ 12,	64,	30,	0x003ffc00000000ULL },
	{ 12,	32,	30,	0x003ffc00003ffcULL },
	{ 13,	64,	31,	0x003ffe00000000ULL },
	{ 13,	32,	31,	0x003ffe00003ffeULL },
	{ 14,	64,	32,	0x003fff00000000ULL },
	{ 14,	32,	0,	0x003fff00003fffULL },
	{ 15,	64,	33,	0x003fff80000000ULL },
	{ 16,	64,	34,	0x003fffc0000000ULL },
	{ 17,	64,	35,	0x003fffe0000000ULL },
	{ 18,	64,	36,	0x003ffff0000000ULL },
	{ 19,	64,	37,	0x003ffff8000000ULL },
	{ 20,	64,	38,	0x003ffffc000000ULL },
	{ 21,	64,	39,	0x003ffffe000000ULL },
	{ 22,	64,	40,	0x003fffff000000ULL },
	{ 23,	64,	41,	0x003fffff800000ULL },
	{ 24,	64,	42,	0x003fffffc00000ULL },
	{ 25,	64,	43,	0x003fffffe00000ULL },
	{ 26,	64,	44,	0x003ffffff00000ULL },
	{ 27,	64,	45,	0x003ffffff80000ULL },
	{ 28,	64,	46,	0x003ffffffc0000ULL },
	{ 29,	64,	47,	0x003ffffffe0000ULL },
	{ 30,	64,	48,	0x003fffffff0000ULL },
	{ 31,	64,	49,	0x003fffffff8000ULL },
	{ 32,	64,	50,	0x003fffffffc000ULL },
	{ 33,	64,	51,	0x003fffffffe000ULL },
	{ 34,	64,	52,	0x003ffffffff000ULL },
	{ 35,	64,	53,	0x003ffffffff800ULL },
	{ 36,	64,	54,	0x003ffffffffc00ULL },
	{ 37,	64,	55,	0x003ffffffffe00ULL },
	{ 38,	64,	56,	0x003fffffffff00ULL },
	{ 39,	64,	57,	0x003fffffffff80ULL },
	{ 40,	64,	58,	0x003fffffffffc0ULL },
	{ 41,	64,	59,	0x003fffffffffe0ULL },
	{ 42,	64,	60,	0x003ffffffffff0ULL },
	{ 43,	64,	61,	0x003ffffffffff8ULL },
	{ 44,	64,	62,	0x003ffffffffffcULL },
	{ 45,	64,	63,	0x003ffffffffffeULL },
	{ 46,	64,	0,	0x003fffffffffffULL },
	{ 1,	64,	18,	0x00400000000000ULL },
	{ 1,	32,	18,	0x00400000004000ULL },
	{ 2,	64,	19,	0x00600000000000ULL },
	{ 2,	32,	19,	0x00600000006000ULL },
	{ 3,	64,	20,	0x00700000000000ULL },
	{ 3,	32,	20,	0x00700000007000ULL },
	{ 4,	64,	21,	0x00780000000000ULL },
	{ 4,	32,	21,	0x00780000007800ULL },
	{ 5,	64,	22,	0x007c0000000000ULL },
	{ 5,	32,	22,	0x007c0000007c00ULL },
	{ 6,	64,	23,	0x007e0000000000ULL },
	{ 6,	32,	23,	0x007e0000007e00ULL },
	{ 7,	64,	24,	0x007f0000000000ULL },
	{ 7,	32,	24,	0x007f0000007f00ULL },
	{ 8,	64,	25,	0x007f8000000000ULL },
	{ 8,	32,	25,	0x007f8000007f80ULL },
	{ 9,	64,	26,	0x007fc000000000ULL },
	{ 9,	32,	26,	0x007fc000007fc0ULL },
	{ 10,	64,	27,	0x007fe000000000ULL },
	{ 10,	32,	27,	0x007fe000007fe0ULL },
	{ 11,	64,	28,	0x007ff000000000ULL },
	{ 11,	32,	28,	0x007ff000007ff0ULL },
	{ 12,	64,	29,	0x007ff800000000ULL },
	{ 12,	32,	29,	0x007ff800007ff8ULL },
	{ 13,	64,	30,	0x007ffc00000000ULL },
	{ 13,	32,	30,	0x007ffc00007ffcULL },
	{ 14,	64,	31,	0x007ffe00000000ULL },
	{ 14,	32,	31,	0x007ffe00007ffeULL },
	{ 15,	64,	32,	0x007fff00000000ULL },
	{ 15,	32,	0,	0x007fff00007fffULL },
	{ 16,	64,	33,	0x007fff80000000ULL },
	{ 17,	64,	34,	0x007fffc0000000ULL },
	{ 18,	64,	35,	0x007fffe0000000ULL },
	{ 19,	64,	36,	0x007ffff0000000ULL },
	{ 20,	64,	37,	0x007ffff8000000ULL },
	{ 21,	64,	38,	0x007ffffc000000ULL },
	{ 22,	64,	39,	0x007ffffe000000ULL },
	{ 23,	64,	40,	0x007fffff000000ULL },
	{ 24,	64,	41,	0x007fffff800000ULL },
	{ 25,	64,	42,	0x007fffffc00000ULL },
	{ 26,	64,	43,	0x007fffffe00000ULL },
	{ 27,	64,	44,	0x007ffffff00000ULL },
	{ 28,	64,	45,	0x007ffffff80000ULL },
	{ 29,	64,	46,	0x007ffffffc0000ULL },
	{ 30,	64,	47,	0x007ffffffe0000ULL },
	{ 31,	64,	48,	0x007fffffff0000ULL },
	{ 32,	64,	49,	0x007fffffff8000ULL },
	{ 33,	64,	50,	0x007fffffffc000ULL },
	{ 34,	64,	51,	0x007fffffffe000ULL },
	{ 35,	64,	52,	0x007ffffffff000ULL },
	{ 36,	64,	53,	0x007ffffffff800ULL },
	{ 37,	64,	54,	0x007ffffffffc00ULL },
	{ 38,	64,	55,	0x007ffffffffe00ULL },
	{ 39,	64,	56,	0x007fffffffff00ULL },
	{ 40,	64,	57,	0x007fffffffff80ULL },
	{ 41,	64,	58,	0x007fffffffffc0ULL },
	{ 42,	64,	59,	0x007fffffffffe0ULL },
	{ 43,	64,	60,	0x007ffffffffff0ULL },
	{ 44,	64,	61,	0x007ffffffffff8ULL },
	{ 45,	64,	62,	0x007ffffffffffcULL },
	{ 46,	64,	63,	0x007ffffffffffeULL },
	{ 47,	64,	0,	0x007fffffffffffULL },
	{ 1,	64,	17,	0x00800000000000ULL },
	{ 1,	32,	17,	0x00800000008000ULL },
	{ 2,	64,	18,	0x00c00000000000ULL },
	{ 2,	32,	18,	0x00c0000000c000ULL },
	{ 3,	64,	19,	0x00e00000000000ULL },
	{ 3,	32,	19,	0x00e0000000e000ULL },
	{ 4,	64,	20,	0x00f00000000000ULL },
	{ 4,	32,	20,	0x00f0000000f000ULL },
	{ 5,	64,	21,	0x00f80000000000ULL },
	{ 5,	32,	21,	0x00f8000000f800ULL },
	{ 6,	64,	22,	0x00fc0000000000ULL },
	{ 6,	32,	22,	0x00fc000000fc00ULL },
	{ 7,	64,	23,	0x00fe0000000000ULL },
	{ 7,	32,	23,	0x00fe000000fe00ULL },
	{ 8,	64,	24,	0x00ff0000000000ULL },
	{ 8,	32,	24,	0x00ff000000ff00ULL },
	{ 9,	64,	25,	0x00ff8000000000ULL },
	{ 9,	32,	25,	0x00ff800000ff80ULL },
	{ 10,	64,	26,	0x00ffc000000000ULL },
	{ 10,	32,	26,	0x00ffc00000ffc0ULL },
	{ 11,	64,	27,	0x00ffe000000000ULL },
	{ 11,	32,	27,	0x00ffe00000ffe0ULL },
	{ 12,	64,	28,	0x00fff000000000ULL },
	{ 12,	32,	28,	0x00fff00000fff0ULL },
	{ 13,	64,	29,	0x00fff800000000ULL },
	{ 13,	32,	29,	0x00fff80000fff8ULL },
	{ 14,	64,	30,	0x00fffc00000000ULL },
	{ 14,	32,	30,	0x00fffc0000fffcULL },
	{ 15,	64,	31,	0x00fffe00000000ULL },
	{ 15,	32,	31,	0x00fffe0000fffeULL },
	{ 16,	64,	32,	0x00ffff00000000ULL },
	{ 16,	32,	0,	0x00ffff0000ffffULL },
	{ 17,	64,	33,	0x00ffff80000000ULL },
	{ 18,	64,	34,	0x00ffffc0000000ULL },
	{ 19,	64,	35,	0x00ffffe0000000ULL },
	{ 20,	64,	36,	0x00fffff0000000ULL },
	{ 21,	64,	37,	0x00fffff8000000ULL },
	{ 22,	64,	38,	0x00fffffc000000ULL },
	{ 23,	64,	39,	0x00fffffe000000ULL },
	{ 24,	64,	40,	0x00ffffff000000ULL },
	{ 25,	64,	41,	0x00ffffff800000ULL },
	{ 26,	64,	42,	0x00ffffffc00000ULL },
	{ 27,	64,	43,	0x00ffffffe00000ULL },
	{ 28,	64,	44,	0x00fffffff00000ULL },
	{ 29,	64,	45,	0x00fffffff80000ULL },
	{ 30,	64,	46,	0x00fffffffc0000ULL },
	{ 31,	64,	47,	0x00fffffffe0000ULL },
	{ 32,	64,	48,	0x00ffffffff0000ULL },
	{ 33,	64,	49,	0x00ffffffff8000ULL },
	{ 34,	64,	50,	0x00ffffffffc000ULL },
	{ 35,	64,	51,	0x00ffffffffe000ULL },
	{ 36,	64,	52,	0x00fffffffff000ULL },
	{ 37,	64,	53,	0x00fffffffff800ULL },
	{ 38,	64,	54,	0x00fffffffffc00ULL },
	{ 39,	64,	55,	0x00fffffffffe00ULL },
	{ 40,	64,	56,	0x00ffffffffff00ULL },
	{ 41,	64,	57,	0x00ffffffffff80ULL },
	{ 42,	64,	58,	0x00ffffffffffc0ULL },
	{ 43,	64,	59,	0x00ffffffffffe0ULL },
	{ 44,	64,	60,	0x00fffffffffff0ULL },
	{ 45,	64,	61,	0x00fffffffffff8ULL },
	{ 46,	64,	62,	0x00fffffffffffcULL },
	{ 47,	64,	63,	0x00fffffffffffeULL },
	{ 48,	64,	0,	0x00ffffffffffffULL },
	{ 1,	64,	16,	0x01000000000000ULL },
	{ 1,	32,	16,	0x01000000010000ULL },
	{ 1,	16,	0,	0x01000100010001ULL },
	{ 2,	64,	17,	0x01800000000000ULL },
	{ 2,	32,	17,	0x01800000018000ULL },
	{ 3,	64,	18,	0x01c00000000000ULL },
	{ 3,	32,	18,	0x01c0000001c000ULL },
	{ 4,	64,	19,	0x01e00000000000ULL },
	{ 4,	32,	19,	0x01e0000001e000ULL },
	{ 5,	64,	20,	0x01f00000000000ULL },
	{ 5,	32,	20,	0x01f0000001f000ULL },
	{ 6,	64,	21,	0x01f80000000000ULL },
	{ 6,	32,	21,	0x01f8000001f800ULL },
	{ 7,	64,	22,	0x01fc0000000000ULL },
	{ 7,	32,	22,	0x01fc000001fc00ULL },
	{ 8,	64,	23,	0x01fe0000000000ULL },
	{ 8,	32,	23,	0x01fe000001fe00ULL },
	{ 9,	64,	24,	0x01ff0000000000ULL },
	{ 9,	32,	24,	0x01ff000001ff00ULL },
	{ 10,	64,	25,	0x01ff8000000000ULL },
	{ 10,	32,	25,	0x01ff800001ff80ULL },
	{ 11,	64,	26,	0x01ffc000000000ULL },
	{ 11,	32,	26,	0x01ffc00001ffc0ULL },
	{ 12,	64,	27,	0x01ffe000000000ULL },
	{ 12,	32,	27,	0x01ffe00001ffe0ULL },
	{ 13,	64,	28,	0x01fff000000000ULL },
	{ 13,	32,	28,	0x01fff00001fff0ULL },
	{ 14,	64,	29,	0x01fff800000000ULL },
	{ 14,	32,	29,	0x01fff80001fff8ULL },
	{ 15,	64,	30,	0x01fffc00000000ULL },
	{ 15,	32,	30,	0x01fffc0001fffcULL },
	{ 16,	64,	31,	0x01fffe00000000ULL },
	{ 16,	32,	31,	0x01fffe0001fffeULL },
	{ 17,	64,	32,	0x01ffff00000000ULL },
	{ 17,	32,	0,	0x01ffff0001ffffULL },
	{ 18,	64,	33,	0x01ffff80000000ULL },
	{ 19,	64,	34,	0x01ffffc0000000ULL },
	{ 20,	64,	35,	0x01ffffe0000000ULL },
	{ 21,	64,	36,	0x01fffff0000000ULL },
	{ 22,	64,	37,	0x01fffff8000000ULL },
	{ 23,	64,	38,	0x01fffffc000000ULL },
	{ 24,	64,	39,	0x01fffffe000000ULL },
	{ 25,	64,	40,	0x01ffffff000000ULL },
	{ 26,	64,	41,	0x01ffffff800000ULL },
	{ 27,	64,	42,	0x01ffffffc00000ULL },
	{ 28,	64,	43,	0x01ffffffe00000ULL },
	{ 29,	64,	44,	0x01fffffff00000ULL },
	{ 30,	64,	45,	0x01fffffff80000ULL },
	{ 31,	64,	46,	0x01fffffffc0000ULL },
	{ 32,	64,	47,	0x01fffffffe0000ULL },
	{ 33,	64,	48,	0x01ffffffff0000ULL },
	{ 34,	64,	49,	0x01ffffffff8000ULL },
	{ 35,	64,	50,	0x01ffffffffc000ULL },
	{ 36,	64,	51,	0x01ffffffffe000ULL },
	{ 37,	64,	52,	0x01fffffffff000ULL },
	{ 38,	64,	53,	0x01fffffffff800ULL },
	{ 39,	64,	54,	0x01fffffffffc00ULL },
	{ 40,	64,	55,	0x01fffffffffe00ULL },
	{ 41,	64,	56,	0x01ffffffffff00ULL },
	{ 42,	64,	57,	0x01ffffffffff80ULL },
	{ 43,	64,	58,	0x01ffffffffffc0ULL },
	{ 44,	64,	59,	0x01ffffffffffe0ULL },
	{ 45,	64,	60,	0x01fffffffffff0ULL },
	{ 46,	64,	61,	0x01fffffffffff8ULL },
	{ 47,	64,	62,	0x01fffffffffffcULL },
	{ 48,	64,	63,	0x01fffffffffffeULL },
	{ 49,	64,	0,	0x01ffffffffffffULL },
	{ 1,	64,	15,	0x02000000000000ULL },
	{ 1,	32,	15,	0x02000000020000ULL },
	{ 1,	16,	15,	0x02000200020002ULL },
	{ 2,	64,	16,	0x03000000000000ULL },
	{ 2,	32,	16,	0x03000000030000ULL },
	{ 2,	16,	0,	0x03000300030003ULL },
	{ 3,	64,	17,	0x03800000000000ULL },
	{ 3,	32,	17,	0x03800000038000ULL },
	{ 4,	64,	18,	0x03c00000000000ULL },
	{ 4,	32,	18,	0x03c0000003c000ULL },
	{ 5,	64,	19,	0x03e00000000000ULL },
	{ 5,	32,	19,	0x03e0000003e000ULL },
	{ 6,	64,	20,	0x03f00000000000ULL },
	{ 6,	32,	20,	0x03f0000003f000ULL },
	{ 7,	64,	21,	0x03f80000000000ULL },
	{ 7,	32,	21,	0x03f8000003f800ULL },
	{ 8,	64,	22,	0x03fc0000000000ULL },
	{ 8,	32,	22,	0x03fc000003fc00ULL },
	{ 9,	64,	23,	0x03fe0000000000ULL },
	{ 9,	32,	23,	0x03fe000003fe00ULL },
	{ 10,	64,	24,	0x03ff0000000000ULL },
	{ 10,	32,	24,	0x03ff000003ff00ULL },
	{ 11,	64,	25,	0x03ff8000000000ULL },
	{ 11,	32,	25,	0x03ff800003ff80ULL },
	{ 12,	64,	26,	0x03ffc000000000ULL },
	{ 12,	32,	26,	0x03ffc00003ffc0ULL },
	{ 13,	64,	27,	0x03ffe000000000ULL },
	{ 13,	32,	27,	0x03ffe00003ffe0ULL },
	{ 14,	64,	28,	0x03fff000000000ULL },
	{ 14,	32,	28,	0x03fff00003fff0ULL },
	{ 15,	64,	29,	0x03fff800000000ULL },
	{ 15,	32,	29,	0x03fff80003fff8ULL },
	{ 16,	64,	30,	0x03fffc00000000ULL },
	{ 16,	32,	30,	0x03fffc0003fffcULL },
	{ 17,	64,	31,	0x03fffe00000000ULL },
	{ 17,	32,	31,	0x03fffe0003fffeULL },
	{ 18,	64,	32,	0x03ffff00000000ULL },
	{ 18,	32,	0,	0x03ffff0003ffffULL },
	{ 19,	64,	33,	0x03ffff80000000ULL },
	{ 20,	64,	34,	0x03ffffc0000000ULL },
	{ 21,	64,	35,	0x03ffffe0000000ULL },
	{ 22,	64,	36,	0x03fffff0000000ULL },
	{ 23,	64,	37,	0x03fffff8000000ULL },
	{ 24,	64,	38,	0x03fffffc000000ULL },
	{ 25,	64,	39,	0x03fffffe000000ULL },
	{ 26,	64,	40,	0x03ffffff000000ULL },
	{ 27,	64,	41,	0x03ffffff800000ULL },
	{ 28,	64,	42,	0x03ffffffc00000ULL },
	{ 29,	64,	43,	0x03ffffffe00000ULL },
	{ 30,	64,	44,	0x03fffffff00000ULL },
	{ 31,	64,	45,	0x03fffffff80000ULL },
	{ 32,	64,	46,	0x03fffffffc0000ULL },
	{ 33,	64,	47,	0x03fffffffe0000ULL },
	{ 34,	64,	48,	0x03ffffffff0000ULL },
	{ 35,	64,	49,	0x03ffffffff8000ULL },
	{ 36,	64,	50,	0x03ffffffffc000ULL },
	{ 37,	64,	51,	0x03ffffffffe000ULL },
	{ 38,	64,	52,	0x03fffffffff000ULL },
	{ 39,	64,	53,	0x03fffffffff800ULL },
	{ 40,	64,	54,	0x03fffffffffc00ULL },
	{ 41,	64,	55,	0x03fffffffffe00ULL },
	{ 42,	64,	56,	0x03ffffffffff00ULL },
	{ 43,	64,	57,	0x03ffffffffff80ULL },
	{ 44,	64,	58,	0x03ffffffffffc0ULL },
	{ 45,	64,	59,	0x03ffffffffffe0ULL },
	{ 46,	64,	60,	0x03fffffffffff0ULL },
	{ 47,	64,	61,	0x03fffffffffff8ULL },
	{ 48,	64,	62,	0x03fffffffffffcULL },
	{ 49,	64,	63,	0x03fffffffffffeULL },
	{ 50,	64,	0,	0x03ffffffffffffULL },
	{ 1,	64,	14,	0x04000000000000ULL },
	{ 1,	32,	14,	0x04000000040000ULL },
	{ 1,	16,	14,	0x04000400040004ULL },
	{ 2,	64,	15,	0x06000000000000ULL },
	{ 2,	32,	15,	0x06000000060000ULL },
	{ 2,	16,	15,	0x06000600060006ULL },
	{ 3,	64,	16,	0x07000000000000ULL },
	{ 3,	32,	16,	0x07000000070000ULL },
	{ 3,	16,	0,	0x07000700070007ULL },
	{ 4,	64,	17,	0x07800000000000ULL },
	{ 4,	32,	17,	0x07800000078000ULL },
	{ 5,	64,	18,	0x07c00000000000ULL },
	{ 5,	32,	18,	0x07c0000007c000ULL },
	{ 6,	64,	19,	0x07e00000000000ULL },
	{ 6,	32,	19,	0x07e0000007e000ULL },
	{ 7,	64,	20,	0x07f00000000000ULL },
	{ 7,	32,	20,	0x07f0000007f000ULL },
	{ 8,	64,	21,	0x07f80000000000ULL },
	{ 8,	32,	21,	0x07f8000007f800ULL },
	{ 9,	64,	22,	0x07fc0000000000ULL },
	{ 9,	32,	22,	0x07fc000007fc00ULL },
	{ 10,	64,	23,	0x07fe0000000000ULL },
	{ 10,	32,	23,	0x07fe000007fe00ULL },
	{ 11,	64,	24,	0x07ff0000000000ULL },
	{ 11,	32,	24,	0x07ff000007ff00ULL },
	{ 12,	64,	25,	0x07ff8000000000ULL },
	{ 12,	32,	25,	0x07ff800007ff80ULL },
	{ 13,	64,	26,	0x07ffc000000000ULL },
	{ 13,	32,	26,	0x07ffc00007ffc0ULL },
	{ 14,	64,	27,	0x07ffe000000000ULL },
	{ 14,	32,	27,	0x07ffe00007ffe0ULL },
	{ 15,	64,	28,	0x07fff000000000ULL },
	{ 15,	32,	28,	0x07fff00007fff0ULL },
	{ 16,	64,	29,	0x07fff800000000ULL },
	{ 16,	32,	29,	0x07fff80007fff8ULL },
	{ 17,	64,	30,	0x07fffc00000000ULL },
	{ 17,	32,	30,	0x07fffc0007fffcULL },
	{ 18,	64,	31,	0x07fffe00000000ULL },
	{ 18,	32,	31,	0x07fffe0007fffeULL },
	{ 19,	64,	32,	0x07ffff00000000ULL },
	{ 19,	32,	0,	0x07ffff0007ffffULL },
	{ 20,	64,	33,	0x07ffff80000000ULL },
	{ 21,	64,	34,	0x07ffffc0000000ULL },
	{ 22,	64,	35,	0x07ffffe0000000ULL },
	{ 23,	64,	36,	0x07fffff0000000ULL },
	{ 24,	64,	37,	0x07fffff8000000ULL },
	{ 25,	64,	38,	0x07fffffc000000ULL },
	{ 26,	64,	39,	0x07fffffe000000ULL },
	{ 27,	64,	40,	0x07ffffff000000ULL },
	{ 28,	64,	41,	0x07ffffff800000ULL },
	{ 29,	64,	42,	0x07ffffffc00000ULL },
	{ 30,	64,	43,	0x07ffffffe00000ULL },
	{ 31,	64,	44,	0x07fffffff00000ULL },
	{ 32,	64,	45,	0x07fffffff80000ULL },
	{ 33,	64,	46,	0x07fffffffc0000ULL },
	{ 34,	64,	47,	0x07fffffffe0000ULL },
	{ 35,	64,	48,	0x07ffffffff0000ULL },
	{ 36,	64,	49,	0x07ffffffff8000ULL },
	{ 37,	64,	50,	0x07ffffffffc000ULL },
	{ 38,	64,	51,	0x07ffffffffe000ULL },
	{ 39,	64,	52,	0x07fffffffff000ULL },
	{ 40,	64,	53,	0x07fffffffff800ULL },
	{ 41,	64,	54,	0x07fffffffffc00ULL },
	{ 42,	64,	55,	0x07fffffffffe00ULL },
	{ 43,	64,	56,	0x07ffffffffff00ULL },
	{ 44,	64,	57,	0x07ffffffffff80ULL },
	{ 45,	64,	58,	0x07ffffffffffc0ULL },
	{ 46,	64,	59,	0x07ffffffffffe0ULL },
	{ 47,	64,	60,	0x07fffffffffff0ULL },
	{ 48,	64,	61,	0x07fffffffffff8ULL },
	{ 49,	64,	62,	0x07fffffffffffcULL },
	{ 50,	64,	63,	0x07fffffffffffeULL },
	{ 51,	64,	0,	0x07ffffffffffffULL },
	{ 1,	64,	13,	0x08000000000000ULL },
	{ 1,	32,	13,	0x08000000080000ULL },
	{ 1,	16,	13,	0x08000800080008ULL },
	{ 2,	64,	14,	0x0c000000000000ULL },
	{ 2,	32,	14,	0x0c0000000c0000ULL },
	{ 2,	16,	14,	0x0c000c000c000cULL },
	{ 3,	64,	15,	0x0e000000000000ULL },
	{ 3,	32,	15,	0x0e0000000e0000ULL },
	{ 3,	16,	15,	0x0e000e000e000eULL },
	{ 4,	64,	16,	0x0f000000000000ULL },
	{ 4,	32,	16,	0x0f0000000f0000ULL },
	{ 4,	16,	0,	0x0f000f000f000fULL },
	{ 5,	64,	17,	0x0f800000000000ULL },
	{ 5,	32,	17,	0x0f8000000f8000ULL },
	{ 6,	64,	18,	0x0fc00000000000ULL },
	{ 6,	32,	18,	0x0fc000000fc000ULL },
	{ 7,	64,	19,	0x0fe00000000000ULL },
	{ 7,	32,	19,	0x0fe000000fe000ULL },
	{ 8,	64,	20,	0x0ff00000000000ULL },
	{ 8,	32,	20,	0x0ff000000ff000ULL },
	{ 9,	64,	21,	0x0ff80000000000ULL },
	{ 9,	32,	21,	0x0ff800000ff800ULL },
	{ 10,	64,	22,	0x0ffc0000000000ULL },
	{ 10,	32,	22,	0x0ffc00000ffc00ULL },
	{ 11,	64,	23,	0x0ffe0000000000ULL },
	{ 11,	32,	23,	0x0ffe00000ffe00ULL },
	{ 12,	64,	24,	0x0fff0000000000ULL },
	{ 12,	32,	24,	0x0fff00000fff00ULL },
	{ 13,	64,	25,	0x0fff8000000000ULL },
	{ 13,	32,	25,	0x0fff80000fff80ULL },
	{ 14,	64,	26,	0x0fffc000000000ULL },
	{ 14,	32,	26,	0x0fffc0000fffc0ULL },
	{ 15,	64,	27,	0x0fffe000000000ULL },
	{ 15,	32,	27,	0x0fffe0000fffe0ULL },
	{ 16,	64,	28,	0x0ffff000000000ULL },
	{ 16,	32,	28,	0x0ffff0000ffff0ULL },
	{ 17,	64,	29,	0x0ffff800000000ULL },
	{ 17,	32,	29,	0x0ffff8000ffff8ULL },
	{ 18,	64,	30,	0x0ffffc00000000ULL },
	{ 18,	32,	30,	0x0ffffc000ffffcULL },
	{ 19,	64,	31,	0x0ffffe00000000ULL },
	{ 19,	32,	31,	0x0ffffe000ffffeULL },
	{ 20,	64,	32,	0x0fffff00000000ULL },
	{ 20,	32,	0,	0x0fffff000fffffULL },
	{ 21,	64,	33,	0x0fffff80000000ULL },
	{ 22,	64,	34,	0x0fffffc0000000ULL },
	{ 23,	64,	35,	0x0fffffe0000000ULL },
	{ 24,	64,	36,	0x0ffffff0000000ULL },
	{ 25,	64,	37,	0x0ffffff8000000ULL },
	{ 26,	64,	38,	0x0ffffffc000000ULL },
	{ 27,	64,	39,	0x0ffffffe000000ULL },
	{ 28,	64,	40,	0x0fffffff000000ULL },
	{ 29,	64,	41,	0x0fffffff800000ULL },
	{ 30,	64,	42,	0x0fffffffc00000ULL },
	{ 31,	64,	43,	0x0fffffffe00000ULL },
	{ 32,	64,	44,	0x0ffffffff00000ULL },
	{ 33,	64,	45,	0x0ffffffff80000ULL },
	{ 34,	64,	46,	0x0ffffffffc0000ULL },
	{ 35,	64,	47,	0x0ffffffffe0000ULL },
	{ 36,	64,	48,	0x0fffffffff0000ULL },
	{ 37,	64,	49,	0x0fffffffff8000ULL },
	{ 38,	64,	50,	0x0fffffffffc000ULL },
	{ 39,	64,	51,	0x0fffffffffe000ULL },
	{ 40,	64,	52,	0x0ffffffffff000ULL },
	{ 41,	64,	53,	0x0ffffffffff800ULL },
	{ 42,	64,	54,	0x0ffffffffffc00ULL },
	{ 43,	64,	55,	0x0ffffffffffe00ULL },
	{ 44,	64,	56,	0x0fffffffffff00ULL },
	{ 45,	64,	57,	0x0fffffffffff80ULL },
	{ 46,	64,	58,	0x0fffffffffffc0ULL },
	{ 47,	64,	59,	0x0fffffffffffe0ULL },
	{ 48,	64,	60,	0x0ffffffffffff0ULL },
	{ 49,	64,	61,	0x0ffffffffffff8ULL },
	{ 50,	64,	62,	0x0ffffffffffffcULL },
	{ 51,	64,	63,	0x0ffffffffffffeULL },
	{ 52,	64,	0,	0x0fffffffffffffULL },
	{ 1,	64,	12,	0x10000000000000ULL },
	{ 1,	32,	12,	0x10000000100000ULL },
	{ 1,	16,	12,	0x10001000100010ULL },
	{ 2,	64,	13,	0x18000000000000ULL },
	{ 2,	32,	13,	0x18000000180000ULL },
	{ 2,	16,	13,	0x18001800180018ULL },
	{ 3,	64,	14,	0x1c000000000000ULL },
	{ 3,	32,	14,	0x1c0000001c0000ULL },
	{ 3,	16,	14,	0x1c001c001c001cULL },
	{ 4,	64,	15,	0x1e000000000000ULL },
	{ 4,	32,	15,	0x1e0000001e0000ULL },
	{ 4,	16,	15,	0x1e001e001e001eULL },
	{ 5,	64,	16,	0x1f000000000000ULL },
	{ 5,	32,	16,	0x1f0000001f0000ULL },
	{ 5,	16,	0,	0x1f001f001f001fULL },
	{ 6,	64,	17,	0x1f800000000000ULL },
	{ 6,	32,	17,	0x1f8000001f8000ULL },
	{ 7,	64,	18,	0x1fc00000000000ULL },
	{ 7,	32,	18,	0x1fc000001fc000ULL },
	{ 8,	64,	19,	0x1fe00000000000ULL },
	{ 8,	32,	19,	0x1fe000001fe000ULL },
	{ 9,	64,	20,	0x1ff00000000000ULL },
	{ 9,	32,	20,	0x1ff000001ff000ULL },
	{ 10,	64,	21,	0x1ff80000000000ULL },
	{ 10,	32,	21,	0x1ff800001ff800ULL },
	{ 11,	64,	22,	0x1ffc0000000000ULL },
	{ 11,	32,	22,	0x1ffc00001ffc00ULL },
	{ 12,	64,	23,	0x1ffe0000000000ULL },
	{ 12,	32,	23,	0x1ffe00001ffe00ULL },
	{ 13,	64,	24,	0x1fff0000000000ULL },
	{ 13,	32,	24,	0x1fff00001fff00ULL },
	{ 14,	64,	25,	0x1fff8000000000ULL },
	{ 14,	32,	25,	0x1fff80001fff80ULL },
	{ 15,	64,	26,	0x1fffc000000000ULL },
	{ 15,	32,	26,	0x1fffc0001fffc0ULL },
	{ 16,	64,	27,	0x1fffe000000000ULL },
	{ 16,	32,	27,	0x1fffe0001fffe0ULL },
	{ 17,	64,	28,	0x1ffff000000000ULL },
	{ 17,	32,	28,	0x1ffff0001ffff0ULL },
	{ 18,	64,	29,	0x1ffff800000000ULL },
	{ 18,	32,	29,	0x1ffff8001ffff8ULL },
	{ 19,	64,	30,	0x1ffffc00000000ULL },
	{ 19,	32,	30,	0x1ffffc001ffffcULL },
	{ 20,	64,	31,	0x1ffffe00000000ULL },
	{ 20,	32,	31,	0x1ffffe001ffffeULL },
	{ 21,	64,	32,	0x1fffff00000000ULL },
	{ 21,	32,	0,	0x1fffff001fffffULL },
	{ 22,	64,	33,	0x1fffff80000000ULL },
	{ 23,	64,	34,	0x1fffffc0000000ULL },
	{ 24,	64,	35,	0x1fffffe0000000ULL },
	{ 25,	64,	36,	0x1ffffff0000000ULL },
	{ 26,	64,	37,	0x1ffffff8000000ULL },
	{ 27,	64,	38,	0x1ffffffc000000ULL },
	{ 28,	64,	39,	0x1ffffffe000000ULL },
	{ 29,	64,	40,	0x1fffffff000000ULL },
	{ 30,	64,	41,	0x1fffffff800000ULL },
	{ 31,	64,	42,	0x1fffffffc00000ULL },
	{ 32,	64,	43,	0x1fffffffe00000ULL },
	{ 33,	64,	44,	0x1ffffffff00000ULL },
	{ 34,	64,	45,	0x1ffffffff80000ULL },
	{ 35,	64,	46,	0x1ffffffffc0000ULL },
	{ 36,	64,	47,	0x1ffffffffe0000ULL },
	{ 37,	64,	48,	0x1fffffffff0000ULL },
	{ 38,	64,	49,	0x1fffffffff8000ULL },
	{ 39,	64,	50,	0x1fffffffffc000ULL },
	{ 40,	64,	51,	0x1fffffffffe000ULL },
	{ 41,	64,	52,	0x1ffffffffff000ULL },
	{ 42,	64,	53,	0x1ffffffffff800ULL },
	{ 43,	64,	54,	0x1ffffffffffc00ULL },
	{ 44,	64,	55,	0x1ffffffffffe00ULL },
	{ 45,	64,	56,	0x1fffffffffff00ULL },
	{ 46,	64,	57,	0x1fffffffffff80ULL },
	{ 47,	64,	58,	0x1fffffffffffc0ULL },
	{ 48,	64,	59,	0x1fffffffffffe0ULL },
	{ 49,	64,	60,	0x1ffffffffffff0ULL },
	{ 50,	64,	61,	0x1ffffffffffff8ULL },
	{ 51,	64,	62,	0x1ffffffffffffcULL },
	{ 52,	64,	63,	0x1ffffffffffffeULL },
	{ 53,	64,	0,	0x1fffffffffffffULL },
	{ 1,	64,	11,	0x20000000000000ULL },
	{ 1,	32,	11,	0x20000000200000ULL },
	{ 1,	16,	11,	0x20002000200020ULL },
	{ 2,	64,	12,	0x30000000000000ULL },
	{ 2,	32,	12,	0x30000000300000ULL },
	{ 2,	16,	12,	0x30003000300030ULL },
	{ 3,	64,	13,	0x38000000000000ULL },
	{ 3,	32,	13,	0x38000000380000ULL },
	{ 3,	16,	13,	0x38003800380038ULL },
	{ 4,	64,	14,	0x3c000000000000ULL },
	{ 4,	32,	14,	0x3c0000003c0000ULL },
	{ 4,	16,	14,	0x3c003c003c003cULL },
	{ 5,	64,	15,	0x3e000000000000ULL },
	{ 5,	32,	15,	0x3e0000003e0000ULL },
	{ 5,	16,	15,	0x3e003e003e003eULL },
	{ 6,	64,	16,	0x3f000000000000ULL },
	{ 6,	32,	16,	0x3f0000003f0000ULL },
	{ 6,	16,	0,	0x3f003f003f003fULL },
	{ 7,	64,	17,	0x3f800000000000ULL },
	{ 7,	32,	17,	0x3f8000003f8000ULL },
	{ 8,	64,	18,	0x3fc00000000000ULL },
	{ 8,	32,	18,	0x3fc000003fc000ULL },
	{ 9,	64,	19,	0x3fe00000000000ULL },
	{ 9,	32,	19,	0x3fe000003fe000ULL },
	{ 10,	64,	20,	0x3ff00000000000ULL },
	{ 10,	32,	20,	0x3ff000003ff000ULL },
	{ 11,	64,	21,	0x3ff80000000000ULL },
	{ 11,	32,	21,	0x3ff800003ff800ULL },
	{ 12,	64,	22,	0x3ffc0000000000ULL },
	{ 12,	32,	22,	0x3ffc00003ffc00ULL },
	{ 13,	64,	23,	0x3ffe0000000000ULL },
	{ 13,	32,	23,	0x3ffe00003ffe00ULL },
	{ 14,	64,	24,	0x3fff0000000000ULL },
	{ 14,	32,	24,	0x3fff00003fff00ULL },
	{ 15,	64,	25,	0x3fff8000000000ULL },
	{ 15,	32,	25,	0x3fff80003fff80ULL },
	{ 16,	64,	26,	0x3fffc000000000ULL },
	{ 16,	32,	26,	0x3fffc0003fffc0ULL },
	{ 17,	64,	27,	0x3fffe000000000ULL },
	{ 17,	32,	27,	0x3fffe0003fffe0ULL },
	{ 18,	64,	28,	0x3ffff000000000ULL },
	{ 18,	32,	28,	0x3ffff0003ffff0ULL },
	{ 19,	64,	29,	0x3ffff800000000ULL },
	{ 19,	32,	29,	0x3ffff8003ffff8ULL },
	{ 20,	64,	30,	0x3ffffc00000000ULL },
	{ 20,	32,	30,	0x3ffffc003ffffcULL },
	{ 21,	64,	31,	0x3ffffe00000000ULL },
	{ 21,	32,	31,	0x3ffffe003ffffeULL },
	{ 22,	64,	32,	0x3fffff00000000ULL },
	{ 22,	32,	0,	0x3fffff003fffffULL },
	{ 23,	64,	33,	0x3fffff80000000ULL },
	{ 24,	64,	34,	0x3fffffc0000000ULL },
	{ 25,	64,	35,	0x3fffffe0000000ULL },
	{ 26,	64,	36,	0x3ffffff0000000ULL },
	{ 27,	64,	37,	0x3ffffff8000000ULL },
	{ 28,	64,	38,	0x3ffffffc000000ULL },
	{ 29,	64,	39,	0x3ffffffe000000ULL },
	{ 30,	64,	40,	0x3fffffff000000ULL },
	{ 31,	64,	41,	0x3fffffff800000ULL },
	{ 32,	64,	42,	0x3fffffffc00000ULL },
	{ 33,	64,	43,	0x3fffffffe00000ULL },
	{ 34,	64,	44,	0x3ffffffff00000ULL },
	{ 35,	64,	45,	0x3ffffffff80000ULL },
	{ 36,	64,	46,	0x3ffffffffc0000ULL },
	{ 37,	64,	47,	0x3ffffffffe0000ULL },
	{ 38,	64,	48,	0x3fffffffff0000ULL },
	{ 39,	64,	49,	0x3fffffffff8000ULL },
	{ 40,	64,	50,	0x3fffffffffc000ULL },
	{ 41,	64,	51,	0x3fffffffffe000ULL },
	{ 42,	64,	52,	0x3ffffffffff000ULL },
	{ 43,	64,	53,	0x3ffffffffff800ULL },
	{ 44,	64,	54,	0x3ffffffffffc00ULL },
	{ 45,	64,	55,	0x3ffffffffffe00ULL },
	{ 46,	64,	56,	0x3fffffffffff00ULL },
	{ 47,	64,	57,	0x3fffffffffff80ULL },
	{ 48,	64,	58,	0x3fffffffffffc0ULL },
	{ 49,	64,	59,	0x3fffffffffffe0ULL },
	{ 50,	64,	60,	0x3ffffffffffff0ULL },
	{ 51,	64,	61,	0x3ffffffffffff8ULL },
	{ 52,	64,	62,	0x3ffffffffffffcULL },
	{ 53,	64,	63,	0x3ffffffffffffeULL },
	{ 54,	64,	0,	0x3fffffffffffffULL },
	{ 1,	64,	10,	0x40000000000000ULL },
	{ 1,	32,	10,	0x40000000400000ULL },
	{ 1,	16,	10,	0x40004000400040ULL },
	{ 2,	64,	11,	0x60000000000000ULL },
	{ 2,	32,	11,	0x60000000600000ULL },
	{ 2,	16,	11,	0x60006000600060ULL },
	{ 3,	64,	12,	0x70000000000000ULL },
	{ 3,	32,	12,	0x70000000700000ULL },
	{ 3,	16,	12,	0x70007000700070ULL },
	{ 4,	64,	13,	0x78000000000000ULL },
	{ 4,	32,	13,	0x78000000780000ULL },
	{ 4,	16,	13,	0x78007800780078ULL },
	{ 5,	64,	14,	0x7c000000000000ULL },
	{ 5,	32,	14,	0x7c0000007c0000ULL },
	{ 5,	16,	14,	0x7c007c007c007cULL },
	{ 6,	64,	15,	0x7e000000000000ULL },
	{ 6,	32,	15,	0x7e0000007e0000ULL },
	{ 6,	16,	15,	0x7e007e007e007eULL },
	{ 7,	64,	16,	0x7f000000000000ULL },
	{ 7,	32,	16,	0x7f0000007f0000ULL },
	{ 7,	16,	0,	0x7f007f007f007fULL },
	{ 8,	64,	17,	0x7f800000000000ULL },
	{ 8,	32,	17,	0x7f8000007f8000ULL },
	{ 9,	64,	18,	0x7fc00000000000ULL },
	{ 9,	32,	18,	0x7fc000007fc000ULL },
	{ 10,	64,	19,	0x7fe00000000000ULL },
	{ 10,	32,	19,	0x7fe000007fe000ULL },
	{ 11,	64,	20,	0x7ff00000000000ULL },
	{ 11,	32,	20,	0x7ff000007ff000ULL },
	{ 12,	64,	21,	0x7ff80000000000ULL },
	{ 12,	32,	21,	0x7ff800007ff800ULL },
	{ 13,	64,	22,	0x7ffc0000000000ULL },
	{ 13,	32,	22,	0x7ffc00007ffc00ULL },
	{ 14,	64,	23,	0x7ffe0000000000ULL },
	{ 14,	32,	23,	0x7ffe00007ffe00ULL },
	{ 15,	64,	24,	0x7fff0000000000ULL },
	{ 15,	32,	24,	0x7fff00007fff00ULL },
	{ 16,	64,	25,	0x7fff8000000000ULL },
	{ 16,	32,	25,	0x7fff80007fff80ULL },
	{ 17,	64,	26,	0x7fffc000000000ULL },
	{ 17,	32,	26,	0x7fffc0007fffc0ULL },
	{ 18,	64,	27,	0x7fffe000000000ULL },
	{ 18,	32,	27,	0x7fffe0007fffe0ULL },
	{ 19,	64,	28,	0x7ffff000000000ULL },
	{ 19,	32,	28,	0x7ffff0007ffff0ULL },
	{ 20,	64,	29,	0x7ffff800000000ULL },
	{ 20,	32,	29,	0x7ffff8007ffff8ULL },
	{ 21,	64,	30,	0x7ffffc00000000ULL },
	{ 21,	32,	30,	0x7ffffc007ffffcULL },
	{ 22,	64,	31,	0x7ffffe00000000ULL },
	{ 22,	32,	31,	0x7ffffe007ffffeULL },
	{ 23,	64,	32,	0x7fffff00000000ULL },
	{ 23,	32,	0,	0x7fffff007fffffULL },
	{ 24,	64,	33,	0x7fffff80000000ULL },
	{ 25,	64,	34,	0x7fffffc0000000ULL },
	{ 26,	64,	35,	0x7fffffe0000000ULL },
	{ 27,	64,	36,	0x7ffffff0000000ULL },
	{ 28,	64,	37,	0x7ffffff8000000ULL },
	{ 29,	64,	38,	0x7ffffffc000000ULL },
	{ 30,	64,	39,	0x7ffffffe000000ULL },
	{ 31,	64,	40,	0x7fffffff000000ULL },
	{ 32,	64,	41,	0x7fffffff800000ULL },
	{ 33,	64,	42,	0x7fffffffc00000ULL },
	{ 34,	64,	43,	0x7fffffffe00000ULL },
	{ 35,	64,	44,	0x7ffffffff00000ULL },
	{ 36,	64,	45,	0x7ffffffff80000ULL },
	{ 37,	64,	46,	0x7ffffffffc0000ULL },
	{ 38,	64,	47,	0x7ffffffffe0000ULL },
	{ 39,	64,	48,	0x7fffffffff0000ULL },
	{ 40,	64,	49,	0x7fffffffff8000ULL },
	{ 41,	64,	50,	0x7fffffffffc000ULL },
	{ 42,	64,	51,	0x7fffffffffe000ULL },
	{ 43,	64,	52,	0x7ffffffffff000ULL },
	{ 44,	64,	53,	0x7ffffffffff800ULL },
	{ 45,	64,	54,	0x7ffffffffffc00ULL },
	{ 46,	64,	55,	0x7ffffffffffe00ULL },
	{ 47,	64,	56,	0x7fffffffffff00ULL },
	{ 48,	64,	57,	0x7fffffffffff80ULL },
	{ 49,	64,	58,	0x7fffffffffffc0ULL },
	{ 50,	64,	59,	0x7fffffffffffe0ULL },
	{ 51,	64,	60,	0x7ffffffffffff0ULL },
	{ 52,	64,	61,	0x7ffffffffffff8ULL },
	{ 53,	64,	62,	0x7ffffffffffffcULL },
	{ 54,	64,	63,	0x7ffffffffffffeULL },
	{ 55,	64,	0,	0x7fffffffffffffULL },
	{ 1,	64,	9,	0x80000000000000ULL },
	{ 1,	32,	9,	0x80000000800000ULL },
	{ 1,	16,	9,	0x80008000800080ULL },
	{ 2,	64,	10,	0xc0000000000000ULL },
	{ 2,	32,	10,	0xc0000000c00000ULL },
	{ 2,	16,	10,	0xc000c000c000c0ULL },
	{ 3,	64,	11,	0xe0000000000000ULL },
	{ 3,	32,	11,	0xe0000000e00000ULL },
	{ 3,	16,	11,	0xe000e000e000e0ULL },
	{ 4,	64,	12,	0xf0000000000000ULL },
	{ 4,	32,	12,	0xf0000000f00000ULL },
	{ 4,	16,	12,	0xf000f000f000f0ULL },
	{ 5,	64,	13,	0xf8000000000000ULL },
	{ 5,	32,	13,	0xf8000000f80000ULL },
	{ 5,	16,	13,	0xf800f800f800f8ULL },
	{ 6,	64,	14,	0xfc000000000000ULL },
	{ 6,	32,	14,	0xfc000000fc0000ULL },
	{ 6,	16,	14,	0xfc00fc00fc00fcULL },
	{ 7,	64,	15,	0xfe000000000000ULL },
	{ 7,	32,	15,	0xfe000000fe0000ULL },
	{ 7,	16,	15,	0xfe00fe00fe00feULL },
	{ 8,	64,	16,	0xff000000000000ULL },
	{ 8,	32,	16,	0xff000000ff0000ULL },
	{ 8,	16,	0,	0xff00ff00ff00ffULL },
	{ 9,	64,	17,	0xff800000000000ULL },
	{ 9,	32,	17,	0xff800000ff8000ULL },
	{ 10,	64,	18,	0xffc00000000000ULL },
	{ 10,	32,	18,	0xffc00000ffc000ULL },
	{ 11,	64,	19,	0xffe00000000000ULL },
	{ 11,	32,	19,	0xffe00000ffe000ULL },
	{ 12,	64,	20,	0xfff00000000000ULL },
	{ 12,	32,	20,	0xfff00000fff000ULL },
	{ 13,	64,	21,	0xfff80000000000ULL },
	{ 13,	32,	21,	0xfff80000fff800ULL },
	{ 14,	64,	22,	0xfffc0000000000ULL },
	{ 14,	32,	22,	0xfffc0000fffc00ULL },
	{ 15,	64,	23,	0xfffe0000000000ULL },
	{ 15,	32,	23,	0xfffe0000fffe00ULL },
	{ 16,	64,	24,	0xffff0000000000ULL },
	{ 16,	32,	24,	0xffff0000ffff00ULL },
	{ 17,	64,	25,	0xffff8000000000ULL },
	{ 17,	32,	25,	0xffff8000ffff80ULL },
	{ 18,	64,	26,	0xffffc000000000ULL },
	{ 18,	32,	26,	0xffffc000ffffc0ULL },
	{ 19,	64,	27,	0xffffe000000000ULL },
	{ 19,	32,	27,	0xffffe000ffffe0ULL },
	{ 20,	64,	28,	0xfffff000000000ULL },
	{ 20,	32,	28,	0xfffff000fffff0ULL },
	{ 21,	64,	29,	0xfffff800000000ULL },
	{ 21,	32,	29,	0xfffff800fffff8ULL },
	{ 22,	64,	30,	0xfffffc00000000ULL },
	{ 22,	32,	30,	0xfffffc00fffffcULL },
	{ 23,	64,	31,	0xfffffe00000000ULL },
	{ 23,	32,	31,	0xfffffe00fffffeULL },
	{ 24,	64,	32,	0xffffff00000000ULL },
	{ 24,	32,	0,	0xffffff00ffffffULL },
	{ 25,	64,	33,	0xffffff80000000ULL },
	{ 26,	64,	34,	0xffffffc0000000ULL },
	{ 27,	64,	35,	0xffffffe0000000ULL },
	{ 28,	64,	36,	0xfffffff0000000ULL },
	{ 29,	64,	37,	0xfffffff8000000ULL },
	{ 30,	64,	38,	0xfffffffc000000ULL },
	{ 31,	64,	39,	0xfffffffe000000ULL },
	{ 32,	64,	40,	0xffffffff000000ULL },
	{ 33,	64,	41,	0xffffffff800000ULL },
	{ 34,	64,	42,	0xffffffffc00000ULL },
	{ 35,	64,	43,	0xffffffffe00000ULL },
	{ 36,	64,	44,	0xfffffffff00000ULL },
	{ 37,	64,	45,	0xfffffffff80000ULL },
	{ 38,	64,	46,	0xfffffffffc0000ULL },
	{ 39,	64,	47,	0xfffffffffe0000ULL },
	{ 40,	64,	48,	0xffffffffff0000ULL },
	{ 41,	64,	49,	0xffffffffff8000ULL },
	{ 42,	64,	50,	0xffffffffffc000ULL },
	{ 43,	64,	51,	0xffffffffffe000ULL },
	{ 44,	64,	52,	0xfffffffffff000ULL },
	{ 45,	64,	53,	0xfffffffffff800ULL },
	{ 46,	64,	54,	0xfffffffffffc00ULL },
	{ 47,	64,	55,	0xfffffffffffe00ULL },
	{ 48,	64,	56,	0xffffffffffff00ULL },
	{ 49,	64,	57,	0xffffffffffff80ULL },
	{ 50,	64,	58,	0xffffffffffffc0ULL },
	{ 51,	64,	59,	0xffffffffffffe0ULL },
	{ 52,	64,	60,	0xfffffffffffff0ULL },
	{ 53,	64,	61,	0xfffffffffffff8ULL },
	{ 54,	64,	62,	0xfffffffffffffcULL },
	{ 55,	64,	63,	0xfffffffffffffeULL },
	{ 56,	64,	0,	0xffffffffffffffULL },
	{ 1,	64,	8,	0x100000000000000ULL },
	{ 1,	32,	8,	0x100000001000000ULL },
	{ 1,	16,	8,	0x100010001000100ULL },
	{ 1,	8,	0,	0x101010101010101ULL },
	{ 2,	64,	9,	0x180000000000000ULL },
	{ 2,	32,	9,	0x180000001800000ULL },
	{ 2,	16,	9,	0x180018001800180ULL },
	{ 3,	64,	10,	0x1c0000000000000ULL },
	{ 3,	32,	10,	0x1c0000001c00000ULL },
	{ 3,	16,	10,	0x1c001c001c001c0ULL },
	{ 4,	64,	11,	0x1e0000000000000ULL },
	{ 4,	32,	11,	0x1e0000001e00000ULL },
	{ 4,	16,	11,	0x1e001e001e001e0ULL },
	{ 5,	64,	12,	0x1f0000000000000ULL },
	{ 5,	32,	12,	0x1f0000001f00000ULL },
	{ 5,	16,	12,	0x1f001f001f001f0ULL },
	{ 6,	64,	13,	0x1f8000000000000ULL },
	{ 6,	32,	13,	0x1f8000001f80000ULL },
	{ 6,	16,	13,	0x1f801f801f801f8ULL },
	{ 7,	64,	14,	0x1fc000000000000ULL },
	{ 7,	32,	14,	0x1fc000001fc0000ULL },
	{ 7,	16,	14,	0x1fc01fc01fc01fcULL },
	{ 8,	64,	15,	0x1fe000000000000ULL },
	{ 8,	32,	15,	0x1fe000001fe0000ULL },
	{ 8,	16,	15,	0x1fe01fe01fe01feULL },
	{ 9,	64,	16,	0x1ff000000000000ULL },
	{ 9,	32,	16,	0x1ff000001ff0000ULL },
	{ 9,	16,	0,	0x1ff01ff01ff01ffULL },
	{ 10,	64,	17,	0x1ff800000000000ULL },
	{ 10,	32,	17,	0x1ff800001ff8000ULL },
	{ 11,	64,	18,	0x1ffc00000000000ULL },
	{ 11,	32,	18,	0x1ffc00001ffc000ULL },
	{ 12,	64,	19,	0x1ffe00000000000ULL },
	{ 12,	32,	19,	0x1ffe00001ffe000ULL },
	{ 13,	64,	20,	0x1fff00000000000ULL },
	{ 13,	32,	20,	0x1fff00001fff000ULL },
	{ 14,	64,	21,	0x1fff80000000000ULL },
	{ 14,	32,	21,	0x1fff80001fff800ULL },
	{ 15,	64,	22,	0x1fffc0000000000ULL },
	{ 15,	32,	22,	0x1fffc0001fffc00ULL },
	{ 16,	64,	23,	0x1fffe0000000000ULL },
	{ 16,	32,	23,	0x1fffe0001fffe00ULL },
	{ 17,	64,	24,	0x1ffff0000000000ULL },
	{ 17,	32,	24,	0x1ffff0001ffff00ULL },
	{ 18,	64,	25,	0x1ffff8000000000ULL },
	{ 18,	32,	25,	0x1ffff8001ffff80ULL },
	{ 19,	64,	26,	0x1ffffc000000000ULL },
	{ 19,	32,	26,	0x1ffffc001ffffc0ULL },
	{ 20,	64,	27,	0x1ffffe000000000ULL },
	{ 20,	32,	27,	0x1ffffe001ffffe0ULL },
	{ 21,	64,	28,	0x1fffff000000000ULL },
	{ 21,	32,	28,	0x1fffff001fffff0ULL },
	{ 22,	64,	29,	0x1fffff800000000ULL },
	{ 22,	32,	29,	0x1fffff801fffff8ULL },
	{ 23,	64,	30,	0x1fffffc00000000ULL },
	{ 23,	32,	30,	0x1fffffc01fffffcULL },
	{ 24,	64,	31,	0x1fffffe00000000ULL },
	{ 24,	32,	31,	0x1fffffe01fffffeULL },
	{ 25,	64,	32,	0x1ffffff00000000ULL },
	{ 25,	32,	0,	0x1ffffff01ffffffULL },
	{ 26,	64,	33,	0x1ffffff80000000ULL },
	{ 27,	64,	34,	0x1ffffffc0000000ULL },
	{ 28,	64,	35,	0x1ffffffe0000000ULL },
	{ 29,	64,	36,	0x1fffffff0000000ULL },
	{ 30,	64,	37,	0x1fffffff8000000ULL },
	{ 31,	64,	38,	0x1fffffffc000000ULL },
	{ 32,	64,	39,	0x1fffffffe000000ULL },
	{ 33,	64,	40,	0x1ffffffff000000ULL },
	{ 34,	64,	41,	0x1ffffffff800000ULL },
	{ 35,	64,	42,	0x1ffffffffc00000ULL },
	{ 36,	64,	43,	0x1ffffffffe00000ULL },
	{ 37,	64,	44,	0x1fffffffff00000ULL },
	{ 38,	64,	45,	0x1fffffffff80000ULL },
	{ 39,	64,	46,	0x1fffffffffc0000ULL },
	{ 40,	64,	47,	0x1fffffffffe0000ULL },
	{ 41,	64,	48,	0x1ffffffffff0000ULL },
	{ 42,	64,	49,	0x1ffffffffff8000ULL },
	{ 43,	64,	50,	0x1ffffffffffc000ULL },
	{ 44,	64,	51,	0x1ffffffffffe000ULL },
	{ 45,	64,	52,	0x1fffffffffff000ULL },
	{ 46,	64,	53,	0x1fffffffffff800ULL },
	{ 47,	64,	54,	0x1fffffffffffc00ULL },
	{ 48,	64,	55,	0x1fffffffffffe00ULL },
	{ 49,	64,	56,	0x1ffffffffffff00ULL },
	{ 50,	64,	57,	0x1ffffffffffff80ULL },
	{ 51,	64,	58,	0x1ffffffffffffc0ULL },
	{ 52,	64,	59,	0x1ffffffffffffe0ULL },
	{ 53,	64,	60,	0x1fffffffffffff0ULL },
	{ 54,	64,	61,	0x1fffffffffffff8ULL },
	{ 55,	64,	62,	0x1fffffffffffffcULL },
	{ 56,	64,	63,	0x1fffffffffffffeULL },
	{ 57,	64,	0,	0x1ffffffffffffffULL },
	{ 1,	64,	7,	0x200000000000000ULL },
	{ 1,	32,	7,	0x200000002000000ULL },
	{ 1,	16,	7,	0x200020002000200ULL },
	{ 1,	8,	7,	0x202020202020202ULL },
	{ 2,	64,	8,	0x300000000000000ULL },
	{ 2,	32,	8,	0x300000003000000ULL },
	{ 2,	16,	8,	0x300030003000300ULL },
	{ 2,	8,	0,	0x303030303030303ULL },
	{ 3,	64,	9,	0x380000000000000ULL },
	{ 3,	32,	9,	0x380000003800000ULL },
	{ 3,	16,	9,	0x380038003800380ULL },
	{ 4,	64,	10,	0x3c0000000000000ULL },
	{ 4,	32,	10,	0x3c0000003c00000ULL },
	{ 4,	16,	10,	0x3c003c003c003c0ULL },
	{ 5,	64,	11,	0x3e0000000000000ULL },
	{ 5,	32,	11,	0x3e0000003e00000ULL },
	{ 5,	16,	11,	0x3e003e003e003e0ULL },
	{ 6,	64,	12,	0x3f0000000000000ULL },
	{ 6,	32,	12,	0x3f0000003f00000ULL },
	{ 6,	16,	12,	0x3f003f003f003f0ULL },
	{ 7,	64,	13,	0x3f8000000000000ULL },
	{ 7,	32,	13,	0x3f8000003f80000ULL },
	{ 7,	16,	13,	0x3f803f803f803f8ULL },
	{ 8,	64,	14,	0x3fc000000000000ULL },
	{ 8,	32,	14,	0x3fc000003fc0000ULL },
	{ 8,	16,	14,	0x3fc03fc03fc03fcULL },
	{ 9,	64,	15,	0x3fe000000000000ULL },
	{ 9,	32,	15,	0x3fe000003fe0000ULL },
	{ 9,	16,	15,	0x3fe03fe03fe03feULL },
	{ 10,	64,	16,	0x3ff000000000000ULL },
	{ 10,	32,	16,	0x3ff000003ff0000ULL },
	{ 10,	16,	0,	0x3ff03ff03ff03ffULL },
	{ 11,	64,	17,	0x3ff800000000000ULL },
	{ 11,	32,	17,	0x3ff800003ff8000ULL },
	{ 12,	64,	18,	0x3ffc00000000000ULL },
	{ 12,	32,	18,	0x3ffc00003ffc000ULL },
	{ 13,	64,	19,	0x3ffe00000000000ULL },
	{ 13,	32,	19,	0x3ffe00003ffe000ULL },
	{ 14,	64,	20,	0x3fff00000000000ULL },
	{ 14,	32,	20,	0x3fff00003fff000ULL },
	{ 15,	64,	21,	0x3fff80000000000ULL },
	{ 15,	32,	21,	0x3fff80003fff800ULL },
	{ 16,	64,	22,	0x3fffc0000000000ULL },
	{ 16,	32,	22,	0x3fffc0003fffc00ULL },
	{ 17,	64,	23,	0x3fffe0000000000ULL },
	{ 17,	32,	23,	0x3fffe0003fffe00ULL },
	{ 18,	64,	24,	0x3ffff0000000000ULL },
	{ 18,	32,	24,	0x3ffff0003ffff00ULL },
	{ 19,	64,	25,	0x3ffff8000000000ULL },
	{ 19,	32,	25,	0x3ffff8003ffff80ULL },
	{ 20,	64,	26,	0x3ffffc000000000ULL },
	{ 20,	32,	26,	0x3ffffc003ffffc0ULL },
	{ 21,	64,	27,	0x3ffffe000000000ULL },
	{ 21,	32,	27,	0x3ffffe003ffffe0ULL },
	{ 22,	64,	28,	0x3fffff000000000ULL },
	{ 22,	32,	28,	0x3fffff003fffff0ULL },
	{ 23,	64,	29,	0x3fffff800000000ULL },
	{ 23,	32,	29,	0x3fffff803fffff8ULL },
	{ 24,	64,	30,	0x3fffffc00000000ULL },
	{ 24,	32,	30,	0x3fffffc03fffffcULL },
	{ 25,	64,	31,	0x3fffffe00000000ULL },
	{ 25,	32,	31,	0x3fffffe03fffffeULL },
	{ 26,	64,	32,	0x3ffffff00000000ULL },
	{ 26,	32,	0,	0x3ffffff03ffffffULL },
	{ 27,	64,	33,	0x3ffffff80000000ULL },
	{ 28,	64,	34,	0x3ffffffc0000000ULL },
	{ 29,	64,	35,	0x3ffffffe0000000ULL },
	{ 30,	64,	36,	0x3fffffff0000000ULL },
	{ 31,	64,	37,	0x3fffffff8000000ULL },
	{ 32,	64,	38,	0x3fffffffc000000ULL },
	{ 33,	64,	39,	0x3fffffffe000000ULL },
	{ 34,	64,	40,	0x3ffffffff000000ULL },
	{ 35,	64,	41,	0x3ffffffff800000ULL },
	{ 36,	64,	42,	0x3ffffffffc00000ULL },
	{ 37,	64,	43,	0x3ffffffffe00000ULL },
	{ 38,	64,	44,	0x3fffffffff00000ULL },
	{ 39,	64,	45,	0x3fffffffff80000ULL },
	{ 40,	64,	46,	0x3fffffffffc0000ULL },
	{ 41,	64,	47,	0x3fffffffffe0000ULL },
	{ 42,	64,	48,	0x3ffffffffff0000ULL },
	{ 43,	64,	49,	0x3ffffffffff8000ULL },
	{ 44,	64,	50,	0x3ffffffffffc000ULL },
	{ 45,	64,	51,	0x3ffffffffffe000ULL },
	{ 46,	64,	52,	0x3fffffffffff000ULL },
	{ 47,	64,	53,	0x3fffffffffff800ULL },
	{ 48,	64,	54,	0x3fffffffffffc00ULL },
	{ 49,	64,	55,	0x3fffffffffffe00ULL },
	{ 50,	64,	56,	0x3ffffffffffff00ULL },
	{ 51,	64,	57,	0x3ffffffffffff80ULL },
	{ 52,	64,	58,	0x3ffffffffffffc0ULL },
	{ 53,	64,	59,	0x3ffffffffffffe0ULL },
	{ 54,	64,	60,	0x3fffffffffffff0ULL },
	{ 55,	64,	61,	0x3fffffffffffff8ULL },
	{ 56,	64,	62,	0x3fffffffffffffcULL },
	{ 57,	64,	63,	0x3fffffffffffffeULL },
	{ 58,	64,	0,	0x3ffffffffffffffULL },
	{ 1,	64,	6,	0x400000000000000ULL },
	{ 1,	32,	6,	0x400000004000000ULL },
	{ 1,	16,	6,	0x400040004000400ULL },
	{ 1,	8,	6,	0x404040404040404ULL },
	{ 2,	64,	7,	0x600000000000000ULL },
	{ 2,	32,	7,	0x600000006000000ULL },
	{ 2,	16,	7,	0x600060006000600ULL },
	{ 2,	8,	7,	0x606060606060606ULL },
	{ 3,	64,	8,	0x700000000000000ULL },
	{ 3,	32,	8,	0x700000007000000ULL },
	{ 3,	16,	8,	0x700070007000700ULL },
	{ 3,	8,	0,	0x707070707070707ULL },
	{ 4,	64,	9,	0x780000000000000ULL },
	{ 4,	32,	9,	0x780000007800000ULL },
	{ 4,	16,	9,	0x780078007800780ULL },
	{ 5,	64,	10,	0x7c0000000000000ULL },
	{ 5,	32,	10,	0x7c0000007c00000ULL },
	{ 5,	16,	10,	0x7c007c007c007c0ULL },
	{ 6,	64,	11,	0x7e0000000000000ULL },
	{ 6,	32,	11,	0x7e0000007e00000ULL },
	{ 6,	16,	11,	0x7e007e007e007e0ULL },
	{ 7,	64,	12,	0x7f0000000000000ULL },
	{ 7,	32,	12,	0x7f0000007f00000ULL },
	{ 7,	16,	12,	0x7f007f007f007f0ULL },
	{ 8,	64,	13,	0x7f8000000000000ULL },
	{ 8,	32,	13,	0x7f8000007f80000ULL },
	{ 8,	16,	13,	0x7f807f807f807f8ULL },
	{ 9,	64,	14,	0x7fc000000000000ULL },
	{ 9,	32,	14,	0x7fc000007fc0000ULL },
	{ 9,	16,	14,	0x7fc07fc07fc07fcULL },
	{ 10,	64,	15,	0x7fe000000000000ULL },
	{ 10,	32,	15,	0x7fe000007fe0000ULL },
	{ 10,	16,	15,	0x7fe07fe07fe07feULL },
	{ 11,	64,	16,	0x7ff000000000000ULL },
	{ 11,	32,	16,	0x7ff000007ff0000ULL },
	{ 11,	16,	0,	0x7ff07ff07ff07ffULL },
	{ 12,	64,	17,	0x7ff800000000000ULL },
	{ 12,	32,	17,	0x7ff800007ff8000ULL },
	{ 13,	64,	18,	0x7ffc00000000000ULL },
	{ 13,	32,	18,	0x7ffc00007ffc000ULL },
	{ 14,	64,	19,	0x7ffe00000000000ULL },
	{ 14,	32,	19,	0x7ffe00007ffe000ULL },
	{ 15,	64,	20,	0x7fff00000000000ULL },
	{ 15,	32,	20,	0x7fff00007fff000ULL },
	{ 16,	64,	21,	0x7fff80000000000ULL },
	{ 16,	32,	21,	0x7fff80007fff800ULL },
	{ 17,	64,	22,	0x7fffc0000000000ULL },
	{ 17,	32,	22,	0x7fffc0007fffc00ULL },
	{ 18,	64,	23,	0x7fffe0000000000ULL },
	{ 18,	32,	23,	0x7fffe0007fffe00ULL },
	{ 19,	64,	24,	0x7ffff0000000000ULL },
	{ 19,	32,	24,	0x7ffff0007ffff00ULL },
	{ 20,	64,	25,	0x7ffff8000000000ULL },
	{ 20,	32,	25,	0x7ffff8007ffff80ULL },
	{ 21,	64,	26,	0x7ffffc000000000ULL },
	{ 21,	32,	26,	0x7ffffc007ffffc0ULL },
	{ 22,	64,	27,	0x7ffffe000000000ULL },
	{ 22,	32,	27,	0x7ffffe007ffffe0ULL },
	{ 23,	64,	28,	0x7fffff000000000ULL },
	{ 23,	32,	28,	0x7fffff007fffff0ULL },
	{ 24,	64,	29,	0x7fffff800000000ULL },
	{ 24,	32,	29,	0x7fffff807fffff8ULL },
	{ 25,	64,	30,	0x7fffffc00000000ULL },
	{ 25,	32,	30,	0x7fffffc07fffffcULL },
	{ 26,	64,	31,	0x7fffffe00000000ULL },
	{ 26,	32,	31,	0x7fffffe07fffffeULL },
	{ 27,	64,	32,	0x7ffffff00000000ULL },
	{ 27,	32,	0,	0x7ffffff07ffffffULL },
	{ 28,	64,	33,	0x7ffffff80000000ULL },
	{ 29,	64,	34,	0x7ffffffc0000000ULL },
	{ 30,	64,	35,	0x7ffffffe0000000ULL },
	{ 31,	64,	36,	0x7fffffff0000000ULL },
	{ 32,	64,	37,	0x7fffffff8000000ULL },
	{ 33,	64,	38,	0x7fffffffc000000ULL },
	{ 34,	64,	39,	0x7fffffffe000000ULL },
	{ 35,	64,	40,	0x7ffffffff000000ULL },
	{ 36,	64,	41,	0x7ffffffff800000ULL },
	{ 37,	64,	42,	0x7ffffffffc00000ULL },
	{ 38,	64,	43,	0x7ffffffffe00000ULL },
	{ 39,	64,	44,	0x7fffffffff00000ULL },
	{ 40,	64,	45,	0x7fffffffff80000ULL },
	{ 41,	64,	46,	0x7fffffffffc0000ULL },
	{ 42,	64,	47,	0x7fffffffffe0000ULL },
	{ 43,	64,	48,	0x7ffffffffff0000ULL },
	{ 44,	64,	49,	0x7ffffffffff8000ULL },
	{ 45,	64,	50,	0x7ffffffffffc000ULL },
	{ 46,	64,	51,	0x7ffffffffffe000ULL },
	{ 47,	64,	52,	0x7fffffffffff000ULL },
	{ 48,	64,	53,	0x7fffffffffff800ULL },
	{ 49,	64,	54,	0x7fffffffffffc00ULL },
	{ 50,	64,	55,	0x7fffffffffffe00ULL },
	{ 51,	64,	56,	0x7ffffffffffff00ULL },
	{ 52,	64,	57,	0x7ffffffffffff80ULL },
	{ 53,	64,	58,	0x7ffffffffffffc0ULL },
	{ 54,	64,	59,	0x7ffffffffffffe0ULL },
	{ 55,	64,	60,	0x7fffffffffffff0ULL },
	{ 56,	64,	61,	0x7fffffffffffff8ULL },
	{ 57,	64,	62,	0x7fffffffffffffcULL },
	{ 58,	64,	63,	0x7fffffffffffffeULL },
	{ 59,	64,	0,	0x7ffffffffffffffULL },
	{ 1,	64,	5,	0x800000000000000ULL },
	{ 1,	32,	5,	0x800000008000000ULL },
	{ 1,	16,	5,	0x800080008000800ULL },
	{ 1,	8,	5,	0x808080808080808ULL },
	{ 2,	64,	6,	0xc00000000000000ULL },
	{ 2,	32,	6,	0xc0000000c000000ULL },
	{ 2,	16,	6,	0xc000c000c000c00ULL },
	{ 2,	8,	6,	0xc0c0c0c0c0c0c0cULL },
	{ 3,	64,	7,	0xe00000000000000ULL },
	{ 3,	32,	7,	0xe0000000e000000ULL },
	{ 3,	16,	7,	0xe000e000e000e00ULL },
	{ 3,	8,	7,	0xe0e0e0e0e0e0e0eULL },
	{ 4,	64,	8,	0xf00000000000000ULL },
	{ 4,	32,	8,	0xf0000000f000000ULL },
	{ 4,	16,	8,	0xf000f000f000f00ULL },
	{ 4,	8,	0,	0xf0f0f0f0f0f0f0fULL },
	{ 5,	64,	9,	0xf80000000000000ULL },
	{ 5,	32,	9,	0xf8000000f800000ULL },
	{ 5,	16,	9,	0xf800f800f800f80ULL },
	{ 6,	64,	10,	0xfc0000000000000ULL },
	{ 6,	32,	10,	0xfc000000fc00000ULL },
	{ 6,	16,	10,	0xfc00fc00fc00fc0ULL },
	{ 7,	64,	11,	0xfe0000000000000ULL },
	{ 7,	32,	11,	0xfe000000fe00000ULL },
	{ 7,	16,	11,	0xfe00fe00fe00fe0ULL },
	{ 8,	64,	12,	0xff0000000000000ULL },
	{ 8,	32,	12,	0xff000000ff00000ULL },
	{ 8,	16,	12,	0xff00ff00ff00ff0ULL },
	{ 9,	64,	13,	0xff8000000000000ULL },
	{ 9,	32,	13,	0xff800000ff80000ULL },
	{ 9,	16,	13,	0xff80ff80ff80ff8ULL },
	{ 10,	64,	14,	0xffc000000000000ULL },
	{ 10,	32,	14,	0xffc00000ffc0000ULL },
	{ 10,	16,	14,	0xffc0ffc0ffc0ffcULL },
	{ 11,	64,	15,	0xffe000000000000ULL },
	{ 11,	32,	15,	0xffe00000ffe0000ULL },
	{ 11,	16,	15,	0xffe0ffe0ffe0ffeULL },
	{ 12,	64,	16,	0xfff000000000000ULL },
	{ 12,	32,	16,	0xfff00000fff0000ULL },
	{ 12,	16,	0,	0xfff0fff0fff0fffULL },
	{ 13,	64,	17,	0xfff800000000000ULL },
	{ 13,	32,	17,	0xfff80000fff8000ULL },
	{ 14,	64,	18,	0xfffc00000000000ULL },
	{ 14,	32,	18,	0xfffc0000fffc000ULL },
	{ 15,	64,	19,	0xfffe00000000000ULL },
	{ 15,	32,	19,	0xfffe0000fffe000ULL },
	{ 16,	64,	20,	0xffff00000000000ULL },
	{ 16,	32,	20,	0xffff0000ffff000ULL },
	{ 17,	64,	21,	0xffff80000000000ULL },
	{ 17,	32,	21,	0xffff8000ffff800ULL },
	{ 18,	64,	22,	0xffffc0000000000ULL },
	{ 18,	32,	22,	0xffffc000ffffc00ULL },
	{ 19,	64,	23,	0xffffe0000000000ULL },
	{ 19,	32,	23,	0xffffe000ffffe00ULL },
	{ 20,	64,	24,	0xfffff0000000000ULL },
	{ 20,	32,	24,	0xfffff000fffff00ULL },
	{ 21,	64,	25,	0xfffff8000000000ULL },
	{ 21,	32,	25,	0xfffff800fffff80ULL },
	{ 22,	64,	26,	0xfffffc000000000ULL },
	{ 22,	32,	26,	0xfffffc00fffffc0ULL },
	{ 23,	64,	27,	0xfffffe000000000ULL },
	{ 23,	32,	27,	0xfffffe00fffffe0ULL },
	{ 24,	64,	28,	0xffffff000000000ULL },
	{ 24,	32,	28,	0xffffff00ffffff0ULL },
	{ 25,	64,	29,	0xffffff800000000ULL },
	{ 25,	32,	29,	0xffffff80ffffff8ULL },
	{ 26,	64,	30,	0xffffffc00000000ULL },
	{ 26,	32,	30,	0xffffffc0ffffffcULL },
	{ 27,	64,	31,	0xffffffe00000000ULL },
	{ 27,	32,	31,	0xffffffe0ffffffeULL },
	{ 28,	64,	32,	0xfffffff00000000ULL },
	{ 28,	32,	0,	0xfffffff0fffffffULL },
	{ 29,	64,	33,	0xfffffff80000000ULL },
	{ 30,	64,	34,	0xfffffffc0000000ULL },
	{ 31,	64,	35,	0xfffffffe0000000ULL },
	{ 32,	64,	36,	0xffffffff0000000ULL },
	{ 33,	64,	37,	0xffffffff8000000ULL },
	{ 34,	64,	38,	0xffffffffc000000ULL },
	{ 35,	64,	39,	0xffffffffe000000ULL },
	{ 36,	64,	40,	0xfffffffff000000ULL },
	{ 37,	64,	41,	0xfffffffff800000ULL },
	{ 38,	64,	42,	0xfffffffffc00000ULL },
	{ 39,	64,	43,	0xfffffffffe00000ULL },
	{ 40,	64,	44,	0xffffffffff00000ULL },
	{ 41,	64,	45,	0xffffffffff80000ULL },
	{ 42,	64,	46,	0xffffffffffc0000ULL },
	{ 43,	64,	47,	0xffffffffffe0000ULL },
	{ 44,	64,	48,	0xfffffffffff0000ULL },
	{ 45,	64,	49,	0xfffffffffff8000ULL },
	{ 46,	64,	50,	0xfffffffffffc000ULL },
	{ 47,	64,	51,	0xfffffffffffe000ULL },
	{ 48,	64,	52,	0xffffffffffff000ULL },
	{ 49,	64,	53,	0xffffffffffff800ULL },
	{ 50,	64,	54,	0xffffffffffffc00ULL },
	{ 51,	64,	55,	0xffffffffffffe00ULL },
	{ 52,	64,	56,	0xfffffffffffff00ULL },
	{ 53,	64,	57,	0xfffffffffffff80ULL },
	{ 54,	64,	58,	0xfffffffffffffc0ULL },
	{ 55,	64,	59,	0xfffffffffffffe0ULL },
	{ 56,	64,	60,	0xffffffffffffff0ULL },
	{ 57,	64,	61,	0xffffffffffffff8ULL },
	{ 58,	64,	62,	0xffffffffffffffcULL },
	{ 59,	64,	63,	0xffffffffffffffeULL },
	{ 60,	64,	0,	0xfffffffffffffffULL },
	{ 1,	64,	4,	0x1000000000000000ULL },
	{ 1,	32,	4,	0x1000000010000000ULL },
	{ 1,	16,	4,	0x1000100010001000ULL },
	{ 1,	8,	4,	0x1010101010101010ULL },
	{ 1,	4,	0,	0x1111111111111111ULL },
	{ 2,	64,	5,	0x1800000000000000ULL },
	{ 2,	32,	5,	0x1800000018000000ULL },
	{ 2,	16,	5,	0x1800180018001800ULL },
	{ 2,	8,	5,	0x1818181818181818ULL },
	{ 3,	64,	6,	0x1c00000000000000ULL },
	{ 3,	32,	6,	0x1c0000001c000000ULL },
	{ 3,	16,	6,	0x1c001c001c001c00ULL },
	{ 3,	8,	6,	0x1c1c1c1c1c1c1c1cULL },
	{ 4,	64,	7,	0x1e00000000000000ULL },
	{ 4,	32,	7,	0x1e0000001e000000ULL },
	{ 4,	16,	7,	0x1e001e001e001e00ULL },
	{ 4,	8,	7,	0x1e1e1e1e1e1e1e1eULL },
	{ 5,	64,	8,	0x1f00000000000000ULL },
	{ 5,	32,	8,	0x1f0000001f000000ULL },
	{ 5,	16,	8,	0x1f001f001f001f00ULL },
	{ 5,	8,	0,	0x1f1f1f1f1f1f1f1fULL },
	{ 6,	64,	9,	0x1f80000000000000ULL },
	{ 6,	32,	9,	0x1f8000001f800000ULL },
	{ 6,	16,	9,	0x1f801f801f801f80ULL },
	{ 7,	64,	10,	0x1fc0000000000000ULL },
	{ 7,	32,	10,	0x1fc000001fc00000ULL },
	{ 7,	16,	10,	0x1fc01fc01fc01fc0ULL },
	{ 8,	64,	11,	0x1fe0000000000000ULL },
	{ 8,	32,	11,	0x1fe000001fe00000ULL },
	{ 8,	16,	11,	0x1fe01fe01fe01fe0ULL },
	{ 9,	64,	12,	0x1ff0000000000000ULL },
	{ 9,	32,	12,	0x1ff000001ff00000ULL },
	{ 9,	16,	12,	0x1ff01ff01ff01ff0ULL },
	{ 10,	64,	13,	0x1ff8000000000000ULL },
	{ 10,	32,	13,	0x1ff800001ff80000ULL },
	{ 10,	16,	13,	0x1ff81ff81ff81ff8ULL },
	{ 11,	64,	14,	0x1ffc000000000000ULL },
	{ 11,	32,	14,	0x1ffc00001ffc0000ULL },
	{ 11,	16,	14,	0x1ffc1ffc1ffc1ffcULL },
	{ 12,	64,	15,	0x1ffe000000000000ULL },
	{ 12,	32,	15,	0x1ffe00001ffe0000ULL },
	{ 12,	16,	15,	0x1ffe1ffe1ffe1ffeULL },
	{ 13,	64,	16,	0x1fff000000000000ULL },
	{ 13,	32,	16,	0x1fff00001fff0000ULL },
	{ 13,	16,	0,	0x1fff1fff1fff1fffULL },
	{ 14,	64,	17,	0x1fff800000000000ULL },
	{ 14,	32,	17,	0x1fff80001fff8000ULL },
	{ 15,	64,	18,	0x1fffc00000000000ULL },
	{ 15,	32,	18,	0x1fffc0001fffc000ULL },
	{ 16,	64,	19,	0x1fffe00000000000ULL },
	{ 16,	32,	19,	0x1fffe0001fffe000ULL },
	{ 17,	64,	20,	0x1ffff00000000000ULL },
	{ 17,	32,	20,	0x1ffff0001ffff000ULL },
	{ 18,	64,	21,	0x1ffff80000000000ULL },
	{ 18,	32,	21,	0x1ffff8001ffff800ULL },
	{ 19,	64,	22,	0x1ffffc0000000000ULL },
	{ 19,	32,	22,	0x1ffffc001ffffc00ULL },
	{ 20,	64,	23,	0x1ffffe0000000000ULL },
	{ 20,	32,	23,	0x1ffffe001ffffe00ULL },
	{ 21,	64,	24,	0x1fffff0000000000ULL },
	{ 21,	32,	24,	0x1fffff001fffff00ULL },
	{ 22,	64,	25,	0x1fffff8000000000ULL },
	{ 22,	32,	25,	0x1fffff801fffff80ULL },
	{ 23,	64,	26,	0x1fffffc000000000ULL },
	{ 23,	32,	26,	0x1fffffc01fffffc0ULL },
	{ 24,	64,	27,	0x1fffffe000000000ULL },
	{ 24,	32,	27,	0x1fffffe01fffffe0ULL },
	{ 25,	64,	28,	0x1ffffff000000000ULL },
	{ 25,	32,	28,	0x1ffffff01ffffff0ULL },
	{ 26,	64,	29,	0x1ffffff800000000ULL },
	{ 26,	32,	29,	0x1ffffff81ffffff8ULL },
	{ 27,	64,	30,	0x1ffffffc00000000ULL },
	{ 27,	32,	30,	0x1ffffffc1ffffffcULL },
	{ 28,	64,	31,	0x1ffffffe00000000ULL },
	{ 28,	32,	31,	0x1ffffffe1ffffffeULL },
	{ 29,	64,	32,	0x1fffffff00000000ULL },
	{ 29,	32,	0,	0x1fffffff1fffffffULL },
	{ 30,	64,	33,	0x1fffffff80000000ULL },
	{ 31,	64,	34,	0x1fffffffc0000000ULL },
	{ 32,	64,	35,	0x1fffffffe0000000ULL },
	{ 33,	64,	36,	0x1ffffffff0000000ULL },
	{ 34,	64,	37,	0x1ffffffff8000000ULL },
	{ 35,	64,	38,	0x1ffffffffc000000ULL },
	{ 36,	64,	39,	0x1ffffffffe000000ULL },
	{ 37,	64,	40,	0x1fffffffff000000ULL },
	{ 38,	64,	41,	0x1fffffffff800000ULL },
	{ 39,	64,	42,	0x1fffffffffc00000ULL },
	{ 40,	64,	43,	0x1fffffffffe00000ULL },
	{ 41,	64,	44,	0x1ffffffffff00000ULL },
	{ 42,	64,	45,	0x1ffffffffff80000ULL },
	{ 43,	64,	46,	0x1ffffffffffc0000ULL },
	{ 44,	64,	47,	0x1ffffffffffe0000ULL },
	{ 45,	64,	48,	0x1fffffffffff0000ULL },
	{ 46,	64,	49,	0x1fffffffffff8000ULL },
	{ 47,	64,	50,	0x1fffffffffffc000ULL },
	{ 48,	64,	51,	0x1fffffffffffe000ULL },
	{ 49,	64,	52,	0x1ffffffffffff000ULL },
	{ 50,	64,	53,	0x1ffffffffffff800ULL },
	{ 51,	64,	54,	0x1ffffffffffffc00ULL },
	{ 52,	64,	55,	0x1ffffffffffffe00ULL },
	{ 53,	64,	56,	0x1fffffffffffff00ULL },
	{ 54,	64,	57,	0x1fffffffffffff80ULL },
	{ 55,	64,	58,	0x1fffffffffffffc0ULL },
	{ 56,	64,	59,	0x1fffffffffffffe0ULL },
	{ 57,	64,	60,	0x1ffffffffffffff0ULL },
	{ 58,	64,	61,	0x1ffffffffffffff8ULL },
	{ 59,	64,	62,	0x1ffffffffffffffcULL },
	{ 60,	64,	63,	0x1ffffffffffffffeULL },
	{ 61,	64,	0,	0x1fffffffffffffffULL },
	{ 1,	64,	3,	0x2000000000000000ULL },
	{ 1,	32,	3,	0x2000000020000000ULL },
	{ 1,	16,	3,	0x2000200020002000ULL },
	{ 1,	8,	3,	0x2020202020202020ULL },
	{ 1,	4,	3,	0x2222222222222222ULL },
	{ 2,	64,	4,	0x3000000000000000ULL },
	{ 2,	32,	4,	0x3000000030000000ULL },
	{ 2,	16,	4,	0x3000300030003000ULL },
	{ 2,	8,	4,	0x3030303030303030ULL },
	{ 2,	4,	0,	0x3333333333333333ULL },
	{ 3,	64,	5,	0x3800000000000000ULL },
	{ 3,	32,	5,	0x3800000038000000ULL },
	{ 3,	16,	5,	0x3800380038003800ULL },
	{ 3,	8,	5,	0x3838383838383838ULL },
	{ 4,	64,	6,	0x3c00000000000000ULL },
	{ 4,	32,	6,	0x3c0000003c000000ULL },
	{ 4,	16,	6,	0x3c003c003c003c00ULL },
	{ 4,	8,	6,	0x3c3c3c3c3c3c3c3cULL },
	{ 5,	64,	7,	0x3e00000000000000ULL },
	{ 5,	32,	7,	0x3e0000003e000000ULL },
	{ 5,	16,	7,	0x3e003e003e003e00ULL },
	{ 5,	8,	7,	0x3e3e3e3e3e3e3e3eULL },
	{ 6,	64,	8,	0x3f00000000000000ULL },
	{ 6,	32,	8,	0x3f0000003f000000ULL },
	{ 6,	16,	8,	0x3f003f003f003f00ULL },
	{ 6,	8,	0,	0x3f3f3f3f3f3f3f3fULL },
	{ 7,	64,	9,	0x3f80000000000000ULL },
	{ 7,	32,	9,	0x3f8000003f800000ULL },
	{ 7,	16,	9,	0x3f803f803f803f80ULL },
	{ 8,	64,	10,	0x3fc0000000000000ULL },
	{ 8,	32,	10,	0x3fc000003fc00000ULL },
	{ 8,	16,	10,	0x3fc03fc03fc03fc0ULL },
	{ 9,	64,	11,	0x3fe0000000000000ULL },
	{ 9,	32,	11,	0x3fe000003fe00000ULL },
	{ 9,	16,	11,	0x3fe03fe03fe03fe0ULL },
	{ 10,	64,	12,	0x3ff0000000000000ULL },
	{ 10,	32,	12,	0x3ff000003ff00000ULL },
	{ 10,	16,	12,	0x3ff03ff03ff03ff0ULL },
	{ 11,	64,	13,	0x3ff8000000000000ULL },
	{ 11,	32,	13,	0x3ff800003ff80000ULL },
	{ 11,	16,	13,	0x3ff83ff83ff83ff8ULL },
	{ 12,	64,	14,	0x3ffc000000000000ULL },
	{ 12,	32,	14,	0x3ffc00003ffc0000ULL },
	{ 12,	16,	14,	0x3ffc3ffc3ffc3ffcULL },
	{ 13,	64,	15,	0x3ffe000000000000ULL },
	{ 13,	32,	15,	0x3ffe00003ffe0000ULL },
	{ 13,	16,	15,	0x3ffe3ffe3ffe3ffeULL },
	{ 14,	64,	16,	0x3fff000000000000ULL },
	{ 14,	32,	16,	0x3fff00003fff0000ULL },
	{ 14,	16,	0,	0x3fff3fff3fff3fffULL },
	{ 15,	64,	17,	0x3fff800000000000ULL },
	{ 15,	32,	17,	0x3fff80003fff8000ULL },
	{ 16,	64,	18,	0x3fffc00000000000ULL },
	{ 16,	32,	18,	0x3fffc0003fffc000ULL },
	{ 17,	64,	19,	0x3fffe00000000000ULL },
	{ 17,	32,	19,	0x3fffe0003fffe000ULL },
	{ 18,	64,	20,	0x3ffff00000000000ULL },
	{ 18,	32,	20,	0x3ffff0003ffff000ULL },
	{ 19,	64,	21,	0x3ffff80000000000ULL },
	{ 19,	32,	21,	0x3ffff8003ffff800ULL },
	{ 20,	64,	22,	0x3ffffc0000000000ULL },
	{ 20,	32,	22,	0x3ffffc003ffffc00ULL },
	{ 21,	64,	23,	0x3ffffe0000000000ULL },
	{ 21,	32,	23,	0x3ffffe003ffffe00ULL },
	{ 22,	64,	24,	0x3fffff0000000000ULL },
	{ 22,	32,	24,	0x3fffff003fffff00ULL },
	{ 23,	64,	25,	0x3fffff8000000000ULL },
	{ 23,	32,	25,	0x3fffff803fffff80ULL },
	{ 24,	64,	26,	0x3fffffc000000000ULL },
	{ 24,	32,	26,	0x3fffffc03fffffc0ULL },
	{ 25,	64,	27,	0x3fffffe000000000ULL },
	{ 25,	32,	27,	0x3fffffe03fffffe0ULL },
	{ 26,	64,	28,	0x3ffffff000000000ULL },
	{ 26,	32,	28,	0x3ffffff03ffffff0ULL },
	{ 27,	64,	29,	0x3ffffff800000000ULL },
	{ 27,	32,	29,	0x3ffffff83ffffff8ULL },
	{ 28,	64,	30,	0x3ffffffc00000000ULL },
	{ 28,	32,	30,	0x3ffffffc3ffffffcULL },
	{ 29,	64,	31,	0x3ffffffe00000000ULL },
	{ 29,	32,	31,	0x3ffffffe3ffffffeULL },
	{ 30,	64,	32,	0x3fffffff00000000ULL },
	{ 30,	32,	0,	0x3fffffff3fffffffULL },
	{ 31,	64,	33,	0x3fffffff80000000ULL },
	{ 32,	64,	34,	0x3fffffffc0000000ULL },
	{ 33,	64,	35,	0x3fffffffe0000000ULL },
	{ 34,	64,	36,	0x3ffffffff0000000ULL },
	{ 35,	64,	37,	0x3ffffffff8000000ULL },
	{ 36,	64,	38,	0x3ffffffffc000000ULL },
	{ 37,	64,	39,	0x3ffffffffe000000ULL },
	{ 38,	64,	40,	0x3fffffffff000000ULL },
	{ 39,	64,	41,	0x3fffffffff800000ULL },
	{ 40,	64,	42,	0x3fffffffffc00000ULL },
	{ 41,	64,	43,	0x3fffffffffe00000ULL },
	{ 42,	64,	44,	0x3ffffffffff00000ULL },
	{ 43,	64,	45,	0x3ffffffffff80000ULL },
	{ 44,	64,	46,	0x3ffffffffffc0000ULL },
	{ 45,	64,	47,	0x3ffffffffffe0000ULL },
	{ 46,	64,	48,	0x3fffffffffff0000ULL },
	{ 47,	64,	49,	0x3fffffffffff8000ULL },
	{ 48,	64,	50,	0x3fffffffffffc000ULL },
	{ 49,	64,	51,	0x3fffffffffffe000ULL },
	{ 50,	64,	52,	0x3ffffffffffff000ULL },
	{ 51,	64,	53,	0x3ffffffffffff800ULL },
	{ 52,	64,	54,	0x3ffffffffffffc00ULL },
	{ 53,	64,	55,	0x3ffffffffffffe00ULL },
	{ 54,	64,	56,	0x3fffffffffffff00ULL },
	{ 55,	64,	57,	0x3fffffffffffff80ULL },
	{ 56,	64,	58,	0x3fffffffffffffc0ULL },
	{ 57,	64,	59,	0x3fffffffffffffe0ULL },
	{ 58,	64,	60,	0x3ffffffffffffff0ULL },
	{ 59,	64,	61,	0x3ffffffffffffff8ULL },
	{ 60,	64,	62,	0x3ffffffffffffffcULL },
	{ 61,	64,	63,	0x3ffffffffffffffeULL },
	{ 62,	64,	0,	0x3fffffffffffffffULL },
	{ 1,	64,	2,	0x4000000000000000ULL },
	{ 1,	32,	2,	0x4000000040000000ULL },
	{ 1,	16,	2,	0x4000400040004000ULL },
	{ 1,	8,	2,	0x4040404040404040ULL },
	{ 1,	4,	2,	0x4444444444444444ULL },
	{ 1,	2,	0,	0x5555555555555555ULL },
	{ 2,	64,	3,	0x6000000000000000ULL },
	{ 2,	32,	3,	0x6000000060000000ULL },
	{ 2,	16,	3,	0x6000600060006000ULL },
	{ 2,	8,	3,	0x6060606060606060ULL },
	{ 2,	4,	3,	0x6666666666666666ULL },
	{ 3,	64,	4,	0x7000000000000000ULL },
	{ 3,	32,	4,	0x7000000070000000ULL },
	{ 3,	16,	4,	0x7000700070007000ULL },
	{ 3,	8,	4,	0x7070707070707070ULL },
	{ 3,	4,	0,	0x7777777777777777ULL },
	{ 4,	64,	5,	0x7800000000000000ULL },
	{ 4,	32,	5,	0x7800000078000000ULL },
	{ 4,	16,	5,	0x7800780078007800ULL },
	{ 4,	8,	5,	0x7878787878787878ULL },
	{ 5,	64,	6,	0x7c00000000000000ULL },
	{ 5,	32,	6,	0x7c0000007c000000ULL },
	{ 5,	16,	6,	0x7c007c007c007c00ULL },
	{ 5,	8,	6,	0x7c7c7c7c7c7c7c7cULL },
	{ 6,	64,	7,	0x7e00000000000000ULL },
	{ 6,	32,	7,	0x7e0000007e000000ULL },
	{ 6,	16,	7,	0x7e007e007e007e00ULL },
	{ 6,	8,	7,	0x7e7e7e7e7e7e7e7eULL },
	{ 7,	64,	8,	0x7f00000000000000ULL },
	{ 7,	32,	8,	0x7f0000007f000000ULL },
	{ 7,	16,	8,	0x7f007f007f007f00ULL },
	{ 7,	8,	0,	0x7f7f7f7f7f7f7f7fULL },
	{ 8,	64,	9,	0x7f80000000000000ULL },
	{ 8,	32,	9,	0x7f8000007f800000ULL },
	{ 8,	16,	9,	0x7f807f807f807f80ULL },
	{ 9,	64,	10,	0x7fc0000000000000ULL },
	{ 9,	32,	10,	0x7fc000007fc00000ULL },
	{ 9,	16,	10,	0x7fc07fc07fc07fc0ULL },
	{ 10,	64,	11,	0x7fe0000000000000ULL },
	{ 10,	32,	11,	0x7fe000007fe00000ULL },
	{ 10,	16,	11,	0x7fe07fe07fe07fe0ULL },
	{ 11,	64,	12,	0x7ff0000000000000ULL },
	{ 11,	32,	12,	0x7ff000007ff00000ULL },
	{ 11,	16,	12,	0x7ff07ff07ff07ff0ULL },
	{ 12,	64,	13,	0x7ff8000000000000ULL },
	{ 12,	32,	13,	0x7ff800007ff80000ULL },
	{ 12,	16,	13,	0x7ff87ff87ff87ff8ULL },
	{ 13,	64,	14,	0x7ffc000000000000ULL },
	{ 13,	32,	14,	0x7ffc00007ffc0000ULL },
	{ 13,	16,	14,	0x7ffc7ffc7ffc7ffcULL },
	{ 14,	64,	15,	0x7ffe000000000000ULL },
	{ 14,	32,	15,	0x7ffe00007ffe0000ULL },
	{ 14,	16,	15,	0x7ffe7ffe7ffe7ffeULL },
	{ 15,	64,	16,	0x7fff000000000000ULL },
	{ 15,	32,	16,	0x7fff00007fff0000ULL },
	{ 15,	16,	0,	0x7fff7fff7fff7fffULL },
	{ 16,	64,	17,	0x7fff800000000000ULL },
	{ 16,	32,	17,	0x7fff80007fff8000ULL },
	{ 17,	64,	18,	0x7fffc00000000000ULL },
	{ 17,	32,	18,	0x7fffc0007fffc000ULL },
	{ 18,	64,	19,	0x7fffe00000000000ULL },
	{ 18,	32,	19,	0x7fffe0007fffe000ULL },
	{ 19,	64,	20,	0x7ffff00000000000ULL },
	{ 19,	32,	20,	0x7ffff0007ffff000ULL },
	{ 20,	64,	21,	0x7ffff80000000000ULL },
	{ 20,	32,	21,	0x7ffff8007ffff800ULL },
	{ 21,	64,	22,	0x7ffffc0000000000ULL },
	{ 21,	32,	22,	0x7ffffc007ffffc00ULL },
	{ 22,	64,	23,	0x7ffffe0000000000ULL },
	{ 22,	32,	23,	0x7ffffe007ffffe00ULL },
	{ 23,	64,	24,	0x7fffff0000000000ULL },
	{ 23,	32,	24,	0x7fffff007fffff00ULL },
	{ 24,	64,	25,	0x7fffff8000000000ULL },
	{ 24,	32,	25,	0x7fffff807fffff80ULL },
	{ 25,	64,	26,	0x7fffffc000000000ULL },
	{ 25,	32,	26,	0x7fffffc07fffffc0ULL },
	{ 26,	64,	27,	0x7fffffe000000000ULL },
	{ 26,	32,	27,	0x7fffffe07fffffe0ULL },
	{ 27,	64,	28,	0x7ffffff000000000ULL },
	{ 27,	32,	28,	0x7ffffff07ffffff0ULL },
	{ 28,	64,	29,	0x7ffffff800000000ULL },
	{ 28,	32,	29,	0x7ffffff87ffffff8ULL },
	{ 29,	64,	30,	0x7ffffffc00000000ULL },
	{ 29,	32,	30,	0x7ffffffc7ffffffcULL },
	{ 30,	64,	31,	0x7ffffffe00000000ULL },
	{ 30,	32,	31,	0x7ffffffe7ffffffeULL },
	{ 31,	64,	32,	0x7fffffff00000000ULL },
	{ 31,	32,	0,	0x7fffffff7fffffffULL },
	{ 32,	64,	33,	0x7fffffff80000000ULL },
	{ 33,	64,	34,	0x7fffffffc0000000ULL },
	{ 34,	64,	35,	0x7fffffffe0000000ULL },
	{ 35,	64,	36,	0x7ffffffff0000000ULL },
	{ 36,	64,	37,	0x7ffffffff8000000ULL },
	{ 37,	64,	38,	0x7ffffffffc000000ULL },
	{ 38,	64,	39,	0x7ffffffffe000000ULL },
	{ 39,	64,	40,	0x7fffffffff000000ULL },
	{ 40,	64,	41,	0x7fffffffff800000ULL },
	{ 41,	64,	42,	0x7fffffffffc00000ULL },
	{ 42,	64,	43,	0x7fffffffffe00000ULL },
	{ 43,	64,	44,	0x7ffffffffff00000ULL },
	{ 44,	64,	45,	0x7ffffffffff80000ULL },
	{ 45,	64,	46,	0x7ffffffffffc0000ULL },
	{ 46,	64,	47,	0x7ffffffffffe0000ULL },
	{ 47,	64,	48,	0x7fffffffffff0000ULL },
	{ 48,	64,	49,	0x7fffffffffff8000ULL },
	{ 49,	64,	50,	0x7fffffffffffc000ULL },
	{ 50,	64,	51,	0x7fffffffffffe000ULL },
	{ 51,	64,	52,	0x7ffffffffffff000ULL },
	{ 52,	64,	53,	0x7ffffffffffff800ULL },
	{ 53,	64,	54,	0x7ffffffffffffc00ULL },
	{ 54,	64,	55,	0x7ffffffffffffe00ULL },
	{ 55,	64,	56,	0x7fffffffffffff00ULL },
	{ 56,	64,	57,	0x7fffffffffffff80ULL },
	{ 57,	64,	58,	0x7fffffffffffffc0ULL },
	{ 58,	64,	59,	0x7fffffffffffffe0ULL },
	{ 59,	64,	60,	0x7ffffffffffffff0ULL },
	{ 60,	64,	61,	0x7ffffffffffffff8ULL },
	{ 61,	64,	62,	0x7ffffffffffffffcULL },
	{ 62,	64,	63,	0x7ffffffffffffffeULL },
	{ 63,	64,	0,	0x7fffffffffffffffULL },
	{ 1,	64,	1,	0x8000000000000000ULL },
	{ 2,	64,	1,	0x8000000000000001ULL },
	{ 3,	64,	1,	0x8000000000000003ULL },
	{ 4,	64,	1,	0x8000000000000007ULL },
	{ 5,	64,	1,	0x800000000000000fULL },
	{ 6,	64,	1,	0x800000000000001fULL },
	{ 7,	64,	1,	0x800000000000003fULL },
	{ 8,	64,	1,	0x800000000000007fULL },
	{ 9,	64,	1,	0x80000000000000ffULL },
	{ 10,	64,	1,	0x80000000000001ffULL },
	{ 11,	64,	1,	0x80000000000003ffULL },
	{ 12,	64,	1,	0x80000000000007ffULL },
	{ 13,	64,	1,	0x8000000000000fffULL },
	{ 14,	64,	1,	0x8000000000001fffULL },
	{ 15,	64,	1,	0x8000000000003fffULL },
	{ 16,	64,	1,	0x8000000000007fffULL },
	{ 17,	64,	1,	0x800000000000ffffULL },
	{ 18,	64,	1,	0x800000000001ffffULL },
	{ 19,	64,	1,	0x800000000003ffffULL },
	{ 20,	64,	1,	0x800000000007ffffULL },
	{ 21,	64,	1,	0x80000000000fffffULL },
	{ 22,	64,	1,	0x80000000001fffffULL },
	{ 23,	64,	1,	0x80000000003fffffULL },
	{ 24,	64,	1,	0x80000000007fffffULL },
	{ 25,	64,	1,	0x8000000000ffffffULL },
	{ 26,	64,	1,	0x8000000001ffffffULL },
	{ 27,	64,	1,	0x8000000003ffffffULL },
	{ 28,	64,	1,	0x8000000007ffffffULL },
	{ 29,	64,	1,	0x800000000fffffffULL },
	{ 30,	64,	1,	0x800000001fffffffULL },
	{ 31,	64,	1,	0x800000003fffffffULL },
	{ 32,	64,	1,	0x800000007fffffffULL },
	{ 1,	32,	1,	0x8000000080000000ULL },
	{ 33,	64,	1,	0x80000000ffffffffULL },
	{ 2,	32,	1,	0x8000000180000001ULL },
	{ 34,	64,	1,	0x80000001ffffffffULL },
	{ 3,	32,	1,	0x8000000380000003ULL },
	{ 35,	64,	1,	0x80000003ffffffffULL },
	{ 4,	32,	1,	0x8000000780000007ULL },
	{ 36,	64,	1,	0x80000007ffffffffULL },
	{ 5,	32,	1,	0x8000000f8000000fULL },
	{ 37,	64,	1,	0x8000000fffffffffULL },
	{ 6,	32,	1,	0x8000001f8000001fULL },
	{ 38,	64,	1,	0x8000001fffffffffULL },
	{ 7,	32,	1,	0x8000003f8000003fULL },
	{ 39,	64,	1,	0x8000003fffffffffULL },
	{ 8,	32,	1,	0x8000007f8000007fULL },
	{ 40,	64,	1,	0x8000007fffffffffULL },
	{ 9,	32,	1,	0x800000ff800000ffULL },
	{ 41,	64,	1,	0x800000ffffffffffULL },
	{ 10,	32,	1,	0x800001ff800001ffULL },
	{ 42,	64,	1,	0x800001ffffffffffULL },
	{ 11,	32,	1,	0x800003ff800003ffULL },
	{ 43,	64,	1,	0x800003ffffffffffULL },
	{ 12,	32,	1,	0x800007ff800007ffULL },
	{ 44,	64,	1,	0x800007ffffffffffULL },
	{ 13,	32,	1,	0x80000fff80000fffULL },
	{ 45,	64,	1,	0x80000fffffffffffULL },
	{ 14,	32,	1,	0x80001fff80001fffULL },
	{ 46,	64,	1,	0x80001fffffffffffULL },
	{ 15,	32,	1,	0x80003fff80003fffULL },
	{ 47,	64,	1,	0x80003fffffffffffULL },
	{ 16,	32,	1,	0x80007fff80007fffULL },
	{ 48,	64,	1,	0x80007fffffffffffULL },
	{ 1,	16,	1,	0x8000800080008000ULL },
	{ 17,	32,	1,	0x8000ffff8000ffffULL },
	{ 49,	64,	1,	0x8000ffffffffffffULL },
	{ 2,	16,	1,	0x8001800180018001ULL },
	{ 18,	32,	1,	0x8001ffff8001ffffULL },
	{ 50,	64,	1,	0x8001ffffffffffffULL },
	{ 3,	16,	1,	0x8003800380038003ULL },
	{ 19,	32,	1,	0x8003ffff8003ffffULL },
	{ 51,	64,	1,	0x8003ffffffffffffULL },
	{ 4,	16,	1,	0x8007800780078007ULL },
	{ 20,	32,	1,	0x8007ffff8007ffffULL },
	{ 52,	64,	1,	0x8007ffffffffffffULL },
	{ 5,	16,	1,	0x800f800f800f800fULL },
	{ 21,	32,	1,	0x800fffff800fffffULL },
	{ 53,	64,	1,	0x800fffffffffffffULL },
	{ 6,	16,	1,	0x801f801f801f801fULL },
	{ 22,	32,	1,	0x801fffff801fffffULL },
	{ 54,	64,	1,	0x801fffffffffffffULL },
	{ 7,	16,	1,	0x803f803f803f803fULL },
	{ 23,	32,	1,	0x803fffff803fffffULL },
	{ 55,	64,	1,	0x803fffffffffffffULL },
	{ 8,	16,	1,	0x807f807f807f807fULL },
	{ 24,	32,	1,	0x807fffff807fffffULL },
	{ 56,	64,	1,	0x807fffffffffffffULL },
	{ 1,	8,	1,	0x8080808080808080ULL },
	{ 9,	16,	1,	0x80ff80ff80ff80ffULL },
	{ 25,	32,	1,	0x80ffffff80ffffffULL },
	{ 57,	64,	1,	0x80ffffffffffffffULL },
	{ 2,	8,	1,	0x8181818181818181ULL },
	{ 10,	16,	1,	0x81ff81ff81ff81ffULL },
	{ 26,	32,	1,	0x81ffffff81ffffffULL },
	{ 58,	64,	1,	0x81ffffffffffffffULL },
	{ 3,	8,	1,	0x8383838383838383ULL },
	{ 11,	16,	1,	0x83ff83ff83ff83ffULL },
	{ 27,	32,	1,	0x83ffffff83ffffffULL },
	{ 59,	64,	1,	0x83ffffffffffffffULL },
	{ 4,	8,	1,	0x8787878787878787ULL },
	{ 12,	16,	1,	0x87ff87ff87ff87ffULL },
	{ 28,	32,	1,	0x87ffffff87ffffffULL },
	{ 60,	64,	1,	0x87ffffffffffffffULL },
	{ 1,	4,	1,	0x8888888888888888ULL },
	{ 5,	8,	1,	0x8f8f8f8f8f8f8f8fULL },
	{ 13,	16,	1,	0x8fff8fff8fff8fffULL },
	{ 29,	32,	1,	0x8fffffff8fffffffULL },
	{ 61,	64,	1,	0x8fffffffffffffffULL },
	{ 2,	4,	1,	0x9999999999999999ULL },
	{ 6,	8,	1,	0x9f9f9f9f9f9f9f9fULL },
	{ 14,	16,	1,	0x9fff9fff9fff9fffULL },
	{ 30,	32,	1,	0x9fffffff9fffffffULL },
	{ 62,	64,	1,	0x9fffffffffffffffULL },
	{ 1,	2,	1,	0xaaaaaaaaaaaaaaaaULL },
	{ 3,	4,	1,	0xbbbbbbbbbbbbbbbbULL },
	{ 7,	8,	1,	0xbfbfbfbfbfbfbfbfULL },
	{ 15,	16,	1,	0xbfffbfffbfffbfffULL },
	{ 31,	32,	1,	0xbfffffffbfffffffULL },
	{ 63,	64,	1,	0xbfffffffffffffffULL },
	{ 2,	64,	2,	0xc000000000000000ULL },
	{ 3,	64,	2,	0xc000000000000001ULL },
	{ 4,	64,	2,	0xc000000000000003ULL },
	{ 5,	64,	2,	0xc000000000000007ULL },
	{ 6,	64,	2,	0xc00000000000000fULL },
	{ 7,	64,	2,	0xc00000000000001fULL },
	{ 8,	64,	2,	0xc00000000000003fULL },
	{ 9,	64,	2,	0xc00000000000007fULL },
	{ 10,	64,	2,	0xc0000000000000ffULL },
	{ 11,	64,	2,	0xc0000000000001ffULL },
	{ 12,	64,	2,	0xc0000000000003ffULL },
	{ 13,	64,	2,	0xc0000000000007ffULL },
	{ 14,	64,	2,	0xc000000000000fffULL },
	{ 15,	64,	2,	0xc000000000001fffULL },
	{ 16,	64,	2,	0xc000000000003fffULL },
	{ 17,	64,	2,	0xc000000000007fffULL },
	{ 18,	64,	2,	0xc00000000000ffffULL },
	{ 19,	64,	2,	0xc00000000001ffffULL },
	{ 20,	64,	2,	0xc00000000003ffffULL },
	{ 21,	64,	2,	0xc00000000007ffffULL },
	{ 22,	64,	2,	0xc0000000000fffffULL },
	{ 23,	64,	2,	0xc0000000001fffffULL },
	{ 24,	64,	2,	0xc0000000003fffffULL },
	{ 25,	64,	2,	0xc0000000007fffffULL },
	{ 26,	64,	2,	0xc000000000ffffffULL },
	{ 27,	64,	2,	0xc000000001ffffffULL },
	{ 28,	64,	2,	0xc000000003ffffffULL },
	{ 29,	64,	2,	0xc000000007ffffffULL },
	{ 30,	64,	2,	0xc00000000fffffffULL },
	{ 31,	64,	2,	0xc00000001fffffffULL },
	{ 32,	64,	2,	0xc00000003fffffffULL },
	{ 33,	64,	2,	0xc00000007fffffffULL },
	{ 2,	32,	2,	0xc0000000c0000000ULL },
	{ 34,	64,	2,	0xc0000000ffffffffULL },
	{ 3,	32,	2,	0xc0000001c0000001ULL },
	{ 35,	64,	2,	0xc0000001ffffffffULL },
	{ 4,	32,	2,	0xc0000003c0000003ULL },
	{ 36,	64,	2,	0xc0000003ffffffffULL },
	{ 5,	32,	2,	0xc0000007c0000007ULL },
	{ 37,	64,	2,	0xc0000007ffffffffULL },
	{ 6,	32,	2,	0xc000000fc000000fULL },
	{ 38,	64,	2,	0xc000000fffffffffULL },
	{ 7,	32,	2,	0xc000001fc000001fULL },
	{ 39,	64,	2,	0xc000001fffffffffULL },
	{ 8,	32,	2,	0xc000003fc000003fULL },
	{ 40,	64,	2,	0xc000003fffffffffULL },
	{ 9,	32,	2,	0xc000007fc000007fULL },
	{ 41,	64,	2,	0xc000007fffffffffULL },
	{ 10,	32,	2,	0xc00000ffc00000ffULL },
	{ 42,	64,	2,	0xc00000ffffffffffULL },
	{ 11,	32,	2,	0xc00001ffc00001ffULL },
	{ 43,	64,	2,	0xc00001ffffffffffULL },
	{ 12,	32,	2,	0xc00003ffc00003ffULL },
	{ 44,	64,	2,	0xc00003ffffffffffULL },
	{ 13,	32,	2,	0xc00007ffc00007ffULL },
	{ 45,	64,	2,	0xc00007ffffffffffULL },
	{ 14,	32,	2,	0xc0000fffc0000fffULL },
	{ 46,	64,	2,	0xc0000fffffffffffULL },
	{ 15,	32,	2,	0xc0001fffc0001fffULL },
	{ 47,	64,	2,	0xc0001fffffffffffULL },
	{ 16,	32,	2,	0xc0003fffc0003fffULL },
	{ 48,	64,	2,	0xc0003fffffffffffULL },
	{ 17,	32,	2,	0xc0007fffc0007fffULL },
	{ 49,	64,	2,	0xc0007fffffffffffULL },
	{ 2,	16,	2,	0xc000c000c000c000ULL },
	{ 18,	32,	2,	0xc000ffffc000ffffULL },
	{ 50,	64,	2,	0xc000ffffffffffffULL },
	{ 3,	16,	2,	0xc001c001c001c001ULL },
	{ 19,	32,	2,	0xc001ffffc001ffffULL },
	{ 51,	64,	2,	0xc001ffffffffffffULL },
	{ 4,	16,	2,	0xc003c003c003c003ULL },
	{ 20,	32,	2,	0xc003ffffc003ffffULL },
	{ 52,	64,	2,	0xc003ffffffffffffULL },
	{ 5,	16,	2,	0xc007c007c007c007ULL },
	{ 21,	32,	2,	0xc007ffffc007ffffULL },
	{ 53,	64,	2,	0xc007ffffffffffffULL },
	{ 6,	16,	2,	0xc00fc00fc00fc00fULL },
	{ 22,	32,	2,	0xc00fffffc00fffffULL },
	{ 54,	64,	2,	0xc00fffffffffffffULL },
	{ 7,	16,	2,	0xc01fc01fc01fc01fULL },
	{ 23,	32,	2,	0xc01fffffc01fffffULL },
	{ 55,	64,	2,	0xc01fffffffffffffULL },
	{ 8,	16,	2,	0xc03fc03fc03fc03fULL },
	{ 24,	32,	2,	0xc03fffffc03fffffULL },
	{ 56,	64,	2,	0xc03fffffffffffffULL },
	{ 9,	16,	2,	0xc07fc07fc07fc07fULL },
	{ 25,	32,	2,	0xc07fffffc07fffffULL },
	{ 57,	64,	2,	0xc07fffffffffffffULL },
	{ 2,	8,	2,	0xc0c0c0c0c0c0c0c0ULL },
	{ 10,	16,	2,	0xc0ffc0ffc0ffc0ffULL },
	{ 26,	32,	2,	0xc0ffffffc0ffffffULL },
	{ 58,	64,	2,	0xc0ffffffffffffffULL },
	{ 3,	8,	2,	0xc1c1c1c1c1c1c1c1ULL },
	{ 11,	16,	2,	0xc1ffc1ffc1ffc1ffULL },
	{ 27,	32,	2,	0xc1ffffffc1ffffffULL },
	{ 59,	64,	2,	0xc1ffffffffffffffULL },
	{ 4,	8,	2,	0xc3c3c3c3c3c3c3c3ULL },
	{ 12,	16,	2,	0xc3ffc3ffc3ffc3ffULL },
	{ 28,	32,	2,	0xc3ffffffc3ffffffULL },
	{ 60,	64,	2,	0xc3ffffffffffffffULL },
	{ 5,	8,	2,	0xc7c7c7c7c7c7c7c7ULL },
	{ 13,	16,	2,	0xc7ffc7ffc7ffc7ffULL },
	{ 29,	32,	2,	0xc7ffffffc7ffffffULL },
	{ 61,	64,	2,	0xc7ffffffffffffffULL },
	{ 2,	4,	2,	0xccccccccccccccccULL },
	{ 6,	8,	2,	0xcfcfcfcfcfcfcfcfULL },
	{ 14,	16,	2,	0xcfffcfffcfffcfffULL },
	{ 30,	32,	2,	0xcfffffffcfffffffULL },
	{ 62,	64,	2,	0xcfffffffffffffffULL },
	{ 3,	4,	2,	0xddddddddddddddddULL },
	{ 7,	8,	2,	0xdfdfdfdfdfdfdfdfULL },
	{ 15,	16,	2,	0xdfffdfffdfffdfffULL },
	{ 31,	32,	2,	0xdfffffffdfffffffULL },
	{ 63,	64,	2,	0xdfffffffffffffffULL },
	{ 3,	64,	3,	0xe000000000000000ULL },
	{ 4,	64,	3,	0xe000000000000001ULL },
	{ 5,	64,	3,	0xe000000000000003ULL },
	{ 6,	64,	3,	0xe000000000000007ULL },
	{ 7,	64,	3,	0xe00000000000000fULL },
	{ 8,	64,	3,	0xe00000000000001fULL },
	{ 9,	64,	3,	0xe00000000000003fULL },
	{ 10,	64,	3,	0xe00000000000007fULL },
	{ 11,	64,	3,	0xe0000000000000ffULL },
	{ 12,	64,	3,	0xe0000000000001ffULL },
	{ 13,	64,	3,	0xe0000000000003ffULL },
	{ 14,	64,	3,	0xe0000000000007ffULL },
	{ 15,	64,	3,	0xe000000000000fffULL },
	{ 16,	64,	3,	0xe000000000001fffULL },
	{ 17,	64,	3,	0xe000000000003fffULL },
	{ 18,	64,	3,	0xe000000000007fffULL },
	{ 19,	64,	3,	0xe00000000000ffffULL },
	{ 20,	64,	3,	0xe00000000001ffffULL },
	{ 21,	64,	3,	0xe00000000003ffffULL },
	{ 22,	64,	3,	0xe00000000007ffffULL },
	{ 23,	64,	3,	0xe0000000000fffffULL },
	{ 24,	64,	3,	0xe0000000001fffffULL },
	{ 25,	64,	3,	0xe0000000003fffffULL },
	{ 26,	64,	3,	0xe0000000007fffffULL },
	{ 27,	64,	3,	0xe000000000ffffffULL },
	{ 28,	64,	3,	0xe000000001ffffffULL },
	{ 29,	64,	3,	0xe000000003ffffffULL },
	{ 30,	64,	3,	0xe000000007ffffffULL },
	{ 31,	64,	3,	0xe00000000fffffffULL },
	{ 32,	64,	3,	0xe00000001fffffffULL },
	{ 33,	64,	3,	0xe00000003fffffffULL },
	{ 34,	64,	3,	0xe00000007fffffffULL },
	{ 3,	32,	3,	0xe0000000e0000000ULL },
	{ 35,	64,	3,	0xe0000000ffffffffULL },
	{ 4,	32,	3,	0xe0000001e0000001ULL },
	{ 36,	64,	3,	0xe0000001ffffffffULL },
	{ 5,	32,	3,	0xe0000003e0000003ULL },
	{ 37,	64,	3,	0xe0000003ffffffffULL },
	{ 6,	32,	3,	0xe0000007e0000007ULL },
	{ 38,	64,	3,	0xe0000007ffffffffULL },
	{ 7,	32,	3,	0xe000000fe000000fULL },
	{ 39,	64,	3,	0xe000000fffffffffULL },
	{ 8,	32,	3,	0xe000001fe000001fULL },
	{ 40,	64,	3,	0xe000001fffffffffULL },
	{ 9,	32,	3,	0xe000003fe000003fULL },
	{ 41,	64,	3,	0xe000003fffffffffULL },
	{ 10,	32,	3,	0xe000007fe000007fULL },
	{ 42,	64,	3,	0xe000007fffffffffULL },
	{ 11,	32,	3,	0xe00000ffe00000ffULL },
	{ 43,	64,	3,	0xe00000ffffffffffULL },
	{ 12,	32,	3,	0xe00001ffe00001ffULL },
	{ 44,	64,	3,	0xe00001ffffffffffULL },
	{ 13,	32,	3,	0xe00003ffe00003ffULL },
	{ 45,	64,	3,	0xe00003ffffffffffULL },
	{ 14,	32,	3,	0xe00007ffe00007ffULL },
	{ 46,	64,	3,	0xe00007ffffffffffULL },
	{ 15,	32,	3,	0xe0000fffe0000fffULL },
	{ 47,	64,	3,	0xe0000fffffffffffULL },
	{ 16,	32,	3,	0xe0001fffe0001fffULL },
	{ 48,	64,	3,	0xe0001fffffffffffULL },
	{ 17,	32,	3,	0xe0003fffe0003fffULL },
	{ 49,	64,	3,	0xe0003fffffffffffULL },
	{ 18,	32,	3,	0xe0007fffe0007fffULL },
	{ 50,	64,	3,	0xe0007fffffffffffULL },
	{ 3,	16,	3,	0xe000e000e000e000ULL },
	{ 19,	32,	3,	0xe000ffffe000ffffULL },
	{ 51,	64,	3,	0xe000ffffffffffffULL },
	{ 4,	16,	3,	0xe001e001e001e001ULL },
	{ 20,	32,	3,	0xe001ffffe001ffffULL },
	{ 52,	64,	3,	0xe001ffffffffffffULL },
	{ 5,	16,	3,	0xe003e003e003e003ULL },
	{ 21,	32,	3,	0xe003ffffe003ffffULL },
	{ 53,	64,	3,	0xe003ffffffffffffULL },
	{ 6,	16,	3,	0xe007e007e007e007ULL },
	{ 22,	32,	3,	0xe007ffffe007ffffULL },
	{ 54,	64,	3,	0xe007ffffffffffffULL },
	{ 7,	16,	3,	0xe00fe00fe00fe00fULL },
	{ 23,	32,	3,	0xe00fffffe00fffffULL },
	{ 55,	64,	3,	0xe00fffffffffffffULL },
	{ 8,	16,	3,	0xe01fe01fe01fe01fULL },
	{ 24,	32,	3,	0xe01fffffe01fffffULL },
	{ 56,	64,	3,	0xe01fffffffffffffULL },
	{ 9,	16,	3,	0xe03fe03fe03fe03fULL },
	{ 25,	32,	3,	0xe03fffffe03fffffULL },
	{ 57,	64,	3,	0xe03fffffffffffffULL },
	{ 10,	16,	3,	0xe07fe07fe07fe07fULL },
	{ 26,	32,	3,	0xe07fffffe07fffffULL },
	{ 58,	64,	3,	0xe07fffffffffffffULL },
	{ 3,	8,	3,	0xe0e0e0e0e0e0e0e0ULL },
	{ 11,	16,	3,	0xe0ffe0ffe0ffe0ffULL },
	{ 27,	32,	3,	0xe0ffffffe0ffffffULL },
	{ 59,	64,	3,	0xe0ffffffffffffffULL },
	{ 4,	8,	3,	0xe1e1e1e1e1e1e1e1ULL },
	{ 12,	16,	3,	0xe1ffe1ffe1ffe1ffULL },
	{ 28,	32,	3,	0xe1ffffffe1ffffffULL },
	{ 60,	64,	3,	0xe1ffffffffffffffULL },
	{ 5,	8,	3,	0xe3e3e3e3e3e3e3e3ULL },
	{ 13,	16,	3,	0xe3ffe3ffe3ffe3ffULL },
	{ 29,	32,	3,	0xe3ffffffe3ffffffULL },
	{ 61,	64,	3,	0xe3ffffffffffffffULL },
	{ 6,	8,	3,	0xe7e7e7e7e7e7e7e7ULL },
	{ 14,	16,	3,	0xe7ffe7ffe7ffe7ffULL },
	{ 30,	32,	3,	0xe7ffffffe7ffffffULL },
	{ 62,	64,	3,	0xe7ffffffffffffffULL },
	{ 3,	4,	3,	0xeeeeeeeeeeeeeeeeULL },
	{ 7,	8,	3,	0xefefefefefefefefULL },
	{ 15,	16,	3,	0xefffefffefffefffULL },
	{ 31,	32,	3,	0xefffffffefffffffULL },
	{ 63,	64,	3,	0xefffffffffffffffULL },
	{ 4,	64,	4,	0xf000000000000000ULL },
	{ 5,	64,	4,	0xf000000000000001ULL },
	{ 6,	64,	4,	0xf000000000000003ULL },
	{ 7,	64,	4,	0xf000000000000007ULL },
	{ 8,	64,	4,	0xf00000000000000fULL },
	{ 9,	64,	4,	0xf00000000000001fULL },
	{ 10,	64,	4,	0xf00000000000003fULL },
	{ 11,	64,	4,	0xf00000000000007fULL },
	{ 12,	64,	4,	0xf0000000000000ffULL },
	{ 13,	64,	4,	0xf0000000000001ffULL },
	{ 14,	64,	4,	0xf0000000000003ffULL },
	{ 15,	64,	4,	0xf0000000000007ffULL },
	{ 16,	64,	4,	0xf000000000000fffULL },
	{ 17,	64,	4,	0xf000000000001fffULL },
	{ 18,	64,	4,	0xf000000000003fffULL },
	{ 19,	64,	4,	0xf000000000007fffULL },
	{ 20,	64,	4,	0xf00000000000ffffULL },
	{ 21,	64,	4,	0xf00000000001ffffULL },
	{ 22,	64,	4,	0xf00000000003ffffULL },
	{ 23,	64,	4,	0xf00000000007ffffULL },
	{ 24,	64,	4,	0xf0000000000fffffULL },
	{ 25,	64,	4,	0xf0000000001fffffULL },
	{ 26,	64,	4,	0xf0000000003fffffULL },
	{ 27,	64,	4,	0xf0000000007fffffULL },
	{ 28,	64,	4,	0xf000000000ffffffULL },
	{ 29,	64,	4,	0xf000000001ffffffULL },
	{ 30,	64,	4,	0xf000000003ffffffULL },
	{ 31,	64,	4,	0xf000000007ffffffULL },
	{ 32,	64,	4,	0xf00000000fffffffULL },
	{ 33,	64,	4,	0xf00000001fffffffULL },
	{ 34,	64,	4,	0xf00000003fffffffULL },
	{ 35,	64,	4,	0xf00000007fffffffULL },
	{ 4,	32,	4,	0xf0000000f0000000ULL },
	{ 36,	64,	4,	0xf0000000ffffffffULL },
	{ 5,	32,	4,	0xf0000001f0000001ULL },
	{ 37,	64,	4,	0xf0000001ffffffffULL },
	{ 6,	32,	4,	0xf0000003f0000003ULL },
	{ 38,	64,	4,	0xf0000003ffffffffULL },
	{ 7,	32,	4,	0xf0000007f0000007ULL },
	{ 39,	64,	4,	0xf0000007ffffffffULL },
	{ 8,	32,	4,	0xf000000ff000000fULL },
	{ 40,	64,	4,	0xf000000fffffffffULL },
	{ 9,	32,	4,	0xf000001ff000001fULL },
	{ 41,	64,	4,	0xf000001fffffffffULL },
	{ 10,	32,	4,	0xf000003ff000003fULL },
	{ 42,	64,	4,	0xf000003fffffffffULL },
	{ 11,	32,	4,	0xf000007ff000007fULL },
	{ 43,	64,	4,	0xf000007fffffffffULL },
	{ 12,	32,	4,	0xf00000fff00000ffULL },
	{ 44,	64,	4,	0xf00000ffffffffffULL },
	{ 13,	32,	4,	0xf00001fff00001ffULL },
	{ 45,	64,	4,	0xf00001ffffffffffULL },
	{ 14,	32,	4,	0xf00003fff00003ffULL },
	{ 46,	64,	4,	0xf00003ffffffffffULL },
	{ 15,	32,	4,	0xf00007fff00007ffULL },
	{ 47,	64,	4,	0xf00007ffffffffffULL },
	{ 16,	32,	4,	0xf0000ffff0000fffULL },
	{ 48,	64,	4,	0xf0000fffffffffffULL },
	{ 17,	32,	4,	0xf0001ffff0001fffULL },
	{ 49,	64,	4,	0xf0001fffffffffffULL },
	{ 18,	32,	4,	0xf0003ffff0003fffULL },
	{ 50,	64,	4,	0xf0003fffffffffffULL },
	{ 19,	32,	4,	0xf0007ffff0007fffULL },
	{ 51,	64,	4,	0xf0007fffffffffffULL },
	{ 4,	16,	4,	0xf000f000f000f000ULL },
	{ 20,	32,	4,	0xf000fffff000ffffULL },
	{ 52,	64,	4,	0xf000ffffffffffffULL },
	{ 5,	16,	4,	0xf001f001f001f001ULL },
	{ 21,	32,	4,	0xf001fffff001ffffULL },
	{ 53,	64,	4,	0xf001ffffffffffffULL },
	{ 6,	16,	4,	0xf003f003f003f003ULL },
	{ 22,	32,	4,	0xf003fffff003ffffULL },
	{ 54,	64,	4,	0xf003ffffffffffffULL },
	{ 7,	16,	4,	0xf007f007f007f007ULL },
	{ 23,	32,	4,	0xf007fffff007ffffULL },
	{ 55,	64,	4,	0xf007ffffffffffffULL },
	{ 8,	16,	4,	0xf00ff00ff00ff00fULL },
	{ 24,	32,	4,	0xf00ffffff00fffffULL },
	{ 56,	64,	4,	0xf00fffffffffffffULL },
	{ 9,	16,	4,	0xf01ff01ff01ff01fULL },
	{ 25,	32,	4,	0xf01ffffff01fffffULL },
	{ 57,	64,	4,	0xf01fffffffffffffULL },
	{ 10,	16,	4,	0xf03ff03ff03ff03fULL },
	{ 26,	32,	4,	0xf03ffffff03fffffULL },
	{ 58,	64,	4,	0xf03fffffffffffffULL },
	{ 11,	16,	4,	0xf07ff07ff07ff07fULL },
	{ 27,	32,	4,	0xf07ffffff07fffffULL },
	{ 59,	64,	4,	0xf07fffffffffffffULL },
	{ 4,	8,	4,	0xf0f0f0f0f0f0f0f0ULL },
	{ 12,	16,	4,	0xf0fff0fff0fff0ffULL },
	{ 28,	32,	4,	0xf0fffffff0ffffffULL },
	{ 60,	64,	4,	0xf0ffffffffffffffULL },
	{ 5,	8,	4,	0xf1f1f1f1f1f1f1f1ULL },
	{ 13,	16,	4,	0xf1fff1fff1fff1ffULL },
	{ 29,	32,	4,	0xf1fffffff1ffffffULL },
	{ 61,	64,	4,	0xf1ffffffffffffffULL },
	{ 6,	8,	4,	0xf3f3f3f3f3f3f3f3ULL },
	{ 14,	16,	4,	0xf3fff3fff3fff3ffULL },
	{ 30,	32,	4,	0xf3fffffff3ffffffULL },
	{ 62,	64,	4,	0xf3ffffffffffffffULL },
	{ 7,	8,	4,	0xf7f7f7f7f7f7f7f7ULL },
	{ 15,	16,	4,	0xf7fff7fff7fff7ffULL },
	{ 31,	32,	4,	0xf7fffffff7ffffffULL },
	{ 63,	64,	4,	0xf7ffffffffffffffULL },
	{ 5,	64,	5,	0xf800000000000000ULL },
	{ 6,	64,	5,	0xf800000000000001ULL },
	{ 7,	64,	5,	0xf800000000000003ULL },
	{ 8,	64,	5,	0xf800000000000007ULL },
	{ 9,	64,	5,	0xf80000000000000fULL },
	{ 10,	64,	5,	0xf80000000000001fULL },
	{ 11,	64,	5,	0xf80000000000003fULL },
	{ 12,	64,	5,	0xf80000000000007fULL },
	{ 13,	64,	5,	0xf8000000000000ffULL },
	{ 14,	64,	5,	0xf8000000000001ffULL },
	{ 15,	64,	5,	0xf8000000000003ffULL },
	{ 16,	64,	5,	0xf8000000000007ffULL },
	{ 17,	64,	5,	0xf800000000000fffULL },
	{ 18,	64,	5,	0xf800000000001fffULL },
	{ 19,	64,	5,	0xf800000000003fffULL },
	{ 20,	64,	5,	0xf800000000007fffULL },
	{ 21,	64,	5,	0xf80000000000ffffULL },
	{ 22,	64,	5,	0xf80000000001ffffULL },
	{ 23,	64,	5,	0xf80000000003ffffULL },
	{ 24,	64,	5,	0xf80000000007ffffULL },
	{ 25,	64,	5,	0xf8000000000fffffULL },
	{ 26,	64,	5,	0xf8000000001fffffULL },
	{ 27,	64,	5,	0xf8000000003fffffULL },
	{ 28,	64,	5,	0xf8000000007fffffULL },
	{ 29,	64,	5,	0xf800000000ffffffULL },
	{ 30,	64,	5,	0xf800000001ffffffULL },
	{ 31,	64,	5,	0xf800000003ffffffULL },
	{ 32,	64,	5,	0xf800000007ffffffULL },
	{ 33,	64,	5,	0xf80000000fffffffULL },
	{ 34,	64,	5,	0xf80000001fffffffULL },
	{ 35,	64,	5,	0xf80000003fffffffULL },
	{ 36,	64,	5,	0xf80000007fffffffULL },
	{ 5,	32,	5,	0xf8000000f8000000ULL },
	{ 37,	64,	5,	0xf8000000ffffffffULL },
	{ 6,	32,	5,	0xf8000001f8000001ULL },
	{ 38,	64,	5,	0xf8000001ffffffffULL },
	{ 7,	32,	5,	0xf8000003f8000003ULL },
	{ 39,	64,	5,	0xf8000003ffffffffULL },
	{ 8,	32,	5,	0xf8000007f8000007ULL },
	{ 40,	64,	5,	0xf8000007ffffffffULL },
	{ 9,	32,	5,	0xf800000ff800000fULL },
	{ 41,	64,	5,	0xf800000fffffffffULL },
	{ 10,	32,	5,	0xf800001ff800001fULL },
	{ 42,	64,	5,	0xf800001fffffffffULL },
	{ 11,	32,	5,	0xf800003ff800003fULL },
	{ 43,	64,	5,	0xf800003fffffffffULL },
	{ 12,	32,	5,	0xf800007ff800007fULL },
	{ 44,	64,	5,	0xf800007fffffffffULL },
	{ 13,	32,	5,	0xf80000fff80000ffULL },
	{ 45,	64,	5,	0xf80000ffffffffffULL },
	{ 14,	32,	5,	0xf80001fff80001ffULL },
	{ 46,	64,	5,	0xf80001ffffffffffULL },
	{ 15,	32,	5,	0xf80003fff80003ffULL },
	{ 47,	64,	5,	0xf80003ffffffffffULL },
	{ 16,	32,	5,	0xf80007fff80007ffULL },
	{ 48,	64,	5,	0xf80007ffffffffffULL },
	{ 17,	32,	5,	0xf8000ffff8000fffULL },
	{ 49,	64,	5,	0xf8000fffffffffffULL },
	{ 18,	32,	5,	0xf8001ffff8001fffULL },
	{ 50,	64,	5,	0xf8001fffffffffffULL },
	{ 19,	32,	5,	0xf8003ffff8003fffULL },
	{ 51,	64,	5,	0xf8003fffffffffffULL },
	{ 20,	32,	5,	0xf8007ffff8007fffULL },
	{ 52,	64,	5,	0xf8007fffffffffffULL },
	{ 5,	16,	5,	0xf800f800f800f800ULL },
	{ 21,	32,	5,	0xf800fffff800ffffULL },
	{ 53,	64,	5,	0xf800ffffffffffffULL },
	{ 6,	16,	5,	0xf801f801f801f801ULL },
	{ 22,	32,	5,	0xf801fffff801ffffULL },
	{ 54,	64,	5,	0xf801ffffffffffffULL },
	{ 7,	16,	5,	0xf803f803f803f803ULL },
	{ 23,	32,	5,	0xf803fffff803ffffULL },
	{ 55,	64,	5,	0xf803ffffffffffffULL },
	{ 8,	16,	5,	0xf807f807f807f807ULL },
	{ 24,	32,	5,	0xf807fffff807ffffULL },
	{ 56,	64,	5,	0xf807ffffffffffffULL },
	{ 9,	16,	5,	0xf80ff80ff80ff80fULL },
	{ 25,	32,	5,	0xf80ffffff80fffffULL },
	{ 57,	64,	5,	0xf80fffffffffffffULL },
	{ 10,	16,	5,	0xf81ff81ff81ff81fULL },
	{ 26,	32,	5,	0xf81ffffff81fffffULL },
	{ 58,	64,	5,	0xf81fffffffffffffULL },
	{ 11,	16,	5,	0xf83ff83ff83ff83fULL },
	{ 27,	32,	5,	0xf83ffffff83fffffULL },
	{ 59,	64,	5,	0xf83fffffffffffffULL },
	{ 12,	16,	5,	0xf87ff87ff87ff87fULL },
	{ 28,	32,	5,	0xf87ffffff87fffffULL },
	{ 60,	64,	5,	0xf87fffffffffffffULL },
	{ 5,	8,	5,	0xf8f8f8f8f8f8f8f8ULL },
	{ 13,	16,	5,	0xf8fff8fff8fff8ffULL },
	{ 29,	32,	5,	0xf8fffffff8ffffffULL },
	{ 61,	64,	5,	0xf8ffffffffffffffULL },
	{ 6,	8,	5,	0xf9f9f9f9f9f9f9f9ULL },
	{ 14,	16,	5,	0xf9fff9fff9fff9ffULL },
	{ 30,	32,	5,	0xf9fffffff9ffffffULL },
	{ 62,	64,	5,	0xf9ffffffffffffffULL },
	{ 7,	8,	5,	0xfbfbfbfbfbfbfbfbULL },
	{ 15,	16,	5,	0xfbfffbfffbfffbffULL },
	{ 31,	32,	5,	0xfbfffffffbffffffULL },
	{ 63,	64,	5,	0xfbffffffffffffffULL },
	{ 6,	64,	6,	0xfc00000000000000ULL },
	{ 7,	64,	6,	0xfc00000000000001ULL },
	{ 8,	64,	6,	0xfc00000000000003ULL },
	{ 9,	64,	6,	0xfc00000000000007ULL },
	{ 10,	64,	6,	0xfc0000000000000fULL },
	{ 11,	64,	6,	0xfc0000000000001fULL },
	{ 12,	64,	6,	0xfc0000000000003fULL },
	{ 13,	64,	6,	0xfc0000000000007fULL },
	{ 14,	64,	6,	0xfc000000000000ffULL },
	{ 15,	64,	6,	0xfc000000000001ffULL },
	{ 16,	64,	6,	0xfc000000000003ffULL },
	{ 17,	64,	6,	0xfc000000000007ffULL },
	{ 18,	64,	6,	0xfc00000000000fffULL },
	{ 19,	64,	6,	0xfc00000000001fffULL },
	{ 20,	64,	6,	0xfc00000000003fffULL },
	{ 21,	64,	6,	0xfc00000000007fffULL },
	{ 22,	64,	6,	0xfc0000000000ffffULL },
	{ 23,	64,	6,	0xfc0000000001ffffULL },
	{ 24,	64,	6,	0xfc0000000003ffffULL },
	{ 25,	64,	6,	0xfc0000000007ffffULL },
	{ 26,	64,	6,	0xfc000000000fffffULL },
	{ 27,	64,	6,	0xfc000000001fffffULL },
	{ 28,	64,	6,	0xfc000000003fffffULL },
	{ 29,	64,	6,	0xfc000000007fffffULL },
	{ 30,	64,	6,	0xfc00000000ffffffULL },
	{ 31,	64,	6,	0xfc00000001ffffffULL },
	{ 32,	64,	6,	0xfc00000003ffffffULL },
	{ 33,	64,	6,	0xfc00000007ffffffULL },
	{ 34,	64,	6,	0xfc0000000fffffffULL },
	{ 35,	64,	6,	0xfc0000001fffffffULL },
	{ 36,	64,	6,	0xfc0000003fffffffULL },
	{ 37,	64,	6,	0xfc0000007fffffffULL },
	{ 6,	32,	6,	0xfc000000fc000000ULL },
	{ 38,	64,	6,	0xfc000000ffffffffULL },
	{ 7,	32,	6,	0xfc000001fc000001ULL },
	{ 39,	64,	6,	0xfc000001ffffffffULL },
	{ 8,	32,	6,	0xfc000003fc000003ULL },
	{ 40,	64,	6,	0xfc000003ffffffffULL },
	{ 9,	32,	6,	0xfc000007fc000007ULL },
	{ 41,	64,	6,	0xfc000007ffffffffULL },
	{ 10,	32,	6,	0xfc00000ffc00000fULL },
	{ 42,	64,	6,	0xfc00000fffffffffULL },
	{ 11,	32,	6,	0xfc00001ffc00001fULL },
	{ 43,	64,	6,	0xfc00001fffffffffULL },
	{ 12,	32,	6,	0xfc00003ffc00003fULL },
	{ 44,	64,	6,	0xfc00003fffffffffULL },
	{ 13,	32,	6,	0xfc00007ffc00007fULL },
	{ 45,	64,	6,	0xfc00007fffffffffULL },
	{ 14,	32,	6,	0xfc0000fffc0000ffULL },
	{ 46,	64,	6,	0xfc0000ffffffffffULL },
	{ 15,	32,	6,	0xfc0001fffc0001ffULL },
	{ 47,	64,	6,	0xfc0001ffffffffffULL },
	{ 16,	32,	6,	0xfc0003fffc0003ffULL },
	{ 48,	64,	6,	0xfc0003ffffffffffULL },
	{ 17,	32,	6,	0xfc0007fffc0007ffULL },
	{ 49,	64,	6,	0xfc0007ffffffffffULL },
	{ 18,	32,	6,	0xfc000ffffc000fffULL },
	{ 50,	64,	6,	0xfc000fffffffffffULL },
	{ 19,	32,	6,	0xfc001ffffc001fffULL },
	{ 51,	64,	6,	0xfc001fffffffffffULL },
	{ 20,	32,	6,	0xfc003ffffc003fffULL },
	{ 52,	64,	6,	0xfc003fffffffffffULL },
	{ 21,	32,	6,	0xfc007ffffc007fffULL },
	{ 53,	64,	6,	0xfc007fffffffffffULL },
	{ 6,	16,	6,	0xfc00fc00fc00fc00ULL },
	{ 22,	32,	6,	0xfc00fffffc00ffffULL },
	{ 54,	64,	6,	0xfc00ffffffffffffULL },
	{ 7,	16,	6,	0xfc01fc01fc01fc01ULL },
	{ 23,	32,	6,	0xfc01fffffc01ffffULL },
	{ 55,	64,	6,	0xfc01ffffffffffffULL },
	{ 8,	16,	6,	0xfc03fc03fc03fc03ULL },
	{ 24,	32,	6,	0xfc03fffffc03ffffULL },
	{ 56,	64,	6,	0xfc03ffffffffffffULL },
	{ 9,	16,	6,	0xfc07fc07fc07fc07ULL },
	{ 25,	32,	6,	0xfc07fffffc07ffffULL },
	{ 57,	64,	6,	0xfc07ffffffffffffULL },
	{ 10,	16,	6,	0xfc0ffc0ffc0ffc0fULL },
	{ 26,	32,	6,	0xfc0ffffffc0fffffULL },
	{ 58,	64,	6,	0xfc0fffffffffffffULL },
	{ 11,	16,	6,	0xfc1ffc1ffc1ffc1fULL },
	{ 27,	32,	6,	0xfc1ffffffc1fffffULL },
	{ 59,	64,	6,	0xfc1fffffffffffffULL },
	{ 12,	16,	6,	0xfc3ffc3ffc3ffc3fULL },
	{ 28,	32,	6,	0xfc3ffffffc3fffffULL },
	{ 60,	64,	6,	0xfc3fffffffffffffULL },
	{ 13,	16,	6,	0xfc7ffc7ffc7ffc7fULL },
	{ 29,	32,	6,	0xfc7ffffffc7fffffULL },
	{ 61,	64,	6,	0xfc7fffffffffffffULL },
	{ 6,	8,	6,	0xfcfcfcfcfcfcfcfcULL },
	{ 14,	16,	6,	0xfcfffcfffcfffcffULL },
	{ 30,	32,	6,	0xfcfffffffcffffffULL },
	{ 62,	64,	6,	0xfcffffffffffffffULL },
	{ 7,	8,	6,	0xfdfdfdfdfdfdfdfdULL },
	{ 15,	16,	6,	0xfdfffdfffdfffdffULL },
	{ 31,	32,	6,	0xfdfffffffdffffffULL },
	{ 63,	64,	6,	0xfdffffffffffffffULL },
	{ 7,	64,	7,	0xfe00000000000000ULL },
	{ 8,	64,	7,	0xfe00000000000001ULL },
	{ 9,	64,	7,	0xfe00000000000003ULL },
	{ 10,	64,	7,	0xfe00000000000007ULL },
	{ 11,	64,	7,	0xfe0000000000000fULL },
	{ 12,	64,	7,	0xfe0000000000001fULL },
	{ 13,	64,	7,	0xfe0000000000003fULL },
	{ 14,	64,	7,	0xfe0000000000007fULL },
	{ 15,	64,	7,	0xfe000000000000ffULL },
	{ 16,	64,	7,	0xfe000000000001ffULL },
	{ 17,	64,	7,	0xfe000000000003ffULL },
	{ 18,	64,	7,	0xfe000000000007ffULL },
	{ 19,	64,	7,	0xfe00000000000fffULL },
	{ 20,	64,	7,	0xfe00000000001fffULL },
	{ 21,	64,	7,	0xfe00000000003fffULL },
	{ 22,	64,	7,	0xfe00000000007fffULL },
	{ 23,	64,	7,	0xfe0000000000ffffULL },
	{ 24,	64,	7,	0xfe0000000001ffffULL },
	{ 25,	64,	7,	0xfe0000000003ffffULL },
	{ 26,	64,	7,	0xfe0000000007ffffULL },
	{ 27,	64,	7,	0xfe000000000fffffULL },
	{ 28,	64,	7,	0xfe000000001fffffULL },
	{ 29,	64,	7,	0xfe000000003fffffULL },
	{ 30,	64,	7,	0xfe000000007fffffULL },
	{ 31,	64,	7,	0xfe00000000ffffffULL },
	{ 32,	64,	7,	0xfe00000001ffffffULL },
	{ 33,	64,	7,	0xfe00000003ffffffULL },
	{ 34,	64,	7,	0xfe00000007ffffffULL },
	{ 35,	64,	7,	0xfe0000000fffffffULL },
	{ 36,	64,	7,	0xfe0000001fffffffULL },
	{ 37,	64,	7,	0xfe0000003fffffffULL },
	{ 38,	64,	7,	0xfe0000007fffffffULL },
	{ 7,	32,	7,	0xfe000000fe000000ULL },
	{ 39,	64,	7,	0xfe000000ffffffffULL },
	{ 8,	32,	7,	0xfe000001fe000001ULL },
	{ 40,	64,	7,	0xfe000001ffffffffULL },
	{ 9,	32,	7,	0xfe000003fe000003ULL },
	{ 41,	64,	7,	0xfe000003ffffffffULL },
	{ 10,	32,	7,	0xfe000007fe000007ULL },
	{ 42,	64,	7,	0xfe000007ffffffffULL },
	{ 11,	32,	7,	0xfe00000ffe00000fULL },
	{ 43,	64,	7,	0xfe00000fffffffffULL },
	{ 12,	32,	7,	0xfe00001ffe00001fULL },
	{ 44,	64,	7,	0xfe00001fffffffffULL },
	{ 13,	32,	7,	0xfe00003ffe00003fULL },
	{ 45,	64,	7,	0xfe00003fffffffffULL },
	{ 14,	32,	7,	0xfe00007ffe00007fULL },
	{ 46,	64,	7,	0xfe00007fffffffffULL },
	{ 15,	32,	7,	0xfe0000fffe0000ffULL },
	{ 47,	64,	7,	0xfe0000ffffffffffULL },
	{ 16,	32,	7,	0xfe0001fffe0001ffULL },
	{ 48,	64,	7,	0xfe0001ffffffffffULL },
	{ 17,	32,	7,	0xfe0003fffe0003ffULL },
	{ 49,	64,	7,	0xfe0003ffffffffffULL },
	{ 18,	32,	7,	0xfe0007fffe0007ffULL },
	{ 50,	64,	7,	0xfe0007ffffffffffULL },
	{ 19,	32,	7,	0xfe000ffffe000fffULL },
	{ 51,	64,	7,	0xfe000fffffffffffULL },
	{ 20,	32,	7,	0xfe001ffffe001fffULL },
	{ 52,	64,	7,	0xfe001fffffffffffULL },
	{ 21,	32,	7,	0xfe003ffffe003fffULL },
	{ 53,	64,	7,	0xfe003fffffffffffULL },
	{ 22,	32,	7,	0xfe007ffffe007fffULL },
	{ 54,	64,	7,	0xfe007fffffffffffULL },
	{ 7,	16,	7,	0xfe00fe00fe00fe00ULL },
	{ 23,	32,	7,	0xfe00fffffe00ffffULL },
	{ 55,	64,	7,	0xfe00ffffffffffffULL },
	{ 8,	16,	7,	0xfe01fe01fe01fe01ULL },
	{ 24,	32,	7,	0xfe01fffffe01ffffULL },
	{ 56,	64,	7,	0xfe01ffffffffffffULL },
	{ 9,	16,	7,	0xfe03fe03fe03fe03ULL },
	{ 25,	32,	7,	0xfe03fffffe03ffffULL },
	{ 57,	64,	7,	0xfe03ffffffffffffULL },
	{ 10,	16,	7,	0xfe07fe07fe07fe07ULL },
	{ 26,	32,	7,	0xfe07fffffe07ffffULL },
	{ 58,	64,	7,	0xfe07ffffffffffffULL },
	{ 11,	16,	7,	0xfe0ffe0ffe0ffe0fULL },
	{ 27,	32,	7,	0xfe0ffffffe0fffffULL },
	{ 59,	64,	7,	0xfe0fffffffffffffULL },
	{ 12,	16,	7,	0xfe1ffe1ffe1ffe1fULL },
	{ 28,	32,	7,	0xfe1ffffffe1fffffULL },
	{ 60,	64,	7,	0xfe1fffffffffffffULL },
	{ 13,	16,	7,	0xfe3ffe3ffe3ffe3fULL },
	{ 29,	32,	7,	0xfe3ffffffe3fffffULL },
	{ 61,	64,	7,	0xfe3fffffffffffffULL },
	{ 14,	16,	7,	0xfe7ffe7ffe7ffe7fULL },
	{ 30,	32,	7,	0xfe7ffffffe7fffffULL },
	{ 62,	64,	7,	0xfe7fffffffffffffULL },
	{ 7,	8,	7,	0xfefefefefefefefeULL },
	{ 15,	16,	7,	0xfefffefffefffeffULL },
	{ 31,	32,	7,	0xfefffffffeffffffULL },
	{ 63,	64,	7,	0xfeffffffffffffffULL },
	{ 8,	64,	8,	0xff00000000000000ULL },
	{ 9,	64,	8,	0xff00000000000001ULL },
	{ 10,	64,	8,	0xff00000000000003ULL },
	{ 11,	64,	8,	0xff00000000000007ULL },
	{ 12,	64,	8,	0xff0000000000000fULL },
	{ 13,	64,	8,	0xff0000000000001fULL },
	{ 14,	64,	8,	0xff0000000000003fULL },
	{ 15,	64,	8,	0xff0000000000007fULL },
	{ 16,	64,	8,	0xff000000000000ffULL },
	{ 17,	64,	8,	0xff000000000001ffULL },
	{ 18,	64,	8,	0xff000000000003ffULL },
	{ 19,	64,	8,	0xff000000000007ffULL },
	{ 20,	64,	8,	0xff00000000000fffULL },
	{ 21,	64,	8,	0xff00000000001fffULL },
	{ 22,	64,	8,	0xff00000000003fffULL },
	{ 23,	64,	8,	0xff00000000007fffULL },
	{ 24,	64,	8,	0xff0000000000ffffULL },
	{ 25,	64,	8,	0xff0000000001ffffULL },
	{ 26,	64,	8,	0xff0000000003ffffULL },
	{ 27,	64,	8,	0xff0000000007ffffULL },
	{ 28,	64,	8,	0xff000000000fffffULL },
	{ 29,	64,	8,	0xff000000001fffffULL },
	{ 30,	64,	8,	0xff000000003fffffULL },
	{ 31,	64,	8,	0xff000000007fffffULL },
	{ 32,	64,	8,	0xff00000000ffffffULL },
	{ 33,	64,	8,	0xff00000001ffffffULL },
	{ 34,	64,	8,	0xff00000003ffffffULL },
	{ 35,	64,	8,	0xff00000007ffffffULL },
	{ 36,	64,	8,	0xff0000000fffffffULL },
	{ 37,	64,	8,	0xff0000001fffffffULL },
	{ 38,	64,	8,	0xff0000003fffffffULL },
	{ 39,	64,	8,	0xff0000007fffffffULL },
	{ 8,	32,	8,	0xff000000ff000000ULL },
	{ 40,	64,	8,	0xff000000ffffffffULL },
	{ 9,	32,	8,	0xff000001ff000001ULL },
	{ 41,	64,	8,	0xff000001ffffffffULL },
	{ 10,	32,	8,	0xff000003ff000003ULL },
	{ 42,	64,	8,	0xff000003ffffffffULL },
	{ 11,	32,	8,	0xff000007ff000007ULL },
	{ 43,	64,	8,	0xff000007ffffffffULL },
	{ 12,	32,	8,	0xff00000fff00000fULL },
	{ 44,	64,	8,	0xff00000fffffffffULL },
	{ 13,	32,	8,	0xff00001fff00001fULL },
	{ 45,	64,	8,	0xff00001fffffffffULL },
	{ 14,	32,	8,	0xff00003fff00003fULL },
	{ 46,	64,	8,	0xff00003fffffffffULL },
	{ 15,	32,	8,	0xff00007fff00007fULL },
	{ 47,	64,	8,	0xff00007fffffffffULL },
	{ 16,	32,	8,	0xff0000ffff0000ffULL },
	{ 48,	64,	8,	0xff0000ffffffffffULL },
	{ 17,	32,	8,	0xff0001ffff0001ffULL },
	{ 49,	64,	8,	0xff0001ffffffffffULL },
	{ 18,	32,	8,	0xff0003ffff0003ffULL },
	{ 50,	64,	8,	0xff0003ffffffffffULL },
	{ 19,	32,	8,	0xff0007ffff0007ffULL },
	{ 51,	64,	8,	0xff0007ffffffffffULL },
	{ 20,	32,	8,	0xff000fffff000fffULL },
	{ 52,	64,	8,	0xff000fffffffffffULL },
	{ 21,	32,	8,	0xff001fffff001fffULL },
	{ 53,	64,	8,	0xff001fffffffffffULL },
	{ 22,	32,	8,	0xff003fffff003fffULL },
	{ 54,	64,	8,	0xff003fffffffffffULL },
	{ 23,	32,	8,	0xff007fffff007fffULL },
	{ 55,	64,	8,	0xff007fffffffffffULL },
	{ 8,	16,	8,	0xff00ff00ff00ff00ULL },
	{ 24,	32,	8,	0xff00ffffff00ffffULL },
	{ 56,	64,	8,	0xff00ffffffffffffULL },
	{ 9,	16,	8,	0xff01ff01ff01ff01ULL },
	{ 25,	32,	8,	0xff01ffffff01ffffULL },
	{ 57,	64,	8,	0xff01ffffffffffffULL },
	{ 10,	16,	8,	0xff03ff03ff03ff03ULL },
	{ 26,	32,	8,	0xff03ffffff03ffffULL },
	{ 58,	64,	8,	0xff03ffffffffffffULL },
	{ 11,	16,	8,	0xff07ff07ff07ff07ULL },
	{ 27,	32,	8,	0xff07ffffff07ffffULL },
	{ 59,	64,	8,	0xff07ffffffffffffULL },
	{ 12,	16,	8,	0xff0fff0fff0fff0fULL },
	{ 28,	32,	8,	0xff0fffffff0fffffULL },
	{ 60,	64,	8,	0xff0fffffffffffffULL },
	{ 13,	16,	8,	0xff1fff1fff1fff1fULL },
	{ 29,	32,	8,	0xff1fffffff1fffffULL },
	{ 61,	64,	8,	0xff1fffffffffffffULL },
	{ 14,	16,	8,	0xff3fff3fff3fff3fULL },
	{ 30,	32,	8,	0xff3fffffff3fffffULL },
	{ 62,	64,	8,	0xff3fffffffffffffULL },
	{ 15,	16,	8,	0xff7fff7fff7fff7fULL },
	{ 31,	32,	8,	0xff7fffffff7fffffULL },
	{ 63,	64,	8,	0xff7fffffffffffffULL },
	{ 9,	64,	9,	0xff80000000000000ULL },
	{ 10,	64,	9,	0xff80000000000001ULL },
	{ 11,	64,	9,	0xff80000000000003ULL },
	{ 12,	64,	9,	0xff80000000000007ULL },
	{ 13,	64,	9,	0xff8000000000000fULL },
	{ 14,	64,	9,	0xff8000000000001fULL },
	{ 15,	64,	9,	0xff8000000000003fULL },
	{ 16,	64,	9,	0xff8000000000007fULL },
	{ 17,	64,	9,	0xff800000000000ffULL },
	{ 18,	64,	9,	0xff800000000001ffULL },
	{ 19,	64,	9,	0xff800000000003ffULL },
	{ 20,	64,	9,	0xff800000000007ffULL },
	{ 21,	64,	9,	0xff80000000000fffULL },
	{ 22,	64,	9,	0xff80000000001fffULL },
	{ 23,	64,	9,	0xff80000000003fffULL },
	{ 24,	64,	9,	0xff80000000007fffULL },
	{ 25,	64,	9,	0xff8000000000ffffULL },
	{ 26,	64,	9,	0xff8000000001ffffULL },
	{ 27,	64,	9,	0xff8000000003ffffULL },
	{ 28,	64,	9,	0xff8000000007ffffULL },
	{ 29,	64,	9,	0xff800000000fffffULL },
	{ 30,	64,	9,	0xff800000001fffffULL },
	{ 31,	64,	9,	0xff800000003fffffULL },
	{ 32,	64,	9,	0xff800000007fffffULL },
	{ 33,	64,	9,	0xff80000000ffffffULL },
	{ 34,	64,	9,	0xff80000001ffffffULL },
	{ 35,	64,	9,	0xff80000003ffffffULL },
	{ 36,	64,	9,	0xff80000007ffffffULL },
	{ 37,	64,	9,	0xff8000000fffffffULL },
	{ 38,	64,	9,	0xff8000001fffffffULL },
	{ 39,	64,	9,	0xff8000003fffffffULL },
	{ 40,	64,	9,	0xff8000007fffffffULL },
	{ 9,	32,	9,	0xff800000ff800000ULL },
	{ 41,	64,	9,	0xff800000ffffffffULL },
	{ 10,	32,	9,	0xff800001ff800001ULL },
	{ 42,	64,	9,	0xff800001ffffffffULL },
	{ 11,	32,	9,	0xff800003ff800003ULL },
	{ 43,	64,	9,	0xff800003ffffffffULL },
	{ 12,	32,	9,	0xff800007ff800007ULL },
	{ 44,	64,	9,	0xff800007ffffffffULL },
	{ 13,	32,	9,	0xff80000fff80000fULL },
	{ 45,	64,	9,	0xff80000fffffffffULL },
	{ 14,	32,	9,	0xff80001fff80001fULL },
	{ 46,	64,	9,	0xff80001fffffffffULL },
	{ 15,	32,	9,	0xff80003fff80003fULL },
	{ 47,	64,	9,	0xff80003fffffffffULL },
	{ 16,	32,	9,	0xff80007fff80007fULL },
	{ 48,	64,	9,	0xff80007fffffffffULL },
	{ 17,	32,	9,	0xff8000ffff8000ffULL },
	{ 49,	64,	9,	0xff8000ffffffffffULL },
	{ 18,	32,	9,	0xff8001ffff8001ffULL },
	{ 50,	64,	9,	0xff8001ffffffffffULL },
	{ 19,	32,	9,	0xff8003ffff8003ffULL },
	{ 51,	64,	9,	0xff8003ffffffffffULL },
	{ 20,	32,	9,	0xff8007ffff8007ffULL },
	{ 52,	64,	9,	0xff8007ffffffffffULL },
	{ 21,	32,	9,	0xff800fffff800fffULL },
	{ 53,	64,	9,	0xff800fffffffffffULL },
	{ 22,	32,	9,	0xff801fffff801fffULL },
	{ 54,	64,	9,	0xff801fffffffffffULL },
	{ 23,	32,	9,	0xff803fffff803fffULL },
	{ 55,	64,	9,	0xff803fffffffffffULL },
	{ 24,	32,	9,	0xff807fffff807fffULL },
	{ 56,	64,	9,	0xff807fffffffffffULL },
	{ 9,	16,	9,	0xff80ff80ff80ff80ULL },
	{ 25,	32,	9,	0xff80ffffff80ffffULL },
	{ 57,	64,	9,	0xff80ffffffffffffULL },
	{ 10,	16,	9,	0xff81ff81ff81ff81ULL },
	{ 26,	32,	9,	0xff81ffffff81ffffULL },
	{ 58,	64,	9,	0xff81ffffffffffffULL },
	{ 11,	16,	9,	0xff83ff83ff83ff83ULL },
	{ 27,	32,	9,	0xff83ffffff83ffffULL },
	{ 59,	64,	9,	0xff83ffffffffffffULL },
	{ 12,	16,	9,	0xff87ff87ff87ff87ULL },
	{ 28,	32,	9,	0xff87ffffff87ffffULL },
	{ 60,	64,	9,	0xff87ffffffffffffULL },
	{ 13,	16,	9,	0xff8fff8fff8fff8fULL },
	{ 29,	32,	9,	0xff8fffffff8fffffULL },
	{ 61,	64,	9,	0xff8fffffffffffffULL },
	{ 14,	16,	9,	0xff9fff9fff9fff9fULL },
	{ 30,	32,	9,	0xff9fffffff9fffffULL },
	{ 62,	64,	9,	0xff9fffffffffffffULL },
	{ 15,	16,	9,	0xffbfffbfffbfffbfULL },
	{ 31,	32,	9,	0xffbfffffffbfffffULL },
	{ 63,	64,	9,	0xffbfffffffffffffULL },
	{ 10,	64,	10,	0xffc0000000000000ULL },
	{ 11,	64,	10,	0xffc0000000000001ULL },
	{ 12,	64,	10,	0xffc0000000000003ULL },
	{ 13,	64,	10,	0xffc0000000000007ULL },
	{ 14,	64,	10,	0xffc000000000000fULL },
	{ 15,	64,	10,	0xffc000000000001fULL },
	{ 16,	64,	10,	0xffc000000000003fULL },
	{ 17,	64,	10,	0xffc000000000007fULL },
	{ 18,	64,	10,	0xffc00000000000ffULL },
	{ 19,	64,	10,	0xffc00000000001ffULL },
	{ 20,	64,	10,	0xffc00000000003ffULL },
	{ 21,	64,	10,	0xffc00000000007ffULL },
	{ 22,	64,	10,	0xffc0000000000fffULL },
	{ 23,	64,	10,	0xffc0000000001fffULL },
	{ 24,	64,	10,	0xffc0000000003fffULL },
	{ 25,	64,	10,	0xffc0000000007fffULL },
	{ 26,	64,	10,	0xffc000000000ffffULL },
	{ 27,	64,	10,	0xffc000000001ffffULL },
	{ 28,	64,	10,	0xffc000000003ffffULL },
	{ 29,	64,	10,	0xffc000000007ffffULL },
	{ 30,	64,	10,	0xffc00000000fffffULL },
	{ 31,	64,	10,	0xffc00000001fffffULL },
	{ 32,	64,	10,	0xffc00000003fffffULL },
	{ 33,	64,	10,	0xffc00000007fffffULL },
	{ 34,	64,	10,	0xffc0000000ffffffULL },
	{ 35,	64,	10,	0xffc0000001ffffffULL },
	{ 36,	64,	10,	0xffc0000003ffffffULL },
	{ 37,	64,	10,	0xffc0000007ffffffULL },
	{ 38,	64,	10,	0xffc000000fffffffULL },
	{ 39,	64,	10,	0xffc000001fffffffULL },
	{ 40,	64,	10,	0xffc000003fffffffULL },
	{ 41,	64,	10,	0xffc000007fffffffULL },
	{ 10,	32,	10,	0xffc00000ffc00000ULL },
	{ 42,	64,	10,	0xffc00000ffffffffULL },
	{ 11,	32,	10,	0xffc00001ffc00001ULL },
	{ 43,	64,	10,	0xffc00001ffffffffULL },
	{ 12,	32,	10,	0xffc00003ffc00003ULL },
	{ 44,	64,	10,	0xffc00003ffffffffULL },
	{ 13,	32,	10,	0xffc00007ffc00007ULL },
	{ 45,	64,	10,	0xffc00007ffffffffULL },
	{ 14,	32,	10,	0xffc0000fffc0000fULL },
	{ 46,	64,	10,	0xffc0000fffffffffULL },
	{ 15,	32,	10,	0xffc0001fffc0001fULL },
	{ 47,	64,	10,	0xffc0001fffffffffULL },
	{ 16,	32,	10,	0xffc0003fffc0003fULL },
	{ 48,	64,	10,	0xffc0003fffffffffULL },
	{ 17,	32,	10,	0xffc0007fffc0007fULL },
	{ 49,	64,	10,	0xffc0007fffffffffULL },
	{ 18,	32,	10,	0xffc000ffffc000ffULL },
	{ 50,	64,	10,	0xffc000ffffffffffULL },
	{ 19,	32,	10,	0xffc001ffffc001ffULL },
	{ 51,	64,	10,	0xffc001ffffffffffULL },
	{ 20,	32,	10,	0xffc003ffffc003ffULL },
	{ 52,	64,	10,	0xffc003ffffffffffULL },
	{ 21,	32,	10,	0xffc007ffffc007ffULL },
	{ 53,	64,	10,	0xffc007ffffffffffULL },
	{ 22,	32,	10,	0xffc00fffffc00fffULL },
	{ 54,	64,	10,	0xffc00fffffffffffULL },
	{ 23,	32,	10,	0xffc01fffffc01fffULL },
	{ 55,	64,	10,	0xffc01fffffffffffULL },
	{ 24,	32,	10,	0xffc03fffffc03fffULL },
	{ 56,	64,	10,	0xffc03fffffffffffULL },
	{ 25,	32,	10,	0xffc07fffffc07fffULL },
	{ 57,	64,	10,	0xffc07fffffffffffULL },
	{ 10,	16,	10,	0xffc0ffc0ffc0ffc0ULL },
	{ 26,	32,	10,	0xffc0ffffffc0ffffULL },
	{ 58,	64,	10,	0xffc0ffffffffffffULL },
	{ 11,	16,	10,	0xffc1ffc1ffc1ffc1ULL },
	{ 27,	32,	10,	0xffc1ffffffc1ffffULL },
	{ 59,	64,	10,	0xffc1ffffffffffffULL },
	{ 12,	16,	10,	0xffc3ffc3ffc3ffc3ULL },
	{ 28,	32,	10,	0xffc3ffffffc3ffffULL },
	{ 60,	64,	10,	0xffc3ffffffffffffULL },
	{ 13,	16,	10,	0xffc7ffc7ffc7ffc7ULL },
	{ 29,	32,	10,	0xffc7ffffffc7ffffULL },
	{ 61,	64,	10,	0xffc7ffffffffffffULL },
	{ 14,	16,	10,	0xffcfffcfffcfffcfULL },
	{ 30,	32,	10,	0xffcfffffffcfffffULL },
	{ 62,	64,	10,	0xffcfffffffffffffULL },
	{ 15,	16,	10,	0xffdfffdfffdfffdfULL },
	{ 31,	32,	10,	0xffdfffffffdfffffULL },
	{ 63,	64,	10,	0xffdfffffffffffffULL },
	{ 11,	64,	11,	0xffe0000000000000ULL },
	{ 12,	64,	11,	0xffe0000000000001ULL },
	{ 13,	64,	11,	0xffe0000000000003ULL },
	{ 14,	64,	11,	0xffe0000000000007ULL },
	{ 15,	64,	11,	0xffe000000000000fULL },
	{ 16,	64,	11,	0xffe000000000001fULL },
	{ 17,	64,	11,	0xffe000000000003fULL },
	{ 18,	64,	11,	0xffe000000000007fULL },
	{ 19,	64,	11,	0xffe00000000000ffULL },
	{ 20,	64,	11,	0xffe00000000001ffULL },
	{ 21,	64,	11,	0xffe00000000003ffULL },
	{ 22,	64,	11,	0xffe00000000007ffULL },
	{ 23,	64,	11,	0xffe0000000000fffULL },
	{ 24,	64,	11,	0xffe0000000001fffULL },
	{ 25,	64,	11,	0xffe0000000003fffULL },
	{ 26,	64,	11,	0xffe0000000007fffULL },
	{ 27,	64,	11,	0xffe000000000ffffULL },
	{ 28,	64,	11,	0xffe000000001ffffULL },
	{ 29,	64,	11,	0xffe000000003ffffULL },
	{ 30,	64,	11,	0xffe000000007ffffULL },
	{ 31,	64,	11,	0xffe00000000fffffULL },
	{ 32,	64,	11,	0xffe00000001fffffULL },
	{ 33,	64,	11,	0xffe00000003fffffULL },
	{ 34,	64,	11,	0xffe00000007fffffULL },
	{ 35,	64,	11,	0xffe0000000ffffffULL },
	{ 36,	64,	11,	0xffe0000001ffffffULL },
	{ 37,	64,	11,	0xffe0000003ffffffULL },
	{ 38,	64,	11,	0xffe0000007ffffffULL },
	{ 39,	64,	11,	0xffe000000fffffffULL },
	{ 40,	64,	11,	0xffe000001fffffffULL },
	{ 41,	64,	11,	0xffe000003fffffffULL },
	{ 42,	64,	11,	0xffe000007fffffffULL },
	{ 11,	32,	11,	0xffe00000ffe00000ULL },
	{ 43,	64,	11,	0xffe00000ffffffffULL },
	{ 12,	32,	11,	0xffe00001ffe00001ULL },
	{ 44,	64,	11,	0xffe00001ffffffffULL },
	{ 13,	32,	11,	0xffe00003ffe00003ULL },
	{ 45,	64,	11,	0xffe00003ffffffffULL },
	{ 14,	32,	11,	0xffe00007ffe00007ULL },
	{ 46,	64,	11,	0xffe00007ffffffffULL },
	{ 15,	32,	11,	0xffe0000fffe0000fULL },
	{ 47,	64,	11,	0xffe0000fffffffffULL },
	{ 16,	32,	11,	0xffe0001fffe0001fULL },
	{ 48,	64,	11,	0xffe0001fffffffffULL },
	{ 17,	32,	11,	0xffe0003fffe0003fULL },
	{ 49,	64,	11,	0xffe0003fffffffffULL },
	{ 18,	32,	11,	0xffe0007fffe0007fULL },
	{ 50,	64,	11,	0xffe0007fffffffffULL },
	{ 19,	32,	11,	0xffe000ffffe000ffULL },
	{ 51,	64,	11,	0xffe000ffffffffffULL },
	{ 20,	32,	11,	0xffe001ffffe001ffULL },
	{ 52,	64,	11,	0xffe001ffffffffffULL },
	{ 21,	32,	11,	0xffe003ffffe003ffULL },
	{ 53,	64,	11,	0xffe003ffffffffffULL },
	{ 22,	32,	11,	0xffe007ffffe007ffULL },
	{ 54,	64,	11,	0xffe007ffffffffffULL },
	{ 23,	32,	11,	0xffe00fffffe00fffULL },
	{ 55,	64,	11,	0xffe00fffffffffffULL },
	{ 24,	32,	11,	0xffe01fffffe01fffULL },
	{ 56,	64,	11,	0xffe01fffffffffffULL },
	{ 25,	32,	11,	0xffe03fffffe03fffULL },
	{ 57,	64,	11,	0xffe03fffffffffffULL },
	{ 26,	32,	11,	0xffe07fffffe07fffULL },
	{ 58,	64,	11,	0xffe07fffffffffffULL },
	{ 11,	16,	11,	0xffe0ffe0ffe0ffe0ULL },
	{ 27,	32,	11,	0xffe0ffffffe0ffffULL },
	{ 59,	64,	11,	0xffe0ffffffffffffULL },
	{ 12,	16,	11,	0xffe1ffe1ffe1ffe1ULL },
	{ 28,	32,	11,	0xffe1ffffffe1ffffULL },
	{ 60,	64,	11,	0xffe1ffffffffffffULL },
	{ 13,	16,	11,	0xffe3ffe3ffe3ffe3ULL },
	{ 29,	32,	11,	0xffe3ffffffe3ffffULL },
	{ 61,	64,	11,	0xffe3ffffffffffffULL },
	{ 14,	16,	11,	0xffe7ffe7ffe7ffe7ULL },
	{ 30,	32,	11,	0xffe7ffffffe7ffffULL },
	{ 62,	64,	11,	0xffe7ffffffffffffULL },
	{ 15,	16,	11,	0xffefffefffefffefULL },
	{ 31,	32,	11,	0xffefffffffefffffULL },
	{ 63,	64,	11,	0xffefffffffffffffULL },
	{ 12,	64,	12,	0xfff0000000000000ULL },
	{ 13,	64,	12,	0xfff0000000000001ULL },
	{ 14,	64,	12,	0xfff0000000000003ULL },
	{ 15,	64,	12,	0xfff0000000000007ULL },
	{ 16,	64,	12,	0xfff000000000000fULL },
	{ 17,	64,	12,	0xfff000000000001fULL },
	{ 18,	64,	12,	0xfff000000000003fULL },
	{ 19,	64,	12,	0xfff000000000007fULL },
	{ 20,	64,	12,	0xfff00000000000ffULL },
	{ 21,	64,	12,	0xfff00000000001ffULL },
	{ 22,	64,	12,	0xfff00000000003ffULL },
	{ 23,	64,	12,	0xfff00000000007ffULL },
	{ 24,	64,	12,	0xfff0000000000fffULL },
	{ 25,	64,	12,	0xfff0000000001fffULL },
	{ 26,	64,	12,	0xfff0000000003fffULL },
	{ 27,	64,	12,	0xfff0000000007fffULL },
	{ 28,	64,	12,	0xfff000000000ffffULL },
	{ 29,	64,	12,	0xfff000000001ffffULL },
	{ 30,	64,	12,	0xfff000000003ffffULL },
	{ 31,	64,	12,	0xfff000000007ffffULL },
	{ 32,	64,	12,	0xfff00000000fffffULL },
	{ 33,	64,	12,	0xfff00000001fffffULL },
	{ 34,	64,	12,	0xfff00000003fffffULL },
	{ 35,	64,	12,	0xfff00000007fffffULL },
	{ 36,	64,	12,	0xfff0000000ffffffULL },
	{ 37,	64,	12,	0xfff0000001ffffffULL },
	{ 38,	64,	12,	0xfff0000003ffffffULL },
	{ 39,	64,	12,	0xfff0000007ffffffULL },
	{ 40,	64,	12,	0xfff000000fffffffULL },
	{ 41,	64,	12,	0xfff000001fffffffULL },
	{ 42,	64,	12,	0xfff000003fffffffULL },
	{ 43,	64,	12,	0xfff000007fffffffULL },
	{ 12,	32,	12,	0xfff00000fff00000ULL },
	{ 44,	64,	12,	0xfff00000ffffffffULL },
	{ 13,	32,	12,	0xfff00001fff00001ULL },
	{ 45,	64,	12,	0xfff00001ffffffffULL },
	{ 14,	32,	12,	0xfff00003fff00003ULL },
	{ 46,	64,	12,	0xfff00003ffffffffULL },
	{ 15,	32,	12,	0xfff00007fff00007ULL },
	{ 47,	64,	12,	0xfff00007ffffffffULL },
	{ 16,	32,	12,	0xfff0000ffff0000fULL },
	{ 48,	64,	12,	0xfff0000fffffffffULL },
	{ 17,	32,	12,	0xfff0001ffff0001fULL },
	{ 49,	64,	12,	0xfff0001fffffffffULL },
	{ 18,	32,	12,	0xfff0003ffff0003fULL },
	{ 50,	64,	12,	0xfff0003fffffffffULL },
	{ 19,	32,	12,	0xfff0007ffff0007fULL },
	{ 51,	64,	12,	0xfff0007fffffffffULL },
	{ 20,	32,	12,	0xfff000fffff000ffULL },
	{ 52,	64,	12,	0xfff000ffffffffffULL },
	{ 21,	32,	12,	0xfff001fffff001ffULL },
	{ 53,	64,	12,	0xfff001ffffffffffULL },
	{ 22,	32,	12,	0xfff003fffff003ffULL },
	{ 54,	64,	12,	0xfff003ffffffffffULL },
	{ 23,	32,	12,	0xfff007fffff007ffULL },
	{ 55,	64,	12,	0xfff007ffffffffffULL },
	{ 24,	32,	12,	0xfff00ffffff00fffULL },
	{ 56,	64,	12,	0xfff00fffffffffffULL },
	{ 25,	32,	12,	0xfff01ffffff01fffULL },
	{ 57,	64,	12,	0xfff01fffffffffffULL },
	{ 26,	32,	12,	0xfff03ffffff03fffULL },
	{ 58,	64,	12,	0xfff03fffffffffffULL },
	{ 27,	32,	12,	0xfff07ffffff07fffULL },
	{ 59,	64,	12,	0xfff07fffffffffffULL },
	{ 12,	16,	12,	0xfff0fff0fff0fff0ULL },
	{ 28,	32,	12,	0xfff0fffffff0ffffULL },
	{ 60,	64,	12,	0xfff0ffffffffffffULL },
	{ 13,	16,	12,	0xfff1fff1fff1fff1ULL },
	{ 29,	32,	12,	0xfff1fffffff1ffffULL },
	{ 61,	64,	12,	0xfff1ffffffffffffULL },
	{ 14,	16,	12,	0xfff3fff3fff3fff3ULL },
	{ 30,	32,	12,	0xfff3fffffff3ffffULL },
	{ 62,	64,	12,	0xfff3ffffffffffffULL },
	{ 15,	16,	12,	0xfff7fff7fff7fff7ULL },
	{ 31,	32,	12,	0xfff7fffffff7ffffULL },
	{ 63,	64,	12,	0xfff7ffffffffffffULL },
	{ 13,	64,	13,	0xfff8000000000000ULL },
	{ 14,	64,	13,	0xfff8000000000001ULL },
	{ 15,	64,	13,	0xfff8000000000003ULL },
	{ 16,	64,	13,	0xfff8000000000007ULL },
	{ 17,	64,	13,	0xfff800000000000fULL },
	{ 18,	64,	13,	0xfff800000000001fULL },
	{ 19,	64,	13,	0xfff800000000003fULL },
	{ 20,	64,	13,	0xfff800000000007fULL },
	{ 21,	64,	13,	0xfff80000000000ffULL },
	{ 22,	64,	13,	0xfff80000000001ffULL },
	{ 23,	64,	13,	0xfff80000000003ffULL },
	{ 24,	64,	13,	0xfff80000000007ffULL },
	{ 25,	64,	13,	0xfff8000000000fffULL },
	{ 26,	64,	13,	0xfff8000000001fffULL },
	{ 27,	64,	13,	0xfff8000000003fffULL },
	{ 28,	64,	13,	0xfff8000000007fffULL },
	{ 29,	64,	13,	0xfff800000000ffffULL },
	{ 30,	64,	13,	0xfff800000001ffffULL },
	{ 31,	64,	13,	0xfff800000003ffffULL },
	{ 32,	64,	13,	0xfff800000007ffffULL },
	{ 33,	64,	13,	0xfff80000000fffffULL },
	{ 34,	64,	13,	0xfff80000001fffffULL },
	{ 35,	64,	13,	0xfff80000003fffffULL },
	{ 36,	64,	13,	0xfff80000007fffffULL },
	{ 37,	64,	13,	0xfff8000000ffffffULL },
	{ 38,	64,	13,	0xfff8000001ffffffULL },
	{ 39,	64,	13,	0xfff8000003ffffffULL },
	{ 40,	64,	13,	0xfff8000007ffffffULL },
	{ 41,	64,	13,	0xfff800000fffffffULL },
	{ 42,	64,	13,	0xfff800001fffffffULL },
	{ 43,	64,	13,	0xfff800003fffffffULL },
	{ 44,	64,	13,	0xfff800007fffffffULL },
	{ 13,	32,	13,	0xfff80000fff80000ULL },
	{ 45,	64,	13,	0xfff80000ffffffffULL },
	{ 14,	32,	13,	0xfff80001fff80001ULL },
	{ 46,	64,	13,	0xfff80001ffffffffULL },
	{ 15,	32,	13,	0xfff80003fff80003ULL },
	{ 47,	64,	13,	0xfff80003ffffffffULL },
	{ 16,	32,	13,	0xfff80007fff80007ULL },
	{ 48,	64,	13,	0xfff80007ffffffffULL },
	{ 17,	32,	13,	0xfff8000ffff8000fULL },
	{ 49,	64,	13,	0xfff8000fffffffffULL },
	{ 18,	32,	13,	0xfff8001ffff8001fULL },
	{ 50,	64,	13,	0xfff8001fffffffffULL },
	{ 19,	32,	13,	0xfff8003ffff8003fULL },
	{ 51,	64,	13,	0xfff8003fffffffffULL },
	{ 20,	32,	13,	0xfff8007ffff8007fULL },
	{ 52,	64,	13,	0xfff8007fffffffffULL },
	{ 21,	32,	13,	0xfff800fffff800ffULL },
	{ 53,	64,	13,	0xfff800ffffffffffULL },
	{ 22,	32,	13,	0xfff801fffff801ffULL },
	{ 54,	64,	13,	0xfff801ffffffffffULL },
	{ 23,	32,	13,	0xfff803fffff803ffULL },
	{ 55,	64,	13,	0xfff803ffffffffffULL },
	{ 24,	32,	13,	0xfff807fffff807ffULL },
	{ 56,	64,	13,	0xfff807ffffffffffULL },
	{ 25,	32,	13,	0xfff80ffffff80fffULL },
	{ 57,	64,	13,	0xfff80fffffffffffULL },
	{ 26,	32,	13,	0xfff81ffffff81fffULL },
	{ 58,	64,	13,	0xfff81fffffffffffULL },
	{ 27,	32,	13,	0xfff83ffffff83fffULL },
	{ 59,	64,	13,	0xfff83fffffffffffULL },
	{ 28,	32,	13,	0xfff87ffffff87fffULL },
	{ 60,	64,	13,	0xfff87fffffffffffULL },
	{ 13,	16,	13,	0xfff8fff8fff8fff8ULL },
	{ 29,	32,	13,	0xfff8fffffff8ffffULL },
	{ 61,	64,	13,	0xfff8ffffffffffffULL },
	{ 14,	16,	13,	0xfff9fff9fff9fff9ULL },
	{ 30,	32,	13,	0xfff9fffffff9ffffULL },
	{ 62,	64,	13,	0xfff9ffffffffffffULL },
	{ 15,	16,	13,	0xfffbfffbfffbfffbULL },
	{ 31,	32,	13,	0xfffbfffffffbffffULL },
	{ 63,	64,	13,	0xfffbffffffffffffULL },
	{ 14,	64,	14,	0xfffc000000000000ULL },
	{ 15,	64,	14,	0xfffc000000000001ULL },
	{ 16,	64,	14,	0xfffc000000000003ULL },
	{ 17,	64,	14,	0xfffc000000000007ULL },
	{ 18,	64,	14,	0xfffc00000000000fULL },
	{ 19,	64,	14,	0xfffc00000000001fULL },
	{ 20,	64,	14,	0xfffc00000000003fULL },
	{ 21,	64,	14,	0xfffc00000000007fULL },
	{ 22,	64,	14,	0xfffc0000000000ffULL },
	{ 23,	64,	14,	0xfffc0000000001ffULL },
	{ 24,	64,	14,	0xfffc0000000003ffULL },
	{ 25,	64,	14,	0xfffc0000000007ffULL },
	{ 26,	64,	14,	0xfffc000000000fffULL },
	{ 27,	64,	14,	0xfffc000000001fffULL },
	{ 28,	64,	14,	0xfffc000000003fffULL },
	{ 29,	64,	14,	0xfffc000000007fffULL },
	{ 30,	64,	14,	0xfffc00000000ffffULL },
	{ 31,	64,	14,	0xfffc00000001ffffULL },
	{ 32,	64,	14,	0xfffc00000003ffffULL },
	{ 33,	64,	14,	0xfffc00000007ffffULL },
	{ 34,	64,	14,	0xfffc0000000fffffULL },
	{ 35,	64,	14,	0xfffc0000001fffffULL },
	{ 36,	64,	14,	0xfffc0000003fffffULL },
	{ 37,	64,	14,	0xfffc0000007fffffULL },
	{ 38,	64,	14,	0xfffc000000ffffffULL },
	{ 39,	64,	14,	0xfffc000001ffffffULL },
	{ 40,	64,	14,	0xfffc000003ffffffULL },
	{ 41,	64,	14,	0xfffc000007ffffffULL },
	{ 42,	64,	14,	0xfffc00000fffffffULL },
	{ 43,	64,	14,	0xfffc00001fffffffULL },
	{ 44,	64,	14,	0xfffc00003fffffffULL },
	{ 45,	64,	14,	0xfffc00007fffffffULL },
	{ 14,	32,	14,	0xfffc0000fffc0000ULL },
	{ 46,	64,	14,	0xfffc0000ffffffffULL },
	{ 15,	32,	14,	0xfffc0001fffc0001ULL },
	{ 47,	64,	14,	0xfffc0001ffffffffULL },
	{ 16,	32,	14,	0xfffc0003fffc0003ULL },
	{ 48,	64,	14,	0xfffc0003ffffffffULL },
	{ 17,	32,	14,	0xfffc0007fffc0007ULL },
	{ 49,	64,	14,	0xfffc0007ffffffffULL },
	{ 18,	32,	14,	0xfffc000ffffc000fULL },
	{ 50,	64,	14,	0xfffc000fffffffffULL },
	{ 19,	32,	14,	0xfffc001ffffc001fULL },
	{ 51,	64,	14,	0xfffc001fffffffffULL },
	{ 20,	32,	14,	0xfffc003ffffc003fULL },
	{ 52,	64,	14,	0xfffc003fffffffffULL },
	{ 21,	32,	14,	0xfffc007ffffc007fULL },
	{ 53,	64,	14,	0xfffc007fffffffffULL },
	{ 22,	32,	14,	0xfffc00fffffc00ffULL },
	{ 54,	64,	14,	0xfffc00ffffffffffULL },
	{ 23,	32,	14,	0xfffc01fffffc01ffULL },
	{ 55,	64,	14,	0xfffc01ffffffffffULL },
	{ 24,	32,	14,	0xfffc03fffffc03ffULL },
	{ 56,	64,	14,	0xfffc03ffffffffffULL },
	{ 25,	32,	14,	0xfffc07fffffc07ffULL },
	{ 57,	64,	14,	0xfffc07ffffffffffULL },
	{ 26,	32,	14,	0xfffc0ffffffc0fffULL },
	{ 58,	64,	14,	0xfffc0fffffffffffULL },
	{ 27,	32,	14,	0xfffc1ffffffc1fffULL },
	{ 59,	64,	14,	0xfffc1fffffffffffULL },
	{ 28,	32,	14,	0xfffc3ffffffc3fffULL },
	{ 60,	64,	14,	0xfffc3fffffffffffULL },
	{ 29,	32,	14,	0xfffc7ffffffc7fffULL },
	{ 61,	64,	14,	0xfffc7fffffffffffULL },
	{ 14,	16,	14,	0xfffcfffcfffcfffcULL },
	{ 30,	32,	14,	0xfffcfffffffcffffULL },
	{ 62,	64,	14,	0xfffcffffffffffffULL },
	{ 15,	16,	14,	0xfffdfffdfffdfffdULL },
	{ 31,	32,	14,	0xfffdfffffffdffffULL },
	{ 63,	64,	14,	0xfffdffffffffffffULL },
	{ 15,	64,	15,	0xfffe000000000000ULL },
	{ 16,	64,	15,	0xfffe000000000001ULL },
	{ 17,	64,	15,	0xfffe000000000003ULL },
	{ 18,	64,	15,	0xfffe000000000007ULL },
	{ 19,	64,	15,	0xfffe00000000000fULL },
	{ 20,	64,	15,	0xfffe00000000001fULL },
	{ 21,	64,	15,	0xfffe00000000003fULL },
	{ 22,	64,	15,	0xfffe00000000007fULL },
	{ 23,	64,	15,	0xfffe0000000000ffULL },
	{ 24,	64,	15,	0xfffe0000000001ffULL },
	{ 25,	64,	15,	0xfffe0000000003ffULL },
	{ 26,	64,	15,	0xfffe0000000007ffULL },
	{ 27,	64,	15,	0xfffe000000000fffULL },
	{ 28,	64,	15,	0xfffe000000001fffULL },
	{ 29,	64,	15,	0xfffe000000003fffULL },
	{ 30,	64,	15,	0xfffe000000007fffULL },
	{ 31,	64,	15,	0xfffe00000000ffffULL },
	{ 32,	64,	15,	0xfffe00000001ffffULL },
	{ 33,	64,	15,	0xfffe00000003ffffULL },
	{ 34,	64,	15,	0xfffe00000007ffffULL },
	{ 35,	64,	15,	0xfffe0000000fffffULL },
	{ 36,	64,	15,	0xfffe0000001fffffULL },
	{ 37,	64,	15,	0xfffe0000003fffffULL },
	{ 38,	64,	15,	0xfffe0000007fffffULL },
	{ 39,	64,	15,	0xfffe000000ffffffULL },
	{ 40,	64,	15,	0xfffe000001ffffffULL },
	{ 41,	64,	15,	0xfffe000003ffffffULL },
	{ 42,	64,	15,	0xfffe000007ffffffULL },
	{ 43,	64,	15,	0xfffe00000fffffffULL },
	{ 44,	64,	15,	0xfffe00001fffffffULL },
	{ 45,	64,	15,	0xfffe00003fffffffULL },
	{ 46,	64,	15,	0xfffe00007fffffffULL },
	{ 15,	32,	15,	0xfffe0000fffe0000ULL },
	{ 47,	64,	15,	0xfffe0000ffffffffULL },
	{ 16,	32,	15,	0xfffe0001fffe0001ULL },
	{ 48,	64,	15,	0xfffe0001ffffffffULL },
	{ 17,	32,	15,	0xfffe0003fffe0003ULL },
	{ 49,	64,	15,	0xfffe0003ffffffffULL },
	{ 18,	32,	15,	0xfffe0007fffe0007ULL },
	{ 50,	64,	15,	0xfffe0007ffffffffULL },
	{ 19,	32,	15,	0xfffe000ffffe000fULL },
	{ 51,	64,	15,	0xfffe000fffffffffULL },
	{ 20,	32,	15,	0xfffe001ffffe001fULL },
	{ 52,	64,	15,	0xfffe001fffffffffULL },
	{ 21,	32,	15,	0xfffe003ffffe003fULL },
	{ 53,	64,	15,	0xfffe003fffffffffULL },
	{ 22,	32,	15,	0xfffe007ffffe007fULL },
	{ 54,	64,	15,	0xfffe007fffffffffULL },
	{ 23,	32,	15,	0xfffe00fffffe00ffULL },
	{ 55,	64,	15,	0xfffe00ffffffffffULL },
	{ 24,	32,	15,	0xfffe01fffffe01ffULL },
	{ 56,	64,	15,	0xfffe01ffffffffffULL },
	{ 25,	32,	15,	0xfffe03fffffe03ffULL },
	{ 57,	64,	15,	0xfffe03ffffffffffULL },
	{ 26,	32,	15,	0xfffe07fffffe07ffULL },
	{ 58,	64,	15,	0xfffe07ffffffffffULL },
	{ 27,	32,	15,	0xfffe0ffffffe0fffULL },
	{ 59,	64,	15,	0xfffe0fffffffffffULL },
	{ 28,	32,	15,	0xfffe1ffffffe1fffULL },
	{ 60,	64,	15,	0xfffe1fffffffffffULL },
	{ 29,	32,	15,	0xfffe3ffffffe3fffULL },
	{ 61,	64,	15,	0xfffe3fffffffffffULL },
	{ 30,	32,	15,	0xfffe7ffffffe7fffULL },
	{ 62,	64,	15,	0xfffe7fffffffffffULL },
	{ 15,	16,	15,	0xfffefffefffefffeULL },
	{ 31,	32,	15,	0xfffefffffffeffffULL },
	{ 63,	64,	15,	0xfffeffffffffffffULL },
	{ 16,	64,	16,	0xffff000000000000ULL },
	{ 17,	64,	16,	0xffff000000000001ULL },
	{ 18,	64,	16,	0xffff000000000003ULL },
	{ 19,	64,	16,	0xffff000000000007ULL },
	{ 20,	64,	16,	0xffff00000000000fULL },
	{ 21,	64,	16,	0xffff00000000001fULL },
	{ 22,	64,	16,	0xffff00000000003fULL },
	{ 23,	64,	16,	0xffff00000000007fULL },
	{ 24,	64,	16,	0xffff0000000000ffULL },
	{ 25,	64,	16,	0xffff0000000001ffULL },
	{ 26,	64,	16,	0xffff0000000003ffULL },
	{ 27,	64,	16,	0xffff0000000007ffULL },
	{ 28,	64,	16,	0xffff000000000fffULL },
	{ 29,	64,	16,	0xffff000000001fffULL },
	{ 30,	64,	16,	0xffff000000003fffULL },
	{ 31,	64,	16,	0xffff000000007fffULL },
	{ 32,	64,	16,	0xffff00000000ffffULL },
	{ 33,	64,	16,	0xffff00000001ffffULL },
	{ 34,	64,	16,	0xffff00000003ffffULL },
	{ 35,	64,	16,	0xffff00000007ffffULL },
	{ 36,	64,	16,	0xffff0000000fffffULL },
	{ 37,	64,	16,	0xffff0000001fffffULL },
	{ 38,	64,	16,	0xffff0000003fffffULL },
	{ 39,	64,	16,	0xffff0000007fffffULL },
	{ 40,	64,	16,	0xffff000000ffffffULL },
	{ 41,	64,	16,	0xffff000001ffffffULL },
	{ 42,	64,	16,	0xffff000003ffffffULL },
	{ 43,	64,	16,	0xffff000007ffffffULL },
	{ 44,	64,	16,	0xffff00000fffffffULL },
	{ 45,	64,	16,	0xffff00001fffffffULL },
	{ 46,	64,	16,	0xffff00003fffffffULL },
	{ 47,	64,	16,	0xffff00007fffffffULL },
	{ 16,	32,	16,	0xffff0000ffff0000ULL },
	{ 48,	64,	16,	0xffff0000ffffffffULL },
	{ 17,	32,	16,	0xffff0001ffff0001ULL },
	{ 49,	64,	16,	0xffff0001ffffffffULL },
	{ 18,	32,	16,	0xffff0003ffff0003ULL },
	{ 50,	64,	16,	0xffff0003ffffffffULL },
	{ 19,	32,	16,	0xffff0007ffff0007ULL },
	{ 51,	64,	16,	0xffff0007ffffffffULL },
	{ 20,	32,	16,	0xffff000fffff000fULL },
	{ 52,	64,	16,	0xffff000fffffffffULL },
	{ 21,	32,	16,	0xffff001fffff001fULL },
	{ 53,	64,	16,	0xffff001fffffffffULL },
	{ 22,	32,	16,	0xffff003fffff003fULL },
	{ 54,	64,	16,	0xffff003fffffffffULL },
	{ 23,	32,	16,	0xffff007fffff007fULL },
	{ 55,	64,	16,	0xffff007fffffffffULL },
	{ 24,	32,	16,	0xffff00ffffff00ffULL },
	{ 56,	64,	16,	0xffff00ffffffffffULL },
	{ 25,	32,	16,	0xffff01ffffff01ffULL },
	{ 57,	64,	16,	0xffff01ffffffffffULL },
	{ 26,	32,	16,	0xffff03ffffff03ffULL },
	{ 58,	64,	16,	0xffff03ffffffffffULL },
	{ 27,	32,	16,	0xffff07ffffff07ffULL },
	{ 59,	64,	16,	0xffff07ffffffffffULL },
	{ 28,	32,	16,	0xffff0fffffff0fffULL },
	{ 60,	64,	16,	0xffff0fffffffffffULL },
	{ 29,	32,	16,	0xffff1fffffff1fffULL },
	{ 61,	64,	16,	0xffff1fffffffffffULL },
	{ 30,	32,	16,	0xffff3fffffff3fffULL },
	{ 62,	64,	16,	0xffff3fffffffffffULL },
	{ 31,	32,	16,	0xffff7fffffff7fffULL },
	{ 63,	64,	16,	0xffff7fffffffffffULL },
	{ 17,	64,	17,	0xffff800000000000ULL },
	{ 18,	64,	17,	0xffff800000000001ULL },
	{ 19,	64,	17,	0xffff800000000003ULL },
	{ 20,	64,	17,	0xffff800000000007ULL },
	{ 21,	64,	17,	0xffff80000000000fULL },
	{ 22,	64,	17,	0xffff80000000001fULL },
	{ 23,	64,	17,	0xffff80000000003fULL },
	{ 24,	64,	17,	0xffff80000000007fULL },
	{ 25,	64,	17,	0xffff8000000000ffULL },
	{ 26,	64,	17,	0xffff8000000001ffULL },
	{ 27,	64,	17,	0xffff8000000003ffULL },
	{ 28,	64,	17,	0xffff8000000007ffULL },
	{ 29,	64,	17,	0xffff800000000fffULL },
	{ 30,	64,	17,	0xffff800000001fffULL },
	{ 31,	64,	17,	0xffff800000003fffULL },
	{ 32,	64,	17,	0xffff800000007fffULL },
	{ 33,	64,	17,	0xffff80000000ffffULL },
	{ 34,	64,	17,	0xffff80000001ffffULL },
	{ 35,	64,	17,	0xffff80000003ffffULL },
	{ 36,	64,	17,	0xffff80000007ffffULL },
	{ 37,	64,	17,	0xffff8000000fffffULL },
	{ 38,	64,	17,	0xffff8000001fffffULL },
	{ 39,	64,	17,	0xffff8000003fffffULL },
	{ 40,	64,	17,	0xffff8000007fffffULL },
	{ 41,	64,	17,	0xffff800000ffffffULL },
	{ 42,	64,	17,	0xffff800001ffffffULL },
	{ 43,	64,	17,	0xffff800003ffffffULL },
	{ 44,	64,	17,	0xffff800007ffffffULL },
	{ 45,	64,	17,	0xffff80000fffffffULL },
	{ 46,	64,	17,	0xffff80001fffffffULL },
	{ 47,	64,	17,	0xffff80003fffffffULL },
	{ 48,	64,	17,	0xffff80007fffffffULL },
	{ 17,	32,	17,	0xffff8000ffff8000ULL },
	{ 49,	64,	17,	0xffff8000ffffffffULL },
	{ 18,	32,	17,	0xffff8001ffff8001ULL },
	{ 50,	64,	17,	0xffff8001ffffffffULL },
	{ 19,	32,	17,	0xffff8003ffff8003ULL },
	{ 51,	64,	17,	0xffff8003ffffffffULL },
	{ 20,	32,	17,	0xffff8007ffff8007ULL },
	{ 52,	64,	17,	0xffff8007ffffffffULL },
	{ 21,	32,	17,	0xffff800fffff800fULL },
	{ 53,	64,	17,	0xffff800fffffffffULL },
	{ 22,	32,	17,	0xffff801fffff801fULL },
	{ 54,	64,	17,	0xffff801fffffffffULL },
	{ 23,	32,	17,	0xffff803fffff803fULL },
	{ 55,	64,	17,	0xffff803fffffffffULL },
	{ 24,	32,	17,	0xffff807fffff807fULL },
	{ 56,	64,	17,	0xffff807fffffffffULL },
	{ 25,	32,	17,	0xffff80ffffff80ffULL },
	{ 57,	64,	17,	0xffff80ffffffffffULL },
	{ 26,	32,	17,	0xffff81ffffff81ffULL },
	{ 58,	64,	17,	0xffff81ffffffffffULL },
	{ 27,	32,	17,	0xffff83ffffff83ffULL },
	{ 59,	64,	17,	0xffff83ffffffffffULL },
	{ 28,	32,	17,	0xffff87ffffff87ffULL },
	{ 60,	64,	17,	0xffff87ffffffffffULL },
	{ 29,	32,	17,	0xffff8fffffff8fffULL },
	{ 61,	64,	17,	0xffff8fffffffffffULL },
	{ 30,	32,	17,	0xffff9fffffff9fffULL },
	{ 62,	64,	17,	0xffff9fffffffffffULL },
	{ 31,	32,	17,	0xffffbfffffffbfffULL },
	{ 63,	64,	17,	0xffffbfffffffffffULL },
	{ 18,	64,	18,	0xffffc00000000000ULL },
	{ 19,	64,	18,	0xffffc00000000001ULL },
	{ 20,	64,	18,	0xffffc00000000003ULL },
	{ 21,	64,	18,	0xffffc00000000007ULL },
	{ 22,	64,	18,	0xffffc0000000000fULL },
	{ 23,	64,	18,	0xffffc0000000001fULL },
	{ 24,	64,	18,	0xffffc0000000003fULL },
	{ 25,	64,	18,	0xffffc0000000007fULL },
	{ 26,	64,	18,	0xffffc000000000ffULL },
	{ 27,	64,	18,	0xffffc000000001ffULL },
	{ 28,	64,	18,	0xffffc000000003ffULL },
	{ 29,	64,	18,	0xffffc000000007ffULL },
	{ 30,	64,	18,	0xffffc00000000fffULL },
	{ 31,	64,	18,	0xffffc00000001fffULL },
	{ 32,	64,	18,	0xffffc00000003fffULL },
	{ 33,	64,	18,	0xffffc00000007fffULL },
	{ 34,	64,	18,	0xffffc0000000ffffULL },
	{ 35,	64,	18,	0xffffc0000001ffffULL },
	{ 36,	64,	18,	0xffffc0000003ffffULL },
	{ 37,	64,	18,	0xffffc0000007ffffULL },
	{ 38,	64,	18,	0xffffc000000fffffULL },
	{ 39,	64,	18,	0xffffc000001fffffULL },
	{ 40,	64,	18,	0xffffc000003fffffULL },
	{ 41,	64,	18,	0xffffc000007fffffULL },
	{ 42,	64,	18,	0xffffc00000ffffffULL },
	{ 43,	64,	18,	0xffffc00001ffffffULL },
	{ 44,	64,	18,	0xffffc00003ffffffULL },
	{ 45,	64,	18,	0xffffc00007ffffffULL },
	{ 46,	64,	18,	0xffffc0000fffffffULL },
	{ 47,	64,	18,	0xffffc0001fffffffULL },
	{ 48,	64,	18,	0xffffc0003fffffffULL },
	{ 49,	64,	18,	0xffffc0007fffffffULL },
	{ 18,	32,	18,	0xffffc000ffffc000ULL },
	{ 50,	64,	18,	0xffffc000ffffffffULL },
	{ 19,	32,	18,	0xffffc001ffffc001ULL },
	{ 51,	64,	18,	0xffffc001ffffffffULL },
	{ 20,	32,	18,	0xffffc003ffffc003ULL },
	{ 52,	64,	18,	0xffffc003ffffffffULL },
	{ 21,	32,	18,	0xffffc007ffffc007ULL },
	{ 53,	64,	18,	0xffffc007ffffffffULL },
	{ 22,	32,	18,	0xffffc00fffffc00fULL },
	{ 54,	64,	18,	0xffffc00fffffffffULL },
	{ 23,	32,	18,	0xffffc01fffffc01fULL },
	{ 55,	64,	18,	0xffffc01fffffffffULL },
	{ 24,	32,	18,	0xffffc03fffffc03fULL },
	{ 56,	64,	18,	0xffffc03fffffffffULL },
	{ 25,	32,	18,	0xffffc07fffffc07fULL },
	{ 57,	64,	18,	0xffffc07fffffffffULL },
	{ 26,	32,	18,	0xffffc0ffffffc0ffULL },
	{ 58,	64,	18,	0xffffc0ffffffffffULL },
	{ 27,	32,	18,	0xffffc1ffffffc1ffULL },
	{ 59,	64,	18,	0xffffc1ffffffffffULL },
	{ 28,	32,	18,	0xffffc3ffffffc3ffULL },
	{ 60,	64,	18,	0xffffc3ffffffffffULL },
	{ 29,	32,	18,	0xffffc7ffffffc7ffULL },
	{ 61,	64,	18,	0xffffc7ffffffffffULL },
	{ 30,	32,	18,	0xffffcfffffffcfffULL },
	{ 62,	64,	18,	0xffffcfffffffffffULL },
	{ 31,	32,	18,	0xffffdfffffffdfffULL },
	{ 63,	64,	18,	0xffffdfffffffffffULL },
	{ 19,	64,	19,	0xffffe00000000000ULL },
	{ 20,	64,	19,	0xffffe00000000001ULL },
	{ 21,	64,	19,	0xffffe00000000003ULL },
	{ 22,	64,	19,	0xffffe00000000007ULL },
	{ 23,	64,	19,	0xffffe0000000000fULL },
	{ 24,	64,	19,	0xffffe0000000001fULL },
	{ 25,	64,	19,	0xffffe0000000003fULL },
	{ 26,	64,	19,	0xffffe0000000007fULL },
	{ 27,	64,	19,	0xffffe000000000ffULL },
	{ 28,	64,	19,	0xffffe000000001ffULL },
	{ 29,	64,	19,	0xffffe000000003ffULL },
	{ 30,	64,	19,	0xffffe000000007ffULL },
	{ 31,	64,	19,	0xffffe00000000fffULL },
	{ 32,	64,	19,	0xffffe00000001fffULL },
	{ 33,	64,	19,	0xffffe00000003fffULL },
	{ 34,	64,	19,	0xffffe00000007fffULL },
	{ 35,	64,	19,	0xffffe0000000ffffULL },
	{ 36,	64,	19,	0xffffe0000001ffffULL },
	{ 37,	64,	19,	0xffffe0000003ffffULL },
	{ 38,	64,	19,	0xffffe0000007ffffULL },
	{ 39,	64,	19,	0xffffe000000fffffULL },
	{ 40,	64,	19,	0xffffe000001fffffULL },
	{ 41,	64,	19,	0xffffe000003fffffULL },
	{ 42,	64,	19,	0xffffe000007fffffULL },
	{ 43,	64,	19,	0xffffe00000ffffffULL },
	{ 44,	64,	19,	0xffffe00001ffffffULL },
	{ 45,	64,	19,	0xffffe00003ffffffULL },
	{ 46,	64,	19,	0xffffe00007ffffffULL },
	{ 47,	64,	19,	0xffffe0000fffffffULL },
	{ 48,	64,	19,	0xffffe0001fffffffULL },
	{ 49,	64,	19,	0xffffe0003fffffffULL },
	{ 50,	64,	19,	0xffffe0007fffffffULL },
	{ 19,	32,	19,	0xffffe000ffffe000ULL },
	{ 51,	64,	19,	0xffffe000ffffffffULL },
	{ 20,	32,	19,	0xffffe001ffffe001ULL },
	{ 52,	64,	19,	0xffffe001ffffffffULL },
	{ 21,	32,	19,	0xffffe003ffffe003ULL },
	{ 53,	64,	19,	0xffffe003ffffffffULL },
	{ 22,	32,	19,	0xffffe007ffffe007ULL },
	{ 54,	64,	19,	0xffffe007ffffffffULL },
	{ 23,	32,	19,	0xffffe00fffffe00fULL },
	{ 55,	64,	19,	0xffffe00fffffffffULL },
	{ 24,	32,	19,	0xffffe01fffffe01fULL },
	{ 56,	64,	19,	0xffffe01fffffffffULL },
	{ 25,	32,	19,	0xffffe03fffffe03fULL },
	{ 57,	64,	19,	0xffffe03fffffffffULL },
	{ 26,	32,	19,	0xffffe07fffffe07fULL },
	{ 58,	64,	19,	0xffffe07fffffffffULL },
	{ 27,	32,	19,	0xffffe0ffffffe0ffULL },
	{ 59,	64,	19,	0xffffe0ffffffffffULL },
	{ 28,	32,	19,	0xffffe1ffffffe1ffULL },
	{ 60,	64,	19,	0xffffe1ffffffffffULL },
	{ 29,	32,	19,	0xffffe3ffffffe3ffULL },
	{ 61,	64,	19,	0xffffe3ffffffffffULL },
	{ 30,	32,	19,	0xffffe7ffffffe7ffULL },
	{ 62,	64,	19,	0xffffe7ffffffffffULL },
	{ 31,	32,	19,	0xffffefffffffefffULL },
	{ 63,	64,	19,	0xffffefffffffffffULL },
	{ 20,	64,	20,	0xfffff00000000000ULL },
	{ 21,	64,	20,	0xfffff00000000001ULL },
	{ 22,	64,	20,	0xfffff00000000003ULL },
	{ 23,	64,	20,	0xfffff00000000007ULL },
	{ 24,	64,	20,	0xfffff0000000000fULL },
	{ 25,	64,	20,	0xfffff0000000001fULL },
	{ 26,	64,	20,	0xfffff0000000003fULL },
	{ 27,	64,	20,	0xfffff0000000007fULL },
	{ 28,	64,	20,	0xfffff000000000ffULL },
	{ 29,	64,	20,	0xfffff000000001ffULL },
	{ 30,	64,	20,	0xfffff000000003ffULL },
	{ 31,	64,	20,	0xfffff000000007ffULL },
	{ 32,	64,	20,	0xfffff00000000fffULL },
	{ 33,	64,	20,	0xfffff00000001fffULL },
	{ 34,	64,	20,	0xfffff00000003fffULL },
	{ 35,	64,	20,	0xfffff00000007fffULL },
	{ 36,	64,	20,	0xfffff0000000ffffULL },
	{ 37,	64,	20,	0xfffff0000001ffffULL },
	{ 38,	64,	20,	0xfffff0000003ffffULL },
	{ 39,	64,	20,	0xfffff0000007ffffULL },
	{ 40,	64,	20,	0xfffff000000fffffULL },
	{ 41,	64,	20,	0xfffff000001fffffULL },
	{ 42,	64,	20,	0xfffff000003fffffULL },
	{ 43,	64,	20,	0xfffff000007fffffULL },
	{ 44,	64,	20,	0xfffff00000ffffffULL },
	{ 45,	64,	20,	0xfffff00001ffffffULL },
	{ 46,	64,	20,	0xfffff00003ffffffULL },
	{ 47,	64,	20,	0xfffff00007ffffffULL },
	{ 48,	64,	20,	0xfffff0000fffffffULL },
	{ 49,	64,	20,	0xfffff0001fffffffULL },
	{ 50,	64,	20,	0xfffff0003fffffffULL },
	{ 51,	64,	20,	0xfffff0007fffffffULL },
	{ 20,	32,	20,	0xfffff000fffff000ULL },
	{ 52,	64,	20,	0xfffff000ffffffffULL },
	{ 21,	32,	20,	0xfffff001fffff001ULL },
	{ 53,	64,	20,	0xfffff001ffffffffULL },
	{ 22,	32,	20,	0xfffff003fffff003ULL },
	{ 54,	64,	20,	0xfffff003ffffffffULL },
	{ 23,	32,	20,	0xfffff007fffff007ULL },
	{ 55,	64,	20,	0xfffff007ffffffffULL },
	{ 24,	32,	20,	0xfffff00ffffff00fULL },
	{ 56,	64,	20,	0xfffff00fffffffffULL },
	{ 25,	32,	20,	0xfffff01ffffff01fULL },
	{ 57,	64,	20,	0xfffff01fffffffffULL },
	{ 26,	32,	20,	0xfffff03ffffff03fULL },
	{ 58,	64,	20,	0xfffff03fffffffffULL },
	{ 27,	32,	20,	0xfffff07ffffff07fULL },
	{ 59,	64,	20,	0xfffff07fffffffffULL },
	{ 28,	32,	20,	0xfffff0fffffff0ffULL },
	{ 60,	64,	20,	0xfffff0ffffffffffULL },
	{ 29,	32,	20,	0xfffff1fffffff1ffULL },
	{ 61,	64,	20,	0xfffff1ffffffffffULL },
	{ 30,	32,	20,	0xfffff3fffffff3ffULL },
	{ 62,	64,	20,	0xfffff3ffffffffffULL },
	{ 31,	32,	20,	0xfffff7fffffff7ffULL },
	{ 63,	64,	20,	0xfffff7ffffffffffULL },
	{ 21,	64,	21,	0xfffff80000000000ULL },
	{ 22,	64,	21,	0xfffff80000000001ULL },
	{ 23,	64,	21,	0xfffff80000000003ULL },
	{ 24,	64,	21,	0xfffff80000000007ULL },
	{ 25,	64,	21,	0xfffff8000000000fULL },
	{ 26,	64,	21,	0xfffff8000000001fULL },
	{ 27,	64,	21,	0xfffff8000000003fULL },
	{ 28,	64,	21,	0xfffff8000000007fULL },
	{ 29,	64,	21,	0xfffff800000000ffULL },
	{ 30,	64,	21,	0xfffff800000001ffULL },
	{ 31,	64,	21,	0xfffff800000003ffULL },
	{ 32,	64,	21,	0xfffff800000007ffULL },
	{ 33,	64,	21,	0xfffff80000000fffULL },
	{ 34,	64,	21,	0xfffff80000001fffULL },
	{ 35,	64,	21,	0xfffff80000003fffULL },
	{ 36,	64,	21,	0xfffff80000007fffULL },
	{ 37,	64,	21,	0xfffff8000000ffffULL },
	{ 38,	64,	21,	0xfffff8000001ffffULL },
	{ 39,	64,	21,	0xfffff8000003ffffULL },
	{ 40,	64,	21,	0xfffff8000007ffffULL },
	{ 41,	64,	21,	0xfffff800000fffffULL },
	{ 42,	64,	21,	0xfffff800001fffffULL },
	{ 43,	64,	21,	0xfffff800003fffffULL },
	{ 44,	64,	21,	0xfffff800007fffffULL },
	{ 45,	64,	21,	0xfffff80000ffffffULL },
	{ 46,	64,	21,	0xfffff80001ffffffULL },
	{ 47,	64,	21,	0xfffff80003ffffffULL },
	{ 48,	64,	21,	0xfffff80007ffffffULL },
	{ 49,	64,	21,	0xfffff8000fffffffULL },
	{ 50,	64,	21,	0xfffff8001fffffffULL },
	{ 51,	64,	21,	0xfffff8003fffffffULL },
	{ 52,	64,	21,	0xfffff8007fffffffULL },
	{ 21,	32,	21,	0xfffff800fffff800ULL },
	{ 53,	64,	21,	0xfffff800ffffffffULL },
	{ 22,	32,	21,	0xfffff801fffff801ULL },
	{ 54,	64,	21,	0xfffff801ffffffffULL },
	{ 23,	32,	21,	0xfffff803fffff803ULL },
	{ 55,	64,	21,	0xfffff803ffffffffULL },
	{ 24,	32,	21,	0xfffff807fffff807ULL },
	{ 56,	64,	21,	0xfffff807ffffffffULL },
	{ 25,	32,	21,	0xfffff80ffffff80fULL },
	{ 57,	64,	21,	0xfffff80fffffffffULL },
	{ 26,	32,	21,	0xfffff81ffffff81fULL },
	{ 58,	64,	21,	0xfffff81fffffffffULL },
	{ 27,	32,	21,	0xfffff83ffffff83fULL },
	{ 59,	64,	21,	0xfffff83fffffffffULL },
	{ 28,	32,	21,	0xfffff87ffffff87fULL },
	{ 60,	64,	21,	0xfffff87fffffffffULL },
	{ 29,	32,	21,	0xfffff8fffffff8ffULL },
	{ 61,	64,	21,	0xfffff8ffffffffffULL },
	{ 30,	32,	21,	0xfffff9fffffff9ffULL },
	{ 62,	64,	21,	0xfffff9ffffffffffULL },
	{ 31,	32,	21,	0xfffffbfffffffbffULL },
	{ 63,	64,	21,	0xfffffbffffffffffULL },
	{ 22,	64,	22,	0xfffffc0000000000ULL },
	{ 23,	64,	22,	0xfffffc0000000001ULL },
	{ 24,	64,	22,	0xfffffc0000000003ULL },
	{ 25,	64,	22,	0xfffffc0000000007ULL },
	{ 26,	64,	22,	0xfffffc000000000fULL },
	{ 27,	64,	22,	0xfffffc000000001fULL },
	{ 28,	64,	22,	0xfffffc000000003fULL },
	{ 29,	64,	22,	0xfffffc000000007fULL },
	{ 30,	64,	22,	0xfffffc00000000ffULL },
	{ 31,	64,	22,	0xfffffc00000001ffULL },
	{ 32,	64,	22,	0xfffffc00000003ffULL },
	{ 33,	64,	22,	0xfffffc00000007ffULL },
	{ 34,	64,	22,	0xfffffc0000000fffULL },
	{ 35,	64,	22,	0xfffffc0000001fffULL },
	{ 36,	64,	22,	0xfffffc0000003fffULL },
	{ 37,	64,	22,	0xfffffc0000007fffULL },
	{ 38,	64,	22,	0xfffffc000000ffffULL },
	{ 39,	64,	22,	0xfffffc000001ffffULL },
	{ 40,	64,	22,	0xfffffc000003ffffULL },
	{ 41,	64,	22,	0xfffffc000007ffffULL },
	{ 42,	64,	22,	0xfffffc00000fffffULL },
	{ 43,	64,	22,	0xfffffc00001fffffULL },
	{ 44,	64,	22,	0xfffffc00003fffffULL },
	{ 45,	64,	22,	0xfffffc00007fffffULL },
	{ 46,	64,	22,	0xfffffc0000ffffffULL },
	{ 47,	64,	22,	0xfffffc0001ffffffULL },
	{ 48,	64,	22,	0xfffffc0003ffffffULL },
	{ 49,	64,	22,	0xfffffc0007ffffffULL },
	{ 50,	64,	22,	0xfffffc000fffffffULL },
	{ 51,	64,	22,	0xfffffc001fffffffULL },
	{ 52,	64,	22,	0xfffffc003fffffffULL },
	{ 53,	64,	22,	0xfffffc007fffffffULL },
	{ 22,	32,	22,	0xfffffc00fffffc00ULL },
	{ 54,	64,	22,	0xfffffc00ffffffffULL },
	{ 23,	32,	22,	0xfffffc01fffffc01ULL },
	{ 55,	64,	22,	0xfffffc01ffffffffULL },
	{ 24,	32,	22,	0xfffffc03fffffc03ULL },
	{ 56,	64,	22,	0xfffffc03ffffffffULL },
	{ 25,	32,	22,	0xfffffc07fffffc07ULL },
	{ 57,	64,	22,	0xfffffc07ffffffffULL },
	{ 26,	32,	22,	0xfffffc0ffffffc0fULL },
	{ 58,	64,	22,	0xfffffc0fffffffffULL },
	{ 27,	32,	22,	0xfffffc1ffffffc1fULL },
	{ 59,	64,	22,	0xfffffc1fffffffffULL },
	{ 28,	32,	22,	0xfffffc3ffffffc3fULL },
	{ 60,	64,	22,	0xfffffc3fffffffffULL },
	{ 29,	32,	22,	0xfffffc7ffffffc7fULL },
	{ 61,	64,	22,	0xfffffc7fffffffffULL },
	{ 30,	32,	22,	0xfffffcfffffffcffULL },
	{ 62,	64,	22,	0xfffffcffffffffffULL },
	{ 31,	32,	22,	0xfffffdfffffffdffULL },
	{ 63,	64,	22,	0xfffffdffffffffffULL },
	{ 23,	64,	23,	0xfffffe0000000000ULL },
	{ 24,	64,	23,	0xfffffe0000000001ULL },
	{ 25,	64,	23,	0xfffffe0000000003ULL },
	{ 26,	64,	23,	0xfffffe0000000007ULL },
	{ 27,	64,	23,	0xfffffe000000000fULL },
	{ 28,	64,	23,	0xfffffe000000001fULL },
	{ 29,	64,	23,	0xfffffe000000003fULL },
	{ 30,	64,	23,	0xfffffe000000007fULL },
	{ 31,	64,	23,	0xfffffe00000000ffULL },
	{ 32,	64,	23,	0xfffffe00000001ffULL },
	{ 33,	64,	23,	0xfffffe00000003ffULL },
	{ 34,	64,	23,	0xfffffe00000007ffULL },
	{ 35,	64,	23,	0xfffffe0000000fffULL },
	{ 36,	64,	23,	0xfffffe0000001fffULL },
	{ 37,	64,	23,	0xfffffe0000003fffULL },
	{ 38,	64,	23,	0xfffffe0000007fffULL },
	{ 39,	64,	23,	0xfffffe000000ffffULL },
	{ 40,	64,	23,	0xfffffe000001ffffULL },
	{ 41,	64,	23,	0xfffffe000003ffffULL },
	{ 42,	64,	23,	0xfffffe000007ffffULL },
	{ 43,	64,	23,	0xfffffe00000fffffULL },
	{ 44,	64,	23,	0xfffffe00001fffffULL },
	{ 45,	64,	23,	0xfffffe00003fffffULL },
	{ 46,	64,	23,	0xfffffe00007fffffULL },
	{ 47,	64,	23,	0xfffffe0000ffffffULL },
	{ 48,	64,	23,	0xfffffe0001ffffffULL },
	{ 49,	64,	23,	0xfffffe0003ffffffULL },
	{ 50,	64,	23,	0xfffffe0007ffffffULL },
	{ 51,	64,	23,	0xfffffe000fffffffULL },
	{ 52,	64,	23,	0xfffffe001fffffffULL },
	{ 53,	64,	23,	0xfffffe003fffffffULL },
	{ 54,	64,	23,	0xfffffe007fffffffULL },
	{ 23,	32,	23,	0xfffffe00fffffe00ULL },
	{ 55,	64,	23,	0xfffffe00ffffffffULL },
	{ 24,	32,	23,	0xfffffe01fffffe01ULL },
	{ 56,	64,	23,	0xfffffe01ffffffffULL },
	{ 25,	32,	23,	0xfffffe03fffffe03ULL },
	{ 57,	64,	23,	0xfffffe03ffffffffULL },
	{ 26,	32,	23,	0xfffffe07fffffe07ULL },
	{ 58,	64,	23,	0xfffffe07ffffffffULL },
	{ 27,	32,	23,	0xfffffe0ffffffe0fULL },
	{ 59,	64,	23,	0xfffffe0fffffffffULL },
	{ 28,	32,	23,	0xfffffe1ffffffe1fULL },
	{ 60,	64,	23,	0xfffffe1fffffffffULL },
	{ 29,	32,	23,	0xfffffe3ffffffe3fULL },
	{ 61,	64,	23,	0xfffffe3fffffffffULL },
	{ 30,	32,	23,	0xfffffe7ffffffe7fULL },
	{ 62,	64,	23,	0xfffffe7fffffffffULL },
	{ 31,	32,	23,	0xfffffefffffffeffULL },
	{ 63,	64,	23,	0xfffffeffffffffffULL },
	{ 24,	64,	24,	0xffffff0000000000ULL },
	{ 25,	64,	24,	0xffffff0000000001ULL },
	{ 26,	64,	24,	0xffffff0000000003ULL },
	{ 27,	64,	24,	0xffffff0000000007ULL },
	{ 28,	64,	24,	0xffffff000000000fULL },
	{ 29,	64,	24,	0xffffff000000001fULL },
	{ 30,	64,	24,	0xffffff000000003fULL },
	{ 31,	64,	24,	0xffffff000000007fULL },
	{ 32,	64,	24,	0xffffff00000000ffULL },
	{ 33,	64,	24,	0xffffff00000001ffULL },
	{ 34,	64,	24,	0xffffff00000003ffULL },
	{ 35,	64,	24,	0xffffff00000007ffULL },
	{ 36,	64,	24,	0xffffff0000000fffULL },
	{ 37,	64,	24,	0xffffff0000001fffULL },
	{ 38,	64,	24,	0xffffff0000003fffULL },
	{ 39,	64,	24,	0xffffff0000007fffULL },
	{ 40,	64,	24,	0xffffff000000ffffULL },
	{ 41,	64,	24,	0xffffff000001ffffULL },
	{ 42,	64,	24,	0xffffff000003ffffULL },
	{ 43,	64,	24,	0xffffff000007ffffULL },
	{ 44,	64,	24,	0xffffff00000fffffULL },
	{ 45,	64,	24,	0xffffff00001fffffULL },
	{ 46,	64,	24,	0xffffff00003fffffULL },
	{ 47,	64,	24,	0xffffff00007fffffULL },
	{ 48,	64,	24,	0xffffff0000ffffffULL },
	{ 49,	64,	24,	0xffffff0001ffffffULL },
	{ 50,	64,	24,	0xffffff0003ffffffULL },
	{ 51,	64,	24,	0xffffff0007ffffffULL },
	{ 52,	64,	24,	0xffffff000fffffffULL },
	{ 53,	64,	24,	0xffffff001fffffffULL },
	{ 54,	64,	24,	0xffffff003fffffffULL },
	{ 55,	64,	24,	0xffffff007fffffffULL },
	{ 24,	32,	24,	0xffffff00ffffff00ULL },
	{ 56,	64,	24,	0xffffff00ffffffffULL },
	{ 25,	32,	24,	0xffffff01ffffff01ULL },
	{ 57,	64,	24,	0xffffff01ffffffffULL },
	{ 26,	32,	24,	0xffffff03ffffff03ULL },
	{ 58,	64,	24,	0xffffff03ffffffffULL },
	{ 27,	32,	24,	0xffffff07ffffff07ULL },
	{ 59,	64,	24,	0xffffff07ffffffffULL },
	{ 28,	32,	24,	0xffffff0fffffff0fULL },
	{ 60,	64,	24,	0xffffff0fffffffffULL },
	{ 29,	32,	24,	0xffffff1fffffff1fULL },
	{ 61,	64,	24,	0xffffff1fffffffffULL },
	{ 30,	32,	24,	0xffffff3fffffff3fULL },
	{ 62,	64,	24,	0xffffff3fffffffffULL },
	{ 31,	32,	24,	0xffffff7fffffff7fULL },
	{ 63,	64,	24,	0xffffff7fffffffffULL },
	{ 25,	64,	25,	0xffffff8000000000ULL },
	{ 26,	64,	25,	0xffffff8000000001ULL },
	{ 27,	64,	25,	0xffffff8000000003ULL },
	{ 28,	64,	25,	0xffffff8000000007ULL },
	{ 29,	64,	25,	0xffffff800000000fULL },
	{ 30,	64,	25,	0xffffff800000001fULL },
	{ 31,	64,	25,	0xffffff800000003fULL },
	{ 32,	64,	25,	0xffffff800000007fULL },
	{ 33,	64,	25,	0xffffff80000000ffULL },
	{ 34,	64,	25,	0xffffff80000001ffULL },
	{ 35,	64,	25,	0xffffff80000003ffULL },
	{ 36,	64,	25,	0xffffff80000007ffULL },
	{ 37,	64,	25,	0xffffff8000000fffULL },
	{ 38,	64,	25,	0xffffff8000001fffULL },
	{ 39,	64,	25,	0xffffff8000003fffULL },
	{ 40,	64,	25,	0xffffff8000007fffULL },
	{ 41,	64,	25,	0xffffff800000ffffULL },
	{ 42,	64,	25,	0xffffff800001ffffULL },
	{ 43,	64,	25,	0xffffff800003ffffULL },
	{ 44,	64,	25,	0xffffff800007ffffULL },
	{ 45,	64,	25,	0xffffff80000fffffULL },
	{ 46,	64,	25,	0xffffff80001fffffULL },
	{ 47,	64,	25,	0xffffff80003fffffULL },
	{ 48,	64,	25,	0xffffff80007fffffULL },
	{ 49,	64,	25,	0xffffff8000ffffffULL },
	{ 50,	64,	25,	0xffffff8001ffffffULL },
	{ 51,	64,	25,	0xffffff8003ffffffULL },
	{ 52,	64,	25,	0xffffff8007ffffffULL },
	{ 53,	64,	25,	0xffffff800fffffffULL },
	{ 54,	64,	25,	0xffffff801fffffffULL },
	{ 55,	64,	25,	0xffffff803fffffffULL },
	{ 56,	64,	25,	0xffffff807fffffffULL },
	{ 25,	32,	25,	0xffffff80ffffff80ULL },
	{ 57,	64,	25,	0xffffff80ffffffffULL },
	{ 26,	32,	25,	0xffffff81ffffff81ULL },
	{ 58,	64,	25,	0xffffff81ffffffffULL },
	{ 27,	32,	25,	0xffffff83ffffff83ULL },
	{ 59,	64,	25,	0xffffff83ffffffffULL },
	{ 28,	32,	25,	0xffffff87ffffff87ULL },
	{ 60,	64,	25,	0xffffff87ffffffffULL },
	{ 29,	32,	25,	0xffffff8fffffff8fULL },
	{ 61,	64,	25,	0xffffff8fffffffffULL },
	{ 30,	32,	25,	0xffffff9fffffff9fULL },
	{ 62,	64,	25,	0xffffff9fffffffffULL },
	{ 31,	32,	25,	0xffffffbfffffffbfULL },
	{ 63,	64,	25,	0xffffffbfffffffffULL },
	{ 26,	64,	26,	0xffffffc000000000ULL },
	{ 27,	64,	26,	0xffffffc000000001ULL },
	{ 28,	64,	26,	0xffffffc000000003ULL },
	{ 29,	64,	26,	0xffffffc000000007ULL },
	{ 30,	64,	26,	0xffffffc00000000fULL },
	{ 31,	64,	26,	0xffffffc00000001fULL },
	{ 32,	64,	26,	0xffffffc00000003fULL },
	{ 33,	64,	26,	0xffffffc00000007fULL },
	{ 34,	64,	26,	0xffffffc0000000ffULL },
	{ 35,	64,	26,	0xffffffc0000001ffULL },
	{ 36,	64,	26,	0xffffffc0000003ffULL },
	{ 37,	64,	26,	0xffffffc0000007ffULL },
	{ 38,	64,	26,	0xffffffc000000fffULL },
	{ 39,	64,	26,	0xffffffc000001fffULL },
	{ 40,	64,	26,	0xffffffc000003fffULL },
	{ 41,	64,	26,	0xffffffc000007fffULL },
	{ 42,	64,	26,	0xffffffc00000ffffULL },
	{ 43,	64,	26,	0xffffffc00001ffffULL },
	{ 44,	64,	26,	0xffffffc00003ffffULL },
	{ 45,	64,	26,	0xffffffc00007ffffULL },
	{ 46,	64,	26,	0xffffffc0000fffffULL },
	{ 47,	64,	26,	0xffffffc0001fffffULL },
	{ 48,	64,	26,	0xffffffc0003fffffULL },
	{ 49,	64,	26,	0xffffffc0007fffffULL },
	{ 50,	64,	26,	0xffffffc000ffffffULL },
	{ 51,	64,	26,	0xffffffc001ffffffULL },
	{ 52,	64,	26,	0xffffffc003ffffffULL },
	{ 53,	64,	26,	0xffffffc007ffffffULL },
	{ 54,	64,	26,	0xffffffc00fffffffULL },
	{ 55,	64,	26,	0xffffffc01fffffffULL },
	{ 56,	64,	26,	0xffffffc03fffffffULL },
	{ 57,	64,	26,	0xffffffc07fffffffULL },
	{ 26,	32,	26,	0xffffffc0ffffffc0ULL },
	{ 58,	64,	26,	0xffffffc0ffffffffULL },
	{ 27,	32,	26,	0xffffffc1ffffffc1ULL },
	{ 59,	64,	26,	0xffffffc1ffffffffULL },
	{ 28,	32,	26,	0xffffffc3ffffffc3ULL },
	{ 60,	64,	26,	0xffffffc3ffffffffULL },
	{ 29,	32,	26,	0xffffffc7ffffffc7ULL },
	{ 61,	64,	26,	0xffffffc7ffffffffULL },
	{ 30,	32,	26,	0xffffffcfffffffcfULL },
	{ 62,	64,	26,	0xffffffcfffffffffULL },
	{ 31,	32,	26,	0xffffffdfffffffdfULL },
	{ 63,	64,	26,	0xffffffdfffffffffULL },
	{ 27,	64,	27,	0xffffffe000000000ULL },
	{ 28,	64,	27,	0xffffffe000000001ULL },
	{ 29,	64,	27,	0xffffffe000000003ULL },
	{ 30,	64,	27,	0xffffffe000000007ULL },
	{ 31,	64,	27,	0xffffffe00000000fULL },
	{ 32,	64,	27,	0xffffffe00000001fULL },
	{ 33,	64,	27,	0xffffffe00000003fULL },
	{ 34,	64,	27,	0xffffffe00000007fULL },
	{ 35,	64,	27,	0xffffffe0000000ffULL },
	{ 36,	64,	27,	0xffffffe0000001ffULL },
	{ 37,	64,	27,	0xffffffe0000003ffULL },
	{ 38,	64,	27,	0xffffffe0000007ffULL },
	{ 39,	64,	27,	0xffffffe000000fffULL },
	{ 40,	64,	27,	0xffffffe000001fffULL },
	{ 41,	64,	27,	0xffffffe000003fffULL },
	{ 42,	64,	27,	0xffffffe000007fffULL },
	{ 43,	64,	27,	0xffffffe00000ffffULL },
	{ 44,	64,	27,	0xffffffe00001ffffULL },
	{ 45,	64,	27,	0xffffffe00003ffffULL },
	{ 46,	64,	27,	0xffffffe00007ffffULL },
	{ 47,	64,	27,	0xffffffe0000fffffULL },
	{ 48,	64,	27,	0xffffffe0001fffffULL },
	{ 49,	64,	27,	0xffffffe0003fffffULL },
	{ 50,	64,	27,	0xffffffe0007fffffULL },
	{ 51,	64,	27,	0xffffffe000ffffffULL },
	{ 52,	64,	27,	0xffffffe001ffffffULL },
	{ 53,	64,	27,	0xffffffe003ffffffULL },
	{ 54,	64,	27,	0xffffffe007ffffffULL },
	{ 55,	64,	27,	0xffffffe00fffffffULL },
	{ 56,	64,	27,	0xffffffe01fffffffULL },
	{ 57,	64,	27,	0xffffffe03fffffffULL },
	{ 58,	64,	27,	0xffffffe07fffffffULL },
	{ 27,	32,	27,	0xffffffe0ffffffe0ULL },
	{ 59,	64,	27,	0xffffffe0ffffffffULL },
	{ 28,	32,	27,	0xffffffe1ffffffe1ULL },
	{ 60,	64,	27,	0xffffffe1ffffffffULL },
	{ 29,	32,	27,	0xffffffe3ffffffe3ULL },
	{ 61,	64,	27,	0xffffffe3ffffffffULL },
	{ 30,	32,	27,	0xffffffe7ffffffe7ULL },
	{ 62,	64,	27,	0xffffffe7ffffffffULL },
	{ 31,	32,	27,	0xffffffefffffffefULL },
	{ 63,	64,	27,	0xffffffefffffffffULL },
	{ 28,	64,	28,	0xfffffff000000000ULL },
	{ 29,	64,	28,	0xfffffff000000001ULL },
	{ 30,	64,	28,	0xfffffff000000003ULL },
	{ 31,	64,	28,	0xfffffff000000007ULL },
	{ 32,	64,	28,	0xfffffff00000000fULL },
	{ 33,	64,	28,	0xfffffff00000001fULL },
	{ 34,	64,	28,	0xfffffff00000003fULL },
	{ 35,	64,	28,	0xfffffff00000007fULL },
	{ 36,	64,	28,	0xfffffff0000000ffULL },
	{ 37,	64,	28,	0xfffffff0000001ffULL },
	{ 38,	64,	28,	0xfffffff0000003ffULL },
	{ 39,	64,	28,	0xfffffff0000007ffULL },
	{ 40,	64,	28,	0xfffffff000000fffULL },
	{ 41,	64,	28,	0xfffffff000001fffULL },
	{ 42,	64,	28,	0xfffffff000003fffULL },
	{ 43,	64,	28,	0xfffffff000007fffULL },
	{ 44,	64,	28,	0xfffffff00000ffffULL },
	{ 45,	64,	28,	0xfffffff00001ffffULL },
	{ 46,	64,	28,	0xfffffff00003ffffULL },
	{ 47,	64,	28,	0xfffffff00007ffffULL },
	{ 48,	64,	28,	0xfffffff0000fffffULL },
	{ 49,	64,	28,	0xfffffff0001fffffULL },
	{ 50,	64,	28,	0xfffffff0003fffffULL },
	{ 51,	64,	28,	0xfffffff0007fffffULL },
	{ 52,	64,	28,	0xfffffff000ffffffULL },
	{ 53,	64,	28,	0xfffffff001ffffffULL },
	{ 54,	64,	28,	0xfffffff003ffffffULL },
	{ 55,	64,	28,	0xfffffff007ffffffULL },
	{ 56,	64,	28,	0xfffffff00fffffffULL },
	{ 57,	64,	28,	0xfffffff01fffffffULL },
	{ 58,	64,	28,	0xfffffff03fffffffULL },
	{ 59,	64,	28,	0xfffffff07fffffffULL },
	{ 28,	32,	28,	0xfffffff0fffffff0ULL },
	{ 60,	64,	28,	0xfffffff0ffffffffULL },
	{ 29,	32,	28,	0xfffffff1fffffff1ULL },
	{ 61,	64,	28,	0xfffffff1ffffffffULL },
	{ 30,	32,	28,	0xfffffff3fffffff3ULL },
	{ 62,	64,	28,	0xfffffff3ffffffffULL },
	{ 31,	32,	28,	0xfffffff7fffffff7ULL },
	{ 63,	64,	28,	0xfffffff7ffffffffULL },
	{ 29,	64,	29,	0xfffffff800000000ULL },
	{ 30,	64,	29,	0xfffffff800000001ULL },
	{ 31,	64,	29,	0xfffffff800000003ULL },
	{ 32,	64,	29,	0xfffffff800000007ULL },
	{ 33,	64,	29,	0xfffffff80000000fULL },
	{ 34,	64,	29,	0xfffffff80000001fULL },
	{ 35,	64,	29,	0xfffffff80000003fULL },
	{ 36,	64,	29,	0xfffffff80000007fULL },
	{ 37,	64,	29,	0xfffffff8000000ffULL },
	{ 38,	64,	29,	0xfffffff8000001ffULL },
	{ 39,	64,	29,	0xfffffff8000003ffULL },
	{ 40,	64,	29,	0xfffffff8000007ffULL },
	{ 41,	64,	29,	0xfffffff800000fffULL },
	{ 42,	64,	29,	0xfffffff800001fffULL },
	{ 43,	64,	29,	0xfffffff800003fffULL },
	{ 44,	64,	29,	0xfffffff800007fffULL },
	{ 45,	64,	29,	0xfffffff80000ffffULL },
	{ 46,	64,	29,	0xfffffff80001ffffULL },
	{ 47,	64,	29,	0xfffffff80003ffffULL },
	{ 48,	64,	29,	0xfffffff80007ffffULL },
	{ 49,	64,	29,	0xfffffff8000fffffULL },
	{ 50,	64,	29,	0xfffffff8001fffffULL },
	{ 51,	64,	29,	0xfffffff8003fffffULL },
	{ 52,	64,	29,	0xfffffff8007fffffULL },
	{ 53,	64,	29,	0xfffffff800ffffffULL },
	{ 54,	64,	29,	0xfffffff801ffffffULL },
	{ 55,	64,	29,	0xfffffff803ffffffULL },
	{ 56,	64,	29,	0xfffffff807ffffffULL },
	{ 57,	64,	29,	0xfffffff80fffffffULL },
	{ 58,	64,	29,	0xfffffff81fffffffULL },
	{ 59,	64,	29,	0xfffffff83fffffffULL },
	{ 60,	64,	29,	0xfffffff87fffffffULL },
	{ 29,	32,	29,	0xfffffff8fffffff8ULL },
	{ 61,	64,	29,	0xfffffff8ffffffffULL },
	{ 30,	32,	29,	0xfffffff9fffffff9ULL },
	{ 62,	64,	29,	0xfffffff9ffffffffULL },
	{ 31,	32,	29,	0xfffffffbfffffffbULL },
	{ 63,	64,	29,	0xfffffffbffffffffULL },
	{ 30,	64,	30,	0xfffffffc00000000ULL },
	{ 31,	64,	30,	0xfffffffc00000001ULL },
	{ 32,	64,	30,	0xfffffffc00000003ULL },
	{ 33,	64,	30,	0xfffffffc00000007ULL },
	{ 34,	64,	30,	0xfffffffc0000000fULL },
	{ 35,	64,	30,	0xfffffffc0000001fULL },
	{ 36,	64,	30,	0xfffffffc0000003fULL },
	{ 37,	64,	30,	0xfffffffc0000007fULL },
	{ 38,	64,	30,	0xfffffffc000000ffULL },
	{ 39,	64,	30,	0xfffffffc000001ffULL },
	{ 40,	64,	30,	0xfffffffc000003ffULL },
	{ 41,	64,	30,	0xfffffffc000007ffULL },
	{ 42,	64,	30,	0xfffffffc00000fffULL },
	{ 43,	64,	30,	0xfffffffc00001fffULL },
	{ 44,	64,	30,	0xfffffffc00003fffULL },
	{ 45,	64,	30,	0xfffffffc00007fffULL },
	{ 46,	64,	30,	0xfffffffc0000ffffULL },
	{ 47,	64,	30,	0xfffffffc0001ffffULL },
	{ 48,	64,	30,	0xfffffffc0003ffffULL },
	{ 49,	64,	30,	0xfffffffc0007ffffULL },
	{ 50,	64,	30,	0xfffffffc000fffffULL },
	{ 51,	64,	30,	0xfffffffc001fffffULL },
	{ 52,	64,	30,	0xfffffffc003fffffULL },
	{ 53,	64,	30,	0xfffffffc007fffffULL },
	{ 54,	64,	30,	0xfffffffc00ffffffULL },
	{ 55,	64,	30,	0xfffffffc01ffffffULL },
	{ 56,	64,	30,	0xfffffffc03ffffffULL },
	{ 57,	64,	30,	0xfffffffc07ffffffULL },
	{ 58,	64,	30,	0xfffffffc0fffffffULL },
	{ 59,	64,	30,	0xfffffffc1fffffffULL },
	{ 60,	64,	30,	0xfffffffc3fffffffULL },
	{ 61,	64,	30,	0xfffffffc7fffffffULL },
	{ 30,	32,	30,	0xfffffffcfffffffcULL },
	{ 62,	64,	30,	0xfffffffcffffffffULL },
	{ 31,	32,	30,	0xfffffffdfffffffdULL },
	{ 63,	64,	30,	0xfffffffdffffffffULL },
	{ 31,	64,	31,	0xfffffffe00000000ULL },
	{ 32,	64,	31,	0xfffffffe00000001ULL },
	{ 33,	64,	31,	0xfffffffe00000003ULL },
	{ 34,	64,	31,	0xfffffffe00000007ULL },
	{ 35,	64,	31,	0xfffffffe0000000fULL },
	{ 36,	64,	31,	0xfffffffe0000001fULL },
	{ 37,	64,	31,	0xfffffffe0000003fULL },
	{ 38,	64,	31,	0xfffffffe0000007fULL },
	{ 39,	64,	31,	0xfffffffe000000ffULL },
	{ 40,	64,	31,	0xfffffffe000001ffULL },
	{ 41,	64,	31,	0xfffffffe000003ffULL },
	{ 42,	64,	31,	0xfffffffe000007ffULL },
	{ 43,	64,	31,	0xfffffffe00000fffULL },
	{ 44,	64,	31,	0xfffffffe00001fffULL },
	{ 45,	64,	31,	0xfffffffe00003fffULL },
	{ 46,	64,	31,	0xfffffffe00007fffULL },
	{ 47,	64,	31,	0xfffffffe0000ffffULL },
	{ 48,	64,	31,	0xfffffffe0001ffffULL },
	{ 49,	64,	31,	0xfffffffe0003ffffULL },
	{ 50,	64,	31,	0xfffffffe0007ffffULL },
	{ 51,	64,	31,	0xfffffffe000fffffULL },
	{ 52,	64,	31,	0xfffffffe001fffffULL },
	{ 53,	64,	31,	0xfffffffe003fffffULL },
	{ 54,	64,	31,	0xfffffffe007fffffULL },
	{ 55,	64,	31,	0xfffffffe00ffffffULL },
	{ 56,	64,	31,	0xfffffffe01ffffffULL },
	{ 57,	64,	31,	0xfffffffe03ffffffULL },
	{ 58,	64,	31,	0xfffffffe07ffffffULL },
	{ 59,	64,	31,	0xfffffffe0fffffffULL },
	{ 60,	64,	31,	0xfffffffe1fffffffULL },
	{ 61,	64,	31,	0xfffffffe3fffffffULL },
	{ 62,	64,	31,	0xfffffffe7fffffffULL },
	{ 31,	32,	31,	0xfffffffefffffffeULL },
	{ 63,	64,	31,	0xfffffffeffffffffULL },
	{ 32,	64,	32,	0xffffffff00000000ULL },
	{ 33,	64,	32,	0xffffffff00000001ULL },
	{ 34,	64,	32,	0xffffffff00000003ULL },
	{ 35,	64,	32,	0xffffffff00000007ULL },
	{ 36,	64,	32,	0xffffffff0000000fULL },
	{ 37,	64,	32,	0xffffffff0000001fULL },
	{ 38,	64,	32,	0xffffffff0000003fULL },
	{ 39,	64,	32,	0xffffffff0000007fULL },
	{ 40,	64,	32,	0xffffffff000000ffULL },
	{ 41,	64,	32,	0xffffffff000001ffULL },
	{ 42,	64,	32,	0xffffffff000003ffULL },
	{ 43,	64,	32,	0xffffffff000007ffULL },
	{ 44,	64,	32,	0xffffffff00000fffULL },
	{ 45,	64,	32,	0xffffffff00001fffULL },
	{ 46,	64,	32,	0xffffffff00003fffULL },
	{ 47,	64,	32,	0xffffffff00007fffULL },
	{ 48,	64,	32,	0xffffffff0000ffffULL },
	{ 49,	64,	32,	0xffffffff0001ffffULL },
	{ 50,	64,	32,	0xffffffff0003ffffULL },
	{ 51,	64,	32,	0xffffffff0007ffffULL },
	{ 52,	64,	32,	0xffffffff000fffffULL },
	{ 53,	64,	32,	0xffffffff001fffffULL },
	{ 54,	64,	32,	0xffffffff003fffffULL },
	{ 55,	64,	32,	0xffffffff007fffffULL },
	{ 56,	64,	32,	0xffffffff00ffffffULL },
	{ 57,	64,	32,	0xffffffff01ffffffULL },
	{ 58,	64,	32,	0xffffffff03ffffffULL },
	{ 59,	64,	32,	0xffffffff07ffffffULL },
	{ 60,	64,	32,	0xffffffff0fffffffULL },
	{ 61,	64,	32,	0xffffffff1fffffffULL },
	{ 62,	64,	32,	0xffffffff3fffffffULL },
	{ 63,	64,	32,	0xffffffff7fffffffULL },
	{ 33,	64,	33,	0xffffffff80000000ULL },
	{ 34,	64,	33,	0xffffffff80000001ULL },
	{ 35,	64,	33,	0xffffffff80000003ULL },
	{ 36,	64,	33,	0xffffffff80000007ULL },
	{ 37,	64,	33,	0xffffffff8000000fULL },
	{ 38,	64,	33,	0xffffffff8000001fULL },
	{ 39,	64,	33,	0xffffffff8000003fULL },
	{ 40,	64,	33,	0xffffffff8000007fULL },
	{ 41,	64,	33,	0xffffffff800000ffULL },
	{ 42,	64,	33,	0xffffffff800001ffULL },
	{ 43,	64,	33,	0xffffffff800003ffULL },
	{ 44,	64,	33,	0xffffffff800007ffULL },
	{ 45,	64,	33,	0xffffffff80000fffULL },
	{ 46,	64,	33,	0xffffffff80001fffULL },
	{ 47,	64,	33,	0xffffffff80003fffULL },
	{ 48,	64,	33,	0xffffffff80007fffULL },
	{ 49,	64,	33,	0xffffffff8000ffffULL },
	{ 50,	64,	33,	0xffffffff8001ffffULL },
	{ 51,	64,	33,	0xffffffff8003ffffULL },
	{ 52,	64,	33,	0xffffffff8007ffffULL },
	{ 53,	64,	33,	0xffffffff800fffffULL },
	{ 54,	64,	33,	0xffffffff801fffffULL },
	{ 55,	64,	33,	0xffffffff803fffffULL },
	{ 56,	64,	33,	0xffffffff807fffffULL },
	{ 57,	64,	33,	0xffffffff80ffffffULL },
	{ 58,	64,	33,	0xffffffff81ffffffULL },
	{ 59,	64,	33,	0xffffffff83ffffffULL },
	{ 60,	64,	33,	0xffffffff87ffffffULL },
	{ 61,	64,	33,	0xffffffff8fffffffULL },
	{ 62,	64,	33,	0xffffffff9fffffffULL },
	{ 63,	64,	33,	0xffffffffbfffffffULL },
	{ 34,	64,	34,	0xffffffffc0000000ULL },
	{ 35,	64,	34,	0xffffffffc0000001ULL },
	{ 36,	64,	34,	0xffffffffc0000003ULL },
	{ 37,	64,	34,	0xffffffffc0000007ULL },
	{ 38,	64,	34,	0xffffffffc000000fULL },
	{ 39,	64,	34,	0xffffffffc000001fULL },
	{ 40,	64,	34,	0xffffffffc000003fULL },
	{ 41,	64,	34,	0xffffffffc000007fULL },
	{ 42,	64,	34,	0xffffffffc00000ffULL },
	{ 43,	64,	34,	0xffffffffc00001ffULL },
	{ 44,	64,	34,	0xffffffffc00003ffULL },
	{ 45,	64,	34,	0xffffffffc00007ffULL },
	{ 46,	64,	34,	0xffffffffc0000fffULL },
	{ 47,	64,	34,	0xffffffffc0001fffULL },
	{ 48,	64,	34,	0xffffffffc0003fffULL },
	{ 49,	64,	34,	0xffffffffc0007fffULL },
	{ 50,	64,	34,	0xffffffffc000ffffULL },
	{ 51,	64,	34,	0xffffffffc001ffffULL },
	{ 52,	64,	34,	0xffffffffc003ffffULL },
	{ 53,	64,	34,	0xffffffffc007ffffULL },
	{ 54,	64,	34,	0xffffffffc00fffffULL },
	{ 55,	64,	34,	0xffffffffc01fffffULL },
	{ 56,	64,	34,	0xffffffffc03fffffULL },
	{ 57,	64,	34,	0xffffffffc07fffffULL },
	{ 58,	64,	34,	0xffffffffc0ffffffULL },
	{ 59,	64,	34,	0xffffffffc1ffffffULL },
	{ 60,	64,	34,	0xffffffffc3ffffffULL },
	{ 61,	64,	34,	0xffffffffc7ffffffULL },
	{ 62,	64,	34,	0xffffffffcfffffffULL },
	{ 63,	64,	34,	0xffffffffdfffffffULL },
	{ 35,	64,	35,	0xffffffffe0000000ULL },
	{ 36,	64,	35,	0xffffffffe0000001ULL },
	{ 37,	64,	35,	0xffffffffe0000003ULL },
	{ 38,	64,	35,	0xffffffffe0000007ULL },
	{ 39,	64,	35,	0xffffffffe000000fULL },
	{ 40,	64,	35,	0xffffffffe000001fULL },
	{ 41,	64,	35,	0xffffffffe000003fULL },
	{ 42,	64,	35,	0xffffffffe000007fULL },
	{ 43,	64,	35,	0xffffffffe00000ffULL },
	{ 44,	64,	35,	0xffffffffe00001ffULL },
	{ 45,	64,	35,	0xffffffffe00003ffULL },
	{ 46,	64,	35,	0xffffffffe00007ffULL },
	{ 47,	64,	35,	0xffffffffe0000fffULL },
	{ 48,	64,	35,	0xffffffffe0001fffULL },
	{ 49,	64,	35,	0xffffffffe0003fffULL },
	{ 50,	64,	35,	0xffffffffe0007fffULL },
	{ 51,	64,	35,	0xffffffffe000ffffULL },
	{ 52,	64,	35,	0xffffffffe001ffffULL },
	{ 53,	64,	35,	0xffffffffe003ffffULL },
	{ 54,	64,	35,	0xffffffffe007ffffULL },
	{ 55,	64,	35,	0xffffffffe00fffffULL },
	{ 56,	64,	35,	0xffffffffe01fffffULL },
	{ 57,	64,	35,	0xffffffffe03fffffULL },
	{ 58,	64,	35,	0xffffffffe07fffffULL },
	{ 59,	64,	35,	0xffffffffe0ffffffULL },
	{ 60,	64,	35,	0xffffffffe1ffffffULL },
	{ 61,	64,	35,	0xffffffffe3ffffffULL },
	{ 62,	64,	35,	0xffffffffe7ffffffULL },
	{ 63,	64,	35,	0xffffffffefffffffULL },
	{ 36,	64,	36,	0xfffffffff0000000ULL },
	{ 37,	64,	36,	0xfffffffff0000001ULL },
	{ 38,	64,	36,	0xfffffffff0000003ULL },
	{ 39,	64,	36,	0xfffffffff0000007ULL },
	{ 40,	64,	36,	0xfffffffff000000fULL },
	{ 41,	64,	36,	0xfffffffff000001fULL },
	{ 42,	64,	36,	0xfffffffff000003fULL },
	{ 43,	64,	36,	0xfffffffff000007fULL },
	{ 44,	64,	36,	0xfffffffff00000ffULL },
	{ 45,	64,	36,	0xfffffffff00001ffULL },
	{ 46,	64,	36,	0xfffffffff00003ffULL },
	{ 47,	64,	36,	0xfffffffff00007ffULL },
	{ 48,	64,	36,	0xfffffffff0000fffULL },
	{ 49,	64,	36,	0xfffffffff0001fffULL },
	{ 50,	64,	36,	0xfffffffff0003fffULL },
	{ 51,	64,	36,	0xfffffffff0007fffULL },
	{ 52,	64,	36,	0xfffffffff000ffffULL },
	{ 53,	64,	36,	0xfffffffff001ffffULL },
	{ 54,	64,	36,	0xfffffffff003ffffULL },
	{ 55,	64,	36,	0xfffffffff007ffffULL },
	{ 56,	64,	36,	0xfffffffff00fffffULL },
	{ 57,	64,	36,	0xfffffffff01fffffULL },
	{ 58,	64,	36,	0xfffffffff03fffffULL },
	{ 59,	64,	36,	0xfffffffff07fffffULL },
	{ 60,	64,	36,	0xfffffffff0ffffffULL },
	{ 61,	64,	36,	0xfffffffff1ffffffULL },
	{ 62,	64,	36,	0xfffffffff3ffffffULL },
	{ 63,	64,	36,	0xfffffffff7ffffffULL },
	{ 37,	64,	37,	0xfffffffff8000000ULL },
	{ 38,	64,	37,	0xfffffffff8000001ULL },
	{ 39,	64,	37,	0xfffffffff8000003ULL },
	{ 40,	64,	37,	0xfffffffff8000007ULL },
	{ 41,	64,	37,	0xfffffffff800000fULL },
	{ 42,	64,	37,	0xfffffffff800001fULL },
	{ 43,	64,	37,	0xfffffffff800003fULL },
	{ 44,	64,	37,	0xfffffffff800007fULL },
	{ 45,	64,	37,	0xfffffffff80000ffULL },
	{ 46,	64,	37,	0xfffffffff80001ffULL },
	{ 47,	64,	37,	0xfffffffff80003ffULL },
	{ 48,	64,	37,	0xfffffffff80007ffULL },
	{ 49,	64,	37,	0xfffffffff8000fffULL },
	{ 50,	64,	37,	0xfffffffff8001fffULL },
	{ 51,	64,	37,	0xfffffffff8003fffULL },
	{ 52,	64,	37,	0xfffffffff8007fffULL },
	{ 53,	64,	37,	0xfffffffff800ffffULL },
	{ 54,	64,	37,	0xfffffffff801ffffULL },
	{ 55,	64,	37,	0xfffffffff803ffffULL },
	{ 56,	64,	37,	0xfffffffff807ffffULL },
	{ 57,	64,	37,	0xfffffffff80fffffULL },
	{ 58,	64,	37,	0xfffffffff81fffffULL },
	{ 59,	64,	37,	0xfffffffff83fffffULL },
	{ 60,	64,	37,	0xfffffffff87fffffULL },
	{ 61,	64,	37,	0xfffffffff8ffffffULL },
	{ 62,	64,	37,	0xfffffffff9ffffffULL },
	{ 63,	64,	37,	0xfffffffffbffffffULL },
	{ 38,	64,	38,	0xfffffffffc000000ULL },
	{ 39,	64,	38,	0xfffffffffc000001ULL },
	{ 40,	64,	38,	0xfffffffffc000003ULL },
	{ 41,	64,	38,	0xfffffffffc000007ULL },
	{ 42,	64,	38,	0xfffffffffc00000fULL },
	{ 43,	64,	38,	0xfffffffffc00001fULL },
	{ 44,	64,	38,	0xfffffffffc00003fULL },
	{ 45,	64,	38,	0xfffffffffc00007fULL },
	{ 46,	64,	38,	0xfffffffffc0000ffULL },
	{ 47,	64,	38,	0xfffffffffc0001ffULL },
	{ 48,	64,	38,	0xfffffffffc0003ffULL },
	{ 49,	64,	38,	0xfffffffffc0007ffULL },
	{ 50,	64,	38,	0xfffffffffc000fffULL },
	{ 51,	64,	38,	0xfffffffffc001fffULL },
	{ 52,	64,	38,	0xfffffffffc003fffULL },
	{ 53,	64,	38,	0xfffffffffc007fffULL },
	{ 54,	64,	38,	0xfffffffffc00ffffULL },
	{ 55,	64,	38,	0xfffffffffc01ffffULL },
	{ 56,	64,	38,	0xfffffffffc03ffffULL },
	{ 57,	64,	38,	0xfffffffffc07ffffULL },
	{ 58,	64,	38,	0xfffffffffc0fffffULL },
	{ 59,	64,	38,	0xfffffffffc1fffffULL },
	{ 60,	64,	38,	0xfffffffffc3fffffULL },
	{ 61,	64,	38,	0xfffffffffc7fffffULL },
	{ 62,	64,	38,	0xfffffffffcffffffULL },
	{ 63,	64,	38,	0xfffffffffdffffffULL },
	{ 39,	64,	39,	0xfffffffffe000000ULL },
	{ 40,	64,	39,	0xfffffffffe000001ULL },
	{ 41,	64,	39,	0xfffffffffe000003ULL },
	{ 42,	64,	39,	0xfffffffffe000007ULL },
	{ 43,	64,	39,	0xfffffffffe00000fULL },
	{ 44,	64,	39,	0xfffffffffe00001fULL },
	{ 45,	64,	39,	0xfffffffffe00003fULL },
	{ 46,	64,	39,	0xfffffffffe00007fULL },
	{ 47,	64,	39,	0xfffffffffe0000ffULL },
	{ 48,	64,	39,	0xfffffffffe0001ffULL },
	{ 49,	64,	39,	0xfffffffffe0003ffULL },
	{ 50,	64,	39,	0xfffffffffe0007ffULL },
	{ 51,	64,	39,	0xfffffffffe000fffULL },
	{ 52,	64,	39,	0xfffffffffe001fffULL },
	{ 53,	64,	39,	0xfffffffffe003fffULL },
	{ 54,	64,	39,	0xfffffffffe007fffULL },
	{ 55,	64,	39,	0xfffffffffe00ffffULL },
	{ 56,	64,	39,	0xfffffffffe01ffffULL },
	{ 57,	64,	39,	0xfffffffffe03ffffULL },
	{ 58,	64,	39,	0xfffffffffe07ffffULL },
	{ 59,	64,	39,	0xfffffffffe0fffffULL },
	{ 60,	64,	39,	0xfffffffffe1fffffULL },
	{ 61,	64,	39,	0xfffffffffe3fffffULL },
	{ 62,	64,	39,	0xfffffffffe7fffffULL },
	{ 63,	64,	39,	0xfffffffffeffffffULL },
	{ 40,	64,	40,	0xffffffffff000000ULL },
	{ 41,	64,	40,	0xffffffffff000001ULL },
	{ 42,	64,	40,	0xffffffffff000003ULL },
	{ 43,	64,	40,	0xffffffffff000007ULL },
	{ 44,	64,	40,	0xffffffffff00000fULL },
	{ 45,	64,	40,	0xffffffffff00001fULL },
	{ 46,	64,	40,	0xffffffffff00003fULL },
	{ 47,	64,	40,	0xffffffffff00007fULL },
	{ 48,	64,	40,	0xffffffffff0000ffULL },
	{ 49,	64,	40,	0xffffffffff0001ffULL },
	{ 50,	64,	40,	0xffffffffff0003ffULL },
	{ 51,	64,	40,	0xffffffffff0007ffULL },
	{ 52,	64,	40,	0xffffffffff000fffULL },
	{ 53,	64,	40,	0xffffffffff001fffULL },
	{ 54,	64,	40,	0xffffffffff003fffULL },
	{ 55,	64,	40,	0xffffffffff007fffULL },
	{ 56,	64,	40,	0xffffffffff00ffffULL },
	{ 57,	64,	40,	0xffffffffff01ffffULL },
	{ 58,	64,	40,	0xffffffffff03ffffULL },
	{ 59,	64,	40,	0xffffffffff07ffffULL },
	{ 60,	64,	40,	0xffffffffff0fffffULL },
	{ 61,	64,	40,	0xffffffffff1fffffULL },
	{ 62,	64,	40,	0xffffffffff3fffffULL },
	{ 63,	64,	40,	0xffffffffff7fffffULL },
	{ 41,	64,	41,	0xffffffffff800000ULL },
	{ 42,	64,	41,	0xffffffffff800001ULL },
	{ 43,	64,	41,	0xffffffffff800003ULL },
	{ 44,	64,	41,	0xffffffffff800007ULL },
	{ 45,	64,	41,	0xffffffffff80000fULL },
	{ 46,	64,	41,	0xffffffffff80001fULL },
	{ 47,	64,	41,	0xffffffffff80003fULL },
	{ 48,	64,	41,	0xffffffffff80007fULL },
	{ 49,	64,	41,	0xffffffffff8000ffULL },
	{ 50,	64,	41,	0xffffffffff8001ffULL },
	{ 51,	64,	41,	0xffffffffff8003ffULL },
	{ 52,	64,	41,	0xffffffffff8007ffULL },
	{ 53,	64,	41,	0xffffffffff800fffULL },
	{ 54,	64,	41,	0xffffffffff801fffULL },
	{ 55,	64,	41,	0xffffffffff803fffULL },
	{ 56,	64,	41,	0xffffffffff807fffULL },
	{ 57,	64,	41,	0xffffffffff80ffffULL },
	{ 58,	64,	41,	0xffffffffff81ffffULL },
	{ 59,	64,	41,	0xffffffffff83ffffULL },
	{ 60,	64,	41,	0xffffffffff87ffffULL },
	{ 61,	64,	41,	0xffffffffff8fffffULL },
	{ 62,	64,	41,	0xffffffffff9fffffULL },
	{ 63,	64,	41,	0xffffffffffbfffffULL },
	{ 42,	64,	42,	0xffffffffffc00000ULL },
	{ 43,	64,	42,	0xffffffffffc00001ULL },
	{ 44,	64,	42,	0xffffffffffc00003ULL },
	{ 45,	64,	42,	0xffffffffffc00007ULL },
	{ 46,	64,	42,	0xffffffffffc0000fULL },
	{ 47,	64,	42,	0xffffffffffc0001fULL },
	{ 48,	64,	42,	0xffffffffffc0003fULL },
	{ 49,	64,	42,	0xffffffffffc0007fULL },
	{ 50,	64,	42,	0xffffffffffc000ffULL },
	{ 51,	64,	42,	0xffffffffffc001ffULL },
	{ 52,	64,	42,	0xffffffffffc003ffULL },
	{ 53,	64,	42,	0xffffffffffc007ffULL },
	{ 54,	64,	42,	0xffffffffffc00fffULL },
	{ 55,	64,	42,	0xffffffffffc01fffULL },
	{ 56,	64,	42,	0xffffffffffc03fffULL },
	{ 57,	64,	42,	0xffffffffffc07fffULL },
	{ 58,	64,	42,	0xffffffffffc0ffffULL },
	{ 59,	64,	42,	0xffffffffffc1ffffULL },
	{ 60,	64,	42,	0xffffffffffc3ffffULL },
	{ 61,	64,	42,	0xffffffffffc7ffffULL },
	{ 62,	64,	42,	0xffffffffffcfffffULL },
	{ 63,	64,	42,	0xffffffffffdfffffULL },
	{ 43,	64,	43,	0xffffffffffe00000ULL },
	{ 44,	64,	43,	0xffffffffffe00001ULL },
	{ 45,	64,	43,	0xffffffffffe00003ULL },
	{ 46,	64,	43,	0xffffffffffe00007ULL },
	{ 47,	64,	43,	0xffffffffffe0000fULL },
	{ 48,	64,	43,	0xffffffffffe0001fULL },
	{ 49,	64,	43,	0xffffffffffe0003fULL },
	{ 50,	64,	43,	0xffffffffffe0007fULL },
	{ 51,	64,	43,	0xffffffffffe000ffULL },
	{ 52,	64,	43,	0xffffffffffe001ffULL },
	{ 53,	64,	43,	0xffffffffffe003ffULL },
	{ 54,	64,	43,	0xffffffffffe007ffULL },
	{ 55,	64,	43,	0xffffffffffe00fffULL },
	{ 56,	64,	43,	0xffffffffffe01fffULL },
	{ 57,	64,	43,	0xffffffffffe03fffULL },
	{ 58,	64,	43,	0xffffffffffe07fffULL },
	{ 59,	64,	43,	0xffffffffffe0ffffULL },
	{ 60,	64,	43,	0xffffffffffe1ffffULL },
	{ 61,	64,	43,	0xffffffffffe3ffffULL },
	{ 62,	64,	43,	0xffffffffffe7ffffULL },
	{ 63,	64,	43,	0xffffffffffefffffULL },
	{ 44,	64,	44,	0xfffffffffff00000ULL },
	{ 45,	64,	44,	0xfffffffffff00001ULL },
	{ 46,	64,	44,	0xfffffffffff00003ULL },
	{ 47,	64,	44,	0xfffffffffff00007ULL },
	{ 48,	64,	44,	0xfffffffffff0000fULL },
	{ 49,	64,	44,	0xfffffffffff0001fULL },
	{ 50,	64,	44,	0xfffffffffff0003fULL },
	{ 51,	64,	44,	0xfffffffffff0007fULL },
	{ 52,	64,	44,	0xfffffffffff000ffULL },
	{ 53,	64,	44,	0xfffffffffff001ffULL },
	{ 54,	64,	44,	0xfffffffffff003ffULL },
	{ 55,	64,	44,	0xfffffffffff007ffULL },
	{ 56,	64,	44,	0xfffffffffff00fffULL },
	{ 57,	64,	44,	0xfffffffffff01fffULL },
	{ 58,	64,	44,	0xfffffffffff03fffULL },
	{ 59,	64,	44,	0xfffffffffff07fffULL },
	{ 60,	64,	44,	0xfffffffffff0ffffULL },
	{ 61,	64,	44,	0xfffffffffff1ffffULL },
	{ 62,	64,	44,	0xfffffffffff3ffffULL },
	{ 63,	64,	44,	0xfffffffffff7ffffULL },
	{ 45,	64,	45,	0xfffffffffff80000ULL },
	{ 46,	64,	45,	0xfffffffffff80001ULL },
	{ 47,	64,	45,	0xfffffffffff80003ULL },
	{ 48,	64,	45,	0xfffffffffff80007ULL },
	{ 49,	64,	45,	0xfffffffffff8000fULL },
	{ 50,	64,	45,	0xfffffffffff8001fULL },
	{ 51,	64,	45,	0xfffffffffff8003fULL },
	{ 52,	64,	45,	0xfffffffffff8007fULL },
	{ 53,	64,	45,	0xfffffffffff800ffULL },
	{ 54,	64,	45,	0xfffffffffff801ffULL },
	{ 55,	64,	45,	0xfffffffffff803ffULL },
	{ 56,	64,	45,	0xfffffffffff807ffULL },
	{ 57,	64,	45,	0xfffffffffff80fffULL },
	{ 58,	64,	45,	0xfffffffffff81fffULL },
	{ 59,	64,	45,	0xfffffffffff83fffULL },
	{ 60,	64,	45,	0xfffffffffff87fffULL },
	{ 61,	64,	45,	0xfffffffffff8ffffULL },
	{ 62,	64,	45,	0xfffffffffff9ffffULL },
	{ 63,	64,	45,	0xfffffffffffbffffULL },
	{ 46,	64,	46,	0xfffffffffffc0000ULL },
	{ 47,	64,	46,	0xfffffffffffc0001ULL },
	{ 48,	64,	46,	0xfffffffffffc0003ULL },
	{ 49,	64,	46,	0xfffffffffffc0007ULL },
	{ 50,	64,	46,	0xfffffffffffc000fULL },
	{ 51,	64,	46,	0xfffffffffffc001fULL },
	{ 52,	64,	46,	0xfffffffffffc003fULL },
	{ 53,	64,	46,	0xfffffffffffc007fULL },
	{ 54,	64,	46,	0xfffffffffffc00ffULL },
	{ 55,	64,	46,	0xfffffffffffc01ffULL },
	{ 56,	64,	46,	0xfffffffffffc03ffULL },
	{ 57,	64,	46,	0xfffffffffffc07ffULL },
	{ 58,	64,	46,	0xfffffffffffc0fffULL },
	{ 59,	64,	46,	0xfffffffffffc1fffULL },
	{ 60,	64,	46,	0xfffffffffffc3fffULL },
	{ 61,	64,	46,	0xfffffffffffc7fffULL },
	{ 62,	64,	46,	0xfffffffffffcffffULL },
	{ 63,	64,	46,	0xfffffffffffdffffULL },
	{ 47,	64,	47,	0xfffffffffffe0000ULL },
	{ 48,	64,	47,	0xfffffffffffe0001ULL },
	{ 49,	64,	47,	0xfffffffffffe0003ULL },
	{ 50,	64,	47,	0xfffffffffffe0007ULL },
	{ 51,	64,	47,	0xfffffffffffe000fULL },
	{ 52,	64,	47,	0xfffffffffffe001fULL },
	{ 53,	64,	47,	0xfffffffffffe003fULL },
	{ 54,	64,	47,	0xfffffffffffe007fULL },
	{ 55,	64,	47,	0xfffffffffffe00ffULL },
	{ 56,	64,	47,	0xfffffffffffe01ffULL },
	{ 57,	64,	47,	0xfffffffffffe03ffULL },
	{ 58,	64,	47,	0xfffffffffffe07ffULL },
	{ 59,	64,	47,	0xfffffffffffe0fffULL },
	{ 60,	64,	47,	0xfffffffffffe1fffULL },
	{ 61,	64,	47,	0xfffffffffffe3fffULL },
	{ 62,	64,	47,	0xfffffffffffe7fffULL },
	{ 63,	64,	47,	0xfffffffffffeffffULL },
	{ 48,	64,	48,	0xffffffffffff0000ULL },
	{ 49,	64,	48,	0xffffffffffff0001ULL },
	{ 50,	64,	48,	0xffffffffffff0003ULL },
	{ 51,	64,	48,	0xffffffffffff0007ULL },
	{ 52,	64,	48,	0xffffffffffff000fULL },
	{ 53,	64,	48,	0xffffffffffff001fULL },
	{ 54,	64,	48,	0xffffffffffff003fULL },
	{ 55,	64,	48,	0xffffffffffff007fULL },
	{ 56,	64,	48,	0xffffffffffff00ffULL },
	{ 57,	64,	48,	0xffffffffffff01ffULL },
	{ 58,	64,	48,	0xffffffffffff03ffULL },
	{ 59,	64,	48,	0xffffffffffff07ffULL },
	{ 60,	64,	48,	0xffffffffffff0fffULL },
	{ 61,	64,	48,	0xffffffffffff1fffULL },
	{ 62,	64,	48,	0xffffffffffff3fffULL },
	{ 63,	64,	48,	0xffffffffffff7fffULL },
	{ 49,	64,	49,	0xffffffffffff8000ULL },
	{ 50,	64,	49,	0xffffffffffff8001ULL },
	{ 51,	64,	49,	0xffffffffffff8003ULL },
	{ 52,	64,	49,	0xffffffffffff8007ULL },
	{ 53,	64,	49,	0xffffffffffff800fULL },
	{ 54,	64,	49,	0xffffffffffff801fULL },
	{ 55,	64,	49,	0xffffffffffff803fULL },
	{ 56,	64,	49,	0xffffffffffff807fULL },
	{ 57,	64,	49,	0xffffffffffff80ffULL },
	{ 58,	64,	49,	0xffffffffffff81ffULL },
	{ 59,	64,	49,	0xffffffffffff83ffULL },
	{ 60,	64,	49,	0xffffffffffff87ffULL },
	{ 61,	64,	49,	0xffffffffffff8fffULL },
	{ 62,	64,	49,	0xffffffffffff9fffULL },
	{ 63,	64,	49,	0xffffffffffffbfffULL },
	{ 50,	64,	50,	0xffffffffffffc000ULL },
	{ 51,	64,	50,	0xffffffffffffc001ULL },
	{ 52,	64,	50,	0xffffffffffffc003ULL },
	{ 53,	64,	50,	0xffffffffffffc007ULL },
	{ 54,	64,	50,	0xffffffffffffc00fULL },
	{ 55,	64,	50,	0xffffffffffffc01fULL },
	{ 56,	64,	50,	0xffffffffffffc03fULL },
	{ 57,	64,	50,	0xffffffffffffc07fULL },
	{ 58,	64,	50,	0xffffffffffffc0ffULL },
	{ 59,	64,	50,	0xffffffffffffc1ffULL },
	{ 60,	64,	50,	0xffffffffffffc3ffULL },
	{ 61,	64,	50,	0xffffffffffffc7ffULL },
	{ 62,	64,	50,	0xffffffffffffcfffULL },
	{ 63,	64,	50,	0xffffffffffffdfffULL },
	{ 51,	64,	51,	0xffffffffffffe000ULL },
	{ 52,	64,	51,	0xffffffffffffe001ULL },
	{ 53,	64,	51,	0xffffffffffffe003ULL },
	{ 54,	64,	51,	0xffffffffffffe007ULL },
	{ 55,	64,	51,	0xffffffffffffe00fULL },
	{ 56,	64,	51,	0xffffffffffffe01fULL },
	{ 57,	64,	51,	0xffffffffffffe03fULL },
	{ 58,	64,	51,	0xffffffffffffe07fULL },
	{ 59,	64,	51,	0xffffffffffffe0ffULL },
	{ 60,	64,	51,	0xffffffffffffe1ffULL },
	{ 61,	64,	51,	0xffffffffffffe3ffULL },
	{ 62,	64,	51,	0xffffffffffffe7ffULL },
	{ 63,	64,	51,	0xffffffffffffefffULL },
	{ 52,	64,	52,	0xfffffffffffff000ULL },
	{ 53,	64,	52,	0xfffffffffffff001ULL },
	{ 54,	64,	52,	0xfffffffffffff003ULL },
	{ 55,	64,	52,	0xfffffffffffff007ULL },
	{ 56,	64,	52,	0xfffffffffffff00fULL },
	{ 57,	64,	52,	0xfffffffffffff01fULL },
	{ 58,	64,	52,	0xfffffffffffff03fULL },
	{ 59,	64,	52,	0xfffffffffffff07fULL },
	{ 60,	64,	52,	0xfffffffffffff0ffULL },
	{ 61,	64,	52,	0xfffffffffffff1ffULL },
	{ 62,	64,	52,	0xfffffffffffff3ffULL },
	{ 63,	64,	52,	0xfffffffffffff7ffULL },
	{ 53,	64,	53,	0xfffffffffffff800ULL },
	{ 54,	64,	53,	0xfffffffffffff801ULL },
	{ 55,	64,	53,	0xfffffffffffff803ULL },
	{ 56,	64,	53,	0xfffffffffffff807ULL },
	{ 57,	64,	53,	0xfffffffffffff80fULL },
	{ 58,	64,	53,	0xfffffffffffff81fULL },
	{ 59,	64,	53,	0xfffffffffffff83fULL },
	{ 60,	64,	53,	0xfffffffffffff87fULL },
	{ 61,	64,	53,	0xfffffffffffff8ffULL },
	{ 62,	64,	53,	0xfffffffffffff9ffULL },
	{ 63,	64,	53,	0xfffffffffffffbffULL },
	{ 54,	64,	54,	0xfffffffffffffc00ULL },
	{ 55,	64,	54,	0xfffffffffffffc01ULL },
	{ 56,	64,	54,	0xfffffffffffffc03ULL },
	{ 57,	64,	54,	0xfffffffffffffc07ULL },
	{ 58,	64,	54,	0xfffffffffffffc0fULL },
	{ 59,	64,	54,	0xfffffffffffffc1fULL },
	{ 60,	64,	54,	0xfffffffffffffc3fULL },
	{ 61,	64,	54,	0xfffffffffffffc7fULL },
	{ 62,	64,	54,	0xfffffffffffffcffULL },
	{ 63,	64,	54,	0xfffffffffffffdffULL },
	{ 55,	64,	55,	0xfffffffffffffe00ULL },
	{ 56,	64,	55,	0xfffffffffffffe01ULL },
	{ 57,	64,	55,	0xfffffffffffffe03ULL },
	{ 58,	64,	55,	0xfffffffffffffe07ULL },
	{ 59,	64,	55,	0xfffffffffffffe0fULL },
	{ 60,	64,	55,	0xfffffffffffffe1fULL },
	{ 61,	64,	55,	0xfffffffffffffe3fULL },
	{ 62,	64,	55,	0xfffffffffffffe7fULL },
	{ 63,	64,	55,	0xfffffffffffffeffULL },
	{ 56,	64,	56,	0xffffffffffffff00ULL },
	{ 57,	64,	56,	0xffffffffffffff01ULL },
	{ 58,	64,	56,	0xffffffffffffff03ULL },
	{ 59,	64,	56,	0xffffffffffffff07ULL },
	{ 60,	64,	56,	0xffffffffffffff0fULL },
	{ 61,	64,	56,	0xffffffffffffff1fULL },
	{ 62,	64,	56,	0xffffffffffffff3fULL },
	{ 63,	64,	56,	0xffffffffffffff7fULL },
	{ 57,	64,	57,	0xffffffffffffff80ULL },
	{ 58,	64,	57,	0xffffffffffffff81ULL },
	{ 59,	64,	57,	0xffffffffffffff83ULL },
	{ 60,	64,	57,	0xffffffffffffff87ULL },
	{ 61,	64,	57,	0xffffffffffffff8fULL },
	{ 62,	64,	57,	0xffffffffffffff9fULL },
	{ 63,	64,	57,	0xffffffffffffffbfULL },
	{ 58,	64,	58,	0xffffffffffffffc0ULL },
	{ 59,	64,	58,	0xffffffffffffffc1ULL },
	{ 60,	64,	58,	0xffffffffffffffc3ULL },
	{ 61,	64,	58,	0xffffffffffffffc7ULL },
	{ 62,	64,	58,	0xffffffffffffffcfULL },
	{ 63,	64,	58,	0xffffffffffffffdfULL },
	{ 59,	64,	59,	0xffffffffffffffe0ULL },
	{ 60,	64,	59,	0xffffffffffffffe1ULL },
	{ 61,	64,	59,	0xffffffffffffffe3ULL },
	{ 62,	64,	59,	0xffffffffffffffe7ULL },
	{ 63,	64,	59,	0xffffffffffffffefULL },
	{ 60,	64,	60,	0xfffffffffffffff0ULL },
	{ 61,	64,	60,	0xfffffffffffffff1ULL },
	{ 62,	64,	60,	0xfffffffffffffff3ULL },
	{ 63,	64,	60,	0xfffffffffffffff7ULL },
	{ 61,	64,	61,	0xfffffffffffffff8ULL },
	{ 62,	64,	61,	0xfffffffffffffff9ULL },
	{ 63,	64,	61,	0xfffffffffffffffbULL },
	{ 62,	64,	62,	0xfffffffffffffffcULL },
	{ 63,	64,	62,	0xfffffffffffffffdULL },
	{ 63,	64,	63,	0xfffffffffffffffeULL },
};

Mask*
findmask(uvlong v)
{
	int top, bot, mid;
	Mask *m;

	bot = 0;
	top = nelem(bitmasks);
	while(bot < top){
		mid = (bot+top)/2;
		m = &bitmasks[mid];
		if(v == m->v)
			return m;
		if(v < m->v)
			top = mid;
		else
			bot = mid+1;
	}
	return nil;
}
