#include <bits/stdc++.h>
using namespace std;
#define int long long
//  8/25  反而是数据大的测试集过了，小的没过？？
int n, k;
// char arr[10005];
struct parent {
    int fa = -1;
    int ma = -1;
    char sex;
};
unordered_map<int, parent> adj;
bool check(int a, int b, int times) {
    // cout << a << ' ' << b << endl;
    if (a == -1 || b == -1) {
        return true;
    }
    if (times >= 5) {
        return true;
    }
    if (a == b) {
        return false;
    }
    return check(adj[a].fa, adj[b].ma, times + 1) &&
           check(adj[a].fa, adj[b].ma, times + 1) &&
           check(adj[a].ma, adj[b].fa, times + 1) &&
           check(adj[a].ma, adj[b].ma, times + 1);
}
signed main() {
    cin >> n;
    int tid, fa1, fa2;
    char c;
    for (int i = 1; i <= n; i++) {
        cin >> tid >> c >> fa1 >> fa2;
        adj[tid].sex = c, adj[tid].fa = fa1, adj[tid].ma = fa2;
        // adj[tid] = {fa1, fa2};
        adj[fa1].sex = 'M';
        adj[fa2].sex = 'F';
        // cout << adj[tid].first << adj[tid].second << endl;
    }

    cin >> k;
    int u, v;
    while (k--) {
        cin >> u >> v;
        // cout << "u:" << u << "v:" << v << endl;
        if (adj[u].sex == adj[v].sex) {
            cout << "Never Mind";
            // continue;
        } else {
            if (check(u, v, 0)) {
                cout << "Yes";
            } else {
                cout << "No";
            }
        }

        if (k >= 1) {
            cout << endl;
        }
    }
    return 0;
}