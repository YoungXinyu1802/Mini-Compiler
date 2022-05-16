#include "codeGen.h"
#include "ObjGen.h"

using namespace llvm;

int ObjGen(CodeGenerator& generator)
{
    //LLVM提供sys::getDefaultTargetTriple，返回当前计算机的目标三元组。
    auto TargetTriple = sys::getDefaultTargetTriple();
    
    //初始化发出目标代码的所有目标
    InitializeAllTargetInfos();
    InitializeAllTargets();
    InitializeAllTargetMCs();
    InitializeAllAsmParsers();
    InitializeAllAsmPrinters();

    std::string Error;
    auto Target = TargetRegistry::lookupTarget(TargetTriple, Error);
    // Print an error and exit if we couldn't find the requested target.
    // This generally occurs if we've forgotten to initialise the
    // TargetRegistry or we have a bogus target triple.
    if (!Target) {
        errs() << Error;
        return 1;//返回1表示异常退出
    }

    //使用通用CPU
    auto CPU = "generic";
    auto Features = "";
    TargetOptions opt;
    auto RM = Optional<Reloc::Model>();
    auto TargetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);

    //配置我们的模块，以指定目标和数据布局
    generator.TheModule->setDataLayout(TargetMachine->createDataLayout());
    generator.TheModule->setTargetTriple(TargetTriple);

    //定义我们要将文件写入的位置：
    auto Filename = "output.o";
    std::error_code EC;
    raw_fd_ostream dest(Filename, EC, sys::fs::F_None);
    if (EC) {
        errs() << "Could not open file: " << EC.message();
        return 1;
    }

    //定义了一个发出目标代码的传递，然后我们运行该传递
    legacy::PassManager pass;
    auto FileType = TargetMachine::CGFT_ObjectFile;
    if (TargetMachine->addPassesToEmitFile(pass, dest, FileType)) {
        errs() << "TargetMachine can't emit a file of this type";
        return 1;
    }
    pass.run(*(generator.TheModule));
    dest.flush();
	
	outs() << "Wrote " << Filename << "\n";
    return 0;
}

