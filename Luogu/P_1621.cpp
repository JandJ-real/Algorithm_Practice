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
int a, b, p;
// b-a+1-合并次数
vector<bool> isPrime(100005, true);
vector<int> vis;
void sieveOfEratosthenes(int n) {
    isPrime[0] = isPrime[1] = false;  // 0和1不是素数
int i;
    for (i = 2; i <= n; i++) {
        if (isPrime[i]) {
            if (i >= p && i <= b)
                vis.push_back(i);
            // 标记i的所有倍数为非素数
            for (int j = i * i; j < n; j += i) {
                isPrime[j] = false;
            }
        }
    }

    return;
}
int fa[100005];

int ans;
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
signed main() {
    cin >> a >> b >> p;
    sieveOfEratosthenes(100000);
    for (int i = a; i <= b; i++) {
        fa[i] = i;
    }
    /*
        for (int i = p; i <= b; i++) {
            if (isPrime[i]) {
                vis.push_back(i);
                //cout<<"push:"<<i<<endl;
            }
        }
    */

    for (int x : vis) {
        //cout << "x:" << x << endl;
        int c = 1;
        //------------------------
        while (c * x < a) {
            c++;
        }
        // int tempcnt = 0;
        while ((c + 1) * x <= b) {
            hebing(c * x, (c + 1) * x);
            c++;
        }
        //-------------------------
    }
    for (int i = a; i <= b; i++) {
        if (fa[i] == i) {
            ans++;
        }
    }
    cout << ans;
}
