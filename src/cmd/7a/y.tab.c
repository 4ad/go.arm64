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
#define YYLAST   736

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  95
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  165
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  434

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
     375,   382,   389,   396,   400,   404,   411,   418,   425,   431,
     438,   439,   442,   448,   451,   457,   467,   473,   478,   483,
     489,   492,   498,   506,   507,   508,   514,   520,   521,   522,
     523,   526,   533,   541,   542,   548,   551,   558,   565,   572,
     579,   587,   597,   598,   599,   601,   609,   615,   623,   629,
     635,   641,   649,   655,   662,   673,   677,   683,   691,   692,
     700,   701,   707,   713,   721,   722,   725,   731,   739,   740,
     741,   742,   750,   755,   762,   768,   772,   781,   787,   794,
     802,   810,   818,   828,   831,   835,   841,   842,   843,   846,
     847,   851,   855,   859,   863,   869,   870,   874,   878,   882,
     886,   890,   894,   898,   902,   906
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
  "fcon", "addr", "nireg", "oreg", "ioreg", "imsr", "imm", "reg", "shift",
  "extreg", "indexreg", "scon", "sreg", "spreg", "spr", "frcon", "freg",
  "vaddr", "vlane", "vset", "vreglist", "vreg", "name", "offset",
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

#define YYPACT_NINF -213

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-213)))

