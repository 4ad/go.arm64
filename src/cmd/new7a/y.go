//line a.y:2
package main

import __yyfmt__ "fmt"

//line a.y:2
import (
	"cmd/internal/asm"
	"cmd/internal/obj"
	. "cmd/internal/obj/arm64"
)

//line a.y:11
type yySymType struct {
	yys  int
	sym  *asm.Sym
	lval int64
	dval float64
	sval string
	addr obj.Addr
}

const LTYPE0 = 57346
const LTYPE1 = 57347
const LTYPE2 = 57348
const LTYPE3 = 57349
const LTYPE4 = 57350
const LTYPE5 = 57351
const LTYPE6 = 57352
const LTYPE7 = 57353
const LTYPE8 = 57354
const LTYPE9 = 57355
const LTYPEA = 57356
const LTYPEB = 57357
const LTYPEC = 57358
const LTYPED = 57359
const LTYPEE = 57360
const LTYPEF = 57361
const LTYPEG = 57362
const LTYPEH = 57363
const LTYPEI = 57364
const LTYPEJ = 57365
const LTYPEK = 57366
const LTYPEL = 57367
const LTYPEM = 57368
const LTYPEN = 57369
const LTYPEO = 57370
const LTYPEP = 57371
const LTYPEQ = 57372
const LTYPER = 57373
const LTYPES = 57374
const LTYPET = 57375
const LTYPEU = 57376
const LTYPEV = 57377
const LTYPEW = 57378
const LTYPEX = 57379
const LTYPEY = 57380
const LTYPEZ = 57381
const LMOVK = 57382
const LDMB = 57383
const LSTXR = 57384
const LCONST = 57385
const LSP = 57386
const LSB = 57387
const LFP = 57388
const LPC = 57389
const LR = 57390
const LREG = 57391
const LF = 57392
const LFREG = 57393
const LV = 57394
const LVREG = 57395
const LC = 57396
const LCREG = 57397
const LFCR = 57398
const LFCSEL = 57399
const LCOND = 57400
const LS = 57401
const LAT = 57402
const LEXT = 57403
const LSPR = 57404
const LSPREG = 57405
const LVTYPE = 57406
const LPCDAT = 57407
const LFUNCDAT = 57408
const LSCHED = 57409
const LFCONST = 57410
const LSCONST = 57411
const LNAME = 57412
const LLAB = 57413
const LVAR = 57414

var yyToknames = []string{
	"'|'",
	"'^'",
	"'&'",
	"'<'",
	"'>'",
	"'+'",
	"'-'",
	"'*'",
	"'/'",
	"'%'",
	"LTYPE0",
	"LTYPE1",
	"LTYPE2",
	"LTYPE3",
	"LTYPE4",
	"LTYPE5",
	"LTYPE6",
	"LTYPE7",
	"LTYPE8",
	"LTYPE9",
	"LTYPEA",
	"LTYPEB",
	"LTYPEC",
	"LTYPED",
	"LTYPEE",
	"LTYPEF",
	"LTYPEG",
	"LTYPEH",
	"LTYPEI",
	"LTYPEJ",
	"LTYPEK",
	"LTYPEL",
	"LTYPEM",
	"LTYPEN",
	"LTYPEO",
	"LTYPEP",
	"LTYPEQ",
	"LTYPER",
	"LTYPES",
	"LTYPET",
	"LTYPEU",
	"LTYPEV",
	"LTYPEW",
	"LTYPEX",
	"LTYPEY",
	"LTYPEZ",
	"LMOVK",
	"LDMB",
	"LSTXR",
	"LCONST",
	"LSP",
	"LSB",
	"LFP",
	"LPC",
	"LR",
	"LREG",
	"LF",
	"LFREG",
	"LV",
	"LVREG",
	"LC",
	"LCREG",
	"LFCR",
	"LFCSEL",
	"LCOND",
	"LS",
	"LAT",
	"LEXT",
	"LSPR",
	"LSPREG",
	"LVTYPE",
	"LPCDAT",
	"LFUNCDAT",
	"LSCHED",
	"LFCONST",
	"LSCONST",
	"LNAME",
	"LLAB",
	"LVAR",
}
var yyStatenames = []string{}

const yyEofCode = 1
const yyErrCode = 2
const yyMaxDepth = 200

//line yacctab:1
var yyExca = []int{
	-1, 1,
	1, -1,
	-2, 0,
	-1, 16,
	85, 24,
	-2, 69,
	-1, 150,
	1, 3,
	-2, 0,
	-1, 229,
	94, 134,
	-2, 69,
	-1, 251,
	86, 119,
	-2, 105,
	-1, 252,
	86, 120,
	-2, 106,
}

const yyNprod = 165
const yyPrivate = 57344

var yyTokenNames []string
var yyStates []string

const yyLast = 789

