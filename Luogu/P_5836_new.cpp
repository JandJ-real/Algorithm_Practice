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
char arr[100005];
int fa[100005];
int find(int x) {
    if (fa[x] != x) {
        fa[x] = find(fa[x]);
    }
    return fa[x];
}
void hebing(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) {
        return;
    } else {
        fa[a] = b;
    }
    return;
}
signed main() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        fa[i] = i;
    }
    int a, b;
    char c;
    for (int i = 1; i < n; i++) {
        a = read(), b = read();
        if (arr[a] == arr[b]) {
            hebing(a, b);
        }
    }
    while (m--) {
        cin >> a >> b >> c;
        a = find(a);
        b = find(b);
        if (a == b) {
            if (arr[a] == c) {
                cout << 1;
                continue;
            }
            cout << 0;
        } else {
            cout << 1;
        }
    }
}
