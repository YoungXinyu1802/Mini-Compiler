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
            // string ?
            return TheBuilder.getInt8(this->s_val[0]);
        case C_BOOLEAN:
            Debug("C_BOOLEAN");
            return TheBuilder.getInt1(this->b_val);
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
                if(isDouble){
                    return TheBuilder.CreateFAdd(lhsVal, rhsVal, "addtmpf");
                }
                else{
                    return TheBuilder.CreateAdd(lhsVal, rhsVal, "addtmpi");
                }
            }
            case C_SUB:{
                if(isDouble){
                    return TheBuilder.CreateFSub(lhsVal, rhsVal, "subtmpf");
                }
                else{
                    return TheBuilder.CreateSub(lhsVal, rhsVal, "subtmpi");
                }
            }
            case C_MUL:{
                if(isDouble){
                    return TheBuilder.CreateFMul(lhsVal, rhsVal, "multmpf");
                }
                else{
                    return TheBuilder.CreateMul(lhsVal, rhsVal, "multmpi");
                }
            }
            case C_DIV:{
                if(isDouble){
                    return TheBuilder.CreateFDiv(lhsVal, rhsVal, "divtmpf");
                }
                else{
                    return TheBuilder.CreateSDiv(lhsVal, rhsVal, "divtmpi");
                }
            }
            case C_GE:{
                if(isDouble){
                    return TheBuilder.CreateFCmpOGE(lhsVal, rhsVal, "cmptmpf");
                }
                else{
                    return TheBuilder.CreateICmpSGE(lhsVal, rhsVal, "cmptmpi");
                }
            }
            case C_GT:{
                if(isDouble){
                    return TheBuilder.CreateFCmpOGT(lhsVal, rhsVal, "cmptmpf");
                }
                else{
                    return TheBuilder.CreateICmpSGT(lhsVal, rhsVal, "cmptmpi");
                }
            }
            case C_LT:{
                if(isDouble){
                    return TheBuilder.CreateFCmpOLT(lhsVal, rhsVal, "cmptmpf");
                }
                else{
                    return TheBuilder.CreateICmpSLT(lhsVal, rhsVal, "cmptmpi");
                }
            }
            case C_LE:{
                if(isDouble){
                    return TheBuilder.CreateFCmpOLE(lhsVal, rhsVal, "cmptmpf");
                }
                else{
                    return TheBuilder.CreateICmpSLE(lhsVal, rhsVal, "cmptmpi");
                }
            }        
            case C_EQ:{
                if(isDouble){
                    return TheBuilder.CreateFCmpOEQ(lhsVal, rhsVal, "cmptmpf");
                }
                else{
                    return TheBuilder.CreateICmpEQ(lhsVal, rhsVal, "cmptmpi");
                }
            }
            case C_NE:{
                if(isDouble){
                    return TheBuilder.CreateFCmpONE(lhsVal, rhsVal, "cmptmpf");
                }
                else{
                    return TheBuilder.CreateICmpNE(lhsVal, rhsVal, "cmptmpi");
                }
            }
            case C_OR:{
                if(isDouble){
                    Debug("TYPE ERROR");
                    return nullptr;
                }
                return TheBuilder.CreateOr(lhsVal, rhsVal, "ortmp");
            }
            case C_MOD:{
                if(isDouble){
                    return TheBuilder.CreateFRem(lhsVal, rhsVal, "modtmpf");
                }
                else{
                    return TheBuilder.CreateSRem(lhsVal, rhsVal, "modtmpi");
                }
            }
            case C_AND:{
                if(isDouble){
                    Debug("TYPE ERROR");
                    return nullptr;
                }
                return TheBuilder.CreateAnd(lhsVal, rhsVal, "andtmp");
            }
            case C_XOR:{
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
    llvm::BasicBlock *endBlock = llvm::BasicBlock::Create(TheContext, "end", TheFunction);

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
    // llvm::Value *startValue = this->start->codeGen(generator);
    // llvm::Value *endValue = this->end->codeGen(generator);
    // llvm::Value *stepValue = this->step->codeGen(generator);

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
            return value;
        }
        case ELSEIF:{
            for (auto & statement : *this->v_Else.statements){
                value = statement->codeGen(generator);
            }
            return value;
        }
        case ELSE:{
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
    llvm::BasicBlock *mergeBlock = llvm::BasicBlock::Create(TheContext, "merge", TheFunction);

    TheBuilder.CreateCondBr(condValue, thenBlock, elseBlock);
    // Then
    TheBuilder.SetInsertPoint(thenBlock);
    for (auto & statement : *this->statements){
        statement->codeGen(generator);
    }
    TheBuilder.CreateBr(mergeBlock);
    thenBlock = TheBuilder.GetInsertBlock();

    // Else
    TheBuilder.SetInsertPoint(elseBlock);
    this->elsePart->codeGen(generator);
    TheBuilder.CreateBr(mergeBlock);
    elseBlock = TheBuilder.GetInsertBlock();

    // Merge
    TheBuilder.SetInsertPoint(mergeBlock);

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
    for (auto & func : *this->myFuncs){
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
    llvm::Function *function = TheModule->getFunction(*this->func_Name);
    if (!function) {
        std::cerr << "No such function " << this->func_Name << std::endl;
    }

    std::vector<llvm::Value *> funcArgs;
    for (auto & arg : *this->args){
        funcArgs.push_back(arg->codeGen(generator));
    }

    llvm::Value * ret = TheBuilder.CreateCall(function, funcArgs, "call");
    TheBuilder.CreateRet(ret);

    return ret;
}

llvm::Type *llvmType(const BuildInType & type){
    switch(type){
        case C_INTEGER:{
            return TheBuilder.getInt32Ty();
        }
        case C_REAL:{
            return TheBuilder.getDoubleTy();
        }
        case C_BOOLEAN:{
            return TheBuilder.getInt1Ty();
        }
        case C_CHAR:{
            return TheBuilder.getInt8Ty();
        }
    }

}

llvm::AllocaInst *createTempAlloca(llvm::Function * TheFunction, llvm::StringRef varName, llvm::Type * varType){
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
        }
        case FUNCTION:{
            value = this->v_assignExpression.function->codeGen(generator);
        }
    }
    // 还需要区分是不是数组，有点问题
    TheBuilder.CreateStore(value, generator.getValue(*this->val->ID_Name));
    return value;
}