var yyAct = []int{

	152, 382, 249, 133, 74, 2, 65, 67, 262, 331,
	311, 154, 228, 69, 72, 61, 61, 70, 142, 104,
	406, 54, 61, 369, 106, 368, 94, 95, 96, 118,
	118, 227, 181, 226, 381, 380, 84, 419, 111, 113,
	404, 139, 69, 121, 144, 144, 57, 385, 140, 357,
	351, 347, 56, 346, 345, 135, 344, 176, 134, 149,
	93, 156, 339, 146, 64, 117, 119, 338, 102, 268,
	97, 109, 110, 386, 66, 81, 80, 166, 274, 122,
	123, 172, 173, 174, 63, 62, 280, 165, 175, 212,
	145, 145, 147, 98, 167, 189, 106, 69, 203, 180,
	71, 112, 114, 194, 179, 120, 118, 151, 153, 178,
	177, 87, 86, 60, 187, 193, 162, 141, 143, 78,
	60, 148, 81, 80, 63, 62, 207, 208, 115, 215,
	76, 192, 266, 312, 186, 124, 126, 126, 128, 131,
	204, 55, 202, 418, 417, 75, 81, 80, 79, 63,
	62, 87, 86, 229, 108, 416, 236, 415, 81, 80,
	251, 82, 414, 412, 411, 69, 78, 410, 409, 387,
	261, 260, 172, 375, 374, 89, 88, 55, 373, 271,
	272, 273, 270, 372, 276, 277, 367, 366, 365, 364,
	78, 209, 362, 92, 361, 79, 282, 106, 283, 53,
	284, 83, 78, 360, 359, 61, 138, 358, 82, 55,
	355, 354, 297, 185, 298, 267, 286, 210, 69, 79,
	258, 353, 330, 281, 301, 108, 139, 309, 310, 308,
	250, 79, 82, 144, 317, 314, 69, 108, 259, 292,
	135, 313, 319, 134, 82, 75, 235, 234, 233, 63,
	62, 316, 294, 290, 332, 332, 332, 332, 296, 232,
	278, 231, 230, 300, 333, 334, 335, 139, 225, 341,
	224, 223, 287, 288, 289, 222, 291, 55, 221, 145,
	350, 295, 219, 348, 340, 218, 81, 80, 217, 299,
	216, 214, 211, 206, 205, 352, 320, 321, 322, 323,
	324, 201, 200, 327, 328, 329, 315, 75, 349, 318,
	199, 63, 62, 87, 86, 198, 363, 197, 196, 302,
	303, 195, 304, 305, 306, 307, 371, 370, 229, 164,
	78, 163, 155, 52, 51, 48, 49, 379, 50, 116,
	220, 267, 405, 81, 80, 384, 100, 383, 383, 157,
	158, 293, 159, 89, 88, 106, 407, 107, 213, 79,
	413, 391, 392, 284, 284, 108, 326, 356, 139, 394,
	275, 399, 82, 69, 389, 402, 87, 86, 401, 400,
	63, 62, 135, 376, 377, 134, 75, 78, 75, 256,
	63, 62, 63, 62, 255, 247, 246, 245, 243, 244,
	238, 239, 240, 241, 242, 378, 285, 393, 170, 254,
	63, 62, 160, 161, 424, 77, 79, 125, 336, 429,
	325, 60, 108, 183, 184, 81, 80, 252, 388, 82,
	390, 63, 62, 430, 264, 263, 265, 431, 432, 264,
	263, 265, 279, 63, 62, 257, 264, 263, 265, 293,
	403, 127, 127, 182, 129, 183, 184, 421, 240, 241,
	242, 425, 408, 395, 253, 396, 397, 398, 7, 78,
	75, 150, 1, 73, 63, 62, 87, 86, 89, 88,
	337, 85, 68, 188, 420, 136, 422, 423, 91, 90,
	81, 80, 428, 59, 58, 137, 92, 0, 79, 0,
	0, 0, 0, 76, 83, 0, 8, 0, 0, 81,
	80, 82, 0, 0, 0, 0, 426, 427, 9, 10,
	11, 12, 14, 15, 16, 17, 18, 38, 26, 28,
	29, 30, 47, 37, 78, 31, 34, 41, 35, 36,
	42, 43, 44, 25, 27, 19, 20, 21, 22, 23,
	40, 0, 24, 78, 13, 45, 46, 81, 171, 168,
	0, 107, 99, 79, 0, 0, 81, 80, 105, 108,
	0, 39, 0, 0, 0, 0, 82, 81, 80, 32,
	33, 5, 79, 101, 3, 103, 4, 0, 342, 6,
	0, 343, 0, 0, 0, 82, 81, 80, 0, 0,
	130, 78, 132, 0, 0, 81, 80, 0, 0, 0,
	78, 247, 246, 245, 243, 244, 238, 239, 240, 241,
	242, 78, 0, 0, 0, 0, 170, 169, 92, 0,
	79, 238, 239, 240, 241, 242, 83, 92, 0, 79,
	78, 0, 0, 82, 0, 83, 0, 0, 0, 78,
	79, 0, 82, 0, 0, 60, 108, 0, 0, 0,
	0, 0, 0, 82, 0, 0, 0, 92, 0, 79,
	0, 0, 0, 0, 0, 108, 190, 0, 79, 0,
	0, 0, 82, 0, 191, 0, 0, 0, 0, 0,
	0, 82, 0, 0, 0, 0, 269, 247, 246, 245,
	243, 244, 238, 239, 240, 241, 242, 247, 246, 245,
	243, 244, 238, 239, 240, 241, 242, 246, 245, 243,
	244, 238, 239, 240, 241, 242, 245, 243, 244, 238,
	239, 240, 241, 242, 243, 244, 238, 239, 240, 241,
	242, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 248, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 237,
}
var yyPact = []int{

	-1000, 504, -1000, 252, 254, 249, -1000, 248, 114, 55,
	26, 26, 416, 33, 55, 55, 55, 26, 332, 278,
	278, 33, 278, 481, 33, 33, 191, 253, 587, 587,
	332, 55, 33, 33, 316, 51, 51, 278, 316, 278,
	113, 416, 332, 334, 568, 33, 332, 55, -1000, 149,
	149, -1000, -1000, -1000, -1000, 55, 246, -1000, -1000, -1000,
	149, 342, -1000, 28, 245, 243, -1000, -1000, -1000, -1,
	-1000, -1000, -1000, -1000, -1000, -1000, 548, -1000, -1000, -1000,
	149, 149, 149, 66, 22, -1000, -1000, 21, -1000, 16,
	-1000, 11, 446, 127, 596, 277, 416, 235, 232, 231,
	-1000, 229, 224, 216, 215, 587, 10, 414, 149, 208,
	207, -1000, -1000, -1000, 55, 55, 91, 206, 1, 346,
	205, 43, 204, 202, 199, 196, -1000, -1000, 330, 192,
	189, 185, 184, 182, -1000, -58, -1000, -60, 291, -1,
	176, 175, -1000, 173, 162, -1000, 161, -1000, 160, -1000,
	504, 703, -1000, 693, -1000, 373, -1000, 457, 401, 386,
	381, 438, 149, 332, 416, 385, -1, -1000, 45, -1000,
	-1000, 137, -1000, -1000, -1000, -20, 607, 322, 149, 149,
	149, -10, 362, 149, 149, 332, 435, -1000, -1000, -2,
	446, 66, -1000, -1000, -1000, 352, 277, 332, 332, 332,
	26, 332, 153, 294, -1000, 33, 332, -1000, -1000, -1000,
	-1000, 568, 380, 149, 332, -1000, 33, 416, 316, 316,
	263, 316, 316, 316, 316, 113, 149, 149, -84, 123,
	322, 332, 568, 149, 332, 416, -1000, -1000, 149, 149,
	149, 149, 149, 413, 358, 149, 149, 149, -1000, 136,
	-1000, -1000, -1000, 149, 149, 149, 149, 411, 391, -1000,
	-1000, -22, -27, -1000, -1000, -1000, 557, -1000, 500, -1000,
	-33, -35, -36, -38, 380, 414, -1000, -1000, -1000, 149,
	392, -10, -39, 55, -1000, -1000, -1000, -1000, 135, 125,
	124, -1000, 332, -40, 121, 118, -1000, 117, 108, -1000,
	-1000, -1000, -1000, 106, 55, 103, 102, 101, 100, -67,
	-69, -1000, 291, 291, 97, 92, -1000, 88, -1000, 87,
	447, 447, -1000, -1000, -1000, 149, 149, 727, 720, 712,
	332, -1000, -1000, -1000, -1000, -1000, 149, -1000, -55, -1000,
	-1000, -56, 66, 322, -1000, -1000, -1000, -1000, -42, -15,
	83, -1000, -1000, 332, 277, 332, -1000, -1000, 352, 352,
	33, 43, 316, -1000, 316, 316, 316, 113, -1000, -1000,
	-1000, -1000, 416, 322, 149, 332, 622, 622, -1000, -1000,
	-1000, -1000, -49, 271, -72, -1000, 301, 332, 82, -1000,
	81, 78, 77, 350, -1000, -1000, 76, 71, 69, -1000,
	-1000, 58, 57, -1000, -1000, -1000, -1000, -52, -1000, 332,
	33, 332, 332, 149, 33, 316, 316, 332, 149, -1000,
	-1000, 55, -1000, -1000, -1000, 55, 55, -1000, -1000, -1000,
	-1000, -1000, -1000,
}
var yyPgo = []int{

	0, 0, 57, 8, 32, 4, 2, 9, 1, 495,
	12, 6, 19, 74, 100, 14, 494, 415, 417, 493,
	485, 3, 46, 7, 36, 17, 483, 481, 52, 473,
	562, 18, 472, 5, 471, 468, 11,
}
var yyR1 = []int{

	0, 32, 32, 33, 34, 33, 33, 33, 33, 33,
	33, 33, 35, 35, 35, 35, 35, 35, 35, 35,
	35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
	35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
	35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
	35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
	35, 35, 35, 35, 35, 35, 35, 35, 30, 36,
	36, 31, 31, 12, 12, 23, 23, 23, 23, 23,
	17, 17, 11, 11, 11, 11, 11, 11, 11, 11,
	26, 26, 25, 25, 25, 27, 27, 27, 27, 27,
	27, 28, 28, 28, 22, 13, 13, 16, 16, 16,
	16, 19, 19, 19, 8, 8, 7, 5, 5, 6,
	6, 29, 29, 18, 18, 14, 14, 21, 21, 21,
	21, 20, 20, 9, 10, 10, 10, 15, 15, 24,
	24, 24, 4, 4, 4, 3, 3, 3, 1, 1,
	1, 1, 1, 1, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2,
}
var yyR2 = []int{

	0, 0, 2, 0, 0, 4, 4, 4, 2, 1,
	2, 2, 2, 6, 5, 4, 4, 4, 4, 7,
	3, 3, 3, 3, 1, 5, 4, 4, 8, 6,
	6, 9, 4, 5, 8, 8, 2, 2, 2, 3,
	3, 3, 3, 4, 6, 8, 6, 4, 3, 4,
	4, 4, 4, 6, 5, 9, 9, 8, 4, 6,
	6, 8, 2, 4, 4, 2, 6, 2, 1, 0,
	2, 7, 1, 4, 2, 2, 2, 4, 2, 1,
	2, 3, 1, 1, 1, 1, 1, 1, 1, 1,
	3, 1, 1, 4, 1, 3, 4, 5, 5, 6,
	6, 1, 1, 1, 2, 1, 1, 4, 4, 4,
	4, 1, 2, 5, 1, 2, 1, 1, 4, 1,
	1, 1, 4, 1, 1, 1, 4, 1, 1, 1,
	1, 4, 4, 3, 1, 3, 3, 1, 4, 4,
	5, 7, 0, 2, 2, 1, 1, 1, 1, 1,
	2, 2, 2, 3, 1, 3, 3, 3, 3, 3,
	4, 4, 3, 3, 3,
}
var yyChk = []int{

	-1000, -32, -33, 80, 82, 77, 85, -35, 2, 14,
	15, 16, 17, 50, 18, 19, 20, 21, 22, 41,
	42, 43, 44, 45, 48, 39, 24, 40, 25, 26,
	27, 31, 75, 76, 32, 34, 35, 29, 23, 67,
	46, 33, 36, 37, 38, 51, 52, 28, 83, 84,
	84, 85, 85, 85, -36, 86, -28, -22, -16, -19,
	87, -5, 59, 58, -28, -11, -13, -23, 66, -1,
	-25, -14, -15, -29, -5, 54, 87, -17, 53, 82,
	10, 9, 95, 88, -24, -27, 61, 60, 63, 62,
	73, 72, 80, -22, -36, -36, -36, -28, -13, -30,
	68, -30, -22, -30, -12, 87, -1, 80, 88, -22,
	-22, -36, -13, -36, -13, -14, 86, -24, -1, -24,
	-13, -36, -22, -22, -14, -18, -14, -17, 87, -18,
	-30, -14, -30, -21, -25, -15, -20, -9, 93, -1,
	-11, -13, -31, -13, -1, -22, -31, -22, -13, -36,
	-34, -2, -1, -2, -36, 86, -1, 7, 8, 10,
	70, 71, 88, 86, 86, 88, -1, -25, 11, 79,
	78, 10, -1, -1, -1, -5, -2, 88, 88, 88,
	88, -4, 7, 9, 10, 86, 7, -12, -26, -1,
	80, 88, -24, -12, -11, 86, 86, 86, 86, 86,
	86, 86, -24, 88, -4, 86, 86, -36, -36, -13,
	-14, 86, 88, 12, 86, -23, 86, 86, 86, 86,
	10, 86, 86, 86, 86, 86, 91, 91, -10, -15,
	86, 86, 86, 86, 86, 86, -33, 85, 9, 10,
	11, 12, 13, 7, 8, 6, 5, 4, 85, -6,
	-13, -5, 54, 7, 8, 8, 8, 7, -2, -13,
	-11, -5, -3, 55, 54, 56, 87, 78, 89, 89,
	-5, -1, -1, -1, 88, 8, -1, -1, -13, 7,
	88, -4, -5, -6, -5, 54, -12, -13, -13, -13,
	-28, -13, 86, 57, -22, -13, -22, -1, -1, -13,
	-22, -11, -14, -14, -14, -14, -14, -14, -21, -1,
	-1, 94, 10, -36, -5, -13, -31, -1, -13, -11,
	-2, -2, -2, -2, -2, 7, 8, -2, -2, -2,
	86, -7, -1, -7, -7, -7, 7, 89, 89, 89,
	-25, -1, 88, 91, 89, 89, 89, 89, -3, -4,
	-1, 89, -36, 86, 86, 86, -13, 89, 86, 86,
	86, 86, 86, -36, 86, 86, 86, 86, 92, 92,
	-15, -10, 86, 86, 86, 86, -2, -2, -13, -1,
	90, 90, -8, -5, -8, 89, 88, 86, -13, -12,
	-13, -6, -6, -22, -23, -14, -14, -14, -14, -21,
	-11, -5, -1, -13, 89, 71, 92, 55, -13, 86,
	86, 86, 86, 10, 86, 86, 86, 86, 86, 89,
	-13, -22, -13, -13, -1, -22, -14, -14, -13, -1,
	-36, -36, -36,
}
var yyDef = []int{

	1, -2, 2, 0, 0, 0, 9, 0, 0, 69,
	0, 0, 0, 0, 69, 69, -2, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 69, 69, 0, 0,
	0, 69, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 69, 4, 0,
	0, 8, 10, 11, 12, 69, 0, 101, 102, 103,
	0, 111, 117, 0, 0, 0, 82, 83, 84, 85,
	86, 87, 88, 89, 105, 106, 0, 79, 148, 149,
	0, 0, 0, 0, 92, 94, 125, 0, 137, 0,
	121, 0, 142, 0, 0, 0, 0, 0, 0, 0,
	68, 0, 0, 0, 0, 0, 0, 142, 0, 0,
	0, 36, 37, 38, 69, 69, 69, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 123, 124, 0, 0,
	0, 0, 0, 0, 127, 128, 129, 130, 0, 0,
	0, 0, 62, 0, 0, 72, 0, 65, 0, 67,
	-2, 0, 154, 0, 70, 0, 104, 0, 0, 0,
	0, 112, 0, 0, 0, 0, 75, 76, 0, 78,
	80, 0, 150, 151, 152, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 20, 21, 0,
	142, 0, 91, 22, 23, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 74, 0, 0, 39, 40, 41,
	42, 0, 0, 0, 0, 48, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, -2,
	0, 0, 0, 0, 0, 0, 5, 6, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 7, 0,
	15, -2, -2, 0, 0, 0, 0, 0, 0, 16,
	17, 0, 0, 145, 146, 147, 0, 81, 95, 153,
	0, 0, 0, 0, 0, 142, 143, 144, 18, 0,
	0, 74, 0, 69, 119, 120, 26, 27, 0, 0,
	0, 32, 0, 0, 0, 0, 43, 0, 0, 47,
	49, 50, 51, 52, 69, 0, 0, 0, 58, 0,
	0, 133, 0, 0, 0, 0, 63, 0, 64, 0,
	155, 156, 157, 158, 159, 0, 0, 162, 163, 164,
	14, 107, 116, 108, 109, 110, 0, 118, 96, 139,
	77, 0, 0, 0, 93, 126, 138, 122, 0, 0,
	0, 90, 25, 0, 0, 0, 33, 73, 0, 0,
	0, 0, 0, 54, 0, 0, 0, 0, 131, 132,
	135, 136, 0, 0, 0, 0, 160, 161, 13, 113,
	97, 98, 0, 114, 0, 140, 0, 0, 29, 30,
	0, 0, 0, 44, 46, 53, 0, 0, 0, 59,
	60, 0, 0, 66, 99, 115, 100, 0, 19, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 141,
	28, 69, 34, 35, 45, 69, 69, 57, 61, 71,
	31, 55, 56,
}
var yyTok1 = []int{

	1, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 90, 3, 3, 87, 13, 6, 3,
	88, 89, 11, 9, 86, 10, 3, 12, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 83, 85,
	7, 84, 8, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 91, 3, 92, 5, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 93, 4, 94, 95,
}
var yyTok2 = []int{

	2, 3, 14, 15, 16, 17, 18, 19, 20, 21,
	22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
	32, 33, 34, 35, 36, 37, 38, 39, 40, 41,
	42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61,
	62, 63, 64, 65, 66, 67, 68, 69, 70, 71,
	72, 73, 74, 75, 76, 77, 78, 79, 80, 81,
	82,
}
var yyTok3 = []int{
	0,
}

