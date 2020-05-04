/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

	#include <bits/stdc++.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "struct.h"
	using namespace std;

	extern int yylex();

	int lineno = 0;
	void yyerror(string s)
	{
		//fprintf(stderr,"Error at line %d\n%s", lineno,s);
		cerr<<"Error at line "<<lineno<<endl<<s<<endl;
	}

	symbol_table ST;
	int active_function_index = 0;
	int level = 0;
	intermediate_code code;
	int gtemp = 0;
	temp_data all_temp_var;

#line 91 "parser.tab.c" /* yacc.c:339  */

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
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 26 "parser.y" /* yacc.c:355  */

	#ifndef _STRUCT_H_INCLUDED_
	#define _STRUCT_H_INCLUDED_
	#include "struct.h"
	#endif

#line 128 "parser.tab.c" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    FLOAT = 259,
    VOID = 260,
    IF = 261,
    ELSE = 262,
    FOR = 263,
    WHILE = 264,
    BREAK = 265,
    CONTINUE = 266,
    SWITCH = 267,
    CASE = 268,
    DEFAULT = 269,
    RETURN = 270,
    PRINT = 271,
    PLUS = 272,
    MINUS = 273,
    MULTIPLY = 274,
    DIVIDE = 275,
    MOD = 276,
    ASSIGN = 277,
    OR = 278,
    AND = 279,
    NOT = 280,
    SEMI = 281,
    COMMA = 282,
    COLON = 283,
    LT = 284,
    GT = 285,
    LTE = 286,
    GTE = 287,
    EQ = 288,
    NEQ = 289,
    LB = 290,
    RB = 291,
    LSQ = 292,
    RSQ = 293,
    LCURLY = 294,
    RCURLY = 295,
    INCREMENT = 296,
    DECREMENT = 297,
    ID = 298,
    NUM_INT = 299,
    NUM_FLOAT = 300
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 33 "parser.y" /* yacc.c:355  */
 
	char* Char;
	int int_val;
	float float_val;
	int type;
	varList * variable_list;
	int no_of_parameters;
	expression_* exp;
	id_array_* ia_;

#line 197 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 214 "parser.tab.c" /* yacc.c:358  */

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   190

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  152

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    77,    77,    80,    81,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    98,   107,   113,
     120,   123,   126,   147,   153,   159,   171,   185,   205,   224,
     225,   226,   229,   230,   232,   235,   236,   239,   242,   244,
     247,   250,   251,   254,   255,   258,   261,   264,   265,   268,
     277,   286,   296,   304,   314,   327,   340,   353,   366,   379,
     394,   407,   420,   430,   443,   456,   466,   476,   484,   500,
     516,   532,   550,   555,   560,   574,   581,   627,   676,   693,
     725,   729
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "VOID", "IF", "ELSE",
  "FOR", "WHILE", "BREAK", "CONTINUE", "SWITCH", "CASE", "DEFAULT",
  "RETURN", "PRINT", "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "MOD",
  "ASSIGN", "OR", "AND", "NOT", "SEMI", "COMMA", "COLON", "LT", "GT",
  "LTE", "GTE", "EQ", "NEQ", "LB", "RB", "LSQ", "RSQ", "LCURLY", "RCURLY",
  "INCREMENT", "DECREMENT", "ID", "NUM_INT", "NUM_FLOAT", "$accept",
  "prog", "stmt_list", "stmt", "var_dec", "var_list", "func_dec",
  "func_header", "func_type_id", "func_params", "param_decl", "decl",
  "type", "if_block", "if_condition", "loop_block", "while_condition",
  "for_condition", "stmt_block", "switch_case_statement",
  "case_statement_block", "case_list", "case_statement",
  "default_statemnt", "assignment", "bool_conditions", "condition",
  "comparison", "operation", "term", "factor", "unary_expression",
  "expression", "decl_id_array", "id_array", "left_curly", "right_curly", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300
};
# endif

#define YYPACT_NINF -84

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-84)))

