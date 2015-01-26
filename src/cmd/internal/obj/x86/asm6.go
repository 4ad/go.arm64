// Inferno utils/6l/span.c
// http://code.google.com/p/inferno-os/source/browse/utils/6l/span.c
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

package x86

import (
	"cmd/internal/obj"
	"fmt"
	"log"
	"strings"
)

// Instruction layout.

const (
	MaxAlign   = 32
	LoopAlign  = 16
	MaxLoopPad = 0
	FuncAlign  = 16
)

type Optab struct {
	as     int16
	ytab   []byte
	prefix uint8
	op     [23]uint8
}

type Movtab struct {
	as   int16
	ft   uint8
	tt   uint8
	code uint8
	op   [4]uint8
}

const (
	Yxxx = 0 + iota
	Ynone
	Yi0
	Yi1
	Yi8
	Ys32
	Yi32
	Yi64
	Yiauto
	Yal
	Ycl
	Yax
	Ycx
	Yrb
	Yrl
	Yrf
	Yf0
	Yrx
	Ymb
	Yml
	Ym
	Ybr
	Ycol
	Ycs
	Yss
	Yds
	Yes
	Yfs
	Ygs
	Ygdtr
	Yidtr
	Yldtr
	Ymsw
	Ytask
	Ycr0
	Ycr1
	Ycr2
	Ycr3
	Ycr4
	Ycr5
	Ycr6
	Ycr7
	Ycr8
	Ydr0
	Ydr1
	Ydr2
	Ydr3
	Ydr4
	Ydr5
	Ydr6
	Ydr7
	Ytr0
	Ytr1
	Ytr2
	Ytr3
	Ytr4
	Ytr5
	Ytr6
	Ytr7
	Yrl32
	Yrl64
	Ymr
	Ymm
	Yxr
	Yxm
	Ytls
	Ymax
	Zxxx = 0 + iota - 67
	Zlit
	Zlitm_r
	Z_rp
	Zbr
	Zcall
	Zcallindreg
	Zib_
	Zib_rp
	Zibo_m
	Zibo_m_xm
	Zil_
	Zil_rp
	Ziq_rp
	Zilo_m
	Ziqo_m
	Zjmp
	Zloop
	Zo_iw
	Zm_o
	Zm_r
	Zm2_r
	Zm_r_xm
	Zm_r_i_xm
	Zm_r_3d
	Zm_r_xm_nr
	Zr_m_xm_nr
	Zibm_r
	Zmb_r
	Zaut_r
	Zo_m
	Zo_m64
	Zpseudo
	Zr_m
	Zr_m_xm
	Zr_m_i_xm
	Zrp_
	Z_ib
	Z_il
	Zm_ibo
	Zm_ilo
	Zib_rr
	Zil_rr
	Zclr
	Zbyte
	Zmax
	Px     = 0
	P32    = 0x32
	Pe     = 0x66
	Pm     = 0x0f
	Pq     = 0xff
	Pb     = 0xfe
	Pf2    = 0xf2
	Pf3    = 0xf3
	Pq3    = 0x67
	Pw     = 0x48
	Py     = 0x80
	Rxf    = 1 << 9
	Rxt    = 1 << 8
	Rxw    = 1 << 3
	Rxr    = 1 << 2
	Rxx    = 1 << 1
	Rxb    = 1 << 0
	Maxand = 10
)

var ycover [Ymax * Ymax]uint8

var reg [D_NONE]int

var regrex [D_NONE + 1]int

var ynone = []uint8{
	Ynone,
	Ynone,
	Zlit,
	1,
	0,
}

var ytext = []uint8{
	Ymb,
	Yi64,
	Zpseudo,
	1,
	0,
}

var ynop = []uint8{
	Ynone,
	Ynone,
	Zpseudo,
	0,
	Ynone,
	Yiauto,
	Zpseudo,
	0,
	Ynone,
	Yml,
	Zpseudo,
	0,
	Ynone,
	Yrf,
	Zpseudo,
	0,
	Ynone,
	Yxr,
	Zpseudo,
	0,
	Yiauto,
	Ynone,
	Zpseudo,
	0,
	Yml,
	Ynone,
	Zpseudo,
	0,
	Yrf,
	Ynone,
	Zpseudo,
	0,
	Yxr,
	Ynone,
	Zpseudo,
	1,
	0,
}

var yfuncdata = []uint8{
	Yi32,
	Ym,
	Zpseudo,
	0,
	0,
}

var ypcdata = []uint8{
	Yi32,
	Yi32,
	Zpseudo,
	0,
	0,
}

var yxorb = []uint8{
	Yi32,
	Yal,
	Zib_,
	1,
	Yi32,
	Ymb,
	Zibo_m,
	2,
	Yrb,
	Ymb,
	Zr_m,
	1,
	Ymb,
	Yrb,
	Zm_r,
	1,
	0,
}

var yxorl = []uint8{
	Yi8,
	Yml,
	Zibo_m,
	2,
	Yi32,
	Yax,
	Zil_,
	1,
	Yi32,
	Yml,
	Zilo_m,
	2,
	Yrl,
	Yml,
	Zr_m,
	1,
	Yml,
	Yrl,
	Zm_r,
	1,
	0,
}

var yaddl = []uint8{
	Yi8,
	Yml,
	Zibo_m,
	2,
	Yi32,
	Yax,
	Zil_,
	1,
	Yi32,
	Yml,
	Zilo_m,
	2,
	Yrl,
	Yml,
	Zr_m,
	1,
	Yml,
	Yrl,
	Zm_r,
	1,
	0,
}

var yincb = []uint8{
	Ynone,
	Ymb,
	Zo_m,
	2,
	0,
}

var yincw = []uint8{
	Ynone,
	Yml,
	Zo_m,
	2,
	0,
}

var yincl = []uint8{
	Ynone,
	Yml,
	Zo_m,
	2,
	0,
}

var ycmpb = []uint8{
	Yal,
	Yi32,
	Z_ib,
	1,
	Ymb,
	Yi32,
	Zm_ibo,
	2,
	Ymb,
	Yrb,
	Zm_r,
	1,
	Yrb,
	Ymb,
	Zr_m,
	1,
	0,
}

var ycmpl = []uint8{
	Yml,
	Yi8,
	Zm_ibo,
	2,
	Yax,
	Yi32,
	Z_il,
	1,
	Yml,
	Yi32,
	Zm_ilo,
	2,
	Yml,
	Yrl,
	Zm_r,
	1,
	Yrl,
	Yml,
	Zr_m,
	1,
	0,
}

var yshb = []uint8{
	Yi1,
	Ymb,
	Zo_m,
	2,
	Yi32,
	Ymb,
	Zibo_m,
	2,
	Ycx,
	Ymb,
	Zo_m,
	2,
	0,
}

var yshl = []uint8{
	Yi1,
	Yml,
	Zo_m,
	2,
	Yi32,
	Yml,
	Zibo_m,
	2,
	Ycl,
	Yml,
	Zo_m,
	2,
	Ycx,
	Yml,
	Zo_m,
	2,
	0,
}

var ytestb = []uint8{
	Yi32,
	Yal,
	Zib_,
	1,
	Yi32,
	Ymb,
	Zibo_m,
	2,
	Yrb,
	Ymb,
	Zr_m,
	1,
	Ymb,
	Yrb,
	Zm_r,
	1,
	0,
}

var ytestl = []uint8{
	Yi32,
	Yax,
	Zil_,
	1,
	Yi32,
	Yml,
	Zilo_m,
	2,
	Yrl,
	Yml,
	Zr_m,
	1,
	Yml,
	Yrl,
	Zm_r,
	1,
	0,
}

var ymovb = []uint8{
	Yrb,
	Ymb,
	Zr_m,
	1,
	Ymb,
	Yrb,
	Zm_r,
	1,
	Yi32,
	Yrb,
	Zib_rp,
	1,
	Yi32,
	Ymb,
	Zibo_m,
	2,
	0,
}

var ymbs = []uint8{
	Ymb,
	Ynone,
	Zm_o,
	2,
	0,
}

var ybtl = []uint8{
	Yi8,
	Yml,
	Zibo_m,
	2,
	Yrl,
	Yml,
	Zr_m,
	1,
	0,
}

var ymovw = []uint8{
	Yrl,
	Yml,
	Zr_m,
	1,
	Yml,
	Yrl,
	Zm_r,
	1,
	Yi0,
	Yrl,
	Zclr,
	1,
	Yi32,
	Yrl,
	Zil_rp,
	1,
	Yi32,
	Yml,
	Zilo_m,
	2,
	Yiauto,
	Yrl,
	Zaut_r,
	2,
	0,
}

var ymovl = []uint8{
	Yrl,
	Yml,
	Zr_m,
	1,
	Yml,
	Yrl,
	Zm_r,
	1,
	Yi0,
	Yrl,
	Zclr,
	1,
	Yi32,
	Yrl,
	Zil_rp,
	1,
	Yi32,
	Yml,
	Zilo_m,
	2,
	Yml,
	Ymr,
	Zm_r_xm,
	1, // MMX MOVD
	Ymr,
	Yml,
	Zr_m_xm,
	1, // MMX MOVD
	Yml,
	Yxr,
	Zm_r_xm,
	2, // XMM MOVD (32 bit)
	Yxr,
	Yml,
	Zr_m_xm,
	2, // XMM MOVD (32 bit)
	Yiauto,
	Yrl,
	Zaut_r,
	2,
	0,
}

var yret = []uint8{
	Ynone,
	Ynone,
	Zo_iw,
	1,
	Yi32,
	Ynone,
	Zo_iw,
	1,
	0,
}

var ymovq = []uint8{
	Yrl,
	Yml,
	Zr_m,
	1, // 0x89
	Yml,
	Yrl,
	Zm_r,
	1, // 0x8b
	Yi0,
	Yrl,
	Zclr,
	1, // 0x31
	Ys32,
	Yrl,
	Zilo_m,
	2, // 32 bit signed 0xc7,(0)
	Yi64,
	Yrl,
	Ziq_rp,
	1, // 0xb8 -- 32/64 bit immediate
	Yi32,
	Yml,
	Zilo_m,
	2, // 0xc7,(0)
	Ym,
	Ymr,
	Zm_r_xm_nr,
	1, // MMX MOVQ (shorter encoding)
	Ymr,
	Ym,
	Zr_m_xm_nr,
	1, // MMX MOVQ
	Ymm,
	Ymr,
	Zm_r_xm,
	1, // MMX MOVD
	Ymr,
	Ymm,
	Zr_m_xm,
	1, // MMX MOVD
	Yxr,
	Ymr,
	Zm_r_xm_nr,
	2, // MOVDQ2Q
	Yxm,
	Yxr,
	Zm_r_xm_nr,
	2, // MOVQ xmm1/m64 -> xmm2
	Yxr,
	Yxm,
	Zr_m_xm_nr,
	2, // MOVQ xmm1 -> xmm2/m64
	Yml,
	Yxr,
	Zm_r_xm,
	2, // MOVD xmm load
	Yxr,
	Yml,
	Zr_m_xm,
	2, // MOVD xmm store
	Yiauto,
	Yrl,
	Zaut_r,
	2, // built-in LEAQ
	0,
}

var ym_rl = []uint8{
	Ym,
	Yrl,
	Zm_r,
	1,
	0,
}

var yrl_m = []uint8{
	Yrl,
	Ym,
	Zr_m,
	1,
	0,
}

var ymb_rl = []uint8{
	Ymb,
	Yrl,
	Zmb_r,
	1,
	0,
}

var yml_rl = []uint8{
	Yml,
	Yrl,
	Zm_r,
	1,
	0,
}

var yrl_ml = []uint8{
	Yrl,
	Yml,
	Zr_m,
	1,
	0,
}

var yml_mb = []uint8{
	Yrb,
	Ymb,
	Zr_m,
	1,
	Ymb,
	Yrb,
	Zm_r,
	1,
	0,
}

var yrb_mb = []uint8{
	Yrb,
	Ymb,
	Zr_m,
	1,
	0,
}

var yxchg = []uint8{
	Yax,
	Yrl,
	Z_rp,
	1,
	Yrl,
	Yax,
	Zrp_,
	1,
	Yrl,
	Yml,
	Zr_m,
	1,
	Yml,
	Yrl,
	Zm_r,
	1,
	0,
}

var ydivl = []uint8{
	Yml,
	Ynone,
	Zm_o,
	2,
	0,
}

var ydivb = []uint8{
	Ymb,
	Ynone,
	Zm_o,
	2,
	0,
}

var yimul = []uint8{
	Yml,
	Ynone,
	Zm_o,
	2,
	Yi8,
	Yrl,
	Zib_rr,
	1,
	Yi32,
	Yrl,
	Zil_rr,
	1,
	Yml,
	Yrl,
	Zm_r,
	2,
	0,
}

var yimul3 = []uint8{
	Yml,
	Yrl,
	Zibm_r,
	2,
	0,
}

var ybyte = []uint8{
	Yi64,
	Ynone,
	Zbyte,
	1,
	0,
}

var yin = []uint8{
	Yi32,
	Ynone,
	Zib_,
	1,
	Ynone,
	Ynone,
	Zlit,
	1,
	0,
}

var yint = []uint8{
	Yi32,
	Ynone,
	Zib_,
	1,
	0,
}

var ypushl = []uint8{
	Yrl,
	Ynone,
	Zrp_,
	1,
	Ym,
	Ynone,
	Zm_o,
	2,
	Yi8,
	Ynone,
	Zib_,
	1,
	Yi32,
	Ynone,
	Zil_,
	1,
	0,
}

var ypopl = []uint8{
	Ynone,
	Yrl,
	Z_rp,
	1,
	Ynone,
	Ym,
	Zo_m,
	2,
	0,
}

var ybswap = []uint8{
	Ynone,
	Yrl,
	Z_rp,
	2,
	0,
}

var yscond = []uint8{
	Ynone,
	Ymb,
	Zo_m,
	2,
	0,
}

var yjcond = []uint8{
	Ynone,
	Ybr,
	Zbr,
	0,
	Yi0,
	Ybr,
	Zbr,
	0,
	Yi1,
	Ybr,
	Zbr,
	1,
	0,
}

var yloop = []uint8{
	Ynone,
	Ybr,
	Zloop,
	1,
	0,
}

var ycall = []uint8{
	Ynone,
	Yml,
	Zcallindreg,
	0,
	Yrx,
	Yrx,
	Zcallindreg,
	2,
	Ynone,
	Ybr,
	Zcall,
	1,
	0,
}

var yduff = []uint8{
	Ynone,
	Yi32,
	Zcall,
	1,
	0,
}

var yjmp = []uint8{
	Ynone,
	Yml,
	Zo_m64,
	2,
	Ynone,
	Ybr,
	Zjmp,
	1,
	0,
}

var yfmvd = []uint8{
	Ym,
	Yf0,
	Zm_o,
	2,
	Yf0,
	Ym,
	Zo_m,
	2,
	Yrf,
	Yf0,
	Zm_o,
	2,
	Yf0,
	Yrf,
	Zo_m,
	2,
	0,
}

var yfmvdp = []uint8{
	Yf0,
	Ym,
	Zo_m,
	2,
	Yf0,
	Yrf,
	Zo_m,
	2,
	0,
}

var yfmvf = []uint8{
	Ym,
	Yf0,
	Zm_o,
	2,
	Yf0,
	Ym,
	Zo_m,
	2,
	0,
}

var yfmvx = []uint8{
	Ym,
	Yf0,
	Zm_o,
	2,
	0,
}

var yfmvp = []uint8{
	Yf0,
	Ym,
	Zo_m,
	2,
	0,
}

var yfadd = []uint8{
	Ym,
	Yf0,
	Zm_o,
	2,
	Yrf,
	Yf0,
	Zm_o,
	2,
	Yf0,
	Yrf,
	Zo_m,
	2,
	0,
}

var yfaddp = []uint8{
	Yf0,
	Yrf,
	Zo_m,
	2,
	0,
}

var yfxch = []uint8{
	Yf0,
	Yrf,
	Zo_m,
	2,
	Yrf,
	Yf0,
	Zm_o,
	2,
	0,
}

var ycompp = []uint8{
	Yf0,
	Yrf,
	Zo_m,
	2, /* botch is really f0,f1 */
	0,
}

var ystsw = []uint8{
	Ynone,
	Ym,
	Zo_m,
	2,
	Ynone,
	Yax,
	Zlit,
	1,
	0,
}

var ystcw = []uint8{
	Ynone,
	Ym,
	Zo_m,
	2,
	Ym,
	Ynone,
	Zm_o,
	2,
	0,
}

var ysvrs = []uint8{
	Ynone,
	Ym,
	Zo_m,
	2,
	Ym,
	Ynone,
	Zm_o,
	2,
	0,
}

var ymm = []uint8{
	Ymm,
	Ymr,
	Zm_r_xm,
	1,
	Yxm,
	Yxr,
	Zm_r_xm,
	2,
	0,
}

var yxm = []uint8{
	Yxm,
	Yxr,
	Zm_r_xm,
	1,
	0,
}

var yxcvm1 = []uint8{
	Yxm,
	Yxr,
	Zm_r_xm,
	2,
	Yxm,
	Ymr,
	Zm_r_xm,
	2,
	0,
}

var yxcvm2 = []uint8{
	Yxm,
	Yxr,
	Zm_r_xm,
	2,
	Ymm,
	Yxr,
	Zm_r_xm,
	2,
	0,
}

/*
static uchar	yxmq[] =
{
	Yxm,	Yxr,	Zm_r_xm,	2,
	0
};
*/
var yxr = []uint8{
	Yxr,
	Yxr,
	Zm_r_xm,
	1,
	0,
}

var yxr_ml = []uint8{
	Yxr,
	Yml,
	Zr_m_xm,
	1,
	0,
}

var ymr = []uint8{
	Ymr,
	Ymr,
	Zm_r,
	1,
	0,
}

var ymr_ml = []uint8{
	Ymr,
	Yml,
	Zr_m_xm,
	1,
	0,
}

var yxcmp = []uint8{
	Yxm,
	Yxr,
	Zm_r_xm,
	1,
	0,
}

var yxcmpi = []uint8{
	Yxm,
	Yxr,
	Zm_r_i_xm,
	2,
	0,
}

var yxmov = []uint8{
	Yxm,
	Yxr,
	Zm_r_xm,
	1,
	Yxr,
	Yxm,
	Zr_m_xm,
	1,
	0,
}

var yxcvfl = []uint8{
	Yxm,
	Yrl,
	Zm_r_xm,
	1,
	0,
}

var yxcvlf = []uint8{
	Yml,
	Yxr,
	Zm_r_xm,
	1,
	0,
}

var yxcvfq = []uint8{
	Yxm,
	Yrl,
	Zm_r_xm,
	2,
	0,
}

var yxcvqf = []uint8{
	Yml,
	Yxr,
	Zm_r_xm,
	2,
	0,
}

var yps = []uint8{
	Ymm,
	Ymr,
	Zm_r_xm,
	1,
	Yi8,
	Ymr,
	Zibo_m_xm,
	2,
	Yxm,
	Yxr,
	Zm_r_xm,
	2,
	Yi8,
	Yxr,
	Zibo_m_xm,
	3,
	0,
}

var yxrrl = []uint8{
	Yxr,
	Yrl,
	Zm_r,
	1,
	0,
}

var ymfp = []uint8{
	Ymm,
	Ymr,
	Zm_r_3d,
	1,
	0,
}

var ymrxr = []uint8{
	Ymr,
	Yxr,
	Zm_r,
	1,
	Yxm,
	Yxr,
	Zm_r_xm,
	1,
	0,
}

var ymshuf = []uint8{
	Ymm,
	Ymr,
	Zibm_r,
	2,
	0,
}

var ymshufb = []uint8{
	Yxm,
	Yxr,
	Zm2_r,
	2,
	0,
}

var yxshuf = []uint8{
	Yxm,
	Yxr,
	Zibm_r,
	2,
	0,
}

var yextrw = []uint8{
	Yxr,
	Yrl,
	Zibm_r,
	2,
	0,
}

var yinsrw = []uint8{
	Yml,
	Yxr,
	Zibm_r,
	2,
	0,
}

var yinsr = []uint8{
	Ymm,
	Yxr,
	Zibm_r,
	3,
	0,
}

var ypsdq = []uint8{
	Yi8,
	Yxr,
	Zibo_m,
	2,
	0,
}

var ymskb = []uint8{
	Yxr,
	Yrl,
	Zm_r_xm,
	2,
	Ymr,
	Yrl,
	Zm_r_xm,
	1,
	0,
}

var ycrc32l = []uint8{Yml, Yrl, Zlitm_r, 0}

var yprefetch = []uint8{
	Ym,
	Ynone,
	Zm_o,
	2,
	0,
}

var yaes = []uint8{
	Yxm,
	Yxr,
	Zlitm_r,
	2,
	0,
}

var yaes2 = []uint8{
	Yxm,
	Yxr,
	Zibm_r,
	2,
	0,
}