#define YYTABLE_NINF -136

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -213,   567,  -213,   -65,   -64,    -9,    -9,   434,   -64,   -64,
      92,    -9,    67,   163,   -14,   241,   241,    67,   -64,   -44,
     -64,   163,   434,    54,    54,    67,   232,   300,   -54,    -6,
     -44,   -44,   -54,   -44,    65,    81,   -54,   -54,   -54,    67,
     -44,   -54,   -54,   -49,   209,   -38,  -213,  -213,   -22,  -213,
     -64,  -213,   -18,  -213,   445,    11,  -213,  -213,  -213,    79,
      13,   445,   445,  -213,  -213,    36,  -213,    48,  -213,  -213,
      52,  -213,    49,  -213,    51,   253,   445,  -213,  -213,    20,
    -213,  -213,  -213,  -213,  -213,  -213,  -213,    63,    68,   316,
     368,   434,    24,    56,    72,  -213,  -213,   445,    76,    77,
     160,    89,  -213,  -213,    95,    97,   104,   108,    22,  -213,
     110,  -213,   112,   126,  -213,  -213,   129,   131,   146,   151,
     128,  -213,   -64,   -64,   158,   171,   184,   186,   286,   241,
     190,   192,   254,  -213,   196,  -213,   206,   222,    68,   201,
       9,  -213,   214,   236,   238,   242,  -213,  -213,   445,   445,
    -213,  -213,   445,  -213,   172,   323,   332,   344,   351,   356,
      67,  -213,  -213,   445,   445,   445,   357,   445,   445,   278,
     430,   281,  -213,  -213,  -213,    68,   283,  -213,   542,  -213,
     434,   274,   347,    49,   253,  -213,  -213,  -213,   282,  -213,
    -213,   207,   368,   163,   300,    12,   445,    67,   163,  -213,
     163,   274,   297,   163,   163,    67,   300,   445,    67,    67,
    -213,  -213,  -213,  -213,    67,    67,    67,    -9,  -213,   293,
      67,   326,   290,    41,    81,   445,   445,   -54,   373,    67,
     434,   163,   -54,   434,   644,   566,   616,   552,   299,  -213,
     303,   304,   445,   445,   445,   445,   379,  -213,   302,   308,
     310,   286,  -213,  -213,    12,  -213,   448,   450,   445,   445,
     445,   385,   392,   445,   445,   445,   445,   445,  -213,  -213,
     318,  -213,  -213,  -213,   319,   320,   278,   321,   198,  -213,
    -213,   -64,  -213,   307,  -213,   328,   329,  -213,   331,  -213,
     337,   340,   -64,   342,  -213,   345,  -213,   349,  -213,   350,
     352,   355,    67,  -213,   330,  -213,   254,   254,   359,   338,
     354,   361,   445,  -213,   363,   365,  -213,  -213,  -213,  -213,
    -213,  -213,    67,  -213,  -213,  -213,  -213,  -213,   445,  -213,
    -213,  -213,   324,   353,  -213,   253,   274,   372,   697,   724,
     195,   445,   445,    70,    70,  -213,  -213,  -213,  -213,   374,
    -213,  -213,  -213,   163,   -54,    97,   163,   434,   163,  -213,
     274,   445,   207,    67,   368,    67,  -213,  -213,  -213,  -213,
      81,  -213,  -213,   207,   380,    67,   163,  -213,  -213,   410,
    -213,   378,   397,   377,  -213,   333,   333,  -213,   384,   462,
    -213,   389,  -213,  -213,   394,   395,   396,   398,  -213,   399,
    -213,   403,    67,  -213,   413,   415,  -213,  -213,  -213,   163,
     445,   -54,    67,   445,    67,    67,   -54,    67,  -213,   163,
    -213,   -64,  -213,   -64,  -213,  -213,  -213,  -213,   -64,  -213,
    -213,  -213,  -213,  -213
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,    70,     0,     0,     0,    70,    70,
      70,     0,     0,     0,    70,     0,     0,     0,    70,     0,
      70,     0,     0,     0,     0,     0,     0,     0,     0,    70,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    10,     3,     0,    12,
      70,    13,     0,   118,     0,     0,   102,   103,   104,   112,
       0,     0,     0,   149,   107,     0,   126,     0,   138,    85,
       0,   122,   143,   150,     0,     0,     0,    84,    80,     0,
      87,    95,    83,   106,    90,    88,    89,    93,    86,     0,
       0,     0,     0,     0,     0,    37,    38,     0,     0,     0,
       0,     0,    68,    69,     0,     0,     0,     0,     0,   125,
       0,   124,     0,     0,    63,    73,     0,     0,     0,     0,
      70,    39,    70,    70,     0,     0,     0,     0,   143,     0,
       0,     0,     0,   128,     0,   130,   131,   129,     0,     0,
       0,    66,     0,     0,     0,     0,     9,     5,     0,     0,
      11,    71,     0,   105,     0,     0,     0,     0,     0,   113,
       0,   152,   151,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    81,    79,    77,    76,     0,   155,     0,   153,
       0,     0,     0,   143,     0,    21,    22,    92,     0,    23,
      24,     0,     0,     0,     0,     0,     0,     0,     0,    49,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      42,    43,    40,    41,     0,     0,     0,     0,    75,     0,
       0,     0,     0,    70,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   107,    16,
     106,     0,     0,     0,     0,     0,     0,    17,     0,     0,
       0,   143,   144,   145,     0,    82,     0,    96,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   154,    18,
       0,   147,   146,   148,     0,     0,    75,     0,     0,   121,
     120,    70,    27,     0,    44,     0,     0,    48,     0,    52,
       0,    53,    70,     0,    64,     0,    65,     0,    28,     0,
       0,     0,     0,    33,     0,   134,     0,     0,    59,     0,
       0,     0,     0,    19,     0,     0,    50,    51,     6,     7,
       8,   119,    15,   108,   117,   109,   110,   111,     0,   127,
     139,   123,     0,     0,    78,     0,     0,     0,   165,   164,
     163,     0,     0,   156,   157,   158,   159,   160,    94,    97,
     140,    91,    26,     0,     0,     0,     0,     0,     0,    55,
       0,     0,     0,     0,     0,     0,    34,    74,   136,   137,
       0,   133,   132,     0,     0,     0,     0,    14,   114,     0,
     141,     0,   115,     0,    99,   161,   162,    98,     0,    45,
      47,     0,    61,    54,     0,     0,     0,    30,    31,     0,
      60,     0,     0,    67,     0,     0,   100,   116,   101,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    20,     0,
     142,    70,    46,    70,    62,    72,    36,    29,    70,    35,
      58,    57,    56,    32
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -213,  -213,   243,  -213,  -213,   123,    -4,    -7,   -88,   -98,
     313,     4,  -213,   -32,  -213,    16,    74,    58,  -213,  -213,
     165,    59,   116,  -183,  -213,   480,    17,  -212,  -213,  -213,
     202,   -24,    18,  -115,   256,     2,    90
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    47,   234,    48,   104,   151,   114,   130,    77,
      78,    79,   186,    80,    81,    55,    56,    82,    57,    58,
     381,   323,    83,   241,    84,   110,    85,   134,   135,   136,
     222,    86,    87,   169,   275,   177,   178
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      51,   185,   189,   133,    89,    90,    91,   199,   281,    88,
      95,   137,   308,   218,   102,   228,   105,    99,    99,    49,
     118,    50,    60,   103,    88,   121,   107,    92,   117,   117,
      94,   202,    54,    98,   100,   146,   131,   138,   106,    64,
     111,   111,   174,    52,    53,   149,   123,    64,    52,    53,
     306,    52,    53,    65,    66,   166,   153,   167,   168,    61,
     170,   171,   150,   161,   162,   271,   272,   273,   276,   152,
      93,    50,    96,    61,    62,   101,   175,    54,   179,   120,
     265,   266,   267,   113,   116,   155,   156,   122,   157,    61,
      62,   188,   131,    88,   229,   190,   154,   142,   160,   172,
     115,   115,   119,    63,   282,   180,   126,   187,   223,   191,
     139,   140,   141,    65,    66,   144,   145,    63,   212,   213,
      64,    59,    59,   163,    52,    53,    50,    59,   172,   173,
      72,    99,    73,    63,  -135,   164,   332,   211,    75,   165,
     108,   192,    67,    68,   128,    76,    73,   219,   158,   159,
     181,   129,    97,   124,   125,   182,   127,   193,   400,    76,
      72,   194,    73,   143,   195,   248,   249,   250,    75,   252,
     253,   196,   162,   132,   197,    76,   -25,    50,   210,   396,
     198,    64,    88,    74,   269,    52,    53,    65,    66,   200,
     401,   176,   133,   201,   131,   203,   285,   204,   286,   294,
     137,   261,   262,   263,   264,   265,   266,   267,   117,   295,
     283,   205,   239,    50,   206,   288,   207,   289,   247,   307,
     291,   292,    65,    66,   334,   238,   138,   309,   310,    52,
      53,   208,    88,   301,   314,    88,   209,   317,   235,   236,
      61,    62,   237,   214,   324,   324,   324,   324,   315,    61,
      62,   271,   272,   273,   304,   287,   215,   390,   138,   337,
     279,    61,    62,   293,    52,    53,   296,   297,   284,   216,
     240,   217,   298,   299,   300,   220,   398,   352,   303,   221,
     115,   224,   368,   223,    63,    64,   227,   313,   359,    52,
      53,   147,   148,    63,   167,   168,   225,   270,   274,   230,
     277,   311,   325,   326,   327,    63,   316,   280,    61,    62,
      52,    53,   226,    73,   374,    67,    68,   290,    54,    97,
      72,   231,    73,   232,    61,    62,    76,   233,    97,   242,
     378,    52,    53,    59,    73,    76,   109,   109,   133,   243,
      97,   263,   264,   265,   266,   267,   137,    76,   338,   339,
     340,   244,    63,   343,   344,   345,   346,   347,   245,    88,
     366,   392,   246,   395,   251,   254,   131,   256,    63,   278,
     388,   257,   138,   391,   255,   393,    61,    62,   302,   312,
     377,    73,   304,   305,  -121,   328,    54,    97,  -120,   322,
     329,   341,   353,   404,    76,   183,   330,    73,   331,   342,
     271,   272,   273,   184,    52,    53,   348,   349,   350,   351,
      76,   379,   422,   354,   355,   425,   356,   431,   367,   432,
      63,   397,   357,   399,   433,   358,   421,   360,   389,   371,
     361,   385,   386,   403,   362,   363,   430,   364,    61,    62,
     365,   380,    61,    62,   370,   372,   373,   128,   375,    73,
     376,   382,   382,    61,    62,    97,    61,    62,    61,    62,
     418,   384,    76,   387,   405,   402,   406,   407,   408,   409,
     424,   410,   426,   427,   411,   429,   394,   318,   280,   412,
     413,   414,    63,   415,   416,   423,    63,    64,   417,   280,
     428,    52,    53,    65,    66,    67,    68,    63,   419,    69,
      63,   383,    63,   420,   112,    70,    71,   255,     0,   369,
     333,    73,     0,    72,     0,    73,     0,    97,     0,     0,
      74,    75,     0,     0,    76,     0,    73,    72,    76,    73,
       0,    73,    97,     0,     0,    75,     0,   335,     0,    76,
     336,     0,    76,     0,    76,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,     0,     0,     2,     3,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,     0,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,     0,    36,     0,    37,    38,    39,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,     0,
     268,     0,     0,    40,     0,     0,     0,     0,     0,     0,
     321,    41,    42,    43,    -4,     3,    44,     0,    45,     0,
     319,    46,     0,     0,     0,     0,     0,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
       0,    36,     0,    37,    38,    39,     0,     0,     0,     0,
     320,   259,   260,   261,   262,   263,   264,   265,   266,   267,
      40,     0,     0,     0,     0,     0,     0,     0,    41,    42,
      43,     0,     0,    44,     0,    45,     0,     0,    46,   260,
     261,   262,   263,   264,   265,   266,   267
};

