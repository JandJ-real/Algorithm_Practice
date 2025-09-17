#include <bits/stdc++.h>
//只能想到暴力dp
//不能继续优化的原因，其实这样逆过来想是不好想的，失去了可优化的空间

//单调队列优化！！！！！！！！
//我们想找到能跳到当前格子i的所有j中，dp值最小的那个 
//维护一个dp值增大的队列，并随着i的增大淘汰队头跳不到i的元素，保证对于当前i，队头始终是最优的并且有效的

//单调队列简直是放屁，这不是线性的
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
//最少需要跳多少次才能跳到第n个格子？
//明确一点：不能走回头路
int n;//格子数量
vector<int> arr;//要往回走的格子数
vector<int> k;//最多往前跳多少格
vector<int> dp;//到达某个格子最少需要几步
signed main() {
    cin >> n;
    arr.resize(n + 1);
    k.resize(n + 1);
    dp.resize(n + 1,INT_MAX);
    dp[1] = 0;
    int temp;
    for (int i = 1; i <= n;i++){
        temp=read();
        arr[i] = i - temp;
    }
    for (int i = 1; i <= n; i++) {
        temp = read();
        k[i] = min(n, i + temp);
    }
    //以上为输入
    //deque<int> sw;
    //sw.push_back(1);
    int r = 1;
    for (int i = 2; i <= n;i++){
      /*    while(!sw.empty()&&k[sw.front()]<i){
        //淘汰掉到不了i的
        sw.pop_front();
      }
      int befor = arr[i];
      if(!sw.empty())
       dp[befor] = min(dp[befor], dp[sw.front()] + 1);

      while((!sw.empty())&&dp[sw.back()]>=dp[befor]){
        sw.pop_back();
      }
      sw.push_back(befor);*/
      
          // 到达该点后,退回的位置
          int befor = arr[i];
          if (befor >= 1)
          {
            // 确保不越界
            for (int j = 1; j < befor; j++)
            {
              // 在befor前面的点中找能到达i的点，保证不走回头路的同时在不停前进
              if (k[j] >= i)
              {
                dp[befor] = min(dp[befor], dp[j] + 1);
                // r = j;
              }
            }
            r = max(r, befor);
            }
    }
   
    
if(dp[n]==INT_MAX){
    cout << -1;
}
else{
    cout << dp[n];
}
        return 0;
}