/*
 * You are doasm, holding in your hand a Prog* with p->as set to, say, ACRC32,
 * and p->from and p->to as operands (Addr*).  The linker scans optab to find
 * the entry with the given p->as and then looks through the ytable for that
 * instruction (the second field in the optab struct) for a line whose first
 * two values match the Ytypes of the p->from and p->to operands.  The function
 * oclass in span.c computes the specific Ytype of an operand and then the set
 * of more general Ytypes that it satisfies is implied by the ycover table, set
 * up in instinit.  For example, oclass distinguishes the constants 0 and 1
 * from the more general 8-bit constants, but instinit says
 *
 *        ycover[Yi0*Ymax + Ys32] = 1;
 *        ycover[Yi1*Ymax + Ys32] = 1;
 *        ycover[Yi8*Ymax + Ys32] = 1;
 *
 * which means that Yi0, Yi1, and Yi8 all count as Ys32 (signed 32)
 * if that's what an instruction can handle.
 *
 * In parallel with the scan through the ytable for the appropriate line, there
 * is a z pointer that starts out pointing at the strange magic byte list in
 * the Optab struct.  With each step past a non-matching ytable line, z
 * advances by the 4th entry in the line.  When a matching line is found, that
 * z pointer has the extra data to use in laying down the instruction bytes.
 * The actual bytes laid down are a function of the 3rd entry in the line (that
 * is, the Ztype) and the z bytes.
 *
 * For example, let's look at AADDL.  The optab line says:
 *        { AADDL,        yaddl,  Px, 0x83,(00),0x05,0x81,(00),0x01,0x03 },
 *
 * and yaddl says
 *        uchar   yaddl[] =
 *        {
 *                Yi8,    Yml,    Zibo_m, 2,
 *                Yi32,   Yax,    Zil_,   1,
 *                Yi32,   Yml,    Zilo_m, 2,
 *                Yrl,    Yml,    Zr_m,   1,
 *                Yml,    Yrl,    Zm_r,   1,
 *                0
 *        };
 *
 * so there are 5 possible types of ADDL instruction that can be laid down, and
 * possible states used to lay them down (Ztype and z pointer, assuming z
 * points at {0x83,(00),0x05,0x81,(00),0x01,0x03}) are:
 *
 *        Yi8, Yml -> Zibo_m, z (0x83, 00)
 *        Yi32, Yax -> Zil_, z+2 (0x05)
 *        Yi32, Yml -> Zilo_m, z+2+1 (0x81, 0x00)
 *        Yrl, Yml -> Zr_m, z+2+1+2 (0x01)
 *        Yml, Yrl -> Zm_r, z+2+1+2+1 (0x03)
 *
 * The Pconstant in the optab line controls the prefix bytes to emit.  That's
 * relatively straightforward as this program goes.
 *
 * The switch on t[2] in doasm implements the various Z cases.  Zibo_m, for
 * example, is an opcode byte (z[0]) then an asmando (which is some kind of
 * encoded addressing mode for the Yml arg), and then a single immediate byte.
 * Zilo_m is the same but a long (32-bit) immediate.
 */
