#ifndef AST_H
#define AST_H
#endif

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <list>
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include <climits>


using namespace std;
/* class declaration */ 
#pragma region

class CodeGenerator;

class Node;
class _Program;
class _Function;
class _mainFunction;
class _Subroutine;
class _Statement;
class _Definition;
class _Expression;
class _singleExpression;
class _Variable;
class _Identifier;
class _assignExpression;
class _complexExpression;
class _functionCall;
class _forStatement;
class _whileStatement;
class _ifStatement;
class _elsePart;
class _Args;
class _argsDefinition;
class _String;
class _returnStatement;
class _Term;
class _Value;
class _Input;
class _Output;

typedef std::vector<_argsDefinition*> _ArgsDefinitionList;
typedef std::vector<_Function*> _FunctionList;
typedef std::vector<_Statement*> _StatementList;
typedef std::vector<_Variable*> _VarList;
typedef std::vector<_singleExpression*>_SingleExpressionList;
//待完善 变量存储相关

union c_val {
    int i;
    double r;
    bool b;
    char c;
    std::string s;
};

#pragma endregion


// AST Node Type
enum NodeType {
    NODE = 0,
    PROGRAM_NODE,
    ID,
    ROUTINE_NODE,
    ROUTINE_HEAD,
    LABEL_PART,
    CONST_EXPR_LIST,
    CONST_EXPR,
    CONST_VALUE,
    TYPE_DEFINE_LIST,
    TYPE_DEFINITION,
    TYPE_DECL,
    SIMPLE_TYPE_DECL,
    ARRAY_TYPE_DECL,
    RECORD_TYPE_DECL,
    STMT_LIST
} ;
enum BuildInType {
    C_INTEGER,
    C_REAL,
    C_CHAR,
    C_BOOLEAN
};
enum C_Operator {
    C_ADD,
    C_SUB,
    C_MUL,
    C_DIV,
    C_GE,
    C_GT, 
    C_LT,
    C_LE,
    C_EQUAL,
    C_NOEQUAL,
    C_OR,
    C_MOD,
    C_AND,
    C_XOR,
};

class Node
{
public:
    virtual ~Node(){} 
    virtual void setNodeType(NodeType type){
        this->type=type;
    }

    virtual void printNode(){};
private:
    int type;
};

class _Program: public Node{
public:
    _FunctionList *myFuncs;
    _Program(_FunctionList *Funcs){
        this->myFuncs=Funcs;
    }
    _Program(){
        this->myFuncs=NULL;
    }
};

//基类 1
class _Function:public Node{
public:
    std::string func_Type;
    _mainFunction* mainFunc;
    _Subroutine* subFunc;
    _Function(){
        this->func_Type="NULL";
        this->mainFunc=NULL;
        this->subFunc=NULL;
    }
    _Function(_mainFunction* mainFunc){
        this->func_Type="mainFunc";
        this->mainFunc=mainFunc;
        this->subFunc=NULL;
    }
    _Function(_Subroutine* subFunc){
        this->func_Type="subFunc";
        this->mainFunc=NULL;
        this->subFunc=subFunc;
    }
};

class _mainFunction: public Node{
public:
    _StatementList* statements;
    _ArgsDefinitionList*  args;
    _mainFunction(_ArgsDefinitionList* _args, _StatementList* _statements){
        this->args=_args;
        this->statements=_statements;
    }
};

class _Subroutine:public Node{
public:
    _StatementList* statements;
    std::string* Type; /* "int"|"char"|"double"|"boolean" */
    std::string* Func_Id;  /* Function Identifier */
    _ArgsDefinitionList*  args; 
    _Subroutine(std::string* Type,std::string* Identifier,_ArgsDefinitionList* _args, _StatementList* _statements){
        this->Type=Type;
        this->Func_Id=Identifier;
        this->args=_args;
        this->statements=_statements;    
    }
};

