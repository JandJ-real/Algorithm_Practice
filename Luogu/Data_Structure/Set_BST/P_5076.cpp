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
//查询数的排名
//查询特定排名的数
//求第一个小于x的数
//求的一个大于x的数
//插入一个数
int q;
multiset<int> arr;
vector<int> anses;
signed main() {
    cin >> q;
    int a, b;
    for (int i = 1; i <= q; i++) {
        a = read();
        b = read();
        if (a == 1) {
            int ans = 1;
            for (auto it = arr.begin(); it != arr.end(); it++) {
                if (*it < b) {
                    ans++;
                } else {
                    break;
                }
            }
            anses.push_back(ans);
        }
        if (a == 2) {
            auto it = arr.begin();
            for (int i = 1; i < b; i++) {
                it++;
            }
            anses.push_back(*it);
        }
        if (a == 3) {
            //这里有一些奇怪的地方
            auto it = lower_bound(arr.begin(), arr.end(), b);
            if (it == arr.begin()) {
                anses.push_back(-2147483647);
            } else {
                it--;
                anses.push_back(*it);
            }
        }
        if (a == 4) {
            auto it = upper_bound(arr.begin(), arr.end(), b);
            if (it != arr.end()) {
                anses.push_back(*it);
            } else {
                anses.push_back(2147483647);
            }
        }
        if (a == 5) {
            arr.insert(b);
        }
    }

    for (size_t i = 0; i < anses.size(); i++) {
        cout << anses[i] << endl;
    }
}