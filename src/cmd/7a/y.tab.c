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

#line 258 "y.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 273 "y.tab.c" /* yacc.c:358  */

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
#define YYLAST   709

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  92
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  164
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  430

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   323

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
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
  "LSPR", "LSPREG", "LVTYPE", "LFCONST", "LSCONST", "LNAME", "LLAB",
  "LVAR", "':'", "'='", "';'", "','", "'$'", "'('", "')'", "'!'", "'['",
  "']'", "'{'", "'}'", "'~'", "$accept", "prog", "line", "$@1", "$@2",
  "inst", "cond", "comma", "sysarg", "rel", "ximm", "fcon", "addr",
  "nireg", "oreg", "ioreg", "imsr", "imm", "reg", "shift", "extreg",
  "indexreg", "scon", "sreg", "spreg", "spr", "frcon", "freg", "vaddr",
  "vlane", "vset", "vreglist", "vreg", "name", "offset", "pointer", "con",
  "expr", YY_NULLPTR
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
     315,   316,   317,   318,   319,   320,   321,   322,   323,    58,
      61,    59,    44,    36,    40,    41,    33,    91,    93,   123,
     125,   126
};
# endif

#define YYPACT_NINF -216

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-216)))

#define YYTABLE_NINF -135

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
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

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
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

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -216,  -216,  -192,  -216,  -216,  -216,   140,    -4,    -6,   -68,
    -102,   227,     4,  -216,   -24,  -216,    -3,    32,    70,  -216,
    -216,   201,    72,   117,  -175,  -216,   510,    18,  -215,  -216,
    -216,   237,   -33,     7,   -94,   305,     2,    90
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    45,   232,   230,    46,   102,   148,   112,   129,
      75,    76,    77,   183,    78,    79,    53,    54,    80,    55,
      56,   377,   319,    81,   238,    82,   108,    83,   133,   134,
     135,   220,    84,    85,   166,   272,   174,   175
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
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

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
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
        case 4:
#line 45 "a.y" /* yacc.c:1661  */
    {
		if((yyvsp[-1].sym)->value != pc)
			yyerror("redeclaration of %s", (yyvsp[-1].sym)->name);
		(yyvsp[-1].sym)->value = pc;
	}
#line 1693 "y.tab.c" /* yacc.c:1661  */
    break;

  case 6:
#line 52 "a.y" /* yacc.c:1661  */
    {
		(yyvsp[-1].sym)->type = LLAB;
		(yyvsp[-1].sym)->value = pc;
	}
#line 1702 "y.tab.c" /* yacc.c:1661  */
    break;

  case 8:
#line 58 "a.y" /* yacc.c:1661  */
    {
		(yyvsp[-3].sym)->type = LVAR;
		(yyvsp[-3].sym)->value = (yyvsp[-1].lval);
	}
#line 1711 "y.tab.c" /* yacc.c:1661  */
    break;

  case 9:
#line 63 "a.y" /* yacc.c:1661  */
    {
		if((yyvsp[-3].sym)->value != (yyvsp[-1].lval))
			yyerror("redeclaration of %s", (yyvsp[-3].sym)->name);
		(yyvsp[-3].sym)->value = (yyvsp[-1].lval);
	}
#line 1721 "y.tab.c" /* yacc.c:1661  */
    break;

  case 13:
#line 77 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-1].lval), &nullgen, NREG, &nullgen);
	}
#line 1729 "y.tab.c" /* yacc.c:1661  */
    break;

  case 14:
#line 84 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].lval), &(yyvsp[0].addr));
	}
#line 1737 "y.tab.c" /* yacc.c:1661  */
    break;

  case 15:
#line 88 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-4].lval), &(yyvsp[-3].addr), (yyvsp[-1].lval), &nullgen);
	}
#line 1745 "y.tab.c" /* yacc.c:1661  */
    break;

  case 16:
#line 92 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1753 "y.tab.c" /* yacc.c:1661  */
    break;

  case 17:
#line 99 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1761 "y.tab.c" /* yacc.c:1661  */
    break;

  case 18:
#line 106 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1769 "y.tab.c" /* yacc.c:1661  */
    break;

  case 19:
#line 113 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1777 "y.tab.c" /* yacc.c:1661  */
    break;

  case 20:
#line 117 "a.y" /* yacc.c:1661  */
    {
		Addr a;
		a = nullgen;
		a.type = D_CONST;
		a.offset = (yyvsp[-2].lval);
		outgcode((yyvsp[-6].lval), &(yyvsp[-5].addr), NREG, &a, &(yyvsp[0].addr));
	}
#line 1789 "y.tab.c" /* yacc.c:1661  */
    break;

  case 21:
#line 128 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1797 "y.tab.c" /* yacc.c:1661  */
    break;

  case 22:
#line 132 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1805 "y.tab.c" /* yacc.c:1661  */
    break;

  case 23:
#line 139 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1813 "y.tab.c" /* yacc.c:1661  */
    break;

  case 24:
#line 146 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1821 "y.tab.c" /* yacc.c:1661  */
    break;

  case 25:
#line 150 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[0].lval), &nullgen, NREG, &nullgen);
	}
#line 1829 "y.tab.c" /* yacc.c:1661  */
    break;

  case 26:
#line 157 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-4].lval), &(yyvsp[-3].addr), (yyvsp[-1].lval), &nullgen);
	}
#line 1837 "y.tab.c" /* yacc.c:1661  */
    break;

  case 27:
#line 164 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1845 "y.tab.c" /* yacc.c:1661  */
    break;

  case 28:
#line 171 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1853 "y.tab.c" /* yacc.c:1661  */
    break;

  case 29:
#line 178 "a.y" /* yacc.c:1661  */
    {
		outgcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-2].addr).reg, &(yyvsp[-4].addr), &(yyvsp[0].addr));
	}
#line 1861 "y.tab.c" /* yacc.c:1661  */
    break;

  case 30:
#line 182 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].addr).reg, &(yyvsp[0].addr));
	}
#line 1869 "y.tab.c" /* yacc.c:1661  */
    break;

  case 31:
#line 189 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].addr).reg, &(yyvsp[0].addr));
	}
#line 1877 "y.tab.c" /* yacc.c:1661  */
    break;

  case 32:
#line 196 "a.y" /* yacc.c:1661  */
    {
		outgcode((yyvsp[-8].lval), &(yyvsp[-7].addr), (yyvsp[-3].addr).reg, &(yyvsp[-5].addr), &(yyvsp[-1].addr));
	}
#line 1885 "y.tab.c" /* yacc.c:1661  */
    break;

  case 33:
#line 203 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1893 "y.tab.c" /* yacc.c:1661  */
    break;

  case 34:
#line 207 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-4].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1901 "y.tab.c" /* yacc.c:1661  */
    break;

  case 35:
#line 214 "a.y" /* yacc.c:1661  */
    {
		outgcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-2].lval), &(yyvsp[-4].addr), &(yyvsp[0].addr));
	}
#line 1909 "y.tab.c" /* yacc.c:1661  */
    break;

  case 36:
#line 221 "a.y" /* yacc.c:1661  */
    {
		outgcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-2].lval), &(yyvsp[-4].addr), &(yyvsp[0].addr));
	}
#line 1917 "y.tab.c" /* yacc.c:1661  */
    break;

  case 37:
#line 228 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-1].lval), &nullgen, NREG, &nullgen);
	}
#line 1925 "y.tab.c" /* yacc.c:1661  */
    break;

  case 38:
#line 232 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-1].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1933 "y.tab.c" /* yacc.c:1661  */
    break;

  case 39:
#line 239 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-1].lval), &nullgen, NREG, &nullgen);
	}
#line 1941 "y.tab.c" /* yacc.c:1661  */
    break;

  case 40:
#line 243 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-2].lval), &(yyvsp[-1].addr), NREG, &nullgen);
	}
#line 1949 "y.tab.c" /* yacc.c:1661  */
    break;

  case 41:
#line 247 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-2].lval), &(yyvsp[-1].addr), NREG, &nullgen);
	}
#line 1957 "y.tab.c" /* yacc.c:1661  */
    break;

  case 42:
#line 251 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1965 "y.tab.c" /* yacc.c:1661  */
    break;

  case 43:
#line 255 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1973 "y.tab.c" /* yacc.c:1661  */
    break;

  case 44:
