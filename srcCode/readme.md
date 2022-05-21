## 5.21 16:00 此次修改部分

### Variable类进行大修
- 增加两个构造函数
- 对enumType及名称做了修改
- 主要集中在后三个构造函数上
- MemARRAY: a.b[x]类型，指成员变量为数组
- StructMemARRAY: a[x].b[y]类型，结构体变量与成员变量均为数组
- StructMemARRAY: a[x].b类型，仅结构体变量为数组
- 此外为了更好地区分Variable类内成员，对类内变量的名称做了修改，后端也要更改一下
- exprID：常量数组/结构体数组变量下标表达式
- 增加exprMem:成员变量数组下标表达式
