// Copyright 2014 The Go Authors.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package main

import (
	"cmd/internal/obj"
	"cmd/internal/obj/arm64"
)
import "cmd/internal/gc"

const (
	LeftRdwr  uint32 = gc.LeftRead | gc.LeftWrite
	RightRdwr uint32 = gc.RightRead | gc.RightWrite
)

// This table gives the basic information about instruction
// generated by the compiler and processed in the optimizer.
// See opt.h for bit definitions.
//
// Instructions not generated need not be listed.
// As an exception to that rule, we typically write down all the
// size variants of an operation even if we just use a subset.
//
// The table is formatted for 8-space tabs.
var progtable = [arm64.ALAST]gc.ProgInfo{
	obj.ATYPE:     gc.ProgInfo{gc.Pseudo | gc.Skip, 0, 0, 0},
	obj.ATEXT:     gc.ProgInfo{gc.Pseudo, 0, 0, 0},
	obj.AFUNCDATA: gc.ProgInfo{gc.Pseudo, 0, 0, 0},
	obj.APCDATA:   gc.ProgInfo{gc.Pseudo, 0, 0, 0},
	obj.AUNDEF:    gc.ProgInfo{gc.Break, 0, 0, 0},
	obj.AUSEFIELD: gc.ProgInfo{gc.OK, 0, 0, 0},
	obj.ACHECKNIL: gc.ProgInfo{gc.LeftRead, 0, 0, 0},
	obj.AVARDEF:   gc.ProgInfo{gc.Pseudo | gc.RightWrite, 0, 0, 0},
	obj.AVARKILL:  gc.ProgInfo{gc.Pseudo | gc.RightWrite, 0, 0, 0},

	// NOP is an internal no-op that also stands
	// for USED and SET annotations, not the Power opcode.
	obj.ANOP: gc.ProgInfo{gc.LeftRead | gc.RightWrite, 0, 0, 0},
	arm64.AHINT: gc.ProgInfo{gc.OK, 0, 0, 0},

	// Integer
	arm64.AADD:    gc.ProgInfo{gc.SizeQ | gc.LeftRead | gc.RegRead | gc.RightWrite, 0, 0, 0},
	arm64.ASUB:    gc.ProgInfo{gc.SizeQ | gc.LeftRead | gc.RegRead | gc.RightWrite, 0, 0, 0},
	arm64.ANEG:    gc.ProgInfo{gc.SizeQ | gc.LeftRead | gc.RegRead | gc.RightWrite, 0, 0, 0},
	arm64.AAND:    gc.ProgInfo{gc.SizeQ | gc.LeftRead | gc.RegRead | gc.RightWrite, 0, 0, 0},
	arm64.AORR:    gc.ProgInfo{gc.SizeQ | gc.LeftRead | gc.RegRead | gc.RightWrite, 0, 0, 0},
	arm64.AEOR:    gc.ProgInfo{gc.SizeQ | gc.LeftRead | gc.RegRead | gc.RightWrite, 0, 0, 0},
	arm64.AMUL:  gc.ProgInfo{gc.SizeQ | gc.LeftRead | gc.RegRead | gc.RightWrite, 0, 0, 0},
	arm64.ASMULL:  gc.ProgInfo{gc.SizeQ | gc.LeftRead | gc.RegRead | gc.RightWrite, 0, 0, 0},
	arm64.AUMULL:  gc.ProgInfo{gc.SizeQ | gc.LeftRead | gc.RegRead | gc.RightWrite, 0, 0, 0},
	arm64.ASMULH:  gc.ProgInfo{gc.SizeL | gc.LeftRead | gc.RegRead | gc.RightWrite, 0, 0, 0},
	arm64.AUMULH:  gc.ProgInfo{gc.SizeL | gc.LeftRead | gc.RegRead | gc.RightWrite, 0, 0, 0},
	arm64.ASDIV:   gc.ProgInfo{gc.SizeQ | gc.LeftRead | gc.RegRead | gc.RightWrite, 0, 0, 0},
	arm64.AUDIV:  gc.ProgInfo{gc.SizeQ | gc.LeftRead | gc.RegRead | gc.RightWrite, 0, 0, 0},
	arm64.ALSL:    gc.ProgInfo{gc.SizeQ | gc.LeftRead | gc.RegRead | gc.RightWrite, 0, 0, 0},
	arm64.ALSR:    gc.ProgInfo{gc.SizeQ | gc.LeftRead | gc.RegRead | gc.RightWrite, 0, 0, 0},
	arm64.AASR:   gc.ProgInfo{gc.SizeQ | gc.LeftRead | gc.RegRead | gc.RightWrite, 0, 0, 0},
	arm64.ACMP:    gc.ProgInfo{gc.SizeQ | gc.LeftRead | gc.RightRead, 0, 0, 0},

	// Floating point.
	arm64.AFADDD:   gc.ProgInfo{gc.SizeD | gc.LeftRead | gc.RegRead | gc.RightWrite, 0, 0, 0},
	arm64.AFADDS:  gc.ProgInfo{gc.SizeF | gc.LeftRead | gc.RegRead | gc.RightWrite, 0, 0, 0},
	arm64.AFSUBD:   gc.ProgInfo{gc.SizeD | gc.LeftRead | gc.RegRead | gc.RightWrite, 0, 0, 0},
	arm64.AFSUBS:  gc.ProgInfo{gc.SizeF | gc.LeftRead | gc.RegRead | gc.RightWrite, 0, 0, 0},
	arm64.AFNEGD:  gc.ProgInfo{gc.SizeD | gc.LeftRead | gc.RightWrite, 0, 0, 0},
	arm64.AFNEGS:  gc.ProgInfo{gc.SizeF | gc.LeftRead | gc.RightWrite, 0, 0, 0},
	arm64.AFMULD:   gc.ProgInfo{gc.SizeD | gc.LeftRead | gc.RegRead | gc.RightWrite, 0, 0, 0},
	arm64.AFMULS:  gc.ProgInfo{gc.SizeF | gc.LeftRead | gc.RegRead | gc.RightWrite, 0, 0, 0},
	arm64.AFDIVD:   gc.ProgInfo{gc.SizeD | gc.LeftRead | gc.RegRead | gc.RightWrite, 0, 0, 0},
	arm64.AFDIVS:  gc.ProgInfo{gc.SizeF | gc.LeftRead | gc.RegRead | gc.RightWrite, 0, 0, 0},
	arm64.AFCMPD:  gc.ProgInfo{gc.SizeD | gc.LeftRead | gc.RightRead, 0, 0, 0},
	arm64.AFCMPS:  gc.ProgInfo{gc.SizeF | gc.LeftRead | gc.RightRead, 0, 0, 0},

	// float -> integer
	arm64.AFCVTZSD: gc.ProgInfo{gc.SizeD | gc.LeftRead | gc.RightWrite | gc.Conv, 0, 0, 0},
	arm64.AFCVTZSS: gc.ProgInfo{gc.SizeF | gc.LeftRead | gc.RightWrite | gc.Conv, 0, 0, 0},
	arm64.AFCVTZSDW: gc.ProgInfo{gc.SizeD | gc.LeftRead | gc.RightWrite | gc.Conv, 0, 0, 0},
	arm64.AFCVTZSSW: gc.ProgInfo{gc.SizeF | gc.LeftRead | gc.RightWrite | gc.Conv, 0, 0, 0},
	arm64.AFCVTZUD: gc.ProgInfo{gc.SizeD | gc.LeftRead | gc.RightWrite | gc.Conv, 0, 0, 0},
	arm64.AFCVTZUS: gc.ProgInfo{gc.SizeF | gc.LeftRead | gc.RightWrite | gc.Conv, 0, 0, 0},
	arm64.AFCVTZUDW: gc.ProgInfo{gc.SizeD | gc.LeftRead | gc.RightWrite | gc.Conv, 0, 0, 0},
	arm64.AFCVTZUSW: gc.ProgInfo{gc.SizeF | gc.LeftRead | gc.RightWrite | gc.Conv, 0, 0, 0},

	// float -> float
	arm64.AFCVTSD: gc.ProgInfo{gc.SizeD | gc.LeftRead | gc.RightWrite | gc.Conv, 0, 0, 0},
	arm64.AFCVTDS: gc.ProgInfo{gc.SizeD | gc.LeftRead | gc.RightWrite | gc.Conv, 0, 0, 0},

	// integer -> float
	arm64.ASCVTFD: gc.ProgInfo{gc.SizeQ | gc.LeftRead | gc.RightWrite | gc.Conv, 0, 0, 0},
	arm64.ASCVTFS: gc.ProgInfo{gc.SizeQ | gc.LeftRead | gc.RightWrite | gc.Conv, 0, 0, 0},
	arm64.ASCVTFWD: gc.ProgInfo{gc.SizeL | gc.LeftRead | gc.RightWrite | gc.Conv, 0, 0, 0},
	arm64.ASCVTFWS: gc.ProgInfo{gc.SizeL | gc.LeftRead | gc.RightWrite | gc.Conv, 0, 0, 0},
	arm64.AUCVTFD: gc.ProgInfo{gc.SizeQ | gc.LeftRead | gc.RightWrite | gc.Conv, 0, 0, 0},
	arm64.AUCVTFS: gc.ProgInfo{gc.SizeQ | gc.LeftRead | gc.RightWrite | gc.Conv, 0, 0, 0},
	arm64.AUCVTFWD: gc.ProgInfo{gc.SizeL | gc.LeftRead | gc.RightWrite | gc.Conv, 0, 0, 0},
	arm64.AUCVTFWS: gc.ProgInfo{gc.SizeL | gc.LeftRead | gc.RightWrite | gc.Conv, 0, 0, 0},

	// Moves
	arm64.AMOVB:  gc.ProgInfo{gc.SizeB | gc.LeftRead | gc.RightWrite | gc.Move | gc.Conv, 0, 0, 0},
	arm64.AMOVBU: gc.ProgInfo{gc.SizeB | gc.LeftRead | gc.RightWrite | gc.Move | gc.Conv, 0, 0, 0},
	arm64.AMOVH:  gc.ProgInfo{gc.SizeW | gc.LeftRead | gc.RightWrite | gc.Move | gc.Conv, 0, 0, 0},
	arm64.AMOVHU: gc.ProgInfo{gc.SizeW | gc.LeftRead | gc.RightWrite | gc.Move | gc.Conv, 0, 0, 0},
	arm64.AMOVW:  gc.ProgInfo{gc.SizeL | gc.LeftRead | gc.RightWrite | gc.Move | gc.Conv, 0, 0, 0},
	arm64.AMOVWU:  gc.ProgInfo{gc.SizeL | gc.LeftRead | gc.RightWrite | gc.Move | gc.Conv, 0, 0, 0},
	arm64.AMOVD:   gc.ProgInfo{gc.SizeQ | gc.LeftRead | gc.RightWrite | gc.Move, 0, 0, 0},
	arm64.AFMOVS:  gc.ProgInfo{gc.SizeF | gc.LeftRead | gc.RightWrite | gc.Move | gc.Conv, 0, 0, 0},
	arm64.AFMOVD:  gc.ProgInfo{gc.SizeD | gc.LeftRead | gc.RightWrite | gc.Move, 0, 0, 0},

	// Jumps
	arm64.AB:     gc.ProgInfo{gc.Jump | gc.Break, 0, 0, 0},
	arm64.ABL:     gc.ProgInfo{gc.Call, 0, 0, 0},
	arm64.ABEQ:    gc.ProgInfo{gc.Cjmp, 0, 0, 0},
	arm64.ABNE:    gc.ProgInfo{gc.Cjmp, 0, 0, 0},
	arm64.ABGE:    gc.ProgInfo{gc.Cjmp, 0, 0, 0},
	arm64.ABLT:    gc.ProgInfo{gc.Cjmp, 0, 0, 0},
	arm64.ABGT:    gc.ProgInfo{gc.Cjmp, 0, 0, 0},
	arm64.ABLE:    gc.ProgInfo{gc.Cjmp, 0, 0, 0},
	arm64.ABLO:    gc.ProgInfo{gc.Cjmp, 0, 0, 0},
	arm64.ABLS:    gc.ProgInfo{gc.Cjmp, 0, 0, 0},
	arm64.ABHI:    gc.ProgInfo{gc.Cjmp, 0, 0, 0},
	arm64.ABHS:    gc.ProgInfo{gc.Cjmp, 0, 0, 0},
	obj.ARET: gc.ProgInfo{gc.Break, 0, 0, 0},
	obj.ADUFFZERO: gc.ProgInfo{gc.Call, 0, 0, 0},
	obj.ADUFFCOPY: gc.ProgInfo{gc.Call, 0, 0, 0},
}

