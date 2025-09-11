#pragma once
#include"Clause.hpp"
class CNF
{
    public:
        MyVector<Clause> Clauses;

        //构造函数
        CNF();
        ~CNF();
        //添加子句
        void addClause(Clause c);
        //移除所有包含单子句L的句子
        void removeClause( const Clause& c);
        //移除剩下所有子句中的~L
        void removeLinClause(const Literal& L);
        
        //清空CNF
        void clear();

        //检查是否含有空子句
        bool containsEmptyClause() const;

        //检查是否含有单子句
        bool containsUnitClause() const;

        //获取单子句 基础策略：：直接按次序遍历，返回第一个单子句
        /*这个或许放在dpll里更好*/
        Clause getUnitClause_default();

        //判空
        bool empty() const;
        //打印
        void print();
        
        //若CNF至少有一个非空子句，返回true
        bool hasnext() const;
};
