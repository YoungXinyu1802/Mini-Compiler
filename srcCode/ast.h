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
class _SubRoutine;
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

class _binaryOpExpression;


typedef std::vector<_Variable*> _ArgsList;
typedef std::vector<_argsDefinition*> _ArgsDefinitionList;
typedef std::vector<_Function*> _FunctionList;
typedef std::vector<_Statement*> _StatementList;
typedef std::vector<_Variable*> _VarList;
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
    C_BOOLEAN,
    C_STRING
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
class _Function:public _Program{
public:
    _StatementList* statements;
    string func_Type;
    _Function(){
        this->statements=NULL;
        this->func_Type="NULL";
    }
};

class _mainFunction: public _Function{
public:
    _ArgsList*  args;
    _mainFunction(_ArgsList* _args, _StatementList* _statements){
        this->args=_args;
        this->statements=_statements;
        this->func_Type="main";
    }
};
class _Subroutine:public _Function{
public:
    std::string* Type;
    std::string* Func_Id;
    _ArgsDefinitionList*  args;
    _Subroutine(std::string* Type,std::string* Identifier,_ArgsDefinitionList* _args, _StatementList* _statements){
        this->Type=Type;
        this->Func_Id=Identifier;
        this->args=_args;
        this->statements=_statements;
        this->func_Type="subRoutine";
    
    }
};

//基类 2
class _Statement: public Node{
public:
    string Statement_Type;
    int label=-1;
    // 用于为语句设置标号
    void setLabel(int label){
        this->label = label;
    }
    // 用于得到标号
    int getLable() const{
        return label;
    }
};


class _Definition: public _Statement{
public:
    BuildInType def_Type;
    string *def_Name;
    _Definition(string type, string *name){
        if(type=="int"){
            def_Type=C_INTEGER;
        }
        else if(type=="char"){
            def_Type=C_CHAR;
        }
        else if (type=="double"){
            def_Type=C_REAL;
        }
        else{
            def_Type=C_BOOLEAN;
        }
        this->def_Name=name;
        this->Statement_Type="Definition";//给一个判断依据
    }
    //怎么注册生命周期？

};

class _Expression: public _Statement{
public:
    string Expression_Type;
    _Expression(){
        this->Statement_Type="Expression";
    }

};

class _singleExpression:public _Statement{
public:
    _Variable *lhs;
    _singleExpression *rhs;
    std::string OP;
    _singleExpression(_Variable *lhs, std::string OP,_singleExpression *rhs){
        this->lhs=lhs;
        this->rhs=rhs;
        this->OP=OP;
        this->Statement_Type="singleExpression";
    }
    _singleExpression(){
        this->lhs=NULL;
        this->rhs=NULL;
    }
};


class _assignExpression: public _Expression{
public: 
    _Statement *rhs;
    _Variable *val;
    _assignExpression(_Variable *value,_Statement *stas){
        this->val=value;
        this->rhs=stas;
        this->Expression_Type="Assignment";
    }
};

class _complexExpression: public _Expression{
public: 
    string complex_Type;
    _complexExpression(){
        this->Expression_Type="Complex";
    }
};

class _returnExpression: public _Expression{
public: 
    _singleExpression *expr;
    _returnExpression(_singleExpression *expression){
        this->Expression_Type="return";
        this->expr=expression;
    }
};

class _functionCall: public _Expression{
public: 
    std::string* func_Name;
    _ArgsList *args;
    BuildInType returnType;
    _functionCall(std::string* func_Name,_ArgsList *arg){
        this->func_Name=func_Name;
        this->args=arg;
        this->getReturnType();
        this->Expression_Type="functionCall";
    }
    BuildInType getReturnType(){
        //return getFuncType(func_Name);
        return C_INTEGER;
    }
};


class _forStatement: public _complexExpression{
public: 
    _assignExpression *expr1;
    _singleExpression *expr2;
    _assignExpression *expr3;
    _StatementList *statements;
    _forStatement(_assignExpression *s1,_singleExpression *s2, _assignExpression *s3, _StatementList *ss){
        this->expr1=s1;
        this->expr2=s2;
        this->expr3=s3;
        this->statements=ss;
        this->complex_Type="forSTMT";
    }

};

class _whileStatement: public _complexExpression{
public:
    _singleExpression *condition;
    _StatementList *statements;
    _whileStatement(_singleExpression *con, _StatementList *ss){
        this->condition=con;
        this->statements=ss;
        this->complex_Type="whileSTMT";
    }
};

class _ifStatement: public _complexExpression{
public:
    _singleExpression *condition1;
    _StatementList *statements;
    _elsePart *elsePart;
    _ifStatement(_singleExpression *condition1, _StatementList *s1,_elsePart *elseP){
        this->condition1=condition1;
        this->statements=s1;
        this->elsePart=elseP;
        this->complex_Type="ifSTMT";
    }
};

class _elsePart: public _complexExpression{
public:
    _StatementList *statements;
    _ifStatement *ifBody;
    int type;//else part类型
    _elsePart(_StatementList *ss){
        this->statements=ss;
        this->ifBody=NULL;
        this->type=1;
        this->complex_Type="elsePart";
    }
    _elsePart(_ifStatement *ifbody){
        this->ifBody=ifbody;
        this->statements=NULL;
        this->type=2;
        this->complex_Type="elsePart";
    }
    _elsePart(){
        this->type=0;
        this->statements=NULL;
        this->ifBody=NULL;
        this->complex_Type="elsePart";
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

//基类3
class _Data:public _singleExpression{
    
};

class _Identifier: public _Data{
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

class _Variable: public _singleExpression{
public:
    std::string *ID_Name;
    _Expression *expr;
    _Variable(std::string *name){
        this->ID_Name=name;
    }
    _Variable(std::string name,_Expression expression){
        *this->ID_Name=name;
        *this->expr=expression;
    }
};



class _Integer:public _Data{
public: 
    int value;
    _Integer(int value){
        this->value=value;
    }
    _Integer(char *value){
        this->value=atoi(value); //将字符串转换为整数
    }
    BuildInType getType() {
        return C_INTEGER;
    }
};

class _Float:public _Data{
public:
    double value;
    _Float(double value){
        this->value=value;
    }
    _Float(char *value){
        this->value=atof(value);
    }
    BuildInType getType(){
        return C_REAL;
    }
};

class _Bool:public _Data{
public:
    bool value;
    _Bool(bool value){
        this->value=value;
    }
 
    BuildInType getType() {
        return C_BOOLEAN;
    }
};

class _String:public _Data{
public:
    std::string *value;
    _String(std::string *value){
        this->value=value;
    }
    BuildInType getType() {
        return C_STRING;
    }
};
//暂不支持string