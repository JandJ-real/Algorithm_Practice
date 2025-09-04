#include <bits/stdc++.h>

using namespace std;
int v;//村庄的数量
int p;//邮件的数量
int main() {
cin>>v>>p;
vector<int> arr(v+1);
for(int i=1;i<=v;i++){
    cin >> arr[i];
}

//以上为输入
if(v==p)
    cout << 0;
vector<vector<int>> dp(v + 1, vector<int>(v + 1, INT_MAX));
for (i = 1;i+p-1<=v;i++){
    dp[i][i + p - 1] = 0;
}
for(int i=p+1;i<=v;i++){
    for(int j=1;j<=v+1-i;j++){

    }
}
}
