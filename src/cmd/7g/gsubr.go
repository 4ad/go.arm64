// Derived from Inferno utils/6c/txt.c
// http://code.google.com/p/inferno-os/source/browse/utils/6c/txt.c
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

package main

import (
	"cmd/internal/obj"
	"cmd/internal/obj/arm64"
	"fmt"
)
import "cmd/internal/gc"

// TODO(rsc): Can make this bigger if we move
// the text segment up higher in 6l for all GOOS.
// At the same time, can raise StackBig in ../../runtime/stack.h.
var unmappedzero int64 = 4096

var resvd = []int{
	arm64.REGTMP,
	arm64.REGG,
	arm64.REGZERO,
	arm64.REGSP,
	arm64.FREGZERO,
	arm64.FREGHALF,
	arm64.FREGONE,
	arm64.FREGTWO,
}

func ginit() {
	for i := 0; i < len(reg); i++ {
		reg[i] = 1
	}
	for i := 0; i < arm64.NREG+arm64.NFREG; i++ {
		reg[i] = 0
	}

	for i := 0; i < len(resvd); i++ {
		reg[resvd[i]-arm64.REG_R0]++
	}
}

var regpc [len(reg)]uint32

func gclean() {
	for i := int(0); i < len(resvd); i++ {
		reg[resvd[i]-arm64.REG_R0]--
	}

	for i := int(0); i < len(reg); i++ {
		if reg[i] != 0 {
			gc.Yyerror("reg %v left allocated, %p\n", obj.Rconv(i+arm64.REG_R0), regpc[i])
		}
	}
}

func anyregalloc() bool {
	var j int

	for i := int(0); i < len(reg); i++ {
		if reg[i] == 0 {
			goto ok
		}
		for j = 0; j < len(resvd); j++ {
			if resvd[j] == i {
				goto ok
			}
		}
		return true
	ok:
	}

	return false
}

/*
 * allocate register of type t, leave in n.
 * if o != N, o is desired fixed register.
 * caller must regfree(n).
 */
func regalloc(n *gc.Node, t *gc.Type, o *gc.Node) {
	if t == nil {
		gc.Fatal("regalloc: t nil")
	}
	et := int(int(gc.Simtype[t.Etype]))

	if gc.Debug['r'] != 0 {
		fixfree := int(0)
		fltfree := int(0)
		for i := int(arm64.REG_R0); i < arm64.REG_F31; i++ {
			if reg[i-arm64.REG_R0] == 0 {
				if i < arm64.REG_F0 {
					fixfree++
				} else {
					fltfree++
				}
			}
		}

		fmt.Printf("regalloc fix %d flt %d free\n", fixfree, fltfree)
	}

	var i int
	switch et {
	case gc.TINT8,
		gc.TUINT8,
		gc.TINT16,
		gc.TUINT16,
		gc.TINT32,
		gc.TUINT32,
		gc.TINT64,
		gc.TUINT64,
		gc.TPTR32,
		gc.TPTR64,
		gc.TBOOL:
		if o != nil && o.Op == gc.OREGISTER {
			i = int(o.Val.U.Reg)
			if i >= arm64.REGMIN && i <= arm64.REGMAX {
				goto out
			}
		}

		for i = arm64.REGMIN; i <= arm64.REGMAX; i++ {
			if reg[i-arm64.REG_R0] == 0 {
				regpc[i-arm64.REG_R0] = uint32(obj.Getcallerpc(&n))
				goto out
			}
		}

		gc.Flusherrors()
		for i := int(arm64.REG_R0); i < arm64.REG_R0+arm64.NREG; i++ {
			fmt.Printf("R%d %p\n", i, regpc[i-arm64.REG_R0])
		}
		gc.Fatal("out of fixed registers")

	case gc.TFLOAT32,
		gc.TFLOAT64:
		if o != nil && o.Op == gc.OREGISTER {
			i = int(o.Val.U.Reg)
			if i >= arm64.FREGMIN && i <= arm64.FREGMAX {
				goto out
			}
		}

		for i = arm64.FREGMIN; i <= arm64.FREGMAX; i++ {
			if reg[i-arm64.REG_R0] == 0 {
				regpc[i-arm64.REG_R0] = uint32(obj.Getcallerpc(&n))
				goto out
			}
		}

		gc.Flusherrors()
		for i := int(arm64.REG_F0); i < arm64.REG_F0+arm64.NREG; i++ {
			fmt.Printf("F%d %p\n", i, regpc[i-arm64.REG_R0])
		}
		gc.Fatal("out of floating registers")

	case gc.TCOMPLEX64,
		gc.TCOMPLEX128:
		gc.Tempname(n, t)
		return
	}

	gc.Fatal("regalloc: unknown type %v", gc.Tconv(t, 0))
	return

out:
	reg[i-arm64.REG_R0]++
	gc.Nodreg(n, t, i)
}

