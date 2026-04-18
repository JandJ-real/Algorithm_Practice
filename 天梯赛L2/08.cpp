#include <bits/stdc++.h>
using namespace std;
#define int long long
//这是字符串长度<1000的暴力枚举，有无优化？
/*
● #include <bits/stdc++.h>
  using namespace std;
  #define int long long

  string str;
  int ans = 1;

  signed main() {
      getline(cin, str);

      // 构造变换串: "abc" → "#a#b#c#"
      // 统一处理奇偶长度回文，消除分类讨论
      string t = "#";
      for (char c : str) {
          t += c;
          t += '#';
      }

      int n = t.size();
      vector<int> p(n, 0); // p[i]: 变换串中以 i 为中心的回文半径
      int c = 0, r = 0;    // 已知最右回文的中心 c 和右边界 r

      for (int i = 0; i < n; i++) {
          // 利用对称性：i 在当前最右回文内部时，直接借用镜像位置的结果
          if (i < r) {
              p[i] = min(r - i, p[2 * c - i]);
          }
          // 在已知基础上继续向外扩展
          while (i - p[i] - 1 >= 0 && i + p[i] + 1 < n
                 && t[i - p[i] - 1] == t[i + p[i] + 1]) {
              p[i]++;
          }
          // 更新最右回文边界
          if (i + p[i] > r) {
              c = i;
              r = i + p[i];
          }
          ans = max(ans, p[i]);
      }

      cout << ans;
      return 0;
  }

  ---
  核心思路

  变换串的作用："aba" → "#a#b#a#"，把奇偶长度回文统一为奇长度，p[i]
的值恰好等于原串中该回文的长度。

  O(n) 的关键：维护"当前已知的最右回文"（中心 c，右边界 r）。当 i < r 时，i 关于
c 的镜像 mirror = 2c - i 已经计算过，直接复用：

  |<----  p[c]  ---->|
  c-p[c]   mirror   c   i   r
             |<-p[mirror]->|

  - 若 p[mirror] < r - i：p[i] = p[mirror]，无需扩展
  - 若 p[mirror] >= r - i：p[i] 至少为 r - i，再从边界继续扩展

  每个字符最多被扩展一次，总复杂度 O(n)。
*/
// getline(cin,str)  读入整行字符串
string str;
int ans=1;//关键bug，没有显示回文串就是单个字符回文串，即1
signed main() {
    getline(cin,str);//@@@@@@@@@@
    //cin >> str;
    string str1 = str;
    for (int i = 0; i < (int)str.length()-1; i++) {
        for (int j = i + 1; j < (int)str.length(); j++) {
            reverse(str.begin() + i, str.begin() + j + 1);
            //cout << str << endl;
            int k;
            for (k = i; k <= j; k++) {
                if (str[k] != str1[k]) {
                    break;
                }
            }
            if (k == j + 1) {
                ans = max(ans, j - i + 1);
            }
            reverse(str.begin() + i, str.begin() + j + 1);
        }
    }
    cout << ans;
    return 0;
}