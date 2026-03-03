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
int q;
int arr[1000006];
int mmax[1000000 * 4 + 5];
int lazy[1000000 * 4 + 5];
int lazy2[1000000 * 4 + 5];  //有lazy2先下传lazy2，再下传lazy
int flag[1000000 * 4 + 5];
void push_up(int p) {
    mmax[p] = max(mmax[p << 1], mmax[p << 1 | 1]);
}
void build(int p, int l, int r) {
    if (l == r) {
        mmax[p] = arr[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    push_up(p);
}
void push_down(int p) {
    if (lazy[p]) {
        int temp = lazy[p];
        mmax[p << 1] += temp;
        mmax[p << 1 | 1] += temp;
        if (flag[p << 1]) {
            lazy2[p << 1] += temp;
        } else {
            lazy[p << 1] += temp;
        }
        if (flag[p << 1 | 1]) {
            lazy2[p << 1 | 1] += temp;
        } else {
            lazy[p << 1 | 1] += temp;
        }
        lazy[p] = 0;
    } else if (flag[p]) {
        int temp = lazy2[p];
        mmax[p << 1] = temp;
        mmax[p << 1 | 1] = temp;
        lazy2[p << 1] = temp;
        flag[p << 1] = 1;
        lazy2[p << 1 | 1] = temp;
        flag[p << 1 | 1] = 1;
        lazy[p << 1] = 0;
        lazy[p << 1 | 1] = 0;
        // lazy2[p] = LLONG_MIN;
        flag[p] = 0;
    }
}

// change对于懒标记而言是个灾难
void change(int p, int l, int r, int L, int R, int x) {
    if (l >= L && r <= R) {
        mmax[p] = x;
        lazy2[p] = x;
        flag[p] = 1;
        lazy[p] = 0;
        return;
    }
    // mmax[p] = max(mmax[p], x);
    //  push_down(p);
    push_down(p);
    int mid = (l + r) >> 1;
    if (L <= mid)
        change(p << 1, l, mid, L, R, x);
    if (R >= mid + 1)
        change(p << 1 | 1, mid + 1, r, L, R, x);
    push_up(p);
}
void add(int p, int l, int r, int L, int R, int x) {
    if (l >= L && r <= R) {
        mmax[p] += x;
        if (flag[p]) {
            lazy2[p] += x;
        } else {
            lazy[p] += x;
        }
        return;
    }
    push_down(p);
    int mid = (l + r) >> 1;
    if (L <= mid)
        add(p << 1, l, mid, L, R, x);
    if (R >= mid + 1)
        add(p << 1 | 1, mid + 1, r, L, R, x);
    push_up(p);
}
int getmax(int p, int l, int r, int L, int R) {
    if (l >= L && r <= R) {
        // ans = max(ans, mmax[p]);
        return mmax[p];
    }
    push_down(p);
    int mid = (l + r) >> 1;
    int ans = LLONG_MIN;
    if (L <= mid)
        ans = max(ans, getmax(p << 1, l, mid, L, R));
    if (R >= mid + 1)
        ans = max(ans, getmax(p << 1 | 1, mid + 1, r, L, R));
    return ans;
}
signed main() {
    cin >> n >> q;
    memset(flag, 0, sizeof(flag));
    for (int i = 1; i <= n; i++) {
        arr[i] = read();
    }
    for (int i = 1; i <= 4 * n; i++) {
        mmax[i] = LLONG_MIN;
        // lazy2[i] = LLONG_MIN;
    }
    build(1, 1, n);
    int opt, a, b, c;
    /*
        for (int i = 1; i <= 25; i++) {
            cout << mmax[i] << ' ';
        }
        cout << endl;
    */
    while (q--) {
        opt = read();
        if (opt == 1) {
            a = read(), b = read(), c = read();

            change(1, 1, n, a, b, c);

        } else if (opt == 2) {
            a = read(), b = read(), c = read();
            add(1, 1, n, a, b, c);

        } else {
            a = read(), b = read();
            cout << getmax(1, 1, n, a, b) << endl;
        }
    }
}
/*
1-6 1-3 4-6 1-2 3-3 4-5 6-6 1-1 2-2 0 0 4-4 5-5 0 0
5    4   5   1   4   5    4  1   1  0  0   5   1 0 0*/
