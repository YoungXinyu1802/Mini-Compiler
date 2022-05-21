%{
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
    _InputList *c_InputList;
    _OutputList *c_OutputList;
    _StructList *c_StructList;
    _Struct *c_Struct;
    _DefinitionList *c_DefinitionList;
}



//特殊符号

%token LP RP LB RB RCB LCB DOT COMMA COLON MUL DIV NOT ADD SUB NE
%token AND OR GE GT LE LT EQ ASSIGN SEMI LD RD MOD



//c 语言关键词

%token IF ELSE SIGNED UNION THIS UNSIGNED CONST GOTO VIRTUAL FOR 
%token FLOAT BREAK AUTO CLASS OPERATOR CASE DO LONG TYPEDEF STATIC FRIEND
%token TEMPLATE DEFAULT NEW VOID REGISTER RETURN ENUM INLINE TRY SHORT CONTINUE 
%token SIZEOF SWITCH PRIVATE PROTECTED ASM WHILE CATCH DELETE PUBLIC VOLATILE 
%token STRUCT PRINTF SCANF MAIN CHAR CIN COUT ENDL SETW



//终结符

%token SYS_TYPE SYS_BOOL IDENTIFIER REAL INTEGER STRING


%type<sVal>SYS_TYPE  IDENTIFIER STRING
%type<intVal>INTEGER
%type<floatVal>REAL
%type<cVal>CHAR
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
%type<c_InputList>                   InputList
%type<c_OutputList>                  OutputList
%type<c_StructList>                  structList
%type<c_Struct>                      Struct
%type<c_DefinitionList>              DefinitionList


%start Program
%%

Program: 
structList functionList{
    $$=new _Program($1,$2);
    root=$$;
}

structList:
Struct structList{
    $2->push_back($1); //remain to complete
    $$=$2;
}
|Struct{
    $$=new _StructList();
    $$->push_back($1);
}
|{
    $$=new _StructList();
}

Struct:
STRUCT IDENTIFIER LCB DefinitionList RCB SEMI{
    $$=new _Struct($2,$4); //remain to complete
}

DefinitionList:
Definition DefinitionList{
    $$=$2;
    $$->push_back($1); //remain to complete
}
|Definition{
    $$=new _DefinitionList();
    $$->push_back($1);
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
CIN RD InputList{
    $$=new _Input($3);
}

Output:
COUT LD OutputList{
    $$=new _Output($3);
}
|COUT LD SETW LP Value RP LD OutputList{
    $$=new _Output($8);
    $$->setDigit($5);
}

OutputList:
Variable LD OutputList{
    $3->push_back($1);
    $$=$3;
}
|Value LD OutputList{
    $3->push_back($1);
    $$=$3;
}
|Value{
    $$=new _OutputList();
    $$->push_back($1);
}
|Variable{
    $$=new _OutputList();
    $$->push_back($1);
}
|ENDL{
    char c='\n';
    _Value* temp= new _Value(c);
    $$=new _OutputList();
    $$->push_back(temp);
}

InputList:
Variable RD InputList{
    $3->push_back($1);
    $$=$3;
}
|Variable{
    $$=new _InputList();
    $$->push_back($1);
}

returnStatement:
RETURN singleExpression SEMI{
    $$=new _returnStatement($2);
}



Definition:
SYS_TYPE DataList SEMI{
    $$=new _Definition($1,$2);
}
|STRUCT IDENTIFIER DataList SEMI{
    int a=0;
    cout<<"here"<<endl;
    $$=new _Definition(a,$2,$3);
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
|IDENTIFIER LB singleExpression RB{
    $$=new _Variable($1,$3);
}
|IDENTIFIER LB RB{
    string a="nullTest";
    $$=new _Variable($1,a);
}
|IDENTIFIER DOT IDENTIFIER{
    $$=new _Variable($1,$3);
}
|IDENTIFIER DOT IDENTIFIER LB singleExpression RB{
    $$=new _Variable($1,$3,$5);   
}
|IDENTIFIER LB singleExpression RB DOT IDENTIFIER LB singleExpression RB{
    $$=new _Variable($1,$3,$6,$8);
}
|IDENTIFIER LB singleExpression RB DOT IDENTIFIER{
    $$=new _Variable($1,$3,$6); 
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
|Variable ASSIGN  LCB DataList RCB{
    $$= new _assignExpression($1,$4);
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
|singleExpression  EQ expr {
    $$ = new _singleExpression($1, C_EQ, $3);
}
|singleExpression  NE  expr {
    $$ = new _singleExpression($1, C_NE, $3);
}
|expr {
    $$ = $1;
}


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
    $$=new _singleExpression(new _singleExpression(new _Value(0)),C_SUB,$2);
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
|CHAR{
    cout<<"char"<<endl;
    $$=new _Value($1);
}
|ENDL{
    char c='\n';
    $$=new _Value(c);
}


functionCall:
IDENTIFIER LP DataList RP{
    $$=new _functionCall($1,$3);
}
|IDENTIFIER LP RP{
    $$=new _functionCall($1);
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
    if(*$1=="int"){
        $$=new _argsDefinition(C_INTEGER,$2);
    }
    else if(*$1=="double"){
        $$=new _argsDefinition(C_REAL,$2);
    }
    else if(*$1=="char"){
        $$=new _argsDefinition(C_CHAR,$2);
    }
    else if(*$1=="boolean"){
        $$=new _argsDefinition(C_BOOLEAN,$2);
    }
}