#include <bits/stdc++.h>

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
int n, m, r, MOD;
int arr[100005];
vector<int> adj[100005];

int siz[100005];
int son[100005];
int Fa[100005];
int deep[100005];
void dfs1(int cur, int fa, int dep) {
    //第一次dfs 建立fa，son，deep，siz
    siz[cur] = 1;
    int maxson = 0;
    deep[cur] = dep;
    Fa[cur] = fa;
    for (int next : adj[cur]) {
        if (next != fa) {
            dfs1(next, cur, dep + 1);
        }
        siz[cur] += siz[next];
        if (siz[next] > maxson) {
            maxson = siz[next];
            son[cur] = next;
        }
    }
}
int dfn[100005];  //树剖之后的新编号（时间戳）
int top[100005];  //节点i所在树链的顶端（深度最小）
int rnk[100005];  //反向查询，表示某个新编号对应的节点是哪个
int tim = 0;
void dfs2(int cur, int tp) {
    top[cur] = tp;
    dfn[cur] = ++tim;
    rnk[tim] = cur;
    if (!son[cur]) {
        //没有重儿子就结束
        return;
    }
    //先走重儿子
    dfs2(son[cur], tp);
    //再走轻儿子，每个重开一个树链
    for (int next : adj[cur]) {
        if (next != Fa[cur] && next != son[cur]) {
            dfs2(next, next);
        }
    }
    return;
}
signed main() {
    cin >> n >> m >> r >> MOD;
    for (int i = 1; i <= n; i++) {
        arr[i] = read();
    }
    int a, b;
    for (int i = 1; i < n; i++) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs1(r,0,0);
    dfs2(r,r);
    while (m--) {
    }
}
