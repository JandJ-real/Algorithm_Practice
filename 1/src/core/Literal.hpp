#pragma once
#include"../definition.h"
class Literal
{
    public:
        int var;
        Literal();
        Literal(int var);//��ֵ���캯��

        ~Literal();//����
        bool isNegative();//�Ƿ��Ǹ�����
        int getAbs();//���ؾ���ֵ
        void print();//��ӡ����
        bool operator!=(const Literal& l)const;//���Ⱥ�����
        bool operator==(const Literal& l)const;//�Ⱥ�����

};
