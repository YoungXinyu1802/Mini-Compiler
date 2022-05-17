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
#line 1 "compiler.y" /* yacc.c:339  */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "ast.hh"

void yyerror(const char *s) { 
    std::printf("Error: %s\n", s);
    std::exit(1); 
}

int yylex(void);


// int main()
// {
// 	int yyparse (void);
// }

_Program *root;

#line 89 "parser.cpp" /* yacc.c:339  */

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
   by #include "parser.hpp".  */
#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
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
    LP = 258,
    RP = 259,
    LB = 260,
    RB = 261,
    RCB = 262,
    LCB = 263,
    DOT = 264,
    COMMA = 265,
    COLON = 266,
    MUL = 267,
    DIV = 268,
    NOT = 269,
    ADD = 270,
    SUB = 271,
    NOEQUAL = 272,
    AND = 273,
    OR = 274,
    GE = 275,
    GT = 276,
    LE = 277,
    LT = 278,
    EQUAL = 279,
    ASSIGN = 280,
    SEMI = 281,
    LD = 282,
    RD = 283,
    MOD = 284,
    IF = 285,
    ELSE = 286,
    SIGNED = 287,
    UNION = 288,
    THIS = 289,
    UNSIGNED = 290,
    CONST = 291,
    GOTO = 292,
    VIRTUAL = 293,
    FOR = 294,
    FLOAT = 295,
    BREAK = 296,
    AUTO = 297,
    CLASS = 298,
    OPERATOR = 299,
    CASE = 300,
    DO = 301,
    LONG = 302,
    TYPEDEF = 303,
    STATIC = 304,
    FRIEND = 305,
    TEMPLATE = 306,
    DEFAULT = 307,
    NEW = 308,
    VOID = 309,
    REGISTER = 310,
    RETURN = 311,
    ENUM = 312,
    INLINE = 313,
    TRY = 314,
    SHORT = 315,
    CONTINUE = 316,
    SIZEOF = 317,
    SWITCH = 318,
    PRIVATE = 319,
    PROTECTED = 320,
    ASM = 321,
    WHILE = 322,
    CATCH = 323,
    DELETE = 324,
    PUBLIC = 325,
    VOLATILE = 326,
    STRUCT = 327,
    PRINTF = 328,
    SCANF = 329,
    MAIN = 330,
    CHAR = 331,
    CIN = 332,
    COUT = 333,
    SYS_TYPE = 334,
    SYS_BOOL = 335,
    IDENTIFIER = 336,
    REAL = 337,
    INTEGER = 338,
    STRING = 339
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 24 "compiler.y" /* yacc.c:355  */

    std::string *sVal;
    int intVal;
    double floatVal;
    bool bVal;
    char cVal;
    Node *node;
    //基础变量类型定义，暂略
    _Program *c_Program;
    _FunctionList *c_functionList;
    _Function *c_Function;
    _mainFunction *c_mainFunction;
    _Subroutine *c_Subroutine;
    _Statement *c_Statement;
    _StatementList *c_StatementList;
    _Definition *c_Definition;
    _Expression *c_Expression;
    _singleExpression *c_singleExpression;
    _DataList *c_DataList;
    _Variable *c_Variable;
    _assignExpression *c_assignExpression;
    _complexExpression *c_complexExpression;
    _functionCall *c_functionCall;
    _forStatement *c_forSTMT;
    _whileStatement *c_whileSTMT;
    _ifStatement *c_ifSTMT;
    _elsePart *c_elsePart;
    _ArgsDefinitionList *c_ArgsDefinitionList;
    _argsDefinition *c_ArgsDefinition;
    _returnStatement *c_returnStatement;
    _SingleExpressionList *c_singleExpressionList;
    _Term *c_Term;
    _Value *c_Value;
    _Input *c_Input;
    _Output *c_Output;

