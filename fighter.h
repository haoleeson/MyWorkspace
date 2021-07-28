//OOT第2次作业-EisenHao
#ifndef FIGHTER_H_
#define FIGHTER_H_

#include "stdio.h"
#include "string.h"

//定义fighter类
class fighter
{
protected:
    char* fighterName = NULL; //用于存储构造函数时，new 的拳手名字字符串的首地址，方便析构时删除申请的char空间
public:
    fighter(char* name);//构造函数
    ~fighter();//析构函数，删除申请的拳手名字字符串char空间
    void outTitle();//显示："We are fighters."
    virtual void hello();//显示："（拳手名） is a fighter"
    char* getFighterName();//返回拳手名字字符串的首地址
};
//构造函数
fighter::fighter(char *name)
{
    int length = strlen(name);//求字符串长度
    this->fighterName = new char[length]();//申请等长度char空间
    //拷贝字符串
    for (int i=0; i<length; i++)
    {
        *(this->fighterName + i) = * (name + i);
    }
}
//析构函数，删除申请的拳手名字字符串char空间
fighter::~fighter()
{
    printf("%s is gone.\n", this->fighterName);
    if(fighterName != NULL) //若申请空间非空
    {
        delete []fighterName;//删除申请的char空间
        fighterName = NULL;//指针赋NULL
    }
}
//显示标题："We are fighters."
void fighter::outTitle()
{
    printf("We are fighters.\n");
}
//显示："（拳手名） is a fighter"
void fighter::hello()
{
    printf("%s is a fighter\n", this->fighterName);
}
//返回拳手名字字符串的首地址
char* fighter::getFighterName()
{
    return fighterName;
}


//定义Warrior类
class Warrior : public fighter
{
private:
    char* fatherNamePtr = NULL;//记住父类实例名字首地址
public:
    Warrior(char* name, fighter* ft);//构造函数
    ~Warrior();//析构函数，删除申请的拳手名字字符串char空间
    void hello();//重置：显示："（拳手名） is a stronger warrior than (一个父类实例名)."
};
//构造函数
Warrior::Warrior(char* name, fighter* ft):fighter(name)
{
    fatherNamePtr = ft->getFighterName();//记住父类实例名字首地址
}
//析构函数，删除申请的拳手名字字符串char空间
Warrior::~Warrior()
{
    if(fatherNamePtr == NULL) //若“父类实例”申请空间为空，父类的实例被清空
    {
        delete []fighterName;//删除"子类实例"申请的char空间
        fighterName = NULL;//指针赋NULL
    }
}
//重置：显示："（拳手名） is a stronger warrior than (一个父类实例名)."
void Warrior::hello()
{
    printf("%s is a stronger warrior than %s\n", this->fighterName, fatherNamePtr);
}
#endif

