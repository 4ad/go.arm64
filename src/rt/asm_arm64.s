// Copyright 2015 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "go_asm.h"
#include "../runtime/go_tls.h"
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
	MOV	SP, R0
	MOV	R0, gobuf_sp(R3)
	MOV	LR, gobuf_pc(R3)
	MOV	g, gobuf_g(R3)
	MOV	ZR, gobuf_lr(R3)
	MOV	ZR, gobuf_ret(R3)
	MOV	ZR, gobuf_ctxt(R3)
	RETURN

// void gogo(Gobuf*)
// restore state from Gobuf; longjmp
TEXT runtime·gogo(SB), NOSPLIT, $-8-8
	MOV	buf+0(FP), R5
	MOV	gobuf_g(R5), g	// make sure g is not nil
	BL	runtime·save_g(SB)

	MOV	0(g), R4
	MOV	gobuf_sp(R5), R0
	MOV	R0, SP
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
	MOV	SP, R0
	MOV	R0, (g_sched+gobuf_sp)(g)
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
	MOV	(g_sched+gobuf_sp)(g), R0
	MOV	R0, SP	// sp = m->g0->sched.sp
	MOV	R3, -8(SP)
	MOV	R0, -16(SP)
	SUB $16, SP
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
	MOV	R3, R26		// context
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
	MOV	SP, R0
	MOV	R0, (g_sched+gobuf_sp)(g)
	MOV	$0, (g_sched+gobuf_lr)(g)
	MOV	g, (g_sched+gobuf_g)(g)

	// switch to g0
	MOV	R5, g
	BL	runtime·save_g(SB)
	MOV	(g_sched+gobuf_sp)(g), R3
	// make it look like mstart called systemstack on g0, to stop traceback
	SUB	$16, R3
	AND	$~15, R3
	MOV	$runtime·mstart(SB), R4
	MOV	R4, 0(R3)
	MOV	R3, SP

	// call target function
	MOV	0(R26), R3	// code pointer
	BL	(R3)

	// switch back to g
	MOV	g_m(g), R3
	MOV	m_curg(R3), g
	BL	runtime·save_g(SB)
	MOV	(g_sched+gobuf_sp)(g), R0
	MOV	R0, SP
	MOV	$0, (g_sched+gobuf_sp)(g)
	RETURN

noswitch:
	// already on m stack, just call directly
	MOV	0(R26), R3	// code pointer
	BL	(R3)
	RETURN

TEXT runtime·rt0_go(SB),NOSPLIT,$0
	// SP = stack; R0 = argc; R1 = argv

	// initialize essential registers
	BL	runtime·reginit(SB)

	SUB	$32, SP
	MOVW	R0, 8(SP) // argc
	MOV	R1, 16(SP) // argv

	// create istack out of the given (operating system) stack.
	// _cgo_init may update stackguard.
	MOV	$runtime·g0(SB), g
	MOV SP, R7
	MOV	$(-64*1024)(R7), R0
	MOV	R0, g_stackguard0(g)
	MOV	R0, g_stackguard1(g)
	MOV	R0, (g_stack+stack_lo)(g)
	MOV	R7, (g_stack+stack_hi)(g)

	// if there is a _cgo_init, call it using the gcc ABI.
	MOV	_cgo_init(SB), R12
	CMP	$0, R12
	BEQ	nocgo

	BL	runtime·abort(SB)

nocgo:
	// update stackguard after _cgo_init
	MOV	(g_stack+stack_lo)(g), R0
	ADD	$const__StackGuard, R0
	MOV	R0, g_stackguard0(g)
	MOV	R0, g_stackguard1(g)

	// set the per-goroutine and per-mach "registers"
	MOV	$runtime·m0(SB), R0

	// save m->g0 = g0
	MOV	g, m_g0(R0)
	// save m0 to g0->m
	MOV	R0, g_m(g)

	BL	runtime·check(SB)

	MOVW	8(SP), R0	// copy argc
	MOVW	R0, -8(SP)
	MOV	16(SP), R0		// copy argv
	MOV	R0, 0(SP)
	BL	runtime·args(SB)
	BL	runtime·osinit(SB)
	BL	runtime·schedinit(SB)

	// create a new goroutine to start program
	MOV	$runtime·main·f(SB), R0		// entry
	MOV	SP, R7
	MOV	$0, -8(R7)!
	MOV	R0, -8(R7)!
	MOV	$0, -8(R7)!
	MOV	$0, -8(R7)!
	MOV	R7, SP
	BL	runtime·newproc(SB)
	ADD	$32, SP

	// start this M
	BL	runtime·mstart(SB)

	MOV	$0, (ZR)
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
	MOVB	1(R1)!, R4
	MOVB	1(R2)!, R5
	CMP	R4, R5
	BEQ	loop

	MOVW	$0, R0
	MOVB	R0, ret+24(FP)
