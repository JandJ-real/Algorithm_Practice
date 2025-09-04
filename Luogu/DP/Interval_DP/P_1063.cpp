#include <bits/stdc++.h>
//与P_1880类似的环结构区间dp
using namespace std;
int n;//珠子个数
#define int long long
signed main() {
cin>>n;
vector<int> temp(n);
vector<pair<int,int>> arr(n);
for(int i=0;i<n;i++){
    cin >> temp[i];
}
for(int i=0;i<n-1;i++){
    arr[i].first=temp[i];
    arr[i].second = temp[i + 1];
}
arr[n-1].first=temp[n-1];
arr[n - 1].second = temp[0]; /*for (int i = 0; i < n; i++) {
       cout << arr[i].first<<' ' << arr[i].second << endl;
   }*/

//以上为输入
//依然用取模
vector<vector<int>> dp(n ,vector<int>(n,0));
for(int i=2;i<=n;i++){
    //枚举长度
    for(int j=0;j<n;j++){
        //枚举左端点
        //枚举j~j+i-1作为断点

        dp[j][(j + i - 1) % n] =
            max(dp[j][(j + i - 1) % n],
                dp[(j + 1) % n][(j + i - 1) % n] +
                    arr[j].first * arr[j].second *
                        arr[(j + i - 1) % n].second);

        for (int z = (j + 1)%n; z != (j + i-1+n) % n;
             z = (z + 1) % n)
        {
            dp[j][(j + i - 1) % n] =
                max(dp[j][(j + i - 1) % n],
                    dp[j][z] + dp[(z + 1)%n][(j + i - 1) % n] +
                        arr[j].first * arr[z].second * arr[(j + i - 1) % n].second);
        }

    }
}
int ans=0;
for(int i=0;i<n;i++){
    int r = (i + n - 1) % n;
    ans = max(ans, dp[i][r]);
}
cout << ans;
}