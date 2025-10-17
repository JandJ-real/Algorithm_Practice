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
int Seed;
inline int rnd()
{
    static const int MOD = 1e9;
    return Seed = (1LL * Seed * 0x66CCFF % MOD + 20120712) % MOD;
}

int n;
int k;  //按顺序移动到下一个同学位置
int d;  //每多跳过一个学生就要多花费 d 点精力值
int x;  //每一次最多只能跳过 x−1 个学生
int tp;

vector<int> arr;
//求花费精力最小值
/*
dp[i]=dp[j]+k+arr[i]+(i-j-1)*d
     =max(dp[j]-j*d)+k+arr[i]+(i-1)*d
*/
//窗口大小：x
vector<int> dp;
signed main()
{
    cin >> n >> k >> d >> x >> tp;
    arr.resize(n + 1);
    dp.resize(n + 1);

   
    if (tp) {
        //cout << "hhhh" << endl;
        cin >> Seed;
        //cout << "seed:" << Seed << endl;
        for (int i = 1; i <= n; i++) {
            //cout << "i:" << i << endl;
            arr[i] = rnd();
        }
    }
    else{
        for (int i = 1; i <= n; i++) {
            arr[i] = read();
        }
    }
    deque<int> de;
    // dp[0] = 0;
    dp[1] = arr[1];
    de.push_back(1);
    for (int i = 2; i <= n; i++) {
        // cout << "i:" << i << endl;
        while (!de.empty() && de.back() - de.front() >= x) {
            de.pop_front();
        }
        int num = de.front();
        dp[i] = dp[num] - num * d + k + arr[i] + (i - 1) * d;
        while (!de.empty() && dp[de.back()] - de.back() * d > dp[i] - i * d) {
            de.pop_back();
        }
        de.push_back(i);
    }
    cout << dp[n];
}