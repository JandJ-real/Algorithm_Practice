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
int n, m;
int Fa[1005];
void start() {
    for (int i = 1; i <= n; i++) {
        Fa[i] = i;
    }
    return;
}
int zx(int x) {
    if (Fa[x] == x) {
        return x;
    }
    return zx(Fa[x]);
}
void hb(int a, int b) {
    Fa[zx(a)] = zx(b);
    return;
}
signed main() {
    while (cin >> n, n) {
        cin >> m;
        start();
        int a, b;
        while (m--) {
            cin >> a >> b;
            if (zx(a) != zx(b))
                n--;
            hb(a, b);
        }
        cout<<n-1<<endl;
    }
}
