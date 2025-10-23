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
int MOD = 998244353;
int n;
int dp[1005][40005];
int ans;
vector<int> h;
//如果地上只留了一个或者两个电塔，那么这种方案也是美观的。地上没有电塔的方案被认为是不美观的。
signed main() {
    cin >> n;
    h.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        h[i] = read();
    }
   
    for (int i = 1; i <= n; i++) {
        ans++;
        for (int j = i - 1; j ; j--) {
            int dx = h[i] - h[j] + 20000;
            dp[i][dx] += dp[j][dx]+1;
            //cout << "i:" << i << ' ' << "j:" << j << ' ' << "dx:" << dx - 20000 << ' ' << dp[i][dx] << endl;
            dp[i][dx] %= MOD;
            ans += dp[j][dx]+1;
            ans %= MOD;
        }
    }

    cout << ans;
}