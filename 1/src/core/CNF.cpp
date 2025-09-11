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
            if(Clauses[i].literals[j].var == c.literals[0].var)//若包含
            {
                break;
            }
        }
        if(j==Clauses[i].literals.size())//不含
        {
            newclauses.push_back(Clauses[i]);//添加到new
        }
    
    }
    Clauses=newclauses;//指向新数组
}

//移除剩下所有子句中的非L文字
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

//清空
void CNF::clear()
{
    Clauses.clear();
}

 //检查是否含有空子句
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

