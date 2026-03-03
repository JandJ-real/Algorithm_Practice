#include <bits/stdc++.h>
using namespace std;
#define int long long

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int n, m, p;
int Fa[5005];
int zx(int x) {
    if (Fa[x] == x) {
        return x;
    }

    return zx(Fa[x]);
}
void hb(int a, int b) {
    Fa[zx(a)] = zx(b);
}
signed main() {
    cin >> n >> m >> p;
    for (int i = 1; i <= n; i++) {
        Fa[i] = i;
    }
    int a, b;
    while (m--) {
        a = read(), b = read();
        hb(a, b);
    }
    while (p--) {
        a = read(), b = read();
        if (zx(a) == zx(b)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}
