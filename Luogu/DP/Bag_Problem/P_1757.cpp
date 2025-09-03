#include <bits/stdc++.h>
//分组背包(记板子)
//背包问题，给的几个参数不要搞混！！！！
using namespace std;
int n;//物品数
int m;//最大承重
signed main() {
//关键是要分组存储
cin>>m>>n;
vector<int> w(n+1);
vector<int> v(n + 1);
vector<int> z(n + 1,0);//第几组物品有几个
vector<vector<int>> q(n + 1, vector<int>(n + 1));//某一组的第几个物品是第几号
int temp;//存储编号
int totalz = 0;
for (int i = 1; i <= n;i++){
    cin >> w[i] >> v[i] >> temp;
    totalz = max(totalz, temp);
    z[temp]++;
    q[temp][z[temp]] = i;
}

//以上是输入
vector<int> dp(m+1);
for (int i = 1;i<=totalz;i++){//枚举每一组
    for (int j = m; j >= 0;j--){//枚举容量
        for (int t = 1; t <= z[i];t++){//枚举该组中每一个物品
            int num = q[i][t];
            if (j - w[num] >= 0)
            {
              dp[j] = max(dp[j - w[num]] + v[num], dp[j]);
            }
        }
    }
}
//分析：每一个容量把该组中的所有物品都筛选了一遍并且保证只选取其中的一个
cout << dp[m];
}