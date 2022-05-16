#ifndef AST_HH
#define AST_HH


#include <llvm/IR/Value.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <list>
#include <string.h>
#include <vector>
#include <map>
#include <ostream>
#include <climits>
#include <algorithm>

using namespace std;
/* class declaration */ 

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
class _assignExpression;
class _complexExpression;
class _functionCall;
class _forStatement;
class _whileStatement;
class _ifStatement;
class _Data;
class _elsePart;
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
typedef std::vector<_Data*> _DataList;
typedef std::vector<_singleExpression*>_SingleExpressionList;
//待完善 变量存储相关


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
    C_EQ,
    C_NE,
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

    virtual llvm::Value *codeGen(CodeGenerator & generator) = 0;
    // virtual string JsonGen()=0;
private:
    int type;
};

class _Program: public Node{
public:
    _FunctionList *myFuncs;
    _Program(_FunctionList *Funcs){
        reverse(Funcs->begin(),Funcs->end());
        this->myFuncs=Funcs;
        std::cout<<"Program\n";
        if(this->myFuncs==NULL){
            cout<<"NULL"<<endl;
        }
        else{
            cout<<"Not NULL"<<endl;
            _Function* f=(*this->myFuncs).front();
            if(f==NULL){
                cout<<"f is null"<<endl;
            }
            else{
                cout<<"f is not null"<<endl;
            }
        }
    }

    // _Program(_FunctionList *Funcs){
    //     this->myFuncs=Funcs;
    // }
    _Program(){
        this->myFuncs=NULL;
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    // virtual string JsonGen() override;
};


//基类 1
class _Function:public Node{
public:
    std::string func_Type;
    union u_Function{
        _mainFunction* mainFunc;
         _Subroutine* subFunc;
    }v_Function;

    enum u_Type{
        MAIN,
        SUB
    }v_Type;

    _Function(_mainFunction* mainFunc){
        this->v_Type=MAIN;
        this->v_Function.mainFunc=mainFunc;
    }
    _Function(_Subroutine* subFunc){
        this->v_Type=SUB;
        this->v_Function.subFunc=subFunc;
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    // virtual string JsonGen() override;
};


class _mainFunction: public Node{
public:
    _StatementList* statements;
    _ArgsDefinitionList* args;
    _mainFunction(_ArgsDefinitionList* _args, _StatementList* _statements){
        reverse(_statements->begin(),_statements->end());
        this->statements=_statements;

        if(_args!=NULL){
            reverse(_args->begin(),_args->end());
        }
        this->args=_args;
        std::cout<<"Main\n";
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    // virtual string JsonGen() override;
};

class _Subroutine:public Node{
public:
    _StatementList* statements;
    std::string* Type; /* "int"|"char"|"double"|"boolean" */
    std::string* Func_Id;  /* Function Identifier */
    _ArgsDefinitionList* args; 
    _Subroutine(std::string* Type,std::string* Identifier,_ArgsDefinitionList* _args, _StatementList* _statements){
        this->Type=Type;
        this->Func_Id=Identifier;
        reverse(_statements->begin(),_statements->end());
        this->statements=_statements;

        if(_args!=NULL){
            reverse(_args->begin(),_args->end());
        }
        this->args=_args;   
        std::cout<<"Sub\n";
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    // virtual string JsonGen() override;
};

//基类 2
class _Statement: public Node{
public:
    union u_Statement{
        _Definition* definStatement;
        _Expression* exprStatement;
        _returnStatement* returnStatement;
        _Output* outputExpr;
        _Input* inputExpr;
    }v_Statement;
    enum u_Type{
        DEFINITION,
        EXPRESSION,
        RETURNSTATEMENT,
        INPUT,
        OUTPUT
    }v_Type;
    
