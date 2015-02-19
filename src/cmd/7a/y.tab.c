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
#define YYLAST   776

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  95
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  169
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  448

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
       0,    41,    41,    43,    42,    48,    50,    49,    58,    63,
      69,    73,    74,    75,    81,    88,    92,    96,   103,   110,
     117,   121,   132,   136,   143,   150,   154,   161,   168,   175,
     182,   186,   193,   200,   207,   211,   218,   225,   232,   236,
     243,   247,   251,   255,   259,   266,   271,   278,   288,   295,
     302,   309,   318,   329,   336,   340,   347,   354,   361,   368,
     375,   379,   386,   393,   400,   404,   408,   415,   422,   430,
     438,   446,   452,   459,   460,   463,   469,   472,   478,   488,
     494,   499,   504,   510,   513,   519,   527,   528,   529,   535,
     541,   542,   543,   544,   547,   554,   562,   563,   569,   572,
     579,   586,   593,   600,   608,   618,   619,   620,   622,   630,
     636,   644,   653,   659,   665,   671,   679,   685,   692,   703,
     707,   713,   721,   722,   730,   731,   737,   743,   751,   752,
     755,   761,   769,   770,   771,   772,   780,   785,   792,   798,
     802,   811,   817,   824,   832,   840,   848,   858,   861,   865,
     871,   872,   873,   876,   877,   881,   885,   889,   893,   899,
     900,   904,   908,   912,   916,   920,   924,   928,   932,   936
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
  "prog", "$@1", "line", "$@2", "inst", "cond", "comma", "sysarg", "rel",
  "ximm", "fcon", "addr", "nireg", "oreg", "ioreg", "imsr", "imm", "reg",
  "regreg", "shift", "extreg", "indexreg", "scon", "sreg", "spreg", "spr",
  "frcon", "freg", "vaddr", "vlane", "vset", "vreglist", "vreg", "name",
  "offset", "pointer", "con", "expr", YY_NULLPTR
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

#define YYPACT_NINF -224

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-224)))

