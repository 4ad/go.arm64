// Copyright 2015 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "go_asm.h"
#include "go_tls.h"
#include "funcdata.h"
#include "textflag.h"

DATA	runtime·main·f+0(SB)/8,$runtime·main(SB)
GLOBL	runtime·main·f(SB),RODATA,$8

TEXT runtime·breakpoint(SB),NOSPLIT,$-8-0
	MOV	ZR, (ZR) // TODO: TD
	RETURN

TEXT runtime·asminit(SB),NOSPLIT,$-8-0
	RETURN

TEXT runtime·reginit(SB),NOSPLIT,$-8-0
	// initialize essential FP registers
	FMOVD	$4503601774854144.0, F27
	FMOVD	$0.5, F29
	FSUBD	F29, F29, F28
	FADDD	F29, F29, F30
	FADDD	F30, F30, F31
	RETURN

/*
 *  go-routine
 */

// void gosave(Gobuf*)
// save state in Gobuf; setjmp
TEXT runtime·gosave(SB), NOSPLIT, $-8-8
	MOV	buf+0(FP), R3
	MOV	R1, gobuf_sp(R3)
	MOV	LR, gobuf_pc(R3)
	MOV	g, gobuf_g(R3)
	MOV	R0, gobuf_lr(R3)
	MOV	R0, gobuf_ret(R3)
	MOV	R0, gobuf_ctxt(R3)
	RETURN

// void gogo(Gobuf*)
// restore state from Gobuf; longjmp
TEXT runtime·gogo(SB), NOSPLIT, $-8-8
	MOV	buf+0(FP), R5
	MOV	gobuf_g(R5), g	// make sure g is not nil
	BL	runtime·save_g(SB)

	MOV	0(g), R4
	MOV	gobuf_sp(R5), R1
	MOV	gobuf_lr(R5), LR
	MOV	gobuf_ret(R5), R3
	MOV	gobuf_ctxt(R5), R11
	MOV	$0, gobuf_sp(R5)
	MOV	$0, gobuf_ret(R5)
	MOV	$0, gobuf_lr(R5)
	MOV	$0, gobuf_ctxt(R5)
	CMP	ZR, ZR // set condition codes for == test, needed by stack split
	MOV	gobuf_pc(R5), R6
	B	(R6)

// void mcall(fn func(*g))
// Switch to m->g0's stack, call fn(g).
// Fn must never return.  It should gogo(&g->sched)
// to keep running g.
TEXT runtime·mcall(SB), NOSPLIT, $-8-8
	// Save caller state in g->sched
	MOV	R1, (g_sched+gobuf_sp)(g)
	MOV	LR, (g_sched+gobuf_pc)(g)
	MOV	$0, (g_sched+gobuf_lr)(g)
	MOV	g, (g_sched+gobuf_g)(g)

	// Switch to m->g0 & its stack, call fn.
	MOV	g, R3
	MOV	g_m(g), R8
	MOV	m_g0(R8), g
	BL	runtime·save_g(SB)
	CMP	g, R3
	BNE	2(PC)
	B	runtime·badmcall(SB)
	MOV	fn+0(FP), R11			// context
	MOV	0(R11), R4			// code pointer
	MOV	(g_sched+gobuf_sp)(g), R1	// sp = m->g0->sched.sp
	MOV	R3, (R1)-8!
	MOV	R0, (R1)-8!
	BL	(R4)
	B	runtime·badmcall2(SB)

// systemstack_switch is a dummy routine that systemstack leaves at the bottom
// of the G stack.  We need to distinguish the routine that
// lives at the bottom of the G stack from the one that lives
// at the top of the system stack because the one at the top of
// the system stack terminates the stack walk (see topofstack()).
TEXT runtime·systemstack_switch(SB), NOSPLIT, $0-0
	UNDEF
	BL	(LR)	// make sure this function is not leaf
	RETURN

