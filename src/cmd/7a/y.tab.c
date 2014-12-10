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
#line 8 "a.y"
{
	Sym	*sym;
	vlong	lval;
	double	dval;
	char	sval[NSNAME];
	Addr	addr;
}
/* Line 193 of yacc.c.  */
#line 247 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 260 "y.tab.c"

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
#define YYLAST   711

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  92
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  163
/* YYNRULES -- Number of states.  */
#define YYNSTATES  428

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
     186,   190,   194,   198,   202,   207,   214,   221,   226,   230,
     235,   240,   247,   253,   263,   273,   282,   287,   294,   301,
     310,   313,   318,   323,   326,   333,   336,   338,   339,   342,
     350,   352,   357,   360,   363,   366,   369,   374,   377,   379,
     382,   386,   388,   390,   392,   394,   396,   398,   400,   402,
     406,   408,   410,   415,   417,   421,   426,   432,   438,   445,
     452,   454,   456,   458,   461,   463,   465,   470,   475,   480,
     485,   487,   490,   496,   498,   501,   503,   505,   510,   512,
     514,   516,   521,   523,   525,   527,   532,   534,   536,   538,
     540,   545,   550,   554,   556,   560,   564,   566,   571,   576,
     582,   590,   591,   594,   597,   599,   601,   603,   605,   607,
     610,   613,   616,   620,   622,   626,   630,   634,   638,   642,
     647,   652,   656,   660
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
     128,    82,   109,    -1,    25,   125,    11,   128,    82,   102,
      -1,    26,   110,    82,   110,    -1,    30,    99,   102,    -1,
      31,   119,    82,   119,    -1,    33,   118,    82,   119,    -1,
      33,   118,    82,   119,    82,   119,    -1,    34,   118,    82,
     119,    99,    -1,    28,    98,    82,   119,    82,   119,    82,
     109,    99,    -1,    22,   119,    82,   119,    82,   119,    82,
     119,    99,    -1,    66,    98,    82,   119,    82,   119,    82,
     119,    -1,    45,   120,    82,   120,    -1,    45,   120,    82,
     120,    82,   120,    -1,    32,   104,    82,   115,    82,   104,
      -1,    35,   110,    82,   110,    82,   115,    82,   110,    -1,
      36,   100,    -1,    36,   110,    82,   100,    -1,    37,   100,
      82,   110,    -1,    50,   109,    -1,    51,   110,    82,   104,
      82,   115,    -1,    27,    99,    -1,    67,    -1,    -1,    82,
      99,    -1,   128,    82,   128,    82,   128,    82,   128,    -1,
     109,    -1,   128,    84,    56,    85,    -1,    76,   126,    -1,
      77,   126,    -1,    83,   128,    -1,    83,   106,    -1,    83,
      10,    83,   106,    -1,    83,    75,    -1,   103,    -1,    83,
      74,    -1,    83,     9,    74,    -1,   110,    -1,   102,    -1,
      65,    -1,   128,    -1,   106,    -1,   119,    -1,   124,    -1,
     117,    -1,    84,   115,    85,    -1,   125,    -1,   125,    -1,
     125,    84,   115,    85,    -1,   107,    -1,    84,   115,    85,
      -1,   128,    84,   115,    85,    -1,   128,    84,   115,    85,
      86,    -1,    84,   115,    85,   128,    86,    -1,    84,   115,
      85,    84,   113,    85,    -1,    84,   115,    85,    87,   113,
      88,    -1,   109,    -1,   111,    -1,   112,    -1,    83,   128,
      -1,   115,    -1,    53,    -1,   115,     6,     6,   114,    -1,
     115,     7,     7,   114,    -1,   115,     9,     7,   114,    -1,
     115,    69,     7,   114,    -1,   115,    -1,   115,    70,    -1,
     115,    70,     6,     6,   128,    -1,   115,    -1,   115,    70,
      -1,   128,    -1,    58,    -1,    57,    84,   129,    85,    -1,
     115,    -1,    53,    -1,    72,    -1,    71,    84,   128,    85,
      -1,   119,    -1,   103,    -1,    60,    -1,    59,    84,   128,
      85,    -1,   106,    -1,   124,    -1,   121,    -1,   122,    -1,
     124,    87,   128,    88,    -1,   122,    87,   128,    88,    -1,
      89,   123,    90,    -1,   124,    -1,   124,     9,   124,    -1,
     124,    99,   123,    -1,    62,    -1,    61,    84,   128,    85,
      -1,   128,    84,   127,    85,    -1,    76,   126,    84,   127,
      85,    -1,    76,     6,     7,   126,    84,    54,    85,    -1,
      -1,     8,   128,    -1,     9,   128,    -1,    54,    -1,    53,
      -1,    55,    -1,    52,    -1,    78,    -1,     9,   128,    -1,
       8,   128,    -1,    91,   128,    -1,    84,   129,    85,    -1,
     128,    -1,   129,     8,   129,    -1,   129,     9,   129,    -1,
     129,    10,   129,    -1,   129,    11,   129,    -1,   129,    12,
     129,    -1,   129,     6,     6,   129,    -1,   129,     7,     7,
     129,    -1,   129,     5,   129,    -1,   129,     4,   129,    -1,
     129,     3,   129,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    39,    39,    40,    44,    43,    51,    50,    56,    61,
      67,    68,    69,    75,    82,    86,    90,    97,   104,   111,
     115,   126,   130,   137,   144,   148,   155,   162,   169,   176,
     180,   187,   194,   201,   205,   212,   219,   226,   230,   237,
     241,   245,   249,   253,   260,   264,   271,   278,   285,   292,
     299,   303,   310,   317,   324,   331,   338,   342,   349,   356,
     363,   367,   371,   378,   385,   392,   398,   405,   406,   409,
     415,   418,   424,   432,   439,   445,   450,   455,   461,   464,
     470,   478,   479,   480,   486,   492,   493,   494,   495,   498,
     505,   513,   514,   520,   523,   530,   537,   544,   549,   557,
     567,   568,   569,   571,   579,   585,   593,   599,   605,   611,
     619,   625,   632,   643,   647,   653,   661,   662,   670,   671,
     677,   683,   691,   692,   695,   701,   709,   710,   711,   712,
     720,   725,   732,   738,   742,   751,   757,   764,   772,   780,
     788,   798,   801,   805,   811,   812,   813,   816,   817,   821,
     825,   829,   833,   839,   840,   844,   848,   852,   856,   860,
     864,   868,   872,   876
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
      97,    97,    97,    97,    97,    97,    98,    99,    99,   100,
     100,   101,   101,   101,   102,   102,   102,   102,   102,   103,
     103,   104,   104,   104,   104,   104,   104,   104,   104,   105,
     105,   106,   106,   106,   107,   107,   107,   107,   107,   107,
     108,   108,   108,   109,   110,   110,   111,   111,   111,   111,
     112,   112,   112,   113,   113,   114,   115,   115,   116,   116,
     117,   117,   118,   118,   119,   119,   120,   120,   120,   120,
     121,   121,   122,   123,   123,   123,   124,   124,   125,   125,
     125,   126,   126,   126,   127,   127,   127,   128,   128,   128,
     128,   128,   128,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     0,     4,     0,     4,     4,     4,
       1,     2,     2,     2,     6,     5,     4,     4,     4,     4,
       7,     3,     3,     3,     3,     1,     5,     4,     4,     8,
       6,     6,     9,     4,     5,     8,     8,     2,     2,     2,
       3,     3,     3,     3,     4,     6,     6,     4,     3,     4,
       4,     6,     5,     9,     9,     8,     4,     6,     6,     8,
       2,     4,     4,     2,     6,     2,     1,     0,     2,     7,
       1,     4,     2,     2,     2,     2,     4,     2,     1,     2,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     4,     1,     3,     4,     5,     5,     6,     6,
       1,     1,     1,     2,     1,     1,     4,     4,     4,     4,
       1,     2,     5,     1,     2,     1,     1,     4,     1,     1,
       1,     4,     1,     1,     1,     4,     1,     1,     1,     1,
       4,     4,     3,     1,     3,     3,     1,     4,     4,     5,
       7,     0,     2,     2,     1,     1,     1,     1,     1,     2,
       2,     2,     3,     1,     3,     3,     3,     3,     3,     4,
       4,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,    67,     0,     0,     0,    67,    67,
      67,     0,     0,     0,    67,     0,     0,     0,    67,     0,
      67,     0,     0,     0,     0,     0,     0,     0,     0,    67,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    10,     3,     0,    12,    67,    13,
       0,   116,     0,     0,   100,   101,   102,   110,     0,     0,
       0,   147,   105,     0,   124,     0,   136,    83,     0,   120,
     141,   148,     0,     0,     0,    82,    78,     0,    85,    93,
      81,   104,    88,    86,    87,    91,    84,     0,     0,     0,
       0,     0,     0,    37,    38,     0,     0,     0,     0,     0,
      65,    66,     0,     0,     0,     0,     0,   123,     0,   122,
       0,     0,    60,    70,     0,     0,     0,     0,    67,    39,
      67,    67,     0,     0,     0,     0,   141,   141,     0,     0,
       0,     0,   126,     0,   128,   129,   127,     0,     0,     0,
      63,     0,     0,     6,     0,     4,     0,    11,    68,     0,
     103,     0,     0,     0,     0,     0,   111,     0,   150,   149,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    79,
      77,    75,    74,     0,   153,     0,   151,     0,     0,     0,
     141,     0,    21,    22,    90,     0,    23,    24,     0,     0,
       0,     0,     0,     0,     0,     0,    48,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    42,    43,    40,
      41,     0,     0,     0,     0,    72,    73,     0,     0,     0,
       0,    67,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   105,    16,   104,     0,     0,
       0,     0,     0,     0,    17,     0,     0,     0,   141,   142,
     143,     0,    80,     0,    94,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   152,    18,     0,   145,   144,
     146,     0,     0,    72,     0,     0,   119,   118,    67,    27,
       0,    44,     0,     0,    47,     0,    49,     0,    50,    67,
       0,    61,     0,    62,     0,    28,     0,     0,     0,     0,
      33,     0,   132,     0,     0,    56,     0,     0,     0,     0,
      19,     0,     0,     7,     8,     5,     9,   117,    15,   106,
     115,   107,   108,   109,     0,   125,   137,   121,     0,     0,
      76,     0,     0,     0,   163,   162,   161,     0,     0,   154,
     155,   156,   157,   158,    92,    95,   138,    89,    26,     0,
       0,     0,     0,     0,     0,    52,     0,     0,     0,     0,
       0,     0,    34,    71,   134,   135,     0,   131,   130,     0,
       0,     0,     0,    14,   112,     0,   139,     0,   113,     0,
      97,   159,   160,    96,     0,    45,    46,     0,    58,    51,
       0,     0,     0,    30,    31,     0,    57,     0,     0,    64,
       0,     0,    98,   114,    99,     0,     0,     0,     0,     0,
       0,     0,     0,    20,     0,   140,    67,    67,    59,    69,
      36,    29,    67,    35,    55,    54,    53,    32
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
    -216,   554,  -216,   -62,   -67,   -12,   -12,   439,   -67,   -67,
      23,   -12,    54,    83,    91,    48,    48,    54,   -67,   -44,
     -67,    83,   439,   -10,   -10,    54,   252,   254,   -56,   293,
     -44,   -44,   -56,   -44,   162,   331,   -56,   -56,   -56,    54,
     -44,    73,   -49,   -42,  -216,  -216,   -37,  -216,   -67,  -216,
     -29,  -216,   282,   -15,  -216,  -216,  -216,    71,     1,   282,
     282,  -216,  -216,    -9,  -216,     8,  -216,  -216,    13,  -216,
      57,  -216,   125,   376,   282,  -216,  -216,     3,  -216,  -216,
    -216,  -216,  -216,  -216,  -216,    17,    26,   397,   442,   439,
      12,    36,    40,  -216,  -216,   282,    45,    53,    61,    63,
    -216,  -216,    68,    78,   104,   110,    34,  -216,   128,  -216,
     130,   138,  -216,  -216,   140,   146,   149,   166,   321,  -216,
     -67,   -67,   202,   207,   214,   216,   225,   225,    48,   217,
      81,   175,  -216,   218,  -216,    93,   221,    26,   219,     6,
    -216,   234,   235,  -216,   282,  -216,   282,  -216,  -216,   282,
    -216,   201,   297,   300,   316,   317,   319,    54,  -216,  -216,
     282,   282,   282,   320,   282,   282,   245,    94,   248,  -216,
    -216,  -216,    26,   256,  -216,   531,  -216,   439,   222,   102,
      57,   376,  -216,  -216,  -216,   260,  -216,  -216,   220,   442,
      83,   254,    -2,   282,    54,    83,  -216,    83,   222,   273,
      83,    83,    54,   254,   282,    54,    54,  -216,  -216,  -216,
    -216,    54,    54,    54,   -12,  -216,  -216,   266,    54,   298,
     259,    31,   331,   282,   282,   -56,   350,    54,   439,    83,
     623,   553,   623,   603,   541,   276,  -216,   279,   281,   282,
     282,   282,   282,   358,  -216,   280,   286,   291,   225,  -216,
    -216,    -2,  -216,   106,   378,   282,   282,   282,   371,   382,
     282,   282,   282,   282,   282,  -216,  -216,   306,  -216,  -216,
    -216,   309,   323,   245,   326,   213,  -216,  -216,   -67,  -216,
     322,  -216,   332,   334,  -216,   335,  -216,   337,   339,   -67,
     342,  -216,   343,  -216,   344,  -216,   345,   353,   354,    54,
    -216,   352,  -216,   175,   175,   357,   314,   356,   359,   282,
    -216,   360,   370,  -216,  -216,  -216,  -216,  -216,    54,  -216,
    -216,  -216,  -216,  -216,   282,  -216,  -216,  -216,   369,   355,
    -216,   376,   222,   372,   671,   685,   699,   282,   282,   164,
     164,  -216,  -216,  -216,  -216,   373,  -216,  -216,  -216,    83,
     -56,    78,    83,   439,    83,  -216,   222,   282,   220,    54,
     442,    54,  -216,  -216,  -216,  -216,   331,  -216,  -216,   220,
     375,   222,    83,  -216,  -216,   401,  -216,   379,   391,   383,
    -216,   389,   389,  -216,   381,  -216,  -216,   384,  -216,  -216,
     394,   396,   402,   404,  -216,   405,  -216,   407,    54,  -216,
     408,   410,  -216,  -216,  -216,    83,   -56,    54,   282,    54,
      54,   -56,    54,  -216,    83,  -216,   -67,   -67,  -216,  -216,
    -216,  -216,   -67,  -216,  -216,  -216,  -216,  -216
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -216,  -216,  -151,  -216,  -216,  -216,    98,    -4,    -7,   -66,
    -102,   263,     4,  -216,   -24,  -216,    -3,    32,    70,  -216,
    -216,   161,    10,   114,  -175,  -216,   478,    18,  -215,  -216,
    -216,   199,   -33,    19,   -94,   255,     2,    58
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -134
static const yytype_int16 yytable[] =
{
      49,   196,   136,    58,    87,    88,    89,   305,    90,    86,
      93,   132,   226,   278,   100,    48,   103,    97,    97,    47,
     116,   182,   186,   101,    86,   119,   105,    52,   115,   115,
     145,    92,   215,   216,    96,    98,   130,   137,   146,   104,
     303,   109,   109,   199,   147,    50,    51,   121,   171,    63,
      64,   268,   269,   270,   150,   149,    59,    60,   113,   113,
     117,   158,   159,   163,   124,   164,   165,   151,   138,   139,
     140,    52,   193,   106,   172,   160,   176,   152,   153,   313,
     154,   315,    91,   157,    94,   177,   273,    99,   227,   185,
     130,    86,   161,   187,   188,   111,   114,   162,   221,   120,
      61,   178,    59,    60,   -25,    48,   184,    62,   169,   141,
     179,    50,    51,    48,    59,    60,   209,   210,   189,    57,
      57,  -133,   190,   279,    70,    57,    71,   191,   122,   123,
      97,   125,    95,    59,   167,   168,   208,   192,   142,    74,
     155,   156,    63,    64,    62,   194,    61,   217,    50,    51,
     195,   396,   143,   144,   328,   268,   269,   270,    61,    50,
      51,    72,   245,   246,   247,   219,   249,   250,   252,   159,
      59,    60,    71,    48,   262,   263,   264,    61,    95,    86,
     223,   266,    70,   392,    71,    74,   197,   173,   207,   136,
      73,   130,   198,   282,   397,   283,   291,    74,   132,   169,
     170,    70,   231,    71,   233,   115,   292,   234,   280,    73,
     200,   298,   201,   285,    61,   286,    74,   304,   288,   289,
     202,   236,   203,   281,   137,   306,   307,   244,   204,   330,
      86,   205,   311,   164,   165,   113,    65,    66,   126,   127,
      71,   320,   320,   320,   320,   128,    95,   312,   206,   386,
     321,   322,   323,    74,   235,   137,   333,   308,    50,    51,
      59,    60,    59,    60,   284,   237,   268,   269,   270,   301,
     364,   221,   290,   276,   348,   293,   294,    50,    51,    50,
      51,   295,   296,   297,   211,   355,   107,   107,   300,   212,
      59,    60,   267,   271,   394,   274,   213,   310,   214,   218,
     222,   225,   277,   239,    61,    62,    61,   240,   224,    50,
      51,   370,   287,   334,   335,   336,   228,   229,   339,   340,
     341,   342,   343,   241,   242,   243,   374,   248,    57,   251,
      71,   253,    71,   136,    61,    52,    95,    52,    95,    59,
      60,   254,   132,    74,   275,    74,    62,   252,   299,   302,
      50,    51,    63,    64,   301,    86,   309,   388,  -119,   391,
      71,  -118,   130,   318,   324,   325,    95,   384,   137,   362,
     387,   326,   389,    74,    62,   118,   327,   337,    50,    51,
      63,    64,   385,    61,    59,    60,    59,    60,   373,   338,
     400,   344,    65,    66,   345,   381,   382,   260,   261,   262,
     263,   264,   367,    48,   349,    59,    60,    70,   346,    71,
     419,   347,   425,   426,   350,    73,   351,   352,   427,   353,
     131,   354,    74,   416,   356,   357,   358,   359,    61,   393,
      61,   395,   424,    50,    51,   360,   361,   363,   417,   366,
     376,   369,   371,   422,   368,   378,   378,    59,    60,    61,
      59,    60,   372,   375,    71,   401,    71,   398,   380,   383,
      95,   403,   331,   405,   402,   332,   406,    74,   413,    74,
     390,   404,   277,   180,   127,    71,   407,   418,   408,   420,
     421,   181,   423,   277,   409,   399,   410,   411,    74,   412,
     414,    61,    62,   379,    61,   415,    50,    51,    63,    64,
      65,    66,   110,   365,    67,     0,   329,     0,     0,     0,
      68,    69,     0,     0,     0,    70,     0,    71,   126,   127,
      71,     0,    72,    73,     0,     0,    95,     0,     0,     0,
      74,     0,     0,    74,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,     2,     3,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,     0,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
       0,    36,     0,    37,    38,    39,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,     0,     0,     0,
      40,     0,     0,     0,     3,     0,   317,     0,     0,     0,
      41,    42,    43,     0,   314,    44,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,     0,
      36,     0,    37,    38,    39,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   316,     0,     0,     0,     0,    40,
     257,   258,   259,   260,   261,   262,   263,   264,     0,    41,
      42,    43,     0,     0,    44,   258,   259,   260,   261,   262,
     263,   264
};

