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
//只要以某个点为根建立节点数数组即可
vector<pair<int, int>> adj[1000005];
int siz[1000005];
int Fa[1000005];
//初始化siz数组
void f(int cur, int fa) {
    siz[cur] = 1;
    for (size_t i = 0; i < adj[cur].size(); i++) {
        int next = adj[cur][i].first;
        int num = adj[cur][i].second;
        if (fa != next) {
            Fa[next] = num;
            f(next, cur);
        } else {
            continue;
        }
        siz[cur] += siz[next];
    }
    // cout<<"cur:"<<cur<<' '<<"siz:"<<siz[cur]<<endl;
    return;
}
//计算i，j人数差：abs(siz[i]-(n-siz[i]));
int ans;
signed main() {
    cin >> n;
    int a, b, c;
    for (int i = 1; i < n; i++) {
        a = read(), b = read(), c = read();
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    f(1, 0);
    // cout<<endl;
    for (int i = 2; i <= n; i++) {
        ans += abs(siz[i] - (n - siz[i])) * Fa[i];
        // cout << i << ' ' << Fa[i].first << "::" << abs(siz[i] - (n - siz[Fa[i].first] + 1))<<endl;
    }
    cout << ans;
}