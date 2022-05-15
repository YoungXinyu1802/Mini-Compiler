#include "codeGen.h"
#include "ast.hh"

using namespace std;

CodeGenerator::CodeGenerator(){
    TheModule = std::unique_ptr<llvm::Module>(new llvm::Module("main", TheContext));
}

llvm::Value* CodeGenerator::getValue(const std::string & name){
    llvm::Value * result = nullptr;
    for (llvm::Function * it : funcStack){
        llvm::ValueSymbolTable * symTab = it->getValueSymbolTable();
        std::cout << symTab->size() << endl;

        if ((result = it->getValueSymbolTable()->lookup(name)) != nullptr){
            std::cout << "Find " << std::endl;
            return result;
        }
        else{
            std::cout << "Not Find " << std::endl;
        }
    }
    return nullptr;
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