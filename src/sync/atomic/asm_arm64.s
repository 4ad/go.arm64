// Copyright 2014 The Go Authors.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "textflag.h"

TEXT ·SwapInt32(SB),NOSPLIT,$0-20
	B	·SwapUint32(SB)

TEXT ·SwapUint32(SB),NOSPLIT,$0-20
again:
	MOV	addr+0(FP), R0
	MOVW	new+8(FP), R1
	LDAXR	(R0), R2
	STLXRW	R1, (R0), R3
	CBNZ	R3, again
	MOVW	R2, old+16(FP)
	RETURN

TEXT ·SwapInt64(SB),NOSPLIT,$0-24
	B	·SwapUint32(SB)

TEXT ·SwapUint64(SB),NOSPLIT,$0-24
again:
	MOV	addr+0(FP), R0
	MOV	new+8(FP), R1
	LDAXR	(R0), R2
	STLXR	R1, (R0), R3
	CBNZ	R3, again
	MOV	R2, old+16(FP)
	RETURN

TEXT ·SwapUintptr(SB),NOSPLIT,$0-24
	B	·SwapUint64(SB)

TEXT ·CompareAndSwapInt32(SB),NOSPLIT,$0-17
	B	·CompareAndSwapUint32(SB)

TEXT ·CompareAndSwapUint32(SB),NOSPLIT,$0-17
	MOV	addr+0(FP), R0
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
	MOVB	R0, swapped+16(FP)
	RETURN

TEXT ·CompareAndSwapUintptr(SB),NOSPLIT,$0-25
	B	·CompareAndSwapUint64(SB)

TEXT ·CompareAndSwapInt64(SB),NOSPLIT,$0-25
	B	·CompareAndSwapUint64(SB)

TEXT ·CompareAndSwapUint64(SB),NOSPLIT,$0-25
	MOV	addr+0(FP), R0
	MOV	old+8(FP), R1
	MOV	new+16(FP), R2
again:
	LDAXR	(R0), R3
	CMP	R3, R1
	BNE	ok
	STLXR	R2, (R0), R3
	CBNZ	R3, again
ok:
	CSET	EQ, R0
	MOVB	R0, swapped+24(FP)
	RETURN

TEXT ·AddInt32(SB),NOSPLIT,$0-20
	B	·AddUint32(SB)

TEXT ·AddUint32(SB),NOSPLIT,$0-20
again:
	MOV	addr+0(FP), R0
	MOVW	delta+8(FP), R1
	LDAXRW	(R0), R2
	ADDW	R2, R1, R2
	STLXRW	R2, (R0), R3
	CBNZ	R3, again
	MOVW	R2, new+16(FP)
	RETURN

TEXT ·AddUintptr(SB),NOSPLIT,$0-24
	B	·AddUint64(SB)

TEXT ·AddInt64(SB),NOSPLIT,$0-24
	B	·AddUint64(SB)

TEXT ·AddUint64(SB),NOSPLIT,$0-24
again:
	MOV	addr+0(FP), R0
	MOV	delta+8(FP), R1
	LDAXR	(R0), R2
	ADD	R2, R1, R2
	STLXR	R2, (R0), R3
	CBNZ	R3, again
	MOV	R2, new+16(FP)
	RETURN
