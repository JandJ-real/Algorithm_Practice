#include <bits/stdc++.h>
/*
1.朴素找lca并且遍历两端点到祖宗的路径
2.树上前缀和
*/
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
// G:1  H:0
const int LOG = 20;
int n, m;
char arr[100005];
vector<int> adj[100005];
// int Fa[100005];
int deep[100005];
int parent[100005][LOG];
vector<pair<int, int>> prefix(100005);
void f(int cur, int fa, int dep) {
    parent[cur][0] = fa;
    deep[cur] = dep;
    if (arr[cur] == 'G') {
        prefix[cur].first = prefix[fa].first + 1;
        prefix[cur].second = prefix[fa].second;
    } else {
        prefix[cur].first = prefix[fa].first;
        prefix[cur].second = prefix[fa].second + 1;
    }
    for (int i = 1; i < LOG; i++) {
        if (parent[cur][i - 1] != 0) {
            parent[cur][i] = parent[parent[cur][i - 1]][i - 1];
        } else {
            parent[cur][i] = 0;
        }
    }
    for (int i = 0; i < (int)adj[cur].size(); i++) {
        int next = adj[cur][i];
        if (next != fa) {
            f(next, cur, dep + 1);
        }
    }
    return;
}
int lca(int a, int b) {
    if (deep[a] < deep[b]) {
        swap(a, b);
    }
    int diff = deep[a] - deep[b];
    for (int i = LOG - 1; i >= 0; i--) {
        if (diff & (1 << i)) {
            a = parent[a][i];
        }
        if (a == b) {
            return a;
        }
    }
    for (int i = LOG - 1; i >= 0; i--) {
        if (parent[a][i] != parent[b][i]) {
            a = parent[a][i];
            b = parent[b][i];
        }
    }
    return parent[a][0];
}
vector<int> ans;
signed main() {
    cin >> n >> m;
    char target;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    int a, b;
    for (int i = 1; i < n; i++) {
        a = read();
        b = read();
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    f(1, 0, 0);
    while (m--) {
        a = read();
        b = read();
        cin >> target;
        int L = lca(a, b);
        if (target == 'G') {
            if (arr[L] == 'G') {
                ans.push_back(1);
                continue;
            }
            if (prefix[a].first - prefix[L].first + prefix[b].first - prefix[L].first > 0) {
                ans.push_back(1);
                continue;
            }
        } else {
            if (arr[L] == 'H') {
                ans.push_back(1);
                continue;
            }
            if (prefix[a].second - prefix[L].second + prefix[b].second - prefix[L].second > 0) {
                ans.push_back(1);
                continue;
            }
        }
        ans.push_back(0);
    }

    for (int i = 0; i < (int)ans.size(); i++) {
        cout << ans[i];
    }
}