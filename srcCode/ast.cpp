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
        bool lhsDouble, rhsDouble, isDouble;
        lhsDouble = lhsVal->getType()->isDoubleTy();
        rhsDouble = rhsVal->getType()->isDoubleTy();
        isDouble = lhsDouble || rhsDouble;
        if(isDouble){
            lhsVal = TheBuilder.CreateSIToFP(lhsVal, llvm::Type::getDoubleTy(TheContext));
            rhsVal = TheBuilder.CreateSIToFP(rhsVal, llvm::Type::getDoubleTy(TheContext));
        }

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
        case C_VOID:{
            Debug("llvmType::C_VOID");
            return llvm::Type::getVoidTy(TheContext);
        }
    }

}
llvm::Value *_Program::codeGen(CodeGenerator & generator){
    Debug("_Program::codeGen");
    if(this->hasStruct())
    {
        for(auto stu :*this->myStructs){
            std::string name=*stu->struct_ID;
            generator.StructMap[name]=stu;
            llvm::StructType *structType = generator.TheModule->getTypeByName(name);//获取当前module中名为Number的结构体
            if (!structType) {
                    //如果当前module中没有，就创建一个
                structType = llvm::StructType::create(TheContext, name);
                std::vector<llvm::Type*> elements;	//添加结构体元素
                for (auto defvar : *stu->defins){
                    llvm::Type* defType;
                    if(defvar->isStruct){
                        defType=generator.TypeMap[defvar->getStructID()];
                    }
                    else{
                        defType = llvmType(defvar->def_Type);
                    }
                    for (auto elemvar : *defvar->data){
                        llvm::Type* type;
                        _Variable * elemvariable = dynamic_cast<_Variable*>(elemvar);
                        if(elemvariable->v_Type == _Variable::ARRAY){
                            llvm::Value *size = elemvariable->exprID->codeGen(generator);
                            llvm::ConstantInt *sizeInt = llvm::dyn_cast<llvm::ConstantInt>(size);                       
                            type = llvm::ArrayType::get(defType, sizeInt->getZExtValue());
                        }
                        else{
                            type=defType;
                        }
                        elements.push_back(type);
                    }
                }
                structType->setBody(elements);
                generator.TypeMap[name]=structType;
            }
            
        }
    }
    

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
    if (this->args){
        for (auto & arg : *this->args){
            funcArgs.push_back(arg->codeGen(generator));
        }
    }
    llvm::Value * ret = TheBuilder.CreateCall(function, funcArgs, "call");
    return ret;
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
            else if(val->v_Type==_Variable::ARRAY){            
                cout<<"single array assignment"<<endl;
                llvm::Value *index =val->exprID->codeGen(generator);
                auto array= generator.getValue(*this->val->ID_Name);
                
                llvm::Constant* con_0 = llvm::ConstantInt::get(llvm::Type::getInt32Ty(TheContext), 0);
                llvm::Value *Idxs[]={con_0,index};
                llvm::Value *array_i;
                if(generator.getCurFunc()->getName()=="Main")
                {
                    cout<<"Array in function main"<<endl;
                    array_i = TheBuilder.CreateGEP(array,Idxs);
                }
                else
                {
                    cout<<"Array in function args"<<endl;
                    array=TheBuilder.CreateLoad(array);
                    array_i = TheBuilder.CreateGEP(array,index);
                }             
                //TheBuilder.CreateStore(value,TheBuilder.CreateConstGEP2_32(arrayType,array,0,index));
                TheBuilder.CreateStore(value,array_i);       
            }
            else if(val->v_Type==_Variable::Struct){
                cout<<"single struct assignment"<<endl;
                std::string name=*val->ID_Name;
                std::string mem=*val->member;
                std::string struct_ID = generator.VarStructID[name];
                _Struct* stru = generator.StructMap[struct_ID];
                llvm::Type* structType = generator.TypeMap[struct_ID];
                int index = stru->getIndex(mem);

                auto alloc = generator.getValue(name);
                TheBuilder.CreateStore(value,TheBuilder.CreateConstGEP2_32(structType,alloc,0,index));
            }
            else if(val->v_Type==_Variable::MemARRAY){
                std::string name=*val->ID_Name;
                std::string mem=*val->member;
                std::string struct_ID = generator.VarStructID[name];
                _Struct* stru = generator.StructMap[struct_ID];
                llvm::Type* structType = generator.TypeMap[struct_ID];
                int index1 = stru->getIndex(mem);

                auto alloc = generator.getValue(name);
                alloc = TheBuilder.CreateConstGEP2_32(structType,alloc,0,index1);

                llvm::Value *index =val->exprMem->codeGen(generator);
                llvm::Constant* con_0 = llvm::ConstantInt::get(llvm::Type::getInt32Ty(TheContext), 0);
                llvm::Value *Idxs[]={con_0,index};
                alloc = TheBuilder.CreateGEP(alloc,Idxs);
                TheBuilder.CreateStore(value,alloc);
            }
            else if(val->v_Type==_Variable::StructARRAY){
                cout<<"sing structarray assignment"<<endl;
                llvm::Value *index1 =val->exprID->codeGen(generator);
                auto array= generator.getValue(*this->val->ID_Name);
                llvm::Constant* con_0 = llvm::ConstantInt::get(llvm::Type::getInt32Ty(TheContext), 0);
                llvm::Value *Idxs[]={con_0,index1};
                array = TheBuilder.CreateGEP(array,Idxs);

                std::string name=*val->ID_Name;
                std::string mem=*val->member;
                std::string struct_ID = generator.VarStructID[name];
                _Struct* stru = generator.StructMap[struct_ID];
                llvm::Type* structType = generator.TypeMap[struct_ID];
                int index = stru->getIndex(mem);

                TheBuilder.CreateStore(value,TheBuilder.CreateConstGEP2_32(structType,array,0,index));
            }
            else if(val->v_Type==_Variable::StructMemARRAY){
                cout<<"sing structMemarray assignment"<<endl;
                llvm::Value *index0 =val->exprID->codeGen(generator);
                auto array= generator.getValue(*this->val->ID_Name);
                llvm::Constant* con_0 = llvm::ConstantInt::get(llvm::Type::getInt32Ty(TheContext), 0);
                llvm::Value *Idxs0[]={con_0,index0};
                array = TheBuilder.CreateGEP(array,Idxs0);

                std::string name=*val->ID_Name;
                std::string mem=*val->member;
                std::string struct_ID = generator.VarStructID[name];
                _Struct* stru = generator.StructMap[struct_ID];
                llvm::Type* structType = generator.TypeMap[struct_ID];
                int index1 = stru->getIndex(mem);

                auto alloc = TheBuilder.CreateConstGEP2_32(structType,array,0,index1);

                llvm::Value *index =val->exprMem->codeGen(generator);
                llvm::Value *Idxs[]={con_0,index};
                alloc = TheBuilder.CreateGEP(alloc,Idxs);
                TheBuilder.CreateStore(value,alloc);
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
            if(val->v_Type==_Variable::Struct){
                cout<<"Struct array assignment"<<endl;
                std::string name=*val->ID_Name;
                std::string mem=*val->member;
                std::string struct_ID = generator.VarStructID[name];
                _Struct* stru = generator.StructMap[struct_ID];
                llvm::Type* structType = generator.TypeMap[struct_ID];
                int index1 = stru->getIndex(mem);

                array = TheBuilder.CreateConstGEP2_32(structType,array,0,index1);
            }
            
            llvm::Type * arrayType = TheBuilder.CreateLoad(array)->getType();
            arrayType->print(llvm::outs());
            cout<<endl;
            int index=0;
            for (auto var : *this->v_assignExpression.data){
                _Value * _value = dynamic_cast<_Value*>(var);
                llvm::Value* value=_value->codeGen(generator);
                TheBuilder.CreateStore(value,TheBuilder.CreateConstGEP2_32(arrayType,array,0,index));
                index++;
            }
            break;
        }
        //case STRUCT     
    }   
    return value;
}

