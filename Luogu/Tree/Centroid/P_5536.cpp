#include <bits/stdc++.h>
/*
1.按k分类，k<直径长度在直径上找路径作为核心城市；k>直径长度从大到小减去距离（实际上是错误的，都是错误的）
2.由特殊到一般：单个核心城市时，为直径中点，即树的中心；
  多个核心城市，只需以中心为根，按dfs序往下增长取缔即可
  （也可从中心开始bfs，直到核心城市数目达标，，不行不行，结果不好算）
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
int n, k;
//如何设置核心城市，能让最大距离最小 偏心距
//核心城市连通，但可能不是路径
vector<int> adj[100005];
int maxdep;
int u;
int v;
int Fa[100005];
vector<int> zhijing;
// vector<int> st;
// map<int, int> mp;
int deep[100005];
int maxdeep[100005];
int dist[100005];
void dfs1(int cur, int fa, int dep) {
    if (dep > maxdep) {
        maxdep = dep;
        u = cur;
    }
    for (int i = 0; i < (int)adj[cur].size(); i++) {
        int next = adj[cur][i];
        if (next != fa) {
            dfs1(next, cur, dep + 1);
        }
    }
    return;
}

void dfs2(int cur, int fa, int dep) {
    Fa[cur] = fa;
    if (dep > maxdep) {
        maxdep = dep;
        v = cur;
    }
    for (int i = 0; i < (int)adj[cur].size(); i++) {
        int next = adj[cur][i];
        if (next != fa) {
            dfs2(next, cur, dep + 1);
        }
    }
}
void dfsmid(int cur, int fa, int dep) {
    deep[cur] = dep;
    Fa[cur] = fa;
    maxdeep[cur] = dep;
    for (int i = 0; i < (int)adj[cur].size(); i++) {
        int next = adj[cur][i];

        if (next != fa) {
            dfsmid(next, cur, dep + 1);
        }
    }
    maxdeep[fa] = max(maxdeep[fa], maxdeep[cur]);
}
bool mycompare(int a, int b) {
    if (a > b) {
        return true;
    } else
        return false;
}
int ans;
signed main() {
    cin >> n >> k;
    int a, b;
    for (int i = 1; i < n; i++) {
        a = read(), b = read();
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs1(1, 0, 0);
    maxdep = 0;
    dfs2(u, 0, 0);
    // cout<<"zhijing:"<<u<<' '<<v<<endl;
    while (v != u) {
        zhijing.push_back(v);
        v = Fa[v];
    }
    zhijing.push_back(u);
    // cout<<"zhijing:"<<endl;
    /*    for(int i=0;i<(int)zhijing.size();i++){
        cout<<zhijing[i]<<endl;
    }*/
    //现在已经找出一条直径上的所有点

    int mid = zhijing[((int)zhijing.size() / 2)];
    dfsmid(mid, 0, 0);
    // cout << "mid:" << mid << endl;
    for (int i = 1; i <= n; i++) {
        dist[i] = maxdeep[i] - deep[i];
        // cout << i << ':' << dist[i] << endl;
    }
    sort(dist + 1, dist + n + 1, mycompare);

    for (int i = k + 1; i <= n; i++) {
        ans = max(ans, dist[i] + 1);
    }
    cout << ans;
    /*
        queue<pair<int, int>> que;
    int flag[100005];
    memset(flag, 0, sizeof(flag));
    if (k <= (int)zhijing.size()) {
        //取k个连续点，bfs
        int curmax = 0;
        int minmax = INT_MAX;
        for (int i = 0; i + k <= (int)zhijing.size(); i++) {
            memset(flag, 0, sizeof(flag));
            curmax = 0;
            for (int ii = 0; ii < k; ii++) {
                que.push({zhijing[i + ii], 0});
                flag[zhijing[i + ii]] = 1;
            }
            while (!que.empty()) {
                int cur = que.front().first;
                int curnum = que.front().second;
                // cout<<"cur:"<<cur<<' '<<"curnum"<<curnum<<endl;
                curmax = max(curmax, curnum);
                que.pop();
                for (int j = 0; j < (int)adj[cur].size(); j++) {
                    int next = adj[cur][j];
                    if (!flag[next]) {
                        flag[next] = 1;
                        que.push({next, curnum + 1});
                    }
                }
            }
            // cout << i << ' ' << curmax << endl;
            minmax = min(curmax, minmax);
        }
        cout << minmax << endl;

    } else {
        // cout << "tobe" << endl;
        for (int i = 0; i < (int)zhijing.size(); i++) {
            que.push({zhijing[i], 0});
            flag[zhijing[i]] = 1;
        }
        int curmax = 0;

        while (!que.empty()) {
            int cur = que.front().first;
            int curnum = que.front().second;
            // cout<<"cur:"<<cur<<' '<<"curnum"<<curnum<<endl;
            curmax = max(curmax, curnum);
            que.pop();
            for (int j = 0; j < (int)adj[cur].size(); j++) {
                int next = adj[cur][j];
                if (!flag[next]) {
                    flag[next] = 1;
                    mp[curnum + 1]++;
                    // cout<<"cur:"<<cur<<"next:"<<next<<endl;
                    // cout<<"cur:"<<mp[curnum+1]<<endl;
                    // st.push_back(curnum + 1);
                    que.push({next, curnum + 1});
                }
            }
        }
        int d = k - (int)zhijing.size();
        //或许可以有更好的存储办法
        // sort(st.begin(), st.end());
        // cout<<"d:"<<d<<endl;
        while (d--) {
            // cout<<"curmax:"<<curmax<<endl;
            // cout << "mp[curmax]:" << mp[curmax] << endl;
            mp[curmax]--;
            mp[curmax - 1]++;
            if (!mp[curmax]) {
                curmax -= 1;
            }
        }
        cout << curmax << endl;
        //统计所有点到直径的距离存到st中，多多少个减多少，从大的开始减
    }
    */
}
/*
10 6
1 3
2 3
3 4
4 5
4 6
4 7
7 8
6 9
9 10   2

10 7
1 3
2 3
3 4
4 5
4 6
4 7
7 8
6 9
9 10  1

*/