// finished
llvm::Value *_Definition::codeGen(CodeGenerator & generator){
    Debug("_Definition::codeGen");
    llvm::Type *defType;
    llvm::Function *TheFunction = generator.getCurFunc();

    bool isArray = (variable->v_Type == _Variable::ARRAY);

    if (isArray){
        llvm::Value *size = this->variable->expr->codeGen(generator);
        llvm::ConstantInt *sizeInt = llvm::dyn_cast<llvm::ConstantInt>(size);
        // uint64_t size_int = size->getUniqueInteger().getZextValue();
        llvm::Type *arrayType = llvm::ArrayType::get(defType, sizeInt->getZExtValue());
    }
    else{
        defType = llvmType(this->def_Type);
        // auto alloc = createTempAlloca(TheFunction, *variable->ID_Name, defType);
    }
    auto alloc = createTempAlloca(TheFunction, *variable->ID_Name, defType);
    return alloc;
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
    auto alloc = createTempAlloca(TheFunction, *args->ID_Name, defType);
    return alloc;
}

// unfinished
llvm::Value *_Variable::codeGen(CodeGenerator & generator){
    Debug("_Variable::codeGen");
    llvm::Value *value = generator.getValue(*this->ID_Name);
    if(this->v_Type == CONST){
        return value;
    }
    else if (this->v_Type == ARRAY){
        llvm::Value *index = this->expr->codeGen(generator);
    }

}

llvm::Value *_mainFunction::codeGen(CodeGenerator & generator){
    Debug("_mainFunction::codeGen");
    for (auto & statement : *this->statements){
        statement->codeGen(generator);
    }
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
    llvm::Function *function = llvm::Function::Create(funcType, llvm::GlobalValue::InternalLinkage, *this->Func_Id, TheModule.get());
    generator.pushFunc(function);

    // create a basic block
    llvm::BasicBlock *basicBlock = llvm::BasicBlock::Create(TheContext, "entry", function);
    TheBuilder.SetInsertPoint(basicBlock);

    // create a function argument iterator
    llvm::Function::arg_iterator argIter = function->arg_begin();
    for (auto & arg : *this->args){
        llvm::AllocaInst *alloc = createTempAlloca(function, *arg->args->ID_Name, llvmType(arg->arg_Type));
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
    TheBuilder.SetInsertPoint(&(generator.getCurFunc())->getBasicBlockList().back());
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
        if(varType == TheBuilder.getInt8Ty()){
            format += "%c";
        }
        else if(varType == TheBuilder.getInt32Ty()){
            format += "%d";
        }
        else if(varType == TheBuilder.getDoubleTy()){
            format += "%f";
        }
        else if(varType == TheBuilder.getInt8Ty()){
            format += "%d";
        }
        params.push_back(varValue);
    }
    params.insert(params.begin(), TheBuilder.CreateGlobalStringPtr(format));
    
    auto scanf_type = llvm::FunctionType::get(TheBuilder.getInt32Ty(), true);
    auto func = llvm::Function::Create(scanf_type, llvm::Function::ExternalLinkage, llvm::Twine("scanf"), TheModule.get());
    
    return TheBuilder.CreateCall(func, params, "scanf");

}

llvm::Value *_Output::codeGen(CodeGenerator & generator){
    Debug("_Output::codeGen");

    string format = "";
    vector<llvm::Value*> params;
    for (auto & var : *this->vars){
        llvm::Value *varValue = var->codeGen(generator);
        llvm::Type *varType = varValue->getType();
        if(varType == TheBuilder.getInt8Ty()){
            format += "%c";
        }
        else if(varType == TheBuilder.getInt32Ty()){
            format += "%d";
        }
        else if(varType == TheBuilder.getDoubleTy()){
            format += "%f";
        }
        else if(varType == TheBuilder.getInt8Ty()){
            format += "%d";
        }
        params.push_back(varValue);
    }
    params.insert(params.begin(), TheBuilder.CreateGlobalStringPtr(format));


    std::vector<llvm::Type*> argsType;
    argsType.push_back(TheBuilder.getInt8PtrTy());
    auto outputType = llvm::FunctionType::get(TheBuilder.getInt32Ty(), llvm::makeArrayRef(argsType), true);
    auto func = llvm::Function::Create(outputType, llvm::Function::ExternalLinkage, llvm::Twine("printf"), TheModule.get());
}