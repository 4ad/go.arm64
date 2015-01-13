// Copyright 2014 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "textflag.h"

// void runtime·memclr(void*, uintptr)
TEXT runtime·memclr(SB),NOSPLIT,$0-16
	MOV	ptr+0(FP), R3
	MOV	n+8(FP), R4
	CMP	$0, R4
	BEQ	done
	ADD	R3, R4, R4
	MOV	$0, R5
	MOVBU	R5, (R3)1!
	CMP	R3, R4
	BNE	-2(PC)
done:
	RETURN