#line 262 "a.y" /* yacc.c:1661  */
    {
		settext((yyvsp[-2].addr).sym);
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1982 "y.tab.c" /* yacc.c:1661  */
    break;

  case 45:
#line 267 "a.y" /* yacc.c:1661  */
    {
		settext((yyvsp[-4].addr).sym);
		(yyvsp[0].addr).offset &= 0xffffffffull;
		(yyvsp[0].addr).offset |= (vlong)ArgsSizeUnknown << 32;
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].lval), &(yyvsp[0].addr));
	}
#line 1993 "y.tab.c" /* yacc.c:1661  */
    break;

  case 46:
#line 274 "a.y" /* yacc.c:1661  */
    {
		settext((yyvsp[-6].addr).sym);
		(yyvsp[-2].addr).offset &= 0xffffffffull;
		(yyvsp[-2].addr).offset |= ((yyvsp[0].lval) & 0xffffffffull) << 32;
		outcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-4].lval), &(yyvsp[-2].addr));
	}
#line 2004 "y.tab.c" /* yacc.c:1661  */
    break;

  case 47:
#line 284 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].lval), &(yyvsp[0].addr));
	}
#line 2012 "y.tab.c" /* yacc.c:1661  */
    break;

  case 48:
#line 291 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2020 "y.tab.c" /* yacc.c:1661  */
    break;

  case 49:
#line 298 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 2028 "y.tab.c" /* yacc.c:1661  */
    break;

  case 50:
#line 305 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2036 "y.tab.c" /* yacc.c:1661  */
    break;

  case 51:
#line 312 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2044 "y.tab.c" /* yacc.c:1661  */
    break;

  case 52:
#line 316 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].addr).reg, &(yyvsp[0].addr));
	}
#line 2052 "y.tab.c" /* yacc.c:1661  */
    break;

  case 53:
#line 323 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-4].lval), &(yyvsp[-3].addr), (yyvsp[-1].addr).reg, &nullgen);
	}
#line 2060 "y.tab.c" /* yacc.c:1661  */
    break;

  case 54:
#line 330 "a.y" /* yacc.c:1661  */
    {
		outgcode((yyvsp[-8].lval), &(yyvsp[-7].addr), (yyvsp[-3].addr).reg, &(yyvsp[-5].addr), &(yyvsp[-1].addr));
	}
#line 2068 "y.tab.c" /* yacc.c:1661  */
    break;

  case 55:
#line 337 "a.y" /* yacc.c:1661  */
    {
		outgcode((yyvsp[-8].lval), &(yyvsp[-7].addr), (yyvsp[-5].addr).reg, &(yyvsp[-3].addr), &(yyvsp[-1].addr));
	}
#line 2076 "y.tab.c" /* yacc.c:1661  */
    break;

  case 56:
#line 344 "a.y" /* yacc.c:1661  */
    {
		outgcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-2].addr).reg, &(yyvsp[-4].addr), &(yyvsp[0].addr));
	}
#line 2084 "y.tab.c" /* yacc.c:1661  */
    break;

  case 57:
#line 351 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2092 "y.tab.c" /* yacc.c:1661  */
    break;

  case 58:
#line 355 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].addr).reg, &(yyvsp[0].addr));
	}
#line 2100 "y.tab.c" /* yacc.c:1661  */
    break;

  case 59:
#line 362 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].lval), &(yyvsp[0].addr));
	}
#line 2108 "y.tab.c" /* yacc.c:1661  */
    break;

  case 60:
#line 369 "a.y" /* yacc.c:1661  */
    {
		outgcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-2].lval), &(yyvsp[-4].addr), &(yyvsp[0].addr));
	}
#line 2116 "y.tab.c" /* yacc.c:1661  */
    break;

  case 61:
#line 376 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-1].lval), &(yyvsp[0].addr), NREG, &nullgen);
	}
#line 2124 "y.tab.c" /* yacc.c:1661  */
    break;

  case 62:
#line 380 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[0].addr), (yyvsp[-2].addr).reg, &nullgen);
	}
#line 2132 "y.tab.c" /* yacc.c:1661  */
    break;

  case 63:
#line 384 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2140 "y.tab.c" /* yacc.c:1661  */
    break;

  case 64:
#line 391 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-1].lval), &(yyvsp[0].addr), NREG, &nullgen);
	}
#line 2148 "y.tab.c" /* yacc.c:1661  */
    break;

  case 65:
#line 398 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[0].lval), &(yyvsp[-2].addr));
	}
