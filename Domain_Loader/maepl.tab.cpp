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
#define YYLAST   183

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  67
/* YYNRULES -- Number of rules.  */
#define YYNRULES  108
/* YYNRULES -- Number of states.  */
#define YYNSTATES  235

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
       0,     0,     3,     4,     5,     6,    15,    16,    24,    25,
      31,    32,    38,    42,    43,    44,    50,    51,    59,    60,
      68,    69,    77,    78,    86,    87,    95,    96,   104,   105,
     111,   112,   113,   121,   122,   123,   131,   132,   138,   143,
     144,   150,   151,   156,   157,   158,   165,   166,   167,   172,
     173,   174,   185,   186,   187,   194,   195,   196,   205,   206,
     207,   216,   217,   218,   222,   223,   224,   225,   234,   235,
     236,   243,   244,   245,   252,   253,   255,   256,   260,   261,
     262,   270,   271,   272,   280,   281,   282,   290,   291,   293,
     294,   300,   301,   307,   308,   314,   316,   320,   321,   324,
     327,   329,   332,   334,   335,   338,   340,   341,   342
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      35,     0,    -1,    -1,    -1,    -1,     8,    28,    23,    36,
      39,    24,    37,    35,    -1,    -1,    17,    28,    23,    42,
      24,    38,    35,    -1,    -1,    20,    30,    29,    40,    39,
      -1,    -1,     4,    30,    29,    41,    39,    -1,    55,    57,
      97,    -1,    -1,    -1,     8,    30,    28,    43,    42,    -1,
      -1,    14,    30,    23,    53,    24,    44,    42,    -1,    -1,
      13,    30,    23,    95,    24,    45,    42,    -1,    -1,    22,
      28,    23,    95,    24,    46,    42,    -1,    -1,    12,    30,
      23,    81,    24,    47,    42,    -1,    -1,     7,    30,    23,
      98,    24,    48,    42,    -1,    -1,    19,    30,    23,    51,
      24,    49,    42,    -1,    -1,    20,    30,    29,    50,    42,
      -1,    -1,    -1,    28,    30,    23,    59,    24,    52,    51,
      -1,    -1,    -1,    28,    30,    23,    98,    24,    54,    53,
      -1,    -1,    21,    30,    23,    98,    24,    -1,    28,    23,
      99,    24,    -1,    -1,    18,    30,    23,    96,    24,    -1,
      -1,    28,    23,    61,    24,    -1,    -1,    -1,    23,    28,
      28,    24,    60,    59,    -1,    -1,    -1,    28,    28,    62,
      61,    -1,    -1,    -1,     3,    28,    64,    23,    61,    24,
      65,    23,    66,    24,    -1,    -1,    -1,    15,    30,    28,
      28,    67,    66,    -1,    -1,    -1,    11,    28,    23,    68,
      74,    24,    69,    66,    -1,    -1,    -1,     6,    30,    23,
      70,    72,    24,    71,    66,    -1,    -1,    -1,    28,    73,
      72,    -1,    -1,    -1,    -1,    16,    30,    23,    75,    89,
      24,    76,    74,    -1,    -1,    -1,    10,    30,    77,    94,
      78,    74,    -1,    -1,    -1,     9,    30,    79,    94,    80,
      74,    -1,    -1,    56,    -1,    -1,    56,    82,    81,    -1,
      -1,    -1,    25,    23,    83,    81,    24,    84,    81,    -1,
      -1,    -1,    26,    23,    85,    81,    24,    86,    81,    -1,
      -1,    -1,    27,    23,    87,    89,    24,    88,    81,    -1,
      -1,    56,    -1,    -1,    25,    23,    90,    81,    24,    -1,
      -1,    26,    23,    91,    81,    24,    -1,    -1,    27,    23,
      92,    89,    24,    -1,    28,    -1,    23,    95,    24,    -1,
      -1,    56,    95,    -1,    96,    58,    -1,    58,    -1,    97,
      63,    -1,    63,    -1,    -1,    98,    93,    -1,    93,    -1,
      -1,    -1,    28,   100,    99,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    76,    76,    77,    78,    77,    81,    80,    85,    85,
      86,    86,    87,    89,    90,    90,    91,    91,    92,    92,
      93,    93,    94,    94,    95,    95,    96,    96,    97,    97,
      99,   100,   100,   103,   104,   104,   107,   108,   113,   116,
     117,   120,   121,   124,   125,   125,   127,   128,   128,   131,
     132,   131,   136,   137,   137,   138,   139,   138,   144,   145,
     144,   147,   148,   148,   150,   151,   152,   151,   153,   154,
     153,   155,   156,   155,   166,   167,   168,   168,   169,   170,
     169,   171,   172,   171,   173,   174,   173,   177,   178,   179,
     179,   181,   181,   183,   183,   186,   189,   191,   192,   195,
     196,   199,   200,   202,   203,   204,   206,   207,   207
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
  "$@2", "$@3", "domain_body", "$@4", "$@5", "problem_body", "$@6", "$@7",
  "$@8", "$@9", "$@10", "$@11", "$@12", "$@13", "reachability_body",
  "$@14", "objects", "$@15", "types_container", "proposition_instance",
  "propositions_container", "proposition", "bracketed_input", "$@16",
  "input", "$@17", "action", "$@18", "$@19", "action_body", "$@20", "$@21",
  "$@22", "$@23", "$@24", "designated_events_body", "$@25", "event_body",
  "$@26", "$@27", "$@28", "$@29", "$@30", "$@31", "formula", "$@32",
  "$@33", "$@34", "$@35", "$@36", "$@37", "$@38", "formula_single", "$@39",
  "$@40", "$@41", "variable", "bracketed_propositions_instances",
  "proposition_instances", "propositions", "actions", "variables",
  "ordered_variables", "$@42", YY_NULL
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
       0,    34,    35,    36,    37,    35,    38,    35,    40,    39,
      41,    39,    39,    42,    43,    42,    44,    42,    45,    42,
      46,    42,    47,    42,    48,    42,    49,    42,    50,    42,
      51,    52,    51,    53,    54,    53,    55,    55,    56,    57,
      57,    58,    58,    59,    60,    59,    61,    62,    61,    64,
      65,    63,    66,    67,    66,    68,    69,    66,    70,    71,
      66,    72,    73,    72,    74,    75,    76,    74,    77,    78,
      74,    79,    80,    74,    81,    81,    82,    81,    83,    84,
      81,    85,    86,    81,    87,    88,    81,    89,    89,    90,
      89,    91,    89,    92,    89,    93,    94,    95,    95,    96,
      96,    97,    97,    98,    98,    98,    99,   100,    99
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     0,     8,     0,     7,     0,     5,
       0,     5,     3,     0,     0,     5,     0,     7,     0,     7,
       0,     7,     0,     7,     0,     7,     0,     7,     0,     5,
       0,     0,     7,     0,     0,     7,     0,     5,     4,     0,
       5,     0,     4,     0,     0,     6,     0,     0,     4,     0,
       0,    10,     0,     0,     6,     0,     0,     8,     0,     0,
       8,     0,     0,     3,     0,     0,     0,     8,     0,     0,
       6,     0,     0,     6,     0,     1,     0,     3,     0,     0,
       7,     0,     0,     7,     0,     0,     7,     0,     1,     0,
       5,     0,     5,     0,     5,     1,     3,     0,     2,     2,
       1,     2,     1,     0,     2,     1,     0,     0,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     0,     0,     0,     1,     3,    13,    36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    39,     0,     0,     0,     0,     0,     0,
       0,     0,     6,     0,     0,     0,     4,     0,     0,   103,
      14,    74,    97,    33,    30,    28,    97,     2,    10,     8,
     103,     2,     0,     0,   102,    12,    95,   105,     0,    13,
       0,     0,     0,     0,    76,     0,    97,     0,     0,     0,
       0,     0,    13,     0,     7,    36,    36,     0,     5,    41,
      49,   101,    24,   104,    15,    78,    81,    84,   106,    74,
      22,    98,    18,     0,    16,     0,    26,    29,    20,    11,
       9,    37,     0,   100,     0,     0,    13,    74,    74,    87,
     107,     0,    77,    13,    13,   103,    13,    43,    13,    13,
      46,    40,    99,    46,    25,     0,     0,     0,     0,     0,
      88,     0,   106,    38,    23,    19,     0,    17,     0,     0,
      27,    21,     0,     0,     0,    79,    82,    89,    91,    93,
      85,   108,    34,     0,    31,    47,    42,    50,    74,    74,
      74,    74,    87,    74,    33,     0,    30,    46,     0,    80,
      83,     0,     0,     0,    86,    35,    44,    32,    48,    52,
      90,    92,    94,    43,     0,     0,     0,     0,    45,     0,
       0,     0,    51,    58,    55,     0,    61,    64,    53,    62,
       0,     0,     0,     0,     0,    52,    61,    59,    71,    68,
       0,    56,    54,    63,    52,     0,     0,    65,    52,    60,
      97,    72,    69,    87,    57,     0,    64,    64,     0,    96,
      73,    70,    66,    64,    67
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     9,    51,    47,    22,    76,    75,    18,    59,
     116,   114,   119,   113,   106,   118,    72,    71,   166,    69,
     164,    23,    64,    38,   103,   139,   183,   143,   167,    54,
     105,   168,   187,   205,   197,   218,   196,   214,   200,   206,
     204,   223,   233,   216,   227,   215,   226,    65,    89,   107,
     158,   108,   159,   109,   163,   131,   160,   161,   162,    57,
     221,    67,   104,    55,    58,   111,   132
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -196
static const yytype_int16 yypact[] =
{
      17,   -11,     4,    38,    10,    18,  -196,  -196,    23,     8,
      14,    20,    26,    28,    39,    57,    59,    27,    64,    60,
      61,    62,    69,    76,    72,    68,    74,    75,    77,    78,
      70,    79,  -196,    80,    81,    82,  -196,    73,   101,    83,
    -196,    48,    84,    85,    86,  -196,    84,    17,  -196,  -196,
      83,    17,    92,    88,  -196,   101,  -196,  -196,   -15,    23,
      94,    95,    96,    98,    99,   100,    84,   102,    97,   104,
     103,   105,    23,   106,  -196,     8,     8,    25,  -196,   107,
    -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,   108,    48,
    -196,  -196,  -196,   109,  -196,   111,  -196,  -196,  -196,  -196,
    -196,  -196,   114,  -196,    33,   115,    23,    48,    48,    58,
    -196,   116,  -196,    23,    23,    83,    23,   118,    23,    23,
     117,  -196,  -196,   117,  -196,   119,   120,   123,   124,   125,
    -196,   126,   108,  -196,  -196,  -196,    42,  -196,   121,   127,
    -196,  -196,   128,   129,   130,  -196,  -196,  -196,  -196,  -196,
    -196,  -196,  -196,   131,  -196,  -196,  -196,  -196,    48,    48,
      48,    48,    58,    48,    85,   133,    86,   117,   132,  -196,
    -196,   134,   136,   137,  -196,  -196,  -196,  -196,  -196,     5,
    -196,  -196,  -196,   118,   112,   135,   122,   138,  -196,   141,
     142,   139,  -196,  -196,  -196,   140,   143,    30,  -196,  -196,
     145,   144,   146,   147,   148,     5,   143,  -196,  -196,  -196,
     150,  -196,  -196,  -196,     5,   156,   156,  -196,     5,  -196,
      84,  -196,  -196,    58,  -196,   158,    30,    30,   159,  -196,
    -196,  -196,  -196,    30,  -196
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -196,    21,  -196,  -196,  -196,   -61,  -196,  -196,   -54,  -196,
    -196,  -196,  -196,  -196,  -196,  -196,  -196,   -60,  -196,   -57,
    -196,  -196,   -42,  -196,    35,   -75,  -196,  -116,  -196,    67,
    -196,  -196,  -195,  -196,  -196,  -196,  -196,  -196,   -40,  -196,
    -179,  -196,  -196,  -196,  -196,  -196,  -196,   -81,  -196,  -196,
    -196,  -196,  -196,  -196,  -196,  -160,  -196,  -196,  -196,   -55,
     -91,   -45,  -196,  -196,   -44,    -1,  -196
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -76
static const yytype_int16 yytable[] =
{
      66,    73,   173,    83,    66,    84,    77,   144,   112,    82,
     212,   184,    19,    56,    99,   100,   185,     4,    97,   219,
     186,    91,    83,   224,    66,     1,   125,   126,    20,    21,
      10,    11,     5,     7,     2,    12,    13,    14,     6,   201,
     202,     8,    15,    16,    24,    17,   203,   230,   231,   101,
      25,   178,   124,    56,   234,    31,    26,   121,    27,   134,
     135,   102,   137,   228,   140,   141,   152,   130,    74,    28,
      56,   136,    78,    60,    61,    62,    63,   169,   170,   171,
     172,    83,   174,   127,   128,   129,    63,    29,    32,    30,
      33,    34,    35,    36,    37,    39,    40,    41,    42,    45,
      43,    44,    46,    52,    53,    50,   177,   175,   188,    48,
      49,    56,    63,    68,    70,    79,    80,    85,    86,    87,
     130,    88,    81,   -75,    90,   222,    92,    93,    94,    96,
      98,   151,   115,    95,   117,   102,   110,   120,   123,   122,
     133,   138,   189,   145,   146,   142,   147,   148,   149,   153,
     150,   154,   191,   156,   157,   179,   155,   176,   180,   165,
     181,   182,   192,   190,   193,   194,   213,   195,   198,   207,
       0,   199,   211,   217,   208,   225,   209,   210,    66,   220,
       0,   130,   229,   232
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-196)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      42,    46,   162,    58,    46,    59,    50,   123,    89,    24,
     205,     6,     4,    28,    75,    76,    11,    28,    72,   214,
      15,    66,    77,   218,    66,     8,   107,   108,    20,    21,
       7,     8,    28,    23,    17,    12,    13,    14,     0,     9,
      10,    23,    19,    20,    30,    22,    16,   226,   227,    24,
      30,   167,   106,    28,   233,    28,    30,    24,    30,   113,
     114,    28,   116,   223,   118,   119,    24,   109,    47,    30,
      28,   115,    51,    25,    26,    27,    28,   158,   159,   160,
     161,   136,   163,    25,    26,    27,    28,    30,    24,    30,
      30,    30,    30,    24,    18,    23,    28,    23,    23,    29,
      23,    23,    23,    30,     3,    23,   166,   164,   183,    29,
      29,    28,    28,    28,    28,    23,    28,    23,    23,    23,
     162,    23,    55,    24,    24,   216,    24,    30,    24,    24,
      24,   132,    23,    30,    23,    28,    28,    23,    23,   104,
      24,    23,    30,    24,    24,    28,    23,    23,    23,    28,
      24,    24,    30,    24,    24,    23,    28,    24,    24,    28,
      24,    24,    24,    28,    23,    23,   206,    28,    28,    24,
      -1,    28,    24,    23,    30,   220,    30,    30,   220,    23,
      -1,   223,    24,    24
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,    17,    35,    28,    28,     0,    23,    23,    36,
       7,     8,    12,    13,    14,    19,    20,    22,    42,     4,
      20,    21,    39,    55,    30,    30,    30,    30,    30,    30,
      30,    28,    24,    30,    30,    30,    24,    18,    57,    23,
      28,    23,    23,    23,    23,    29,    23,    38,    29,    29,
      23,    37,    30,     3,    63,    97,    28,    93,    98,    43,
      25,    26,    27,    28,    56,    81,    56,    95,    28,    53,
      28,    51,    50,    95,    35,    41,    40,    98,    35,    23,
      28,    63,    24,    93,    42,    23,    23,    23,    23,    82,
      24,    95,    24,    30,    24,    30,    24,    42,    24,    39,
      39,    24,    28,    58,    96,    64,    48,    83,    85,    87,
      28,    99,    81,    47,    45,    23,    44,    23,    49,    46,
      23,    24,    58,    23,    42,    81,    81,    25,    26,    27,
      56,    89,   100,    24,    42,    42,    98,    42,    23,    59,
      42,    42,    28,    61,    61,    24,    24,    23,    23,    23,
      24,    99,    24,    28,    24,    28,    24,    24,    84,    86,
      90,    91,    92,    88,    54,    28,    52,    62,    65,    81,
      81,    81,    81,    89,    81,    53,    24,    51,    61,    23,
      24,    24,    24,    60,     6,    11,    15,    66,    59,    30,
      28,    30,    24,    23,    23,    28,    70,    68,    28,    28,
      72,     9,    10,    16,    74,    67,    73,    24,    30,    30,
      30,    24,    66,    72,    71,    79,    77,    23,    69,    66,
      23,    94,    94,    75,    66,    95,    80,    78,    89,    24,
      74,    74,    24,    76,    74
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
    { if (buffer->is_action_reflexive()) domain->create_action_reflexive_reachables();
                                                                    domain->finish_domain();                                              }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 81 "maepl.y"
    { if (buffer->is_state_reflexive()) domain->create_state_reflexive_reachables();
                                                                  domain->finish_problem();                                             }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 85 "maepl.y"
    { buffer->set_action_reflexivity((yyvsp[(3) - (3)].bval));                                   }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 86 "maepl.y"
    { if ((yyvsp[(3) - (3)].bval)) domain->set_announce_enabled();                               }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 90 "maepl.y"
    { domain->set_domain((yyvsp[(3) - (3)].sval));                                               }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 91 "maepl.y"
    { domain->set_objects(buffer->get_objects());                           }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 92 "maepl.y"
    { domain->set_initial_propositions(buffer->get_proposition_instances());}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 93 "maepl.y"
    { domain->create_world((yyvsp[(2) - (5)].sval), buffer->get_proposition_instances());        }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 94 "maepl.y"
    { domain->set_goal(buffer->get_formula());                              }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 95 "maepl.y"
    { domain->set_designated_worlds(buffer->get_variables());               }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 96 "maepl.y"
    {                                                                       }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 97 "maepl.y"
    { buffer->set_state_reflexivity((yyvsp[(3) - (3)].bval));                                    }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 100 "maepl.y"
    { domain->add_reachability((yyvsp[(1) - (5)].sval), buffer->get_inputs());                   }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 104 "maepl.y"
    { buffer->set_object_type((yyvsp[(1) - (5)].sval));
                                               buffer->push_objects();                                      }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 107 "maepl.y"
    { std::cerr << "Missing types definition\n";                   }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 109 "maepl.y"
    { buffer->push_types(); 
                                               domain->set_types(buffer->get_types());                      }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 113 "maepl.y"
    {buffer->push_proposition_instance((yyvsp[(1) - (4)].sval));                           }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 116 "maepl.y"
    { std::cerr << "Missing propositions definition\n";            }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 121 "maepl.y"
    { domain->add_proposition((yyvsp[(1) - (4)].sval), buffer->get_inputs());           }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 125 "maepl.y"
    { buffer->add_input((yyvsp[(2) - (4)].sval), (yyvsp[(3) - (4)].sval));                                   }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 128 "maepl.y"
    { buffer->add_input((yyvsp[(1) - (2)].sval), (yyvsp[(2) - (2)].sval));                                   }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 131 "maepl.y"
    { domain->new_action(std::string((yyvsp[(2) - (2)].sval)));                         }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 132 "maepl.y"
    { domain->set_action_input(buffer->get_inputs());              }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 134 "maepl.y"
    { domain->finish_action();                                     }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 137 "maepl.y"
    { domain->set_action_owner((yyvsp[(3) - (4)].sval), (yyvsp[(4) - (4)].sval));                            }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 138 "maepl.y"
    { buffer->set_event_name((yyvsp[(2) - (3)].sval));                                  }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 139 "maepl.y"
    { domain->create_event(                                        
                                                 buffer->get_event_name(),                                  
                                                 buffer->get_formula(),                         
                                                 buffer->get_event_add_list(),                              
                                                 buffer->get_event_delete_list());                          }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 144 "maepl.y"
    { buffer->clear_designated_events();                           }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 145 "maepl.y"
    { domain->set_designated_events(buffer->get_designated_events());}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 148 "maepl.y"
    { buffer->add_designated_event((yyvsp[(1) - (1)].sval));                            }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 151 "maepl.y"
    { buffer->clear_formula();                                     }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 152 "maepl.y"
    {                                                              }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 153 "maepl.y"
    { buffer->clear_variable_list();                               }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 154 "maepl.y"
    { buffer->push_event_delete_list();                            }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 155 "maepl.y"
    { buffer->clear_variable_list();                               }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 156 "maepl.y"
    { buffer->push_event_add_list();                               }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 167 "maepl.y"
    {buffer->push_pop_formula();                                 }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 168 "maepl.y"
    {buffer->push_pop_formula();                                 }
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 169 "maepl.y"
    {buffer->push_formula("And");                                  }
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 170 "maepl.y"
    {buffer->pop_formula();                                        }
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 171 "maepl.y"
    {buffer->push_formula("Or");                                   }
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 172 "maepl.y"
    {buffer->pop_formula();                                        }
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 173 "maepl.y"
    {buffer->push_formula("Not");                                  }
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 174 "maepl.y"
    {buffer->pop_formula();                                        }
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 178 "maepl.y"
    {buffer->push_pop_formula();                                 }
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 179 "maepl.y"
    {buffer->push_formula("And");                                  }
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 180 "maepl.y"
    {buffer->pop_formula();                                        }
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 181 "maepl.y"
    {buffer->push_formula("Or");                                   }
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 182 "maepl.y"
    {buffer->pop_formula();                                        }
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 183 "maepl.y"
    {buffer->push_formula("Not");                                  }
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 184 "maepl.y"
    {buffer->pop_formula();                                        }
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 186 "maepl.y"
    { buffer->add_variable((yyvsp[(1) - (1)].sval));                                    }
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 207 "maepl.y"
    {buffer->add_ordered_variable((yyvsp[(1) - (1)].sval));                               }
    break;


/* Line 1792 of yacc.c  */
#line 1919 "maepl.tab.cpp"
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
#line 208 "maepl.y"


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
