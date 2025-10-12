#include <bits/stdc++.h>
//两个维度的dp，不同情况的状态转移
//想不到的点在哪
//管你在哪
//做个总方案数量的专题：点菜，纸币
using namespace std;

inline int read() {
  int x = 0, f = 1;    // x: 存储结果, f: 符号标志(1正数, -1负数)
  char ch = getchar(); // 读取第一个字符

  while (!isdigit(ch)) { // 跳过非数字字符
    if (ch == '-')
      f = -1;       // 遇到负号，设置符号为负
    ch = getchar(); // 继续读取下一个字符
  }

  while (isdigit(ch)) {    // 处理数字部分
    x = x * 10 + ch - '0'; // 将字符转换为数字并累加
    ch = getchar();        // 读取下一个字符
  }

  return x * f; // 返回结果（考虑符号）
}
int n;//菜品种类
int m;//凑的钱数
vector<int> arr;
//刚好花完的方案数
//每种只能点一个
vector<vector<int>> dp;//表示前i个菜花光j元钱的方案有几种
signed main() {
    cin >> n >> m;
    arr.resize(n+1);
    dp.resize(n+1);
    for (int i = 1; i <= n;i++){
        arr[i] = read();
        dp[i].resize(m + 1,0);
        dp[i][0] = 1;
    }
    dp[0].resize(m + 1, 0);
    dp[0][0] = 1;

    //先枚举菜，再枚举钱，保证每个菜只发挥了一次作用
    for (int i = 1; i <= n;i++){
        for (int j = 1; j <= m;j++){
            //三种不同情况的状态转移
            if(j-arr[i]==0)
                dp[i][j] = dp[i - 1][j]+1;
            else if(j-arr[i]>0){
                dp[i][j] = dp[i - 1][j - arr[i]]+dp[i-1][j];
            }
            else{
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    cout << dp[n][m];
}