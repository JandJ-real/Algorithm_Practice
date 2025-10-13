#include <bits/stdc++.h>
//本题是排列，如果换成组合呢
//只需将循环的顺序变一下，有点像0-1背包和完全背包
//死记这一点：循环顺序决定排列与组合
using namespace std;
//#define mod (1e9+7)
#define int long long
int mod = 1e9 + 7;
inline int read()
{
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
int w;  //要凑出的价值
int n;  //纸币种类
vector<int> arr;
vector<int> dp;
signed main()
{
    cin >> n >> w;
    arr.resize(n);
    dp.resize(w + 1, 0);
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        arr[i] = read();
    }
    //以上为输入
    for (int i = 1; i <= w; i++) {
        for (int j = 0; j < n; j++) {
            int last = i - arr[j];
            if (last >= 0) {
                dp[i] += (dp[last] % (mod));
                dp[i] %= (mod);
            }
        }
    }
    cout << dp[w];
}