static const yytype_int16 yycheck[] =
{
       4,    89,    90,    35,     8,     9,    10,   105,   191,     7,
      14,    35,   224,   128,    18,     6,    20,    15,    16,    84,
      27,    85,     6,    67,    22,    29,    22,    11,    26,    27,
      13,     9,    86,    15,    16,    84,    34,    35,    21,    53,
      23,    24,    74,    57,    58,    83,    29,    53,    57,    58,
       9,    57,    58,    59,    60,     6,    54,     8,     9,     8,
       9,    10,    84,    61,    62,    53,    54,    55,   183,    87,
      12,    85,    14,     8,     9,    17,    74,    86,    76,    85,
      10,    11,    12,    25,    26,     6,     7,    29,     9,     8,
       9,    89,    90,    91,    85,    91,    85,    39,    85,    77,
      26,    27,    28,    52,   192,    85,    32,    89,   132,    85,
      36,    37,    38,    59,    60,    41,    42,    52,   122,   123,
      53,     5,     6,    87,    57,    58,    85,    11,    77,    78,
      79,   129,    81,    52,    93,    87,   251,   120,    87,    87,
      86,    85,    61,    62,    79,    94,    81,   129,    69,    70,
      87,    86,    87,    30,    31,    87,    33,    85,   370,    94,
      79,    85,    81,    40,    87,   163,   164,   165,    87,   167,
     168,    11,   170,    92,    85,    94,    84,    85,   120,   362,
      85,    53,   180,    86,   180,    57,    58,    59,    60,    85,
     373,    75,   224,    85,   192,    85,   194,    85,   196,   206,
     224,     6,     7,     8,     9,    10,    11,    12,   206,   207,
     193,    85,   154,    85,    85,   198,    85,   200,   160,   223,
     203,   204,    59,    60,   256,    53,   224,   225,   226,    57,
      58,    85,   230,   217,   230,   233,    85,   233,   148,   149,
       8,     9,   152,    85,   242,   243,   244,   245,   231,     8,
       9,    53,    54,    55,    56,   197,    85,   355,   256,   257,
      53,     8,     9,   205,    57,    58,   208,   209,   194,    85,
     154,    85,   214,   215,   216,    85,   364,   281,   220,    87,
     206,    85,   306,   307,    52,    53,    85,   229,   292,    57,
      58,    82,    83,    52,     8,     9,    90,   181,   182,    85,
     184,   227,   243,   244,   245,    52,   232,   191,     8,     9,
      57,    58,    90,    81,   312,    61,    62,   201,    86,    87,
      79,    85,    81,    85,     8,     9,    94,    85,    87,     6,
     328,    57,    58,   217,    81,    94,    23,    24,   370,     7,
      87,     8,     9,    10,    11,    12,   370,    94,   258,   259,
     260,     7,    52,   263,   264,   265,   266,   267,     7,   357,
     302,   357,     6,   361,     7,    87,   364,    86,    52,    87,
     353,    88,   370,   356,    77,   358,     8,     9,    85,     6,
     322,    81,    56,    93,    85,     6,    86,    87,    85,    85,
      88,     6,    85,   376,    94,    79,    88,    81,    88,     7,
      53,    54,    55,    87,    57,    58,    88,    88,    88,    88,
      94,    87,   410,    85,    85,   413,    85,   421,    88,   423,
      52,   363,    85,   365,   428,    85,   409,    85,   354,    91,
      85,   341,   342,   375,    85,    85,   419,    85,     8,     9,
      85,    88,     8,     9,    85,    91,    85,    79,    85,    81,
      85,   335,   336,     8,     9,    87,     8,     9,     8,     9,
     402,    89,    94,    89,    54,    85,    88,    70,    91,    85,
     412,     9,   414,   415,    85,   417,   360,   234,   362,    85,
      85,    85,    52,    85,    85,   411,    52,    53,    85,   373,
     416,    57,    58,    59,    60,    61,    62,    52,    85,    65,
      52,   336,    52,    88,    24,    71,    72,    77,    -1,   307,
     254,    81,    -1,    79,    -1,    81,    -1,    87,    -1,    -1,
      86,    87,    -1,    -1,    94,    -1,    81,    79,    94,    81,
      -1,    81,    87,    -1,    -1,    87,    -1,    87,    -1,    94,
      90,    -1,    94,    -1,    94,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    -1,    -1,     0,     1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    -1,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    -1,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    -1,    47,    -1,    49,    50,    51,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    -1,
      88,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    74,    75,    76,     0,     1,    79,    -1,    81,    -1,
      84,    84,    -1,    -1,    -1,    -1,    -1,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    -1,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    47,    -1,    49,    50,    51,    -1,    -1,    -1,    -1,
      84,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,
      76,    -1,    -1,    79,    -1,    81,    -1,    -1,    84,     5,
       6,     7,     8,     9,    10,    11,    12
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    96,     0,     1,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    47,    49,    50,    51,
      66,    74,    75,    76,    79,    81,    84,    97,    99,    84,
      85,   101,    57,    58,    86,   110,   111,   113,   114,   117,
     110,     8,     9,    52,    53,    59,    60,    61,    62,    65,
      71,    72,    79,    81,    86,    87,    94,   104,   105,   106,
     108,   109,   112,   117,   119,   121,   126,   127,   130,   101,
     101,   101,   110,   112,   121,   101,   112,    87,   127,   130,
     127,   112,   101,    67,   100,   101,   121,   106,    86,   105,
     120,   121,   120,   112,   102,   111,   112,   130,   102,   111,
      85,   101,   112,   121,   100,   100,   111,   100,    79,    86,
     103,   130,    92,   108,   122,   123,   124,   126,   130,   111,
     111,   111,   112,   100,   111,   111,    84,    82,    83,    83,
      84,   101,    87,   130,    85,     6,     7,     9,    69,    70,
      85,   130,   130,    87,    87,    87,     6,     8,     9,   128,
       9,    10,    77,    78,   108,   130,   117,   130,   131,   130,
      85,    87,    87,    79,    87,   103,   107,   127,   130,   103,
     106,    85,    85,    85,    85,    87,    11,    85,    85,   104,
      85,    85,     9,    85,    85,    85,    85,    85,    85,    85,
     112,   121,   101,   101,    85,    85,    85,    85,   128,   127,
      85,    87,   125,   126,    85,    90,    90,    85,     6,    85,
      85,    85,    85,    85,    98,   131,   131,   131,    53,   112,
     117,   118,     6,     7,     7,     7,     6,   112,   130,   130,
     130,     7,   130,   130,    87,    77,    86,    88,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    88,   106,
     117,    53,    54,    55,   117,   129,   128,   117,    87,    53,
     117,   118,   103,   121,   111,   130,   130,   112,   121,   121,
     117,   121,   121,   112,   102,   130,   112,   112,   112,   112,
     112,   110,    85,   112,    56,    93,     9,   101,   122,   130,
     130,   111,     6,   112,   106,   121,   111,   106,    97,    84,
      84,    88,    85,   116,   130,   116,   116,   116,     6,    88,
      88,    88,   128,   129,   108,    87,    90,   130,   131,   131,
     131,     6,     7,   131,   131,   131,   131,   131,    88,    88,
      88,    88,   101,    85,    85,    85,    85,    85,    85,   101,
      85,    85,    85,    85,    85,    85,   112,    88,   126,   125,
      85,    91,    91,    85,   130,    85,    85,   112,   130,    87,
      88,   115,   117,   115,    89,   131,   131,    89,   121,   111,
     104,   121,   106,   121,   117,   130,   118,   112,   103,   112,
     122,   118,    85,   112,   121,    54,    88,    70,    91,    85,
       9,    85,    85,    85,    85,    85,    85,    85,   112,    85,
      88,   121,   130,   111,   112,   130,   112,   112,   111,   112,
     121,   101,   101,   101
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
      99,    99,    99,    99,    99,    99,    99,    99,    99,   100,
     101,   101,   102,   102,   103,   103,   104,   104,   104,   104,
     104,   105,   105,   106,   106,   106,   106,   106,   106,   106,
     106,   107,   107,   108,   108,   108,   109,   109,   109,   109,
     109,   109,   110,   110,   110,   111,   112,   112,   113,   113,
     113,   113,   114,   114,   114,   115,   115,   116,   117,   117,
     118,   118,   119,   119,   120,   120,   121,   121,   122,   122,
     122,   122,   123,   123,   124,   125,   125,   125,   126,   126,
     127,   127,   127,   128,   128,   128,   129,   129,   129,   130,
     130,   130,   130,   130,   130,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131
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
       6,     6,     8,     2,     4,     4,     2,     6,     2,     1,
       0,     2,     7,     1,     4,     2,     2,     2,     4,     2,
       1,     2,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     4,     1,     3,     4,     5,     5,
       6,     6,     1,     1,     1,     2,     1,     1,     4,     4,
       4,     4,     1,     2,     5,     1,     2,     1,     1,     4,
       1,     1,     1,     4,     1,     1,     1,     4,     1,     1,
       1,     1,     4,     4,     3,     1,     3,     3,     1,     4,
       4,     5,     7,     0,     2,     2,     1,     1,     1,     1,
       1,     2,     2,     2,     3,     1,     3,     3,     3,     3,
       3,     4,     4,     3,     3,     3
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
#line 1710 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 55 "a.y" /* yacc.c:1646  */
    {
		(yyvsp[-3].sym)->type = LVAR;
		(yyvsp[-3].sym)->value = (yyvsp[-1].lval);
	}
#line 1719 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 60 "a.y" /* yacc.c:1646  */
    {
		if((yyvsp[-3].sym)->value != (yyvsp[-1].lval))
			yyerror("redeclaration of %s", (yyvsp[-3].sym)->name);
		(yyvsp[-3].sym)->value = (yyvsp[-1].lval);
	}
#line 1729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 66 "a.y" /* yacc.c:1646  */
    {
		nosched = (yyvsp[-1].lval);
	}
#line 1737 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 78 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &nullgen, NREG, &nullgen);
	}
