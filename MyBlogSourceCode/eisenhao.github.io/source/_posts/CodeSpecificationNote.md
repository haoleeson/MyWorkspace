layout: post
title: 代码规范笔记
date: 2021/7/14 22:30:45
updated: 2021/7/14 22:10:45
comments: true
tags: 
- Code
categories:
- 技术

---

# 1. 排版与格式

## 1.1. include
include guards 或#pragma once
include guards 必须使用<CODEPATH>_<FILE>_H（或 HPP）的全大写形式。CODEPATH 中需要去掉标示主干/分支的关键词如：trunk, branch-xxx 

<!-- more -->

## 1.2. 头文件顺序

强制头 (.h) 文件按以下顺序组织：
- 文件声明
- include guards
- 引用的头文件
- 自定义类型声明，函数声明（一般函数，模板函数）, 内联函数/模板函数

## 1.3. 源文件顺序
强制 CPP 文件按以下顺序组织：
- 文件声明
- 引用的头文件
- 代码部分（注意：涉及的函数和类方法按照头文件的顺序组织）

## 1.4. 代码格式要求
代码行组织要求：
- 强制使用适当的空行来分组代码的逻辑
- 强制左大括号不独立，右大括号独立成行。并且左大括号所在行进行垂直对齐
- 以 4 个空格为单位缩进，不使用制表符
- 命名空间不缩进
- public/protected/private 关键字与类声明对齐
- 比较短的函数声明，整个声明占一行；过长的函数声明，令每一参数占一行，并且垂直对齐，换行后的参数至少保持 8 个空格缩进
- 比较短的函数调用语句，整个语句占一行；过长的函数调用，控制折行确保每行不要超过 100 列，换行后至少额外缩进 8 个空格
```cpp
grey_wolf.eat(white_sheep);
hungry_lion.eat(
        big_grey_wolf,
        little_white_sheep,
        quick_brown_fox,
        lazy_dog);
```

- if 语句的分支部分必须使用大括号包围
- 如果条件表达式很长很复杂，在低优先级运算符前换行，换行后运算符 (|| or &&) 放在新行最前面，并额外缩进 8 个空格
- 强制连续的 if...elseif... 判断，原则上应该以 else 语句结束。若该条件合法但没有相应动作，通过注释标明//pass 或//do nothing; 若是不合法情况，应报错
```cpp
if (you.com_from(EARTH)
        || you.com_from(MARS)
        ||you.com_from(VENUS)) {
    return"youcomefromsolar system";
} // else do nothing
return std::string();
```

- 强制每一个 case 语句都必须以 break 语句或 return 语句结束
- 强制语句原则上应该有一个 default 语句，如果没有动作，通过注释标明//pass 或//do nothing
- 强制 case 语句需要与 switch 对齐，不要增加额外缩进

# 2. 命名及注释
## 2.1. 命名
- 文件名全部用小写字母，中间用_间隔；比如：this_is_my_awesome_file.cpp
- 单元测试文件名使用<被测文件名>_test.h(.cpp) 命名
- 函数命名使用下划线分隔的全小写命名法
- 类类型使用首字母大写的驼峰命名法命名
- 使用下划线分隔的全小写命名法命名命名空间
- 一行内只应声明一个变量
- 局部变量应在声明处赋初值，指针类型局部变量必须在声明处赋初值

## 2.2. 注释
- 强制 每个文件都必须有文件声明放在文件头部，按如下内容组织：1) 版权声明；2) 许可证（可选）3) 作者 4) 代码功能/用法说明
- 强制 文档化注释必须标明作者和简要介绍，公有函数必须解释其输入参数、输入参数合法取值、输出参数、返回值、抛出的异常

# 3. 代码规范

- 强制 class 表示被封装的用户自定义类型，不公开定义非静态数据成员，一般通过成员方法进行交互
- 建议 struct 表示数据的简单集合，公开定义数据成员，只定义用于初始化数据成员的方法
- 强制 必须使用构造函数初始化列表显式初始化直接基类与所有的基本类型数据成员
- **强制 没有复制意义的类必须用 DISALLOW_COPY_AND_ASSIGN 宏禁止拷贝构造函数和赋值构造函数。**
```cpp
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
        TypeName(constTypeName&); \
        TypeName& operator=(constTypeName&)
class Foo {
public:
    explicit Foo(int f) : _f(f) {}
    ~Foo();
private:
    DISALLOW_COPY_AND_ASSIGN(Foo);
};
```

- 强制 有默认值语意的类，必须显式定义默认构造函数
- 强制 没有默认值语意的类，必须显式定义其它构造函数或 private 声明默认构造函数，并不给出实现
- 强制 若类定义了虚函数，必须定义虚析构函数

## 3.1. 命名空间
- **所有代码都应该定义在 namespace 中，main() 函数除外。**
- **头文件中禁止在函数、方法和类作用域外的地方使用 using namespace 或者 using class**，但是类别名（type alias）和别名模板（alias template）的使用不受限制

## 3.2. 类型转换
- 强制 必须使用 C++ 风格类型转换。如 static_cast、dynamic_cast、const_cast、reinterpret_cast
```cpp
double d = static_cast<double>(i);
const MyBuf * buf = reinterpret_cast<const MyBuf*>(network_buf);
const Derived * d = dynamic_cast<const Derived*>(b);
old_copy(dest, const_cast<void *>(src), n);
```

## 3.3. smart_ptr
- **强制 禁止使用 auto_ptr**
- 应使用：
```cpp
std::unique_ptr<Foo> ptr(newFoo());
std::scoped_ptr<Shape> p;
std::shared_ptr<Shape> p = createShape();
```

- 建议不要使用 strcpy()/strcat()/strdup()/sprintf() 等没有越界检查的函数
- 建议不要使用 strncpy/strncat 实现有问题的函数
- 强制 禁止定义 struct 的同时 typedef 一个类型名，除非该头文件必须兼容 gcc，应使用：
```cpp
struct MyStruct {
    ...
};
```

## 3.4. 返回值
- 强制 如果使用 int 作为返回值，必须遵循“负值表示失败，非负值表示成功”

## 3.5. 除下述类型的函数都需要单测
- 接口型函数
- 流程型函数
- 框架型函数

# 道
## 一流代码特性
- 高效、鲁棒、简洁、简短、共享、可测试、可移植
- 可监控、可运维、可扩展

## 写好代码注重什么？
- 正确和性能、可读和可维护、共享和重用、运维和运营

# 推荐书籍
- 《编写可读代码的艺术》
- 《code complete》
- 《设计模式》
- 《重构-改善既有代码的设计》