#define YYTABLE_NINF -140

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -224,    23,  -224,   643,   -63,   -59,   -14,   -14,   404,   -59,
     -59,    44,   -14,   -23,    40,   135,    62,    62,   -23,   -59,
     -29,   -59,    40,   404,    -9,    -9,   -23,    74,   387,   -40,
       3,   -29,   -29,   -40,   -29,   348,   299,   -39,   -40,   404,
     -40,   -40,   -23,   -29,   -40,   -40,   -30,    68,    -7,  -224,
    -224,   -10,  -224,   -59,  -224,    -8,  -224,   528,    -1,  -224,
    -224,  -224,   160,    27,   528,   528,  -224,  -224,    55,  -224,
      58,  -224,  -224,    67,  -224,   199,  -224,   337,    95,   528,
    -224,  -224,    30,  -224,  -224,  -224,  -224,  -224,  -224,  -224,
      70,    86,   440,   445,   404,    93,    96,   100,  -224,  -224,
     528,   106,   111,   189,   119,  -224,  -224,   124,   133,   140,
     143,    10,  -224,   159,  -224,   165,   166,  -224,  -224,   167,
     168,   173,   185,   105,  -224,   -59,   -59,   186,   188,   190,
     191,   209,    62,   194,   197,   174,  -224,   196,  -224,   198,
     201,    86,    28,   202,   204,   208,    39,  -224,   214,   215,
     216,   217,  -224,  -224,   528,   528,  -224,  -224,   528,  -224,
     126,   300,   303,   304,   311,   318,   -23,  -224,  -224,   528,
     528,   528,   323,   528,   528,   249,   478,   251,  -224,  -224,
    -224,    86,   250,  -224,   542,  -224,   404,   183,   259,   199,
      95,  -224,  -224,  -224,   253,  -224,  -224,    28,   445,    40,
     387,    14,   528,   -23,    40,  -224,    40,   183,   265,    40,
      40,   -23,   387,   528,   -23,   -23,  -224,  -224,  -224,  -224,
     -23,   -23,   -23,   -14,  -224,   258,   -23,   288,   257,     4,
     299,   528,   528,  -224,  -224,   263,   404,   -40,   -39,   346,
     -23,   404,    40,   -40,   404,   643,   642,   692,   628,   268,
    -224,   273,   274,   528,   528,   528,   528,   365,  -224,   284,
     285,   287,   209,  -224,  -224,    14,  -224,   492,   508,   528,
     528,   528,   370,   372,   528,   528,   528,   528,   528,  -224,
    -224,   293,  -224,  -224,  -224,   296,   302,   249,   309,    81,
     -59,  -224,   307,  -224,   313,   314,  -224,   316,  -224,   317,
     319,   -59,   322,  -224,   324,  -224,   341,  -224,   351,   353,
     356,   -23,  -224,   315,  -224,   174,   174,   358,   297,   342,
      28,  -224,   360,  -224,   528,  -224,   361,   362,  -224,  -224,
    -224,  -224,  -224,  -224,   -23,  -224,  -224,  -224,  -224,  -224,
     528,  -224,  -224,  -224,   321,   363,  -224,    95,   183,   366,
     724,   357,   255,   528,   528,    80,    80,  -224,  -224,  -224,
    -224,   378,  -224,  -224,  -224,    40,   -40,   133,    40,   404,
      40,  -224,   183,   528,    28,   -23,   445,   -23,  -224,  -224,
    -224,  -224,   299,  -224,  -224,   371,    28,   385,   -23,    40,
    -224,  -224,   418,  -224,   389,   408,   391,  -224,   411,   411,
    -224,   399,   479,  -224,   409,  -224,  -224,   410,   417,   420,
     422,  -224,   425,  -224,  -224,   428,   -23,  -224,   430,   401,
    -224,  -224,  -224,    40,   528,   -40,   -23,   528,   -23,   -23,
     -40,   -23,  -224,    40,  -224,   -59,  -224,   -59,  -224,  -224,
    -224,  -224,   -59,  -224,  -224,  -224,  -224,  -224
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     3,     1,     0,     0,    73,     0,     0,     0,    73,
      73,    73,     0,     0,     0,    73,     0,     0,     0,    73,
       0,    73,     0,     0,     0,     0,     0,     0,     0,     0,
      73,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    11,
       4,     0,    13,    73,    14,     0,   122,     0,     0,   105,
     106,   107,   116,     0,     0,     0,   153,   110,     0,   130,
       0,   142,    88,     0,   126,   147,   154,     0,     0,     0,
      87,    83,     0,    90,    98,    86,   109,    93,    91,    92,
      96,    89,     0,     0,     0,     0,     0,     0,    38,    39,
       0,     0,     0,     0,     0,    71,    72,     0,     0,     0,
       0,     0,   129,     0,   128,     0,     0,    64,    76,     0,
       0,     0,     0,    73,    40,    73,    73,     0,     0,     0,
       0,   147,     0,     0,     0,     0,   132,     0,   134,   135,
     133,     0,     0,     0,     0,     0,     0,    67,     0,     0,
       0,     0,    10,     6,     0,     0,    12,    74,     0,   108,
       0,     0,     0,     0,     0,   117,     0,   156,   155,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    84,    82,
      80,    79,     0,   159,     0,   157,     0,     0,     0,   147,
       0,    22,    23,    95,     0,    24,    25,     0,     0,     0,
       0,     0,     0,     0,     0,    50,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    43,    44,    41,    42,
       0,     0,     0,     0,    78,     0,     0,     0,     0,    73,
       0,     0,     0,   125,   124,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   110,
      17,   109,     0,     0,     0,     0,     0,     0,    18,     0,
       0,     0,   147,   148,   149,     0,    85,     0,    99,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   158,
      19,     0,   151,   150,   152,     0,     0,    78,     0,     0,
      73,    28,     0,    45,     0,     0,    49,     0,    53,     0,
      54,    73,     0,    65,     0,    66,     0,    29,     0,     0,
       0,     0,    34,     0,   138,     0,     0,    60,     0,     0,
       0,    69,     0,    70,     0,    20,     0,     0,    51,    52,
       7,     8,     9,   123,    16,   112,   121,   113,   114,   115,
       0,   131,   143,   127,     0,     0,    81,     0,     0,     0,
     169,   168,   167,     0,     0,   160,   161,   162,   163,   164,
      97,   100,   144,    94,    27,     0,     0,     0,     0,     0,
       0,    56,     0,     0,     0,     0,     0,     0,    35,    77,
     140,   141,     0,   137,   136,     0,     0,     0,     0,     0,
      15,   118,     0,   145,     0,   119,     0,   102,   165,   166,
     101,     0,    46,    48,     0,    62,    55,     0,     0,     0,
      31,    32,     0,    61,   111,     0,     0,    68,     0,     0,
     103,   120,   104,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    21,     0,   146,    73,    47,    73,    63,    75,
      37,    30,    73,    36,    59,    58,    57,    33
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -224,  -224,  -224,   248,  -224,  -224,    21,    -5,   -26,   -81,
    -107,   223,    36,  -224,   -28,  -224,    15,    78,    83,   282,
    -224,  -224,   148,   -60,   132,  -140,  -224,   497,    17,  -223,
    -224,  -224,   207,   -33,    16,  -116,   260,     1,    57
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     3,    50,   245,    51,   107,   157,   117,   133,
      80,    81,    82,   192,    83,    84,    58,    59,    85,   143,
      60,    61,   394,   335,    86,   235,    87,   113,    88,   137,
     138,   139,   228,    89,    90,   175,   286,   183,   184
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      54,   205,   121,   140,    92,    93,    94,   317,   136,    91,
      98,   191,   195,   315,   105,   224,   108,   102,   102,   208,
     252,    52,    63,     2,    91,   124,    53,    95,   120,   120,
      67,    97,   101,   103,    55,    56,   134,   141,   106,   109,
      91,   114,   114,    55,    56,   239,    57,   126,   142,   180,
      68,    69,   127,   128,   152,   130,    67,   290,   159,   110,
      55,    56,    68,    69,   149,   167,   168,   282,   283,   284,
      64,    65,    57,   287,   156,   145,   155,   111,   181,   158,
     185,   233,    64,    65,   160,    55,    56,   178,   123,    53,
     276,   277,   278,   194,   134,    91,    96,  -139,    99,    68,
      69,   104,   229,    64,    65,   118,   118,   122,   193,   116,
     119,   129,   166,   125,    66,   186,   144,   291,   146,   147,
     218,   219,   150,   151,   240,   148,    66,    67,   -26,    53,
     196,    55,    56,   102,   282,   283,   284,   313,    62,    62,
     217,    75,   169,    76,    62,   170,   344,    66,   225,   100,
     153,   154,    55,    56,   171,    76,    79,   187,    67,   413,
      57,   100,    55,    56,    68,    69,   161,   162,    79,   163,
     259,   260,   261,   188,   263,   264,    76,   168,   197,   249,
     385,   198,   100,    55,    56,   199,   303,    91,    67,    79,
      53,   200,    55,    56,   337,   338,   339,   140,   201,   134,
     202,   294,   136,   295,   203,   172,   216,   173,   174,   204,
     182,   246,   247,   120,   304,   248,   292,   173,   174,    77,
      53,   297,   280,   298,   316,   206,   300,   301,   207,   164,
     165,   141,   318,   319,   409,    70,    71,    91,   310,   346,
      55,    56,    91,   250,   209,    91,   415,   112,   112,   258,
     210,   211,   212,   213,   336,   336,   336,   336,   214,   327,
     403,   272,   273,   274,   275,   276,   277,   278,   141,   349,
     215,   220,   321,   221,   234,   222,   223,   326,   293,   226,
     329,   230,   380,   229,   227,   364,   296,   236,   231,   237,
     118,   232,   251,   238,   302,   411,   371,   305,   306,   241,
     242,   243,   244,   307,   308,   309,   253,    64,    65,   312,
     254,   255,   282,   283,   284,   322,    55,    56,   256,   281,
     285,   328,   288,   325,   257,   387,   350,   351,   352,   234,
     262,   355,   356,   357,   358,   359,   265,   267,   268,   299,
     289,   391,   266,   311,   313,    64,   176,   177,   320,   140,
     314,    66,   324,  -125,   136,    62,    64,    65,  -124,   334,
      70,    71,   271,   272,   273,   274,   275,   276,   277,   278,
      91,   340,   341,   342,   408,   343,   353,   134,    75,   354,
      76,   360,   401,   141,   361,   404,    78,   406,   383,    66,
     362,   135,   365,    79,   378,    64,    65,   363,   366,   367,
      66,   368,   369,   379,   370,   405,   418,   372,   392,   373,
     398,   399,    64,    65,   178,   179,    75,   390,    76,   274,
     275,   276,   277,   278,    78,   436,   374,   131,   439,    76,
     445,    79,   446,   384,   132,   100,   375,   447,   376,    66,
     435,   377,    79,   382,   402,   386,   388,   389,    64,    65,
     444,   393,   234,    64,    65,   397,    66,    67,   410,   414,
     412,    55,    56,    68,    69,    70,    71,   400,    76,    72,
     416,   417,   419,    57,   100,    73,    74,   420,   421,   395,
     395,    79,   422,    75,   423,    76,    64,    65,   424,   434,
      77,    78,    66,   330,   425,   426,   396,    66,    79,   432,
      64,    65,   427,   437,   407,   428,   234,   429,   442,   438,
     430,   440,   441,   431,   443,   433,    64,    65,   234,   189,
     323,    76,   115,   381,   131,   345,    76,   190,     0,     0,
      66,     0,   100,     0,    79,     0,    64,    65,     0,    79,
       0,     0,     0,     0,    66,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   266,     0,     0,     0,    76,
      66,     0,     0,     0,     0,   100,     0,     0,     0,     0,
       0,    75,    79,    76,     0,     0,     0,     0,     0,    78,
      66,     0,     0,     0,     0,     0,    79,     0,     0,    76,
       0,     0,     0,     0,     0,   347,     0,     0,   348,     0,
       0,     0,    79,     0,     0,     0,     0,     0,     0,    76,
       0,     0,     0,     0,     0,   100,     0,     0,     0,     0,
       0,     0,    79,     0,     0,     0,     0,     0,     0,     0,
     279,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,     0,     0,    -5,     4,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,     0,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,     0,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,     0,     0,     0,     0,    43,
       0,     0,     0,     0,     0,     0,   333,    44,    45,    46,
       0,     0,    47,     0,    48,     0,   331,    49,   270,   271,
     272,   273,   274,   275,   276,   277,   278,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   332
};