#line 1745 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 85 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].lval), &(yyvsp[0].addr));
	}
#line 1753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 89 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-4].lval), &(yyvsp[-3].addr), (yyvsp[-1].lval), &nullgen);
	}
#line 1761 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 93 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1769 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 100 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1777 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 107 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1785 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 114 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1793 "y.tab.c" /* yacc.c:1646  */
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
#line 1805 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 129 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1813 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 133 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1821 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 140 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1829 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 147 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1837 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 151 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[0].lval), &nullgen, NREG, &nullgen);
	}
#line 1845 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 158 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-4].lval), &(yyvsp[-3].addr), (yyvsp[-1].lval), &nullgen);
	}
#line 1853 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 165 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1861 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 172 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1869 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 179 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-2].addr).reg, &(yyvsp[-4].addr), &(yyvsp[0].addr));
	}
#line 1877 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 183 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].addr).reg, &(yyvsp[0].addr));
	}
#line 1885 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 190 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].addr).reg, &(yyvsp[0].addr));
	}
#line 1893 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 197 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-8].lval), &(yyvsp[-7].addr), (yyvsp[-3].addr).reg, &(yyvsp[-5].addr), &(yyvsp[-1].addr));
	}
#line 1901 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 204 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1909 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 208 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-4].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1917 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 215 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-2].lval), &(yyvsp[-4].addr), &(yyvsp[0].addr));
	}
