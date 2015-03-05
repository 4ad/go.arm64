// Copyright 2015 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "textflag.h"

TEXT _rt0_arm64_linux(SB),NOSPLIT,$-8
	// reference the dummy symbols so that they end up in the binary.
	MOVD	$dummydata(SB), R11
	MOVD	$dummyrodata(SB), R11
	MOVD	$dummynoptrdata(SB), R11
	MOVD	$dummybss(SB), R11
	MOVD	$dummynoptrbss(SB), R11
	MOVD	0(RSP), R0	// argc
	ADD	$8, RSP, R1	// argv
	BL	main(SB)

TEXT main(SB),NOSPLIT,$-8
	MOVD	$runtime·rt0_go(SB), R2
	BL	(R2)
exit:
	MOVD $0, R0
	MOVD	$94, R8	// sys_exit
	SVC
	B	exit

// Linker has a bug, and we need non-zero length symbols in
// these sections.

// .data
DATA dummydata(SB)/4, $2
GLOBL dummydata(SB), 0, $4

// .rodata
DATA dummyrodata(SB)/4, $1
GLOBL dummyrodata(SB), RODATA, $4

// .noptrdata
DATA dummynoptrdata(SB)/4, $3
GLOBL dummynoptrdata(SB), NOPTR, $4

// .bss
GLOBL dummybss(SB), 0, $4

// .noptrbss
GLOBL dummynoptrbss(SB), NOPTR, $4
