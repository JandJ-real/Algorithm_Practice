#include <bits/stdc++.h>
//0-1背包问题
using namespace std;
int t;//时间t
int m;//草药数目
signed main() {
    cin >> t >> m;
vector<int> w(m+1,0);
vector<int> v(m + 1,0);
for(int i=1;i<=m;i++){
  cin >> w[i] >> v[i];
}

vector<int> dp(t+1 ,0);

for(int i=1;i<=m;i++){
    //枚举接下来的草药序号
    for(int j=t;j>=w[i];j--){
        dp[j] = max(dp[j - w[i]] + v[i], dp[j]);
    }
}

//倒序可避免重复选取该物品，变成完全背包问题
cout << dp[t];
}