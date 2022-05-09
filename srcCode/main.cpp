#include <fstream>
#include "ast_json.h"
#include "parser.hpp"
extern int yyparse();
extern _Program *root;

int main(int argc, char **argv) {
    yyparse();
    std::cout<<"Finish Parse"<<endl;
    std::ofstream os("tree.json");
    os << root->JsonGen() << std::endl; //...怎么读入AST的？
   
   

    return 0;
}
