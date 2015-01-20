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
#define YYLAST   741

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  92
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  162
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  424

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
       0,    40,    40,    41,    43,    45,    44,    53,    58,    64,
      65,    66,    72,    79,    83,    87,    94,   101,   108,   112,
     123,   127,   134,   141,   145,   152,   159,   166,   173,   177,
     184,   191,   198,   202,   209,   216,   223,   227,   234,   238,
     242,   246,   250,   257,   262,   269,   279,   286,   293,   300,
     307,   311,   318,   325,   332,   339,   346,   350,   357,   364,
     371,   375,   379,   386,   393,   400,   406,   413,   414,   417,
     423,   426,   432,   442,   448,   453,   458,   464,   467,   473,
     481,   482,   483,   489,   495,   496,   497,   498,   501,   508,
     516,   517,   523,   526,   533,   540,   547,   554,   562,   572,
     573,   574,   576,   584,   590,   598,   604,   610,   616,   624,
     630,   637,   648,   652,   658,   666,   667,   675,   676,   682,
     688,   696,   697,   700,   706,   714,   715,   716,   717,   725,
     730,   737,   743,   747,   756,   762,   769,   777,   785,   793,
     803,   806,   810,   816,   817,   818,   821,   822,   826,   830,
     834,   838,   844,   845,   849,   853,   857,   861,   865,   869,
     873,   877,   881
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
  "']'", "'{'", "'}'", "'~'", "$accept", "prog", "line", "$@1", "inst",
  "cond", "comma", "sysarg", "rel", "ximm", "fcon", "addr", "nireg",
  "oreg", "ioreg", "imsr", "imm", "reg", "shift", "extreg", "indexreg",
  "scon", "sreg", "spreg", "spr", "frcon", "freg", "vaddr", "vlane",
  "vset", "vreglist", "vreg", "name", "offset", "pointer", "con", "expr", YY_NULLPTR
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

#define YYPACT_NINF -199

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-199)))

