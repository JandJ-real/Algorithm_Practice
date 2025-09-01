#include <bits/stdc++.h>

using namespace std;
int n;//苹果总数
int m;//能吃苹果范围
int main() {
 cin>>n>>m;
 vector<int> value(m+1);
 for(int i=1;i<=m;i++){
     cin >> value[i];
 }
 //以上为输入
 vector<int> dp(n+1,0);//总数为0~n的最优解(初始化为0？)
 for(int i=1;i<m;i++){
    //选出每一个苹果
    for (int j = i;j<=n;j++){
        dp[j] = max(dp[j], dp[j - i] + value[i]);
    }
 }
 cout << dp[n] << endl;
}