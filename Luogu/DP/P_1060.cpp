#include <bits/stdc++.h>

using namespace std;
int n;//总钱数（背包容量）
int m;//物品个数
signed main() {
cin>>n>>m;
vector<int> w(m+1);
vector<int> v(m+1);
for(int i=1;i<=m;i++){
    cin >> w[i] >> v[i];
}
//以上为输入
vector<int> dp(n + 1,0);
dp[0] = 0;
for(int i=1;i<=m;i++){
    //枚举物品编号
    for(int j=n;j>=1;j--){
        //枚举容量
        
        if(w[i]<=j){
            dp[j] = max(dp[j], dp[j - w[i]] + w[i] * v[i]);
        }
    }
}
cout << dp[n];
}