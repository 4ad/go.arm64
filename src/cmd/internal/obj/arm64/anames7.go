package arm64

var Anames = []string{
	"XXX",
	"CALL",
	"CHECKNIL",
	"DATA",
	"DUFFCOPY",
	"DUFFZERO",
	"END",
	"FUNCDATA",
	"GLOBL",
	"JMP",
	"NOP",
	"PCDATA",
	"RET",
	"TEXT",
	"TYPE",
	"UNDEF",
	"USEFIELD",
	"VARDEF",
	"VARKILL",
	"ADC",
	"ADCS",
	"ADCSW",
	"ADCW",
	"ADD",
	"ADDS",
	"ADDSW",
	"ADDW",
	"ADR",
	"ADRP",
	"AND",
	"ANDS",
	"ANDSW",
	"ANDW",
	"ASR",
	"ASRW",
	"AT",
	"B",
	"BFI",
	"BFIW",
	"BFM",
	"BFMW",
	"BFXIL",
	"BFXILW",
	"BIC",
	"BICS",
	"BICSW",
	"BICW",
	"BL",
	"BRK",
	"CBNZ",
	"CBNZW",
	"CBZ",
	"CBZW",
	"CCMN",
	"CCMNW",
	"CCMP",
	"CCMPW",
	"CINC",
	"CINCW",
	"CINV",
	"CINVW",
	"CLREX",
	"CLS",
	"CLSW",
	"CLZ",
	"CLZW",
	"CMN",
	"CMNW",
	"CMP",
	"CMPW",
	"CNEG",
	"CNEGW",
	"CRC32B",
	"CRC32CB",
	"CRC32CH",
	"CRC32CW",
	"CRC32CX",
	"CRC32H",
	"CRC32W",
	"CRC32X",
	"CSEL",
	"CSELW",
	"CSET",
	"CSETM",
	"CSETMW",
	"CSETW",
	"CSINC",
	"CSINCW",
	"CSINV",
	"CSINVW",
	"CSNEG",
	"CSNEGW",
	"DC",
	"DCPS1",
	"DCPS2",
	"DCPS3",
	"DMB",
	"DRPS",
	"DSB",
	"EON",
	"EONW",
	"EOR",
	"EORW",
	"ERET",
	"EXTR",
	"EXTRW",
	"HINT",
	"HLT",
	"HVC",
	"IC",
	"ISB",
	"LDAR",
	"LDARB",
	"LDARH",
	"LDARW",
	"LDAXP",
	"LDAXPW",
	"LDAXR",
	"LDAXRB",
	"LDAXRH",
	"LDAXRW",
	"LDP",
	"LDXR",
	"LDXRB",
	"LDXRH",
	"LDXRW",
	"LDXP",
	"LDXPW",
	"LSL",
	"LSLW",
	"LSR",
	"LSRW",
	"MADD",
	"MADDW",
	"MNEG",
	"MNEGW",
	"MOVK",
	"MOVKW",
	"MOVN",
	"MOVNW",
	"MOVZ",
	"MOVZW",
	"MRS",
	"MSR",
	"MSUB",
	"MSUBW",
	"MUL",
	"MULW",
	"MVN",
	"MVNW",
	"NEG",
	"NEGS",
	"NEGSW",
	"NEGW",
	"NGC",
	"NGCS",
	"NGCSW",
	"NGCW",
	"NOP",
	"ORN",
	"ORNW",
	"ORR",
	"ORRW",
	"PRFM",
	"PRFUM",
	"RBIT",
	"RBITW",
	"REM",
	"REMW",
	"RET",
	"REV",
	"REV16",
	"REV16W",
	"REV32",
	"REVW",
	"ROR",
	"RORW",
	"SBC",
	"SBCS",
	"SBCSW",
	"SBCW",
	"SBFIZ",
	"SBFIZW",
	"SBFM",
	"SBFMW",
	"SBFX",
	"SBFXW",
	"SDIV",
	"SDIVW",
	"SEV",
	"SEVL",
	"SMADDL",
	"SMC",
	"SMNEGL",
	"SMSUBL",
	"SMULH",
	"SMULL",
	"STXR",
	"STXRB",
	"STXRH",
	"STXP",
	"STXPW",
	"STXRW",
	"STLP",
	"STLPW",
	"STLR",
	"STLRB",
	"STLRH",
	"STLRW",
	"STLXP",
	"STLXPW",
	"STLXR",
	"STLXRB",
	"STLXRH",
	"STLXRW",
	"STP",
	"SUB",
	"SUBS",
	"SUBSW",
	"SUBW",
	"SVC",
	"SXTB",
	"SXTBW",
	"SXTH",
	"SXTHW",
	"SXTW",
	"SYS",
	"SYSL",
	"TBNZ",
	"TBZ",
	"TLBI",
	"TST",
	"TSTW",
	"UBFIZ",
	"UBFIZW",
	"UBFM",
	"UBFMW",
	"UBFX",
	"UBFXW",
	"UDIV",
	"UDIVW",
	"UMADDL",
	"UMNEGL",
	"UMSUBL",
	"UMULH",
	"UMULL",
	"UREM",
	"UREMW",
	"UXTB",
	"UXTH",
	"UXTW",
	"UXTBW",
	"UXTHW",
	"WFE",
	"WFI",
	"YIELD",
	"MOVB",
	"MOVBU",
	"MOVH",
	"MOVHU",
	"MOVW",
	"MOVWU",
	"MOVD",
	"MOVNP",
	"MOVNPW",
	"MOVP",
	"MOVPD",
	"MOVPQ",
	"MOVPS",
	"MOVPSW",
	"MOVPW",
	"BEQ",
	"BNE",
	"BCS",
	"BHS",
	"BCC",
	"BLO",
	"BMI",
	"BPL",
	"BVS",
	"BVC",
	"BHI",
	"BLS",
	"BGE",
	"BLT",
	"BGT",
	"BLE",
	"FABSD",
	"FABSS",
	"FADDD",
	"FADDS",
	"FCCMPD",
	"FCCMPED",
	"FCCMPS",
	"FCCMPES",
	"FCMPD",
	"FCMPED",
	"FCMPES",
	"FCMPS",
	"FCVTSD",
	"FCVTDS",
	"FCVTZSD",
	"FCVTZSDW",
	"FCVTZSS",
	"FCVTZSSW",
	"FCVTZUD",
	"FCVTZUDW",
	"FCVTZUS",
	"FCVTZUSW",
	"FDIVD",
	"FDIVS",
	"FMOVD",
	"FMOVS",
	"FMULD",
	"FMULS",
	"FNEGD",
	"FNEGS",
	"FSQRTD",
	"FSQRTS",
	"FSUBD",
	"FSUBS",
	"SCVTFD",
	"SCVTFS",
	"SCVTFWD",
	"SCVTFWS",
	"UCVTFD",
	"UCVTFS",
	"UCVTFWD",
	"UCVTFWS",
	"HISTORY",
	"NAME",
	"WORD",
	"DYNT",
	"INIT",
	"BCASE",
	"CASE",
	"DWORD",
	"SIGNAME",
	"GOK",
	"RETURN",
	"END",
	"FCSELS",
	"FCSELD",
	"FMAXS",
	"FMINS",
	"FMAXD",
	"FMIND",
	"FMAXNMS",
	"FMAXNMD",
	"FNMULS",
	"FNMULD",
	"FRINTNS",
	"FRINTND",
	"FRINTPS",
	"FRINTPD",
	"FRINTMS",
	"FRINTMD",
	"FRINTZS",
	"FRINTZD",
	"FRINTAS",
	"FRINTAD",
	"FRINTXS",
	"FRINTXD",
	"FRINTIS",
	"FRINTID",
	"FMADDS",
	"FMADDD",
	"FMSUBS",
	"FMSUBD",
	"FNMADDS",
	"FNMADDD",
	"FNMSUBS",
	"FNMSUBD",
	"FMINNMS",
	"FMINNMD",
	"FCVTDH",
	"FCVTHS",
	"FCVTHD",
	"FCVTSH",
	"AESD",
	"AESE",
	"AESIMC",
	"AESMC",
	"SHA1C",
	"SHA1H",
	"SHA1M",
	"SHA1P",
	"SHA1SU0",
	"SHA1SU1",
	"SHA256H",
	"SHA256H2",
	"SHA256SU0",
	"SHA256SU1",
	"UNDEF",
	"USEFIELD",
	"TYPE",
	"FUNCDATA",
	"PCDATA",
	"CHECKNIL",
	"VARDEF",
	"VARKILL",
	"DUFFCOPY",
	"DUFFZERO",
	"LAST",
}

