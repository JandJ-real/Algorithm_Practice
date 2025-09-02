#include <bits/stdc++.h>
//混合背包
//多重背包问题 看成 多重0-1背包问题
using namespace std;
int t;//时间t
int n;//数量
#define int long long
signed main() {
  string a,b;
  cin >> a>>b;
  int lena = a.length();
  int lenb = b.length();
  int am, ah, bm, bh;
  if(lena==4){
      ah = a[0] - '0';
      am = (a[2] - '0') * 10 + (a[3] - '0');
  }
  else{
    ah = (a[0] - '0') * 10 + (a[1] - '0');
    am = (a[3] - '0') * 10 + (a[4] - '0');
  }
  if (lenb == 4) {
    bh = b[0] - '0';
    bm = (b[2] - '0') * 10 + (b[3] - '0');
  } else {
    bh = (b[0] - '0') * 10 + (b[1] - '0');
    bm = (b[3] - '0') * 10 + (b[4] - '0');
  }
  t = (bh - ah) * 60 + bm - am;

  cin>>n;
  vector<int> w(n + 1, 0);//耗时
  vector<int> v(n + 1, 0);//价值
  vector<int> m(n + 1, 0);//模式
  for(int i=1;i<=n;i++){
      cin >> w[i] >> v[i] >> m[i];
  }
  //以上为输入
  vector<int> dp(t + 1, 0);
  for (int i = 1; i <= n; i++)
  {
      // 枚举
      // 判断类型
      if (!m[i])
      {
          // 完全背包
          for (int j = w[i]; j <= t; j++){
              dp[j] = max(dp[j - w[i]] + v[i], dp[j]);
          }

      }
      else{
        //多重背包
        for (int q = 1; q <= m[i];q++){
          for (int j = t; j >= w[i]; j--) {
            dp[j] = max(dp[j - w[i]] + v[i], dp[j]);
          }
        }
      } /*
       else if(m[i]==1){
         //0-1背包
           for (int j = t; j >= w[i];j--){
             dp[j] = max(dp[j - w[i]] + v[i], dp[j]);
           }
       }



           //这种用标记数组处理多重背包问题的方法为何不行
           
       else{
         //多重背包
         vector<int> flag(t + 1, 0);//标记每个人用了几次
         for (int j = w[i]; j <= t; j++) {
           if ((dp[j - w[i]] + v[i] > dp[j])&&flag[j-w[i]]<m[i]) {
             flag[j]=flag[j-w[i]]+1;
             dp[j] = dp[j - w[i]] + v[i];
           }
           else {

           //虽然这里的逻辑有点怪怪的

               dp[j] = max(dp[j], dp[j - w[i]]);
           } //不是只有拿或不拿吗？
         }

       }
 */
  }
  cout << dp[t];
}