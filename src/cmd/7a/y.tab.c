/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "a.y" /* yacc.c:339  */

#include <u.h>
#include <stdio.h>	/* if we don't, bison will, and a.h re-#defines getc */
#include <libc.h>
#include "a.h"
#include "../../runtime/funcdata.h"

#line 74 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
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
    LPCDAT = 319,
    LFUNCDAT = 320,
    LSCHED = 321,
    LFCONST = 322,
    LSCONST = 323,
    LNAME = 324,
    LLAB = 325,
    LVAR = 326
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
#define LPCDAT 319
#define LFUNCDAT 320
#define LSCHED 321
#define LFCONST 322
#define LSCONST 323
#define LNAME 324
#define LLAB 325
#define LVAR 326

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 9 "a.y" /* yacc.c:355  */

	Sym	*sym;
	vlong	lval;
	double	dval;
	char	sval[NSNAME];
	Addr	addr;

#line 264 "y.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 279 "y.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   804

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  95
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  168
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  447

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   326

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    89,     2,     2,    86,    12,     5,     2,
      87,    88,    10,     8,    85,     9,     2,    11,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    82,    84,
       6,    83,     7,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    90,     2,    91,     4,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    92,     3,    93,    94,     2,     2,     2,
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
      75,    76,    77,    78,    79,    80,    81
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    41,    41,    42,    44,    46,    45,    54,    59,    65,
      69,    70,    71,    77,    84,    88,    92,    99,   106,   113,
     117,   128,   132,   139,   146,   150,   157,   164,   171,   178,
     182,   189,   196,   203,   207,   214,   221,   228,   232,   239,
     243,   247,   251,   255,   262,   267,   274,   284,   291,   298,
     305,   314,   325,   332,   336,   343,   350,   357,   364,   371,
     375,   382,   389,   396,   400,   404,   411,   418,   426,   434,
     442,   448,   455,   456,   459,   465,   468,   474,   484,   490,
     495,   500,   506,   509,   515,   523,   524,   525,   531,   537,
     538,   539,   540,   543,   550,   558,   559,   565,   568,   575,
     582,   589,   596,   604,   614,   615,   616,   618,   626,   632,
     640,   649,   655,   661,   667,   675,   681,   688,   699,   703,
     709,   717,   718,   726,   727,   733,   739,   747,   748,   751,
     757,   765,   766,   767,   768,   776,   781,   788,   794,   798,
     807,   813,   820,   828,   836,   844,   854,   857,   861,   867,
     868,   869,   872,   873,   877,   881,   885,   889,   895,   896,
     900,   904,   908,   912,   916,   920,   924,   928,   932
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
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
  "LSPR", "LSPREG", "LVTYPE", "LPCDAT", "LFUNCDAT", "LSCHED", "LFCONST",
  "LSCONST", "LNAME", "LLAB", "LVAR", "':'", "'='", "';'", "','", "'$'",
  "'('", "')'", "'!'", "'['", "']'", "'{'", "'}'", "'~'", "$accept",
  "prog", "line", "$@1", "inst", "cond", "comma", "sysarg", "rel", "ximm",
  "fcon", "addr", "nireg", "oreg", "ioreg", "imsr", "imm", "reg", "regreg",
  "shift", "extreg", "indexreg", "scon", "sreg", "spreg", "spr", "frcon",
  "freg", "vaddr", "vlane", "vset", "vreglist", "vreg", "name", "offset",
  "pointer", "con", "expr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   124,    94,    38,    60,    62,    43,    45,
      42,    47,    37,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,    58,    61,    59,    44,    36,    40,    41,    33,
      91,    93,   123,   125,   126
};
# endif

#define YYPACT_NINF -223

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-223)))

