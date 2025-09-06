#include <bits/stdc++.h>
//调试的重要性
//方法很明确
using namespace std;
int n; //数字数量
int m; //分为m个部分
int minn = INT_MAX;
int maxn = 0;
signed main() {
  cin >> n >> m;
  vector<int> arr(2 * n);
  int temp;
  for (int i = 0; i < n; i++) {
    cin >> temp;

    arr[i] = arr[i + n] = temp;
  }
  //前缀和
  vector<int> prefix(2 * n + 1, 0);
  for (int i = 1; i <= n * 2; i++) {
    prefix[i] = prefix[i - 1] + arr[i - 1];
  }
  // 1~i之和=prefix[i]-prefix[0]
  /*for (int i = 1; i <= 2 * n;i++){
    for(int j=0;j<=i;j++){
        cout<<j+1<<'~' <<i<<':'<< prefix[i] - prefix[j]<<' ';
    }
  }*/

  // 二维dp

  for (int l = 1; l <= n; l++) {
    int r = l + n - 1;
    // 枚举左右边界
    vector<vector<int>> dp(
        n * 2 + 1, vector<int>(m + 1, INT_MAX)); // 到i分为j个部分，最小值 i>=j

    vector<vector<int>> dp1(n * 2 + 1,
                            vector<int>(m + 1, 0)); // 到i分为j个部分，最大值
                                                    // 初始化
    for (int i = l; i <= r; i++) {

      dp[i][1] = dp1[i][1] = ((prefix[i] - prefix[l - 1]) % 10 + 10) % 10;
    }
  
    /*
    1,1 2,1 2,2 3,1 3,2 3,3
    */
    // 5，3 = 2，2+ 或3，2+或4，2+
    for (int i = l + 1; i <= r; i++) {
      for (int j = 2; j <= min(i - l + 1, m); j++) {
        for (int q = j - 1 + l - 1; q < i; q++) {
            //可以合并
          dp[i][j] =
              min(dp[i][j],
                  dp[q][j - 1] * (((prefix[i] - prefix[q]) % 10 + 10) % 10));
          // q+1~i
          dp1[i][j] =
              max(dp1[i][j],
                  dp1[q][j - 1] * (((prefix[i] - prefix[q]) % 10 + 10) % 10));
        }
      }
    }
    //关键调试，发现状态转移方程少打了一个括号
    /*   for (int i = 1; i <= 2 * n; i++) {
      for (int j = 1; j <= m; j++) {
        cout << dp1[i][j] << ' ';
      }
      cout << endl;
    }*/

    minn = min(minn, dp[r][m]);

    maxn = max(maxn, dp1[r][m]);
  }

  cout << minn << endl;
  cout << maxn;
}