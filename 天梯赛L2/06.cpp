#include <bits/stdc++.h>
using namespace std;
#define int long long
//熟练度不够
int n;
int hou[35];
int zhong[35];
/*
7
2 3 1 5 7 6 4
1 2 3 4 5 6 7
*/
vector<int> adj[35];
map<int, int> m;
void dfs(int l1, int r1, int l2, int r2) {
    // cout<<l1<<' '<<r1<<' '<<l2<<' '<<r2<<endl;
    if (l1 == r1 && l2 == r2) {
        return;
    }
    int gen = hou[r1];
    int index = m[gen];
    int lnum = index - l2;     //左子树数目
    int rnum = r2 - l2 - lnum; //右子树数目
    int lgen = hou[l1 + lnum - 1];
    int rgen = hou[r1 - 1];
    if (lnum != 0) {
        adj[gen].push_back(lgen);
        dfs(l1, l1 + lnum - 1, l2, index - 1);
    }
    if (rnum != 0) {
        adj[gen].push_back(rgen);
        dfs(l1 + lnum - 1 + 1, r1 - 1, index + 1, r2);
    }
}
signed main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> hou[i];
    }
    int x;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        zhong[i] = x;
        m[x] = i;
    }
    int root = hou[n];
    dfs(1, n, 1, n);
    queue<int> que;
    cout << root;
    for (int i = 0; i < (int)adj[root].size(); i++) {
        que.push(adj[root][i]);
    }
    while (!que.empty()) {
        int cur = que.front();
        que.pop();
        cout << ' ' << cur;
        for (int i = 0; i < (int)adj[cur].size(); i++) {
            que.push(adj[cur][i]);
        }
    }
    return 0;
}