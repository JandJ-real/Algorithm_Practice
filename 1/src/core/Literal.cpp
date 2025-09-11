#include"literal.hpp"

Literal::Literal()
{
    this->var=0;
}

//带值构造函数
Literal::Literal(int var)
{
    this->var=var;
}
//仅包含一个 int 类型的成员变量 var（基本数据类型）。
//对于基本类型（int、bool、double 等），它们的内存由编译器
//自动管理（分配在栈上），生命周期随对象一起结束，无需手动释放。故函数内没有语句
Literal::~Literal()
{

}

//是否是负文字
bool Literal::isNegative()
{
    return this->var < 0;
}

//返回绝对值

int Literal::getAbs()
{
    return abs(this->var);
}

void Literal::print()
{
    //没有命名冲突时 this->var和var等价，上面同理
    cout << this->var << " ";
}

bool Literal::operator!=(const Literal& l) const
{
    return this->var != l.var;//this是指针 要->，l是直接引用，成员要.
}

bool Literal::operator==(const Literal& l)const
{
    return this->var == l.var;
}
