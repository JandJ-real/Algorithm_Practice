//还可用单调队列优化
//状态转移方程难懂
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;//人数
int m;//最大人数差
int ans = 0;
vector<int> arr;
/*void f(int start){
  int l = 0;
  int r = 0;
  for (int i = start; i < n; i++) {
    if (arr[i] == 1) {
      l++;
    } else {
      r++;
    }
    if (abs(l - r) > m && l && r) {
      ans++;
      f(i);
      return;
    }
  }}*/

signed main() {
cin>>n>>m;
arr.resize(n+1,0) ;
//cout << arr[0];
for(int i=1;i<=n;i++){
    cin >> arr[i];
    if(arr[i]==2){
        arr[i] = -1;
    }
}
//前缀和
vector<int> prefix(n + 1,arr[1]);
prefix[0] = 0;
for(int i=2;i<=n;i++){
    prefix[i] = prefix[i - 1] + arr[i];
}
vector<int> dp(n+1,INT_MAX);

dp[1] = 1;
dp[0] = 0;
for (int i = 2;i<=n;i++){
    //前i个人的最小房间数
    for (int j =i- 1;j>=1;j--){
        //1~i-1作为分割线的后一个元素
        int num = abs(prefix[i] -
                      prefix[j - 1]);
                      //计算j~i的和
        if (num <= m ||num==i-j+1){
            //如果和满足单独一个房间的条件
            dp[i] = min(dp[i], dp[j-1] + 1);
        }
    }
}
cout << dp[n];
}
