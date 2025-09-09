#include <bits/stdc++.h>
//图的dp问题离不开拓扑排序！！！！！！
using namespace std;
// 邻接表表示法的图
#define int long long
int n; //点
int m; //边
vector<vector<int>> arr(1505,vector<int>(1505));


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
  n = read();//点
  m = read();//边
  
  vector<int> g[n + 1]; //有向无环图 邻接表
                        // i->j
  int a;
  int b;
  int c;
  vector<int> ind(n + 1, 0); // 1-based
  for (int i = 1; i <= m; i++) {
    /*  a = read();

    b = read();
    c = read();*/

    cin>>a>>b>>c;
    
    
    g[a].push_back(b);
    ind[b]++;
    arr[a][b] = c;//a->b a<b
  }
//以上为输入

  //计算所有点的入度
//处理除1外入度为0的点
queue<int> q;
/*  for(int i=2;i<=n;i++){
      if(!ind[i]){
        for (size_t j = 0; j < g[i].size(); j++) {
            int k = g[i][j];
            ind[k]--;
        }
  }
  }*/

for (int i = 2; i <= n; i++) {

  if (!ind[i])
    q.push(i);
   } //找出初始除1外入度为0的点
   while (!q.empty()) {
     int x = q.front();
     q.pop();
     for (size_t i = 0; i < g[x].size(); i++)
       if (!--ind[g[x][i]])
         q.push(g[x][i]);
   }//处理所有除1外入度为1的点

  //压入1
  
  vector<int> dp(n + 1, -1e9);//从1到i最长路
  dp[1] = 0;
  q.push(1);
  //维护队列，入度和dp数组(bfs)

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (size_t i = 0; i < g[u].size(); i++) {
      // u->v
      int v = g[u][i];
      dp[v] = max(dp[v], dp[u] + arr[u][v]);
      ind[v]--;
      if (ind[v] == 0) {
        q.push(v);
      }
      
    }
  }

//如果未到达n
if(dp[n]==-1e9){
    cout << "-1"; 
}
else
  cout << dp[n];
}