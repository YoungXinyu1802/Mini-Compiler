#include "ast.h"


using namespace std;

//一些共用函数
string getJsonString(string name){
    return "{\"name\":\"" +name +"\"}";
}

string getJsonString(string name, vector<string> children) {
    string result = "{ \"name\" : \"" + name + "\", \"children\" : [ ";
    int i = 0;
    for(auto &child : children) {
        if(i != children.size() - 1)
            result += child + ", ";
        else 
            result += child + " ";
        i++;
    }
    return result + " ] }";
}

string getJsonString(string name, string value){
    if(name=="STRING"){
        return "{\"name\":\"" +name +"\", \"value\":"+ value+" }";
    }
    return "{\"name\":\"" +name +"\", \"value\":\""+ value+"\" }";
}

string getJsonString(string name, string value ,vector<string> children){
    string result = "{ \"name\" : \"" + name + "\",  \"value\" : \"" + value + "\",\"children\" : [ ";
    int i = 0;
    for(auto &child : children) {
        if(i != children.size() - 1)
            result += child + ", ";
        else 
            result += child + " ";
        i++;
    }
    return result + " ] }";
}
string getJsonString(string name, string value ,string type){
     return "{\"name\":\"" +name +"\", \"type\":\""+ type+"\",  \"value :\""+value +"\" }";
}


//一些类内函数
string _Program::JsonGen(){
    std::vector<string>children;
    std::vector<string>funcs;
    std::vector<string>structs;
    for(auto mystruct: *this->myStructs){
        structs.push_back(mystruct->JsonGen());
    }
    children.push_back(getJsonString("structList",structs));
    std::cout<<"in Program"<<endl;
    for(auto func: *this->myFuncs){
        funcs.push_back(func->JsonGen());
    }
    children.push_back(getJsonString("FunctionList",funcs));
    return getJsonString("Program",children);
}

string _Function::JsonGen(){
    std::vector<string> children;
    if(this->v_Type==MAIN){
        cout<<"cpp main"<<endl;
        children.push_back(this->v_Function.mainFunc->JsonGen());
    }
    if(this->v_Type==SUB){
        children.push_back(this->v_Function.subFunc->JsonGen());
    }
    return getJsonString("Function",children);
}

string _Struct::JsonGen(){
    std::vector<string> children;
    std::vector<string>defins;
    children.push_back(getJsonString("ID",*this->struct_ID));
    for(auto defin:*this->defins){
        defins.push_back(defin->JsonGen());
    }
    children.push_back(getJsonString("DefinitionList",defins));
    cout<<"struct jsonGen"<<endl;
    return getJsonString("Struct",children);    
}

string _mainFunction::JsonGen(){
    std::vector<string> children;
    std::vector<string> funcArgs;
    for(auto arg:*this->args){
        funcArgs.push_back(arg->JsonGen());
    }
    children.push_back(getJsonString("ArgsDefinitionList",funcArgs));

    std::vector<string>stas;
    cout<<this->statements->size()<<"cpp"<<endl;
    for(auto sta:*this->statements){
        stas.push_back(sta->JsonGen());
    }
    children.push_back(getJsonString("StatementList",stas));
    cout<<"finish main json"<<endl;
    return getJsonString("mainFunc",children);
}

string _Subroutine::JsonGen(){
    std::vector<string> children;
    std::vector<string> funcArgs;
    for(auto arg:*this->args){
        funcArgs.push_back(arg->JsonGen());
    }
    children.push_back(getJsonString("ArgsDefinitionList",funcArgs));

    std::vector<string>stas;
    for(auto sta: *this->statements){
        stas.push_back(sta->JsonGen());
    }
    children.push_back(getJsonString("StatementList",stas));

    return getJsonString("Subroutine",*this->Func_Id,children);
}

string _Statement::JsonGen(){
    std::vector<string>children;
    cout<<"in json statement"<<endl;
    if(this->v_Type==DEFINITION){
        children.push_back(this->v_Statement.definStatement->JsonGen());
    }
    else if(this->v_Type==EXPRESSION){
        cout<<"in statement expression json"<<endl;
        children.push_back(this->v_Statement.exprStatement->JsonGen());
    }
    else if(this->v_Type==RETURNSTATEMENT){
        children.push_back(this->v_Statement.returnStatement->JsonGen());
    }
    else if(this->v_Type==INPUT){
        children.push_back(this->v_Statement.outputExpr->JsonGen());
    }
    else if(this->v_Type==OUTPUT){
        children.push_back(this->v_Statement.inputExpr->JsonGen());
    }

    return getJsonString("Statement",children);
}

string _Input::JsonGen(){
    std::vector<string>children;
    std::vector<string>datas;
    for(auto var: *this->vars){
        datas.push_back(var->JsonGen());
    }
    children.push_back(getJsonString("DataList",datas));

    return getJsonString("Input",children);
}

