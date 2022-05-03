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
    $$=$1;
}

|Subroutine{
    $$=$1;
}



mainFunc:
SYS_TYPE MAIN LP ArgsList RP LCB StatementList RCB{
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
    $$=$1;
}

|Expression{
    $$=$1;
}

|RETURN singleExpression SEMI{
    $$=new _returnExpression($2);
}



Definition:
SYS_TYPE IDENTIFIER SEMI{
    if(*$1=="int"){
        $$=new _Definition("int",$2);
    }
    else if(*$1=="double"){
        $$=new _Definition("double",$2);
    }
    else if(*$1=="boolean"){
        $$=new _Definition("boolean",$2);
    }
    else{
        $$=new _Definition("char",$2);   
    }
    
}



VarList:
Variable COMMA VarList{
    $3->push_back($1);
    $$=$3;
}
|Variable{
    $$=new _VarList().push_back($1);
}



Variable:
IDENTIFIER{
    $$=new _Variable($1);
}

|IDENTIFIER LB Expression RB{

    $$=new _Variable(*$1,*$3);

}



Expression:
assignExpression SEMI{
    $$=$1;
}
|complexExpression{
    $$=$1;
}
|functionCall SEMI{
    $$=$1;
}



assignExpression:
Variable ASSIGN singleExpression{
    $$= new _assignExpression($1,$3);
}


singleExpression:
Variable PLUS singleExpression{
    $$=new _singleExpression($1,"PLUS",$3);
}
|Variable MINUS singleExpression{
    $$=new _singleExpression($1,"MINUS",$3);
}
|Variable MUL singleExpression{
    $$=new _singleExpression($1,"MUL",$3);
}
|Variable DIV singleExpression{
    $$=new _singleExpression($1,"DIV",$3);
}
|Variable GE singleExpression{
    $$=new _singleExpression($1,"GE",$3);
}
|Variable GT singleExpression{
    $$=new _singleExpression($1,"GT",$3);
}
|Variable LE singleExpression{
    $$=new _singleExpression($1,"LE",$3);
}
|Variable LT singleExpression{
    $$=new _singleExpression($1,"LT",$3);
}
|Variable EQUAL singleExpression{
    $$=new _singleExpression($1,"EQUAL",$3);
}
|Variable NOEQUAL singleExpression{
    $$=new _singleExpression($1,"NOEQUAL",$3);
}
|Variable{
    $$=$1;
}
|Value{
    $$=new _Data();
    $$=$1;
}


Value:
REAL{
    $$=new _Float($1);
}
|INTEGER{
    $$=new _Integer($1);
}
|STRING{
    $$=new _String($1);
}


functionCall:
IDENTIFIER LP ArgsList RP{
    $$=new _functionCall($1,$3);
}

complexExpression:
forSTMT{
    $$=$1;
}
|whileSTMT{
    $$=$1;
}
|ifSTMT{
    $$=$1;
}



forSTMT:
FOR LP assignExpression SEMI singleExpression SEMI assignExpression RP LCB StatementList RCB
{
    $$=new _forStatement($3,$5,$7,$10);
}



whileSTMT:
WHILE LP singleExpression RB LCB StatementList RCB{
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
    $$=new _elsePart();//空body,应该能支持这个选项
}



Subroutine:
SYS_TYPE IDENTIFIER LP ArgsDefinitionList RP LCB StatementList RCB{
    $$=new _Subroutine($1,$2,$4,$7);
}



ArgsList:
Variable COMMA ArgsList{
    $3->push_back($1);
    $$=$3;
}
|Variable{
    $$=new _ArgsList();
    $$->push_back($1);
}
|{
    $$=new _ArgsList();
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























