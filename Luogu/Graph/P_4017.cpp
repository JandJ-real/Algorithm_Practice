#include <bits/stdc++.h>
//取模要在每一个运算过程中取，只因为超过long long的范围！！！！！！！！！！！！
using namespace std;
// 邻接表表示法的图
#define int long long
int n; //点
int m; //边
int MOD = 80112002;
int ans = 0;
/*//寻找拓扑排序序列 返回拓扑排序序列数组
vector<int> topologicalSort(const Graph &graph) {
  int V = graph.getVertices();
  vector<int> inDegree(V, 0);
  vector<int> result;

  // 计算入度
  for (int i = 0; i < V; ++i) {
    for (const auto &neighbor : graph.getAdjacencyList()[i]) {
      inDegree[neighbor.first]++;
    }
  }

  queue<int> q;
  for (int i = 0; i < V; ++i) {
    if (inDegree[i] == 0) {
      q.push(i);
    }
  }

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    result.push_back(u);

    for (const auto &neighbor : graph.getAdjacencyList()[u]) {
      int v = neighbor.first;
      inDegree[v]--;
      if (inDegree[v] == 0) {
        q.push(v);
      }
    }
  }

  if (result.size() != V) {
    return {}; // 存在环，无法拓扑排序
  }

  return result;
}*/
inline int read() {
  int x = 0, f = 1;    // x: 存储结果, f: 符号标志(1正数, -1负数)
  char ch = getchar(); // 读取第一个字符

  while (!isdigit(ch)) { // 跳过非数字字符
    if (ch == '-')
      f = -1;       // 遇到负号，设置符号为负
    ch = getchar(); // 继续读取下一个字符
  }

  while (isdigit(ch)) {    // 处理数字部分
    x = x * 10 + ch - '0'; // 将字符转换为数字并累加
    ch = getchar();        // 读取下一个字符
  }

  return x * f; // 返回结果（考虑符号）
}
signed main() {
  // 1-based
  n = read();
  m = read();
  
  vector<int> g[n + 1]; //有向无环图 邻接表
                        // i->j
  int a;
  int b;
  
  for (int i = 1; i <= m; i++) {
    a = read();
    b = read();
    g[a].push_back(b);
  }

  //计算所有点的入度和出度
  vector<int> ind(n + 1, 0); // 1-based
  vector<int> outd(n + 1, 0);
  for (int i = 1; i <= n; ++i) {
    for (size_t j = 0; j < g[i].size(); j++) {
      ind[g[i][j]]++;
      outd[i]++;
    }
  }
  /* for(int i=1;i<=n;i++){
     cout << ind[i] << outd[i] << endl;

 }*/

  //压入初始入度为0的点
  queue<int> q;
  vector<int> dp(n + 1,0);//表示从入度为0的点到该点有几条路
  for (int i = 1; i <= n; ++i) {
    if (!ind[i]) {
      q.push(i);
      dp[i] = 1;//顺便初始化
    }
  }
  //维护队列，入度和dp数组(bfs)

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (size_t i = 0; i < g[u].size(); i++) {
      // u->v
      int v = g[u][i];
      ind[v]--;
      if (ind[v] == 0) {
        q.push(v);
      }
      dp[v] =(dp[v]+ dp[u])%MOD;
    }
  }
  /* for (int i = 1; i <= n; i++) {
      cout << dp[i] << endl;
    }*/

  for (int i = 1; i <= n; i++) {
    if(!outd[i])
        ans =(ans+ dp[i])%MOD;
}
  cout << (ans%MOD);
}