done:
	RETURN

// cgocallback(void (*fn)(void*), void *frame, uintptr framesize)
// Turn the fn into a Go func (by taking its address) and call
// cgocallback_gofunc.
TEXT runtime·cgocallback(SB),NOSPLIT,$24-24
	MOV	$fn+0(FP), R3
	MOV	R3, 8(SP)
	MOV	frame+8(FP), R3
	MOV	R3, 16(SP)
	MOV	framesize+16(FP), R3
	MOV	R3, 24(SP)
	MOV	$runtime·cgocallback_gofunc(SB), R3
	BL	(R3)
	RETURN

// cgocallback_gofunc(FuncVal*, void *frame, uintptr framesize)
// See cgocall.c for more details.
TEXT ·cgocallback_gofunc(SB),NOSPLIT,$16-24
	NO_LOCAL_POINTERS

	// Load m and g from thread-local storage.
	MOVB	runtime·iscgo(SB), R3
	CMP	$0, R3 
	BEQ	nocgo
	// TODO(aram):
	BL runtime·abort(SB)
nocgo:

	// If g is nil, Go did not create the current thread.
	// Call needm to obtain one for temporary use.
	// In this case, we're running on the thread stack, so there's
	// lots of space, but the linker doesn't know. Hide the call from
	// the linker analysis by using an indirect call.
	CMP	$0, g
	BNE	havem
	MOV	g, savedm-8(SP) // g is zero, so is m.
	MOV	$runtime·needm(SB), R3
	BL	(R3)

	// Set m->sched.sp = SP, so that if a panic happens
	// during the function we are about to execute, it will
	// have a valid SP to run on the g0 stack.
	// The next few lines (after the havem label)
	// will save this SP onto the stack and then write
	// the same SP back to m->sched.sp. That seems redundant,
	// but if an unrecovered panic happens, unwindm will
	// restore the g->sched.sp from the stack location
	// and then systemstack will try to use it. If we don't set it here,
	// that restored SP will be uninitialized (typically 0) and
	// will not be usable.
	MOV	g_m(g), R3
	MOV	m_g0(R3), R3
	MOV	SP, R0
	MOV	R0, (g_sched+gobuf_sp)(R3)

havem:
	MOV	g_m(g), R8
	MOV	R8, savedm-8(SP)
	// Now there's a valid m, and we're running on its m->g0.
	// Save current m->g0->sched.sp on stack and then set it to SP.
	// Save current sp in m->g0->sched.sp in preparation for
	// switch back to m->curg stack.
	// NOTE: unwindm knows that the saved g->sched.sp is at 8(R1) aka savedsp-16(SP).
	MOV	m_g0(R8), R3
	MOV	(g_sched+gobuf_sp)(R3), R4
	MOV	R4, savedsp-16(SP)
	MOV	SP, R0
	MOV	R0, (g_sched+gobuf_sp)(R3)

	// Switch to m->curg stack and call runtime.cgocallbackg.
	// Because we are taking over the execution of m->curg
	// but *not* resuming what had been running, we need to
	// save that information (m->curg->sched) so we can restore it.
	// We can restore m->curg->sched.sp easily, because calling
	// runtime.cgocallbackg leaves SP unchanged upon return.
	// To save m->curg->sched.pc, we push it onto the stack.
	// This has the added benefit that it looks to the traceback
	// routine like cgocallbackg is going to return to that
	// PC (because the frame we allocate below has the same
	// size as cgocallback_gofunc's frame declared above)
	// so that the traceback will seamlessly trace back into
	// the earlier calls.
	//
	// In the new goroutine, -16(SP) and -8(SP) are unused.
	MOV	m_curg(R8), g
	BL	runtime·save_g(SB)
	MOV	(g_sched+gobuf_sp)(g), R4 // prepare stack as R4
	MOV	(g_sched+gobuf_pc)(g), R5
	MOV	R5, -24(R4)
	MOV	$-24(R4), R0
	MOV	R0, SP
	BL	runtime·cgocallbackg(SB)

	// Restore g->sched (== m->curg->sched) from saved values.
	MOV	0(SP), R5
	MOV	R5, (g_sched+gobuf_pc)(g)
	MOV	$24(SP), R4
	MOV	R4, (g_sched+gobuf_sp)(g)

	// Switch back to m->g0's stack and restore m->g0->sched.sp.
	// (Unlike m->curg, the g0 goroutine never uses sched.pc,
	// so we do not have to restore it.)
	MOV	g_m(g), R8
	MOV	m_g0(R8), g
	BL	runtime·save_g(SB)
	MOV	(g_sched+gobuf_sp)(g), R0
	MOV	R0, SP
	MOV	savedsp-16(SP), R4
	MOV	R4, (g_sched+gobuf_sp)(g)

	// If the m on entry was nil, we called needm above to borrow an m
	// for the duration of the call. Since the call is over, return it with dropm.
	MOV	savedm-8(SP), R6
	CMP	$0, R6
	BNE	droppedm
	MOV	$runtime·dropm(SB), R3
	BL	(R3)
