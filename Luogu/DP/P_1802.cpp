#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;       //好友数
int x;       //药水数量(背包容量)
int sum = 0; //保底经验
signed main() {
  //认为可以通过输来获得经验
  cin >> n >> x;
  if(n==0){
    cout<<0;
    return 0;
  }
  vector<int> v(n + 1); //存储因为赢而多获得的经验
  vector<int> w(n + 1); //赢需要的药水数
  int a;
  int b;
  for (int i = 1; i <= n; i++) {
    cin >> a >> b;
    sum += a;
    v[i] = b - a;
    cin >> w[i];
  }
  //初始化随题目灵活变化
  //不初始化为sum的话会出事
  vector<int> dp(x + 1,sum);
 
  for (int i = 1; i <= n; i++) {
    //枚举物品
    for (int j = x; j >= w[i]; j--) {
      //枚举容量
      dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
    }
  }
  
  cout << dp[x] * 5;
}