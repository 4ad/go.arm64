//go:generate go tool yacc a.y

package main

import (
	"cmd/internal/asm"
	"cmd/internal/obj"
	"cmd/internal/obj/arm64"
)

var (
	yyerror  = asm.Yyerror
	nullgen  obj.Addr
	stmtline int32
)

func main() {
	cinit()

	asm.LSCONST = LSCONST
	asm.LCONST = LCONST
	asm.LFCONST = LFCONST
	asm.LNAME = LNAME
	asm.LVAR = LVAR
	asm.LLAB = LLAB

	asm.Lexinit = lexinit
	asm.Cclean = cclean
	asm.Yyparse = yyparse

	asm.Thechar = '7'
	asm.Thestring = "arm64"
	asm.Thelinkarch = &arm64.Linkarm64

	asm.Main()
}

type yy struct{}

func (yy) Lex(v *yySymType) int {
	var av asm.Yylval
	tok := asm.Yylex(&av)
	v.sym = av.Sym
	v.lval = av.Lval
	v.sval = av.Sval
	v.dval = av.Dval
	return tok
}

func (yy) Error(msg string) {
	asm.Yyerror("%s", msg)
}

func yyparse() {
	nosched = 0
	yyParse(yy{})
}

var lexinit = []asm.Lextab{
	{"SP", LSP, arm64.NAME_AUTO},
	{"SB", LSB, arm64.NAME_EXTERN},
	{"FP", LFP, arm64.NAME_PARAM},
	{"PC", LPC, arm64.TYPE_BRANCH},
	{"R", LR, 0},
	{"R0", LREG, REG_R0},
	{"R1", LREG, REG_R1},
	{"R2", LREG, REG_R2},
	{"R3", LREG, REG_R3},
	{"R4", LREG, REG_R4},
	{"R5", LREG, REG_R5},
	{"R6", LREG, REG_R6},
	{"R7", LREG, REG_R7},
	{"R8", LREG, REG_R8},
	{"R9", LREG, REG_R9},
	{"R10", LREG, REG_R10},
	{"R11", LREG, REG_R11},
	{"R12", LREG, REG_R12},
	{"R13", LREG, REG_R13},
	{"R14", LREG, REG_R14},
	{"R15", LREG, REG_R15},
	{"R16", LREG, REG_R16},
	{"R17", LREG, REG_R17},
	{"R18", LREG, REG_R18},
	{"R19", LREG, REG_R19},
	{"R20", LREG, REG_R20},
	{"R21", LREG, REG_R21},
	{"R22", LREG, REG_R22},
	{"R23", LREG, REG_R23},
	{"R24", LREG, REG_R24},
	{"R25", LREG, REG_R25},
	{"R26", LREG, REG_R26},
	{"R27", LREG, REG_R27},
	{"g", LREG, REG_R28}, // avoid unintentionally clobbering g using R28
	{"RFP", LREG, REG_R29}, // avoid unintentionally clobbering the frame pointer using R29
	{"R30", LREG, REG_R30},
	{"LR", LREG, REG_R30},
	{"ZR", LREG, REG_R31},
	{"RSP", LREG, REG_R31},
	{"F", LF, 0},
	{"F0", LFREG, REG_F0},
	{"F1", LFREG, REG_F1},
	{"F2", LFREG, REG_F2},
	{"F3", LFREG, REG_F3},
	{"F4", LFREG, REG_F4},
	{"F5", LFREG, REG_F5},
	{"F6", LFREG, REG_F6},
	{"F7", LFREG, REG_F7},
	{"F8", LFREG, REG_F8},
	{"F9", LFREG, REG_F9},
	{"F10", LFREG, REG_F10},
	{"F11", LFREG, REG_F11},
	{"F12", LFREG, REG_F12},
	{"F13", LFREG, REG_F13},
	{"F14", LFREG, REG_F14},
	{"F15", LFREG, REG_F15},
	{"F16", LFREG, REG_F16},
	{"F17", LFREG, REG_F17},
	{"F18", LFREG, REG_F18},
	{"F19", LFREG, REG_F19},
	{"F20", LFREG, REG_F20},
	{"F21", LFREG, REG_F21},
	{"F22", LFREG, REG_F22},
	{"F23", LFREG, REG_F23},
	{"F24", LFREG, REG_F24},
	{"F25", LFREG, REG_F25},
	{"F26", LFREG, REG_F26},
	{"F27", LFREG, REG_F27},
	{"F28", LFREG, REG_F28},
	{"F29", LFREG, REG_F29},
	{"F30", LFREG, REG_F30},
	{"F31", LFREG, REG_F31},
	{"V", LV, 0},
	{"V0", LVREG, REG_V0},
	{"V1", LVREG, REG_V1},
	{"V2", LVREG, REG_V2},
	{"V3", LVREG, REG_V3},
	{"V4", LVREG, REG_V4},
	{"V5", LVREG, REG_V5},
	{"V6", LVREG, REG_V6},
	{"V7", LVREG, REG_V7},
	{"V8", LVREG, REG_V8},
	{"V9", LVREG, REG_V9},
	{"V10", LVREG, REG_V10},
	{"V11", LVREG, REG_V11},
	{"V12", LVREG, REG_V12},
	{"V13", LVREG, REG_V13},
	{"V14", LVREG, REG_V14},
	{"V15", LVREG, REG_V15},
	{"V16", LVREG, REG_V16},
	{"V17", LVREG, REG_V17},
	{"V18", LVREG, REG_V18},
	{"V19", LVREG, REG_V19},
	{"V20", LVREG, REG_V20},
	{"V21", LVREG, REG_V21},
	{"V22", LVREG, REG_V22},
	{"V23", LVREG, REG_V23},
	{"V24", LVREG, REG_V24},
	{"V25", LVREG, REG_V25},
	{"V26", LVREG, REG_V26},
	{"V27", LVREG, REG_V27},
	{"V28", LVREG, REG_V28},
	{"V29", LVREG, REG_V29},
	{"V30", LVREG, REG_V30},
	{"V31", LVREG, REG_V31},
	{"FPSR", LFCR, arm64.REG_FPSR},
	{"FPCR", LFCR, arm64.REG_FPCR},
	{"SPR", LSPR, arm64.REG_SPR},
	{"NZCV", LSPREG, arm64.REG_NZCV},
	{"ELR_EL1", LSPREG, arm64.REG_ELR_EL1},
	{"ELR_EL2", LSPREG, arm64.REG_ELR_EL2},
	//	{ "ELR_EL3",	LSPREG,	arm64.REG_ELR_EL3 },
	//	{ "LR_EL0",	LSPREG,	arm64.REG_LR_EL0 },
	{"DAIF", LSPREG, arm64.REG_DAIF},
	{"CurrentEL", LSPREG, arm64.REG_CurrentEL},
	{"SP_EL0", LSPREG, arm64.REG_SP_EL0},
	//	{ "SP_EL1",	LSPREG,	arm64.REG_SP_EL1 },
	//	{ "SP_EL2",	LSPREG,	arm64.REG_SP_EL2 },
	{"SPSel", LSPREG, arm64.REG_SPSel},
	//	{ "SPSR_abt",	LSPREG,	arm64.REG_SPSR_abt },
	{"SPSR_EL1", LSPREG, arm64.REG_SPSR_EL1},
	{"SPSR_EL2", LSPREG, arm64.REG_SPSR_EL2},
	//	{ "SPSR_EL3",	LSPREG,	arm64.REG_SPSR_EL3 },
	//	{ "SPSR_fiq",	LSPREG,	arm64.REG_SPSR_fiq },
	//	{ "SPSR_ieq",	LSPREG,	arm64.REG_SPSR_ieq },
	//	{ "SPSR_und",	LSPREG,	arm64.REG_SPSR_und },
	{"DAIFSet", LSPREG, arm64.REG_DAIFSet},
	{"DAIFClr", LSPREG, arm64.REG_DAIFClr},
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
	{"ADC", LTYPE1, arm64.AADC},
	{"ADCS", LTYPE1, arm64.AADCS},
	{"ADCSW", LTYPE1, arm64.AADCSW},
	{"ADCW", LTYPE1, arm64.AADCW},
	{"ADD", LTYPE1, arm64.AADD},
	{"ADDS", LTYPE1, arm64.AADDS},
	{"ADDSW", LTYPE1, arm64.AADDSW},
	{"ADDW", LTYPE1, arm64.AADDW},
	{"ADR", LTYPEV, arm64.AADR},
	{"ADRP", LTYPEV, arm64.AADRP},
	{"AND", LTYPE1, arm64.AAND},
	{"ANDS", LTYPE1, arm64.AANDS},
	{"ANDSW", LTYPE1, arm64.AANDSW},
	{"ANDW", LTYPE1, arm64.AANDW},
	{"ASR", LTYPE1, arm64.AASR},
	{"ASRW", LTYPE1, arm64.AASRW},
	{"AT", LTYPEN, arm64.AAT},
	{"BFI", LTYPEY, arm64.ABFI},
	{"BFIW", LTYPEY, arm64.ABFIW},
	{"BFM", LTYPEY, arm64.ABFM},
	{"BFMW", LTYPEY, arm64.ABFMW},
	{"BFXIL", LTYPEY, arm64.ABFXIL},
	{"BFXILW", LTYPEY, arm64.ABFXILW},
	{"BIC", LTYPE1, arm64.ABIC},
	{"BICS", LTYPE1, arm64.ABICS},
	{"BICSW", LTYPE1, arm64.ABICSW},
	{"BICW", LTYPE1, arm64.ABICW},
	{"BRK", LTYPE6, arm64.ABRK},
	{"CBNZ", LTYPE8, arm64.ACBNZ},
	{"CBNZW", LTYPE8, arm64.ACBNZW},
	{"CBZ", LTYPE8, arm64.ACBZ},
	{"CBZW", LTYPE8, arm64.ACBZW},
	{"CCMN", LTYPEU, arm64.ACCMN},
	{"CCMNW", LTYPEU, arm64.ACCMNW},
	{"CCMP", LTYPEU, arm64.ACCMP},
	{"CCMPW", LTYPEU, arm64.ACCMPW},
	{"CINC", LTYPES, arm64.ACINC},
	{"CINCW", LTYPES, arm64.ACINCW},
	{"CINV", LTYPES, arm64.ACINV},
	{"CINVW", LTYPES, arm64.ACINVW},
	{"CLREX", LTYPE6, arm64.ACLREX},
	{"CLS", LTYPE2, arm64.ACLS},
	{"CLSW", LTYPE2, arm64.ACLSW},
	{"CLZ", LTYPE2, arm64.ACLZ},
	{"CLZW", LTYPE2, arm64.ACLZW},
	{"CMN", LTYPE7, arm64.ACMN},
	{"CMNW", LTYPE7, arm64.ACMNW},
	{"CMP", LTYPE7, arm64.ACMP},
	{"CMPW", LTYPE7, arm64.ACMPW},
	{"CNEG", LTYPES, arm64.ACNEG},
	{"CNEGW", LTYPES, arm64.ACNEGW},
	{"CRC32B", LTYPE1, arm64.ACRC32B},
	{"CRC32CB", LTYPE1, arm64.ACRC32CB},
	{"CRC32CH", LTYPE1, arm64.ACRC32CH},
	{"CRC32CW", LTYPE1, arm64.ACRC32CW},
	{"CRC32CX", LTYPE1, arm64.ACRC32CX},
	{"CRC32H", LTYPE1, arm64.ACRC32H},
	{"CRC32W", LTYPE1, arm64.ACRC32W},
	{"CRC32X", LTYPE1, arm64.ACRC32X},
	{"CSEL", LTYPES, arm64.ACSEL},
	{"CSELW", LTYPES, arm64.ACSELW},
	{"CSET", LTYPER, arm64.ACSET},
	{"CSETM", LTYPER, arm64.ACSETM},
	{"CSETMW", LTYPER, arm64.ACSETMW},
	{"CSETW", LTYPER, arm64.ACSETW},
	{"CSINC", LTYPES, arm64.ACSINC},
	{"CSINCW", LTYPES, arm64.ACSINCW},
	{"CSINV", LTYPES, arm64.ACSINV},
	{"CSINVW", LTYPES, arm64.ACSINVW},
	{"CSNEG", LTYPES, arm64.ACSNEG},
	{"CSNEGW", LTYPES, arm64.ACSNEGW},
	{"DC", LTYPEN, arm64.ADC},
	{"DCPS1", LTYPE6, arm64.ADCPS1},
	{"DCPS2", LTYPE6, arm64.ADCPS2},
	{"DCPS3", LTYPE6, arm64.ADCPS3},
	{"DMB", LDMB, arm64.ADMB},
	{"DRPS", LTYPE6, arm64.ADRPS},
	{"DSB", LDMB, arm64.ADSB},
	{"EON", LTYPE1, arm64.AEON},
	{"EONW", LTYPE1, arm64.AEONW},
	{"EOR", LTYPE1, arm64.AEOR},
	{"EORW", LTYPE1, arm64.AEORW},
	{"ERET", LTYPE0, arm64.AERET},
	{"EXTR", LTYPEP, arm64.AEXTR},
	{"EXTRW", LTYPEP, arm64.AEXTRW},
	{"HINT", LDMB, arm64.AHINT},
	{"HLT", LTYPE6, arm64.AHLT},
	{"HVC", LTYPE6, arm64.AHVC},
	{"IC", LTYPEN, arm64.AIC},
	{"ISB", LDMB, arm64.AISB},
	{"LSL", LTYPE1, arm64.ALSL},
	{"LSLW", LTYPE1, arm64.ALSLW},
	{"LSR", LTYPE1, arm64.ALSR},
	{"LSRW", LTYPE1, arm64.ALSRW},
	{"MADD", LTYPEM, arm64.AMADD},
	{"MADDW", LTYPEM, arm64.AMADDW},
	{"MNEG", LTYPE1, arm64.AMNEG},
	{"MNEGW", LTYPE1, arm64.AMNEGW},
	{"MRS", LTYPE3, arm64.AMRS},
	{"MSR", LTYPE3, arm64.AMSR},
	{"MSUB", LTYPEM, arm64.AMSUB},
	{"MSUBW", LTYPEM, arm64.AMSUBW},
	{"MUL", LTYPE1, arm64.AMUL},
	{"MULW", LTYPE1, arm64.AMULW},
	{"MVN", LTYPE1, arm64.AMVN},
	{"MVNW", LTYPE1, arm64.AMVNW},
	{"NEG", LTYPE1, arm64.ANEG},
	{"NEGS", LTYPE1, arm64.ANEGS},
	{"NEGSW", LTYPE1, arm64.ANEGSW},
	{"NEGW", LTYPE1, arm64.ANEGW},
	{"NGC", LTYPE2, arm64.ANGC},
	{"NGCS", LTYPE2, arm64.ANGCS},
	{"NGCSW", LTYPE2, arm64.ANGCSW},
	{"NGCW", LTYPE2, arm64.ANGCW},
	{"ORN", LTYPE1, arm64.AORN},
	{"ORNW", LTYPE1, arm64.AORNW},
	{"ORR", LTYPE1, arm64.AORR},
	{"ORRW", LTYPE1, arm64.AORRW},
	{"PRFM", LTYPE1, arm64.APRFM},
	{"PRFUM", LTYPE1, arm64.APRFUM},
	{"RBIT", LTYPE2, arm64.ARBIT},
	{"RBITW", LTYPE2, arm64.ARBITW},
	{"REM", LTYPE1, arm64.AREM},
	{"REMW", LTYPE1, arm64.AREMW},
	{"RET", LTYPEA, arm64.ARETURN},
	{"REV", LTYPE2, arm64.AREV},
	{"REV16", LTYPE2, arm64.AREV16},
	{"REV16W", LTYPE2, arm64.AREV16W},
	{"REV32", LTYPE2, arm64.AREV32},
	{"REVW", LTYPE2, arm64.AREVW},
	{"ROR", LTYPE1, arm64.AROR},
	{"RORW", LTYPE1, arm64.ARORW},
	{"SBC", LTYPE1, arm64.ASBC},
	{"SBCS", LTYPE1, arm64.ASBCS},
	{"SBCSW", LTYPE1, arm64.ASBCSW},
	{"SBCW", LTYPE1, arm64.ASBCW},
	{"SBFIZ", LTYPEY, arm64.ASBFIZ},
	{"SBFIZW", LTYPEY, arm64.ASBFIZW},
	{"SBFM", LTYPEY, arm64.ASBFM},
	{"SBFMW", LTYPEY, arm64.ASBFMW},
	{"SBFX", LTYPEY, arm64.ASBFX},
	{"SBFXW", LTYPEY, arm64.ASBFXW},
	{"SDIV", LTYPE1, arm64.ASDIV},
	{"SDIVW", LTYPE1, arm64.ASDIVW},
	{"SEV", LTYPE0, arm64.ASEV},
	{"SEVL", LTYPE0, arm64.ASEVL},
	{"SMADDL", LTYPEM, arm64.ASMADDL},
	{"SMC", LTYPE6, arm64.ASMC},
	{"SMNEGL", LTYPE1, arm64.ASMNEGL},
	{"SMSUBL", LTYPEM, arm64.ASMSUBL},
	{"SMULH", LTYPE1, arm64.ASMULH},
	{"SMULL", LTYPE1, arm64.ASMULL},
	{"STLR", LTYPE3, arm64.ASTLR},
	{"STLRB", LTYPE3, arm64.ASTLRB},
	{"STLRH", LTYPE3, arm64.ASTLRH},
	{"STLRW", LTYPE3, arm64.ASTLRW},
	{"STLXP", LSTXR, arm64.ASTLXP},
	{"STLXR", LSTXR, arm64.ASTLXR},
	{"STLXRB", LSTXR, arm64.ASTLXRB},
	{"STLXRH", LSTXR, arm64.ASTLXRH},
	{"STLXRW", LSTXR, arm64.ASTLXRW},
	{"STXR", LSTXR, arm64.ASTXR},
	{"STXRB", LSTXR, arm64.ASTXRB},
	{"STXRH", LSTXR, arm64.ASTXRH},
	// {"STXP", LSTXR, arm64.ASTXP},	// TODO(aram)
	// {"STXPW", LSTXR, arm64.ASTXPW},	// TODO(aram)
	{"STXRW", LSTXR, arm64.ASTXRW},
	{"SUB", LTYPE1, arm64.ASUB},
	{"SUBS", LTYPE1, arm64.ASUBS},
	{"SUBSW", LTYPE1, arm64.ASUBSW},
	{"SUBW", LTYPE1, arm64.ASUBW},
	{"SVC", LTYPE6, arm64.ASVC},
	{"SXTB", LTYPE2, arm64.ASXTB},
	{"SXTBW", LTYPE2, arm64.ASXTBW},
	{"SXTH", LTYPE2, arm64.ASXTH},
	{"SXTHW", LTYPE2, arm64.ASXTHW},
	{"SXTW", LTYPE2, arm64.ASXTW},
	{"SYS", LTYPEN, arm64.ASYS},
	{"SYSL", LTYPEO, arm64.ASYSL},
	{"TBNZ", LTYPET, arm64.ATBNZ},
	{"TBZ", LTYPET, arm64.ATBZ},
	{"TLBI", LTYPEN, arm64.ATLBI},
	{"TST", LTYPE7, arm64.ATST},
	{"TSTW", LTYPE7, arm64.ATSTW},
	{"UBFIZ", LTYPEY, arm64.AUBFIZ},
	{"UBFIZW", LTYPEY, arm64.AUBFIZW},
	{"UBFM", LTYPEY, arm64.AUBFM},
	{"UBFMW", LTYPEY, arm64.AUBFMW},
	{"UBFX", LTYPEY, arm64.AUBFX},
	{"UBFXW", LTYPEY, arm64.AUBFXW},
	{"UDIV", LTYPE1, arm64.AUDIV},
	{"UDIVW", LTYPE1, arm64.AUDIVW},
	{"UMADDL", LTYPEM, arm64.AUMADDL},
	{"UMNEGL", LTYPE1, arm64.AUMNEGL},
	{"UMSUBL", LTYPEM, arm64.AUMSUBL},
	{"UMULH", LTYPE1, arm64.AUMULH},
	{"UMULL", LTYPE1, arm64.AUMULL},
	{"UREM", LTYPE1, arm64.AUREM},
	{"UREMW", LTYPE1, arm64.AUREMW},
	{"UXTB", LTYPE2, arm64.AUXTB},
	{"UXTH", LTYPE2, arm64.AUXTH},
	{"UXTBW", LTYPE2, arm64.AUXTBW},
	{"UXTHW", LTYPE2, arm64.AUXTHW},
	{"UXTW", LTYPE2, arm64.AUXTW},
	{"WFE", LTYPE0, arm64.AWFE},
	{"WFI", LTYPE0, arm64.AWFI},
	{"YIELD", LTYPE0, arm64.AYIELD},
	{"LDXR", LTYPE3, arm64.ALDXR},
	{"LDXRB", LTYPE3, arm64.ALDXRB},
	{"LDXRH", LTYPE3, arm64.ALDXRH},
	{"LDXRW", LTYPE3, arm64.ALDXRW},
	{"LDAR", LTYPE3, arm64.ALDAR},
	{"LDARB", LTYPE3, arm64.ALDARB},
	{"LDARH", LTYPE3, arm64.ALDARH},
	{"LDARW", LTYPE3, arm64.ALDARW},
	{"LDXP", LTYPE3, arm64.ALDXP},
	{"LDXPW", LTYPE3, arm64.ALDXPW},
	{"LDAXP", LTYPE3, arm64.ALDAXP},
	{"LDAXPW", LTYPE3, arm64.ALDAXPW},
	{"LDAXR", LTYPE3, arm64.ALDAXR},
	{"LDAXRB", LTYPE3, arm64.ALDAXRB},
	{"LDAXRH", LTYPE3, arm64.ALDAXRH},
	{"LDAXRW", LTYPE3, arm64.ALDAXRW},
	{"MOVK", LMOVK, arm64.AMOVK},
	{"MOVKW", LMOVK, arm64.AMOVKW},
	{"MOVN", LMOVK, arm64.AMOVN},
	{"MOVNW", LMOVK, arm64.AMOVNW},
	{"MOVZ", LMOVK, arm64.AMOVZ},
	{"MOVZW", LMOVK, arm64.AMOVZW},
	{"MOVB", LTYPE3, arm64.AMOVB},
	{"MOVBU", LTYPE3, arm64.AMOVBU},
	{"MOVH", LTYPE3, arm64.AMOVH},
	{"MOVHU", LTYPE3, arm64.AMOVHU},
	{"MOVW", LTYPE3, arm64.AMOVW},
	{"MOVWU", LTYPE3, arm64.AMOVWU},
	{"MOV", LTYPE3, arm64.AMOV},
	{"STP", LTYPEX, arm64.ASTP},
	{"LDP", LTYPEZ, arm64.ALDP},
	{"MOVP", LTYPEJ, arm64.AMOVP},
	{"MOVPD", LTYPEJ, arm64.AMOVPD},
	{"MOVPQ", LTYPEJ, arm64.AMOVPQ},
	{"MOVPS", LTYPEJ, arm64.AMOVPS},
	{"MOVPSW", LTYPEJ, arm64.AMOVPSW},
	{"MOVPW", LTYPEJ, arm64.AMOVPW},
	{"MOVNP", LTYPEJ, arm64.AMOVNP},
	{"MOVNPW", LTYPEJ, arm64.AMOVNPW},
	{"FMOVD", LTYPE3, arm64.AFMOVD},
	{"FMOVS", LTYPE3, arm64.AFMOVS},
	{"SCVTFD", LTYPE3, arm64.ASCVTFD},
	{"SCVTFS", LTYPE3, arm64.ASCVTFS},
	{"SCVTFWD", LTYPE3, arm64.ASCVTFWD},
	{"SCVTFWS", LTYPE3, arm64.ASCVTFWS},
	{"UCVTFD", LTYPE3, arm64.AUCVTFD},
	{"UCVTFS", LTYPE3, arm64.AUCVTFS},
	{"UCVTFWD", LTYPE3, arm64.AUCVTFWD},
	{"UCVTFWS", LTYPE3, arm64.AUCVTFWS},
	{"FCVTSD", LTYPE3, arm64.AFCVTSD},
	{"FCVTDS", LTYPE3, arm64.AFCVTDS},
	{"FCVTZSD", LTYPE3, arm64.AFCVTZSD},
	{"FCVTZSDW", LTYPE3, arm64.AFCVTZSDW},
	{"FCVTZSS", LTYPE3, arm64.AFCVTZSS},
	{"FCVTZSSW", LTYPE3, arm64.AFCVTZSSW},
	{"FCVTZUD", LTYPE3, arm64.AFCVTZUD},
	{"FCVTZUDW", LTYPE3, arm64.AFCVTZUDW},
	{"FCVTZUS", LTYPE3, arm64.AFCVTZUS},
	{"FCVTZUSW", LTYPE3, arm64.AFCVTZUSW},
	{"FCMPS", LTYPEL, arm64.AFCMPS},
	{"FCMPD", LTYPEL, arm64.AFCMPD},
	{"FCMPES", LTYPEL, arm64.AFCMPES},
	{"FCMPED", LTYPEL, arm64.AFCMPED},
	{"FCCMPS", LTYPEF, arm64.AFCCMPS},
	{"FCCMPD", LTYPEF, arm64.AFCCMPD},
	{"FCCMPES", LTYPEF, arm64.AFCCMPES},
	{"FCCMPED", LTYPEF, arm64.AFCCMPED},
	{"FADDS", LTYPEK, arm64.AFADDS},
	{"FADDD", LTYPEK, arm64.AFADDD},
	{"FSUBS", LTYPEK, arm64.AFSUBS},
	{"FSUBD", LTYPEK, arm64.AFSUBD},
	{"FMULS", LTYPEK, arm64.AFMULS},
	{"FMULD", LTYPEK, arm64.AFMULD},
	{"FDIVS", LTYPEK, arm64.AFDIVS},
	{"FDIVD", LTYPEK, arm64.AFDIVD},
	{"FCSELS", LFCSEL, arm64.AFCSELS},
	{"FCSELD", LFCSEL, arm64.AFCSELD},
	{"FMAXS", LTYPEK, arm64.AFMAXS},
	{"FMINS", LTYPEK, arm64.AFMINS},
	{"FMAXD", LTYPEK, arm64.AFMAXD},
	{"FMIND", LTYPEK, arm64.AFMIND},
	{"FMAXNMS", LTYPEK, arm64.AFMAXNMS},
	{"FMAXNMD", LTYPEK, arm64.AFMAXNMD},
	{"FMINNMS", LTYPEK, arm64.AFMINNMS},
	{"FMINNMD", LTYPEK, arm64.AFMINNMD},
	{"FNMULS", LTYPEK, arm64.AFNMULS},
	{"FNMULD", LTYPEK, arm64.AFNMULD},
	{"FRINTNS", LTYPE3, arm64.AFRINTNS},
	{"FRINTND", LTYPE3, arm64.AFRINTND},
	{"FRINTPS", LTYPE3, arm64.AFRINTPS},
	{"FRINTPD", LTYPE3, arm64.AFRINTPD},
	{"FRINTMS", LTYPE3, arm64.AFRINTMS},
	{"FRINTMD", LTYPE3, arm64.AFRINTMD},
	{"FRINTZS", LTYPE3, arm64.AFRINTZS},
	{"FRINTZD", LTYPE3, arm64.AFRINTZD},
	{"FRINTAS", LTYPE3, arm64.AFRINTAS},
	{"FRINTAD", LTYPE3, arm64.AFRINTAD},
	{"FRINTXS", LTYPE3, arm64.AFRINTXS},
	{"FRINTXD", LTYPE3, arm64.AFRINTXD},
	{"FRINTIS", LTYPE3, arm64.AFRINTIS},
	{"FRINTID", LTYPE3, arm64.AFRINTID},
	{"FMADDS", LTYPEM, arm64.AFMADDS},
	{"FMADDD", LTYPEM, arm64.AFMADDD},
	{"FMSUBS", LTYPEM, arm64.AFMSUBS},
	{"FMSUBD", LTYPEM, arm64.AFMSUBD},
	{"FNMADDS", LTYPEM, arm64.AFNMADDS},
	{"FNMADDD", LTYPEM, arm64.AFNMADDD},
	{"FNMSUBS", LTYPEM, arm64.AFNMSUBS},
	{"FNMSUBD", LTYPEM, arm64.AFNMSUBD},
	{"FABSS", LTYPE3, arm64.AFABSS},
	{"FABSD", LTYPE3, arm64.AFABSD},
	{"FNEGS", LTYPE3, arm64.AFNEGS},
	{"FNEGD", LTYPE3, arm64.AFNEGD},
	{"FSQRTS", LTYPE3, arm64.AFSQRTS},
	{"FSQRTD", LTYPE3, arm64.AFSQRTD},
	{"FCVTDH", LTYPE3, arm64.AFCVTDH},
	{"FCVTHS", LTYPE3, arm64.AFCVTHS},
	{"FCVTHD", LTYPE3, arm64.AFCVTHD},
	{"FCVTSH", LTYPE3, arm64.AFCVTSH},
	{"AESD", LTYPEW, arm64.AAESD},
	{"AESE", LTYPEW, arm64.AAESE},
	{"AESIMC", LTYPEW, arm64.AAESIMC},
	{"AESMC", LTYPEW, arm64.AAESMC},
	{"SHA1C", LTYPEW, arm64.ASHA1C},
	{"SHA1H", LTYPEW, arm64.ASHA1H},
	{"SHA1M", LTYPEW, arm64.ASHA1M},
	{"SHA1P", LTYPEW, arm64.ASHA1P},
	{"SHA1SU0", LTYPEW, arm64.ASHA1SU0},
	{"SHA1SU1", LTYPEW, arm64.ASHA1SU1},
	{"SHA256H", LTYPEW, arm64.ASHA256H},
	{"SHA256H2", LTYPEW, arm64.ASHA256H2},
	{"SHA256SU0", LTYPEW, arm64.ASHA256SU0},
	{"SHA256SU1", LTYPEW, arm64.ASHA256SU1},
	{"B", LTYPE4, arm64.AB},
	{"BL", LTYPE4, arm64.ABL},
	{"BEQ", LTYPE5, arm64.ABEQ},
	{"BNE", LTYPE5, arm64.ABNE},
	{"BCS", LTYPE5, arm64.ABCS},
	{"BHS", LTYPE5, arm64.ABHS},
	{"BCC", LTYPE5, arm64.ABCC},
	{"BLO", LTYPE5, arm64.ABLO},
	{"BMI", LTYPE5, arm64.ABMI},
	{"BPL", LTYPE5, arm64.ABPL},
	{"BVS", LTYPE5, arm64.ABVS},
	{"BVC", LTYPE5, arm64.ABVC},
	{"BHI", LTYPE5, arm64.ABHI},
	{"BLS", LTYPE5, arm64.ABLS},
	{"BGE", LTYPE5, arm64.ABGE},
	{"BLT", LTYPE5, arm64.ABLT},
	{"BGT", LTYPE5, arm64.ABGT},
	{"BLE", LTYPE5, arm64.ABLE},
	{"BCASE", LTYPE5, arm64.ABCASE},
	{"TEXT", LTYPEB, arm64.ATEXT},
	{"GLOBL", LTYPEB, arm64.AGLOBL},
	{"DATA", LTYPEC, arm64.ADATA},
	{"CASE", LTYPED, arm64.ACASE},
	{"END", LTYPEE, arm64.AEND},
	{"WORD", LTYPEH, arm64.AWORD},
	{"DWORD", LTYPEH, arm64.ADWORD},
	{"SCHED", LSCHED, 0},
	{"NOSCHED", LSCHED, 0x80},
	{"NOP", LTYPEQ, arm64.ANOP},
	{"UNDEF", LTYPEQ, arm64.AUNDEF},
	{"RETURN", LTYPEA, arm64.ARETURN},
	{"PCDATA", LPCDAT, arm64.APCDATA},
	{"FUNCDATA", LFUNCDAT, arm64.AFUNCDATA},
	{"", 0, 0},
}

