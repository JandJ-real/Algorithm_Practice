#pragma once

#include<cstddef>
#include<stdexcept>
#include<algorithm>

template<typename T>

class MyVector
{
    private:
        T* Data;//指向动态数组的指针
        size_t Size;//当前元素数量
        size_t Capacity;//当前分配的内存容量

        //扩容函数
        void resize(size_t new_capacity)
        {
            if(new_capacity <= Capacity) return;//不需扩容

            T* new_data = new T[new_capacity];//分配新内存

            //将旧数据拷贝到新内存
            for(size_t i=0;i<Size;++i)
            {
                new_data[i]=Data[i];
            }
            
            //释放旧内存
            delete[] Data;

            //更新指针and容量
            Data = new_data;
            Capacity = new_capacity;
        }

    public:
        
        //构造函数
        MyVector() : Data(nullptr),Size(0),Capacity(0) {}
        /*成员初始化列表
        构造函数(参数) : 成员1(值1), 成员2(值2), ... {}*/

        //带初始容量的构造函数
        explicit MyVector(size_t initial_capacity)
            : Data(new T[initial_capacity]),Size(0),Capacity(initial_capacity) {};
            /*关键字 explicit：
            非常重要！它防止了编译器的隐式类型转换。
            没有它，代码 MyVector vec = 10; 会被编译通过（隐式将 int 转换为 MyVector），这通常不是我们想要的行为。
            有了它，必须显式调用：MyVector vec(10); 或 MyVector vec = MyVector(10);*/
        
        MyVector(size_t n, const T& value)
            :Data(new T[n]), Size(n), Capacity(n)
        {
            for(size_t i=0;i<n;++i)
            {
                Data[i]=value;
            }
        }

        //拷贝构造函数
        MyVector(const MyVector& other)
            :Data(new T[other.Capacity]),Size(other.Size),Capacity(other.Capacity){
                for(size_t i=0;i<Size;++i)
                {
                    Data[i]=other.Data[i];
                }
            }
        /*根据另一个MyVector对象other，创建一个深拷贝，新旧两对象完全独立，修改一个不会影响另一个*/

        //赋值运算符
        MyVector& operator=(const MyVector& other)
        {
            if(this != &other)
            {
                //先释放当前内存
                delete[] Data;

                //分配新内存
                Data=new T[other.Capacity];
                Size=other.Size;
                Capacity=other.Capacity;

                //拷贝数据
                for(size_t i=0;i<Size;++i)
                {
                    Data[i]=other.Data[i];
                }
            }
            return *this;//为了支持链式赋值v1 = v2 = v3;
        }

        //析构函数
        ~MyVector()
        {
            delete[] Data;
        }

        //在末尾添加元素
        void push_back(const T& value)
        {
            if(Size>=Capacity)
            {
                //扩容：若容量为0则扩容到1，否则翻倍
                resize(Capacity==0 ? 1 : Capacity*2);
            }
            Data[Size++] = value;
        }

        //删除末尾元素
        void pop_back()
        {
            if(Size>0) --Size;
        }

        //访问元素（带边界检查）
        T& at(size_t index)
        {
            if(index>=Size) 
            {
                /*throw 是 C++ 的异常抛出（Exception Throwing） 关键字。它的
                作用是：当检测到错误（此处是索引越界）时，立即中止当前函数的正
                常执行流程，并创建一个错误对象（异常对象）将其“抛出”到函数外部
                ，通知调用者“这里发生了一个错误，需要处理*/
                throw std::out_of_range("Index out of range");
            }
            return Data[index];
        }
        const T& at(size_t index) const
        {
            if(index>=Size) 
            {
                /*throw 是 C++ 的异常抛出（Exception Throwing） 关键字。它的
                作用是：当检测到错误（此处是索引越界）时，立即中止当前函数的正
                常执行流程，并创建一个错误对象（异常对象）将其“抛出”到函数外部
                ，通知调用者“这里发生了一个错误，需要处理*/
                throw std::out_of_range("Index out of range");
            }
            return Data[index];
        }

        

        //运算符[]访问
        //第一个const 规定返回的引用是常量引用，只读，防止通过[]意外地修改向量中的元素
        //第二个const 声明这个成员函数本身是一个常量成员函数，这个关键字向编译器承诺：“我（这个函数）不会修改调用我的那个对象的任何成员变量。”
        T& operator[](size_t index)
        {
            return Data[index];
        }
        const T& operator[](size_t index) const
        {
            return Data[index];
        }

