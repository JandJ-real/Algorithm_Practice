#include <bits/stdc++.h>
using namespace std;
#define int long long
const int LOG = 20;
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int n;
int k;
// vector<int> adj[50005];
//  ---------- 链式前向星 ----------
int head[50005], to[100005], nxt[100005], tot;
inline void add_edge(int u, int v) {
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}
int parent[50005][LOG];
int deep[50005];
// int siz[50005];
// int son[50005];
// int Fa[50005];
inline void dfs1(int cur, int fa, int dep) {
    // siz[cur] = 1;
    deep[cur] = dep;
    // int curmax = 0;
    parent[cur][0] = fa;
    for (int i = 1; i < LOG; i++) {
        if (parent[cur][i - 1]) {
            parent[cur][i] = parent[parent[cur][i - 1]][i - 1];
        } else {
            parent[cur][i] = 0;
        }
    }
    for (int i = head[cur]; i; i = nxt[i]) {
        int next = to[i];
        if (next != fa) {
            dfs1(next, cur, dep + 1);
        }
    }
    return;
}
/*
// int arr[50005];
// int newarr[50005];  //需要吗
int top[50005];
int dfn[50005];
int tim = 0;
inline void dfs2(int cur, int tp) {
    top[cur] = tp;
    dfn[cur] = ++tim;
    // newarr[tim] = arr[cur];
    if (!son[cur]) {
        return;
    }
    dfs2(son[cur], tp);
    for (int i = head[cur]; i; i = nxt[i]) {
        int next = to[i];
        if (next != son[cur] && next != Fa[cur]) {
            dfs2(next, next);
        }
    }
    return;
}
// int fin[50005];
*/

/*
// ---------- 链式前向星 ----------
int head[50005], to[50005], nxt[50005], tot;
inline void add_edge(int u, int v) {
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}
*/

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
int power[50005];
int ans;
void getans(int cur, int fa) {
    for (int i = head[cur]; i; i = nxt[i]) {
        int next = to[i];
        if (next != fa) {
            getans(next, cur);
            power[cur] += power[next];
        }
    }
    ans = max(ans, power[cur]);
}
// ---------- 主函数 ----------
signed main() {
    cin >> n >> k;
    int a, b;

    for (int i = 1; i < n; i++) {
        a = read();
        b = read();
        add_edge(a, b);
        add_edge(b, a);
    }

    int l, r;
    dfs1(1, 0, 1);
    // dfs2(1, 1);
    while (k--) {
        l = read(), r = read();
        int L = lca(l, r);
        //cout<<"l:r:lca:"<<l<<r<<L<<endl;
        power[l]++, power[r]++, power[L]--,power[parent[L][0]]--;
    }
    getans(1,0);
    cout<<ans;
    /*
    vector<int> prefix(n+2,0);//加到前一个
        //build(1, 1, n);
        while (k--) {
            l = read(), r = read();
            if (deep[top[l]] < deep[top[r]]) {
                swap(l, r);
            }
            while (top[l] != top[r]) {
                prefix[dfn[top[l]]-1]++;
                prefix[dfn[l]]--;
                //add(1, 1, n, dfn[top[l]], dfn[l], 1);
                l = Fa[top[l]];
            }
            if (top[l] == top[r]) {
                if (deep[l] < deep[r]) {
                    swap(l, r);
                }
                prefix[dfn[r] - 1]++;
                prefix[dfn[l]]--;
                //add(1, 1, n, dfn[r], dfn[l], 1);
            }
        }
        //push_all(1, 1, n);
        int cur=0;
        int ans=0;
    for(int i=1;i<=n;i++){
        cur+=prefix[i-1];
        ans=max(ans,cur);
    }
        // cout<<"sum:"<<seg.t[1].sum<<endl;
        cout << ans;
    */
}
