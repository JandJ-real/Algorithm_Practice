#include <bits/stdc++.h>

using namespace std;
#define int long long
inline int read() {
    int x = 0, f = 1;     // x: 存储结果, f: 符号标志(1正数, -1负数)
    char ch = getchar();  // 读取第一个字符

    while (!isdigit(ch)) {  // 跳过非数字字符
        if (ch == '-')
            f = -1;      // 遇到负号，设置符号为负
        ch = getchar();  // 继续读取下一个字符
    }

    while (isdigit(ch)) {       // 处理数字部分
        x = x * 10 + ch - '0';  // 将字符转换为数字并累加
        ch = getchar();         // 读取下一个字符
    }

    return x * f;  // 返回结果（考虑符号）
}
int n;
int arr[100005];
vector<int> dp;
//相邻项 相与不为零的最大长度
int ans;
signed main() {
    cin >> n;
    dp.resize(n+1,1);
    arr[1]=read();
    // for(int i=1;i<=n;i++){
    //     arr[i]=read();
    // }
    int temp;
for(int i=2;i<=n;i++){
    temp=read();
    arr[i]=temp;
    for(int j=1;j<=i-1;j++){
        if((temp&arr[j])!=0){
            dp[i]=max(dp[i],dp[j]+1);
        }
    }
    ans=max(ans,dp[i]);
}
cout<<ans;
}