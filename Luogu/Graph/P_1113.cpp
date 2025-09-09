#include <bits/stdc++.h>
//拓扑排序 (最早完成任务 板子题)
//拓扑排序的作用：在图的dp中满足无后效性的条件
//tmd总是在1-based和0-based上出问题
using namespace std;
// 邻接表表示法的图
#define int long long
int n; //点
int m; //边
vector<int> arr;
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
  arr.resize(n + 1);
  vector<int> g[n + 1]; //有向无环图 邻接表
                        // i->j
  int a;
  int b;
  int c;
  for (int i = 1; i <= n; i++) {
    a = read();

    b = read();
    arr[i] = b;
    //cout << arr[i] << ' ';
    c = read();
    while (c) {
      g[c].push_back(a);
      c = read();
    }
  }

  //计算所有点的入度
  vector<int> ind(n + 1, 0); // 1-based
  for (int i = 1; i <= n; ++i) {
    for (size_t j = 0; j < g[i].size(); j++) {
      ind[g[i][j]]++;
    }
  }
 
  //压入初始入度为0的点
  queue<int> q;
  vector<int> dp(n + 1, 0);
  for (int i = 1; i <= n; ++i) {
    if (!ind[i] ) {
      q.push(i);
      dp[i] = arr[i];//同时初始化
    }
  }
  //维护队列，入度和dp数组(bfs)
  
  while (!q.empty()) {
    int u = q.front();
    q.pop();



      for (size_t i =0; i < g[u].size(); i++) {
        //u->v
        int v = g[u][i];
        ind[v]--;
        if (ind[v] == 0) {
          q.push(v);
        }
        dp[v] = max(dp[v], dp[u] + arr[v]);
      }
  }
  
  //输出最大的dp值
  for (int i = 1; i <= n; i++) {
      //cout << dp[i] << ' ';
      ans = max(ans, dp[i]);
  }
  cout << ans;
}