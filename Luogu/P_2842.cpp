#include <bits/stdc++.h>
//这就是完全背包啊，为什么想不到呢
using namespace std;
//1.long long
//2.本身无法达到则剪枝
//#define int long long
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
int w;//凑出w价值
int n;//纸币种类数
int arr[10005];
vector<int> dp;//INT_MAX表示凑不出
signed main() {
    cin >> n >> w;
   
    dp.resize(w + 1,INT_MAX);
    dp[0] = 0;
    int temp;
    for (int i = 0; i < n;i++){
        temp = read();
        arr[temp] = 1;
    }
   
    //以上为输入
    for (int i = 0; i < w;i++){
        if(dp[i]==INT_MAX)
            continue;//无法到达则跳过
        for (int j = i + 1; j <= w;j++){
if(arr[j-i]){
    dp[j] = min(dp[j], dp[i]+1);
    /*
    此处debug的过程十分有趣
    要么long long 要么加上剪枝
    否则dp[i]+1会越界
    */
    //有必要吗
    //dp[j] = dp[i] + 1;
}
        }
    }
    cout << dp[w];
}