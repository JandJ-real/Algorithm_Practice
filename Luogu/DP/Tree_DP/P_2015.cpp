#include <bits/stdc++.h>
//树上dp板子题 (本题为0-1背包)
//在图这种数据结构下思考问题(进行dp)有点困难啊
using namespace std;
#define int long long
int n;       //结点数
int m;//边数
int q;//需要保留的树枝数量
vector<int> siz;//在dfs中记录以i为根的子树有多少边(即树枝)，便于确定dp的范围
vector<vector<pair<int, int>>> g;
vector<vector<int>> dp;
// i的子树上保留j条边，至多保留的苹果数
int ans=0;
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
//树的经典dfs
//整体逻辑是自底向上的
/*void dfs(int u, int fa) {
  for (int i=0;i<g[u].size();i++) { // 遍历u的所有邻居v
int v=g[u][i].first;//枚举邻居
    if (v != fa) {     // 避免回到父节点(只因是无向图)
      dfs(v, u);
      siz[u] += siz[v]+1;//加上邻居的那条边
    }
  }
}
void dp1(int u,int fa){
  for (int i = 0; i < g[u].size(); i++) {
    int v = g[u][i].first; //枚举邻居
    if(v!=fa){
      dp1(v, u);
      //u->v
      for(int j=min(siz[u],q);j>=1;j--){
        //枚举u为根的保留边量
        for(int k=min(siz[v],j-1);k>=0;k--){
          //枚举以v为根的保留边量
          //转移
          dp[u][j] = max(dp[u][j], dp[u][j - k - 1] + dp[v][k] +
g[u][i].second);
        }
      }

    }
  }

}*/
//以上二者可合并
void dfs(int u, int fa) {
  for (size_t i = 0; i < g[u].size(); i++) { // 遍历u的所有邻居v
    int v = g[u][i].first;                //枚举邻居
    if (v != fa) { // 避免回到父节点(只因是无向图)
      dfs(v, u);
      siz[u] += siz[v] + 1; //加上邻居的那条边

      //进行dp (树上背包)
      //dp[i][j]中的i对应着一个背包容量，j对应取的物品的重量，似乎好理解一点了
      //递归是为了从叶子开始初始化dp数组和siz数组，只因树不像数组那样是线性的可以直接找到起点
      for (int j = 1; j <= min(siz[u], q); j++) {
        //枚举u为根的保留边量
        for (int k = min(siz[v], j - 1); k >= 0; k--) {
          //枚举以v为根的保留边量，0-1背包所以倒序
          //转移
          dp[u][j] =
              max(dp[u][j], dp[u][j - k - 1] + dp[v][k] + g[u][i].second);
        }
      }
    }
  }
}

signed main() {
n=read();
siz.resize(n + 1,0);
g.resize(n + 1);
dp.resize(n+1);
for(int i=0;i<=n;i++){
  dp[i].resize(n + 1,0);
}
q = read();
m = n - 1;

//1是根节点 必有两儿子
int a, b, c;
for(int i=1;i<=m;i++){
    a = read();
    b = read();
    c = read();
    g[a].push_back({b,c});
    g[b].push_back({a,c});
}
//以上为输入

//每个树枝牵连一些树枝 对应一个总值

dfs(1,0);//构建siz数组 同时进行dp

cout << dp[1][q];
}