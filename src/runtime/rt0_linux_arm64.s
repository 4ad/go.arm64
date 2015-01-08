#include "textflag.h"

TEXT _rt0_arm64_linux(SB),NOSPLIT,$0
	B _main<>(SB)

TEXT _main<>(SB),NOSPLIT,$-8
	MOV 0(SP), R3 // argc
	ADD $8, SP, R4 // argv
	B main(SB)

TEXT main(SB),NOSPLIT,$-8
	MOV	$runtime·rt0_go(SB), R0
	B	(R0)
