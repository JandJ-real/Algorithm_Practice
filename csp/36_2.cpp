#include<bits/stdc++.h>

using namespace std;
//ai表示从i前往下一个区域消耗能量
//bi表示从第i个区域获得的能量
//目的：计算bi变为零的情况下最小初始值为多少
int n;//梦境数量
int main(){
   cin>>n;
   vector<int> a(n + 1);//0-n
   vector<int> b(n+1,0) ;//n凑数 0 -- n-1
   for (int i = 0; i <= n; i++) {
     cin>>a[i];
   }
   for (int i = 0; i < n; i++) {
     cin>>b[i];
   }
   vector<int> c(n + 1, 0);//0-n共n+1个
   vector<int> prefix(n + 1, 0);//1->1
   vector<int> suffix(n + 1, 0);//1-n
  
   
   c[0] = a[0] ;
   c[1] = c[0] + a[1] - b[0];
   prefix[0] = -10000;
   prefix[1] = c[0];
   for(int i=2;i<=n;i++){
       c[i] = c[i-1]+a[i] - b[i-1];
       prefix[i] = max(prefix[i-1],c[i-1]);
   }
    
   suffix[n] = c[n];
   for (int i = n;i>1;i--){
       suffix[i - 1] = max(suffix[i], c[i-1]);
   }/*
for(int i=0;i<=n;i++){
    cout << prefix[i] << ' ' << suffix[i] << endl;
}*/
   //预处理完毕
for(int i=0;i<n;i++){
    cout << max(prefix[i], suffix[i + 1] + b[i]) << ' ';
}
   }
//1.绝大部分时间浪费在凑数上
//2.开始解题前的数学分析
//3.预处理的思维方法
   
