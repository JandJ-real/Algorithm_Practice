#include <bits/stdc++.h>
using namespace std;
//只建一个医院，鉴定为邮局简化版 并非
//树的问题可以用图解决？
//看题解说是树的重心

/*
树的重心的定义：
树若以某点为根，使得该树最大子树的结点数最小，那么这个点则为该树的重心，一棵树可能有多个重心。

树的重心的性质：
1、树上所有的点到树的重心的距离之和是最短的，如果有多个重心，那么总距离相等。

2、插入或删除一个点，树的重心的位置最多移动一个单位。

3、若添加一条边连接2棵树，那么新树的重心一定在原来两棵树的重心的路径上。*/

//弗洛伊德算法可以优化到o(n2) 而找树的重心是o(n)

#define int long long
int n;
int ans = INT_MAX;


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
    cin >> n;
    vector<int> arr(n + 1);
    vector<vector<int>> g(n + 1);
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 100)); //记录距离
    int a, b;
    for(int i=1;i<=n;i++){
      arr[i] = read();
      a = read();
      b = read();
      dp[i][i] = 0;
      if (a)
      {
        g[i].push_back(a);
        g[a].push_back(i);
        dp[i][a] = 1;
        dp[a][i] = 1;
      }
        if (b) {
          g[i].push_back(b);
          g[b].push_back(i);
          dp[i][b] = 1;
          dp[b][i] = 1;
        }
    }
    //以上为输入 顺便初始化dp数组
  
  
//弗洛伊德
for(int i=1;i<=n;i++){
  for(int j=1;j<=n;j++){
    for(int k=1;k<=n;k++){
      if(dp[i][j]&&dp[j][k]){
        dp[i][k] = min(dp[i][k], dp[i][j] + dp[j][k]);
      }
    }
  }
}
/*for(int i=1;i<=n;i++){
  for(int j=1;j<=n;j++){
    cout << dp[i][j]<<' ';
  }
  cout << endl;
}*/

int temp=0;
for(int i=1;i<=n;i++){
  for(int j=1;j<=n;j++){
    temp += dp[i][j]*arr[j];
  }
  ans = min(temp, ans);
  temp = 0;
}
cout << ans;
}