var optab =
/*	as, ytab, andproto, opcode */
[]Optab{
	Optab{AXXX, nil, 0, [23]uint8{}},
	Optab{AAAA, ynone, P32, [23]uint8{0x37}},
	Optab{AAAD, ynone, P32, [23]uint8{0xd5, 0x0a}},
	Optab{AAAM, ynone, P32, [23]uint8{0xd4, 0x0a}},
	Optab{AAAS, ynone, P32, [23]uint8{0x3f}},
	Optab{AADCB, yxorb, Pb, [23]uint8{0x14, 0x80, 02, 0x10, 0x10}},
	Optab{AADCL, yxorl, Px, [23]uint8{0x83, 02, 0x15, 0x81, 02, 0x11, 0x13}},
	Optab{AADCQ, yxorl, Pw, [23]uint8{0x83, 02, 0x15, 0x81, 02, 0x11, 0x13}},
	Optab{AADCW, yxorl, Pe, [23]uint8{0x83, 02, 0x15, 0x81, 02, 0x11, 0x13}},
	Optab{AADDB, yxorb, Pb, [23]uint8{0x04, 0x80, 00, 0x00, 0x02}},
	Optab{AADDL, yaddl, Px, [23]uint8{0x83, 00, 0x05, 0x81, 00, 0x01, 0x03}},
	Optab{AADDPD, yxm, Pq, [23]uint8{0x58}},
	Optab{AADDPS, yxm, Pm, [23]uint8{0x58}},
	Optab{AADDQ, yaddl, Pw, [23]uint8{0x83, 00, 0x05, 0x81, 00, 0x01, 0x03}},
	Optab{AADDSD, yxm, Pf2, [23]uint8{0x58}},
	Optab{AADDSS, yxm, Pf3, [23]uint8{0x58}},
	Optab{AADDW, yaddl, Pe, [23]uint8{0x83, 00, 0x05, 0x81, 00, 0x01, 0x03}},
	Optab{AADJSP, nil, 0, [23]uint8{}},
	Optab{AANDB, yxorb, Pb, [23]uint8{0x24, 0x80, 04, 0x20, 0x22}},
	Optab{AANDL, yxorl, Px, [23]uint8{0x83, 04, 0x25, 0x81, 04, 0x21, 0x23}},
	Optab{AANDNPD, yxm, Pq, [23]uint8{0x55}},
	Optab{AANDNPS, yxm, Pm, [23]uint8{0x55}},
	Optab{AANDPD, yxm, Pq, [23]uint8{0x54}},
	Optab{AANDPS, yxm, Pq, [23]uint8{0x54}},
	Optab{AANDQ, yxorl, Pw, [23]uint8{0x83, 04, 0x25, 0x81, 04, 0x21, 0x23}},
	Optab{AANDW, yxorl, Pe, [23]uint8{0x83, 04, 0x25, 0x81, 04, 0x21, 0x23}},
	Optab{AARPL, yrl_ml, P32, [23]uint8{0x63}},
	Optab{ABOUNDL, yrl_m, P32, [23]uint8{0x62}},
	Optab{ABOUNDW, yrl_m, Pe, [23]uint8{0x62}},
	Optab{ABSFL, yml_rl, Pm, [23]uint8{0xbc}},
	Optab{ABSFQ, yml_rl, Pw, [23]uint8{0x0f, 0xbc}},
	Optab{ABSFW, yml_rl, Pq, [23]uint8{0xbc}},
	Optab{ABSRL, yml_rl, Pm, [23]uint8{0xbd}},
	Optab{ABSRQ, yml_rl, Pw, [23]uint8{0x0f, 0xbd}},
	Optab{ABSRW, yml_rl, Pq, [23]uint8{0xbd}},
	Optab{ABSWAPL, ybswap, Px, [23]uint8{0x0f, 0xc8}},
	Optab{ABSWAPQ, ybswap, Pw, [23]uint8{0x0f, 0xc8}},
	Optab{ABTCL, ybtl, Pm, [23]uint8{0xba, 07, 0xbb}},
	Optab{ABTCQ, ybtl, Pw, [23]uint8{0x0f, 0xba, 07, 0x0f, 0xbb}},
	Optab{ABTCW, ybtl, Pq, [23]uint8{0xba, 07, 0xbb}},
	Optab{ABTL, ybtl, Pm, [23]uint8{0xba, 04, 0xa3}},
	Optab{ABTQ, ybtl, Pw, [23]uint8{0x0f, 0xba, 04, 0x0f, 0xa3}},
	Optab{ABTRL, ybtl, Pm, [23]uint8{0xba, 06, 0xb3}},
	Optab{ABTRQ, ybtl, Pw, [23]uint8{0x0f, 0xba, 06, 0x0f, 0xb3}},
	Optab{ABTRW, ybtl, Pq, [23]uint8{0xba, 06, 0xb3}},
	Optab{ABTSL, ybtl, Pm, [23]uint8{0xba, 05, 0xab}},
	Optab{ABTSQ, ybtl, Pw, [23]uint8{0x0f, 0xba, 05, 0x0f, 0xab}},
	Optab{ABTSW, ybtl, Pq, [23]uint8{0xba, 05, 0xab}},
	Optab{ABTW, ybtl, Pq, [23]uint8{0xba, 04, 0xa3}},
	Optab{ABYTE, ybyte, Px, [23]uint8{1}},
	Optab{ACALL, ycall, Px, [23]uint8{0xff, 02, 0xe8}},
	Optab{ACDQ, ynone, Px, [23]uint8{0x99}},
	Optab{ACLC, ynone, Px, [23]uint8{0xf8}},
	Optab{ACLD, ynone, Px, [23]uint8{0xfc}},
	Optab{ACLI, ynone, Px, [23]uint8{0xfa}},
	Optab{ACLTS, ynone, Pm, [23]uint8{0x06}},
	Optab{ACMC, ynone, Px, [23]uint8{0xf5}},
	Optab{ACMOVLCC, yml_rl, Pm, [23]uint8{0x43}},
	Optab{ACMOVLCS, yml_rl, Pm, [23]uint8{0x42}},
	Optab{ACMOVLEQ, yml_rl, Pm, [23]uint8{0x44}},
	Optab{ACMOVLGE, yml_rl, Pm, [23]uint8{0x4d}},
	Optab{ACMOVLGT, yml_rl, Pm, [23]uint8{0x4f}},
	Optab{ACMOVLHI, yml_rl, Pm, [23]uint8{0x47}},
	Optab{ACMOVLLE, yml_rl, Pm, [23]uint8{0x4e}},
	Optab{ACMOVLLS, yml_rl, Pm, [23]uint8{0x46}},
	Optab{ACMOVLLT, yml_rl, Pm, [23]uint8{0x4c}},
	Optab{ACMOVLMI, yml_rl, Pm, [23]uint8{0x48}},
	Optab{ACMOVLNE, yml_rl, Pm, [23]uint8{0x45}},
	Optab{ACMOVLOC, yml_rl, Pm, [23]uint8{0x41}},
	Optab{ACMOVLOS, yml_rl, Pm, [23]uint8{0x40}},
	Optab{ACMOVLPC, yml_rl, Pm, [23]uint8{0x4b}},
	Optab{ACMOVLPL, yml_rl, Pm, [23]uint8{0x49}},
	Optab{ACMOVLPS, yml_rl, Pm, [23]uint8{0x4a}},
	Optab{ACMOVQCC, yml_rl, Pw, [23]uint8{0x0f, 0x43}},
	Optab{ACMOVQCS, yml_rl, Pw, [23]uint8{0x0f, 0x42}},
	Optab{ACMOVQEQ, yml_rl, Pw, [23]uint8{0x0f, 0x44}},
	Optab{ACMOVQGE, yml_rl, Pw, [23]uint8{0x0f, 0x4d}},
	Optab{ACMOVQGT, yml_rl, Pw, [23]uint8{0x0f, 0x4f}},
	Optab{ACMOVQHI, yml_rl, Pw, [23]uint8{0x0f, 0x47}},
	Optab{ACMOVQLE, yml_rl, Pw, [23]uint8{0x0f, 0x4e}},
	Optab{ACMOVQLS, yml_rl, Pw, [23]uint8{0x0f, 0x46}},
	Optab{ACMOVQLT, yml_rl, Pw, [23]uint8{0x0f, 0x4c}},
	Optab{ACMOVQMI, yml_rl, Pw, [23]uint8{0x0f, 0x48}},
	Optab{ACMOVQNE, yml_rl, Pw, [23]uint8{0x0f, 0x45}},
	Optab{ACMOVQOC, yml_rl, Pw, [23]uint8{0x0f, 0x41}},
	Optab{ACMOVQOS, yml_rl, Pw, [23]uint8{0x0f, 0x40}},
	Optab{ACMOVQPC, yml_rl, Pw, [23]uint8{0x0f, 0x4b}},
	Optab{ACMOVQPL, yml_rl, Pw, [23]uint8{0x0f, 0x49}},
	Optab{ACMOVQPS, yml_rl, Pw, [23]uint8{0x0f, 0x4a}},
	Optab{ACMOVWCC, yml_rl, Pq, [23]uint8{0x43}},
	Optab{ACMOVWCS, yml_rl, Pq, [23]uint8{0x42}},
	Optab{ACMOVWEQ, yml_rl, Pq, [23]uint8{0x44}},
	Optab{ACMOVWGE, yml_rl, Pq, [23]uint8{0x4d}},
	Optab{ACMOVWGT, yml_rl, Pq, [23]uint8{0x4f}},
	Optab{ACMOVWHI, yml_rl, Pq, [23]uint8{0x47}},
	Optab{ACMOVWLE, yml_rl, Pq, [23]uint8{0x4e}},
	Optab{ACMOVWLS, yml_rl, Pq, [23]uint8{0x46}},
	Optab{ACMOVWLT, yml_rl, Pq, [23]uint8{0x4c}},
	Optab{ACMOVWMI, yml_rl, Pq, [23]uint8{0x48}},
	Optab{ACMOVWNE, yml_rl, Pq, [23]uint8{0x45}},
	Optab{ACMOVWOC, yml_rl, Pq, [23]uint8{0x41}},
	Optab{ACMOVWOS, yml_rl, Pq, [23]uint8{0x40}},
	Optab{ACMOVWPC, yml_rl, Pq, [23]uint8{0x4b}},
	Optab{ACMOVWPL, yml_rl, Pq, [23]uint8{0x49}},
	Optab{ACMOVWPS, yml_rl, Pq, [23]uint8{0x4a}},
	Optab{ACMPB, ycmpb, Pb, [23]uint8{0x3c, 0x80, 07, 0x38, 0x3a}},
	Optab{ACMPL, ycmpl, Px, [23]uint8{0x83, 07, 0x3d, 0x81, 07, 0x39, 0x3b}},
	Optab{ACMPPD, yxcmpi, Px, [23]uint8{Pe, 0xc2}},
	Optab{ACMPPS, yxcmpi, Pm, [23]uint8{0xc2, 0}},
	Optab{ACMPQ, ycmpl, Pw, [23]uint8{0x83, 07, 0x3d, 0x81, 07, 0x39, 0x3b}},
	Optab{ACMPSB, ynone, Pb, [23]uint8{0xa6}},
	Optab{ACMPSD, yxcmpi, Px, [23]uint8{Pf2, 0xc2}},
	Optab{ACMPSL, ynone, Px, [23]uint8{0xa7}},
	Optab{ACMPSQ, ynone, Pw, [23]uint8{0xa7}},
	Optab{ACMPSS, yxcmpi, Px, [23]uint8{Pf3, 0xc2}},
	Optab{ACMPSW, ynone, Pe, [23]uint8{0xa7}},
	Optab{ACMPW, ycmpl, Pe, [23]uint8{0x83, 07, 0x3d, 0x81, 07, 0x39, 0x3b}},
	Optab{ACOMISD, yxcmp, Pe, [23]uint8{0x2f}},
	Optab{ACOMISS, yxcmp, Pm, [23]uint8{0x2f}},
	Optab{ACPUID, ynone, Pm, [23]uint8{0xa2}},
	Optab{ACVTPL2PD, yxcvm2, Px, [23]uint8{Pf3, 0xe6, Pe, 0x2a}},
	Optab{ACVTPL2PS, yxcvm2, Pm, [23]uint8{0x5b, 0, 0x2a, 0}},
	Optab{ACVTPD2PL, yxcvm1, Px, [23]uint8{Pf2, 0xe6, Pe, 0x2d}},
	Optab{ACVTPD2PS, yxm, Pe, [23]uint8{0x5a}},
	Optab{ACVTPS2PL, yxcvm1, Px, [23]uint8{Pe, 0x5b, Pm, 0x2d}},
	Optab{ACVTPS2PD, yxm, Pm, [23]uint8{0x5a}},
	Optab{API2FW, ymfp, Px, [23]uint8{0x0c}},
	Optab{ACVTSD2SL, yxcvfl, Pf2, [23]uint8{0x2d}},
	Optab{ACVTSD2SQ, yxcvfq, Pw, [23]uint8{Pf2, 0x2d}},
	Optab{ACVTSD2SS, yxm, Pf2, [23]uint8{0x5a}},
	Optab{ACVTSL2SD, yxcvlf, Pf2, [23]uint8{0x2a}},
	Optab{ACVTSQ2SD, yxcvqf, Pw, [23]uint8{Pf2, 0x2a}},
	Optab{ACVTSL2SS, yxcvlf, Pf3, [23]uint8{0x2a}},
	Optab{ACVTSQ2SS, yxcvqf, Pw, [23]uint8{Pf3, 0x2a}},
	Optab{ACVTSS2SD, yxm, Pf3, [23]uint8{0x5a}},
	Optab{ACVTSS2SL, yxcvfl, Pf3, [23]uint8{0x2d}},
	Optab{ACVTSS2SQ, yxcvfq, Pw, [23]uint8{Pf3, 0x2d}},
	Optab{ACVTTPD2PL, yxcvm1, Px, [23]uint8{Pe, 0xe6, Pe, 0x2c}},
	Optab{ACVTTPS2PL, yxcvm1, Px, [23]uint8{Pf3, 0x5b, Pm, 0x2c}},
	Optab{ACVTTSD2SL, yxcvfl, Pf2, [23]uint8{0x2c}},
	Optab{ACVTTSD2SQ, yxcvfq, Pw, [23]uint8{Pf2, 0x2c}},
	Optab{ACVTTSS2SL, yxcvfl, Pf3, [23]uint8{0x2c}},
	Optab{ACVTTSS2SQ, yxcvfq, Pw, [23]uint8{Pf3, 0x2c}},
	Optab{ACWD, ynone, Pe, [23]uint8{0x99}},
	Optab{ACQO, ynone, Pw, [23]uint8{0x99}},
	Optab{ADAA, ynone, P32, [23]uint8{0x27}},
	Optab{ADAS, ynone, P32, [23]uint8{0x2f}},
	Optab{ADATA, nil, 0, [23]uint8{}},
	Optab{ADECB, yincb, Pb, [23]uint8{0xfe, 01}},
	Optab{ADECL, yincl, Px, [23]uint8{0xff, 01}},
	Optab{ADECQ, yincl, Pw, [23]uint8{0xff, 01}},
	Optab{ADECW, yincw, Pe, [23]uint8{0xff, 01}},
	Optab{ADIVB, ydivb, Pb, [23]uint8{0xf6, 06}},
	Optab{ADIVL, ydivl, Px, [23]uint8{0xf7, 06}},
	Optab{ADIVPD, yxm, Pe, [23]uint8{0x5e}},
	Optab{ADIVPS, yxm, Pm, [23]uint8{0x5e}},
	Optab{ADIVQ, ydivl, Pw, [23]uint8{0xf7, 06}},
	Optab{ADIVSD, yxm, Pf2, [23]uint8{0x5e}},
	Optab{ADIVSS, yxm, Pf3, [23]uint8{0x5e}},
	Optab{ADIVW, ydivl, Pe, [23]uint8{0xf7, 06}},
	Optab{AEMMS, ynone, Pm, [23]uint8{0x77}},
	Optab{AENTER, nil, 0, [23]uint8{}}, /* botch */
	Optab{AFXRSTOR, ysvrs, Pm, [23]uint8{0xae, 01, 0xae, 01}},
	Optab{AFXSAVE, ysvrs, Pm, [23]uint8{0xae, 00, 0xae, 00}},
	Optab{AFXRSTOR64, ysvrs, Pw, [23]uint8{0x0f, 0xae, 01, 0x0f, 0xae, 01}},
	Optab{AFXSAVE64, ysvrs, Pw, [23]uint8{0x0f, 0xae, 00, 0x0f, 0xae, 00}},
	Optab{AGLOBL, nil, 0, [23]uint8{}},
	Optab{AGOK, nil, 0, [23]uint8{}},
	Optab{AHISTORY, nil, 0, [23]uint8{}},
	Optab{AHLT, ynone, Px, [23]uint8{0xf4}},
	Optab{AIDIVB, ydivb, Pb, [23]uint8{0xf6, 07}},
	Optab{AIDIVL, ydivl, Px, [23]uint8{0xf7, 07}},
	Optab{AIDIVQ, ydivl, Pw, [23]uint8{0xf7, 07}},
	Optab{AIDIVW, ydivl, Pe, [23]uint8{0xf7, 07}},
	Optab{AIMULB, ydivb, Pb, [23]uint8{0xf6, 05}},
	Optab{AIMULL, yimul, Px, [23]uint8{0xf7, 05, 0x6b, 0x69, Pm, 0xaf}},
	Optab{AIMULQ, yimul, Pw, [23]uint8{0xf7, 05, 0x6b, 0x69, Pm, 0xaf}},
	Optab{AIMULW, yimul, Pe, [23]uint8{0xf7, 05, 0x6b, 0x69, Pm, 0xaf}},
	Optab{AIMUL3Q, yimul3, Pw, [23]uint8{0x6b, 00}},
	Optab{AINB, yin, Pb, [23]uint8{0xe4, 0xec}},
	Optab{AINCB, yincb, Pb, [23]uint8{0xfe, 00}},
	Optab{AINCL, yincl, Px, [23]uint8{0xff, 00}},
	Optab{AINCQ, yincl, Pw, [23]uint8{0xff, 00}},
	Optab{AINCW, yincw, Pe, [23]uint8{0xff, 00}},
	Optab{AINL, yin, Px, [23]uint8{0xe5, 0xed}},
	Optab{AINSB, ynone, Pb, [23]uint8{0x6c}},
	Optab{AINSL, ynone, Px, [23]uint8{0x6d}},
	Optab{AINSW, ynone, Pe, [23]uint8{0x6d}},
	Optab{AINT, yint, Px, [23]uint8{0xcd}},
	Optab{AINTO, ynone, P32, [23]uint8{0xce}},
	Optab{AINW, yin, Pe, [23]uint8{0xe5, 0xed}},
	Optab{AIRETL, ynone, Px, [23]uint8{0xcf}},
	Optab{AIRETQ, ynone, Pw, [23]uint8{0xcf}},
	Optab{AIRETW, ynone, Pe, [23]uint8{0xcf}},
	Optab{AJCC, yjcond, Px, [23]uint8{0x73, 0x83, 00}},
	Optab{AJCS, yjcond, Px, [23]uint8{0x72, 0x82}},
	Optab{AJCXZL, yloop, Px, [23]uint8{0xe3}},
	Optab{AJCXZQ, yloop, Px, [23]uint8{0xe3}},
	Optab{AJEQ, yjcond, Px, [23]uint8{0x74, 0x84}},
	Optab{AJGE, yjcond, Px, [23]uint8{0x7d, 0x8d}},
	Optab{AJGT, yjcond, Px, [23]uint8{0x7f, 0x8f}},
	Optab{AJHI, yjcond, Px, [23]uint8{0x77, 0x87}},
	Optab{AJLE, yjcond, Px, [23]uint8{0x7e, 0x8e}},
	Optab{AJLS, yjcond, Px, [23]uint8{0x76, 0x86}},
	Optab{AJLT, yjcond, Px, [23]uint8{0x7c, 0x8c}},
	Optab{AJMI, yjcond, Px, [23]uint8{0x78, 0x88}},
	Optab{AJMP, yjmp, Px, [23]uint8{0xff, 04, 0xeb, 0xe9}},
	Optab{AJNE, yjcond, Px, [23]uint8{0x75, 0x85}},
	Optab{AJOC, yjcond, Px, [23]uint8{0x71, 0x81, 00}},
	Optab{AJOS, yjcond, Px, [23]uint8{0x70, 0x80, 00}},
	Optab{AJPC, yjcond, Px, [23]uint8{0x7b, 0x8b}},
	Optab{AJPL, yjcond, Px, [23]uint8{0x79, 0x89}},
	Optab{AJPS, yjcond, Px, [23]uint8{0x7a, 0x8a}},
	Optab{ALAHF, ynone, Px, [23]uint8{0x9f}},
	Optab{ALARL, yml_rl, Pm, [23]uint8{0x02}},
	Optab{ALARW, yml_rl, Pq, [23]uint8{0x02}},
	Optab{ALDMXCSR, ysvrs, Pm, [23]uint8{0xae, 02, 0xae, 02}},
	Optab{ALEAL, ym_rl, Px, [23]uint8{0x8d}},
	Optab{ALEAQ, ym_rl, Pw, [23]uint8{0x8d}},
	Optab{ALEAVEL, ynone, P32, [23]uint8{0xc9}},
	Optab{ALEAVEQ, ynone, Py, [23]uint8{0xc9}},
	Optab{ALEAVEW, ynone, Pe, [23]uint8{0xc9}},
	Optab{ALEAW, ym_rl, Pe, [23]uint8{0x8d}},
	Optab{ALOCK, ynone, Px, [23]uint8{0xf0}},
	Optab{ALODSB, ynone, Pb, [23]uint8{0xac}},
	Optab{ALODSL, ynone, Px, [23]uint8{0xad}},
	Optab{ALODSQ, ynone, Pw, [23]uint8{0xad}},
	Optab{ALODSW, ynone, Pe, [23]uint8{0xad}},
	Optab{ALONG, ybyte, Px, [23]uint8{4}},
	Optab{ALOOP, yloop, Px, [23]uint8{0xe2}},
	Optab{ALOOPEQ, yloop, Px, [23]uint8{0xe1}},
	Optab{ALOOPNE, yloop, Px, [23]uint8{0xe0}},
	Optab{ALSLL, yml_rl, Pm, [23]uint8{0x03}},
	Optab{ALSLW, yml_rl, Pq, [23]uint8{0x03}},
	Optab{AMASKMOVOU, yxr, Pe, [23]uint8{0xf7}},
	Optab{AMASKMOVQ, ymr, Pm, [23]uint8{0xf7}},
	Optab{AMAXPD, yxm, Pe, [23]uint8{0x5f}},
	Optab{AMAXPS, yxm, Pm, [23]uint8{0x5f}},
	Optab{AMAXSD, yxm, Pf2, [23]uint8{0x5f}},
	Optab{AMAXSS, yxm, Pf3, [23]uint8{0x5f}},
	Optab{AMINPD, yxm, Pe, [23]uint8{0x5d}},
	Optab{AMINPS, yxm, Pm, [23]uint8{0x5d}},
	Optab{AMINSD, yxm, Pf2, [23]uint8{0x5d}},
	Optab{AMINSS, yxm, Pf3, [23]uint8{0x5d}},
	Optab{AMOVAPD, yxmov, Pe, [23]uint8{0x28, 0x29}},
	Optab{AMOVAPS, yxmov, Pm, [23]uint8{0x28, 0x29}},
	Optab{AMOVB, ymovb, Pb, [23]uint8{0x88, 0x8a, 0xb0, 0xc6, 00}},
	Optab{AMOVBLSX, ymb_rl, Pm, [23]uint8{0xbe}},
	Optab{AMOVBLZX, ymb_rl, Pm, [23]uint8{0xb6}},
	Optab{AMOVBQSX, ymb_rl, Pw, [23]uint8{0x0f, 0xbe}},
	Optab{AMOVBQZX, ymb_rl, Pm, [23]uint8{0xb6}},
	Optab{AMOVBWSX, ymb_rl, Pq, [23]uint8{0xbe}},
	Optab{AMOVBWZX, ymb_rl, Pq, [23]uint8{0xb6}},
	Optab{AMOVO, yxmov, Pe, [23]uint8{0x6f, 0x7f}},
	Optab{AMOVOU, yxmov, Pf3, [23]uint8{0x6f, 0x7f}},
	Optab{AMOVHLPS, yxr, Pm, [23]uint8{0x12}},
	Optab{AMOVHPD, yxmov, Pe, [23]uint8{0x16, 0x17}},
	Optab{AMOVHPS, yxmov, Pm, [23]uint8{0x16, 0x17}},
	Optab{AMOVL, ymovl, Px, [23]uint8{0x89, 0x8b, 0x31, 0xb8, 0xc7, 00, 0x6e, 0x7e, Pe, 0x6e, Pe, 0x7e, 0}},
	Optab{AMOVLHPS, yxr, Pm, [23]uint8{0x16}},
	Optab{AMOVLPD, yxmov, Pe, [23]uint8{0x12, 0x13}},
	Optab{AMOVLPS, yxmov, Pm, [23]uint8{0x12, 0x13}},
	Optab{AMOVLQSX, yml_rl, Pw, [23]uint8{0x63}},
	Optab{AMOVLQZX, yml_rl, Px, [23]uint8{0x8b}},
	Optab{AMOVMSKPD, yxrrl, Pq, [23]uint8{0x50}},
	Optab{AMOVMSKPS, yxrrl, Pm, [23]uint8{0x50}},
	Optab{AMOVNTO, yxr_ml, Pe, [23]uint8{0xe7}},
	Optab{AMOVNTPD, yxr_ml, Pe, [23]uint8{0x2b}},
	Optab{AMOVNTPS, yxr_ml, Pm, [23]uint8{0x2b}},
	Optab{AMOVNTQ, ymr_ml, Pm, [23]uint8{0xe7}},
	Optab{AMOVQ, ymovq, Pw, [23]uint8{0x89, 0x8b, 0x31, 0xc7, 00, 0xb8, 0xc7, 00, 0x6f, 0x7f, 0x6e, 0x7e, Pf2, 0xd6, Pf3, 0x7e, Pe, 0xd6, Pe, 0x6e, Pe, 0x7e, 0}},
	Optab{AMOVQOZX, ymrxr, Pf3, [23]uint8{0xd6, 0x7e}},
	Optab{AMOVSB, ynone, Pb, [23]uint8{0xa4}},
	Optab{AMOVSD, yxmov, Pf2, [23]uint8{0x10, 0x11}},
	Optab{AMOVSL, ynone, Px, [23]uint8{0xa5}},
	Optab{AMOVSQ, ynone, Pw, [23]uint8{0xa5}},
	Optab{AMOVSS, yxmov, Pf3, [23]uint8{0x10, 0x11}},
	Optab{AMOVSW, ynone, Pe, [23]uint8{0xa5}},
	Optab{AMOVUPD, yxmov, Pe, [23]uint8{0x10, 0x11}},
	Optab{AMOVUPS, yxmov, Pm, [23]uint8{0x10, 0x11}},
	Optab{AMOVW, ymovw, Pe, [23]uint8{0x89, 0x8b, 0x31, 0xb8, 0xc7, 00, 0}},
	Optab{AMOVWLSX, yml_rl, Pm, [23]uint8{0xbf}},
	Optab{AMOVWLZX, yml_rl, Pm, [23]uint8{0xb7}},
	Optab{AMOVWQSX, yml_rl, Pw, [23]uint8{0x0f, 0xbf}},
	Optab{AMOVWQZX, yml_rl, Pw, [23]uint8{0x0f, 0xb7}},
	Optab{AMULB, ydivb, Pb, [23]uint8{0xf6, 04}},
	Optab{AMULL, ydivl, Px, [23]uint8{0xf7, 04}},
	Optab{AMULPD, yxm, Pe, [23]uint8{0x59}},
	Optab{AMULPS, yxm, Ym, [23]uint8{0x59}},
	Optab{AMULQ, ydivl, Pw, [23]uint8{0xf7, 04}},
	Optab{AMULSD, yxm, Pf2, [23]uint8{0x59}},
	Optab{AMULSS, yxm, Pf3, [23]uint8{0x59}},
	Optab{AMULW, ydivl, Pe, [23]uint8{0xf7, 04}},
	Optab{ANAME, nil, 0, [23]uint8{}},
	Optab{ANEGB, yscond, Pb, [23]uint8{0xf6, 03}},
	Optab{ANEGL, yscond, Px, [23]uint8{0xf7, 03}},
	Optab{ANEGQ, yscond, Pw, [23]uint8{0xf7, 03}},
	Optab{ANEGW, yscond, Pe, [23]uint8{0xf7, 03}},
	Optab{ANOP, ynop, Px, [23]uint8{0, 0}},
	Optab{ANOTB, yscond, Pb, [23]uint8{0xf6, 02}},
	Optab{ANOTL, yscond, Px, [23]uint8{0xf7, 02}},
	Optab{ANOTQ, yscond, Pw, [23]uint8{0xf7, 02}},
	Optab{ANOTW, yscond, Pe, [23]uint8{0xf7, 02}},
	Optab{AORB, yxorb, Pb, [23]uint8{0x0c, 0x80, 01, 0x08, 0x0a}},
	Optab{AORL, yxorl, Px, [23]uint8{0x83, 01, 0x0d, 0x81, 01, 0x09, 0x0b}},
	Optab{AORPD, yxm, Pq, [23]uint8{0x56}},
	Optab{AORPS, yxm, Pm, [23]uint8{0x56}},
	Optab{AORQ, yxorl, Pw, [23]uint8{0x83, 01, 0x0d, 0x81, 01, 0x09, 0x0b}},
	Optab{AORW, yxorl, Pe, [23]uint8{0x83, 01, 0x0d, 0x81, 01, 0x09, 0x0b}},
	Optab{AOUTB, yin, Pb, [23]uint8{0xe6, 0xee}},
	Optab{AOUTL, yin, Px, [23]uint8{0xe7, 0xef}},
	Optab{AOUTSB, ynone, Pb, [23]uint8{0x6e}},
	Optab{AOUTSL, ynone, Px, [23]uint8{0x6f}},
	Optab{AOUTSW, ynone, Pe, [23]uint8{0x6f}},
	Optab{AOUTW, yin, Pe, [23]uint8{0xe7, 0xef}},
	Optab{APACKSSLW, ymm, Py, [23]uint8{0x6b, Pe, 0x6b}},
	Optab{APACKSSWB, ymm, Py, [23]uint8{0x63, Pe, 0x63}},
	Optab{APACKUSWB, ymm, Py, [23]uint8{0x67, Pe, 0x67}},
	Optab{APADDB, ymm, Py, [23]uint8{0xfc, Pe, 0xfc}},
	Optab{APADDL, ymm, Py, [23]uint8{0xfe, Pe, 0xfe}},
	Optab{APADDQ, yxm, Pe, [23]uint8{0xd4}},
	Optab{APADDSB, ymm, Py, [23]uint8{0xec, Pe, 0xec}},
	Optab{APADDSW, ymm, Py, [23]uint8{0xed, Pe, 0xed}},
	Optab{APADDUSB, ymm, Py, [23]uint8{0xdc, Pe, 0xdc}},
	Optab{APADDUSW, ymm, Py, [23]uint8{0xdd, Pe, 0xdd}},
	Optab{APADDW, ymm, Py, [23]uint8{0xfd, Pe, 0xfd}},
	Optab{APAND, ymm, Py, [23]uint8{0xdb, Pe, 0xdb}},
	Optab{APANDN, ymm, Py, [23]uint8{0xdf, Pe, 0xdf}},
	Optab{APAUSE, ynone, Px, [23]uint8{0xf3, 0x90}},
	Optab{APAVGB, ymm, Py, [23]uint8{0xe0, Pe, 0xe0}},
	Optab{APAVGW, ymm, Py, [23]uint8{0xe3, Pe, 0xe3}},
	Optab{APCMPEQB, ymm, Py, [23]uint8{0x74, Pe, 0x74}},
	Optab{APCMPEQL, ymm, Py, [23]uint8{0x76, Pe, 0x76}},
	Optab{APCMPEQW, ymm, Py, [23]uint8{0x75, Pe, 0x75}},
	Optab{APCMPGTB, ymm, Py, [23]uint8{0x64, Pe, 0x64}},
	Optab{APCMPGTL, ymm, Py, [23]uint8{0x66, Pe, 0x66}},
	Optab{APCMPGTW, ymm, Py, [23]uint8{0x65, Pe, 0x65}},
	Optab{APEXTRW, yextrw, Pq, [23]uint8{0xc5, 00}},
	Optab{APF2IL, ymfp, Px, [23]uint8{0x1d}},
	Optab{APF2IW, ymfp, Px, [23]uint8{0x1c}},
	Optab{API2FL, ymfp, Px, [23]uint8{0x0d}},
	Optab{APFACC, ymfp, Px, [23]uint8{0xae}},
	Optab{APFADD, ymfp, Px, [23]uint8{0x9e}},
	Optab{APFCMPEQ, ymfp, Px, [23]uint8{0xb0}},
	Optab{APFCMPGE, ymfp, Px, [23]uint8{0x90}},
	Optab{APFCMPGT, ymfp, Px, [23]uint8{0xa0}},
	Optab{APFMAX, ymfp, Px, [23]uint8{0xa4}},
	Optab{APFMIN, ymfp, Px, [23]uint8{0x94}},
	Optab{APFMUL, ymfp, Px, [23]uint8{0xb4}},
	Optab{APFNACC, ymfp, Px, [23]uint8{0x8a}},
	Optab{APFPNACC, ymfp, Px, [23]uint8{0x8e}},
	Optab{APFRCP, ymfp, Px, [23]uint8{0x96}},
	Optab{APFRCPIT1, ymfp, Px, [23]uint8{0xa6}},
	Optab{APFRCPI2T, ymfp, Px, [23]uint8{0xb6}},
	Optab{APFRSQIT1, ymfp, Px, [23]uint8{0xa7}},
	Optab{APFRSQRT, ymfp, Px, [23]uint8{0x97}},
	Optab{APFSUB, ymfp, Px, [23]uint8{0x9a}},
	Optab{APFSUBR, ymfp, Px, [23]uint8{0xaa}},
	Optab{APINSRW, yinsrw, Pq, [23]uint8{0xc4, 00}},
	Optab{APINSRD, yinsr, Pq, [23]uint8{0x3a, 0x22, 00}},
	Optab{APINSRQ, yinsr, Pq3, [23]uint8{0x3a, 0x22, 00}},
	Optab{APMADDWL, ymm, Py, [23]uint8{0xf5, Pe, 0xf5}},
	Optab{APMAXSW, yxm, Pe, [23]uint8{0xee}},
	Optab{APMAXUB, yxm, Pe, [23]uint8{0xde}},
	Optab{APMINSW, yxm, Pe, [23]uint8{0xea}},
	Optab{APMINUB, yxm, Pe, [23]uint8{0xda}},
	Optab{APMOVMSKB, ymskb, Px, [23]uint8{Pe, 0xd7, 0xd7}},
	Optab{APMULHRW, ymfp, Px, [23]uint8{0xb7}},
	Optab{APMULHUW, ymm, Py, [23]uint8{0xe4, Pe, 0xe4}},
	Optab{APMULHW, ymm, Py, [23]uint8{0xe5, Pe, 0xe5}},
	Optab{APMULLW, ymm, Py, [23]uint8{0xd5, Pe, 0xd5}},
	Optab{APMULULQ, ymm, Py, [23]uint8{0xf4, Pe, 0xf4}},
	Optab{APOPAL, ynone, P32, [23]uint8{0x61}},
	Optab{APOPAW, ynone, Pe, [23]uint8{0x61}},
	Optab{APOPFL, ynone, P32, [23]uint8{0x9d}},
	Optab{APOPFQ, ynone, Py, [23]uint8{0x9d}},
	Optab{APOPFW, ynone, Pe, [23]uint8{0x9d}},
	Optab{APOPL, ypopl, P32, [23]uint8{0x58, 0x8f, 00}},
	Optab{APOPQ, ypopl, Py, [23]uint8{0x58, 0x8f, 00}},
	Optab{APOPW, ypopl, Pe, [23]uint8{0x58, 0x8f, 00}},
	Optab{APOR, ymm, Py, [23]uint8{0xeb, Pe, 0xeb}},
	Optab{APSADBW, yxm, Pq, [23]uint8{0xf6}},
	Optab{APSHUFHW, yxshuf, Pf3, [23]uint8{0x70, 00}},
	Optab{APSHUFL, yxshuf, Pq, [23]uint8{0x70, 00}},
	Optab{APSHUFLW, yxshuf, Pf2, [23]uint8{0x70, 00}},
	Optab{APSHUFW, ymshuf, Pm, [23]uint8{0x70, 00}},
	Optab{APSHUFB, ymshufb, Pq, [23]uint8{0x38, 0x00}},
	Optab{APSLLO, ypsdq, Pq, [23]uint8{0x73, 07}},
	Optab{APSLLL, yps, Py, [23]uint8{0xf2, 0x72, 06, Pe, 0xf2, Pe, 0x72, 06}},
	Optab{APSLLQ, yps, Py, [23]uint8{0xf3, 0x73, 06, Pe, 0xf3, Pe, 0x73, 06}},
	Optab{APSLLW, yps, Py, [23]uint8{0xf1, 0x71, 06, Pe, 0xf1, Pe, 0x71, 06}},
	Optab{APSRAL, yps, Py, [23]uint8{0xe2, 0x72, 04, Pe, 0xe2, Pe, 0x72, 04}},
	Optab{APSRAW, yps, Py, [23]uint8{0xe1, 0x71, 04, Pe, 0xe1, Pe, 0x71, 04}},
	Optab{APSRLO, ypsdq, Pq, [23]uint8{0x73, 03}},
	Optab{APSRLL, yps, Py, [23]uint8{0xd2, 0x72, 02, Pe, 0xd2, Pe, 0x72, 02}},
	Optab{APSRLQ, yps, Py, [23]uint8{0xd3, 0x73, 02, Pe, 0xd3, Pe, 0x73, 02}},
	Optab{APSRLW, yps, Py, [23]uint8{0xd1, 0x71, 02, Pe, 0xe1, Pe, 0x71, 02}},
	Optab{APSUBB, yxm, Pe, [23]uint8{0xf8}},
	Optab{APSUBL, yxm, Pe, [23]uint8{0xfa}},
	Optab{APSUBQ, yxm, Pe, [23]uint8{0xfb}},
	Optab{APSUBSB, yxm, Pe, [23]uint8{0xe8}},
	Optab{APSUBSW, yxm, Pe, [23]uint8{0xe9}},
	Optab{APSUBUSB, yxm, Pe, [23]uint8{0xd8}},
	Optab{APSUBUSW, yxm, Pe, [23]uint8{0xd9}},
	Optab{APSUBW, yxm, Pe, [23]uint8{0xf9}},
	Optab{APSWAPL, ymfp, Px, [23]uint8{0xbb}},
	Optab{APUNPCKHBW, ymm, Py, [23]uint8{0x68, Pe, 0x68}},
	Optab{APUNPCKHLQ, ymm, Py, [23]uint8{0x6a, Pe, 0x6a}},
	Optab{APUNPCKHQDQ, yxm, Pe, [23]uint8{0x6d}},
	Optab{APUNPCKHWL, ymm, Py, [23]uint8{0x69, Pe, 0x69}},
	Optab{APUNPCKLBW, ymm, Py, [23]uint8{0x60, Pe, 0x60}},
	Optab{APUNPCKLLQ, ymm, Py, [23]uint8{0x62, Pe, 0x62}},
	Optab{APUNPCKLQDQ, yxm, Pe, [23]uint8{0x6c}},
	Optab{APUNPCKLWL, ymm, Py, [23]uint8{0x61, Pe, 0x61}},
	Optab{APUSHAL, ynone, P32, [23]uint8{0x60}},
	Optab{APUSHAW, ynone, Pe, [23]uint8{0x60}},
	Optab{APUSHFL, ynone, P32, [23]uint8{0x9c}},
	Optab{APUSHFQ, ynone, Py, [23]uint8{0x9c}},
	Optab{APUSHFW, ynone, Pe, [23]uint8{0x9c}},
	Optab{APUSHL, ypushl, P32, [23]uint8{0x50, 0xff, 06, 0x6a, 0x68}},
	Optab{APUSHQ, ypushl, Py, [23]uint8{0x50, 0xff, 06, 0x6a, 0x68}},
	Optab{APUSHW, ypushl, Pe, [23]uint8{0x50, 0xff, 06, 0x6a, 0x68}},
	Optab{APXOR, ymm, Py, [23]uint8{0xef, Pe, 0xef}},
	Optab{AQUAD, ybyte, Px, [23]uint8{8}},
	Optab{ARCLB, yshb, Pb, [23]uint8{0xd0, 02, 0xc0, 02, 0xd2, 02}},
	Optab{ARCLL, yshl, Px, [23]uint8{0xd1, 02, 0xc1, 02, 0xd3, 02, 0xd3, 02}},
	Optab{ARCLQ, yshl, Pw, [23]uint8{0xd1, 02, 0xc1, 02, 0xd3, 02, 0xd3, 02}},
	Optab{ARCLW, yshl, Pe, [23]uint8{0xd1, 02, 0xc1, 02, 0xd3, 02, 0xd3, 02}},
	Optab{ARCPPS, yxm, Pm, [23]uint8{0x53}},
	Optab{ARCPSS, yxm, Pf3, [23]uint8{0x53}},
	Optab{ARCRB, yshb, Pb, [23]uint8{0xd0, 03, 0xc0, 03, 0xd2, 03}},
	Optab{ARCRL, yshl, Px, [23]uint8{0xd1, 03, 0xc1, 03, 0xd3, 03, 0xd3, 03}},
	Optab{ARCRQ, yshl, Pw, [23]uint8{0xd1, 03, 0xc1, 03, 0xd3, 03, 0xd3, 03}},
	Optab{ARCRW, yshl, Pe, [23]uint8{0xd1, 03, 0xc1, 03, 0xd3, 03, 0xd3, 03}},
	Optab{AREP, ynone, Px, [23]uint8{0xf3}},
	Optab{AREPN, ynone, Px, [23]uint8{0xf2}},
	Optab{ARET, ynone, Px, [23]uint8{0xc3}},
	Optab{ARETFW, yret, Pe, [23]uint8{0xcb, 0xca}},
	Optab{ARETFL, yret, Px, [23]uint8{0xcb, 0xca}},
	Optab{ARETFQ, yret, Pw, [23]uint8{0xcb, 0xca}},
	Optab{AROLB, yshb, Pb, [23]uint8{0xd0, 00, 0xc0, 00, 0xd2, 00}},
	Optab{AROLL, yshl, Px, [23]uint8{0xd1, 00, 0xc1, 00, 0xd3, 00, 0xd3, 00}},
	Optab{AROLQ, yshl, Pw, [23]uint8{0xd1, 00, 0xc1, 00, 0xd3, 00, 0xd3, 00}},
	Optab{AROLW, yshl, Pe, [23]uint8{0xd1, 00, 0xc1, 00, 0xd3, 00, 0xd3, 00}},
	Optab{ARORB, yshb, Pb, [23]uint8{0xd0, 01, 0xc0, 01, 0xd2, 01}},
	Optab{ARORL, yshl, Px, [23]uint8{0xd1, 01, 0xc1, 01, 0xd3, 01, 0xd3, 01}},
	Optab{ARORQ, yshl, Pw, [23]uint8{0xd1, 01, 0xc1, 01, 0xd3, 01, 0xd3, 01}},
	Optab{ARORW, yshl, Pe, [23]uint8{0xd1, 01, 0xc1, 01, 0xd3, 01, 0xd3, 01}},
	Optab{ARSQRTPS, yxm, Pm, [23]uint8{0x52}},
	Optab{ARSQRTSS, yxm, Pf3, [23]uint8{0x52}},
	Optab{ASAHF, ynone, Px, [23]uint8{0x86, 0xe0, 0x50, 0x9d}}, /* XCHGB AH,AL; PUSH AX; POPFL */
	Optab{ASALB, yshb, Pb, [23]uint8{0xd0, 04, 0xc0, 04, 0xd2, 04}},
	Optab{ASALL, yshl, Px, [23]uint8{0xd1, 04, 0xc1, 04, 0xd3, 04, 0xd3, 04}},
	Optab{ASALQ, yshl, Pw, [23]uint8{0xd1, 04, 0xc1, 04, 0xd3, 04, 0xd3, 04}},
	Optab{ASALW, yshl, Pe, [23]uint8{0xd1, 04, 0xc1, 04, 0xd3, 04, 0xd3, 04}},
	Optab{ASARB, yshb, Pb, [23]uint8{0xd0, 07, 0xc0, 07, 0xd2, 07}},
	Optab{ASARL, yshl, Px, [23]uint8{0xd1, 07, 0xc1, 07, 0xd3, 07, 0xd3, 07}},
	Optab{ASARQ, yshl, Pw, [23]uint8{0xd1, 07, 0xc1, 07, 0xd3, 07, 0xd3, 07}},
	Optab{ASARW, yshl, Pe, [23]uint8{0xd1, 07, 0xc1, 07, 0xd3, 07, 0xd3, 07}},
	Optab{ASBBB, yxorb, Pb, [23]uint8{0x1c, 0x80, 03, 0x18, 0x1a}},
	Optab{ASBBL, yxorl, Px, [23]uint8{0x83, 03, 0x1d, 0x81, 03, 0x19, 0x1b}},
	Optab{ASBBQ, yxorl, Pw, [23]uint8{0x83, 03, 0x1d, 0x81, 03, 0x19, 0x1b}},
	Optab{ASBBW, yxorl, Pe, [23]uint8{0x83, 03, 0x1d, 0x81, 03, 0x19, 0x1b}},
	Optab{ASCASB, ynone, Pb, [23]uint8{0xae}},
	Optab{ASCASL, ynone, Px, [23]uint8{0xaf}},
	Optab{ASCASQ, ynone, Pw, [23]uint8{0xaf}},
	Optab{ASCASW, ynone, Pe, [23]uint8{0xaf}},
	Optab{ASETCC, yscond, Pb, [23]uint8{0x0f, 0x93, 00}},
	Optab{ASETCS, yscond, Pb, [23]uint8{0x0f, 0x92, 00}},
	Optab{ASETEQ, yscond, Pb, [23]uint8{0x0f, 0x94, 00}},
	Optab{ASETGE, yscond, Pb, [23]uint8{0x0f, 0x9d, 00}},
	Optab{ASETGT, yscond, Pb, [23]uint8{0x0f, 0x9f, 00}},
	Optab{ASETHI, yscond, Pb, [23]uint8{0x0f, 0x97, 00}},
	Optab{ASETLE, yscond, Pb, [23]uint8{0x0f, 0x9e, 00}},
	Optab{ASETLS, yscond, Pb, [23]uint8{0x0f, 0x96, 00}},
	Optab{ASETLT, yscond, Pb, [23]uint8{0x0f, 0x9c, 00}},
	Optab{ASETMI, yscond, Pb, [23]uint8{0x0f, 0x98, 00}},
	Optab{ASETNE, yscond, Pb, [23]uint8{0x0f, 0x95, 00}},
	Optab{ASETOC, yscond, Pb, [23]uint8{0x0f, 0x91, 00}},
	Optab{ASETOS, yscond, Pb, [23]uint8{0x0f, 0x90, 00}},
	Optab{ASETPC, yscond, Pb, [23]uint8{0x0f, 0x9b, 00}},
	Optab{ASETPL, yscond, Pb, [23]uint8{0x0f, 0x99, 00}},
	Optab{ASETPS, yscond, Pb, [23]uint8{0x0f, 0x9a, 00}},
	Optab{ASHLB, yshb, Pb, [23]uint8{0xd0, 04, 0xc0, 04, 0xd2, 04}},
	Optab{ASHLL, yshl, Px, [23]uint8{0xd1, 04, 0xc1, 04, 0xd3, 04, 0xd3, 04}},
	Optab{ASHLQ, yshl, Pw, [23]uint8{0xd1, 04, 0xc1, 04, 0xd3, 04, 0xd3, 04}},
	Optab{ASHLW, yshl, Pe, [23]uint8{0xd1, 04, 0xc1, 04, 0xd3, 04, 0xd3, 04}},
	Optab{ASHRB, yshb, Pb, [23]uint8{0xd0, 05, 0xc0, 05, 0xd2, 05}},
	Optab{ASHRL, yshl, Px, [23]uint8{0xd1, 05, 0xc1, 05, 0xd3, 05, 0xd3, 05}},
	Optab{ASHRQ, yshl, Pw, [23]uint8{0xd1, 05, 0xc1, 05, 0xd3, 05, 0xd3, 05}},
	Optab{ASHRW, yshl, Pe, [23]uint8{0xd1, 05, 0xc1, 05, 0xd3, 05, 0xd3, 05}},
	Optab{ASHUFPD, yxshuf, Pq, [23]uint8{0xc6, 00}},
	Optab{ASHUFPS, yxshuf, Pm, [23]uint8{0xc6, 00}},
	Optab{ASQRTPD, yxm, Pe, [23]uint8{0x51}},
	Optab{ASQRTPS, yxm, Pm, [23]uint8{0x51}},
	Optab{ASQRTSD, yxm, Pf2, [23]uint8{0x51}},
	Optab{ASQRTSS, yxm, Pf3, [23]uint8{0x51}},
	Optab{ASTC, ynone, Px, [23]uint8{0xf9}},
	Optab{ASTD, ynone, Px, [23]uint8{0xfd}},
	Optab{ASTI, ynone, Px, [23]uint8{0xfb}},
	Optab{ASTMXCSR, ysvrs, Pm, [23]uint8{0xae, 03, 0xae, 03}},
	Optab{ASTOSB, ynone, Pb, [23]uint8{0xaa}},
	Optab{ASTOSL, ynone, Px, [23]uint8{0xab}},
	Optab{ASTOSQ, ynone, Pw, [23]uint8{0xab}},
	Optab{ASTOSW, ynone, Pe, [23]uint8{0xab}},
	Optab{ASUBB, yxorb, Pb, [23]uint8{0x2c, 0x80, 05, 0x28, 0x2a}},
	Optab{ASUBL, yaddl, Px, [23]uint8{0x83, 05, 0x2d, 0x81, 05, 0x29, 0x2b}},
	Optab{ASUBPD, yxm, Pe, [23]uint8{0x5c}},
	Optab{ASUBPS, yxm, Pm, [23]uint8{0x5c}},
	Optab{ASUBQ, yaddl, Pw, [23]uint8{0x83, 05, 0x2d, 0x81, 05, 0x29, 0x2b}},
	Optab{ASUBSD, yxm, Pf2, [23]uint8{0x5c}},
	Optab{ASUBSS, yxm, Pf3, [23]uint8{0x5c}},
	Optab{ASUBW, yaddl, Pe, [23]uint8{0x83, 05, 0x2d, 0x81, 05, 0x29, 0x2b}},
	Optab{ASWAPGS, ynone, Pm, [23]uint8{0x01, 0xf8}},
	Optab{ASYSCALL, ynone, Px, [23]uint8{0x0f, 0x05}}, /* fast syscall */
	Optab{ATESTB, ytestb, Pb, [23]uint8{0xa8, 0xf6, 00, 0x84, 0x84}},
	Optab{ATESTL, ytestl, Px, [23]uint8{0xa9, 0xf7, 00, 0x85, 0x85}},
	Optab{ATESTQ, ytestl, Pw, [23]uint8{0xa9, 0xf7, 00, 0x85, 0x85}},
	Optab{ATESTW, ytestl, Pe, [23]uint8{0xa9, 0xf7, 00, 0x85, 0x85}},
	Optab{ATEXT, ytext, Px, [23]uint8{}},
	Optab{AUCOMISD, yxcmp, Pe, [23]uint8{0x2e}},
	Optab{AUCOMISS, yxcmp, Pm, [23]uint8{0x2e}},
	Optab{AUNPCKHPD, yxm, Pe, [23]uint8{0x15}},
	Optab{AUNPCKHPS, yxm, Pm, [23]uint8{0x15}},
	Optab{AUNPCKLPD, yxm, Pe, [23]uint8{0x14}},
	Optab{AUNPCKLPS, yxm, Pm, [23]uint8{0x14}},
	Optab{AVERR, ydivl, Pm, [23]uint8{0x00, 04}},
	Optab{AVERW, ydivl, Pm, [23]uint8{0x00, 05}},
	Optab{AWAIT, ynone, Px, [23]uint8{0x9b}},
	Optab{AWORD, ybyte, Px, [23]uint8{2}},
	Optab{AXCHGB, yml_mb, Pb, [23]uint8{0x86, 0x86}},
	Optab{AXCHGL, yxchg, Px, [23]uint8{0x90, 0x90, 0x87, 0x87}},
	Optab{AXCHGQ, yxchg, Pw, [23]uint8{0x90, 0x90, 0x87, 0x87}},
	Optab{AXCHGW, yxchg, Pe, [23]uint8{0x90, 0x90, 0x87, 0x87}},
	Optab{AXLAT, ynone, Px, [23]uint8{0xd7}},
	Optab{AXORB, yxorb, Pb, [23]uint8{0x34, 0x80, 06, 0x30, 0x32}},
	Optab{AXORL, yxorl, Px, [23]uint8{0x83, 06, 0x35, 0x81, 06, 0x31, 0x33}},
	Optab{AXORPD, yxm, Pe, [23]uint8{0x57}},
	Optab{AXORPS, yxm, Pm, [23]uint8{0x57}},
	Optab{AXORQ, yxorl, Pw, [23]uint8{0x83, 06, 0x35, 0x81, 06, 0x31, 0x33}},
	Optab{AXORW, yxorl, Pe, [23]uint8{0x83, 06, 0x35, 0x81, 06, 0x31, 0x33}},
	Optab{AFMOVB, yfmvx, Px, [23]uint8{0xdf, 04}},
	Optab{AFMOVBP, yfmvp, Px, [23]uint8{0xdf, 06}},
	Optab{AFMOVD, yfmvd, Px, [23]uint8{0xdd, 00, 0xdd, 02, 0xd9, 00, 0xdd, 02}},
	Optab{AFMOVDP, yfmvdp, Px, [23]uint8{0xdd, 03, 0xdd, 03}},
	Optab{AFMOVF, yfmvf, Px, [23]uint8{0xd9, 00, 0xd9, 02}},
	Optab{AFMOVFP, yfmvp, Px, [23]uint8{0xd9, 03}},
	Optab{AFMOVL, yfmvf, Px, [23]uint8{0xdb, 00, 0xdb, 02}},
	Optab{AFMOVLP, yfmvp, Px, [23]uint8{0xdb, 03}},
	Optab{AFMOVV, yfmvx, Px, [23]uint8{0xdf, 05}},
	Optab{AFMOVVP, yfmvp, Px, [23]uint8{0xdf, 07}},
	Optab{AFMOVW, yfmvf, Px, [23]uint8{0xdf, 00, 0xdf, 02}},
	Optab{AFMOVWP, yfmvp, Px, [23]uint8{0xdf, 03}},
	Optab{AFMOVX, yfmvx, Px, [23]uint8{0xdb, 05}},
	Optab{AFMOVXP, yfmvp, Px, [23]uint8{0xdb, 07}},
	Optab{AFCOMB, nil, 0, [23]uint8{}},
	Optab{AFCOMBP, nil, 0, [23]uint8{}},
	Optab{AFCOMD, yfadd, Px, [23]uint8{0xdc, 02, 0xd8, 02, 0xdc, 02}},  /* botch */
	Optab{AFCOMDP, yfadd, Px, [23]uint8{0xdc, 03, 0xd8, 03, 0xdc, 03}}, /* botch */
	Optab{AFCOMDPP, ycompp, Px, [23]uint8{0xde, 03}},
	Optab{AFCOMF, yfmvx, Px, [23]uint8{0xd8, 02}},
	Optab{AFCOMFP, yfmvx, Px, [23]uint8{0xd8, 03}},
	Optab{AFCOML, yfmvx, Px, [23]uint8{0xda, 02}},
	Optab{AFCOMLP, yfmvx, Px, [23]uint8{0xda, 03}},
	Optab{AFCOMW, yfmvx, Px, [23]uint8{0xde, 02}},
	Optab{AFCOMWP, yfmvx, Px, [23]uint8{0xde, 03}},
	Optab{AFUCOM, ycompp, Px, [23]uint8{0xdd, 04}},
	Optab{AFUCOMP, ycompp, Px, [23]uint8{0xdd, 05}},
	Optab{AFUCOMPP, ycompp, Px, [23]uint8{0xda, 13}},
	Optab{AFADDDP, yfaddp, Px, [23]uint8{0xde, 00}},
	Optab{AFADDW, yfmvx, Px, [23]uint8{0xde, 00}},
	Optab{AFADDL, yfmvx, Px, [23]uint8{0xda, 00}},
	Optab{AFADDF, yfmvx, Px, [23]uint8{0xd8, 00}},
	Optab{AFADDD, yfadd, Px, [23]uint8{0xdc, 00, 0xd8, 00, 0xdc, 00}},
	Optab{AFMULDP, yfaddp, Px, [23]uint8{0xde, 01}},
	Optab{AFMULW, yfmvx, Px, [23]uint8{0xde, 01}},
	Optab{AFMULL, yfmvx, Px, [23]uint8{0xda, 01}},
	Optab{AFMULF, yfmvx, Px, [23]uint8{0xd8, 01}},
	Optab{AFMULD, yfadd, Px, [23]uint8{0xdc, 01, 0xd8, 01, 0xdc, 01}},
	Optab{AFSUBDP, yfaddp, Px, [23]uint8{0xde, 05}},
	Optab{AFSUBW, yfmvx, Px, [23]uint8{0xde, 04}},
	Optab{AFSUBL, yfmvx, Px, [23]uint8{0xda, 04}},
	Optab{AFSUBF, yfmvx, Px, [23]uint8{0xd8, 04}},
	Optab{AFSUBD, yfadd, Px, [23]uint8{0xdc, 04, 0xd8, 04, 0xdc, 05}},
	Optab{AFSUBRDP, yfaddp, Px, [23]uint8{0xde, 04}},
	Optab{AFSUBRW, yfmvx, Px, [23]uint8{0xde, 05}},
	Optab{AFSUBRL, yfmvx, Px, [23]uint8{0xda, 05}},
	Optab{AFSUBRF, yfmvx, Px, [23]uint8{0xd8, 05}},
	Optab{AFSUBRD, yfadd, Px, [23]uint8{0xdc, 05, 0xd8, 05, 0xdc, 04}},
	Optab{AFDIVDP, yfaddp, Px, [23]uint8{0xde, 07}},
	Optab{AFDIVW, yfmvx, Px, [23]uint8{0xde, 06}},
	Optab{AFDIVL, yfmvx, Px, [23]uint8{0xda, 06}},
	Optab{AFDIVF, yfmvx, Px, [23]uint8{0xd8, 06}},
	Optab{AFDIVD, yfadd, Px, [23]uint8{0xdc, 06, 0xd8, 06, 0xdc, 07}},
	Optab{AFDIVRDP, yfaddp, Px, [23]uint8{0xde, 06}},
	Optab{AFDIVRW, yfmvx, Px, [23]uint8{0xde, 07}},
	Optab{AFDIVRL, yfmvx, Px, [23]uint8{0xda, 07}},
	Optab{AFDIVRF, yfmvx, Px, [23]uint8{0xd8, 07}},
	Optab{AFDIVRD, yfadd, Px, [23]uint8{0xdc, 07, 0xd8, 07, 0xdc, 06}},
	Optab{AFXCHD, yfxch, Px, [23]uint8{0xd9, 01, 0xd9, 01}},
	Optab{AFFREE, nil, 0, [23]uint8{}},
	Optab{AFLDCW, ystcw, Px, [23]uint8{0xd9, 05, 0xd9, 05}},
	Optab{AFLDENV, ystcw, Px, [23]uint8{0xd9, 04, 0xd9, 04}},
	Optab{AFRSTOR, ysvrs, Px, [23]uint8{0xdd, 04, 0xdd, 04}},
	Optab{AFSAVE, ysvrs, Px, [23]uint8{0xdd, 06, 0xdd, 06}},
	Optab{AFSTCW, ystcw, Px, [23]uint8{0xd9, 07, 0xd9, 07}},
	Optab{AFSTENV, ystcw, Px, [23]uint8{0xd9, 06, 0xd9, 06}},
	Optab{AFSTSW, ystsw, Px, [23]uint8{0xdd, 07, 0xdf, 0xe0}},
	Optab{AF2XM1, ynone, Px, [23]uint8{0xd9, 0xf0}},
	Optab{AFABS, ynone, Px, [23]uint8{0xd9, 0xe1}},
	Optab{AFCHS, ynone, Px, [23]uint8{0xd9, 0xe0}},
	Optab{AFCLEX, ynone, Px, [23]uint8{0xdb, 0xe2}},
	Optab{AFCOS, ynone, Px, [23]uint8{0xd9, 0xff}},
	Optab{AFDECSTP, ynone, Px, [23]uint8{0xd9, 0xf6}},
	Optab{AFINCSTP, ynone, Px, [23]uint8{0xd9, 0xf7}},
	Optab{AFINIT, ynone, Px, [23]uint8{0xdb, 0xe3}},
	Optab{AFLD1, ynone, Px, [23]uint8{0xd9, 0xe8}},
	Optab{AFLDL2E, ynone, Px, [23]uint8{0xd9, 0xea}},
	Optab{AFLDL2T, ynone, Px, [23]uint8{0xd9, 0xe9}},
	Optab{AFLDLG2, ynone, Px, [23]uint8{0xd9, 0xec}},
	Optab{AFLDLN2, ynone, Px, [23]uint8{0xd9, 0xed}},
	Optab{AFLDPI, ynone, Px, [23]uint8{0xd9, 0xeb}},
	Optab{AFLDZ, ynone, Px, [23]uint8{0xd9, 0xee}},
	Optab{AFNOP, ynone, Px, [23]uint8{0xd9, 0xd0}},
	Optab{AFPATAN, ynone, Px, [23]uint8{0xd9, 0xf3}},
	Optab{AFPREM, ynone, Px, [23]uint8{0xd9, 0xf8}},
	Optab{AFPREM1, ynone, Px, [23]uint8{0xd9, 0xf5}},
	Optab{AFPTAN, ynone, Px, [23]uint8{0xd9, 0xf2}},
	Optab{AFRNDINT, ynone, Px, [23]uint8{0xd9, 0xfc}},
	Optab{AFSCALE, ynone, Px, [23]uint8{0xd9, 0xfd}},
	Optab{AFSIN, ynone, Px, [23]uint8{0xd9, 0xfe}},
	Optab{AFSINCOS, ynone, Px, [23]uint8{0xd9, 0xfb}},
	Optab{AFSQRT, ynone, Px, [23]uint8{0xd9, 0xfa}},
	Optab{AFTST, ynone, Px, [23]uint8{0xd9, 0xe4}},
	Optab{AFXAM, ynone, Px, [23]uint8{0xd9, 0xe5}},
	Optab{AFXTRACT, ynone, Px, [23]uint8{0xd9, 0xf4}},
	Optab{AFYL2X, ynone, Px, [23]uint8{0xd9, 0xf1}},
	Optab{AFYL2XP1, ynone, Px, [23]uint8{0xd9, 0xf9}},
	Optab{ACMPXCHGB, yrb_mb, Pb, [23]uint8{0x0f, 0xb0}},
	Optab{ACMPXCHGL, yrl_ml, Px, [23]uint8{0x0f, 0xb1}},
	Optab{ACMPXCHGW, yrl_ml, Pe, [23]uint8{0x0f, 0xb1}},
	Optab{ACMPXCHGQ, yrl_ml, Pw, [23]uint8{0x0f, 0xb1}},
	Optab{ACMPXCHG8B, yscond, Pm, [23]uint8{0xc7, 01}},
	Optab{AINVD, ynone, Pm, [23]uint8{0x08}},
	Optab{AINVLPG, ymbs, Pm, [23]uint8{0x01, 07}},
	Optab{ALFENCE, ynone, Pm, [23]uint8{0xae, 0xe8}},
	Optab{AMFENCE, ynone, Pm, [23]uint8{0xae, 0xf0}},
	Optab{AMOVNTIL, yrl_ml, Pm, [23]uint8{0xc3}},
	Optab{AMOVNTIQ, yrl_ml, Pw, [23]uint8{0x0f, 0xc3}},
	Optab{ARDMSR, ynone, Pm, [23]uint8{0x32}},
	Optab{ARDPMC, ynone, Pm, [23]uint8{0x33}},
	Optab{ARDTSC, ynone, Pm, [23]uint8{0x31}},
	Optab{ARSM, ynone, Pm, [23]uint8{0xaa}},
	Optab{ASFENCE, ynone, Pm, [23]uint8{0xae, 0xf8}},
	Optab{ASYSRET, ynone, Pm, [23]uint8{0x07}},
	Optab{AWBINVD, ynone, Pm, [23]uint8{0x09}},
	Optab{AWRMSR, ynone, Pm, [23]uint8{0x30}},
	Optab{AXADDB, yrb_mb, Pb, [23]uint8{0x0f, 0xc0}},
	Optab{AXADDL, yrl_ml, Px, [23]uint8{0x0f, 0xc1}},
	Optab{AXADDQ, yrl_ml, Pw, [23]uint8{0x0f, 0xc1}},
	Optab{AXADDW, yrl_ml, Pe, [23]uint8{0x0f, 0xc1}},
	Optab{ACRC32B, ycrc32l, Px, [23]uint8{0xf2, 0x0f, 0x38, 0xf0, 0}},
	Optab{ACRC32Q, ycrc32l, Pw, [23]uint8{0xf2, 0x0f, 0x38, 0xf1, 0}},
	Optab{APREFETCHT0, yprefetch, Pm, [23]uint8{0x18, 01}},
	Optab{APREFETCHT1, yprefetch, Pm, [23]uint8{0x18, 02}},
	Optab{APREFETCHT2, yprefetch, Pm, [23]uint8{0x18, 03}},
	Optab{APREFETCHNTA, yprefetch, Pm, [23]uint8{0x18, 00}},
	Optab{AMOVQL, yrl_ml, Px, [23]uint8{0x89}},
	Optab{AUNDEF, ynone, Px, [23]uint8{0x0f, 0x0b}},
	Optab{AAESENC, yaes, Pq, [23]uint8{0x38, 0xdc, 0}},
	Optab{AAESENCLAST, yaes, Pq, [23]uint8{0x38, 0xdd, 0}},
	Optab{AAESDEC, yaes, Pq, [23]uint8{0x38, 0xde, 0}},
	Optab{AAESDECLAST, yaes, Pq, [23]uint8{0x38, 0xdf, 0}},
	Optab{AAESIMC, yaes, Pq, [23]uint8{0x38, 0xdb, 0}},
	Optab{AAESKEYGENASSIST, yaes2, Pq, [23]uint8{0x3a, 0xdf, 0}},
	Optab{APSHUFD, yaes2, Pq, [23]uint8{0x70, 0}},
	Optab{APCLMULQDQ, yxshuf, Pq, [23]uint8{0x3a, 0x44, 0}},
	Optab{AUSEFIELD, ynop, Px, [23]uint8{0, 0}},
	Optab{ATYPE, nil, 0, [23]uint8{}},
	Optab{AFUNCDATA, yfuncdata, Px, [23]uint8{0, 0}},
	Optab{APCDATA, ypcdata, Px, [23]uint8{0, 0}},
	Optab{ACHECKNIL, nil, 0, [23]uint8{}},
	Optab{AVARDEF, nil, 0, [23]uint8{}},
	Optab{AVARKILL, nil, 0, [23]uint8{}},
	Optab{ADUFFCOPY, yduff, Px, [23]uint8{0xe8}},
	Optab{ADUFFZERO, yduff, Px, [23]uint8{0xe8}},
	Optab{AEND, nil, 0, [23]uint8{}},
	Optab{0, nil, 0, [23]uint8{}},
}