static const yytype_int16 yycheck[] =
{
       4,   103,    35,     6,     8,     9,    10,   222,    11,     7,
      14,    35,     6,   188,    18,    82,    20,    15,    16,    81,
      27,    87,    88,    67,    22,    29,    22,    83,    26,    27,
      79,    13,   126,   127,    15,    16,    34,    35,    80,    21,
       9,    23,    24,     9,    81,    57,    58,    29,    72,    59,
      60,    53,    54,    55,    52,    84,     8,     9,    26,    27,
      28,    59,    60,     6,    32,     8,     9,    82,    36,    37,
      38,    83,    11,    83,    72,    84,    74,     6,     7,   230,
       9,   232,    12,    82,    14,    82,   180,    17,    82,    87,
      88,    89,    84,    89,    82,    25,    26,    84,   131,    29,
      52,    84,     8,     9,    81,    82,    87,    53,    74,    39,
      84,    57,    58,    82,     8,     9,   120,   121,    82,     5,
       6,    90,    82,   189,    76,    11,    78,    82,    30,    31,
     128,    33,    84,     8,     9,    10,   118,    84,    40,    91,
      69,    70,    59,    60,    53,    82,    52,   128,    57,    58,
      82,   366,    79,    80,   248,    53,    54,    55,    52,    57,
      58,    83,   160,   161,   162,    84,   164,   165,    74,   167,
       8,     9,    78,    82,    10,    11,    12,    52,    84,   177,
      87,   177,    76,   358,    78,    91,    82,    73,   118,   222,
      84,   189,    82,   191,   369,   193,   203,    91,   222,    74,
      75,    76,   144,    78,   146,   203,   204,   149,   190,    84,
      82,   214,    82,   195,    52,   197,    91,   221,   200,   201,
      82,   151,    82,   191,   222,   223,   224,   157,    82,   253,
     228,    82,   228,     8,     9,   203,    61,    62,    76,    77,
      78,   239,   240,   241,   242,    83,    84,   229,    82,   351,
     240,   241,   242,    91,    53,   253,   254,   225,    57,    58,
       8,     9,     8,     9,   194,   151,    53,    54,    55,    56,
     303,   304,   202,    53,   278,   205,   206,    57,    58,    57,
      58,   211,   212,   213,    82,   289,    23,    24,   218,    82,
       8,     9,   178,   179,   360,   181,    82,   227,    82,    82,
      82,    82,   188,     6,    52,    53,    52,     7,    87,    57,
      58,   309,   198,   255,   256,   257,    82,    82,   260,   261,
     262,   263,   264,     7,     7,     6,   324,     7,   214,    84,
      78,    83,    78,   366,    52,    83,    84,    83,    84,     8,
       9,    85,   366,    91,    84,    91,    53,    74,    82,    90,
      57,    58,    59,    60,    56,   353,     6,   353,    82,   357,
      78,    82,   360,    82,     6,    85,    84,   349,   366,   299,
     352,    85,   354,    91,    53,    82,    85,     6,    57,    58,
      59,    60,   350,    52,     8,     9,     8,     9,   318,     7,
     372,    85,    61,    62,    85,   337,   338,     8,     9,    10,
      11,    12,    88,    82,    82,     8,     9,    76,    85,    78,
     408,    85,   416,   417,    82,    84,    82,    82,   422,    82,
      89,    82,    91,   405,    82,    82,    82,    82,    52,   359,
      52,   361,   414,    57,    58,    82,    82,    85,   406,    82,
      85,    82,    82,   411,    88,   331,   332,     8,     9,    52,
       8,     9,    82,    84,    78,    54,    78,    82,    86,    86,
      84,    70,    84,    82,    85,    87,    82,    91,   398,    91,
     356,    88,   358,    76,    77,    78,    82,   407,    82,   409,
     410,    84,   412,   369,    82,   371,    82,    82,    91,    82,
      82,    52,    53,   332,    52,    85,    57,    58,    59,    60,
      61,    62,    24,   304,    65,    -1,   251,    -1,    -1,    -1,
      71,    72,    -1,    -1,    -1,    76,    -1,    78,    76,    77,
      78,    -1,    83,    84,    -1,    -1,    84,    -1,    -1,    -1,
      91,    -1,    -1,    91,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,     0,     1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    -1,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    -1,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    47,    -1,    49,    50,    51,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    85,    -1,    -1,    -1,
      66,    -1,    -1,    -1,     1,    -1,    85,    -1,    -1,    -1,
      76,    77,    78,    -1,    81,    81,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    -1,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      47,    -1,    49,    50,    51,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    81,    -1,    -1,    -1,    -1,    66,
       5,     6,     7,     8,     9,    10,    11,    12,    -1,    76,
      77,    78,    -1,    -1,    81,     6,     7,     8,     9,    10,
      11,    12
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
     119,    54,    85,    70,    88,    82,    82,    82,    82,    82,
      82,    82,    82,   110,    82,    85,   119,   109,   110,   128,
     110,   110,   109,   110,   119,    99,    99,    99
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
#line 44 "a.y"
    {
		if((yyvsp[(1) - (2)].sym)->value != pc)
			yyerror("redeclaration of %s", (yyvsp[(1) - (2)].sym)->name);
		(yyvsp[(1) - (2)].sym)->value = pc;
	}
    break;

  case 6:
#line 51 "a.y"
    {
		(yyvsp[(1) - (2)].sym)->type = LLAB;
		(yyvsp[(1) - (2)].sym)->value = pc;
	}
    break;

  case 8:
#line 57 "a.y"
    {
		(yyvsp[(1) - (4)].sym)->type = LVAR;
		(yyvsp[(1) - (4)].sym)->value = (yyvsp[(3) - (4)].lval);
	}
    break;

  case 9:
#line 62 "a.y"
    {
		if((yyvsp[(1) - (4)].sym)->value != (yyvsp[(3) - (4)].lval))
			yyerror("redeclaration of %s", (yyvsp[(1) - (4)].sym)->name);
		(yyvsp[(1) - (4)].sym)->value = (yyvsp[(3) - (4)].lval);
	}
    break;

  case 13:
#line 76 "a.y"
    {
		outcode((yyvsp[(1) - (2)].lval), &nullgen, NREG, &nullgen);
	}
    break;

  case 14:
#line 83 "a.y"
    {
		outcode((yyvsp[(1) - (6)].lval), &(yyvsp[(2) - (6)].addr), (yyvsp[(4) - (6)].lval), &(yyvsp[(6) - (6)].addr));
	}
    break;

  case 15:
#line 87 "a.y"
    {
		outcode((yyvsp[(1) - (5)].lval), &(yyvsp[(2) - (5)].addr), (yyvsp[(4) - (5)].lval), &nullgen);
	}
    break;

  case 16:
#line 91 "a.y"
    {
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(2) - (4)].addr), NREG, &(yyvsp[(4) - (4)].addr));
	}
    break;

  case 17:
