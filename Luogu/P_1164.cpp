#include <bits/stdc++.h>
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
    arr.resize(n);
    for (int i = 0; i < n;i++){
        arr[i] = read();
    }
for
}