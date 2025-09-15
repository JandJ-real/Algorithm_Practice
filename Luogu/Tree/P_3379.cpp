#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500010;

vector<int> G[MAXN];
vector<pair<int, int>> Q[MAXN];
int parent[MAXN], ancestor[MAXN];
bool vis[MAXN];
int ans[MAXN];

int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }

void tarjan(int u) {
  vis[u] = true;
  ancestor[u] = u;

  for (int v : G[u]) {
    if (!vis[v]) {
      tarjan(v);
      parent[v] = u;
      ancestor[find(u)] = u;
    }
  }

  for (auto &[v, id] : Q[u]) {
    if (vis[v]) {
      ans[id] = ancestor[find(v)];
    }
  }
}

int main() {
  int n, m,s;
  cin >> n >> m>>s;

  // 建树
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }

  // 添加查询
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    Q[u].emplace_back(v, i);
    Q[v].emplace_back(u, i);
  }

  // 初始化并查集
  for (int i = 1; i <= n; i++)
    parent[i] = i;

  tarjan(s); //s是根节点

  // 输出结果
  for (int i = 0; i < m; i++) {
    cout << ans[i] << endl;
  }

  return 0;
}