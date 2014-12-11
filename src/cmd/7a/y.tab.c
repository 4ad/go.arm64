/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "a.y"

#include <u.h>
#include <stdio.h>	/* if we don't, bison will, and a.h re-#defines getc */
#include <libc.h>
#include "a.h"
#include "../../runtime/funcdata.h"


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 9 "a.y"
{
	Sym	*sym;
	vlong	lval;
	double	dval;
	char	sval[NSNAME];
	Addr	addr;
}
/* Line 193 of yacc.c.  */
#line 248 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 261 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   709

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  92
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  164
/* YYNRULES -- Number of states.  */
#define YYNSTATES  430

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   323

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    86,     2,     2,    83,    12,     5,     2,
      84,    85,    10,     8,    82,     9,     2,    11,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    79,    81,
       6,    80,     7,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    87,     2,    88,     4,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    89,     3,    90,    91,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,     8,    13,    14,    19,    24,
      29,    31,    34,    37,    40,    47,    53,    58,    63,    68,
      73,    81,    85,    89,    93,    97,    99,   105,   110,   115,
     124,   131,   138,   148,   153,   159,   168,   177,   180,   183,
     186,   190,   194,   198,   202,   207,   214,   223,   230,   235,
     239,   244,   249,   256,   262,   272,   282,   291,   296,   303,
     310,   319,   322,   327,   332,   335,   342,   345,   347,   348,
     351,   359,   361,   366,   369,   372,   375,   378,   383,   386,
     388,   391,   395,   397,   399,   401,   403,   405,   407,   409,
     411,   415,   417,   419,   424,   426,   430,   435,   441,   447,
     454,   461,   463,   465,   467,   470,   472,   474,   479,   484,
     489,   494,   496,   499,   505,   507,   510,   512,   514,   519,
     521,   523,   525,   530,   532,   534,   536,   541,   543,   545,
     547,   549,   554,   559,   563,   565,   569,   573,   575,   580,
     585,   591,   599,   600,   603,   606,   608,   610,   612,   614,
     616,   619,   622,   625,   629,   631,   635,   639,   643,   647,
     651,   656,   661,   665,   669
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      93,     0,    -1,    -1,    93,    94,    -1,    -1,    77,    79,
      95,    94,    -1,    -1,    76,    79,    96,    94,    -1,    76,
      80,   129,    81,    -1,    78,    80,   129,    81,    -1,    81,
      -1,    97,    81,    -1,     1,    81,    -1,    13,    99,    -1,
      14,   108,    82,   116,    82,   110,    -1,    14,   108,    82,
     116,    82,    -1,    14,   108,    82,   110,    -1,    15,   108,
      82,   110,    -1,    16,   104,    82,   104,    -1,    49,   109,
      82,   110,    -1,    49,   109,     6,     6,   128,    82,   110,
      -1,    17,    99,   101,    -1,    17,    99,   105,    -1,    18,
      99,   101,    -1,    19,    99,   104,    -1,    19,    -1,    20,
     108,    82,   116,    99,    -1,    21,   110,    82,   101,    -1,
      40,    98,    82,   110,    -1,    41,    98,    82,   110,    82,
     110,    82,   110,    -1,    41,    98,    82,   110,    82,   110,
      -1,    42,   109,    82,   110,    82,   101,    -1,    43,    98,
      82,   108,    82,   110,    82,   109,    99,    -1,    44,   101,
      82,   110,    -1,    44,    83,   125,    82,   110,    -1,    47,
     109,    82,   109,    82,   116,    82,   110,    -1,    38,   109,
      82,   110,    82,   116,    82,   110,    -1,    23,    99,    -1,
      23,   110,    -1,    39,    99,    -1,    39,   110,    99,    -1,
      39,   119,    99,    -1,    39,    82,   110,    -1,    39,    82,
     119,    -1,    24,   125,    82,   109,    -1,    24,   125,    82,
     128,    82,   109,    -1,    24,   125,    82,   128,    82,   109,
       9,   128,    -1,    25,   125,    11,   128,    82,   102,    -1,
      26,   110,    82,   110,    -1,    30,    99,   102,    -1,    31,
     119,    82,   119,    -1,    33,   118,    82,   119,    -1,    33,
     118,    82,   119,    82,   119,    -1,    34,   118,    82,   119,
      99,    -1,    28,    98,    82,   119,    82,   119,    82,   109,
      99,    -1,    22,   119,    82,   119,    82,   119,    82,   119,
      99,    -1,    66,    98,    82,   119,    82,   119,    82,   119,
      -1,    45,   120,    82,   120,    -1,    45,   120,    82,   120,
      82,   120,    -1,    32,   104,    82,   115,    82,   104,    -1,
      35,   110,    82,   110,    82,   115,    82,   110,    -1,    36,
     100,    -1,    36,   110,    82,   100,    -1,    37,   100,    82,
     110,    -1,    50,   109,    -1,    51,   110,    82,   104,    82,
     115,    -1,    27,    99,    -1,    67,    -1,    -1,    82,    99,
      -1,   128,    82,   128,    82,   128,    82,   128,    -1,   109,
      -1,   128,    84,    56,    85,    -1,    76,   126,    -1,    77,
     126,    -1,    83,   128,    -1,    83,   106,    -1,    83,    10,
      83,   106,    -1,    83,    75,    -1,   103,    -1,    83,    74,
      -1,    83,     9,    74,    -1,   110,    -1,   102,    -1,    65,
      -1,   128,    -1,   106,    -1,   119,    -1,   124,    -1,   117,
      -1,    84,   115,    85,    -1,   125,    -1,   125,    -1,   125,
      84,   115,    85,    -1,   107,    -1,    84,   115,    85,    -1,
     128,    84,   115,    85,    -1,   128,    84,   115,    85,    86,
      -1,    84,   115,    85,   128,    86,    -1,    84,   115,    85,
      84,   113,    85,    -1,    84,   115,    85,    87,   113,    88,
      -1,   109,    -1,   111,    -1,   112,    -1,    83,   128,    -1,
     115,    -1,    53,    -1,   115,     6,     6,   114,    -1,   115,
       7,     7,   114,    -1,   115,     9,     7,   114,    -1,   115,
      69,     7,   114,    -1,   115,    -1,   115,    70,    -1,   115,
      70,     6,     6,   128,    -1,   115,    -1,   115,    70,    -1,
     128,    -1,    58,    -1,    57,    84,   129,    85,    -1,   115,
      -1,    53,    -1,    72,    -1,    71,    84,   128,    85,    -1,
     119,    -1,   103,    -1,    60,    -1,    59,    84,   128,    85,
      -1,   106,    -1,   124,    -1,   121,    -1,   122,    -1,   124,
      87,   128,    88,    -1,   122,    87,   128,    88,    -1,    89,
     123,    90,    -1,   124,    -1,   124,     9,   124,    -1,   124,
      99,   123,    -1,    62,    -1,    61,    84,   128,    85,    -1,
     128,    84,   127,    85,    -1,    76,   126,    84,   127,    85,
      -1,    76,     6,     7,   126,    84,    54,    85,    -1,    -1,
       8,   128,    -1,     9,   128,    -1,    54,    -1,    53,    -1,
      55,    -1,    52,    -1,    78,    -1,     9,   128,    -1,     8,
     128,    -1,    91,   128,    -1,    84,   129,    85,    -1,   128,
      -1,   129,     8,   129,    -1,   129,     9,   129,    -1,   129,
      10,   129,    -1,   129,    11,   129,    -1,   129,    12,   129,
      -1,   129,     6,     6,   129,    -1,   129,     7,     7,   129,
      -1,   129,     5,   129,    -1,   129,     4,   129,    -1,   129,
       3,   129,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    40,    40,    41,    45,    44,    52,    51,    57,    62,
      68,    69,    70,    76,    83,    87,    91,    98,   105,   112,
     116,   127,   131,   138,   145,   149,   156,   163,   170,   177,
     181,   188,   195,   202,   206,   213,   220,   227,   231,   238,
     242,   246,   250,   254,   261,   266,   273,   283,   290,   297,
     304,   311,   315,   322,   329,   336,   343,   350,   354,   361,
     368,   375,   379,   383,   390,   397,   404,   410,   417,   418,
     421,   427,   430,   436,   444,   451,   457,   462,   467,   473,
     476,   482,   490,   491,   492,   498,   504,   505,   506,   507,
     510,   517,   525,   526,   532,   535,   542,   549,   556,   563,
     571,   581,   582,   583,   585,   593,   599,   607,   613,   619,
     625,   633,   639,   646,   657,   661,   667,   675,   676,   684,
     685,   691,   697,   705,   706,   709,   715,   723,   724,   725,
     726,   734,   739,   746,   752,   756,   765,   771,   778,   786,
     794,   802,   812,   815,   819,   825,   826,   827,   830,   831,
     835,   839,   843,   847,   853,   854,   858,   862,   866,   870,
     874,   878,   882,   886,   890
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "'|'", "'^'", "'&'", "'<'", "'>'", "'+'",
  "'-'", "'*'", "'/'", "'%'", "LTYPE0", "LTYPE1", "LTYPE2", "LTYPE3",
  "LTYPE4", "LTYPE5", "LTYPE6", "LTYPE7", "LTYPE8", "LTYPE9", "LTYPEA",
  "LTYPEB", "LTYPEC", "LTYPED", "LTYPEE", "LTYPEF", "LTYPEG", "LTYPEH",
  "LTYPEI", "LTYPEJ", "LTYPEK", "LTYPEL", "LTYPEM", "LTYPEN", "LTYPEO",
  "LTYPEP", "LTYPEQ", "LTYPER", "LTYPES", "LTYPET", "LTYPEU", "LTYPEV",
  "LTYPEW", "LTYPEX", "LTYPEY", "LTYPEZ", "LMOVK", "LDMB", "LSTXR",
  "LCONST", "LSP", "LSB", "LFP", "LPC", "LR", "LREG", "LF", "LFREG", "LV",
  "LVREG", "LC", "LCREG", "LFCR", "LFCSEL", "LCOND", "LS", "LAT", "LEXT",
  "LSPR", "LSPREG", "LVTYPE", "LFCONST", "LSCONST", "LNAME", "LLAB",
  "LVAR", "':'", "'='", "';'", "','", "'$'", "'('", "')'", "'!'", "'['",
  "']'", "'{'", "'}'", "'~'", "$accept", "prog", "line", "@1", "@2",
  "inst", "cond", "comma", "sysarg", "rel", "ximm", "fcon", "addr",
  "nireg", "oreg", "ioreg", "imsr", "imm", "reg", "shift", "extreg",
  "indexreg", "scon", "sreg", "spreg", "spr", "frcon", "freg", "vaddr",
  "vlane", "vset", "vreglist", "vreg", "name", "offset", "pointer", "con",
  "expr", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   124,    94,    38,    60,    62,    43,    45,
      42,    47,    37,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,    58,
      61,    59,    44,    36,    40,    41,    33,    91,    93,   123,
     125,   126
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    92,    93,    93,    95,    94,    96,    94,    94,    94,
      94,    94,    94,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    98,    99,    99,
     100,   100,   101,   101,   101,   102,   102,   102,   102,   102,
     103,   103,   104,   104,   104,   104,   104,   104,   104,   104,
     105,   105,   106,   106,   106,   107,   107,   107,   107,   107,
     107,   108,   108,   108,   109,   110,   110,   111,   111,   111,
     111,   112,   112,   112,   113,   113,   114,   115,   115,   116,
     116,   117,   117,   118,   118,   119,   119,   120,   120,   120,
     120,   121,   121,   122,   123,   123,   123,   124,   124,   125,
     125,   125,   126,   126,   126,   127,   127,   127,   128,   128,
     128,   128,   128,   128,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     0,     4,     0,     4,     4,     4,
       1,     2,     2,     2,     6,     5,     4,     4,     4,     4,
       7,     3,     3,     3,     3,     1,     5,     4,     4,     8,
       6,     6,     9,     4,     5,     8,     8,     2,     2,     2,
       3,     3,     3,     3,     4,     6,     8,     6,     4,     3,
       4,     4,     6,     5,     9,     9,     8,     4,     6,     6,
       8,     2,     4,     4,     2,     6,     2,     1,     0,     2,
       7,     1,     4,     2,     2,     2,     2,     4,     2,     1,
       2,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     4,     1,     3,     4,     5,     5,     6,
       6,     1,     1,     1,     2,     1,     1,     4,     4,     4,
       4,     1,     2,     5,     1,     2,     1,     1,     4,     1,
       1,     1,     4,     1,     1,     1,     4,     1,     1,     1,
       1,     4,     4,     3,     1,     3,     3,     1,     4,     4,
       5,     7,     0,     2,     2,     1,     1,     1,     1,     1,
       2,     2,     2,     3,     1,     3,     3,     3,     3,     3,
       4,     4,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,    68,     0,     0,     0,    68,    68,
      68,     0,     0,     0,    68,     0,     0,     0,    68,     0,
      68,     0,     0,     0,     0,     0,     0,     0,     0,    68,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    10,     3,     0,    12,    68,    13,
       0,   117,     0,     0,   101,   102,   103,   111,     0,     0,
       0,   148,   106,     0,   125,     0,   137,    84,     0,   121,
     142,   149,     0,     0,     0,    83,    79,     0,    86,    94,
      82,   105,    89,    87,    88,    92,    85,     0,     0,     0,
       0,     0,     0,    37,    38,     0,     0,     0,     0,     0,
      66,    67,     0,     0,     0,     0,     0,   124,     0,   123,
       0,     0,    61,    71,     0,     0,     0,     0,    68,    39,
      68,    68,     0,     0,     0,     0,   142,   142,     0,     0,
       0,     0,   127,     0,   129,   130,   128,     0,     0,     0,
      64,     0,     0,     6,     0,     4,     0,    11,    69,     0,
     104,     0,     0,     0,     0,     0,   112,     0,   151,   150,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
      78,    76,    75,     0,   154,     0,   152,     0,     0,     0,
     142,     0,    21,    22,    91,     0,    23,    24,     0,     0,
       0,     0,     0,     0,     0,     0,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    42,    43,    40,
      41,     0,     0,     0,     0,    73,    74,     0,     0,     0,
       0,    68,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   106,    16,   105,     0,     0,
       0,     0,     0,     0,    17,     0,     0,     0,   142,   143,
     144,     0,    81,     0,    95,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   153,    18,     0,   146,   145,
     147,     0,     0,    73,     0,     0,   120,   119,    68,    27,
       0,    44,     0,     0,    48,     0,    50,     0,    51,    68,
       0,    62,     0,    63,     0,    28,     0,     0,     0,     0,
      33,     0,   133,     0,     0,    57,     0,     0,     0,     0,
      19,     0,     0,     7,     8,     5,     9,   118,    15,   107,
     116,   108,   109,   110,     0,   126,   138,   122,     0,     0,
      77,     0,     0,     0,   164,   163,   162,     0,     0,   155,
     156,   157,   158,   159,    93,    96,   139,    90,    26,     0,
       0,     0,     0,     0,     0,    53,     0,     0,     0,     0,
       0,     0,    34,    72,   135,   136,     0,   132,   131,     0,
       0,     0,     0,    14,   113,     0,   140,     0,   114,     0,
      98,   160,   161,    97,     0,    45,    47,     0,    59,    52,
       0,     0,     0,    30,    31,     0,    58,     0,     0,    65,
       0,     0,    99,   115,   100,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    20,     0,   141,    68,    46,    68,
      60,    70,    36,    29,    68,    35,    56,    55,    54,    32
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    45,   232,   230,    46,   102,   148,   112,   129,
      75,    76,    77,   183,    78,    79,    53,    54,    80,    55,
      56,   377,   319,    81,   238,    82,   108,    83,   133,   134,
     135,   220,    84,    85,   166,   272,   174,   175
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -216
static const yytype_int16 yypact[] =
{
    -216,   559,  -216,   -66,   -52,    -5,    -5,   393,   -52,   -52,
      37,    -5,    14,    65,    22,   328,   328,    14,   -52,   -32,
     -52,    65,   393,   -10,   -10,    14,    48,   383,   -40,   100,
     -32,   -32,   -40,   -32,   176,   125,   -40,   -40,   -40,    14,
     -32,    58,   -28,   -25,  -216,  -216,     0,  -216,   -52,  -216,
      -1,  -216,   448,    10,  -216,  -216,  -216,   193,    15,   448,
     448,  -216,  -216,     1,  -216,    24,  -216,  -216,    29,  -216,
      57,  -216,    36,   282,   448,  -216,  -216,    20,  -216,  -216,
    -216,  -216,  -216,  -216,  -216,    45,    66,   309,   319,   393,
      79,    83,    86,  -216,  -216,   448,    96,    68,   161,   110,
    -216,  -216,   114,   124,   122,   128,     3,  -216,   130,  -216,
     138,   149,  -216,  -216,   158,   166,   179,   187,   220,  -216,
     -52,   -52,   202,   228,   234,   247,   147,   147,   328,   248,
     174,   184,  -216,   250,  -216,   251,   256,    66,   267,    21,
    -216,   274,   276,  -216,   448,  -216,   448,  -216,  -216,   448,
    -216,   180,   357,   358,   372,   374,   377,    14,  -216,  -216,
     448,   448,   448,   382,   448,   448,   280,   433,   301,  -216,
    -216,  -216,    66,   314,  -216,   137,  -216,   393,   229,   246,
      57,   282,  -216,  -216,  -216,   310,  -216,  -216,   236,   319,
      65,   383,   121,   448,    14,    65,  -216,    65,   229,   324,
      65,    65,    14,   383,   448,    14,    14,  -216,  -216,  -216,
    -216,    14,    14,    14,    -5,  -216,  -216,   323,    14,   351,
     326,    25,   125,   448,   448,   -40,   403,    14,   393,    65,
     628,   540,   628,   558,   486,   332,  -216,   335,   336,   448,
     448,   448,   448,   415,  -216,   337,   339,   340,   147,  -216,
    -216,   121,  -216,   451,   257,   448,   448,   448,   420,   423,
     448,   448,   448,   448,   448,  -216,  -216,   347,  -216,  -216,
    -216,   349,   352,   280,   353,   459,  -216,  -216,   -52,  -216,
     354,  -216,   361,   365,  -216,   380,  -216,   381,   388,   -52,
     390,  -216,   397,  -216,   400,  -216,   405,   417,   419,    14,
    -216,   355,  -216,   184,   184,   422,   414,   418,   426,   448,
    -216,   427,   428,  -216,  -216,  -216,  -216,  -216,    14,  -216,
    -216,  -216,  -216,  -216,   448,  -216,  -216,  -216,   421,   431,
    -216,   282,   229,   432,   607,   675,   313,   448,   448,   296,
     296,  -216,  -216,  -216,  -216,   434,  -216,  -216,  -216,    65,
     -40,   124,    65,   393,    65,  -216,   229,   448,   236,    14,
     319,    14,  -216,  -216,  -216,  -216,   125,  -216,  -216,   236,
     437,   229,    65,  -216,  -216,   467,  -216,   438,   452,   440,
    -216,   366,   366,  -216,   443,   521,  -216,   449,  -216,  -216,
     454,   455,   456,   458,  -216,   471,  -216,   472,    14,  -216,
     473,   503,  -216,  -216,  -216,    65,   448,   -40,    14,   448,
      14,    14,   -40,    14,  -216,    65,  -216,   -52,  -216,   -52,
    -216,  -216,  -216,  -216,   -52,  -216,  -216,  -216,  -216,  -216
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -216,  -216,  -192,  -216,  -216,  -216,   140,    -4,    -6,   -68,
    -102,   227,     4,  -216,   -24,  -216,    -3,    32,    70,  -216,
    -216,   201,    72,   117,  -175,  -216,   510,    18,  -215,  -216,
    -216,   237,   -33,     7,   -94,   305,     2,    90
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -135
static const yytype_int16 yytable[] =
{
      49,   196,   136,    58,    87,    88,    89,   305,    90,    86,
      93,   132,   199,   278,   100,    47,   103,    97,    97,   182,
     186,   116,    96,    98,    86,   119,   105,   226,   115,   115,
      48,    92,   215,   216,   303,   101,   130,   137,   313,   104,
     315,   109,   109,    52,    59,   167,   168,   121,   171,    63,
      64,   145,    50,    51,   150,   146,    59,    60,   113,   113,
     117,   158,   159,   163,   124,   164,   165,    62,   138,   139,
     140,    50,    51,   106,   172,    62,   176,   169,    52,    50,
      51,   147,    91,   149,    94,   160,   273,    99,    61,   185,
     130,    86,   151,   187,   184,   111,   114,   157,   221,   120,
      61,    62,   177,   227,    48,    50,    51,    48,   161,   141,
     169,   170,    70,   162,    71,  -134,   209,   210,   -25,    48,
      73,   279,    57,    57,    63,    64,    71,    74,    57,   178,
      97,    52,    95,    59,    60,   217,   208,   143,   144,    74,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     179,   396,   192,    62,   328,   164,   165,    50,    51,    63,
      64,   188,   245,   246,   247,   189,   249,   250,   190,   159,
     122,   123,   193,   125,   268,   269,   270,    61,   191,    86,
     142,   266,   118,   392,    59,    60,    65,    66,   207,   136,
     173,   130,   194,   282,   397,   283,   195,   291,   132,   152,
     153,    70,   154,    71,   197,   115,   292,    72,   280,    73,
     198,   298,   200,   285,   131,   286,    74,   304,   288,   289,
     201,   236,   265,   281,   137,   306,   307,   244,    61,   330,
      86,   202,   311,   235,   231,   113,   233,    50,    51,   234,
     203,   320,   320,   320,   320,    65,    66,   312,   204,   386,
     107,   107,   126,   127,    71,   137,   333,   308,   219,   128,
      95,   205,   155,   156,   284,    59,    60,    74,   237,   206,
     364,   221,   290,    62,   348,   293,   294,    50,    51,    63,
      64,   295,   296,   297,   211,   355,    50,    51,   300,   276,
      59,    60,   394,    50,    51,   267,   271,   310,   274,   268,
     269,   270,    48,    50,    51,   277,   262,   263,   264,    61,
     212,   370,   321,   322,   323,   287,   213,    59,    60,   258,
     259,   260,   261,   262,   263,   264,   374,    59,    60,   214,
     218,    57,   222,   136,    61,    71,    59,    60,   223,    50,
      51,   331,   132,   224,   332,   334,   335,   336,    74,   225,
     339,   340,   341,   342,   343,    86,   228,   388,   229,   391,
      71,    61,   130,   239,   251,   240,    95,   384,   137,   362,
     387,    61,   389,    74,   260,   261,   262,   263,   264,   241,
      61,   242,   385,   243,   253,   180,   127,    71,   373,   248,
     400,    59,    60,   181,   275,   126,   127,    71,   252,   254,
      74,    59,    60,    95,    70,   299,    71,   301,   418,   309,
      74,   421,    95,   427,  -120,   428,   302,  -119,   318,    74,
     429,   324,   325,   417,   326,   327,   337,   381,   382,   393,
     338,   395,   344,   426,   345,    61,   349,   346,   347,   419,
     363,    59,    60,   350,   424,    61,    62,   351,   378,   378,
      50,    51,    63,    64,    65,    66,    59,    60,    67,    59,
      60,    71,   352,   353,    68,    69,    52,    95,   414,    70,
     354,    71,   356,   390,    74,   277,    72,    73,   420,   357,
     422,   423,   358,   425,    74,    61,   277,   359,   399,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   360,
      61,   361,   367,    61,   366,   375,   368,   252,   369,   371,
     372,    71,   268,   269,   270,   301,   376,    95,   380,   398,
     383,   401,   403,   402,    74,   405,    71,    70,   404,    71,
     406,   407,    95,   379,   110,    73,   408,   409,   410,    74,
     411,   365,    74,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   412,   413,   415,   329,     0,     0,     2,
       3,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   317,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,   416,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,     0,    36,     0,    37,    38,
      39,   256,   257,   258,   259,   260,   261,   262,   263,   264,
       0,   314,     0,     0,     0,    40,     0,     0,     0,     3,
       0,     0,     0,     0,     0,    41,    42,    43,     0,   316,
      44,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,     0,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,     0,    36,     0,    37,    38,    39,
     257,   258,   259,   260,   261,   262,   263,   264,     0,     0,
       0,     0,     0,     0,    40,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    41,    42,    43,     0,     0,    44
};

static const yytype_int16 yycheck[] =
{
       4,   103,    35,     6,     8,     9,    10,   222,    11,     7,
      14,    35,     9,   188,    18,    81,    20,    15,    16,    87,
      88,    27,    15,    16,    22,    29,    22,     6,    26,    27,
      82,    13,   126,   127,     9,    67,    34,    35,   230,    21,
     232,    23,    24,    83,     8,     9,    10,    29,    72,    59,
      60,    79,    57,    58,    52,    80,     8,     9,    26,    27,
      28,    59,    60,     6,    32,     8,     9,    53,    36,    37,
      38,    57,    58,    83,    72,    53,    74,    74,    83,    57,
      58,    81,    12,    84,    14,    84,   180,    17,    52,    87,
      88,    89,    82,    89,    87,    25,    26,    82,   131,    29,
      52,    53,    82,    82,    82,    57,    58,    82,    84,    39,
      74,    75,    76,    84,    78,    90,   120,   121,    81,    82,
      84,   189,     5,     6,    59,    60,    78,    91,    11,    84,
     128,    83,    84,     8,     9,   128,   118,    79,    80,    91,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      84,   366,    84,    53,   248,     8,     9,    57,    58,    59,
      60,    82,   160,   161,   162,    82,   164,   165,    82,   167,
      30,    31,    11,    33,    53,    54,    55,    52,    82,   177,
      40,   177,    82,   358,     8,     9,    61,    62,   118,   222,
      73,   189,    82,   191,   369,   193,    82,   203,   222,     6,
       7,    76,     9,    78,    82,   203,   204,    83,   190,    84,
      82,   214,    82,   195,    89,   197,    91,   221,   200,   201,
      82,   151,    85,   191,   222,   223,   224,   157,    52,   253,
     228,    82,   228,    53,   144,   203,   146,    57,    58,   149,
      82,   239,   240,   241,   242,    61,    62,   229,    82,   351,
      23,    24,    76,    77,    78,   253,   254,   225,    84,    83,
      84,    82,    69,    70,   194,     8,     9,    91,   151,    82,
     303,   304,   202,    53,   278,   205,   206,    57,    58,    59,
      60,   211,   212,   213,    82,   289,    57,    58,   218,    53,
       8,     9,   360,    57,    58,   178,   179,   227,   181,    53,
      54,    55,    82,    57,    58,   188,    10,    11,    12,    52,
      82,   309,   240,   241,   242,   198,    82,     8,     9,     6,
       7,     8,     9,    10,    11,    12,   324,     8,     9,    82,
      82,   214,    82,   366,    52,    78,     8,     9,    87,    57,
      58,    84,   366,    87,    87,   255,   256,   257,    91,    82,
     260,   261,   262,   263,   264,   353,    82,   353,    82,   357,
      78,    52,   360,     6,    84,     7,    84,   349,   366,   299,
     352,    52,   354,    91,     8,     9,    10,    11,    12,     7,
      52,     7,   350,     6,    83,    76,    77,    78,   318,     7,
     372,     8,     9,    84,    84,    76,    77,    78,    74,    85,
      91,     8,     9,    84,    76,    82,    78,    56,   406,     6,
      91,   409,    84,   417,    82,   419,    90,    82,    82,    91,
     424,     6,    85,   405,    85,    85,     6,   337,   338,   359,
       7,   361,    85,   415,    85,    52,    82,    85,    85,   407,
      85,     8,     9,    82,   412,    52,    53,    82,   331,   332,
      57,    58,    59,    60,    61,    62,     8,     9,    65,     8,
       9,    78,    82,    82,    71,    72,    83,    84,   398,    76,
      82,    78,    82,   356,    91,   358,    83,    84,   408,    82,
     410,   411,    82,   413,    91,    52,   369,    82,   371,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    82,
      52,    82,    88,    52,    82,    84,    88,    74,    82,    82,
      82,    78,    53,    54,    55,    56,    85,    84,    86,    82,
      86,    54,    70,    85,    91,    82,    78,    76,    88,    78,
       9,    82,    84,   332,    24,    84,    82,    82,    82,    91,
      82,   304,    91,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    82,    82,    82,   251,    -1,    -1,     0,
       1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    85,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    85,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    47,    -1,    49,    50,
      51,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      -1,    81,    -1,    -1,    -1,    66,    -1,    -1,    -1,     1,
      -1,    -1,    -1,    -1,    -1,    76,    77,    78,    -1,    81,
      81,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    -1,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    47,    -1,    49,    50,    51,
       5,     6,     7,     8,     9,    10,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    77,    78,    -1,    -1,    81
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    93,     0,     1,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    47,    49,    50,    51,
      66,    76,    77,    78,    81,    94,    97,    81,    82,    99,
      57,    58,    83,   108,   109,   111,   112,   115,   108,     8,
       9,    52,    53,    59,    60,    61,    62,    65,    71,    72,
      76,    78,    83,    84,    91,   102,   103,   104,   106,   107,
     110,   115,   117,   119,   124,   125,   128,    99,    99,    99,
     108,   110,   119,    99,   110,    84,   125,   128,   125,   110,
      99,    67,    98,    99,   119,   104,    83,   103,   118,   119,
     118,   110,   100,   109,   110,   128,   100,   109,    82,    99,
     110,   119,    98,    98,   109,    98,    76,    77,    83,   101,
     128,    89,   106,   120,   121,   122,   124,   128,   109,   109,
     109,   110,    98,    79,    80,    79,    80,    81,    99,    84,
     128,    82,     6,     7,     9,    69,    70,    82,   128,   128,
      84,    84,    84,     6,     8,     9,   126,     9,    10,    74,
      75,   106,   128,   115,   128,   129,   128,    82,    84,    84,
      76,    84,   101,   105,   125,   128,   101,   104,    82,    82,
      82,    82,    84,    11,    82,    82,   102,    82,    82,     9,
      82,    82,    82,    82,    82,    82,    82,   110,   119,    99,
      99,    82,    82,    82,    82,   126,   126,   125,    82,    84,
     123,   124,    82,    87,    87,    82,     6,    82,    82,    82,
      96,   129,    95,   129,   129,    53,   110,   115,   116,     6,
       7,     7,     7,     6,   110,   128,   128,   128,     7,   128,
     128,    84,    74,    83,    85,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    85,   104,   115,    53,    54,
      55,   115,   127,   126,   115,    84,    53,   115,   116,   101,
     119,   109,   128,   128,   110,   119,   119,   115,   119,   119,
     110,   100,   128,   110,   110,   110,   110,   110,   108,    82,
     110,    56,    90,     9,    99,   120,   128,   128,   109,     6,
     110,   104,   119,    94,    81,    94,    81,    85,    82,   114,
     128,   114,   114,   114,     6,    85,    85,    85,   126,   127,
     106,    84,    87,   128,   129,   129,   129,     6,     7,   129,
     129,   129,   129,   129,    85,    85,    85,    85,    99,    82,
      82,    82,    82,    82,    82,    99,    82,    82,    82,    82,
      82,    82,   110,    85,   124,   123,    82,    88,    88,    82,
     128,    82,    82,   110,   128,    84,    85,   113,   115,   113,
      86,   129,   129,    86,   119,   109,   102,   119,   104,   119,
     115,   128,   116,   110,   101,   110,   120,   116,    82,   115,
     119,    54,    85,    70,    88,    82,     9,    82,    82,    82,
      82,    82,    82,    82,   110,    82,    85,   119,   128,   109,
     110,   128,   110,   110,   109,   110,   119,    99,    99,    99
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:
#line 45 "a.y"
    {
		if((yyvsp[(1) - (2)].sym)->value != pc)
			yyerror("redeclaration of %s", (yyvsp[(1) - (2)].sym)->name);
		(yyvsp[(1) - (2)].sym)->value = pc;
	}
    break;

  case 6:
#line 52 "a.y"
    {
		(yyvsp[(1) - (2)].sym)->type = LLAB;
		(yyvsp[(1) - (2)].sym)->value = pc;
	}
    break;

  case 8:
#line 58 "a.y"
    {
		(yyvsp[(1) - (4)].sym)->type = LVAR;
		(yyvsp[(1) - (4)].sym)->value = (yyvsp[(3) - (4)].lval);
	}
    break;

  case 9:
#line 63 "a.y"
    {
		if((yyvsp[(1) - (4)].sym)->value != (yyvsp[(3) - (4)].lval))
			yyerror("redeclaration of %s", (yyvsp[(1) - (4)].sym)->name);
		(yyvsp[(1) - (4)].sym)->value = (yyvsp[(3) - (4)].lval);
	}
    break;

  case 13:
#line 77 "a.y"
    {
		outcode((yyvsp[(1) - (2)].lval), &nullgen, NREG, &nullgen);
	}
    break;

  case 14:
#line 84 "a.y"
    {
		outcode((yyvsp[(1) - (6)].lval), &(yyvsp[(2) - (6)].addr), (yyvsp[(4) - (6)].lval), &(yyvsp[(6) - (6)].addr));
	}
    break;

  case 15:
#line 88 "a.y"
    {
		outcode((yyvsp[(1) - (5)].lval), &(yyvsp[(2) - (5)].addr), (yyvsp[(4) - (5)].lval), &nullgen);
	}
    break;

  case 16:
#line 92 "a.y"
    {
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(2) - (4)].addr), NREG, &(yyvsp[(4) - (4)].addr));
	}
    break;

  case 17:
