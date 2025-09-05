//先写个40分代码
//另外60分数据规模大，需要用四边形不等式优化
#include <bits/stdc++.h>
//给出的分类是区间dp，但是感觉更像是背包问题
using namespace std;
int v;//村庄的数量
int p;//邮件的数量
int main() {
cin>>v>>p;
vector<int> arr(v+1);
for(int i=1;i<=v;i++){
    cin >> arr[i];
}
sort(arr.begin(), arr.end());
//以上为输入
if(v==p)
    cout << 0;
//打表i~j放一个的最小值
vector<vector<int>> w(v + 1, vector<int>(v + 1, 0));
for (int i = 1; i <= v; i++)
{
    for(int j=i;j<=v;j++){
        int mid = (i + j) / 2;
        for (int z = i; z <= j;z++){
            w[i][j] += abs(arr[mid]- arr[z]);
        }
    }
}
//前i个村庄放j个邮局的最小值
vector<vector<int>> dp(v + 1, vector<int>(p + 1, INT_MAX));
for (int i = 1;i<=v;i++){
    //初始化，一个邮局的情况
    dp[i][1] = w[1][i];
}
for (int i = 2;i<=v;i++){
    //前i个村庄
    for(int j=2;j<=i&&j<=p;j++){
        //放j个邮局
        //状态转移 为什么呢？？？
        for(int k=j-1;k<=i-1;k++){
            //意思是分为两部分，前一部分放j-1个邮局，后一部分放一个邮局，但是为什么呢
            dp[i][j] = min(dp[i][j], dp[k][j - 1] + w[k + 1][i]);
        }
        //似懂非懂，记就对了，板子题
        
    }
}
cout << dp[v][p];
}
