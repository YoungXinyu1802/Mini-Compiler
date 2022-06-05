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
class _Struct;

typedef std::vector<_argsDefinition*> _ArgsDefinitionList;
typedef std::vector<_Function*> _FunctionList;
typedef std::vector<_Statement*> _StatementList;
typedef std::vector<_Data*> _DataList;
typedef std::vector<_Data*> _InputList;
typedef std::vector<_Data*> _OutputList;
typedef std::vector<_singleExpression*>_SingleExpressionList;
typedef std::vector<_Struct*> _StructList;
typedef std::vector<_Definition*> _DefinitionList;
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
    C_BOOLEAN,
    C_STRING,
    C_VOID,
    C_STRUCT
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
    virtual string JsonGen()=0;
private:
    int type;
};

class _Data:public Node{

};

class _Variable: public _Data{
public:
    std::string *ID_Name;
    std::string *member;
    _singleExpression *exprID;
    _singleExpression *exprMem;

    enum u_Type{
        CONST,
        ARRAY,
        ArrayPtr,
        Struct,
        StructMemARRAY,
        MemARRAY,
        StructARRAY
    }v_Type;

    _Variable(std::string *name){
        this->ID_Name=name;
        this->exprID=NULL;
        this->exprMem=NULL;
        this->v_Type=CONST;
        std::cout<<"Variable"<<" "<<*name<<endl;
    }
    _Variable(std::string* name,_singleExpression* expression){
        this->ID_Name=name;
        this->exprID=expression;
        this->exprMem=NULL;
        this->v_Type=ARRAY;
        cout<<"Array\n";

    }
    _Variable(std::string* name,std::string arrayNULL){
        this->ID_Name=name;
        this->exprID=NULL;
        this->exprMem=NULL;
        this->v_Type=ArrayPtr;
        cout<<"Arrayptr\n";
    }
    _Variable(std::string* name, std::string*member){
        this->ID_Name=name;
        this->exprID=NULL;
        this->exprMem=NULL;
        this->member=member;
        this->v_Type=Struct;
    }
    _Variable(std::string* name, std::string*member,_singleExpression* expression){
        this->ID_Name=name;
        this->member=member;
        this->v_Type=MemARRAY;//modified
        this->exprMem=expression;
        this->exprID=NULL;
    }
    _Variable(std::string* name1,_singleExpression* expr1,std::string* name2,_singleExpression* expr2){
        cout<<"in structMemArray"<<endl;
        this->ID_Name=name1;
        this->member=name2;
        this->v_Type=StructMemARRAY;
        this->exprMem=expr2;
        this->exprID=expr1;
    }
    _Variable(std::string* name, _singleExpression* expression,std::string*member){
        cout<<"in structArray"<<endl;
        this->ID_Name=name;
        this->member=member;
        this->v_Type=StructARRAY;//modified
        this->exprID=expression;
        this->exprMem=NULL;
    }


    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    virtual string JsonGen() override;
};

class _Value:public _Data{
public:
    int i_val;
    double f_val;
    std::string s_val;
    bool b_val;
    char c_val;
    BuildInType var_type;
    _Value(int value){
        this->i_val=value;
        this->var_type=C_INTEGER;
    }
    _Value(double value){
        this->f_val=value;
        this->var_type=C_REAL;
    }
    _Value(std::string* value){
    
        this->s_val=*value;
        this->var_type=C_STRING;
    }
    _Value(char value){
        cout<<"charvalue: "<<value<<endl;
        this->c_val=value;
        this->var_type=C_CHAR;
    }
    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    virtual string JsonGen() override;
};

class _Definition: public Node{
public:
    BuildInType def_Type;
    bool isStruct;
    string* structID;
    _DataList* data;
    _Definition(std::string* type, _DataList* var){
        isStruct=false;
        if(*type=="int"){
            def_Type=C_INTEGER;
        }
        else if(*type=="char"){
            def_Type=C_CHAR;
        }
        else if (*type=="double"){
            def_Type=C_REAL;
        }
        else if(*type=="string"){
            def_Type=C_STRING;
        }
        else{
            def_Type=C_BOOLEAN;
        }
        reverse(var->begin(),var->end());
        this->data=var;
        std::cout<<"Definition\n";    
    }
    _Definition(int type,std::string* ID,_DataList*var){
        isStruct=true;
        this->def_Type=C_STRUCT;
        this->structID=ID;
        reverse(var->begin(),var->end());
        this->data=var;
    }
    string getStructID(){
        return *this->structID;
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    virtual string JsonGen() override;
};

class _Struct:public Node{
public:
    _DefinitionList* defins;
    std::string* struct_ID;

    _Struct(std::string* name,_DefinitionList* definitions ){
        this->struct_ID=name;
        this->defins=definitions;
    }

    int getIndex(std::string name){
        int count=0;
        for(auto defin:*this->defins){
            //next pointer
            for(auto var: *defin->data){
                _Variable* tVar=dynamic_cast<_Variable*>(var);
                if(*tVar->ID_Name==name){
                    cout<<"find index"<<count<<endl;
                    return count;
                }
                ++count;
            }
        }
        return -1;// default: no matched ID_name
    }