var opindex [ALAST + 1]*Optab

// isextern reports whether s describes an external symbol that must avoid pc-relative addressing.
// This happens on systems like Solaris that call .so functions instead of system calls.
// It does not seem to be necessary for any other systems. This is probably working
// around a Solaris-specific bug that should be fixed differently, but we don't know
// what that bug is. And this does fix it.
func isextern(s *obj.LSym) int {

	// All the Solaris dynamic imports from libc.so begin with "libc_".
	return bool2int(strings.HasPrefix(s.Name, "libc_"))
}

// single-instruction no-ops of various lengths.
// constructed by hand and disassembled with gdb to verify.
// see http://www.agner.org/optimize/optimizing_assembly.pdf for discussion.
var nop = [][16]uint8{
	[16]uint8{0x90},
	[16]uint8{0x66, 0x90},
	[16]uint8{0x0F, 0x1F, 0x00},
	[16]uint8{0x0F, 0x1F, 0x40, 0x00},
	[16]uint8{0x0F, 0x1F, 0x44, 0x00, 0x00},
	[16]uint8{0x66, 0x0F, 0x1F, 0x44, 0x00, 0x00},
	[16]uint8{0x0F, 0x1F, 0x80, 0x00, 0x00, 0x00, 0x00},
	[16]uint8{0x0F, 0x1F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00},
	[16]uint8{0x66, 0x0F, 0x1F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00},
}