var cnames7 = []string{
	"NONE",
	"REG",
	"RSP",
	"FREG",
	"VREG",
	"PAIR",
	"SHIFT",
	"EXTREG",
	"SPR",
	"COND",
	"ZCON",
	"ADDCON0",
	"ADDCON",
	"MOVCON",
	"BITCON",
	"ABCON",
	"MBCON",
	"LCON",
	"VCON",
	"FCON",
	"VCONADDR",
	"AACON",
	"LACON",
	"AECON",
	"SBRA",
	"LBRA",
	"NPAUTO",
	"NSAUTO",
	"PSAUTO",
	"PPAUTO",
	"UAUTO4K",
	"UAUTO8K",
	"UAUTO16K",
	"UAUTO32K",
	"UAUTO64K",
	"LAUTO",
	"SEXT1",
	"SEXT2",
	"SEXT4",
	"SEXT8",
	"SEXT16",
	"LEXT",
	"ZOREG",
	"NPOREG",
	"NSOREG",
	"PSOREG",
	"PPOREG",
	"UOREG4K",
	"UOREG8K",
	"UOREG16K",
	"UOREG32K",
	"UOREG64K",
	"LOREG",
	"ADDR",
	"ROFF",
	"XPRE",
	"XPOST",
	"GOK",
	"TEXTSIZE",
	"NCLASS",
}