static const yytype_int16 yycheck[] =
{
       5,   108,    28,    36,     9,    10,    11,   230,    36,     8,
      15,    92,    93,     9,    19,   131,    21,    16,    17,     9,
     160,    84,     7,     0,    23,    30,    85,    12,    27,    28,
      53,    14,    16,    17,    57,    58,    35,    36,    67,    22,
      39,    24,    25,    57,    58,     6,    86,    30,    87,    77,
      59,    60,    31,    32,    84,    34,    53,   197,    57,    23,
      57,    58,    59,    60,    43,    64,    65,    53,    54,    55,
       8,     9,    86,   189,    84,    39,    83,    86,    77,    87,
      79,    53,     8,     9,    85,    57,    58,    77,    85,    85,
      10,    11,    12,    92,    93,    94,    13,    93,    15,    59,
      60,    18,   135,     8,     9,    27,    28,    29,    92,    26,
      27,    33,    85,    30,    52,    85,    38,   198,    40,    41,
     125,   126,    44,    45,    85,    42,    52,    53,    84,    85,
      94,    57,    58,   132,    53,    54,    55,    56,     6,     7,
     123,    79,    87,    81,    12,    87,   262,    52,   132,    87,
      82,    83,    57,    58,    87,    81,    94,    87,    53,   382,
      86,    87,    57,    58,    59,    60,     6,     7,    94,     9,
     169,   170,   171,    87,   173,   174,    81,   176,    85,    53,
     320,    85,    87,    57,    58,    85,   212,   186,    53,    94,
      85,    85,    57,    58,   254,   255,   256,   230,    87,   198,
      11,   200,   230,   202,    85,     6,   123,     8,     9,    85,
      78,   154,   155,   212,   213,   158,   199,     8,     9,    86,
      85,   204,   186,   206,   229,    85,   209,   210,    85,    69,
      70,   230,   231,   232,   374,    61,    62,   236,   223,   267,
      57,    58,   241,   160,    85,   244,   386,    24,    25,   166,
      85,    85,    85,    85,   253,   254,   255,   256,    85,   242,
     367,     6,     7,     8,     9,    10,    11,    12,   267,   268,
      85,    85,   236,    85,   142,    85,    85,   241,   200,    85,
     244,    85,   315,   316,    87,   290,   203,    85,    90,    85,
     212,    90,   160,    85,   211,   376,   301,   214,   215,    85,
      85,    85,    85,   220,   221,   222,     6,     8,     9,   226,
       7,     7,    53,    54,    55,   237,    57,    58,     7,   187,
     188,   243,   190,   240,     6,   324,   269,   270,   271,   197,
       7,   274,   275,   276,   277,   278,    87,    86,    88,   207,
      87,   340,    77,    85,    56,     8,     9,    10,    85,   382,
      93,    52,     6,    85,   382,   223,     8,     9,    85,    85,
      61,    62,     5,     6,     7,     8,     9,    10,    11,    12,
     369,     6,    88,    88,   373,    88,     6,   376,    79,     7,
      81,    88,   365,   382,    88,   368,    87,   370,    91,    52,
      88,    92,    85,    94,   311,     8,     9,    88,    85,    85,
      52,    85,    85,    88,    85,   369,   389,    85,    87,    85,
     353,   354,     8,     9,    77,    78,    79,   334,    81,     8,
       9,    10,    11,    12,    87,   424,    85,    79,   427,    81,
     435,    94,   437,    91,    86,    87,    85,   442,    85,    52,
     423,    85,    94,    85,   366,    85,    85,    85,     8,     9,
     433,    88,   320,     8,     9,    89,    52,    53,   375,    88,
     377,    57,    58,    59,    60,    61,    62,    89,    81,    65,
      85,   388,    54,    86,    87,    71,    72,    88,    70,   347,
     348,    94,    91,    79,    85,    81,     8,     9,     9,    88,
      86,    87,    52,   245,    85,    85,   348,    52,    94,   416,
       8,     9,    85,   425,   372,    85,   374,    85,   430,   426,
      85,   428,   429,    85,   431,    85,     8,     9,   386,    79,
     238,    81,    25,   316,    79,   265,    81,    87,    -1,    -1,
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
      -1,    -1,    79,    -1,    81,    -1,    84,    84,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    96,     0,    97,     1,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    66,    74,    75,    76,    79,    81,    84,
      98,   100,    84,    85,   102,    57,    58,    86,   111,   112,
     115,   116,   119,   111,     8,     9,    52,    53,    59,    60,
      61,    62,    65,    71,    72,    79,    81,    86,    87,    94,
     105,   106,   107,   109,   110,   113,   119,   121,   123,   128,
     129,   132,   102,   102,   102,   111,   113,   123,   102,   113,
      87,   129,   132,   129,   113,   102,    67,   101,   102,   123,
     107,    86,   106,   122,   123,   122,   113,   103,   112,   113,
     132,   103,   112,    85,   102,   113,   123,   101,   101,   112,
     101,    79,    86,   104,   132,    92,   109,   124,   125,   126,
     128,   132,    87,   114,   112,   107,   112,   112,   113,   101,
     112,   112,    84,    82,    83,    83,    84,   102,    87,   132,
      85,     6,     7,     9,    69,    70,    85,   132,   132,    87,
      87,    87,     6,     8,     9,   130,     9,    10,    77,    78,
     109,   132,   119,   132,   133,   132,    85,    87,    87,    79,
      87,   104,   108,   129,   132,   104,   107,    85,    85,    85,
      85,    87,    11,    85,    85,   105,    85,    85,     9,    85,
      85,    85,    85,    85,    85,    85,   113,   123,   102,   102,
      85,    85,    85,    85,   130,   129,    85,    87,   127,   128,
      85,    90,    90,    53,   119,   120,    85,    85,    85,     6,
      85,    85,    85,    85,    85,    99,   133,   133,   133,    53,
     113,   119,   120,     6,     7,     7,     7,     6,   113,   132,
     132,   132,     7,   132,   132,    87,    77,    86,    88,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    88,
     107,   119,    53,    54,    55,   119,   131,   130,   119,    87,
     120,   104,   123,   112,   132,   132,   113,   123,   123,   119,
     123,   123,   113,   103,   132,   113,   113,   113,   113,   113,
     111,    85,   113,    56,    93,     9,   102,   124,   132,   132,
      85,   107,   112,   114,     6,   113,   107,   123,   112,   107,
      98,    84,    84,    88,    85,   118,   132,   118,   118,   118,
       6,    88,    88,    88,   130,   131,   109,    87,    90,   132,
     133,   133,   133,     6,     7,   133,   133,   133,   133,   133,
      88,    88,    88,    88,   102,    85,    85,    85,    85,    85,
      85,   102,    85,    85,    85,    85,    85,    85,   113,    88,
     128,   127,    85,    91,    91,   120,    85,   132,    85,    85,
     113,   132,    87,    88,   117,   119,   117,    89,   133,   133,
      89,   123,   112,   105,   123,   107,   123,   119,   132,   120,
     113,   104,   113,   124,    88,   120,    85,   113,   123,    54,
      88,    70,    91,    85,     9,    85,    85,    85,    85,    85,
      85,    85,   113,    85,    88,   123,   132,   112,   113,   132,
     113,   113,   112,   113,   123,   102,   102,   102
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    95,    96,    97,    96,    98,    99,    98,    98,    98,
      98,    98,    98,    98,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   101,   102,   102,   103,   103,   104,   104,   105,
     105,   105,   105,   105,   106,   106,   107,   107,   107,   107,
     107,   107,   107,   107,   108,   108,   109,   109,   109,   110,
     110,   110,   110,   110,   110,   111,   111,   111,   112,   113,
     113,   114,   115,   115,   115,   115,   116,   116,   116,   117,
     117,   118,   119,   119,   120,   120,   121,   121,   122,   122,
     123,   123,   124,   124,   124,   124,   125,   125,   126,   127,
     127,   127,   128,   128,   129,   129,   129,   130,   130,   130,
     131,   131,   131,   132,   132,   132,   132,   132,   132,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     3,     0,     0,     4,     4,     4,
       2,     1,     2,     2,     2,     6,     5,     4,     4,     4,
       4,     7,     3,     3,     3,     3,     1,     5,     4,     4,
       8,     6,     6,     9,     4,     5,     8,     8,     2,     2,
       2,     3,     3,     3,     3,     4,     6,     8,     6,     4,
       3,     4,     4,     4,     4,     6,     5,     9,     9,     8,
       4,     6,     6,     8,     2,     4,     4,     2,     6,     4,
       4,     2,     1,     0,     2,     7,     1,     4,     2,     2,
       2,     4,     2,     1,     2,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     4,     1,     3,
       4,     5,     5,     6,     6,     1,     1,     1,     2,     1,
       1,     5,     4,     4,     4,     4,     1,     2,     5,     1,
       2,     1,     1,     4,     1,     1,     1,     4,     1,     1,
       1,     4,     1,     1,     1,     1,     4,     4,     3,     1,
       3,     3,     1,     4,     4,     5,     7,     0,     2,     2,
       1,     1,     1,     1,     1,     2,     2,     2,     3,     1,
       3,     3,     3,     3,     3,     4,     4,     3,     3,     3
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
        case 3:
#line 43 "a.y" /* yacc.c:1646  */
    {
		stmtline = lineno;
	}
#line 1717 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 50 "a.y" /* yacc.c:1646  */
    {
		(yyvsp[-1].sym) = labellookup((yyvsp[-1].sym));
		if((yyvsp[-1].sym)->type == LLAB && (yyvsp[-1].sym)->value != pc)
			yyerror("redeclaration of %s", (yyvsp[-1].sym)->labelname);
		(yyvsp[-1].sym)->type = LLAB;
		(yyvsp[-1].sym)->value = pc;
	}
#line 1729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 59 "a.y" /* yacc.c:1646  */
    {
		(yyvsp[-3].sym)->type = LVAR;
		(yyvsp[-3].sym)->value = (yyvsp[-1].lval);
	}
#line 1738 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 64 "a.y" /* yacc.c:1646  */
    {
		if((yyvsp[-3].sym)->value != (yyvsp[-1].lval))
			yyerror("redeclaration of %s", (yyvsp[-3].sym)->name);
		(yyvsp[-3].sym)->value = (yyvsp[-1].lval);
	}
#line 1748 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 70 "a.y" /* yacc.c:1646  */
    {
		nosched = (yyvsp[-1].lval);
	}
#line 1756 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 82 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &nullgen, NREG, &nullgen);
	}