//line yaccpar:1

/*	parser for yacc output	*/

var yyDebug = 0

type yyLexer interface {
	Lex(lval *yySymType) int
	Error(s string)
}

const yyFlag = -1000

func yyTokname(c int) string {
	// 4 is TOKSTART above
	if c >= 4 && c-4 < len(yyToknames) {
		if yyToknames[c-4] != "" {
			return yyToknames[c-4]
		}
	}
	return __yyfmt__.Sprintf("tok-%v", c)
}

func yyStatname(s int) string {
	if s >= 0 && s < len(yyStatenames) {
		if yyStatenames[s] != "" {
			return yyStatenames[s]
		}
	}
	return __yyfmt__.Sprintf("state-%v", s)
}

func yylex1(lex yyLexer, lval *yySymType) int {
	c := 0
	char := lex.Lex(lval)
	if char <= 0 {
		c = yyTok1[0]
		goto out
	}
	if char < len(yyTok1) {
		c = yyTok1[char]
		goto out
	}
	if char >= yyPrivate {
		if char < yyPrivate+len(yyTok2) {
			c = yyTok2[char-yyPrivate]
			goto out
		}
	}
	for i := 0; i < len(yyTok3); i += 2 {
		c = yyTok3[i+0]
		if c == char {
			c = yyTok3[i+1]
			goto out
		}
	}

out:
	if c == 0 {
		c = yyTok2[1] /* unknown char */
	}
	if yyDebug >= 3 {
		__yyfmt__.Printf("lex %s(%d)\n", yyTokname(c), uint(char))
	}
	return c
}