    _Statement(_Definition* defin){
        this->v_Statement.definStatement=defin;
        this->v_Type=DEFINITION;
    }
    _Statement(_Expression* expr){
        this->v_Statement.exprStatement=expr;
        this->v_Type=EXPRESSION;
    }
    _Statement(_returnStatement* returnExpr){
        this->v_Statement.returnStatement=returnExpr;
        this->v_Type=RETURNSTATEMENT;
    }
    _Statement(_Input* inputExpr){
        this->v_Statement.inputExpr=inputExpr;
        this->v_Type=INPUT;
    }
    _Statement(_Output* outputExpr){
        this->v_Statement.outputExpr=outputExpr;
        this->v_Type=OUTPUT;
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    // virtual string JsonGen() override;
};

class _Input:public Node{
public:
    _DataList* vars;
    _Input(_DataList* variables){
        reverse(variables->begin(),variables->end());
        this->vars=variables;
        std::cout<<"Input\n";
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    // virtual string JsonGen() override;
};

class _Output:public  Node{
public:
    _DataList* vars;
    _Output(_DataList* variables){
        reverse(variables->begin(),variables->end());
        this->vars=variables;
        std::cout<<"Output\n";
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    // virtual string JsonGen() override;
};


class _returnStatement: public Node{
public:
    _singleExpression *expr;
    _returnStatement(_singleExpression* expression){
        this->expr=expression;
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    // virtual string JsonGen() override;
};

class _Definition: public Node{
public:
    BuildInType def_Type;
    _DataList* data;
    _Definition(std::string* type, _DataList* var){
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
        reverse(var->begin(),var->end());
        this->data=var;
        std::cout<<"Definition\n";    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    // virtual string JsonGen() override;
};

class _Expression: public Node{
public:
    std::string Expression_Type;
    union u_Expression{
        _assignExpression* assignExpression;
        _complexExpression* complexExpression;
        _functionCall* functionCall;
    }v_Expression;

    enum{
        ASSIGNMENT,
        COMPLEX,
        FUNCTIONCALL
    }v_Type;

    _Expression(_assignExpression* assignExpr){
        this->v_Expression.assignExpression=assignExpr;
        this->v_Type=ASSIGNMENT;
    }
    _Expression(_complexExpression* complexExpr){
        this->v_Expression.complexExpression=complexExpr;
        this->v_Type=COMPLEX;
    }
    _Expression(_functionCall* func){
        this->v_Expression.functionCall;
        this->v_Type=FUNCTIONCALL;
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    // virtual string JsonGen() override;
};

class _singleExpression:public Node{
public:
   _singleExpression* lhs;
   _singleExpression* rhs;
   C_Operator OP;
   union u_single{
       _Value* val;
       _Variable* var;
   }v_single;
   enum u_Type{
       VALUE,
       VARIABLE,
       EXPRESSION
   }v_Type;

   _singleExpression(_Value* value){
       this->v_single.val=value;
       this->v_Type=VALUE;
   }
   _singleExpression(_Variable* value){
       this->v_single.var=value;
       this->v_Type=VARIABLE;
   }
   _singleExpression(_singleExpression* lhs,C_Operator OP,_singleExpression* rhs){
       this->lhs=lhs;
       this->rhs=rhs;
       this->OP=OP;
       this->v_Type=EXPRESSION;
   }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;

};

class _Term:public Node{
public:
    int Type;
    union u_Term{
        _Value* val;
        _Variable* var;
        _singleExpression* singleExpr;
    }v_Term;

    enum u_Type{ 
        VALUE,
        VARIABLE,
        SINGLE
    }v_Type;

    _Term(_Value* value){
        this->v_Term.val=value;
        this->v_Type=VALUE;
    }
    _Term(_Variable* value){
        this->v_Term.var=value;
        this->v_Type=VARIABLE;
    }
    _Term(_singleExpression* single){
        this->v_Term.singleExpr=single;
        this->v_Type=SINGLE;
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    // virtual string JsonGen() override;
};

class _assignExpression: public Node{
public: 
    _Variable* val;
    union u_assignExpression{
        _singleExpression* rhs;
        _functionCall* function;
    }v_assignExpression;

    enum u_Type{
        SINGLE,
        FUNCTION,
        VOID
    }v_Type;

    int type;
    _assignExpression(_Variable* value,_singleExpression* stas){
        this->v_assignExpression.rhs=stas;
        this->v_Type=SINGLE;
        this->val=value;        
    }
    _assignExpression(_Variable* value,_functionCall* func){
        this->v_assignExpression.function=func;
        this->val=value;
        this->v_Type=FUNCTION;
    }
    // buhuixie
    _assignExpression(_functionCall* func){
        this->v_assignExpression.function=func;
        this->v_Type=VOID;
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    // virtual string JsonGen() override;
};

class _complexExpression: public Node{
public: 
    union u_complexExpression{
        _forStatement* forSTMT;
        _whileStatement* whileSTMT;
        _ifStatement* ifSTMT;
    }v_complexExpression;