#line 99 "a.y"
    {
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(2) - (4)].addr), NREG, &(yyvsp[(4) - (4)].addr));
	}
    break;

  case 18:
#line 106 "a.y"
    {
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(2) - (4)].addr), NREG, &(yyvsp[(4) - (4)].addr));
	}
    break;

  case 19:
#line 113 "a.y"
    {
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(2) - (4)].addr), NREG, &(yyvsp[(4) - (4)].addr));
	}
    break;

  case 20:
#line 117 "a.y"
    {
		Addr a;
		a = nullgen;
		a.type = D_CONST;
		a.offset = (yyvsp[(5) - (7)].lval);
		outgcode((yyvsp[(1) - (7)].lval), &(yyvsp[(2) - (7)].addr), NREG, &a, &(yyvsp[(7) - (7)].addr));
	}
    break;

  case 21:
#line 128 "a.y"
    {
		outcode((yyvsp[(1) - (3)].lval), &nullgen, NREG, &(yyvsp[(3) - (3)].addr));
	}
    break;

  case 22:
#line 132 "a.y"
    {
		outcode((yyvsp[(1) - (3)].lval), &nullgen, NREG, &(yyvsp[(3) - (3)].addr));
	}
    break;

  case 23:
#line 139 "a.y"
    {
		outcode((yyvsp[(1) - (3)].lval), &nullgen, NREG, &(yyvsp[(3) - (3)].addr));
	}
    break;

  case 24:
