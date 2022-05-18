#include "ast.hh"
#include "codeGen.h"

using namespace std;

// problems: array, input, output, assignment, variable
void Debug(string s){
    cout << "[Debug]" << s << endl;
}

llvm::Value *_Value::codeGen(CodeGenerator & generator){
    Debug("_Value::codeGen");
    switch(this->var_type){
        case C_INTEGER:
            Debug("C_INTEGER");
            return TheBuilder.getInt32(this->i_val);
        case C_REAL:
            Debug("C_REAL");
            return llvm::ConstantFP::get(TheContext, llvm::APFloat(this->f_val));
        case C_CHAR:
            Debug("C_CHAR");
            return TheBuilder.getInt8(this->c_val);
        case C_BOOLEAN:
            Debug("C_BOOLEAN");
            return TheBuilder.getInt1(this->b_val);
        case C_STRING:
            Debug("C_STRING");
            std::string s = this->s_val.substr(1, this->s_val.size()-2);
            Debug(this->s_val);
            return TheBuilder.CreateGlobalStringPtr(s);
    }
}



llvm::Value *_singleExpression::codeGen(CodeGenerator & generator){
    Debug("_singleExpression::codeGen");
    if(this->v_Type == VALUE){
        return this->v_single.val->codeGen(generator);
    }

    else if(this->v_Type == VARIABLE){
        return this->v_single.var->codeGen(generator);
    }

    else if(this->v_Type == EXPRESSION){
        // get the values
        llvm::Value *lhsVal = lhs->codeGen(generator);
        llvm::Value *rhsVal = rhs->codeGen(generator);

        // conduct the operation
        bool isDouble = lhsVal->getType()->isDoubleTy() || rhsVal->getType()->isDoubleTy();
        switch(this->OP){
            case C_ADD:{
                Debug("C_ADD");
                if(isDouble){
                    return TheBuilder.CreateFAdd(lhsVal, rhsVal, "addtmpf");
                }
                else{
                    return TheBuilder.CreateAdd(lhsVal, rhsVal, "addtmpi");
                }
            }
            case C_SUB:{
                Debug("C_SUB");
                if(isDouble){
                    return TheBuilder.CreateFSub(lhsVal, rhsVal, "subtmpf");
                }
                else{
                    return TheBuilder.CreateSub(lhsVal, rhsVal, "subtmpi");
                }
            }
            case C_MUL:{
                Debug("C_MUL");
                if(isDouble){
                    return TheBuilder.CreateFMul(lhsVal, rhsVal, "multmpf");
                }
                else{
                    return TheBuilder.CreateMul(lhsVal, rhsVal, "multmpi");
                }
            }
            case C_DIV:{
                Debug("C_DIV");
                if(isDouble){
                    return TheBuilder.CreateFDiv(lhsVal, rhsVal, "divtmpf");
                }
                else{
                    return TheBuilder.CreateSDiv(lhsVal, rhsVal, "divtmpi");
                }
            }
            case C_GE:{
                Debug("C_GE");
                if(isDouble){
                    return TheBuilder.CreateFCmpOGE(lhsVal, rhsVal, "cmptmpf");
                }
                else{
                    return TheBuilder.CreateICmpSGE(lhsVal, rhsVal, "cmptmpi");
                }
            }
            case C_GT:{
                Debug("C_GT");
                if(isDouble){
                    return TheBuilder.CreateFCmpOGT(lhsVal, rhsVal, "cmptmpf");
                }
                else{
                    return TheBuilder.CreateICmpSGT(lhsVal, rhsVal, "cmptmpi");
                }
            }
            case C_LT:{
                Debug("C_LT");
                if(isDouble){
                    return TheBuilder.CreateFCmpOLT(lhsVal, rhsVal, "cmptmpf");
                }
                else{
                    return TheBuilder.CreateICmpSLT(lhsVal, rhsVal, "cmptmpi");
                }
            }
            case C_LE:{
                Debug("C_LE");
                if(isDouble){
                    return TheBuilder.CreateFCmpOLE(lhsVal, rhsVal, "cmptmpf");
                }
                else{
                    return TheBuilder.CreateICmpSLE(lhsVal, rhsVal, "cmptmpi");
                }
            }        
            case C_EQ:{
                Debug("C_EQ");
                if(isDouble){
                    return TheBuilder.CreateFCmpOEQ(lhsVal, rhsVal, "cmptmpf");
                }
                else{
                    return TheBuilder.CreateICmpEQ(lhsVal, rhsVal, "cmptmpi");
                }
            }
            case C_NE:{
                Debug("C_NE");
                if(isDouble){
                    return TheBuilder.CreateFCmpONE(lhsVal, rhsVal, "cmptmpf");
                }
                else{
                    return TheBuilder.CreateICmpNE(lhsVal, rhsVal, "cmptmpi");
                }
            }
            case C_OR:{
                Debug("C_OR");
                if(isDouble){
                    Debug("TYPE ERROR");
                    return nullptr;
                }
                return TheBuilder.CreateOr(lhsVal, rhsVal, "ortmp");
            }
            case C_MOD:{
                Debug("C_MOD");
                if(isDouble){
                    return TheBuilder.CreateFRem(lhsVal, rhsVal, "modtmpf");
                }
                else{
                    return TheBuilder.CreateSRem(lhsVal, rhsVal, "modtmpi");
                }
            }
            case C_AND:{
                Debug("C_AND");
                if(isDouble){
                    Debug("TYPE ERROR");
                    return nullptr;
                }
                return TheBuilder.CreateAnd(lhsVal, rhsVal, "andtmp");
            }
            case C_XOR:{
                Debug("C_XOR");
                if(isDouble){
                    Debug("TYPE ERROR");
                    return nullptr;
                }
                return TheBuilder.CreateXor(lhsVal, rhsVal, "xortmp");
            }
        }
    }
}

