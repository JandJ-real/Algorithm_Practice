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
int arr[10005];
vector<int> adj[10005];
int in[10005];
int out[10005];
int dp[10005];
signed main() {
    cin >> n;
    int a, len, to;
    for (int i = 1; i <= n; i++) {
        a = read(), len = read();
        arr[i] = len;
        dp[i] = len;
        while (cin >> to, to) {
            adj[to].push_back(a);
            out[to]++, in[a]++;
        }
    }
    queue<int> que;
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0) {
            que.push(i);
        }
    }
    int temp;
    int ans = 0;
    while (!que.empty()) {
        temp = que.front();
        que.pop();
        for (int next : adj[temp]) {
            if ((--in[next]) == 0) {
                que.push(next);
            }
            dp[next] = max(dp[next], dp[temp] + arr[next]);
        }
    }
    for (int i = 1; i <= n; i++) {
        ans = max(ans, dp[i]);
    }

    cout << ans;
}