#define YYTABLE_NINF -133

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -199,   591,  -199,   -46,   -32,     9,     9,   378,   -32,   -32,
      75,     9,    78,     3,    56,   283,   283,    78,   -32,    -8,
     -32,     3,   378,    38,    38,    78,   288,   368,   -13,    87,
      -8,    -8,   -13,    -8,   134,   414,   -13,   -13,   -13,    78,
      -8,    50,    -6,  -199,  -199,    -9,  -199,   -32,  -199,    19,
    -199,   416,     5,  -199,  -199,  -199,    42,    24,   416,   416,
    -199,  -199,    26,  -199,    43,  -199,  -199,    49,  -199,   111,
    -199,    48,   253,   416,  -199,  -199,    59,  -199,  -199,  -199,
    -199,  -199,  -199,  -199,    91,   103,   433,   449,   378,   107,
     141,   164,  -199,  -199,   416,   167,   179,    90,   173,  -199,
    -199,   191,   108,   192,   194,    25,  -199,   195,  -199,   208,
     212,  -199,  -199,   216,   219,   221,   222,   226,  -199,   -32,
     -32,   225,   227,   239,   242,   159,   283,   245,   187,   109,
    -199,   247,  -199,   185,   243,   103,   251,    20,  -199,   252,
     256,  -199,   416,   416,  -199,  -199,   416,  -199,   190,   341,
     343,   344,   345,   342,    78,  -199,  -199,   416,   416,   416,
     347,   416,   416,   271,   469,   274,  -199,  -199,  -199,   103,
     279,  -199,   568,  -199,   378,   171,   177,   111,   253,  -199,
    -199,  -199,   284,  -199,  -199,   199,   449,     3,   368,   153,
     416,    78,     3,  -199,     3,   171,   296,     3,     3,    78,
     368,   416,    78,    78,  -199,  -199,  -199,  -199,    78,    78,
      78,     9,  -199,   298,    78,   325,   294,     4,   414,   416,
     416,   -13,   379,    78,   378,     3,   660,    73,   590,   578,
     306,  -199,   308,   310,   416,   416,   416,   416,   383,  -199,
     309,   312,   313,   159,  -199,  -199,   153,  -199,   479,   291,
     416,   416,   416,   387,   388,   416,   416,   416,   416,   416,
    -199,  -199,   314,  -199,  -199,  -199,   315,   318,   271,   319,
      95,  -199,  -199,   -32,  -199,   324,  -199,   326,   328,  -199,
     329,  -199,   330,   331,   -32,   333,  -199,   335,  -199,   336,
    -199,   337,   339,   346,    78,  -199,   348,  -199,   109,   109,
     363,   359,   360,   371,   416,  -199,   373,   381,  -199,  -199,
    -199,  -199,    78,  -199,  -199,  -199,  -199,  -199,   416,  -199,
    -199,  -199,   376,   380,  -199,   253,   171,   384,   639,   307,
     706,   416,   416,   248,   248,  -199,  -199,  -199,  -199,   393,
    -199,  -199,  -199,     3,   -13,   108,     3,   378,     3,  -199,
     171,   416,   199,    78,   449,    78,  -199,  -199,  -199,  -199,
     414,  -199,  -199,   199,   382,    78,     3,  -199,  -199,   375,
    -199,   389,   357,   392,  -199,   189,   189,  -199,   385,   473,
    -199,   407,  -199,  -199,   409,   411,   413,   420,  -199,   422,
    -199,   424,    78,  -199,   426,   427,  -199,  -199,  -199,     3,
     416,   -13,    78,   416,    78,    78,   -13,    78,  -199,     3,
    -199,   -32,  -199,   -32,  -199,  -199,  -199,  -199,   -32,  -199,
    -199,  -199,  -199,  -199
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,    67,     0,     0,     0,    67,    67,
      67,     0,     0,     0,    67,     0,     0,     0,    67,     0,
      67,     0,     0,     0,     0,     0,     0,     0,     0,    67,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     9,     3,     0,    11,    67,    12,     0,
     115,     0,     0,    99,   100,   101,   109,     0,     0,     0,
     146,   104,     0,   123,     0,   135,    82,     0,   119,   140,
     147,     0,     0,     0,    81,    77,     0,    84,    92,    80,
     103,    87,    85,    86,    90,    83,     0,     0,     0,     0,
       0,     0,    36,    37,     0,     0,     0,     0,     0,    65,
      66,     0,     0,     0,     0,     0,   122,     0,   121,     0,
       0,    60,    70,     0,     0,     0,     0,    67,    38,    67,
      67,     0,     0,     0,     0,   140,     0,     0,     0,     0,
     125,     0,   127,   128,   126,     0,     0,     0,    63,     0,
       0,     5,     0,     0,    10,    68,     0,   102,     0,     0,
       0,     0,     0,   110,     0,   149,   148,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    78,    76,    74,    73,
       0,   152,     0,   150,     0,     0,     0,   140,     0,    20,
      21,    89,     0,    22,    23,     0,     0,     0,     0,     0,
       0,     0,     0,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    41,    42,    39,    40,     0,     0,
       0,     0,    72,     0,     0,     0,     0,    67,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     104,    15,   103,     0,     0,     0,     0,     0,     0,    16,
       0,     0,     0,   140,   141,   142,     0,    79,     0,    93,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     151,    17,     0,   144,   143,   145,     0,     0,    72,     0,
       0,   118,   117,    67,    26,     0,    43,     0,     0,    47,
       0,    49,     0,    50,    67,     0,    61,     0,    62,     0,
      27,     0,     0,     0,     0,    32,     0,   131,     0,     0,
      56,     0,     0,     0,     0,    18,     0,     0,     6,     7,
       8,   116,    14,   105,   114,   106,   107,   108,     0,   124,
     136,   120,     0,     0,    75,     0,     0,     0,   162,   161,
     160,     0,     0,   153,   154,   155,   156,   157,    91,    94,
     137,    88,    25,     0,     0,     0,     0,     0,     0,    52,
       0,     0,     0,     0,     0,     0,    33,    71,   133,   134,
       0,   130,   129,     0,     0,     0,     0,    13,   111,     0,
     138,     0,   112,     0,    96,   158,   159,    95,     0,    44,
      46,     0,    58,    51,     0,     0,     0,    29,    30,     0,
      57,     0,     0,    64,     0,     0,    97,   113,    98,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    19,     0,
     139,    67,    45,    67,    59,    69,    35,    28,    67,    34,
      55,    54,    53,    31
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -199,  -199,   270,  -199,  -199,    12,    -4,   -15,   -79,  -100,
     217,   -19,  -199,   -24,  -199,    33,    -5,    79,  -199,  -199,
     188,    31,   147,  -170,  -199,   489,    17,  -198,  -199,  -199,
     220,   -34,    39,  -106,   269,     2,   -78
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    44,   226,    45,   101,   145,   111,   127,    74,
      75,    76,   180,    77,    78,    52,    53,    79,    54,    55,
     371,   313,    80,   233,    81,   107,    82,   131,   132,   133,
     216,    83,    84,   163,   267,   171,   172
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      48,   134,   193,   104,    86,    87,    88,   179,   183,    85,
      92,   130,   115,   298,    99,   273,   102,    96,    96,   212,
     300,   112,   112,   116,    85,   118,   222,   123,   114,   114,
      91,   136,   137,   138,   196,    46,   128,   135,   103,    57,
     108,   108,   121,   122,    89,   124,   120,   168,   149,   150,
      47,   151,   140,   147,    95,    97,    58,   164,   165,   100,
     155,   156,    62,    63,   227,   228,    49,    50,   229,   184,
      51,   268,   144,   169,   143,   173,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,    47,   148,   182,   128,
      85,    90,    51,    93,  -132,   217,    98,    62,    63,   166,
      60,   190,   223,   146,   110,   113,   154,   274,   119,    61,
     157,   152,   153,    49,    50,   206,   207,   160,   139,   161,
     162,   105,   166,   167,    69,   181,    70,   158,    96,   141,
     142,    61,    72,   159,   205,    49,    50,   322,    47,    73,
      61,   174,    58,    59,    49,    50,    62,    63,   263,   264,
     265,   296,    56,    56,   309,   261,   -24,    47,    56,   240,
     241,   242,   390,   244,   245,   213,   156,   161,   162,   117,
      64,    65,   328,   329,   330,   175,    85,   333,   334,   335,
     336,   337,   386,   276,   134,   286,    60,   176,   128,   185,
     277,    71,   278,   391,   130,   112,   204,   255,   256,   257,
     258,   259,   114,   287,   275,   306,   263,   264,   265,   280,
     125,   281,    70,   299,   283,   284,   303,   126,    94,   170,
     135,   301,   302,   186,   324,    73,    85,   231,    49,    50,
     263,   264,   265,   239,    49,    50,   314,   314,   314,   314,
     106,   106,   307,   230,   293,   380,   187,    49,    50,   188,
     135,   327,   271,   375,   376,   191,    49,    50,   257,   258,
     259,    58,    59,   189,   358,   217,   315,   316,   317,   342,
     279,   215,   219,   192,   194,   388,   195,   197,   285,    61,
     349,   288,   289,    49,    50,    62,    63,   290,   291,   292,
     198,    58,    59,   295,   199,   232,    58,    59,   200,    58,
      59,   201,   305,   202,   203,    60,   364,   208,    47,   209,
      49,    50,   252,   253,   254,   255,   256,   257,   258,   259,
     368,   210,   262,   266,   211,   269,   134,   214,   382,   218,
     220,    70,   272,   221,   224,    60,   130,    94,   225,   379,
      60,    61,   282,    60,    73,    49,    50,   234,   238,    85,
     235,   236,   237,   385,   243,   246,   128,   248,    56,    69,
     378,    70,   135,   381,   249,   383,    70,    94,   270,    70,
     247,    51,    94,   356,    73,   325,    58,    59,   326,    73,
     294,   296,    73,   394,   297,   304,    58,    59,  -118,   318,
    -117,   367,   312,   331,   319,   332,   413,   320,   321,   338,
     339,   418,   412,   340,   341,   415,   343,   421,   344,   422,
     345,   346,   347,   348,   423,   350,   411,   351,   352,   353,
      60,   354,    58,    59,    58,    59,   420,   397,   355,   395,
      60,    61,   387,   357,   389,    49,    50,    62,    63,    64,
      65,    58,    59,    66,   393,   360,    70,   361,   362,    67,
      68,    51,    94,   363,    69,   365,    70,    58,    59,    73,
     369,    71,    72,   366,   392,   370,    60,   399,    60,    73,
     374,   408,   372,   372,   396,    64,    65,    58,    59,   377,
     398,   414,   400,   416,   417,    60,   419,    58,    59,   401,
      69,   402,    70,   403,    70,   404,   308,   384,    72,   272,
      94,    60,   405,   129,   406,    73,   407,    73,   409,   177,
     272,    70,   410,   109,   373,   323,     0,   178,     0,   359,
       0,    60,     0,     0,    73,   125,     0,    70,     0,     0,
       0,    60,     0,    94,     0,     0,     0,     0,     0,     0,
      73,     0,     0,   247,     0,     0,     0,    70,     0,     0,
       0,     0,     0,    94,     0,    69,     0,    70,     0,     0,
      73,     0,     0,    72,     0,     0,     0,     0,     0,     0,
      73,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,     2,     3,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,     0,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,     0,    36,     0,
      37,    38,    39,   251,   252,   253,   254,   255,   256,   257,
     258,   259,     0,   260,     0,     0,     0,    40,     0,     0,
      -4,     3,     0,   311,     0,     0,     0,    41,     0,    42,
       0,   310,    43,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,     0,    36,     0,    37,
      38,    39,   253,   254,   255,   256,   257,   258,   259,     0,
       0,     0,     0,     0,     0,     0,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    41,     0,    42,     0,
       0,    43
};

