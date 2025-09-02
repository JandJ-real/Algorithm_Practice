#include <bits/stdc++.h>
//为何看起来很暴力但是没有tle？？
using namespace std;
int n;//行数
int main() {
cin>>n;
vector<vector<int>> dp(n + 1, vector<int>(n + 1)); //到每行最大和
//初始化
int temp;
cin >> temp;
dp[1][1] = temp;
for (int i = 2;i<=n;i++){
    //枚举层数
    for (int j = 1; j <= i;j++){
        //枚举该层的每个点
        cin >> temp;
        if(j>i-1){
            dp[i][j] = dp[i - 1][j - 1]+temp;
        }
        else if(j-1<=0){
            dp[i][j] = dp[i - 1][j] + temp;
        }
        else{
            dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j]) + temp;
        }
    }
}
int m=0;
for(int i=1;i<=n;i++){
    m = max(m, dp[n][i]);
}
cout << m;
}