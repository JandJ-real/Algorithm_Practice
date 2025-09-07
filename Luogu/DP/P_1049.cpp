#include <bits/stdc++.h>
//写的时候感觉有点诡异，因为价值和重量是一样的
using namespace std;
int v;//箱子容量
int n;//物品总数
signed main() {
cin>>v>>n;
vector<int> arr(n+1);//物品体积
for(int i=1;i<=n;i++){
    cin >> arr[i];
}
vector<int> dp(v + 1,0);
for(int i=1;i<=n;i++){
    for (int j = v; j >= arr[i];j--){
        dp[j] = max(dp[j],dp[j - arr[i]] + arr[i]);
    }
}
cout << v - dp[v];
}