#line 98 "a.y"
    {
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(2) - (4)].addr), NREG, &(yyvsp[(4) - (4)].addr));
	}
    break;

  case 18:
#line 105 "a.y"
    {
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(2) - (4)].addr), NREG, &(yyvsp[(4) - (4)].addr));
	}
    break;

  case 19:
#line 112 "a.y"
    {
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(2) - (4)].addr), NREG, &(yyvsp[(4) - (4)].addr));
	}
    break;

  case 20:
#line 116 "a.y"
    {
		Addr a;
		a = nullgen;
		a.type = D_CONST;
		a.offset = (yyvsp[(5) - (7)].lval);
		outgcode((yyvsp[(1) - (7)].lval), &(yyvsp[(2) - (7)].addr), NREG, &a, &(yyvsp[(7) - (7)].addr));
	}
    break;

  case 21:
#line 127 "a.y"
    {
		outcode((yyvsp[(1) - (3)].lval), &nullgen, NREG, &(yyvsp[(3) - (3)].addr));
	}
    break;

  case 22:
#line 131 "a.y"
    {
		outcode((yyvsp[(1) - (3)].lval), &nullgen, NREG, &(yyvsp[(3) - (3)].addr));
	}
    break;

  case 23:
#line 138 "a.y"
    {
		outcode((yyvsp[(1) - (3)].lval), &nullgen, NREG, &(yyvsp[(3) - (3)].addr));
	}
    break;

  case 24:
