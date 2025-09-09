#include <bits/stdc++.h>
//到达的编号最大结点
// 狗屎一样的优化
// 题解：反向建边再从大到小dfs，访问过的不再访问，可以降低到O(n);
using namespace std;
// 邻接表表示法的图
int n; //点
int m; //边
int ans = -1;
vector<int> dp;
class Graph {
  //注意顶点序号的0-based 与 1-based
public:
  int V;                              // 顶点数
  vector<vector<pair<int, int>>> adj; // 邻接表: [顶点][(邻接顶点, 权重)]
  bool directed;                      // 是否为有向图
  // 构造函数
  Graph(int vertices, bool isDirected = false)
      : V(vertices), directed(isDirected) {
    adj.resize(V);
  }

  // 添加边 (无向图添加双向边，有向图添加单向边)
  void addEdge(int u, int v, int weight = 1) {
    adj[u].emplace_back(v, weight);
    if (!directed) {
      adj[v].emplace_back(u, weight);
    }
  }

  // 获取顶点数
  int getVertices() const { return V; }

  // 获取邻接表
  const vector<vector<pair<int, int>>> &getAdjacencyList() const { return adj; }

  // 打印图
  void printGraph() {
    for (int i = 0; i < V; ++i) {
      cout << "顶点 " << i << " 的邻居: ";
      for (const auto &neighbor : adj[i]) {
        cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
      }
      cout << endl;
    }
  }
};

bool mycompare(pair<int, int> a, pair<int, int> b) {
  if (a.first < b.first) {
    return true;
  } else {
    return false;
  }
}
// BFS - 广度优先搜索
vector<int> BFS(const Graph &graph, int start) {
  int V = graph.getVertices();
  vector<bool> visited(V, false);
  vector<int> result;
  queue<int> q;

  visited[start] = true;
  q.push(start);

  while (!q.empty()) {
    int current = q.front();
    q.pop();
    result.push_back(current);

    for (const auto &neighbor : graph.getAdjacencyList()[current]) {
      int next = neighbor.first;
      if (!visited[next]) {
        visited[next] = true;
        q.push(next);
      }
    }
  }

  return result;
}

// DFS - 深度优先搜索 (递归辅助函数)
void DFSUtil(const Graph &graph, int v, vector<bool> &visited,
             vector<int> &result) {
  visited[v] = true;
  result.push_back(v);
  ans = max(ans, v);
  ans = max(ans, dp[v]);
  if(ans==n-1)
      return;
  for (const auto &neighbor : graph.getAdjacencyList()[v]) {
    int next = neighbor.first;
    if (!visited[next]) {
        
        DFSUtil(graph, next, visited, result);
    }
  }
}

// DFS - 深度优先搜索
vector<int> DFS(const Graph &graph, int start) {
  int V = graph.getVertices();
  vector<bool> visited(V, false);
  vector<int> result;
  DFSUtil(graph, start, visited, result);
  return result;
}
void printPath(const vector<int> &path) {
  for (size_t i = 0; i < path.size(); ++i) {
    // cout<<path[i];
    cout << path[i] + 1; // 1-based
    if (i < path.size() - 1)
      cout << ' ';
  }
  cout << endl;
}
signed main() {
  cin >> n >> m;
  dp.resize(n);
  Graph g(n, true); //无向图则只需一个参数，有向图需要加一个true参数
  int a;
  int b;
  for (int i = 1; i <= m; i++) {
    cin >> a >> b;
    //防止越界
    g.addEdge(a - 1, b - 1); //只需遍历的话，不需要加权值(默认是1)
  }                          /*  for (int i = 0; i < n; i++) {
                              sort(g.adj[i].begin(), g.adj[i].end(), mycompare);
                            }*/
for(int i=0;i<n;i++){
    DFS(g, i);
    dp[i] = ans;
    cout << ans+1 << ' ';
    ans = -1;
}

}