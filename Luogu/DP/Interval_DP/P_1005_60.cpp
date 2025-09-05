//题目要使用高精度，懒得粘板子
//以下是60分代码
#include <bits/stdc++.h>
//有点像奶牛的问题
//貌似只需对每一行单独求最大值再相加就行了
using namespace std;
#define int long long
int n;//n行
int m;//m列

signed main() {
cin>>n>>m;
vector<vector<int>> arr(n + 1, vector<int>(m + 1));
for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
        cin >> arr[i][j];
    }
}
//以上为输入
int ans=0;

//初始化，不知道0行不行 行的
for(int z=1;z<=n;z++){
  vector<vector<int>> dp(m + 1, vector<int>(m + 1, 0));
  for (int j = 1; j <= m; j++) {
    dp[j][j] = arr[z][j] * (1LL<<m);
  }
  for (int i = 2; i <= m; i++) {
    //枚举长度
    for (int j = 1; j <= m-i+1; j++) {
      //枚举左端点
      
        dp[j][j + i - 1] =
            max(dp[j + 1][j + i - 1] + arr[z][j] * (1LL<<(m-i+1)),
                dp[j][j + i - 2] + arr[z][j + i - 1] * (1LL<<(m-i+1)));
      
    }
  }
  ans+= dp[1][m];
}

cout << ans;

}