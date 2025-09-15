#include <bits/stdc++.h>
//有依赖的背包
//感觉可以类似分组背包，只是在枚举每个物品时还需按主件和附件分类
using namespace std;
//价格与重要度的乘积的总和最大
#define int long long
int n, m;//总钱数，物品个数

signed main() {
cin>>n>>m;
vector<int> w(m+1);//物品价格
vector<int> v(m + 1);//物品重要度
vector<int> mode(m + 1);//分组信息
//int temp;//暂存主附件信息
vector<int> z(m + 1,0);//存储每一组有多少个，便于枚举
vector<vector<int>> t(m + 1, vector<int>(m + 1));//某组某个是第几号
int cur = 0;//存储现在有几组
for (int i = 1;i<=m;i++){
    cin >> w[i] >> v[i] >> mode[i];
}
for(int i=1;i<=m;i++){
    if(!mode[i]){
        //主件
        cur++;
        z[cur]++;
        t[cur][1] = i;
    }
}
for(int i=1;i<=m;i++){
    if(mode[i]){
      for (int j = 1; j <= cur; j++) {
        if(t[j][1]==mode[i]){
            z[j]++;
            t[j][z[j]] = i;
        }
      }
    }
} 

//会不会附件出现在主件前面？？  已解决
//以上为输入

//分组背包板子
vector<int> dp(n+1,0);
for (int i = 1; i <= cur;i++){
    //枚举每一组
    int num = t[i][1];
    int sum_1 = w[num];
    int xsum_1 = v[num] * w[num];
    for (int j = n; j >= sum_1; j--)
    {
        // 枚举容量
        dp[j] = max(dp[j - sum_1] + xsum_1, dp[j]);
        //列举附件的所有组合 2~z[i]
        vector<int> dpsum(4, sum_1);//初始化时都先选主件 0-based
        vector<int> dpxsum(4, xsum_1); //初始化时都先选主件 0-based
        int s = 0;//当前遍历过的方案数

        for (int q = 2; q <= z[i]; q++) {
          //枚举该组中的每一个物品
          int temp = s;//暂存，便于遍历
          for (int e = 0; e <= temp; e++) {
            //加到之前的每一个方案中
            s++;
            dpsum[s]=dpsum[e]+w[t[i][q]];
            dpxsum[s] = dpxsum[e] + w[t[i][q]] * v[t[i][q]];
            if(j>=dpsum[s]){
                dp[j] = max(dp[j - dpsum[s]] + dpxsum[s], dp[j]);
            }
        }
}
    }
}
//通过位运算列举组合的办法

/*// 收集所有附件的重量和价值
vector<int> attach_weights, attach_values;
for (int j = 1; j < group_size[i]; j++) {
  int item = groups[i][j];
  attach_weights.push_back(w[item]);
  attach_values.push_back(w[item] * v[item]);
}

// 容量从大到小遍历（01背包防止重复选择）
for (int j = n; j >= main_weight; j--) {
  // 方案1：只选择主件
  dp[j] = max(dp[j], dp[j - main_weight] + main_value);

  // 生成所有可能的附件组合（2^attach_count种）
  // 用位运算枚举所有子集
  for (int mask = 1; mask < (1 << attach_count); mask++) {
    int total_weight = main_weight;
    int total_value = main_value;

    // 计算当前组合的总重量和总价值
    for (int k = 0; k < attach_count; k++) {
      if (mask & (1 << k)) {
        total_weight += attach_weights[k];
        total_value += attach_values[k];
      }
    }

    // 如果容量足够，更新dp
    if (j >= total_weight) {
      dp[j] = max(dp[j], dp[j - total_weight] + total_value);
    }
  }
}
    }
    }
}*/




cout << dp[n];
}