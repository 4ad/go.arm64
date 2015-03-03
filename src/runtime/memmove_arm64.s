// Copyright 2014 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "textflag.h"

// void runtime·memmove(void*, void*, uintptr)
TEXT runtime·memmove(SB), NOSPLIT, $-8-24
	MOV	to+0(FP), R3
	MOV	from+8(FP), R4
	MOV	n+16(FP), R5
	CMP	$0, R5
	BNE	check
	RETURN

check:
	CMP	R3, R4
	BGT	backward

	ADD	R3, R5
loop:
	MOVBU	(R4)1!, R6
	MOVBU	R6, (R3)1!
	CMP	R3, R5
	BNE	loop
	RETURN

backward:
	ADD	R5, R4
	ADD	R3, R5
loop1:
	MOVBU	-1(R4)!, R6
	MOVBU	R6, -1(R5)!
	CMP	R3, R5
	BNE	loop1
	RETURN
