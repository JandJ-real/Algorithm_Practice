#pragma once
#include"../definition.h"
class Literal
{
    public:
        int var;
        Literal();
        Literal(int var);//带值构造函数

        ~Literal();//析构
        bool isNegative();//是否是负文字
        int getAbs();//返回绝对值
        void print();//打印文字
        bool operator!=(const Literal& l)const;//不等号重载
        bool operator==(const Literal& l)const;//等号重载

};
