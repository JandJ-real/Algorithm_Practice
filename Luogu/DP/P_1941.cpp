#include <bits/stdc++.h>

using namespace std;
#define int long long
vector<int> up;
vector<int> down;
vector<pair<int, int>> tap;
vector<int> flag;
vector<vector<int>> dp; //到i,j位置时，点几下(1-based)
int ans = INT_MAX;
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
//这一秒的操作在下一秒才生效
//初始位置假定最高？？
int n; //长
int m; //高
int k; //管道数
signed main() {
  n = read();
  m = read();
  k = read();
  up.resize(n + 1);
  down.resize(n + 1);
  flag.resize(n + 1, 0);
  tap.resize(n + 1, {1, m}); //初始化为
  dp.resize(n + 1);

  dp[0].resize(m + 1, 0);
  for (int i = 1; i <= n; i++) {
    dp[i].resize(m + 1, INT_MAX);
    up[i] = read();
    down[i] = read();
  }

  int a;
  int b;
  int c;
  for (int i = 1; i <= k; i++) {
    a = read();
    b = read();
    c = read();
    flag[a] = 1;
    tap[a] = {b + 1, c - 1}; // 应该>=b+1并且<=c-1
  }
  /* for (int i = 0; i <= n;i++){
      cout << tap[i].first << ' ' << tap[i].second << endl;
  }*/

  // 以上为输入
  

  for (int i = 0; i <= n - 1; i++) {
      int ll = tap[i].first;
      int rr = tap[i].second;
      for (int j = ll; j <= rr; j++)
      {
          // 枚举可发位置
          if (dp[i][j] != INT_MAX)
          {
              int l = tap[i + 1].first;
              int r = tap[i + 1].second;
              int num = j - down[i + 1];
              if (num >= l && num <= r)
              {
                  dp[i + 1][num] =
                      min(dp[i + 1][num], dp[i][j]);
              }

              int start=1;//最小点击次数
              if (j < l)
              {
                  start = (l - j + up[i + 1] - 1) / up[i + 1];
              }
              for (int click = start;; click++)
              {
                  int rise_height = j + click * up[i + 1];
                  if (rise_height > m)
                      rise_height = m;

                  if (rise_height < l)
                      continue;
                  if (rise_height > r)
                      break;

                  dp[i + 1][rise_height] = min(dp[i + 1][rise_height], dp[i][j] +
                                                                           click);

                  if (rise_height == m)
                      break;
              } /// 区别在哪？？？？？？？？？？？？？？？？？？？？？？
              // 这一部分实际上是完全背包
              /*int jj = j;
         jj += up[i + 1], jj = min(jj, m);
         int num = 1;
         while (jj >= l && jj <= r) {
           dp[i + 1][jj] = min(dp[i + 1][jj], dp[i][j] + num);
           num++;
           if(jj==m){
               break;
           }
           jj += up[i + 1],jj=min(jj,m);
         }*/
          }
      }
  }

  
  //以下为输出
  for (int i = tap[n].first; i <= tap[n].second; i++) {
    ans = min(ans, dp[n][i]);
  }
  if (ans != INT_MAX)
    cout << 1 << endl << ans;

  else {
    int tapnum = 0;
    for (int i = n - 1; i >= 1; i--) {
      for (int j = tap[i].first; j <= tap[i].second; j++) {
        ans = min(ans, dp[i][j]);
      }

      if (ans != INT_MAX) {
        cout << 0 << endl << k - tapnum;
        return 0;
      }
      if (flag[i]) {
        tapnum++;
      }
    }
  }
}