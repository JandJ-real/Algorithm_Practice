//做了很久很久很久

//启示：
//1.通过取模来表示环结构时，在每一个+运算后面都要取模(%),达成循环，在每一个-运算后面加n再取模，避免负数，意思是要足够细心
//2.前缀和属于基础思路之后的优化，不必一开始就考虑，反而影响整体思路
//3.多用纸笔手动模拟，尝试多种不同情况
//4.环结构可以用2n数组来模拟，简单不易出错(见pro，同时有四边形不等式优化动态规划)
//5.调试代码记得注释掉！！！！！！
//6.取模的题目中，使用0-based(很重要)
//7.
#include <bits/stdc++.h>
//最小得分
//最大得分
using namespace std;

#define int long long
int n; // n堆石子
signed main() {
cin>>n;
vector<int> arr(n );
for(int i=0;i<n;i++){
    cin >> arr[i];
}
//以上为输入


vector<vector<int>> dp(n,vector<int>(n,0));//max

for (int i = 2; i <= n;i++){
    //枚举长度
    for(int j=0;j<n;j++){
        //枚举左起点
        //此处可以用前缀和优化，但是得用2n数组应该
        int sum=arr[j];//先取出第一个数计算，防止正好绕个圈的情况下，for循环会在一开始就终止
        for (int v = (j+1)%n; v != (j + i)%n; v = (v + 1) % n) {//例如此处，j+1后很容易忘记取模
          sum += arr[v];
        }
        //同上，先将第一个数取出先计算
        dp[j][(j + i - 1) % n] =
            max(dp[j][j] + dp[(j+ 1)%n][(j + i - 1) % n] + sum,
                dp[j][(j + i - 1) % n]);
                //此处注意取模
        for (int v = (j + 1) % n; v != ((j + i -1) % n); v = (v + 1) % n) {
          dp[j][(j + i - 1) % n] =
              max(dp[j][v] + dp[(v + 1)%n][(j + i - 1) % n] + sum,
                  dp[j][(j + i - 1) % n]);
        }
    }
}


//与max类似地
//值得注意的是，除[i][i]位置，其它均要取大数，否则因为取的是最小值，会一直是0；；这应该算初始化要注意的点
vector<vector<int>> dp1(n, vector<int>(n, INT_MAX)); // min
for(int i=0;i<n;i++){
    dp1[i][i] = 0;
}
for (int i = 2; i <= n; i++) {
  //枚举长度
  for (int j = 0; j < n; j++) {
    //枚举左起点
    int sum = arr[j];
    for (int v = (j + 1) % n; v != (j + i) % n; v = (v + 1) % n) {
      sum += arr[v];
    }
    
    dp1[j][(j + i - 1) % n] = min(dp1[j][j] + dp1[(j + 1)%n][(j + i - 1) % n] + sum,
                                  dp1[j][(j + i - 1) % n]);
    for (int v = (j + 1) % n; v != ((j + i-1 ) % n); v = (v + 1) % n) {
      dp1[j][(j + i - 1) % n] =
          min(dp1[j][v] + dp1[(v + 1)%n][(j + i - 1) % n] + sum,
              dp1[j][(j + i - 1) % n]);
    }
  }
}
//调试代码记得注释掉！！！！！！！！
 /*for(int i=0;i<n;i++){
       for(int j=0;j<n;j++){
           cout << dp[i][j]<<' ';
       }
       cout << endl;
   }*/

int min_ans=INT_MAX;
int max_ans=0;


for (int i = 0;i<n;i++){
  int r = (i + n - 1) % n;
  max_ans = max(max_ans, dp[i][r]);
}

for (int i = 0; i < n; i++) {
  int r=(i+n-1)%n;
 
  min_ans = min(min_ans, dp1[i][r]);
}

cout << min_ans << endl;
cout << max_ans;
}
