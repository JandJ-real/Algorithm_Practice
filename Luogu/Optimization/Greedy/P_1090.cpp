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
multiset<int> arr;
// int dp[10005][10005]; //失败的dp
// int prefix[10005];
/*
dp[i][j]=min(dp[i+1][j]+prefix[j]-prefix[i-1],dp[i][j-1]+prefix[j]-prefix[i-1])

*/
int ans = 0;

signed main() {
    cin >> n;
    int temp;
    for (int i = 1; i <= n; i++) {
        temp = read();
        arr.insert(temp);
        // prefix[i] = prefix[i - 1] + arr[i];
    }
    int f, s;
    while (arr.size() > 1) {
        auto it = arr.begin();
        f = *it,  it++, s = *it, arr.erase(it--),arr.erase(it);
        arr.insert(f + s);
        ans+=f+s;
    }
    //cout << "iii" << endl;
    //auto it = arr.begin();
    //ans = *it;

    // multiset<int> arr1 = arr;

    /*
        while (arr.size() > 1) {
        if (l >= r) {
            ans += (++tim) * l;
            arr.pop_front();
            l = arr.front();
        } else if (l < r) {
            ans += (++tim) * r;
            arr.pop_back();
            r = arr.back();
        }
    }
    ans += tim * arr.front();
    */

    cout << ans;
    /*
        for (int i = 1; i < n; i++) {
            for (int j = 1; j + i <= n; j++) {
                int r = j + i;
                dp[j][r] = prefix[r] - prefix[j - 1];
                dp[j][r] += min(dp[j + 1][r], dp[j][r - 1]);
            }
        }
        cout << dp[1][n];
    */
}