static const yytype_int16 yycheck[] =
{
       4,    35,   102,    22,     8,     9,    10,    86,    87,     7,
      14,    35,    27,     9,    18,   185,    20,    15,    16,   125,
     218,    26,    27,    28,    22,    29,     6,    32,    26,    27,
      13,    36,    37,    38,     9,    81,    34,    35,    21,     6,
      23,    24,    30,    31,    11,    33,    29,    71,     6,     7,
      82,     9,    40,    51,    15,    16,     8,     9,    10,    67,
      58,    59,    59,    60,   142,   143,    57,    58,   146,    88,
      83,   177,    81,    71,    80,    73,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    82,    82,    86,    87,
      88,    12,    83,    14,    90,   129,    17,    59,    60,    74,
      52,    11,    82,    84,    25,    26,    82,   186,    29,    53,
      84,    69,    70,    57,    58,   119,   120,     6,    39,     8,
       9,    83,    74,    75,    76,    86,    78,    84,   126,    79,
      80,    53,    84,    84,   117,    57,    58,   243,    82,    91,
      53,    82,     8,     9,    57,    58,    59,    60,    53,    54,
      55,    56,     5,     6,    81,   174,    81,    82,    11,   157,
     158,   159,   360,   161,   162,   126,   164,     8,     9,    82,
      61,    62,   250,   251,   252,    84,   174,   255,   256,   257,
     258,   259,   352,   188,   218,   200,    52,    84,   186,    82,
     188,    83,   190,   363,   218,   200,   117,     8,     9,    10,
      11,    12,   200,   201,   187,   224,    53,    54,    55,   192,
      76,   194,    78,   217,   197,   198,   221,    83,    84,    72,
     218,   219,   220,    82,   248,    91,   224,   148,    57,    58,
      53,    54,    55,   154,    57,    58,   234,   235,   236,   237,
      23,    24,   225,    53,   211,   345,    82,    57,    58,    82,
     248,   249,    53,   331,   332,    82,    57,    58,    10,    11,
      12,     8,     9,    84,   298,   299,   235,   236,   237,   273,
     191,    84,    87,    82,    82,   354,    82,    82,   199,    53,
     284,   202,   203,    57,    58,    59,    60,   208,   209,   210,
      82,     8,     9,   214,    82,   148,     8,     9,    82,     8,
       9,    82,   223,    82,    82,    52,   304,    82,    82,    82,
      57,    58,     5,     6,     7,     8,     9,    10,    11,    12,
     318,    82,   175,   176,    82,   178,   360,    82,   347,    82,
      87,    78,   185,    82,    82,    52,   360,    84,    82,   344,
      52,    53,   195,    52,    91,    57,    58,     6,     6,   347,
       7,     7,     7,   351,     7,    84,   354,    83,   211,    76,
     343,    78,   360,   346,    85,   348,    78,    84,    84,    78,
      74,    83,    84,   294,    91,    84,     8,     9,    87,    91,
      82,    56,    91,   366,    90,     6,     8,     9,    82,     6,
      82,   312,    82,     6,    85,     7,   401,    85,    85,    85,
      85,   406,   400,    85,    85,   403,    82,   411,    82,   413,
      82,    82,    82,    82,   418,    82,   399,    82,    82,    82,
      52,    82,     8,     9,     8,     9,   409,    70,    82,    54,
      52,    53,   353,    85,   355,    57,    58,    59,    60,    61,
      62,     8,     9,    65,   365,    82,    78,    88,    88,    71,
      72,    83,    84,    82,    76,    82,    78,     8,     9,    91,
      84,    83,    84,    82,    82,    85,    52,    82,    52,    91,
      86,   392,   325,   326,    85,    61,    62,     8,     9,    86,
      88,   402,     9,   404,   405,    52,   407,     8,     9,    82,
      76,    82,    78,    82,    78,    82,   226,   350,    84,   352,
      84,    52,    82,    89,    82,    91,    82,    91,    82,    76,
     363,    78,    85,    24,   326,   246,    -1,    84,    -1,   299,
      -1,    52,    -1,    -1,    91,    76,    -1,    78,    -1,    -1,
      -1,    52,    -1,    84,    -1,    -1,    -1,    -1,    -1,    -1,
      91,    -1,    -1,    74,    -1,    -1,    -1,    78,    -1,    -1,
      -1,    -1,    -1,    84,    -1,    76,    -1,    78,    -1,    -1,
      91,    -1,    -1,    84,    -1,    -1,    -1,    -1,    -1,    -1,
      91,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,     0,     1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    -1,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      -1,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    47,    -1,
      49,    50,    51,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    -1,    85,    -1,    -1,    -1,    66,    -1,    -1,
       0,     1,    -1,    85,    -1,    -1,    -1,    76,    -1,    78,
      -1,    81,    81,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    -1,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    47,    -1,    49,
      50,    51,     6,     7,     8,     9,    10,    11,    12,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    78,    -1,
      -1,    81
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    93,     0,     1,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    47,    49,    50,    51,
      66,    76,    78,    81,    94,    96,    81,    82,    98,    57,
      58,    83,   107,   108,   110,   111,   114,   107,     8,     9,
      52,    53,    59,    60,    61,    62,    65,    71,    72,    76,
      78,    83,    84,    91,   101,   102,   103,   105,   106,   109,
     114,   116,   118,   123,   124,   127,    98,    98,    98,   107,
     109,   118,    98,   109,    84,   124,   127,   124,   109,    98,
      67,    97,    98,   118,   103,    83,   102,   117,   118,   117,
     109,    99,   108,   109,   127,    99,   108,    82,    98,   109,
     118,    97,    97,   108,    97,    76,    83,   100,   127,    89,
     105,   119,   120,   121,   123,   127,   108,   108,   108,   109,
      97,    79,    80,    80,    81,    98,    84,   127,    82,     6,
       7,     9,    69,    70,    82,   127,   127,    84,    84,    84,
       6,     8,     9,   125,     9,    10,    74,    75,   105,   127,
     114,   127,   128,   127,    82,    84,    84,    76,    84,   100,
     104,   124,   127,   100,   103,    82,    82,    82,    82,    84,
      11,    82,    82,   101,    82,    82,     9,    82,    82,    82,
      82,    82,    82,    82,   109,   118,    98,    98,    82,    82,
      82,    82,   125,   124,    82,    84,   122,   123,    82,    87,
      87,    82,     6,    82,    82,    82,    95,   128,   128,   128,
      53,   109,   114,   115,     6,     7,     7,     7,     6,   109,
     127,   127,   127,     7,   127,   127,    84,    74,    83,    85,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      85,   103,   114,    53,    54,    55,   114,   126,   125,   114,
      84,    53,   114,   115,   100,   118,   108,   127,   127,   109,
     118,   118,   114,   118,   118,   109,    99,   127,   109,   109,
     109,   109,   109,   107,    82,   109,    56,    90,     9,    98,
     119,   127,   127,   108,     6,   109,   103,   118,    94,    81,
      81,    85,    82,   113,   127,   113,   113,   113,     6,    85,
      85,    85,   125,   126,   105,    84,    87,   127,   128,   128,
     128,     6,     7,   128,   128,   128,   128,   128,    85,    85,
      85,    85,    98,    82,    82,    82,    82,    82,    82,    98,
      82,    82,    82,    82,    82,    82,   109,    85,   123,   122,
      82,    88,    88,    82,   127,    82,    82,   109,   127,    84,
      85,   112,   114,   112,    86,   128,   128,    86,   118,   108,
     101,   118,   103,   118,   114,   127,   115,   109,   100,   109,
     119,   115,    82,   109,   118,    54,    85,    70,    88,    82,
       9,    82,    82,    82,    82,    82,    82,    82,   109,    82,
      85,   118,   127,   108,   109,   127,   109,   109,   108,   109,
     118,    98,    98,    98
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    92,    93,    93,    94,    95,    94,    94,    94,    94,
      94,    94,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    97,    98,    98,    99,
      99,   100,   100,   101,   101,   101,   101,   101,   102,   102,
     103,   103,   103,   103,   103,   103,   103,   103,   104,   104,
     105,   105,   105,   106,   106,   106,   106,   106,   106,   107,
     107,   107,   108,   109,   109,   110,   110,   110,   110,   111,
     111,   111,   112,   112,   113,   114,   114,   115,   115,   116,
     116,   117,   117,   118,   118,   119,   119,   119,   119,   120,
     120,   121,   122,   122,   122,   123,   123,   124,   124,   124,
     125,   125,   125,   126,   126,   126,   127,   127,   127,   127,
     127,   127,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     0,     0,     4,     4,     4,     1,
       2,     2,     2,     6,     5,     4,     4,     4,     4,     7,
       3,     3,     3,     3,     1,     5,     4,     4,     8,     6,
       6,     9,     4,     5,     8,     8,     2,     2,     2,     3,
       3,     3,     3,     4,     6,     8,     6,     4,     3,     4,
       4,     6,     5,     9,     9,     8,     4,     6,     6,     8,
       2,     4,     4,     2,     6,     2,     1,     0,     2,     7,
       1,     4,     2,     2,     2,     4,     2,     1,     2,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     4,     1,     3,     4,     5,     5,     6,     6,     1,
       1,     1,     2,     1,     1,     4,     4,     4,     4,     1,
       2,     5,     1,     2,     1,     1,     4,     1,     1,     1,
       4,     1,     1,     1,     4,     1,     1,     1,     1,     4,
       4,     3,     1,     3,     3,     1,     4,     4,     5,     7,
       0,     2,     2,     1,     1,     1,     1,     1,     2,     2,
       2,     3,     1,     3,     3,     3,     3,     3,     4,     4,
       3,     3,     3
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
#line 45 "a.y" /* yacc.c:1646  */
    {
		(yyvsp[-1].sym) = labellookup((yyvsp[-1].sym));
		if((yyvsp[-1].sym)->type == LLAB && (yyvsp[-1].sym)->value != pc)
			yyerror("redeclaration of %s", (yyvsp[-1].sym)->labelname);
		(yyvsp[-1].sym)->type = LLAB;
		(yyvsp[-1].sym)->value = pc;
	}
#line 1702 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 54 "a.y" /* yacc.c:1646  */
    {
		(yyvsp[-3].sym)->type = LVAR;
		(yyvsp[-3].sym)->value = (yyvsp[-1].lval);
	}
#line 1711 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 59 "a.y" /* yacc.c:1646  */
    {
		if((yyvsp[-3].sym)->value != (yyvsp[-1].lval))
			yyerror("redeclaration of %s", (yyvsp[-3].sym)->name);
		(yyvsp[-3].sym)->value = (yyvsp[-1].lval);
	}
#line 1721 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 73 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &nullgen, NREG, &nullgen);
	}
