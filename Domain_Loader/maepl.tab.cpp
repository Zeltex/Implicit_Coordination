/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "maepl.y"

  #include <cstdio>
  #include <iostream>
  using namespace std;
  #include "Maepl.hpp"
  #include "Domain_Buffer.hpp"

  // stuff from flex that bison needs to know about:
  extern int yylex();
  extern int yyparse();
  extern FILE *yyin;
  extern int line_num;
 
  void yyerror(const char *s);

  Domain_Interface* domain;
  Domain_Buffer* buffer;

/* Line 371 of yacc.c  */
#line 87 "maepl.tab.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
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
   by #include "maepl.tab.h".  */
#ifndef YY_YY_MAEPL_TAB_H_INCLUDED
# define YY_YY_MAEPL_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ACTION_DEF = 258,
     DEFINE_DEF = 259,
     DESIGNATED_EVENTS_DEF = 260,
     DESIGNATED_WORLDS_DEF = 261,
     DOMAIN_DEF = 262,
     EFFECT_ADD_DEF = 263,
     EFFECT_DELETE_DEF = 264,
     EVENT_DEF = 265,
     GOAL_DEF = 266,
     INIT_DEF = 267,
     OBJECTS_DEF = 268,
     OWNER_DEF = 269,
     PRECONDITIONS_DEF = 270,
     PROBLEM_DEF = 271,
     PROPOSITIONS_DEF = 272,
     REACHAbility_DEF = 273,
     REFLEXIVITY_DEF = 274,
     TYPES_DEF = 275,
     WORLD_DEF = 276,
     LBRACK = 277,
     RBRACK = 278,
     AND = 279,
     OR = 280,
     NOT = 281,
     NAME = 282,
     TRUTH = 283,
     EQUALS = 284,
     INT = 285,
     FLOAT = 286,
     STRING = 287
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 21 "maepl.y"

  int ival;
  float fval;
  char *sval;
  bool bval;


/* Line 387 of yacc.c  */
#line 170 "maepl.tab.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

