#include <bits/stdc++.h>
//二维0-1背包
using namespace std;
int n, m, t; //愿望数，金钱，时间

//行不通的原因：这个遍历逻辑(即深搜的逻辑)有可能重复实现同一个愿望

/*
void dfs(int i, int j, int q,vector<vector<int>>& dp) {
  dp[j][q] = max(dp[j - a[i]][q - b[i]]+1, dp[j][q]);
  if (j - 1 >= a[i])
      dfs(i, j - 1, q,dp);
  if (q - 1 >= b[i])
    dfs(i, j , q-1,dp);
  return;
}*/
signed main() {
  cin >> n >> m >> t;
  vector<int> a(n + 1); //花费金钱
  vector<int> b(n + 1); //花费时间
  for (int i = 1; i <= n; i++) {
    cin >> a[i] >> b[i];
  }

  //以上为输入
  vector<vector<int>> dp(
      m + 1, vector<int>(t + 1, 0)); //花费某金钱某时间最多实现愿望数

  for (int i = 1; i <= n; i++) {
    //枚举愿望
    //这个逻辑是从下往上一行一行的搜，所以不会重复
    for (int j = m; j >= a[i]; j--) {
      for (int q = t; q >= b[i]; q--) {
        dp[j][q] = max(dp[j - a[i]][q - b[i]] + 1, dp[j][q]);
      }
    }
  }

  cout << dp[m][t];
}