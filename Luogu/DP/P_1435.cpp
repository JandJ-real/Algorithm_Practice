#include <bits/stdc++.h>

using namespace std;
//区分大小写
//区间dp！！！！！！
//已知回文到增加一个字符后的回文
//与之前不同的是可以由3字符回文->5字符回文
string str;
int len;
int main() {
    cin >> str;
    len = str.length();
    vector<vector<int>> dp(len + 1, vector<int>(len + 1));
    for(int i=1;i<=len;i++){
        dp[i][i] = 0;
    }
    for (int i = 2;i<=len;i++){
        for (int j = 1;j<=len;j++){
            int l = j;
            int r=j+i-1;
            if(r>len){
                break;
            }
            
            if(str[l-1]==str[r-1]&&i>=3){
                dp[l][r] = dp[l + 1][r - 1];
            }
            else if(str[l-1]!=str[r-1]){
                dp[l][r] = min(dp[l][r - 1], dp[l + 1][r]) + 1;//有问题？？
            }//结果证明没问题
            else{
                dp[l][r] = 0;
            }
           
        }
    }
    cout << dp[1][len];
}