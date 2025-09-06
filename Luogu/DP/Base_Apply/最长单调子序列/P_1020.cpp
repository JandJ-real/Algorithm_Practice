#include <bits/stdc++.h>
//最长不上升子序列
using namespace std;
#define int long long
vector<int> arr(1,0);//1-based
int n;//导弹个数
int num;//已处理导弹数量
signed main() {
int temp;
while (scanf("%d",&temp)!=EOF){
  arr.push_back(temp);
}
n = arr.size()-1;
//以上为输入

//以下为最长单调子序列板子
vector<int> dp;//长度为i的不上升子序列末尾元素的最大值
for(int i=1;i<=n;i++){
    //注意：不上升用upper加greater反转，即寻找第一个<arr[i]的位置(只因等于也可增加长度)
    auto it = upper_bound(dp.begin(), dp.end(), arr[i],greater<int>());
    if(it==dp.end()){
        dp.push_back(arr[i]);
    }else{
        *it = arr[i];
    }
}
cout << dp.size()<<endl;

//求最少要几套拦截系统，即最少几个不上升子序列可以覆盖全部，即令每个不上升子序列尽可能大，根据某个定理，可以转化为求最长严格上升子序列的长度
vector<int> dp1; //长度为i的上升子序列末尾元素的最小值
for (int i = 1; i <= n; i++) {
  //注意：上升用lower，即寻找第一个>=arr[i]的位置(只因等于不可增加长度)
  auto it = lower_bound(dp1.begin(), dp1.end(), arr[i]);
  if (it == dp1.end()) {
    dp1.push_back(arr[i]);
  } else {
    *it = arr[i];
  }
}
cout << dp1.size();
//尝试模拟多次最长不上升子序列，看何时处理完所有导弹
//ai说行不通
/*num += dp.size();
int time = 1;
for(int i=0;i<dp.size();i++){
    for (auto it = arr.begin();it!=arr.end();it++){
        if(*it==dp[i]){
            arr.erase(it);
            break;
        }
    }
}
while(num!=n){
  vector<int> dp; //长度为i的不上升子序列末尾元素的最大值
  for (int i = 1; i <= n-num; i++) {
    auto it = lower_bound(dp.begin(), dp.end(), arr[i], greater<int>());
    if (it == dp.end()) {
      dp.push_back(arr[i]);
    } else {
      *it = arr[i];
    }
  }
  for (int i = 0; i < dp.size(); i++) {
    for (auto it = arr.begin(); it != arr.end(); it++) {
      if (*it == dp[i]) {
        arr.erase(it);
        break;
      }
    }
  }
  time++;
  num += dp.size();
}
cout << time;*/
}