#line 2156 "y.tab.c" /* yacc.c:1661  */
    break;

  case 66:
#line 405 "a.y" /* yacc.c:1661  */
    {
		outcode((yyvsp[-1].lval), &nullgen, NREG, &nullgen);
	}
#line 2164 "y.tab.c" /* yacc.c:1661  */
    break;

  case 67:
#line 411 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_COND;
		(yyval.addr).reg = (yyvsp[0].lval);
	}
#line 2174 "y.tab.c" /* yacc.c:1661  */
    break;

  case 70:
#line 422 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_CONST;
		(yyval.addr).offset = SYSARG4((yyvsp[-6].lval), (yyvsp[-4].lval), (yyvsp[-2].lval), (yyvsp[0].lval));
	}
#line 2184 "y.tab.c" /* yacc.c:1661  */
    break;

  case 72:
#line 431 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_BRANCH;
		(yyval.addr).offset = (yyvsp[-3].lval) + pc;
	}
#line 2194 "y.tab.c" /* yacc.c:1661  */
    break;

  case 73:
#line 437 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		if(pass == 2)
			yyerror("undefined label: %s", (yyvsp[-1].sym)->name);
		(yyval.addr).type = D_BRANCH;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2206 "y.tab.c" /* yacc.c:1661  */
    break;

  case 74:
#line 445 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_BRANCH;
		(yyval.addr).offset = (yyvsp[-1].sym)->value + (yyvsp[0].lval);
	}
#line 2216 "y.tab.c" /* yacc.c:1661  */
    break;

  case 75:
#line 452 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_CONST;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2226 "y.tab.c" /* yacc.c:1661  */
    break;

  case 76:
#line 458 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = (yyvsp[0].addr);
		(yyval.addr).type = D_CONST;
	}
#line 2235 "y.tab.c" /* yacc.c:1661  */
    break;

  case 77:
#line 463 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = (yyvsp[0].addr);
		(yyval.addr).type = D_OCONST;
	}
#line 2244 "y.tab.c" /* yacc.c:1661  */
    break;

  case 78:
#line 468 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SCONST;
		memmove((yyval.addr).u.sval, (yyvsp[0].sval), sizeof((yyval.addr).u.sval));
	}
#line 2254 "y.tab.c" /* yacc.c:1661  */
    break;

  case 80:
#line 477 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FCONST;
		(yyval.addr).u.dval = (yyvsp[0].dval);
	}
#line 2264 "y.tab.c" /* yacc.c:1661  */
    break;

  case 81:
#line 483 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FCONST;
		(yyval.addr).u.dval = -(yyvsp[0].dval);
	}
#line 2274 "y.tab.c" /* yacc.c:1661  */
    break;

  case 84:
#line 493 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SPR;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2284 "y.tab.c" /* yacc.c:1661  */
    break;

  case 85:
#line 499 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2294 "y.tab.c" /* yacc.c:1661  */
    break;

  case 90:
#line 511 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
		(yyval.addr).offset = 0;
	}
#line 2305 "y.tab.c" /* yacc.c:1661  */
    break;

  case 91:
#line 518 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = (yyvsp[0].addr);
		if((yyvsp[0].addr).name != D_EXTERN && (yyvsp[0].addr).name != D_STATIC) {
		}
	}
#line 2315 "y.tab.c" /* yacc.c:1661  */
    break;

  case 93:
#line 527 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = (yyvsp[-3].addr);
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
	}
#line 2325 "y.tab.c" /* yacc.c:1661  */
    break;

  case 95:
#line 536 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
		(yyval.addr).offset = 0;
	}
#line 2336 "y.tab.c" /* yacc.c:1661  */
    break;

  case 96:
#line 543 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
		(yyval.addr).offset = (yyvsp[-3].lval);
	}
#line 2347 "y.tab.c" /* yacc.c:1661  */
    break;

  case 97:
#line 550 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_XPRE;
		(yyval.addr).reg = (yyvsp[-2].lval);
		(yyval.addr).offset = (yyvsp[-4].lval);
	}
#line 2358 "y.tab.c" /* yacc.c:1661  */
    break;

  case 98:
#line 557 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_XPOST;
		(yyval.addr).reg = (yyvsp[-3].lval);
		(yyval.addr).offset = (yyvsp[-1].lval);
	}
