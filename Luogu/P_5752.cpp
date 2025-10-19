#include <bits/stdc++.h>

using namespace std;
#define int long long
inline int read() {
    int x = 0, f = 1;     // x: 存储结果, f: 符号标志(1正数, -1负数)
    char ch = getchar();  // 读取第一个字符

    while (!isdigit(ch)) {  // 跳过非数字字符
        if (ch == '-')
            f = -1;      // 遇到负号，设置符号为负
        ch = getchar();  // 继续读取下一个字符
    }

    while (isdigit(ch)) {       // 处理数字部分
        x = x * 10 + ch - '0';  // 将字符转换为数字并累加
        ch = getchar();         // 读取下一个字符
    }

    return x * f;  // 返回结果（考虑符号）
}
/*
如何模拟分割
原：1，1   8，8
1，1 8，3
1，4  8，8   -  1，4  2，8   =   3，4   8，8
3，4   4，8  -  3，6   4，8    3，4  4，5

a ,b   c,d   a,b  k,d   k+1,b  c,d
a ,b   c,d   a,b  c,k   a,k+1  c,d
*/
int n;
int arr[9][9];
int prefix[9][9];
signed main() {
    cin >> n;
    int temp;
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            temp=read();
            prefix[i][j] = prefix[i][j - 1] + temp;
        }
    }
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            prefix[j][i] += prefix[j - 1][i];
        }
    }

    /*
a,b   c,d
c,d   -  a-1,d   -  c,b-1    +   a-1,b-1  
2,1-0,1-2,0+0,0
*/
    /*for (int i = 0; i <= 8; i++) {
        for (int j = 0; j <= 8; j++) {
            cout<<prefix[i][j]<<' ';
        }
        cout<<endl;
    }*/
}