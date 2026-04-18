#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;       //节点数
double z, r; //根节点值，衰减百分比
vector<int> adj[100005];
int flag[100005];
// int arr[100005];
double ans;
void dfs(int fa, int cur, double v) {
    //cout << fa << ' ' << cur << ' ' << v << endl;
    if (flag[cur]) {
        ans += v * flag[cur];
        return;
    }
    for (int next : adj[cur]) {
        dfs(cur, next, v * (100-r) / 100);
    }
}
signed main() {
    cin >> n >> z >> r;
    int num, x;
    for (int i = 0; i < n; i++) {
        cin >> num;
        if (num) {
            for (int j = 1; j <= num; j++) {
                cin >> x;
                adj[i].push_back(x);
            }
        } else {
            cin >> x;
            flag[i] = x;
        }
    }
    dfs(-1, 0, z);
    cout << (int)ans;
    return 0;
}