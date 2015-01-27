package main

import (
	"cmd/internal/asm"
	"cmd/internal/obj"
	"cmd/internal/obj/arm64"
)

var itab = []struct {
	name  string
	type_ uint16
	value uint32
}{

	{"SP", LSP, D_AUTO},

	{"SB", LSB, D_EXTERN},

	{"FP", LFP, D_PARAM},

	{"PC", LPC, D_BRANCH},

	{"R", LR, 0},

	{"R0", LREG, 0},

	{"R1", LREG, 1},

	{"R2", LREG, 2},

	{"R3", LREG, 3},

	{"R4", LREG, 4},

	{"R5", LREG, 5},

	{"R6", LREG, 6},

	{"R7", LREG, 7},

	{"R8", LREG, 8},

	{"R9", LREG, 9},

	{"R10", LREG, 10},

	{"R11", LREG, 11},

	{"R12", LREG, 12},

	{"R13", LREG, 13},

	{"R14", LREG, 14},

	{"R15", LREG, 15},

	{"R16", LREG, 16},

	{"R17", LREG, 17},

	{"R18", LREG, 18},

	{"R19", LREG, 19},

	{"R20", LREG, 20},

	{"R21", LREG, 21},

	{"R22", LREG, 22},

	{"R23", LREG, 23},

	{"R24", LREG, 24},

	{"R25", LREG, 25},

	{"R26", LREG, 26},

	{"R27", LREG, 27},

	{"R28", LREG, 28},

	{"g", LREG, 29}, // avoid unintentionally clobbering g using R29

	{"R30", LREG, 30},

	{"LR", LREG, 30},

	{"ZR", LREG, 31},

	{"RSP", LREG, 31},

	{"F", LF, 0},

	{"F0", LFREG, 0},

	{"F1", LFREG, 1},

	{"F2", LFREG, 2},

	{"F3", LFREG, 3},

	{"F4", LFREG, 4},

	{"F5", LFREG, 5},

	{"F6", LFREG, 6},

	{"F7", LFREG, 7},

	{"F8", LFREG, 8},

	{"F9", LFREG, 9},

	{"F10", LFREG, 10},

	{"F11", LFREG, 11},

	{"F12", LFREG, 12},

	{"F13", LFREG, 13},

	{"F14", LFREG, 14},

	{"F15", LFREG, 15},

	{"F16", LFREG, 16},

	{"F17", LFREG, 17},

	{"F18", LFREG, 18},

	{"F19", LFREG, 19},

	{"F20", LFREG, 20},

	{"F21", LFREG, 21},

	{"F22", LFREG, 22},

	{"F23", LFREG, 23},

	{"F24", LFREG, 24},

	{"F25", LFREG, 25},

	{"F26", LFREG, 26},

	{"F27", LFREG, 27},

	{"F28", LFREG, 28},

	{"F29", LFREG, 29},

	{"F30", LFREG, 30},

	{"F31", LFREG, 31},

	{"V", LV, 0},

	{"V0", LVREG, 0},

	{"V1", LVREG, 1},

	{"V2", LVREG, 2},

	{"V3", LVREG, 3},

	{"V4", LVREG, 4},

	{"V5", LVREG, 5},

	{"V6", LVREG, 6},

	{"V7", LVREG, 7},

	{"V8", LVREG, 8},

	{"V9", LVREG, 9},

	{"V10", LVREG, 10},

	{"V11", LVREG, 11},

	{"V12", LVREG, 12},

	{"V13", LVREG, 13},

	{"V14", LVREG, 14},

	{"V15", LVREG, 15},

	{"V16", LVREG, 16},

	{"V17", LVREG, 17},

	{"V18", LVREG, 18},

	{"V19", LVREG, 19},

	{"V20", LVREG, 20},

	{"V21", LVREG, 21},

	{"V22", LVREG, 22},

	{"V23", LVREG, 23},

	{"V24", LVREG, 24},

	{"V25", LVREG, 25},

	{"V26", LVREG, 26},

	{"V27", LVREG, 27},

	{"V28", LVREG, 28},

	{"V29", LVREG, 29},

	{"V30", LVREG, 30},

	{"V31", LVREG, 31},

	{"FPSR", LFCR, D_FPSR},

	{"FPCR", LFCR, D_FPCR},

	{"SPR", LSPR, D_SPR},

	{"NZCV", LSPREG, D_NZCV},

	{"ELR_EL1", LSPREG, D_ELR_EL1},

	{"ELR_EL2", LSPREG, D_ELR_EL2},

	//	{ "ELR_EL3",	LSPREG,	D_ELR_EL3 },
	//	{ "LR_EL0",	LSPREG,	D_LR_EL0 },

	{"DAIF", LSPREG, D_DAIF},

	{"CurrentEL", LSPREG, D_CurrentEL},

	{"SP_EL0", LSPREG, D_SP_EL0},

	//	{ "SP_EL1",	LSPREG,	D_SP_EL1 },
	//	{ "SP_EL2",	LSPREG,	D_SP_EL2 },

	{"SPSel", LSPREG, D_SPSel},

	//	{ "SPSR_abt",	LSPREG,	D_SPSR_abt,

	{"SPSR_EL1", LSPREG, D_SPSR_EL1},

	{"SPSR_EL2", LSPREG, D_SPSR_EL2},

	//	{ "SPSR_EL3",	LSPREG,	D_SPSR_EL3 },
	//	{ "SPSR_fiq",	LSPREG,	D_SPSR_fiq },
	//	{ "SPSR_ieq",	LSPREG,	D_SPSR_ieq },
	//	{ "SPSR_und",	LSPREG,	D_SPSR_und },

	{"DAIFSet", LSPREG, D_DAIFSet},

	{"DAIFClr", LSPREG, D_DAIFClr},

	{"EQ", LCOND, 0},

	{"NE", LCOND, 1},

	{"CS", LCOND, 2},

	{"HS", LCOND, 2},

	{"CC", LCOND, 3},

	{"LO", LCOND, 3},

	{"MI", LCOND, 4},

	{"PL", LCOND, 5},

	{"VS", LCOND, 6},

	{"VC", LCOND, 7},

	{"HI", LCOND, 8},

	{"LS", LCOND, 9},

	{"GE", LCOND, 10},

	{"LT", LCOND, 11},

	{"GT", LCOND, 12},

	{"LE", LCOND, 13},

	{"AL", LCOND, 14},

	{".UXTB", LEXT, 0},

	{".UXTH", LEXT, 1},

	{".UXTW", LEXT, 2},

	{".UXTX", LEXT, 3},

	{".SXTB", LEXT, 4},

	{".SXTH", LEXT, 5},

	{".SXTW", LEXT, 6},

	{".SXTX", LEXT, 7},

	{".UB", LEXT, 0},

	{".UH", LEXT, 1},

	{".UW", LEXT, 2},

	{".UX", LEXT, 3},

	{".SB", LEXT, 4},

	{".SH", LEXT, 5},

	{".SW", LEXT, 6},

	{".SX", LEXT, 7},

	{"@", LAT, 0},

	{"ADC", LTYPE1, AADC},

	{"ADCS", LTYPE1, AADCS},

	{"ADCSW", LTYPE1, AADCSW},

	{"ADCW", LTYPE1, AADCW},

	{"ADD", LTYPE1, AADD},

	{"ADDS", LTYPE1, AADDS},

	{"ADDSW", LTYPE1, AADDSW},

	{"ADDW", LTYPE1, AADDW},

	{"ADR", LTYPEV, AADR},

	{"ADRP", LTYPEV, AADRP},

	{"AND", LTYPE1, AAND},

	{"ANDS", LTYPE1, AANDS},

	{"ANDSW", LTYPE1, AANDSW},

	{"ANDW", LTYPE1, AANDW},

	{"ASR", LTYPE1, AASR},

	{"ASRW", LTYPE1, AASRW},

	{"AT", LTYPEN, AAT},

	{"BFI", LTYPEY, ABFI},

	{"BFIW", LTYPEY, ABFIW},

	{"BFM", LTYPEY, ABFM},

	{"BFMW", LTYPEY, ABFMW},

	{"BFXIL", LTYPEY, ABFXIL},

	{"BFXILW", LTYPEY, ABFXILW},

	{"BIC", LTYPE1, ABIC},

	{"BICS", LTYPE1, ABICS},

	{"BICSW", LTYPE1, ABICSW},

	{"BICW", LTYPE1, ABICW},

	{"BRK", LTYPE6, ABRK},

	{"CBNZ", LTYPE8, ACBNZ},

	{"CBNZW", LTYPE8, ACBNZW},

	{"CBZ", LTYPE8, ACBZ},

	{"CBZW", LTYPE8, ACBZW},

	{"CCMN", LTYPEU, ACCMN},

	{"CCMNW", LTYPEU, ACCMNW},

	{"CCMP", LTYPEU, ACCMP},

	{"CCMPW", LTYPEU, ACCMPW},

	{"CINC", LTYPES, ACINC},

	{"CINCW", LTYPES, ACINCW},

	{"CINV", LTYPES, ACINV},

	{"CINVW", LTYPES, ACINVW},

	{"CLREX", LTYPE6, ACLREX},

	{"CLS", LTYPE2, ACLS},

	{"CLSW", LTYPE2, ACLSW},

	{"CLZ", LTYPE2, ACLZ},

	{"CLZW", LTYPE2, ACLZW},

	{"CMN", LTYPE7, ACMN},

	{"CMNW", LTYPE7, ACMNW},

	{"CMP", LTYPE7, ACMP},

	{"CMPW", LTYPE7, ACMPW},

	{"CNEG", LTYPES, ACNEG},

	{"CNEGW", LTYPES, ACNEGW},

	{"CRC32B", LTYPE1, ACRC32B},

	{"CRC32CB", LTYPE1, ACRC32CB},

	{"CRC32CH", LTYPE1, ACRC32CH},

	{"CRC32CW", LTYPE1, ACRC32CW},

	{"CRC32CX", LTYPE1, ACRC32CX},

	{"CRC32H", LTYPE1, ACRC32H},

	{"CRC32W", LTYPE1, ACRC32W},

	{"CRC32X", LTYPE1, ACRC32X},

	{"CSEL", LTYPES, ACSEL},

	{"CSELW", LTYPES, ACSELW},

	{"CSET", LTYPER, ACSET},

	{"CSETM", LTYPER, ACSETM},

	{"CSETMW", LTYPER, ACSETMW},

	{"CSETW", LTYPER, ACSETW},

	{"CSINC", LTYPES, ACSINC},

	{"CSINCW", LTYPES, ACSINCW},

	{"CSINV", LTYPES, ACSINV},

	{"CSINVW", LTYPES, ACSINVW},

	{"CSNEG", LTYPES, ACSNEG},

	{"CSNEGW", LTYPES, ACSNEGW},

	{"DC", LTYPEN, ADC},

	{"DCPS1", LTYPE6, ADCPS1},

	{"DCPS2", LTYPE6, ADCPS2},

	{"DCPS3", LTYPE6, ADCPS3},

	{"DMB", LDMB, ADMB},

	{"DRPS", LTYPE6, ADRPS},

	{"DSB", LDMB, ADSB},

	{"EON", LTYPE1, AEON},

	{"EONW", LTYPE1, AEONW},

	{"EOR", LTYPE1, AEOR},

	{"EORW", LTYPE1, AEORW},

	{"ERET", LTYPE0, AERET},

	{"EXTR", LTYPEP, AEXTR},

	{"EXTRW", LTYPEP, AEXTRW},

	{"HINT", LDMB, AHINT},

	{"HLT", LTYPE6, AHLT},

	{"HVC", LTYPE6, AHVC},

	{"IC", LTYPEN, AIC},

	{"ISB", LDMB, AISB},

	{"LSL", LTYPE1, ALSL},

	{"LSLW", LTYPE1, ALSLW},

	{"LSR", LTYPE1, ALSR},

	{"LSRW", LTYPE1, ALSRW},

	{"MADD", LTYPEM, AMADD},

	{"MADDW", LTYPEM, AMADDW},

	{"MNEG", LTYPE1, AMNEG},

	{"MNEGW", LTYPE1, AMNEGW},

	{"MRS", LTYPE3, AMRS},

	{"MSR", LTYPE3, AMSR},

	{"MSUB", LTYPEM, AMSUB},

	{"MSUBW", LTYPEM, AMSUBW},

	{"MUL", LTYPE1, AMUL},

	{"MULW", LTYPE1, AMULW},

	{"MVN", LTYPE1, AMVN},

	{"MVNW", LTYPE1, AMVNW},

	{"NEG", LTYPE1, ANEG},

	{"NEGS", LTYPE1, ANEGS},

	{"NEGSW", LTYPE1, ANEGSW},

	{"NEGW", LTYPE1, ANEGW},

	{"NGC", LTYPE2, ANGC},

	{"NGCS", LTYPE2, ANGCS},

	{"NGCSW", LTYPE2, ANGCSW},

	{"NGCW", LTYPE2, ANGCW},

	{"ORN", LTYPE1, AORN},

	{"ORNW", LTYPE1, AORNW},

	{"ORR", LTYPE1, AORR},

	{"ORRW", LTYPE1, AORRW},

	{"PRFM", LTYPE1, APRFM},

	{"PRFUM", LTYPE1, APRFUM},

	{"RBIT", LTYPE2, ARBIT},

	{"RBITW", LTYPE2, ARBITW},

	{"REM", LTYPE1, AREM},

	{"REMW", LTYPE1, AREMW},

	{"RET", LTYPEA, ARETURN},

	{"REV", LTYPE2, AREV},

	{"REV16", LTYPE2, AREV16},

	{"REV16W", LTYPE2, AREV16W},

	{"REV32", LTYPE2, AREV32},

	{"REVW", LTYPE2, AREVW},

	{"ROR", LTYPE1, AROR},

	{"RORW", LTYPE1, ARORW},

	{"SBC", LTYPE1, ASBC},

	{"SBCS", LTYPE1, ASBCS},

	{"SBCSW", LTYPE1, ASBCSW},

	{"SBCW", LTYPE1, ASBCW},

	{"SBFIZ", LTYPEY, ASBFIZ},

	{"SBFIZW", LTYPEY, ASBFIZW},

	{"SBFM", LTYPEY, ASBFM},

	{"SBFMW", LTYPEY, ASBFMW},

	{"SBFX", LTYPEY, ASBFX},

	{"SBFXW", LTYPEY, ASBFXW},

	{"SDIV", LTYPE1, ASDIV},

	{"SDIVW", LTYPE1, ASDIVW},

	{"SEV", LTYPE0, ASEV},

	{"SEVL", LTYPE0, ASEVL},

	{"SMADDL", LTYPEM, ASMADDL},

	{"SMC", LTYPE6, ASMC},

	{"SMNEGL", LTYPE1, ASMNEGL},

	{"SMSUBL", LTYPEM, ASMSUBL},

	{"SMULH", LTYPE1, ASMULH},

	{"SMULL", LTYPE1, ASMULL},

	{"STLR", LTYPE3, ASTLR},

	{"STLRB", LTYPE3, ASTLRB},

	{"STLRH", LTYPE3, ASTLRH},

	{"STLRW", LTYPE3, ASTLRW},

	{"STLXP", LSTXR, ASTLXP},

	{"STLXR", LSTXR, ASTLXR},

	{"STLXRB", LSTXR, ASTLXRB},

	{"STLXRH", LSTXR, ASTLXRH},

	{"STLXRW", LSTXR, ASTLXRW},

	{"STXR", LSTXR, ASTXR},

	{"STXRB", LSTXR, ASTXRB},

	{"STXRH", LSTXR, ASTXRH},

	{"STXP", LSTXR, ASTXP},

	{"STXPW", LSTXR, ASTXPW},

	{"STXRW", LSTXR, ASTXRW},

	{"SUB", LTYPE1, ASUB},

	{"SUBS", LTYPE1, ASUBS},

	{"SUBSW", LTYPE1, ASUBSW},

	{"SUBW", LTYPE1, ASUBW},

	{"SVC", LTYPE6, ASVC},

	{"SXTB", LTYPE2, ASXTB},

	{"SXTBW", LTYPE2, ASXTBW},

	{"SXTH", LTYPE2, ASXTH},

	{"SXTHW", LTYPE2, ASXTHW},

	{"SXTW", LTYPE2, ASXTW},

	{"SYS", LTYPEN, ASYS},

	{"SYSL", LTYPEO, ASYSL},

	{"TBNZ", LTYPET, ATBNZ},

	{"TBZ", LTYPET, ATBZ},

	{"TLBI", LTYPEN, ATLBI},

	{"TST", LTYPE7, ATST},

	{"TSTW", LTYPE7, ATSTW},

	{"UBFIZ", LTYPEY, AUBFIZ},

	{"UBFIZW", LTYPEY, AUBFIZW},

	{"UBFM", LTYPEY, AUBFM},

	{"UBFMW", LTYPEY, AUBFMW},

	{"UBFX", LTYPEY, AUBFX},

	{"UBFXW", LTYPEY, AUBFXW},

	{"UDIV", LTYPE1, AUDIV},

	{"UDIVW", LTYPE1, AUDIVW},

	{"UMADDL", LTYPEM, AUMADDL},

	{"UMNEGL", LTYPE1, AUMNEGL},

	{"UMSUBL", LTYPEM, AUMSUBL},

	{"UMULH", LTYPE1, AUMULH},

	{"UMULL", LTYPE1, AUMULL},

	{"UREM", LTYPE1, AUREM},

	{"UREMW", LTYPE1, AUREMW},

	{"UXTB", LTYPE2, AUXTB},

	{"UXTH", LTYPE2, AUXTH},

	{"UXTBW", LTYPE2, AUXTBW},

	{"UXTHW", LTYPE2, AUXTHW},

	{"UXTW", LTYPE2, AUXTW},

	{"WFE", LTYPE0, AWFE},

	{"WFI", LTYPE0, AWFI},

	{"YIELD", LTYPE0, AYIELD},

	{"LDXR", LTYPE3, ALDXR},

	{"LDXRB", LTYPE3, ALDXRB},

	{"LDXRH", LTYPE3, ALDXRH},

	{"LDXRW", LTYPE3, ALDXRW},

	{"LDAR", LTYPE3, ALDAR},

	{"LDARB", LTYPE3, ALDARB},

	{"LDARH", LTYPE3, ALDARH},

	{"LDARW", LTYPE3, ALDARW},

	{"LDXP", LTYPE3, ALDXP},

	{"LDXPW", LTYPE3, ALDXPW},

	{"LDAXP", LTYPE3, ALDAXP},

	{"LDAXPW", LTYPE3, ALDAXPW},

	{"LDAXR", LTYPE3, ALDAXR},

	{"LDAXRB", LTYPE3, ALDAXRB},

	{"LDAXRH", LTYPE3, ALDAXRH},

	{"LDAXRW", LTYPE3, ALDAXRW},

	{"MOVK", LMOVK, AMOVK},

	{"MOVKW", LMOVK, AMOVKW},

	{"MOVN", LMOVK, AMOVN},

	{"MOVNW", LMOVK, AMOVNW},

	{"MOVZ", LMOVK, AMOVZ},

	{"MOVZW", LMOVK, AMOVZW},

	{"MOVB", LTYPE3, AMOVB},

	{"MOVBU", LTYPE3, AMOVBU},

	{"MOVH", LTYPE3, AMOVH},

	{"MOVHU", LTYPE3, AMOVHU},

	{"MOVW", LTYPE3, AMOVW},

	{"MOVWU", LTYPE3, AMOVWU},

	{"MOV", LTYPE3, AMOV},

	{"MOVP", LTYPEJ, AMOVP},

	{"MOVPD", LTYPEJ, AMOVPD},

	{"MOVPQ", LTYPEJ, AMOVPQ},

	{"MOVPS", LTYPEJ, AMOVPS},

	{"MOVPSW", LTYPEJ, AMOVPSW},

	{"MOVPW", LTYPEJ, AMOVPW},

	{"MOVNP", LTYPEJ, AMOVNP},

	{"MOVNPW", LTYPEJ, AMOVNPW},

	{"FMOVD", LTYPE3, AFMOVD},

	{"FMOVS", LTYPE3, AFMOVS},

	{"SCVTFD", LTYPE3, ASCVTFD},

	{"SCVTFS", LTYPE3, ASCVTFS},

	{"SCVTFWD", LTYPE3, ASCVTFWD},

	{"SCVTFWS", LTYPE3, ASCVTFWS},

	{"UCVTFD", LTYPE3, AUCVTFD},

	{"UCVTFS", LTYPE3, AUCVTFS},

	{"UCVTFWD", LTYPE3, AUCVTFWD},

	{"UCVTFWS", LTYPE3, AUCVTFWS},

	{"FCVTSD", LTYPE3, AFCVTSD},

	{"FCVTDS", LTYPE3, AFCVTDS},

	{"FCVTZSD", LTYPE3, AFCVTZSD},

	{"FCVTZSDW", LTYPE3, AFCVTZSDW},

	{"FCVTZSS", LTYPE3, AFCVTZSS},

	{"FCVTZSSW", LTYPE3, AFCVTZSSW},

	{"FCVTZUD", LTYPE3, AFCVTZUD},

	{"FCVTZUDW", LTYPE3, AFCVTZUDW},

	{"FCVTZUS", LTYPE3, AFCVTZUS},

	{"FCVTZUSW", LTYPE3, AFCVTZUSW},

	{"FCMPS", LTYPEL, AFCMPS},

	{"FCMPD", LTYPEL, AFCMPD},

	{"FCMPES", LTYPEL, AFCMPES},

	{"FCMPED", LTYPEL, AFCMPED},

	{"FCCMPS", LTYPEF, AFCCMPS},

	{"FCCMPD", LTYPEF, AFCCMPD},

	{"FCCMPES", LTYPEF, AFCCMPES},

	{"FCCMPED", LTYPEF, AFCCMPED},

	{"FADDS", LTYPEK, AFADDS},

	{"FADDD", LTYPEK, AFADDD},

	{"FSUBS", LTYPEK, AFSUBS},

	{"FSUBD", LTYPEK, AFSUBD},

	{"FMULS", LTYPEK, AFMULS},

	{"FMULD", LTYPEK, AFMULD},

	{"FDIVS", LTYPEK, AFDIVS},

	{"FDIVD", LTYPEK, AFDIVD},

	{"FCSELS", LFCSEL, AFCSELS},

	{"FCSELD", LFCSEL, AFCSELD},

	{"FMAXS", LTYPEK, AFMAXS},

	{"FMINS", LTYPEK, AFMINS},

	{"FMAXD", LTYPEK, AFMAXD},

	{"FMIND", LTYPEK, AFMIND},

	{"FMAXNMS", LTYPEK, AFMAXNMS},

	{"FMAXNMD", LTYPEK, AFMAXNMD},

	{"FMINNMS", LTYPEK, AFMINNMS},

	{"FMINNMD", LTYPEK, AFMINNMD},

	{"FNMULS", LTYPEK, AFNMULS},

	{"FNMULD", LTYPEK, AFNMULD},

	{"FRINTNS", LTYPE3, AFRINTNS},

	{"FRINTND", LTYPE3, AFRINTND},

	{"FRINTPS", LTYPE3, AFRINTPS},

	{"FRINTPD", LTYPE3, AFRINTPD},

	{"FRINTMS", LTYPE3, AFRINTMS},

	{"FRINTMD", LTYPE3, AFRINTMD},

	{"FRINTZS", LTYPE3, AFRINTZS},

	{"FRINTZD", LTYPE3, AFRINTZD},

	{"FRINTAS", LTYPE3, AFRINTAS},

	{"FRINTAD", LTYPE3, AFRINTAD},

	{"FRINTXS", LTYPE3, AFRINTXS},

	{"FRINTXD", LTYPE3, AFRINTXD},

	{"FRINTIS", LTYPE3, AFRINTIS},

	{"FRINTID", LTYPE3, AFRINTID},

	{"FMADDS", LTYPEM, AFMADDS},

	{"FMADDD", LTYPEM, AFMADDD},

	{"FMSUBS", LTYPEM, AFMSUBS},

	{"FMSUBD", LTYPEM, AFMSUBD},

	{"FNMADDS", LTYPEM, AFNMADDS},

	{"FNMADDD", LTYPEM, AFNMADDD},

	{"FNMSUBS", LTYPEM, AFNMSUBS},

	{"FNMSUBD", LTYPEM, AFNMSUBD},

	{"FABSS", LTYPE3, AFABSS},

	{"FABSD", LTYPE3, AFABSD},

	{"FNEGS", LTYPE3, AFNEGS},

	{"FNEGD", LTYPE3, AFNEGD},

	{"FSQRTS", LTYPE3, AFSQRTS},

	{"FSQRTD", LTYPE3, AFSQRTD},

	{"FCVTDH", LTYPE3, AFCVTDH},

	{"FCVTHS", LTYPE3, AFCVTHS},

	{"FCVTHD", LTYPE3, AFCVTHD},

	{"FCVTSH", LTYPE3, AFCVTSH},

	{"AESD", LTYPEW, AAESD},

	{"AESE", LTYPEW, AAESE},

	{"AESIMC", LTYPEW, AAESIMC},

	{"AESMC", LTYPEW, AAESMC},

	{"SHA1C", LTYPEW, ASHA1C},

	{"SHA1H", LTYPEW, ASHA1H},

	{"SHA1M", LTYPEW, ASHA1M},

	{"SHA1P", LTYPEW, ASHA1P},

	{"SHA1SU0", LTYPEW, ASHA1SU0},

	{"SHA1SU1", LTYPEW, ASHA1SU1},

	{"SHA256H", LTYPEW, ASHA256H},

	{"SHA256H2", LTYPEW, ASHA256H2},

	{"SHA256SU0", LTYPEW, ASHA256SU0},

	{"SHA256SU1", LTYPEW, ASHA256SU1},

	{"B", LTYPE4, AB},

	{"BL", LTYPE4, ABL},

	{"BEQ", LTYPE5, ABEQ},

	{"BNE", LTYPE5, ABNE},

	{"BCS", LTYPE5, ABCS},

	{"BHS", LTYPE5, ABHS},

	{"BCC", LTYPE5, ABCC},

	{"BLO", LTYPE5, ABLO},

	{"BMI", LTYPE5, ABMI},

	{"BPL", LTYPE5, ABPL},

	{"BVS", LTYPE5, ABVS},

	{"BVC", LTYPE5, ABVC},

	{"BHI", LTYPE5, ABHI},

	{"BLS", LTYPE5, ABLS},

	{"BGE", LTYPE5, ABGE},

	{"BLT", LTYPE5, ABLT},

	{"BGT", LTYPE5, ABGT},

	{"BLE", LTYPE5, ABLE},

	{"BCASE", LTYPE5, ABCASE},

	{"TEXT", LTYPEB, ATEXT},

	{"GLOBL", LTYPEB, AGLOBL},

	{"DATA", LTYPEC, ADATA},

	{"CASE", LTYPED, ACASE},

	{"END", LTYPEE, AEND},

	{"WORD", LTYPEH, AWORD},

	{"DWORD", LTYPEH, ADWORD},

	{"SCHED", LSCHED, 0},

	{"NOSCHED", LSCHED, 0x80},

	{"NOP", LTYPEQ, ANOP},

	{"UNDEF", LTYPEQ, AUNDEF},

	{"RETURN", LTYPEA, ARETURN},

	{"PCDATA", LPCDAT, APCDATA},

	{"FUNCDATA", LFUNCDAT, AFUNCDATA},

	{0, 0, 0},
}

