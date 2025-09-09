#include <bits/stdc++.h>
//缩点 板子题
//缩点即 将有向有环图转化为有向无环图(该转换是满足题目要求的)
//    即 将图中的强连通分量合并为单个节点
//求带权图的最大连通分量？
using namespace std;
// 邻接表表示法的图
#define int long long

int ans = 0; // ans答案
//---------------------------------------------------
const int N = 1e4 + 10, M = 1e5 + 10; //点数和边数
int a[N], u[M], v[M]; //记录缩点前后的权值，记录原边起点，记录原边终点

int dfn[N], low[N], cnt = 0, stk[N], top = 0, instk[N], belong[N];
// dfn深搜时节点u被搜索的次序(时间戳)  low能回溯到的最早的栈中节点的次序号
//  cnt记录访问次序，stk是栈，top栈顶，instk是否在栈里，belong属于哪个强连通分量

int n;       //点
int m;       //边
vector<int> arr;
vector<int> g[N];

//找强连通分量(belong数组)并计算了缩点值(a数组)
void tarjan(int u) { // tarjan算法
  dfn[u] = low[u] = ++cnt, stk[++top] = u, instk[u] = 1;

  for (auto i : g[u]) {             //遍历邻居
    if (!dfn[i]) {                  //没有访问过
      tarjan(i);                    //去递归它
      low[u] = min(low[u], low[i]); //更新low值 最早
    } else if (instk[i])            //访问过且在栈中
      low[u] = min(low[u], dfn[i]); //更新low值
  }

  if (dfn[u] == low[u]) { //找到一个SCC
    do {
      instk[stk[top]] = 0;  //出栈
      belong[stk[top]] = u; //这个结点属于u代表的SCC
      if (stk[top] != u)
        a[u] += a[stk[top]]; //缩点累加权值   但是权值不用重复加自己
    } while (stk[top--] != u); //循环直到栈顶是自己  自己也是算在scc里的
  }
}



//----------------------------------------------------------
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
  arr.resize(n + 1); // 1-based
  g->resize(n + 1);  //有向无环图 邻接表
                     // i->j

  for (int i = 1; i <= n; i++) {
    a[i] = read();
  }
  for (int i = 1; i <= m; i++) {
    u[i] = read();
    v[i] = read();
    g[u[i]].push_back(v[i]);
  }
  //以上为输入
  //进行缩点
  for (int i = 1; i <= n; i++) {
    if (!dfn[i])
      tarjan(i);
  }
  /*for (int i = 0; i <= n; i++) {
    cout << a[i] << endl;
  }*/

  // 计算所有点的入度
  vector<int> ind(n + 1, 0); // 1-based
                             // 用belong和a数组重建图
  vector<int> g2[N];

  for (int i = 1; i <= m; i++) {
    int x = belong[u[i]];
    int y = belong[v[i]];
    if (x != y) {
      g2[x].push_back(y);
      ind[y]++; //顺便初始化入度
    }
  }

  //压入初始入度为0的点
  queue<int> q;
  vector<int> dp(n + 1, 0);
  for (int i = 1; i <= n; ++i) {
    if (!ind[i] && belong[i] == i) {
      //入度为0且是强连通分量代表
      q.push(i);
      dp[i] = a[i]; //同时初始化
    }
  }
  //维护队列，入度和dp数组(bfs)

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (size_t i = 0; i < g2[u].size(); i++) {
      // u->v
      int v = g2[u][i];
      ind[v]--;
      if (ind[v] == 0) {
        q.push(v);
      }
      dp[v] = max(dp[v], dp[u] + a[v]);
    }
  }

  for (int i = 0; i <= n; i++) {
    ans = max(ans, dp[i]);
  }
  cout << ans;
}