//区间dp
//带权？？
#include <bits/stdc++.h>
//依然求最值
using namespace std;
int n;//物品个数
int main() {
cin>>n;
vector<int> arr(n+1,0);//凑数 1~n
for(int i=1;i<=n;i++){
    cin >> arr[i];
}
vector<vector<int>> dp(n + 1, vector<int>(n + 1));//表示该区间最大贡献
for(int i=1;i<=n;i++){
    dp[i][i] = arr[i] * n;
}
//迭代到1~n最大贡献即为所得
for (int i = 2;i<=n;i++){
    //遍历区间长
    for(int j=1;j<=n;j++){
        //遍历左起点
        int l=j;
        int r=j+i-1;
        if(r>n){
            break;//确保不越界
        }
        //取相邻最大值，只因由内向外是连续的天数
        dp[l][r] = max(dp[l + 1][r] + arr[l] * (n - i + 1), dp[l][r-1] + arr[r] * (n - i + 1));
    }
}
cout << dp[1][n];
}
