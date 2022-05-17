#include "codeGen.h"
#include "ast.hh"

using namespace std;

CodeGenerator::CodeGenerator(){
    TheModule = std::unique_ptr<llvm::Module>(new llvm::Module("main", TheContext));
}

llvm::Value* CodeGenerator::getValue(const std::string & name){
    llvm::Value * result = nullptr;
    try{
        for (llvm::Function * it : funcStack){
            llvm::ValueSymbolTable * symTab = it->getValueSymbolTable();

            if ((result = it->getValueSymbolTable()->lookup(name)) != nullptr){
                std::cout << "Find " << name << std::endl;
                // result = TheBuilder.CreateLoad(result);
                return result;
            }
            else{
                throw name;
            }
        }        
    }
    catch(const std::string msg){
        std::cout << "error: '" << msg << "' is not declared. " << std::endl;
    }
    assert(result != nullptr);
}

llvm::Function* CodeGenerator::getCurFunc(){
    llvm::Function * func = funcStack.back();
    std::cout << "get function: " << func->getName().str() << std::endl;
    return funcStack.back();
}

void CodeGenerator::pushFunc(llvm::Function* func){
    funcStack.push_back(func);
}

void CodeGenerator::popFunc(){
    funcStack.pop_back();
}

void CodeGenerator::generate(_Program& root){
    cout << "[Begin IR]" << endl;
    root.codeGen(*this);
    cout << "[Finish IR]" << endl;

    TheModule->print(llvm::outs(), nullptr);
}