// Native Client rejects the repeated 0x66 prefix.
// {0x66, 0x66, 0x0F, 0x1F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00},
func fillnop(p []byte, n int) {

	var m int

	for n > 0 {
		m = n
		if m > len(nop) {
			m = len(nop)
		}
		copy(p[:m], nop[m-1][:m])
		p = p[m:]
		n -= m
	}
}

func naclpad(ctxt *obj.Link, s *obj.LSym, c int32, pad int32) int32 {
	obj.Symgrow(ctxt, s, int64(c)+int64(pad))
	fillnop(s.P[c:], int(pad))
	return c + pad
}

func spadjop(ctxt *obj.Link, p *obj.Prog, l int, q int) int {
	if p.Mode != 64 || ctxt.Arch.Ptrsize == 4 {
		return l
	}
	return q
}

func span6(ctxt *obj.Link, s *obj.LSym) {
	var p *obj.Prog
	var q *obj.Prog
	var c int32
	var v int32
	var loop int32
	var bp []byte
	var n int
	var m int
	var i int

	ctxt.Cursym = s

	if s.P != nil {
		return
	}

	if ycover[0] == 0 {
		instinit()
	}

	for p = ctxt.Cursym.Text; p != nil; p = p.Link {
		n = 0
		if p.To.Type == D_BRANCH {
			if p.Pcond == nil {
				p.Pcond = p
			}
		}
		q = p.Pcond
		if q != nil {
			if q.Back != 2 {
				n = 1
			}
		}
		p.Back = uint8(n)
		if p.As == AADJSP {
			p.To.Type = D_SP
			v = int32(-p.From.Offset)
			p.From.Offset = int64(v)
			p.As = int16(spadjop(ctxt, p, AADDL, AADDQ))
			if v < 0 {
				p.As = int16(spadjop(ctxt, p, ASUBL, ASUBQ))
				v = -v
				p.From.Offset = int64(v)
			}

			if v == 0 {
				p.As = ANOP
			}
		}
	}

	for p = s.Text; p != nil; p = p.Link {
		p.Back = 2 // use short branches first time through
		q = p.Pcond
		if q != nil && (q.Back&2 != 0) {
			p.Back |= 1 // backward jump
			q.Back |= 4 // loop head
		}

		if p.As == AADJSP {
			p.To.Type = D_SP
			v = int32(-p.From.Offset)
			p.From.Offset = int64(v)
			p.As = int16(spadjop(ctxt, p, AADDL, AADDQ))
			if v < 0 {
				p.As = int16(spadjop(ctxt, p, ASUBL, ASUBQ))
				v = -v
				p.From.Offset = int64(v)
			}

			if v == 0 {
				p.As = ANOP
			}
		}
	}

	n = 0
	for {
		loop = 0
		for i = 0; i < len(s.R); i++ {
			s.R[i] = obj.Reloc{}
		}
		s.R = s.R[:0]
		s.P = s.P[:0]
		c = 0
		for p = s.Text; p != nil; p = p.Link {
			if ctxt.Headtype == obj.Hnacl && p.Isize > 0 {
				var deferreturn *obj.LSym

				if deferreturn == nil {
					deferreturn = obj.Linklookup(ctxt, "runtime.deferreturn", 0)
				}

				// pad everything to avoid crossing 32-byte boundary
				if c>>5 != (c+int32(p.Isize)-1)>>5 {

					c = naclpad(ctxt, s, c, -c&31)
				}

				// pad call deferreturn to start at 32-byte boundary
				// so that subtracting 5 in jmpdefer will jump back
				// to that boundary and rerun the call.
				if p.As == ACALL && p.To.Sym == deferreturn {

					c = naclpad(ctxt, s, c, -c&31)
				}

				// pad call to end at 32-byte boundary
				if p.As == ACALL {

					c = naclpad(ctxt, s, c, -(c+int32(p.Isize))&31)
				}

				// the linker treats REP and STOSQ as different instructions
				// but in fact the REP is a prefix on the STOSQ.
				// make sure REP has room for 2 more bytes, so that
				// padding will not be inserted before the next instruction.
				if (p.As == AREP || p.As == AREPN) && c>>5 != (c+3-1)>>5 {

					c = naclpad(ctxt, s, c, -c&31)
				}

				// same for LOCK.
				// various instructions follow; the longest is 4 bytes.
				// give ourselves 8 bytes so as to avoid surprises.
				if p.As == ALOCK && c>>5 != (c+8-1)>>5 {

					c = naclpad(ctxt, s, c, -c&31)
				}
			}

			if (p.Back&4 != 0) && c&(LoopAlign-1) != 0 {
				// pad with NOPs
				v = -c & (LoopAlign - 1)

				if v <= MaxLoopPad {
					obj.Symgrow(ctxt, s, int64(c)+int64(v))
					fillnop(s.P[c:], int(v))
					c += v
				}
			}

			p.Pc = int64(c)

			// process forward jumps to p
			for q = p.Comefrom; q != nil; q = q.Forwd {

				v = int32(p.Pc - (q.Pc + int64(q.Mark)))
				if q.Back&2 != 0 { // short
					if v > 127 {
						loop++
						q.Back ^= 2
					}

					if q.As == AJCXZL {
						s.P[q.Pc+2] = byte(v)
					} else {

						s.P[q.Pc+1] = byte(v)
					}
				} else {

					bp = s.P[q.Pc+int64(q.Mark)-4:]
					bp[0] = byte(v)
					bp = bp[1:]
					bp[0] = byte(v >> 8)
					bp = bp[1:]
					bp[0] = byte(v >> 16)
					bp = bp[1:]
					bp[0] = byte(v >> 24)
				}
			}

			p.Comefrom = nil

			p.Pc = int64(c)
			asmins(ctxt, p)
			m = -cap(ctxt.Andptr) + cap(ctxt.And[:])
			if int(p.Isize) != m {
				p.Isize = uint8(m)
				loop++
			}

			obj.Symgrow(ctxt, s, p.Pc+int64(m))
			copy(s.P[p.Pc:][:m], ctxt.And[:m])
			p.Mark = uint16(m)
			c += int32(m)
		}

		n++
		if n > 20 {
			ctxt.Diag("span must be looping")
			log.Fatalf("loop")
		}
		if !(loop != 0) {
			break
		}
	}

	if ctxt.Headtype == obj.Hnacl {
		c = naclpad(ctxt, s, c, -c&31)
	}

	c += -c & (FuncAlign - 1)
	s.Size = int64(c)

	if false { /* debug['a'] > 1 */
		fmt.Printf("span1 %s %d (%d tries)\n %.6x", s.Name, s.Size, n, 0)
		for i = 0; i < len(s.P); i++ {
			fmt.Printf(" %.2x", s.P[i])
			if i%16 == 15 {
				fmt.Printf("\n  %.6x", uint(i+1))
			}
		}

		if i%16 != 0 {
			fmt.Printf("\n")
		}

		for i = 0; i < len(s.R); i++ {
			var r *obj.Reloc

			r = &s.R[i]
			fmt.Printf(" rel %#.4x/%d %s%+d\n", uint32(r.Off), r.Siz, r.Sym.Name, r.Add)
		}
	}
}

func instinit() {
	var c int
	var i int

	for i = 1; optab[i].as != 0; i++ {
		c = int(optab[i].as)
		if opindex[c] != nil {
			log.Fatalf("phase error in optab: %d (%v)", i, Aconv(c))
		}
		opindex[c] = &optab[i]
	}

	for i = 0; i < Ymax; i++ {
		ycover[i*Ymax+i] = 1
	}

	ycover[Yi0*Ymax+Yi8] = 1
	ycover[Yi1*Ymax+Yi8] = 1

	ycover[Yi0*Ymax+Ys32] = 1
	ycover[Yi1*Ymax+Ys32] = 1
	ycover[Yi8*Ymax+Ys32] = 1

	ycover[Yi0*Ymax+Yi32] = 1
	ycover[Yi1*Ymax+Yi32] = 1
	ycover[Yi8*Ymax+Yi32] = 1
	ycover[Ys32*Ymax+Yi32] = 1

	ycover[Yi0*Ymax+Yi64] = 1
	ycover[Yi1*Ymax+Yi64] = 1
	ycover[Yi8*Ymax+Yi64] = 1
	ycover[Ys32*Ymax+Yi64] = 1
	ycover[Yi32*Ymax+Yi64] = 1

	ycover[Yal*Ymax+Yrb] = 1
	ycover[Ycl*Ymax+Yrb] = 1
	ycover[Yax*Ymax+Yrb] = 1
	ycover[Ycx*Ymax+Yrb] = 1
	ycover[Yrx*Ymax+Yrb] = 1
	ycover[Yrl*Ymax+Yrb] = 1

	ycover[Ycl*Ymax+Ycx] = 1

	ycover[Yax*Ymax+Yrx] = 1
	ycover[Ycx*Ymax+Yrx] = 1

	ycover[Yax*Ymax+Yrl] = 1
	ycover[Ycx*Ymax+Yrl] = 1
	ycover[Yrx*Ymax+Yrl] = 1

	ycover[Yf0*Ymax+Yrf] = 1

	ycover[Yal*Ymax+Ymb] = 1
	ycover[Ycl*Ymax+Ymb] = 1
	ycover[Yax*Ymax+Ymb] = 1
	ycover[Ycx*Ymax+Ymb] = 1
	ycover[Yrx*Ymax+Ymb] = 1
	ycover[Yrb*Ymax+Ymb] = 1
	ycover[Yrl*Ymax+Ymb] = 1
	ycover[Ym*Ymax+Ymb] = 1

	ycover[Yax*Ymax+Yml] = 1
	ycover[Ycx*Ymax+Yml] = 1
	ycover[Yrx*Ymax+Yml] = 1
	ycover[Yrl*Ymax+Yml] = 1
	ycover[Ym*Ymax+Yml] = 1

	ycover[Yax*Ymax+Ymm] = 1
	ycover[Ycx*Ymax+Ymm] = 1
	ycover[Yrx*Ymax+Ymm] = 1
	ycover[Yrl*Ymax+Ymm] = 1
	ycover[Ym*Ymax+Ymm] = 1
	ycover[Ymr*Ymax+Ymm] = 1

	ycover[Ym*Ymax+Yxm] = 1
	ycover[Yxr*Ymax+Yxm] = 1

	for i = 0; i < D_NONE; i++ {
		reg[i] = -1
		if i >= D_AL && i <= D_R15B {
			reg[i] = (i - D_AL) & 7
			if i >= D_SPB && i <= D_DIB {
				regrex[i] = 0x40
			}
			if i >= D_R8B && i <= D_R15B {
				regrex[i] = Rxr | Rxx | Rxb
			}
		}

		if i >= D_AH && i <= D_BH {
			reg[i] = 4 + ((i - D_AH) & 7)
		}
		if i >= D_AX && i <= D_R15 {
			reg[i] = (i - D_AX) & 7
			if i >= D_R8 {
				regrex[i] = Rxr | Rxx | Rxb
			}
		}

		if i >= D_F0 && i <= D_F0+7 {
			reg[i] = (i - D_F0) & 7
		}
		if i >= D_M0 && i <= D_M0+7 {
			reg[i] = (i - D_M0) & 7
		}
		if i >= D_X0 && i <= D_X0+15 {
			reg[i] = (i - D_X0) & 7
			if i >= D_X0+8 {
				regrex[i] = Rxr | Rxx | Rxb
			}
		}

		if i >= D_CR+8 && i <= D_CR+15 {
			regrex[i] = Rxr
		}
	}
}

func prefixof(ctxt *obj.Link, a *obj.Addr) int {
	switch a.Type {
	case D_INDIR + D_CS:
		return 0x2e

	case D_INDIR + D_DS:
		return 0x3e

	case D_INDIR + D_ES:
		return 0x26

	case D_INDIR + D_FS:
		return 0x64

	case D_INDIR + D_GS:
		return 0x65

		// NOTE: Systems listed here should be only systems that
	// support direct TLS references like 8(TLS) implemented as
	// direct references from FS or GS. Systems that require
	// the initial-exec model, where you load the TLS base into
	// a register and then index from that register, do not reach
	// this code and should not be listed.
	case D_INDIR + D_TLS:
		switch ctxt.Headtype {

		default:
			log.Fatalf("unknown TLS base register for %s", obj.Headstr(ctxt.Headtype))

		case obj.Hdragonfly,
			obj.Hfreebsd,
			obj.Hlinux,
			obj.Hnetbsd,
			obj.Hopenbsd,
			obj.Hsolaris:
			return 0x64 // FS

		case obj.Hdarwin:
			return 0x65 // GS
		}
	}

	switch a.Index {
	case D_CS:
		return 0x2e

	case D_DS:
		return 0x3e

	case D_ES:
		return 0x26

	case D_FS:
		return 0x64

	case D_GS:
		return 0x65
	}

	return 0
}

func oclass(ctxt *obj.Link, a *obj.Addr) int {
	var v int64
	var l int32

	if a.Type >= D_INDIR || a.Index != D_NONE {
		if a.Index != D_NONE && a.Scale == 0 {
			if a.Type == D_ADDR {
				switch a.Index {
				case D_EXTERN,
					D_STATIC:
					if a.Sym != nil && isextern(a.Sym) != 0 {
						return Yi32
					}
					return Yiauto // use pc-relative addressing

				case D_AUTO,
					D_PARAM:
					return Yiauto
				}

				return Yxxx
			}

			return Ycol
		}

		return Ym
	}

	switch a.Type {
	case D_AL:
		return Yal

	case D_AX:
		return Yax

		/*
			case D_SPB:
		*/
	case D_BPB,
		D_SIB,
		D_DIB,
		D_R8B,
		D_R9B,
		D_R10B,
		D_R11B,
		D_R12B,
		D_R13B,
		D_R14B,
		D_R15B:
		if ctxt.Asmode != 64 {

			return Yxxx
		}
		fallthrough

	case D_DL,
		D_BL,
		D_AH,
		D_CH,
		D_DH,
		D_BH:
		return Yrb

	case D_CL:
		return Ycl

	case D_CX:
		return Ycx

	case D_DX,
		D_BX:
		return Yrx

	case D_R8, /* not really Yrl */
		D_R9,
		D_R10,
		D_R11,
		D_R12,
		D_R13,
		D_R14,
		D_R15:
		if ctxt.Asmode != 64 {

			return Yxxx
		}
		fallthrough

	case D_SP,
		D_BP,
		D_SI,
		D_DI:
		return Yrl

	case D_F0 + 0:
		return Yf0

	case D_F0 + 1,
		D_F0 + 2,
		D_F0 + 3,
		D_F0 + 4,
		D_F0 + 5,
		D_F0 + 6,
		D_F0 + 7:
		return Yrf

	case D_M0 + 0,
		D_M0 + 1,
		D_M0 + 2,
		D_M0 + 3,
		D_M0 + 4,
		D_M0 + 5,
		D_M0 + 6,
		D_M0 + 7:
		return Ymr

	case D_X0 + 0,
		D_X0 + 1,
		D_X0 + 2,
		D_X0 + 3,
		D_X0 + 4,
		D_X0 + 5,
		D_X0 + 6,
		D_X0 + 7,
		D_X0 + 8,
		D_X0 + 9,
		D_X0 + 10,
		D_X0 + 11,
		D_X0 + 12,
		D_X0 + 13,
		D_X0 + 14,
		D_X0 + 15:
		return Yxr

	case D_NONE:
		return Ynone

	case D_CS:
		return Ycs
	case D_SS:
		return Yss
	case D_DS:
		return Yds
	case D_ES:
		return Yes
	case D_FS:
		return Yfs
	case D_GS:
		return Ygs
	case D_TLS:
		return Ytls

	case D_GDTR:
		return Ygdtr
	case D_IDTR:
		return Yidtr
	case D_LDTR:
		return Yldtr
	case D_MSW:
		return Ymsw
	case D_TASK:
		return Ytask

	case D_CR + 0:
		return Ycr0
	case D_CR + 1:
		return Ycr1
	case D_CR + 2:
		return Ycr2
	case D_CR + 3:
		return Ycr3
	case D_CR + 4:
		return Ycr4
	case D_CR + 5:
		return Ycr5
	case D_CR + 6:
		return Ycr6
	case D_CR + 7:
		return Ycr7
	case D_CR + 8:
		return Ycr8

	case D_DR + 0:
		return Ydr0
	case D_DR + 1:
		return Ydr1
	case D_DR + 2:
		return Ydr2
	case D_DR + 3:
		return Ydr3
	case D_DR + 4:
		return Ydr4
	case D_DR + 5:
		return Ydr5
	case D_DR + 6:
		return Ydr6
	case D_DR + 7:
		return Ydr7

	case D_TR + 0:
		return Ytr0
	case D_TR + 1:
		return Ytr1
	case D_TR + 2:
		return Ytr2
	case D_TR + 3:
		return Ytr3
	case D_TR + 4:
		return Ytr4
	case D_TR + 5:
		return Ytr5
	case D_TR + 6:
		return Ytr6
	case D_TR + 7:
		return Ytr7

	case D_EXTERN,
		D_STATIC,
		D_AUTO,
		D_PARAM:
		return Ym

	case D_CONST,
		D_ADDR:
		if a.Sym == nil {
			v = a.Offset
			if v == 0 {
				return Yi0
			}
			if v == 1 {
				return Yi1
			}
			if v >= -128 && v <= 127 {
				return Yi8
			}
			l = int32(v)
			if int64(l) == v {
				return Ys32 /* can sign extend */
			}
			if v>>32 == 0 {
				return Yi32 /* unsigned */
			}
			return Yi64
		}

		return Yi32

	case D_BRANCH:
		return Ybr
	}

	return Yxxx
}

