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

int m, n;
//动态规划 失败太大了
// int dp[10005][10005];
int arr[100005];
int minn[4 * 100000 + 5];
void push_up(int p) {
    minn[p] = min(minn[p << 1], minn[p << 1 | 1]);
}
void build(int p, int l, int r) {
    if (l == r) {
        minn[p] = arr[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    push_up(p);
    return;
}
int getmin(int p, int l, int r, int L, int R) {
    int ans = INT_MAX;
    if (l >= L && r <= R) {
        ans = min(ans, minn[p]);
        return ans;
    }
    int mid = (l + r) >> 1;
    if (L <= mid) {
        ans = min(ans, getmin(p << 1, l, mid, L, R));
    }
    if (R >= mid + 1) {
        ans = min(ans, getmin(p << 1 | 1, mid + 1, r, L, R));
    }
    return ans;
}
signed main() {
    cin >> m >> n;
    for (int i = 1; i <= m; i++) {
        arr[i] = read();
    }
    int a, b;
    build(1, 1, m);
    /*
      for (int i = 1; i <= 100; i++) {
        cout << minn[i] << endl;
    }
    */

    while (n--) {
        cin >> a >> b;
        cout << getmin(1, 1, m, a, b) << ' ';
    }
}