func cinit() {
	var s *Sym
	var i int

	nullgen.Type = D_NONE
	nullgen.Name = D_NONE
	nullgen.Reg = NREG
	nullgen.Scale = NREG // replaced Gen.xreg with Prog.scale

	nerrors = 0

	iostack = nil
	iofree = nil
	peekc = IGN
	nhunk = 0
	for i = 0; i < NHASH; i++ {
		hash[i] = nil
	}
	for i = 0; itab[i].name != ""; i++ {
		s = slookup(itab[i].name)
		if s.value != 0 {
			yyerror("internal: duplicate %s", s.name)
		}
		s.type_ = itab[i].type_
		s.value = int32(itab[i].value)
	}
}

func cclean() {
	outcode(AEND, &nullgen, NREG, &nullgen)
}

var lastpc *obj.Prog

func outcode(a int, g1 *obj.Addr, reg int, g2 *obj.Addr) {
	var p *obj.Prog
	var pl *obj.Plist

	if pass == 1 {
		goto out
	}

	if g1.Scale != NREG {
		if reg != NREG || g2.Scale != NREG {
			yyerror("bad addressing modes")
		}
		reg = int(g1.Scale)
	} else if g2.Scale != NREG {
		if reg != NREG {
			yyerror("bad addressing modes")
		}
		reg = int(g2.Scale)
	}

	p = ctxt.Arch.Prg()
	p.As = int16(a)
	p.Lineno = lineno
	if nosched != 0 {
		p.Mark |= NOSCHED
	}
	p.From = *g1
	p.Reg = uint8(reg)
	p.To = *g2
	p.Pc = int64(pc)

	if lastpc == nil {
		pl = obj.Linknewplist(ctxt)
		pl.Firstpc = p
	} else {

		lastpc.Link = p
	}
	lastpc = p

out:
	if a != AGLOBL && a != ADATA {
		pc++
	}
}