// func systemstack(fn func())
TEXT runtime·systemstack(SB), NOSPLIT, $0-8
	MOV	fn+0(FP), R3	// R3 = fn
	MOV	R3, R11		// context
	MOV	g_m(g), R4	// R4 = m

	MOV	m_gsignal(R4), R5	// R5 = gsignal
	CMP	g, R5
	BEQ	noswitch

	MOV	m_g0(R4), R5	// R5 = g0
	CMP	g, R5
	BEQ	noswitch

	MOV	m_curg(R4), R6
	CMP	g, R6
	BEQ	switch

	// Bad: g is not gsignal, not g0, not curg. What is it?
	// Hide call from linker nosplit analysis.
	MOV	$runtime·badsystemstack(SB), R3
	BL	(R3)

switch:
	// save our state in g->sched.  Pretend to
	// be systemstack_switch if the G stack is scanned.
	MOV	$runtime·systemstack_switch(SB), R6
	ADD	$8, R6	// get past prologue
	MOV	R6, (g_sched+gobuf_pc)(g)
	MOV	R1, (g_sched+gobuf_sp)(g)
	MOV	R0, (g_sched+gobuf_lr)(g)
	MOV	g, (g_sched+gobuf_g)(g)

	// switch to g0
	MOV	R5, g
	BL	runtime·save_g(SB)
	MOV	(g_sched+gobuf_sp)(g), R3
	// make it look like mstart called systemstack on g0, to stop traceback
	SUB	$8, R3
	MOV	$runtime·mstart(SB), R4
	MOV	R4, 0(R3)
	MOV	R3, R1

	// call target function
	MOV	0(R11), R3	// code pointer
	BL	(R3)

	// switch back to g
	MOV	g_m(g), R3
	MOV	m_curg(R3), g
	BL	runtime·save_g(SB)
	MOV	(g_sched+gobuf_sp)(g), R1
	MOV	$0, (g_sched+gobuf_sp)(g)
	RETURN

noswitch:
	// already on m stack, just call directly
	MOV	0(R11), R3	// code pointer
	BL	(R3)
	RETURN

TEXT runtime·rt0_go(SB),NOSPLIT,$0-0
	BL	main·main(SB)
	RETURN

TEXT runtime·fastrand1(SB),NOSPLIT,$-8-4
	MOV	g_m(g), R1
	MOV	m_fastrand(R1), R0
	ADDS	R0, R0
	BGE	notneg
	EOR	$0x88888eef, R0
notneg:
	MOV	R0, m_fastrand(R1)
	MOVW	R0, ret+0(FP)
	RETURN

TEXT runtime·memeq(SB),NOSPLIT,$-8-25
	MOV	a+0(FP), R1
	MOV	b+8(FP), R2
	MOV	size+16(FP), R3
	ADD	R1, R3, R6
	MOV	$1, R0
	MOVB	R0, ret+24(FP)
loop:
	CMP	R1, R6
	BEQ	done
	MOVB	(R1)1!, R4
	MOVB	(R2)1!, R5
	CMP	R4, R5
	BEQ	loop

	MOVW	$0, R0
	MOVB	R0, ret+24(FP)
done:
	RETURN

TEXT runtime·getcallerpc(SB),NOSPLIT,$-8-16
	MOV	0(SP), R0
	MOV	R0, ret+8(FP)
	RETURN

TEXT runtime·gogetcallerpc(SB),NOSPLIT,$-8-16
	MOV	0(SP), R0
	MOV	R0,ret+8(FP)
	RETURN

TEXT runtime·setcallerpc(SB),NOSPLIT,$-8-16
	MOV	pc+8(FP), R0
	MOV	R0, 0(SP)		// set calling pc
	RETURN

TEXT runtime·getcallersp(SB),NOSPLIT,$0-16
	MOV	argp+0(FP), R3
	SUB	$8, R0
	MOV	R0, ret+8(FP)
	RETURN

// func gogetcallersp(p unsafe.Pointer) uintptr
TEXT runtime·gogetcallersp(SB),NOSPLIT,$0-16
	MOV	sp+0(FP), R0
	SUB	$8, R0
	MOV	R0,ret+8(FP)
	RETURN