#line 251 "parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 268 "parser.cpp" /* yacc.c:358  */

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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   197

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  151

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   339

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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   122,   122,   129,   134,   142,   146,   153,   160,   165,
     173,   176,   179,   182,   185,   191,   196,   201,   208,   215,
     219,   223,   227,   235,   238,   245,   248,   251,   257,   260,
     263,   268,   271,   274,   277,   280,   283,   286,   292,   295,
     298,   301,   308,   311,   314,   317,   320,   326,   329,   332,
     335,   338,   346,   349,   352,   355,   362,   368,   371,   374,
     381,   389,   396,   403,   406,   409,   416,   421,   425,   429,
     434
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LP", "RP", "LB", "RB", "RCB", "LCB",
  "DOT", "COMMA", "COLON", "MUL", "DIV", "NOT", "ADD", "SUB", "NOEQUAL",
  "AND", "OR", "GE", "GT", "LE", "LT", "EQUAL", "ASSIGN", "SEMI", "LD",
  "RD", "MOD", "IF", "ELSE", "SIGNED", "UNION", "THIS", "UNSIGNED",
  "CONST", "GOTO", "VIRTUAL", "FOR", "FLOAT", "BREAK", "AUTO", "CLASS",
  "OPERATOR", "CASE", "DO", "LONG", "TYPEDEF", "STATIC", "FRIEND",
  "TEMPLATE", "DEFAULT", "NEW", "VOID", "REGISTER", "RETURN", "ENUM",
  "INLINE", "TRY", "SHORT", "CONTINUE", "SIZEOF", "SWITCH", "PRIVATE",
  "PROTECTED", "ASM", "WHILE", "CATCH", "DELETE", "PUBLIC", "VOLATILE",
  "STRUCT", "PRINTF", "SCANF", "MAIN", "CHAR", "CIN", "COUT", "SYS_TYPE",
  "SYS_BOOL", "IDENTIFIER", "REAL", "INTEGER", "STRING", "$accept",
  "Program", "functionList", "Function", "mainFunc", "StatementList",
  "Statement", "Input", "Output", "returnStatement", "Definition",
  "DataList", "Variable", "Expression", "assignExpression",
  "singleExpression", "expr", "term", "factor", "Value", "functionCall",
  "complexExpression", "forSTMT", "whileSTMT", "ifSTMT", "elsePart",
  "Subroutine", "ArgsDefinitionList", "ArgsDefinition", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339
};
# endif

#define YYPACT_NINF -79

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-79)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -61,   -68,    11,   -79,   -61,   -79,   -79,    17,    20,   -79,
     -79,   -39,   -39,   -57,    48,    45,    52,    54,   -79,    61,
     -39,    86,     5,    -5,   -79,    -5,     5,     5,     5,   -79,
     -79,   -79,   -79,   -79,    24,    34,   136,   -79,   -79,    99,
     100,     5,   101,    79,    85,   -45,    96,   114,    -5,   102,
     103,   -79,   -79,   105,   -79,   108,   116,   -79,   -79,   -79,
     -79,   118,    93,   -79,   -79,   -79,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
     -57,   135,     5,   -45,   -45,   124,   131,   141,   -45,   -79,
     -79,   -79,   -79,     1,   -79,   -79,   -79,   -79,    34,    34,
      34,    34,    34,    34,   136,   136,   136,   -79,   -79,   -79,
     -79,   115,   127,   -79,   123,   -79,   -79,   -79,   -45,   -45,
     122,   -45,   154,   -79,   152,     5,   156,   -79,   -79,   -79,
     155,    -5,   146,    -5,   -79,   166,   -57,   178,   157,   182,
     -79,    -3,   -79,   179,    -5,   -79,    -5,   183,   184,   -79,
     -79
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     4,     5,     6,     0,     0,     1,
       3,    69,    69,     0,     0,    68,     0,    23,    70,     0,
      69,     0,     0,     0,    67,     0,     0,     0,     0,    55,
      52,    53,    54,    49,     0,    37,    41,    46,    48,     0,
       0,     0,     0,     0,     0,     0,    23,     0,     9,     0,
       0,    12,    10,     0,    11,     0,     0,    26,    57,    58,
      59,     0,     0,    50,    51,    24,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    22,    21,     0,     7,
       8,    13,    14,     0,    25,    27,    66,    47,    36,    31,
      32,    33,    34,    35,    38,    39,    40,    42,    43,    45,
      44,     0,     0,    17,     0,    15,    16,    18,     0,     0,
       0,     0,    28,    29,     0,     0,     0,    19,    20,    56,
       0,     0,     0,     0,    30,     0,     0,     0,    65,     0,
      61,     0,    62,     0,     0,    64,     0,     0,     0,    63,
      60
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -79,   -79,   185,   -79,   -79,   -22,   -79,   -79,   -79,   -79,
     -79,   -55,   -13,   -79,   -78,   -25,   113,     6,    15,   -23,
     104,   -79,   -79,   -79,    51,   -79,   -79,    -6,   -79
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,    47,    48,    49,    50,    51,
      52,    85,    33,    54,    55,    34,    35,    36,    37,    38,
      56,    57,    58,    59,    60,   142,     6,    14,    15
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      18,    62,   112,    61,    26,   144,    16,     7,    26,   121,
      53,     9,    53,     8,    24,    27,    81,    28,     1,    27,
      11,    28,    87,    12,    17,    39,    90,    39,   115,   116,
      65,    29,    86,   120,    40,    53,    17,    30,    31,    32,
      13,    66,    63,    64,    67,    68,    69,    70,    71,    72,
      73,    41,    19,    74,   111,    20,    21,   114,   139,    22,
      87,    87,    42,   127,   128,    87,   130,    53,   122,    23,
      86,    86,    43,    44,    45,    86,    46,    29,   104,   105,
     106,    29,    46,    30,    31,    32,    17,    30,    31,    32,
     107,   108,   109,   110,    25,    87,    87,    97,    87,    88,
     132,    22,    79,    80,    82,    86,    86,    83,    86,   135,
      66,   137,    84,    67,    68,    69,    70,    71,    53,   124,
      53,    89,   147,    53,   148,    96,   129,   126,    91,    92,
      93,    53,    66,    53,    94,    67,    68,    69,    70,    71,
      66,   118,    95,    67,    68,    69,    70,    71,    75,    76,
     117,   119,    66,   125,    77,    67,    68,    69,    70,    71,
     131,   113,   134,    66,   133,    78,    67,    68,    69,    70,
      71,    66,   136,   138,    67,    68,    69,    70,    71,    98,
      99,   100,   101,   102,   103,   140,   143,   146,   141,    10,
     149,   150,   145,     0,     0,     0,     0,   123
};

