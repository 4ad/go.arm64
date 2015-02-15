// Copyright 2014 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

//
// System calls and other sys.stuff for arm64, Linux
//

#include "go_asm.h"
#include "../runtime/go_tls.h"
#include "textflag.h"

#define AT_FDCWD -100

#define SYS_exit		93
#define SYS_read		63
#define SYS_write		64
#define SYS_openat		56
#define SYS_close		57
#define SYS_fcntl		25
#define SYS_gettimeofday	169
#define SYS_pselect6		72
#define SYS_mmap		222
#define SYS_munmap		215
#define SYS_setitimer		103
#define SYS_clone		220
#define SYS_sched_yield		124
#define SYS_rt_sigreturn	139
#define SYS_rt_sigaction	134
#define SYS_rt_sigprocmask	135
#define SYS_sigaltstack		132
#define SYS_getrlimit		163
#define SYS_madvise		233
#define SYS_mincore		232
#define SYS_gettid		178
#define SYS_tkill		130
#define SYS_futex		98
#define SYS_sched_getaffinity	123
#define SYS_exit_group		94
#define SYS_epoll_create1	20
#define SYS_epoll_ctl		21
#define SYS_epoll_pwait		22
#define SYS_clock_gettime	113

#define SYS_brk			214

TEXT runtime·brk(SB),NOSPLIT,$-8-16
	MOV	addr+0(FP), R0
	MOV	$SYS_brk, R8
	SVC
	MOV	R0, ret+8(FP)
	RETURN

TEXT runtime·exit(SB),NOSPLIT,$-8-4
	MOVW	code+0(FP), R0
	MOV	$SYS_exit_group, R8
	SVC	
	RETURN

TEXT runtime·exit1(SB),NOSPLIT,$-8-4
	MOVW	code+0(FP), R0
	MOV	$SYS_exit, R8
	SVC
	RETURN

TEXT runtime·open(SB),NOSPLIT,$-8-20
	MOV	$AT_FDCWD, R0
	MOV	name+0(FP), R1
	MOVW	mode+8(FP), R2
	MOVW	perm+12(FP), R3
	MOV	$SYS_openat, R8
	SVC
	MOVW	R0, ret+16(FP)
	RETURN

TEXT runtime·close(SB),NOSPLIT,$-8-12
	MOVW	fd+0(FP), R0 
	MOV	$SYS_close, R8
	SVC
	MOVW	R0, ret+8(FP)
	RETURN

TEXT runtime·write(SB),NOSPLIT,$-8-28
	MOV	fd+0(FP), R0
	MOV	p+8(FP), R1
	MOVW	n+16(FP), R2
	MOV	$SYS_write, R8
	SVC
	MOVW	R0, ret+24(FP)
	RETURN

TEXT runtime·read(SB),NOSPLIT,$-8-28
	MOVW	fd+0(FP), R0
	MOV	p+8(FP), R1
	MOVW	n+16(FP), R2
	MOV	$SYS_read, R8
	SVC
	MOVW	R0, ret+24(FP)
	RETURN

TEXT runtime·getrlimit(SB),NOSPLIT,$-8-20
	MOVW	kind+0(FP), R0
	MOV	limit+8(FP), R1
	MOV	$SYS_getrlimit, R8
	SVC
	MOVW	R0, ret+16(FP)
	RETURN

TEXT runtime·usleep(SB),NOSPLIT,$16-4
	MOVW	usec+0(FP), R3
	MOV	R3, R5
	MOVW	$1000000000, R4
	UDIV	R4, R3
	MOV	R3, 8(SP)
	MUL	R3, R4
	SUB	R4, R5
	MOV	R5, 16(SP)

	// pselect6(0, 0, 0, 0, &ts, 0)
	MOV	$0, R0
	MOV	$0, R1
	MOV	$0, R2
	MOV	$0, R3
	ADD	$8, SP, R4
	MOV	$0, R5
	MOV	$SYS_pselect6, R8
	SVC
	RETURN

TEXT runtime·raise(SB),NOSPLIT,$-8
	MOV	$SYS_gettid, R8
	SVC
	MOVW	R0, R0	// arg 1 tid
	MOVW	sig+0(FP), R1	// arg 2
	MOV	$SYS_tkill, R8
	SVC
	RETURN