func regfree(n *gc.Node) {
	if n.Op == gc.ONAME {
		return
	}
	if n.Op != gc.OREGISTER && n.Op != gc.OINDREG {
		gc.Fatal("regfree: not a register")
	}
	i := int(int(n.Val.U.Reg) - arm64.REG_R0)
	if i == arm64.REGSP-arm64.REG_R0 {
		return
	}
	if i < 0 || i >= len(reg) {
		gc.Fatal("regfree: reg out of range")
	}
	if reg[i] <= 0 {
		gc.Fatal("regfree: reg not allocated")
	}
	reg[i]--
	if reg[i] == 0 {
		regpc[i] = 0
	}
}

/*
 * generate
 *	as $c, n
 */
func ginscon(as int, c int64, n2 *gc.Node) {
	var n1 gc.Node

	gc.Nodconst(&n1, gc.Types[gc.TINT64], c)

	if as != arm64.AMOVD && (c < -arm64.BIG || c > arm64.BIG) {
		// cannot have more than 16-bit of immediate in ADD, etc.
		// instead, MOV into register first.
		var ntmp gc.Node
		regalloc(&ntmp, gc.Types[gc.TINT64], nil)

		gins(arm64.AMOVD, &n1, &ntmp)
		gins(as, &ntmp, n2)
		regfree(&ntmp)
		return
	}

	gins(as, &n1, n2)
}

/*
 * generate
 *	as n, $c (CMP)
 */
func ginscon2(as int, n2 *gc.Node, c int64) {
	var n1 gc.Node

	gc.Nodconst(&n1, gc.Types[gc.TINT64], c)

	switch as {
	default:
		gc.Fatal("ginscon2")

	case arm64.ACMP:
		if -arm64.BIG <= c && c <= arm64.BIG {
			gins(as, n2, &n1)
			return
		}
	}

	// MOV n1 into register first
	var ntmp gc.Node
	regalloc(&ntmp, gc.Types[gc.TINT64], nil)

	gins(arm64.AMOVD, &n1, &ntmp)
	gins(as, n2, &ntmp)
	regfree(&ntmp)
}

/*
 * set up nodes representing 2^63
 */
var bigi gc.Node

var bigf gc.Node

var bignodes_did int

func bignodes() {
	if bignodes_did != 0 {
		return
	}
	bignodes_did = 1

	gc.Nodconst(&bigi, gc.Types[gc.TUINT64], 1)
	gc.Mpshiftfix(bigi.Val.U.Xval, 63)

	bigf = bigi
	bigf.Type = gc.Types[gc.TFLOAT64]
	bigf.Val.Ctype = gc.CTFLT
	bigf.Val.U.Fval = new(gc.Mpflt)
	gc.Mpmovefixflt(bigf.Val.U.Fval, bigi.Val.U.Xval)
}

/*
 * generate move:
 *	t = f
 * hard part is conversions.
 */