llvm::Value *_returnStatement::codeGen(CodeGenerator & generator){
    Debug("_returnStatement::codeGen");
    llvm::Value *retVal = this->expr->codeGen(generator);
    TheBuilder.CreateRet(retVal);
    return retVal;
}

llvm::Value *_whileStatement::codeGen(CodeGenerator & generator){
    Debug("_whileStatement::codeGen");

    llvm::Function *TheFunction = generator.getCurFunc();
    llvm::BasicBlock *condBlock = llvm::BasicBlock::Create(TheContext, "cond", TheFunction);
    llvm::BasicBlock *loopBlock = llvm::BasicBlock::Create(TheContext, "loop", TheFunction);
    llvm::BasicBlock *endBlock = llvm::BasicBlock::Create(TheContext, "loopend", TheFunction);

    // condtion block
    TheBuilder.CreateBr(condBlock);
    TheBuilder.SetInsertPoint(condBlock);
    llvm::Value *condValue = this->condition->codeGen(generator);
    auto branch = TheBuilder.CreateCondBr(condValue, loopBlock, endBlock);
    condBlock = TheBuilder.GetInsertBlock();

    // loop block
    TheBuilder.SetInsertPoint(loopBlock);
    for (auto statement : *this->statements){
        statement->codeGen(generator);
    }
    TheBuilder.CreateBr(condBlock);

    // end block
    TheBuilder.SetInsertPoint(endBlock);
    return branch;
}

llvm::Value *_forStatement::codeGen(CodeGenerator & generator){
    llvm::Function *TheFunction = generator.getCurFunc();
    this->startExpr->codeGen(generator);

    llvm::BasicBlock *condBlock = llvm::BasicBlock::Create(TheContext, "forcond", TheFunction);
    llvm::BasicBlock *endBlock = llvm::BasicBlock::Create(TheContext, "forend", TheFunction);
    llvm::BasicBlock *loopBlock = llvm::BasicBlock::Create(TheContext, "forbody", TheFunction);
    TheBuilder.CreateBr(condBlock);

    // basic block for condition
    TheBuilder.SetInsertPoint(condBlock);
    // maybe it should be cast to boolean
    llvm::Value *condValue = this->condExpr->codeGen(generator);
    auto block = TheBuilder.CreateCondBr(condValue, loopBlock, endBlock);

    // basic block for body
    TheBuilder.SetInsertPoint(loopBlock);
    for (auto & stmt : *this->statements){
        stmt->codeGen(generator);
    }
    // step
    // assignment should return the updated value
    llvm::Value *updateVal = this->stepExpr->codeGen(generator);
    TheBuilder.CreateBr(condBlock);
    loopBlock = TheBuilder.GetInsertBlock();

    // basic block for end
    TheBuilder.SetInsertPoint(endBlock);
    return block;
}

