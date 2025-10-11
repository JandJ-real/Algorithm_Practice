#include <bits/stdc++.h>
//说组合，组合到
//好好研究这个问题：循环顺序决定排列与组合
/*
重要的是顺序
排列是有币的空间就加
组合是有特定币的空间就加，而且这个币还是不重复的，做到不可能前面因为这个币加了，后面又因为这个币加
*/
using namespace std;
#define int long long
int MOD = 1e9 + 7;
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
int n, w;
vector<int> arr;
vector<int> dp;
signed main() {
    cin >> n >> w;
    arr.resize(n);
    dp.resize(w + 1);
    dp[0] = 1;
    for (int i = 0; i < n;i++){
        arr[i] = read();
    }
    for (int i = 0; i < n;i++){
        for (int j = 1; j <= w;j++){
            int last = j - arr[i];
            if(last>=0){
                dp[j] += (dp[last] % MOD);
                dp[j] %= MOD;
            }
        }
    }
    cout << dp[w];
}