// finished
llvm::Value *_Definition::codeGen(CodeGenerator & generator){
    Debug("_Definition::codeGen");
    llvm::Type *defType;
    llvm::Function *TheFunction = generator.getCurFunc();
    llvm::Value* alloca = nullptr;

    if(this->isStruct){
        defType=generator.TypeMap[this->getStructID()];
    }
    else{
        defType = llvmType(this->def_Type);
    }
    for (auto var : *this->data){
        _Variable * variable = dynamic_cast<_Variable*>(var);
        if(this->isStruct){
            generator.VarStructID[*variable->ID_Name]=this->getStructID();
        }
        bool isArray = (variable->v_Type == _Variable::ARRAY);

        if (isArray){
            llvm::Value *size = variable->exprID->codeGen(generator);
            llvm::ConstantInt *sizeInt = llvm::dyn_cast<llvm::ConstantInt>(size);
            // uint64_t size_int = size->getUniqueInteger().getZextValue();            
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
        llvm::Value *size = this->args->exprID->codeGen(generator);
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


llvm::Value *_Variable::codeGen(CodeGenerator & generator){
    Debug("_Variable::codeGen");
    llvm::Value *value = nullptr;

    if(this->v_Type == CONST){
        cout << "const" << endl;
        value = generator.getValue(*this->ID_Name);
        value = TheBuilder.CreateLoad(value);
    }
    else if (this->v_Type == ARRAY){
         cout << "array" << endl;
        llvm::Value *index = this->exprID->codeGen(generator);
        llvm::Constant* con_0 = llvm::ConstantInt::get(llvm::Type::getInt32Ty(TheContext), 0);
        llvm::Value *Idxs[]={con_0,index};
        auto array= generator.getValue(*this->ID_Name);
        llvm::Value *array_i;
        if(generator.getCurFunc()->getName()=="Main")
        {
            cout<<"Array in function main"<<endl;
            array_i = TheBuilder.CreateGEP(array,Idxs);
        }
        else
        {
            cout<<"Array in function args"<<endl;
            array=TheBuilder.CreateLoad(array);
            array_i = TheBuilder.CreateGEP(array,index);
        }
        value = TheBuilder.CreateLoad(array_i);

    }
    else if (this->v_Type == ArrayPtr){
        value = generator.getValue(*this->ID_Name);
        // value = TheBuilder.CreateLoad(value);
        cout << "variable type" << value->getType()->getTypeID() << endl;
    }
    else if (this->v_Type == Struct){
        cout<<"struct variable codegen"<<endl;
        std::string name=*ID_Name;
        std::string mem=*member;
        std::string struct_ID = generator.VarStructID[name];
        _Struct* stru = generator.StructMap[struct_ID];
        llvm::Type* structType = generator.TypeMap[struct_ID];
        int index = stru->getIndex(mem);

        auto alloc = generator.getValue(name);
        auto structaddr = TheBuilder.CreateConstGEP2_32(structType,alloc,0,index);
        value = TheBuilder.CreateLoad(structaddr);
    }
    else if(this->v_Type == MemARRAY){
        std::string name=*ID_Name;
        std::string mem=*member;
        std::string struct_ID = generator.VarStructID[name];
        _Struct* stru = generator.StructMap[struct_ID];
        llvm::Type* structType = generator.TypeMap[struct_ID];
        int index1 = stru->getIndex(mem);

        auto alloc = generator.getValue(name);
        auto structaddr = TheBuilder.CreateConstGEP2_32(structType,alloc,0,index1);

        llvm::Value *index = this->exprMem->codeGen(generator);
        llvm::Constant* con_0 = llvm::ConstantInt::get(llvm::Type::getInt32Ty(TheContext), 0);
        llvm::Value *Idxs[]={con_0,index};

        auto arrayaddr = TheBuilder.CreateGEP(structaddr,Idxs);
        value = TheBuilder.CreateLoad(arrayaddr);
    }
    else if(this->v_Type == StructARRAY){
        llvm::Value *index = this->exprID->codeGen(generator);
        llvm::Constant* con_0 = llvm::ConstantInt::get(llvm::Type::getInt32Ty(TheContext), 0);
        llvm::Value *Idxs[]={con_0,index};
        auto array= generator.getValue(*this->ID_Name);
        llvm::Value *array_i = TheBuilder.CreateGEP(array,Idxs);

        std::string name=*ID_Name;
        std::string mem=*member;
        std::string struct_ID = generator.VarStructID[name];
        _Struct* stru = generator.StructMap[struct_ID];
        llvm::Type* structType = generator.TypeMap[struct_ID];
        int index1 = stru->getIndex(mem);

        auto structaddr = TheBuilder.CreateConstGEP2_32(structType,array_i,0,index1);
        value = TheBuilder.CreateLoad(structaddr);
    }
    else if(this->v_Type == StructMemARRAY){
        llvm::Value *index = this->exprID->codeGen(generator);
        llvm::Constant* con_0 = llvm::ConstantInt::get(llvm::Type::getInt32Ty(TheContext), 0);
        llvm::Value *Idxs[]={con_0,index};
        auto array= generator.getValue(*this->ID_Name);
        llvm::Value *array_i = TheBuilder.CreateGEP(array,Idxs);

        std::string name=*ID_Name;
        std::string mem=*member;
        std::string struct_ID = generator.VarStructID[name];
        _Struct* stru = generator.StructMap[struct_ID];
        llvm::Type* structType = generator.TypeMap[struct_ID];
        int index1 = stru->getIndex(mem);

        auto structaddr = TheBuilder.CreateConstGEP2_32(structType,array_i,0,index1);

        llvm::Value *index2 = this->exprMem->codeGen(generator);
        llvm::Value *Idxs2[]={con_0,index2};

        auto arrayaddr = TheBuilder.CreateGEP(structaddr,Idxs2);
        value = TheBuilder.CreateLoad(arrayaddr);
    }
    return value;
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
    else if (*Type == "boolean"){
        retType=C_BOOLEAN;
    }
    else if (*Type == "void"){
        retType=C_VOID;
    }

    vector<llvm::Type *> argsType;
    for (auto & arg : *this->args){
        if (arg->args->v_Type == _Variable::ArrayPtr){
            switch(arg->arg_Type){
                case C_INTEGER:
                    cout << "int array point" << endl;
                    argsType.push_back(llvm::Type::getInt32PtrTy(TheContext));
                    break;
                case C_CHAR:
                    argsType.push_back(llvm::Type::getInt8PtrTy(TheContext));
                    break;
            }
        }
        else{
            argsType.push_back(llvmType(arg->arg_Type));
        }
        // argsType.push_back(llvmType(arg->arg_Type));
    }
    llvm::FunctionType *funcType = llvm::FunctionType::get(llvmType(retType), argsType, false);
    llvm::Function *function = llvm::Function::Create(funcType, llvm::GlobalValue::InternalLinkage, *this->Func_Id, generator.TheModule.get());
    generator.pushFunc(function);

    // create a basic block
    llvm::BasicBlock *basicBlock = llvm::BasicBlock::Create(TheContext, "entry", function);
    TheBuilder.SetInsertPoint(basicBlock);

    // create a function argument iterator
    llvm::Function::arg_iterator argIter = function->arg_begin();
    vector<llvm::Type*>::iterator argsTypeIter = argsType.begin();
    for (auto & arg : *this->args){
        cout << "argType: " << (*argsTypeIter)->getTypeID() << endl;
        llvm::AllocaInst *alloc = createDefAlloca(function, *arg->args->ID_Name, *argsTypeIter++);
        TheBuilder.CreateStore(argIter++, alloc);
    }
    // // return
    // llvm::Value *res = nullptr;
    // res = createTempAlloca(function, "res", llvmType(retType));
    
    //Sub routine
    for (auto & stmt : *this->statements){
        stmt->codeGen(generator);
    }
    
    if (retType == C_VOID){
        TheBuilder.CreateRetVoid();
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
            if (setD){
                string c = std::to_string(digit);
                format += "%" + c + "d";
            }
            else{
                format += "%d";
            }
        }
        else if(varType == TheBuilder.getDoubleTy()){
            format += "%.1f";
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
llvm::Value* _Struct::codeGen(CodeGenerator & generator){
    llvm::Value* value;
    return value;
}

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
    if(this->myStructs!=NULL){
        for(auto mystruct: *this->myStructs){
            structs.push_back(mystruct->JsonGen());
        }
        children.push_back(getJsonString("structList",structs));
    }
    
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
    std::vector<string>vars;
    for(auto sta: *this->data){
        vars.push_back(sta->JsonGen());
    }
    
    children.push_back(getJsonString("DataList",vars));
    return getJsonString("Definition",type,children);
}

string _Struct::JsonGen(){
    std::vector<string>children;
    std::vector<string>datas;
    for(auto var: *this->defins){
        datas.push_back(var->JsonGen());
    }
    children.push_back(getJsonString("Definitions",datas));

    return getJsonString("Struct",children);
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
    else if(OP==C_EQ){
        res="EQUAL";
    }
    else if(OP==C_NE){
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
    for(auto arg: *this->args){
        argsJson.push_back(arg->JsonGen());
    }
    cout<<"functioncall end json"<<endl;
    children.push_back(getJsonString("ArgsList",argsJson));
    return getJsonString("functionCall",*this->func_Name,children);
}

string _forStatement::JsonGen(){
    std::vector<string>children;
    children.push_back(this->startExpr->JsonGen());
    children.push_back(this->condExpr->JsonGen());
    children.push_back(this->stepExpr->JsonGen());
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
    children.push_back(this->condition->JsonGen());
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
        return getJsonString("else","noElse");
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
    cout<<"Varible"<<endl;
    cout<<this->v_Type<<endl;
    if(this->v_Type==CONST){
        return getJsonString("Variable",*this->ID_Name);
    }
    else if(this->v_Type==ARRAY){
        std::vector<string> children;
        children.push_back(this->exprID->JsonGen());
        return getJsonString("Array",*this->ID_Name,children);
    }
    else if(this->v_Type==ArrayPtr){
        return getJsonString("ArrayPtr",*this->ID_Name);
    }
    else if(this->v_Type==Struct){
        std::vector<string> children;
        children.push_back(getJsonString("memberName",*this->member));
        return getJsonString("Struct",*this->ID_Name,children);
    }
    else if(this->v_Type==MemARRAY){
        std::vector<string> children;
        children.push_back(getJsonString("memberName",*this->member));
        children.push_back(this->exprMem->JsonGen());
        return getJsonString("memArray",*this->ID_Name,children);
    }
    else if(this->v_Type==StructMemARRAY){
        std::vector<string> children;
        children.push_back(this->exprID->JsonGen());
        children.push_back(getJsonString("memberName",*this->member));
        children.push_back(this->exprMem->JsonGen());
        return getJsonString("structMemArray",*this->ID_Name,children);
    }
    else if(this->v_Type==StructARRAY){
        std::vector<string> children;
        children.push_back(this->exprID->JsonGen());
        children.push_back(getJsonString("memberName",*this->member));
        return getJsonString("structARRAY",*this->ID_Name,children);
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
        
        return getJsonString("Char","char");
    }
    else if(this->var_type==C_STRING){
        string s=this->s_val;
        cout<<"ssval"<<s<<endl;
        return getJsonString("STRING",s);
    }
}