string _Output::JsonGen(){
    std::vector<string>children;
    std::vector<string>datas;
    for(auto var: *this->vars){
        datas.push_back(var->JsonGen());
    }
    children.push_back(getJsonString("DataList",datas));

    return getJsonString("Output",children);
}

string _returnStatement::JsonGen(){
    std::vector<string>children;
    children.push_back(this->expr->JsonGen());
    return getJsonString("returnStatement",children);
}

string _Definition::JsonGen(){
    std::vector<string>children;
    string type = "";
    if(this->def_Type==C_INTEGER){
        type="int";
    }
    else if(this->def_Type==C_REAL){
        type="double";
    }
    else if(this->def_Type==C_CHAR){
        type="char";
    }
    else if(this->def_Type==C_STRING){
        type="string";
    }
    else if(this->def_Type==C_BOOLEAN){
        type="boolean";
    }
    else if(this->def_Type==C_STRUCT){
        type="struct";
    }
    children.push_back(getJsonString("type",type));
    if(this->isStruct){
        children.push_back(getJsonString("structID",this->getStructID()));
    }
    std::vector<string>vars;
    for(auto sta: *this->data){
        vars.push_back(sta->JsonGen());
    }
    
    children.push_back(getJsonString("DataList",vars));
    return getJsonString("Definition",type,children);
}

string _Expression::JsonGen(){
    std::vector<string>children;
    if(this->v_Type==ASSIGNMENT){
        children.push_back(this->v_Expression.assignExpression->JsonGen());
    }
    else if(this->v_Type==COMPLEX){
        children.push_back(this->v_Expression.complexExpression->JsonGen());
    }
    else if(this->v_Type==FUNCTIONCALL){
        cout<<"in functioncall json"<<endl;
        if(this->v_Expression.functionCall==NULL){
            cout<<"func ptr is null"<<endl;

        }
        children.push_back(this->v_Expression.functionCall->JsonGen());
    }

    return getJsonString("Expression",children);
}
string getOPString(C_Operator OP){
    string res;
    if(OP==C_ADD){
        res="ADD";
    }
    else if(OP==C_SUB){
        res="SUB";
    }
    else if(OP==C_MUL){
        res="MUL";
    }
    else if(OP==C_DIV){
        res="DIV";
    }
    else if(OP==C_GE){
        res="GE";
    }
    else if(OP==C_GT){
        res="GT";
    }
    else if(OP==C_LT){
        res="LT";
    }
    else if(OP==C_LE){
        res="LE";
    }
    else if(OP==C_EQUAL){
        res="EQUAL";
    }
    else if(OP==C_NOEQUAL){
        res="NOEQUAL";
    }
    else if(OP==C_OR){
        res="OR";
    }
    else if(OP==C_MOD){
        res="MOD";
    }
    else if(C_AND){
        res="AND";
    }
    else{
        res="XOR";
    }
    return res;
}

string _singleExpression::JsonGen(){
    std::vector<string>children;
    if(this->v_Type==VALUE){
        children.push_back(this->v_single.val->JsonGen());
    }
    else if(this->v_Type==VARIABLE){
        children.push_back(this->v_single.var->JsonGen());
    }
    else if(this->v_Type==EXPRESSION){
        children.push_back(this->lhs->JsonGen());
        string opType=getJsonString("Operation",getOPString(this->OP));
        children.push_back(opType);
        children.push_back(this->rhs->JsonGen());
    }

    return getJsonString("singleExpr",children);
}



string _assignExpression::JsonGen(){
    std::vector<string> children;
    if(this->v_Type==SINGLE){
        children.push_back(this->val->JsonGen());
        children.push_back(this->v_assignExpression.rhs->JsonGen());
    }
    else if(this->v_Type==FUNCTION){
        children.push_back(this->val->JsonGen());
        children.push_back(this->v_assignExpression.function->JsonGen());
    }
    else if(this->v_Type==VOID){
        children.push_back(this->v_assignExpression.function->JsonGen());
    }
    else if(this->v_Type==ARRAY){
        children.push_back(this->val->JsonGen());
        std::vector<string>datas;
        for(auto var: *this->v_assignExpression.data){
            datas.push_back(var->JsonGen());
        }
    children.push_back(getJsonString("DataList",datas));

    }
    return getJsonString("Assignment",children);
}

string _complexExpression::JsonGen(){
    std::vector<string>children;
    if(this->v_Type==FOR){
        children.push_back(this->v_complexExpression.forSTMT->JsonGen());
    }
    else if(this->v_Type==WHILE){
        children.push_back(this->v_complexExpression.whileSTMT->JsonGen());
    }
    else if(this->v_Type==IF){
        children.push_back(this->v_complexExpression.ifSTMT->JsonGen());
    }
    return getJsonString("complexExpr",children);
}

