#include <bits/stdc++.h>

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
int ans = INT_MIN;
signed main() {
    cin >> n;
    cin >> l >> r;
    arr.resize(n + 1);
    dp.resize(n + 1,INT_MIN);
    for (int i = 0; i <= n;i++){
        arr[i] = read();
    }
    dp[0] = 0;
//sliding window维护r-l长度的最小值？
    deque<int> de;
    int dist = r - l+1;
    de.push_back(0);
    
    for (int i = l; i <= n;i++){
        if(i<=l+r){
    for (int j = l; j <= r;j++){
            int last = i - j;
            if(last<0){
                break;
            }
            if(dp[last]==INT_MIN)
                continue;
            dp[i] = max(dp[i], dp[last] + arr[i]);
        }
        //count++;
        while(!de.empty()&&dp[de.back()]<dp[i]){
            de.pop_back();
        }
        de.push_back(i);
        while(!de.empty()&&de.back()-de.front()>=dist){
            de.pop_front();
        }
        }
        else{
            dp[i] = max(dp[i], dp[de.front()] + arr[i]);
             while(!de.empty()&&dp[de.back()]<dp[i]){
            de.pop_back();
        }
        de.push_back(i);
        while(!de.empty()&&de.back()-de.front()>=dist){
            de.pop_front();
        }
        }
        }
    
    
    for (int i = r; i >= 1;i--){
        ans = max(ans, dp[n + 1 - i]);
    }
        cout << ans;
}