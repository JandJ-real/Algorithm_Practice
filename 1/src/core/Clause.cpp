#include"Clause.hpp"

Clause::Clause()
{
    
}

Clause::~Clause()
{

}

void Clause::addLiteral(Literal l)
{
    literals.push_back(l);
}

//�½�һ��vector��Ȼ���ԭ���İ����������������l��ѹ��ȥ��Ȼ�����
//���� �Ż���汾 ʹ��˫ָ�룬����һ�飬����Ҫ������Ԫ����ǰ�ţ�������size 
void Clause::removeLiteral(const Literal& l)
{
    size_t write_idx = 0;

    for (size_t read_idx = 0; read_idx < literals.size(); ++read_idx)
    {
        if (!(literals[read_idx] == l))  // ���������Ҫɾ���� literal
        {
            if (write_idx != read_idx)
                literals[write_idx] = literals[read_idx];  // ����
            ++write_idx;
        }
        // ������ڣ���ɶ������������
    }

    literals.setSize(write_idx);  // ֱ�Ӹ�����ЧԪ�ظ���
}

void Clause::print()
{
    std::cout << "{";
    for(size_t i=0;i<literals.size();++i)
    {
        literals[i].print();
    }
    std::cout << "}";
}

//�ж��Ƿ��Ӿ�
bool Clause::isSingleUnit() const
{
    return literals.size()==1;
}