#line 1729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 80 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].lval), &(yyvsp[0].addr));
	}
#line 1737 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 84 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-4].lval), &(yyvsp[-3].addr), (yyvsp[-1].lval), &nullgen);
	}
#line 1745 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 88 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 95 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1761 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 102 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1769 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 109 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1777 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 113 "a.y" /* yacc.c:1646  */
    {
		Addr a;
		a = nullgen;
		a.type = D_CONST;
		a.offset = (yyvsp[-2].lval);
		outgcode((yyvsp[-6].lval), &(yyvsp[-5].addr), NREG, &a, &(yyvsp[0].addr));
	}
#line 1789 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 124 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1797 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 128 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1805 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 135 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1813 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 142 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1821 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 146 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[0].lval), &nullgen, NREG, &nullgen);
	}
#line 1829 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 153 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-4].lval), &(yyvsp[-3].addr), (yyvsp[-1].lval), &nullgen);
	}
#line 1837 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 160 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1845 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 167 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1853 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 174 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-2].addr).reg, &(yyvsp[-4].addr), &(yyvsp[0].addr));
	}
#line 1861 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 178 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].addr).reg, &(yyvsp[0].addr));
	}
#line 1869 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 185 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].addr).reg, &(yyvsp[0].addr));
	}
#line 1877 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 192 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-8].lval), &(yyvsp[-7].addr), (yyvsp[-3].addr).reg, &(yyvsp[-5].addr), &(yyvsp[-1].addr));
	}
