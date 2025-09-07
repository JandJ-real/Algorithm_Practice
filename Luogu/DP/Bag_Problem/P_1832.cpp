#include <bits/stdc++.h>
//为什么可以用类似完全背包的方法
//ans:回到完全背包问题的本质，本质就是列举了所有状态转移的情况，只需把原来更新最值的步骤换为记录方案数量就行了，值得注意的是初始化上的不同
using namespace std;
#define int long long
//筛法求1000以内的素数
vector<int> primes;        // 存储素数
vector<bool> isPrimeTable; // 标记是否是素数
int maxN = 0;              // 当前筛法的最大范围

/**
 * 初始化素数表
 * @param n: 筛法范围[2, n]
 */
void initPrimes(int n) {
  if (n <= maxN)
    return; // 已经初始化过更大的范围

  maxN = n;
  isPrimeTable.assign(n + 1, true);
  isPrimeTable[0] = isPrimeTable[1] = false;
  primes.clear();

  // 埃氏筛法
  for (int i = 2; i <= n; i++) {
    if (isPrimeTable[i]) {
      primes.push_back(i);
      for (int j = i * i; j <= n; j += i) {
        isPrimeTable[j] = false;
      }
    }
  }
}
// dp[i]表示 表示i有几种
int n;
signed main() {
  initPrimes(1000);
  cin >> n;
  //完全背包 好像不太一样
  vector<int> dp(n + 1, 0);
  dp[0] = 1;
  dp[1] = 0;
  for (int j = 2;j<=n;j++)
{
    if (isPrimeTable[j])
      for (int i = j; i <= n; i++)
          dp[i] += dp[i - j];
  }

  /*
  2 0,2 1,1
  3 0,3 1,2
  4 0,4 1,3 2,2
  6 0，6   1，5   2，4  3，3   2
  7 0，7   1，6   2，5    3  ，4    3
  8 0，8    1，7     2，6  3，5   4，4
  */
  cout << dp[n];
}