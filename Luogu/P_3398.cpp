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
const int LOG = 20;
int n, q;
vector<int> adj[100005];
vector<char> ans;
int deep[100005];
int parent[100005][LOG];
void f(int cur, int fa, int dep) {
    deep[cur] = dep;
    parent[cur][0] = fa;
    for (int i = 1; i < LOG; i++) {
        if (parent[cur][i - 1]) {
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
int dist(int a, int b) {
    int L = lca(a, b);
    return deep[a] + deep[b] - 2 * deep[L];
}
bool onpath(int u, int v, int x) {
    return dist(u, x) + dist(v, x) == dist(u, v);
}
signed main() {
    cin >> n >> q;
    int a, b;
    for (int i = 1; i < n; i++) {
        a = read();
        b = read();
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    f(1,0,0);
    int c, d;
    while (q--) {
        a = read(), b = read(), c = read(), d = read();
        int L1 = lca(a, b);
        int L2 = lca(c, d);
        if (onpath(a, b, L2) || onpath(c, d, L1)) {
            ans.push_back('Y');
        }
        else{
            ans.push_back('N');
        }
    }
    for(char temp:ans){
        cout<<temp<<endl;
    }
}