#define YYTABLE_NINF -23

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -84,    12,   145,   -84,   -84,   -84,   -84,   -17,   -10,    -7,
       4,    42,    35,     8,    37,    37,   -84,    37,   -84,    37,
      37,    36,   -84,   -84,   -84,    57,   -84,    50,    40,    51,
     -84,   145,   -84,   145,   145,   -84,   -84,    91,    64,   -84,
     -84,    27,    78,   -84,   -84,   -84,    82,   -84,    37,    37,
      37,   -84,   -84,    37,   -84,    -3,   -84,   -84,   -84,    -9,
     -84,   -84,    84,   -84,   -84,    62,   -13,   102,   -84,   123,
     -84,   -84,   -84,    37,    37,    37,    37,    37,    37,    37,
      37,    37,    37,    37,    37,    37,    97,    95,   108,    99,
      -1,   -84,   -84,   105,    97,   109,   117,   -84,   115,   118,
     116,   145,   -84,   -84,    78,    78,    93,    93,    93,    93,
      93,    93,   -84,   -84,    64,   -84,   -84,   -84,    37,   -84,
      50,   -84,   -84,   -84,    62,   124,   114,   127,   -84,   -84,
     139,   153,   -84,   129,   -84,    37,    37,   128,   100,   -84,
     -84,   133,    46,   -84,   144,   -84,   -84,   -84,   145,   145,
     -84,   -84
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     2,     1,    29,    30,    31,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    16,     0,    80,     0,
       0,    78,    73,    72,     3,     0,    10,     0,     0,     0,
      11,     0,    12,     0,     0,    13,    14,     0,    48,    51,
      52,    53,    62,    65,    66,    67,    74,     4,     0,     0,
       0,     7,     8,     0,     5,     0,    74,    69,    68,     0,
      71,    70,     0,     9,     4,    24,    76,    17,    19,    33,
      35,    36,    15,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     6,    75,     0,     0,     0,    23,    26,     0,     0,
       0,     0,    50,    49,    60,    61,    56,    54,    57,    55,
      58,    59,    63,    64,    47,    81,    39,    34,     0,    37,
       0,    79,    20,    21,     0,    27,     0,    76,    18,    32,
       0,     0,    25,     0,    77,     0,     0,     0,    42,    44,
      28,     0,     0,    40,     0,    43,    41,    38,     0,     0,
      45,    46
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -84,   -84,   -28,   -30,   -84,   -84,   -84,   -84,   -84,   -84,
     -84,    52,   -55,   -84,   -84,   -84,   -84,   -84,   -84,   -84,
     -84,   -84,    39,   -84,   -42,    -8,    47,   -84,   -40,    49,
      43,    71,   -84,    73,    -2,   -25,   -83
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    24,    25,    67,    26,    27,    28,    95,
      96,    97,    29,    30,    31,    32,    33,    34,    35,    36,
     137,   138,   139,   146,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    68,    56,    47,   116
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      46,    69,    64,    70,    71,    55,    87,    88,    89,    59,
      98,   122,     3,    90,    73,    74,    75,    76,    48,    86,
      73,    74,   -22,    91,    99,    49,    14,    92,    50,    46,
      51,    46,    46,    15,    54,   120,    94,   106,   107,   108,
     109,   110,   111,    17,    75,    76,    46,    46,    46,    19,
      20,    21,    22,    23,   143,    14,    77,    78,    79,    80,
      81,    82,    15,    75,    76,     4,     5,     6,    52,    98,
      53,   129,    17,    62,   148,    65,   130,   114,    19,    20,
      21,    22,    23,    63,    46,    57,    58,    73,    74,    18,
      60,    61,    46,   141,    66,   131,   142,    83,    84,    46,
       4,     5,     6,     7,    85,     8,     9,    10,    11,    12,
      75,    76,    13,   136,   144,    14,    46,    72,   150,   151,
     102,   103,    15,    16,   104,   105,   112,   113,    93,   100,
     101,   117,    17,    46,   118,   119,    18,   115,    19,    20,
      21,    22,    23,   121,   124,   123,    46,    46,     4,     5,
       6,     7,   134,     8,     9,    10,    11,    12,   125,   127,
      13,   133,   126,    14,    99,   135,   136,   140,   115,   147,
      15,    16,   149,   128,     0,     0,   132,   145,     0,     0,
      17,     0,     0,     0,    18,     0,    19,    20,    21,    22,
      23
};

