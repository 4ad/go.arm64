// Copyright 2011 The Go Authors.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "textflag.h"

TEXT ·Abs(SB),NOSPLIT,$0-16
	MOV	x+0(FP), R3
	MOV 	$((1<<63)-1), R4
	AND	R4, R3
	MOV	R3, ret+8(FP)
	RETURN
