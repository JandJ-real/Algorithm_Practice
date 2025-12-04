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
int n, c;
map<int, int> mp;
int ans;
signed main() {
    cin >> n >> c;
    int a;
    while (n--) {
        cin >> a;
        // a-b=c  可以将输入的每一个正数分为正负两个，分别作为减数和被减数
        if (c - a <= 0)
            ans += mp[c - a];
        mp[a]++;

        if (a) {
            ans += mp[c + a];
            mp[-a]++;
        }
    }
    cout << ans << endl;
}
/*
8 3
0 3 6 0 6 7 0 9


*/