static const yytype_int16 yycheck[] =
{
       2,    31,    27,    33,    34,    13,    48,    49,    50,    17,
      65,    94,     0,    53,    23,    24,    17,    18,    35,    47,
      23,    24,    35,    26,    37,    35,    18,    36,    35,    31,
      26,    33,    34,    25,    26,    36,    64,    77,    78,    79,
      80,    81,    82,    35,    17,    18,    48,    49,    50,    41,
      42,    43,    44,    45,   137,    18,    29,    30,    31,    32,
      33,    34,    25,    17,    18,     3,     4,     5,    26,   124,
      35,   101,    35,    37,    28,    35,   118,    85,    41,    42,
      43,    44,    45,    26,    86,    14,    15,    23,    24,    39,
      19,    20,    94,   135,    43,   120,   136,    19,    20,   101,
       3,     4,     5,     6,    22,     8,     9,    10,    11,    12,
      17,    18,    15,    13,    14,    18,   118,    26,   148,   149,
      73,    74,    25,    26,    75,    76,    83,    84,    44,    27,
       7,    36,    35,   135,    26,    36,    39,    40,    41,    42,
      43,    44,    45,    38,    27,    36,   148,   149,     3,     4,
       5,     6,    38,     8,     9,    10,    11,    12,    43,    43,
      15,    37,    44,    18,    37,    26,    13,    38,    40,    36,
      25,    26,    28,   100,    -1,    -1,   124,   138,    -1,    -1,
      35,    -1,    -1,    -1,    39,    -1,    41,    42,    43,    44,
      45
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    47,    48,     0,     3,     4,     5,     6,     8,     9,
      10,    11,    12,    15,    18,    25,    26,    35,    39,    41,
      42,    43,    44,    45,    49,    50,    52,    53,    54,    58,
      59,    60,    61,    62,    63,    64,    65,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    80,    81,    35,    35,
      35,    26,    26,    35,    26,    71,    80,    77,    77,    71,
      77,    77,    37,    26,    81,    35,    43,    51,    79,    49,
      49,    49,    26,    23,    24,    17,    18,    29,    30,    31,
      32,    33,    34,    19,    20,    22,    48,    70,    70,    70,
      74,    26,    36,    44,    48,    55,    56,    57,    58,    37,
      27,     7,    72,    72,    75,    75,    74,    74,    74,    74,
      74,    74,    76,    76,    71,    40,    82,    36,    26,    36,
      36,    38,    82,    36,    27,    43,    44,    43,    79,    49,
      70,    81,    57,    37,    38,    26,    13,    66,    67,    68,
      38,    70,    74,    82,    14,    68,    69,    36,    28,    28,
      49,    49
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    48,    48,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    50,    51,    51,
      52,    53,    54,    55,    55,    56,    56,    57,    57,    58,
      58,    58,    59,    59,    60,    61,    61,    62,    63,    64,
      65,    66,    66,    67,    67,    68,    69,    70,    70,    71,
      71,    71,    72,    72,    73,    73,    73,    73,    73,    73,
      74,    74,    74,    75,    75,    75,    76,    77,    77,    77,
      77,    77,    78,    78,    78,    78,    79,    79,    80,    80,
      81,    82
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     3,     2,     2,     2,
       1,     1,     1,     1,     1,     2,     1,     2,     3,     1,
       4,     4,     2,     1,     0,     3,     1,     2,     4,     1,
       1,     1,     4,     2,     4,     2,     2,     4,     8,     3,
       7,     2,     1,     2,     1,     4,     3,     3,     1,     3,
       3,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     3,     3,     1,     1,     1,     2,     2,
       2,     2,     1,     1,     1,     3,     1,     4,     1,     4,
       1,     1
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
        case 2:
#line 77 "parser.y" /* yacc.c:1646  */
    { printf("Accepted\n"); }
#line 1413 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 99 "parser.y" /* yacc.c:1646  */
    {
			if(active_function_index!=-1)
			{
				ST.change_type(active_function_index,(yyvsp[0].variable_list)->indices,(yyvsp[-1].type));
			}
		}
#line 1424 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 108 "parser.y" /* yacc.c:1646  */
    {
		  		(yyval.variable_list) = new varList();
		  		(yyval.variable_list)->indices = (yyvsp[-2].variable_list)->indices;
		  		(yyval.variable_list)->indices.push_back((yyvsp[0].int_val));
		  }
#line 1434 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 114 "parser.y" /* yacc.c:1646  */
    {
		  		(yyval.variable_list) = new varList();
		  		(yyval.variable_list)->indices.push_back((yyvsp[0].int_val));
		  }
#line 1443 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 127 "parser.y" /* yacc.c:1646  */
    {
				string name = (yyvsp[0].Char);
				if(ST.search_function(name)==1)
				{
					(yyval.type) = ERROR;
					yyerror("Function already declared");
					active_function_index = -1;
				}
				else
				{
					(yyval.type) = (yyvsp[-1].type);
					active_function_index = ST.add_function(name,(yyvsp[-1].type));
					level =1;
					string s = "function_"+name+":";
					code.insert(s);
					cout<<"Function added successfully"<<endl;
				}
			}
#line 1466 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 148 "parser.y" /* yacc.c:1646  */
    {
			 	(yyval.no_of_parameters) = (yyvsp[0].no_of_parameters);
			 	ST.set_no_of_parameters(active_function_index,(yyval.no_of_parameters));
			 }
#line 1475 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 153 "parser.y" /* yacc.c:1646  */
    {
			 	(yyval.no_of_parameters) = 0;
			 	ST.set_no_of_parameters(active_function_index,(yyval.no_of_parameters));
			 }
#line 1484 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 160 "parser.y" /* yacc.c:1646  */
    {
				if(active_function_index!=-1)
				{
						if((yyvsp[0].type)!=ERROR)
					{
						(yyval.no_of_parameters) = (yyvsp[-2].no_of_parameters)+1;
					}
					else
						(yyval.no_of_parameters) = (yyvsp[-2].no_of_parameters);
				}
			}
#line 1500 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 172 "parser.y" /* yacc.c:1646  */
    {
				if(active_function_index!=-1)
				{
					if((yyvsp[0].type)!=ERROR)
					{
						(yyval.no_of_parameters) = 1;
					}
					else
						(yyval.no_of_parameters) = 0;
				}
			}
#line 1516 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 186 "parser.y" /* yacc.c:1646  */
    {
		  	if(active_function_index!=-1)
		  	{
		  		string name((yyvsp[0].Char));
		  		//cout<<"decl: active_function_index: "<<active_function_index<<endl;
		  		if(ST.search_parameter(name,active_function_index) == -1)
		  		{
		  			int index = ST.add_parameter(active_function_index, name, SIMPLE, (yyvsp[-1].type));
		  			//cout<< "Parameter "<<name <<"added at index "<<index<<"for active_function_index: "<<active_function_index<<endl;
		  			(yyval.type) = (yyvsp[-1].type);
		  		}
		  		else
		  		{
		  			//cout<<"I came here!"<< name<<endl;
		  			(yyval.type) = ERROR;
		  			yyerror("Variable previously listed as argument");
		  		}
		  	}
	  }
#line 1540 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 206 "parser.y" /* yacc.c:1646  */
    {
		  	if(active_function_index!=-1)
		  	{
		  		string name = (yyvsp[-2].Char);
		  		if(ST.search_parameter(name,active_function_index) == -1)
		  		{
		  			int index = ST.add_parameter(active_function_index, name, ARRAY, (yyvsp[-3].type));
		  			(yyval.type) = (yyvsp[-3].type);
		  		}
		  		else
		  		{
		  			(yyval.type) = ERROR;
		  			yyerror("Variable previously listed as argument");
		  		}
		  	}
	  }
#line 1561 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 224 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = INT_TYPE; }
#line 1567 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 225 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = FLOAT_TYPE; }
#line 1573 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 226 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = VOID_TYPE; }
#line 1579 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 269 "parser.y" /* yacc.c:1646  */
    {
						int type = get_compatible_type_comparison((yyvsp[-2].exp)->type,(yyvsp[0].exp)->type);
						(yyval.exp) = new expression_(type);
						if(type!=ERROR)
						{
							code.insert2("&&",(yyvsp[-2].exp)->temp_name,(yyvsp[0].exp)->temp_name,(yyval.exp)->temp_name);
						}
					}
#line 1592 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 278 "parser.y" /* yacc.c:1646  */
    {
						int type = get_compatible_type_comparison((yyvsp[-2].exp)->type,(yyvsp[0].exp)->type);
						(yyval.exp) = new expression_(type);
						if(type!=ERROR)
						{
							code.insert2("||",(yyvsp[-2].exp)->temp_name,(yyvsp[0].exp)->temp_name,(yyval.exp)->temp_name);
						}
					}
#line 1605 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 287 "parser.y" /* yacc.c:1646  */
    {
						(yyval.exp) = new expression_((yyvsp[0].exp)->type);
						if((yyvsp[0].exp)->type!=ERROR)
						{
							code.insert2("=",(yyvsp[0].exp)->temp_name," ",(yyval.exp)->temp_name);
						}
					}
#line 1617 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 297 "parser.y" /* yacc.c:1646  */
    {
		  		(yyval.exp) = new expression_((yyvsp[0].exp)->type);
		  		if((yyvsp[0].exp)->type!=ERROR)
		  		{
		  			code.insert2("=",(yyvsp[0].exp)->temp_name," ",(yyval.exp)->temp_name);
		  		}
		  }
#line 1629 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 305 "parser.y" /* yacc.c:1646  */
    {
		  		(yyval.exp) = new expression_((yyvsp[0].exp)->type);
		  		if((yyvsp[0].exp)->type!=ERROR)
		  		{
		  			code.insert2("=",(yyvsp[0].exp)->temp_name," ",(yyval.exp)->temp_name);
		  		}
		  }
#line 1641 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 315 "parser.y" /* yacc.c:1646  */
    {
				int type = get_compatible_type_comparison((yyvsp[-2].exp)->type,(yyvsp[0].exp)->type);
				(yyval.exp) = new expression_(type);
				if(type!=ERROR)
				{
					code.insert2(">",(yyvsp[-2].exp)->temp_name," ",(yyvsp[0].exp)->temp_name);
				}
				else
				{
					yyerror("Relational operation on non-compatible data types.");
				}
			}
#line 1658 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 328 "parser.y" /* yacc.c:1646  */
    {
				int type = get_compatible_type_comparison((yyvsp[-2].exp)->type,(yyvsp[0].exp)->type);
				(yyval.exp) = new expression_(type);
				if(type!=ERROR)
				{
					code.insert2(">=",(yyvsp[-2].exp)->temp_name," ",(yyvsp[0].exp)->temp_name);
				}
				else
				{
					yyerror("Relational operation on non-compatible data types.");
				}
			}
#line 1675 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 341 "parser.y" /* yacc.c:1646  */
    {
				int type = get_compatible_type_comparison((yyvsp[-2].exp)->type,(yyvsp[0].exp)->type);
				(yyval.exp) = new expression_(type);
				if(type!=ERROR)
				{
					code.insert2("<",(yyvsp[-2].exp)->temp_name," ",(yyvsp[0].exp)->temp_name);
				}
				else
				{
					yyerror("Relational operation on non-compatible data types.");
				}
			}
#line 1692 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 354 "parser.y" /* yacc.c:1646  */
    {
				int type = get_compatible_type_comparison((yyvsp[-2].exp)->type,(yyvsp[0].exp)->type);
				(yyval.exp) = new expression_(type);
				if(type!=ERROR)
				{
					code.insert2("<=",(yyvsp[-2].exp)->temp_name," ",(yyvsp[0].exp)->temp_name);
				}
				else
				{
					yyerror("Relational operation on non-compatible data types.");
				}
			}
#line 1709 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 367 "parser.y" /* yacc.c:1646  */
    {
				int type = get_compatible_type_comparison((yyvsp[-2].exp)->type,(yyvsp[0].exp)->type);
				(yyval.exp) = new expression_(type);
				if(type!=ERROR)
				{
					code.insert2("==",(yyvsp[-2].exp)->temp_name," ",(yyvsp[0].exp)->temp_name);
				}
				else
				{
					yyerror("Relational operation on non-compatible data types.");
				}
			}
#line 1726 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 380 "parser.y" /* yacc.c:1646  */
    {
				int type = get_compatible_type_comparison((yyvsp[-2].exp)->type,(yyvsp[0].exp)->type);
				(yyval.exp) = new expression_(type);
				if(type!=ERROR)
				{
					code.insert2("!=",(yyvsp[-2].exp)->temp_name," ",(yyvsp[0].exp)->temp_name);
				}
				else
				{
					yyerror("Relational operation on non-compatible data types.");
				}
			}
#line 1743 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 395 "parser.y" /* yacc.c:1646  */
    {
				int type = get_compatible_type_term((yyvsp[-2].exp)->type,(yyvsp[0].exp)->type);
				(yyval.exp) = new expression_(type);
				if(type!=ERROR)
				{
					code.insert2("+",(yyvsp[-2].exp)->temp_name," ",(yyvsp[0].exp)->temp_name);
				}
				else
				{
					yyerror("Addition operation on non-compatible data types.");
				}
			}
#line 1760 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 408 "parser.y" /* yacc.c:1646  */
    {
		   		int type = get_compatible_type_term((yyvsp[-2].exp)->type,(yyvsp[0].exp)->type);
				(yyval.exp) = new expression_(type);
				if(type!=ERROR)
				{
					code.insert2("-",(yyvsp[-2].exp)->temp_name," ",(yyvsp[0].exp)->temp_name);
				}
				else
				{
					yyerror("Subtraction operation on non-compatible data types.");
				}
		   }
#line 1777 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 421 "parser.y" /* yacc.c:1646  */
    {
		   		(yyval.exp) = new expression_((yyvsp[0].exp)->type);
		   		if((yyvsp[0].exp)->type!=ERROR)
		   		{
		   			code.insert2("=",(yyvsp[0].exp)->temp_name," ",(yyval.exp)->temp_name);
		   		}
		   }
#line 1789 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 431 "parser.y" /* yacc.c:1646  */
    {
	  	int type = get_compatible_type_term((yyvsp[-2].exp)->type,(yyvsp[0].exp)->type);
	  	(yyval.exp) = new expression_(type);
	  	if(type!=ERROR)
	  	{
	  		code.insert2("*",(yyvsp[-2].exp)->temp_name," ",(yyval.exp)->temp_name);
	  	}
	  	else
	  	{
	  		yyerror("Multiply operation on non-compatible data types");
	  	}
	  }
#line 1806 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 444 "parser.y" /* yacc.c:1646  */
    {
	  	int type = get_compatible_type_term((yyvsp[-2].exp)->type,(yyvsp[0].exp)->type);
	  	(yyval.exp) = new expression_(type);
	  	if(type!=ERROR)
	  	{
	  		code.insert2("/",(yyvsp[-2].exp)->temp_name," ",(yyval.exp)->temp_name);
	  	}
	  	else
	  	{
	  		yyerror("Division operation on non-compatible data types");
	  	}
	  }
#line 1823 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 457 "parser.y" /* yacc.c:1646  */
    {
	  	(yyval.exp) = new expression_((yyvsp[0].exp)->type);
	  	if((yyvsp[0].exp)->type!=ERROR)
	  	{
	  		code.insert2("=",(yyvsp[0].exp)->temp_name," ",(yyval.exp)->temp_name);
	  	}
	  }
#line 1835 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 467 "parser.y" /* yacc.c:1646  */
    {
			(yyval.exp) = new expression_((yyvsp[0].exp)->type);
			if((yyvsp[0].exp)->type!=ERROR)
			{
				code.insert2("=",(yyvsp[0].exp)->temp_name," ",(yyval.exp)->temp_name);
			}
		}
#line 1847 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 477 "parser.y" /* yacc.c:1646  */
    {
					(yyval.exp) = new expression_((yyvsp[0].exp)->type);
					if((yyvsp[0].exp)->type != ERROR)
					{
						code.insert2("=",(yyvsp[0].exp)->temp_name," ",(yyval.exp)->temp_name);
					}
				}
#line 1859 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 485 "parser.y" /* yacc.c:1646  */
    {
					if((yyvsp[0].exp)->type==FLOAT_TYPE)
					{
						(yyval.exp) = new expression_(ERROR);
						yyerror("Invalid opaeration.");
					}
					else
					{
						(yyval.exp) = new expression_((yyvsp[0].exp)->type);
						if((yyvsp[0].exp)->type!=ERROR)
						{
							code.insert2("NOT",(yyvsp[0].exp)->temp_name," ",(yyval.exp)->temp_name);
						}
					}
				}
#line 1879 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 501 "parser.y" /* yacc.c:1646  */
    {
					if((yyvsp[0].exp)->type!=BOOL_TYPE)
					{
						(yyval.exp) = new expression_((yyvsp[0].exp)->type);
						if((yyvsp[0].exp)->type != ERROR)
						{
							code.insert2("MINUS",(yyvsp[0].exp)->temp_name," ",(yyval.exp)->temp_name);
						}
					}
					else
					{
						yyerror("Invalid operation");
						(yyval.exp) = new expression_(ERROR);
					}
				}
#line 1899 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 517 "parser.y" /* yacc.c:1646  */
    {
					if((yyvsp[0].exp)->type!=BOOL_TYPE && (yyvsp[0].exp)->type!=FLOAT_TYPE)
					{
						(yyval.exp) = new expression_((yyvsp[0].exp)->type);
						if((yyvsp[0].exp)->type!=ERROR)
						{
							code.insert2("-",(yyvsp[0].exp)->temp_name," 1 ",(yyval.exp)->temp_name);
						}
					}
					else
					{
						(yyval.exp) = new expression_(ERROR);
						yyerror("Invalid operation.");
					}
				}
#line 1919 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 533 "parser.y" /* yacc.c:1646  */
    {
					if((yyvsp[0].exp)->type!=BOOL_TYPE && (yyvsp[0].exp)->type!=FLOAT_TYPE)
					{
						(yyval.exp) = new expression_((yyvsp[0].exp)->type);
						if((yyvsp[0].exp)->type!=ERROR)
						{
							code.insert2("+",(yyvsp[0].exp)->temp_name," 1 ",(yyval.exp)->temp_name);
						}
					}
					else
					{
						(yyval.exp) = new expression_(ERROR);
						yyerror("Invalid operation.");
					}
				}
#line 1939 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 551 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exp) = new expression_(FLOAT_TYPE);
				code.insert2("=",to_string((yyvsp[0].float_val))," ",(yyval.exp)->temp_name);
			}
