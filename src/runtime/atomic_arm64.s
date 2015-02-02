// Copyright 2014 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "textflag.h"

// uint32 runtime·atomicload(uint32 volatile* addr)
TEXT ·atomicload(SB),NOSPLIT,$-8-12
	MOV	addr+0(FP), R0
	LDARW	(R0), R0
	MOVW	R0, val+8(FP)
	RETURN

// uint64 runtime·atomicload64(uint64 volatile* addr)
TEXT ·atomicload64(SB),NOSPLIT,$-8-16
	MOV	addr+0(FP), R0
	LDAR	(R0), R0
	MOV	R0, val+8(FP)
	RETURN

// void *runtime·atomicloadp(void *volatile *addr)
TEXT ·atomicloadp(SB),NOSPLIT,$-8-16
	MOV	addr+0(FP), R0
	LDAR	(R0), R0
	MOV	R0, val+8(FP)
	RETURN

TEXT runtime·atomicstorep1(SB), NOSPLIT, $0-16
	B	runtime·atomicstore64(SB)

TEXT runtime·atomicstore(SB), NOSPLIT, $0-12
	MOV	addr+0(FP), R0
	MOVW	val+8(FP), R1
	STLRW	R1, (R0)
	RETURN

TEXT runtime·atomicstore64(SB), NOSPLIT, $0-16
	MOV	addr+0(FP), R0
	MOV	val+8(FP), R1
	STLR	R1, (R0)
	RETURN

TEXT runtime·xchg(SB), NOSPLIT, $0-20
again:
	MOV	addr+0(FP), R0
	MOVW	new+8(FP), R1
	LDAXR	(R0), R2
	STLXRW	R1, (R0), R3
	CBNZ	R3, again
	MOVW	R2, old+16(FP)
	RETURN

TEXT runtime·xchg64(SB), NOSPLIT, $0-24
again:
	MOV	addr+0(FP), R0
	MOV	new+8(FP), R1
	LDAXR	(R0), R2
	STLXR	R1, (R0), R3
	CBNZ	R3, again
	MOV	R2, old+16(FP)
	RETURN

// bool runtime·cas64(uint64 *ptr, uint64 old, uint64 new)
// Atomically:
//      if(*val == *old){
//              *val = new;
//              return 1;
//      } else {
//              return 0;
//      }
TEXT runtime·cas64(SB), NOSPLIT, $0-25
	MOV	addr+0(FP), R0
	MOV	old+8(FP), R1
	MOV	new+16(FP), R2
again:
	LDAXR	(R0), R3
	CMP	R1, R3
	BNE	ok
	STLXR	R2, (R0), R3
	CBNZ	R3, again
ok:
	CSET	EQ, R0
	MOVB	R0, swapped+24(FP)
	RETURN

// uint32 xadd(uint32 volatile *ptr, int32 delta)
// Atomically:
//      *val += delta;
//      return *val;
TEXT runtime·xadd(SB), NOSPLIT, $0-20
again:
	MOV	addr+0(FP), R0
	MOVW	delta+8(FP), R1
	LDAXRW	(R0), R2
	ADDW	R2, R1, R2
	STLXRW	R2, (R0), R3
	CBNZ	R3, again
	MOVW	R2, new+16(FP)
	RETURN

TEXT runtime·xadd64(SB), NOSPLIT, $0-24
again:
	MOV	addr+0(FP), R0
	MOV	delta+8(FP), R1
	LDAXR	(R0), R2
	ADD	R2, R1, R2
	STLXR	R2, (R0), R3
	CBNZ	R3, again
	MOV	R2, new+16(FP)
	RETURN

TEXT runtime·xchguintptr(SB), NOSPLIT, $0-24
	BL	runtime·xchg64(SB)
