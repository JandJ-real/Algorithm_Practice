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
// vector<vector<int>> dist;
// int ans;
// int ans1;
vector<int> adj[50005];
vector<int> siz(50005);
vector<int> flag(50005, 0);
vector<int> anses;
int curmax = INT_MAX;
int ans = 0;
//以某个点为根节点遍历整个无根树，找到最大连通分量最小的点（重心），加入数组anses
//实际上是用有根树的思维解决无根树的问题
void f(int cur) {
    siz[cur] = 1;
    flag[cur] = 1;
    int mmax = 0;
    for (size_t i = 0; i < adj[cur].size(); i++) {
        int next = adj[cur][i];
        if (!flag[next]) {
            f(next);
        } else {
            continue;
        }
        siz[cur] += siz[next];
        mmax = max(mmax, siz[next]);
    }
    mmax = max(mmax, n - siz[cur]);
    if (mmax < curmax) {
        curmax = mmax;
        anses.clear();
        anses.push_back(cur);
    } else if (mmax == curmax) {
        anses.push_back(cur);
    }
}
//找到重心后再深搜得到距离之和的最小值
void dfs(int cur, int fa, int deep) {
    ans += deep;
    for (size_t i = 0; i < adj[cur].size(); i++) {
        int next = adj[cur][i];
        if (next != fa) {
            dfs(next, cur, deep + 1);
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
    f(1);
    sort(anses.begin(), anses.end());
dfs(anses[0],0,0);
    cout << anses[0] << ' ' << ans;
    /*    dist.resize(n + 1);

    for (int i = 1; i <= n; i++) {
        dist[i].resize(n + 1);
        for (int j = 1; j <= n; j++) {
            dist[i][j] = INT_MAX;
        }
        dist[i][i] = 0;
    }
    int a, b;
    for (int i = 1; i < n; i++) {
        a = read();
        b = read();
        dist[a][b] = 1;
        dist[b][a] = 1;
    }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
    //vector<int> arr(n + 1, 0);
    int temp = INT_MAX;
    for (int i = 1; i <= n; i++) {
        int sum = 0;
        for (int j = 1; j <= n; j++) {
            sum += dist[i][j];
        }
        if (sum < temp) {
            temp = sum;
            ans = i;
            ans1=sum;
        }
    }
    cout << ans << ' ' << ans1;*/
}