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

//新建一个vector，然后从原来的挨个遍历，如果不是l就压进去，然后更新
//更新 优化后版本 使用双指针，遍历一遍，将需要保留的元素往前放，最后更新size 
void Clause::removeLiteral(const Literal& l)
{
    size_t write_idx = 0;

    for (size_t read_idx = 0; read_idx < literals.size(); ++read_idx)
    {
        if (!(literals[read_idx] == l))  // 如果不等于要删除的 literal
        {
            if (write_idx != read_idx)
                literals[write_idx] = literals[read_idx];  // 搬移
            ++write_idx;
        }
        // 如果等于，则啥都不做，跳过
    }

    literals.setSize(write_idx);  // 直接更新有效元素个数
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

//判断是否单子句
bool Clause::isSingleUnit() const
{
    return literals.size()==1;
}
