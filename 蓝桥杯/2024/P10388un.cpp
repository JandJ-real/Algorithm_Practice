#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m;
vector<int> adjn[200005];
vector<int> adjm[200005];
int arrn[200005];
int arrm[200005];
int ans;
//二分优化？

void f(int curn, int fan, int curm, int fam, int temp) {
    ans = max(ans, temp);
    for (size_t i = 0; i < adjn[curn].size(); i++) {
        int nextn = adjn[curn][i];

        if (nextn != fan) {
            for (size_t j = 0; j < adjm[curm].size(); j++) {
                int nextm = adjm[curm][j];

                if (nextm != fam) {
                    if (arrn[nextn] == arrm[nextm]) {
                        f(nextn, curn, nextm, curm, temp + 1);
                        break;
                    }
                }
            }
        }
    }
}
signed main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arrn[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> arrm[i];
    }
    int u, v;
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        adjn[u].push_back(v);
        adjn[v].push_back(u);
    }
    for (int i = 1; i < m; i++) {
        cin >> u >> v;
        adjm[u].push_back(v);
        adjm[v].push_back(u);
    }
    if (arrn[1] != arrm[1]) {
        ans = 0;
    } else
        f(1, 0, 1, 0, 1);
    cout << ans << endl;
}