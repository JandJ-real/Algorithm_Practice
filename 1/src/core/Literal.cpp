#include"literal.hpp"

Literal::Literal()
{
    this->var=0;
}

//��ֵ���캯��
Literal::Literal(int var)
{
    this->var=var;
}
//������һ�� int ���͵ĳ�Ա���� var�������������ͣ���
//���ڻ������ͣ�int��bool��double �ȣ������ǵ��ڴ��ɱ�����
//�Զ�����������ջ�ϣ����������������һ������������ֶ��ͷš��ʺ�����û�����
Literal::~Literal()
{

}

//�Ƿ��Ǹ�����
bool Literal::isNegative()
{
    return this->var < 0;
}

//���ؾ���ֵ

int Literal::getAbs()
{
    return abs(this->var);
}

void Literal::print()
{
    //û��������ͻʱ this->var��var�ȼۣ�����ͬ��
    cout << this->var << " ";
}

bool Literal::operator!=(const Literal& l) const
{
    return this->var != l.var;//this��ָ�� Ҫ->��l��ֱ�����ã���ԱҪ.
}

bool Literal::operator==(const Literal& l)const
{
    return this->var == l.var;
}