droppedm:

	// Done!
	RET

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
	B	(ZR)
	UNDEF

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
	CMPW	R1, R3
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
	MOV	0(SP), R0
	SUB	$4, R0
	MOV	R0, LR

	MOV	fv+0(FP), R11
	MOV	argp+8(FP), R0
	MOV	R0, SP
	SUB	$8, SP
	MOV	0(R11), R3
	B	(R3)

// A Duff's device for zeroing memory.
// The compiler jumps to computed addresses within
// this routine to zero chunks of memory.  Do not
// change this code without also changing the code
// in ../cmd/7g/ggen.c:/^clearfat.
// ZR: always zero
// R16 (aka REGRT1): ptr to memory to be zeroed - 8
// On return, R16 points to the last zeroed dword.
TEXT runtime·duffzero(SB), NOSPLIT, $-8-0
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	MOV	ZR, 8(R16)!
	RETURN

TEXT runtime·return0(SB), NOSPLIT, $0
	MOVW	$0, R0
	RETURN

// void setg(G*); set g. for use by needm.
TEXT runtime·setg(SB), NOSPLIT, $0-8
	MOV	gg+0(FP), g
	// This only happens if iscgo, so jump straight to save_g
	BL	runtime·save_g(SB)
	RETURN

// reflectcall: call a function with the given argument list
// func call(argtype *_type, f *FuncVal, arg *byte, argsize, retoffset uint32).
// we don't have variable-sized frames, so we use a small number
// of constant-sized-frame functions to encode a few bits of size in the pc.
// Caution: ugly multiline assembly macros in your future!

#define DISPATCH(NAME,MAXSIZE)		\
	MOV	$MAXSIZE, R0;		\
	CMP	R3, R0;		\
	BGT	4(PC);			\
	MOV	$NAME(SB), R1;	\
	B	(R1)
// Note: can't just "B NAME(SB)" - bad inlining results.

TEXT reflect·call(SB), NOSPLIT, $0-0
	BL	·reflectcall(SB)

TEXT ·reflectcall(SB), NOSPLIT, $-8-32
	MOVWU argsize+24(FP), R3
	// NOTE(rsc): No call16, because CALLFN needs four words
	// of argument space to invoke callwritebarrier.
	DISPATCH(runtime·call32, 32)
	DISPATCH(runtime·call64, 64)
	DISPATCH(runtime·call128, 128)
	DISPATCH(runtime·call256, 256)
	DISPATCH(runtime·call512, 512)
	DISPATCH(runtime·call1024, 1024)
	DISPATCH(runtime·call2048, 2048)
	DISPATCH(runtime·call4096, 4096)
	DISPATCH(runtime·call8192, 8192)
	DISPATCH(runtime·call16384, 16384)
	DISPATCH(runtime·call32768, 32768)
	DISPATCH(runtime·call65536, 65536)
	DISPATCH(runtime·call131072, 131072)
	DISPATCH(runtime·call262144, 262144)
	DISPATCH(runtime·call524288, 524288)
	DISPATCH(runtime·call1048576, 1048576)
	DISPATCH(runtime·call2097152, 2097152)
	DISPATCH(runtime·call4194304, 4194304)
	DISPATCH(runtime·call8388608, 8388608)
	DISPATCH(runtime·call16777216, 16777216)
	DISPATCH(runtime·call33554432, 33554432)
	DISPATCH(runtime·call67108864, 67108864)
	DISPATCH(runtime·call134217728, 134217728)
	DISPATCH(runtime·call268435456, 268435456)
	DISPATCH(runtime·call536870912, 536870912)
	DISPATCH(runtime·call1073741824, 1073741824)
	MOV	$runtime·badreflectcall(SB), R0
	B	(R0)