#endif /* !YY_YY_MAEPL_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 198 "maepl.tab.cpp"

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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

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
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   183

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  59
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNRULES -- Number of states.  */
#define YYNSTATES  220

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   287

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     5,     6,    17,    18,    26,    27,
      28,    34,    35,    43,    44,    52,    53,    61,    62,    70,
      71,    79,    80,    88,    89,    95,    96,   103,   104,   110,
     111,   117,   118,   124,   125,   126,   134,   135,   141,   142,
     148,   149,   154,   155,   156,   161,   162,   163,   174,   175,
     176,   182,   183,   184,   193,   194,   195,   204,   205,   207,
     208,   209,   210,   219,   220,   221,   228,   229,   230,   237,
     238,   242,   243,   245,   246,   250,   251,   252,   260,   261,
     262,   270,   271,   272,   280,   281,   283,   284,   290,   291,
     297,   298,   304,   306,   309,   311,   314,   316,   317,   320
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      34,     0,    -1,    -1,    -1,    -1,     7,    27,    22,    35,
      53,    54,    90,    23,    36,    34,    -1,    -1,    16,    27,
      22,    38,    23,    37,    34,    -1,    -1,    -1,     7,    29,
      27,    39,    38,    -1,    -1,    13,    29,    22,    51,    23,
      40,    38,    -1,    -1,    12,    29,    22,    49,    23,    41,
      38,    -1,    -1,    21,    27,    22,    48,    23,    42,    38,
      -1,    -1,    11,    29,    22,    76,    23,    43,    38,    -1,
      -1,     6,    29,    22,    91,    23,    44,    38,    -1,    -1,
      18,    29,    22,    47,    23,    45,    38,    -1,    -1,    19,
      29,    28,    46,    38,    -1,    -1,    27,    29,    22,    50,
      23,    47,    -1,    -1,    27,    22,    91,    23,    48,    -1,
      -1,    27,    22,    91,    23,    49,    -1,    -1,    22,    27,
      27,    23,    50,    -1,    -1,    -1,    27,    29,    22,    91,
      23,    52,    51,    -1,    -1,    20,    29,    22,    91,    23,
      -1,    -1,    17,    29,    22,    89,    23,    -1,    -1,    27,
      22,    56,    23,    -1,    -1,    -1,    27,    27,    57,    56,
      -1,    -1,    -1,     3,    27,    59,    22,    56,    23,    60,
      22,    61,    23,    -1,    -1,    -1,    14,    29,    27,    62,
      61,    -1,    -1,    -1,    10,    27,    22,    63,    68,    23,
      64,    61,    -1,    -1,    -1,     5,    29,    22,    65,    67,
      23,    66,    61,    -1,    -1,    27,    -1,    -1,    -1,    -1,
      15,    29,    22,    69,    76,    23,    70,    68,    -1,    -1,
      -1,     9,    29,    71,    75,    72,    68,    -1,    -1,    -1,
       8,    29,    73,    75,    74,    68,    -1,    -1,    22,    91,
      23,    -1,    -1,    27,    -1,    -1,    27,    77,    76,    -1,
      -1,    -1,    24,    22,    78,    76,    23,    79,    76,    -1,
      -1,    -1,    25,    22,    80,    76,    23,    81,    76,    -1,
      -1,    -1,    26,    22,    82,    84,    23,    83,    76,    -1,
      -1,    27,    -1,    -1,    24,    22,    85,    76,    23,    -1,
      -1,    25,    22,    86,    76,    23,    -1,    -1,    26,    22,
      87,    84,    23,    -1,    27,    -1,    89,    55,    -1,    55,
      -1,    90,    58,    -1,    58,    -1,    -1,    91,    88,    -1,
      88,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    75,    75,    76,    77,    76,    79,    78,    81,    82,
      82,    83,    83,    84,    84,    85,    85,    86,    86,    87,
      87,    88,    88,    89,    89,    91,    92,    97,    98,   100,
     101,   103,   104,   106,   107,   107,   111,   112,   116,   117,
     120,   121,   123,   124,   124,   128,   129,   128,   133,   134,
     134,   135,   136,   135,   141,   142,   141,   144,   145,   147,
     148,   149,   148,   150,   151,   150,   152,   153,   152,   157,
     158,   163,   164,   165,   165,   166,   167,   166,   168,   169,
     168,   170,   171,   170,   174,   175,   176,   176,   178,   178,
     180,   180,   183,   186,   187,   190,   191,   193,   194,   195
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ACTION_DEF", "DEFINE_DEF",
  "DESIGNATED_EVENTS_DEF", "DESIGNATED_WORLDS_DEF", "DOMAIN_DEF",
  "EFFECT_ADD_DEF", "EFFECT_DELETE_DEF", "EVENT_DEF", "GOAL_DEF",
  "INIT_DEF", "OBJECTS_DEF", "OWNER_DEF", "PRECONDITIONS_DEF",
  "PROBLEM_DEF", "PROPOSITIONS_DEF", "REACHAbility_DEF", "REFLEXIVITY_DEF",
  "TYPES_DEF", "WORLD_DEF", "LBRACK", "RBRACK", "AND", "OR", "NOT", "NAME",
  "TRUTH", "EQUALS", "INT", "FLOAT", "STRING", "$accept", "maepl", "$@1",
  "$@2", "$@3", "problem_body", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9",
  "$@10", "$@11", "reachability_body", "world_body", "init_body", "pairs",
  "objects", "$@12", "types_container", "propositions_container",
  "proposition", "input", "$@13", "action", "$@14", "$@15", "action_body",
  "$@16", "$@17", "$@18", "$@19", "$@20", "designated_events_body",
  "event_body", "$@21", "$@22", "$@23", "$@24", "$@25", "$@26",
  "variables_container", "formula", "$@27", "$@28", "$@29", "$@30", "$@31",
  "$@32", "$@33", "formula_single", "$@34", "$@35", "$@36", "variable",
  "propositions", "actions", "variables", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    33,    34,    35,    36,    34,    37,    34,    38,    39,
      38,    40,    38,    41,    38,    42,    38,    43,    38,    44,
      38,    45,    38,    46,    38,    47,    47,    48,    48,    49,
      49,    50,    50,    51,    52,    51,    53,    53,    54,    54,
      55,    55,    56,    57,    56,    59,    60,    58,    61,    62,
      61,    63,    64,    61,    65,    66,    61,    67,    67,    68,
      69,    70,    68,    71,    72,    68,    73,    74,    68,    75,
      75,    76,    76,    77,    76,    78,    79,    76,    80,    81,
      76,    82,    83,    76,    84,    84,    85,    84,    86,    84,
      87,    84,    88,    89,    89,    90,    90,    91,    91,    91
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     0,    10,     0,     7,     0,     0,
       5,     0,     7,     0,     7,     0,     7,     0,     7,     0,
       7,     0,     7,     0,     5,     0,     6,     0,     5,     0,
       5,     0,     5,     0,     0,     7,     0,     5,     0,     5,
       0,     4,     0,     0,     4,     0,     0,    10,     0,     0,
       5,     0,     0,     8,     0,     0,     8,     0,     1,     0,
       0,     0,     8,     0,     0,     6,     0,     0,     6,     0,
       3,     0,     1,     0,     3,     0,     0,     7,     0,     0,
       7,     0,     0,     7,     0,     1,     0,     5,     0,     5,
       0,     5,     1,     2,     1,     2,     1,     0,     2,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     0,     0,     0,     1,     3,     8,    36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      38,     0,     0,     0,     0,     0,     0,     0,     0,     6,
       0,     0,     0,    97,     9,    71,    29,    33,    25,    23,
      27,     2,    97,     0,     0,    96,     0,    92,    99,     0,
       8,     0,     0,     0,    73,     0,     0,     0,     0,     0,
       0,     0,     8,     0,     0,     7,     0,    40,    45,     4,
      95,    19,    98,    10,    75,    78,    81,    71,    17,    97,
      13,     0,    11,     0,    21,    24,    97,    15,    37,     0,
      94,     0,     0,     2,     8,    71,    71,    84,    74,     8,
       0,     8,    97,     8,    31,     8,     0,     8,    42,    39,
      93,    42,     5,    20,     0,     0,     0,     0,     0,    85,
       0,    18,    29,    14,     0,    12,     0,     0,    22,    27,
      16,     0,     0,     0,    76,    79,    86,    88,    90,    82,
      30,    34,     0,    25,    28,    43,    41,    46,    71,    71,
      71,    71,    84,    71,    33,     0,    26,    42,     0,    77,
      80,     0,     0,     0,    83,    35,    31,    44,    48,    87,
      89,    91,    32,     0,     0,     0,     0,     0,     0,     0,
      47,    54,    51,    49,    57,    59,    48,    58,     0,     0,
       0,     0,     0,    50,    55,    66,    63,     0,    52,    48,
      69,    69,    60,    48,    56,    97,    67,    64,    71,    53,
       0,    59,    59,     0,    70,    68,    65,    61,    59,    62
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     9,    93,    41,    18,    50,   103,   101,   107,
      99,    94,   105,    62,    61,    64,    57,   127,    59,   154,
      20,    32,    90,   132,   157,    45,    92,   158,   176,   186,
     185,   203,   184,   199,   188,   192,   208,   218,   201,   212,
     200,   211,   206,    55,    77,    95,   148,    96,   149,    97,
     153,   120,   150,   151,   152,    48,    91,    46,    49
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -200
static const yytype_int16 yypact[] =
{
       1,    -7,    -6,    30,    14,    17,  -200,  -200,    22,     3,
      16,    21,    27,    45,    52,    58,    60,    48,    65,    61,
      74,    70,    66,    72,    73,    75,    76,    68,    77,  -200,
      78,    79,    98,    80,  -200,    46,    82,    83,    84,  -200,
      85,     1,    80,    81,    86,  -200,     4,  -200,  -200,   -12,
      22,    92,    93,    94,    95,    96,    99,    97,    88,   100,
     101,   102,    22,   104,   105,  -200,    19,   106,  -200,  -200,
    -200,  -200,  -200,  -200,  -200,  -200,  -200,    46,  -200,    80,
    -200,   107,  -200,   109,  -200,  -200,    80,  -200,  -200,   110,
    -200,    24,   112,     1,    22,    46,    46,    59,  -200,    22,
      39,    22,    80,    22,   113,    22,    40,    22,   111,  -200,
    -200,   111,  -200,  -200,   116,   117,   114,   119,   120,  -200,
     121,  -200,    82,  -200,    41,  -200,   118,   123,  -200,    85,
    -200,   122,   124,   125,  -200,  -200,  -200,  -200,  -200,  -200,
    -200,  -200,   126,    84,  -200,  -200,  -200,  -200,    46,    46,
      46,    46,    59,    46,    83,   127,  -200,   111,   129,  -200,
    -200,   131,   132,   133,  -200,  -200,   113,  -200,     0,  -200,
    -200,  -200,  -200,   128,   134,   130,   135,   138,   142,   139,
    -200,  -200,  -200,  -200,   140,    23,     0,  -200,   145,   136,
     141,   143,   146,  -200,  -200,  -200,  -200,   149,  -200,     0,
     151,   151,  -200,     0,  -200,    80,  -200,  -200,    46,  -200,
      42,    23,    23,   152,  -200,  -200,  -200,  -200,    23,  -200
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -200,   -39,  -200,  -200,  -200,   -46,  -200,  -200,  -200,  -200,
    -200,  -200,  -200,  -200,   -41,   -25,   -17,   -60,   -32,  -200,
    -200,  -200,    33,  -108,  -200,   137,  -200,  -200,  -177,  -200,
    -200,  -200,  -200,  -200,  -200,  -199,  -200,  -200,  -200,  -200,
    -200,  -200,   -74,   -71,  -200,  -200,  -200,  -200,  -200,  -200,
    -200,    -9,  -200,  -200,  -200,   -48,  -200,  -200,   -42
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -73
static const yytype_int16 yytable[] =
{
      66,    72,    65,   133,    73,   173,    98,    44,     1,   193,
     174,    71,   215,   216,   175,    47,    85,     2,    72,   219,
       4,     5,   204,    19,   114,   115,   209,    69,    10,    11,
       6,   189,   190,    12,    13,    14,     7,   100,   191,     8,
      15,    16,    88,    17,   106,    21,    47,   109,   113,   167,
      22,    89,    72,   121,   112,   123,    23,   125,    72,   128,
     124,   130,   122,   129,   141,   214,    47,    47,    47,    47,
      51,    52,    53,    54,    24,    28,    72,   159,   160,   161,
     162,    25,   164,   116,   117,   118,   119,    26,    29,    27,
      30,    31,    33,    34,    35,    36,    39,    37,    38,    40,
      42,    44,   156,    67,   144,   140,   172,    47,    43,    56,
      58,    60,    63,    68,    74,    75,    76,    81,   -72,    78,
      80,    79,   165,    82,   110,    84,    86,   207,    87,   102,
      83,   104,   108,    89,   111,   126,   136,   213,   131,   134,
     135,   137,   138,   163,   139,   142,   143,   146,   147,   145,
     166,   168,     0,   155,   169,   170,   171,   177,   180,   179,
     181,   178,    72,   210,   182,   195,   183,   187,   194,   198,
     196,   202,   197,   205,     0,   217,     0,     0,     0,     0,
       0,     0,     0,    70
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-200)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      42,    49,    41,   111,    50,     5,    77,     3,     7,   186,
      10,    23,   211,   212,    14,    27,    62,    16,    66,   218,
      27,    27,   199,    20,    95,    96,   203,    23,     6,     7,
       0,     8,     9,    11,    12,    13,    22,    79,    15,    22,
      18,    19,    23,    21,    86,    29,    27,    23,    94,   157,
      29,    27,   100,    99,    93,   101,    29,   103,   106,   105,
     102,   107,    23,    23,    23,    23,    27,    27,    27,    27,
      24,    25,    26,    27,    29,    27,   124,   148,   149,   150,
     151,    29,   153,    24,    25,    26,    27,    29,    23,    29,
      29,    17,    22,    27,    22,    22,    28,    22,    22,    22,
      22,     3,   143,    22,   129,   122,   166,    27,    29,    27,
      27,    27,    27,    27,    22,    22,    22,    29,    23,    23,
      23,    22,   154,    23,    91,    23,    22,   201,    23,    22,
      29,    22,    22,    27,    22,    22,    22,   208,    27,    23,
      23,    22,    22,   152,    23,    27,    23,    23,    23,    27,
      23,    22,    -1,    27,    23,    23,    23,    29,    23,    29,
      22,    27,   210,   205,    22,    29,    27,    27,    23,    23,
      29,    22,    29,    22,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    46
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,    16,    34,    27,    27,     0,    22,    22,    35,
       6,     7,    11,    12,    13,    18,    19,    21,    38,    20,
      53,    29,    29,    29,    29,    29,    29,    29,    27,    23,
      29,    17,    54,    22,    27,    22,    22,    22,    22,    28,
      22,    37,    22,    29,     3,    58,    90,    27,    88,    91,
      39,    24,    25,    26,    27,    76,    27,    49,    27,    51,
      27,    47,    46,    27,    48,    34,    91,    22,    27,    23,
      58,    23,    88,    38,    22,    22,    22,    77,    23,    22,
      23,    29,    23,    29,    23,    38,    22,    23,    23,    27,
      55,    89,    59,    36,    44,    78,    80,    82,    76,    43,
      91,    41,    22,    40,    22,    45,    91,    42,    22,    23,
      55,    22,    34,    38,    76,    76,    24,    25,    26,    27,
      84,    38,    23,    38,    91,    38,    22,    50,    38,    23,
      38,    27,    56,    56,    23,    23,    22,    22,    22,    23,
      49,    23,    27,    23,    48,    27,    23,    23,    79,    81,
      85,    86,    87,    83,    52,    27,    47,    57,    60,    76,
      76,    76,    76,    84,    76,    51,    23,    56,    22,    23,
      23,    23,    50,     5,    10,    14,    61,    29,    27,    29,
      23,    22,    22,    27,    65,    63,    62,    27,    67,     8,
       9,    15,    68,    61,    23,    29,    29,    29,    23,    66,
      73,    71,    22,    64,    61,    22,    75,    75,    69,    61,
      91,    74,    72,    76,    23,    68,    68,    23,    70,    68
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
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




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

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
        case 3:
/* Line 1792 of yacc.c  */
#line 76 "maepl.y"
    { domain->new_domain(std::string((yyvsp[(2) - (3)].sval)));                         }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 77 "maepl.y"
    { domain->finish_domain();                  }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 79 "maepl.y"
    { domain->finish_problem();                                    }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 82 "maepl.y"
    { domain->set_domain((yyvsp[(3) - (3)].sval));}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 83 "maepl.y"
    {}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 84 "maepl.y"
    {}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 85 "maepl.y"
    {}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 86 "maepl.y"
    {}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 87 "maepl.y"
    {}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 88 "maepl.y"
    {}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 89 "maepl.y"
    {}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 107 "maepl.y"
    { buffer->set_object_type((yyvsp[(1) - (5)].sval));
                                               buffer->push_objects(); 
                                               domain->set_objects(buffer->get_objects());                  }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 111 "maepl.y"
    { std::cerr << "Missing types definition\n";                   }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 113 "maepl.y"
    { buffer->push_types(); 
                                               domain->set_types(buffer->get_types());                      }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 116 "maepl.y"
    { std::cerr << "Missing propositions definition\n";            }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 121 "maepl.y"
    { domain->add_proposition((yyvsp[(1) - (4)].sval), buffer->get_inputs());           }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 124 "maepl.y"
    { buffer->add_input((yyvsp[(1) - (2)].sval), (yyvsp[(2) - (2)].sval));                                   }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 128 "maepl.y"
    { domain->new_action(std::string((yyvsp[(2) - (2)].sval)));                         }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 129 "maepl.y"
    { domain->set_action_input(buffer->get_inputs());              }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 131 "maepl.y"
    { domain->finish_action();                                     }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 134 "maepl.y"
    { domain->set_action_owner((yyvsp[(3) - (3)].sval));                                }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 135 "maepl.y"
    { buffer->set_event_name((yyvsp[(2) - (3)].sval));                                  }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 136 "maepl.y"
    { domain->create_event(                                        
                                                 buffer->get_event_name(),                                  
                                                 buffer->get_event_preconditions(),                         
                                                 buffer->get_event_add_list(),                              
                                                 buffer->get_event_delete_list());                          }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 141 "maepl.y"
    { buffer->clear_designated_events();                           }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 142 "maepl.y"
    { domain->set_designated_events(buffer->get_designated_events());}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 145 "maepl.y"
    { buffer->add_designated_event((yyvsp[(1) - (1)].sval));                            }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 148 "maepl.y"
    { buffer->clear_formula();                                     }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 149 "maepl.y"
    {                                                              }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 150 "maepl.y"
    { buffer->clear_variable_list();                               }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 151 "maepl.y"
    { buffer->push_event_delete_list();                            }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 152 "maepl.y"
    { buffer->clear_variable_list();                               }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 153 "maepl.y"
    { buffer->push_event_add_list();                               }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 158 "maepl.y"
    {                                                              }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 164 "maepl.y"
    {buffer->push_pop_formula("Prop", (yyvsp[(1) - (1)].sval));                         }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 165 "maepl.y"
    {buffer->push_pop_formula("Prop", (yyvsp[(1) - (1)].sval));                         }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 166 "maepl.y"
    {buffer->push_formula("And");                                  }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 167 "maepl.y"
    {buffer->pop_formula();                                        }
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 168 "maepl.y"
    {buffer->push_formula("Or");                                   }
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 169 "maepl.y"
    {buffer->pop_formula();                                        }
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 170 "maepl.y"
    {buffer->push_formula("Not");                                  }
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 171 "maepl.y"
    {buffer->pop_formula();                                        }
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 175 "maepl.y"
    {buffer->push_pop_formula("Prop", (yyvsp[(1) - (1)].sval));                         }
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 176 "maepl.y"
    {buffer->push_formula("And");                                  }
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 177 "maepl.y"
    {buffer->pop_formula();                                        }
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 178 "maepl.y"
    {buffer->push_formula("Or");                                   }
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 179 "maepl.y"
    {buffer->pop_formula();                                        }
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 180 "maepl.y"
    {buffer->push_formula("Not");                                  }
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 181 "maepl.y"
    {buffer->pop_formula();                                        }
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 183 "maepl.y"
    { buffer->add_variable((yyvsp[(1) - (1)].sval));                                    }
    break;


/* Line 1792 of yacc.c  */
#line 1871 "maepl.tab.cpp"
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


/* Line 2055 of yacc.c  */
#line 197 "maepl.y"


void parse_domain(Domain_Interface* domain_input, Domain_Buffer* buffer_input, FILE* file_in) {
    domain = domain_input;
    buffer = buffer_input;
    yyin = file_in;
    yyparse();
}

void yyerror(const char *s) {
  std::cout << "EEK, parse error on line " << line_num << "!  Message: " << s << std::endl;
  // might as well halt now:
  exit(-1);
}
