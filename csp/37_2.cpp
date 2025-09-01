#include <bits/stdc++.h>
using namespace std;
long long dp[10005], m, a, n;
int main() {
  cin >> n >> m;
  for (int v = 1; v <= m; v++) {
    cin >> a;//遍历每个物品的重量及对应价值
    for (int i = v; i <= n; i++) {//从v到n，保证均有选与不选两种选择（若小于v则不能选了）
      dp[i] = max(dp[i], dp[i - v] + a);
    }
  }
  //最终是为了一步步得到dp[n]
  cout << dp[n];
  return 0;
}
//dp问题（背包问题）可以用数学归纳法来理解
//问题的关键是状态转移方程
//可以收集所有背包问题总结分析