#define CALLFN(NAME,MAXSIZE)			\
TEXT NAME(SB), WRAPPER, $MAXSIZE-24;		\
	NO_LOCAL_POINTERS;			\
	/* copy arguments to stack */		\
	MOV	arg+16(FP), R3;			\
	MOVWU	argsize+24(FP), R4;			\
	MOV	SP, R5;				\
	ADD	$(8-1), R5;			\
	SUB	$1, R3;				\
	ADD	R5, R4;				\
	CMP	R5, R4;				\
	BEQ	4(PC);				\
	MOVBU	1(R3)!, R6;			\
	MOVBU	R6, 1(R5)!;			\
	B	-4(PC);				\
	/* call function */			\
	MOV	f+8(FP), R11;			\
	MOV	(R11), R0;			\
	PCDATA  $PCDATA_StackMapIndex, $0;	\
	BL	(R0);				\
	/* copy return values back */		\
	MOV	arg+16(FP), R3;			\
	MOVWU	n+24(FP), R4;			\
	MOVWU	retoffset+28(FP), R6;		\
	MOV	SP, R5;				\
	ADD	R6, R5; 			\
	ADD	R6, R3;				\
	SUB	R6, R4;				\
	ADD	$(8-1), R5;			\
	SUB	$1, R3;				\
	ADD	R5, R4;				\
loop:						\
	CMP	R5, R4;				\
	BEQ	end;				\
	MOVBU	1(R5)!, R6;			\
	MOVBU	R6, 1(R3)!;			\
	B	loop;				\
end:						\
	/* execute write barrier updates */	\
	MOV	argtype+0(FP), R7;		\
	MOV	arg+16(FP), R3;			\
	MOVWU	n+24(FP), R4;			\
	MOVWU	retoffset+28(FP), R6;		\
	MOV	R7, 8(R1);			\
	MOV	R3, 16(R1);			\
	MOV	R4, 24(R1);			\
	MOV	R6, 32(R1);			\
	BL	runtime·callwritebarrier(SB);	\
	RETURN

CALLFN(·call16, 16)
CALLFN(·call32, 32)
CALLFN(·call64, 64)
CALLFN(·call128, 128)
CALLFN(·call256, 256)
CALLFN(·call512, 512)
CALLFN(·call1024, 1024)
CALLFN(·call2048, 2048)
CALLFN(·call4096, 4096)
CALLFN(·call8192, 8192)
CALLFN(·call16384, 16384)
CALLFN(·call32768, 32768)
CALLFN(·call65536, 65536)
CALLFN(·call131072, 131072)
CALLFN(·call262144, 262144)
CALLFN(·call524288, 524288)
CALLFN(·call1048576, 1048576)
CALLFN(·call2097152, 2097152)
CALLFN(·call4194304, 4194304)
CALLFN(·call8388608, 8388608)
CALLFN(·call16777216, 16777216)
CALLFN(·call33554432, 33554432)
CALLFN(·call67108864, 67108864)
CALLFN(·call134217728, 134217728)
CALLFN(·call268435456, 268435456)
CALLFN(·call536870912, 536870912)
CALLFN(·call1073741824, 1073741824)

TEXT runtime·procyield(SB),NOSPLIT,$0-0
	MOVW	cycles+0(FP), R0
again:
	YIELD
	SUBW	$1, R0
	CBNZ	R0, again
	RETURN

// asmcgocall(void(*fn)(void*), void *arg)
// Call fn(arg) on the scheduler stack,
// aligned appropriately for the gcc ABI.
// See cgocall.c for more details.
TEXT ·asmcgocall(SB),NOSPLIT,$0-16
	MOV	fn+0(FP), R3
	MOV	arg+8(FP), R4
	BL	asmcgocall<>(SB)
	RET

TEXT ·asmcgocall_errno(SB),NOSPLIT,$0-20
	MOV	fn+0(FP), R3
	MOV	arg+8(FP), R4
	BL	asmcgocall<>(SB)
	MOVW	R0, ret+16(FP)
	RET

