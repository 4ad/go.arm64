/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     LTYPE0 = 258,
     LTYPE1 = 259,
     LTYPE2 = 260,
     LTYPE3 = 261,
     LTYPE4 = 262,
     LTYPE5 = 263,
     LTYPE6 = 264,
     LTYPE7 = 265,
     LTYPE8 = 266,
     LTYPE9 = 267,
     LTYPEA = 268,
     LTYPEB = 269,
     LTYPEC = 270,
     LTYPED = 271,
     LTYPEE = 272,
     LTYPEF = 273,
     LTYPEG = 274,
     LTYPEH = 275,
     LTYPEI = 276,
     LTYPEJ = 277,
     LTYPEK = 278,
     LTYPEL = 279,
     LTYPEM = 280,
     LTYPEN = 281,
     LTYPEO = 282,
     LTYPEP = 283,
     LTYPEQ = 284,
     LTYPER = 285,
     LTYPES = 286,
     LTYPET = 287,
     LTYPEU = 288,
     LTYPEV = 289,
     LTYPEW = 290,
     LTYPEX = 291,
     LTYPEY = 292,
     LTYPEZ = 293,
     LMOVK = 294,
     LDMB = 295,
     LSTXR = 296,
     LCONST = 297,
     LSP = 298,
     LSB = 299,
     LFP = 300,
     LPC = 301,
     LR = 302,
     LREG = 303,
     LF = 304,
     LFREG = 305,
     LV = 306,
     LVREG = 307,
     LC = 308,
     LCREG = 309,
     LFCR = 310,
     LFCSEL = 311,
     LCOND = 312,
     LS = 313,
     LAT = 314,
     LEXT = 315,
     LSPR = 316,
     LSPREG = 317,
     LVTYPE = 318,
     LFCONST = 319,
     LSCONST = 320,
     LNAME = 321,
     LLAB = 322,
     LVAR = 323
   };
#endif
/* Tokens.  */
#define LTYPE0 258
#define LTYPE1 259
#define LTYPE2 260
#define LTYPE3 261
#define LTYPE4 262
#define LTYPE5 263
#define LTYPE6 264
#define LTYPE7 265
#define LTYPE8 266
#define LTYPE9 267
#define LTYPEA 268
#define LTYPEB 269
#define LTYPEC 270
#define LTYPED 271
#define LTYPEE 272
#define LTYPEF 273
#define LTYPEG 274
#define LTYPEH 275
#define LTYPEI 276
#define LTYPEJ 277
#define LTYPEK 278
#define LTYPEL 279
#define LTYPEM 280
#define LTYPEN 281
#define LTYPEO 282
#define LTYPEP 283
#define LTYPEQ 284
#define LTYPER 285
#define LTYPES 286
#define LTYPET 287
#define LTYPEU 288
#define LTYPEV 289
#define LTYPEW 290
#define LTYPEX 291
#define LTYPEY 292
#define LTYPEZ 293
#define LMOVK 294
#define LDMB 295
#define LSTXR 296
#define LCONST 297
#define LSP 298
#define LSB 299
#define LFP 300
#define LPC 301
#define LR 302
#define LREG 303
#define LF 304
#define LFREG 305
#define LV 306
#define LVREG 307
#define LC 308
#define LCREG 309
#define LFCR 310
#define LFCSEL 311
#define LCOND 312
#define LS 313
#define LAT 314
#define LEXT 315
#define LSPR 316
#define LSPREG 317
#define LVTYPE 318
#define LFCONST 319
#define LSCONST 320
#define LNAME 321
#define LLAB 322
#define LVAR 323




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 8 "a.y"
{
	Sym	*sym;
	vlong	lval;
	double	dval;
	char	sval[NSNAME];
	Addr	addr;
}
/* Line 1529 of yacc.c.  */
#line 193 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

