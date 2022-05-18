## 5.18 2:40 此次前端修改部分：

### array传参引用
- Lex是可以直接替换的
- 不知道Yacc直接替换有没有问题，如果有问题的话
- yacc 将Variable部分的parse替换为：
```
Variable:
IDENTIFIER{
    $$=new _Variable($1);
}
|IDENTIFIER LB singleExpression RB{
    $$=new _Variable($1,$3);
}
|IDENTIFIER LB RB{
    string a="nullTest";
    $$=new _Variable($1,a);
}
```
- ast.h在Variable类enum类型增加一个成员和一个构造函数：实现使用v_Type==ArrayPtr的指针判断
```
enum u_Type{
        CONST,
        ARRAY,
        ArrayPtr
    }v_Type;

_Variable(std::string* name,std::string arrayNULL){
        this->ID_Name=name;
        this->expr=NULL;
        this->v_Type=ArrayPtr;
        cout<<"Arrayptr\n";
    }

```
## inputList  outputList
- 只在yacc有修改，所以不牵涉到后面
- 支持 cin>>a>>b>>c;这样的语法
- 支持 cout<<a<<b<<c<<endl;这样的语法





接下来俺进行前端测试点代码的编写和测试。