//基类 2
class _Statement: public Node{
public:
    _Definition* definStatement;
    _Expression* exprStatement;
    _returnStatement* returnStatement;
    _Output* outputExpr;
    _Input* inputExpr;
    _Statement(){
        this->definStatement=NULL;
        this->exprStatement=NULL;
        this->returnStatement=NULL;
    }
    _Statement(_Definition* defin){
        this->definStatement=defin;
        this->exprStatement=NULL;
        this->returnStatement=NULL;
    }
    _Statement(_Expression* expr){
        this->definStatement=NULL;
        this->exprStatement=expr;
        this->returnStatement=NULL;
    }
    _Statement(_returnStatement* returnExpr){
        this->definStatement=NULL;
        this->exprStatement=NULL;
        this->returnStatement=returnExpr;
    }
    _Statement(_Input* inputExpr){
        this->inputExpr=inputExpr;
        this->definStatement=NULL;
        this->exprStatement=NULL;
        this->returnStatement=NULL;
        this->outputExpr=NULL;
    }
    _Statement(_Output* outputExpr){
        this->outputExpr=outputExpr;
        this->definStatement=NULL;
        this->exprStatement=NULL;
        this->returnStatement=NULL;
        this->inputExpr=NULL;
    }
};

class _Input:public Node{
public:
    _VarList* vars;
    _Input(_VarList* variables){
        this->vars=variables;
    }
};

class _Output:public  Node{
public:
    _VarList* vars;
    _Output(_VarList* variables){
        this->vars=variables;
    }
};


class _returnStatement: public Node{
public:
    _SingleExpressionList *expr;
    _returnStatement(_SingleExpressionList* expression){
        this->expr=expression;
    }

};

class _Definition: public Node{
public:
    BuildInType def_Type;
    std::string *def_Name;
    _Definition(std::string* type, std::string *name){
        if(*type=="int"){
            def_Type=C_INTEGER;
        }
        else if(*type=="char"){
            def_Type=C_CHAR;
        }
        else if (*type=="double"){
            def_Type=C_REAL;
        }
        else{
            def_Type=C_BOOLEAN;
        }
        this->def_Name=name;
    }
};

class _Expression: public Node{
public:
    std::string Expression_Type;
    _assignExpression* assignExpression;
    _complexExpression* complexExpression;
    _functionCall* functionCall;

    _Expression(){
        this->assignExpression=NULL;
        this->complexExpression=NULL;
        this->functionCall=NULL;
    }
    _Expression(_assignExpression* assignExpr){
        this->assignExpression=assignExpr;
        this->complexExpression=NULL;
        this->functionCall=NULL;
        this->Expression_Type="assign";
    }
    _Expression(_complexExpression* complexExpr){
        this->assignExpression=NULL;
        this->complexExpression=complexExpr;
        this->functionCall=NULL;
        this->Expression_Type="complex";
    }
    _Expression(_functionCall* func){
        this->assignExpression=NULL;
        this->complexExpression=NULL;
        this->functionCall=func;
        this->Expression_Type="func";
    }

};

class _singleExpression:public Node{
public:
    _Term* term;
    C_Operator OP;
    int type;
    _singleExpression(_Term* term,C_Operator Op){
        this->term=term;
        this->OP=Op;
        this->type=1;
    }
    _singleExpression(_Term* term){
        this->term=term;
        this->type=2;
    }
};

class _Term:public Node{
public:
    _Value* val;
    _Variable* var;
    _SingleExpressionList* singleExpr;
    int Type;
    _Term(_Value* value){
        this->val=value;
        this->var=NULL;
        this->singleExpr=NULL;
        this->Type=1;
    }
    _Term(_Variable* value){
        this->val=NULL;
        this->var=value;
        this->singleExpr=NULL;
        this->Type=2;
    }
    _Term(_SingleExpressionList* single){
        this->val=NULL;
        this->var=NULL;
        this->singleExpr=single;
        this->Type=3;
    }
};

class _assignExpression: public Node{
public: 
    _SingleExpressionList* rhs;
    _Variable* val;
    _functionCall* function;
    int type;
    _assignExpression(_Variable* value,_SingleExpressionList* stas){
        this->val=value;
        this->rhs=stas;
        this->function=NULL;
        this->type=1;
    }
    _assignExpression(_Variable* value,_functionCall* func){
        this->val=value;
        this->rhs=NULL;
        this->function=func;
        this->type=2;
    }
    _assignExpression(_functionCall* func){
        this->val=NULL;
        this->rhs=NULL;
        this->function=func;
        this->type=0;
    }
};

