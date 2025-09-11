#include"CNF.hpp"

CNF::CNF()
{

}
CNF::~CNF()
{

}

void CNF::addClause(Clause c)
{
    Clauses.push_back(c);
}

void CNF::removeClause(const Clause& c)
{
    MyVector<Clause> newclauses;
    for(size_t i=0;i<Clauses.size();++i)
    {
        size_t j=0;
        for(j=0;j<Clauses[i].literals.size();++j)
        {
            if(Clauses[i].literals[j].var == c.literals[0].var)//������
            {
                break;
            }
        }
        if(j==Clauses[i].literals.size())//����
        {
            newclauses.push_back(Clauses[i]);//��ӵ�new
        }
    
    }
    Clauses=newclauses;//ָ��������
}

//�Ƴ�ʣ�������Ӿ��еķ�L����
void CNF::removeLinClause(const Literal& L)
{
    for(size_t i=0;i<Clauses.size();++i)
    {
        Clauses[i].removeLiteral(L);
    }
}

bool CNF::empty() const
{
    return Clauses.size()==0;
}

void CNF::print()
{
    std::cout << "{";
    for(size_t i=0;i<Clauses.size();++i)
    {
        Clauses[i].print();
    }
    std::cout << "}";
}

bool CNF::hasnext() const
{
    return !Clauses.empty() && !Clauses[0].literals.empty();
}

//���
void CNF::clear()
{
    Clauses.clear();
}

 //����Ƿ��п��Ӿ�
bool CNF::containsEmptyClause() const
{
    for(size_t i=0;i<Clauses.size();++i)
    {
        if(Clauses[i].literals.empty()) return true;
    }
    return false;
}

Clause CNF::getUnitClause_default()
{
    for(size_t i=0;i<Clauses.size();++i)
    {
        if(Clauses[i].isSingleUnit()) return Clauses[i];
    }
    throw std::runtime_error("No Unit Clause Found");
}

bool CNF::containsUnitClause() const
{
    for(size_t i=0;i<Clauses.size();++i)
    {
        if(Clauses[i].isSingleUnit()) return true;
    }
    return false;
}

