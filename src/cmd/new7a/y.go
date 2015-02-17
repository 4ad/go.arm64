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
	-2, 71,
	-1, 155,
	1, 3,
	-2, 0,
	-1, 234,
	94, 137,
	-2, 71,
	-1, 261,
	86, 122,
	-2, 107,
	-1, 262,
	86, 123,
	-2, 108,
}

const yyNprod = 168
const yyPrivate = 57344

var yyTokenNames []string
var yyStates []string

const yyLast = 803

var yyAct = []int{

	157, 394, 242, 69, 135, 159, 233, 272, 106, 186,
	151, 144, 72, 71, 319, 56, 2, 419, 380, 342,
	96, 97, 98, 379, 108, 232, 231, 393, 74, 120,
	120, 67, 113, 115, 392, 86, 432, 123, 417, 58,
	416, 141, 71, 68, 146, 146, 397, 368, 362, 71,
	358, 66, 357, 136, 356, 154, 148, 99, 355, 350,
	349, 278, 100, 161, 119, 121, 89, 88, 398, 137,
	114, 116, 284, 142, 122, 152, 73, 290, 170, 171,
	153, 65, 64, 177, 178, 179, 143, 145, 217, 208,
	150, 172, 185, 130, 62, 83, 82, 194, 108, 71,
	184, 183, 182, 59, 117, 192, 198, 167, 120, 78,
	62, 126, 128, 128, 276, 133, 320, 95, 57, 209,
	83, 82, 212, 213, 431, 104, 430, 220, 111, 112,
	199, 429, 197, 428, 83, 82, 124, 125, 427, 80,
	425, 76, 191, 207, 424, 181, 423, 147, 147, 149,
	77, 422, 63, 63, 65, 64, 89, 88, 399, 63,
	386, 385, 214, 259, 80, 384, 109, 383, 81, 234,
	71, 378, 246, 107, 110, 377, 376, 177, 80, 375,
	373, 84, 57, 77, 281, 282, 283, 65, 64, 286,
	287, 109, 57, 81, 372, 215, 371, 156, 158, 110,
	370, 270, 108, 293, 260, 291, 84, 81, 369, 366,
	294, 55, 269, 353, 365, 57, 354, 305, 364, 306,
	84, 190, 341, 71, 329, 300, 245, 180, 241, 240,
	239, 141, 317, 318, 288, 316, 238, 237, 146, 325,
	321, 71, 71, 136, 236, 298, 295, 296, 297, 324,
	299, 235, 230, 229, 309, 303, 330, 228, 227, 137,
	226, 224, 223, 307, 343, 343, 343, 343, 222, 221,
	219, 216, 327, 328, 211, 210, 206, 141, 205, 352,
	323, 204, 203, 326, 344, 345, 346, 202, 201, 351,
	361, 200, 359, 169, 243, 360, 168, 160, 54, 363,
	310, 311, 261, 312, 313, 314, 315, 53, 50, 51,
	52, 277, 271, 268, 302, 418, 102, 301, 374, 225,
	304, 91, 90, 420, 280, 308, 162, 163, 382, 164,
	77, 79, 387, 218, 65, 64, 89, 88, 292, 89,
	88, 147, 243, 426, 367, 65, 64, 63, 391, 381,
	234, 188, 189, 274, 273, 275, 396, 65, 64, 77,
	83, 82, 118, 65, 64, 337, 108, 129, 129, 83,
	82, 285, 403, 404, 401, 266, 406, 322, 265, 141,
	274, 273, 275, 411, 71, 390, 414, 175, 244, 165,
	166, 136, 65, 64, 331, 332, 333, 334, 335, 264,
	347, 338, 339, 340, 80, 83, 82, 137, 400, 336,
	402, 289, 262, 80, 77, 412, 65, 64, 65, 64,
	274, 273, 275, 301, 127, 267, 187, 437, 188, 189,
	415, 94, 442, 81, 7, 263, 83, 82, 155, 85,
	443, 1, 81, 421, 444, 445, 84, 62, 110, 80,
	407, 75, 408, 409, 410, 84, 248, 249, 250, 251,
	252, 131, 250, 251, 252, 87, 433, 193, 435, 436,
	138, 243, 61, 60, 441, 405, 94, 139, 81, 0,
	80, 77, 388, 389, 110, 65, 64, 89, 88, 91,
	90, 84, 0, 70, 0, 395, 395, 0, 0, 93,
	92, 0, 0, 0, 0, 439, 440, 94, 0, 81,
	0, 243, 243, 0, 78, 85, 0, 0, 0, 0,
	8, 0, 84, 0, 0, 0, 413, 434, 83, 82,
	0, 438, 9, 10, 11, 12, 14, 15, 16, 17,
	18, 38, 26, 28, 29, 30, 49, 37, 0, 31,
	34, 41, 35, 36, 42, 43, 44, 25, 27, 19,
	20, 21, 22, 23, 40, 47, 24, 48, 13, 45,
	46, 0, 80, 83, 176, 173, 83, 82, 83, 82,
	0, 91, 90, 0, 0, 39, 0, 83, 82, 0,
	101, 0, 0, 32, 33, 5, 83, 82, 3, 94,
	4, 81, 0, 6, 83, 82, 0, 85, 0, 0,
	0, 103, 140, 105, 84, 0, 0, 80, 0, 0,
	80, 0, 80, 0, 0, 65, 64, 0, 132, 0,
	134, 80, 255, 253, 254, 248, 249, 250, 251, 252,
	80, 0, 175, 174, 94, 0, 81, 0, 80, 81,
	0, 81, 85, 0, 0, 110, 62, 110, 195, 84,
	81, 0, 84, 0, 84, 277, 196, 0, 0, 81,
	0, 0, 0, 84, 0, 110, 0, 81, 0, 0,
	0, 0, 84, 110, 0, 0, 0, 0, 0, 0,
	84, 257, 256, 255, 253, 254, 248, 249, 250, 251,
	252, 257, 256, 255, 253, 254, 248, 249, 250, 251,
	252, 257, 256, 255, 253, 254, 248, 249, 250, 251,
	252, 257, 256, 255, 253, 254, 248, 249, 250, 251,
	252, 256, 255, 253, 254, 248, 249, 250, 251, 252,
	253, 254, 248, 249, 250, 251, 252, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 348, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 279, 0, 0, 0,
	0, 0, 258, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 247,
}
var yyPact = []int{

	-1000, 518, -1000, 225, 226, 222, -1000, 213, 126, 32,
	23, 23, 427, 7, 32, 32, 32, 23, 305, 248,
	248, 7, 248, 86, 7, 7, 129, 276, 396, 396,
	305, 32, 7, 7, 279, 6, 6, 248, 279, 248,
	519, 427, 305, 360, 569, 7, 305, -13, 427, 32,
	-1000, 595, 595, -1000, -1000, -1000, -1000, 32, 211, -1000,
	-1000, -1000, 595, 319, -1000, 19, 210, 207, -1000, -1000,
	-1000, -10, -1000, -1000, -1000, -1000, -1000, -1000, 564, -1000,
	-1000, -1000, 595, 595, 595, 567, 14, -1000, -1000, 13,
	-1000, 12, -1000, 4, 419, 135, 578, 111, 427, 205,
	202, 201, -1000, 196, 195, 192, 190, 396, 1, 342,
	595, 189, 188, -1000, -1000, -1000, 32, 32, 96, 185,
	0, 321, 184, 22, 183, 182, 176, 175, -1000, -1000,
	309, 174, 172, 171, 167, 166, -1000, -65, -1000, -66,
	259, -10, 165, 158, -1000, 151, 150, -1000, 144, -1000,
	143, 142, 334, 140, -1000, 518, 717, -1000, 707, -1000,
	358, -1000, 428, 391, 370, 367, 418, 595, 305, 427,
	299, -10, -1000, 27, -1000, -1000, 587, -1000, -1000, -1000,
	-28, 697, 287, 595, 595, 595, -16, 363, 595, 595,
	305, 404, -1000, -1000, -11, 419, 567, -1000, -1000, -1000,
	334, 111, 305, 305, 305, 23, 305, 139, 260, -1000,
	7, 305, -1000, -1000, -1000, -1000, 569, 326, 595, 305,
	-1000, 7, 427, 279, 279, 233, 279, 279, 279, 279,
	519, 595, 595, -80, 106, 287, 305, 569, 595, 305,
	427, 427, 138, -1000, -1000, -13, -1000, -1000, 595, 595,
	595, 595, 595, 402, 357, 595, 595, 595, -1000, 136,
	-1000, -1000, -1000, 595, 595, 595, 595, 393, 687, -1000,
	-1000, -29, -30, -1000, -1000, -1000, 351, -1000, 125, -1000,
	-31, -35, -37, -39, 326, 342, -1000, -1000, -1000, 595,
	366, -16, -41, 32, -1000, -1000, 132, 128, 123, -1000,
	305, -42, 122, 114, -1000, 110, 108, -1000, -1000, -1000,
	-1000, 94, 32, 93, 90, 89, 85, -69, -74, -1000,
	259, 259, 81, 79, -1000, 75, -1000, 74, -1000, 334,
	-1000, 451, 451, -1000, -1000, -1000, 595, 595, 733, 626,
	726, 305, -1000, -1000, -1000, -1000, -1000, 595, -1000, -56,
	-1000, -1000, -63, 567, 287, -1000, -1000, -1000, -1000, -43,
	-20, 72, -1000, -1000, 305, 111, 305, -1000, -1000, 334,
	334, 7, 22, 279, -1000, 279, 279, 279, 519, -1000,
	-1000, -1000, -1000, 427, 287, 595, 305, -49, 447, 447,
	-1000, -1000, -1000, -1000, -51, 244, -75, -1000, 268, 305,
	65, -1000, 60, 58, 54, 333, -1000, -1000, 52, 47,
	45, -1000, -1000, 40, 38, -1000, -1000, -1000, -1000, -1000,
	-53, -1000, 305, 7, 305, 305, 595, 7, 279, 279,
	305, 595, -1000, -1000, 32, -1000, -1000, -1000, 32, 32,
	-1000, -1000, -1000, -1000, -1000, -1000,
}
var yyPgo = []int{

	0, 0, 145, 7, 9, 141, 2, 19, 1, 477,
	6, 31, 8, 43, 10, 76, 28, 473, 331, 424,
	472, 470, 4, 103, 3, 35, 12, 467, 465, 39,
	451, 590, 11, 441, 16, 438, 434, 5,
}
var yyR1 = []int{

	0, 33, 33, 34, 35, 34, 34, 34, 34, 34,
	34, 34, 36, 36, 36, 36, 36, 36, 36, 36,
	36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
	36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
	36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
	36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
	36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
	31, 37, 37, 32, 32, 12, 12, 24, 24, 24,
	24, 24, 18, 18, 11, 11, 11, 11, 11, 11,
	11, 11, 27, 27, 26, 26, 26, 28, 28, 28,
	28, 28, 28, 29, 29, 29, 23, 13, 13, 14,
	17, 17, 17, 17, 20, 20, 20, 8, 8, 7,
	5, 5, 6, 6, 30, 30, 19, 19, 15, 15,
	22, 22, 22, 22, 21, 21, 9, 10, 10, 10,
	16, 16, 25, 25, 25, 4, 4, 4, 3, 3,
	3, 1, 1, 1, 1, 1, 1, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
}
var yyR2 = []int{

	0, 0, 2, 0, 0, 4, 4, 4, 2, 1,
	2, 2, 2, 6, 5, 4, 4, 4, 4, 7,
	3, 3, 3, 3, 1, 5, 4, 4, 8, 6,
	6, 9, 4, 5, 8, 8, 2, 2, 2, 3,
	3, 3, 3, 4, 6, 8, 6, 4, 3, 4,
	4, 4, 4, 6, 5, 9, 9, 8, 4, 6,
	6, 8, 2, 4, 4, 2, 6, 4, 4, 2,
	1, 0, 2, 7, 1, 4, 2, 2, 2, 4,
	2, 1, 2, 3, 1, 1, 1, 1, 1, 1,
	1, 1, 3, 1, 1, 4, 1, 3, 4, 5,
	5, 6, 6, 1, 1, 1, 2, 1, 1, 5,
	4, 4, 4, 4, 1, 2, 5, 1, 2, 1,
	1, 4, 1, 1, 1, 4, 1, 1, 1, 4,
	1, 1, 1, 1, 4, 4, 3, 1, 3, 3,
	1, 4, 4, 5, 7, 0, 2, 2, 1, 1,
	1, 1, 1, 2, 2, 2, 3, 1, 3, 3,
	3, 3, 3, 4, 4, 3, 3, 3,
}
var yyChk = []int{

	-1000, -33, -34, 80, 82, 77, 85, -36, 2, 14,
	15, 16, 17, 50, 18, 19, 20, 21, 22, 41,
	42, 43, 44, 45, 48, 39, 24, 40, 25, 26,
	27, 31, 75, 76, 32, 34, 35, 29, 23, 67,
	46, 33, 36, 37, 38, 51, 52, 47, 49, 28,
	83, 84, 84, 85, 85, 85, -37, 86, -29, -23,
	-17, -20, 87, -5, 59, 58, -29, -11, -13, -24,
	66, -1, -26, -15, -16, -30, -5, 54, 87, -18,
	53, 82, 10, 9, 95, 88, -25, -28, 61, 60,
	63, 62, 73, 72, 80, -23, -37, -37, -37, -29,
	-13, -31, 68, -31, -23, -31, -12, 87, -1, 80,
	88, -23, -23, -37, -13, -37, -13, -15, 86, -25,
	-1, -25, -13, -37, -23, -23, -15, -19, -15, -18,
	87, -19, -31, -15, -31, -22, -26, -16, -21, -9,
	93, -1, -11, -13, -32, -13, -1, -23, -32, -23,
	-13, -14, 88, -11, -37, -35, -2, -1, -2, -37,
	86, -1, 7, 8, 10, 70, 71, 88, 86, 86,
	88, -1, -26, 11, 79, 78, 10, -1, -1, -1,
	-5, -2, 88, 88, 88, 88, -4, 7, 9, 10,
	86, 7, -12, -27, -1, 80, 88, -25, -12, -11,
	86, 86, 86, 86, 86, 86, 86, -25, 88, -4,
	86, 86, -37, -37, -13, -15, 86, 88, 12, 86,
	-24, 86, 86, 86, 86, 10, 86, 86, 86, 86,
	86, 91, 91, -10, -16, 86, 86, 86, 86, 86,
	86, 86, -6, -5, 54, 86, -34, 85, 9, 10,
	11, 12, 13, 7, 8, 6, 5, 4, 85, -6,
	-13, -5, 54, 7, 8, 8, 8, 7, -2, -13,
	-11, -5, -3, 55, 54, 56, 87, 78, 89, 89,
	-5, -1, -1, -1, 88, 8, -1, -1, -13, 7,
	88, -4, -5, -6, -12, -13, -13, -13, -29, -13,
	86, 57, -23, -13, -23, -1, -1, -13, -23, -11,
	-15, -15, -15, -15, -15, -15, -22, -1, -1, 94,
	10, -37, -5, -13, -32, -1, -13, -11, -11, 86,
	-14, -2, -2, -2, -2, -2, 7, 8, -2, -2,
	-2, 86, -7, -1, -7, -7, -7, 7, 89, 89,
	89, -26, -1, 88, 91, 89, 89, 89, 89, -3,
	-4, -1, 89, -37, 86, 86, 86, -13, 89, 86,
	86, 86, 86, 86, -37, 86, 86, 86, 86, 92,
	92, -16, -10, 86, 86, 86, 86, -6, -2, -2,
	-13, -1, 90, 90, -8, -5, -8, 89, 88, 86,
	-13, -12, -13, -6, -6, -23, -24, -15, -15, -15,
	-15, -22, -11, -5, -1, -13, 89, 89, 71, 92,
	55, -13, 86, 86, 86, 86, 10, 86, 86, 86,
	86, 86, 89, -13, -23, -13, -13, -1, -23, -15,
	-15, -13, -1, -37, -37, -37,
}
var yyDef = []int{

	1, -2, 2, 0, 0, 0, 9, 0, 0, 71,
	0, 0, 0, 0, 71, 71, -2, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 71, 71, 0, 0,
	0, 71, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 71,
	4, 0, 0, 8, 10, 11, 12, 71, 0, 103,
	104, 105, 0, 114, 120, 0, 0, 0, 84, 85,
	86, 87, 88, 89, 90, 91, 107, 108, 0, 81,
	151, 152, 0, 0, 0, 0, 94, 96, 128, 0,
	140, 0, 124, 0, 145, 0, 0, 0, 0, 0,
	0, 0, 70, 0, 0, 0, 0, 0, 0, 145,
	0, 0, 0, 36, 37, 38, 71, 71, 71, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 126, 127,
	0, 0, 0, 0, 0, 0, 130, 131, 132, 133,
	0, 0, 0, 0, 62, 0, 0, 74, 0, 65,
	0, 0, 0, 0, 69, -2, 0, 157, 0, 72,
	0, 106, 0, 0, 0, 0, 115, 0, 0, 0,
	0, 77, 78, 0, 80, 82, 0, 153, 154, 155,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 20, 21, 0, 145, 0, 93, 22, 23,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 76,
	0, 0, 39, 40, 41, 42, 0, 0, 0, 0,
	48, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, -2, 0, 0, 0, 0, 0,
	0, 0, 0, 122, 123, 0, 5, 6, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 7, 0,
	15, -2, -2, 0, 0, 0, 0, 0, 0, 16,
	17, 0, 0, 148, 149, 150, 0, 83, 97, 156,
	0, 0, 0, 0, 0, 145, 146, 147, 18, 0,
	0, 76, 0, 71, 26, 27, 0, 0, 0, 32,
	0, 0, 0, 0, 43, 0, 0, 47, 49, 50,
	51, 52, 71, 0, 0, 0, 58, 0, 0, 136,
	0, 0, 0, 0, 63, 0, 64, 0, 67, 0,
	68, 158, 159, 160, 161, 162, 0, 0, 165, 166,
	167, 14, 110, 119, 111, 112, 113, 0, 121, 98,
	142, 79, 0, 0, 0, 95, 129, 141, 125, 0,
	0, 0, 92, 25, 0, 0, 0, 33, 75, 0,
	0, 0, 0, 0, 54, 0, 0, 0, 0, 134,
	135, 138, 139, 0, 0, 0, 0, 0, 163, 164,
	13, 116, 99, 100, 0, 117, 0, 143, 0, 0,
	29, 30, 0, 0, 0, 44, 46, 53, 0, 0,
	0, 59, 60, 0, 0, 66, 109, 101, 118, 102,
	0, 19, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 144, 28, 71, 34, 35, 45, 71, 71,
	57, 61, 73, 31, 55, 56,
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
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 68:
		//line a.y:442
		{
			outcode(int(yyS[yypt-3].lval), &yyS[yypt-2].addr, NREG, &yyS[yypt-0].addr)
		}
	case 69:
		//line a.y:449
		{
			outcode(int(yyS[yypt-1].lval), &nullgen, NREG, &nullgen)
		}
	case 70:
		//line a.y:455
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_COND
			yyVAL.addr.Reg = int8(yyS[yypt-0].lval)
		}
	case 73:
		//line a.y:466
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_CONST
			yyVAL.addr.Offset = int64(SYSARG4(int(yyS[yypt-6].lval), int(yyS[yypt-4].lval), int(yyS[yypt-2].lval), int(yyS[yypt-0].lval)))
		}
	case 74:
		yyVAL.addr = yyS[yypt-0].addr
	case 75:
		//line a.y:475
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_BRANCH
			yyVAL.addr.Offset = yyS[yypt-3].lval + int64(asm.PC)
		}
	case 76:
		//line a.y:481
		{
			yyS[yypt-1].sym = asm.LabelLookup(yyS[yypt-1].sym)
			yyVAL.addr = nullgen
			if asm.Pass == 2 && yyS[yypt-1].sym.Type != LLAB {
				yyerror("undefined label: %s", yyS[yypt-1].sym.Labelname)
			}
			yyVAL.addr.Type = D_BRANCH
			yyVAL.addr.Offset = yyS[yypt-1].sym.Value + yyS[yypt-0].lval
		}
	case 77:
		//line a.y:492
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_CONST
			yyVAL.addr.Offset = yyS[yypt-0].lval
		}
	case 78:
		//line a.y:498
		{
			yyVAL.addr = yyS[yypt-0].addr
			yyVAL.addr.Type = D_CONST
		}
	case 79:
		//line a.y:503
		{
			yyVAL.addr = yyS[yypt-0].addr
			yyVAL.addr.Type = D_OCONST
		}
	case 80:
		//line a.y:508
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_SCONST
			yyVAL.addr.U.Sval = yyS[yypt-0].sval
		}
	case 81:
		yyVAL.addr = yyS[yypt-0].addr
	case 82:
		//line a.y:517
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_FCONST
			yyVAL.addr.U.Dval = yyS[yypt-0].dval
		}
	case 83:
		//line a.y:523
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_FCONST
			yyVAL.addr.U.Dval = -yyS[yypt-0].dval
		}
	case 84:
		yyVAL.addr = yyS[yypt-0].addr
	case 85:
		yyVAL.addr = yyS[yypt-0].addr
	case 86:
		//line a.y:533
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_SPR
			yyVAL.addr.Offset = yyS[yypt-0].lval
		}
	case 87:
		//line a.y:539
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_OREG
			yyVAL.addr.Offset = yyS[yypt-0].lval
		}
	case 88:
		yyVAL.addr = yyS[yypt-0].addr
	case 89:
		yyVAL.addr = yyS[yypt-0].addr
	case 90:
		yyVAL.addr = yyS[yypt-0].addr
	case 91:
		yyVAL.addr = yyS[yypt-0].addr
	case 92:
		//line a.y:551
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_OREG
			yyVAL.addr.Reg = int8(yyS[yypt-1].lval)
			yyVAL.addr.Offset = 0
		}
	case 93:
		//line a.y:558
		{
			yyVAL.addr = yyS[yypt-0].addr
			if yyS[yypt-0].addr.Name != D_EXTERN && yyS[yypt-0].addr.Name != D_STATIC {
			}
		}
	case 94:
		yyVAL.addr = yyS[yypt-0].addr
	case 95:
		//line a.y:567
		{
			yyVAL.addr = yyS[yypt-3].addr
			yyVAL.addr.Type = D_OREG
			yyVAL.addr.Reg = int8(yyS[yypt-1].lval)
		}
	case 96:
		yyVAL.addr = yyS[yypt-0].addr
	case 97:
		//line a.y:576
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_OREG
			yyVAL.addr.Reg = int8(yyS[yypt-1].lval)
			yyVAL.addr.Offset = 0
		}
	case 98:
		//line a.y:583
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_OREG
			yyVAL.addr.Reg = int8(yyS[yypt-1].lval)
			yyVAL.addr.Offset = yyS[yypt-3].lval
		}
	case 99:
		//line a.y:590
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_XPRE
			yyVAL.addr.Reg = int8(yyS[yypt-2].lval)
			yyVAL.addr.Offset = yyS[yypt-4].lval
		}
	case 100:
		//line a.y:597
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_XPOST
			yyVAL.addr.Reg = int8(yyS[yypt-3].lval)
			yyVAL.addr.Offset = yyS[yypt-1].lval
		}
	case 101:
		//line a.y:604
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_ROFF
			yyVAL.addr.Reg = int8(yyS[yypt-4].lval)
			yyVAL.addr.Scale = int8(yyS[yypt-1].lval & 0x1f)
			yyVAL.addr.Offset = yyS[yypt-1].lval
		}
	case 102:
		//line a.y:612
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_ROFF
			yyVAL.addr.Reg = int8(yyS[yypt-4].lval)
			yyVAL.addr.Scale = int8(yyS[yypt-1].lval & 0x1f)
			yyVAL.addr.Offset = yyS[yypt-1].lval | (1 << 16)
		}
	case 103:
		yyVAL.addr = yyS[yypt-0].addr
	case 104:
		yyVAL.addr = yyS[yypt-0].addr
	case 105:
		yyVAL.addr = yyS[yypt-0].addr
	case 106:
		//line a.y:626
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_CONST
			yyVAL.addr.Offset = yyS[yypt-0].lval
		}
	case 107:
		//line a.y:634
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_REG
			yyVAL.addr.Reg = int8(yyS[yypt-0].lval)
		}
	case 108:
		//line a.y:640
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_SP
			yyVAL.addr.Reg = REGSP
		}
	case 109:
		//line a.y:648
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_PAIR
			yyVAL.addr.Reg = int8(yyS[yypt-3].lval)
			yyVAL.addr.Offset = yyS[yypt-1].lval
		}
	case 110:
		//line a.y:657
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_SHIFT
			yyVAL.addr.Offset = (yyS[yypt-3].lval << 16) | (yyS[yypt-0].lval << 10) | (0 << 22)
		}
	case 111:
		//line a.y:663
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_SHIFT
			yyVAL.addr.Offset = ((yyS[yypt-3].lval & 0x1F) << 16) | (yyS[yypt-0].lval << 10) | (1 << 22)
		}
	case 112:
		//line a.y:669
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_SHIFT
			yyVAL.addr.Offset = (yyS[yypt-3].lval << 16) | (yyS[yypt-0].lval << 10) | (2 << 22)
		}
	case 113:
		//line a.y:675
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_SHIFT
			yyVAL.addr.Offset = (yyS[yypt-3].lval << 16) | (yyS[yypt-0].lval << 10) | (3 << 22)
		}
	case 114:
		//line a.y:683
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_REG
			yyVAL.addr.Reg = int8(yyS[yypt-0].lval)
		}
	case 115:
		//line a.y:689
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_EXTREG
			yyVAL.addr.Reg = int8(yyS[yypt-1].lval)
			yyVAL.addr.Offset = (yyS[yypt-1].lval << 16) | (yyS[yypt-0].lval << 13)
		}
	case 116:
		//line a.y:696
		{
			if yyS[yypt-0].lval < 0 || yyS[yypt-0].lval > 4 {
				yyerror("shift value out of range")
			}
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_EXTREG
			yyVAL.addr.Reg = int8(yyS[yypt-4].lval)
			yyVAL.addr.Offset = (yyS[yypt-4].lval << 16) | (yyS[yypt-3].lval << 13) | (yyS[yypt-0].lval << 10)
		}
	case 117:
		//line a.y:708
		{
			yyVAL.lval = (3 << 8) | yyS[yypt-0].lval
		}
	case 118:
		//line a.y:712
		{
			yyVAL.lval = (yyS[yypt-0].lval << 8) | yyS[yypt-1].lval
		}
	case 119:
		//line a.y:718
		{
			if yyVAL.lval < 0 || yyVAL.lval >= 64 {
				yyerror("shift value out of range")
			}
			yyVAL.lval = yyS[yypt-0].lval & 0x3F
		}
	case 120:
		yyVAL.lval = yyS[yypt-0].lval
	case 121:
		//line a.y:728
		{
			if yyS[yypt-1].lval < 0 || yyS[yypt-1].lval >= NREG {
				print("register value out of range\n")
			}
			yyVAL.lval = yyS[yypt-1].lval
		}
	case 122:
		yyVAL.lval = yyS[yypt-0].lval
	case 123:
		//line a.y:738
		{
			yyVAL.lval = REGSP
		}
	case 124:
		//line a.y:744
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_SPR
			yyVAL.addr.Offset = yyS[yypt-0].lval
		}
	case 125:
		//line a.y:750
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = int16(yyS[yypt-3].lval)
			yyVAL.addr.Offset = yyS[yypt-1].lval
		}
	case 126:
		yyVAL.addr = yyS[yypt-0].addr
	case 127:
		yyVAL.addr = yyS[yypt-0].addr
	case 128:
		//line a.y:762
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_FREG
			yyVAL.addr.Reg = int8(yyS[yypt-0].lval)
		}
	case 129:
		//line a.y:768
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_FREG
			yyVAL.addr.Reg = int8(yyS[yypt-1].lval)
		}
	case 130:
		yyVAL.addr = yyS[yypt-0].addr
	case 131:
		yyVAL.addr = yyS[yypt-0].addr
	case 132:
		yyVAL.addr = yyS[yypt-0].addr
	case 133:
		//line a.y:779
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_VSET
			yyVAL.addr.Offset = yyS[yypt-0].lval
		}
	case 134:
		//line a.y:787
		{
			yyVAL.addr.Type = D_VLANE
			yyVAL.addr.Offset = yyS[yypt-1].lval
		}
	case 135:
		//line a.y:792
		{
			yyVAL.addr.Type = D_VLANE
			yyVAL.addr.Offset = yyS[yypt-1].lval
		}
	case 136:
		//line a.y:799
		{
			yyVAL.lval = yyS[yypt-1].lval
		}
	case 137:
		//line a.y:805
		{
			yyVAL.lval = 1 << byte(yyS[yypt-0].addr.Reg)
		}
	case 138:
		//line a.y:809
		{
			yyVAL.lval = 0
			for i := yyS[yypt-2].addr.Reg; i <= yyS[yypt-0].addr.Reg; i++ {
				yyVAL.lval |= 1 << byte(i)
			}
			for i := yyS[yypt-0].addr.Reg; i <= yyS[yypt-2].addr.Reg; i++ {
				yyVAL.lval |= 1 << byte(i)
			}
		}
	case 139:
		//line a.y:819
		{
			yyVAL.lval = (1 << byte(yyS[yypt-2].addr.Reg)) | yyS[yypt-0].lval
		}
	case 140:
		//line a.y:825
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_VREG
			yyVAL.addr.Reg = int8(yyS[yypt-0].lval)
			/* TO DO: slice */
		}
	case 141:
		//line a.y:831
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_VREG
			yyVAL.addr.Reg = int8(yyS[yypt-1].lval)
		}
	case 142:
		//line a.y:839
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_OREG
			yyVAL.addr.Name = int8(yyS[yypt-1].lval)
			yyVAL.addr.Sym = nil
			yyVAL.addr.Offset = yyS[yypt-3].lval
		}
	case 143:
		//line a.y:847
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_OREG
			yyVAL.addr.Name = int8(yyS[yypt-1].lval)
			yyVAL.addr.Sym = obj.Linklookup(asm.Ctxt, yyS[yypt-4].sym.Name, 0)
			yyVAL.addr.Offset = yyS[yypt-3].lval
		}
	case 144:
		//line a.y:855
		{
			yyVAL.addr = nullgen
			yyVAL.addr.Type = D_OREG
			yyVAL.addr.Name = D_STATIC
			yyVAL.addr.Sym = obj.Linklookup(asm.Ctxt, yyS[yypt-6].sym.Name, 0)
			yyVAL.addr.Offset = yyS[yypt-3].lval
		}
	case 145:
		//line a.y:864
		{
			yyVAL.lval = 0
		}
	case 146:
		//line a.y:868
		{
			yyVAL.lval = yyS[yypt-0].lval
		}
	case 147:
		//line a.y:872
		{
			yyVAL.lval = -yyS[yypt-0].lval
		}
	case 148:
		yyVAL.lval = yyS[yypt-0].lval
	case 149:
		yyVAL.lval = yyS[yypt-0].lval
	case 150:
		yyVAL.lval = yyS[yypt-0].lval
	case 151:
		yyVAL.lval = yyS[yypt-0].lval
	case 152:
		//line a.y:884
		{
			yyVAL.lval = yyS[yypt-0].sym.Value
		}
	case 153:
		//line a.y:888
		{
			yyVAL.lval = -yyS[yypt-0].lval
		}
	case 154:
		//line a.y:892
		{
			yyVAL.lval = yyS[yypt-0].lval
		}
	case 155:
		//line a.y:896
		{
			yyVAL.lval = ^yyS[yypt-0].lval
		}
	case 156:
		//line a.y:900
		{
			yyVAL.lval = yyS[yypt-1].lval
		}
	case 157:
		yyVAL.lval = yyS[yypt-0].lval
	case 158:
		//line a.y:907
		{
			yyVAL.lval = yyS[yypt-2].lval + yyS[yypt-0].lval
		}
	case 159:
		//line a.y:911
		{
			yyVAL.lval = yyS[yypt-2].lval - yyS[yypt-0].lval
		}
	case 160:
		//line a.y:915
		{
			yyVAL.lval = yyS[yypt-2].lval * yyS[yypt-0].lval
		}
	case 161:
		//line a.y:919
		{
			yyVAL.lval = yyS[yypt-2].lval / yyS[yypt-0].lval
		}
	case 162:
		//line a.y:923
		{
			yyVAL.lval = yyS[yypt-2].lval % yyS[yypt-0].lval
		}
	case 163:
		//line a.y:927
		{
			yyVAL.lval = yyS[yypt-3].lval << uint(yyS[yypt-0].lval)
		}
	case 164:
		//line a.y:931
		{
			yyVAL.lval = yyS[yypt-3].lval >> uint(yyS[yypt-0].lval)
		}
	case 165:
		//line a.y:935
		{
			yyVAL.lval = yyS[yypt-2].lval & yyS[yypt-0].lval
		}
	case 166:
		//line a.y:939
		{
			yyVAL.lval = yyS[yypt-2].lval ^ yyS[yypt-0].lval
		}
	case 167:
		//line a.y:943
		{
			yyVAL.lval = yyS[yypt-2].lval | yyS[yypt-0].lval
		}
	}
	goto yystack /* stack new state and value */
}