#line 1885 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 199 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1893 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 203 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-4].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1901 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 210 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-2].lval), &(yyvsp[-4].addr), &(yyvsp[0].addr));
	}
#line 1909 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 217 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-2].lval), &(yyvsp[-4].addr), &(yyvsp[0].addr));
	}
#line 1917 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 224 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &nullgen, NREG, &nullgen);
	}
#line 1925 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 228 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1933 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 235 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &nullgen, NREG, &nullgen);
	}
#line 1941 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 239 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &(yyvsp[-1].addr), NREG, &nullgen);
	}
#line 1949 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 243 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &(yyvsp[-1].addr), NREG, &nullgen);
	}
#line 1957 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 247 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1965 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 251 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 1973 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 258 "a.y" /* yacc.c:1646  */
    {
		settext((yyvsp[-2].addr).sym);
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 1982 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 263 "a.y" /* yacc.c:1646  */
    {
		settext((yyvsp[-4].addr).sym);
		(yyvsp[0].addr).offset &= 0xffffffffull;
		(yyvsp[0].addr).offset |= (vlong)ArgsSizeUnknown << 32;
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].lval), &(yyvsp[0].addr));
	}
#line 1993 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 270 "a.y" /* yacc.c:1646  */
    {
		settext((yyvsp[-6].addr).sym);
		(yyvsp[-2].addr).offset &= 0xffffffffull;
		(yyvsp[-2].addr).offset |= ((yyvsp[0].lval) & 0xffffffffull) << 32;
		outcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-4].lval), &(yyvsp[-2].addr));
	}
