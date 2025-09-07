#include <bits/stdc++.h>
using namespace std;
//多重背包？ 并非
//顺序其实不重要
//这种动态规划求方案数的很看重初始化
#define int long long

int n; // n种花
int m; //共m盆
int MOD = 1e6 + 7;
signed main() {
  cin >> n >> m;
  vector<int> arr(n + 1); //每种花最多几盆
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
  }
  vector<int> prefix(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    prefix[i] = prefix[i - 1] + arr[i];
  }
  vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0)); //前i种 和为j 有几种方案
  dp[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    //枚举花的种类
    for (int j = 0; j <= min(prefix[i], m); j++) 
    {//j从0开始而不是从1开始，保证初始化完全
      for (int k = 0; k <= min(arr[i], j); k++) {//k也可以取0
        dp[i][j] =(dp[i][j] + dp[i - 1][j - k])%MOD;
      }
    }
  }

  cout << (dp[n][m] % MOD);
}