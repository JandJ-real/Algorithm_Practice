#include <bits/stdc++.h>

using namespace std;
//单调队列优化多重背包
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
int n;            //物品种类
int w;            //背包重量
vector<int> v;    //价值
vector<int> wei;  //重量
vector<int> num;  //数量
vector<int> dp;
vector<int> dp1;
int ans;
signed main()
{
    cin >> n >> w;
    v.resize(n + 1);
    wei.resize(n + 1);
    num.resize(n + 1);
    dp.resize(w + 1, 0);
    dp1.resize(w + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> v[i] >> wei[i] >> num[i];
    }
    deque<int> de;  //单调递减(这里的减是重载之后的减，具体@处)
    //按余数分组，每一组用单调队列优化
    for (int i = 1; i <= n; i++) {
        //枚举物品
        int count = num[i];  //物品数量，同时也是窗口大小
        for (int j = 0; j < wei[i]; j++) {
            //枚举余数
            for (int k = j; k <= w; k += wei[i]) {
                //枚举该余数组的所有容量
                //窗口范围：[k-count*wei[i],k-wei[i]]
                //这里的顺序值得琢磨
                while (!de.empty() && de.front() < k - count * wei[i]) {
                    de.pop_front();
                }
                if (!de.empty()) {
                    dp1[k] = max(dp[k], dp[de.front()] + (k - de.front()) / wei[i] * v[i]);
                }
                while (!de.empty() && dp[k] > dp[de.back()] + (k - de.back()) / wei[i] * v[i]) {//@(本质来说还是因为更有价值)
                    de.pop_back();
                }
                de.push_back(k);
            }
            de.clear();
        }
        //每个物品遍历之后，将目前结果视为旧值(但不是swap!)
        //为什么每一余数组遍历完后不视为旧值呢？因为同一物品的不同余数组之间不相互影响
        /*
        惊天大涅槃
        */
        dp = dp1;
        //swap(dp1, dp);
    }
    for (int i = 1; i <= w; i++) {
        ans = max(ans, dp1[i]);
    }
    cout << ans;
}