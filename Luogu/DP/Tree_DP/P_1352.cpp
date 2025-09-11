#include <bits/stdc++.h>
//第一次只拿了九十分，原因是没有把状态转移的所有情况想到(不选该结点时，子结点也可不选),总是认为具有对称性
using namespace std;
#define int long long
int n;//点
int m;//边
vector<int> arr;//结点权值
vector<vector<int>> g;
vector<int> flag;//用于寻找根结点
vector<pair<int,int>> dp;//1,,0
int gen;//根节点
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
//直系来了就不来
//核心代码
void dfs(int u){
   
    for (size_t i = 0; i < g[u].size();i++){
        int v=g[u][i];//u->v
        dfs(v);
        dp[u].first = max(dp[u].first,dp[u].first+dp[v].second);
        dp[u].second = max(dp[u].second, max(dp[u].second + dp[v].first,
                                             dp[u].second + dp[v].second));
    }
}
signed main() {
    n = read();
    m = n - 1;
    arr.resize(n + 1);
    g.resize(n + 1);
    flag.resize(n + 1,1);
    dp.resize(n + 1);
    int a, b;
    for (int i = 1; i <= n; i++)
    {
        a = read();
        dp[i] = {a, 0};
    }
    for (int i = 1; i <= m; i++){
a=read();
b=read();
g[b].push_back(a);//b->a
flag[a] = 0;
    }
    //以上为输入
    //寻找根结点
    for (int i = 1; i <= n; i++) {
      if (flag[i])
        gen = i;
}
dfs(gen);
cout << max(dp[gen].first, dp[gen].second);
}