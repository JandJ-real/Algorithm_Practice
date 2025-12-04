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
int n, k;
/*
1.当前的话与前面的某些真的话冲突，就是假话
2.x或y比n大，就是假话
3.表示x吃x就是假话
*/
int ans;
int Fa[150005];  //三倍并查 x+n为猎物，x+2*n为天敌
int find(int x) {
    if (Fa[x] != x) {
        Fa[x] = find(Fa[x]);
    }
    return Fa[x];
}
void hebing(int a, int b) {
    Fa[find(a)] = find(b);
    Fa[find(a + n)] = find(b + n);
    Fa[find(a + 2 * n)] = find(b + 2 * n);
}
void hebing2(int a, int b) {
    //a吃b
    Fa[find(a + n)] = find(b);//a的猎物时b
    Fa[find(a + 2 * n)] = find(b + n);//a的天敌是b的猎物
    Fa[find(b + 2 * n)] = find(a);//b的天敌是a
}
signed main() {
    cin >> n >> k;
    for (int i = 1; i <= 3 * n; i++) {
        Fa[i] = i;
    }
    int opt, a, b;
    while (k--) {
        cin >> opt >> a >> b;
        if (a > n || b > n) {
            ans++;
            continue;  //解决2
        }
        if (opt == 1) {
            if (find(a + n) == find(b) || find(a + 2 * n) == find(b)) {
                ans++;
                continue;
            }
            hebing(a, b);
        } else {
            // a+n=b
            if (find(a + 2 * n) == find(b) || find(a) == find(b)) {
                ans++;
                continue;
            }
            hebing2(a, b);
        }
    }
    cout << ans;
}
