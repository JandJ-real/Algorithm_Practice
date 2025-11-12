#include <bits/stdc++.h>

using namespace std;
#define int long long
const int LOG = 20;
int parent[1000005][LOG];
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
int arr[1000005];
vector<int> colornum[1000005];
vector<int> adj[1000005];
//无这种颜色输出 (n*(n-1)) / 2
//节点只有一个：子树节点两两相乘+子树节点之和
//节点有两个以上：首先得有一条（u，v）满足u，v都是该颜色且路径包含所有该颜色的点（即所有该颜色都在一条直链上） 否则为0
//无简单路径输出 0

int Fa[1000005];
int siz[1000005];
int deep[1000005];  //深度从零开始
// int dfsnum[1000005];
//建立父子关系 计算子树大小
int num = 0;
void f(int cur, int fa, int dep) {
    siz[cur] = 1;
    deep[cur] = dep;
    parent[cur][0] = fa;
    // dfsnum[cur] = ++num;

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
            Fa[next] = cur;
            f(next, cur, dep + 1);
        } else {
            continue;
        }
        siz[cur] += siz[next];
    }
    return;
}
//倍增法？？？

/*int lca(int a, int b) {
    if (deep[a] < deep[b]) {
        swap(a, b);
    }
    int d = deep[a] - deep[b];
    while (d--) {
        a = Fa[a];
    }
    if (a == b) {
        return b;
    }
    while (Fa[a] != Fa[b]) {
        a = Fa[a];
        b = Fa[b];
    }
    return Fa[a];
}*/

int lca(int u, int v) {
    if (deep[u] < deep[v])
        swap(u, v);

    int diff = deep[u] - deep[v];
    for (int i = 0; i < LOG; i++) {
        if (diff & (1 << i)) {
            u = parent[u][i];
        }
        if (u == v)
            return u;
    }
    for (int i = LOG-1; i >= 0; i--) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}
int dist(int a, int b) {
    int la = lca(a, b);
    return deep[a] + deep[b] - 2 * deep[la];
}
bool onPath(int u, int v, int x) {
    // x is on path u-v iff dist(u,x)+dist(x,v) == dist(u,v)
    return dist(u, x) + dist(x, v) == dist(u, v);
}

signed main() {
    n=read();
    for (int i = 1; i <= n; i++) {
        arr[i] = read();
        colornum[arr[i]].push_back(i);
    }
    int a, b;
    for (int i = 1; i < n; i++) {
        a = read(), b = read();
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    f(1, 0, 0);
    for (int i = 1; i <= n; i++) {
        int num = (int)colornum[i].size();
        if (num == 0) {
            cout << (n * (n - 1)) / 2 << endl;
        } else if (num == 1) {
            int point = colornum[i][0];
            // cout << "point:" << point << endl;
            int father = Fa[point];
            // cout << "father:" << father << endl;
            int ans1 = 0;

            for (int k = 0; k < (int)adj[point].size(); k++) {
                int son2 = adj[point][k];
                if (son2 != father) {
                    if (father)
                        ans1 += siz[son2] * (n - (siz[point]));
                    for (int j = k + 1; j < (int)adj[point].size(); j++) {
                        int son1 = adj[point][j];

                        if (son1 != father) {
                            ans1 += siz[son1] * siz[son2];
                        }
                    }
                }
            }
            // cout<<"ans1:"<<ans1<<' '<<"ans2:"<<ans2<<endl;
            cout << ans1 + n - 1 << endl;
        } else {
            //如何找到端点
            //两次dfs
            int flag = 1;
            int temp = colornum[i].front();
            int tempmax = 0;
            int u = temp, v = temp;
            //找出距离首元素最远的点u
            for (int x : colornum[i]) {
                int tempdist = dist(temp, x);
                if (tempdist > tempmax) {
                    u = x;
                    tempmax = tempdist;
                }
            }
            //找出距离u最远的点v
            tempmax = 0;
            for (int x : colornum[i]) {
                int tempdist = dist(x, u);
                if (tempdist > tempmax) {
                    v = x;
                    tempmax = tempdist;
                }
            }
            // cout << u << ' ' << v << endl;
            if(num>2)
            for (int x : colornum[i]) {
                if (!onPath(u, v, x)) {
                    cout << '0' << endl;
                    flag = 0;
                }
            }
            if (flag) {
                int ans;
                int ans1 = 1;
                int ans2 = 1;
                for (int ii = 0; ii < (int)adj[u].size(); ii++) {
                    int next = adj[u][ii];
                    if (!onPath(u, v, next)) {
                        if (next == Fa[u]) {
                            ans1 += n - siz[u];
                        } else {
                            ans1 += siz[next];
                        }
                    }
                }
                for (int ii = 0; ii < (int)adj[v].size(); ii++) {
                    int next = adj[v][ii];
                    if (!onPath(u, v, next)) {
                        if (next == Fa[v]) {
                            ans2 += n - siz[v];
                        } else {
                            ans2 += siz[next];
                        }
                    }
                }
                ans = ans1 * ans2;
                cout << ans << endl;
            }
        }
    }
}
