#include <iostream>
using namespace std;

void matrix(int size)
{
   
    int** arr = new int*[size];

    
    for (int i = 0; i < size; i++) {
        arr[i] = new int[size - i];  

       
        for (int j = 0; j < size - i; j++) {
            arr[i][j] = 0;
            cout << arr[i][j] << ' ';
        }
        cout << endl;
    }

    
    for (int i = 0; i < size; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}

int main()
{
    matrix(7);
    return 0;
}