class _complexExpression: public Node{
public: 
    string complex_Type;
    _forStatement* forSTMT;
    _whileStatement* whileSTMT;
    _ifStatement* ifSTMT;
    _complexExpression(){
        this->forSTMT=NULL;
        this->whileSTMT=NULL;
        this->ifSTMT=NULL;
    }
    _complexExpression(_forStatement* forSTMT){
        this->forSTMT=forSTMT;
        this->whileSTMT=NULL;
        this->ifSTMT=NULL;
        this->complex_Type="for";
    }
    _complexExpression(_whileStatement* whileSTMT){
        this->forSTMT=NULL;
        this->whileSTMT=whileSTMT;
        this->ifSTMT=NULL;
        this->complex_Type="while";
    }
    _complexExpression(_ifStatement* ifSTMT){
        this->forSTMT=NULL;
        this->whileSTMT=NULL;
        this->ifSTMT=ifSTMT;
        this->complex_Type="if";
    }
};

class _functionCall: public Node{
public: 
    std::string* func_Name;
    _VarList *args;
    _functionCall(std::string* func_Name,_VarList *arg){
        this->func_Name=func_Name;
        this->args=arg;
    }
};


class _forStatement: public Node{
public: 
    _assignExpression *expr1;
    _SingleExpressionList *expr2;
    _assignExpression *expr3;
    _StatementList *statements;
    _forStatement(_assignExpression *s1,_SingleExpressionList *s2, _assignExpression *s3, _StatementList *ss){
        this->expr1=s1;
        this->expr2=s2;
        this->expr3=s3;
        this->statements=ss;
    }

};

class _whileStatement: public Node{
public:
    _SingleExpressionList *condition;
    _StatementList *statements;
    _whileStatement(_SingleExpressionList *con, _StatementList *ss){
        this->condition=con;
        this->statements=ss;
    }
};

class _ifStatement: public Node{
public:
    _SingleExpressionList *condition1;
    _StatementList *statements;
    _elsePart *elsePart;
    _ifStatement(_SingleExpressionList *condition1, _StatementList *s1,_elsePart *elseP){
        this->condition1=condition1;
        this->statements=s1;
        this->elsePart=elseP;
    }
};

class _elsePart: public Node{
public:
    _StatementList *statements;
    _ifStatement *ifBody;
    int type;//else part类型
    _elsePart(_StatementList *ss){
        this->statements=ss;
        this->ifBody=NULL;
        this->type=1;
    }
    _elsePart(_ifStatement *ifbody){
        this->ifBody=ifbody;
        this->statements=NULL;
        this->type=2;
    }
    _elsePart(){
        this->type=0;
        this->statements=NULL;
        this->ifBody=NULL;
    }
};

//参数接口
class _Args: public Node{
public:
    std::string* arg_ID;
    BuildInType arg_Type;
    std::string type;
    _Args(){
        this->type="none";
    }
    _Args(std::string* name){
        this->arg_ID=name;
    }
};

class _argsDefinition: public Node{
public:
    _Variable* args;
    std::string* arg_Type;
    std::string type;
    _argsDefinition(std::string* type,_Variable* name){
        this->args=name;
        this->arg_Type=type;
    }
    _argsDefinition(){
        this->type="none";
    }
};


class _Identifier: public Node{
public:
    string *Id;
    int Type;
    _Identifier(){
        *this->Id="none";
        this->Type=-1;
    }
    _Identifier(string* a){
        this->Id=a;
        this->Type=1;//非数组
    }
    _Identifier(string* a,_Expression* b){
        this->Id=a;
        this->Type=2;//数组
    }
    string getId(){
        return *this->Id;
    }
};

class _Variable: public Node{
public:
    std::string *ID_Name;
    _Expression *expr;
    int var_Type;
    _Variable(std::string *name){
        this->ID_Name=name;
        this->expr=NULL;
        this->var_Type=1;
    }
    _Variable(std::string* name,_Expression* expression){
        this->ID_Name=name;
        this->expr=expression;
        this->var_Type=2;
    }
};

class _Value:public Node{
public:
    int i_val;
    double f_val;
    std::string s_val;
    bool b_val;
    std::string var_type;
    _Value(int value){
        this->i_val=value;
        this->var_type="Integer";
    }
    _Value(double value){
        this->f_val=value;
        this->var_type="Float";
    }
    _Value(std::string value){
        this->s_val=value;
        this->var_type="String";
    }
    _Value(bool value){
        this->b_val=value;
        this->var_type="Bool";
    }
};