#line 2369 "y.tab.c" /* yacc.c:1661  */
    break;

  case 99:
#line 564 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_ROFF;
		(yyval.addr).reg = (yyvsp[-4].lval);
		(yyval.addr).scale = (yyvsp[-1].lval) & 0x1f;
		(yyval.addr).offset = (yyvsp[-1].lval);
	}
#line 2381 "y.tab.c" /* yacc.c:1661  */
    break;

  case 100:
#line 572 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_ROFF;
		(yyval.addr).reg = (yyvsp[-4].lval);
		(yyval.addr).scale = (yyvsp[-1].lval) & 0x1f;
		(yyval.addr).offset = (yyvsp[-1].lval) | (1<<16);
	}
#line 2393 "y.tab.c" /* yacc.c:1661  */
    break;

  case 104:
#line 586 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_CONST;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2403 "y.tab.c" /* yacc.c:1661  */
    break;

  case 105:
#line 594 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_REG;
		(yyval.addr).reg = (yyvsp[0].lval);
	}
#line 2413 "y.tab.c" /* yacc.c:1661  */
    break;

  case 106:
#line 600 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SP;
		(yyval.addr).reg = REGSP;
	}
#line 2423 "y.tab.c" /* yacc.c:1661  */
    break;

  case 107:
#line 608 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = ((yyvsp[-3].lval) << 16) | ((yyvsp[0].lval) << 10) | (0 << 22);
	}
#line 2433 "y.tab.c" /* yacc.c:1661  */
    break;

  case 108:
#line 614 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = (((yyvsp[-3].lval)&0x1F) << 16) | ((yyvsp[0].lval) << 10) | (1 << 22);
	}
#line 2443 "y.tab.c" /* yacc.c:1661  */
    break;

  case 109:
#line 620 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = ((yyvsp[-3].lval) << 16) | ((yyvsp[0].lval) << 10) | (2 << 22);
	}
#line 2453 "y.tab.c" /* yacc.c:1661  */
    break;

  case 110:
#line 626 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = ((yyvsp[-3].lval) << 16) | ((yyvsp[0].lval) << 10) | (3 << 22);
	}
#line 2463 "y.tab.c" /* yacc.c:1661  */
    break;

  case 111:
#line 634 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_REG;
		(yyval.addr).reg = (yyvsp[0].lval);
	}
#line 2473 "y.tab.c" /* yacc.c:1661  */
    break;

  case 112:
#line 640 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_EXTREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
		(yyval.addr).offset = ((yyvsp[-1].lval) << 16) | ((yyvsp[0].lval) << 13);
	}
#line 2484 "y.tab.c" /* yacc.c:1661  */
    break;

  case 113:
#line 647 "a.y" /* yacc.c:1661  */
    {
		if((yyvsp[0].lval) < 0 || (yyvsp[0].lval) > 4)
			yyerror("shift value out of range");
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_EXTREG;
		(yyval.addr).reg = (yyvsp[-4].lval);
		(yyval.addr).offset = ((yyvsp[-4].lval) << 16) | ((yyvsp[-3].lval) << 13) | ((yyvsp[0].lval) << 10);
	}
#line 2497 "y.tab.c" /* yacc.c:1661  */
    break;

  case 114:
#line 658 "a.y" /* yacc.c:1661  */
    {
		(yyval.lval) = (3 << 8) | (yyvsp[0].lval);
	}
#line 2505 "y.tab.c" /* yacc.c:1661  */
    break;

  case 115:
#line 662 "a.y" /* yacc.c:1661  */
    {
		(yyval.lval) = ((yyvsp[0].lval) << 8) | (yyvsp[-1].lval);
	}
#line 2513 "y.tab.c" /* yacc.c:1661  */
    break;

  case 116:
#line 668 "a.y" /* yacc.c:1661  */
    {
		if((yyval.lval) < 0 || (yyval.lval) >= 64)
			yyerror("shift value out of range");
		(yyval.lval) = (yyvsp[0].lval)&0x3F;
	}
#line 2523 "y.tab.c" /* yacc.c:1661  */
    break;

  case 118:
#line 677 "a.y" /* yacc.c:1661  */
    {
		if((yyvsp[-1].lval) < 0 || (yyvsp[-1].lval) >= NREG)
			print("register value out of range\n");
		(yyval.lval) = (yyvsp[-1].lval);
	}
