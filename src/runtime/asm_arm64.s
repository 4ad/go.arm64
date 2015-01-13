// Copyright 2015 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "go_asm.h"
#include "go_tls.h"
#include "funcdata.h"
#include "textflag.h"

TEXT runtime·rt0_go(SB),NOSPLIT,$0-0
	BL	main·main(SB)
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
	MOVB	(R1)1!, R4
	MOVB	(R2)1!, R5
	CMP	R4, R5
	BEQ	loop

	MOVW	$0, R0
	MOVB	R0, ret+24(FP)
done:
	RETURN

// eqstring tests whether two strings are equal.
// See runtime_test.go:eqstring_generic for
// equivalent Go code.
TEXT runtime·eqstring(SB),NOSPLIT,$-8-33
	MOV	s1len+8(FP), R0
	MOV	s2len+24(FP), R1
	CMP	R0, R1	// are the strings the same length ?
	BNE	noteq	// nope
	MOVW	s1str+0(FP), R2
	MOVW	s2str+16(FP), R3
	CMP	R2, R3	// same base ptr ?
	BEQ	eq
	ADD	R2, R0, R6
loop:
	CMP	R2, R6	// reached the end ?
	BEQ	eq	// strings are equal
	MOVBU	(R2)1!, R4
	MOVBU	(R3)1!, R5
	CMP	R4, R5	// bytes are the same ?
	BEQ	loop	// yup, otherwise fall through
noteq:
	MOV	$0, R7
	MOVB	R7, v+32(FP)
	RETURN
eq:
	MOV	$1, R7
	MOVB	R7, v+32(FP)
	RETURN

