#include <bits/stdc++.h>
/*
1.dfs(顺便处理爷孙)+双重循环找兄弟 -----60
2.dfs(顺便处理爷孙)+三重循环找每个点的儿子们-----70 (可用 度 来计算时间复杂度，确实要小一点)
3.dfs(顺便处理爷孙)+ 数学优化 处理兄弟----100
*/
//gpt高见：属于局部组合计算的树优化问题
//         常见套路：枚举节点邻居，平方差代替双重循环，在dfs或主循环中一次性处理
using namespace std;
#define int long long
const int MOD = 10007;
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
vector<int> adj[200005];
int arr[200005];
int Fa[200005];
int sum = 0;//ans:模10007和
int mmax = 0;//ans：最大值
int pointsum[200005];//和
int sum2[200005];//平方和
int max1[200005];//邻居中的最大值
int max2[200005];//邻居中的第二大值
void f(int cur, int fa) {
    Fa[cur] = fa;
    if (Fa[fa]) {
        int temp = arr[Fa[fa]] * arr[cur];
        mmax = max(mmax, temp);
        sum = (sum + temp) % MOD;
    }
    for (int i = 0; i < (int)adj[cur].size(); i++) {
        int next = adj[cur][i];
        if (next != fa) {
            int nextnum = arr[next];
            pointsum[cur] += nextnum;
            sum2[cur] += nextnum * nextnum;
            int temp = max1[cur];
            if (nextnum > max1[cur]) {
                max1[cur] = nextnum;
                max2[cur] = temp;
            } else {
                max2[cur] = max(max2[cur], nextnum);
            }
            f(next, cur);
        }
    }
    return;
}
signed main() {
    cin >> n;
    int a, b;
    for (int i = 1; i < n; i++) {
        a = read();
        b = read();
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 1; i <= n; i++) {
        arr[i] = read();
    }
    f(1, 0);
    //（和平方-平方和）/2
    for (int i = 1; i <= n; i++) {
        sum = (sum + (pointsum[i] * pointsum[i] - sum2[i]) / 2) % MOD;
        mmax = max(mmax, max1[i] * max2[i]);
    }
    /*
        for (int i = 1; i <= n; i++) {
        for (int j = 0; j < (int)adj[i].size(); j++) {
            for (int k = j + 1; k < (int)adj[i].size(); k++) {
                int tempa = adj[i][j];
                int tempb = adj[i][k];
                if (tempa != Fa[i] && tempb != Fa[i]) {
                    int temp = arr[tempa] * arr[tempb];
                    mmax = max(mmax, temp);
                    sum = (sum + temp) % MOD;
                }
            }
        }
    }
    */

    cout << mmax << ' ' << (sum * 2) % MOD;
}