llvm::Value *_elsePart::codeGen(CodeGenerator & generator){
    Debug("_elseStatement::codeGen");
    llvm::Value *value = nullptr;
    switch(this->v_Type){
        case NONE:{
            Debug("NONE");
            return value;
        }
        case ELSE:{
            Debug("ELSE");
            for (auto & statement : *this->v_Else.statements){
                value = statement->codeGen(generator);
            }
            return value;
        }
        case ELSEIF:{
            Debug("ELSEIF");
            return this->v_Else.ifBody->codeGen(generator);
        }
    }

}

llvm::Value *_ifStatement::codeGen(CodeGenerator & generator){
    Debug("_ifStatement::codeGen");

    llvm::Value *condValue = this->condition->codeGen(generator);
    condValue = TheBuilder.CreateICmpNE(condValue, llvm::ConstantInt::get(llvm::Type::getInt1Ty(TheContext), 0, true), "ifCond");

    llvm::Function *TheFunction = generator.getCurFunc();
    llvm::BasicBlock *thenBlock = llvm::BasicBlock::Create(TheContext, "then", TheFunction);
    llvm::BasicBlock *elseBlock = llvm::BasicBlock::Create(TheContext, "else", TheFunction);
    llvm::BasicBlock *endBlock = llvm::BasicBlock::Create(TheContext, "ifend", TheFunction);

    TheBuilder.CreateCondBr(condValue, thenBlock, elseBlock);
    // Then
    TheBuilder.SetInsertPoint(thenBlock);
    for (auto & statement : *this->statements){
        statement->codeGen(generator);
    }
    TheBuilder.CreateBr(endBlock);
    thenBlock = TheBuilder.GetInsertBlock();

    // Else
    TheBuilder.SetInsertPoint(elseBlock);
    this->elsePart->codeGen(generator);
    TheBuilder.CreateBr(endBlock);
    elseBlock = TheBuilder.GetInsertBlock();

    // Merge
    TheBuilder.SetInsertPoint(endBlock);

    return nullptr;
}

llvm::Value *_complexExpression::codeGen(CodeGenerator & generator){
    Debug("_complexExpression::codeGen");
    switch(this->v_Type){
        case FOR:{
            return this->v_complexExpression.forSTMT->codeGen(generator);
        }
        case WHILE:{
            return this->v_complexExpression.whileSTMT->codeGen(generator);
        }
        case IF:{
            return this->v_complexExpression.ifSTMT->codeGen(generator);
        }
    }
}

llvm::Value *_Term::codeGen(CodeGenerator & generator){
    Debug("_Term::codeGen");
    switch(this->v_Type){
        case VALUE:{
            return this->v_Term.val->codeGen(generator);
        }
        case VARIABLE:{
            return this->v_Term.var->codeGen(generator);
        }
        case SINGLE:{
            return this->v_Term.singleExpr->codeGen(generator);
        }
    }
}

llvm::Value *_Program::codeGen(CodeGenerator & generator){
    Debug("_Program::codeGen");

    for (auto func : *this->myFuncs){
        std::cout << "hello" << std::endl;
        func->codeGen(generator);
    }
}

llvm::Value *_Function::codeGen(CodeGenerator & generator){
    Debug("_Function::codeGen");
    switch(this->v_Type){
        case MAIN:{
            return this->v_Function.mainFunc->codeGen(generator);
        }
        case SUB:{
            return this->v_Function.subFunc->codeGen(generator);
        }
    }
}


llvm::Value *_functionCall::codeGen(CodeGenerator & generator){
    Debug("_functionCall::codeGen");
    llvm::Function *function = generator.TheModule->getFunction(*this->func_Name);
    if (!function) {
        std::cerr << "No such function " << this->func_Name << std::endl;
    }

    std::vector<llvm::Value *> funcArgs;
    for (auto & arg : *this->args){
        funcArgs.push_back(arg->codeGen(generator));
    }

    llvm::Value * ret = TheBuilder.CreateCall(function, funcArgs, "call");
    return ret;
}