#define YYTABLE_NINF -139

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -223,   643,  -223,   -61,   -47,   -14,   -14,   404,   -47,   -47,
     -39,   -14,   -23,    91,   135,    62,    62,   -23,   -47,   -41,
     -47,    91,   404,    -9,    -9,   -23,    74,   387,   -38,     3,
     -41,   -41,   -38,   -41,   348,   299,   -33,   -38,   404,   -38,
     -38,   -23,   -41,   -38,   -38,   -10,    96,    -7,  -223,  -223,
      -5,  -223,   -47,  -223,    -3,  -223,   528,    27,  -223,  -223,
    -223,   160,    30,   528,   528,  -223,  -223,    12,  -223,    55,
    -223,  -223,    67,  -223,   175,  -223,   337,    95,   528,  -223,
    -223,    60,  -223,  -223,  -223,  -223,  -223,  -223,  -223,    70,
      86,   440,   445,   404,   100,   106,   113,  -223,  -223,   528,
     115,   122,   206,   140,  -223,  -223,   143,   154,   156,   159,
      10,  -223,   162,  -223,   163,   165,  -223,  -223,   166,   167,
     168,   173,   105,  -223,   -47,   -47,   185,   186,   188,   190,
     196,    62,   191,   192,   146,  -223,   199,  -223,   197,   198,
      86,    28,   204,   208,   214,    15,  -223,   215,   216,   217,
     221,  -223,  -223,   528,   528,  -223,  -223,   528,  -223,    71,
     275,   284,   303,   304,   312,   -23,  -223,  -223,   528,   528,
     528,   317,   528,   528,   243,   478,   250,  -223,  -223,  -223,
      86,   249,  -223,   542,  -223,   404,   161,   259,   175,    95,
    -223,  -223,  -223,   251,  -223,  -223,    28,   445,    91,   387,
      14,   528,   -23,    91,  -223,    91,   161,   263,    91,    91,
     -23,   387,   528,   -23,   -23,  -223,  -223,  -223,  -223,   -23,
     -23,   -23,   -14,  -223,   257,   -23,   287,   260,     4,   299,
     528,   528,  -223,  -223,   265,   404,   -38,   -33,   338,   -23,
     404,    91,   -38,   404,   720,   642,   692,   628,   267,  -223,
     273,   274,   528,   528,   528,   528,   342,  -223,   283,   285,
     288,   196,  -223,  -223,    14,  -223,   492,   508,   528,   528,
     528,   366,   368,   528,   528,   528,   528,   528,  -223,  -223,
     291,  -223,  -223,  -223,   293,   296,   243,   300,    81,   -47,
    -223,   305,  -223,   307,   313,  -223,   314,  -223,   316,   318,
     -47,   319,  -223,   322,  -223,   323,  -223,   324,   341,   351,
     -23,  -223,   309,  -223,   146,   146,   353,   311,   350,    28,
    -223,   358,  -223,   528,  -223,   360,   361,  -223,  -223,  -223,
    -223,  -223,  -223,   -23,  -223,  -223,  -223,  -223,  -223,   528,
    -223,  -223,  -223,   346,   359,  -223,    95,   161,   362,   773,
     357,   255,   528,   528,    80,    80,  -223,  -223,  -223,  -223,
     370,  -223,  -223,  -223,    91,   -38,   154,    91,   404,    91,
    -223,   161,   528,    28,   -23,   445,   -23,  -223,  -223,  -223,
    -223,   299,  -223,  -223,   367,    28,   382,   -23,    91,  -223,
    -223,   416,  -223,   384,   407,   391,  -223,   411,   411,  -223,
     393,   475,  -223,   403,  -223,  -223,   408,   409,   410,   417,
    -223,   420,  -223,  -223,   422,   -23,  -223,   425,   401,  -223,
    -223,  -223,    91,   528,   -38,   -23,   528,   -23,   -23,   -38,
     -23,  -223,    91,  -223,   -47,  -223,   -47,  -223,  -223,  -223,
    -223,   -47,  -223,  -223,  -223,  -223,  -223
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,    72,     0,     0,     0,    72,    72,
      72,     0,     0,     0,    72,     0,     0,     0,    72,     0,
      72,     0,     0,     0,     0,     0,     0,     0,     0,    72,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    10,     3,
       0,    12,    72,    13,     0,   121,     0,     0,   104,   105,
     106,   115,     0,     0,     0,   152,   109,     0,   129,     0,
     141,    87,     0,   125,   146,   153,     0,     0,     0,    86,
      82,     0,    89,    97,    85,   108,    92,    90,    91,    95,
      88,     0,     0,     0,     0,     0,     0,    37,    38,     0,
       0,     0,     0,     0,    70,    71,     0,     0,     0,     0,
       0,   128,     0,   127,     0,     0,    63,    75,     0,     0,
       0,     0,    72,    39,    72,    72,     0,     0,     0,     0,
     146,     0,     0,     0,     0,   131,     0,   133,   134,   132,
       0,     0,     0,     0,     0,     0,    66,     0,     0,     0,
       0,     9,     5,     0,     0,    11,    73,     0,   107,     0,
       0,     0,     0,     0,   116,     0,   155,   154,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    83,    81,    79,
      78,     0,   158,     0,   156,     0,     0,     0,   146,     0,
      21,    22,    94,     0,    23,    24,     0,     0,     0,     0,
       0,     0,     0,     0,    49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    42,    43,    40,    41,     0,
       0,     0,     0,    77,     0,     0,     0,     0,    72,     0,
       0,     0,   124,   123,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   109,    16,
     108,     0,     0,     0,     0,     0,     0,    17,     0,     0,
       0,   146,   147,   148,     0,    84,     0,    98,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   157,    18,
       0,   150,   149,   151,     0,     0,    77,     0,     0,    72,
      27,     0,    44,     0,     0,    48,     0,    52,     0,    53,
      72,     0,    64,     0,    65,     0,    28,     0,     0,     0,
       0,    33,     0,   137,     0,     0,    59,     0,     0,     0,
      68,     0,    69,     0,    19,     0,     0,    50,    51,     6,
       7,     8,   122,    15,   111,   120,   112,   113,   114,     0,
     130,   142,   126,     0,     0,    80,     0,     0,     0,   168,
     167,   166,     0,     0,   159,   160,   161,   162,   163,    96,
      99,   143,    93,    26,     0,     0,     0,     0,     0,     0,
      55,     0,     0,     0,     0,     0,     0,    34,    76,   139,
     140,     0,   136,   135,     0,     0,     0,     0,     0,    14,
     117,     0,   144,     0,   118,     0,   101,   164,   165,   100,
       0,    45,    47,     0,    61,    54,     0,     0,     0,    30,
      31,     0,    60,   110,     0,     0,    67,     0,     0,   102,
     119,   103,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    20,     0,   145,    72,    46,    72,    62,    74,    36,
      29,    72,    35,    58,    57,    56,    32
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -223,  -223,   252,  -223,  -223,    22,    -4,   -25,   -80,  -106,
     212,    37,  -223,   -27,  -223,    16,    79,    84,   276,  -223,
    -223,   176,   -59,   133,  -139,  -223,   491,    18,  -222,  -223,
    -223,   205,   -32,    17,  -115,   258,     2,    58
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    49,   244,    50,   106,   156,   116,   132,    79,
      80,    81,   191,    82,    83,    57,    58,    84,   142,    59,
      60,   393,   334,    85,   234,    86,   112,    87,   136,   137,
     138,   227,    88,    89,   174,   285,   182,   183
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      53,   204,   120,   139,    91,    92,    93,   316,   135,    90,
      97,   190,   194,   314,   104,   223,   107,   101,   101,   207,
     251,   238,    62,    51,    90,   123,   105,    94,   119,   119,
      66,    96,   100,   102,    54,    55,   133,   140,    52,   108,
      90,   113,   113,    54,    55,   -25,    52,   125,    56,   179,
      67,    68,   126,   127,   141,   129,    66,   289,   158,   109,
      54,    55,    67,    68,   148,   166,   167,   281,   282,   283,
      63,    64,    56,   286,   151,   144,   154,   110,   180,   155,
     184,   232,    63,    64,   157,    54,    55,   177,   122,    52,
     275,   276,   277,   193,   133,    90,    95,  -138,    98,   168,
     239,   103,   228,    63,    64,   117,   117,   121,   192,   115,
     118,   128,   159,   124,    65,   165,   143,   290,   145,   146,
     217,   218,   149,   150,   248,   147,    65,    66,    54,    55,
     195,    54,    55,   101,   281,   282,   283,   312,    61,    61,
     216,    74,   169,    75,    61,   185,   343,    65,   224,    99,
      67,    68,    54,    55,   170,    75,    78,   186,    66,   412,
      56,    99,    54,    55,    67,    68,   160,   161,    78,   162,
     258,   259,   260,   187,   262,   263,    75,   167,   152,   153,
     384,   171,    99,   172,   173,   196,   302,    90,    66,    78,
      52,   197,    54,    55,   336,   337,   338,   139,   198,   133,
     199,   293,   135,   294,   172,   173,   215,    69,    70,   200,
     181,   245,   246,   119,   303,   247,   291,   201,    54,    55,
      52,   296,   279,   297,   315,   202,   299,   300,   203,   163,
     164,   140,   317,   318,   408,   111,   111,    90,   309,   345,
      76,   205,    90,   249,   206,    90,   414,   208,   209,   257,
     210,   211,   212,   213,   335,   335,   335,   335,   214,   326,
     402,   271,   272,   273,   274,   275,   276,   277,   140,   348,
     219,   220,   320,   221,   233,   222,   225,   325,   292,   226,
     328,   252,   379,   228,   229,   363,   295,   230,   231,   235,
     117,   253,   250,   236,   301,   410,   370,   304,   305,   237,
     240,   241,   242,   306,   307,   308,   243,    63,    64,   311,
     254,   255,   281,   282,   283,   321,    54,    55,   256,   280,
     284,   327,   287,   324,   261,   386,   349,   350,   351,   233,
     264,   354,   355,   356,   357,   358,   266,   267,   288,   298,
     265,   390,   310,   312,   323,    63,   175,   176,   339,   139,
     319,    65,  -124,   313,   135,    61,    63,    64,  -123,   333,
      69,    70,   270,   271,   272,   273,   274,   275,   276,   277,
      90,   340,   352,   341,   407,   353,   342,   133,    74,   359,
      75,   360,   400,   140,   361,   403,    77,   405,   362,    65,
     364,   134,   365,    78,   377,    63,    64,   378,   366,   367,
      65,   368,   382,   369,   371,   404,   417,   372,   373,   374,
     397,   398,    63,    64,   177,   178,    74,   389,    75,   273,
     274,   275,   276,   277,    77,   435,   375,   130,   438,    75,
     444,    78,   445,   391,   131,    99,   376,   446,   381,    65,
     434,   383,    78,   385,   401,   387,   388,   392,    63,    64,
     443,   396,   233,    63,    64,   413,    65,    66,   409,   399,
     411,    54,    55,    67,    68,    69,    70,   415,    75,    71,
     418,   416,   419,    56,    99,    72,    73,   420,   422,   394,
     394,    78,   421,    74,   423,    75,    63,    64,   424,   433,
      76,    77,    65,   425,   426,   427,   329,    65,    78,   431,
      63,    64,   428,   436,   406,   429,   233,   430,   441,   437,
     432,   439,   440,   322,   442,   114,    63,    64,   233,   188,
     380,    75,   344,   395,   130,     0,    75,   189,     0,     0,
      65,     0,    99,     0,    78,     0,    63,    64,     0,    78,
       0,     0,     0,     0,    65,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   265,     0,     0,     0,    75,
      65,     0,     0,     0,     0,    99,     0,     0,     0,     0,
       0,    74,    78,    75,     0,     0,     0,     0,     0,    77,
      65,     0,     0,     0,     0,     0,    78,     0,     0,    75,
       0,     0,     0,     0,     0,   346,     0,     0,   347,     0,
       0,     0,    78,     0,     0,     0,     0,     0,     0,    75,
       0,     0,     0,     0,     0,    99,     0,     0,     0,     0,
       0,     0,    78,     0,     0,     0,     0,     0,     0,     0,
     278,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,     0,     0,     2,     3,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,     0,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,     0,     0,     0,     0,    42,
       0,     0,     0,     0,     0,     0,   332,    43,    44,    45,
      -4,     3,    46,     0,    47,     0,   330,    48,     0,     0,
       0,     0,     0,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,     0,     0,     0,     0,   331,   269,   270,   271,
     272,   273,   274,   275,   276,   277,    42,     0,     0,     0,
       0,     0,     0,     0,    43,    44,    45,     0,     0,    46,
       0,    47,     0,     0,    48
};

