#include <bits/stdc++.h>
//完全背包问题
using namespace std;
#define int long long
int t;//时间
int m;//草药数量
signed main() {
cin>>t>>m;
vector<int> w(m + 1,0);
vector<int> v(m + 1,0);
for(int i=1;i<=m;i++){
    cin >> w[i] >> v[i];
}
//以上为输入
vector<int> dp(t + 1,0);
dp[0]=0;
for(int i=1;i<=m;i++){
    for (int j = w[i];j<=t;j++){
        dp[j] = max(dp[j - w[i]] + v[i], dp[j]);
    }
}
cout << dp[t];
}