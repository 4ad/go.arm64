// Copyright 2012 The Go Authors.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "textflag.h"
#include "funcdata.h"

// makeFuncStub is the code half of the function returned by MakeFunc.
// See the comment on the declaration of makeFuncStub in makefunc.go
// for more details.
// No arg size here, runtime pulls arg map out of the func value.
TEXT ·makeFuncStub(SB),(NOSPLIT|WRAPPER),$16
	NO_LOCAL_POINTERS
	MOV	R11, 8(SP)
	MOV	$argframe+0(FP), R3
	MOV	R3, 16(SP)
	BL	·callReflect(SB)
	RETURN

// methodValueCall is the code half of the function returned by makeMethodValue.
// See the comment on the declaration of methodValueCall in makefunc.go
// for more details.
// No arg size here; runtime pulls arg map out of the func value.
TEXT ·methodValueCall(SB),(NOSPLIT|WRAPPER),$16
	NO_LOCAL_POINTERS
	MOV	R11, 8(SP)
	MOV	$argframe+0(FP), R3
	MOV	R3, 16(SP)
	BL	·callMethod(SB)
	RETURN