static const yytype_int16 yycheck[] =
{
       4,   107,    27,    35,     8,     9,    10,   229,    35,     7,
      14,    91,    92,     9,    18,   130,    20,    15,    16,     9,
     159,     6,     6,    84,    22,    29,    67,    11,    26,    27,
      53,    13,    15,    16,    57,    58,    34,    35,    85,    21,
      38,    23,    24,    57,    58,    84,    85,    29,    86,    76,
      59,    60,    30,    31,    87,    33,    53,   196,    56,    22,
      57,    58,    59,    60,    42,    63,    64,    53,    54,    55,
       8,     9,    86,   188,    84,    38,    83,    86,    76,    84,
      78,    53,     8,     9,    87,    57,    58,    77,    85,    85,
      10,    11,    12,    91,    92,    93,    12,    93,    14,    87,
      85,    17,   134,     8,     9,    26,    27,    28,    91,    25,
      26,    32,    85,    29,    52,    85,    37,   197,    39,    40,
     124,   125,    43,    44,    53,    41,    52,    53,    57,    58,
      93,    57,    58,   131,    53,    54,    55,    56,     5,     6,
     122,    79,    87,    81,    11,    85,   261,    52,   131,    87,
      59,    60,    57,    58,    87,    81,    94,    87,    53,   381,
      86,    87,    57,    58,    59,    60,     6,     7,    94,     9,
     168,   169,   170,    87,   172,   173,    81,   175,    82,    83,
     319,     6,    87,     8,     9,    85,   211,   185,    53,    94,
      85,    85,    57,    58,   253,   254,   255,   229,    85,   197,
      85,   199,   229,   201,     8,     9,   122,    61,    62,    87,
      77,   153,   154,   211,   212,   157,   198,    11,    57,    58,
      85,   203,   185,   205,   228,    85,   208,   209,    85,    69,
      70,   229,   230,   231,   373,    23,    24,   235,   222,   266,
      86,    85,   240,   159,    85,   243,   385,    85,    85,   165,
      85,    85,    85,    85,   252,   253,   254,   255,    85,   241,
     366,     6,     7,     8,     9,    10,    11,    12,   266,   267,
      85,    85,   235,    85,   141,    85,    85,   240,   199,    87,
     243,     6,   314,   315,    85,   289,   202,    90,    90,    85,
     211,     7,   159,    85,   210,   375,   300,   213,   214,    85,
      85,    85,    85,   219,   220,   221,    85,     8,     9,   225,
       7,     7,    53,    54,    55,   236,    57,    58,     6,   186,
     187,   242,   189,   239,     7,   323,   268,   269,   270,   196,
      87,   273,   274,   275,   276,   277,    86,    88,    87,   206,
      77,   339,    85,    56,     6,     8,     9,    10,     6,   381,
      85,    52,    85,    93,   381,   222,     8,     9,    85,    85,
      61,    62,     5,     6,     7,     8,     9,    10,    11,    12,
     368,    88,     6,    88,   372,     7,    88,   375,    79,    88,
      81,    88,   364,   381,    88,   367,    87,   369,    88,    52,
      85,    92,    85,    94,   310,     8,     9,    88,    85,    85,
      52,    85,    91,    85,    85,   368,   388,    85,    85,    85,
     352,   353,     8,     9,    77,    78,    79,   333,    81,     8,
       9,    10,    11,    12,    87,   423,    85,    79,   426,    81,
     434,    94,   436,    87,    86,    87,    85,   441,    85,    52,
     422,    91,    94,    85,   365,    85,    85,    88,     8,     9,
     432,    89,   319,     8,     9,    88,    52,    53,   374,    89,
     376,    57,    58,    59,    60,    61,    62,    85,    81,    65,
      54,   387,    88,    86,    87,    71,    72,    70,    85,   346,
     347,    94,    91,    79,     9,    81,     8,     9,    85,    88,
      86,    87,    52,    85,    85,    85,   244,    52,    94,   415,
       8,     9,    85,   424,   371,    85,   373,    85,   429,   425,
      85,   427,   428,   237,   430,    24,     8,     9,   385,    79,
     315,    81,   264,   347,    79,    -1,    81,    87,    -1,    -1,
      52,    -1,    87,    -1,    94,    -1,     8,     9,    -1,    94,
      -1,    -1,    -1,    -1,    52,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    77,    -1,    -1,    -1,    81,
      52,    -1,    -1,    -1,    -1,    87,    -1,    -1,    -1,    -1,
      -1,    79,    94,    81,    -1,    -1,    -1,    -1,    -1,    87,
      52,    -1,    -1,    -1,    -1,    -1,    94,    -1,    -1,    81,
      -1,    -1,    -1,    -1,    -1,    87,    -1,    -1,    90,    -1,
      -1,    -1,    94,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    -1,    -1,    -1,    87,    -1,    -1,    -1,    -1,
      -1,    -1,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    -1,    -1,     0,     1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    -1,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    -1,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    -1,    -1,    -1,    -1,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    74,    75,    76,
       0,     1,    79,    -1,    81,    -1,    84,    84,    -1,    -1,
      -1,    -1,    -1,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    -1,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    -1,    -1,    -1,    -1,    84,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,    79,
      -1,    81,    -1,    -1,    84
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    96,     0,     1,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    66,    74,    75,    76,    79,    81,    84,    97,
      99,    84,    85,   101,    57,    58,    86,   110,   111,   114,
     115,   118,   110,     8,     9,    52,    53,    59,    60,    61,
      62,    65,    71,    72,    79,    81,    86,    87,    94,   104,
     105,   106,   108,   109,   112,   118,   120,   122,   127,   128,
     131,   101,   101,   101,   110,   112,   122,   101,   112,    87,
     128,   131,   128,   112,   101,    67,   100,   101,   122,   106,
      86,   105,   121,   122,   121,   112,   102,   111,   112,   131,
     102,   111,    85,   101,   112,   122,   100,   100,   111,   100,
      79,    86,   103,   131,    92,   108,   123,   124,   125,   127,
     131,    87,   113,   111,   106,   111,   111,   112,   100,   111,
     111,    84,    82,    83,    83,    84,   101,    87,   131,    85,
       6,     7,     9,    69,    70,    85,   131,   131,    87,    87,
      87,     6,     8,     9,   129,     9,    10,    77,    78,   108,
     131,   118,   131,   132,   131,    85,    87,    87,    79,    87,
     103,   107,   128,   131,   103,   106,    85,    85,    85,    85,
      87,    11,    85,    85,   104,    85,    85,     9,    85,    85,
      85,    85,    85,    85,    85,   112,   122,   101,   101,    85,
      85,    85,    85,   129,   128,    85,    87,   126,   127,    85,
      90,    90,    53,   118,   119,    85,    85,    85,     6,    85,
      85,    85,    85,    85,    98,   132,   132,   132,    53,   112,
     118,   119,     6,     7,     7,     7,     6,   112,   131,   131,
     131,     7,   131,   131,    87,    77,    86,    88,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    88,   106,
     118,    53,    54,    55,   118,   130,   129,   118,    87,   119,
     103,   122,   111,   131,   131,   112,   122,   122,   118,   122,
     122,   112,   102,   131,   112,   112,   112,   112,   112,   110,
      85,   112,    56,    93,     9,   101,   123,   131,   131,    85,
     106,   111,   113,     6,   112,   106,   122,   111,   106,    97,
      84,    84,    88,    85,   117,   131,   117,   117,   117,     6,
      88,    88,    88,   129,   130,   108,    87,    90,   131,   132,
     132,   132,     6,     7,   132,   132,   132,   132,   132,    88,
      88,    88,    88,   101,    85,    85,    85,    85,    85,    85,
     101,    85,    85,    85,    85,    85,    85,   112,    88,   127,
     126,    85,    91,    91,   119,    85,   131,    85,    85,   112,
     131,    87,    88,   116,   118,   116,    89,   132,   132,    89,
     122,   111,   104,   122,   106,   122,   118,   131,   119,   112,
     103,   112,   123,    88,   119,    85,   112,   122,    54,    88,
      70,    91,    85,     9,    85,    85,    85,    85,    85,    85,
      85,   112,    85,    88,   122,   131,   111,   112,   131,   112,
     112,   111,   112,   122,   101,   101,   101
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    95,    96,    96,    97,    98,    97,    97,    97,    97,
      97,    97,    97,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,   100,   101,   101,   102,   102,   103,   103,   104,   104,
     104,   104,   104,   105,   105,   106,   106,   106,   106,   106,
     106,   106,   106,   107,   107,   108,   108,   108,   109,   109,
     109,   109,   109,   109,   110,   110,   110,   111,   112,   112,
     113,   114,   114,   114,   114,   115,   115,   115,   116,   116,
     117,   118,   118,   119,   119,   120,   120,   121,   121,   122,
     122,   123,   123,   123,   123,   124,   124,   125,   126,   126,
     126,   127,   127,   128,   128,   128,   129,   129,   129,   130,
     130,   130,   131,   131,   131,   131,   131,   131,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     0,     0,     4,     4,     4,     2,
       1,     2,     2,     2,     6,     5,     4,     4,     4,     4,
       7,     3,     3,     3,     3,     1,     5,     4,     4,     8,
       6,     6,     9,     4,     5,     8,     8,     2,     2,     2,
       3,     3,     3,     3,     4,     6,     8,     6,     4,     3,
       4,     4,     4,     4,     6,     5,     9,     9,     8,     4,
       6,     6,     8,     2,     4,     4,     2,     6,     4,     4,
       2,     1,     0,     2,     7,     1,     4,     2,     2,     2,
       4,     2,     1,     2,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     4,     1,     3,     4,
       5,     5,     6,     6,     1,     1,     1,     2,     1,     1,
       5,     4,     4,     4,     4,     1,     2,     5,     1,     2,
       1,     1,     4,     1,     1,     1,     4,     1,     1,     1,
       4,     1,     1,     1,     1,     4,     4,     3,     1,     3,
       3,     1,     4,     4,     5,     7,     0,     2,     2,     1,
       1,     1,     1,     1,     2,     2,     2,     3,     1,     3,
       3,     3,     3,     3,     4,     4,     3,     3,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 5:
#line 46 "a.y" /* yacc.c:1646  */
    {
		(yyvsp[-1].sym) = labellookup((yyvsp[-1].sym));
		if((yyvsp[-1].sym)->type == LLAB && (yyvsp[-1].sym)->value != pc)
			yyerror("redeclaration of %s", (yyvsp[-1].sym)->labelname);
		(yyvsp[-1].sym)->type = LLAB;
		(yyvsp[-1].sym)->value = pc;
	}
#line 1727 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 55 "a.y" /* yacc.c:1646  */
    {
		(yyvsp[-3].sym)->type = LVAR;
		(yyvsp[-3].sym)->value = (yyvsp[-1].lval);
	}
#line 1736 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 60 "a.y" /* yacc.c:1646  */
    {
		if((yyvsp[-3].sym)->value != (yyvsp[-1].lval))
			yyerror("redeclaration of %s", (yyvsp[-3].sym)->name);
		(yyvsp[-3].sym)->value = (yyvsp[-1].lval);
	}
#line 1746 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 66 "a.y" /* yacc.c:1646  */
    {
		nosched = (yyvsp[-1].lval);
	}
#line 1754 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 78 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &nullgen, NREG, &nullgen);
	}