TEXT runtime·setitimer(SB),NOSPLIT,$-8-24
	MOVW	mode+0(FP), R0
	MOV	new+8(FP), R1
	MOV	old+16(FP), R2
	MOV	$SYS_setitimer, R8
	SVC
	RETURN

TEXT runtime·mincore(SB),NOSPLIT,$-8-28
	MOV	addr+0(FP), R0
	MOV	n+8(FP), R1
	MOV	dst+16(FP), R2
	MOV	$SYS_mincore, R8
	SVC
	MOVW	R0, ret+24(FP)
	RETURN

// func now() (sec int64, nsec int32)
TEXT time·now(SB),NOSPLIT,$16
	MOV	$0(SP), R0
	MOV	$0, R1
	MOV	$SYS_gettimeofday, R8
	SVC
	MOV	0(SP), R3	// sec
	MOV	8(SP), R5	// usec
	MOV	$1000, R4
	MUL	R4, R5
	MOV	R3, sec+0(FP)
	MOVW	R5, nsec+8(FP)
	RETURN

TEXT runtime·nanotime(SB),NOSPLIT,$16
	MOVW	$1, R0 // CLOCK_MONOTONIC
//	MOV	$0(SP), R1
	MOV	SP, R1
	MOV	$SYS_clock_gettime, R8
	SVC
	MOV	0(SP), R3	// sec
	MOV	8(SP), R5	// nsec
	// sec is in R3, nsec in R5
	// return nsec in R3
	MOV	$1000000000, R4
	MUL	R4, R3
	ADD	R5, R3
	MOV	R3, ret+0(FP)
	RETURN

TEXT runtime·rtsigprocmask(SB),NOSPLIT,$-8-28
	MOVW	sig+0(FP), R0
	MOV	new+8(FP), R1
	MOV	old+16(FP), R2
	MOVW	size+24(FP), R3
	MOV	$SYS_rt_sigprocmask, R8
	SVC
	BVC	done
	B	(ZR)	// crash
done:
	RETURN

TEXT runtime·rt_sigaction(SB),NOSPLIT,$-8-36
	MOV	sig+0(FP), R0
	MOV	new+8(FP), R1
	MOV	old+16(FP), R2
	MOV	size+24(FP), R3
	MOV	$SYS_rt_sigaction, R8
	SVC
	MOVW	R0, ret+32(FP)
	RETURN

TEXT runtime·sigtramp(SB),NOSPLIT,$64
	// check that g exists
	CMP	g, ZR
	BNE	6(PC)
	MOV	R3, 8(SP)
	MOV	$runtime·badsignal(SB), R0
	BL	(R0)
	RETURN

	// save g
	MOV	g, 40(SP)
	MOV	g, R6

	// g = m->gsignal
	MOV	g_m(g), R7
	MOV	m_gsignal(R7), g

	MOVW	R3, 8(SP)
	MOV	R4, 16(SP)
	MOV	R5, 24(SP)
	MOV	R6, 32(SP)

	BL	runtime·sighandler(SB)

	// restore g
	MOV	40(SP), g
	RETURN

TEXT runtime·mmap(SB),NOSPLIT,$-8
	MOV	addr+0(FP), R0
	MOV	n+8(FP), R1
	MOVW	prot+16(FP), R2
	MOVW	flags+20(FP), R3
	MOVW	fd+24(FP), R4
	MOVW	off+28(FP), R5

	MOV	$SYS_mmap, R8
	SVC
	MOV	R0, ret+32(FP)
	RETURN

TEXT runtime·munmap(SB),NOSPLIT,$-8
	MOV	addr+0(FP), R0
	MOV	n+8(FP), R1
	MOV	$SYS_munmap, R8
	SVC
	BVC	cool
	MOV	R0, 0xf0(R0)
cool:
	RETURN

TEXT runtime·madvise(SB),NOSPLIT,$-8
	MOV	addr+0(FP), R0
	MOV	n+8(FP), R1
	MOVW	flags+16(FP), R2
	MOV	$SYS_madvise, R8
	SVC
	// ignore failure - maybe pages are locked
	RETURN

// int64 futex(int32 *uaddr, int32 op, int32 val,
//	struct timespec *timeout, int32 *uaddr2, int32 val2);
TEXT runtime·futex(SB),NOSPLIT,$-8
	MOV	addr+0(FP), R0
	MOVW	op+8(FP), R1
	MOVW	val+12(FP), R2
	MOV	ts+16(FP), R3
	MOV	addr2+24(FP), R4
	MOVW	val3+32(FP), R5
	MOV	$SYS_futex, R8
	MOVW	R0, ret+40(FP)
	RETURN