    string getId(int index){
        int count=0;
        for(auto defin:*this->defins){
            //next pointer
            for(auto var: *defin->data){
                _Variable* tVar=dynamic_cast<_Variable*>(var);
                if(index==count){
                    return *tVar->ID_Name;
                }
                ++count;
            }
        }
        return NULL;
    }
    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    virtual string JsonGen() override;
};


class _Program: public Node{
public:
    _FunctionList *myFuncs;
    _StructList *myStructs;
    _Program(_StructList *structs,_FunctionList *Funcs){
        if(structs->size()>0){
            reverse( structs->begin(),structs->end());
            this->myStructs=structs;
        }
        else{
            this->myStructs=NULL;
        }
        reverse( Funcs->begin(),Funcs->end());
        this->myFuncs=Funcs;
        std::cout<<"Program\n";

    }

    // _Program(_FunctionList *Funcs){
    //     this->myFuncs=Funcs;
    // }
    _Program(){
        this->myFuncs=NULL;
    }
    bool hasStruct(){
        if(this->myStructs==NULL){
            cout<<"struct is NULL";
            return false;
        }
        return true;
    }

    _Struct* getStructPtr(string* name){
        for(auto stu :*this->myStructs){
            if(*(stu->struct_ID)==*name){
                return stu;
            }
        }
    }


    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    virtual string JsonGen() override;
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
    virtual string JsonGen() override;
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
    virtual string JsonGen() override;
};

class _Subroutine:public Node{
public:
    _StatementList* statements;
    std::string* Type; /* "int"|"char"|"double"|"boolean"|"void" */
    std::string* Func_Id;  /* Function Identifier */
    _ArgsDefinitionList* args; 
    _Subroutine(std::string* Type,std::string* Identifier,_ArgsDefinitionList* _args, _StatementList* _statements){
        this->Type=Type;
        this->Func_Id=Identifier;
        reverse(_statements->begin(),_statements->end());
        this->statements=_statements;

        // if(_args!=NULL){
        //     reverse(_args->begin(),_args->end());
        // }
        this->args=_args;   
        std::cout<<"Sub\n";
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    virtual string JsonGen() override;
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
    virtual string JsonGen() override;
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
    virtual string JsonGen() override;
};




class _Output:public  Node{
public:
    _DataList* vars;
    int digit;
    bool setD=false;
    _Output(_DataList* variables){
        reverse(variables->begin(),variables->end());
        this->vars=variables;
        std::cout<<"Output\n";
    }
    void setDigit(_Value* val){
        if(val->var_type!=C_INTEGER){
            cout<<"error setDight type"<<endl;
        }
        else{
            this->setD=true;
            this->digit=val->i_val;
            cout<<"success set digit"<<this->digit<<endl;
        }
    }
    bool isSetD(){
        return this->setD;
    }
    int getD(){
        return this->digit;
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    virtual string JsonGen() override;
};


class _returnStatement: public Node{
public:
    _singleExpression *expr;
    _returnStatement(_singleExpression* expression){
        this->expr=expression;
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    virtual string JsonGen() override;
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
        this->v_Expression.functionCall=func;
        this->v_Type=FUNCTIONCALL;
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    virtual string JsonGen() override;
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
    virtual string JsonGen() override;

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
    virtual string JsonGen() override;
};

class _assignExpression: public Node{
public: 
    _Variable* val;
    union u_assignExpression{
        _singleExpression* rhs;
        _functionCall* function;
        _DataList* data;
    }v_assignExpression;

    enum u_Type{
        SINGLE,
        FUNCTION,
        VOID,
	    ARRAY
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
    _assignExpression(_Variable* value,_DataList* datas){
        this->val=value;
        reverse(datas->begin(),datas->end());
        this->v_assignExpression.data=datas;
        this->v_Type=ARRAY;
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    virtual string JsonGen() override;
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
    virtual string JsonGen() override;
};

class _functionCall: public Node{
public: 
    std::string* func_Name;
    _DataList *args;
    _functionCall(std::string* func_Name,_DataList *arg){
        this->func_Name=func_Name;
        this->args=arg;
    }
    _functionCall(std::string* func_Name){
        this->func_Name=func_Name;
        this->args=NULL;
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    virtual string JsonGen() override;
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
    virtual string JsonGen() override;
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
    virtual string JsonGen() override;
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
    virtual string JsonGen() override;
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
    virtual string JsonGen() override;
};



class _argsDefinition: public Node{
public:
    _Variable* args;
    BuildInType arg_Type;
    _argsDefinition(BuildInType type,_Variable* name){
        std::cout << "argsdefinition" << std::endl;
        std::cout << arg_Type << std::endl;
        this->args=name;
        this->arg_Type=type;
    }

    virtual llvm::Value *codeGen(CodeGenerator & generator) override;
    virtual string JsonGen() override;
};


#endif
