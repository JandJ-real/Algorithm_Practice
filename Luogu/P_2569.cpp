#include <bits/stdc++.h>

using namespace std;
#define int long long
inline int read()
{
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
//问题：最终结果的最优解，过程中的某天的选择可能并非最优的？？
int t;
int w;     //间隔w天再次操作 i+1~i+w 均不能交易
int maxp;  //任何时间股票数不能超过maxp
int buy[2005], sell[2005], buynum[2005], sellnum[2005];
vector<vector<int>> dp;
// i天 手持j支股票的最大收益
/*
当天直接买j支 dp[i][j]=-j*buy[i];
不买不卖   dp[i][j]=dp[i-1][j];
从之前的天中，卖到j支 dp[i][j]=dp[i-k][jj]+sell[i]*(jj-j);
                    k[w+1,i-1]
从之前的天中，买到j支 dp[i][j]=dp[i-k][jj]-buy[i]*(j-jj);
                    k[w+1,i-1]

*/
int ans;
signed main()
{
    cin >> t >> maxp >> w;
    dp.resize(t + 1);
    for (int i = 1; i <= t; i++) {
        dp[i].resize(maxp + 1, LONG_LONG_MIN);
        buy[i] = read();
        sell[i] = read();
        buynum[i] = read();
        sellnum[i] = read();
    }
    dp[0].resize(maxp + 1, LONG_LONG_MIN);
    // dp[0][0] = 0;
    // dp[1][0] = 0;
    deque<int> de1;  //卖的，递减
    deque<int> de2;  //买的，递减

    for (int i = 1; i <= t; i++) {
        // 天
        int Buy = buy[i];
        int Sell = sell[i];
        int Buynum = buynum[i];
        int Sellnum = sellnum[i];
        for (int j = 0; j <= buynum[i]; j++) {
            dp[i][j] = -j * Buy;
        }
        //----------------------

        for (int j = 0; j <= maxp; j++) {
            if (i - 1 >= 0)
                dp[i][j] = max(dp[i][j], dp[i - 1][j]);
        }
        if (i <= w + 1)
            continue;
        //------------------------
        //只在每一天，且买入卖出分开使用单调队列
        de1.clear();
        de2.clear();
        int last = i - w - 1;
        // int Sellnum = sellnum[last];
        // Buynum = buynum[last];
        //卖的：
        for (int j = maxp; j >= 0; j--) {
            //维护区间长度
            while (!de1.empty() && de1.front() - Sellnum > j) {
                de1.pop_front();
            }

            //维护单调性
            while (!de1.empty() && dp[last][de1.back()] + Sell * (de1.back()) < dp[last][j] + Sell * j) {
                de1.pop_back();
            }
            de1.push_back(j);
            //状态转移
            if (!de1.empty())
                dp[i][j] = max(dp[i][j], dp[last][de1.front()] + Sell * (de1.front() - j));
        }
        //买的
        for (int j = 0; j <= maxp; j++) {
            while (!de2.empty() && Buynum + de2.front() < j) {
                de2.pop_front();
            }

            while (!de2.empty() && dp[last][de2.back()] - Buy * (de2.back()) < dp[last][j] - Buy * j) {
                de2.pop_back();
            }
            de2.push_back(j);
            if (!de2.empty())
                dp[i][j] = max(dp[i][j], dp[last][de2.front()] + Buy * (de2.front() - j));
            cout << "i:" << i << ' ' << "j:" << j << ' ' << dp[i][j] << ' ';
        }
        cout << endl;
    }

    for (int i = 0; i <= maxp; i++) {
        ans = max(ans, dp[t][i]);
    }
    cout << ans;
}