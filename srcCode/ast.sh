flex compiler.l
bison -d compiler.y
g++ lex.yy.c compiler.tab.c -lm -o test