func gmove(f *gc.Node, t *gc.Node) {
	if gc.Debug['M'] != 0 {
		fmt.Printf("gmove %v -> %v\n", gc.Nconv(f, obj.FmtLong), gc.Nconv(t, obj.FmtLong))
	}

	ft := int(gc.Simsimtype(f.Type))
	tt := int(gc.Simsimtype(t.Type))
	cvt := (*gc.Type)(t.Type)

	if gc.Iscomplex[ft] || gc.Iscomplex[tt] {
		gc.Complexmove(f, t)
		return
	}

	// cannot have two memory operands
	var r2 gc.Node
	var r1 gc.Node
	var a int
	if gc.Ismem(f) && gc.Ismem(t) {
		goto hard
	}

	// convert constant to desired type
	if f.Op == gc.OLITERAL {
		var con gc.Node
		switch tt {
		default:
			gc.Convconst(&con, t.Type, &f.Val)

		case gc.TINT32,
			gc.TINT16,
			gc.TINT8:
			var con gc.Node
			gc.Convconst(&con, gc.Types[gc.TINT64], &f.Val)
			var r1 gc.Node
			regalloc(&r1, con.Type, t)
			gins(arm64.AMOVD, &con, &r1)
			gmove(&r1, t)
			regfree(&r1)
			return

		case gc.TUINT32,
			gc.TUINT16,
			gc.TUINT8:
			var con gc.Node
			gc.Convconst(&con, gc.Types[gc.TUINT64], &f.Val)
			var r1 gc.Node
			regalloc(&r1, con.Type, t)
			gins(arm64.AMOVD, &con, &r1)
			gmove(&r1, t)
			regfree(&r1)
			return
		}

		f = &con
		ft = tt // so big switch will choose a simple mov

		// constants can't move directly to memory.
		if gc.Ismem(t) {
			goto hard
		}
	}

	// float constants come from memory.
	//if(isfloat[tt])
	//	goto hard;

	// 64-bit immediates are also from memory.
	//if(isint[tt])
	//	goto hard;
	//// 64-bit immediates are really 32-bit sign-extended
	//// unless moving into a register.
	//if(isint[tt]) {
	//	if(mpcmpfixfix(con.val.u.xval, minintval[TINT32]) < 0)
	//		goto hard;
	//	if(mpcmpfixfix(con.val.u.xval, maxintval[TINT32]) > 0)
	//		goto hard;
	//}

	// value -> value copy, only one memory operand.
	// figure out the instruction to use.
	// break out of switch for one-instruction gins.
	// goto rdst for "destination must be register".
	// goto hard for "convert to cvt type first".
	// otherwise handle and return.

	switch uint32(ft)<<16 | uint32(tt) {
	default:
		gc.Fatal("gmove %v -> %v", gc.Tconv(f.Type, obj.FmtLong), gc.Tconv(t.Type, obj.FmtLong))

		/*
		 * integer copy and truncate
		 */
	case gc.TINT8<<16 | gc.TINT8, // same size
		gc.TUINT8<<16 | gc.TINT8,
		gc.TINT16<<16 | gc.TINT8,
		// truncate
		gc.TUINT16<<16 | gc.TINT8,
		gc.TINT32<<16 | gc.TINT8,
		gc.TUINT32<<16 | gc.TINT8,
		gc.TINT64<<16 | gc.TINT8,
		gc.TUINT64<<16 | gc.TINT8:
		a = arm64.AMOVB

	case gc.TINT8<<16 | gc.TUINT8, // same size
		gc.TUINT8<<16 | gc.TUINT8,
		gc.TINT16<<16 | gc.TUINT8,
		// truncate
		gc.TUINT16<<16 | gc.TUINT8,
		gc.TINT32<<16 | gc.TUINT8,
		gc.TUINT32<<16 | gc.TUINT8,
		gc.TINT64<<16 | gc.TUINT8,
		gc.TUINT64<<16 | gc.TUINT8:
		a = arm64.AMOVBU

	case gc.TINT16<<16 | gc.TINT16, // same size
		gc.TUINT16<<16 | gc.TINT16,
		gc.TINT32<<16 | gc.TINT16,
		// truncate
		gc.TUINT32<<16 | gc.TINT16,
		gc.TINT64<<16 | gc.TINT16,
		gc.TUINT64<<16 | gc.TINT16:
		a = arm64.AMOVH

	case gc.TINT16<<16 | gc.TUINT16, // same size
		gc.TUINT16<<16 | gc.TUINT16,
		gc.TINT32<<16 | gc.TUINT16,
		// truncate
		gc.TUINT32<<16 | gc.TUINT16,
		gc.TINT64<<16 | gc.TUINT16,
		gc.TUINT64<<16 | gc.TUINT16:
		a = arm64.AMOVHU

	case gc.TINT32<<16 | gc.TINT32, // same size
		gc.TUINT32<<16 | gc.TINT32,
		gc.TINT64<<16 | gc.TINT32,
		// truncate
		gc.TUINT64<<16 | gc.TINT32:
		a = arm64.AMOVW

	case gc.TINT32<<16 | gc.TUINT32, // same size
		gc.TUINT32<<16 | gc.TUINT32,
		gc.TINT64<<16 | gc.TUINT32,
		gc.TUINT64<<16 | gc.TUINT32:
		a = arm64.AMOVWU

	case gc.TINT64<<16 | gc.TINT64, // same size
		gc.TINT64<<16 | gc.TUINT64,
		gc.TUINT64<<16 | gc.TINT64,
		gc.TUINT64<<16 | gc.TUINT64:
		a = arm64.AMOVD

		/*
		 * integer up-conversions
		 */
	case gc.TINT8<<16 | gc.TINT16, // sign extend int8
		gc.TINT8<<16 | gc.TUINT16,
		gc.TINT8<<16 | gc.TINT32,
		gc.TINT8<<16 | gc.TUINT32,
		gc.TINT8<<16 | gc.TINT64,
		gc.TINT8<<16 | gc.TUINT64:
		a = arm64.AMOVB

		goto rdst

	case gc.TUINT8<<16 | gc.TINT16, // zero extend uint8
		gc.TUINT8<<16 | gc.TUINT16,
		gc.TUINT8<<16 | gc.TINT32,
		gc.TUINT8<<16 | gc.TUINT32,
		gc.TUINT8<<16 | gc.TINT64,
		gc.TUINT8<<16 | gc.TUINT64:
		a = arm64.AMOVBU

		goto rdst

	case gc.TINT16<<16 | gc.TINT32, // sign extend int16
		gc.TINT16<<16 | gc.TUINT32,
		gc.TINT16<<16 | gc.TINT64,
		gc.TINT16<<16 | gc.TUINT64:
		a = arm64.AMOVH

		goto rdst

	case gc.TUINT16<<16 | gc.TINT32, // zero extend uint16
		gc.TUINT16<<16 | gc.TUINT32,
		gc.TUINT16<<16 | gc.TINT64,
		gc.TUINT16<<16 | gc.TUINT64:
		a = arm64.AMOVHU

		goto rdst

	case gc.TINT32<<16 | gc.TINT64, // sign extend int32
		gc.TINT32<<16 | gc.TUINT64:
		a = arm64.AMOVW

		goto rdst

	case gc.TUINT32<<16 | gc.TINT64, // zero extend uint32
		gc.TUINT32<<16 | gc.TUINT64:
		a = arm64.AMOVWU

		goto rdst

		//warn("gmove: convert float to int not implemented: %N -> %N\n", f, t);
	//return;
	// algorithm is:
	//	if small enough, use native float64 -> int64 conversion.
	//	otherwise, subtract 2^63, convert, and add it back.
	/*
	* float to integer
	 */
	case gc.TFLOAT32<<16 | gc.TINT32,
		gc.TFLOAT64<<16 | gc.TINT32,
		gc.TFLOAT32<<16 | gc.TINT64,
		gc.TFLOAT64<<16 | gc.TINT64,
		gc.TFLOAT32<<16 | gc.TINT16,
		gc.TFLOAT32<<16 | gc.TINT8,
		gc.TFLOAT32<<16 | gc.TUINT16,
		gc.TFLOAT32<<16 | gc.TUINT8,
		gc.TFLOAT64<<16 | gc.TINT16,
		gc.TFLOAT64<<16 | gc.TINT8,
		gc.TFLOAT64<<16 | gc.TUINT16,
		gc.TFLOAT64<<16 | gc.TUINT8,
		gc.TFLOAT32<<16 | gc.TUINT32,
		gc.TFLOAT64<<16 | gc.TUINT32,
		gc.TFLOAT32<<16 | gc.TUINT64,
		gc.TFLOAT64<<16 | gc.TUINT64:
		bignodes()

		var r1 gc.Node
		regalloc(&r1, gc.Types[ft], f)
		gmove(f, &r1)
		if tt == gc.TUINT64 {
			regalloc(&r2, gc.Types[gc.TFLOAT64], nil)
			gmove(&bigf, &r2)
			gins(arm64.AFCMPU, &r1, &r2)
			p1 := (*obj.Prog)(gc.Gbranch(optoas(gc.OLT, gc.Types[gc.TFLOAT64]), nil, +1))
			gins(arm64.AFSUBD, &r2, &r1)
			gc.Patch(p1, gc.Pc)
			regfree(&r2)
		}

		regalloc(&r2, gc.Types[gc.TFLOAT64], nil)
		var r3 gc.Node
		regalloc(&r3, gc.Types[gc.TINT64], t)
		gins(arm64.AFCTIDZ, &r1, &r2)
		p1 := (*obj.Prog)(gins(arm64.AFMOVD, &r2, nil))
		p1.To.Type = obj.TYPE_MEM
		p1.To.Reg = arm64.REGSP
		p1.To.Offset = -8
		p1 = gins(arm64.AMOVD, nil, &r3)
		p1.From.Type = obj.TYPE_MEM
		p1.From.Reg = arm64.REGSP
		p1.From.Offset = -8
		regfree(&r2)
		regfree(&r1)
		if tt == gc.TUINT64 {
			p1 := (*obj.Prog)(gc.Gbranch(optoas(gc.OLT, gc.Types[gc.TFLOAT64]), nil, +1)) // use CR0 here again
			gc.Nodreg(&r1, gc.Types[gc.TINT64], arm64.REGTMP)
			gins(arm64.AMOVD, &bigi, &r1)
			gins(arm64.AADD, &r1, &r3)
			gc.Patch(p1, gc.Pc)
		}

		gmove(&r3, t)
		regfree(&r3)
		return

		//warn("gmove: convert int to float not implemented: %N -> %N\n", f, t);
	//return;
	// algorithm is:
	//	if small enough, use native int64 -> uint64 conversion.
	//	otherwise, halve (rounding to odd?), convert, and double.
	/*
	 * integer to float
	 */
	case gc.TINT32<<16 | gc.TFLOAT32,
		gc.TINT32<<16 | gc.TFLOAT64,
		gc.TINT64<<16 | gc.TFLOAT32,
		gc.TINT64<<16 | gc.TFLOAT64,
		gc.TINT16<<16 | gc.TFLOAT32,
		gc.TINT16<<16 | gc.TFLOAT64,
		gc.TINT8<<16 | gc.TFLOAT32,
		gc.TINT8<<16 | gc.TFLOAT64,
		gc.TUINT16<<16 | gc.TFLOAT32,
		gc.TUINT16<<16 | gc.TFLOAT64,
		gc.TUINT8<<16 | gc.TFLOAT32,
		gc.TUINT8<<16 | gc.TFLOAT64,
		gc.TUINT32<<16 | gc.TFLOAT32,
		gc.TUINT32<<16 | gc.TFLOAT64,
		gc.TUINT64<<16 | gc.TFLOAT32,
		gc.TUINT64<<16 | gc.TFLOAT64:
		bignodes()

		var r1 gc.Node
		regalloc(&r1, gc.Types[gc.TINT64], nil)
		gmove(f, &r1)
		if ft == gc.TUINT64 {
			gc.Nodreg(&r2, gc.Types[gc.TUINT64], arm64.REGTMP)
			gmove(&bigi, &r2)
			gins(arm64.ACMPU, &r1, &r2)
			p1 := (*obj.Prog)(gc.Gbranch(optoas(gc.OLT, gc.Types[gc.TUINT64]), nil, +1))
			p2 := (*obj.Prog)(gins(arm64.ALSR, nil, &r1))
			p2.From.Type = obj.TYPE_CONST
			p2.From.Offset = 1
			gc.Patch(p1, gc.Pc)
		}

		regalloc(&r2, gc.Types[gc.TFLOAT64], t)
		p1 := (*obj.Prog)(gins(arm64.AMOVD, &r1, nil))
		p1.To.Type = obj.TYPE_MEM
		p1.To.Reg = arm64.REGSP
		p1.To.Offset = -8
		p1 = gins(arm64.AFMOVD, nil, &r2)
		p1.From.Type = obj.TYPE_MEM
		p1.From.Reg = arm64.REGSP
		p1.From.Offset = -8
		gins(arm64.AFCFID, &r2, &r2)
		regfree(&r1)
		if ft == gc.TUINT64 {
			p1 := (*obj.Prog)(gc.Gbranch(optoas(gc.OLT, gc.Types[gc.TUINT64]), nil, +1)) // use CR0 here again
			gc.Nodreg(&r1, gc.Types[gc.TFLOAT64], arm64.FREGTWO)
			gins(arm64.AFMULD, &r1, &r2)
			gc.Patch(p1, gc.Pc)
		}

		gmove(&r2, t)
		regfree(&r2)
		return

		/*
		 * float to float
		 */
	case gc.TFLOAT32<<16 | gc.TFLOAT32:
		a = arm64.AFMOVS

	case gc.TFLOAT64<<16 | gc.TFLOAT64:
		a = arm64.AFMOVD

	case gc.TFLOAT32<<16 | gc.TFLOAT64:
		a = arm64.AFMOVS
		goto rdst

	case gc.TFLOAT64<<16 | gc.TFLOAT32:
		a = arm64.AFRSP
		goto rdst
	}

	gins(a, f, t)
	return

	// requires register destination
rdst:
	regalloc(&r1, t.Type, t)

	gins(a, f, &r1)
	gmove(&r1, t)
	regfree(&r1)
	return

	// requires register intermediate
hard:
	regalloc(&r1, cvt, t)

	gmove(f, &r1)
	gmove(&r1, t)
	regfree(&r1)
	return
}

