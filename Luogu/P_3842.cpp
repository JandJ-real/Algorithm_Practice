#include <bits/stdc++.h>
//优化：滚动数组，边输入边计算，预处理每行差值
using namespace std;
#define x first
#define y second
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
int n;
//最终到达(n,n)
//每层有起点与终点
//只要分析线段的相交关系即可，另外记录每一层的起点与终点
//a：下  b：上
//1：a存在端点在b的闭区间中，a只走一遍，b要加上终点到其离a最近端点的距离
//2.
vector<pair<int,int>> arr;
vector<vector<int>> dp;//1表示左端点为终点，0表示右端点为终点   的最小步数
int ans=n-1;
signed main() {
    cin >> n;
    arr.resize(n + 1);
    dp.resize(n + 1);
    for (int i = 1; i <= n;i++){
        arr[i].x = read();
        arr[i].y = read();
        dp[i].resize(2);
    }
    //输入

    dp[1][0] = arr[1].y - 1;
    dp[1][1] = 2 * arr[1].y - 1 - arr [1].x;
    for (int i = 2; i <= n;i++){
        int l = arr[i - 1].x;
        int r = arr[i - 1].y;
        dp[i][1] = min(dp[i - 1][1] + abs(arr[i].y - l) + arr[i].y - arr[i].x, dp[i - 1][0] + abs(r - arr[i].y) + arr[i].y - arr[i].x);
        dp[i][0] = min(dp[i - 1][1] + abs(l - arr[i].x) + arr[i].y - arr[i].x, dp[i - 1][0] + abs(r - arr[i].x) + arr[i].y - arr[i].x);
    }
    dp[n][1] += n - arr[n].x;
    dp[n][0] += n - arr[n].y;
    cout << min(dp[n][1]+n-1, dp[n][0]+n-1);
}