func asmidx(ctxt *obj.Link, scale int, index int, base int) {
	var i int

	switch index {
	default:
		goto bad

	case D_NONE:
		i = 4 << 3
		goto bas

	case D_R8,
		D_R9,
		D_R10,
		D_R11,
		D_R12,
		D_R13,
		D_R14,
		D_R15:
		if ctxt.Asmode != 64 {
			goto bad
		}
		fallthrough

	case D_AX,
		D_CX,
		D_DX,
		D_BX,
		D_BP,
		D_SI,
		D_DI:
		i = reg[index] << 3
		break
	}

	switch scale {
	default:
		goto bad

	case 1:
		break

	case 2:
		i |= 1 << 6

	case 4:
		i |= 2 << 6

	case 8:
		i |= 3 << 6
		break
	}

bas:
	switch base {
	default:
		goto bad

	case D_NONE: /* must be mod=00 */
		i |= 5

	case D_R8,
		D_R9,
		D_R10,
		D_R11,
		D_R12,
		D_R13,
		D_R14,
		D_R15:
		if ctxt.Asmode != 64 {
			goto bad
		}
		fallthrough

	case D_AX,
		D_CX,
		D_DX,
		D_BX,
		D_SP,
		D_BP,
		D_SI,
		D_DI:
		i |= reg[base]
		break
	}

	ctxt.Andptr[0] = byte(i)
	ctxt.Andptr = ctxt.Andptr[1:]
	return

bad:
	ctxt.Diag("asmidx: bad address %d/%d/%d", scale, index, base)
	ctxt.Andptr[0] = 0
	ctxt.Andptr = ctxt.Andptr[1:]
	return
}

func put4(ctxt *obj.Link, v int32) {
	ctxt.Andptr[0] = byte(v)
	ctxt.Andptr[1] = byte(v >> 8)
	ctxt.Andptr[2] = byte(v >> 16)
	ctxt.Andptr[3] = byte(v >> 24)
	ctxt.Andptr = ctxt.Andptr[4:]
}

func relput4(ctxt *obj.Link, p *obj.Prog, a *obj.Addr) {
	var v int64
	var rel obj.Reloc
	var r *obj.Reloc

	v = vaddr(ctxt, p, a, &rel)
	if rel.Siz != 0 {
		if rel.Siz != 4 {
			ctxt.Diag("bad reloc")
		}
		r = obj.Addrel(ctxt.Cursym)
		*r = rel
		r.Off = int32(p.Pc + int64(-cap(ctxt.Andptr)+cap(ctxt.And[:])))
	}

	put4(ctxt, int32(v))
}

func put8(ctxt *obj.Link, v int64) {
	ctxt.Andptr[0] = byte(v)
	ctxt.Andptr[1] = byte(v >> 8)
	ctxt.Andptr[2] = byte(v >> 16)
	ctxt.Andptr[3] = byte(v >> 24)
	ctxt.Andptr[4] = byte(v >> 32)
	ctxt.Andptr[5] = byte(v >> 40)
	ctxt.Andptr[6] = byte(v >> 48)
	ctxt.Andptr[7] = byte(v >> 56)
	ctxt.Andptr = ctxt.Andptr[8:]
}

/*
static void
relput8(Prog *p, Addr *a)
{
	vlong v;
	Reloc rel, *r;

	v = vaddr(ctxt, p, a, &rel);
	if(rel.siz != 0) {
		r = addrel(ctxt->cursym);
		*r = rel;
		r->siz = 8;
		r->off = p->pc + ctxt->andptr - ctxt->and;
	}
	put8(ctxt, v);
}
*/
func vaddr(ctxt *obj.Link, p *obj.Prog, a *obj.Addr, r *obj.Reloc) int64 {

	var t int
	var v int64
	var s *obj.LSym

	if r != nil {
		*r = obj.Reloc{}
	}

	t = int(a.Type)
	v = a.Offset
	if t == D_ADDR {
		t = int(a.Index)
	}
	switch t {
	case D_STATIC,
		D_EXTERN:
		s = a.Sym
		if r == nil {
			ctxt.Diag("need reloc for %v", Dconv(p, 0, a))
			log.Fatalf("reloc")
		}

		if isextern(s) != 0 {
			r.Siz = 4
			r.Type = obj.R_ADDR
		} else {

			r.Siz = 4
			r.Type = obj.R_PCREL
		}

		r.Off = -1 // caller must fill in
		r.Sym = s
		r.Add = v
		v = 0
		if s.Type == obj.STLSBSS {
			r.Xadd = r.Add - int64(r.Siz)
			r.Type = obj.R_TLS
			r.Xsym = s
		}

	case D_INDIR + D_TLS:
		if r == nil {
			ctxt.Diag("need reloc for %v", Dconv(p, 0, a))
			log.Fatalf("reloc")
		}

		r.Type = obj.R_TLS_LE
		r.Siz = 4
		r.Off = -1 // caller must fill in
		r.Add = v
		v = 0
		break
	}

	return v
}

func asmandsz(ctxt *obj.Link, p *obj.Prog, a *obj.Addr, r int, rex int, m64 int) {
	var v int32
	var t int
	var scale int
	var rel obj.Reloc

	rex &= 0x40 | Rxr
	v = int32(a.Offset)
	t = int(a.Type)
	rel.Siz = 0
	if a.Index != D_NONE && a.Index != D_TLS {
		if t < D_INDIR {
			switch t {
			default:
				goto bad

			case D_EXTERN,
				D_STATIC:
				if !(isextern(a.Sym) != 0) {
					goto bad
				}
				t = D_NONE
				v = int32(vaddr(ctxt, p, a, &rel))

			case D_AUTO,
				D_PARAM:
				t = D_SP
				break
			}
		} else {

			t -= D_INDIR
		}
		ctxt.Rexflag |= regrex[int(a.Index)]&Rxx | regrex[t]&Rxb | rex
		if t == D_NONE {
			ctxt.Andptr[0] = byte(0<<6 | 4<<0 | r<<3)
			ctxt.Andptr = ctxt.Andptr[1:]
			asmidx(ctxt, int(a.Scale), int(a.Index), t)
			goto putrelv
		}

		if v == 0 && rel.Siz == 0 && t != D_BP && t != D_R13 {
			ctxt.Andptr[0] = byte(0<<6 | 4<<0 | r<<3)
			ctxt.Andptr = ctxt.Andptr[1:]
			asmidx(ctxt, int(a.Scale), int(a.Index), t)
			return
		}

		if v >= -128 && v < 128 && rel.Siz == 0 {
			ctxt.Andptr[0] = byte(1<<6 | 4<<0 | r<<3)
			ctxt.Andptr = ctxt.Andptr[1:]
			asmidx(ctxt, int(a.Scale), int(a.Index), t)
			ctxt.Andptr[0] = byte(v)
			ctxt.Andptr = ctxt.Andptr[1:]
			return
		}

		ctxt.Andptr[0] = byte(2<<6 | 4<<0 | r<<3)
		ctxt.Andptr = ctxt.Andptr[1:]
		asmidx(ctxt, int(a.Scale), int(a.Index), t)
		goto putrelv
	}

	if t >= D_AL && t <= D_X0+15 {
		if v != 0 {
			goto bad
		}
		ctxt.Andptr[0] = byte(3<<6 | reg[t]<<0 | r<<3)
		ctxt.Andptr = ctxt.Andptr[1:]
		ctxt.Rexflag |= regrex[t]&(0x40|Rxb) | rex
		return
	}

	scale = int(a.Scale)
	if t < D_INDIR {
		switch a.Type {
		default:
			goto bad

		case D_STATIC,
			D_EXTERN:
			t = D_NONE
			v = int32(vaddr(ctxt, p, a, &rel))

		case D_AUTO,
			D_PARAM:
			t = D_SP
			break
		}

		scale = 1
	} else {

		t -= D_INDIR
	}
	if t == D_TLS {
		v = int32(vaddr(ctxt, p, a, &rel))
	}

	ctxt.Rexflag |= regrex[t]&Rxb | rex
	if t == D_NONE || (D_CS <= t && t <= D_GS) || t == D_TLS {
		if (a.Sym == nil || !(isextern(a.Sym) != 0)) && t == D_NONE && (a.Type == D_STATIC || a.Type == D_EXTERN) || ctxt.Asmode != 64 {
			ctxt.Andptr[0] = byte(0<<6 | 5<<0 | r<<3)
			ctxt.Andptr = ctxt.Andptr[1:]
			goto putrelv
		}

		/* temporary */
		ctxt.Andptr[0] = byte(0<<6 | 4<<0 | r<<3)
		ctxt.Andptr = ctxt.Andptr[1:] /* sib present */
		ctxt.Andptr[0] = 0<<6 | 4<<3 | 5<<0
		ctxt.Andptr = ctxt.Andptr[1:] /* DS:d32 */
		goto putrelv
	}

	if t == D_SP || t == D_R12 {
		if v == 0 {
			ctxt.Andptr[0] = byte(0<<6 | reg[t]<<0 | r<<3)
			ctxt.Andptr = ctxt.Andptr[1:]
			asmidx(ctxt, scale, D_NONE, t)
			return
		}

		if v >= -128 && v < 128 {
			ctxt.Andptr[0] = byte(1<<6 | reg[t]<<0 | r<<3)
			ctxt.Andptr = ctxt.Andptr[1:]
			asmidx(ctxt, scale, D_NONE, t)
			ctxt.Andptr[0] = byte(v)
			ctxt.Andptr = ctxt.Andptr[1:]
			return
		}

		ctxt.Andptr[0] = byte(2<<6 | reg[t]<<0 | r<<3)
		ctxt.Andptr = ctxt.Andptr[1:]
		asmidx(ctxt, scale, D_NONE, t)
		goto putrelv
	}

	if t >= D_AX && t <= D_R15 {
		if a.Index == D_TLS {
			rel = obj.Reloc{}
			rel.Type = obj.R_TLS_IE
			rel.Siz = 4
			rel.Sym = nil
			rel.Add = int64(v)
			v = 0
		}

		if v == 0 && rel.Siz == 0 && t != D_BP && t != D_R13 {
			ctxt.Andptr[0] = byte(0<<6 | reg[t]<<0 | r<<3)
			ctxt.Andptr = ctxt.Andptr[1:]
			return
		}

		if v >= -128 && v < 128 && rel.Siz == 0 {
			ctxt.Andptr[0] = byte(1<<6 | reg[t]<<0 | r<<3)
			ctxt.Andptr[1] = byte(v)
			ctxt.Andptr = ctxt.Andptr[2:]
			return
		}

		ctxt.Andptr[0] = byte(2<<6 | reg[t]<<0 | r<<3)
		ctxt.Andptr = ctxt.Andptr[1:]
		goto putrelv
	}

	goto bad

putrelv:
	if rel.Siz != 0 {
		var r *obj.Reloc

		if rel.Siz != 4 {
			ctxt.Diag("bad rel")
			goto bad
		}

		r = obj.Addrel(ctxt.Cursym)
		*r = rel
		r.Off = int32(ctxt.Curp.Pc + int64(-cap(ctxt.Andptr)+cap(ctxt.And[:])))
	}

	put4(ctxt, v)
	return

bad:
	ctxt.Diag("asmand: bad address %v", Dconv(p, 0, a))
	return
}

func asmand(ctxt *obj.Link, p *obj.Prog, a *obj.Addr, ra *obj.Addr) {
	asmandsz(ctxt, p, a, reg[ra.Type], regrex[ra.Type], 0)
}

func asmando(ctxt *obj.Link, p *obj.Prog, a *obj.Addr, o int) {
	asmandsz(ctxt, p, a, o, 0, 0)
}

func bytereg(a *obj.Addr, t *uint8) {
	if a.Index == D_NONE && (a.Type >= D_AX && a.Type <= D_R15) {
		a.Type = D_AL + (a.Type - D_AX)
		*t = 0
	}
}

const (
	E = 0xff
)

var ymovtab = []Movtab{
	/* push */
	Movtab{APUSHL, Ycs, Ynone, 0, [4]uint8{0x0e, E, 0, 0}},
	Movtab{APUSHL, Yss, Ynone, 0, [4]uint8{0x16, E, 0, 0}},
	Movtab{APUSHL, Yds, Ynone, 0, [4]uint8{0x1e, E, 0, 0}},
	Movtab{APUSHL, Yes, Ynone, 0, [4]uint8{0x06, E, 0, 0}},
	Movtab{APUSHL, Yfs, Ynone, 0, [4]uint8{0x0f, 0xa0, E, 0}},
	Movtab{APUSHL, Ygs, Ynone, 0, [4]uint8{0x0f, 0xa8, E, 0}},
	Movtab{APUSHQ, Yfs, Ynone, 0, [4]uint8{0x0f, 0xa0, E, 0}},
	Movtab{APUSHQ, Ygs, Ynone, 0, [4]uint8{0x0f, 0xa8, E, 0}},
	Movtab{APUSHW, Ycs, Ynone, 0, [4]uint8{Pe, 0x0e, E, 0}},
	Movtab{APUSHW, Yss, Ynone, 0, [4]uint8{Pe, 0x16, E, 0}},
	Movtab{APUSHW, Yds, Ynone, 0, [4]uint8{Pe, 0x1e, E, 0}},
	Movtab{APUSHW, Yes, Ynone, 0, [4]uint8{Pe, 0x06, E, 0}},
	Movtab{APUSHW, Yfs, Ynone, 0, [4]uint8{Pe, 0x0f, 0xa0, E}},
	Movtab{APUSHW, Ygs, Ynone, 0, [4]uint8{Pe, 0x0f, 0xa8, E}},

	/* pop */
	Movtab{APOPL, Ynone, Yds, 0, [4]uint8{0x1f, E, 0, 0}},
	Movtab{APOPL, Ynone, Yes, 0, [4]uint8{0x07, E, 0, 0}},
	Movtab{APOPL, Ynone, Yss, 0, [4]uint8{0x17, E, 0, 0}},
	Movtab{APOPL, Ynone, Yfs, 0, [4]uint8{0x0f, 0xa1, E, 0}},
	Movtab{APOPL, Ynone, Ygs, 0, [4]uint8{0x0f, 0xa9, E, 0}},
	Movtab{APOPQ, Ynone, Yfs, 0, [4]uint8{0x0f, 0xa1, E, 0}},
	Movtab{APOPQ, Ynone, Ygs, 0, [4]uint8{0x0f, 0xa9, E, 0}},
	Movtab{APOPW, Ynone, Yds, 0, [4]uint8{Pe, 0x1f, E, 0}},
	Movtab{APOPW, Ynone, Yes, 0, [4]uint8{Pe, 0x07, E, 0}},
	Movtab{APOPW, Ynone, Yss, 0, [4]uint8{Pe, 0x17, E, 0}},
	Movtab{APOPW, Ynone, Yfs, 0, [4]uint8{Pe, 0x0f, 0xa1, E}},
	Movtab{APOPW, Ynone, Ygs, 0, [4]uint8{Pe, 0x0f, 0xa9, E}},

	/* mov seg */
	Movtab{AMOVW, Yes, Yml, 1, [4]uint8{0x8c, 0, 0, 0}},
	Movtab{AMOVW, Ycs, Yml, 1, [4]uint8{0x8c, 1, 0, 0}},
	Movtab{AMOVW, Yss, Yml, 1, [4]uint8{0x8c, 2, 0, 0}},
	Movtab{AMOVW, Yds, Yml, 1, [4]uint8{0x8c, 3, 0, 0}},
	Movtab{AMOVW, Yfs, Yml, 1, [4]uint8{0x8c, 4, 0, 0}},
	Movtab{AMOVW, Ygs, Yml, 1, [4]uint8{0x8c, 5, 0, 0}},
	Movtab{AMOVW, Yml, Yes, 2, [4]uint8{0x8e, 0, 0, 0}},
	Movtab{AMOVW, Yml, Ycs, 2, [4]uint8{0x8e, 1, 0, 0}},
	Movtab{AMOVW, Yml, Yss, 2, [4]uint8{0x8e, 2, 0, 0}},
	Movtab{AMOVW, Yml, Yds, 2, [4]uint8{0x8e, 3, 0, 0}},
	Movtab{AMOVW, Yml, Yfs, 2, [4]uint8{0x8e, 4, 0, 0}},
	Movtab{AMOVW, Yml, Ygs, 2, [4]uint8{0x8e, 5, 0, 0}},

	/* mov cr */
	Movtab{AMOVL, Ycr0, Yml, 3, [4]uint8{0x0f, 0x20, 0, 0}},
	Movtab{AMOVL, Ycr2, Yml, 3, [4]uint8{0x0f, 0x20, 2, 0}},
	Movtab{AMOVL, Ycr3, Yml, 3, [4]uint8{0x0f, 0x20, 3, 0}},
	Movtab{AMOVL, Ycr4, Yml, 3, [4]uint8{0x0f, 0x20, 4, 0}},
	Movtab{AMOVL, Ycr8, Yml, 3, [4]uint8{0x0f, 0x20, 8, 0}},
	Movtab{AMOVQ, Ycr0, Yml, 3, [4]uint8{0x0f, 0x20, 0, 0}},
	Movtab{AMOVQ, Ycr2, Yml, 3, [4]uint8{0x0f, 0x20, 2, 0}},
	Movtab{AMOVQ, Ycr3, Yml, 3, [4]uint8{0x0f, 0x20, 3, 0}},
	Movtab{AMOVQ, Ycr4, Yml, 3, [4]uint8{0x0f, 0x20, 4, 0}},
	Movtab{AMOVQ, Ycr8, Yml, 3, [4]uint8{0x0f, 0x20, 8, 0}},
	Movtab{AMOVL, Yml, Ycr0, 4, [4]uint8{0x0f, 0x22, 0, 0}},
	Movtab{AMOVL, Yml, Ycr2, 4, [4]uint8{0x0f, 0x22, 2, 0}},
	Movtab{AMOVL, Yml, Ycr3, 4, [4]uint8{0x0f, 0x22, 3, 0}},
	Movtab{AMOVL, Yml, Ycr4, 4, [4]uint8{0x0f, 0x22, 4, 0}},
	Movtab{AMOVL, Yml, Ycr8, 4, [4]uint8{0x0f, 0x22, 8, 0}},
	Movtab{AMOVQ, Yml, Ycr0, 4, [4]uint8{0x0f, 0x22, 0, 0}},
	Movtab{AMOVQ, Yml, Ycr2, 4, [4]uint8{0x0f, 0x22, 2, 0}},
	Movtab{AMOVQ, Yml, Ycr3, 4, [4]uint8{0x0f, 0x22, 3, 0}},
	Movtab{AMOVQ, Yml, Ycr4, 4, [4]uint8{0x0f, 0x22, 4, 0}},
	Movtab{AMOVQ, Yml, Ycr8, 4, [4]uint8{0x0f, 0x22, 8, 0}},

	/* mov dr */
	Movtab{AMOVL, Ydr0, Yml, 3, [4]uint8{0x0f, 0x21, 0, 0}},
	Movtab{AMOVL, Ydr6, Yml, 3, [4]uint8{0x0f, 0x21, 6, 0}},
	Movtab{AMOVL, Ydr7, Yml, 3, [4]uint8{0x0f, 0x21, 7, 0}},
	Movtab{AMOVQ, Ydr0, Yml, 3, [4]uint8{0x0f, 0x21, 0, 0}},
	Movtab{AMOVQ, Ydr6, Yml, 3, [4]uint8{0x0f, 0x21, 6, 0}},
	Movtab{AMOVQ, Ydr7, Yml, 3, [4]uint8{0x0f, 0x21, 7, 0}},
	Movtab{AMOVL, Yml, Ydr0, 4, [4]uint8{0x0f, 0x23, 0, 0}},
	Movtab{AMOVL, Yml, Ydr6, 4, [4]uint8{0x0f, 0x23, 6, 0}},
	Movtab{AMOVL, Yml, Ydr7, 4, [4]uint8{0x0f, 0x23, 7, 0}},
	Movtab{AMOVQ, Yml, Ydr0, 4, [4]uint8{0x0f, 0x23, 0, 0}},
	Movtab{AMOVQ, Yml, Ydr6, 4, [4]uint8{0x0f, 0x23, 6, 0}},
	Movtab{AMOVQ, Yml, Ydr7, 4, [4]uint8{0x0f, 0x23, 7, 0}},

	/* mov tr */
	Movtab{AMOVL, Ytr6, Yml, 3, [4]uint8{0x0f, 0x24, 6, 0}},
	Movtab{AMOVL, Ytr7, Yml, 3, [4]uint8{0x0f, 0x24, 7, 0}},
	Movtab{AMOVL, Yml, Ytr6, 4, [4]uint8{0x0f, 0x26, 6, E}},
	Movtab{AMOVL, Yml, Ytr7, 4, [4]uint8{0x0f, 0x26, 7, E}},

	/* lgdt, sgdt, lidt, sidt */
	Movtab{AMOVL, Ym, Ygdtr, 4, [4]uint8{0x0f, 0x01, 2, 0}},
	Movtab{AMOVL, Ygdtr, Ym, 3, [4]uint8{0x0f, 0x01, 0, 0}},
	Movtab{AMOVL, Ym, Yidtr, 4, [4]uint8{0x0f, 0x01, 3, 0}},
	Movtab{AMOVL, Yidtr, Ym, 3, [4]uint8{0x0f, 0x01, 1, 0}},
	Movtab{AMOVQ, Ym, Ygdtr, 4, [4]uint8{0x0f, 0x01, 2, 0}},
	Movtab{AMOVQ, Ygdtr, Ym, 3, [4]uint8{0x0f, 0x01, 0, 0}},
	Movtab{AMOVQ, Ym, Yidtr, 4, [4]uint8{0x0f, 0x01, 3, 0}},
	Movtab{AMOVQ, Yidtr, Ym, 3, [4]uint8{0x0f, 0x01, 1, 0}},

	/* lldt, sldt */
	Movtab{AMOVW, Yml, Yldtr, 4, [4]uint8{0x0f, 0x00, 2, 0}},
	Movtab{AMOVW, Yldtr, Yml, 3, [4]uint8{0x0f, 0x00, 0, 0}},

	/* lmsw, smsw */
	Movtab{AMOVW, Yml, Ymsw, 4, [4]uint8{0x0f, 0x01, 6, 0}},
	Movtab{AMOVW, Ymsw, Yml, 3, [4]uint8{0x0f, 0x01, 4, 0}},

	/* ltr, str */
	Movtab{AMOVW, Yml, Ytask, 4, [4]uint8{0x0f, 0x00, 3, 0}},
	Movtab{AMOVW, Ytask, Yml, 3, [4]uint8{0x0f, 0x00, 1, 0}},

	/* load full pointer */
	Movtab{AMOVL, Yml, Ycol, 5, [4]uint8{0, 0, 0, 0}},
	Movtab{AMOVW, Yml, Ycol, 5, [4]uint8{Pe, 0, 0, 0}},

	/* double shift */
	Movtab{ASHLL, Ycol, Yml, 6, [4]uint8{0xa4, 0xa5, 0, 0}},
	Movtab{ASHRL, Ycol, Yml, 6, [4]uint8{0xac, 0xad, 0, 0}},
	Movtab{ASHLQ, Ycol, Yml, 6, [4]uint8{Pw, 0xa4, 0xa5, 0}},
	Movtab{ASHRQ, Ycol, Yml, 6, [4]uint8{Pw, 0xac, 0xad, 0}},
	Movtab{ASHLW, Ycol, Yml, 6, [4]uint8{Pe, 0xa4, 0xa5, 0}},
	Movtab{ASHRW, Ycol, Yml, 6, [4]uint8{Pe, 0xac, 0xad, 0}},

	/* load TLS base */
	Movtab{AMOVQ, Ytls, Yrl, 7, [4]uint8{0, 0, 0, 0}},
	Movtab{0, 0, 0, 0, [4]uint8{}},
}

