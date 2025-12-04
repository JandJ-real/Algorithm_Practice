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
int n;
map<string, int> mp;
int num;
signed main() {
    cin>>n;
    int a;
    string str;
    int b;
    while (n--) {
        cin >> a;
        if (a == 1) {
            cin >> str >> b;
            if (!mp[str])
                num++;
            mp[str] = b;
            cout << "OK" << endl;

        } else if (a == 2) {
            cin >> str;
            if (!mp[str])
                cout << "Not found" << endl;
            else {
                cout << mp[str] << endl;
            }

        } else if (a == 3) {
            cin >> str;
            if (!mp[str])
                cout << "Not found" << endl;
            else {
                mp[str] = 0;
                cout << "Deleted successfully" << endl;
                num--;
            }
        } else {
            cout<<num<<endl;
        }
    }
}
