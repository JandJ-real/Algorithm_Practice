#pragma once
#include"Literal.hpp"
#include"../containers/MyVector.hpp"

class Clause
{
    public:
        //文字集合
        MyVector<Literal> literals;

        //构造函数
        Clause();
        //析构函数
        ~Clause();

        //添加文字
        void addLiteral(Literal l);
        //删除所有指定文字
        void removeLiteral(const Literal& l);

        //打印子句
        void print();

        //判断是否为单子句 
        bool isSingleUnit() const;
};