#line 1925 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 222 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-2].lval), &(yyvsp[-4].addr), &(yyvsp[0].addr));
	}
#line 1933 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 229 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &nullgen, NREG, &nullgen);
	}
#line 1941 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 233 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1949 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 240 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &nullgen, NREG, &nullgen);
	}
#line 1957 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 244 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &(yyvsp[-1].addr), NREG, &nullgen);
	}
#line 1965 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 248 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &(yyvsp[-1].addr), NREG, &nullgen);
	}
#line 1973 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 252 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1981 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 256 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1989 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 263 "a.y" /* yacc.c:1646  */
    {
		settext((yyvsp[-2].addr).sym);
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1998 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 268 "a.y" /* yacc.c:1646  */
    {
		settext((yyvsp[-4].addr).sym);
		(yyvsp[0].addr).offset &= 0xffffffffull;
		(yyvsp[0].addr).offset |= (vlong)ArgsSizeUnknown << 32;
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].lval), &(yyvsp[0].addr));
	}
#line 2009 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 275 "a.y" /* yacc.c:1646  */
    {
		settext((yyvsp[-6].addr).sym);
		(yyvsp[-2].addr).offset &= 0xffffffffull;
		(yyvsp[-2].addr).offset |= ((yyvsp[0].lval) & 0xffffffffull) << 32;
		outcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-4].lval), &(yyvsp[-2].addr));
	}
