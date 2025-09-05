#include <bits/stdc++.h>
using namespace std;
//一道隐藏的完全背包问题 而且是t-1轮完全背包

//关键点：将已经买入的纪念品转化为第二天的背包容量

//启示：题目给的简单测试集，除了让你拿点小分，更多的是引导从简单的问题入手，分析问题的本质(t=1时，简单模拟即可看出是一次完全背包问题，从而想到多重完全背包)
int t;//未来天数
int n;//纪念品数量
int m;//初始金币
signed main() {
cin>>t>>n>>m;
vector<vector<int>> arr(t+1,vector<int>(n+1));
for (int i = 1; i <= t;i++){
    for(int j=1;j<=n;j++){
        cin >> arr[i][j];
    }
}
//以上为输入
//t-1轮完全背包
int ans = m;
int start = m;
for (int l = 1; l <= t - 1;l++){
  vector<int> dp(start + 1,0);
  for (int i = 1; i <= start; i++) {
    //枚举容量
    for (int j = 1; j <= n; j++) {
      //枚举物品
      if (arr[l][j]<=i){
          dp[i] = max(dp[i], dp[i - arr[l][j]] + arr[l + 1][j]-arr[l][j]);
      }
    }
  }
  start += dp[start];
  if(l==t-1)
      ans = start;
}
cout << ans;
}