#line 2533 "y.tab.c" /* yacc.c:1661  */
    break;

  case 120:
#line 686 "a.y" /* yacc.c:1661  */
    {
		(yyval.lval) = REGSP;
	}
#line 2541 "y.tab.c" /* yacc.c:1661  */
    break;

  case 121:
#line 692 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SPR;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2551 "y.tab.c" /* yacc.c:1661  */
    break;

  case 122:
#line 698 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = (yyvsp[-3].lval);
		(yyval.addr).offset = (yyvsp[-1].lval);
	}
#line 2561 "y.tab.c" /* yacc.c:1661  */
    break;

  case 125:
#line 710 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FREG;
		(yyval.addr).reg = (yyvsp[0].lval);
	}
#line 2571 "y.tab.c" /* yacc.c:1661  */
    break;

  case 126:
#line 716 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
	}
#line 2581 "y.tab.c" /* yacc.c:1661  */
    break;

  case 130:
#line 727 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_VSET;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2591 "y.tab.c" /* yacc.c:1661  */
    break;

  case 131:
#line 735 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr).type = D_VLANE;
		(yyval.addr).offset = (yyvsp[-1].lval);
	}
#line 2600 "y.tab.c" /* yacc.c:1661  */
    break;

  case 132:
#line 740 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr).type = D_VLANE;
		(yyval.addr).offset = (yyvsp[-1].lval);
	}
#line 2609 "y.tab.c" /* yacc.c:1661  */
    break;

  case 133:
#line 747 "a.y" /* yacc.c:1661  */
    {
		(yyval.lval) = (yyvsp[-1].lval);
	}
#line 2617 "y.tab.c" /* yacc.c:1661  */
    break;

  case 134:
#line 753 "a.y" /* yacc.c:1661  */
    {
		(yyval.lval) = 1 << (yyvsp[0].addr).reg;
	}
#line 2625 "y.tab.c" /* yacc.c:1661  */
    break;

  case 135:
#line 757 "a.y" /* yacc.c:1661  */
    {
		int i;
		(yyval.lval)=0;
		for(i=(yyvsp[-2].addr).reg; i<=(yyvsp[0].addr).reg; i++)
			(yyval.lval) |= 1<<i;
		for(i=(yyvsp[0].addr).reg; i<=(yyvsp[-2].addr).reg; i++)
			(yyval.lval) |= 1<<i;
	}
#line 2638 "y.tab.c" /* yacc.c:1661  */
    break;

  case 136:
#line 766 "a.y" /* yacc.c:1661  */
    {
		(yyval.lval) = (1<<(yyvsp[-2].addr).reg) | (yyvsp[0].lval);
	}
#line 2646 "y.tab.c" /* yacc.c:1661  */
    break;

  case 137:
#line 772 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_VREG;
		(yyval.addr).reg = (yyvsp[0].lval);
		/* TO DO: slice */
	}
#line 2657 "y.tab.c" /* yacc.c:1661  */
    break;

  case 138:
#line 779 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_VREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
	}
#line 2667 "y.tab.c" /* yacc.c:1661  */
    break;

  case 139:
#line 787 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).name = (yyvsp[-1].lval);
		(yyval.addr).sym = nil;
		(yyval.addr).offset = (yyvsp[-3].lval);
	}
#line 2679 "y.tab.c" /* yacc.c:1661  */
    break;

  case 140:
#line 795 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).name = (yyvsp[-1].lval);
		(yyval.addr).sym = linklookup(ctxt, (yyvsp[-4].sym)->name, 0);
		(yyval.addr).offset = (yyvsp[-3].lval);
	}
#line 2691 "y.tab.c" /* yacc.c:1661  */
    break;

  case 141:
#line 803 "a.y" /* yacc.c:1661  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).name = D_STATIC;
		(yyval.addr).sym = linklookup(ctxt, (yyvsp[-6].sym)->name, 0);
		(yyval.addr).offset = (yyvsp[-3].lval);
	}
#line 2703 "y.tab.c" /* yacc.c:1661  */
    break;

  case 142:
#line 812 "a.y" /* yacc.c:1661  */
    {
		(yyval.lval) = 0;
	}