#line 2004 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 280 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].lval), &(yyvsp[0].addr));
	}
#line 2012 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 287 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2020 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 294 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-2].lval), &nullgen, NREG, &(yyvsp[0].addr));
	}
#line 2028 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 301 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2036 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 308 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2044 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 312 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].addr).reg, &(yyvsp[0].addr));
	}
#line 2052 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 319 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-4].lval), &(yyvsp[-3].addr), (yyvsp[-1].addr).reg, &nullgen);
	}
#line 2060 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 326 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-8].lval), &(yyvsp[-7].addr), (yyvsp[-3].addr).reg, &(yyvsp[-5].addr), &(yyvsp[-1].addr));
	}
#line 2068 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 333 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-8].lval), &(yyvsp[-7].addr), (yyvsp[-5].addr).reg, &(yyvsp[-3].addr), &(yyvsp[-1].addr));
	}
#line 2076 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 340 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-2].addr).reg, &(yyvsp[-4].addr), &(yyvsp[0].addr));
	}
#line 2084 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 347 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2092 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 351 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].addr).reg, &(yyvsp[0].addr));
	}
#line 2100 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 358 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-5].lval), &(yyvsp[-4].addr), (yyvsp[-2].lval), &(yyvsp[0].addr));
	}
#line 2108 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 365 "a.y" /* yacc.c:1646  */
    {
		outgcode((yyvsp[-7].lval), &(yyvsp[-6].addr), (yyvsp[-2].lval), &(yyvsp[-4].addr), &(yyvsp[0].addr));
	}
#line 2116 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 372 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &(yyvsp[0].addr), NREG, &nullgen);
	}
#line 2124 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 376 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[0].addr), (yyvsp[-2].addr).reg, &nullgen);
	}
#line 2132 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 380 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-3].lval), &(yyvsp[-2].addr), NREG, &(yyvsp[0].addr));
	}
#line 2140 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 387 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &(yyvsp[0].addr), NREG, &nullgen);
	}
#line 2148 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 394 "a.y" /* yacc.c:1646  */
    {
		outtcode((yyvsp[-5].lval), &(yyvsp[-4].addr), &(yyvsp[-2].addr), &(yyvsp[0].addr));
	}
