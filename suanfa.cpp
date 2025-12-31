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
int n, c;
int pos[100];
int power[100];
/*
dp[i][j][0/1] 关掉区间i~j后，站在i处或站在j处

dp[i][j][0]=min( dp[i+1][j][0]+power[i]+(i,j之外的power（前缀和）) ,dp[i+1][j][1]+(j-i)*(power[i]+前缀和) );

dp[i][j][1]=min( dp[i][j-1][1]+power[j]+前缀和，dp[i][j-1][0]+(j-i)*（power[j]+前缀和）)

ans=min(dp[1][n][0],dp[1][n][1]);
*/
int dp[55][55][2];
int prefix[55];  // i~j:prefix[j]-prefix[i-1];
signed main() {
    cin >> n >> c;
    for (int i = 1; i <= n; i++) {
        cin >> pos[i] >> power[i];
        prefix[i] = prefix[i - 1] + power[i];
    }

    for (int i = 1; i <= n; i++) {
        dp[i][i][0] = INT_MAX;
        dp[i][i][1] = INT_MAX;
    }
    dp[c][c][0] = 0, dp[c][c][1] = 0;
    for (int i = 1; i < n; i++) {
        //区间大小
        for (int j = 1; j + i <= n; j++) {
            int r = j + i;
            dp[j][r][0] = min(
                dp[j + 1][r][0] +
                    (pos[j + 1] - pos[j]) * (power[j] + prefix[j - 1] - prefix[0] + prefix[n] - prefix[r]),
                dp[j + 1][r][1] + (pos[r] - pos[j]) * (power[j] + prefix[j - 1] - prefix[0] + prefix[n] - prefix[r]));
            dp[j][r][1] = min(
                dp[j][r - 1][1] +
                    (pos[r] - pos[r - 1]) * (power[r] + prefix[j - 1] - prefix[0] + prefix[n] - prefix[r]),
                dp[j][r - 1][0] + (pos[r] - pos[j]) * (power[r] + prefix[j - 1] - prefix[0] + prefix[n] - prefix[r]));
        }
    }
    cout << min(dp[1][n][0], dp[1][n][1]);
}