static const yytype_int16 yycheck[] =
{
      13,    26,    80,    25,     3,     8,    12,    75,     3,     8,
      23,     0,    25,    81,    20,    14,    41,    16,    79,    14,
       3,    16,    45,     3,    81,    30,    48,    30,    83,    84,
       6,    76,    45,    88,    39,    48,    81,    82,    83,    84,
      79,    17,    27,    28,    20,    21,    22,    23,    24,    15,
      16,    56,     4,    19,    79,    10,     4,    82,   136,     5,
      83,    84,    67,   118,   119,    88,   121,    80,    93,     8,
      83,    84,    77,    78,    79,    88,    81,    76,    72,    73,
      74,    76,    81,    82,    83,    84,    81,    82,    83,    84,
      75,    76,    77,    78,     8,   118,   119,     4,   121,     3,
     125,     5,     3,     3,     3,   118,   119,    28,   121,   131,
      17,   133,    27,    20,    21,    22,    23,    24,   131,     4,
     133,     7,   144,   136,   146,     7,     4,     4,    26,    26,
      25,   144,    17,   146,    26,    20,    21,    22,    23,    24,
      17,    10,    26,    20,    21,    22,    23,    24,    12,    13,
      26,    10,    17,    26,    18,    20,    21,    22,    23,    24,
       8,    26,     7,    17,     8,    29,    20,    21,    22,    23,
      24,    17,    26,     7,    20,    21,    22,    23,    24,    66,
      67,    68,    69,    70,    71,     7,     4,     8,    31,     4,
       7,     7,   141,    -1,    -1,    -1,    -1,    93
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    79,    86,    87,    88,    89,   111,    75,    81,     0,
      87,     3,     3,    79,   112,   113,   112,    81,    97,     4,
      10,     4,     5,     8,   112,     8,     3,    14,    16,    76,
      82,    83,    84,    97,   100,   101,   102,   103,   104,    30,
      39,    56,    67,    77,    78,    79,    81,    90,    91,    92,
      93,    94,    95,    97,    98,    99,   105,   106,   107,   108,
     109,    90,   100,   103,   103,     6,    17,    20,    21,    22,
      23,    24,    15,    16,    19,    12,    13,    18,    29,     3,
       3,   100,     3,    28,    27,    96,    97,   104,     3,     7,
      90,    26,    26,    25,    26,    26,     7,     4,   101,   101,
     101,   101,   101,   101,   102,   102,   102,   103,   103,   103,
     103,   100,    99,    26,   100,    96,    96,    26,    10,    10,
      96,     8,   100,   105,     4,    26,     4,    96,    96,     4,
      96,     8,   100,     8,     7,    90,    26,    90,     7,    99,
       7,    31,   110,     4,     8,   109,     8,    90,    90,     7,
       7
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    85,    86,    87,    87,    88,    88,    89,    90,    90,
      91,    91,    91,    91,    91,    92,    93,    94,    95,    96,
      96,    96,    96,    97,    97,    98,    98,    98,    99,    99,
      99,   100,   100,   100,   100,   100,   100,   100,   101,   101,
     101,   101,   102,   102,   102,   102,   102,   103,   103,   103,
     103,   103,   104,   104,   104,   104,   105,   106,   106,   106,
     107,   108,   109,   110,   110,   110,   111,   112,   112,   112,
     113
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     8,     2,     1,
       1,     1,     1,     2,     2,     3,     3,     3,     3,     3,
       3,     1,     1,     1,     4,     2,     1,     2,     3,     3,
       5,     3,     3,     3,     3,     3,     3,     1,     3,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     1,     1,
       2,     2,     1,     1,     1,     1,     4,     1,     1,     1,
      11,     7,     8,     4,     2,     0,     8,     3,     1,     0,
       2
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
#line 122 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_Program)=new _Program((yyvsp[0].c_functionList));
    root = (yyval.c_Program);
}
#line 1475 "parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 129 "compiler.y" /* yacc.c:1646  */
    {
    (yyvsp[0].c_functionList)->push_back((yyvsp[-1].c_Function));
    (yyval.c_functionList)=(yyvsp[0].c_functionList);

}
#line 1485 "parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 134 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_functionList)=new _FunctionList();
    (yyval.c_functionList)->push_back((yyvsp[0].c_Function));
}
#line 1494 "parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 142 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_Function)=new _Function((yyvsp[0].c_mainFunction));
}
#line 1502 "parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 146 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_Function)=new _Function((yyvsp[0].c_Subroutine));
}
#line 1510 "parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 153 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_mainFunction)=new _mainFunction((yyvsp[-4].c_ArgsDefinitionList),(yyvsp[-1].c_StatementList));
}
#line 1518 "parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 160 "compiler.y" /* yacc.c:1646  */
    {
    (yyvsp[0].c_StatementList)->push_back((yyvsp[-1].c_Statement));
    (yyval.c_StatementList)=(yyvsp[0].c_StatementList);

}
#line 1528 "parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 165 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_StatementList)=new _StatementList();
    (yyval.c_StatementList)->push_back((yyvsp[0].c_Statement));
}
#line 1537 "parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 173 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_Statement)=new _Statement((yyvsp[0].c_Definition));
}
#line 1545 "parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 176 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_Statement)=new _Statement((yyvsp[0].c_Expression));
}
#line 1553 "parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 179 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_Statement)=new _Statement((yyvsp[0].c_returnStatement));
}
#line 1561 "parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 182 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_Statement)=new _Statement((yyvsp[-1].c_Input));
}
#line 1569 "parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 185 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_Statement)=new _Statement((yyvsp[-1].c_Output));
}
#line 1577 "parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 191 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_Input)=new _Input((yyvsp[0].c_DataList));
}
#line 1585 "parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 196 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_Output)=new _Output((yyvsp[0].c_DataList));
}
#line 1593 "parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 201 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_returnStatement)=new _returnStatement((yyvsp[-1].c_singleExpression));
}
#line 1601 "parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 208 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_Definition)=new _Definition((yyvsp[-2].sVal),(yyvsp[-1].c_DataList));
}
#line 1609 "parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 215 "compiler.y" /* yacc.c:1646  */
    {
    (yyvsp[0].c_DataList)->push_back((yyvsp[-2].c_Variable));
    (yyval.c_DataList)=(yyvsp[0].c_DataList);
}
#line 1618 "parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 219 "compiler.y" /* yacc.c:1646  */
    {
    (yyvsp[0].c_DataList)->push_back((yyvsp[-2].c_Value));
    (yyval.c_DataList)=(yyvsp[0].c_DataList);
}
#line 1627 "parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 223 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_DataList)=new _DataList();
    (yyval.c_DataList)->push_back((yyvsp[0].c_Value));
}
#line 1636 "parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 227 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_DataList)=new _DataList();
    (yyval.c_DataList)->push_back((yyvsp[0].c_Variable));
}
#line 1645 "parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 235 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_Variable)=new _Variable((yyvsp[0].sVal));
}
#line 1653 "parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 238 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_Variable)=new _Variable((yyvsp[-3].sVal),(yyvsp[-1].c_singleExpression));
}
#line 1661 "parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 245 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_Expression)=new _Expression((yyvsp[-1].c_assignExpression));
}
#line 1669 "parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 248 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_Expression)=new _Expression((yyvsp[0].c_complexExpression));
}
#line 1677 "parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 251 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_Expression)=new _Expression((yyvsp[-1].c_functionCall));
}
#line 1685 "parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 257 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_assignExpression)= new _assignExpression((yyvsp[-2].c_Variable),(yyvsp[0].c_singleExpression));
}
#line 1693 "parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 260 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_assignExpression)= new _assignExpression((yyvsp[-2].c_Variable),(yyvsp[0].c_functionCall));
}
#line 1701 "parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 263 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_assignExpression)= new _assignExpression((yyvsp[-4].c_Variable),(yyvsp[-1].c_DataList));
}
#line 1709 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 268 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_singleExpression) = new _singleExpression((yyvsp[-2].c_singleExpression), C_GE, (yyvsp[0].c_singleExpression));
}
#line 1717 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 271 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_singleExpression) = new _singleExpression((yyvsp[-2].c_singleExpression), C_GT, (yyvsp[0].c_singleExpression));
}
#line 1725 "parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 274 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_singleExpression) = new _singleExpression((yyvsp[-2].c_singleExpression), C_LE, (yyvsp[0].c_singleExpression));
}
#line 1733 "parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 277 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_singleExpression) = new _singleExpression((yyvsp[-2].c_singleExpression), C_LT, (yyvsp[0].c_singleExpression));
}
#line 1741 "parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 280 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_singleExpression) = new _singleExpression((yyvsp[-2].c_singleExpression), C_EQ, (yyvsp[0].c_singleExpression));
}
#line 1749 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 283 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_singleExpression) = new _singleExpression((yyvsp[-2].c_singleExpression), C_NE, (yyvsp[0].c_singleExpression));
}
#line 1757 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 286 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_singleExpression) = (yyvsp[0].c_singleExpression);
}
#line 1765 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 292 "compiler.y" /* yacc.c:1646  */
    { 
    (yyval.c_singleExpression) = new _singleExpression((yyvsp[-2].c_singleExpression), C_ADD, (yyvsp[0].c_singleExpression)); 
}
#line 1773 "parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 295 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_singleExpression) = new _singleExpression((yyvsp[-2].c_singleExpression), C_SUB, (yyvsp[0].c_singleExpression)); 
}
#line 1781 "parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 298 "compiler.y" /* yacc.c:1646  */
    { 
    (yyval.c_singleExpression) = new _singleExpression((yyvsp[-2].c_singleExpression), C_OR, (yyvsp[0].c_singleExpression)); 
}
#line 1789 "parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 301 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_singleExpression) = (yyvsp[0].c_singleExpression); 
}
#line 1797 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 308 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_singleExpression) = new _singleExpression((yyvsp[-2].c_singleExpression), C_MUL, (yyvsp[0].c_singleExpression));
}
#line 1805 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 311 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_singleExpression) = new _singleExpression((yyvsp[-2].c_singleExpression), C_DIV, (yyvsp[0].c_singleExpression));
}
#line 1813 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 314 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_singleExpression) = new _singleExpression((yyvsp[-2].c_singleExpression), C_MOD, (yyvsp[0].c_singleExpression));
}
#line 1821 "parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 317 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_singleExpression) = new _singleExpression((yyvsp[-2].c_singleExpression), C_AND, (yyvsp[0].c_singleExpression));
}
#line 1829 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 320 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_singleExpression) = (yyvsp[0].c_singleExpression); 
}
#line 1837 "parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 326 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_singleExpression)=(yyvsp[-1].c_singleExpression);
}
#line 1845 "parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 329 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_singleExpression)=new _singleExpression((yyvsp[0].c_Value));
}
#line 1853 "parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 332 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_singleExpression)=new _singleExpression((yyvsp[0].c_Variable));
}
#line 1861 "parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 335 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_singleExpression)=new _singleExpression(new _singleExpression(new _Value(1)),C_XOR,(yyvsp[0].c_singleExpression));
}
#line 1869 "parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 338 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_singleExpression)=new _singleExpression(new _singleExpression(new _Value(1)),C_SUB,(yyvsp[0].c_singleExpression));
}
#line 1877 "parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 346 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_Value)=new _Value((yyvsp[0].floatVal));
}
#line 1885 "parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 349 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_Value)=new _Value((yyvsp[0].intVal));
}
#line 1893 "parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 352 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_Value)=new _Value((yyvsp[0].sVal));
}
#line 1901 "parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 355 "compiler.y" /* yacc.c:1646  */
    {
    cout<<"char"<<endl;
    (yyval.c_Value)=new _Value((yyvsp[0].cVal));
}
#line 1910 "parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 362 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_functionCall)=new _functionCall((yyvsp[-3].sVal),(yyvsp[-1].c_DataList));
}
#line 1918 "parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 368 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_complexExpression)=new _complexExpression((yyvsp[0].c_forSTMT));
}
#line 1926 "parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 371 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_complexExpression)=new _complexExpression((yyvsp[0].c_whileSTMT));
}
#line 1934 "parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 374 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_complexExpression)=new _complexExpression((yyvsp[0].c_ifSTMT));
}
#line 1942 "parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 382 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_forSTMT)=new _forStatement((yyvsp[-8].c_assignExpression),(yyvsp[-6].c_singleExpression),(yyvsp[-4].c_assignExpression),(yyvsp[-1].c_StatementList));
}
#line 1950 "parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 389 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_whileSTMT)=new _whileStatement((yyvsp[-4].c_singleExpression),(yyvsp[-1].c_StatementList));
}
#line 1958 "parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 396 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_ifSTMT)=new _ifStatement((yyvsp[-5].c_singleExpression),(yyvsp[-2].c_StatementList),(yyvsp[0].c_elsePart));
}
#line 1966 "parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 403 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_elsePart)=new _elsePart((yyvsp[-1].c_StatementList));
}
#line 1974 "parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 406 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_elsePart)= new _elsePart((yyvsp[0].c_ifSTMT));
}
#line 1982 "parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 409 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_elsePart)=new _elsePart();//空body
}
#line 1990 "parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 416 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_Subroutine)=new _Subroutine((yyvsp[-7].sVal),(yyvsp[-6].sVal),(yyvsp[-4].c_ArgsDefinitionList),(yyvsp[-1].c_StatementList));
}
#line 1998 "parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 421 "compiler.y" /* yacc.c:1646  */
    {
    (yyvsp[0].c_ArgsDefinitionList)->push_back((yyvsp[-2].c_ArgsDefinition));
    (yyval.c_ArgsDefinitionList)=(yyvsp[0].c_ArgsDefinitionList);
}
#line 2007 "parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 425 "compiler.y" /* yacc.c:1646  */
    {
    (yyval.c_ArgsDefinitionList)=new _ArgsDefinitionList();
    (yyval.c_ArgsDefinitionList)->push_back((yyvsp[0].c_ArgsDefinition));
}
#line 2016 "parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 429 "compiler.y" /* yacc.c:1646  */
    {
   (yyval.c_ArgsDefinitionList)=new _ArgsDefinitionList(); 
}
#line 2024 "parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 434 "compiler.y" /* yacc.c:1646  */
    {
    if(*(yyvsp[-1].sVal)=="int"){
        (yyval.c_ArgsDefinition)=new _argsDefinition(C_INTEGER,(yyvsp[0].c_Variable));
    }
    else if(*(yyvsp[-1].sVal)=="double"){
        (yyval.c_ArgsDefinition)=new _argsDefinition(C_REAL,(yyvsp[0].c_Variable));
    }
    else if(*(yyvsp[-1].sVal)=="char"){
        (yyval.c_ArgsDefinition)=new _argsDefinition(C_CHAR,(yyvsp[0].c_Variable));
    }
    else if(*(yyvsp[-1].sVal)=="boolean"){
        (yyval.c_ArgsDefinition)=new _argsDefinition(C_BOOLEAN,(yyvsp[0].c_Variable));
    }
}
#line 2043 "parser.cpp" /* yacc.c:1646  */
    break;


#line 2047 "parser.cpp" /* yacc.c:1646  */
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