func isax(a *obj.Addr) int {
	switch a.Type {
	case D_AX,
		D_AL,
		D_AH,
		D_INDIR + D_AX:
		return 1
	}

	if a.Index == D_AX {
		return 1
	}
	return 0
}

func subreg(p *obj.Prog, from int, to int) {
	if false { /*debug['Q']*/
		fmt.Printf("\n%v\ts/%v/%v/\n", p, Rconv(from), Rconv(to))
	}

	if int(p.From.Type) == from {
		p.From.Type = int16(to)
	}
	if int(p.To.Type) == from {
		p.To.Type = int16(to)
	}

	if int(p.From.Index) == from {
		p.From.Index = uint8(to)
	}
	if int(p.To.Index) == from {
		p.To.Index = uint8(to)
	}

	from += D_INDIR
	if int(p.From.Type) == from {
		p.From.Type = int16(to + D_INDIR)
	}
	if int(p.To.Type) == from {
		p.To.Type = int16(to + D_INDIR)
	}

	if false { /*debug['Q']*/
		fmt.Printf("%v\n", p)
	}
}

func mediaop(ctxt *obj.Link, o *Optab, op int, osize int, z int) int {
	switch op {
	case Pm,
		Pe,
		Pf2,
		Pf3:
		if osize != 1 {
			if op != Pm {
				ctxt.Andptr[0] = byte(op)
				ctxt.Andptr = ctxt.Andptr[1:]
			}
			ctxt.Andptr[0] = Pm
			ctxt.Andptr = ctxt.Andptr[1:]
			z++
			op = int(o.op[z])
			break
		}
		fallthrough

	default:
		if -cap(ctxt.Andptr) == -cap(ctxt.And) || ctxt.And[-cap(ctxt.Andptr)+cap(ctxt.And[:])-1] != Pm {
			ctxt.Andptr[0] = Pm
			ctxt.Andptr = ctxt.Andptr[1:]
		}
		break
	}

	ctxt.Andptr[0] = byte(op)
	ctxt.Andptr = ctxt.Andptr[1:]
	return z
}

func doasm(ctxt *obj.Link, p *obj.Prog) {
	var o *Optab
	var q *obj.Prog
	var pp obj.Prog
	var t []byte
	var mo []Movtab
	var z int
	var op int
	var ft int
	var tt int
	var xo int
	var l int
	var pre int
	var v int64
	var rel obj.Reloc
	var r *obj.Reloc
	var a *obj.Addr

	ctxt.Curp = p // TODO

	o = opindex[p.As]

	if o == nil {
		ctxt.Diag("asmins: missing op %v", p)
		return
	}

	pre = prefixof(ctxt, &p.From)
	if pre != 0 {
		ctxt.Andptr[0] = byte(pre)
		ctxt.Andptr = ctxt.Andptr[1:]
	}
	pre = prefixof(ctxt, &p.To)
	if pre != 0 {
		ctxt.Andptr[0] = byte(pre)
		ctxt.Andptr = ctxt.Andptr[1:]
	}

	if p.Ft == 0 {
		p.Ft = uint8(oclass(ctxt, &p.From))
	}
	if p.Tt == 0 {
		p.Tt = uint8(oclass(ctxt, &p.To))
	}

	ft = int(p.Ft) * Ymax
	tt = int(p.Tt) * Ymax

	t = o.ytab
	if t == nil {
		ctxt.Diag("asmins: noproto %v", p)
		return
	}

	xo = bool2int(o.op[0] == 0x0f)
	for z = 0; t[0] != 0; (func() { z += int(t[3]) + xo; t = t[4:] })() {
		if ycover[ft+int(t[0])] != 0 {
			if ycover[tt+int(t[1])] != 0 {
				goto found
			}
		}
	}
	goto domov

found:
	switch o.prefix {
	case Pq: /* 16 bit escape and opcode escape */
		ctxt.Andptr[0] = Pe
		ctxt.Andptr = ctxt.Andptr[1:]

		ctxt.Andptr[0] = Pm
		ctxt.Andptr = ctxt.Andptr[1:]

	case Pq3: /* 16 bit escape, Rex.w, and opcode escape */
		ctxt.Andptr[0] = Pe
		ctxt.Andptr = ctxt.Andptr[1:]

		ctxt.Andptr[0] = Pw
		ctxt.Andptr = ctxt.Andptr[1:]
		ctxt.Andptr[0] = Pm
		ctxt.Andptr = ctxt.Andptr[1:]

	case Pf2, /* xmm opcode escape */
		Pf3:
		ctxt.Andptr[0] = byte(o.prefix)
		ctxt.Andptr = ctxt.Andptr[1:]

		ctxt.Andptr[0] = Pm
		ctxt.Andptr = ctxt.Andptr[1:]

	case Pm: /* opcode escape */
		ctxt.Andptr[0] = Pm
		ctxt.Andptr = ctxt.Andptr[1:]

	case Pe: /* 16 bit escape */
		ctxt.Andptr[0] = Pe
		ctxt.Andptr = ctxt.Andptr[1:]

	case Pw: /* 64-bit escape */
		if p.Mode != 64 {

			ctxt.Diag("asmins: illegal 64: %v", p)
		}
		ctxt.Rexflag |= Pw

	case Pb: /* botch */
		bytereg(&p.From, &p.Ft)

		bytereg(&p.To, &p.Tt)

	case P32: /* 32 bit but illegal if 64-bit mode */
		if p.Mode == 64 {

			ctxt.Diag("asmins: illegal in 64-bit mode: %v", p)
		}

	case Py: /* 64-bit only, no prefix */
		if p.Mode != 64 {

			ctxt.Diag("asmins: illegal in %d-bit mode: %v", p.Mode, p)
		}
		break
	}

	if z >= len(o.op) {
		log.Fatalf("asmins bad table %v", p)
	}
	op = int(o.op[z])
	if op == 0x0f {
		ctxt.Andptr[0] = byte(op)
		ctxt.Andptr = ctxt.Andptr[1:]
		z++
		op = int(o.op[z])
	}

	switch t[2] {
	default:
		ctxt.Diag("asmins: unknown z %d %v", t[2], p)
		return

	case Zpseudo:
		break

	case Zlit:
		for ; ; z++ {
			op = int(o.op[z])
			if !(op != 0) {
				break
			}
			ctxt.Andptr[0] = byte(op)
			ctxt.Andptr = ctxt.Andptr[1:]
		}

	case Zlitm_r:
		for ; ; z++ {
			op = int(o.op[z])
			if !(op != 0) {
				break
			}
			ctxt.Andptr[0] = byte(op)
			ctxt.Andptr = ctxt.Andptr[1:]
		}
		asmand(ctxt, p, &p.From, &p.To)

	case Zmb_r:
		bytereg(&p.From, &p.Ft)
		fallthrough

		/* fall through */
	case Zm_r:
		ctxt.Andptr[0] = byte(op)
		ctxt.Andptr = ctxt.Andptr[1:]

		asmand(ctxt, p, &p.From, &p.To)

	case Zm2_r:
		ctxt.Andptr[0] = byte(op)
		ctxt.Andptr = ctxt.Andptr[1:]
		ctxt.Andptr[0] = byte(o.op[z+1])
		ctxt.Andptr = ctxt.Andptr[1:]
		asmand(ctxt, p, &p.From, &p.To)

	case Zm_r_xm:
		mediaop(ctxt, o, op, int(t[3]), z)
		asmand(ctxt, p, &p.From, &p.To)

	case Zm_r_xm_nr:
		ctxt.Rexflag = 0
		mediaop(ctxt, o, op, int(t[3]), z)
		asmand(ctxt, p, &p.From, &p.To)

	case Zm_r_i_xm:
		mediaop(ctxt, o, op, int(t[3]), z)
		asmand(ctxt, p, &p.From, &p.To)
		ctxt.Andptr[0] = byte(p.To.Offset)
		ctxt.Andptr = ctxt.Andptr[1:]

	case Zm_r_3d:
		ctxt.Andptr[0] = 0x0f
		ctxt.Andptr = ctxt.Andptr[1:]
		ctxt.Andptr[0] = 0x0f
		ctxt.Andptr = ctxt.Andptr[1:]
		asmand(ctxt, p, &p.From, &p.To)
		ctxt.Andptr[0] = byte(op)
		ctxt.Andptr = ctxt.Andptr[1:]

	case Zibm_r:
		for {
			tmp1 := z
			z++
			op = int(o.op[tmp1])
			if !(op != 0) {
				break
			}
			ctxt.Andptr[0] = byte(op)
			ctxt.Andptr = ctxt.Andptr[1:]
		}
		asmand(ctxt, p, &p.From, &p.To)
		ctxt.Andptr[0] = byte(p.To.Offset)
		ctxt.Andptr = ctxt.Andptr[1:]

	case Zaut_r:
		ctxt.Andptr[0] = 0x8d
		ctxt.Andptr = ctxt.Andptr[1:] /* leal */
		if p.From.Type != D_ADDR {
			ctxt.Diag("asmins: Zaut sb type ADDR")
		}
		p.From.Type = int16(p.From.Index)
		p.From.Index = D_NONE
		asmand(ctxt, p, &p.From, &p.To)
		p.From.Index = uint8(p.From.Type)
		p.From.Type = D_ADDR

	case Zm_o:
		ctxt.Andptr[0] = byte(op)
		ctxt.Andptr = ctxt.Andptr[1:]
		asmando(ctxt, p, &p.From, int(o.op[z+1]))

	case Zr_m:
		ctxt.Andptr[0] = byte(op)
		ctxt.Andptr = ctxt.Andptr[1:]
		asmand(ctxt, p, &p.To, &p.From)

	case Zr_m_xm:
		mediaop(ctxt, o, op, int(t[3]), z)
		asmand(ctxt, p, &p.To, &p.From)

	case Zr_m_xm_nr:
		ctxt.Rexflag = 0
		mediaop(ctxt, o, op, int(t[3]), z)
		asmand(ctxt, p, &p.To, &p.From)

	case Zr_m_i_xm:
		mediaop(ctxt, o, op, int(t[3]), z)
		asmand(ctxt, p, &p.To, &p.From)
		ctxt.Andptr[0] = byte(p.From.Offset)
		ctxt.Andptr = ctxt.Andptr[1:]

	case Zo_m:
		ctxt.Andptr[0] = byte(op)
		ctxt.Andptr = ctxt.Andptr[1:]
		asmando(ctxt, p, &p.To, int(o.op[z+1]))

	case Zcallindreg:
		r = obj.Addrel(ctxt.Cursym)
		r.Off = int32(p.Pc)
		r.Type = obj.R_CALLIND
		r.Siz = 0
		fallthrough

		// fallthrough
	case Zo_m64:
		ctxt.Andptr[0] = byte(op)
		ctxt.Andptr = ctxt.Andptr[1:]

		asmandsz(ctxt, p, &p.To, int(o.op[z+1]), 0, 1)

	case Zm_ibo:
		ctxt.Andptr[0] = byte(op)
		ctxt.Andptr = ctxt.Andptr[1:]
		asmando(ctxt, p, &p.From, int(o.op[z+1]))
		ctxt.Andptr[0] = byte(vaddr(ctxt, p, &p.To, nil))
		ctxt.Andptr = ctxt.Andptr[1:]

	case Zibo_m:
		ctxt.Andptr[0] = byte(op)
		ctxt.Andptr = ctxt.Andptr[1:]
		asmando(ctxt, p, &p.To, int(o.op[z+1]))
		ctxt.Andptr[0] = byte(vaddr(ctxt, p, &p.From, nil))
		ctxt.Andptr = ctxt.Andptr[1:]

	case Zibo_m_xm:
		z = mediaop(ctxt, o, op, int(t[3]), z)
		asmando(ctxt, p, &p.To, int(o.op[z+1]))
		ctxt.Andptr[0] = byte(vaddr(ctxt, p, &p.From, nil))
		ctxt.Andptr = ctxt.Andptr[1:]

	case Z_ib,
		Zib_:
		if t[2] == Zib_ {
			a = &p.From
		} else {

			a = &p.To
		}
		ctxt.Andptr[0] = byte(op)
		ctxt.Andptr = ctxt.Andptr[1:]
		ctxt.Andptr[0] = byte(vaddr(ctxt, p, a, nil))
		ctxt.Andptr = ctxt.Andptr[1:]

	case Zib_rp:
		ctxt.Rexflag |= regrex[p.To.Type] & (Rxb | 0x40)
		ctxt.Andptr[0] = byte(op + reg[p.To.Type])
		ctxt.Andptr = ctxt.Andptr[1:]
		ctxt.Andptr[0] = byte(vaddr(ctxt, p, &p.From, nil))
		ctxt.Andptr = ctxt.Andptr[1:]

	case Zil_rp:
		ctxt.Rexflag |= regrex[p.To.Type] & Rxb
		ctxt.Andptr[0] = byte(op + reg[p.To.Type])
		ctxt.Andptr = ctxt.Andptr[1:]
		if o.prefix == Pe {
			v = vaddr(ctxt, p, &p.From, nil)
			ctxt.Andptr[0] = byte(v)
			ctxt.Andptr = ctxt.Andptr[1:]
			ctxt.Andptr[0] = byte(v >> 8)
			ctxt.Andptr = ctxt.Andptr[1:]
		} else {

			relput4(ctxt, p, &p.From)
		}

	case Zo_iw:
		ctxt.Andptr[0] = byte(op)
		ctxt.Andptr = ctxt.Andptr[1:]
		if p.From.Type != D_NONE {
			v = vaddr(ctxt, p, &p.From, nil)
			ctxt.Andptr[0] = byte(v)
			ctxt.Andptr = ctxt.Andptr[1:]
			ctxt.Andptr[0] = byte(v >> 8)
			ctxt.Andptr = ctxt.Andptr[1:]
		}

	case Ziq_rp:
		v = vaddr(ctxt, p, &p.From, &rel)
		l = int(v >> 32)
		if l == 0 && rel.Siz != 8 {
			//p->mark |= 0100;
			//print("zero: %llux %P\n", v, p);
			ctxt.Rexflag &^= (0x40 | Rxw)

			ctxt.Rexflag |= regrex[p.To.Type] & Rxb
			ctxt.Andptr[0] = byte(0xb8 + reg[p.To.Type])
			ctxt.Andptr = ctxt.Andptr[1:]
			if rel.Type != 0 {
				r = obj.Addrel(ctxt.Cursym)
				*r = rel
				r.Off = int32(p.Pc + int64(-cap(ctxt.Andptr)+cap(ctxt.And[:])))
			}

			put4(ctxt, int32(v))
		} else if l == -1 && uint64(v)&(uint64(1)<<31) != 0 { /* sign extend */

			//p->mark |= 0100;
			//print("sign: %llux %P\n", v, p);
			ctxt.Andptr[0] = 0xc7
			ctxt.Andptr = ctxt.Andptr[1:]

			asmando(ctxt, p, &p.To, 0)
			put4(ctxt, int32(v)) /* need all 8 */
		} else {

			//print("all: %llux %P\n", v, p);
			ctxt.Rexflag |= regrex[p.To.Type] & Rxb

			ctxt.Andptr[0] = byte(op + reg[p.To.Type])
			ctxt.Andptr = ctxt.Andptr[1:]
			if rel.Type != 0 {
				r = obj.Addrel(ctxt.Cursym)
				*r = rel
				r.Off = int32(p.Pc + int64(-cap(ctxt.Andptr)+cap(ctxt.And[:])))
			}

			put8(ctxt, v)
		}

	case Zib_rr:
		ctxt.Andptr[0] = byte(op)
		ctxt.Andptr = ctxt.Andptr[1:]
		asmand(ctxt, p, &p.To, &p.To)
		ctxt.Andptr[0] = byte(vaddr(ctxt, p, &p.From, nil))
		ctxt.Andptr = ctxt.Andptr[1:]

	case Z_il,
		Zil_:
		if t[2] == Zil_ {
			a = &p.From
		} else {

			a = &p.To
		}
		ctxt.Andptr[0] = byte(op)
		ctxt.Andptr = ctxt.Andptr[1:]
		if o.prefix == Pe {
			v = vaddr(ctxt, p, a, nil)
			ctxt.Andptr[0] = byte(v)
			ctxt.Andptr = ctxt.Andptr[1:]
			ctxt.Andptr[0] = byte(v >> 8)
			ctxt.Andptr = ctxt.Andptr[1:]
		} else {

			relput4(ctxt, p, a)
		}

	case Zm_ilo,
		Zilo_m:
		ctxt.Andptr[0] = byte(op)
		ctxt.Andptr = ctxt.Andptr[1:]
		if t[2] == Zilo_m {
			a = &p.From
			asmando(ctxt, p, &p.To, int(o.op[z+1]))
		} else {

			a = &p.To
			asmando(ctxt, p, &p.From, int(o.op[z+1]))
		}

		if o.prefix == Pe {
			v = vaddr(ctxt, p, a, nil)
			ctxt.Andptr[0] = byte(v)
			ctxt.Andptr = ctxt.Andptr[1:]
			ctxt.Andptr[0] = byte(v >> 8)
			ctxt.Andptr = ctxt.Andptr[1:]
		} else {

			relput4(ctxt, p, a)
		}

	case Zil_rr:
		ctxt.Andptr[0] = byte(op)
		ctxt.Andptr = ctxt.Andptr[1:]
		asmand(ctxt, p, &p.To, &p.To)
		if o.prefix == Pe {
			v = vaddr(ctxt, p, &p.From, nil)
			ctxt.Andptr[0] = byte(v)
			ctxt.Andptr = ctxt.Andptr[1:]
			ctxt.Andptr[0] = byte(v >> 8)
			ctxt.Andptr = ctxt.Andptr[1:]
		} else {

			relput4(ctxt, p, &p.From)
		}

	case Z_rp:
		ctxt.Rexflag |= regrex[p.To.Type] & (Rxb | 0x40)
		ctxt.Andptr[0] = byte(op + reg[p.To.Type])
		ctxt.Andptr = ctxt.Andptr[1:]

	case Zrp_:
		ctxt.Rexflag |= regrex[p.From.Type] & (Rxb | 0x40)
		ctxt.Andptr[0] = byte(op + reg[p.From.Type])
		ctxt.Andptr = ctxt.Andptr[1:]

	case Zclr:
		ctxt.Rexflag &^= Pw
		ctxt.Andptr[0] = byte(op)
		ctxt.Andptr = ctxt.Andptr[1:]
		asmand(ctxt, p, &p.To, &p.To)

	case Zcall:
		if p.To.Sym == nil {
			ctxt.Diag("call without target")
			log.Fatalf("bad code")
		}

		ctxt.Andptr[0] = byte(op)
		ctxt.Andptr = ctxt.Andptr[1:]
		r = obj.Addrel(ctxt.Cursym)
		r.Off = int32(p.Pc + int64(-cap(ctxt.Andptr)+cap(ctxt.And[:])))
		r.Sym = p.To.Sym
		r.Add = p.To.Offset
		r.Type = obj.R_CALL
		r.Siz = 4
		put4(ctxt, 0)

		// TODO: jump across functions needs reloc
	case Zbr,
		Zjmp,
		Zloop:
		if p.To.Sym != nil {

			if t[2] != Zjmp {
				ctxt.Diag("branch to ATEXT")
				log.Fatalf("bad code")
			}

			ctxt.Andptr[0] = byte(o.op[z+1])
			ctxt.Andptr = ctxt.Andptr[1:]
			r = obj.Addrel(ctxt.Cursym)
			r.Off = int32(p.Pc + int64(-cap(ctxt.Andptr)+cap(ctxt.And[:])))
			r.Sym = p.To.Sym
			r.Type = obj.R_PCREL
			r.Siz = 4
			put4(ctxt, 0)
			break
		}

		// Assumes q is in this function.
		// TODO: Check in input, preserve in brchain.

		// Fill in backward jump now.
		q = p.Pcond

		if q == nil {
			ctxt.Diag("jmp/branch/loop without target")
			log.Fatalf("bad code")
		}

		if p.Back&1 != 0 {
			v = q.Pc - (p.Pc + 2)
			if v >= -128 {
				if p.As == AJCXZL {
					ctxt.Andptr[0] = 0x67
					ctxt.Andptr = ctxt.Andptr[1:]
				}
				ctxt.Andptr[0] = byte(op)
				ctxt.Andptr = ctxt.Andptr[1:]
				ctxt.Andptr[0] = byte(v)
				ctxt.Andptr = ctxt.Andptr[1:]
			} else if t[2] == Zloop {
				ctxt.Diag("loop too far: %v", p)
			} else {

				v -= 5 - 2
				if t[2] == Zbr {
					ctxt.Andptr[0] = 0x0f
					ctxt.Andptr = ctxt.Andptr[1:]
					v--
				}

				ctxt.Andptr[0] = byte(o.op[z+1])
				ctxt.Andptr = ctxt.Andptr[1:]
				ctxt.Andptr[0] = byte(v)
				ctxt.Andptr = ctxt.Andptr[1:]
				ctxt.Andptr[0] = byte(v >> 8)
				ctxt.Andptr = ctxt.Andptr[1:]
				ctxt.Andptr[0] = byte(v >> 16)
				ctxt.Andptr = ctxt.Andptr[1:]
				ctxt.Andptr[0] = byte(v >> 24)
				ctxt.Andptr = ctxt.Andptr[1:]
			}

			break
		}

		// Annotate target; will fill in later.
		p.Forwd = q.Comefrom

		q.Comefrom = p
		if p.Back&2 != 0 { // short
			if p.As == AJCXZL {
				ctxt.Andptr[0] = 0x67
				ctxt.Andptr = ctxt.Andptr[1:]
			}
			ctxt.Andptr[0] = byte(op)
			ctxt.Andptr = ctxt.Andptr[1:]
			ctxt.Andptr[0] = 0
			ctxt.Andptr = ctxt.Andptr[1:]
		} else if t[2] == Zloop {
			ctxt.Diag("loop too far: %v", p)
		} else {

			if t[2] == Zbr {
				ctxt.Andptr[0] = 0x0f
				ctxt.Andptr = ctxt.Andptr[1:]
			}
			ctxt.Andptr[0] = byte(o.op[z+1])
			ctxt.Andptr = ctxt.Andptr[1:]
			ctxt.Andptr[0] = 0
			ctxt.Andptr = ctxt.Andptr[1:]
			ctxt.Andptr[0] = 0
			ctxt.Andptr = ctxt.Andptr[1:]
			ctxt.Andptr[0] = 0
			ctxt.Andptr = ctxt.Andptr[1:]
			ctxt.Andptr[0] = 0
			ctxt.Andptr = ctxt.Andptr[1:]
		}

		break

	/*
		v = q->pc - p->pc - 2;
		if((v >= -128 && v <= 127) || p->pc == -1 || q->pc == -1) {
			*ctxt->andptr++ = op;
			*ctxt->andptr++ = v;
		} else {
			v -= 5-2;
			if(t[2] == Zbr) {
				*ctxt->andptr++ = 0x0f;
				v--;
			}
			*ctxt->andptr++ = o->op[z+1];
			*ctxt->andptr++ = v;
			*ctxt->andptr++ = v>>8;
			*ctxt->andptr++ = v>>16;
			*ctxt->andptr++ = v>>24;
		}
	*/

	case Zbyte:
		v = vaddr(ctxt, p, &p.From, &rel)
		if rel.Siz != 0 {
			rel.Siz = uint8(op)
			r = obj.Addrel(ctxt.Cursym)
			*r = rel
			r.Off = int32(p.Pc + int64(-cap(ctxt.Andptr)+cap(ctxt.And[:])))
		}

		ctxt.Andptr[0] = byte(v)
		ctxt.Andptr = ctxt.Andptr[1:]
		if op > 1 {
			ctxt.Andptr[0] = byte(v >> 8)
			ctxt.Andptr = ctxt.Andptr[1:]
			if op > 2 {
				ctxt.Andptr[0] = byte(v >> 16)
				ctxt.Andptr = ctxt.Andptr[1:]
				ctxt.Andptr[0] = byte(v >> 24)
				ctxt.Andptr = ctxt.Andptr[1:]
				if op > 4 {
					ctxt.Andptr[0] = byte(v >> 32)
					ctxt.Andptr = ctxt.Andptr[1:]
					ctxt.Andptr[0] = byte(v >> 40)
					ctxt.Andptr = ctxt.Andptr[1:]
					ctxt.Andptr[0] = byte(v >> 48)
					ctxt.Andptr = ctxt.Andptr[1:]
					ctxt.Andptr[0] = byte(v >> 56)
					ctxt.Andptr = ctxt.Andptr[1:]
				}
			}
		}

		break
	}

	return

domov:
	for mo = ymovtab; mo[0].as != 0; mo = mo[1:] {
		if p.As == mo[0].as {
			if ycover[ft+int(mo[0].ft)] != 0 {
				if ycover[tt+int(mo[0].tt)] != 0 {
					t = mo[0].op[:]
					goto mfound
				}
			}
		}
	}

bad:
	if p.Mode != 64 {
		/*
		 * here, the assembly has failed.
		 * if its a byte instruction that has
		 * unaddressable registers, try to
		 * exchange registers and reissue the
		 * instruction with the operands renamed.
		 */
		pp = *p

		z = int(p.From.Type)
		if z >= D_BP && z <= D_DI {
			if isax(&p.To) != 0 || p.To.Type == D_NONE {
				// We certainly don't want to exchange
				// with AX if the op is MUL or DIV.
				ctxt.Andptr[0] = 0x87
				ctxt.Andptr = ctxt.Andptr[1:] /* xchg lhs,bx */
				asmando(ctxt, p, &p.From, reg[D_BX])
				subreg(&pp, z, D_BX)
				doasm(ctxt, &pp)
				ctxt.Andptr[0] = 0x87
				ctxt.Andptr = ctxt.Andptr[1:] /* xchg lhs,bx */
				asmando(ctxt, p, &p.From, reg[D_BX])
			} else {

				ctxt.Andptr[0] = byte(0x90 + reg[z])
				ctxt.Andptr = ctxt.Andptr[1:] /* xchg lsh,ax */
				subreg(&pp, z, D_AX)
				doasm(ctxt, &pp)
				ctxt.Andptr[0] = byte(0x90 + reg[z])
				ctxt.Andptr = ctxt.Andptr[1:] /* xchg lsh,ax */
			}

			return
		}

		z = int(p.To.Type)
		if z >= D_BP && z <= D_DI {
			if isax(&p.From) != 0 {
				ctxt.Andptr[0] = 0x87
				ctxt.Andptr = ctxt.Andptr[1:] /* xchg rhs,bx */
				asmando(ctxt, p, &p.To, reg[D_BX])
				subreg(&pp, z, D_BX)
				doasm(ctxt, &pp)
				ctxt.Andptr[0] = 0x87
				ctxt.Andptr = ctxt.Andptr[1:] /* xchg rhs,bx */
				asmando(ctxt, p, &p.To, reg[D_BX])
			} else {

				ctxt.Andptr[0] = byte(0x90 + reg[z])
				ctxt.Andptr = ctxt.Andptr[1:] /* xchg rsh,ax */
				subreg(&pp, z, D_AX)
				doasm(ctxt, &pp)
				ctxt.Andptr[0] = byte(0x90 + reg[z])
				ctxt.Andptr = ctxt.Andptr[1:] /* xchg rsh,ax */
			}

			return
		}
	}

	ctxt.Diag("doasm: notfound from=%x to=%x %v", uint16(p.From.Type), uint16(p.To.Type), p)
	return

mfound:
	switch mo[0].code {
	default:
		ctxt.Diag("asmins: unknown mov %d %v", mo[0].code, p)

	case 0: /* lit */
		for z = 0; t[z] != E; z++ {

			ctxt.Andptr[0] = t[z]
			ctxt.Andptr = ctxt.Andptr[1:]
		}

	case 1: /* r,m */
		ctxt.Andptr[0] = t[0]
		ctxt.Andptr = ctxt.Andptr[1:]

		asmando(ctxt, p, &p.To, int(t[1]))

	case 2: /* m,r */
		ctxt.Andptr[0] = t[0]
		ctxt.Andptr = ctxt.Andptr[1:]

		asmando(ctxt, p, &p.From, int(t[1]))

	case 3: /* r,m - 2op */
		ctxt.Andptr[0] = t[0]
		ctxt.Andptr = ctxt.Andptr[1:]

		ctxt.Andptr[0] = t[1]
		ctxt.Andptr = ctxt.Andptr[1:]
		asmando(ctxt, p, &p.To, int(t[2]))
		ctxt.Rexflag |= regrex[p.From.Type] & (Rxr | 0x40)

	case 4: /* m,r - 2op */
		ctxt.Andptr[0] = t[0]
		ctxt.Andptr = ctxt.Andptr[1:]

		ctxt.Andptr[0] = t[1]
		ctxt.Andptr = ctxt.Andptr[1:]
		asmando(ctxt, p, &p.From, int(t[2]))
		ctxt.Rexflag |= regrex[p.To.Type] & (Rxr | 0x40)

	case 5: /* load full pointer, trash heap */
		if t[0] != 0 {

			ctxt.Andptr[0] = t[0]
			ctxt.Andptr = ctxt.Andptr[1:]
		}
		switch p.To.Index {
		default:
			goto bad

		case D_DS:
			ctxt.Andptr[0] = 0xc5
			ctxt.Andptr = ctxt.Andptr[1:]

		case D_SS:
			ctxt.Andptr[0] = 0x0f
			ctxt.Andptr = ctxt.Andptr[1:]
			ctxt.Andptr[0] = 0xb2
			ctxt.Andptr = ctxt.Andptr[1:]

		case D_ES:
			ctxt.Andptr[0] = 0xc4
			ctxt.Andptr = ctxt.Andptr[1:]

		case D_FS:
			ctxt.Andptr[0] = 0x0f
			ctxt.Andptr = ctxt.Andptr[1:]
			ctxt.Andptr[0] = 0xb4
			ctxt.Andptr = ctxt.Andptr[1:]

		case D_GS:
			ctxt.Andptr[0] = 0x0f
			ctxt.Andptr = ctxt.Andptr[1:]
			ctxt.Andptr[0] = 0xb5
			ctxt.Andptr = ctxt.Andptr[1:]
			break
		}

		asmand(ctxt, p, &p.From, &p.To)

	case 6: /* double shift */
		if t[0] == Pw {

			if p.Mode != 64 {
				ctxt.Diag("asmins: illegal 64: %v", p)
			}
			ctxt.Rexflag |= Pw
			t = t[1:]
		} else if t[0] == Pe {
			ctxt.Andptr[0] = Pe
			ctxt.Andptr = ctxt.Andptr[1:]
			t = t[1:]
		}

		z = int(p.From.Type)
		switch z {
		default:
			goto bad

		case D_CONST:
			ctxt.Andptr[0] = 0x0f
			ctxt.Andptr = ctxt.Andptr[1:]
			ctxt.Andptr[0] = t[0]
			ctxt.Andptr = ctxt.Andptr[1:]
			asmandsz(ctxt, p, &p.To, reg[int(p.From.Index)], regrex[int(p.From.Index)], 0)
			ctxt.Andptr[0] = byte(p.From.Offset)
			ctxt.Andptr = ctxt.Andptr[1:]

		case D_CL,
			D_CX:
			ctxt.Andptr[0] = 0x0f
			ctxt.Andptr = ctxt.Andptr[1:]
			ctxt.Andptr[0] = t[1]
			ctxt.Andptr = ctxt.Andptr[1:]
			asmandsz(ctxt, p, &p.To, reg[int(p.From.Index)], regrex[int(p.From.Index)], 0)
			break
		}

		// NOTE: The systems listed here are the ones that use the "TLS initial exec" model,
	// where you load the TLS base register into a register and then index off that
	// register to access the actual TLS variables. Systems that allow direct TLS access
	// are handled in prefixof above and should not be listed here.
	case 7: /* mov tls, r */
		switch ctxt.Headtype {

		default:
			log.Fatalf("unknown TLS base location for %s", obj.Headstr(ctxt.Headtype))

		case obj.Hplan9:
			if ctxt.Plan9privates == nil {
				ctxt.Plan9privates = obj.Linklookup(ctxt, "_privates", 0)
			}
			pp.From = obj.Addr{}
			pp.From.Type = D_EXTERN
			pp.From.Sym = ctxt.Plan9privates
			pp.From.Offset = 0
			pp.From.Index = D_NONE
			ctxt.Rexflag |= Pw
			ctxt.Andptr[0] = 0x8B
			ctxt.Andptr = ctxt.Andptr[1:]
			asmand(ctxt, p, &pp.From, &p.To)

			// TLS base is 0(FS).
		case obj.Hsolaris: // TODO(rsc): Delete Hsolaris from list. Should not use this code. See progedit in obj6.c.
			pp.From = p.From

			pp.From.Type = D_INDIR + D_NONE
			pp.From.Offset = 0
			pp.From.Index = D_NONE
			pp.From.Scale = 0
			ctxt.Rexflag |= Pw
			ctxt.Andptr[0] = 0x64
			ctxt.Andptr = ctxt.Andptr[1:] // FS
			ctxt.Andptr[0] = 0x8B
			ctxt.Andptr = ctxt.Andptr[1:]
			asmand(ctxt, p, &pp.From, &p.To)

			// Windows TLS base is always 0x28(GS).
		case obj.Hwindows:
			pp.From = p.From

			pp.From.Type = D_INDIR + D_GS
			pp.From.Offset = 0x28
			pp.From.Index = D_NONE
			pp.From.Scale = 0
			ctxt.Rexflag |= Pw
			ctxt.Andptr[0] = 0x65
			ctxt.Andptr = ctxt.Andptr[1:] // GS
			ctxt.Andptr[0] = 0x8B
			ctxt.Andptr = ctxt.Andptr[1:]
			asmand(ctxt, p, &pp.From, &p.To)
			break
		}

		break
	}
}

