#include <bits/stdc++.h>

using namespace std;
#define x first;
#define y second;
#define int long long
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
int n;//大小
int m;//老鼠出现总数
vector<int> t;
vector<pair<int, int>> arr;
int ted;//时刻终点
//dp[i][j][k]i时刻在(j,k)位置最多打死的老鼠数
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
signed main() {
    cin >> n >> m;
    t.resize(m + 1);
    arr.resize(m + 1);
    int tempa;
    int tempb;
    for (int i = 1; i <= m;i++){
        t[i] = read();
        tempa = read();
        tempb = read();
        arr[i] = {tempa, tempb};
    }
    ted = t[m];
    int i;
    //初始化
    for (i = 1; i <= m;i++){
if(t[i]>1){
    break;
}
dp[1][arr[i].x][arr[i].y] = 1;
    }
    for (; i <= m;i++){
        int cur = t[i];
        for (int j = 1; j <= n;j++){
            for (int k = 1; k <= n;k++){
                for (int z = 0; z<4;z++){
                    int fromx = j + dx[z];
                    int fromy = k + dy[z];
                    if(isright(fromx)&&isright(fromy)){
                        dp[cur][j][k] = dp[cur - 1][fromx][fromy];//修改逻辑
                    }
                } }
        }
    }
 }