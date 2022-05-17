/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_COMPILER_TAB_H_INCLUDED
# define YY_YY_COMPILER_TAB_H_INCLUDED
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
    PLUS = 270,
    MINUS = 271,
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
    IF = 282,
    ELSE = 283,
    SIGNED = 284,
    UNION = 285,
    THIS = 286,
    UNSIGNED = 287,
    CONST = 288,
    GOTO = 289,
    VIRTUAL = 290,
    FOR = 291,
    FLOAT = 292,
    BREAK = 293,
    AUTO = 294,
    CLASS = 295,
    OPERATOR = 296,
    CASE = 297,
    DO = 298,
    LONG = 299,
    TYPEDEF = 300,
    STATIC = 301,
    FRIEND = 302,
    TEMPLATE = 303,
    DEFAULT = 304,
    NEW = 305,
    VOID = 306,
    REGISTER = 307,
    RETURN = 308,
    ENUM = 309,
    INLINE = 310,
    TRY = 311,
    SHORT = 312,
    CONTINUE = 313,
    SIZEOF = 314,
    SWITCH = 315,
    PRIVATE = 316,
    PROTECTED = 317,
    ASM = 318,
    WHILE = 319,
    CATCH = 320,
    DELETE = 321,
    PUBLIC = 322,
    VOLATILE = 323,
    STRUCT = 324,
    PRINTF = 325,
    SCANF = 326,
    MAIN = 327,
    STRING = 328,
    CHAR = 329,
    SYS_TYPE = 330,
    SYS_BOOL = 331,
    IDENTIFIER = 332,
    REAL = 333,
    INTEGER = 334
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 25 "compiler.y"

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
    _ArgsList *c_ArgsList;
    _Statement *c_Statement;
    _StatementList *c_StatementList;
    _Definition *c_Definition;
    _Expression *c_Expression;
    _singleExpression *c_singleExpression;
    _VarList *c_VarList;
    _Variable *c_Variable;
    _assignExpression *c_assignExpression;
    _complexExpression *c_complexExpression;
    _functionCall *c_functionCall;
    _forStatement *c_forSTMT;
    _whileStatement *c_whileSTMT;
    _ifStatement *c_ifSTMT;
    _Data *c_Data;
    _elsePart *c_elsePart;
    _ArgsDefinitionList *c_ArgsDefinitionList;
    _argsDefinition *c_ArgsDefinition;

#line 170 "compiler.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_COMPILER_TAB_H_INCLUDED  */