#line 1948 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 556 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exp) = new expression_(INT_TYPE);
				code.insert2("=",to_string((yyvsp[0].int_val))," ",(yyval.exp)->temp_name);
			}
#line 1957 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 561 "parser.y" /* yacc.c:1646  */
    {
				if((yyvsp[0].ia_)->var == NULL)
				{
					yyerror("Variable not declared");
					(yyval.exp) = new expression_(ERROR);
				}
				else 
				{
					(yyval.exp) = new expression_((yyvsp[0].ia_)->var->num_type);
					code.insert2("=", (yyvsp[0].ia_)->var->name," ",(yyval.exp)->temp_name);
				}
				
			}
#line 1975 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 575 "parser.y" /* yacc.c:1646  */
    {

				(yyval.exp) = new expression_(0);
			}
#line 1984 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 582 "parser.y" /* yacc.c:1646  */
    {
				if(active_function_index!=-1)
				{
					string s = (yyvsp[0].Char);
					variable* v = ST.search_cur_var(active_function_index, level, s);

					if(v==NULL)
					{
						int index = ST.add_variable(active_function_index,s,level,SIMPLE,INT_TYPE,0);
						(yyval.int_val) = index;
					}
					else
					{
						if(v->decl_level != level)
						{
							if(level!=2)
							{
								int index = ST.add_variable(active_function_index,s,level,SIMPLE,INT_TYPE,0);
								(yyval.int_val) = index;
							}

							else
							{
								if(ST.search_parameter(s,active_function_index) == -1)
								{
									int index = ST.add_variable(active_function_index,s,level,SIMPLE,INT_TYPE,0);
									(yyval.int_val) = index;
								}
								else
								{
									yyerror("variable re-declared");
									(yyval.int_val) = -1;
								}
							}
						
						}
						else
						{
							yyerror("variable re-declared");
							(yyval.int_val) = -1;
						}

					}
				}  
		  }