#line 1764 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 89 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].lval), &(yyvsp[0].addr));
	}
#line 1772 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 93 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-4].lval), &(yyvsp[-3].addr), (yyvsp[-1].lval), &nullgen);
	}
#line 1780 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 97 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1788 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 104 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1796 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 111 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1804 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 118 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1812 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 122 "a.y" /* yacc.c:1646  */
    {
		Addr a;
		a = nullgen;
		a.type = D_CONST;
		a.offset = (yyvsp[-2].lval);
		outgcode((yyvsp[-6].lval), &(yyvsp[-5].addr), NREG, &a, &(yyvsp[0].addr));
	}
#line 1824 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 133 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1832 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 137 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1840 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 144 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1848 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 151 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1856 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 155 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[0].lval), &nullgen, NREG, &nullgen);
	}
#line 1864 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 162 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-4].lval), &(yyvsp[-3].addr), (yyvsp[-1].lval), &nullgen);
	}
#line 1872 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 169 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1880 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 176 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1888 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 183 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-2].addr).reg, &(yyvsp[-4].addr), &(yyvsp[0].addr));
	}
#line 1896 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 187 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].addr).reg, &(yyvsp[0].addr));
	}
#line 1904 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 194 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].addr).reg, &(yyvsp[0].addr));
	}
