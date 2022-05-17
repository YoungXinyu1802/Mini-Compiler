#ifndef OBJGEN_H
#define OBJGEN_H

#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/TargetRegistry.h>
//llvm/Support/TargetRegistry.h
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/ADT/Optional.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/IR/LegacyPassManager.h>
//#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Host.h"

int ObjGen(CodeGenerator& generator);

#endif 
