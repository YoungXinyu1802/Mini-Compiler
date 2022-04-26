%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int yywrap()
{
	return 1;
}

void yyerror(const char *s)
{
	printf("[error] %s\n", s);
}

int main()
{
	yyparse();
	return 0;
}

%}

%union{
    string *sVal;
    int intVal;
    double floatVal;
    bool bVal;
    char cVal;
    Node *node;
    //基础变量类型定义，暂略
}

//特殊符号
%token LP RP LB RB RCB LCB DOT COMMA COLON MUL DIV NOT PLUS MINUS NOEQUAL
%token AND OR GE GT LE LT EQUAL ASSIGN SEMI

//c 语言关键词
%token IF ELSE WHILE SIGNED UNION THIS UNSIGNED CONST GOTO VIRTUAL FOR 
%token FLOAT BREAK AUTO CLASS OPERATOR CASE DO LONG TYPEDEF STATIC FRIEND
%token TEMPLATE DEFAULT NEW VOID REGISTER RETURN ENUM INLINE TRY SHORT CONTINUE 
%token SIZEOF SWITCH PRIVATE PROTECTED ASM WHILE CATCH DELETE PUBLIC VOLATILE 
%token STRUCT PRINTF SCANF MAIN

//终结符
%token SYS_TYPE SYS_BOOL INDENTIFIER REAL INTEGER

//中间变量类型定义 暂略
%type<>                     program
%type<>                     functionList
%type<>                     Function
%type<>                     mainFunc
%type<>                     Subroutine
%type<>                     mainFunc
%type<>                     Statement
%type<>                     StatementList
%type<>                     Definition
%type<>                     Expression
%type<>                     singleExpression
%type<>                     varList
%type<>                     Identifier
%type<>                     Variable
%type<>                     assignExpression
%type<>                     complexExpression
%type<>                     functionCall
%type<>                     forSTMT
%type<>                     whileSTMT
%type<>                     ifSTMT
%type<>                     elsePart
%type<>                     argsList
%type<>                     argsDefinitionList





%%
Program: 
|functionList{
    $$=$1;
}

functionList:
|Function functionList{
    $2.add($1);
    $$=$2;
}
|Function{
    $$=new functionList();
    $$.add($1);
}

Function:
|mainFunc{
    $$=$1;
}
|Subroutine{
    $$=$1;
}

mainFunc:
|SYS_TYPE MAIN LP ArgsList RP LCB Statements RCB{
    $$=new mainFunc($4,$7);
}

StatementList:
|Statement StatementList{
    $2.add($1);
    $$=$2;
}
|Statement{
    $$=new StatementList();
    $$.add($1);
}

Statement:
|Definition{
    $$=$1;
}
|Expression{
    $$=$1;
}
|RETURN singleExpression SEMI{
    $$=new returnExpression($2);
}

Definition:
|SYS_TYPE varList SEMI{
    $$=new Definition($1,$2);
}

varList:
|Variable COMMA varList{
    $3.add($1);
    $$=$3;
}
|Variable{
    $$=new varList().add($1);
}

Variable:
|IDENTIFIER{
    $1=new Identifier($1);
}
|IDENTIFIER LB Expression RB{
    $1=new Array($1,$3);
}

Expression:
|assignEXpression SEMI{
    $$=$1;
}
|complexExpression{
    $$=$1;
}
|functionCall SEMI{
    $$=$1;
}

assignExpression:
|Variable ASSIGN singleExpression{
    $$= new assignExpression($1,$3);
}

singleExpression:
|Variable PLUS singleExpression{
    $$=new binaryOpExpression($1,"PLUS",$3);
}
|Variable MINUS singleExpression{
    $$=new binaryOpExpression($1,"MINUS",$3);
}
|Variable MUL singleExpression{
    $$=new binaryOpExpression($1,"MUL",$3);
}
|Variable DIV singleExpression{
    $$=new binaryOpExpression($1,"DIV",$3);
}
|Variable GE singleExpression{
    $$=new binaryOpExpression($1,"GE",$3);
}
|Variable GT singleExpression{
    $$=new binaryOpExpression($1,"GT",$3);
}
|Variable LE singleExpression{
    $$=new binaryOpExpression($1,"LE",$3);
}
|Variable LT singleExpression{
    $$=new binaryOpExpression($1,"LT",$3);
}
|Variable EQUAL singleExpression{
    $$=new binaryOpExpression($1,"equal",$3);
}
|Variable NOEQUAL singleExpression{
    $$=new binaryOpExpression($1,"noequal",$3);
}
|Variable AND singleExpression{
    $$=$1 && $3;
}
|Variable OR singleExpression{
    $$=$1 || $3;
}
|functionCall{
    $$=$1;
}
|Variable{
    $$=$1
}
|Value{
    $$=$1;
}

Value:
|REAL{
    $$=$1;
}
|INTEGER{
    $$=$1;
}
|STRING{
    $$=$1;
}

functionCall:
|IDENTIFIER LP ArgsList RP{
    $$=new functionCall($1,$3);
}

complexExpression:
|forStmt{
    $$=$1;
}
|whileSTMT{
    $$=$1;
}
|ifSTMT{
    $$=$1;
}

forSTMT:
|FOR LP assignExpression SEMI singleExpression SEMI assignExpression RP LCB statementList RCB
{
    $$=new forSTMT($3,$5,$7,%9);
}

whileSTMT:
|WHILE LP singleExpression RB LCB statementList RCB{
    $$=new whileStatement($3,$6);
}

ifSTMT:
|IF LP singleExpression RP LCB statementList RCB elsePART{
    $$=new ifSTMT($3,$6,$8);
}

elsePart:
|ELSE LCB statementList RCB{
    $$=new elsePart($3);
}
|ELSE ifSTMT{
    $$=$1;
}
|{
    $$=new elsePart();//空body,应该能支持这个选项
}

Subroutine:
|SYS_TYPE IDENTIFIER LP argsDefinitionList RP LCB statementList RCB{
    //这一块应该怎么定义？？？
    $$=new Subroutine($1,$2,$4,$7);
}

argsList:
|Variable COMMA argsList{
    $$=$3.add($1);
}
|Variable{
    $$=new argsList();
    $$.add($1);
}
|{
    $$=new argsList();
}

argsDefinitionList:
|SYS_TYPE Variable COMMA argsDefinitionList{
    $$=$4.add($1,$2);
}
|SYS_TYPE Variable{
    $$=new argsDefinitionList();
    $$.add($1,$2);
}
|{
   $$=new argsDefinitionList(); 
}