#line 2034 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 628 "parser.y" /* yacc.c:1646  */
    {
		  		if(active_function_index!=-1)
		  		{
		  			string s = (yyvsp[-3].Char);
					variable* v = ST.search_cur_var(active_function_index, level, s);

					if(v==NULL)
					{
						int index = ST.add_variable(active_function_index,s,level,ARRAY,INT_TYPE,(yyvsp[-1].int_val));
						(yyval.int_val) = index;
					}
					else
					{
						if(v->decl_level != level)
						{
							if(level!=2)
							{
								int index = ST.add_variable(active_function_index,s,level,ARRAY,INT_TYPE,(yyvsp[-1].int_val));
								(yyval.int_val) = index;
							}

							else
							{
								if(ST.search_parameter(s,active_function_index) == -1)
								{
									int index = ST.add_variable(active_function_index,s,level,ARRAY,INT_TYPE,(yyvsp[-1].int_val));
									(yyval.int_val) = index;
								}
								else
								{
									yyerror("variable re-declared");
									(yyval.int_val) = -1;
								}
							}
						
						}
						else
						{
							yyerror("variable re-declared");
							(yyval.int_val) =-1;
						}

					}
					cout<<"variable "<<(yyvsp[-3].Char)<<" added successfully"<<endl;
		  		}
		  }
