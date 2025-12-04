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
int t;
int n;
int fa[200005];
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
    }
    fa[a] = b;
    return;
}
bool check(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) {
        return true;
    }
    return false;
}

// int enemy[1000000005];
signed main() {
    cin >> t;
    while (t--) {
        cin >> n;
        int tim = 0;
        map<int, int> mp;
        // memset(fa, 0, sizeof(fa));
        for (int i = 1; i <= 200000; i++) {
            fa[i] = i;
        }
        int i, j, e;
        queue<pair<int, int>> que;
        int flag = 0;
        while (n--) {
            cin >> i >> j >> e;
            //映射到合理范围
            if (!mp[i]) {
                mp[i] = ++tim;
            }
            if (!mp[j]) {
                mp[j] = ++tim;
            }
            i = mp[i], j = mp[j];
            if (e) {
                hebing(i, j);

            } else {
                que.push({i, j});
            }
        }

        while (!que.empty() && !flag) {
            int f, s;
            f = que.front().first;
            s = que.front().second;
            que.pop();
            if (check(f, s)) {
                cout << "NO" << endl;
                flag = 1;
            }
        }
        if (!flag)
            cout << "YES" << endl;
    }
}