#line 1762 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 85 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].lval), &(yyvsp[0].addr));
	}
#line 1770 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 89 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-4].lval), &(yyvsp[-3].addr), (yyvsp[-1].lval), &nullgen);
	}
#line 1778 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 93 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1786 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 100 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1794 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 107 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1802 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 114 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1810 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 118 "a.y" /* yacc.c:1646  */
    {
		Addr a;
		a = nullgen;
		a.type = D_CONST;
		a.offset = (yyvsp[-2].lval);
		outgcode((yyvsp[-6].lval), &(yyvsp[-5].addr), NREG, &a, &(yyvsp[0].addr));
	}
#line 1822 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 129 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1830 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 133 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1838 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 140 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1846 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 147 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1854 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 151 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[0].lval), &nullgen, NREG, &nullgen);
	}
#line 1862 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 158 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-4].lval), &(yyvsp[-3].addr), (yyvsp[-1].lval), &nullgen);
	}
#line 1870 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 165 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1878 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 172 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1886 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 179 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-2].addr).reg, &(yyvsp[-4].addr), &(yyvsp[0].addr));
	}
#line 1894 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 183 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].addr).reg, &(yyvsp[0].addr));
	}
#line 1902 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 190 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].addr).reg, &(yyvsp[0].addr));
	}
