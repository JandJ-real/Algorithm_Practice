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
int n, m;
int arr[1005];
int g[4 * 1000 + 5];
//如何找两个数的gcd？辗转相除？
int gcd(int a, int b) {
    if (a == 0 || b == 0) {
        return a + b;
    }
    int c = a / b;
    int r = a - c * b;
    if (r == 0) {
        return b;
    }
    return gcd(b, r);
}
void push_up(int p) {
    g[p] = gcd(g[p << 1], g[p << 1 | 1]);
}
void build(int p, int l, int r) {
    if (l == r) {
        g[p] = arr[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    push_up(p);
}
int getgcd(int p, int l, int r, int L, int R) {
    if (l >= L && r <= R) {
        return g[p];
    }
    int mid = (l + r) >> 1;
    int ans1 = 0, ans2 = 0;
    if (L <= mid)
        ans1 = getgcd(p << 1, l, mid, L, R);
    if (R >= mid + 1)
        ans2 = getgcd(p << 1 | 1, mid + 1, r, L, R);
    return gcd(ans1, ans2);
}
signed main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        arr[i] = read();
    }
    build(1, 1, n);
    int a, b;
    // cout<<gcd(2,4)<<gcd(3,5)<<gcd(8,16)<<endl;
    while (m--) {
        a = read(), b = read();
        cout << getgcd(1, 1, n, a, b) << endl;
    }
}
