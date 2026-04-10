#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m, q;
int dp[5005][5005];
//用弗洛伊德要理解弗洛伊德的本质，就是找中间商
signed main() {
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = -1;
        }
    }
    int u, v, num;
    for (int i = 1; i <= m; i++) {
        cin >> u >> v >> num;
        //重边！！！  没说是dag
        dp[u][v] = max(dp[u][v], num);
        dp[v][u] = max(dp[v][u], num);
    }
    for (int k = 1; k <= n; k++) {
        for (int j = 1; j <= n; j++) {
            for (int i = 1; i <= n; i++) {
                if (i != j && j != k && i != k)
                    dp[i][j] = max(dp[i][j], min(dp[i][k], dp[j][k]));
            }
        }
    }
    while (q--) {
        cin >> u >> v;
        cout << dp[u][v] << endl;
    }
}