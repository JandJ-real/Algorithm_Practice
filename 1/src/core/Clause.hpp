#pragma once
#include"Literal.hpp"
#include"../containers/MyVector.hpp"

class Clause
{
    public:
        //���ּ���
        MyVector<Literal> literals;

        //���캯��
        Clause();
        //��������
        ~Clause();

        //�������
        void addLiteral(Literal l);
        //ɾ������ָ������
        void removeLiteral(const Literal& l);

        //��ӡ�Ӿ�
        void print();

        //�ж��Ƿ�Ϊ���Ӿ� 
        bool isSingleUnit() const;
};