#line 1910 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 197 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-8].lval), &(yyvsp[-7].addr), (yyvsp[-3].addr).reg, &(yyvsp[-5].addr), &(yyvsp[-1].addr));
	}
#line 1918 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 204 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1926 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 208 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-4].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1934 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 215 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-2].lval), &(yyvsp[-4].addr), &(yyvsp[0].addr));
	}
#line 1942 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 222 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-2].lval), &(yyvsp[-4].addr), &(yyvsp[0].addr));
	}
#line 1950 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 229 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &nullgen, NREG, &nullgen);
	}
#line 1958 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 233 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1966 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 240 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &nullgen, NREG, &nullgen);
	}
#line 1974 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 244 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &(yyvsp[-1].addr), NREG, &nullgen);
	}
#line 1982 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 248 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &(yyvsp[-1].addr), NREG, &nullgen);
	}
#line 1990 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 252 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1998 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 256 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 2006 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 263 "a.y" /* yacc.c:1646  */
    {
		settext((yyvsp[-2].addr).sym);
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2015 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 268 "a.y" /* yacc.c:1646  */
    {
		settext((yyvsp[-4].addr).sym);
		(yyvsp[0].addr).offset &= 0xffffffffull;
		(yyvsp[0].addr).offset |= (vlong)ArgsSizeUnknown << 32;
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].lval), &(yyvsp[0].addr));
	}
