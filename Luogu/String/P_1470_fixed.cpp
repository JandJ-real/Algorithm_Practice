#include <bits/stdc++.h>
using namespace std;
#define int long long

// dp[i]的充要条件是存在一个比i小的j使得dp[j]为真并且j+1到i属于集合P
set<string> p;
int num = 0;

// 判断字符串a是否在集合p中
int judge(string a) {
  if(p.find(a)!=p.end()){
      return 1;
  }
  return 0;
}

signed main() {
  string temp;
  cin >> temp;
  
  // 读取集合P中的所有元素，直到遇到"."
  do {
    p.insert(temp);
    num++;
    cin >> temp;
  } while (temp != ".");
  
  getchar(); // 消除"."后的换行符，这个是必要的
  
  // 以上为集合P的输入
  string s;
  string a;
  
  // 修复1: 读取序列S的逻辑
  // 原代码问题：使用了额外的getchar()可能会丢失序列S的第一个字符
  // 修复：去掉多余的getchar()，因为getline已经正确处理了换行符
  while (getline(cin, a)) {
    s += a;
    // 如果当前行长度小于60，说明这是最后一行（题目说每76个字符换行）
    if (a.length() < 60) {
      break;
    }
  } 
  // 删除了原来的 getchar(); 这行代码会导致丢失序列S的第一个字符
  
  int n = s.length();
  
  // 修复2: 动态规划数组初始化和算法逻辑
  // dp[i]表示字符串s的前i个字符是否可以被集合P中的元素完全分解
  vector<int> dp(n + 1, 0);
  dp[0] = 1; // 空串可以被分解（边界条件）
  
  // 动态规划主循环
  for (int i = 0; i < n; i++) {
    if (dp[i]) { // 如果前i个字符可以被分解
      // 尝试所有可能的下一个子串
      for (int j = i + 1; j <= n; j++) {
        string str = s.substr(i, j - i); // 取子串s[i...j-1]
        
        if (judge(str)) { // 如果这个子串在集合P中
          dp[j] = 1; // 标记前j个字符可以被分解
        }
      }
    }
  }
  
  // 修复3: 输出逻辑
  // 从后往前找到最大的能被完全分解的前缀长度
  for (int i = n; i >= 0; i--) {
    if (dp[i]) {
      cout << i << endl;
      return 0;
    }
  }
  
  return 0;
}