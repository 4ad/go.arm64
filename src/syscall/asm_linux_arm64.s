// Copyright 2014 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "textflag.h"

// func Syscall(trap int64, a1, a2, a3 int64) (r1, r2, err int64);

TEXT	·Syscall(SB),NOSPLIT,$0-56
	BL	runtime·entersyscall(SB)
	MOV	a1+8(FP), R0
	MOV	a2+16(FP), R1
	MOV	a3+24(FP), R2
	MOV	$0, R3
	MOV	$0, R4
	MOV	$0, R5
	MOV	trap+0(FP), R8	// syscall entry
	SVC
	BVC	ok
	MOV	$-1, R4
	MOV	R4, r1+32(FP)	// r1
	MOV	ZR, r2+40(FP)	// r2
	MOV	R0, err+48(FP)	// errno
	BL	runtime·exitsyscall(SB)
	RETURN
ok:
	MOV	R0, r1+32(FP)	// r1
	MOV	R1, r2+40(FP)	// r2
	MOV	ZR, err+48(FP)	// errno
	BL	runtime·exitsyscall(SB)
	RETURN

TEXT ·Syscall6(SB),NOSPLIT,$0-80
	BL	runtime·entersyscall(SB)
	MOV	a1+8(FP), R0
	MOV	a2+16(FP), R1
	MOV	a3+24(FP), R2
	MOV	a4+32(FP), R3
	MOV	a5+40(FP), R4
	MOV	a6+48(FP), R5
	MOV	trap+0(FP), R8	// syscall entry
	SVC
	BVC	ok
	MOV	$-1, R4
	MOV	R4, r1+56(FP)	// r1
	MOV	ZR, r2+64(FP)	// r2
	MOV	R0, err+72(FP)	// errno
	BL	runtime·exitsyscall(SB)
	RETURN
ok:
	MOV	R0, r1+56(FP)	// r1
	MOV	R1, r2+64(FP)	// r2
	MOV	ZR, err+72(FP)	// errno
	BL	runtime·exitsyscall(SB)
	RETURN

TEXT ·RawSyscall(SB),NOSPLIT,$0-56
	MOV	a1+8(FP), R0
	MOV	a2+16(FP), R1
	MOV	a3+24(FP), R2
	MOV	$0, R3
	MOV	$0, R4
	MOV	$0, R5
	MOV	trap+0(FP), R8	// syscall entry
	SVC
	BVC	ok
	MOV	$-1, R4
	MOV	R4, r1+32(FP)	// r1
	MOV	ZR, r2+40(FP)	// r2
	MOV	ZR, err+48(FP)	// errno
	RETURN
ok:
	MOV	R0, r1+32(FP)	// r1
	MOV	R1, r2+40(FP)	// r2
	MOV	ZR, err+48(FP)	// errno
	RETURN

TEXT ·RawSyscall6(SB),NOSPLIT,$0-80
	MOV	a1+8(FP), R0
	MOV	a2+16(FP), R1
	MOV	a3+24(FP), R2
	MOV	a4+32(FP), R3
	MOV	a5+40(FP), R4
	MOV	a6+48(FP), R5
	MOV	trap+0(FP), R8	// syscall entry
	SVC
	BVC	ok
	MOV	$-1, R4
	MOV	R4, r1+56(FP)	// r1
	MOV	ZR, r2+64(FP)	// r2
	MOV	R0, err+72(FP)	// errno
	RETURN
ok:
	MOV	R0, r1+56(FP)	// r1
	MOV	R1, r2+64(FP)	// r2
	MOV	ZR, err+72(FP)	// errno
	RETURN
