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
int sum[100000 * 4 + 5];
int lazy[100000 * 4 + 5];  //只能是0/1
void push_up(int p) {
    sum[p] = sum[p << 1] + sum[p << 1 | 1];
}
void push_down(int p, int l, int r) {
    int mid = (l + r) >> 1;
    int temp = lazy[p];
    if (temp) {
        sum[p << 1] = (mid - l + 1) - sum[p << 1];
        sum[p << 1 | 1] = (r - mid) - sum[p << 1 | 1];
        lazy[p << 1] = !lazy[p << 1];
        lazy[p << 1 | 1] = !lazy[p << 1 | 1];
        lazy[p] = 0;
    }
}
void change(int p, int l, int r, int L, int R) {
    if (l >= L && r <= R) {
        lazy[p] = !lazy[p];
        sum[p] = (r - l + 1) - sum[p];
        return;
    }
    push_down(p, l, r);
    int mid = (l + r) >> 1;
    if (L <= mid)
        change(p << 1, l, mid, L, R);
    if (R >= mid + 1)
        change(p << 1 | 1, mid + 1, r, L, R);
    push_up(p);
}
int getsum(int p, int l, int r, int L, int R) {
    if (l >= L && r <= R) {
        return sum[p];
    }
    push_down(p, l, r);
    int ans = 0;
    int mid = (l + r) >> 1;
    if (L <= mid)
        ans += getsum(p << 1, l, mid, L, R);
    if (R >= mid + 1)
        ans += getsum(p << 1 | 1, mid + 1, r, L, R);
    return ans;
}

int n, m;
signed main() {
    cin >> n >> m;
    int c, a, b;
    while (m--) {
        cin >> c >> a >> b;
        if (c) {
            cout << getsum(1, 1, n, a, b) << endl;

        } else {
            change(1, 1, n, a, b);
        }
    }
}