func outgcode(a int, g1 *obj.Addr, reg int, g2 *obj.Addr, g3 *obj.Addr) {
	var p *obj.Prog
	var pl *obj.Plist

	if pass == 1 {
		goto out
	}

	p = ctxt.Arch.Prg()
	p.As = int16(a)
	p.Lineno = lineno
	if nosched != 0 {
		p.Mark |= NOSCHED
	}
	p.From = *g1
	p.Reg = uint8(reg)
	p.To = *g2
	p.From3 = *g3
	p.Pc = int64(pc)
	fmt.Printf("oc: %v\n", p)

	if lastpc == nil {
		pl = obj.Linknewplist(ctxt)
		pl.Firstpc = p
	} else {

		lastpc.Link = p
	}
	lastpc = p

out:
	if a != AGLOBL && a != ADATA {
		pc++
	}
}

func outtcode(a int, from *obj.Addr, to *obj.Addr, to3 *obj.Addr) {
	var p *obj.Prog
	var pl *obj.Plist

	if pass == 1 {
		goto out
	}

	p = ctxt.Arch.Prg()
	p.As = int16(a)
	p.Lineno = lineno
	if nosched != 0 {
		p.Mark |= NOSCHED
	}
	p.From = *from
	p.To = *to
	p.To3 = *to3
	p.Pc = int64(pc)

	if lastpc == nil {
		pl = obj.Linknewplist(ctxt)
		pl.Firstpc = p
	} else {

		lastpc.Link = p
	}
	lastpc = p

out:
	if a != AGLOBL && a != ADATA {
		pc++
	}
}