#line 2026 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 275 "a.y" /* yacc.c:1646  */
    {
		settext((yyvsp[-6].addr).sym);
		(yyvsp[-2].addr).offset &= 0xffffffffull;
		(yyvsp[-2].addr).offset |= ((yyvsp[0].lval) & 0xffffffffull) << 32;
		outcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-4].lval), &(yyvsp[-2].addr));
	}
#line 2037 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 285 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].lval), &(yyvsp[0].addr));
	}
#line 2045 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 292 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2053 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 299 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 2061 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 306 "a.y" /* yacc.c:1646  */
    {
		if((yyvsp[-2].addr).type != D_CONST || (yyvsp[0].addr).type != D_CONST)
			yyerror("arguments to PCDATA must be integer constants");
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2071 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 315 "a.y" /* yacc.c:1646  */
    {
		if((yyvsp[-2].addr).type != D_CONST)
			yyerror("index for FUNCDATA must be integer constant");
		if((yyvsp[0].addr).type != D_EXTERN && (yyvsp[0].addr).type != D_STATIC && (yyvsp[0].addr).type != D_OREG)
			yyerror("value for FUNCDATA must be symbol reference");
 		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2083 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 326 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2091 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 333 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2099 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 337 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].addr).reg, &(yyvsp[0].addr));
	}
#line 2107 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 344 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-4].lval), &(yyvsp[-3].addr), (yyvsp[-1].addr).reg, &nullgen);
	}
#line 2115 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 351 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-8].lval), &(yyvsp[-7].addr), (yyvsp[-3].addr).reg, &(yyvsp[-5].addr), &(yyvsp[-1].addr));
	}