/*
 * generate one instruction:
 *	as f, t
 */
func gins(as int, f *gc.Node, t *gc.Node) *obj.Prog {
	// TODO(austin): Add self-move test like in 6g (but be careful
	// of truncation moves)

	af := obj.Addr(obj.Addr{})

	at := obj.Addr(obj.Addr{})
	if f != nil {
		gc.Naddr(f, &af, 1)
	}
	if t != nil {
		gc.Naddr(t, &at, 1)
	}
	p := (*obj.Prog)(gc.Prog(as))
	if f != nil {
		p.From = af
	}
	if t != nil {
		p.To = at
	}
	if gc.Debug['g'] != 0 {
		fmt.Printf("%v\n", p)
	}

	w := int32(0)
	switch as {
	case arm64.AMOVB,
		arm64.AMOVBU,
		arm64.AMOVBZU:
		w = 1

	case arm64.AMOVH,
		arm64.AMOVHU,
		arm64.AMOVHZU:
		w = 2

	case arm64.AMOVW,
		arm64.AMOVWU,
		arm64.AMOVWZU:
		w = 4

	case arm64.AMOVD,
		arm64.AMOVDU:
		if af.Type == obj.TYPE_CONST || af.Type == obj.TYPE_ADDR {
			break
		}
		w = 8
	}

	if w != 0 && ((f != nil && af.Width < int64(w)) || (t != nil && at.Type != obj.TYPE_REG && at.Width > int64(w))) {
		gc.Dump("f", f)
		gc.Dump("t", t)
		gc.Fatal("bad width: %v (%d, %d)\n", p, af.Width, at.Width)
	}

	return p
}

