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
    std::cout << "getCurFunc" << std::endl;
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

llvm::ExecutionEngine* CodeGenerator::genExeEngine(){
    std::string err;
    auto RTDyldMM = unique_ptr<llvm::SectionMemoryManager>(new llvm::SectionMemoryManager());
    llvm::ExecutionEngine* engine = llvm::EngineBuilder(std::move(TheModule))
        .setEngineKind(llvm::EngineKind::JIT)
        .setErrorStr(&err)
        .setVerifyModules(true)
        .setMCJITMemoryManager(move(RTDyldMM))
        .setOptLevel(llvm::CodeGenOpt::Default)
        .create();
    if (!engine){
        throw std::logic_error("Create Engine Error: " + err);
    }
    engine->addModule(std::move(TheModule));
    engine->finalizeObject();
    return engine;
}