#line 2711 "y.tab.c" /* yacc.c:1661  */
    break;

  case 143:
#line 816 "a.y" /* yacc.c:1661  */
    {
		(yyval.lval) = (yyvsp[0].lval);
	}
#line 2719 "y.tab.c" /* yacc.c:1661  */
    break;

  case 144:
#line 820 "a.y" /* yacc.c:1661  */
    {
		(yyval.lval) = -(yyvsp[0].lval);
	}
#line 2727 "y.tab.c" /* yacc.c:1661  */
    break;

  case 149:
#line 832 "a.y" /* yacc.c:1661  */
    {
		(yyval.lval) = (yyvsp[0].sym)->value;
	}
#line 2735 "y.tab.c" /* yacc.c:1661  */
    break;

  case 150:
#line 836 "a.y" /* yacc.c:1661  */
    {
		(yyval.lval) = -(yyvsp[0].lval);
	}
#line 2743 "y.tab.c" /* yacc.c:1661  */
    break;

  case 151:
#line 840 "a.y" /* yacc.c:1661  */
    {
		(yyval.lval) = (yyvsp[0].lval);
	}
#line 2751 "y.tab.c" /* yacc.c:1661  */
    break;

  case 152:
#line 844 "a.y" /* yacc.c:1661  */
    {
		(yyval.lval) = ~(yyvsp[0].lval);
	}
#line 2759 "y.tab.c" /* yacc.c:1661  */
    break;

  case 153:
#line 848 "a.y" /* yacc.c:1661  */
    {
		(yyval.lval) = (yyvsp[-1].lval);
	}
#line 2767 "y.tab.c" /* yacc.c:1661  */
    break;

  case 155:
#line 855 "a.y" /* yacc.c:1661  */
    {
		(yyval.lval) = (yyvsp[-2].lval) + (yyvsp[0].lval);
	}
#line 2775 "y.tab.c" /* yacc.c:1661  */
    break;

  case 156:
#line 859 "a.y" /* yacc.c:1661  */
    {
		(yyval.lval) = (yyvsp[-2].lval) - (yyvsp[0].lval);
	}
#line 2783 "y.tab.c" /* yacc.c:1661  */
    break;

  case 157:
#line 863 "a.y" /* yacc.c:1661  */
    {
		(yyval.lval) = (yyvsp[-2].lval) * (yyvsp[0].lval);
	}
#line 2791 "y.tab.c" /* yacc.c:1661  */
    break;

  case 158:
#line 867 "a.y" /* yacc.c:1661  */
    {
		(yyval.lval) = (yyvsp[-2].lval) / (yyvsp[0].lval);
	}
#line 2799 "y.tab.c" /* yacc.c:1661  */
    break;

  case 159:
#line 871 "a.y" /* yacc.c:1661  */
    {
		(yyval.lval) = (yyvsp[-2].lval) % (yyvsp[0].lval);
	}
#line 2807 "y.tab.c" /* yacc.c:1661  */
    break;

  case 160:
#line 875 "a.y" /* yacc.c:1661  */
    {
		(yyval.lval) = (yyvsp[-3].lval) << (yyvsp[0].lval);
	}
#line 2815 "y.tab.c" /* yacc.c:1661  */
    break;

  case 161:
#line 879 "a.y" /* yacc.c:1661  */
    {
		(yyval.lval) = (yyvsp[-3].lval) >> (yyvsp[0].lval);
	}
#line 2823 "y.tab.c" /* yacc.c:1661  */
    break;

  case 162:
#line 883 "a.y" /* yacc.c:1661  */
    {
		(yyval.lval) = (yyvsp[-2].lval) & (yyvsp[0].lval);
	}
#line 2831 "y.tab.c" /* yacc.c:1661  */
    break;

  case 163:
#line 887 "a.y" /* yacc.c:1661  */
    {
		(yyval.lval) = (yyvsp[-2].lval) ^ (yyvsp[0].lval);
	}
#line 2839 "y.tab.c" /* yacc.c:1661  */
    break;

  case 164:
#line 891 "a.y" /* yacc.c:1661  */
    {
		(yyval.lval) = (yyvsp[-2].lval) | (yyvsp[0].lval);
	}
#line 2847 "y.tab.c" /* yacc.c:1661  */
    break;


#line 2851 "y.tab.c" /* yacc.c:1661  */
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
