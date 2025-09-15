#include <bits/stdc++.h>
using namespace std;
int n;//单词数量
vector<string> arr;
vector<pair<char, char>> ht;
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

signed main() {
    n = read();
    arr.resize(n + 1);
    ht.resize(n + 1);
    string str;
    for (int i = 1; i <= n;i++){
        cin >> str;
        ht[i].first = str[0];
        ht[i].second = str[str.length() - 1];
        arr[i] = str;
    }
    
}