#include <bits/stdc++.h>

#define rep(i, m, n) for (int i = m; i <= n; ++i)
#define INF 2147483647

using namespace std;

inline int read() {
  int s = 0, w = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      w = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    s = s * 10 + ch - '0';
    ch = getchar();
  }
  return s * w;
}

const int MAXN = 10010;


vector<int> g[MAXN]; // 无权图
// 如果是有权图，使用：vector<pair<int, int>> g[MAXN]; 存储 (邻居, 权值)

int w[MAXN], n, siz[MAXN];
long long ans = INF, f[MAXN];

//获取f[1] siz[]数据
void dfs(int u, int fa, int dep) {
  siz[u] = w[u];
  for (int v : g[u]) { // 遍历u的所有邻居v
    if (v != fa) {     // 避免回到父节点(只因是无向图)
      dfs(v, u, dep + 1);
      siz[u] += siz[v];
    }
  }
  f[1] += w[u] * dep;
}

void dp(int u, int fa) {
  //遍历邻居
  for (int v : g[u]) {
    if (v != fa) {
        //根节点转移
      f[v] = f[u] + siz[1] - siz[v] * 2;
      dp(v, u);
    }
  }
  ans = min(ans, f[u]);
}

int a, b;
int main() {
  n = read();
  rep(i, 1, n) {
    w[i] = read();
    a = read();
    b = read();
    
    if (a) {
      g[i].push_back(a);
      g[a].push_back(i);
    }
    if (b) {
      g[i].push_back(b);
      g[b].push_back(i);
    }
  }
  //以上为输入
  dfs(1, 0, 0);
  dp(1, 0);
  printf("%lld\n", ans);
  return 0;
}