#line 1912 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 201 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-8].lval), &(yyvsp[-7].addr), (yyvsp[-3].addr).reg, &(yyvsp[-5].addr), &(yyvsp[-1].addr));
	}
#line 1920 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 208 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1928 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 212 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-4].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1936 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 219 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-2].lval), &(yyvsp[-4].addr), &(yyvsp[0].addr));
	}
#line 1944 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 226 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-2].lval), &(yyvsp[-4].addr), &(yyvsp[0].addr));
	}
#line 1952 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 233 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &nullgen, NREG, &nullgen);
	}
#line 1960 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 237 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1968 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 244 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &nullgen, NREG, &nullgen);
	}
#line 1976 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 248 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &(yyvsp[-1].addr), NREG, &nullgen);
	}
#line 1984 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 252 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &(yyvsp[-1].addr), NREG, &nullgen);
	}
#line 1992 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 256 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 2000 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 260 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 2008 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 267 "a.y" /* yacc.c:1646  */
    {
		settext((yyvsp[-2].addr).sym);
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2017 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 272 "a.y" /* yacc.c:1646  */
    {
		settext((yyvsp[-4].addr).sym);
		(yyvsp[0].addr).offset &= 0xffffffffull;
		(yyvsp[0].addr).offset |= (vlong)ArgsSizeUnknown << 32;
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].lval), &(yyvsp[0].addr));
	}
