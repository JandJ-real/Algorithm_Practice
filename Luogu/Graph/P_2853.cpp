#include <bits/stdc++.h>
//收获：tarjan大法好
//      弗洛伊德算法(顶点对可达性，顶点对最短距离) 均可用bitset优化
//也可直接深搜，如下所述
//从k个奶牛分别dfs，用mk[i]表示第i个牧场被遍历过多少次，最后只有mk[i]==k的牧场满足条件。无权的有向图也可以用vector存储。
using namespace std;
// 邻接表表示法的图
#define int long long
int knum;//奶牛数量
vector<int> arr;//奶牛位置1-based
int ans = 0; // ans答案

//---------------------------------------------------
const int N = 1e3 + 10, M = 1e5 + 10; //点数和边数
int a[N], u[M], v[M]; //记录缩点前后的权值，记录原边起点，记录原边终点

int dfn[N], low[N], cnt = 0, stk[N], top = 0, instk[N], belong[N];
// dfn深搜时节点u被搜索的次序(时间戳)  low能回溯到的最早的栈中节点的次序号
//  cnt记录访问次序，stk是栈，top栈顶，instk是否在栈里，belong属于哪个强连通分量

int n; //点
int m; //边

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
int flag[N];
signed main() {
  // 1-based
  knum = read();
  n = read();
  m = read();

  arr.resize(knum + 1);//1-based
  g->resize(n + 1);  //有向无环图 邻接表
                     // i->j

  for (int i = 1; i <= n; i++) {
    a[i] = 1;
  }
  for(int i=1;i<=knum;i++){
      arr[i]=read();
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
  /*  //初始化dp数组
    vector<vector<int>> dp(n + 1, vector<int>(n+1,0));
    for(int i=1;i<=n;i++){
        dp[i][i] = 1;
    }

     for(int i=1;i<=m;i++){
          dp[belong[u[i]]][belong[v[i]]] = 1;
      }



      //弗洛伊德算法
      for (int i = 1; i <= n; i++) {
        for(int j=1;j<=n;j++){
            for(int k=1;k<=n;k++){
    if(dp[belong[j]][belong[i]]&&dp[belong[i]][belong[k]]){
        dp[belong[j]][belong[k]] = 1;
    }
            }

        }
    }*/
  //判断各对顶点的可达性
  //用 位集(bitset) 优化弗洛伊德算法
  vector<bitset<N>> reach(n+1);//1-based
  //初始化reach
  for (int i = 1; i <= n; i++) {
    reach[i][i] = 1;//自环
  }

  for (int i = 1; i <= m; i++) {
    reach[belong[u[i]]][belong[v[i]]] = 1;//邻边
  }
  //替代原弗洛伊德算法
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
        if(reach[belong[i]][belong[j]]){
            reach[belong[i]] |= reach[belong[j]];
        }
    }
  }

  //将可达性转移到dp数组中
  vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
        dp[i][j] = reach[i][j];
    }
  }

  //对奶牛的强连通分量预处理
  unordered_set<int> momo;
  for(int i=1;i<=knum;i++){
      momo.insert(belong[arr[i]]);
  }

  for(int i=1;i<=n;i++){
    //枚举所有强连通分量
    int temp=belong[i];
    int flag2=1;

    //cout << "temp:" << temp;
    if(!flag[temp]){
        //如果没有搜索过
        for (auto it = momo.begin();it!=momo.end();it++)
        {
            // 枚举所有有奶牛的强连通分量
            int num = belong[*it];
            // cout << "num:" << num;
            if (!dp[num][temp])
            {
                // cout << "temp:" << temp <<' '<<"num:" << num ;
                flag2 = 0;
                break;
            }
        }
      //如果一直没有break
      if(flag2){
        //说明可行
        //cout << temp << endl;
        ans += a[temp];
      }
      flag[temp] = 1;
    }
    
  }
 

  cout << ans;
}