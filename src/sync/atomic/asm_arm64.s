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