#line 2085 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 677 "parser.y" /* yacc.c:1646  */
    {
		  		if(active_function_index!=-1)
		  		{
		  			string s = (yyvsp[0].Char);
		  			variable* v = ST.search_global_var(active_function_index,level,s);
		  			if(v==NULL)
		  			{
		  				string err = "Variable "+s+" not declared.";
		  				yyerror(err);
		  			}
		  			else
		  			{
		  				(yyval.ia_) = new id_array_(v);
		  			}
		  		}
		  }
#line 2106 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 694 "parser.y" /* yacc.c:1646  */
    {
		  		if(active_function_index!=-1)
		  		{
		  			string s((yyvsp[-3].Char));
		  			variable* v = ST.search_global_var(active_function_index,level,s);
		  			if(v == NULL)
		  			{
		  				string err = "Variable "+s+" not declared.";
		  				yyerror(err);
		  			}

		  			if(v!=NULL)
		  			{
		  				if(v->type != ARRAY)
		  				{
		  					string err = "Variable "+s+" not declared as array.";
		  					yyerror(err);
		  				}
		  			}

		  			if(v!=NULL)
		  			{
		  				string temp = "_T"+to_string(gtemp);
		  				gtemp++;
		  				code.insert2("=",to_string((yyvsp[-1].int_val))," ",temp);
		  				all_temp_var.temp_var_name.push_back(temp);
		  			}
		  		}
		  }
#line 2140 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 726 "parser.y" /* yacc.c:1646  */
    { level++; }
#line 2146 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 2150 "parser.tab.c" /* yacc.c:1646  */
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
#line 730 "parser.y" /* yacc.c:1906  */


int main()
{
	yyparse();
	ST.display_symbol_table();
}
