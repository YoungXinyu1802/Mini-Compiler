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

- Program

  ```
  Program:
  	-functionList
  ```

- functionList

  ```
  functionList:
  	-function functionList
  ```

- Function:

  ```
  Function:
  	-mainFunc
  	-subroutine
  ```

- mainFunc

  ```
  mainFunc:
  	-ReturnType Main(key-word) '(' ArgsList ')' '{' StatementList '}'
  ```

- StatementList

  ```
  StatementList:
  	-Statement StatementList
  ```

- Statement:

  ```
  Statement:
  	-Definition
  	-Expression
  	-return(keyword) singleExpression ';'
  ```

- Definition:

  ```
  Definition:
  	-DataType VarList ';'
  ```

- VarList:

  ```
  VarList:
  	- Variable ',' VarList
  	- Variable
  ```

- Variable:

  ```
  Variable:
  	- Identifier
  	- Identifier '[ Expression ]'
  ```

- Expression:

  ```
  Expression:
  	-AssignExpression ';'
  	-complexExpression
  	-functionCall ';'
  ```

- AssignExpression:

  ```
  AssignExpression:	
  	-Variable '=' singleExpression
  ```
  
- singleExpression:

  ```
  singleExpression:
  	-Variable OP singleExpression
  	-functionCall
  	-Variable
  	-val
  ```

- functionCall:

  ```
  funtcionCall:
  	-Identifier '(' Argslist ')'
  ```

- complexStatement:

  ```
  complexStatement:
  	-for-stmt
  	-while-stmt
  	-if-stmt
  ```

- for-stmt:

  ```
  for-stmt:
  	-for(key-word)'(' AssignExpression ';' singleExpression ';' AssignExpression ')'
  		'{'   
  		statementList
  		'}'
  ```

- while-stmt:

  ```
  while-stmt:
  	-while(key-word) '(' singleExpression ')'
  		'{'
  			statementList
  		'}'
  ```

- if-stmt:

  ```
  if-stmt:
  	-if(key-word)'(' singleExp ')'
  		'{'
  			statementList
  		'}'
  		elsePart
  ```

- elsePart:

  ```
  elsePart:
  	- ε
  	- else '{'
  		statementList
  		'}'
      - else if-stmt
  ```

- subroutine:

  ```
  subroutine:
  	- returnType Identifier '(' ArgsDefinitionList')'
  		'{'
  			statementList
  		'}'
  ```

- ArgsList:

  ```
  ArgsList:
  	- Variable ',' ArgsList
  	- Variable
  	- epsilon
  ```

- ArgsDefinitionList:

  ```
  ArgsDefinitionList:
  	- DataType Variable ',' ArgsDefinitionList
  	- DataType Variable
  	- eplsilon
  ```
  



### About AST 

- Node 类设计

  ```
  class Node
  {
  public:
      virtual ~Node(){} 
      virtual void setNodeType(NodeType type){
          this->type=type;
      }
      // 用于llvm生成中间代码
      virtual llvm::Value *codeGen(CodeGenerator & generator) = 0;
      // 用于生成AST可视化需要的Json数据
      virtual string getJson(){return "";};
      //打印测试接口
      virtual void printNode(){};
  private:
      int type;
  };
  
  ```

- 子类设计

  基类

  ```
  class Function{
  
  }
  
  class Statement{
  
  }
  
  class Data{
  
  }
  
  class Args{
  
  } 
  
  class ArgsDefinition{
  
  }
  ```

  

- 变量注册 查找 生命周期



- 





### 三、语义分析

llvm 语法完成语法树内容的语义分析

### 四、生成目标代码