#line 2028 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 279 "a.y" /* yacc.c:1646  */
    {
		settext((yyvsp[-6].addr).sym);
		(yyvsp[-2].addr).offset &= 0xffffffffull;
		(yyvsp[-2].addr).offset |= ((yyvsp[0].lval) & 0xffffffffull) << 32;
		outcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-4].lval), &(yyvsp[-2].addr));
	}
#line 2039 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 289 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].lval), &(yyvsp[0].addr));
	}
#line 2047 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 296 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2055 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 303 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 2063 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 310 "a.y" /* yacc.c:1646  */
    {
		if((yyvsp[-2].addr).type != D_CONST || (yyvsp[0].addr).type != D_CONST)
			yyerror("arguments to PCDATA must be integer constants");
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2073 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 319 "a.y" /* yacc.c:1646  */
    {
		if((yyvsp[-2].addr).type != D_CONST)
			yyerror("index for FUNCDATA must be integer constant");
		if((yyvsp[0].addr).type != D_EXTERN && (yyvsp[0].addr).type != D_STATIC && (yyvsp[0].addr).type != D_OREG)
			yyerror("value for FUNCDATA must be symbol reference");
 		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2085 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 330 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2093 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 337 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2101 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 341 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].addr).reg, &(yyvsp[0].addr));
	}
#line 2109 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 348 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-4].lval), &(yyvsp[-3].addr), (yyvsp[-1].addr).reg, &nullgen);
	}
#line 2117 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 355 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-8].lval), &(yyvsp[-7].addr), (yyvsp[-3].addr).reg, &(yyvsp[-5].addr), &(yyvsp[-1].addr));
	}
#line 2125 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 362 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-8].lval), &(yyvsp[-7].addr), (yyvsp[-5].addr).reg, &(yyvsp[-3].addr), &(yyvsp[-1].addr));
	}
#line 2133 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 369 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-2].addr).reg, &(yyvsp[-4].addr), &(yyvsp[0].addr));
	}
#line 2141 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 376 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2149 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 380 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].addr).reg, &(yyvsp[0].addr));
	}
#line 2157 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 387 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].lval), &(yyvsp[0].addr));
	}
#line 2165 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 394 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-2].lval), &(yyvsp[-4].addr), &(yyvsp[0].addr));
	}
#line 2173 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 401 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &(yyvsp[0].addr), NREG, &nullgen);
	}