func yyParse(yylex yyLexer) int {
	var yyn int
	var yylval yySymType
	var yyVAL yySymType
	yyS := make([]yySymType, yyMaxDepth)

	Nerrs := 0   /* number of errors */
	Errflag := 0 /* error recovery flag */
	yystate := 0
	yychar := -1
	yyp := -1
	goto yystack

ret0:
	return 0

ret1:
	return 1

yystack:
	/* put a state and value onto the stack */
	if yyDebug >= 4 {
		__yyfmt__.Printf("char %v in %v\n", yyTokname(yychar), yyStatname(yystate))
	}

	yyp++
	if yyp >= len(yyS) {
		nyys := make([]yySymType, len(yyS)*2)
		copy(nyys, yyS)
		yyS = nyys
	}
	yyS[yyp] = yyVAL
	yyS[yyp].yys = yystate

yynewstate:
	yyn = yyPact[yystate]
	if yyn <= yyFlag {
		goto yydefault /* simple state */
	}
	if yychar < 0 {
		yychar = yylex1(yylex, &yylval)
	}
	yyn += yychar
	if yyn < 0 || yyn >= yyLast {
		goto yydefault
	}
	yyn = yyAct[yyn]
	if yyChk[yyn] == yychar { /* valid shift */
		yychar = -1
		yyVAL = yylval
		yystate = yyn
		if Errflag > 0 {
			Errflag--
		}
		goto yystack
	}

yydefault:
	/* default state action */
	yyn = yyDef[yystate]
	if yyn == -2 {
		if yychar < 0 {
			yychar = yylex1(yylex, &yylval)
		}

		/* look through exception table */
		xi := 0
		for {
			if yyExca[xi+0] == -1 && yyExca[xi+1] == yystate {
				break
			}
			xi += 2
		}
		for xi += 2; ; xi += 2 {
			yyn = yyExca[xi+0]
			if yyn < 0 || yyn == yychar {
				break
			}
		}
		yyn = yyExca[xi+1]
		if yyn < 0 {
			goto ret0
		}
	}
	if yyn == 0 {
		/* error ... attempt to resume parsing */
		switch Errflag {
		case 0: /* brand new error */
			yylex.Error("syntax error")
			Nerrs++
			if yyDebug >= 1 {
				__yyfmt__.Printf("%s", yyStatname(yystate))
				__yyfmt__.Printf(" saw %s\n", yyTokname(yychar))
			}
			fallthrough

		case 1, 2: /* incompletely recovered error ... try again */
			Errflag = 3

			/* find a state where "error" is a legal shift action */
			for yyp >= 0 {
				yyn = yyPact[yyS[yyp].yys] + yyErrCode
				if yyn >= 0 && yyn < yyLast {
					yystate = yyAct[yyn] /* simulate a shift of "error" */
					if yyChk[yystate] == yyErrCode {
						goto yystack
					}
				}

				/* the current p has no shift on "error", pop stack */
				if yyDebug >= 2 {
					__yyfmt__.Printf("error recovery pops state %d\n", yyS[yyp].yys)
				}
				yyp--
			}
			/* there is no state on the stack with an error shift ... abort */
			goto ret1

		case 3: /* no shift yet; clobber input char */
			if yyDebug >= 2 {
				__yyfmt__.Printf("error recovery discards %s\n", yyTokname(yychar))
			}
			if yychar == yyEofCode {
				goto ret1
			}
			yychar = -1
			goto yynewstate /* try again in the same state */
		}
	}

	/* reduction by production yyn */
	if yyDebug >= 2 {
		__yyfmt__.Printf("reduce %v in:\n\t%v\n", yyn, yyStatname(yystate))
	}

	yynt := yyn
	yypt := yyp
	_ = yypt // guard against "declared and not used"

	yyp -= yyR2[yyn]
	// yyp is now the index of $0. Perform the default action. Iff the
	// reduced production is ε, $1 is possibly out of range.
	if yyp+1 >= len(yyS) {
		nyys := make([]yySymType, len(yyS)*2)
		copy(nyys, yyS)
		yyS = nyys
	}
	yyVAL = yyS[yyp+1]

	/* consult goto table to find next state */
	yyn = yyR1[yyn]
	yyg := yyPgo[yyn]
	yyj := yyg + yyS[yyp].yys + 1

	if yyj >= yyLast {
		yystate = yyAct[yyg]
	} else {
		yystate = yyAct[yyj]
		if yyChk[yystate] != -yyn {
			yystate = yyAct[yyg]
		}
	}
	// dummy call; replaced with literal code
	switch yynt {

	case 4:
		//line a.y:50
		{
			yyS[yypt-1].sym = asm.LabelLookup(yyS[yypt-1].sym)
			if yyS[yypt-1].sym.Type == LLAB && yyS[yypt-1].sym.Value != int64(asm.PC) {
				yyerror("redeclaration of %s", yyS[yypt-1].sym.Labelname)
			}
			yyS[yypt-1].sym.Type = LLAB
			yyS[yypt-1].sym.Value = int64(asm.PC)
		}
	case 6:
		//line a.y:60
		{
			yyS[yypt-3].sym.Type = LVAR
			yyS[yypt-3].sym.Value = yyS[yypt-1].lval
		}
	case 7:
		//line a.y:65
		{
			if yyS[yypt-3].sym.Value != yyS[yypt-1].lval {
				yyerror("redeclaration of %s", yyS[yypt-3].sym.Name)
			}
			yyS[yypt-3].sym.Value = yyS[yypt-1].lval
		}
	case 8:
		//line a.y:72
		{
			nosched = int(yyS[yypt-1].lval)
		}
	case 12:
		//line a.y:84
		{
			outcode(int(yyS[yypt-1].lval), &nullgen, NREG, &nullgen)
		}
	case 13:
		//line a.y:91
		{
			outcode(int(yyS[yypt-5].lval), &yyS[yypt-4].addr, int(yyS[yypt-2].lval), &yyS[yypt-0].addr)
		}
	case 14:
		//line a.y:95
		{
			outcode(int(yyS[yypt-4].lval), &yyS[yypt-3].addr, int(yyS[yypt-1].lval), &nullgen)
		}
	case 15:
		//line a.y:99
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 16:
		//line a.y:106
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 17:
		//line a.y:113
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 18:
		//line a.y:120
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 19:
		//line a.y:124
		{
			var a obj.Addr
			a = nullgen
			a.Type = D_CONST
			a.Offset = yyS[yypt-2].lval
			outgcode(int(yyS[yypt-6].lval), &yyS[yypt-5].addr, NREG, &a, &yyS[yypt-0].addr)
		}
	case 20:
		//line a.y:135
		{
			outcode(int(yyS[yypt-2].lval), &nullgen, NREG, &yyS[yypt-0].addr)
		}
	case 21:
		//line a.y:139
		{
			outcode(int(yyS[yypt-2].lval), &nullgen, NREG, &yyS[yypt-0].addr)
		}
	case 22:
		//line a.y:146
		{
			outcode(int(yyS[yypt-2].lval), &nullgen, NREG, &yyS[yypt-0].addr)
		}
	case 23:
		//line a.y:153
		{
			outcode(int(yyS[yypt-2].lval), &nullgen, NREG, &yyS[yypt-0].addr)
		}
	case 24:
		//line a.y:157
		{
			outcode(int(yyS[yypt-0].lval), &nullgen, NREG, &nullgen)
		}
	case 25:
		//line a.y:164
		{
			outcode(int(yyS[yypt-4].lval), &yyS[yypt-3].addr, int(yyS[yypt-1].lval), &nullgen)
		}
	case 26:
		//line a.y:171
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 27:
		//line a.y:178
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 28:
		//line a.y:185
		{
			outgcode(int(yyS[yypt-7].lval), &yyS[yypt-6].addr, int(yyS[yypt-2].addr.Reg), &yyS[yypt-4].addr, &yyS[yypt-0].addr)
		}
	case 29:
		//line a.y:189
		{
			outcode(int(yyS[yypt-5].lval), &yyS[yypt-4].addr, int(yyS[yypt-2].addr.Reg), &yyS[yypt-0].addr)
		}
	case 30:
		//line a.y:196
		{
			outcode(int(yyS[yypt-5].lval), &yyS[yypt-4].addr, int(yyS[yypt-2].addr.Reg), &yyS[yypt-0].addr)
		}
	case 31:
		//line a.y:203
		{
			outgcode(int(yyS[yypt-8].lval), &yyS[yypt-7].addr, int(yyS[yypt-3].addr.Reg), &yyS[yypt-5].addr, &yyS[yypt-1].addr)
		}
	case 32:
		//line a.y:210
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 33:
		//line a.y:214
		{
			outcode(int(yyS[yypt-4].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 34:
		//line a.y:221
		{
			outgcode(int(yyS[yypt-7].lval), &yyS[yypt-6].addr, int(yyS[yypt-2].lval), &yyS[yypt-4].addr, &yyS[yypt-0].addr)
		}
	case 35:
		//line a.y:228
		{
			outgcode(int(yyS[yypt-7].lval), &yyS[yypt-6].addr, int(yyS[yypt-2].lval), &yyS[yypt-4].addr, &yyS[yypt-0].addr)
		}
	case 36:
		//line a.y:235
		{
			outcode(int(yyS[yypt-1].lval), &nullgen, NREG, &nullgen)
		}
	case 37:
		//line a.y:239
		{
			outcode(int(yyS[yypt-1].lval), &nullgen, NREG, &yyS[yypt-0].addr)
		}
	case 38:
		//line a.y:246
		{
			outcode(int(yyS[yypt-1].lval), &nullgen, NREG, &nullgen)
		}
	case 39:
		//line a.y:250
		{
			outcode(int(yyS[yypt-2].lval), &yyS[yypt-1].addr, NREG, &nullgen)
		}
	case 40:
		//line a.y:254
		{
			outcode(int(yyS[yypt-2].lval), &yyS[yypt-1].addr, NREG, &nullgen)
		}
	case 41:
		//line a.y:258
		{
			outcode(int(yyS[yypt-2].lval), &nullgen, NREG, &yyS[yypt-0].addr)
		}
	case 42:
		//line a.y:262
		{
			outcode(int(yyS[yypt-2].lval), &nullgen, NREG, &yyS[yypt-0].addr)
		}
	case 43:
		//line a.y:269
		{
			asm.Settext(yyS[yypt-2].addr.Sym)
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 44:
		//line a.y:274
		{
			asm.Settext(yyS[yypt-4].addr.Sym)
			yyS[yypt-0].addr.Offset &= 0xffffffff
			yyS[yypt-0].addr.Offset |= -obj.ArgsSizeUnknown << 32
			outcode(int(yyS[yypt-5].lval), &yyS[yypt-4].addr, int(yyS[yypt-2].lval), &yyS[yypt-0].addr)
		}
	case 45:
		//line a.y:281
		{
			asm.Settext(yyS[yypt-6].addr.Sym)
			yyS[yypt-2].addr.Offset &= 0xffffffff
			yyS[yypt-2].addr.Offset |= (yyS[yypt-0].lval & 0xffffffff) << 32
			outcode(int(yyS[yypt-7].lval), &yyS[yypt-6].addr, int(yyS[yypt-4].lval), &yyS[yypt-2].addr)
		}
	case 46:
		//line a.y:291
		{
			outcode(int(yyS[yypt-5].lval), &yyS[yypt-4].addr, int(yyS[yypt-2].lval), &yyS[yypt-0].addr)
		}
	case 47:
		//line a.y:298
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 48:
		//line a.y:305
		{
			outcode(int(yyS[yypt-2].lval), &nullgen, NREG, &yyS[yypt-0].addr)
		}
	case 49:
		//line a.y:312
		{
			if yyS[yypt-2].addr.Type != D_CONST || yyS[yypt-0].addr.Type != D_CONST {
				yyerror("arguments to PCDATA must be integer constants")
			}
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 50:
		//line a.y:322
		{
			if yyS[yypt-2].addr.Type != D_CONST {
				yyerror("index for FUNCDATA must be integer constant")
			}
			if yyS[yypt-0].addr.Type != D_EXTERN && yyS[yypt-0].addr.Type != D_STATIC && yyS[yypt-0].addr.Type != D_OREG {
				yyerror("value for FUNCDATA must be symbol reference")
			}
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 51:
		//line a.y:335
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 52:
		//line a.y:342
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 53:
		//line a.y:346
		{
			outcode(int(yyS[yypt-5].lval), &yyS[yypt-4].addr, int(yyS[yypt-2].addr.Reg), &yyS[yypt-0].addr)
		}
	case 54:
		//line a.y:353
		{
			outcode(int(yyS[yypt-4].lval), &yyS[yypt-3].addr, int(yyS[yypt-1].addr.Reg), &nullgen)
		}
	case 55:
		//line a.y:360
		{
			outgcode(int(yyS[yypt-8].lval), &yyS[yypt-7].addr, int(yyS[yypt-3].addr.Reg), &yyS[yypt-5].addr, &yyS[yypt-1].addr)
		}
	case 56:
		//line a.y:367
		{
			outgcode(int(yyS[yypt-8].lval), &yyS[yypt-7].addr, int(yyS[yypt-5].addr.Reg), &yyS[yypt-3].addr, &yyS[yypt-1].addr)
		}
	case 57:
		//line a.y:374
		{
			outgcode(int(yyS[yypt-7].lval), &yyS[yypt-6].addr, int(yyS[yypt-2].addr.Reg), &yyS[yypt-4].addr, &yyS[yypt-0].addr)
		}
	case 58:
		//line a.y:381
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 59:
		//line a.y:385
		{
			outcode(int(yyS[yypt-5].lval), &yyS[yypt-4].addr, int(yyS[yypt-2].addr.Reg), &yyS[yypt-0].addr)
		}
	case 60:
		//line a.y:392
		{
			outcode(int(yyS[yypt-5].lval), &yyS[yypt-4].addr, int(yyS[yypt-2].lval), &yyS[yypt-0].addr)
		}
	case 61:
		//line a.y:399
		{
			outgcode(int(yyS[yypt-7].lval), &yyS[yypt-6].addr, int(yyS[yypt-2].lval), &yyS[yypt-4].addr, &yyS[yypt-0].addr)
		}
	case 62:
		//line a.y:406
		{
			outcode(int(yyS[yypt-1].lval), &yyS[yypt-0].addr, NREG, &nullgen)
		}
	case 63:
		//line a.y:410
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-0].addr, int(yyS[yypt-2].addr.Reg), &nullgen)
		}
	case 64:
		//line a.y:414
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 65:
		//line a.y:421
		{
			outcode(int(yyS[yypt-1].lval), &yyS[yypt-0].addr, NREG, &nullgen)
		}
	case 66:
		//line a.y:428
		{
			outtcode(int(yyS[yypt-5].lval), &yyS[yypt-4].addr, &yyS[yypt-2].addr, &yyS[yypt-0].addr)
		}
	case 67:
		//line a.y:435
		{
			outcode(int(yyS[yypt-1].lval), &nullgen, NREG, &nullgen)
		}
	case 68:
		//line a.y:441
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_COND
			yyVAL.addr.Reg = int8(yyS[yypt-0].lval)
		}
	case 71:
		//line a.y:452
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_CONST
			yyVAL.addr.Offset = int64(SYSARG4(int(yyS[yypt-6].lval), int(yyS[yypt-4].lval), int(yyS[yypt-2].lval), int(yyS[yypt-0].lval)))
		}
	case 72:
		yyVAL.addr = yyS[yypt-0].addr
	case 73:
		//line a.y:461
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_BRANCH
			yyVAL.addr.Offset = yyS[yypt-3].lval + int64(asm.PC)
		}
	case 74:
		//line a.y:467
		{
			yyS[yypt-1].sym = asm.LabelLookup(yyS[yypt-1].sym)
			yyVAL.addr = nullgen
			if asm.Pass == 2 && yyS[yypt-1].sym.Type != LLAB {
				yyerror("undefined label: %s", yyS[yypt-1].sym.Labelname)
			}
			yyVAL.addr.Type = D_BRANCH
			yyVAL.addr.Offset = yyS[yypt-1].sym.Value + yyS[yypt-0].lval
		}
	case 75:
		//line a.y:478
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_CONST
			yyVAL.addr.Offset = yyS[yypt-0].lval
		}
	case 76:
		//line a.y:484
		{
			yyVAL.addr = yyS[yypt-0].addr
			yyVAL.addr.Type = D_CONST
		}
	case 77:
		//line a.y:489
		{
			yyVAL.addr = yyS[yypt-0].addr
			yyVAL.addr.Type = D_OCONST
		}
	case 78:
		//line a.y:494
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_SCONST
			yyVAL.addr.U.Sval = yyS[yypt-0].sval
		}
	case 79:
		yyVAL.addr = yyS[yypt-0].addr
	case 80:
		//line a.y:503
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_FCONST
			yyVAL.addr.U.Dval = yyS[yypt-0].dval
		}
	case 81:
		//line a.y:509
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_FCONST
			yyVAL.addr.U.Dval = -yyS[yypt-0].dval
		}
	case 82:
		yyVAL.addr = yyS[yypt-0].addr
	case 83:
		yyVAL.addr = yyS[yypt-0].addr
	case 84:
		//line a.y:519
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_SPR
			yyVAL.addr.Offset = yyS[yypt-0].lval
		}
	case 85:
		//line a.y:525
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_OREG
			yyVAL.addr.Offset = yyS[yypt-0].lval
		}
	case 86:
		yyVAL.addr = yyS[yypt-0].addr
	case 87:
		yyVAL.addr = yyS[yypt-0].addr
	case 88:
		yyVAL.addr = yyS[yypt-0].addr
	case 89:
		yyVAL.addr = yyS[yypt-0].addr
	case 90:
		//line a.y:537
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_OREG
			yyVAL.addr.Reg = int8(yyS[yypt-1].lval)
			yyVAL.addr.Offset = 0
		}
	case 91:
		//line a.y:544
		{
			yyVAL.addr = yyS[yypt-0].addr
			if yyS[yypt-0].addr.Name != D_EXTERN && yyS[yypt-0].addr.Name != D_STATIC {
			}
		}
	case 92:
		yyVAL.addr = yyS[yypt-0].addr
	case 93:
		//line a.y:553
		{
			yyVAL.addr = yyS[yypt-3].addr
			yyVAL.addr.Type = D_OREG
			yyVAL.addr.Reg = int8(yyS[yypt-1].lval)
		}
	case 94:
		yyVAL.addr = yyS[yypt-0].addr
	case 95:
		//line a.y:562
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_OREG
			yyVAL.addr.Reg = int8(yyS[yypt-1].lval)
			yyVAL.addr.Offset = 0
		}
	case 96:
		//line a.y:569
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_OREG
			yyVAL.addr.Reg = int8(yyS[yypt-1].lval)
			yyVAL.addr.Offset = yyS[yypt-3].lval
		}
	case 97:
		//line a.y:576
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_XPRE
			yyVAL.addr.Reg = int8(yyS[yypt-2].lval)
			yyVAL.addr.Offset = yyS[yypt-4].lval
		}
	case 98:
		//line a.y:583
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_XPOST
			yyVAL.addr.Reg = int8(yyS[yypt-3].lval)
			yyVAL.addr.Offset = yyS[yypt-1].lval
		}
	case 99:
		//line a.y:590
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_ROFF
			yyVAL.addr.Reg = int8(yyS[yypt-4].lval)
			yyVAL.addr.Scale = int8(yyS[yypt-1].lval & 0x1f)
			yyVAL.addr.Offset = yyS[yypt-1].lval
		}
	case 100:
		//line a.y:598
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_ROFF
			yyVAL.addr.Reg = int8(yyS[yypt-4].lval)
			yyVAL.addr.Scale = int8(yyS[yypt-1].lval & 0x1f)
			yyVAL.addr.Offset = yyS[yypt-1].lval | (1 << 16)
		}
	case 101:
		yyVAL.addr = yyS[yypt-0].addr
	case 102:
		yyVAL.addr = yyS[yypt-0].addr
	case 103:
		yyVAL.addr = yyS[yypt-0].addr
	case 104:
		//line a.y:612
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_CONST
			yyVAL.addr.Offset = yyS[yypt-0].lval
		}
	case 105:
		//line a.y:620
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_REG
			yyVAL.addr.Reg = int8(yyS[yypt-0].lval)
		}
	case 106:
		//line a.y:626
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_SP
			yyVAL.addr.Reg = REGSP
		}
	case 107:
		//line a.y:634
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_SHIFT
			yyVAL.addr.Offset = (yyS[yypt-3].lval << 16) | (yyS[yypt-0].lval << 10) | (0 << 22)
		}
	case 108:
		//line a.y:640
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_SHIFT
			yyVAL.addr.Offset = ((yyS[yypt-3].lval & 0x1F) << 16) | (yyS[yypt-0].lval << 10) | (1 << 22)
		}
	case 109:
		//line a.y:646
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_SHIFT
			yyVAL.addr.Offset = (yyS[yypt-3].lval << 16) | (yyS[yypt-0].lval << 10) | (2 << 22)
		}
	case 110:
		//line a.y:652
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_SHIFT
			yyVAL.addr.Offset = (yyS[yypt-3].lval << 16) | (yyS[yypt-0].lval << 10) | (3 << 22)
		}
	case 111:
		//line a.y:660
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_REG
			yyVAL.addr.Reg = int8(yyS[yypt-0].lval)
		}
	case 112:
		//line a.y:666
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_EXTREG
			yyVAL.addr.Reg = int8(yyS[yypt-1].lval)
			yyVAL.addr.Offset = (yyS[yypt-1].lval << 16) | (yyS[yypt-0].lval << 13)
		}
	case 113:
		//line a.y:673
		{
			if yyS[yypt-0].lval < 0 || yyS[yypt-0].lval > 4 {
				yyerror("shift value out of range")
			}
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_EXTREG
			yyVAL.addr.Reg = int8(yyS[yypt-4].lval)
			yyVAL.addr.Offset = (yyS[yypt-4].lval << 16) | (yyS[yypt-3].lval << 13) | (yyS[yypt-0].lval << 10)
		}
	case 114:
		//line a.y:685
		{
			yyVAL.lval = (3 << 8) | yyS[yypt-0].lval
		}
	case 115:
		//line a.y:689
		{
			yyVAL.lval = (yyS[yypt-0].lval << 8) | yyS[yypt-1].lval
		}
	case 116:
		//line a.y:695
		{
			if yyVAL.lval < 0 || yyVAL.lval >= 64 {
				yyerror("shift value out of range")
			}
			yyVAL.lval = yyS[yypt-0].lval & 0x3F
		}
	case 117:
		yyVAL.lval = yyS[yypt-0].lval
	case 118:
		//line a.y:705
		{
			if yyS[yypt-1].lval < 0 || yyS[yypt-1].lval >= NREG {
				print("register value out of range\n")
			}
			yyVAL.lval = yyS[yypt-1].lval
		}
	case 119:
		yyVAL.lval = yyS[yypt-0].lval
	case 120:
		//line a.y:715
		{
			yyVAL.lval = REGSP
		}
	case 121:
		//line a.y:721
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_SPR
			yyVAL.addr.Offset = yyS[yypt-0].lval
		}
	case 122:
		//line a.y:727
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = int16(yyS[yypt-3].lval)
			yyVAL.addr.Offset = yyS[yypt-1].lval
		}
	case 123:
		yyVAL.addr = yyS[yypt-0].addr
	case 124:
		yyVAL.addr = yyS[yypt-0].addr
	case 125:
		//line a.y:739
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_FREG
			yyVAL.addr.Reg = int8(yyS[yypt-0].lval)
		}
	case 126:
		//line a.y:745
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_FREG
			yyVAL.addr.Reg = int8(yyS[yypt-1].lval)
		}
	case 127:
		yyVAL.addr = yyS[yypt-0].addr
	case 128:
		yyVAL.addr = yyS[yypt-0].addr
	case 129:
		yyVAL.addr = yyS[yypt-0].addr
	case 130:
		//line a.y:756
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_VSET
			yyVAL.addr.Offset = yyS[yypt-0].lval
		}
	case 131:
		//line a.y:764
		{
			yyVAL.addr.Type = D_VLANE
			yyVAL.addr.Offset = yyS[yypt-1].lval
		}
	case 132:
		//line a.y:769
		{
			yyVAL.addr.Type = D_VLANE
			yyVAL.addr.Offset = yyS[yypt-1].lval
		}
	case 133:
		//line a.y:776
		{
			yyVAL.lval = yyS[yypt-1].lval
		}
	case 134:
		//line a.y:782
		{
			yyVAL.lval = 1 << byte(yyS[yypt-0].addr.Reg)
		}
	case 135:
		//line a.y:786
		{
			yyVAL.lval = 0
			for i := yyS[yypt-2].addr.Reg; i <= yyS[yypt-0].addr.Reg; i++ {
				yyVAL.lval |= 1 << byte(i)
			}
			for i := yyS[yypt-0].addr.Reg; i <= yyS[yypt-2].addr.Reg; i++ {
				yyVAL.lval |= 1 << byte(i)
			}
		}
	case 136:
		//line a.y:796
		{
			yyVAL.lval = (1 << byte(yyS[yypt-2].addr.Reg)) | yyS[yypt-0].lval
		}
	case 137:
		//line a.y:802
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_VREG
			yyVAL.addr.Reg = int8(yyS[yypt-0].lval)
			/* TO DO: slice */
		}
	case 138:
		//line a.y:808
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_VREG
			yyVAL.addr.Reg = int8(yyS[yypt-1].lval)
		}
	case 139:
		//line a.y:816
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_OREG
			yyVAL.addr.Name = int8(yyS[yypt-1].lval)
			yyVAL.addr.Sym = nil
			yyVAL.addr.Offset = yyS[yypt-3].lval
		}
	case 140:
		//line a.y:824
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_OREG
			yyVAL.addr.Name = int8(yyS[yypt-1].lval)
			yyVAL.addr.Sym = obj.Linklookup(asm.Ctxt, yyS[yypt-4].sym.Name, 0)
			yyVAL.addr.Offset = yyS[yypt-3].lval
		}
	case 141:
		//line a.y:832
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_OREG
			yyVAL.addr.Name = D_STATIC
			yyVAL.addr.Sym = obj.Linklookup(asm.Ctxt, yyS[yypt-6].sym.Name, 0)
			yyVAL.addr.Offset = yyS[yypt-3].lval
		}
	case 142:
		//line a.y:841
		{
			yyVAL.lval = 0
		}
	case 143:
		//line a.y:845
		{
			yyVAL.lval = yyS[yypt-0].lval
		}
	case 144:
		//line a.y:849
		{
			yyVAL.lval = -yyS[yypt-0].lval
		}
	case 145:
		yyVAL.lval = yyS[yypt-0].lval
	case 146:
		yyVAL.lval = yyS[yypt-0].lval
	case 147:
		yyVAL.lval = yyS[yypt-0].lval
	case 148:
		yyVAL.lval = yyS[yypt-0].lval
	case 149:
		//line a.y:861
		{
			yyVAL.lval = yyS[yypt-0].sym.Value
		}
	case 150:
		//line a.y:865
		{
			yyVAL.lval = -yyS[yypt-0].lval
		}
	case 151:
		//line a.y:869
		{
			yyVAL.lval = yyS[yypt-0].lval
		}
	case 152:
		//line a.y:873
		{
			yyVAL.lval = ^yyS[yypt-0].lval
		}
	case 153:
		//line a.y:877
		{
			yyVAL.lval = yyS[yypt-1].lval
		}
	case 154:
		yyVAL.lval = yyS[yypt-0].lval
	case 155:
		//line a.y:884
		{
			yyVAL.lval = yyS[yypt-2].lval + yyS[yypt-0].lval
		}
	case 156:
		//line a.y:888
		{
			yyVAL.lval = yyS[yypt-2].lval - yyS[yypt-0].lval
		}
	case 157:
		//line a.y:892
		{
			yyVAL.lval = yyS[yypt-2].lval * yyS[yypt-0].lval
		}
	case 158:
		//line a.y:896
		{
			yyVAL.lval = yyS[yypt-2].lval / yyS[yypt-0].lval
		}
	case 159:
		//line a.y:900
		{
			yyVAL.lval = yyS[yypt-2].lval % yyS[yypt-0].lval
		}
	case 160:
		//line a.y:904
		{
			yyVAL.lval = yyS[yypt-3].lval << uint(yyS[yypt-0].lval)
		}
	case 161:
		//line a.y:908
		{
			yyVAL.lval = yyS[yypt-3].lval >> uint(yyS[yypt-0].lval)
		}
	case 162:
		//line a.y:912
		{
			yyVAL.lval = yyS[yypt-2].lval & yyS[yypt-0].lval
		}
	case 163:
		//line a.y:916
		{
			yyVAL.lval = yyS[yypt-2].lval ^ yyS[yypt-0].lval
		}
	case 164:
		//line a.y:920
		{
			yyVAL.lval = yyS[yypt-2].lval | yyS[yypt-0].lval
		}
	}
	goto yystack /* stack new state and value */
}
