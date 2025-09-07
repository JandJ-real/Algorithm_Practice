#include <bits/stdc++.h>

//启示：不要被题目的流程牵着走(除非硬模拟)，看清问题的本质

//暴力？
//DP！！！！！
//某点断开取两端？
//取某一段取全部！！！！！！
using namespace std;
int n;//长度
int m;//2n
int ans = 0;
signed main() {
cin>>n;
m = 2 * n;
string str;
cin>>str;
str += str;
//初始化 递推
vector<int> lr(2*n+2,0);
vector<int> lb(2*n+2,0);
vector<int> rr(2*n+2,0);
vector<int> rb(2*n+2,0);
for(int i=0;i<2*n;i++){
if(str[i]=='w'){
lr[i+1]=lr[i]+1;
lb[i + 1] = lb[i] + 1;
}
else if(str[i]=='r'){
    lr[i+1]=lr[i]+1;
}
else{
    lb[i + 1] = lb[i] + 1;
}
}
for (int i = 2*n-1; i >=0; i--) {
  if (str[i] == 'w') {
    rr[i ] = rr[i+1] + 1;
    rb[i ] = rb[i+1] + 1;
  } else if (str[i] == 'r') {
    rr[i] = rr[i + 1] + 1;
  } else {
    rb[i] = rb[i + 1] + 1;
  }
}
for(int i=1;i<=2*n;i++){
    ans = max(ans, max(rr[i], rb[i]) + max(lr[i], lb[i]));
}
cout << ((ans>n )? n : (ans));
}