        //获取第一个元素
        //***常量对象不能调用非常量成员函数,因为编译器无法保证这个函数不会修改对象。
        //非常量版本 (用于可修改的对象) 返回普通引用T&
        T& front()
        {
            if(Size==0) throw std::out_of_range("Vector is empty");
            return Data[0];
        }

        //常量版本 (用于只读的对象)
        const T& front() const
        {
            if(Size==0) throw std::out_of_range("Vector is empty");
            return Data[0];
        }



        //获取最后一个元素
        T& back()
        {
            if(Size==0) throw std::out_of_range("Vector is empty");
            return Data[Size-1];
        }

        const T& back() const
        {
            if(Size==0) throw std::out_of_range("Vector is empty");
            return Data[Size-1];
        }

        //获取数据指针
        T* data()
        {
            return Data;
        }
        const T* data() const
        {
            return Data;
        }

        //容量and大小
        //这几个是按值返回，返回的是一个值相同的副本，调用这无论如何修改这个返回值，都不会影响原对象内部的成员变量，故前面不需要const。
        //上面几个是引用返回，意味着调用者拿到的是对象内部数据的一个别名（alias），是直接关联。通过这个引用，可以直接修改对象内部的数据。需要在前面加const
        
        size_t size ()const
        {
            return Size;
        }

        size_t capacity ()const
        {
            return Capacity;
        }

        bool empty ()const
        {
            return Size==0;
        }

        //清空，不释放内存
        void clear()
        {
            Size=0;
        }

        

        //释放多于内存
        void shrink_to_fit()
        {
            if(Size < Capacity)
            {
                T* new_data = new T[Size];
                for(size_t i=0;i<Size;++i)
                {
                    new_data[i]=Data[i];
                }
                delete[] Data;
                Data=new_data;
                Capacity=Size;
            }
        }

        //预留容量
        void reserve(size_t new_capacity)
        {
            if(new_capacity > Capacity)
            {
                resize(new_capacity);
            }
        }

        T* begin(){return Data;}
        const T* begin() const {return Data;}
        T* end(){return Data+Size;}
        const T* end() const {return Data+Size;}

        // 删除指定位置的元素（通过索引）
    void erase(size_t index) {
        if (index >= Size) {
            throw std::out_of_range("Index out of range in erase");
        }
        
        // 将后面的元素向前移动一位
        for (size_t i = index; i < Size - 1; ++i) {
            Data[i] = Data[i + 1];
        }
        --Size;
    }

    // 删除指定位置的元素（通过迭代器）
    T* erase(T* position) {
        if (position < begin() || position >= end()) {
            throw std::out_of_range("Iterator out of range in erase");
        }
        
        size_t index = position - begin();
        erase(index);
        return begin() + index; // 返回指向被删除元素后面元素的迭代器
    }

    // 删除指定范围的元素 [first, last)
    T* erase(T* first, T* last) {
        if (first < begin() || last > end() || first > last) {
            throw std::out_of_range("Invalid range in erase");
        }
        
        if (first == last) return first; // 空范围，直接返回
        
        size_t start_index = first - begin();
        size_t end_index = last - begin();
        size_t elements_to_remove = end_index - start_index;
        
        // 将后面的元素向前移动
        for (size_t i = end_index; i < Size; ++i) {
            Data[start_index + (i - end_index)] = Data[i];
        }
        
        Size -= elements_to_remove;
        return begin() + start_index; // 返回指向被删除范围后面元素的迭代器
    }

    // 删除第一个等于指定值的元素
    bool erase(const T& value) {
        for (size_t i = 0; i < Size; ++i) {
            if (Data[i] == value) {
                erase(i);
                return true;
            }
        }
        return false; // 没有找到要删除的元素
    }

    // 删除所有等于指定值的元素
    size_t erase_all(const T& value) {
        size_t count = 0;
        size_t write_index = 0;
        
        for (size_t read_index = 0; read_index < Size; ++read_index) {
            if (Data[read_index] != value) {
                Data[write_index] = Data[read_index];
                ++write_index;
            } else {
                ++count;
            }
        }
        
        Size = write_index;
        return count; // 返回删除的元素数量
    }

    void setSize(size_t new_size)
    {
        Size = new_size;
    }    
};