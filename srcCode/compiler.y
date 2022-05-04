%{
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "ast.h"

void yyerror(const char *s) { 
    std::printf("Error: %s\n", s);
    std::exit(1); 
}

int yylex(void);


int main()
{
	int yyparse (void);
}

_Program *root;
%}

%union{
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
    _returnStatement *c_returnStatement;
    _SingleExpressionList *c_singleExpressionList;
    _Term *c_Term;
}



//特殊符号

%token LP RP LB RB RCB LCB DOT COMMA COLON MUL DIV NOT PLUS MINUS NOEQUAL
%token AND OR GE GT LE LT EQUAL ASSIGN SEMI 



//c 语言关键词

%token IF ELSE SIGNED UNION THIS UNSIGNED CONST GOTO VIRTUAL FOR 
%token FLOAT BREAK AUTO CLASS OPERATOR CASE DO LONG TYPEDEF STATIC FRIEND
%token TEMPLATE DEFAULT NEW VOID REGISTER RETURN ENUM INLINE TRY SHORT CONTINUE 
%token SIZEOF SWITCH PRIVATE PROTECTED ASM WHILE CATCH DELETE PUBLIC VOLATILE 
%token STRUCT PRINTF SCANF MAIN STRING CHAR



//终结符

%token SYS_TYPE SYS_BOOL IDENTIFIER REAL INTEGER STRING


%type<sVal>SYS_TYPE  IDENTIFIER STRING
%type<intVal>INTEGER
%type<floatVal>REAL
//中间变量类型定义 暂略

%type<c_Program>                     Program
%type<c_functionList>                functionList
%type<c_Function>                    Function
%type<c_mainFunction>                mainFunc
%type<c_Subroutine>                  Subroutine 
%type<c_ArgsList>                    ArgsList
%type<c_StatementList>               StatementList
%type<c_Statement>                   Statement
%type<c_Definition>                  Definition
%type<c_Expression>                  Expression
%type<c_singleExpression>            singleExpression
%type<c_VarList>                     VarList
%type<c_Variable>                    Variable
%type<c_assignExpression>            assignExpression
%type<c_complexExpression>           complexExpression
%type<c_functionCall>                functionCall
%type<c_forSTMT>                     forSTMT
%type<c_whileSTMT>                   whileSTMT
%type<c_ifSTMT>                      ifSTMT
%type<c_ArgsDefinitionList>          ArgsDefinitionList
%type<c_Data>                        Value
%type<c_elsePart>                    elsePart
%type<c_ArgsDefinition>              ArgsDefinition
%type<c_returnStatement>             returnStatement
%type<c_singleExpressionList>        singleExpressionList;
%type<c_Term>                        term


%start Program
%%

Program: 
functionList{
    $$=new _Program($1);
}


functionList:
Function functionList{
    $2->push_back($1);
    $$=$2;

}
|Function{
    $$=new _FunctionList();
    $$->push_back($1);
}



Function:
mainFunc{
    $$=new _Function($1);
}

|Subroutine{
    $$=new _Function($1);
}



mainFunc:
SYS_TYPE MAIN LP ArgsDefinitionList RP LCB StatementList RCB{
    $$=new _mainFunction($4,$7);
}



StatementList:
Statement StatementList{
    $2->push_back($1);
    $$=$2;

}
|Statement{
    $$=new _StatementList();
    $$->push_back($1);
}



Statement:
Definition{
    $$=new _Statement($1);
}

|Expression{
    $$=new _Statement($1);
}

|returnStatement{
    $$=new _Statement($1);
}

returnStatement:
RETURN singleExpressionList SEMI{
    $$=new _returnExpression($2);
}



Definition:
SYS_TYPE IDENTIFIER SEMI{
    $$=new _Definition($1,$2);
}



VarList:
Variable COMMA VarList{
    $3->push_back($1);
    $$=$3;
}
|Variable{
    $$=new _VarList();
    $$->push_back($1);
}



Variable:
IDENTIFIER{
    $$=new _Variable($1);
}
|IDENTIFIER LB Expression RB{
    $$=new _Variable($1,$3);
}



Expression:
assignExpression SEMI{
    $$=new _Expression($1);
}
|complexExpression{
    $$=new _Expression($1);
}
|functionCall SEMI{
    $$=new _Expression($1);
}



assignExpression:
Variable ASSIGN singleExpressionList{
    $$= new _assignExpression($1,$3);
}


singleExpressionList:
singleExpression singleExpressionList{
    $$=$2;
    $$->push_back($1);
}
|singleExpression{
    $$=new _singleExpressionList();
    $$->push_back($1);
}

singleExpression:
term ADD{
    $$=new _singleExpression($1,C_ADD);
}
|term SUB{
    $$=new _singleExpression($1,C_SUB);
}
|term MUL{
    $$=new _singleExpression($1,C_MUL);
}
|term DIV{
    $$=new _singleExpression($1,C_DIV);
}
|term AND{
    $$=new _singleExpression($1,C_AND);
}
|term OR{
    $$=new _singleExpression($1,C_OR);
}
|term EQUAL{
    $$=new _singleExpression($1,C_EQUAL);
}
|term NOEQUAL{
    $$=new _singleExpression($1,C_NOEQUAL);
}
|term{
    $$=new _singleExpression($1);
}

term:
Value{
    $$=new _Term($1);
}
|Variable{
    $$=new _Term($1);
}
|LP singleExpressionList RP{
    $$=new _Term($1);
}



Value:
REAL{
    $$=new _Value($1);
}
|INTEGER{
    $$=new _Value($1);
}
|STRING{
    $$=new _Value($1);
}


functionCall:
IDENTIFIER LP VarList RP{
    $$=new _functionCall($1,$3);
}

complexExpression:
forSTMT{
    $$=new _complexExpression($1);
}
|whileSTMT{
    $$=new _complexExpression($1);
}
|ifSTMT{
    $$=new _complexExpression($1);
}



forSTMT:
FOR LP assignExpression SEMI singleExpressionList SEMI assignExpression RP LCB StatementList RCB
{
    $$=new _forStatement($3,$5,$7,$10);
}



whileSTMT:
WHILE LP singleExpressionList RB LCB StatementList RCB{
    $$=new _whileStatement($3,$6);
}



ifSTMT:
IF LP singleExpressionList RP LCB StatementList RCB elsePart{
    $$=new _ifStatement($3,$6,$8);
}



elsePart:
ELSE LCB StatementList RCB{
    $$=new _elsePart($3);
}
|ELSE ifSTMT{
    $$= new _elsePart($2);
}
|{
    $$=new _elsePart();//空body
}



Subroutine:
SYS_TYPE IDENTIFIER LP ArgsDefinitionList RP LCB StatementList RCB{
    $$=new _Subroutine($1,$2,$4,$7);
}

ArgsDefinitionList:
ArgsDefinition COMMA ArgsDefinitionList{
    $3->push_back($1);
    $$=$3;
}
|ArgsDefinition{
    $$=new _ArgsDefinitionList();
    $$->push_back($1);
}
|{
   $$=new _ArgsDefinitionList(); 
}

ArgsDefinition:
SYS_TYPE Variable{
    $$=new _argsDefinition($1,$2);
}