TEXT runtime·abort(SB),NOSPLIT,$-8-0
	MOVW	(ZR), ZR
	UNDEF

// eqstring tests whether two strings are equal.
// See runtime_test.go:eqstring_generic for
// equivalent Go code.
TEXT runtime·eqstring(SB),NOSPLIT,$-8-33
	MOV	s1len+8(FP), R0
	MOV	s2len+24(FP), R1
	CMP	R0, R1	// are the strings the same length ?
	BNE	noteq	// nope
	MOVW	s1str+0(FP), R2
	MOVW	s2str+16(FP), R3
	CMP	R2, R3	// same base ptr ?
	BEQ	eq
	ADD	R2, R0, R6
loop:
	CMP	R2, R6	// reached the end ?
	BEQ	eq	// strings are equal
	MOVBU	(R2)1!, R4
	MOVBU	(R3)1!, R5
	CMP	R4, R5	// bytes are the same ?
	BEQ	loop	// yup, otherwise fall through
noteq:
	MOV	$0, R7
	MOVB	R7, v+32(FP)
	RETURN
eq:
	MOV	$1, R7
	MOVB	R7, v+32(FP)
	RETURN

// bool cas(uint32 *ptr, uint32 old, uint32 new)
// Atomically:
//	if(*val == old){
//		*val = new;
//		return 1;
//	} else
//		return 0;
TEXT runtime·cas(SB), NOSPLIT, $0-17
	MOV	ptr+0(FP), R0
	MOVW	old+8(FP), R1
	MOVW	new+12(FP), R2
again:
	LDAXRW	(R0), R3
	CMPW	R3, R1
	BNE	ok
	STLXRW	R2, (R0), R3
	CBNZ	R3, again
ok:
	CSET	EQ, R0
	MOVB	R0, ret+16(FP)
	RETURN

TEXT runtime·casuintptr(SB), NOSPLIT, $0-25
	B	runtime·cas64(SB)

TEXT runtime·atomicloaduintptr(SB), NOSPLIT, $-8-16
	B	runtime·atomicload64(SB)

TEXT runtime·atomicloaduint(SB), NOSPLIT, $-8-16
	B	runtime·atomicload64(SB)

TEXT runtime·atomicstoreuintptr(SB), NOSPLIT, $0-16
	B	runtime·atomicstore64(SB)

// bool casp(void **val, void *old, void *new)
// Atomically:
//	if(*val == old){
//		*val = new;
//		return 1;
//	} else
//		return 0;
TEXT runtime·casp1(SB), NOSPLIT, $0-25
	B runtime·cas64(SB)

TEXT runtime·getg(SB),NOSPLIT,$-8-8
	MOV	g, ret+0(FP)
	RETURN

// void jmpdefer(fv, sp);
// called from deferreturn.
// 1. grab stored LR for caller
// 2. sub 4 bytes to get back to BL deferreturn
// 3. BR to fn
TEXT runtime·jmpdefer(SB), NOSPLIT, $-8-16
	MOV	0(R1), R0
	SUB	$4, R0
	MOV	R0, LR

	MOV	fv+0(FP), R11
	MOV	argp+8(FP), R1
	SUB	$8, R1
	MOV	0(R11), R3
	B	(R3)

// A Duff's device for zeroing memory.
// The compiler jumps to computed addresses within
// this routine to zero chunks of memory.  Do not
// change this code without also changing the code
// in ../cmd/7g/ggen.c:/^clearfat.
// ZR: always zero
// R2 (aka REGRT1): ptr to memory to be zeroed - 8
// On return, R2 points to the last zeroed dword.
TEXT runtime·duffzero(SB), NOSPLIT, $-8-0
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	MOV	ZR, (R2)8!
	RETURN


TEXT runtime·return0(SB), NOSPLIT, $0
	MOVW	$0, R0
	RETURN
