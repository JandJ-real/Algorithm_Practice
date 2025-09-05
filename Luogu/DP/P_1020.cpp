#include <bits/stdc++.h>
//最长不上升子序列
using namespace std;
vector<int> arr(1,0);//1-based
int n;//导弹个数
signed main() {
int temp;
while (scanf("%d",&temp)!=EOF){
  arr.push_back(temp);
}
n = arr.size()-1;
//以上为输入
vector<int> dp;//长度为i的不上升子序列末尾元素的最大值
for(int i=1;i<=n;i++){
    auto it = lower_bound(dp.begin(), dp.end(), arr[i],greater<int>());
    if(it==dp.end()){
        dp.push_back(arr[i]);
    }else{
        *it = arr[i];
    }
}
cout << dp.size();
}