#line 2020 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 285 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].lval), &(yyvsp[0].addr));
	}
#line 2028 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 292 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2036 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 299 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 2044 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 306 "a.y" /* yacc.c:1646  */
    {
		if((yyvsp[-2].addr).type != D_CONST || (yyvsp[0].addr).type != D_CONST)
			yyerror("arguments to PCDATA must be integer constants");
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2054 "y.tab.c" /* yacc.c:1646  */
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
#line 2066 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 326 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2074 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 333 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2082 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 337 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].addr).reg, &(yyvsp[0].addr));
	}
#line 2090 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 344 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-4].lval), &(yyvsp[-3].addr), (yyvsp[-1].addr).reg, &nullgen);
	}
#line 2098 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 351 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-8].lval), &(yyvsp[-7].addr), (yyvsp[-3].addr).reg, &(yyvsp[-5].addr), &(yyvsp[-1].addr));
	}
#line 2106 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 358 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-8].lval), &(yyvsp[-7].addr), (yyvsp[-5].addr).reg, &(yyvsp[-3].addr), &(yyvsp[-1].addr));
	}
#line 2114 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 365 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-2].addr).reg, &(yyvsp[-4].addr), &(yyvsp[0].addr));
	}
#line 2122 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 372 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2130 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 376 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].addr).reg, &(yyvsp[0].addr));
	}
#line 2138 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 383 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].lval), &(yyvsp[0].addr));
	}
#line 2146 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 390 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-2].lval), &(yyvsp[-4].addr), &(yyvsp[0].addr));
	}
#line 2154 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 397 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &(yyvsp[0].addr), NREG, &nullgen);
	}
#line 2162 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 401 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[0].addr), (yyvsp[-2].addr).reg, &nullgen);
	}
#line 2170 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 405 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2178 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 412 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &(yyvsp[0].addr), NREG, &nullgen);
	}
#line 2186 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 419 "a.y" /* yacc.c:1646  */
    {
		outtcode((yyvsp[-5].lval), &(yyvsp[-4].addr), &(yyvsp[-2].addr), &(yyvsp[0].addr));
	}
