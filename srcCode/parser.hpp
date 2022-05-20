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
    NE = 272,
    AND = 273,
    OR = 274,
    GE = 275,
    GT = 276,
    LE = 277,
    LT = 278,
    EQ = 279,
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
    ENDL = 334,
    SETW = 335,
    SYS_TYPE = 336,
    SYS_BOOL = 337,
    IDENTIFIER = 338,
    REAL = 339,
    INTEGER = 340,
    STRING = 341
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 24 "compiler.y"

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
    _InputList *c_InputList;
    _OutputList *c_OutputList;
    _StructList *c_StructList;
    _Struct *c_Struct;
    _DefinitionList *c_DefinitionList;

#line 186 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
