#include <bits/stdc++.h>
//sliding window
//对sliding window 的运用太死板了 
using namespace std;
//1.有些不可到达的位置记为INT_MIN
#define int long long
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
int n;//0~n
int l, r;//下一步范围
vector<int> arr;
vector<int> dp;//在i格子的最大值
vector<int> visited;
int ans = INT_MIN;
signed main() {
    cin >> n;
    cin >> l >> r;
    arr.resize(n + 1);
    visited.resize(n + 1,0);
    dp.resize(n + 1,INT_MIN);
    for (int i = 0; i <= n;i++){
        arr[i] = read();
    }
    dp[0] = 0;
//sliding window维护r-l长度的最大值
//维护单调递减的队列
//问题：维护的长度不是当前格子想要的长度
    deque<int> de;
    
    for (int i = l; i <= n;i++){
        int last=i-l;//最新的能到达i的元素(有效元素)
        //维护队列的完整性和单调性
        while(!de.empty()&&dp[de.back()]<dp[last]){
            de.pop_back();
        }
        //if(dp[last]!=INT_MIN)
        de.push_back(last);
        //维护队列对当前元素的可达性
        while(de.front()+r<i){
            de.pop_front();
        }
        dp[i] = dp[de.front()] + arr[i];
    }

        for (int i = r; i >= 1; i--) {
            ans = max(ans, dp[n + 1 - i]);
        }
        cout << ans;
}