#line 2194 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 426 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &nullgen, NREG, &nullgen);
	}
#line 2202 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 432 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_COND;
		(yyval.addr).reg = (yyvsp[0].lval);
	}
#line 2212 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 443 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_CONST;
		(yyval.addr).offset = SYSARG4((yyvsp[-6].lval), (yyvsp[-4].lval), (yyvsp[-2].lval), (yyvsp[0].lval));
	}
#line 2222 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 452 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_BRANCH;
		(yyval.addr).offset = (yyvsp[-3].lval) + pc;
	}
#line 2232 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 458 "a.y" /* yacc.c:1646  */
    {
		(yyvsp[-1].sym) = labellookup((yyvsp[-1].sym));
		(yyval.addr) = nullgen;
		if(pass == 2 && (yyvsp[-1].sym)->type != LLAB)
			yyerror("undefined label: %s", (yyvsp[-1].sym)->labelname);
		(yyval.addr).type = D_BRANCH;
		(yyval.addr).offset = (yyvsp[-1].sym)->value + (yyvsp[0].lval);
	}
#line 2245 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 468 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_CONST;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2255 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 474 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = (yyvsp[0].addr);
		(yyval.addr).type = D_CONST;
	}
#line 2264 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 479 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = (yyvsp[0].addr);
		(yyval.addr).type = D_OCONST;
	}
#line 2273 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 484 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SCONST;
		memmove((yyval.addr).u.sval, (yyvsp[0].sval), sizeof((yyval.addr).u.sval));
	}
#line 2283 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 493 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FCONST;
		(yyval.addr).u.dval = (yyvsp[0].dval);
	}
#line 2293 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 499 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FCONST;
		(yyval.addr).u.dval = -(yyvsp[0].dval);
	}
#line 2303 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 509 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SPR;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2313 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 515 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2323 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 527 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
		(yyval.addr).offset = 0;
	}
#line 2334 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 534 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = (yyvsp[0].addr);
		if((yyvsp[0].addr).name != D_EXTERN && (yyvsp[0].addr).name != D_STATIC) {
		}
	}
#line 2344 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 543 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = (yyvsp[-3].addr);
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
	}
#line 2354 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 552 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
		(yyval.addr).offset = 0;
	}
#line 2365 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 559 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
		(yyval.addr).offset = (yyvsp[-3].lval);
	}
#line 2376 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 566 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_XPRE;
		(yyval.addr).reg = (yyvsp[-2].lval);
		(yyval.addr).offset = (yyvsp[-4].lval);
	}
#line 2387 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 573 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_XPOST;
		(yyval.addr).reg = (yyvsp[-3].lval);
		(yyval.addr).offset = (yyvsp[-1].lval);
	}
#line 2398 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 580 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_ROFF;
		(yyval.addr).reg = (yyvsp[-4].lval);
		(yyval.addr).scale = (yyvsp[-1].lval) & 0x1f;
		(yyval.addr).offset = (yyvsp[-1].lval);
	}
#line 2410 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 588 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_ROFF;
		(yyval.addr).reg = (yyvsp[-4].lval);
		(yyval.addr).scale = (yyvsp[-1].lval) & 0x1f;
		(yyval.addr).offset = (yyvsp[-1].lval) | (1<<16);
	}
#line 2422 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 602 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_CONST;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2432 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 610 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_REG;
		(yyval.addr).reg = (yyvsp[0].lval);
	}
#line 2442 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 616 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SP;
		(yyval.addr).reg = REGSP;
	}
#line 2452 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 624 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = ((yyvsp[-3].lval) << 16) | ((yyvsp[0].lval) << 10) | (0 << 22);
	}
#line 2462 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 630 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = (((yyvsp[-3].lval)&0x1F) << 16) | ((yyvsp[0].lval) << 10) | (1 << 22);
	}
#line 2472 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 636 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = ((yyvsp[-3].lval) << 16) | ((yyvsp[0].lval) << 10) | (2 << 22);
	}
#line 2482 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 642 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = ((yyvsp[-3].lval) << 16) | ((yyvsp[0].lval) << 10) | (3 << 22);
	}
#line 2492 "y.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 650 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_REG;
		(yyval.addr).reg = (yyvsp[0].lval);
	}
#line 2502 "y.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 656 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_EXTREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
		(yyval.addr).offset = ((yyvsp[-1].lval) << 16) | ((yyvsp[0].lval) << 13);
	}
#line 2513 "y.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 663 "a.y" /* yacc.c:1646  */
    {
		if((yyvsp[0].lval) < 0 || (yyvsp[0].lval) > 4)
			yyerror("shift value out of range");
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_EXTREG;
		(yyval.addr).reg = (yyvsp[-4].lval);
		(yyval.addr).offset = ((yyvsp[-4].lval) << 16) | ((yyvsp[-3].lval) << 13) | ((yyvsp[0].lval) << 10);
	}