llvm::Type *llvmType(const BuildInType & type){
    switch(type){
        case C_INTEGER:{
            Debug("llvmType::C_INTEGER");
            return llvm::Type::getInt32Ty(TheContext);
        }
        case C_REAL:{
            Debug("llvmType::C_REAL");
            return llvm::Type::getDoubleTy(TheContext);
        }
        case C_BOOLEAN:{
            Debug("llvmType::C_BOOLEAN");
            return llvm::Type::getInt1Ty(TheContext);
        }
        case C_CHAR:{
            Debug("llvmType::C_CHAR");
            return llvm::Type::getInt8Ty(TheContext);
        }
    }

}

llvm::AllocaInst *createDefAlloca(llvm::Function * TheFunction, llvm::StringRef varName, llvm::Type * varType){
    llvm::IRBuilder<> tmpBuilder(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
    return tmpBuilder.CreateAlloca(varType, nullptr, varName);
}

llvm::Value *_Statement::codeGen(CodeGenerator & generator){
    Debug("_Statement::codeGen");
    switch(this->v_Type){
        case DEFINITION:{
            return this->v_Statement.definStatement->codeGen(generator);
        }
        case EXPRESSION:{
            return this->v_Statement.exprStatement->codeGen(generator);
        }
        case RETURNSTATEMENT:{
            return this->v_Statement.returnStatement->codeGen(generator);
        }
        case INPUT:{
            return this->v_Statement.inputExpr->codeGen(generator);
        }
        case OUTPUT:{
            return this->v_Statement.outputExpr->codeGen(generator);
        }
    }
}

llvm::Value *_Expression::codeGen(CodeGenerator & generator){
    Debug("_Expression::codeGen");
    switch(this->v_Type){
        case ASSIGNMENT:{
            return this->v_Expression.assignExpression->codeGen(generator);
        }
        case COMPLEX:{
            return this->v_Expression.complexExpression->codeGen(generator);
        }
        case FUNCTIONCALL:{
            return this->v_Expression.functionCall->codeGen(generator);
        }
    }
}

llvm::Value *_assignExpression::codeGen(CodeGenerator & generator){
    Debug("_assignExpression::codeGen");
    llvm::Value *value = nullptr;
    switch(this->v_Type){
        case SINGLE:{
            value = this->v_assignExpression.rhs->codeGen(generator);
            if(val->v_Type==_Variable::CONST)
                TheBuilder.CreateStore(value, generator.getValue(*this->val->ID_Name));
            else{
                llvm::Value *vindex =val->expr->codeGen(generator);

                llvm::ConstantInt *indexInt = llvm::dyn_cast<llvm::ConstantInt>(vindex);        
                int index=indexInt->getZExtValue();
                auto array= generator.getValue(*this->val->ID_Name);
                llvm::Type * arrayType = TheBuilder.CreateLoad(array)->getType();//->getArrayElementType();
                //arrayType->print(llvm::outs());
                //cout<<endl<<arrayType->getTypeID()<<endl;
                TheBuilder.CreateStore(value,TheBuilder.CreateConstGEP2_32(arrayType,array,0,index));
            }
            break;
        }
        case FUNCTION:{
            value = this->v_assignExpression.function->codeGen(generator);

            TheBuilder.CreateStore(value, generator.getValue(*this->val->ID_Name));
            break;
        }
        case ARRAY:{
            auto array= generator.getValue(*this->val->ID_Name);
            llvm::Type * arrayType = TheBuilder.CreateLoad(array)->getType();
            int index=0;
            for (auto var : *this->v_assignExpression.data){
                _Value * _value = dynamic_cast<_Value*>(var);
                llvm::Value* value=_value->codeGen(generator);
                TheBuilder.CreateStore(value,TheBuilder.CreateConstGEP2_32(arrayType,array,0,index));
                index++;
            }
            break;
        }
        
    }
    
    
    return value;
}

// finished
llvm::Value *_Definition::codeGen(CodeGenerator & generator){
    Debug("_Definition::codeGen");
    llvm::Type *defType;
    llvm::Function *TheFunction = generator.getCurFunc();
    llvm::Value* alloca = nullptr;
    for (auto var : *this->data){
        _Variable * variable = dynamic_cast<_Variable*>(var);
        bool isArray = (variable->v_Type == _Variable::ARRAY);

        if (isArray){
            llvm::Value *size = variable->expr->codeGen(generator);
            llvm::ConstantInt *sizeInt = llvm::dyn_cast<llvm::ConstantInt>(size);
            // uint64_t size_int = size->getUniqueInteger().getZextValue();
            defType = llvmType(this->def_Type);
            llvm::Type *arrayType = llvm::ArrayType::get(defType, sizeInt->getZExtValue());
            auto alloc = createDefAlloca(generator.getCurFunc(), *variable->ID_Name, arrayType);
            
            // llvm::Type * arrayT=alloc->getType()->getElementType();
            // llvm::Value *value = generator.getValue(*variable->ID_Name);
            // value = TheBuilder.CreateLoad(value);
            // auto arrayT1=value->getType();

            // arrayType->print(llvm::outs());
            // cout<<" "<<arrayType->getTypeID()<<endl;
            // arrayT->print(llvm::outs());
            // cout<<" "<<arrayT->getTypeID()<<endl;
            // arrayT1->print(llvm::outs());
            // cout<<" "<<arrayT1->getTypeID()<<" "<<arrayT1->isArrayTy()<<endl;

            // llvm::Constant* con_5 = llvm::ConstantInt::get(llvm::Type::getInt32Ty(TheContext), 5);
            // TheBuilder.CreateStore(con_5,TheBuilder.CreateConstGEP2_32(arrayT1,alloc,0,1));
        }
        else{
            defType = llvmType(this->def_Type);
            // auto alloc = createTempAlloca(TheFunction, *variable->ID_Name, defType);
            auto alloc = createDefAlloca(generator.getCurFunc(), *variable->ID_Name, defType);
        }

        // alloca = TheBuilder.CreateAlloca(defType, nullptr, *variable->ID_Name);
        //auto alloc = createTempAlloca(generator.getCurFunc(), *variable->ID_Name, defType);
        std::cout << "alloca: " << *variable->ID_Name << std::endl;
        // TheBuilder.CreateAlloca(defType);
    }

    return alloca;
}

// confusing...
llvm::Value *_argsDefinition::codeGen(CodeGenerator & generator){
    Debug("_Definition::codeGen");
    llvm::Type *defType;
    llvm::Function *TheFunction = generator.getCurFunc();

    bool isArray = (args->v_Type == _Variable::ARRAY);

    if (isArray){
        llvm::Value *size = this->args->expr->codeGen(generator);
        llvm::ConstantInt *sizeInt = llvm::dyn_cast<llvm::ConstantInt>(size);
        // uint64_t size_int = size->getUniqueInteger().getZextValue();
        llvm::Type *arrayType = llvm::ArrayType::get(defType, sizeInt->getZExtValue());
    }
    else{
        defType = llvmType(this->arg_Type);
        // auto alloc = createTempAlloca(TheFunction, *variable->ID_Name, defType);
    }
    auto alloc = createDefAlloca(TheFunction, *args->ID_Name, defType);
    return alloc;
}

// unfinished
llvm::Value *_Variable::codeGen(CodeGenerator & generator){
    Debug("_Variable::codeGen");
    llvm::Value *value = generator.getValue(*this->ID_Name);
    value = TheBuilder.CreateLoad(value);
    if(this->v_Type == CONST){
        return value;
    }
    else if (this->v_Type == ARRAY){
        llvm::Value *index = this->expr->codeGen(generator);
    }

}

llvm::Value *_mainFunction::codeGen(CodeGenerator & generator){
    Debug("_mainFunction::codeGen");
    vector<llvm::Type*> argTypes;
    llvm::FunctionType *funcType = llvm::FunctionType::get(TheBuilder.getInt32Ty(), argTypes, false);
    generator.mainFunction = llvm::Function::Create(funcType, llvm::GlobalValue::ExternalLinkage, "Main", generator.TheModule.get());
    llvm::BasicBlock *basicBlock = llvm::BasicBlock::Create(TheContext, "entry", generator.mainFunction, 0);
    generator.pushFunc(generator.mainFunction);
    TheBuilder.SetInsertPoint(basicBlock);

    for (auto & statement : *this->statements){
        statement->codeGen(generator);
    }
    //Pop back
    generator.popFunc();
}

llvm::Value *_Subroutine::codeGen(CodeGenerator & generator){
    Debug("_Subroutine::codeGen");
    vector<llvm::Type *> argsType;
    for (auto & arg : *this->args){
        argsType.push_back(llvmType(arg->arg_Type));
    }
    BuildInType retType;
    if(*Type=="int"){
        retType=C_INTEGER;
    }
    else if(*Type=="char"){
        retType=C_CHAR;
    }
    else if (*Type=="double"){
        retType=C_REAL;
    }
    else{
        retType=C_BOOLEAN;
    }
    llvm::FunctionType *funcType = llvm::FunctionType::get(llvmType(retType), argsType, false);
    llvm::Function *function = llvm::Function::Create(funcType, llvm::GlobalValue::InternalLinkage, *this->Func_Id, generator.TheModule.get());
    generator.pushFunc(function);

    // create a basic block
    llvm::BasicBlock *basicBlock = llvm::BasicBlock::Create(TheContext, "entry", function);
    TheBuilder.SetInsertPoint(basicBlock);

    // create a function argument iterator
    llvm::Function::arg_iterator argIter = function->arg_begin();
    for (auto & arg : *this->args){
        llvm::AllocaInst *alloc = createDefAlloca(function, *arg->args->ID_Name, llvmType(arg->arg_Type));
        TheBuilder.CreateStore(argIter++, alloc);
    }
    // // return
    // llvm::Value *res = nullptr;
    // res = createTempAlloca(function, "res", llvmType(retType));
    
    //Sub routine
    for (auto & stmt : *this->statements){
        stmt->codeGen(generator);
    }
    
    //Pop back
    generator.popFunc();
    return function;    

}

// confusing...
llvm::Value *_Input::codeGen(CodeGenerator & generator){
    Debug("_Input::codeGen");   
    string format = "";
    vector<llvm::Value*> params;
    for (auto & var : *this->vars){
        llvm::Value *varValue = var->codeGen(generator);
        llvm::Type *varType = varValue->getType();
        llvm::Value *varAddr = generator.getValue(dynamic_cast<_Variable*>(var)->ID_Name->c_str());
        if(varType == TheBuilder.getInt8Ty()){
            format += "%c";
        }
        else if(varType == TheBuilder.getInt32Ty()){
            format += "%d";
        }
        else if(varType == TheBuilder.getDoubleTy()){
            format += "%lf";
        }
        else if(varType == TheBuilder.getInt8Ty()){
            format += "%d";
        }
        params.push_back(varAddr);
    }
    params.insert(params.begin(), TheBuilder.CreateGlobalStringPtr(format));
    
    // return TheBuilder.CreateCall(func, params, "scanf");
    TheBuilder.CreateCall(generator.scanFunction, params, "scanf");


}

llvm::Value *_Output::codeGen(CodeGenerator & generator){
    Debug("_Output::codeGen");

    string format = "";
    vector<llvm::Value*> params;
    bool isString;
    llvm::Value * varValue;
    llvm::Value * strValue;
    for (auto & var : *this->vars){
        varValue = var->codeGen(generator);
        llvm::Type *varType = varValue->getType();
        if(varType == TheBuilder.getInt8Ty()){
            format += "%c";
        }
        else if(varType == TheBuilder.getInt32Ty()){
            format += "%d";
        }
        else if(varType == TheBuilder.getDoubleTy()){
            format += "%lf";
        }
        else if(varType == TheBuilder.getInt8Ty()){
            format += "%d";
        }
        else{
            format += "%s";
        }
        params.push_back(varValue);
    }
    params.insert(params.begin(), TheBuilder.CreateGlobalStringPtr(format));
    TheBuilder.CreateCall(generator.printFunction, llvm::makeArrayRef(params), "printf");
}