func cinit() {
	nullgen.Type = arm64.TYPE_NONE
	nullgen.Name = arm64.TYPE_NONE
	nullgen.Reg = arm64.0
	nullgen.Scale = arm64.0 // replaced Gen.xreg with Prog.scale
}

func cclean() {
	outcode(arm64.AEND, &nullgen, arm64.0, &nullgen)
}

var lastpc *obj.Prog
var nosched int

func outcode(a int, g1 *obj.Addr, reg int, g2 *obj.Addr) {
	var p *obj.Prog
	var pl *obj.Plist

	if asm.Pass == 1 {
		goto out
	}

	if g1.Scale != arm64.0 {
		if reg != arm64.0 || g2.Scale != arm64.0 {
			yyerror("bad addressing modes")
		}
		reg = int(g1.Scale)
	} else if g2.Scale != arm64.0 {
		if reg != arm64.0 {
			yyerror("bad addressing modes")
		}
		reg = int(g2.Scale)
	}

	p = asm.Ctxt.NewProg()
	p.As = int16(a)
	p.Lineno = stmtline
	if nosched != 0 {
		p.Mark |= arm64.NOSCHED
	}
	p.From = *g1
	p.Reg = uint8(reg)
	p.To = *g2
	p.Pc = int64(asm.PC)

	if lastpc == nil {
		pl = obj.Linknewplist(asm.Ctxt)
		pl.Firstpc = p
	} else {

		lastpc.Link = p
	}
	lastpc = p

out:
	if a != arm64.AGLOBL && a != arm64.ADATA {
		asm.PC++
	}
}

