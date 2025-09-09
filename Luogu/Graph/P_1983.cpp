#include <bits/stdc++.h>
//一开始tle  解决：用空间换时间，创建大数组存储状态(flag2)(一开始是用unordered_set去重，效率低)
//然后mle   解决：将while循环中的局部变量flag和flag2转为全局变量，在while循环开始时清空flag，而flag2保留。 解决原因：局部变量存储在栈上，空间小，一般为几mb，全局变量存储区域远大于栈(更有可能是flag2在栈中重复创建，记录被破坏，失去了去重的作用，导致vector g存储大量重复边，膨胀)
using namespace std;
// 邻接表表示法的图
#define int long long
int n; //火车站数
int m; //车次
int ans = 0;

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

vector<int> flag(1e3 + 5, 0);
vector<vector<int>> flag2(1e3 + 5, vector<int>(1e3 + 5, 0));
signed main() {
  // 1-based
  n = read();
  m = read();
  vector<int> g[n + 1]; //有向无环图 邻接表
                        // i->j
  int a;
  int b;
  int c;
  int d;
  while(m--) {
    a = read();
    vector<int> temp(a + 1);//1-based //停靠站
   
  fill(flag.begin(),flag.end(),0);
    for (int j = 1; j <= a ;j++){
        b = read();
        temp[j] = b;
        flag[b] = 1;
    }
    
        c = temp[1];
        d = temp[a];
        for (int k =c+1;k<=d-1;k++){
            if(!flag[k]){
                for(int j=1;j<=a;j++){
                    if(!flag2[temp[j]][k]){
                      g[temp[j]].push_back(k);
                      flag2[temp[j]][k] = 1;
                    }
                  
                }  
            }
        }
  //temp[j] --> k
        
      
  }
//以上为输入


  //计算所有点的入度
  vector<int> ind(n + 1, 0); // 1-based
  for (int i = 1; i <= n; ++i) {
    for (auto it = g[i].begin(); it != g[i].end(); it++) {
      ind[*it]++;
    }
  }

  //压入初始入度为0的点
  queue<int> q;
  vector<int> dp(n + 1, 0);//从度为1的点到该点的最长路径
  for (int i = 1; i <= n; ++i) {
    if (!ind[i]) {
      q.push(i);
      dp[i] = 1; //同时初始化
    }
  }
  //维护队列，入度和dp数组(bfs)

  while (!q.empty()) {

    int u = q.front();
    q.pop();


    for (auto it=g[u].begin(); it!= g[u].end(); it++) {
      // u->v
      int v = *it;
      ind[v]--;
      if (ind[v] == 0) {
        q.push(v);
      }
      dp[v] = max(dp[u] + 1,dp[v]);
      ans = max(ans, dp[v]);
    }


  }


  cout << ans;
}