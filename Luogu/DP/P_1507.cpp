#include <bits/stdc++.h>
using namespace std;
//二维0-1背包
int h;//总体积
int t;//质量
int n;//物品数量
signed main() {
    cin >> h >> t>>n;
    vector<pair<int,int>> w(n+1);
    vector<int> v(n + 1);
    for(int i=1;i<=n;i++){
        //物品 体积与质量 卡路里
        cin >> w[i].first >> w[i].second>>v[i];
    }
//以上为输入
vector<vector<int>> dp(h+1,vector<int>(t+1,0));
for(int i=1;i<=n;i++){
    for (int j = h; j >= w[i].first;j--){
        for (int k = t; k >= w[i].second;k--){
            dp[j][k] = max(dp[j][k], dp[j - w[i].first][k - w[i].second] + v[i]);
        }
    }
}
cout << dp[h][t];
}