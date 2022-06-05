# Mini-Compiler 
## 概述

  本次实验我们小组基于C语言设计并实现了一个类C语言的编译器，该系统以符合C语言基本语法规则的代码文本作为输入，输出为指定机器的目标代码，该C编译器的设计实现涵盖词法分析、语法分析、语义分析、代码生成等阶段和环节，所使用的的具体技术包括但不限于：

  - Flex实现词法分析
  - Bison实现语法分析
  - LLVM实现中间代码生成、目标代码生成
  - json实现AST可视化

  该编译器，目前可以支持

  - 数据类型
    - 内置类型int,char,bool,float
    - 数组类型
    - 结构体类型
    - 数组指针
  - 表达式
    - 一元操作：Minus
    - 二元操作: MUL DIV NOT ADD SUB NE,AND OR GE GT LE LT EQ
    - 变量引用
    - 数组引用
  - 语句
    - 赋值语句
    - 复合语句
    - 嵌套语句
    - 分支语句
    - 循环语句
  - 函数
    - 函数的声明、调用
    - 系统IO函数：cin、cout
    - 值传递和引用传递
  - 可视化
    - AST可视化

## 开发环境

- 操作系统：Linux
- 编译环境
  - Flex 2.5.35
  - Bison 2.3
  - LLVM 6.0.0

## 文件说明

本次提交的文件及其说明如下、

- srcCode: 源代码文件夹
  - compiler.l ：Flex源代码，主要实现词法分析，生成Token
  - compiler.y: Yacc源代码，主要实现语法分析，生成抽象语法树
  - tokenizer.cpp：Flex根据compiler.l生成的词法分析器
  - parser.cpp：Yacc根据compiler.y生成的语法分析器C++文件
  - parser.hpp：Yacc根据compiler.y生成的语法分析器头文件
  - ast.hh：AST函数类声明头文件
  - ast.cpp
  - ObjGen.cpp
  - ObjGen.h
- doc: 报告文档文件夹
  - report.pdf
- test: 测试代码及工具文件夹
  - test1.cmm
  - test2.cmm
  - test3.cmm


## 测试说明

测试时，首先`make`编译出`./compiler`文件，然后将编写的代码作为文件输入生成中间代码。然后用`objtest.cpp`文件链接生成可执行文件

```bash
make
./compiler < ./test.cmm
./run.sh
```

run.sh文件：

```bash
clang++ objtest.cpp output.o -o objtest
./objtest
```
运行生成的`objtest`可执行文件，输入测试，输出结果