#line 2181 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 405 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[0].addr), (yyvsp[-2].addr).reg, &nullgen);
	}
#line 2189 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 409 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2197 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 416 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &(yyvsp[0].addr), NREG, &nullgen);
	}
#line 2205 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 423 "a.y" /* yacc.c:1646  */
    {
		outtcode((yyvsp[-5].lval), &(yyvsp[-4].addr), &(yyvsp[-2].addr), &(yyvsp[0].addr));
	}
#line 2213 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 431 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2221 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 439 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2229 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 447 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &nullgen, NREG, &nullgen);
	}
#line 2237 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 453 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_COND;
		(yyval.addr).reg = (yyvsp[0].lval);
	}
#line 2247 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 464 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_CONST;
		(yyval.addr).offset = SYSARG4((yyvsp[-6].lval), (yyvsp[-4].lval), (yyvsp[-2].lval), (yyvsp[0].lval));
	}
#line 2257 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 473 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_BRANCH;
		(yyval.addr).offset = (yyvsp[-3].lval) + pc;
	}
#line 2267 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 479 "a.y" /* yacc.c:1646  */
    {
		(yyvsp[-1].sym) = labellookup((yyvsp[-1].sym));
		(yyval.addr) = nullgen;
		if(pass == 2 && (yyvsp[-1].sym)->type != LLAB)
			yyerror("undefined label: %s", (yyvsp[-1].sym)->labelname);
		(yyval.addr).type = D_BRANCH;
		(yyval.addr).offset = (yyvsp[-1].sym)->value + (yyvsp[0].lval);
	}
#line 2280 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 489 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_CONST;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2290 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 495 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = (yyvsp[0].addr);
		(yyval.addr).type = D_CONST;
	}
#line 2299 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 500 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = (yyvsp[0].addr);
		(yyval.addr).type = D_OCONST;
	}
#line 2308 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 505 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SCONST;
		memmove((yyval.addr).u.sval, (yyvsp[0].sval), sizeof((yyval.addr).u.sval));
	}
#line 2318 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 514 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FCONST;
		(yyval.addr).u.dval = (yyvsp[0].dval);
	}
#line 2328 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 520 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FCONST;
		(yyval.addr).u.dval = -(yyvsp[0].dval);
	}
#line 2338 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 530 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SPR;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2348 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 536 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2358 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 548 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
		(yyval.addr).offset = 0;
	}
#line 2369 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 555 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = (yyvsp[0].addr);
		if((yyvsp[0].addr).name != D_EXTERN && (yyvsp[0].addr).name != D_STATIC) {
		}
	}
#line 2379 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 564 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = (yyvsp[-3].addr);
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
	}
#line 2389 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 573 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
		(yyval.addr).offset = 0;
	}
#line 2400 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 580 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
		(yyval.addr).offset = (yyvsp[-3].lval);
	}
#line 2411 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 587 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_XPRE;
		(yyval.addr).reg = (yyvsp[-2].lval);
		(yyval.addr).offset = (yyvsp[-4].lval);
	}
#line 2422 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 594 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_XPOST;
		(yyval.addr).reg = (yyvsp[-3].lval);
		(yyval.addr).offset = (yyvsp[-1].lval);
	}
#line 2433 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 601 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_ROFF;
		(yyval.addr).reg = (yyvsp[-4].lval);
		(yyval.addr).scale = (yyvsp[-1].lval) & 0x1f;
		(yyval.addr).offset = (yyvsp[-1].lval);
	}
#line 2445 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 609 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_ROFF;
		(yyval.addr).reg = (yyvsp[-4].lval);
		(yyval.addr).scale = (yyvsp[-1].lval) & 0x1f;
		(yyval.addr).offset = (yyvsp[-1].lval) | (1<<16);
	}
#line 2457 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 623 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_CONST;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2467 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 631 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_REG;
		(yyval.addr).reg = (yyvsp[0].lval);
	}
#line 2477 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 637 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SP;
		(yyval.addr).reg = REGSP;
	}
#line 2487 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 645 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_PAIR;
		(yyval.addr).reg = (yyvsp[-3].lval);
		(yyval.addr).offset = (yyvsp[-1].lval);
	}
#line 2498 "y.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 654 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = ((yyvsp[-3].lval) << 16) | ((yyvsp[0].lval) << 10) | (0 << 22);
	}
#line 2508 "y.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 660 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = (((yyvsp[-3].lval)&0x1F) << 16) | ((yyvsp[0].lval) << 10) | (1 << 22);
	}
#line 2518 "y.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 666 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = ((yyvsp[-3].lval) << 16) | ((yyvsp[0].lval) << 10) | (2 << 22);
	}
#line 2528 "y.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 672 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = ((yyvsp[-3].lval) << 16) | ((yyvsp[0].lval) << 10) | (3 << 22);
	}
#line 2538 "y.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 680 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_REG;
		(yyval.addr).reg = (yyvsp[0].lval);
	}
#line 2548 "y.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 686 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_EXTREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
		(yyval.addr).offset = ((yyvsp[-1].lval) << 16) | ((yyvsp[0].lval) << 13);
	}
