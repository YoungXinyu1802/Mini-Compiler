#include <fstream>
#include "ast_json.h"
#include "parser.hpp"

// #include "ObjGen.h"
extern int yyparse();
extern _Program *root;

int main(int argc, char **argv) {
    yyparse();
    std::cout<<"Finish Parse"<<endl;
    std::ofstream os("tree.json");
    os << root->JsonGen() << std::endl; //...怎么读入AST的？
    // llvm::InitializeNativeTarget();
    // llvm::InitializeNativeTargetAsmPrinter();
    // llvm::InitializeNativeTargetAsmParser(); 
 
    // CodeGenerator generator;
    // generator.generate(*root);
    // ObjGen(generator);
    return 0;
}
