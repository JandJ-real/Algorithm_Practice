#pragma once
#include"Clause.hpp"
class CNF
{
    public:
        MyVector<Clause> Clauses;

        //���캯��
        CNF();
        ~CNF();
        //����Ӿ�
        void addClause(Clause c);
        //�Ƴ����а������Ӿ�L�ľ���
        void removeClause( const Clause& c);
        //�Ƴ�ʣ�������Ӿ��е�~L
        void removeLinClause(const Literal& L);
        
        //���CNF
        void clear();

        //����Ƿ��п��Ӿ�
        bool containsEmptyClause() const;

        //����Ƿ��е��Ӿ�
        bool containsUnitClause() const;

        //��ȡ���Ӿ� �������ԣ���ֱ�Ӱ�������������ص�һ�����Ӿ�
        /*����������dpll�����*/
        Clause getUnitClause_default();

        //�п�
        bool empty() const;
        //��ӡ
        void print();
        
        //��CNF������һ���ǿ��Ӿ䣬����true
        bool hasnext() const;
};
