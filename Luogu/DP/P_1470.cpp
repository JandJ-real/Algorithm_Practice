#include <bits/stdc++.h>
using namespace std;
#define int long long
// dp[i]的充要条件是存在一个比i小的j使得dp[j]为真并且j+1到i属于集合P
set<string> p;
int num = 0;
//可以用set存储，二分查找提高匹配速度 或find函数
int judge(string a) {
  if(p.find(a)!=p.end()){
      return 1;
  }
  return 0;
}

signed main() {
  string temp;
  cin >> temp;
  // cout << "temp:" << temp << endl;
  do {
    p.insert(temp);
    num++;
    cin >> temp;
  } while (temp != ".");
  // cout << temp << endl;
  getchar(); //消除.后的换行符
  // 以上为集合P的输入
  string s;
  string a;
  while (getline(cin, a)) {
    // cout << "a:" << a << endl;
    // cout << a.size();
    if (a.empty()) {
      break;
    }
    s += a;

    
  } 
  
  // cout << "s:" << s << endl;
  // s
  int n = s.length();
  // cout << "n:" << n;
  vector<int> dp(n + 1, 0); // 0或1判断是否符合，索引为1-12
  dp[0] = 1;                //默认符合
  // cout << "num:" << num << endl;
  for (int i = 0; i < n; i++) {
    if (dp[i]) {
      for (int j = i + 1; j <= n; j++) {
        
        if(j-i>10)
          break;//P中元素长度不超过10
        string str = s.substr(i, j - i);
        // cout << "str:" << str << endl;
        if (judge(str)) {
          // cout << str << ' ' << "in" << endl;
          dp[j] = 1;
        }
      }
    }
  }
  for (int i = n; i >= 0; i--) {
    if (dp[i]) {
      cout<<i<<endl;
      return 0;
    }
  }
}