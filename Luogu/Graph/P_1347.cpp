#include <bits/stdc++.h>
//三种情况：稳定的拓扑排序(每次进队的度为1的点只有一个)
//         成环(拓扑排序算法有内置判断)
//         其它 
using namespace std;
// 邻接表表示法的图
#define int long long
int n; //点
int m; //边
vector<int> arr;
int ans = 0;

int topologicalSort(vector<vector<int>> &g, int n,vector<int>& result) {
  int ans = 1;
  size_t V = n;
  // vector<int> inDegree(V, 0);
  //vector<int> result;

  // 计算入度
  // 计算所有点的入度
  vector<int> ind(n + 1, 0); // 1-based
  for (size_t i = 1; i <= V; ++i) {
    for (size_t j = 0; j < g[i].size(); j++) {
      ind[g[i][j]]++;
    }
  }
  

  queue<int> q;
  for (size_t i = 1; i <= V; ++i) {
    if (ind[i] == 0) {
      q.push(i);
    }
  }

  while (!q.empty()) {
    if(q.size()>1)
        ans = 0;
    int u = q.front();
    q.pop();
    result.push_back(u);

    for (size_t i = 0; i < g[u].size(); i++) {
      int v = g[u][i];
      ind[v]--;
      if (ind[v] == 0) {
        q.push(v);
      }
    }
  }

  if (result.size() != V) {
    return -1; // 存在环，无法拓扑排序
  }

  return ans;
}
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
  string str;
  for(int i=1;i<=n;i++){
      str += i + 'A' - 1;
  }
  m = read();
  
  vector<vector<int>> g(n + 1); //有向无环图 邻接表
                        // i->j

  char a;
  char b;
  char c;
  int aa;
  for (int i = 1; i <= m; i++) {
      cin >> a >> b >> c;
      int numa = a - 'A' + 1;
      int numb = c - 'A' + 1;
      if(b=='<'){
          g[numa].push_back(numb);
      }
      else{
        g[numb].push_back(numa);
      }
      //每加入一条边就进行一次拓扑排序
      vector<int> result;
      aa=topologicalSort(g, n,result);
      if(aa==0)
          continue;
    else if(aa==-1){
      cout << "Inconsistency found after "<< i<<" relations.";
      return 0;
    }
    else{
        cout << "Sorted sequence determined after " << i << " relations: ";
        for (size_t k = 0; k < result.size();k++){
            char str = result[k] - 1 + 'A';
            cout << str;
        }
        cout << '.';
        return 0;
    }
    }
    cout << "Sorted sequence cannot be determined.";
}