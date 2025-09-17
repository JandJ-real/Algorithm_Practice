#include <bits/stdc++.h>

using namespace std;
#define int long long
inline int read() {
  int x = 0, f = 1;      // x: 存储结果, f: 符号标志(1正数, -1负数)
  char ch = getchar();   // 读取第一个字符
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
int n;           //格子数量
vector<int> arr; //要往回走的格子数
vector<int> k;   //最多往前跳多少格
vector<int> dp;  //到达某个格子最少需要几步
signed main() {
  cin >> n;
  arr.resize(n + 1);
  k.resize(n + 1);
  dp.resize(n + 1, INT_MAX);
  dp[1] = 0;
  int temp;
  for (int i = 1; i <= n; i++) {
    temp = read();
    arr[i] = i - temp;
  }
  for (int i = 1; i <= n; i++) {
    temp = read();
    k[i] = min(n, i + temp);
  }
  //以上为输入


  int r=1;//记录当前已经覆盖的范围
  for (int i = 1; i <= n;i++){
    //枚举到达每一个格子所面临的情况
if(dp[i]==INT_MAX)
    continue;//不可达到，跳过
    
int l = i + 1;
int ri = k[i];
for (int j = max(l, r); j <= ri;j++){
    int pos = arr[j];
    dp[pos] = min(dp[pos], dp[i] + 1);
    r = max(r, pos); 
}

  }
  if(dp[n]==INT_MAX)
  cout << -1 << endl;
  else{
      cout << dp[n] << endl;
  }
}