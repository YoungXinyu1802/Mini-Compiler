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

#### AST 结构简单描述

```
Program
|
Function FunctionList
        |					                              |
     mainFunction                                     Subroutine
   |			 |										  |
statementlist  argsDefinitionList			     Type Func_ID  statementlist

_______________________________________________________________________________________
					statement statementlist
				 |				|			|
             definition     expression   returnExpression
            	|							|
            type name					singleExpressionList
_____________________________________________________________________________________

            				expression
            			|				|				|(这个部分可能还有问题)
                assignExpression   complexExpression  functionCall        
 
 ____________________________________________________________________________________
							singleExpression singleExpressionList
							 |				|
							term OP 		term
									   |		|			|
                                    value  variable  (singleExpressionList)
                                     |			|				
                  int|double|bool|string     indentifier     
                                    
   _________________________________________________________________________________ 
    			assignExpression
    				|
               variable singleExpressionList         
               
 _________________________________________________________________________________
 				complexExpression
 			|		  |					|
    forStatement   whileStatement    ifStatement
 
 ____________________________________________________________________________________
 					forStatement
 						|
  assingmentExpression  SingleExpressionList assignExpresion statementList
  
  _________________________________________________________________________________
  					whileStatement
  						|
   singleExpressionList   statementList
   
   _______________________________________________________________________________
   					ifStatement
   						|
   	singleExpression  statementList elsePart
   								      |		  |          \
   									空	  statementList  ifStatement
  __________________________________________________________________________________
   									
```

​		



### 三、语义分析

llvm 语法完成语法树内容的语义分析

### 四、生成目标代码

