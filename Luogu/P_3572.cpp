#include <bits/stdc++.h>

using namespace std;

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
//高度大于等于当前树，则劳累值加1
int n;//树量
int q;//鸟量
vector<int> arr;
vector<int> k;
vector<int> dp;//当前鸟到i树时的最小劳累值
int ans;
signed main() {
    cin >> n;
    arr.resize(n+1);
    dp.resize(n + 1,INT_MAX);
    dp[0] = 0;
    dp[1] = 0;
    for (int i = 1; i <= n;i++){
        arr[i] = read();
    }
    cin >> q;
    k.resize(q + 1);
    for (int i = 1; i <= q;i++){
        k[i] = read();
    }
//------------
    deque<int> de;//单调递增
    for (int i = 1; i <= q;i++){
        int dx = k[i];
        de.push_back(1);
        for (int j = 2; j <= n;j++){
            //保证队列中的都能跳到目前的树
            while(!de.empty()&&de.front()+dx<j){
                de.pop_front();
            }
            int from = de.front();
            int temp=0;
            if(arr[from]<=arr[j]){
                temp = 1;
            }
            dp[j] = dp[from] + temp;
            //问题在于如何确保队首为最佳选择呢
            //1.dp最小
            //2.dp相等的，高度高的
            while(!de.empty()&&dp[de.back()]>dp[j]){
                de.pop_back();
            }
            while(!de.empty()&&dp[de.back()]==dp[j]&&arr[de.back()]<arr[j]){
                de.pop_back();
            }
            de.push_back(j);
        }
        cout << dp[n] << endl;
        dp.clear();
        de.clear();
    }

}