    enum u_Type{
        FOR,
        WHILE,
        IF
    }v_Type;


    _complexExpression(_forStatement* forSTMT){
        this->v_complexExpression.forSTMT=forSTMT;
        this->v_Type=FOR;
    }
    _complexExpression(_whileStatement* whileSTMT){
        this->v_complexExpression.whileSTMT=whileSTMT;
        this->v_Type=WHILE;
    }
    _complexExpression(_ifStatement* ifSTMT){
        this->v_complexExpression.ifSTMT=ifSTMT;
        this->v_Type=IF;
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    // virtual string JsonGen() override;
};

class _functionCall: public Node{
public: 
    std::string* func_Name;
    _DataList *args;
    _functionCall(std::string* func_Name,_DataList *arg){
        this->func_Name=func_Name;
        this->args=arg;
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    // virtual string JsonGen() override;
};


class _forStatement: public Node{
public: 
    _assignExpression *startExpr;
    _singleExpression *condExpr;
    _assignExpression *stepExpr;
    _StatementList *statements;
    _forStatement(_assignExpression *s1,_singleExpression *s2, _assignExpression *s3, _StatementList *ss){
        this->startExpr=s1;
        this->condExpr=s2;
        this->stepExpr=s3;
        reverse(ss->begin(),ss->end());
        this->statements=ss;
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    // virtual string JsonGen() override;
};

class _whileStatement: public Node{
public:
    _singleExpression *condition;
    _StatementList *statements;
    _whileStatement(_singleExpression *con, _StatementList *ss){
        this->condition=con;
        reverse(ss->begin(),ss->end());
        this->statements=ss;
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    // virtual string JsonGen() override;
};

class _ifStatement: public Node{
public:
    _singleExpression *condition;
    _StatementList *statements;
    _elsePart *elsePart;
    _ifStatement(_singleExpression *condition, _StatementList *s1,_elsePart *elseP){
        this->condition=condition;
        reverse(s1->begin(),s1->end());
        this->statements=s1;
        this->elsePart=elseP;
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    // virtual string JsonGen() override;
};

class _elsePart: public Node{
public:
    union u_Else{
        _StatementList *statements;
        _ifStatement *ifBody;
    }v_Else;

    enum u_Type{
        ELSEIF,
        ELSE,
        NONE
    }v_Type;

    _elsePart(_StatementList *ss){
        reverse(ss->begin(),ss->end());
        this->v_Else.statements=ss;
        this->v_Type=ELSE;
    }
    _elsePart(_ifStatement *ifbody){
        this->v_Else.ifBody=ifbody;
        this->v_Type=ELSEIF;
    }
    _elsePart(){
        this->v_Type=NONE;
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    // virtual string JsonGen() override;
};



class _argsDefinition: public Node{
public:
    _Variable* args;
    BuildInType arg_Type;
    _argsDefinition(BuildInType type,_Variable* name){
        this->args=name;
        this->arg_Type=type;
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    // virtual string JsonGen() override;
};

class _Data:public Node{

};

class _Variable: public _Data{
public:
    std::string *ID_Name;
    _singleExpression *expr;

    enum u_Type{
        CONST,
        ARRAY
    }v_Type;

    _Variable(std::string *name){
        this->ID_Name=name;
        this->expr=NULL;
        this->v_Type=CONST;
    }
    _Variable(std::string* name,_singleExpression* expression){
        this->ID_Name=name;
        this->expr=expression;
        this->v_Type=ARRAY;
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    // virtual string JsonGen() override;
};

class _Value:public _Data{
public:
    int i_val;
    double f_val;
    std::string s_val;
    bool b_val;
    BuildInType var_type;
    _Value(int value){
        this->i_val=value;
        this->var_type=C_INTEGER;
    }
    _Value(double value){
        this->f_val=value;
        this->var_type=C_REAL;
    }
    _Value(std::string value){
        this->s_val=value;
        this->var_type=C_CHAR;
    }
    _Value(bool value){
        this->b_val=value;
        this->var_type=C_BOOLEAN;
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    // virtual string JsonGen() override;
};

#endif