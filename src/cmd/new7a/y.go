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
	-2, 2,
	-1, 2,
	1, 4,
	-2, 0,
	-1, 17,
	85, 25,
	-2, 72,
	-1, 156,
	1, 4,
	-2, 0,
	-1, 235,
	94, 138,
	-2, 72,
	-1, 262,
	86, 123,
	-2, 108,
	-1, 263,
	86, 124,
	-2, 109,
}

const yyNprod = 169
const yyPrivate = 57344

var yyTokenNames []string
var yyStates []string

const yyLast = 823

var yyAct = []int{

	158, 395, 273, 136, 243, 152, 234, 187, 70, 343,
	145, 160, 320, 3, 72, 420, 75, 381, 380, 59,
	233, 232, 57, 394, 107, 109, 393, 97, 98, 99,
	121, 121, 67, 433, 418, 417, 398, 87, 100, 114,
	116, 73, 142, 72, 124, 147, 147, 369, 363, 69,
	72, 359, 358, 357, 356, 351, 149, 350, 138, 279,
	68, 399, 155, 285, 162, 90, 89, 120, 122, 101,
	153, 291, 66, 65, 171, 218, 209, 115, 117, 74,
	172, 123, 186, 137, 178, 179, 180, 185, 184, 183,
	168, 63, 131, 144, 146, 79, 277, 151, 195, 109,
	72, 63, 182, 143, 321, 60, 58, 432, 118, 121,
	154, 431, 430, 192, 429, 127, 129, 129, 210, 134,
	96, 173, 193, 199, 428, 426, 425, 424, 105, 213,
	214, 112, 113, 221, 423, 198, 400, 387, 386, 125,
	126, 385, 384, 379, 84, 83, 208, 378, 377, 78,
	148, 148, 150, 66, 65, 157, 159, 376, 235, 374,
	200, 373, 372, 371, 77, 370, 260, 367, 78, 215,
	247, 72, 66, 65, 90, 89, 64, 64, 178, 366,
	58, 58, 365, 64, 342, 282, 283, 284, 81, 78,
	287, 288, 191, 66, 65, 90, 89, 92, 91, 216,
	58, 71, 330, 109, 292, 301, 294, 94, 93, 246,
	242, 261, 241, 240, 239, 95, 238, 82, 306, 270,
	307, 56, 79, 86, 72, 237, 299, 295, 236, 231,
	85, 271, 142, 318, 319, 317, 230, 229, 228, 147,
	326, 289, 72, 72, 227, 225, 224, 322, 138, 325,
	223, 181, 331, 296, 297, 298, 222, 300, 220, 217,
	212, 211, 304, 207, 206, 344, 344, 344, 344, 205,
	308, 269, 204, 137, 203, 345, 346, 347, 142, 202,
	353, 201, 170, 169, 310, 161, 55, 324, 360, 54,
	327, 362, 78, 53, 361, 226, 66, 65, 90, 89,
	51, 52, 328, 329, 311, 312, 364, 313, 314, 315,
	316, 278, 419, 103, 92, 91, 302, 303, 244, 352,
	90, 89, 421, 305, 119, 375, 262, 80, 309, 383,
	84, 83, 66, 65, 219, 388, 272, 427, 382, 235,
	84, 83, 163, 164, 148, 165, 189, 190, 281, 392,
	128, 368, 332, 333, 334, 335, 336, 397, 338, 339,
	340, 341, 293, 176, 130, 130, 244, 109, 275, 274,
	276, 64, 66, 65, 81, 404, 405, 275, 274, 276,
	142, 348, 407, 412, 81, 72, 286, 415, 132, 267,
	266, 402, 391, 92, 91, 265, 138, 337, 84, 177,
	174, 323, 290, 82, 268, 166, 167, 264, 8, 354,
	156, 95, 355, 82, 2, 401, 85, 403, 78, 86,
	1, 137, 66, 65, 141, 245, 85, 263, 438, 66,
	65, 66, 65, 443, 76, 84, 83, 416, 84, 83,
	389, 390, 81, 88, 194, 413, 188, 444, 189, 190,
	422, 445, 446, 139, 408, 62, 409, 410, 411, 84,
	83, 275, 274, 276, 302, 61, 140, 176, 175, 95,
	0, 82, 0, 434, 0, 436, 437, 86, 406, 81,
	0, 442, 81, 78, 85, 0, 0, 66, 65, 249,
	250, 251, 252, 253, 0, 244, 251, 252, 253, 0,
	0, 102, 0, 81, 0, 0, 110, 0, 82, 440,
	441, 82, 0, 108, 111, 0, 63, 111, 0, 396,
	396, 85, 0, 104, 85, 106, 0, 0, 0, 0,
	435, 0, 82, 0, 439, 244, 244, 63, 111, 9,
	133, 0, 135, 0, 0, 85, 0, 84, 83, 0,
	414, 10, 11, 12, 13, 15, 16, 17, 18, 19,
	39, 27, 29, 30, 31, 50, 38, 0, 32, 35,
	42, 36, 37, 43, 44, 45, 26, 28, 20, 21,
	22, 23, 24, 41, 48, 25, 49, 14, 46, 47,
	0, 81, 84, 83, 0, 0, 66, 65, 0, 0,
	0, 84, 83, 0, 40, 0, 84, 83, 0, 0,
	84, 83, 33, 34, 6, 84, 83, 4, 0, 5,
	82, 0, 7, 0, 84, 83, 111, 0, 0, 0,
	0, 0, 0, 85, 0, 0, 81, 256, 254, 255,
	249, 250, 251, 252, 253, 81, 0, 0, 0, 0,
	81, 0, 0, 0, 81, 0, 0, 0, 0, 81,
	0, 0, 0, 110, 0, 82, 0, 0, 81, 0,
	0, 111, 95, 0, 82, 278, 0, 0, 85, 82,
	86, 95, 0, 82, 0, 111, 196, 85, 82, 111,
	0, 0, 85, 0, 197, 0, 85, 82, 0, 0,
	0, 85, 0, 111, 0, 0, 0, 0, 0, 0,
	85, 258, 257, 256, 254, 255, 249, 250, 251, 252,
	253, 258, 257, 256, 254, 255, 249, 250, 251, 252,
	253, 258, 257, 256, 254, 255, 249, 250, 251, 252,
	253, 258, 257, 256, 254, 255, 249, 250, 251, 252,
	253, 257, 256, 254, 255, 249, 250, 251, 252, 253,
	254, 255, 249, 250, 251, 252, 253, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 349, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 280, 0, 0, 0,
	0, 0, 259, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 248,
}
var yyPact = []int{

	-1000, -1000, 537, -1000, 217, 209, 204, -1000, 201, 136,
	20, 14, 14, 135, 4, 20, 20, 20, 14, 364,
	245, 245, 4, 245, 426, 4, 4, 95, 238, 601,
	601, 364, 20, 4, 4, 260, 5, 5, 245, 260,
	245, 331, 135, 364, 429, 450, 4, 364, -18, 135,
	20, -1000, 615, 615, -1000, -1000, -1000, -1000, 20, 199,
	-1000, -1000, -1000, 615, 335, -1000, 2, 197, 196, -1000,
	-1000, -1000, -14, -1000, -1000, -1000, -1000, -1000, -1000, 389,
	-1000, -1000, -1000, 615, 615, 615, 538, 1, -1000, -1000,
	0, -1000, -1, -1000, -6, 439, 106, 606, 583, 135,
	195, 193, 188, -1000, 186, 183, 178, 177, 601, -12,
	337, 615, 175, 174, -1000, -1000, -1000, 20, 20, 114,
	173, -13, 322, 172, 8, 170, 164, 160, 159, -1000,
	-1000, 285, 158, 152, 151, 150, 143, -1000, -70, -1000,
	-71, 252, -14, 142, 139, -1000, 130, 128, -1000, 127,
	-1000, 126, 124, 371, 123, -1000, 537, 737, -1000, 727,
	-1000, 373, -1000, 400, 387, 382, 381, 397, 615, 364,
	135, 314, -14, -1000, 9, -1000, -1000, 597, -1000, -1000,
	-1000, -30, 717, 274, 615, 615, 615, -25, 378, 615,
	615, 364, 395, -1000, -1000, -17, 439, 538, -1000, -1000,
	-1000, 371, 583, 364, 364, 364, 14, 364, 119, 259,
	-1000, 4, 364, -1000, -1000, -1000, -1000, 450, 323, 615,
	364, -1000, 4, 135, 260, 260, 233, 260, 260, 260,
	260, 331, 615, 615, -82, 94, 274, 364, 450, 615,
	364, 135, 135, 116, -1000, -1000, -18, -1000, -1000, 615,
	615, 615, 615, 615, 390, 350, 615, 615, 615, -1000,
	98, -1000, -1000, -1000, 615, 615, 615, 615, 374, 707,
	-1000, -1000, -32, -34, -1000, -1000, -1000, 592, -1000, 321,
	-1000, -35, -36, -37, -38, 323, 337, -1000, -1000, -1000,
	615, 407, -25, -41, 20, -1000, -1000, 96, 93, 81,
	-1000, 364, -42, 79, 77, -1000, 76, 75, -1000, -1000,
	-1000, -1000, 73, 20, 71, 62, 61, 57, -74, -75,
	-1000, 252, 252, 56, 55, -1000, 52, -1000, 51, -1000,
	371, -1000, 485, 485, -1000, -1000, -1000, 615, 615, 753,
	631, 746, 364, -1000, -1000, -1000, -1000, -1000, 615, -1000,
	-64, -1000, -1000, -67, 538, 274, -1000, -1000, -1000, -1000,
	-53, -27, 50, -1000, -1000, 364, 583, 364, -1000, -1000,
	371, 371, 4, 8, 260, -1000, 260, 260, 260, 331,
	-1000, -1000, -1000, -1000, 135, 274, 615, 364, -54, 480,
	480, -1000, -1000, -1000, -1000, -55, 241, -77, -1000, 267,
	364, 48, -1000, 41, 40, 39, 327, -1000, -1000, 38,
	28, 26, -1000, -1000, 25, 21, -1000, -1000, -1000, -1000,
	-1000, -56, -1000, 364, 4, 364, 364, 615, 4, 260,
	260, 364, 615, -1000, -1000, 20, -1000, -1000, -1000, 20,
	20, -1000, -1000, -1000, -1000, -1000, -1000,
}
var yyPgo = []int{

	0, 0, 102, 2, 7, 164, 4, 9, 1, 466,
	6, 60, 24, 49, 5, 79, 16, 465, 327, 350,
	455, 453, 3, 105, 8, 37, 41, 444, 443, 19,
	434, 501, 10, 420, 414, 13, 410, 408, 11,
}
var yyR1 = []int{

	0, 33, 34, 33, 35, 36, 35, 35, 35, 35,
	35, 35, 35, 37, 37, 37, 37, 37, 37, 37,
	37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
	37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
	37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
	37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
	37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
	37, 31, 38, 38, 32, 32, 12, 12, 24, 24,
	24, 24, 24, 18, 18, 11, 11, 11, 11, 11,
	11, 11, 11, 27, 27, 26, 26, 26, 28, 28,
	28, 28, 28, 28, 29, 29, 29, 23, 13, 13,
	14, 17, 17, 17, 17, 20, 20, 20, 8, 8,
	7, 5, 5, 6, 6, 30, 30, 19, 19, 15,
	15, 22, 22, 22, 22, 21, 21, 9, 10, 10,
	10, 16, 16, 25, 25, 25, 4, 4, 4, 3,
	3, 3, 1, 1, 1, 1, 1, 1, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2,
}
var yyR2 = []int{

	0, 0, 0, 3, 0, 0, 4, 4, 4, 2,
	1, 2, 2, 2, 6, 5, 4, 4, 4, 4,
	7, 3, 3, 3, 3, 1, 5, 4, 4, 8,
	6, 6, 9, 4, 5, 8, 8, 2, 2, 2,
	3, 3, 3, 3, 4, 6, 8, 6, 4, 3,
	4, 4, 4, 4, 6, 5, 9, 9, 8, 4,
	6, 6, 8, 2, 4, 4, 2, 6, 4, 4,
	2, 1, 0, 2, 7, 1, 4, 2, 2, 2,
	4, 2, 1, 2, 3, 1, 1, 1, 1, 1,
	1, 1, 1, 3, 1, 1, 4, 1, 3, 4,
	5, 5, 6, 6, 1, 1, 1, 2, 1, 1,
	5, 4, 4, 4, 4, 1, 2, 5, 1, 2,
	1, 1, 4, 1, 1, 1, 4, 1, 1, 1,
	4, 1, 1, 1, 1, 4, 4, 3, 1, 3,
	3, 1, 4, 4, 5, 7, 0, 2, 2, 1,
	1, 1, 1, 1, 2, 2, 2, 3, 1, 3,
	3, 3, 3, 3, 4, 4, 3, 3, 3,
}
var yyChk = []int{

	-1000, -33, -34, -35, 80, 82, 77, 85, -37, 2,
	14, 15, 16, 17, 50, 18, 19, 20, 21, 22,
	41, 42, 43, 44, 45, 48, 39, 24, 40, 25,
	26, 27, 31, 75, 76, 32, 34, 35, 29, 23,
	67, 46, 33, 36, 37, 38, 51, 52, 47, 49,
	28, 83, 84, 84, 85, 85, 85, -38, 86, -29,
	-23, -17, -20, 87, -5, 59, 58, -29, -11, -13,
	-24, 66, -1, -26, -15, -16, -30, -5, 54, 87,
	-18, 53, 82, 10, 9, 95, 88, -25, -28, 61,
	60, 63, 62, 73, 72, 80, -23, -38, -38, -38,
	-29, -13, -31, 68, -31, -23, -31, -12, 87, -1,
	80, 88, -23, -23, -38, -13, -38, -13, -15, 86,
	-25, -1, -25, -13, -38, -23, -23, -15, -19, -15,
	-18, 87, -19, -31, -15, -31, -22, -26, -16, -21,
	-9, 93, -1, -11, -13, -32, -13, -1, -23, -32,
	-23, -13, -14, 88, -11, -38, -36, -2, -1, -2,
	-38, 86, -1, 7, 8, 10, 70, 71, 88, 86,
	86, 88, -1, -26, 11, 79, 78, 10, -1, -1,
	-1, -5, -2, 88, 88, 88, 88, -4, 7, 9,
	10, 86, 7, -12, -27, -1, 80, 88, -25, -12,
	-11, 86, 86, 86, 86, 86, 86, 86, -25, 88,
	-4, 86, 86, -38, -38, -13, -15, 86, 88, 12,
	86, -24, 86, 86, 86, 86, 10, 86, 86, 86,
	86, 86, 91, 91, -10, -16, 86, 86, 86, 86,
	86, 86, 86, -6, -5, 54, 86, -35, 85, 9,
	10, 11, 12, 13, 7, 8, 6, 5, 4, 85,
	-6, -13, -5, 54, 7, 8, 8, 8, 7, -2,
	-13, -11, -5, -3, 55, 54, 56, 87, 78, 89,
	89, -5, -1, -1, -1, 88, 8, -1, -1, -13,
	7, 88, -4, -5, -6, -12, -13, -13, -13, -29,
	-13, 86, 57, -23, -13, -23, -1, -1, -13, -23,
	-11, -15, -15, -15, -15, -15, -15, -22, -1, -1,
	94, 10, -38, -5, -13, -32, -1, -13, -11, -11,
	86, -14, -2, -2, -2, -2, -2, 7, 8, -2,
	-2, -2, 86, -7, -1, -7, -7, -7, 7, 89,
	89, 89, -26, -1, 88, 91, 89, 89, 89, 89,
	-3, -4, -1, 89, -38, 86, 86, 86, -13, 89,
	86, 86, 86, 86, 86, -38, 86, 86, 86, 86,
	92, 92, -16, -10, 86, 86, 86, 86, -6, -2,
	-2, -13, -1, 90, 90, -8, -5, -8, 89, 88,
	86, -13, -12, -13, -6, -6, -23, -24, -15, -15,
	-15, -15, -22, -11, -5, -1, -13, 89, 89, 71,
	92, 55, -13, 86, 86, 86, 86, 10, 86, 86,
	86, 86, 86, 89, -13, -23, -13, -13, -1, -23,
	-15, -15, -13, -1, -38, -38, -38,
}
var yyDef = []int{

	1, -2, -2, 3, 0, 0, 0, 10, 0, 0,
	72, 0, 0, 0, 0, 72, 72, -2, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 72, 72, 0,
	0, 0, 72, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	72, 5, 0, 0, 9, 11, 12, 13, 72, 0,
	104, 105, 106, 0, 115, 121, 0, 0, 0, 85,
	86, 87, 88, 89, 90, 91, 92, 108, 109, 0,
	82, 152, 153, 0, 0, 0, 0, 95, 97, 129,
	0, 141, 0, 125, 0, 146, 0, 0, 0, 0,
	0, 0, 0, 71, 0, 0, 0, 0, 0, 0,
	146, 0, 0, 0, 37, 38, 39, 72, 72, 72,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 127,
	128, 0, 0, 0, 0, 0, 0, 131, 132, 133,
	134, 0, 0, 0, 0, 63, 0, 0, 75, 0,
	66, 0, 0, 0, 0, 70, -2, 0, 158, 0,
	73, 0, 107, 0, 0, 0, 0, 116, 0, 0,
	0, 0, 78, 79, 0, 81, 83, 0, 154, 155,
	156, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 21, 22, 0, 146, 0, 94, 23,
	24, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	77, 0, 0, 40, 41, 42, 43, 0, 0, 0,
	0, 49, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, -2, 0, 0, 0, 0,
	0, 0, 0, 0, 123, 124, 0, 6, 7, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
	0, 16, -2, -2, 0, 0, 0, 0, 0, 0,
	17, 18, 0, 0, 149, 150, 151, 0, 84, 98,
	157, 0, 0, 0, 0, 0, 146, 147, 148, 19,
	0, 0, 77, 0, 72, 27, 28, 0, 0, 0,
	33, 0, 0, 0, 0, 44, 0, 0, 48, 50,
	51, 52, 53, 72, 0, 0, 0, 59, 0, 0,
	137, 0, 0, 0, 0, 64, 0, 65, 0, 68,
	0, 69, 159, 160, 161, 162, 163, 0, 0, 166,
	167, 168, 15, 111, 120, 112, 113, 114, 0, 122,
	99, 143, 80, 0, 0, 0, 96, 130, 142, 126,
	0, 0, 0, 93, 26, 0, 0, 0, 34, 76,
	0, 0, 0, 0, 0, 55, 0, 0, 0, 0,
	135, 136, 139, 140, 0, 0, 0, 0, 0, 164,
	165, 14, 117, 100, 101, 0, 118, 0, 144, 0,
	0, 30, 31, 0, 0, 0, 45, 47, 54, 0,
	0, 0, 60, 61, 0, 0, 67, 110, 102, 119,
	103, 0, 20, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 145, 29, 72, 35, 36, 46, 72,
	72, 58, 62, 74, 32, 56, 57,
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

	case 2:
		//line a.y:47
		{
			stmtline = asm.Lineno
		}
	case 5:
		//line a.y:54
		{
			yyS[yypt-1].sym = asm.LabelLookup(yyS[yypt-1].sym)
			if yyS[yypt-1].sym.Type == LLAB && yyS[yypt-1].sym.Value != int64(asm.PC) {
				yyerror("redeclaration of %s", yyS[yypt-1].sym.Labelname)
			}
			yyS[yypt-1].sym.Type = LLAB
			yyS[yypt-1].sym.Value = int64(asm.PC)
		}
	case 7:
		//line a.y:64
		{
			yyS[yypt-3].sym.Type = LVAR
			yyS[yypt-3].sym.Value = yyS[yypt-1].lval
		}
	case 8:
		//line a.y:69
		{
			if yyS[yypt-3].sym.Value != yyS[yypt-1].lval {
				yyerror("redeclaration of %s", yyS[yypt-3].sym.Name)
			}
			yyS[yypt-3].sym.Value = yyS[yypt-1].lval
		}
	case 9:
		//line a.y:76
		{
			nosched = int(yyS[yypt-1].lval)
		}
	case 13:
		//line a.y:88
		{
			outcode(int(yyS[yypt-1].lval), &nullgen, NREG, &nullgen)
		}
	case 14:
		//line a.y:95
		{
			outcode(int(yyS[yypt-5].lval), &yyS[yypt-4].addr, int(yyS[yypt-2].lval), &yyS[yypt-0].addr)
		}
	case 15:
		//line a.y:99
		{
			outcode(int(yyS[yypt-4].lval), &yyS[yypt-3].addr, int(yyS[yypt-1].lval), &nullgen)
		}
	case 16:
		//line a.y:103
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 17:
		//line a.y:110
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 18:
		//line a.y:117
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 19:
		//line a.y:124
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 20:
		//line a.y:128
		{
			var a obj.Addr
			a = nullgen
			a.Type = D_CONST
			a.Offset = yyS[yypt-2].lval
			outgcode(int(yyS[yypt-6].lval), &yyS[yypt-5].addr, NREG, &a, &yyS[yypt-0].addr)
		}
	case 21:
		//line a.y:139
		{
			outcode(int(yyS[yypt-2].lval), &nullgen, NREG, &yyS[yypt-0].addr)
		}
	case 22:
		//line a.y:143
		{
			outcode(int(yyS[yypt-2].lval), &nullgen, NREG, &yyS[yypt-0].addr)
		}
	case 23:
		//line a.y:150
		{
			outcode(int(yyS[yypt-2].lval), &nullgen, NREG, &yyS[yypt-0].addr)
		}
	case 24:
		//line a.y:157
		{
			outcode(int(yyS[yypt-2].lval), &nullgen, NREG, &yyS[yypt-0].addr)
		}
	case 25:
		//line a.y:161
		{
			outcode(int(yyS[yypt-0].lval), &nullgen, NREG, &nullgen)
		}
	case 26:
		//line a.y:168
		{
			outcode(int(yyS[yypt-4].lval), &yyS[yypt-3].addr, int(yyS[yypt-1].lval), &nullgen)
		}
	case 27:
		//line a.y:175
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 28:
		//line a.y:182
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 29:
		//line a.y:189
		{
			outgcode(int(yyS[yypt-7].lval), &yyS[yypt-6].addr, int(yyS[yypt-2].addr.Reg), &yyS[yypt-4].addr, &yyS[yypt-0].addr)
		}
	case 30:
		//line a.y:193
		{
			outcode(int(yyS[yypt-5].lval), &yyS[yypt-4].addr, int(yyS[yypt-2].addr.Reg), &yyS[yypt-0].addr)
		}
	case 31:
		//line a.y:200
		{
			outcode(int(yyS[yypt-5].lval), &yyS[yypt-4].addr, int(yyS[yypt-2].addr.Reg), &yyS[yypt-0].addr)
		}
	case 32:
		//line a.y:207
		{
			outgcode(int(yyS[yypt-8].lval), &yyS[yypt-7].addr, int(yyS[yypt-3].addr.Reg), &yyS[yypt-5].addr, &yyS[yypt-1].addr)
		}
	case 33:
		//line a.y:214
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 34:
		//line a.y:218
		{
			outcode(int(yyS[yypt-4].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 35:
		//line a.y:225
		{
			outgcode(int(yyS[yypt-7].lval), &yyS[yypt-6].addr, int(yyS[yypt-2].lval), &yyS[yypt-4].addr, &yyS[yypt-0].addr)
		}
	case 36:
		//line a.y:232
		{
			outgcode(int(yyS[yypt-7].lval), &yyS[yypt-6].addr, int(yyS[yypt-2].lval), &yyS[yypt-4].addr, &yyS[yypt-0].addr)
		}
	case 37:
		//line a.y:239
		{
			outcode(int(yyS[yypt-1].lval), &nullgen, NREG, &nullgen)
		}
	case 38:
		//line a.y:243
		{
			outcode(int(yyS[yypt-1].lval), &nullgen, NREG, &yyS[yypt-0].addr)
		}
	case 39:
		//line a.y:250
		{
			outcode(int(yyS[yypt-1].lval), &nullgen, NREG, &nullgen)
		}
	case 40:
		//line a.y:254
		{
			outcode(int(yyS[yypt-2].lval), &yyS[yypt-1].addr, NREG, &nullgen)
		}
	case 41:
		//line a.y:258
		{
			outcode(int(yyS[yypt-2].lval), &yyS[yypt-1].addr, NREG, &nullgen)
		}
	case 42:
		//line a.y:262
		{
			outcode(int(yyS[yypt-2].lval), &nullgen, NREG, &yyS[yypt-0].addr)
		}
	case 43:
		//line a.y:266
		{
			outcode(int(yyS[yypt-2].lval), &nullgen, NREG, &yyS[yypt-0].addr)
		}
	case 44:
		//line a.y:273
		{
			asm.Settext(yyS[yypt-2].addr.Sym)
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 45:
		//line a.y:278
		{
			asm.Settext(yyS[yypt-4].addr.Sym)
			yyS[yypt-0].addr.Offset &= 0xffffffff
			yyS[yypt-0].addr.Offset |= -obj.ArgsSizeUnknown << 32
			outcode(int(yyS[yypt-5].lval), &yyS[yypt-4].addr, int(yyS[yypt-2].lval), &yyS[yypt-0].addr)
		}
	case 46:
		//line a.y:285
		{
			asm.Settext(yyS[yypt-6].addr.Sym)
			yyS[yypt-2].addr.Offset &= 0xffffffff
			yyS[yypt-2].addr.Offset |= (yyS[yypt-0].lval & 0xffffffff) << 32
			outcode(int(yyS[yypt-7].lval), &yyS[yypt-6].addr, int(yyS[yypt-4].lval), &yyS[yypt-2].addr)
		}
	case 47:
		//line a.y:295
		{
			outcode(int(yyS[yypt-5].lval), &yyS[yypt-4].addr, int(yyS[yypt-2].lval), &yyS[yypt-0].addr)
		}
	case 48:
		//line a.y:302
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 49:
		//line a.y:309
		{
			outcode(int(yyS[yypt-2].lval), &nullgen, NREG, &yyS[yypt-0].addr)
		}
	case 50:
		//line a.y:316
		{
			if yyS[yypt-2].addr.Type != D_CONST || yyS[yypt-0].addr.Type != D_CONST {
				yyerror("arguments to PCDATA must be integer constants")
			}
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 51:
		//line a.y:326
		{
			if yyS[yypt-2].addr.Type != D_CONST {
				yyerror("index for FUNCDATA must be integer constant")
			}
			if yyS[yypt-0].addr.Type != D_EXTERN && yyS[yypt-0].addr.Type != D_STATIC && yyS[yypt-0].addr.Type != D_OREG {
				yyerror("value for FUNCDATA must be symbol reference")
			}
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 52:
		//line a.y:339
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 53:
		//line a.y:346
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 54:
		//line a.y:350
		{
			outcode(int(yyS[yypt-5].lval), &yyS[yypt-4].addr, int(yyS[yypt-2].addr.Reg), &yyS[yypt-0].addr)
		}
	case 55:
		//line a.y:357
		{
			outcode(int(yyS[yypt-4].lval), &yyS[yypt-3].addr, int(yyS[yypt-1].addr.Reg), &nullgen)
		}
	case 56:
		//line a.y:364
		{
			outgcode(int(yyS[yypt-8].lval), &yyS[yypt-7].addr, int(yyS[yypt-3].addr.Reg), &yyS[yypt-5].addr, &yyS[yypt-1].addr)
		}
	case 57:
		//line a.y:371
		{
			outgcode(int(yyS[yypt-8].lval), &yyS[yypt-7].addr, int(yyS[yypt-5].addr.Reg), &yyS[yypt-3].addr, &yyS[yypt-1].addr)
		}
	case 58:
		//line a.y:378
		{
			outgcode(int(yyS[yypt-7].lval), &yyS[yypt-6].addr, int(yyS[yypt-2].addr.Reg), &yyS[yypt-4].addr, &yyS[yypt-0].addr)
		}
	case 59:
		//line a.y:385
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 60:
		//line a.y:389
		{
			outcode(int(yyS[yypt-5].lval), &yyS[yypt-4].addr, int(yyS[yypt-2].addr.Reg), &yyS[yypt-0].addr)
		}
	case 61:
		//line a.y:396
		{
			outcode(int(yyS[yypt-5].lval), &yyS[yypt-4].addr, int(yyS[yypt-2].lval), &yyS[yypt-0].addr)
		}
	case 62:
		//line a.y:403
		{
			outgcode(int(yyS[yypt-7].lval), &yyS[yypt-6].addr, int(yyS[yypt-2].lval), &yyS[yypt-4].addr, &yyS[yypt-0].addr)
		}
	case 63:
		//line a.y:410
		{
			outcode(int(yyS[yypt-1].lval), &yyS[yypt-0].addr, NREG, &nullgen)
		}
	case 64:
		//line a.y:414
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-0].addr, int(yyS[yypt-2].addr.Reg), &nullgen)
		}
	case 65:
		//line a.y:418
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 66:
		//line a.y:425
		{
			outcode(int(yyS[yypt-1].lval), &yyS[yypt-0].addr, NREG, &nullgen)
		}
	case 67:
		//line a.y:432
		{
			outtcode(int(yyS[yypt-5].lval), &yyS[yypt-4].addr, &yyS[yypt-2].addr, &yyS[yypt-0].addr)
		}
	case 68:
		//line a.y:439
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 69:
		//line a.y:446
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 70:
		//line a.y:453
		{
			outcode(int(yyS[yypt-1].lval), &nullgen, NREG, &nullgen)
		}
	case 71:
		//line a.y:459
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_COND
			yyVAL.addr.Reg = int8(yyS[yypt-0].lval)
		}
	case 74:
		//line a.y:470
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_CONST
			yyVAL.addr.Offset = int64(SYSARG4(int(yyS[yypt-6].lval), int(yyS[yypt-4].lval), int(yyS[yypt-2].lval), int(yyS[yypt-0].lval)))
		}
	case 75:
		yyVAL.addr = yyS[yypt-0].addr
	case 76:
		//line a.y:479
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_BRANCH
			yyVAL.addr.Offset = yyS[yypt-3].lval + int64(asm.PC)
		}
	case 77:
		//line a.y:485
		{
			yyS[yypt-1].sym = asm.LabelLookup(yyS[yypt-1].sym)
			yyVAL.addr = nullgen
			if asm.Pass == 2 && yyS[yypt-1].sym.Type != LLAB {
				yyerror("undefined label: %s", yyS[yypt-1].sym.Labelname)
			}
			yyVAL.addr.Type = D_BRANCH
			yyVAL.addr.Offset = yyS[yypt-1].sym.Value + yyS[yypt-0].lval
		}
	case 78:
		//line a.y:496
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_CONST
			yyVAL.addr.Offset = yyS[yypt-0].lval
		}
	case 79:
		//line a.y:502
		{
			yyVAL.addr = yyS[yypt-0].addr
			yyVAL.addr.Type = D_CONST
		}
	case 80:
		//line a.y:507
		{
			yyVAL.addr = yyS[yypt-0].addr
			yyVAL.addr.Type = D_OCONST
		}
	case 81:
		//line a.y:512
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_SCONST
			yyVAL.addr.U.Sval = yyS[yypt-0].sval
		}
	case 82:
		yyVAL.addr = yyS[yypt-0].addr
	case 83:
		//line a.y:521
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_FCONST
			yyVAL.addr.U.Dval = yyS[yypt-0].dval
		}
	case 84:
		//line a.y:527
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_FCONST
			yyVAL.addr.U.Dval = -yyS[yypt-0].dval
		}
	case 85:
		yyVAL.addr = yyS[yypt-0].addr
	case 86:
		yyVAL.addr = yyS[yypt-0].addr
	case 87:
		//line a.y:537
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_SPR
			yyVAL.addr.Offset = yyS[yypt-0].lval
		}
	case 88:
		//line a.y:543
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_OREG
			yyVAL.addr.Offset = yyS[yypt-0].lval
		}
	case 89:
		yyVAL.addr = yyS[yypt-0].addr
	case 90:
		yyVAL.addr = yyS[yypt-0].addr
	case 91:
		yyVAL.addr = yyS[yypt-0].addr
	case 92:
		yyVAL.addr = yyS[yypt-0].addr
	case 93:
		//line a.y:555
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_OREG
			yyVAL.addr.Reg = int8(yyS[yypt-1].lval)
			yyVAL.addr.Offset = 0
		}
	case 94:
		//line a.y:562
		{
			yyVAL.addr = yyS[yypt-0].addr
			if yyS[yypt-0].addr.Name != D_EXTERN && yyS[yypt-0].addr.Name != D_STATIC {
			}
		}
	case 95:
		yyVAL.addr = yyS[yypt-0].addr
	case 96:
		//line a.y:571
		{
			yyVAL.addr = yyS[yypt-3].addr
			yyVAL.addr.Type = D_OREG
			yyVAL.addr.Reg = int8(yyS[yypt-1].lval)
		}
	case 97:
		yyVAL.addr = yyS[yypt-0].addr
	case 98:
		//line a.y:580
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_OREG
			yyVAL.addr.Reg = int8(yyS[yypt-1].lval)
			yyVAL.addr.Offset = 0
		}
	case 99:
		//line a.y:587
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_OREG
			yyVAL.addr.Reg = int8(yyS[yypt-1].lval)
			yyVAL.addr.Offset = yyS[yypt-3].lval
		}
	case 100:
		//line a.y:594
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_XPRE
			yyVAL.addr.Reg = int8(yyS[yypt-2].lval)
			yyVAL.addr.Offset = yyS[yypt-4].lval
		}
	case 101:
		//line a.y:601
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_XPOST
			yyVAL.addr.Reg = int8(yyS[yypt-3].lval)
			yyVAL.addr.Offset = yyS[yypt-1].lval
		}
	case 102:
		//line a.y:608
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_ROFF
			yyVAL.addr.Reg = int8(yyS[yypt-4].lval)
			yyVAL.addr.Scale = int8(yyS[yypt-1].lval & 0x1f)
			yyVAL.addr.Offset = yyS[yypt-1].lval
		}
	case 103:
		//line a.y:616
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_ROFF
			yyVAL.addr.Reg = int8(yyS[yypt-4].lval)
			yyVAL.addr.Scale = int8(yyS[yypt-1].lval & 0x1f)
			yyVAL.addr.Offset = yyS[yypt-1].lval | (1 << 16)
		}
	case 104:
		yyVAL.addr = yyS[yypt-0].addr
	case 105:
		yyVAL.addr = yyS[yypt-0].addr
	case 106:
		yyVAL.addr = yyS[yypt-0].addr
	case 107:
		//line a.y:630
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_CONST
			yyVAL.addr.Offset = yyS[yypt-0].lval
		}
	case 108:
		//line a.y:638
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_REG
			yyVAL.addr.Reg = int8(yyS[yypt-0].lval)
		}
	case 109:
		//line a.y:644
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_SP
			yyVAL.addr.Reg = REGSP
		}
	case 110:
		//line a.y:652
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_PAIR
			yyVAL.addr.Reg = int8(yyS[yypt-3].lval)
			yyVAL.addr.Offset = yyS[yypt-1].lval
		}
	case 111:
		//line a.y:661
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_SHIFT
			yyVAL.addr.Offset = (yyS[yypt-3].lval << 16) | (yyS[yypt-0].lval << 10) | (0 << 22)
		}
	case 112:
		//line a.y:667
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_SHIFT
			yyVAL.addr.Offset = ((yyS[yypt-3].lval & 0x1F) << 16) | (yyS[yypt-0].lval << 10) | (1 << 22)
		}
	case 113:
		//line a.y:673
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_SHIFT
			yyVAL.addr.Offset = (yyS[yypt-3].lval << 16) | (yyS[yypt-0].lval << 10) | (2 << 22)
		}
	case 114:
		//line a.y:679
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_SHIFT
			yyVAL.addr.Offset = (yyS[yypt-3].lval << 16) | (yyS[yypt-0].lval << 10) | (3 << 22)
		}
	case 115:
		//line a.y:687
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_REG
			yyVAL.addr.Reg = int8(yyS[yypt-0].lval)
		}
	case 116:
		//line a.y:693
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_EXTREG
			yyVAL.addr.Reg = int8(yyS[yypt-1].lval)
			yyVAL.addr.Offset = (yyS[yypt-1].lval << 16) | (yyS[yypt-0].lval << 13)
		}
	case 117:
		//line a.y:700
		{
			if yyS[yypt-0].lval < 0 || yyS[yypt-0].lval > 4 {
				yyerror("shift value out of range")
			}
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_EXTREG
			yyVAL.addr.Reg = int8(yyS[yypt-4].lval)
			yyVAL.addr.Offset = (yyS[yypt-4].lval << 16) | (yyS[yypt-3].lval << 13) | (yyS[yypt-0].lval << 10)
		}
	case 118:
		//line a.y:712
		{
			yyVAL.lval = (3 << 8) | yyS[yypt-0].lval
		}
	case 119:
		//line a.y:716
		{
			yyVAL.lval = (yyS[yypt-0].lval << 8) | yyS[yypt-1].lval
		}
	case 120:
		//line a.y:722
		{
			if yyVAL.lval < 0 || yyVAL.lval >= 64 {
				yyerror("shift value out of range")
			}
			yyVAL.lval = yyS[yypt-0].lval & 0x3F
		}
	case 121:
		yyVAL.lval = yyS[yypt-0].lval
	case 122:
		//line a.y:732
		{
			if yyS[yypt-1].lval < 0 || yyS[yypt-1].lval >= NREG {
				print("register value out of range\n")
			}
			yyVAL.lval = yyS[yypt-1].lval
		}
	case 123:
		yyVAL.lval = yyS[yypt-0].lval
	case 124:
		//line a.y:742
		{
			yyVAL.lval = REGSP
		}
	case 125:
		//line a.y:748
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_SPR
			yyVAL.addr.Offset = yyS[yypt-0].lval
		}
	case 126:
		//line a.y:754
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = int16(yyS[yypt-3].lval)
			yyVAL.addr.Offset = yyS[yypt-1].lval
		}
	case 127:
		yyVAL.addr = yyS[yypt-0].addr
	case 128:
		yyVAL.addr = yyS[yypt-0].addr
	case 129:
		//line a.y:766
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_FREG
			yyVAL.addr.Reg = int8(yyS[yypt-0].lval)
		}
	case 130:
		//line a.y:772
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_FREG
			yyVAL.addr.Reg = int8(yyS[yypt-1].lval)
		}
	case 131:
		yyVAL.addr = yyS[yypt-0].addr
	case 132:
		yyVAL.addr = yyS[yypt-0].addr
	case 133:
		yyVAL.addr = yyS[yypt-0].addr
	case 134:
		//line a.y:783
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_VSET
			yyVAL.addr.Offset = yyS[yypt-0].lval
		}
	case 135:
		//line a.y:791
		{
			yyVAL.addr.Type = D_VLANE
			yyVAL.addr.Offset = yyS[yypt-1].lval
		}
	case 136:
		//line a.y:796
		{
			yyVAL.addr.Type = D_VLANE
			yyVAL.addr.Offset = yyS[yypt-1].lval
		}
	case 137:
		//line a.y:803
		{
			yyVAL.lval = yyS[yypt-1].lval
		}
	case 138:
		//line a.y:809
		{
			yyVAL.lval = 1 << byte(yyS[yypt-0].addr.Reg)
		}
	case 139:
		//line a.y:813
		{
			yyVAL.lval = 0
			for i := yyS[yypt-2].addr.Reg; i <= yyS[yypt-0].addr.Reg; i++ {
				yyVAL.lval |= 1 << byte(i)
			}
			for i := yyS[yypt-0].addr.Reg; i <= yyS[yypt-2].addr.Reg; i++ {
				yyVAL.lval |= 1 << byte(i)
			}
		}
	case 140:
		//line a.y:823
		{
			yyVAL.lval = (1 << byte(yyS[yypt-2].addr.Reg)) | yyS[yypt-0].lval
		}
	case 141:
		//line a.y:829
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_VREG
			yyVAL.addr.Reg = int8(yyS[yypt-0].lval)
			/* TO DO: slice */
		}
	case 142:
		//line a.y:835
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_VREG
			yyVAL.addr.Reg = int8(yyS[yypt-1].lval)
		}
	case 143:
		//line a.y:843
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_OREG
			yyVAL.addr.Name = int8(yyS[yypt-1].lval)
			yyVAL.addr.Sym = nil
			yyVAL.addr.Offset = yyS[yypt-3].lval
		}
	case 144:
		//line a.y:851
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_OREG
			yyVAL.addr.Name = int8(yyS[yypt-1].lval)
			yyVAL.addr.Sym = obj.Linklookup(asm.Ctxt, yyS[yypt-4].sym.Name, 0)
			yyVAL.addr.Offset = yyS[yypt-3].lval
		}
	case 145:
		//line a.y:859
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_OREG
			yyVAL.addr.Name = D_STATIC
			yyVAL.addr.Sym = obj.Linklookup(asm.Ctxt, yyS[yypt-6].sym.Name, 1)
			yyVAL.addr.Offset = yyS[yypt-3].lval
		}
	case 146:
		//line a.y:868
		{
			yyVAL.lval = 0
		}
	case 147:
		//line a.y:872
		{
			yyVAL.lval = yyS[yypt-0].lval
		}
	case 148:
		//line a.y:876
		{
			yyVAL.lval = -yyS[yypt-0].lval
		}
	case 149:
		yyVAL.lval = yyS[yypt-0].lval
	case 150:
		yyVAL.lval = yyS[yypt-0].lval
	case 151:
		yyVAL.lval = yyS[yypt-0].lval
	case 152:
		yyVAL.lval = yyS[yypt-0].lval
	case 153:
		//line a.y:888
		{
			yyVAL.lval = yyS[yypt-0].sym.Value
		}
	case 154:
		//line a.y:892
		{
			yyVAL.lval = -yyS[yypt-0].lval
		}
	case 155:
		//line a.y:896
		{
			yyVAL.lval = yyS[yypt-0].lval
		}
	case 156:
		//line a.y:900
		{
			yyVAL.lval = ^yyS[yypt-0].lval
		}
	case 157:
		//line a.y:904
		{
			yyVAL.lval = yyS[yypt-1].lval
		}
	case 158:
		yyVAL.lval = yyS[yypt-0].lval
	case 159:
		//line a.y:911
		{
			yyVAL.lval = yyS[yypt-2].lval + yyS[yypt-0].lval
		}
	case 160:
		//line a.y:915
		{
			yyVAL.lval = yyS[yypt-2].lval - yyS[yypt-0].lval
		}
	case 161:
		//line a.y:919
		{
			yyVAL.lval = yyS[yypt-2].lval * yyS[yypt-0].lval
		}
	case 162:
		//line a.y:923
		{
			yyVAL.lval = yyS[yypt-2].lval / yyS[yypt-0].lval
		}
	case 163:
		//line a.y:927
		{
			yyVAL.lval = yyS[yypt-2].lval % yyS[yypt-0].lval
		}
	case 164:
		//line a.y:931
		{
			yyVAL.lval = yyS[yypt-3].lval << uint(yyS[yypt-0].lval)
		}
	case 165:
		//line a.y:935
		{
			yyVAL.lval = yyS[yypt-3].lval >> uint(yyS[yypt-0].lval)
		}
	case 166:
		//line a.y:939
		{
			yyVAL.lval = yyS[yypt-2].lval & yyS[yypt-0].lval
		}
	case 167:
		//line a.y:943
		{
			yyVAL.lval = yyS[yypt-2].lval ^ yyS[yypt-0].lval
		}
	case 168:
		//line a.y:947
		{
			yyVAL.lval = yyS[yypt-2].lval | yyS[yypt-0].lval
		}
	}
	goto yystack /* stack new state and value */
}
