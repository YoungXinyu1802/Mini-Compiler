#include "codeGen.h"
#include "ast.hh"

using namespace std;

llvm::Value* CodeGenerator::getValue(const std::string & name){
    llvm::Value * result = nullptr;
    for (auto it : funcStack){
        if ((result = it->getValueSymbolTable()->lookup(name)) != nullptr){
            std::cout << "Find " << std::endl;
            return result;
        }
        else{
            std::cout << "Not Find " << std::endl;
        }
    }
}

llvm::Function* CodeGenerator::getCurFunc(){
    return funcStack.back();
}

void CodeGenerator::pushFunc(llvm::Function* func){
    funcStack.push_back(func);
}

void CodeGenerator::popFunc(){
    funcStack.pop_back();
}
