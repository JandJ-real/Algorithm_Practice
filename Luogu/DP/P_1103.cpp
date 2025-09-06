#include <bits/stdc++.h>
//1.要什么就设什么，什么能解决问题就设什么，不要被形式束缚(末尾数字和长度)
//2.不要跟着题目硬模拟，转化为自己熟悉的模型（把拿掉k本转化为选择n-k本）
//拿掉k本，转化为选择n-k本，思路会清晰很多
using namespace std;
int n;
int k;
int m; //实际长度
int ans = INT_MAX;
bool mycompare(pair<int, int> a, pair<int, int> b) {
  if (a.first < b.first) {
    return true;
  } else {
    return false;
  }
}
signed main() {
  cin >> n >> k;
  m = n - k;
  vector<pair<int, int>> arr(n + 1); // 1-based
  for (int i = 1; i <= n; i++) {
    cin >> arr[i].first >> arr[i].second;
  }
  //按高度排序
  sort(arr.begin() + 1, arr.end(), mycompare);
  vector<int> pre(n);
  vector<int> prefix(n, 0); //前缀和
  //二维dp
  vector<vector<int>> dp(
      n + 1,
      vector<int>(m + 1, INT_MAX)); //末尾数字序号为i长度为j的序列的最小值
  // j=1时，均为0
  for (int i = 1; i <= n; i++) {
    dp[i][1] = 0;
  }
  for (int i = 2; i <= m; i++) {
    dp[i][i] = dp[i - 1][i - 1] + abs(arr[i].second - arr[i - 1].second);
  }
  for (int i = 2; i <= n; i++) {
    // 枚举终点
    for (int j = 2; j <= min(i, m); j++) {
      // 枚举长度
      for (int q = j-1; q < i; q++) {
        dp[i][j] = min(dp[i][j],
                       dp[q][j - 1] + abs(arr[i].second - arr[q].second));
      }
    }
  }
  for (int i = n; i >= m; i--) {
    ans = min(ans, dp[i][m]);
  }
  cout << ans;
}