#line 2123 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 358 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-8].lval), &(yyvsp[-7].addr), (yyvsp[-5].addr).reg, &(yyvsp[-3].addr), &(yyvsp[-1].addr));
	}
#line 2131 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 365 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-2].addr).reg, &(yyvsp[-4].addr), &(yyvsp[0].addr));
	}
#line 2139 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 372 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2147 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 376 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].addr).reg, &(yyvsp[0].addr));
	}
#line 2155 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 383 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].lval), &(yyvsp[0].addr));
	}
#line 2163 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 390 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-2].lval), &(yyvsp[-4].addr), &(yyvsp[0].addr));
	}
#line 2171 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 397 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &(yyvsp[0].addr), NREG, &nullgen);
	}
#line 2179 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 401 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[0].addr), (yyvsp[-2].addr).reg, &nullgen);
	}
#line 2187 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 405 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2195 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 412 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &(yyvsp[0].addr), NREG, &nullgen);
	}
#line 2203 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 419 "a.y" /* yacc.c:1646  */
    {
		outtcode((yyvsp[-5].lval), &(yyvsp[-4].addr), &(yyvsp[-2].addr), &(yyvsp[0].addr));
	}
#line 2211 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 427 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2219 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 435 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2227 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 443 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &nullgen, NREG, &nullgen);
	}
#line 2235 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 449 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_COND;
		(yyval.addr).reg = (yyvsp[0].lval);
	}
#line 2245 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 460 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_CONST;
		(yyval.addr).offset = SYSARG4((yyvsp[-6].lval), (yyvsp[-4].lval), (yyvsp[-2].lval), (yyvsp[0].lval));
	}
#line 2255 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 469 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_BRANCH;
		(yyval.addr).offset = (yyvsp[-3].lval) + pc;
	}
#line 2265 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 475 "a.y" /* yacc.c:1646  */
    {
		(yyvsp[-1].sym) = labellookup((yyvsp[-1].sym));
		(yyval.addr) = nullgen;
		if(pass == 2 && (yyvsp[-1].sym)->type != LLAB)
			yyerror("undefined label: %s", (yyvsp[-1].sym)->labelname);
		(yyval.addr).type = D_BRANCH;
		(yyval.addr).offset = (yyvsp[-1].sym)->value + (yyvsp[0].lval);
	}
#line 2278 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 485 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_CONST;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2288 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 491 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = (yyvsp[0].addr);
		(yyval.addr).type = D_CONST;
	}
#line 2297 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 496 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = (yyvsp[0].addr);
		(yyval.addr).type = D_OCONST;
	}
#line 2306 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 501 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SCONST;
		memmove((yyval.addr).u.sval, (yyvsp[0].sval), sizeof((yyval.addr).u.sval));
	}
#line 2316 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 510 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FCONST;
		(yyval.addr).u.dval = (yyvsp[0].dval);
	}
#line 2326 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 516 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FCONST;
		(yyval.addr).u.dval = -(yyvsp[0].dval);
	}
#line 2336 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 526 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SPR;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2346 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 532 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2356 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 544 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
		(yyval.addr).offset = 0;
	}
#line 2367 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 551 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = (yyvsp[0].addr);
		if((yyvsp[0].addr).name != D_EXTERN && (yyvsp[0].addr).name != D_STATIC) {
		}
	}
#line 2377 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 560 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = (yyvsp[-3].addr);
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
	}
#line 2387 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 569 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
		(yyval.addr).offset = 0;
	}
#line 2398 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 576 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
		(yyval.addr).offset = (yyvsp[-3].lval);
	}
#line 2409 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 583 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_XPRE;
		(yyval.addr).reg = (yyvsp[-2].lval);
		(yyval.addr).offset = (yyvsp[-4].lval);
	}
#line 2420 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 590 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_XPOST;
		(yyval.addr).reg = (yyvsp[-3].lval);
		(yyval.addr).offset = (yyvsp[-1].lval);
	}
#line 2431 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 597 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_ROFF;
		(yyval.addr).reg = (yyvsp[-4].lval);
		(yyval.addr).scale = (yyvsp[-1].lval) & 0x1f;
		(yyval.addr).offset = (yyvsp[-1].lval);
	}
#line 2443 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 605 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_ROFF;
		(yyval.addr).reg = (yyvsp[-4].lval);
		(yyval.addr).scale = (yyvsp[-1].lval) & 0x1f;
		(yyval.addr).offset = (yyvsp[-1].lval) | (1<<16);
	}
#line 2455 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 619 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_CONST;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2465 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 627 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_REG;
		(yyval.addr).reg = (yyvsp[0].lval);
	}
#line 2475 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 633 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SP;
		(yyval.addr).reg = REGSP;
	}
#line 2485 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 641 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_PAIR;
		(yyval.addr).reg = (yyvsp[-3].lval);
		(yyval.addr).offset = (yyvsp[-1].lval);
	}
#line 2496 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 650 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = ((yyvsp[-3].lval) << 16) | ((yyvsp[0].lval) << 10) | (0 << 22);
	}
#line 2506 "y.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 656 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = (((yyvsp[-3].lval)&0x1F) << 16) | ((yyvsp[0].lval) << 10) | (1 << 22);
	}
#line 2516 "y.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 662 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = ((yyvsp[-3].lval) << 16) | ((yyvsp[0].lval) << 10) | (2 << 22);
	}