#line 2156 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 401 "a.y" /* yacc.c:1646  */
    {
		outcode((yyvsp[-1].lval), &nullgen, NREG, &nullgen);
	}
#line 2164 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 407 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_COND;
		(yyval.addr).reg = (yyvsp[0].lval);
	}
#line 2174 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 418 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_CONST;
		(yyval.addr).offset = SYSARG4((yyvsp[-6].lval), (yyvsp[-4].lval), (yyvsp[-2].lval), (yyvsp[0].lval));
	}
#line 2184 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 427 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_BRANCH;
		(yyval.addr).offset = (yyvsp[-3].lval) + pc;
	}
#line 2194 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 433 "a.y" /* yacc.c:1646  */
    {
		(yyvsp[-1].sym) = labellookup((yyvsp[-1].sym));
		(yyval.addr) = nullgen;
		if(pass == 2 && (yyvsp[-1].sym)->type != LLAB)
			yyerror("undefined label: %s", (yyvsp[-1].sym)->labelname);
		(yyval.addr).type = D_BRANCH;
		(yyval.addr).offset = (yyvsp[-1].sym)->value + (yyvsp[0].lval);
	}
#line 2207 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 443 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_CONST;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2217 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 449 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = (yyvsp[0].addr);
		(yyval.addr).type = D_CONST;
	}
#line 2226 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 454 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = (yyvsp[0].addr);
		(yyval.addr).type = D_OCONST;
	}
#line 2235 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 459 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SCONST;
		memmove((yyval.addr).u.sval, (yyvsp[0].sval), sizeof((yyval.addr).u.sval));
	}
#line 2245 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 468 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FCONST;
		(yyval.addr).u.dval = (yyvsp[0].dval);
	}
#line 2255 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 474 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FCONST;
		(yyval.addr).u.dval = -(yyvsp[0].dval);
	}
#line 2265 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 484 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SPR;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2275 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 490 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2285 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 502 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
		(yyval.addr).offset = 0;
	}
#line 2296 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 509 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = (yyvsp[0].addr);
		if((yyvsp[0].addr).name != D_EXTERN && (yyvsp[0].addr).name != D_STATIC) {
		}
	}
#line 2306 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 518 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = (yyvsp[-3].addr);
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
	}
#line 2316 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 527 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
		(yyval.addr).offset = 0;
	}
#line 2327 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 534 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
		(yyval.addr).offset = (yyvsp[-3].lval);
	}
#line 2338 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 541 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_XPRE;
		(yyval.addr).reg = (yyvsp[-2].lval);
		(yyval.addr).offset = (yyvsp[-4].lval);
	}
#line 2349 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 548 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_XPOST;
		(yyval.addr).reg = (yyvsp[-3].lval);
		(yyval.addr).offset = (yyvsp[-1].lval);
	}
#line 2360 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 555 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_ROFF;
		(yyval.addr).reg = (yyvsp[-4].lval);
		(yyval.addr).scale = (yyvsp[-1].lval) & 0x1f;
		(yyval.addr).offset = (yyvsp[-1].lval);
	}
#line 2372 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 563 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_ROFF;
		(yyval.addr).reg = (yyvsp[-4].lval);
		(yyval.addr).scale = (yyvsp[-1].lval) & 0x1f;
		(yyval.addr).offset = (yyvsp[-1].lval) | (1<<16);
	}
#line 2384 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 577 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_CONST;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2394 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 585 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_REG;
		(yyval.addr).reg = (yyvsp[0].lval);
	}
#line 2404 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 591 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SP;
		(yyval.addr).reg = REGSP;
	}
#line 2414 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 599 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = ((yyvsp[-3].lval) << 16) | ((yyvsp[0].lval) << 10) | (0 << 22);
	}
#line 2424 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 605 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = (((yyvsp[-3].lval)&0x1F) << 16) | ((yyvsp[0].lval) << 10) | (1 << 22);
	}
#line 2434 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 611 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = ((yyvsp[-3].lval) << 16) | ((yyvsp[0].lval) << 10) | (2 << 22);
	}
#line 2444 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 617 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SHIFT;
		(yyval.addr).offset = ((yyvsp[-3].lval) << 16) | ((yyvsp[0].lval) << 10) | (3 << 22);
	}
#line 2454 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 625 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_REG;
		(yyval.addr).reg = (yyvsp[0].lval);
	}
#line 2464 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 631 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_EXTREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
		(yyval.addr).offset = ((yyvsp[-1].lval) << 16) | ((yyvsp[0].lval) << 13);
	}
#line 2475 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 638 "a.y" /* yacc.c:1646  */
    {
		if((yyvsp[0].lval) < 0 || (yyvsp[0].lval) > 4)
			yyerror("shift value out of range");
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_EXTREG;
		(yyval.addr).reg = (yyvsp[-4].lval);
		(yyval.addr).offset = ((yyvsp[-4].lval) << 16) | ((yyvsp[-3].lval) << 13) | ((yyvsp[0].lval) << 10);
	}