// int64 clone(int32 flags, void *stk, M *mp, G *gp, void (*fn)(void));
TEXT runtime·clone(SB),NOSPLIT,$-8
	MOVW	flags+0(FP), R0
	MOV	stk+8(FP), R1

	// Copy mp, gp, fn off parent stack for use by child.
	MOV	mm+16(FP), R10
	MOV	gg+24(FP), R11
	MOV	fn+32(FP), R12

	MOV	R10, -8(R1)
	MOV	R11, -16(R1)
	MOV	R12, -24(R1)
	MOV	$1234, R10
	MOV	R10, -32(R1)

	MOV	$SYS_clone, R8
	SVC

	// In parent, return.
	CMP	ZR, R0
	BEQ	child
	MOVW	R0, ret+40(FP)
	RETURN
child:

	// In child, on new stack.
	MOV	-32(SP), R10
	MOV	$1234, R0
	CMP	R0, R10
	BEQ	good
	B	(ZR) // crash

	// Initialize m->procid to Linux tid
good:
	MOV	$SYS_gettid, R8
	SVC

	MOV	-24(SP), R12
	MOV	-16(SP), R11
	MOV	-8(SP), R10

	MOV	R0, m_procid(R10)

	// TODO: setup TLS.

	// In child, set up new stack
	MOV	R10, g_m(R11)
	MOV	R11, g
	//CALL	runtime·stackcheck(SB)

	// Call fn
	MOV	R12, R0
	BL	(R0)

	// It shouldn't return.	 If it does, exit
	MOVW	$111, R0
again:
	MOV	$SYS_exit_group, R8
	SVC
	B	again	// keep exiting

TEXT runtime·sigaltstack(SB),NOSPLIT,$-8
	MOV	new+0(FP), R0
	MOV	old+8(FP), R1
	MOV	$SYS_sigaltstack, R8
	SVC
	BVC	ok
	B	(ZR)  // crash
ok:
	RETURN

TEXT runtime·osyield(SB),NOSPLIT,$-8
	MOV	$SYS_sched_yield, R8
	SVC
	RETURN

TEXT runtime·sched_getaffinity(SB),NOSPLIT,$-8
	MOV	pid+0(FP), R0
	MOV	len+8(FP), R1
	MOV	buf+16(FP), R2
	MOV	$SYS_sched_getaffinity, R8
	SVC
	MOVW	R0, ret+24(FP)
	RETURN

// int32 runtime·epollcreate(int32 size);
TEXT runtime·epollcreate(SB),NOSPLIT,$-8
	MOVW	$0, R0
	MOV	$SYS_epoll_create1, R8
	SVC
	MOVW	R0, ret+8(FP)
	RETURN

// int32 runtime·epollcreate1(int32 flags);
TEXT runtime·epollcreate1(SB),NOSPLIT,$-8
	MOVW	flags+0(FP), R0
	MOV	$SYS_epoll_create1, R8
	SVC
	MOVW	R0, ret+8(FP)
	RETURN

// func epollctl(epfd, op, fd int32, ev *epollEvent) int
TEXT runtime·epollctl(SB),NOSPLIT,$-8
	MOVW	epfd+0(FP), R0
	MOVW	op+4(FP), R1
	MOVW	fd+8(FP), R2
	MOV	ev+16(FP), R3
	MOV	$SYS_epoll_ctl, R8
	SVC
	MOVW	R0, ret+24(FP)
	RETURN

// int32 runtime·epollwait(int32 epfd, EpollEvent *ev, int32 nev, int32 timeout);
TEXT runtime·epollwait(SB),NOSPLIT,$-8
	MOVW	epfd+0(FP), R0
	MOV	ev+8(FP), R1
	MOVW	nev+16(FP), R2
	MOVW	timeout+20(FP), R3
	MOV	$0, R4
	MOV	$SYS_epoll_pwait, R8
	SVC
	MOVW	R0, ret+24(FP)
	RETURN

// void runtime·closeonexec(int32 fd);
TEXT runtime·closeonexec(SB),NOSPLIT,$-8
	MOVW	fd+0(FP), R0  // fd
	MOV	$2, R1	// F_SETFD
	MOV	$1, R2	// FD_CLOEXEC
	MOV	$SYS_fcntl, R8
	SVC
	RETURN
