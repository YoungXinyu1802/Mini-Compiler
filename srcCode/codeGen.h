#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/ValueSymbolTable.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/DynamicLibrary.h>
#include <llvm/Target/TargetMachine.h>
//#include <llvm/Support/Debug.h>
#include "ast.hh"

static llvm::LLVMContext TheContext;
static llvm::IRBuilder<> TheBuilder(TheContext);
class CodeGenerator 
{
public:
    llvm::Function *mainFunction;
    std::vector<llvm::Function*> funcStack;
    std::unique_ptr<llvm::Module> TheModule;

    CodeGenerator();
    llvm::GenericValue run();
    llvm::ExecutionEngine* genExeEngine();
    llvm::Value* getValue(const std::string & name);
    llvm::Function* getCurFunc();
    void pushFunc(llvm::Function* func);
    void popFunc();
    void generate(_Program& Root);
};

#endif