#line 2488 "y.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 649 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (3 << 8) | (yyvsp[0].lval);
	}
#line 2496 "y.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 653 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = ((yyvsp[0].lval) << 8) | (yyvsp[-1].lval);
	}
#line 2504 "y.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 659 "a.y" /* yacc.c:1646  */
    {
		if((yyval.lval) < 0 || (yyval.lval) >= 64)
			yyerror("shift value out of range");
		(yyval.lval) = (yyvsp[0].lval)&0x3F;
	}
#line 2514 "y.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 668 "a.y" /* yacc.c:1646  */
    {
		if((yyvsp[-1].lval) < 0 || (yyvsp[-1].lval) >= NREG)
			print("register value out of range\n");
		(yyval.lval) = (yyvsp[-1].lval);
	}
#line 2524 "y.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 677 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = REGSP;
	}
#line 2532 "y.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 683 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_SPR;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2542 "y.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 689 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = (yyvsp[-3].lval);
		(yyval.addr).offset = (yyvsp[-1].lval);
	}
#line 2552 "y.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 701 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FREG;
		(yyval.addr).reg = (yyvsp[0].lval);
	}
#line 2562 "y.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 707 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_FREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
	}
#line 2572 "y.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 718 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_VSET;
		(yyval.addr).offset = (yyvsp[0].lval);
	}
#line 2582 "y.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 726 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr).type = D_VLANE;
		(yyval.addr).offset = (yyvsp[-1].lval);
	}
#line 2591 "y.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 731 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr).type = D_VLANE;
		(yyval.addr).offset = (yyvsp[-1].lval);
	}
#line 2600 "y.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 738 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-1].lval);
	}
#line 2608 "y.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 744 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = 1 << (yyvsp[0].addr).reg;
	}
#line 2616 "y.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 748 "a.y" /* yacc.c:1646  */
    {
		int i;
		(yyval.lval)=0;
		for(i=(yyvsp[-2].addr).reg; i<=(yyvsp[0].addr).reg; i++)
			(yyval.lval) |= 1<<i;
		for(i=(yyvsp[0].addr).reg; i<=(yyvsp[-2].addr).reg; i++)
			(yyval.lval) |= 1<<i;
	}
#line 2629 "y.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 757 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (1<<(yyvsp[-2].addr).reg) | (yyvsp[0].lval);
	}
#line 2637 "y.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 763 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_VREG;
		(yyval.addr).reg = (yyvsp[0].lval);
		/* TO DO: slice */
	}
#line 2648 "y.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 770 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_VREG;
		(yyval.addr).reg = (yyvsp[-1].lval);
	}
#line 2658 "y.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 778 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).name = (yyvsp[-1].lval);
		(yyval.addr).sym = nil;
		(yyval.addr).offset = (yyvsp[-3].lval);
	}
#line 2670 "y.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 786 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).name = (yyvsp[-1].lval);
		(yyval.addr).sym = linklookup(ctxt, (yyvsp[-4].sym)->name, 0);
		(yyval.addr).offset = (yyvsp[-3].lval);
	}
#line 2682 "y.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 794 "a.y" /* yacc.c:1646  */
    {
		(yyval.addr) = nullgen;
		(yyval.addr).type = D_OREG;
		(yyval.addr).name = D_STATIC;
		(yyval.addr).sym = linklookup(ctxt, (yyvsp[-6].sym)->name, 0);
		(yyval.addr).offset = (yyvsp[-3].lval);
	}
#line 2694 "y.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 803 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = 0;
	}
#line 2702 "y.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 807 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[0].lval);
	}
#line 2710 "y.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 811 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = -(yyvsp[0].lval);
	}
#line 2718 "y.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 823 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[0].sym)->value;
	}
#line 2726 "y.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 827 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = -(yyvsp[0].lval);
	}
#line 2734 "y.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 831 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[0].lval);
	}
#line 2742 "y.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 835 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = ~(yyvsp[0].lval);
	}
#line 2750 "y.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 839 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-1].lval);
	}
#line 2758 "y.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 846 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) + (yyvsp[0].lval);
	}
#line 2766 "y.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 850 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) - (yyvsp[0].lval);
	}
#line 2774 "y.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 854 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) * (yyvsp[0].lval);
	}
#line 2782 "y.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 858 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) / (yyvsp[0].lval);
	}
#line 2790 "y.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 862 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) % (yyvsp[0].lval);
	}
#line 2798 "y.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 866 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-3].lval) << (yyvsp[0].lval);
	}
#line 2806 "y.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 870 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-3].lval) >> (yyvsp[0].lval);
	}
#line 2814 "y.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 874 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) & (yyvsp[0].lval);
	}
#line 2822 "y.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 878 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) ^ (yyvsp[0].lval);
	}
#line 2830 "y.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 882 "a.y" /* yacc.c:1646  */
    {
		(yyval.lval) = (yyvsp[-2].lval) | (yyvsp[0].lval);
	}
#line 2838 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2842 "y.tab.c" /* yacc.c:1646  */
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