string _functionCall::JsonGen(){
    std::vector<string> children;
    std::vector<string> argsJson;
    cout<<"functioncall begin json"<<endl;
    if(this->v_Type==HasArgs){
        for(auto arg: *this->args){
            argsJson.push_back(arg->JsonGen());
        }
        cout<<"functioncall end json"<<endl;
        children.push_back(getJsonString("ArgsList",argsJson));
    }
    children.push_back(getJsonString("FuncName",*this->func_Name));
    return getJsonString("functionCall",*this->func_Name,children);
}

string _forStatement::JsonGen(){
    std::vector<string>children;
    children.push_back(this->exprStart->JsonGen());
    children.push_back(this->exprCond->JsonGen());
    children.push_back(this->exprUpdate->JsonGen());
    std::vector<string>stas;
    for(auto sta: *this->statements){
        stas.push_back(sta->JsonGen());
    }
    children.push_back(getJsonString("StatementList",stas));
    
    return getJsonString("forStatement",children);
}

string _whileStatement::JsonGen(){
    std::vector<string>children;
    children.push_back(this->condition->JsonGen());
    std::vector<string>stas;
    for(auto sta: *this->statements){
        stas.push_back(sta->JsonGen());
    }
    children.push_back(getJsonString("StatementList",stas));
    return getJsonString("whileStatement",children);
}

string _ifStatement::JsonGen(){
    std::vector<string>children;
    children.push_back(this->condition1->JsonGen());
    std::vector<string>stas;
    for(auto sta: *this->statements){
        stas.push_back(sta->JsonGen());
    }
    children.push_back(getJsonString("StatementList",stas));
    children.push_back(this->elsePart->JsonGen());
    return getJsonString("ifStatement",children);

}

string _elsePart::JsonGen(){

    if(this->v_Type==NONE){
        return "";
    }
    std::vector<string>children;
    if(this->v_Type==ELSE){
        std::vector<string>stas;
        for(auto sta: *this->v_Else.statements){
            stas.push_back(sta->JsonGen());
        }
        children.push_back(getJsonString("StatementList",stas));
        return getJsonString("ELSE",children);
    }
    if(this->v_Type==ELSEIF){
        children.push_back(this->v_Else.ifBody->JsonGen());
        return getJsonString("ELSEIF",children);
    }
    return "error elsePart";
}

string _argsDefinition::JsonGen(){
    std::vector<string> children;
    string type;
    if(this->arg_Type==C_INTEGER){
        type="int";
    }
    else if(this->arg_Type==C_REAL){
        type="double";
    }
    else if(this->arg_Type==C_CHAR){
        type="char";
    }
    else if(this->arg_Type==C_BOOLEAN){
        type="boolean";
    }
    std::vector<string> chilren;
    children.push_back(this->args->JsonGen());
    return getJsonString("argsDefinition",type,children);
}


string _Variable::JsonGen(){
    if(this->v_Type==CONST){
        return getJsonString("Variable",*this->ID_Name);
    }
    else if(this->v_Type==ARRAY){
        std::vector<string> children;
        children.push_back(this->expr->JsonGen());
        return getJsonString("Array",*this->ID_Name,children);
    }
    else if(this->v_Type==ArrayPtr){
        return getJsonString("ArrayPtr",*this->ID_Name);
    }
    else if(this->v_Type==Struct){
        std::vector<string> children;
        children.push_back(getJsonString("ID",*this->ID_Name));
        children.push_back(getJsonString("member",*this->member));
        return getJsonString("StructV",children);
    }
    else if(this->v_Type==Struct){
        std::vector<string> children;
        children.push_back(getJsonString("ID",*this->ID_Name));
        children.push_back(getJsonString("member",*this->member));
        children.push_back(this->expr->JsonGen());
        return getJsonString("StructA",children);
    }
}


//叶子节点1
string _Value::JsonGen(){
    if(this->var_type==C_INTEGER){
        string s=std::to_string(this->i_val);
        return getJsonString("Integer",s);//传入Integer 和其值
    }
    else if(this->var_type==C_REAL ){
        string s=std::to_string(this->f_val);
        return getJsonString("Double",s);
    }
    else if(this->var_type==C_CHAR ){
        char c=this->c_val;
        string t="";
        t.push_back(c);
        cout<<"c:"<<c<<endl;
        cout<<"t:"<<t<<endl;
        return getJsonString("Char",t);
    }
    else if(this->var_type==C_STRING){
        string s=this->s_val;
        cout<<"ssval"<<s<<endl;
        return getJsonString("STRING",s);
    }
}

