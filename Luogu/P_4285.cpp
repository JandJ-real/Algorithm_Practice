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
int f[50], e[50];
int ans;
void dfs(int cur, int x, int y, bool flag) {
    int mid = 6 - x - y;  //中间柱子
    // while (x == mid || y == mid) mid++;
    if (x == y) {
        if (cur > 1)
            dfs(cur - 1, f[cur - 1], flag ? e[cur - 1] : y, flag);
        return;
    }
    if (cur > 1)
        dfs(cur - 1, f[cur - 1], mid, false);
    cout << "move " << cur << " from " << (char)(x + 'A' - 1) << " to " << (char)(y + 'A' - 1) << endl;
    ans++;
    f[cur] = y;
    if (cur > 1)
        dfs(cur - 1, f[cur - 1], flag ? e[cur - 1] : y, flag && true);
}
signed main() {
    cin >> n;
    int opt;
    int temp;
    for (int i = 1; i <= 3; i++) {
        cin >> opt;
        while (opt--) {
            cin >> temp;
            f[temp] = i;
        }
    }
    for (int i = 1; i <= 3; i++) {
        cin >> opt;
        while (opt--) {
            cin >> temp;
            e[temp] = i;
        }
    }
    dfs(n, f[n], e[n], true);
    cout << ans << endl;
}
