//比较型dp
/*我们假设有两个人跑步，第一个人正常走路，另一人使用魔法，在某一时间点时，第二人超过了第一人，第一人很后悔，于是重新开始跑步，但这次使用第二人的策略直到原来的时间点，如果第二人不敌第一人，第一人坚持原来策略，直到第二人追上第一人。*/
#include <bits/stdc++.h>
//问能否逃离 Yes->最短时间 No->最长路程
using namespace std;
#define int long long
int m;//魔法初值
int s;//总距离
int t;//时间
//速度17  技能一秒60，耗能10  魔法恢复速度4/s 
//恢复时原地不动
//注意：技能释放也有时间
signed main() {
 cin>>m>>s>>t;
 if(s<=17){
   cout << "Yes" << '\n' << 1;
   return 0;
 } 
 vector<int> dp(t+1);//每一秒最多跑多远
 dp[0] = 0;
 for(int i=1;i<=t;i++){
    //第一人只闪现不跑，提供对照组
    if(m>=10){
        dp[i] = dp[i - 1] + 60;
        m -= 10;
    }
    else{
        dp[i]=dp[i-1];
        m += 4;
    }
 }
 for(int i=1;i<=t;i++){
    //智者根据前人的路确定自己的路
    if(dp[i-1]+17>dp[i]){
        dp[i] = dp[i - 1] + 17;
    }
    if(dp[i]>=s){
        cout << "Yes" << '\n'
             << i;
        return 0;
    }
 }
 cout << "No" << '\n'
      << dp[t];
}