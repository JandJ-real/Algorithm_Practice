#include <bits/stdc++.h>

using namespace std;
#define int long long
const int MOD = 80112002;
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
int n, m;
vector<int> adj[5005];
int in[5005];
int out[5005];
int dp[5005];
signed main() {
    cin >> n >> m;
    int a, b;
    while (m--) {
        a = read(), b = read();
        adj[b].push_back(a);
        out[b]++, in[a]++;
    }
    queue<int> que;
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0) {
            que.push(i);
            dp[i] = 1;
        }
    }
    int temp;
    int ans = 0;
    while (!que.empty()) {
        temp = que.front();
        que.pop();
        for (int next : adj[temp]) {
            in[next]--;
            if (!in[next]) {
                que.push(next);
            }
            dp[next] += dp[temp];
            dp[next] %= MOD;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!out[i]) {
            ans = (ans + dp[i]) % MOD;
        }
    }
    cout << ans;
}