// asmcgocall common code. fn in R3, arg in R4. returns errno in R0.
TEXT asmcgocall<>(SB),NOSPLIT,$0-0
	MOV	SP, R2		// save original stack pointer
	MOV	g, R5

	// Figure out if we need to switch to m->g0 stack.
	// We get called to create new OS threads too, and those
	// come in on the m->g0 stack already.
	MOV	g_m(g), R6
	MOV	m_g0(R6), R6
	CMP	R6, g
	BEQ	g0
	BL	gosave<>(SB)
	MOV	R6, g
	BL	runtime·save_g(SB)
	MOV	(g_sched+gobuf_sp)(g), R13
	MOV	R13, SP

	// Now on a scheduling stack (a pthread-created stack).
g0:
	// Save room for two of our pointers, plus 32 bytes of callee
	// save area that lives on the caller stack.
	MOV	SP, R13
	SUB	$48, R13
	AND	$~15, R13	// 16-byte alignment for gcc ABI
	MOV	R13, SP
	MOV	R5, 40(SP)	// save old g on stack
	MOV	(g_stack+stack_hi)(R5), R5
	SUB	R2, R5
	MOV	R5, 32(SP)	// save depth in old g stack (can't just save SP, as stack might be copied during a callback)
	MOV	R0, 0(SP)	// clear back chain pointer (TODO can we give it real back trace information?)
	// This is a "global call", so put the global entry point in r12
	MOV	R3, R12
	MOV	R4, R0
	BL	(R12)

	// Restore g, stack pointer.  R0 is errno, so don't touch it
	MOV	40(SP), g
	BL	runtime·save_g(SB)
	MOV	(g_stack+stack_hi)(g), R5
	MOV	32(SP), R6
	SUB	R6, R5
	MOV	R5, SP
	RET

// TODO(aram): doc..
TEXT runtime·save_g(SB),NOSPLIT,$-8-0
	MOVB	runtime·iscgo(SB), R0
	CMP	$0, R0
	BEQ	nocgo

	BL	runtime·abort(SB)

nocgo:
	RET

// Save state of caller into g->sched. Smashes R0.
TEXT gosave<>(SB),NOSPLIT,$-8
	MOV	LR, (g_sched+gobuf_pc)(g)
	MOV SP, R0
	MOV	R0, (g_sched+gobuf_sp)(g)
	MOV	LR, (g_sched+gobuf_lr)(g)
	MOV	LR, (g_sched+gobuf_ret)(g)
	MOV	LR, (g_sched+gobuf_ctxt)(g)
	RETURN

// memequal_varlen(a, b unsafe.Pointer) bool
TEXT runtime·memequal_varlen(SB),NOSPLIT,$40-17
	MOV	a+0(FP), R3
	MOV	b+8(FP), R4
	CMP	R3, R4
	BEQ	eq
	MOV	8(R0), R5    // compiler stores size at offset 8 in the closure
	MOV	R3, 8(SP)
	MOV	R4, 16(SP)
	MOV	R5, 24(SP)
	BL	runtime·memeq(SB)
	MOVBU	32(SP), R3
	MOVB	R3, ret+16(FP)
	RETURN
eq:
	MOV	$1, R3
	MOVB	R3, ret+16(FP)
	RETURN

// memhash_varlen(p unsafe.Pointer, h seed) uintptr
// redirects to memhash(p, h, size) using the size
// stored in the closure.
TEXT runtime·memhash_varlen(SB),NOSPLIT,$40-24
	GO_ARGS
	NO_LOCAL_POINTERS
	MOV	p+0(FP), R3
	MOV	h+8(FP), R4
	MOV	8(R0), R5
	MOV	R3, 8(SP)
	MOV	R4, 16(SP)
	MOV	R5, 24(SP)
	BL	runtime·memhash(SB)
	MOV	32(SP), R3
	MOV	R3, ret+16(FP)
	RETURN

// The top-most function running on a goroutine
// returns to goexit+PCQuantum.
TEXT runtime·goexit(SB),NOSPLIT,$-8-0
	MOV	R0, R0	// NOP
	BL	runtime·goexit1(SB)	// does not return

TEXT runtime·prefetcht0(SB),NOSPLIT,$0-8
	RETURN

TEXT runtime·prefetcht1(SB),NOSPLIT,$0-8
	RETURN

TEXT runtime·prefetcht2(SB),NOSPLIT,$0-8
	RETURN

TEXT runtime·prefetchnta(SB),NOSPLIT,$0-8
	RETURN

// TODO(aram):
TEXT runtime·morestack(SB),NOSPLIT,$-8-0
	RET