#line 2526 "y.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 668 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = ((yyvsp[-3].lval) << 16) | ((yyvsp[0].lval) << 10) | (3 << 22);
	}
#line 2536 "y.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 676 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_REG;
		(yyval.addr).reg = (yyvsp[0].lval);
	}
#line 2546 "y.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 682 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_EXTREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
		(yyval.addr).offset = ((yyvsp[-1].lval) << 16) | ((yyvsp[0].lval) << 13);
	}
#line 2557 "y.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 689 "a.y" /* yacc.c:1646  */
    {
		if((yyvsp[0].lval) < 0 || (yyvsp[0].lval) > 4)
			yyerror("shift value out of range");
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_EXTREG;
		(yyval.addr).reg = (yyvsp[-4].lval);
		(yyval.addr).offset = ((yyvsp[-4].lval) << 16) | ((yyvsp[-3].lval) << 13) | ((yyvsp[0].lval) << 10);
	}
#line 2570 "y.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 700 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (3 << 8) | (yyvsp[0].lval);
	}
#line 2578 "y.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 704 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = ((yyvsp[0].lval) << 8) | (yyvsp[-1].lval);
	}
#line 2586 "y.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 710 "a.y" /* yacc.c:1646  */
    {
		if((yyval.lval) < 0 || (yyval.lval) >= 64)
			yyerror("shift value out of range");
		(yyval.lval) = (yyvsp[0].lval)&0x3F;
	}
#line 2596 "y.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 719 "a.y" /* yacc.c:1646  */
    {
		if((yyvsp[-1].lval) < 0 || (yyvsp[-1].lval) >= NREG)
			print("register value out of range\n");
		(yyval.lval) = (yyvsp[-1].lval);
	}
#line 2606 "y.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 728 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = REGSP;
	}
#line 2614 "y.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 734 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SPR;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2624 "y.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 740 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = (yyvsp[-3].lval);
		(yyval.addr).offset = (yyvsp[-1].lval);
	}
#line 2634 "y.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 752 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FREG;
		(yyval.addr).reg = (yyvsp[0].lval);
	}
#line 2644 "y.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 758 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
	}
#line 2654 "y.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 769 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_VSET;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2664 "y.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 777 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr).type = D_VLANE;
		(yyval.addr).offset = (yyvsp[-1].lval);
	}
#line 2673 "y.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 782 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr).type = D_VLANE;
		(yyval.addr).offset = (yyvsp[-1].lval);
	}
#line 2682 "y.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 789 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-1].lval);
	}
#line 2690 "y.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 795 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = 1 << (yyvsp[0].addr).reg;
	}
#line 2698 "y.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 799 "a.y" /* yacc.c:1646  */
    {
		int i;
		(yyval.lval)=0;
		for(i=(yyvsp[-2].addr).reg; i<=(yyvsp[0].addr).reg; i++)
			(yyval.lval) |= 1<<i;
		for(i=(yyvsp[0].addr).reg; i<=(yyvsp[-2].addr).reg; i++)
			(yyval.lval) |= 1<<i;
	}
#line 2711 "y.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 808 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (1<<(yyvsp[-2].addr).reg) | (yyvsp[0].lval);
	}
#line 2719 "y.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 814 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_VREG;
		(yyval.addr).reg = (yyvsp[0].lval);
		/* TO DO: slice */
	}
#line 2730 "y.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 821 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_VREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
	}
#line 2740 "y.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 829 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).name = (yyvsp[-1].lval);
		(yyval.addr).sym = nil;
		(yyval.addr).offset = (yyvsp[-3].lval);
	}
#line 2752 "y.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 837 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).name = (yyvsp[-1].lval);
		(yyval.addr).sym = linklookup(ctxt, (yyvsp[-4].sym)->name, 0);
		(yyval.addr).offset = (yyvsp[-3].lval);
	}
#line 2764 "y.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 845 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).name = D_STATIC;
		(yyval.addr).sym = linklookup(ctxt, (yyvsp[-6].sym)->name, 0);
		(yyval.addr).offset = (yyvsp[-3].lval);
	}
#line 2776 "y.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 854 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = 0;
	}
#line 2784 "y.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 858 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[0].lval);
	}
#line 2792 "y.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 862 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = -(yyvsp[0].lval);
	}
#line 2800 "y.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 874 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[0].sym)->value;
	}
#line 2808 "y.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 878 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = -(yyvsp[0].lval);
	}
#line 2816 "y.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 882 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[0].lval);
	}
#line 2824 "y.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 886 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = ~(yyvsp[0].lval);
	}
#line 2832 "y.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 890 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-1].lval);
	}
#line 2840 "y.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 897 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) + (yyvsp[0].lval);
	}
#line 2848 "y.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 901 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) - (yyvsp[0].lval);
	}
#line 2856 "y.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 905 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) * (yyvsp[0].lval);
	}
#line 2864 "y.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 909 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) / (yyvsp[0].lval);
	}
#line 2872 "y.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 913 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) % (yyvsp[0].lval);
	}
#line 2880 "y.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 917 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-3].lval) << (yyvsp[0].lval);
	}
#line 2888 "y.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 921 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-3].lval) >> (yyvsp[0].lval);
	}
#line 2896 "y.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 925 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) & (yyvsp[0].lval);
	}
#line 2904 "y.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 929 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) ^ (yyvsp[0].lval);
	}
#line 2912 "y.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 933 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) | (yyvsp[0].lval);
	}
#line 2920 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2924 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
