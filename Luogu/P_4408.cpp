#include <bits/stdc++.h>
/*
调了最久的居然是lca （同时跳时没用倒序。。。。）
用的贪心，没有严格证明
一开始太贪了，直接想找离中点最远的点（包括中点）（且不在直径上），deepseek说不行
后来枚举所有点，算maxmin ，反正也是O(n),不会复杂到哪里去
复杂度根本就是一样的啊喂
*/
using namespace std;
#define int long long
const int LOG = 20;
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
// C->A,B
//先去近的找
int n, m;
vector<pair<int, int>> adj[200005];
int u, v;
int target;
int curmax;
int parent[200005][LOG];
vector<int> zhijing;
int deep[200005];
int redeep[200005];
// int dist[200005];
void dfs1(int cur, int fa, int dep) {
    if (dep > curmax) {
        u = cur, curmax = dep;
    }
    for (int i = 0; i < (int)adj[cur].size(); i++) {
        int next = adj[cur][i].first;
        int num = adj[cur][i].second;
        if (next != fa) {
            dfs1(next, cur, dep + num);
        }
    }
}
void dfs2(int cur, int fa, int dep, int redep) {
    if (dep > curmax) {
        v = cur, curmax = dep;
    }
    deep[cur] = dep;
    redeep[cur] = redep;
    parent[cur][0] = fa;
    for (int i = 1; i < LOG; i++) {
        if (parent[cur][i - 1]) {
            parent[cur][i] = parent[parent[cur][i - 1]][i - 1];
        } else {
            parent[cur][i] = 0;
        }
    }
    for (int i = 0; i < (int)adj[cur].size(); i++) {
        int next = adj[cur][i].first;
        int num = adj[cur][i].second;
        if (next != fa) {
            dfs2(next, cur, dep + num, redep + 1);
        }
    }
    return;
}
int lca(int a, int b) {
    if (redeep[a] < redeep[b]) {
        swap(a, b);
    }
    int diff = redeep[a] - redeep[b];
    for (int i = LOG - 1; i >= 0; i--) {
        if (diff & (1 << i)) {
            a = parent[a][i];
        }
        if (a == b)
            return a;
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
void dfsmid(int cur, int fa, int dep) {
    if (dep > curmax && !onpath(u, v, cur)) {
        curmax = dep;
        target = cur;
    }
    for (int i = 0; i < (int)adj[cur].size(); i++) {
        int next = adj[cur][i].first;
        int num = adj[cur][i].second;
        if (next != fa) {
            dfsmid(next, cur, dep + num);
        }
    }
    return;
}
signed main() {
    cin >> n >> m;
    int a, b, c;
    for (int i = 1; i <= m; i++) {
        a = read(), b = read(), c = read();
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    //找三点，
    //猜测是直径两端点加离直径中点最远的点(不在直径上，对)
    dfs1(1, 0, 0);
    curmax = 0;
    dfs2(u, 0, 0, 0);
    // cout<<"zhijing:"<<u<<' '<<v<<endl;

    int vv = v;
    while (vv != u) {
        zhijing.push_back(vv);
        vv = parent[vv][0];
    }
    zhijing.push_back(u);
    //int mid = zhijing[((int)zhijing.size() / 2)];

    // cout<<"midstart:"<<mid<<endl;

    //curmax = 0;
    //target = mid;
    //dfsmid(mid, 0, 0);

    
        int maxmin=0;
    for(int i=1;i<=n;i++){
        maxmin=max(maxmin,min(dist(u,i),dist(v,i)));
    }
    

    // cout<<"midend:"<<mid<<endl;
    cout << dist(u, v) +maxmin;
}