#line 2526 "y.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 674 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (3 << 8) | (yyvsp[0].lval);
	}
#line 2534 "y.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 678 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = ((yyvsp[0].lval) << 8) | (yyvsp[-1].lval);
	}
#line 2542 "y.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 684 "a.y" /* yacc.c:1646  */
    {
		if((yyval.lval) < 0 || (yyval.lval) >= 64)
			yyerror("shift value out of range");
		(yyval.lval) = (yyvsp[0].lval)&0x3F;
	}
#line 2552 "y.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 693 "a.y" /* yacc.c:1646  */
    {
		if((yyvsp[-1].lval) < 0 || (yyvsp[-1].lval) >= NREG)
			print("register value out of range\n");
		(yyval.lval) = (yyvsp[-1].lval);
	}
#line 2562 "y.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 702 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = REGSP;
	}
#line 2570 "y.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 708 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SPR;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2580 "y.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 714 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = (yyvsp[-3].lval);
		(yyval.addr).offset = (yyvsp[-1].lval);
	}
#line 2590 "y.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 726 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FREG;
		(yyval.addr).reg = (yyvsp[0].lval);
	}
#line 2600 "y.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 732 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
	}
#line 2610 "y.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 743 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_VSET;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2620 "y.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 751 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr).type = D_VLANE;
		(yyval.addr).offset = (yyvsp[-1].lval);
	}
#line 2629 "y.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 756 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr).type = D_VLANE;
		(yyval.addr).offset = (yyvsp[-1].lval);
	}
#line 2638 "y.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 763 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-1].lval);
	}
#line 2646 "y.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 769 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = 1 << (yyvsp[0].addr).reg;
	}
#line 2654 "y.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 773 "a.y" /* yacc.c:1646  */
    {
		int i;
		(yyval.lval)=0;
		for(i=(yyvsp[-2].addr).reg; i<=(yyvsp[0].addr).reg; i++)
			(yyval.lval) |= 1<<i;
		for(i=(yyvsp[0].addr).reg; i<=(yyvsp[-2].addr).reg; i++)
			(yyval.lval) |= 1<<i;
	}
#line 2667 "y.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 782 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (1<<(yyvsp[-2].addr).reg) | (yyvsp[0].lval);
	}
#line 2675 "y.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 788 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_VREG;
		(yyval.addr).reg = (yyvsp[0].lval);
		/* TO DO: slice */
	}
#line 2686 "y.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 795 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_VREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
	}
#line 2696 "y.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 803 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).name = (yyvsp[-1].lval);
		(yyval.addr).sym = nil;
		(yyval.addr).offset = (yyvsp[-3].lval);
	}
#line 2708 "y.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 811 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).name = (yyvsp[-1].lval);
		(yyval.addr).sym = linklookup(ctxt, (yyvsp[-4].sym)->name, 0);
		(yyval.addr).offset = (yyvsp[-3].lval);
	}
#line 2720 "y.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 819 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).name = D_STATIC;
		(yyval.addr).sym = linklookup(ctxt, (yyvsp[-6].sym)->name, 0);
		(yyval.addr).offset = (yyvsp[-3].lval);
	}
#line 2732 "y.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 828 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = 0;
	}
#line 2740 "y.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 832 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[0].lval);
	}
#line 2748 "y.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 836 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = -(yyvsp[0].lval);
	}
#line 2756 "y.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 848 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[0].sym)->value;
	}
#line 2764 "y.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 852 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = -(yyvsp[0].lval);
	}
#line 2772 "y.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 856 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[0].lval);
	}
#line 2780 "y.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 860 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = ~(yyvsp[0].lval);
	}
#line 2788 "y.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 864 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-1].lval);
	}
#line 2796 "y.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 871 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) + (yyvsp[0].lval);
	}
#line 2804 "y.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 875 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) - (yyvsp[0].lval);
	}
#line 2812 "y.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 879 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) * (yyvsp[0].lval);
	}
#line 2820 "y.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 883 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) / (yyvsp[0].lval);
	}
#line 2828 "y.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 887 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) % (yyvsp[0].lval);
	}
#line 2836 "y.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 891 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-3].lval) << (yyvsp[0].lval);
	}
#line 2844 "y.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 895 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-3].lval) >> (yyvsp[0].lval);
	}
#line 2852 "y.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 899 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) & (yyvsp[0].lval);
	}
#line 2860 "y.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 903 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) ^ (yyvsp[0].lval);
	}
#line 2868 "y.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 907 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) | (yyvsp[0].lval);
	}
#line 2876 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2880 "y.tab.c" /* yacc.c:1646  */
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
