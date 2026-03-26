#include <bits/stdc++.h>
//倍增法求公共祖先
//树上差分
//将有向无环图  提成树来处理
using namespace std;
#define int long long
//有向无环图的最短距离就是LCA
const int LOG = 20;
int n, q;
int c[100005];  //第几种零食
vector<int> adj[100005];
int deep[100005];
int parent[100005][LOG];
int a, b;
int tohere[100005][25];  //从1到当前节点，Ci这种零食出现的次数
//预处理深度和parent数组用于lca函数,得到
void f(int cur, int fa, int dep) {
    deep[cur] = dep;
    parent[cur][0] = fa;
    for (int i = 1; i <= LOG; i++) {
        tohere[cur][i] = tohere[fa][i];
    }
    tohere[cur][c[cur]]++;
    for (int i = 1; i < LOG; i++) {
        parent[cur][i] = parent[parent[cur][i - 1]][i - 1];
    }
    for (int i = 0; i < (int)adj[cur].size(); i++) {
        int next = adj[cur][i];
        if (next != fa) {
            f(next, cur, dep + 1);
        }
    }
    return;
}
int lca(int u, int v) {
    //令前者深度更大
    if (deep[u] < deep[v]) {
        swap(u, v);
    }
    int diff = deep[u] - deep[v];
    for (int i = LOG - 1; i >= 0; i--) {
        if (diff & (1 << i)) {
            u = parent[u][i];
        }
        if (u == v) {
            return u;
        }
    }
    for (int i = LOG - 1; i >= 0; i--) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}
signed main() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    for (int i = 1; i <= n - 1; i++) {
        cin >> a >> b;
        adj[a].push_back(b);
    }
    f(1, 0, 1);
    /*        cout<<endl;
    for(int i=1;i<=4;i++){
        for(int j=1;j<=LOG;j++){
            cout<<i<<' '<<j<<' '<<tohere[i][j]<<' ';
            cout << endl;
        }
        cout<<endl;
    }*/

    while (q--) {
        cin >> a >> b;
        //从a到b
        int ca = lca(a, b);
        //cout << "ca:" << ca << endl;
        int ans[25]={0,};
        int temp=0;
        ans[c[ca]] = 1;
        for (int i = 1; i <= LOG; i++) {
            ans[i] += (tohere[a][i] + tohere[b][i] - 2 * tohere[ca][i]);
            //cout<<"i:"<<i<<endl;
            //cout << tohere[a][i] << tohere[b][i] << tohere[ca][i]<<ans[i]<<endl;
             if (ans[i]) {
                temp++;
                //cout<<i<<endl;
            }
        }
        cout << temp;
        cout << endl;
    }
}