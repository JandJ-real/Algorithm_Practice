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
int m;
struct node {
    int x;
    int y;
    int tim;
} arr[100005];

// vector<node> arr(100005);
bool mycompare(node a, node b) {
    if (a.tim < b.tim) {
        return true;
    } else {
        return false;
    }
}
int Fa[1005];
int cura;
int find(int x) {
    if (Fa[x] != x) {
        Fa[x] = find(Fa[x]);
    }
    return Fa[x];
}
bool hebing(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) {
        return false;
    }
    Fa[a] = b;
    return true;
}
signed main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        Fa[i] = i;
    }
    int cura = n;
    for (int i = 1; i <= m; i++) {
        arr[i].x = read(), arr[i].y = read(), arr[i].tim = read();
    }
    /*
        for (int i = 1; i <= m; i++) {
        cout << arr[i].x << ' ' << arr[i].y << ' ' << arr[i].tim << ' ' << endl;
    }

    */

    sort(arr + 1, arr + m + 1, mycompare);
    /*
        for (int i = 1; i <= m; i++) {
        cout << arr[i].x << ' ' << arr[i].y << ' ' << arr[i].tim << ' ' << endl;
    }
    */

    for (int i = 1; i <= m; i++) {
        if (hebing(arr[i].x, arr[i].y)) {
            cura--;
            // cout << "---" << endl;
        }
        if (cura == 1) {
            cout << arr[i].tim << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}