func proginfo(p *obj.Prog) (info gc.ProgInfo) {
	info = progtable[p.As]
	if info.Flags == 0 {
		info = progtable[arm64.AADD]
		gc.Fatal("proginfo: unknown instruction %v", p)
	}

	if (info.Flags&gc.RegRead != 0) && p.Reg == 0 {
		info.Flags &^= gc.RegRead
		info.Flags |= gc.RightRead /*CanRegRead |*/
	}

	if (p.From.Type == obj.TYPE_MEM || p.From.Type == obj.TYPE_ADDR) && p.From.Reg != 0 {
		info.Regindex |= RtoB(int(p.From.Reg))
		if p.Scond != 0 {
			info.Regset |= RtoB(int(p.From.Reg))
		}
	}

	if (p.To.Type == obj.TYPE_MEM || p.To.Type == obj.TYPE_ADDR) && p.To.Reg != 0 {
		info.Regindex |= RtoB(int(p.To.Reg))
		if p.Scond != 0 {
			info.Regset |= RtoB(int(p.To.Reg))
		}
	}

	if p.From.Type == obj.TYPE_ADDR && p.From.Sym != nil && (info.Flags&gc.LeftRead != 0) {
		info.Flags &^= gc.LeftRead
		info.Flags |= gc.LeftAddr
	}

	if p.As == obj.ADUFFZERO {
		info.Reguse |= RtoB(arm64.REGRT1)
		info.Regset |= RtoB(arm64.REGRT1)
	}

	if p.As == obj.ADUFFCOPY {
		// TODO(austin) Revisit when duffcopy is implemented
		info.Reguse |= RtoB(arm64.REGRT1) | RtoB(arm64.REGRT2) | RtoB(arm64.REG_R5)

		info.Regset |= RtoB(arm64.REGRT1) | RtoB(arm64.REGRT2)
	}

	return
}
