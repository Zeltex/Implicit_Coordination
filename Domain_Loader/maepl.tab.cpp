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
     ANNOUNCE_DEF = 259,
     DEFINE_DEF = 260,
     DESIGNATED_EVENTS_DEF = 261,
     DESIGNATED_WORLDS_DEF = 262,
     DOMAIN_DEF = 263,
     EFFECT_ADD_DEF = 264,
     EFFECT_DELETE_DEF = 265,
     EVENT_DEF = 266,
     GOAL_DEF = 267,
     INIT_DEF = 268,
     OBJECTS_DEF = 269,
     OWNER_DEF = 270,
     PRECONDITIONS_DEF = 271,
     PROBLEM_DEF = 272,
     PROPOSITIONS_DEF = 273,
     REACHAbility_DEF = 274,
     REFLEXIVITY_DEF = 275,
     TYPES_DEF = 276,
     WORLD_DEF = 277,
     LBRACK = 278,
     RBRACK = 279,
     AND = 280,
     OR = 281,
     NOT = 282,
     NAME = 283,
     TRUTH = 284,
     EQUALS = 285,
     INT = 286,
     FLOAT = 287,
     STRING = 288
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
#line 171 "maepl.tab.cpp"
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
#line 199 "maepl.tab.cpp"

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
#define YYLAST   178

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  66
/* YYNRULES -- Number of rules.  */
#define YYNRULES  106
/* YYNRULES -- Number of states.  */
#define YYNSTATES  228

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   288

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
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     5,     6,    15,    16,    24,    29,
      30,    31,    37,    38,    46,    47,    55,    56,    64,    65,
      73,    74,    82,    83,    91,    92,    98,    99,   100,   108,
     109,   110,   118,   119,   123,   124,   130,   135,   136,   142,
     143,   148,   149,   150,   157,   158,   159,   164,   165,   166,
     177,   178,   179,   185,   186,   187,   196,   197,   198,   207,
     208,   209,   213,   214,   215,   216,   225,   226,   227,   234,
     235,   236,   243,   244,   246,   247,   251,   252,   253,   261,
     262,   263,   271,   272,   273,   281,   282,   284,   285,   291,
     292,   298,   299,   305,   307,   311,   312,   315,   318,   320,
     323,   325,   326,   329,   331,   332,   333
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      35,     0,    -1,    -1,    -1,    -1,     8,    28,    23,    36,
      39,    24,    37,    35,    -1,    -1,    17,    28,    23,    40,
      24,    38,    35,    -1,    53,    54,    56,    96,    -1,    -1,
      -1,     8,    30,    28,    41,    40,    -1,    -1,    14,    30,
      23,    51,    24,    42,    40,    -1,    -1,    13,    30,    23,
      94,    24,    43,    40,    -1,    -1,    22,    28,    23,    94,
      24,    44,    40,    -1,    -1,    12,    30,    23,    80,    24,
      45,    40,    -1,    -1,     7,    30,    23,    97,    24,    46,
      40,    -1,    -1,    19,    30,    23,    49,    24,    47,    40,
      -1,    -1,    20,    30,    29,    48,    40,    -1,    -1,    -1,
      28,    30,    23,    58,    24,    50,    49,    -1,    -1,    -1,
      28,    30,    23,    97,    24,    52,    51,    -1,    -1,     4,
      30,    29,    -1,    -1,    21,    30,    23,    97,    24,    -1,
      28,    23,    98,    24,    -1,    -1,    18,    30,    23,    95,
      24,    -1,    -1,    28,    23,    60,    24,    -1,    -1,    -1,
      23,    28,    28,    24,    59,    58,    -1,    -1,    -1,    28,
      28,    61,    60,    -1,    -1,    -1,     3,    28,    63,    23,
      60,    24,    64,    23,    65,    24,    -1,    -1,    -1,    15,
      30,    28,    66,    65,    -1,    -1,    -1,    11,    28,    23,
      67,    73,    24,    68,    65,    -1,    -1,    -1,     6,    30,
      23,    69,    71,    24,    70,    65,    -1,    -1,    -1,    28,
      72,    71,    -1,    -1,    -1,    -1,    16,    30,    23,    74,
      88,    24,    75,    73,    -1,    -1,    -1,    10,    30,    76,
      93,    77,    73,    -1,    -1,    -1,     9,    30,    78,    93,
      79,    73,    -1,    -1,    55,    -1,    -1,    55,    81,    80,
      -1,    -1,    -1,    25,    23,    82,    80,    24,    83,    80,
      -1,    -1,    -1,    26,    23,    84,    80,    24,    85,    80,
      -1,    -1,    -1,    27,    23,    86,    88,    24,    87,    80,
      -1,    -1,    55,    -1,    -1,    25,    23,    89,    80,    24,
      -1,    -1,    26,    23,    90,    80,    24,    -1,    -1,    27,
      23,    91,    88,    24,    -1,    28,    -1,    23,    94,    24,
      -1,    -1,    55,    94,    -1,    95,    57,    -1,    57,    -1,
      96,    62,    -1,    62,    -1,    -1,    97,    92,    -1,    92,
      -1,    -1,    -1,    28,    99,    98,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    76,    76,    77,    78,    77,    80,    79,    84,    86,
      87,    87,    88,    88,    89,    89,    90,    90,    91,    91,
      92,    92,    93,    93,    94,    94,    96,    97,    97,   103,
     104,   104,   107,   108,   110,   111,   116,   119,   120,   123,
     124,   127,   128,   128,   130,   131,   131,   134,   135,   134,
     139,   140,   140,   141,   142,   141,   147,   148,   147,   150,
     151,   151,   153,   154,   155,   154,   156,   157,   156,   158,
     159,   158,   169,   170,   171,   171,   172,   173,   172,   174,
     175,   174,   176,   177,   176,   180,   181,   182,   182,   184,
     184,   186,   186,   189,   192,   194,   195,   198,   199,   202,
     203,   205,   206,   207,   209,   210,   210
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ACTION_DEF", "ANNOUNCE_DEF",
  "DEFINE_DEF", "DESIGNATED_EVENTS_DEF", "DESIGNATED_WORLDS_DEF",
  "DOMAIN_DEF", "EFFECT_ADD_DEF", "EFFECT_DELETE_DEF", "EVENT_DEF",
  "GOAL_DEF", "INIT_DEF", "OBJECTS_DEF", "OWNER_DEF", "PRECONDITIONS_DEF",
  "PROBLEM_DEF", "PROPOSITIONS_DEF", "REACHAbility_DEF", "REFLEXIVITY_DEF",
  "TYPES_DEF", "WORLD_DEF", "LBRACK", "RBRACK", "AND", "OR", "NOT", "NAME",
  "TRUTH", "EQUALS", "INT", "FLOAT", "STRING", "$accept", "maepl", "$@1",
  "$@2", "$@3", "domain_body", "problem_body", "$@4", "$@5", "$@6", "$@7",
  "$@8", "$@9", "$@10", "$@11", "reachability_body", "$@12", "objects",
  "$@13", "announce_container", "types_container", "proposition_instance",
  "propositions_container", "proposition", "bracketed_input", "$@14",
  "input", "$@15", "action", "$@16", "$@17", "action_body", "$@18", "$@19",
  "$@20", "$@21", "$@22", "designated_events_body", "$@23", "event_body",
  "$@24", "$@25", "$@26", "$@27", "$@28", "$@29", "formula", "$@30",
  "$@31", "$@32", "$@33", "$@34", "$@35", "$@36", "formula_single", "$@37",
  "$@38", "$@39", "variable", "bracketed_propositions_instances",
  "proposition_instances", "propositions", "actions", "variables",
  "ordered_variables", "$@40", YY_NULL
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
     285,   286,   287,   288
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    34,    35,    36,    37,    35,    38,    35,    39,    40,
      41,    40,    42,    40,    43,    40,    44,    40,    45,    40,
      46,    40,    47,    40,    48,    40,    49,    50,    49,    51,
      52,    51,    53,    53,    54,    54,    55,    56,    56,    57,
      57,    58,    59,    58,    60,    61,    60,    63,    64,    62,
      65,    66,    65,    67,    68,    65,    69,    70,    65,    71,
      72,    71,    73,    74,    75,    73,    76,    77,    73,    78,
      79,    73,    80,    80,    81,    80,    82,    83,    80,    84,
      85,    80,    86,    87,    80,    88,    88,    89,    88,    90,
      88,    91,    88,    92,    93,    94,    94,    95,    95,    96,
      96,    97,    97,    97,    98,    99,    98
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     0,     8,     0,     7,     4,     0,
       0,     5,     0,     7,     0,     7,     0,     7,     0,     7,
       0,     7,     0,     7,     0,     5,     0,     0,     7,     0,
       0,     7,     0,     3,     0,     5,     4,     0,     5,     0,
       4,     0,     0,     6,     0,     0,     4,     0,     0,    10,
       0,     0,     5,     0,     0,     8,     0,     0,     8,     0,
       0,     3,     0,     0,     0,     8,     0,     0,     6,     0,
       0,     6,     0,     1,     0,     3,     0,     0,     7,     0,
       0,     7,     0,     0,     7,     0,     1,     0,     5,     0,
       5,     0,     5,     1,     3,     0,     2,     2,     1,     2,
       1,     0,     2,     1,     0,     0,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     0,     0,     0,     1,     3,     9,    32,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    34,     0,     0,     0,     0,     0,     0,     0,     0,
       6,     0,     4,     0,    37,   101,    10,    72,    95,    29,
      26,    24,    95,     2,    33,     2,     0,     0,     0,    93,
     103,     0,     9,     0,     0,     0,     0,    74,     0,    95,
       0,     0,     0,     0,     0,     9,     0,     7,     5,   101,
       0,     0,   100,     8,    20,   102,    11,    76,    79,    82,
     104,    72,    18,    96,    14,     0,    12,     0,    22,    25,
      16,     0,    39,    47,    99,     9,    72,    72,    85,   105,
       0,    75,     9,     9,   101,     9,    41,     9,     9,    35,
       0,    98,     0,     0,    21,     0,     0,     0,     0,     0,
      86,     0,   104,    36,    19,    15,     0,    13,     0,     0,
      23,    17,    44,    38,    97,    44,    77,    80,    87,    89,
      91,    83,   106,    30,     0,    27,     0,     0,     0,    72,
      72,    72,    72,    85,    72,    29,     0,    26,    45,    40,
      48,    78,    81,     0,     0,     0,    84,    31,    42,    28,
      44,     0,    88,    90,    92,    41,    46,    50,    43,     0,
       0,     0,     0,     0,     0,     0,    49,    56,    53,    51,
      59,    62,    50,    60,     0,     0,     0,     0,     0,    52,
      59,    57,    69,    66,     0,    54,    61,    50,     0,     0,
      63,    50,    58,    95,    70,    67,    85,    55,     0,    62,
      62,     0,    94,    71,    68,    64,    62,    65
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     9,    45,    43,    20,    18,    52,   105,   103,
     108,   102,    95,   107,    65,    64,   157,    62,   155,    21,
      34,    57,    48,   111,   129,   175,   147,   170,    72,   113,
     171,   182,   192,   191,   211,   190,   207,   194,   200,   198,
     216,   226,   209,   220,   208,   219,    58,    81,    96,   149,
      97,   150,    98,   154,   121,   151,   152,   153,    50,   214,
      60,   112,    73,    51,   100,   122
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -186
static const yytype_int16 yypact[] =
{
       3,   -14,   -13,    30,     4,     8,  -186,  -186,    25,    32,
      23,    28,    34,    45,    52,    54,    55,    26,    62,    57,
      64,    68,    53,    63,    67,    69,    70,    71,    66,    73,
    -186,    72,  -186,    74,    79,    75,  -186,    42,    77,    78,
      80,  -186,    77,     3,  -186,     3,    76,    81,    95,  -186,
    -186,   -11,    25,    84,    86,    87,    89,    90,    92,    77,
      93,    83,    94,    91,    96,    25,    98,  -186,  -186,    75,
     100,    97,  -186,    95,  -186,  -186,  -186,  -186,  -186,  -186,
      99,    42,  -186,  -186,  -186,   101,  -186,   103,  -186,  -186,
    -186,    22,   102,  -186,  -186,    25,    42,    42,    46,  -186,
     104,  -186,    25,    25,    75,    25,   106,    25,    25,  -186,
     108,  -186,    24,   109,  -186,   110,   111,   113,   114,   115,
    -186,   116,    99,  -186,  -186,  -186,    27,  -186,   105,   117,
    -186,  -186,   118,  -186,  -186,   118,  -186,  -186,  -186,  -186,
    -186,  -186,  -186,  -186,   119,  -186,   120,   121,   125,    42,
      42,    42,    42,    46,    42,    78,   126,    80,  -186,  -186,
    -186,  -186,  -186,   127,   128,   129,  -186,  -186,  -186,  -186,
     118,   131,  -186,  -186,  -186,   106,  -186,     1,  -186,   112,
     130,   132,   133,   136,   137,   135,  -186,  -186,  -186,  -186,
     138,    13,     1,  -186,   140,   139,   141,   143,   144,  -186,
     138,  -186,  -186,  -186,   142,  -186,  -186,     1,   147,   147,
    -186,     1,  -186,    77,  -186,  -186,    46,  -186,   150,    13,
      13,   152,  -186,  -186,  -186,  -186,    13,  -186
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -186,    20,  -186,  -186,  -186,  -186,   -46,  -186,  -186,  -186,
    -186,  -186,  -186,  -186,  -186,   -57,  -186,   -53,  -186,  -186,
    -186,   -38,  -186,     7,   -36,  -186,  -130,  -186,    82,  -186,
    -186,  -183,  -186,  -186,  -186,  -186,  -186,   -56,  -186,  -185,
    -186,  -186,  -186,  -186,  -186,  -186,   -71,  -186,  -186,  -186,
    -186,  -186,  -186,  -186,  -150,  -186,  -186,  -186,   -49,   -66,
     -41,  -186,  -186,   -61,    39,  -186
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -74
static const yytype_int16 yytable[] =
{
      59,    66,    75,   165,    59,   148,    76,   179,    91,   199,
     101,     1,   180,    74,     4,     5,   181,    49,    83,    89,
       2,    59,   195,   196,   212,   115,   116,     7,   217,   197,
       6,     8,    10,    11,   223,   224,    19,    12,    13,    14,
     176,   227,    75,   126,    15,    16,   109,    17,   133,   114,
      49,   143,   110,    22,    29,    49,   124,   125,    23,   127,
     120,   130,   131,    67,    24,    68,   221,    53,    54,    55,
      56,   117,   118,   119,    56,    25,    35,    75,   161,   162,
     163,   164,    26,   166,    27,    28,    30,    31,    32,    33,
      37,    36,    38,    39,    40,    41,    42,    47,    71,    69,
     169,    44,   167,    49,    46,    56,    61,    77,    63,    78,
      79,    70,    80,    85,   -73,   120,    82,    84,    86,   134,
      88,    87,    90,    92,   104,    93,   106,    99,   123,   128,
     110,   132,   135,   144,   136,   137,   138,   139,   140,   178,
     141,   145,   183,   215,   206,   159,   146,   156,   158,   160,
     168,   172,   173,   174,   177,    94,     0,   186,   184,   187,
     188,   142,   185,   189,   201,   210,   193,     0,   205,   202,
     213,   203,   218,   204,   222,    59,   225,     0,   120
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-186)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      38,    42,    51,   153,    42,   135,    52,     6,    69,   192,
      81,     8,    11,    24,    28,    28,    15,    28,    59,    65,
      17,    59,     9,    10,   207,    96,    97,    23,   211,    16,
       0,    23,     7,     8,   219,   220,     4,    12,    13,    14,
     170,   226,    91,   104,    19,    20,    24,    22,    24,    95,
      28,    24,    28,    30,    28,    28,   102,   103,    30,   105,
      98,   107,   108,    43,    30,    45,   216,    25,    26,    27,
      28,    25,    26,    27,    28,    30,    23,   126,   149,   150,
     151,   152,    30,   154,    30,    30,    24,    30,    24,    21,
      23,    28,    23,    23,    23,    29,    23,    18,     3,    23,
     157,    29,   155,    28,    30,    28,    28,    23,    28,    23,
      23,    30,    23,    30,    24,   153,    24,    24,    24,   112,
      24,    30,    24,    23,    23,    28,    23,    28,    24,    23,
      28,    23,    23,    28,    24,    24,    23,    23,    23,   175,
      24,    24,    30,   209,   200,    24,    28,    28,    28,    24,
      24,    24,    24,    24,    23,    73,    -1,    24,    28,    23,
      23,   122,    30,    28,    24,    23,    28,    -1,    24,    30,
      23,    30,   213,    30,    24,   213,    24,    -1,   216
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,    17,    35,    28,    28,     0,    23,    23,    36,
       7,     8,    12,    13,    14,    19,    20,    22,    40,     4,
      39,    53,    30,    30,    30,    30,    30,    30,    30,    28,
      24,    30,    24,    21,    54,    23,    28,    23,    23,    23,
      23,    29,    23,    38,    29,    37,    30,    18,    56,    28,
      92,    97,    41,    25,    26,    27,    28,    55,    80,    55,
      94,    28,    51,    28,    49,    48,    94,    35,    35,    23,
      30,     3,    62,    96,    24,    92,    40,    23,    23,    23,
      23,    81,    24,    94,    24,    30,    24,    30,    24,    40,
      24,    97,    23,    28,    62,    46,    82,    84,    86,    28,
      98,    80,    45,    43,    23,    42,    23,    47,    44,    24,
      28,    57,    95,    63,    40,    80,    80,    25,    26,    27,
      55,    88,    99,    24,    40,    40,    97,    40,    23,    58,
      40,    40,    23,    24,    57,    23,    24,    24,    23,    23,
      23,    24,    98,    24,    28,    24,    28,    60,    60,    83,
      85,    89,    90,    91,    87,    52,    28,    50,    28,    24,
      24,    80,    80,    80,    80,    88,    80,    51,    24,    49,
      61,    64,    24,    24,    24,    59,    60,    23,    58,     6,
      11,    15,    65,    30,    28,    30,    24,    23,    23,    28,
      69,    67,    66,    28,    71,     9,    10,    16,    73,    65,
      72,    24,    30,    30,    30,    24,    71,    70,    78,    76,
      23,    68,    65,    23,    93,    93,    74,    65,    94,    79,
      77,    88,    24,    73,    73,    24,    75,    73
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
#line 77 "maepl.y"
    { domain->new_domain(std::string((yyvsp[(2) - (3)].sval)));                                  }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 78 "maepl.y"
    { domain->finish_domain();                                              }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 80 "maepl.y"
    { if (buffer->is_reflexive()) domain->create_reflexive_reachables();
                                                                  domain->finish_problem();                                             }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 87 "maepl.y"
    { domain->set_domain((yyvsp[(3) - (3)].sval));                                               }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 88 "maepl.y"
    { domain->set_objects(buffer->get_objects());                           }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 89 "maepl.y"
    { domain->set_initial_propositions(buffer->get_proposition_instances());}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 90 "maepl.y"
    { domain->create_world((yyvsp[(2) - (5)].sval), buffer->get_proposition_instances());        }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 91 "maepl.y"
    {                                                                       }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 92 "maepl.y"
    { domain->set_designated_worlds(buffer->get_variables());               }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 93 "maepl.y"
    {                                                                       }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 94 "maepl.y"
    { buffer->set_reflexivity((yyvsp[(3) - (3)].bval));                                          }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 97 "maepl.y"
    { domain->add_reachability((yyvsp[(1) - (5)].sval), buffer->get_inputs());                   }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 104 "maepl.y"
    { buffer->set_object_type((yyvsp[(1) - (5)].sval));
                                               buffer->push_objects();                                      }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 108 "maepl.y"
    { if ((yyvsp[(3) - (3)].bval)) domain->set_announce_enabled();            }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 110 "maepl.y"
    { std::cerr << "Missing types definition\n";                   }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 112 "maepl.y"
    { buffer->push_types(); 
                                               domain->set_types(buffer->get_types());                      }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 116 "maepl.y"
    {buffer->push_proposition_instance((yyvsp[(1) - (4)].sval));                           }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 119 "maepl.y"
    { std::cerr << "Missing propositions definition\n";            }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 124 "maepl.y"
    { domain->add_proposition((yyvsp[(1) - (4)].sval), buffer->get_inputs());           }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 128 "maepl.y"
    { buffer->add_input((yyvsp[(2) - (4)].sval), (yyvsp[(3) - (4)].sval));                                   }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 131 "maepl.y"
    { buffer->add_input((yyvsp[(1) - (2)].sval), (yyvsp[(2) - (2)].sval));                                   }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 134 "maepl.y"
    { domain->new_action(std::string((yyvsp[(2) - (2)].sval)));                         }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 135 "maepl.y"
    { domain->set_action_input(buffer->get_inputs());              }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 137 "maepl.y"
    { domain->finish_action();                                     }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 140 "maepl.y"
    { domain->set_action_owner((yyvsp[(3) - (3)].sval));                                }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 141 "maepl.y"
    { buffer->set_event_name((yyvsp[(2) - (3)].sval));                                  }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 142 "maepl.y"
    { domain->create_event(                                        
                                                 buffer->get_event_name(),                                  
                                                 buffer->get_event_preconditions(),                         
                                                 buffer->get_event_add_list(),                              
                                                 buffer->get_event_delete_list());                          }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 147 "maepl.y"
    { buffer->clear_designated_events();                           }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 148 "maepl.y"
    { domain->set_designated_events(buffer->get_designated_events());}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 151 "maepl.y"
    { buffer->add_designated_event((yyvsp[(1) - (1)].sval));                            }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 154 "maepl.y"
    { buffer->clear_formula();                                     }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 155 "maepl.y"
    {                                                              }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 156 "maepl.y"
    { buffer->clear_variable_list();                               }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 157 "maepl.y"
    { buffer->push_event_delete_list();                            }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 158 "maepl.y"
    { buffer->clear_variable_list();                               }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 159 "maepl.y"
    { buffer->push_event_add_list();                               }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 170 "maepl.y"
    {buffer->push_pop_formula();                                 }
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 171 "maepl.y"
    {buffer->push_pop_formula();                                 }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 172 "maepl.y"
    {buffer->push_formula("And");                                  }
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 173 "maepl.y"
    {buffer->pop_formula();                                        }
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 174 "maepl.y"
    {buffer->push_formula("Or");                                   }
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 175 "maepl.y"
    {buffer->pop_formula();                                        }
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 176 "maepl.y"
    {buffer->push_formula("Not");                                  }
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 177 "maepl.y"
    {buffer->pop_formula();                                        }
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 181 "maepl.y"
    {buffer->push_pop_formula();                                 }
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 182 "maepl.y"
    {buffer->push_formula("And");                                  }
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 183 "maepl.y"
    {buffer->pop_formula();                                        }
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 184 "maepl.y"
    {buffer->push_formula("Or");                                   }
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 185 "maepl.y"
    {buffer->pop_formula();                                        }
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 186 "maepl.y"
    {buffer->push_formula("Not");                                  }
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 187 "maepl.y"
    {buffer->pop_formula();                                        }
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 189 "maepl.y"
    { buffer->add_variable((yyvsp[(1) - (1)].sval));                                    }
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 210 "maepl.y"
    {buffer->add_ordered_variable((yyvsp[(1) - (1)].sval));                               }
    break;


/* Line 1792 of yacc.c  */
#line 1906 "maepl.tab.cpp"
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
#line 211 "maepl.y"


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
