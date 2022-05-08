%{
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "ast.h"

void yyerror(const char *s) { 
    std::printf("Error: %s\n", s);
    std::exit(1); 
}

int yylex(void);


// int main()
// {
// 	int yyparse();
// }

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
}



//特殊符号

%token LP RP LB RB RCB LCB DOT COMMA COLON MUL DIV NOT ADD SUB NOEQUAL
%token AND OR GE GT LE LT EQUAL ASSIGN SEMI LD RD MOD



//c 语言关键词

%token IF ELSE SIGNED UNION THIS UNSIGNED CONST GOTO VIRTUAL FOR 
%token FLOAT BREAK AUTO CLASS OPERATOR CASE DO LONG TYPEDEF STATIC FRIEND
%token TEMPLATE DEFAULT NEW VOID REGISTER RETURN ENUM INLINE TRY SHORT CONTINUE 
%token SIZEOF SWITCH PRIVATE PROTECTED ASM WHILE CATCH DELETE PUBLIC VOLATILE 
%token STRUCT PRINTF SCANF MAIN CHAR CIN COUT



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
%type<c_StatementList>               StatementList
%type<c_Statement>                   Statement
%type<c_Definition>                  Definition
%type<c_Expression>                  Expression
%type<c_singleExpression>            singleExpression term expr factor
%type<c_DataList>                    DataList
%type<c_Variable>                    Variable
%type<c_assignExpression>            assignExpression
%type<c_complexExpression>           complexExpression
%type<c_functionCall>                functionCall
%type<c_forSTMT>                     forSTMT
%type<c_whileSTMT>                   whileSTMT
%type<c_ifSTMT>                      ifSTMT
%type<c_ArgsDefinitionList>          ArgsDefinitionList
%type<c_Value>                       Value
%type<c_elsePart>                    elsePart
%type<c_ArgsDefinition>              ArgsDefinition
%type<c_returnStatement>             returnStatement
%type<c_Input>                       Input
%type<c_Output>                      Output


%start Program
%%

Program: 
functionList{
    $$=new _Program($1);
    root=$$;
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
|Input SEMI{
    $$=new _Statement($1);
}
|Output SEMI{
    $$=new _Statement($1);
}


Input:
CIN RD DataList{
    $$=new _Input($3);
}

Output:
COUT LD DataList{
    $$=new _Output($3);
}

returnStatement:
RETURN singleExpression SEMI{
    $$=new _returnStatement($2);
}



Definition:
SYS_TYPE Variable SEMI{
    $$=new _Definition($1,$2);
}



DataList:
Variable COMMA DataList{
    $3->push_back($1);
    $$=$3;
}
|Value COMMA DataList{
    $3->push_back($1);
    $$=$3;
}
|Value{
    $$=new _DataList();
    $$->push_back($1);
}
|Variable{
    $$=new _DataList();
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
Variable ASSIGN singleExpression{
    $$= new _assignExpression($1,$3);
}
|Variable ASSIGN functionCall{
    $$= new _assignExpression($1,$3);
}

singleExpression : 
singleExpression  GE  expr {
    $$ = new _singleExpression($1, C_GE, $3);
}
|singleExpression  GT  expr {
    $$ = new _singleExpression($1, C_GT, $3);
}
|singleExpression  LE  expr {
    $$ = new _singleExpression($1, C_LE, $3);
}
|singleExpression  LT  expr {
    $$ = new _singleExpression($1, C_LT, $3);
}
|singleExpression  EQUAL  expr {
    $$ = new _singleExpression($1, C_EQUAL, $3);
}
|singleExpression  NOEQUAL  expr {
    $$ = new _singleExpression($1, C_NOEQUAL, $3);
}
|expr {
    $$ = $1;
}
;

expr : 
expr  ADD  term{ 
    $$ = new _singleExpression($1, C_ADD, $3); 
}
|expr  SUB  term {
    $$ = new _singleExpression($1, C_SUB, $3); 
}
|expr  OR  term { 
    $$ = new _singleExpression($1, C_OR, $3); 
}
|term {
    $$ = $1; 
}
;


term : 
term  MUL  factor {
    $$ = new _singleExpression($1, C_MUL, $3);
}
|term  DIV  factor {
    $$ = new _singleExpression($1, C_DIV, $3);
}
|term  MOD  factor {
    $$ = new _singleExpression($1, C_MOD, $3);
}
|term  AND  factor {
    $$ = new _singleExpression($1, C_AND, $3);
}
|factor {
    $$ = $1; 
}


factor:
LP singleExpression RP{
    $$=$2;
}
|Value{
    $$=new _singleExpression($1);
}
|Variable{
    $$=new _singleExpression($1);
}
|NOT factor{
    $$=new _singleExpression(new _singleExpression(new _Value(1)),C_XOR,$2);
}
|SUB factor{
    $$=new _singleExpression(new _singleExpression(new _Value(1)),C_SUB,$2);
}




Value:
REAL{
    cout<<"real";
    $$=new _Value($1);
}
|INTEGER{
    cout<<"int";
    $$=new _Value($1);
}
|STRING{
    cout<<"string";
    $$=new _Value($1);
}


functionCall:
IDENTIFIER LP DataList RP{
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
FOR LP assignExpression SEMI singleExpression SEMI assignExpression RP LCB StatementList RCB
{
    $$=new _forStatement($3,$5,$7,$10);
}



whileSTMT:
WHILE LP singleExpression RP LCB StatementList RCB{
    $$=new _whileStatement($3,$6);
}



ifSTMT:
IF LP singleExpression RP LCB StatementList RCB elsePart{
    $$=new _ifStatement($3,$6,$8);
}



elsePart:
ELSE LCB StatementList RCB{
    cout<<"else";
    $$=new _elsePart($3);
}
|ELSE ifSTMT{
    cout<<"else";
    $$= new _elsePart($2);
}
|{
    cout<<"else";
    $$=new _elsePart();//空body
}



Subroutine:
SYS_TYPE IDENTIFIER LP ArgsDefinitionList RP LCB StatementList RCB{
    cout<<"subr";
    $$=new _Subroutine($1,$2,$4,$7);
}

ArgsDefinitionList:
ArgsDefinition COMMA ArgsDefinitionList{
    cout<<"argsL";
    $3->push_back($1);
    $$=$3;
}
|ArgsDefinition{
    cout<<"argsL";
    $$=new _ArgsDefinitionList();
    $$->push_back($1);
}
|{
    cout<<"argsL";
   $$=new _ArgsDefinitionList(); 
   
}

ArgsDefinition:
SYS_TYPE Variable{
    if(*$1=="int"){
        $$=new _argsDefinition(C_INTEGER,$2);
        cout<<"args";
    }
    else if(*$1=="double"){
        $$=new _argsDefinition(C_REAL,$2);
        cout<<"args";
    }
    else if(*$1=="char"){
        $$=new _argsDefinition(C_CHAR,$2);
        cout<<"args";
    }
    else if(*$1=="boolean"){
        $$=new _argsDefinition(C_BOOLEAN,$2);
        cout<<"args";
    }
}























