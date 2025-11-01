#include <iostream>
using namespace std;
int main() {
    class A {
        int x;

    public:
        A(int x) : x(x) {
        }
    };
    A a;     //语句1
    A b(1);  //语句2
}