func fixlargeoffset(n *gc.Node) {
	if n == nil {
		return
	}
	if n.Op != gc.OINDREG {
		return
	}
	if n.Val.U.Reg == arm64.REGSP { // stack offset cannot be large
		return
	}
	if n.Xoffset != int64(int32(n.Xoffset)) {
		// TODO(minux): offset too large, move into R31 and add to R31 instead.
		// this is used only in test/fixedbugs/issue6036.go.
		gc.Fatal("offset too large: %v", gc.Nconv(n, 0))

		a := gc.Node(*n)
		a.Op = gc.OREGISTER
		a.Type = gc.Types[gc.Tptr]
		a.Xoffset = 0
		gc.Cgen_checknil(&a)
		ginscon(optoas(gc.OADD, gc.Types[gc.Tptr]), n.Xoffset, &a)
		n.Xoffset = 0
	}
}

/*
 * return Axxx for Oxxx on type t.
 */
func optoas(op int, t *gc.Type) int {
	if t == nil {
		gc.Fatal("optoas: t is nil")
	}

	a := int(obj.AXXX)
	switch uint32(op)<<16 | uint32(gc.Simtype[t.Etype]) {
	default:
		gc.Fatal("optoas: no entry for op=%v type=%v", gc.Oconv(int(op), 0), gc.Tconv(t, 0))

	case gc.OEQ<<16 | gc.TBOOL,
		gc.OEQ<<16 | gc.TINT8,
		gc.OEQ<<16 | gc.TUINT8,
		gc.OEQ<<16 | gc.TINT16,
		gc.OEQ<<16 | gc.TUINT16,
		gc.OEQ<<16 | gc.TINT32,
		gc.OEQ<<16 | gc.TUINT32,
		gc.OEQ<<16 | gc.TINT64,
		gc.OEQ<<16 | gc.TUINT64,
		gc.OEQ<<16 | gc.TPTR32,
		gc.OEQ<<16 | gc.TPTR64,
		gc.OEQ<<16 | gc.TFLOAT32,
		gc.OEQ<<16 | gc.TFLOAT64:
		a = arm64.ABEQ

	case gc.ONE<<16 | gc.TBOOL,
		gc.ONE<<16 | gc.TINT8,
		gc.ONE<<16 | gc.TUINT8,
		gc.ONE<<16 | gc.TINT16,
		gc.ONE<<16 | gc.TUINT16,
		gc.ONE<<16 | gc.TINT32,
		gc.ONE<<16 | gc.TUINT32,
		gc.ONE<<16 | gc.TINT64,
		gc.ONE<<16 | gc.TUINT64,
		gc.ONE<<16 | gc.TPTR32,
		gc.ONE<<16 | gc.TPTR64,
		gc.ONE<<16 | gc.TFLOAT32,
		gc.ONE<<16 | gc.TFLOAT64:
		a = arm64.ABNE

	case gc.OLT<<16 | gc.TINT8,
		gc.OLT<<16 | gc.TINT16,
		gc.OLT<<16 | gc.TINT32,
		gc.OLT<<16 | gc.TINT64:
		a = arm64.ABLT
		
		
	case gc.OLT<<16 | gc.TUINT8,
		gc.OLT<<16 | gc.TUINT16,
		gc.OLT<<16 | gc.TUINT32,
		gc.OLT<<16 | gc.TUINT64,
		gc.OLT<<16 | gc.TFLOAT32,
		gc.OLT<<16 | gc.TFLOAT64:
		a = arm64.ABLO

	case gc.OLE<<16 | gc.TINT8,
		gc.OLE<<16 | gc.TINT16,
		gc.OLE<<16 | gc.TINT32,
		gc.OLE<<16 | gc.TINT64:
		a = arm64.ABLE
	
	case gc.OLE<<16 | gc.TUINT8,
		gc.OLE<<16 | gc.TUINT16,
		gc.OLE<<16 | gc.TUINT32,
		gc.OLE<<16 | gc.TUINT64,
		gc.OLE<<16 | gc.TFLOAT32,
		gc.OLE<<16 | gc.TFLOAT64:
		a = arm64.ABLS

	case gc.OGT<<16 | gc.TINT8,
		gc.OGT<<16 | gc.TINT16,
		gc.OGT<<16 | gc.TINT32,
		gc.OGT<<16 | gc.TINT64,
		gc.OGT<<16 | gc.TUINT8,
		gc.OGT<<16 | gc.TUINT16,
		gc.OGT<<16 | gc.TUINT32,
		gc.OGT<<16 | gc.TUINT64,
		gc.OGT<<16 | gc.TFLOAT32,
		gc.OGT<<16 | gc.TFLOAT64:
		a = arm64.ABGT

	case gc.OGE<<16 | gc.TINT8,
		gc.OGE<<16 | gc.TINT16,
		gc.OGE<<16 | gc.TINT32,
		gc.OGE<<16 | gc.TINT64,
		gc.OGE<<16 | gc.TUINT8,
		gc.OGE<<16 | gc.TUINT16,
		gc.OGE<<16 | gc.TUINT32,
		gc.OGE<<16 | gc.TUINT64,
		gc.OGE<<16 | gc.TFLOAT32,
		gc.OGE<<16 | gc.TFLOAT64:
		a = arm64.ABGE

	case gc.OCMP<<16 | gc.TBOOL,
		gc.OCMP<<16 | gc.TINT8,
		gc.OCMP<<16 | gc.TINT16,
		gc.OCMP<<16 | gc.TINT32,
		gc.OCMP<<16 | gc.TPTR32,
		gc.OCMP<<16 | gc.TINT64:
		a = arm64.ACMP

	case gc.OCMP<<16 | gc.TUINT8,
		gc.OCMP<<16 | gc.TUINT16,
		gc.OCMP<<16 | gc.TUINT32,
		gc.OCMP<<16 | gc.TUINT64,
		gc.OCMP<<16 | gc.TPTR64:
		a = arm64.ACMPU

	case gc.OCMP<<16 | gc.TFLOAT32,
		gc.OCMP<<16 | gc.TFLOAT64:
		a = arm64.AFCMPU

	case gc.OAS<<16 | gc.TBOOL,
		gc.OAS<<16 | gc.TINT8:
		a = arm64.AMOVB

	case gc.OAS<<16 | gc.TUINT8:
		a = arm64.AMOVBU

	case gc.OAS<<16 | gc.TINT16:
		a = arm64.AMOVH

	case gc.OAS<<16 | gc.TUINT16:
		a = arm64.AMOVHU

	case gc.OAS<<16 | gc.TINT32:
		a = arm64.AMOVW

	case gc.OAS<<16 | gc.TUINT32,
		gc.OAS<<16 | gc.TPTR32:
		a = arm64.AMOVWU

	case gc.OAS<<16 | gc.TINT64,
		gc.OAS<<16 | gc.TUINT64,
		gc.OAS<<16 | gc.TPTR64:
		a = arm64.AMOVD

	case gc.OAS<<16 | gc.TFLOAT32:
		a = arm64.AFMOVS

	case gc.OAS<<16 | gc.TFLOAT64:
		a = arm64.AFMOVD

	case gc.OADD<<16 | gc.TINT8,
		gc.OADD<<16 | gc.TUINT8,
		gc.OADD<<16 | gc.TINT16,
		gc.OADD<<16 | gc.TUINT16,
		gc.OADD<<16 | gc.TINT32,
		gc.OADD<<16 | gc.TUINT32,
		gc.OADD<<16 | gc.TPTR32,
		gc.OADD<<16 | gc.TINT64,
		gc.OADD<<16 | gc.TUINT64,
		gc.OADD<<16 | gc.TPTR64:
		a = arm64.AADD

	case gc.OADD<<16 | gc.TFLOAT32:
		a = arm64.AFADDS

	case gc.OADD<<16 | gc.TFLOAT64:
		a = arm64.AFADDD

	case gc.OSUB<<16 | gc.TINT8,
		gc.OSUB<<16 | gc.TUINT8,
		gc.OSUB<<16 | gc.TINT16,
		gc.OSUB<<16 | gc.TUINT16,
		gc.OSUB<<16 | gc.TINT32,
		gc.OSUB<<16 | gc.TUINT32,
		gc.OSUB<<16 | gc.TPTR32,
		gc.OSUB<<16 | gc.TINT64,
		gc.OSUB<<16 | gc.TUINT64,
		gc.OSUB<<16 | gc.TPTR64:
		a = arm64.ASUB

	case gc.OSUB<<16 | gc.TFLOAT32:
		a = arm64.AFSUBS

	case gc.OSUB<<16 | gc.TFLOAT64:
		a = arm64.AFSUBD

	case gc.OMINUS<<16 | gc.TINT8,
		gc.OMINUS<<16 | gc.TUINT8,
		gc.OMINUS<<16 | gc.TINT16,
		gc.OMINUS<<16 | gc.TUINT16,
		gc.OMINUS<<16 | gc.TINT32,
		gc.OMINUS<<16 | gc.TUINT32,
		gc.OMINUS<<16 | gc.TPTR32,
		gc.OMINUS<<16 | gc.TINT64,
		gc.OMINUS<<16 | gc.TUINT64,
		gc.OMINUS<<16 | gc.TPTR64:
		a = arm64.ANEG

	case gc.OAND<<16 | gc.TINT8,
		gc.OAND<<16 | gc.TUINT8,
		gc.OAND<<16 | gc.TINT16,
		gc.OAND<<16 | gc.TUINT16,
		gc.OAND<<16 | gc.TINT32,
		gc.OAND<<16 | gc.TUINT32,
		gc.OAND<<16 | gc.TPTR32,
		gc.OAND<<16 | gc.TINT64,
		gc.OAND<<16 | gc.TUINT64,
		gc.OAND<<16 | gc.TPTR64:
		a = arm64.AAND

	case gc.OOR<<16 | gc.TINT8,
		gc.OOR<<16 | gc.TUINT8,
		gc.OOR<<16 | gc.TINT16,
		gc.OOR<<16 | gc.TUINT16,
		gc.OOR<<16 | gc.TINT32,
		gc.OOR<<16 | gc.TUINT32,
		gc.OOR<<16 | gc.TPTR32,
		gc.OOR<<16 | gc.TINT64,
		gc.OOR<<16 | gc.TUINT64,
		gc.OOR<<16 | gc.TPTR64:
		a = arm64.AORR

	case gc.OXOR<<16 | gc.TINT8,
		gc.OXOR<<16 | gc.TUINT8,
		gc.OXOR<<16 | gc.TINT16,
		gc.OXOR<<16 | gc.TUINT16,
		gc.OXOR<<16 | gc.TINT32,
		gc.OXOR<<16 | gc.TUINT32,
		gc.OXOR<<16 | gc.TPTR32,
		gc.OXOR<<16 | gc.TINT64,
		gc.OXOR<<16 | gc.TUINT64,
		gc.OXOR<<16 | gc.TPTR64:
		a = arm64.AEOR

		// TODO(minux): handle rotates
	//case CASE(OLROT, TINT8):
	//case CASE(OLROT, TUINT8):
	//case CASE(OLROT, TINT16):
	//case CASE(OLROT, TUINT16):
	//case CASE(OLROT, TINT32):
	//case CASE(OLROT, TUINT32):
	//case CASE(OLROT, TPTR32):
	//case CASE(OLROT, TINT64):
	//case CASE(OLROT, TUINT64):
	//case CASE(OLROT, TPTR64):
	//	a = 0//???; RLDC?
	//	break;

	case gc.OLSH<<16 | gc.TINT8,
		gc.OLSH<<16 | gc.TUINT8,
		gc.OLSH<<16 | gc.TINT16,
		gc.OLSH<<16 | gc.TUINT16,
		gc.OLSH<<16 | gc.TINT32,
		gc.OLSH<<16 | gc.TUINT32,
		gc.OLSH<<16 | gc.TPTR32,
		gc.OLSH<<16 | gc.TINT64,
		gc.OLSH<<16 | gc.TUINT64,
		gc.OLSH<<16 | gc.TPTR64:
		a = arm64.ALSL

	case gc.ORSH<<16 | gc.TUINT8,
		gc.ORSH<<16 | gc.TUINT16,
		gc.ORSH<<16 | gc.TUINT32,
		gc.ORSH<<16 | gc.TPTR32,
		gc.ORSH<<16 | gc.TUINT64,
		gc.ORSH<<16 | gc.TPTR64:
		a = arm64.ALSR

	case gc.ORSH<<16 | gc.TINT8,
		gc.ORSH<<16 | gc.TINT16,
		gc.ORSH<<16 | gc.TINT32,
		gc.ORSH<<16 | gc.TINT64:
		a = arm64.AASR

		// TODO(minux): handle rotates
	//case CASE(ORROTC, TINT8):
	//case CASE(ORROTC, TUINT8):
	//case CASE(ORROTC, TINT16):
	//case CASE(ORROTC, TUINT16):
	//case CASE(ORROTC, TINT32):
	//case CASE(ORROTC, TUINT32):
	//case CASE(ORROTC, TINT64):
	//case CASE(ORROTC, TUINT64):
	//	a = 0//??? RLDC??
	//	break;

	case gc.OHMUL<<16 | gc.TINT64:
		a = arm64.AMULHD

	case gc.OHMUL<<16 | gc.TUINT64,
		gc.OHMUL<<16 | gc.TPTR64:
		a = arm64.AMULHDU

	case gc.OMUL<<16 | gc.TINT8,
		gc.OMUL<<16 | gc.TINT16,
		gc.OMUL<<16 | gc.TINT32,
		gc.OMUL<<16 | gc.TINT64:
		a = arm64.AMULLD

	case gc.OMUL<<16 | gc.TUINT8,
		gc.OMUL<<16 | gc.TUINT16,
		gc.OMUL<<16 | gc.TUINT32,
		gc.OMUL<<16 | gc.TPTR32,
		// don't use word multiply, the high 32-bit are undefined.
		// fallthrough
		gc.OMUL<<16 | gc.TUINT64,
		gc.OMUL<<16 | gc.TPTR64:
		a = arm64.AMULLD
		// for 64-bit multiplies, signedness doesn't matter.

	case gc.OMUL<<16 | gc.TFLOAT32:
		a = arm64.AFMULS

	case gc.OMUL<<16 | gc.TFLOAT64:
		a = arm64.AFMULD

	case gc.ODIV<<16 | gc.TINT8,
		gc.ODIV<<16 | gc.TINT16,
		gc.ODIV<<16 | gc.TINT32,
		gc.ODIV<<16 | gc.TINT64:
		a = arm64.ADIVD

	case gc.ODIV<<16 | gc.TUINT8,
		gc.ODIV<<16 | gc.TUINT16,
		gc.ODIV<<16 | gc.TUINT32,
		gc.ODIV<<16 | gc.TPTR32,
		gc.ODIV<<16 | gc.TUINT64,
		gc.ODIV<<16 | gc.TPTR64:
		a = arm64.ADIVDU

	case gc.ODIV<<16 | gc.TFLOAT32:
		a = arm64.AFDIVS

	case gc.ODIV<<16 | gc.TFLOAT64:
		a = arm64.AFDIV
	}

	return a
}

const (
	ODynam   = 1 << 0
	OAddable = 1 << 1
)

func xgen(n *gc.Node, a *gc.Node, o int) bool {
	// TODO(minux)

	return -1 != 0 /*TypeKind(100016)*/
}

func sudoclean() {
	return
}

/*
 * generate code to compute address of n,
 * a reference to a (perhaps nested) field inside
 * an array or struct.
 * return 0 on failure, 1 on success.
 * on success, leaves usable address in a.
 *
 * caller is responsible for calling sudoclean
 * after successful sudoaddable,
 * to release the register used for a.
 */
func sudoaddable(as int, n *gc.Node, a *obj.Addr) bool {
	// TODO(minux)

	*a = obj.Addr{}
	return false
}
