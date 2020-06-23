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
     OBSERVABILITY_DEF = 270,
     OWNER_DEF = 271,
     PERCEIVABILITY_DEF = 272,
     PRECONDITIONS_DEF = 273,
     PROBLEM_DEF = 274,
     PROPOSITIONS_DEF = 275,
     REACHAbility_DEF = 276,
     REFLEXIVITY_DEF = 277,
     TYPES_DEF = 278,
     WORLD_DEF = 279,
     LBRACK = 280,
     RBRACK = 281,
     AND = 282,
     OR = 283,
     NOT = 284,
     NAME = 285,
     TRUTH = 286,
     EQUALS = 287,
     INT = 288,
     FLOAT = 289,
     STRING = 290
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
#line 173 "maepl.tab.cpp"
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
#line 201 "maepl.tab.cpp"

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
#define YYLAST   205

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  73
/* YYNRULES -- Number of rules.  */
#define YYNRULES  118
/* YYNRULES -- Number of states.  */
#define YYNSTATES  263

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     5,     6,    15,    16,    24,    25,
      31,    32,    38,    42,    43,    44,    50,    51,    59,    60,
      68,    69,    77,    78,    86,    87,    95,    96,   104,   105,
     111,   112,   120,   121,   129,   130,   131,   139,   140,   141,
     149,   150,   151,   159,   160,   161,   169,   170,   176,   181,
     182,   188,   189,   194,   195,   196,   203,   204,   205,   210,
     211,   212,   223,   224,   225,   232,   233,   234,   243,   244,
     245,   254,   255,   256,   260,   261,   262,   263,   272,   273,
     274,   281,   282,   283,   290,   291,   293,   294,   298,   299,
     300,   308,   309,   310,   318,   319,   320,   328,   329,   331,
     332,   338,   339,   345,   346,   352,   354,   358,   359,   362,
     365,   367,   370,   372,   373,   376,   378,   379,   380
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      37,     0,    -1,    -1,    -1,    -1,     8,    30,    25,    38,
      41,    26,    39,    37,    -1,    -1,    19,    30,    25,    44,
      26,    40,    37,    -1,    -1,    22,    32,    31,    42,    41,
      -1,    -1,     4,    32,    31,    43,    41,    -1,    63,    65,
     105,    -1,    -1,    -1,     8,    32,    30,    45,    44,    -1,
      -1,    14,    32,    25,    61,    26,    46,    44,    -1,    -1,
      13,    32,    25,   103,    26,    47,    44,    -1,    -1,    24,
      30,    25,   103,    26,    48,    44,    -1,    -1,    12,    32,
      25,    89,    26,    49,    44,    -1,    -1,     7,    32,    25,
     106,    26,    50,    44,    -1,    -1,    21,    32,    25,    55,
      26,    51,    44,    -1,    -1,    22,    32,    31,    52,    44,
      -1,    -1,    17,    32,    25,    57,    26,    53,    44,    -1,
      -1,    15,    32,    25,    59,    26,    54,    44,    -1,    -1,
      -1,    30,    32,    25,    67,    26,    56,    55,    -1,    -1,
      -1,    30,    32,    25,   107,    26,    58,    57,    -1,    -1,
      -1,    30,    32,    25,   107,    26,    60,    59,    -1,    -1,
      -1,    30,    32,    25,   106,    26,    62,    61,    -1,    -1,
      23,    32,    25,   106,    26,    -1,    30,    25,   107,    26,
      -1,    -1,    20,    32,    25,   104,    26,    -1,    -1,    30,
      25,    69,    26,    -1,    -1,    -1,    25,    30,    30,    26,
      68,    67,    -1,    -1,    -1,    30,    30,    70,    69,    -1,
      -1,    -1,     3,    30,    72,    25,    69,    26,    73,    25,
      74,    26,    -1,    -1,    -1,    16,    32,    30,    30,    75,
      74,    -1,    -1,    -1,    11,    30,    25,    76,    82,    26,
      77,    74,    -1,    -1,    -1,     6,    32,    25,    78,    80,
      26,    79,    74,    -1,    -1,    -1,    30,    81,    80,    -1,
      -1,    -1,    -1,    18,    32,    25,    83,    97,    26,    84,
      82,    -1,    -1,    -1,    10,    32,    85,   102,    86,    82,
      -1,    -1,    -1,     9,    32,    87,   102,    88,    82,    -1,
      -1,    64,    -1,    -1,    64,    90,    89,    -1,    -1,    -1,
      27,    25,    91,    89,    26,    92,    89,    -1,    -1,    -1,
      28,    25,    93,    89,    26,    94,    89,    -1,    -1,    -1,
      29,    25,    95,    97,    26,    96,    89,    -1,    -1,    64,
      -1,    -1,    27,    25,    98,    89,    26,    -1,    -1,    28,
      25,    99,    89,    26,    -1,    -1,    29,    25,   100,    97,
      26,    -1,    30,    -1,    25,   103,    26,    -1,    -1,    64,
     103,    -1,   104,    66,    -1,    66,    -1,   105,    71,    -1,
      71,    -1,    -1,   106,   101,    -1,   101,    -1,    -1,    -1,
      30,   108,   107,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    78,    78,    79,    80,    79,    83,    82,    90,    90,
      91,    91,    92,    94,    95,    95,    96,    96,    97,    97,
      98,    98,    99,    99,   100,   100,   101,   101,   102,   102,
     103,   103,   104,   104,   106,   107,   107,   109,   110,   110,
     114,   115,   115,   118,   119,   119,   122,   123,   128,   131,
     132,   135,   136,   139,   140,   140,   142,   143,   143,   146,
     147,   146,   151,   152,   152,   153,   154,   153,   159,   160,
     159,   162,   163,   163,   165,   166,   167,   166,   168,   169,
     168,   170,   171,   170,   181,   182,   183,   183,   184,   185,
     184,   186,   187,   186,   188,   189,   188,   192,   193,   194,
     194,   196,   196,   198,   198,   201,   204,   206,   207,   210,
     211,   214,   215,   217,   218,   219,   221,   222,   222
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
  "GOAL_DEF", "INIT_DEF", "OBJECTS_DEF", "OBSERVABILITY_DEF", "OWNER_DEF",
  "PERCEIVABILITY_DEF", "PRECONDITIONS_DEF", "PROBLEM_DEF",
  "PROPOSITIONS_DEF", "REACHAbility_DEF", "REFLEXIVITY_DEF", "TYPES_DEF",
  "WORLD_DEF", "LBRACK", "RBRACK", "AND", "OR", "NOT", "NAME", "TRUTH",
  "EQUALS", "INT", "FLOAT", "STRING", "$accept", "maepl", "$@1", "$@2",
  "$@3", "domain_body", "$@4", "$@5", "problem_body", "$@6", "$@7", "$@8",
  "$@9", "$@10", "$@11", "$@12", "$@13", "$@14", "$@15",
  "reachability_body", "$@16", "perceivability_body", "$@17",
  "observability_body", "$@18", "objects", "$@19", "types_container",
  "proposition_instance", "propositions_container", "proposition",
  "bracketed_input", "$@20", "input", "$@21", "action", "$@22", "$@23",
  "action_body", "$@24", "$@25", "$@26", "$@27", "$@28",
  "designated_events_body", "$@29", "event_body", "$@30", "$@31", "$@32",
  "$@33", "$@34", "$@35", "formula", "$@36", "$@37", "$@38", "$@39",
  "$@40", "$@41", "$@42", "formula_single", "$@43", "$@44", "$@45",
  "variable", "bracketed_propositions_instances", "proposition_instances",
  "propositions", "actions", "variables", "ordered_variables", "$@46", YY_NULL
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
     285,   286,   287,   288,   289,   290
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    37,    38,    39,    37,    40,    37,    42,    41,
      43,    41,    41,    44,    45,    44,    46,    44,    47,    44,
      48,    44,    49,    44,    50,    44,    51,    44,    52,    44,
      53,    44,    54,    44,    55,    56,    55,    57,    58,    57,
      59,    60,    59,    61,    62,    61,    63,    63,    64,    65,
      65,    66,    66,    67,    68,    67,    69,    70,    69,    72,
      73,    71,    74,    75,    74,    76,    77,    74,    78,    79,
      74,    80,    81,    80,    82,    83,    84,    82,    85,    86,
      82,    87,    88,    82,    89,    89,    90,    89,    91,    92,
      89,    93,    94,    89,    95,    96,    89,    97,    97,    98,
      97,    99,    97,   100,    97,   101,   102,   103,   103,   104,
     104,   105,   105,   106,   106,   106,   107,   108,   107
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     0,     8,     0,     7,     0,     5,
       0,     5,     3,     0,     0,     5,     0,     7,     0,     7,
       0,     7,     0,     7,     0,     7,     0,     7,     0,     5,
       0,     7,     0,     7,     0,     0,     7,     0,     0,     7,
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
       2,     0,     0,     0,     0,     0,     1,     3,    13,    46,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,     0,     0,     0,
       4,     0,     0,   113,    14,    84,   107,    43,    40,    37,
      34,    28,   107,     2,    10,     8,   113,     2,     0,     0,
     112,    12,   105,   115,     0,    13,     0,     0,     0,     0,
      86,     0,   107,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    13,     0,     7,    46,    46,     0,     5,    51,
      59,   111,    24,   114,    15,    88,    91,    94,   116,    84,
      22,   108,    18,     0,    16,     0,    32,     0,    30,     0,
      26,    29,    20,    11,     9,    47,     0,   110,     0,     0,
      13,    84,    84,    97,   117,     0,    87,    13,    13,   113,
      13,   116,    13,   116,    13,    53,    13,    13,    56,    50,
     109,    56,    25,     0,     0,     0,     0,     0,    98,     0,
     116,    48,    23,    19,     0,    17,     0,    33,     0,    31,
       0,     0,    27,    21,     0,     0,     0,    89,    92,    99,
     101,   103,    95,   118,    44,    41,    38,     0,    35,    57,
      52,    60,    84,    84,    84,    84,    97,    84,    43,    40,
      37,     0,    34,    56,     0,    90,    93,     0,     0,     0,
      96,    45,    42,    39,    54,    36,    58,    62,   100,   102,
     104,    53,     0,     0,     0,     0,    55,     0,     0,     0,
      61,    68,    65,     0,    71,    74,    63,    72,     0,     0,
       0,     0,     0,    62,    71,    69,    81,    78,     0,    66,
      64,    73,    62,     0,     0,    75,    62,    70,   107,    82,
      79,    97,    67,     0,    74,    74,     0,   106,    83,    80,
      76,    74,    77
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     9,    57,    53,    24,    86,    85,    20,    65,
     130,   128,   137,   127,   120,   136,    82,   134,   132,    81,
     192,    79,   190,    77,   189,    75,   188,    25,    70,    42,
     117,   161,   211,   165,   193,    60,   119,   194,   215,   233,
     225,   246,   224,   242,   228,   234,   232,   251,   261,   244,
     255,   243,   254,    71,    99,   121,   182,   122,   183,   123,
     187,   149,   184,   185,   186,    63,   249,    73,   118,    61,
      64,   125,   150
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -239
static const yytype_int16 yypact[] =
{
       0,   -17,    -6,    35,    19,    32,  -239,  -239,    26,     7,
      20,    21,    34,    36,    42,    50,    52,    53,    54,    37,
      38,    64,    66,    68,    49,    63,    77,    75,    81,    82,
      83,    84,    85,    86,    87,    88,  -239,    89,    90,    91,
    -239,    80,   111,    92,  -239,    43,    93,    94,    95,    96,
      97,  -239,    93,     0,  -239,  -239,    92,     0,   103,    99,
    -239,   111,  -239,  -239,    16,    26,   105,   106,   107,   108,
     109,   110,    93,   112,   102,   113,   114,   115,   116,   117,
     118,   119,    26,   121,  -239,     7,     7,    25,  -239,   122,
    -239,  -239,  -239,  -239,  -239,  -239,  -239,  -239,   123,    43,
    -239,  -239,  -239,   124,  -239,   126,  -239,   129,  -239,   130,
    -239,  -239,  -239,  -239,  -239,  -239,   131,  -239,    28,   132,
      26,    43,    43,    51,  -239,   133,  -239,    26,    26,    92,
      26,   123,    26,   123,    26,   135,    26,    26,   128,  -239,
    -239,   128,  -239,   136,   137,   139,   140,   141,  -239,   142,
     123,  -239,  -239,  -239,    30,  -239,   143,  -239,   144,  -239,
     145,   146,  -239,  -239,   147,   148,   150,  -239,  -239,  -239,
    -239,  -239,  -239,  -239,  -239,  -239,  -239,   149,  -239,  -239,
    -239,  -239,    43,    43,    43,    43,    51,    43,    94,    95,
      96,   152,    97,   128,   155,  -239,  -239,   156,   157,   158,
    -239,  -239,  -239,  -239,  -239,  -239,  -239,     4,  -239,  -239,
    -239,   135,   153,   151,   154,   161,  -239,   163,   164,   160,
    -239,  -239,  -239,   162,   165,    27,  -239,  -239,   167,   159,
     166,   168,   170,     4,   165,  -239,  -239,  -239,   169,  -239,
    -239,  -239,     4,   174,   174,  -239,     4,  -239,    93,  -239,
    -239,    51,  -239,   175,    27,    27,   177,  -239,  -239,  -239,
    -239,    27,  -239
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -239,     8,  -239,  -239,  -239,   -23,  -239,  -239,   -33,  -239,
    -239,  -239,  -239,  -239,  -239,  -239,  -239,  -239,  -239,   -77,
    -239,   -73,  -239,   -70,  -239,   -44,  -239,  -239,   -46,  -239,
      24,   -74,  -239,  -134,  -239,   100,  -239,  -239,  -224,  -239,
    -239,  -239,  -239,  -239,   -67,  -239,  -238,  -239,  -239,  -239,
    -239,  -239,  -239,   -94,  -239,  -239,  -239,  -239,  -239,  -239,
    -239,  -182,  -239,  -239,  -239,   -62,   -71,   -51,  -239,  -239,
     -53,  -119,  -239
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -86
static const yytype_int16 yytable[] =
{
      72,    83,    93,    87,   199,   126,    72,   166,     1,   240,
     212,    21,   156,     4,   158,   213,   258,   259,   247,     2,
     214,   101,   252,   262,     5,    93,    72,   143,   144,    22,
      23,   173,    94,    10,    11,     6,   229,   230,    12,    13,
      14,    15,    92,    16,     7,   231,    62,    17,    18,   111,
      19,   115,    26,    27,   139,    62,   174,     8,   116,   206,
      62,    84,   113,   114,    36,    88,    28,    35,    29,   256,
      66,    67,    68,    69,    30,    40,   154,   148,   145,   146,
     147,    69,    31,    41,    32,    33,    34,   142,   195,   196,
     197,   198,    93,   200,   152,   153,    37,   155,    38,   157,
      39,   159,    43,   162,   163,    44,    45,    46,    47,    48,
      49,    50,    58,    52,    59,   205,    56,   203,    51,   202,
      54,    55,    62,    69,    74,    76,    78,    80,    89,    90,
      95,    96,    97,    98,   103,   -85,   100,   216,   102,   104,
     148,   106,   140,   108,   201,   110,   105,   112,   107,   129,
     109,   131,   116,   124,   133,   135,   138,   141,   164,   151,
     160,    91,   167,   168,   169,   170,   171,   241,   172,   175,
     176,     0,   178,   250,   180,   177,   181,   179,   204,   191,
     207,   218,   208,   209,   210,   217,   219,   220,   221,   222,
     223,   236,   226,   235,   245,   227,   239,   253,   237,   248,
     238,   257,    72,   260,     0,   148
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-239)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      46,    52,    64,    56,   186,    99,    52,   141,     8,   233,
       6,     4,   131,    30,   133,    11,   254,   255,   242,    19,
      16,    72,   246,   261,    30,    87,    72,   121,   122,    22,
      23,   150,    65,     7,     8,     0,     9,    10,    12,    13,
      14,    15,    26,    17,    25,    18,    30,    21,    22,    82,
      24,    26,    32,    32,    26,    30,    26,    25,    30,   193,
      30,    53,    85,    86,    26,    57,    32,    30,    32,   251,
      27,    28,    29,    30,    32,    26,   129,   123,    27,    28,
      29,    30,    32,    20,    32,    32,    32,   120,   182,   183,
     184,   185,   154,   187,   127,   128,    32,   130,    32,   132,
      32,   134,    25,   136,   137,    30,    25,    25,    25,    25,
      25,    25,    32,    25,     3,   192,    25,   190,    31,   189,
      31,    31,    30,    30,    30,    30,    30,    30,    25,    30,
      25,    25,    25,    25,    32,    26,    26,   211,    26,    26,
     186,    26,   118,    26,   188,    26,    32,    26,    32,    25,
      32,    25,    30,    30,    25,    25,    25,    25,    30,    26,
      25,    61,    26,    26,    25,    25,    25,   234,    26,    26,
      26,    -1,    26,   244,    26,    30,    26,    30,    26,    30,
      25,    30,    26,    26,    26,    32,    32,    26,    25,    25,
      30,    32,    30,    26,    25,    30,    26,   248,    32,    25,
      32,    26,   248,    26,    -1,   251
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,    19,    37,    30,    30,     0,    25,    25,    38,
       7,     8,    12,    13,    14,    15,    17,    21,    22,    24,
      44,     4,    22,    23,    41,    63,    32,    32,    32,    32,
      32,    32,    32,    32,    32,    30,    26,    32,    32,    32,
      26,    20,    65,    25,    30,    25,    25,    25,    25,    25,
      25,    31,    25,    40,    31,    31,    25,    39,    32,     3,
      71,   105,    30,   101,   106,    45,    27,    28,    29,    30,
      64,    89,    64,   103,    30,    61,    30,    59,    30,    57,
      30,    55,    52,   103,    37,    43,    42,   106,    37,    25,
      30,    71,    26,   101,    44,    25,    25,    25,    25,    90,
      26,   103,    26,    32,    26,    32,    26,    32,    26,    32,
      26,    44,    26,    41,    41,    26,    30,    66,   104,    72,
      50,    91,    93,    95,    30,   107,    89,    49,    47,    25,
      46,    25,    54,    25,    53,    25,    51,    48,    25,    26,
      66,    25,    44,    89,    89,    27,    28,    29,    64,    97,
     108,    26,    44,    44,   106,    44,   107,    44,   107,    44,
      25,    67,    44,    44,    30,    69,    69,    26,    26,    25,
      25,    25,    26,   107,    26,    26,    26,    30,    26,    30,
      26,    26,    92,    94,    98,    99,   100,    96,    62,    60,
      58,    30,    56,    70,    73,    89,    89,    89,    89,    97,
      89,    61,    59,    57,    26,    55,    69,    25,    26,    26,
      26,    68,     6,    11,    16,    74,    67,    32,    30,    32,
      26,    25,    25,    30,    78,    76,    30,    30,    80,     9,
      10,    18,    82,    75,    81,    26,    32,    32,    32,    26,
      74,    80,    79,    87,    85,    25,    77,    74,    25,   102,
     102,    83,    74,   103,    88,    86,    97,    26,    82,    82,
      26,    84,    82
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
#line 79 "maepl.y"
    { domain->new_domain(std::string((yyvsp[(2) - (3)].sval)));                                  }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 80 "maepl.y"
    { if (buffer->is_action_reflexive()) domain->create_action_reflexive_reachables();
                                                                    domain->finish_domain();                                              }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 83 "maepl.y"
    { if (buffer->is_state_reflexive()) domain->create_state_reflexive_reachables();
                                                                  for (auto agent : buffer->get_missing_perceivables()) {
                                                                    domain->add_perceivability(agent, {agent});
                                                                  }
                                                                  domain->finish_problem();                                             }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 90 "maepl.y"
    { buffer->set_action_reflexivity((yyvsp[(3) - (3)].bval));                                   }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 91 "maepl.y"
    { if ((yyvsp[(3) - (3)].bval)) domain->set_announce_enabled();                               }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 95 "maepl.y"
    { domain->set_domain((yyvsp[(3) - (3)].sval));                                               }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 96 "maepl.y"
    { domain->set_objects(buffer->get_objects());                           }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 97 "maepl.y"
    { domain->set_initial_propositions(buffer->get_proposition_instances());}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 98 "maepl.y"
    { domain->create_world((yyvsp[(2) - (5)].sval), buffer->get_proposition_instances());        }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 99 "maepl.y"
    { domain->set_goal(buffer->get_formula());                              }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 100 "maepl.y"
    { domain->set_designated_worlds(buffer->get_variables());               }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 101 "maepl.y"
    {                                                                       }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 102 "maepl.y"
    { buffer->set_state_reflexivity((yyvsp[(3) - (3)].bval));                                    }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 103 "maepl.y"
    {}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 104 "maepl.y"
    {}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 107 "maepl.y"
    { domain->add_reachability((yyvsp[(1) - (5)].sval), buffer->get_inputs());                   }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 110 "maepl.y"
    { domain->add_perceivability((yyvsp[(1) - (5)].sval), 
                                                                        buffer->add_reflexive_perceivability((yyvsp[(1) - (5)].sval),
                                                                            buffer->get_ordered_variables()));                          }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 115 "maepl.y"
    { domain->add_observability((yyvsp[(1) - (5)].sval), buffer->get_ordered_variables());     }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 119 "maepl.y"
    { buffer->set_object_type((yyvsp[(1) - (5)].sval));
                                               buffer->push_objects();                                      }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 122 "maepl.y"
    { std::cerr << "Missing types definition\n";                   }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 124 "maepl.y"
    { buffer->push_types(); 
                                               domain->set_types(buffer->get_types());                      }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 128 "maepl.y"
    {buffer->push_proposition_instance((yyvsp[(1) - (4)].sval));                           }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 131 "maepl.y"
    { std::cerr << "Missing propositions definition\n";            }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 136 "maepl.y"
    { domain->add_proposition((yyvsp[(1) - (4)].sval), buffer->get_inputs());           }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 140 "maepl.y"
    { buffer->add_input((yyvsp[(2) - (4)].sval), (yyvsp[(3) - (4)].sval));                                   }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 143 "maepl.y"
    { buffer->add_input((yyvsp[(1) - (2)].sval), (yyvsp[(2) - (2)].sval));                                   }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 146 "maepl.y"
    { domain->new_action(std::string((yyvsp[(2) - (2)].sval)));                         }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 147 "maepl.y"
    { domain->set_action_input(buffer->get_inputs());              }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 149 "maepl.y"
    { domain->finish_action();                                     }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 152 "maepl.y"
    { domain->set_action_owner((yyvsp[(3) - (4)].sval), (yyvsp[(4) - (4)].sval));                            }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 153 "maepl.y"
    { buffer->set_event_name((yyvsp[(2) - (3)].sval));                                  }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 154 "maepl.y"
    { domain->create_event(                                        
                                                 buffer->get_event_name(),                                  
                                                 buffer->get_formula(),                         
                                                 buffer->get_event_add_list(),                              
                                                 buffer->get_event_delete_list());                          }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 159 "maepl.y"
    { buffer->clear_designated_events();                           }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 160 "maepl.y"
    { domain->set_designated_events(buffer->get_designated_events());}
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 163 "maepl.y"
    { buffer->add_designated_event((yyvsp[(1) - (1)].sval));                            }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 166 "maepl.y"
    { buffer->clear_formula();                                     }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 167 "maepl.y"
    {                                                              }
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 168 "maepl.y"
    { buffer->clear_variable_list();                               }
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 169 "maepl.y"
    { buffer->push_event_delete_list();                            }
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 170 "maepl.y"
    { buffer->clear_variable_list();                               }
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 171 "maepl.y"
    { buffer->push_event_add_list();                               }
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 182 "maepl.y"
    {buffer->push_pop_formula();                                 }
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 183 "maepl.y"
    {buffer->push_pop_formula();                                 }
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 184 "maepl.y"
    {buffer->push_formula("And");                                  }
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 185 "maepl.y"
    {buffer->pop_formula();                                        }
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 186 "maepl.y"
    {buffer->push_formula("Or");                                   }
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 187 "maepl.y"
    {buffer->pop_formula();                                        }
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 188 "maepl.y"
    {buffer->push_formula("Not");                                  }
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 189 "maepl.y"
    {buffer->pop_formula();                                        }
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 193 "maepl.y"
    {buffer->push_pop_formula();                                 }
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 194 "maepl.y"
    {buffer->push_formula("And");                                  }
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 195 "maepl.y"
    {buffer->pop_formula();                                        }
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 196 "maepl.y"
    {buffer->push_formula("Or");                                   }
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 197 "maepl.y"
    {buffer->pop_formula();                                        }
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 198 "maepl.y"
    {buffer->push_formula("Not");                                  }
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 199 "maepl.y"
    {buffer->pop_formula();                                        }
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 201 "maepl.y"
    { buffer->add_variable((yyvsp[(1) - (1)].sval));                                    }
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 222 "maepl.y"
    {buffer->add_ordered_variable((yyvsp[(1) - (1)].sval));                               }
    break;


/* Line 1792 of yacc.c  */
#line 1976 "maepl.tab.cpp"
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
#line 223 "maepl.y"


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
