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
int n, m, q;
/*
1.查询x所在树的直径的长度
2.连接x，y所在树，使得新树的直径最小  (连中点吗)
*/
vector<int> adj[300005];
int Fa[300005];

int d[300005];
int g[300005];
int c[300005];  //代表元代表的树的直径
int len;        //直径
//bool vis[300005];
int findroot(int x) {
    if (x != Fa[x]) {
        Fa[x] = findroot(Fa[x]);
    }
    return Fa[x];  //!!
}
void hebing(int a, int b) {
    Fa[findroot(a)] = findroot(b);
    return;
}
void calclen(int cur, int fa) {
    int m1 = -1, m2 = -1;  //经过cur的最长和次最长路径
    for (int y : adj[cur]) {
        if (y == fa)
            continue;
        calclen(y, cur);
        int tmp = d[y] + 1;
        //cout << "tmp:" << endl;
        d[cur] = max(d[cur], tmp);
        if (tmp > m1) {
            // cout << "hhahaha" << endl;
            m2 = m1, m1 = tmp;
        }

        else if (tmp > m2)
            m2 = tmp;
    }
    // cout << "m1:m2:" << m1 << m2 << endl;
    g[cur] = max(max(0LL, m1 + m2), max(m1, m2));
    // cout << "cur:" << cur << ' ' << g[cur] << endl;
    len = max(len, g[cur]);
    return;
}
void getlen(int cur) {
    // cout << "hhha" << endl;
    len = 0;
    calclen(cur, 0);
    c[cur] = len;
    return;
}
signed main() {
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        Fa[i] = i;
    }
    int a, b, cc;
    for (int i = 1; i <= m; i++) {
        cin >> a >> b;
        hebing(a, b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 1; i <= n; i++) {
        if (Fa[i] != i) {
            continue;
            // cout << "i:" << i << ' ' << len << endl;
        }
        getlen(i);
        //vis[i] = 1;
    }
    while (q--) {
        cin >> a >> b;
        if (a == 1) {
            int temp = findroot(b);
            cout << c[temp] << endl;
        } else {
            cin >> cc;
            int zb, zc;
            zb = findroot(b);
            zc = findroot(cc);
            if (zb == zc) {
                continue;
            }
            int lenb, lenc;
            lenb = c[zb];
            lenc = c[zc];
            // cout<<"zb:zc:"<<zb<<' '<<zc<<':'<<lenb<<' '<<lenc<<endl;
            /*
                        if (lenb > 2) {
                lenb = max(lenb / 2, lenb - lenb / 2);
            }
            if (lenc > 2) {
                lenc = max(lenc / 2, lenc - lenc / 2);
            }
            */
            int temp = ((lenb + 1) >> 1) + ((lenc + 1) >> 1) + 1;  //一个巧妙的向上取整的方法
            int newlen = max(temp, max(lenb, lenc));
            Fa[zb] = zc;
            // cout<<"zc:"<<zc<<"newlen:"<<newlen<<endl;
            c[findroot(zc)] = newlen;
        }
    }
}
