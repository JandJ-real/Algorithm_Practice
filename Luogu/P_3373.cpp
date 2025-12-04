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
int n, q, MOD;
int arr[100005];
int sum[100000 * 4 + 5];
int lazy[100000 * 4 + 5];
int lazy1[100000 * 4 + 5];
void push_up(int p) {
    sum[p] = (sum[p << 1] + sum[p << 1 | 1]) % MOD;
}
void push_down(int p, int l, int r) {
    int temp = lazy[p];
    int temp1 = lazy1[p];
    int mid = (l + r) >> 1;
    lazy[p] = 0;
    lazy1[p] = 1;
    //先处理乘法
    sum[p << 1] *= temp1;
    sum[p << 1] %= MOD;
    sum[p << 1 | 1] *= temp1;
    sum[p << 1 | 1] %= MOD;

    sum[p << 1] += (mid - l + 1) * temp;
    sum[p << 1] %= MOD;
    sum[p << 1 | 1] += (r - mid) * temp;
    sum[p << 1 | 1] %= MOD;

    lazy1[p << 1] =(lazy1[p<<1] *temp1)%MOD;
    lazy[p << 1] =((lazy[p<<1]* temp1)+temp)%MOD;
    lazy1[p << 1 | 1] = (lazy1[p << 1 | 1] *temp1)%MOD;
    lazy[p << 1 | 1] = ((lazy[p << 1 | 1] * temp1) + temp) % MOD;

}
void build(int p, int l, int r) {
    lazy1[p] = 1;
    if (l == r) {
        sum[p] = arr[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    push_up(p);
    return;
}
void add(int p, int l, int r, int L, int R, int x) {
    if (l >= L && r <= R) {
        /*
                       if(lazy1[p]>1){
            push_down(p,l,r);

        }*/
        lazy[p] += x;
        sum[p] = (sum[p] + x * (r - l + 1)) % MOD;
        return;
    }
    int mid = (l + r) >> 1;
    push_down(p, l, r);
    if (L <= mid)
        add(p << 1, l, mid, L, R, x);
    if (R >= mid + 1)
        add(p << 1 | 1, mid + 1, r, L, R, x);
    push_up(p);
    return;
}
void cheng(int p, int l, int r, int L, int R, int x) {
    if (l >= L && r <= R) {
        /*
                if(lazy[p]){
            push_down(p,l,r);
        */

        lazy1[p] = (lazy1[p] *x)%MOD;
        sum[p] = (sum[p] * x) % MOD;
        lazy[p] = (lazy[p] * x) % MOD;
        return;
    }
    int mid = (l + r) >> 1;
    push_down(p, l, r);
    if (L <= mid)
        cheng(p << 1, l, mid, L, R, x);
    if (R >= mid + 1)
        cheng(p << 1 | 1, mid + 1, r, L, R, x);
    push_up(p);
    return;
}
int getsum(int p, int l, int r, int L, int R) {
    if (l >= L && r <= R) {
        return sum[p];
    }
    int mid = (l + r) >> 1;
    int ans = 0;
    push_down(p, l, r);
    if (L <= mid)
        ans = (ans + getsum(p << 1, l, mid, L, R)) % MOD;
    if (R >= mid + 1)
        ans = (ans + getsum(p << 1 | 1, mid + 1, r, L, R)) % MOD;
    return ans;
}
signed main() {
    cin >> n >> q >> MOD;
    for (int i = 1; i <= n; i++) {
        arr[i] = read();
    }
    build(1, 1, n);
    /*
        for (int i = 1; i <= 20; i++) {
        cout << "i:" << i << ' ' << sum[i] << endl;
    }
    */

    int opt, a, b, c;
    while (q--) {
        opt = read();
        if (opt == 1) {
            a = read(), b = read(), c = read();
            cheng(1, 1, n, a, b, c);
            /*
                     for (int i = 1; i <= 20; i++) {
                cout << "i:" << i << ' ' << lazy1[i] << endl;
            }
            */

        } else if (opt == 2) {
            a = read(), b = read(), c = read();
            add(1, 1, n, a, b, c);
        } else {
            a = read(), b = read();
            cout << getsum(1, 1, n, a, b) << endl;
        }
    }
}
