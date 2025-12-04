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
struct node {
    int u;
    int v;
    int num;
} arr[100005];
bool mycompare(node a, node b) {
    if (a.num > b.num)
        return true;
    else
        return false;
}
int fa[20005];
int find(int x) {
    if (fa[x] == x) {
        return x;
    }
    fa[x] = find(fa[x]);
    return fa[x];
}
bool check(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) {
        return true;
    } else {
        return false;
    }
}
void hebing(int a, int b) {
    a = find(a);
    b = find(b);

    fa[a] = b;
    return;
}
int enemy[20005];
int n;
int m;


signed main() {
    cin >> n >> m;
    int a, b;
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    for (int i = 1; i <= m; i++) {
        arr[i].u = read(), arr[i].v = read(), arr[i].num = read();
    }
    sort(arr + 1, arr + m + 1, mycompare);
    for (int i = 1; i <= m+1; i++) {
        a = arr[i].u;
        b = arr[i].v;
        if (check(a, b)) {
            cout << arr[i].num;
            break;
        }

        else {
            if (!enemy[a]) {
                enemy[a] = b;
            } else {
                hebing(enemy[a], b);
            }
            if (!enemy[b]) {
                enemy[b] = a;
            } else {
                hebing(enemy[b], a);
            }
        }
    }
    return 0;
}
