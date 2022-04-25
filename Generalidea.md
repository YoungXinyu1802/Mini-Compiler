## 总体框架

### Above all: 环境配置

暂略

### 一、词法分析

- 实现token:

  - 首先考虑去换行符等影响因素
  - C语言关键词
  - ![image-20220425091940887](C:\Users\86198\AppData\Roaming\Typora\typora-user-images\image-20220425091940887.png)
  - 输入输出 printf,scanf
  - C语言运算符
  - ![image-20220425092018221](C:\Users\86198\AppData\Roaming\Typora\typora-user-images\image-20220425092018221.png)

  

  - 自定义identifier
  - 数值（10进制，二进制，8进制，16进制），整型 vs 浮点数

- 需要进一步考虑的问题：

  在生成token时，以何种形式来保存值？·如果使用string形式，在何时将其转换成对应的值

  变量的值首先以String 的形式识别

  统一保存后在语法分析中处理

### 二、语法分析

主要工具： Bison/yacc

目的:  token —> AST

首先需要实现变量存储的类型定义 `%union`

要实现的语法：

要实现的语法：

- 变量声明（数组等特殊类型的声明和存储？）

  ```cpp
  dataType Identifier1,..Identifier2;
  //数组？
  dataType Identifier [num];
  ```

- 变量赋值

  ```cpp
  Identifier=Expression (Expression 是个很大的父类-->表达式|数值|其他Identifier)
  //数组初始化？
  ```

- 函数声明 （需要考虑局部变量和全局变量如何存储） (参数列表，返回值)

  ```cpp
  ReturnType Identifier ( Args...  ){
  			statement.....
       //变量声明 (局部变量...栈帧的处理？)
  		 //变量赋值
  		 //表达式计算
  		 //复合语句
  		 //函数调用
  			....
  }
  ```

- 循环语句（while, for）

  ```cpp
  while (condition [expression])
  {
     statement....;
  }
  
  for(expression1;expression2;expression3)
  {
  	statement.....;
  }
  ```

- 条件语句（if-else）

  ```cpp
  if(statement[细分一下？？？])
  {
  	statement1...;
  }
  else if(){
  	statement2...;
  }
  ....
  else{
  	statement3...;
  }
  ```

- struct 结构？

  ```cpp
  这部分可以先不考虑
  ```

- 函数调用（这属于语法分析还是语义分析？）



​	解析过程中打印语法树

### 三、语义分析

llvm 语法完成语法树内容的语义分析

### 四、生成目标代码