#line 146 "a.y"
    {
		outcode((yyvsp[(1) - (3)].lval), &nullgen, NREG, &(yyvsp[(3) - (3)].addr));
	}
    break;

  case 25:
#line 150 "a.y"
    {
		outcode((yyvsp[(1) - (1)].lval), &nullgen, NREG, &nullgen);
	}
    break;

  case 26:
#line 157 "a.y"
    {
		outcode((yyvsp[(1) - (5)].lval), &(yyvsp[(2) - (5)].addr), (yyvsp[(4) - (5)].lval), &nullgen);
	}
    break;

  case 27:
#line 164 "a.y"
    {
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(2) - (4)].addr), NREG, &(yyvsp[(4) - (4)].addr));
	}
    break;

  case 28:
#line 171 "a.y"
    {
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(2) - (4)].addr), NREG, &(yyvsp[(4) - (4)].addr));
	}
    break;

  case 29:
#line 178 "a.y"
    {
		outgcode((yyvsp[(1) - (8)].lval), &(yyvsp[(2) - (8)].addr), (yyvsp[(6) - (8)].addr).reg, &(yyvsp[(4) - (8)].addr), &(yyvsp[(8) - (8)].addr));
	}
    break;

  case 30:
#line 182 "a.y"
    {
		outcode((yyvsp[(1) - (6)].lval), &(yyvsp[(2) - (6)].addr), (yyvsp[(4) - (6)].addr).reg, &(yyvsp[(6) - (6)].addr));
	}
    break;

  case 31:
#line 189 "a.y"
    {
		outcode((yyvsp[(1) - (6)].lval), &(yyvsp[(2) - (6)].addr), (yyvsp[(4) - (6)].addr).reg, &(yyvsp[(6) - (6)].addr));
	}
    break;

  case 32:
#line 196 "a.y"
    {
		outgcode((yyvsp[(1) - (9)].lval), &(yyvsp[(2) - (9)].addr), (yyvsp[(6) - (9)].addr).reg, &(yyvsp[(4) - (9)].addr), &(yyvsp[(8) - (9)].addr));
	}
    break;

  case 33:
#line 203 "a.y"
    {
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(2) - (4)].addr), NREG, &(yyvsp[(4) - (4)].addr));
	}
    break;

  case 34:
#line 207 "a.y"
    {
		outcode((yyvsp[(1) - (5)].lval), &(yyvsp[(3) - (5)].addr), NREG, &(yyvsp[(5) - (5)].addr));
	}
    break;

  case 35:
#line 214 "a.y"
    {
		outgcode((yyvsp[(1) - (8)].lval), &(yyvsp[(2) - (8)].addr), (yyvsp[(6) - (8)].lval), &(yyvsp[(4) - (8)].addr), &(yyvsp[(8) - (8)].addr));
	}
    break;

  case 36:
#line 221 "a.y"
    {
		outgcode((yyvsp[(1) - (8)].lval), &(yyvsp[(2) - (8)].addr), (yyvsp[(6) - (8)].lval), &(yyvsp[(4) - (8)].addr), &(yyvsp[(8) - (8)].addr));
	}
    break;

  case 37:
#line 228 "a.y"
    {
		outcode((yyvsp[(1) - (2)].lval), &nullgen, NREG, &nullgen);
	}
    break;

  case 38:
#line 232 "a.y"
    {
		outcode((yyvsp[(1) - (2)].lval), &nullgen, NREG, &(yyvsp[(2) - (2)].addr));
	}
    break;

  case 39:
#line 239 "a.y"
    {
		outcode((yyvsp[(1) - (2)].lval), &nullgen, NREG, &nullgen);
	}
    break;

  case 40:
#line 243 "a.y"
    {
		outcode((yyvsp[(1) - (3)].lval), &(yyvsp[(2) - (3)].addr), NREG, &nullgen);
	}
    break;

  case 41:
#line 247 "a.y"
    {
		outcode((yyvsp[(1) - (3)].lval), &(yyvsp[(2) - (3)].addr), NREG, &nullgen);
	}
    break;

  case 42:
#line 251 "a.y"
    {
		outcode((yyvsp[(1) - (3)].lval), &nullgen, NREG, &(yyvsp[(3) - (3)].addr));
	}
    break;

  case 43:
#line 255 "a.y"
    {
		outcode((yyvsp[(1) - (3)].lval), &nullgen, NREG, &(yyvsp[(3) - (3)].addr));
	}
    break;

  case 44:
#line 262 "a.y"
    {
		settext((yyvsp[(2) - (4)].addr).sym);
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(2) - (4)].addr), NREG, &(yyvsp[(4) - (4)].addr));
	}
    break;

  case 45:
#line 267 "a.y"
    {
		settext((yyvsp[(2) - (6)].addr).sym);
		(yyvsp[(6) - (6)].addr).offset &= 0xffffffffull;
		(yyvsp[(6) - (6)].addr).offset |= (vlong)ArgsSizeUnknown << 32;
		outcode((yyvsp[(1) - (6)].lval), &(yyvsp[(2) - (6)].addr), (yyvsp[(4) - (6)].lval), &(yyvsp[(6) - (6)].addr));
	}
    break;

  case 46:
#line 274 "a.y"
    {
		settext((yyvsp[(2) - (8)].addr).sym);
		(yyvsp[(6) - (8)].addr).offset &= 0xffffffffull;
		(yyvsp[(6) - (8)].addr).offset |= ((yyvsp[(8) - (8)].lval) & 0xffffffffull) << 32;
		outcode((yyvsp[(1) - (8)].lval), &(yyvsp[(2) - (8)].addr), (yyvsp[(4) - (8)].lval), &(yyvsp[(6) - (8)].addr));
	}
    break;

  case 47:
#line 284 "a.y"
    {
		outcode((yyvsp[(1) - (6)].lval), &(yyvsp[(2) - (6)].addr), (yyvsp[(4) - (6)].lval), &(yyvsp[(6) - (6)].addr));
	}
    break;

  case 48:
#line 291 "a.y"
    {
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(2) - (4)].addr), NREG, &(yyvsp[(4) - (4)].addr));
	}
    break;

  case 49:
#line 298 "a.y"
    {
		outcode((yyvsp[(1) - (3)].lval), &nullgen, NREG, &(yyvsp[(3) - (3)].addr));
	}
    break;

  case 50:
#line 305 "a.y"
    {
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(2) - (4)].addr), NREG, &(yyvsp[(4) - (4)].addr));
	}
    break;

  case 51:
#line 312 "a.y"
    {
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(2) - (4)].addr), NREG, &(yyvsp[(4) - (4)].addr));
	}
    break;

  case 52:
#line 316 "a.y"
    {
		outcode((yyvsp[(1) - (6)].lval), &(yyvsp[(2) - (6)].addr), (yyvsp[(4) - (6)].addr).reg, &(yyvsp[(6) - (6)].addr));
	}
    break;

  case 53:
#line 323 "a.y"
    {
		outcode((yyvsp[(1) - (5)].lval), &(yyvsp[(2) - (5)].addr), (yyvsp[(4) - (5)].addr).reg, &nullgen);
	}
    break;

  case 54:
#line 330 "a.y"
    {
		outgcode((yyvsp[(1) - (9)].lval), &(yyvsp[(2) - (9)].addr), (yyvsp[(6) - (9)].addr).reg, &(yyvsp[(4) - (9)].addr), &(yyvsp[(8) - (9)].addr));
	}
    break;

  case 55:
#line 337 "a.y"
    {
		outgcode((yyvsp[(1) - (9)].lval), &(yyvsp[(2) - (9)].addr), (yyvsp[(4) - (9)].addr).reg, &(yyvsp[(6) - (9)].addr), &(yyvsp[(8) - (9)].addr));
	}
    break;

  case 56:
#line 344 "a.y"
    {
		outgcode((yyvsp[(1) - (8)].lval), &(yyvsp[(2) - (8)].addr), (yyvsp[(6) - (8)].addr).reg, &(yyvsp[(4) - (8)].addr), &(yyvsp[(8) - (8)].addr));
	}
    break;

  case 57:
#line 351 "a.y"
    {
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(2) - (4)].addr), NREG, &(yyvsp[(4) - (4)].addr));
	}
    break;

  case 58:
#line 355 "a.y"
    {
		outcode((yyvsp[(1) - (6)].lval), &(yyvsp[(2) - (6)].addr), (yyvsp[(4) - (6)].addr).reg, &(yyvsp[(6) - (6)].addr));
	}
    break;

  case 59:
#line 362 "a.y"
    {
		outcode((yyvsp[(1) - (6)].lval), &(yyvsp[(2) - (6)].addr), (yyvsp[(4) - (6)].lval), &(yyvsp[(6) - (6)].addr));
	}
    break;

  case 60:
#line 369 "a.y"
    {
		outgcode((yyvsp[(1) - (8)].lval), &(yyvsp[(2) - (8)].addr), (yyvsp[(6) - (8)].lval), &(yyvsp[(4) - (8)].addr), &(yyvsp[(8) - (8)].addr));
	}
    break;

  case 61:
#line 376 "a.y"
    {
		outcode((yyvsp[(1) - (2)].lval), &(yyvsp[(2) - (2)].addr), NREG, &nullgen);
	}
    break;

  case 62:
#line 380 "a.y"
    {
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(4) - (4)].addr), (yyvsp[(2) - (4)].addr).reg, &nullgen);
	}
    break;

  case 63:
#line 384 "a.y"
    {
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(2) - (4)].addr), NREG, &(yyvsp[(4) - (4)].addr));
	}
    break;

  case 64:
#line 391 "a.y"
    {
		outcode((yyvsp[(1) - (2)].lval), &(yyvsp[(2) - (2)].addr), NREG, &nullgen);
	}
    break;

  case 65:
#line 398 "a.y"
    {
		outcode((yyvsp[(1) - (6)].lval), &(yyvsp[(2) - (6)].addr), (yyvsp[(6) - (6)].lval), &(yyvsp[(4) - (6)].addr));
	}
    break;

  case 66:
#line 405 "a.y"
    {
		outcode((yyvsp[(1) - (2)].lval), &nullgen, NREG, &nullgen);
	}
    break;

  case 67:
#line 411 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_COND;
		(yyval.addr).reg = (yyvsp[(1) - (1)].lval);
	}
    break;

  case 70:
#line 422 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_CONST;
		(yyval.addr).offset = SYSARG4((yyvsp[(1) - (7)].lval), (yyvsp[(3) - (7)].lval), (yyvsp[(5) - (7)].lval), (yyvsp[(7) - (7)].lval));
	}
    break;

  case 72:
#line 431 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_BRANCH;
		(yyval.addr).offset = (yyvsp[(1) - (4)].lval) + pc;
	}
    break;

  case 73:
#line 437 "a.y"
    {
		(yyval.addr) = nullgen;
		if(pass == 2)
			yyerror("undefined label: %s", (yyvsp[(1) - (2)].sym)->name);
		(yyval.addr).type = D_BRANCH;
		(yyval.addr).offset = (yyvsp[(2) - (2)].lval);
	}
    break;

  case 74:
#line 445 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_BRANCH;
		(yyval.addr).offset = (yyvsp[(1) - (2)].sym)->value + (yyvsp[(2) - (2)].lval);
	}
    break;

  case 75:
#line 452 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_CONST;
		(yyval.addr).offset = (yyvsp[(2) - (2)].lval);
	}
    break;

  case 76:
#line 458 "a.y"
    {
		(yyval.addr) = (yyvsp[(2) - (2)].addr);
		(yyval.addr).type = D_CONST;
	}
    break;

  case 77:
#line 463 "a.y"
    {
		(yyval.addr) = (yyvsp[(4) - (4)].addr);
		(yyval.addr).type = D_OCONST;
	}
    break;

  case 78:
#line 468 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SCONST;
		memmove((yyval.addr).u.sval, (yyvsp[(2) - (2)].sval), sizeof((yyval.addr).u.sval));
	}
    break;

  case 80:
#line 477 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FCONST;
		(yyval.addr).u.dval = (yyvsp[(2) - (2)].dval);
	}
    break;

  case 81:
#line 483 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FCONST;
		(yyval.addr).u.dval = -(yyvsp[(3) - (3)].dval);
	}
    break;

  case 84:
#line 493 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SPR;
		(yyval.addr).offset = (yyvsp[(1) - (1)].lval);
	}
    break;

  case 85:
#line 499 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).offset = (yyvsp[(1) - (1)].lval);
	}
    break;

  case 90:
#line 511 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[(2) - (3)].lval);
		(yyval.addr).offset = 0;
	}
    break;

  case 91:
#line 518 "a.y"
    {
		(yyval.addr) = (yyvsp[(1) - (1)].addr);
		if((yyvsp[(1) - (1)].addr).name != D_EXTERN && (yyvsp[(1) - (1)].addr).name != D_STATIC) {
		}
	}
    break;

  case 93:
#line 527 "a.y"
    {
		(yyval.addr) = (yyvsp[(1) - (4)].addr);
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[(3) - (4)].lval);
	}
    break;

  case 95:
#line 536 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[(2) - (3)].lval);
		(yyval.addr).offset = 0;
	}
    break;

  case 96:
#line 543 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[(3) - (4)].lval);
		(yyval.addr).offset = (yyvsp[(1) - (4)].lval);
	}
    break;

  case 97:
#line 550 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_XPRE;
		(yyval.addr).reg = (yyvsp[(3) - (5)].lval);
		(yyval.addr).offset = (yyvsp[(1) - (5)].lval);
	}
    break;

  case 98:
#line 557 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_XPOST;
		(yyval.addr).reg = (yyvsp[(2) - (5)].lval);
		(yyval.addr).offset = (yyvsp[(4) - (5)].lval);
	}
    break;

  case 99:
#line 564 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_ROFF;
		(yyval.addr).reg = (yyvsp[(2) - (6)].lval);
		(yyval.addr).scale = (yyvsp[(5) - (6)].lval) & 0x1f;
		(yyval.addr).offset = (yyvsp[(5) - (6)].lval);
	}
    break;

  case 100:
#line 572 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_ROFF;
		(yyval.addr).reg = (yyvsp[(2) - (6)].lval);
		(yyval.addr).scale = (yyvsp[(5) - (6)].lval) & 0x1f;
		(yyval.addr).offset = (yyvsp[(5) - (6)].lval) | (1<<16);
	}
    break;

  case 104:
#line 586 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_CONST;
		(yyval.addr).offset = (yyvsp[(2) - (2)].lval);
	}
    break;

  case 105:
#line 594 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_REG;
		(yyval.addr).reg = (yyvsp[(1) - (1)].lval);
	}
    break;

  case 106:
#line 600 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SP;
		(yyval.addr).reg = REGSP;
	}
    break;

  case 107:
#line 608 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = ((yyvsp[(1) - (4)].lval) << 16) | ((yyvsp[(4) - (4)].lval) << 10) | (0 << 22);
	}
    break;

  case 108:
#line 614 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = (((yyvsp[(1) - (4)].lval)&0x1F) << 16) | ((yyvsp[(4) - (4)].lval) << 10) | (1 << 22);
	}
    break;

  case 109:
#line 620 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = ((yyvsp[(1) - (4)].lval) << 16) | ((yyvsp[(4) - (4)].lval) << 10) | (2 << 22);
	}
    break;

  case 110:
#line 626 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = ((yyvsp[(1) - (4)].lval) << 16) | ((yyvsp[(4) - (4)].lval) << 10) | (3 << 22);
	}
    break;

  case 111:
#line 634 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_REG;
		(yyval.addr).reg = (yyvsp[(1) - (1)].lval);
	}
    break;

  case 112:
#line 640 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_EXTREG;
		(yyval.addr).reg = (yyvsp[(1) - (2)].lval);
		(yyval.addr).offset = ((yyvsp[(1) - (2)].lval) << 16) | ((yyvsp[(2) - (2)].lval) << 13);
	}
    break;

  case 113:
#line 647 "a.y"
    {
		if((yyvsp[(5) - (5)].lval) < 0 || (yyvsp[(5) - (5)].lval) > 4)
			yyerror("shift value out of range");
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_EXTREG;
		(yyval.addr).reg = (yyvsp[(1) - (5)].lval);
		(yyval.addr).offset = ((yyvsp[(1) - (5)].lval) << 16) | ((yyvsp[(2) - (5)].lval) << 13) | ((yyvsp[(5) - (5)].lval) << 10);
	}
    break;

  case 114:
#line 658 "a.y"
    {
		(yyval.lval) = (3 << 8) | (yyvsp[(1) - (1)].lval);
	}
    break;

  case 115:
#line 662 "a.y"
    {
		(yyval.lval) = ((yyvsp[(2) - (2)].lval) << 8) | (yyvsp[(1) - (2)].lval);
	}
    break;

  case 116:
#line 668 "a.y"
    {
		if((yyval.lval) < 0 || (yyval.lval) >= 64)
			yyerror("shift value out of range");
		(yyval.lval) = (yyvsp[(1) - (1)].lval)&0x3F;
	}
    break;

  case 118:
#line 677 "a.y"
    {
		if((yyvsp[(3) - (4)].lval) < 0 || (yyvsp[(3) - (4)].lval) >= NREG)
			print("register value out of range\n");
		(yyval.lval) = (yyvsp[(3) - (4)].lval);
	}
    break;

  case 120:
#line 686 "a.y"
    {
		(yyval.lval) = REGSP;
	}
    break;

  case 121:
#line 692 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SPR;
		(yyval.addr).offset = (yyvsp[(1) - (1)].lval);
	}
    break;

  case 122:
#line 698 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = (yyvsp[(1) - (4)].lval);
		(yyval.addr).offset = (yyvsp[(3) - (4)].lval);
	}
    break;

  case 125:
#line 710 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FREG;
		(yyval.addr).reg = (yyvsp[(1) - (1)].lval);
	}
    break;

  case 126:
#line 716 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FREG;
		(yyval.addr).reg = (yyvsp[(3) - (4)].lval);
	}
    break;

  case 130:
#line 727 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_VSET;
		(yyval.addr).offset = (yyvsp[(1) - (1)].lval);
	}
    break;

  case 131:
#line 735 "a.y"
    {
		(yyval.addr).type = D_VLANE;
		(yyval.addr).offset = (yyvsp[(3) - (4)].lval);
	}
    break;

  case 132:
#line 740 "a.y"
    {
		(yyval.addr).type = D_VLANE;
		(yyval.addr).offset = (yyvsp[(3) - (4)].lval);
	}
    break;

  case 133:
#line 747 "a.y"
    {
		(yyval.lval) = (yyvsp[(2) - (3)].lval);
	}
    break;

  case 134:
#line 753 "a.y"
    {
		(yyval.lval) = 1 << (yyvsp[(1) - (1)].addr).reg;
	}
    break;

  case 135:
#line 757 "a.y"
    {
		int i;
		(yyval.lval)=0;
		for(i=(yyvsp[(1) - (3)].addr).reg; i<=(yyvsp[(3) - (3)].addr).reg; i++)
			(yyval.lval) |= 1<<i;
		for(i=(yyvsp[(3) - (3)].addr).reg; i<=(yyvsp[(1) - (3)].addr).reg; i++)
			(yyval.lval) |= 1<<i;
	}
    break;

  case 136:
#line 766 "a.y"
    {
		(yyval.lval) = (1<<(yyvsp[(1) - (3)].addr).reg) | (yyvsp[(3) - (3)].lval);
	}
    break;

  case 137:
#line 772 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_VREG;
		(yyval.addr).reg = (yyvsp[(1) - (1)].lval);
		/* TO DO: slice */
	}
    break;

  case 138:
#line 779 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_VREG;
		(yyval.addr).reg = (yyvsp[(3) - (4)].lval);
	}
    break;

  case 139:
#line 787 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).name = (yyvsp[(3) - (4)].lval);
		(yyval.addr).sym = nil;
		(yyval.addr).offset = (yyvsp[(1) - (4)].lval);
	}
    break;

  case 140:
#line 795 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).name = (yyvsp[(4) - (5)].lval);
		(yyval.addr).sym = linklookup(ctxt, (yyvsp[(1) - (5)].sym)->name, 0);
		(yyval.addr).offset = (yyvsp[(2) - (5)].lval);
	}
    break;

  case 141:
#line 803 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).name = D_STATIC;
		(yyval.addr).sym = linklookup(ctxt, (yyvsp[(1) - (7)].sym)->name, 0);
		(yyval.addr).offset = (yyvsp[(4) - (7)].lval);
	}
    break;

  case 142:
#line 812 "a.y"
    {
		(yyval.lval) = 0;
	}
    break;

  case 143:
#line 816 "a.y"
    {
		(yyval.lval) = (yyvsp[(2) - (2)].lval);
	}
    break;

  case 144:
#line 820 "a.y"
    {
		(yyval.lval) = -(yyvsp[(2) - (2)].lval);
	}
    break;

  case 149:
#line 832 "a.y"
    {
		(yyval.lval) = (yyvsp[(1) - (1)].sym)->value;
	}
    break;

  case 150:
#line 836 "a.y"
    {
		(yyval.lval) = -(yyvsp[(2) - (2)].lval);
	}
    break;

  case 151:
#line 840 "a.y"
    {
		(yyval.lval) = (yyvsp[(2) - (2)].lval);
	}
    break;

  case 152:
#line 844 "a.y"
    {
		(yyval.lval) = ~(yyvsp[(2) - (2)].lval);
	}
    break;

  case 153:
#line 848 "a.y"
    {
		(yyval.lval) = (yyvsp[(2) - (3)].lval);
	}
    break;

  case 155:
#line 855 "a.y"
    {
		(yyval.lval) = (yyvsp[(1) - (3)].lval) + (yyvsp[(3) - (3)].lval);
	}
    break;

  case 156:
#line 859 "a.y"
    {
		(yyval.lval) = (yyvsp[(1) - (3)].lval) - (yyvsp[(3) - (3)].lval);
	}
    break;

  case 157:
#line 863 "a.y"
    {
		(yyval.lval) = (yyvsp[(1) - (3)].lval) * (yyvsp[(3) - (3)].lval);
	}
    break;

  case 158:
#line 867 "a.y"
    {
		(yyval.lval) = (yyvsp[(1) - (3)].lval) / (yyvsp[(3) - (3)].lval);
	}
    break;

  case 159:
#line 871 "a.y"
    {
		(yyval.lval) = (yyvsp[(1) - (3)].lval) % (yyvsp[(3) - (3)].lval);
	}
    break;

  case 160:
#line 875 "a.y"
    {
		(yyval.lval) = (yyvsp[(1) - (4)].lval) << (yyvsp[(4) - (4)].lval);
	}
    break;

  case 161:
#line 879 "a.y"
    {
		(yyval.lval) = (yyvsp[(1) - (4)].lval) >> (yyvsp[(4) - (4)].lval);
	}
    break;

  case 162:
#line 883 "a.y"
    {
		(yyval.lval) = (yyvsp[(1) - (3)].lval) & (yyvsp[(3) - (3)].lval);
	}
    break;

  case 163:
#line 887 "a.y"
    {
		(yyval.lval) = (yyvsp[(1) - (3)].lval) ^ (yyvsp[(3) - (3)].lval);
	}
    break;

  case 164:
#line 891 "a.y"
    {
		(yyval.lval) = (yyvsp[(1) - (3)].lval) | (yyvsp[(3) - (3)].lval);
	}
    break;


/* Line 1267 of yacc.c.  */
#line 2909 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