func outgcode(a int, g1 *obj.Addr, reg int, g2 *obj.Addr, g3 *obj.Addr) {
	var p *obj.Prog
	var pl *obj.Plist

	if asm.Pass == 1 {
		goto out
	}

	p = asm.Ctxt.NewProg()
	p.As = int16(a)
	p.Lineno = stmtline
	if nosched != 0 {
		p.Mark |= arm64.NOSCHED
	}
	p.From = *g1
	p.Reg = uint8(reg)
	p.To = *g2
	p.From3 = *g3
	p.Pc = int64(asm.PC)

	if lastpc == nil {
		pl = obj.Linknewplist(asm.Ctxt)
		pl.Firstpc = p
	} else {
		lastpc.Link = p
	}
	lastpc = p

out:
	if a != arm64.AGLOBL && a != arm64.ADATA {
		asm.PC++
	}
}

func outtcode(a int, from *obj.Addr, to *obj.Addr, to3 *obj.Addr) {
	var p *obj.Prog
	var pl *obj.Plist

	if asm.Pass == 1 {
		goto out
	}
	p = asm.Ctxt.NewProg()
	p.As = int16(a)
	p.Lineno = stmtline
	if nosched != 0 {
		p.Mark |= arm64.NOSCHED
	}
	p.From = *from
	p.To = *to
	p.To3 = *to3
	p.Pc = int64(asm.PC)

	if lastpc == nil {
		pl = obj.Linknewplist(asm.Ctxt)
		pl.Firstpc = p
	} else {
		lastpc.Link = p
	}
	lastpc = p

out:
	if a != arm64.AGLOBL && a != arm64.ADATA {
		asm.PC++
	}
}