#line 145 "a.y"
    {
		outcode((yyvsp[(1) - (3)].lval), &nullgen, NREG, &(yyvsp[(3) - (3)].addr));
	}
    break;

  case 25:
#line 149 "a.y"
    {
		outcode((yyvsp[(1) - (1)].lval), &nullgen, NREG, &nullgen);
	}
    break;

  case 26:
#line 156 "a.y"
    {
		outcode((yyvsp[(1) - (5)].lval), &(yyvsp[(2) - (5)].addr), (yyvsp[(4) - (5)].lval), &nullgen);
	}
    break;

  case 27:
#line 163 "a.y"
    {
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(2) - (4)].addr), NREG, &(yyvsp[(4) - (4)].addr));
	}
    break;

  case 28:
#line 170 "a.y"
    {
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(2) - (4)].addr), NREG, &(yyvsp[(4) - (4)].addr));
	}
    break;

  case 29:
#line 177 "a.y"
    {
		outgcode((yyvsp[(1) - (8)].lval), &(yyvsp[(2) - (8)].addr), (yyvsp[(6) - (8)].addr).reg, &(yyvsp[(4) - (8)].addr), &(yyvsp[(8) - (8)].addr));
	}
    break;

  case 30:
#line 181 "a.y"
    {
		outcode((yyvsp[(1) - (6)].lval), &(yyvsp[(2) - (6)].addr), (yyvsp[(4) - (6)].addr).reg, &(yyvsp[(6) - (6)].addr));
	}
    break;

  case 31:
#line 188 "a.y"
    {
		outcode((yyvsp[(1) - (6)].lval), &(yyvsp[(2) - (6)].addr), (yyvsp[(4) - (6)].addr).reg, &(yyvsp[(6) - (6)].addr));
	}
    break;

  case 32:
#line 195 "a.y"
    {
		outgcode((yyvsp[(1) - (9)].lval), &(yyvsp[(2) - (9)].addr), (yyvsp[(6) - (9)].addr).reg, &(yyvsp[(4) - (9)].addr), &(yyvsp[(8) - (9)].addr));
	}
    break;

  case 33:
#line 202 "a.y"
    {
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(2) - (4)].addr), NREG, &(yyvsp[(4) - (4)].addr));
	}
    break;

  case 34:
#line 206 "a.y"
    {
		outcode((yyvsp[(1) - (5)].lval), &(yyvsp[(3) - (5)].addr), NREG, &(yyvsp[(5) - (5)].addr));
	}
    break;

  case 35:
#line 213 "a.y"
    {
		outgcode((yyvsp[(1) - (8)].lval), &(yyvsp[(2) - (8)].addr), (yyvsp[(6) - (8)].lval), &(yyvsp[(4) - (8)].addr), &(yyvsp[(8) - (8)].addr));
	}
    break;

  case 36:
#line 220 "a.y"
    {
		outgcode((yyvsp[(1) - (8)].lval), &(yyvsp[(2) - (8)].addr), (yyvsp[(6) - (8)].lval), &(yyvsp[(4) - (8)].addr), &(yyvsp[(8) - (8)].addr));
	}
    break;

  case 37:
#line 227 "a.y"
    {
		outcode((yyvsp[(1) - (2)].lval), &nullgen, NREG, &nullgen);
	}
    break;

  case 38:
#line 231 "a.y"
    {
		outcode((yyvsp[(1) - (2)].lval), &nullgen, NREG, &(yyvsp[(2) - (2)].addr));
	}
    break;

  case 39:
#line 238 "a.y"
    {
		outcode((yyvsp[(1) - (2)].lval), &nullgen, NREG, &nullgen);
	}
    break;

  case 40:
#line 242 "a.y"
    {
		outcode((yyvsp[(1) - (3)].lval), &(yyvsp[(2) - (3)].addr), NREG, &nullgen);
	}
    break;

  case 41:
#line 246 "a.y"
    {
		outcode((yyvsp[(1) - (3)].lval), &(yyvsp[(2) - (3)].addr), NREG, &nullgen);
	}
    break;

  case 42:
#line 250 "a.y"
    {
		outcode((yyvsp[(1) - (3)].lval), &nullgen, NREG, &(yyvsp[(3) - (3)].addr));
	}
    break;

  case 43:
#line 254 "a.y"
    {
		outcode((yyvsp[(1) - (3)].lval), &nullgen, NREG, &(yyvsp[(3) - (3)].addr));
	}
    break;

  case 44:
#line 261 "a.y"
    {
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(2) - (4)].addr), NREG, &(yyvsp[(4) - (4)].addr));
	}
    break;

  case 45:
#line 265 "a.y"
    {
		outcode((yyvsp[(1) - (6)].lval), &(yyvsp[(2) - (6)].addr), (yyvsp[(4) - (6)].lval), &(yyvsp[(6) - (6)].addr));
	}
    break;

  case 46:
#line 272 "a.y"
    {
		outcode((yyvsp[(1) - (6)].lval), &(yyvsp[(2) - (6)].addr), (yyvsp[(4) - (6)].lval), &(yyvsp[(6) - (6)].addr));
	}
    break;

  case 47:
#line 279 "a.y"
    {
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(2) - (4)].addr), NREG, &(yyvsp[(4) - (4)].addr));
	}
    break;

  case 48:
#line 286 "a.y"
    {
		outcode((yyvsp[(1) - (3)].lval), &nullgen, NREG, &(yyvsp[(3) - (3)].addr));
	}
    break;

  case 49:
#line 293 "a.y"
    {
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(2) - (4)].addr), NREG, &(yyvsp[(4) - (4)].addr));
	}
    break;

  case 50:
#line 300 "a.y"
    {
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(2) - (4)].addr), NREG, &(yyvsp[(4) - (4)].addr));
	}
    break;

  case 51:
#line 304 "a.y"
    {
		outcode((yyvsp[(1) - (6)].lval), &(yyvsp[(2) - (6)].addr), (yyvsp[(4) - (6)].addr).reg, &(yyvsp[(6) - (6)].addr));
	}
    break;

  case 52:
#line 311 "a.y"
    {
		outcode((yyvsp[(1) - (5)].lval), &(yyvsp[(2) - (5)].addr), (yyvsp[(4) - (5)].addr).reg, &nullgen);
	}
    break;

  case 53:
#line 318 "a.y"
    {
		outgcode((yyvsp[(1) - (9)].lval), &(yyvsp[(2) - (9)].addr), (yyvsp[(6) - (9)].addr).reg, &(yyvsp[(4) - (9)].addr), &(yyvsp[(8) - (9)].addr));
	}
    break;

  case 54:
#line 325 "a.y"
    {
		outgcode((yyvsp[(1) - (9)].lval), &(yyvsp[(2) - (9)].addr), (yyvsp[(4) - (9)].addr).reg, &(yyvsp[(6) - (9)].addr), &(yyvsp[(8) - (9)].addr));
	}
    break;

  case 55:
#line 332 "a.y"
    {
		outgcode((yyvsp[(1) - (8)].lval), &(yyvsp[(2) - (8)].addr), (yyvsp[(6) - (8)].addr).reg, &(yyvsp[(4) - (8)].addr), &(yyvsp[(8) - (8)].addr));
	}
    break;

  case 56:
#line 339 "a.y"
    {
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(2) - (4)].addr), NREG, &(yyvsp[(4) - (4)].addr));
	}
    break;

  case 57:
#line 343 "a.y"
    {
		outcode((yyvsp[(1) - (6)].lval), &(yyvsp[(2) - (6)].addr), (yyvsp[(4) - (6)].addr).reg, &(yyvsp[(6) - (6)].addr));
	}
    break;

  case 58:
#line 350 "a.y"
    {
		outcode((yyvsp[(1) - (6)].lval), &(yyvsp[(2) - (6)].addr), (yyvsp[(4) - (6)].lval), &(yyvsp[(6) - (6)].addr));
	}
    break;

  case 59:
#line 357 "a.y"
    {
		outgcode((yyvsp[(1) - (8)].lval), &(yyvsp[(2) - (8)].addr), (yyvsp[(6) - (8)].lval), &(yyvsp[(4) - (8)].addr), &(yyvsp[(8) - (8)].addr));
	}
    break;

  case 60:
#line 364 "a.y"
    {
		outcode((yyvsp[(1) - (2)].lval), &(yyvsp[(2) - (2)].addr), NREG, &nullgen);
	}
    break;

  case 61:
#line 368 "a.y"
    {
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(4) - (4)].addr), (yyvsp[(2) - (4)].addr).reg, &nullgen);
	}
    break;

  case 62:
#line 372 "a.y"
    {
		outcode((yyvsp[(1) - (4)].lval), &(yyvsp[(2) - (4)].addr), NREG, &(yyvsp[(4) - (4)].addr));
	}
    break;

  case 63:
#line 379 "a.y"
    {
		outcode((yyvsp[(1) - (2)].lval), &(yyvsp[(2) - (2)].addr), NREG, &nullgen);
	}
    break;

  case 64:
#line 386 "a.y"
    {
		outcode((yyvsp[(1) - (6)].lval), &(yyvsp[(2) - (6)].addr), (yyvsp[(6) - (6)].lval), &(yyvsp[(4) - (6)].addr));
	}
    break;

  case 65:
#line 393 "a.y"
    {
		outcode((yyvsp[(1) - (2)].lval), &nullgen, NREG, &nullgen);
	}
    break;

  case 66:
#line 399 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_COND;
		(yyval.addr).reg = (yyvsp[(1) - (1)].lval);
	}
    break;

  case 69:
#line 410 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_CONST;
		(yyval.addr).offset = SYSARG4((yyvsp[(1) - (7)].lval), (yyvsp[(3) - (7)].lval), (yyvsp[(5) - (7)].lval), (yyvsp[(7) - (7)].lval));
	}
    break;

  case 71:
#line 419 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_BRANCH;
		(yyval.addr).offset = (yyvsp[(1) - (4)].lval) + pc;
	}
    break;

  case 72:
#line 425 "a.y"
    {
		(yyval.addr) = nullgen;
		if(pass == 2)
			yyerror("undefined label: %s", (yyvsp[(1) - (2)].sym)->name);
		(yyval.addr).type = D_BRANCH;
		(yyval.addr).offset = (yyvsp[(2) - (2)].lval);
	}
    break;

  case 73:
#line 433 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_BRANCH;
		(yyval.addr).offset = (yyvsp[(1) - (2)].sym)->value + (yyvsp[(2) - (2)].lval);
	}
    break;

  case 74:
#line 440 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_CONST;
		(yyval.addr).offset = (yyvsp[(2) - (2)].lval);
	}
    break;

  case 75:
#line 446 "a.y"
    {
		(yyval.addr) = (yyvsp[(2) - (2)].addr);
		(yyval.addr).type = D_CONST;
	}
    break;

  case 76:
#line 451 "a.y"
    {
		(yyval.addr) = (yyvsp[(4) - (4)].addr);
		(yyval.addr).type = D_OCONST;
	}
    break;

  case 77:
#line 456 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SCONST;
		memmove((yyval.addr).u.sval, (yyvsp[(2) - (2)].sval), sizeof((yyval.addr).u.sval));
	}
    break;

  case 79:
#line 465 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FCONST;
		(yyval.addr).u.dval = (yyvsp[(2) - (2)].dval);
	}
    break;

  case 80:
#line 471 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FCONST;
		(yyval.addr).u.dval = -(yyvsp[(3) - (3)].dval);
	}
    break;

  case 83:
#line 481 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SPR;
		(yyval.addr).offset = (yyvsp[(1) - (1)].lval);
	}
    break;

  case 84:
#line 487 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).offset = (yyvsp[(1) - (1)].lval);
	}
    break;

  case 89:
#line 499 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[(2) - (3)].lval);
		(yyval.addr).offset = 0;
	}
    break;

  case 90:
#line 506 "a.y"
    {
		(yyval.addr) = (yyvsp[(1) - (1)].addr);
		if((yyvsp[(1) - (1)].addr).name != D_EXTERN && (yyvsp[(1) - (1)].addr).name != D_STATIC) {
		}
	}
    break;

  case 92:
#line 515 "a.y"
    {
		(yyval.addr) = (yyvsp[(1) - (4)].addr);
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[(3) - (4)].lval);
	}
    break;

  case 94:
#line 524 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[(2) - (3)].lval);
		(yyval.addr).offset = 0;
	}
    break;

  case 95:
#line 531 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[(3) - (4)].lval);
		(yyval.addr).offset = (yyvsp[(1) - (4)].lval);
	}
    break;

  case 96:
#line 538 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_XPRE;
		(yyval.addr).reg = (yyvsp[(3) - (5)].lval);
		(yyval.addr).offset = (yyvsp[(1) - (5)].lval);
	}
    break;

  case 97:
#line 545 "a.y"
    {
		(yyval.addr).type = D_XPOST;
		(yyval.addr).offset = (yyvsp[(2) - (5)].lval);
	}
    break;

  case 98:
#line 550 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_ROFF;
		(yyval.addr).reg = (yyvsp[(2) - (6)].lval);
		(yyval.addr).scale = (yyvsp[(5) - (6)].lval) & 0x1f;
		(yyval.addr).offset = (yyvsp[(5) - (6)].lval);
	}
    break;

  case 99:
#line 558 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_ROFF;
		(yyval.addr).reg = (yyvsp[(2) - (6)].lval);
		(yyval.addr).scale = (yyvsp[(5) - (6)].lval) & 0x1f;
		(yyval.addr).offset = (yyvsp[(5) - (6)].lval) | (1<<16);
	}
    break;

  case 103:
#line 572 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_CONST;
		(yyval.addr).offset = (yyvsp[(2) - (2)].lval);
	}
    break;

  case 104:
#line 580 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_REG;
		(yyval.addr).reg = (yyvsp[(1) - (1)].lval);
	}
    break;

  case 105:
#line 586 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SP;
		(yyval.addr).reg = REGSP;
	}
    break;

  case 106:
#line 594 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = ((yyvsp[(1) - (4)].lval) << 16) | ((yyvsp[(4) - (4)].lval) << 10) | (0 << 22);
	}
    break;

  case 107:
#line 600 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = (((yyvsp[(1) - (4)].lval)&0x1F) << 16) | ((yyvsp[(4) - (4)].lval) << 10) | (1 << 22);
	}
    break;

  case 108:
#line 606 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = ((yyvsp[(1) - (4)].lval) << 16) | ((yyvsp[(4) - (4)].lval) << 10) | (2 << 22);
	}
    break;

  case 109:
#line 612 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = ((yyvsp[(1) - (4)].lval) << 16) | ((yyvsp[(4) - (4)].lval) << 10) | (3 << 22);
	}
    break;

  case 110:
#line 620 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_REG;
		(yyval.addr).reg = (yyvsp[(1) - (1)].lval);
	}
    break;

  case 111:
#line 626 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_EXTREG;
		(yyval.addr).reg = (yyvsp[(1) - (2)].lval);
		(yyval.addr).offset = ((yyvsp[(1) - (2)].lval) << 16) | ((yyvsp[(2) - (2)].lval) << 13);
	}
    break;

  case 112:
#line 633 "a.y"
    {
		if((yyvsp[(5) - (5)].lval) < 0 || (yyvsp[(5) - (5)].lval) > 4)
			yyerror("shift value out of range");
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_EXTREG;
		(yyval.addr).reg = (yyvsp[(1) - (5)].lval);
		(yyval.addr).offset = ((yyvsp[(1) - (5)].lval) << 16) | ((yyvsp[(2) - (5)].lval) << 13) | ((yyvsp[(5) - (5)].lval) << 10);
	}
    break;

  case 113:
#line 644 "a.y"
    {
		(yyval.lval) = (3 << 8) | (yyvsp[(1) - (1)].lval);
	}
    break;

  case 114:
#line 648 "a.y"
    {
		(yyval.lval) = ((yyvsp[(2) - (2)].lval) << 8) | (yyvsp[(1) - (2)].lval);
	}
    break;

  case 115:
#line 654 "a.y"
    {
		if((yyval.lval) < 0 || (yyval.lval) >= 64)
			yyerror("shift value out of range");
		(yyval.lval) = (yyvsp[(1) - (1)].lval)&0x3F;
	}
    break;

  case 117:
#line 663 "a.y"
    {
		if((yyvsp[(3) - (4)].lval) < 0 || (yyvsp[(3) - (4)].lval) >= NREG)
			print("register value out of range\n");
		(yyval.lval) = (yyvsp[(3) - (4)].lval);
	}
    break;

  case 119:
#line 672 "a.y"
    {
		(yyval.lval) = REGSP;
	}
    break;

  case 120:
#line 678 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SPR;
		(yyval.addr).offset = (yyvsp[(1) - (1)].lval);
	}
    break;

  case 121:
#line 684 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = (yyvsp[(1) - (4)].lval);
		(yyval.addr).offset = (yyvsp[(3) - (4)].lval);
	}
    break;

  case 124:
#line 696 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FREG;
		(yyval.addr).reg = (yyvsp[(1) - (1)].lval);
	}
    break;

  case 125:
#line 702 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FREG;
		(yyval.addr).reg = (yyvsp[(3) - (4)].lval);
	}
    break;

  case 129:
#line 713 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_VSET;
		(yyval.addr).offset = (yyvsp[(1) - (1)].lval);
	}
    break;

  case 130:
#line 721 "a.y"
    {
		(yyval.addr).type = D_VLANE;
		(yyval.addr).offset = (yyvsp[(3) - (4)].lval);
	}
    break;

  case 131:
#line 726 "a.y"
    {
		(yyval.addr).type = D_VLANE;
		(yyval.addr).offset = (yyvsp[(3) - (4)].lval);
	}
    break;

  case 132:
#line 733 "a.y"
    {
		(yyval.lval) = (yyvsp[(2) - (3)].lval);
	}
    break;

  case 133:
#line 739 "a.y"
    {
		(yyval.lval) = 1 << (yyvsp[(1) - (1)].addr).reg;
	}
    break;

  case 134:
#line 743 "a.y"
    {
		int i;
		(yyval.lval)=0;
		for(i=(yyvsp[(1) - (3)].addr).reg; i<=(yyvsp[(3) - (3)].addr).reg; i++)
			(yyval.lval) |= 1<<i;
		for(i=(yyvsp[(3) - (3)].addr).reg; i<=(yyvsp[(1) - (3)].addr).reg; i++)
			(yyval.lval) |= 1<<i;
	}
    break;

  case 135:
#line 752 "a.y"
    {
		(yyval.lval) = (1<<(yyvsp[(1) - (3)].addr).reg) | (yyvsp[(3) - (3)].lval);
	}
    break;

  case 136:
#line 758 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_VREG;
		(yyval.addr).reg = (yyvsp[(1) - (1)].lval);
		/* TO DO: slice */
	}
    break;

  case 137:
#line 765 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_VREG;
		(yyval.addr).reg = (yyvsp[(3) - (4)].lval);
	}
    break;

  case 138:
#line 773 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).name = (yyvsp[(3) - (4)].lval);
		(yyval.addr).sym = nil;
		(yyval.addr).offset = (yyvsp[(1) - (4)].lval);
	}
    break;

  case 139:
#line 781 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).name = (yyvsp[(4) - (5)].lval);
		(yyval.addr).sym = linklookup(ctxt, (yyvsp[(1) - (5)].sym)->name, 0);
		(yyval.addr).offset = (yyvsp[(2) - (5)].lval);
	}
    break;

  case 140:
#line 789 "a.y"
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).name = D_STATIC;
		(yyval.addr).sym = linklookup(ctxt, (yyvsp[(1) - (7)].sym)->name, 0);
		(yyval.addr).offset = (yyvsp[(4) - (7)].lval);
	}
    break;

  case 141:
#line 798 "a.y"
    {
		(yyval.lval) = 0;
	}
    break;

  case 142:
#line 802 "a.y"
    {
		(yyval.lval) = (yyvsp[(2) - (2)].lval);
	}
    break;

  case 143:
#line 806 "a.y"
    {
		(yyval.lval) = -(yyvsp[(2) - (2)].lval);
	}
    break;

  case 148:
#line 818 "a.y"
    {
		(yyval.lval) = (yyvsp[(1) - (1)].sym)->value;
	}
    break;

  case 149:
#line 822 "a.y"
    {
		(yyval.lval) = -(yyvsp[(2) - (2)].lval);
	}
    break;

  case 150:
#line 826 "a.y"
    {
		(yyval.lval) = (yyvsp[(2) - (2)].lval);
	}
    break;

  case 151:
#line 830 "a.y"
    {
		(yyval.lval) = ~(yyvsp[(2) - (2)].lval);
	}
    break;

  case 152:
#line 834 "a.y"
    {
		(yyval.lval) = (yyvsp[(2) - (3)].lval);
	}
    break;

  case 154:
#line 841 "a.y"
    {
		(yyval.lval) = (yyvsp[(1) - (3)].lval) + (yyvsp[(3) - (3)].lval);
	}
    break;

  case 155:
#line 845 "a.y"
    {
		(yyval.lval) = (yyvsp[(1) - (3)].lval) - (yyvsp[(3) - (3)].lval);
	}
    break;

  case 156:
#line 849 "a.y"
    {
		(yyval.lval) = (yyvsp[(1) - (3)].lval) * (yyvsp[(3) - (3)].lval);
	}
    break;

  case 157:
#line 853 "a.y"
    {
		(yyval.lval) = (yyvsp[(1) - (3)].lval) / (yyvsp[(3) - (3)].lval);
	}
    break;

  case 158:
#line 857 "a.y"
    {
		(yyval.lval) = (yyvsp[(1) - (3)].lval) % (yyvsp[(3) - (3)].lval);
	}
    break;

  case 159:
#line 861 "a.y"
    {
		(yyval.lval) = (yyvsp[(1) - (4)].lval) << (yyvsp[(4) - (4)].lval);
	}
    break;

  case 160:
#line 865 "a.y"
    {
		(yyval.lval) = (yyvsp[(1) - (4)].lval) >> (yyvsp[(4) - (4)].lval);
	}
    break;

  case 161:
#line 869 "a.y"
    {
		(yyval.lval) = (yyvsp[(1) - (3)].lval) & (yyvsp[(3) - (3)].lval);
	}
    break;

  case 162:
#line 873 "a.y"
    {
		(yyval.lval) = (yyvsp[(1) - (3)].lval) ^ (yyvsp[(3) - (3)].lval);
	}
    break;

  case 163:
#line 877 "a.y"
    {
		(yyval.lval) = (yyvsp[(1) - (3)].lval) | (yyvsp[(3) - (3)].lval);
	}
    break;


/* Line 1267 of yacc.c.  */
#line 2893 "y.tab.c"
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