#line 2559 "y.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 693 "a.y" /* yacc.c:1646  */
    {
		if((yyvsp[0].lval) < 0 || (yyvsp[0].lval) > 4)
			yyerror("shift value out of range");
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_EXTREG;
		(yyval.addr).reg = (yyvsp[-4].lval);
		(yyval.addr).offset = ((yyvsp[-4].lval) << 16) | ((yyvsp[-3].lval) << 13) | ((yyvsp[0].lval) << 10);
	}
#line 2572 "y.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 704 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (3 << 8) | (yyvsp[0].lval);
	}
#line 2580 "y.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 708 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = ((yyvsp[0].lval) << 8) | (yyvsp[-1].lval);
	}
#line 2588 "y.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 714 "a.y" /* yacc.c:1646  */
    {
		if((yyval.lval) < 0 || (yyval.lval) >= 64)
			yyerror("shift value out of range");
		(yyval.lval) = (yyvsp[0].lval)&0x3F;
	}
#line 2598 "y.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 723 "a.y" /* yacc.c:1646  */
    {
		if((yyvsp[-1].lval) < 0 || (yyvsp[-1].lval) >= NREG)
			print("register value out of range\n");
		(yyval.lval) = (yyvsp[-1].lval);
	}
#line 2608 "y.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 732 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = REGSP;
	}
#line 2616 "y.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 738 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SPR;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2626 "y.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 744 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = (yyvsp[-3].lval);
		(yyval.addr).offset = (yyvsp[-1].lval);
	}
#line 2636 "y.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 756 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FREG;
		(yyval.addr).reg = (yyvsp[0].lval);
	}
#line 2646 "y.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 762 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
	}
#line 2656 "y.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 773 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_VSET;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2666 "y.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 781 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr).type = D_VLANE;
		(yyval.addr).offset = (yyvsp[-1].lval);
	}
#line 2675 "y.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 786 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr).type = D_VLANE;
		(yyval.addr).offset = (yyvsp[-1].lval);
	}
#line 2684 "y.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 793 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-1].lval);
	}
#line 2692 "y.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 799 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = 1 << (yyvsp[0].addr).reg;
	}
#line 2700 "y.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 803 "a.y" /* yacc.c:1646  */
    {
		int i;
		(yyval.lval)=0;
		for(i=(yyvsp[-2].addr).reg; i<=(yyvsp[0].addr).reg; i++)
			(yyval.lval) |= 1<<i;
		for(i=(yyvsp[0].addr).reg; i<=(yyvsp[-2].addr).reg; i++)
			(yyval.lval) |= 1<<i;
	}
#line 2713 "y.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 812 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (1<<(yyvsp[-2].addr).reg) | (yyvsp[0].lval);
	}
#line 2721 "y.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 818 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_VREG;
		(yyval.addr).reg = (yyvsp[0].lval);
		/* TO DO: slice */
	}
#line 2732 "y.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 825 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_VREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
	}
#line 2742 "y.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 833 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).name = (yyvsp[-1].lval);
		(yyval.addr).sym = nil;
		(yyval.addr).offset = (yyvsp[-3].lval);
	}
#line 2754 "y.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 841 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).name = (yyvsp[-1].lval);
		(yyval.addr).sym = linklookup(ctxt, (yyvsp[-4].sym)->name, 0);
		(yyval.addr).offset = (yyvsp[-3].lval);
	}
#line 2766 "y.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 849 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).name = D_STATIC;
		(yyval.addr).sym = linklookup(ctxt, (yyvsp[-6].sym)->name, 1);
		(yyval.addr).offset = (yyvsp[-3].lval);
	}
#line 2778 "y.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 858 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = 0;
	}
#line 2786 "y.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 862 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[0].lval);
	}
#line 2794 "y.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 866 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = -(yyvsp[0].lval);
	}
#line 2802 "y.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 878 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[0].sym)->value;
	}
#line 2810 "y.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 882 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = -(yyvsp[0].lval);
	}
#line 2818 "y.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 886 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[0].lval);
	}
#line 2826 "y.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 890 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = ~(yyvsp[0].lval);
	}
#line 2834 "y.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 894 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-1].lval);
	}
#line 2842 "y.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 901 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) + (yyvsp[0].lval);
	}
#line 2850 "y.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 905 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) - (yyvsp[0].lval);
	}
#line 2858 "y.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 909 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) * (yyvsp[0].lval);
	}
#line 2866 "y.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 913 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) / (yyvsp[0].lval);
	}
#line 2874 "y.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 917 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) % (yyvsp[0].lval);
	}
#line 2882 "y.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 921 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-3].lval) << (yyvsp[0].lval);
	}
#line 2890 "y.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 925 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-3].lval) >> (yyvsp[0].lval);
	}
#line 2898 "y.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 929 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) & (yyvsp[0].lval);
	}
#line 2906 "y.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 933 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) ^ (yyvsp[0].lval);
	}
#line 2914 "y.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 937 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) | (yyvsp[0].lval);
	}
#line 2922 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2926 "y.tab.c" /* yacc.c:1646  */
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
