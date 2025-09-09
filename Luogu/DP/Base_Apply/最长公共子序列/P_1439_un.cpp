#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;
signed main() {
cin>>n;
vector<int> a(n+1);
vector<int> b(n+1);
vector<int> mapp(n + 1);
for(int i=1;i<=n;i++){
    scanf("%lld", &a[i]);
    
}
for (int i = 1; i <= n; i++) {
  scanf("%lld", &b[i]);
mapp[b[i]] = i;}
  //用滚动数组优化
  vector<vector<int>> dp(2, vector<int>(n + 1, 0));
  int t = 1;
  for (int i = 1; i <= n; i++) {
    int num = mapp[a[i]];
    for(int j=1;j<=n;j++){
        
        if(num==j)
        {
            dp[t][j] = dp[1-t][j - 1] + 1;
        }
        else{
            dp[t][j] = max(dp[1-t][j], dp[t][j - 1]);
        }
    }
    t = 1 - t;
}
cout << dp[1-t][n];
 }