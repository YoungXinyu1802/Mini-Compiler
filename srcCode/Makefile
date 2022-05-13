LLVM_CONFIG = /usr/bin/llvm-config

NO_WARNING =  -Wno-return-type \
	-Wno-c++11-compat-deprecated-writable-strings \
	-Wno-deprecated-register \
	-Wno-switch \

CXXFLAGS = `$(LLVM_CONFIG) --cppflags` -std=c++14 $(NO_WARNING) -fpermissive 
LDFLAGS = `$(LLVM_CONFIG) --ldflags`
LIBS = `$(LLVM_CONFIG) --libs --system-libs`

NAME = compiler
OBJS = parser.o tokenizer.o ast.o  main.o codeGen.o

all : $(NAME)

$(NAME): $(OBJS)
	g++ -o $@ $(OBJS) $(LIBS) $(LDFLAGS)

%.o: %.cpp ast.hh codeGen.h 
	g++ -c $(CXXFLAGS) -o $@ $< 

parser.cpp: ${NAME}.y
	bison -d -o parser.cpp ${NAME}.y

parser.hpp: parser.cpp

tokenizer.cpp: ${NAME}.l
	flex -o tokenizer.cpp ${NAME}.l


.PHONY: clean
clean:
	-rm -f *.o
	-rm -f parser.hpp parser.cpp tokenizer.cpp spl
	-rm -f tree.json
	-rm -f *.s
	-rm -f *.ll
	-rm -f test/*.txt test/*.ll

run :
	./test.sh