var naclret = []uint8{
	0x5e, // POPL SI
	// 0x8b, 0x7d, 0x00, // MOVL (BP), DI - catch return to invalid address, for debugging
	0x83,
	0xe6,
	0xe0, // ANDL $~31, SI
	0x4c,
	0x01,
	0xfe, // ADDQ R15, SI
	0xff,
	0xe6, // JMP SI
}

var naclspfix = []uint8{0x4c, 0x01, 0xfc} // ADDQ R15, SP

var naclbpfix = []uint8{0x4c, 0x01, 0xfd} // ADDQ R15, BP

var naclmovs = []uint8{
	0x89,
	0xf6, // MOVL SI, SI
	0x49,
	0x8d,
	0x34,
	0x37, // LEAQ (R15)(SI*1), SI
	0x89,
	0xff, // MOVL DI, DI
	0x49,
	0x8d,
	0x3c,
	0x3f, // LEAQ (R15)(DI*1), DI
}

var naclstos = []uint8{
	0x89,
	0xff, // MOVL DI, DI
	0x49,
	0x8d,
	0x3c,
	0x3f, // LEAQ (R15)(DI*1), DI
}

func nacltrunc(ctxt *obj.Link, reg int) {
	if reg >= D_R8 {
		ctxt.Andptr[0] = 0x45
		ctxt.Andptr = ctxt.Andptr[1:]
	}
	reg = (reg - D_AX) & 7
	ctxt.Andptr[0] = 0x89
	ctxt.Andptr = ctxt.Andptr[1:]
	ctxt.Andptr[0] = byte(3<<6 | reg<<3 | reg)
	ctxt.Andptr = ctxt.Andptr[1:]
}

func asmins(ctxt *obj.Link, p *obj.Prog) {
	var i int
	var n int
	var np int
	var c int
	var and0 []byte
	var r *obj.Reloc

	ctxt.Andptr = ctxt.And[:]
	ctxt.Asmode = int(p.Mode)

	if p.As == AUSEFIELD {
		r = obj.Addrel(ctxt.Cursym)
		r.Off = 0
		r.Siz = 0
		r.Sym = p.From.Sym
		r.Type = obj.R_USEFIELD
		return
	}

	if ctxt.Headtype == obj.Hnacl {
		if p.As == AREP {
			ctxt.Rep++
			return
		}

		if p.As == AREPN {
			ctxt.Repn++
			return
		}

		if p.As == ALOCK {
			ctxt.Lock++
			return
		}

		if p.As != ALEAQ && p.As != ALEAL {
			if p.From.Index != D_NONE && p.From.Scale > 0 {
				nacltrunc(ctxt, int(p.From.Index))
			}
			if p.To.Index != D_NONE && p.To.Scale > 0 {
				nacltrunc(ctxt, int(p.To.Index))
			}
		}

		switch p.As {
		case ARET:
			copy(ctxt.Andptr, naclret)
			ctxt.Andptr = ctxt.Andptr[len(naclret):]
			return

		case ACALL,
			AJMP:
			if D_AX <= p.To.Type && p.To.Type <= D_DI {
				// ANDL $~31, reg
				ctxt.Andptr[0] = 0x83
				ctxt.Andptr = ctxt.Andptr[1:]

				ctxt.Andptr[0] = byte(0xe0 | (p.To.Type - D_AX))
				ctxt.Andptr = ctxt.Andptr[1:]
				ctxt.Andptr[0] = 0xe0
				ctxt.Andptr = ctxt.Andptr[1:]

				// ADDQ R15, reg
				ctxt.Andptr[0] = 0x4c
				ctxt.Andptr = ctxt.Andptr[1:]

				ctxt.Andptr[0] = 0x01
				ctxt.Andptr = ctxt.Andptr[1:]
				ctxt.Andptr[0] = byte(0xf8 | (p.To.Type - D_AX))
				ctxt.Andptr = ctxt.Andptr[1:]
			}

			if D_R8 <= p.To.Type && p.To.Type <= D_R15 {
				// ANDL $~31, reg
				ctxt.Andptr[0] = 0x41
				ctxt.Andptr = ctxt.Andptr[1:]

				ctxt.Andptr[0] = 0x83
				ctxt.Andptr = ctxt.Andptr[1:]
				ctxt.Andptr[0] = byte(0xe0 | (p.To.Type - D_R8))
				ctxt.Andptr = ctxt.Andptr[1:]
				ctxt.Andptr[0] = 0xe0
				ctxt.Andptr = ctxt.Andptr[1:]

				// ADDQ R15, reg
				ctxt.Andptr[0] = 0x4d
				ctxt.Andptr = ctxt.Andptr[1:]

				ctxt.Andptr[0] = 0x01
				ctxt.Andptr = ctxt.Andptr[1:]
				ctxt.Andptr[0] = byte(0xf8 | (p.To.Type - D_R8))
				ctxt.Andptr = ctxt.Andptr[1:]
			}

		case AINT:
			ctxt.Andptr[0] = 0xf4
			ctxt.Andptr = ctxt.Andptr[1:]
			return

		case ASCASB,
			ASCASW,
			ASCASL,
			ASCASQ,
			ASTOSB,
			ASTOSW,
			ASTOSL,
			ASTOSQ:
			copy(ctxt.Andptr, naclstos)
			ctxt.Andptr = ctxt.Andptr[len(naclstos):]

		case AMOVSB,
			AMOVSW,
			AMOVSL,
			AMOVSQ:
			copy(ctxt.Andptr, naclmovs)
			ctxt.Andptr = ctxt.Andptr[len(naclmovs):]
			break
		}

		if ctxt.Rep != 0 {
			ctxt.Andptr[0] = 0xf3
			ctxt.Andptr = ctxt.Andptr[1:]
			ctxt.Rep = 0
		}

		if ctxt.Repn != 0 {
			ctxt.Andptr[0] = 0xf2
			ctxt.Andptr = ctxt.Andptr[1:]
			ctxt.Repn = 0
		}

		if ctxt.Lock != 0 {
			ctxt.Andptr[0] = 0xf0
			ctxt.Andptr = ctxt.Andptr[1:]
			ctxt.Lock = 0
		}
	}

	ctxt.Rexflag = 0
	and0 = ctxt.Andptr
	ctxt.Asmode = int(p.Mode)
	doasm(ctxt, p)
	if ctxt.Rexflag != 0 {
		/*
		 * as befits the whole approach of the architecture,
		 * the rex prefix must appear before the first opcode byte
		 * (and thus after any 66/67/f2/f3/26/2e/3e prefix bytes, but
		 * before the 0f opcode escape!), or it might be ignored.
		 * note that the handbook often misleadingly shows 66/f2/f3 in `opcode'.
		 */
		if p.Mode != 64 {

			ctxt.Diag("asmins: illegal in mode %d: %v", p.Mode, p)
		}
		n = -cap(ctxt.Andptr) + cap(and0)
		for np = 0; np < n; np++ {
			c = int(and0[np])
			if c != 0xf2 && c != 0xf3 && (c < 0x64 || c > 0x67) && c != 0x2e && c != 0x3e && c != 0x26 {
				break
			}
		}

		copy(and0[np+1:], and0[np:n])
		and0[np] = byte(0x40 | ctxt.Rexflag)
		ctxt.Andptr = ctxt.Andptr[1:]
	}

	n = -cap(ctxt.Andptr) + cap(ctxt.And[:])
	for i = len(ctxt.Cursym.R) - 1; i >= 0; i-- {
		r = &ctxt.Cursym.R[i:][0]
		if int64(r.Off) < p.Pc {
			break
		}
		if ctxt.Rexflag != 0 {
			r.Off++
		}
		if r.Type == obj.R_PCREL || r.Type == obj.R_CALL {
			r.Add -= p.Pc + int64(n) - (int64(r.Off) + int64(r.Siz))
		}
	}

	if ctxt.Headtype == obj.Hnacl && p.As != ACMPL && p.As != ACMPQ {
		switch p.To.Type {
		case D_SP:
			copy(ctxt.Andptr, naclspfix)
			ctxt.Andptr = ctxt.Andptr[len(naclspfix):]

		case D_BP:
			copy(ctxt.Andptr, naclbpfix)
			ctxt.Andptr = ctxt.Andptr[len(naclbpfix):]
			break
		}
	}
}
