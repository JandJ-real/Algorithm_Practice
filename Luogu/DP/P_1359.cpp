#include <bits/stdc++.h>

using namespace std;
int n;//出租站个数
signed main() {
cin>>n;
vector<vector<int>> arr(n + 1, vector<int>(n + 1));//从i到j的费用 i<j
for(int i=1;i<n;i++){
    for(int j=1+i;j<=n;j++){
        cin >> arr[i][j];
    }
}
vector<int> dp(n + 1,INT_MAX);
dp[1] = 0;
for(int i=2;i<=n;i++){
    for (int j = 1;j<i;j++){
        dp[i] = min(dp[i], dp[j] + arr[j][i]);
    }
}
cout << dp[n];
}