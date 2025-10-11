#include <bits/stdc++.h>
using namespace std;
//debug:
/*
1.修复马的落点，避免越界
2.long long √  还真有那么大
*/

//优化：
/*
问题：写的时候也发现了，空间上不仅要初始化地图，还要存储每一个相应位置的路径数，空间开销大
解决：滚动数组，只因每一个当前位置，只与当前行和前一行有关，其他的可以舍去
*/
//题解太优雅了，我不行了
#define int long long
#define x first
#define y second
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
//求路径条数
//数据量小，可以暴搜
pair<int, int> ed;
pair<int, int> ma;
int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
int dy[] = {-2, -1, 1, 2, 2, 1, -1, -2};
vector<vector<int>> mp;//1表示能走
vector<vector<int>> dp;//0表示不可到达
signed main() {
    ed.x = read();
    ed.y = read();
    ma.x = read();
    ma.y = read();
    mp.resize(ed.x + 1);
    dp.resize(ed.x + 1);
    for (int i = 0; i <= ed.x;i++){
        mp[i].resize(ed.y + 1,1);
        dp[i].resize(ed.y + 1,0);
    }
    dp[0][0] = 1;
    mp[ma.x][ma.y] = 0;
    //mp[ed.x][ed.y] = 2;
    for (int i = 0; i < 8;i++){
        int nx = ma.x + dx[i];
        int ny = ma.y + dy[i];
        if(nx>=0&&ny>=0&&nx<=ed.x&&ny<=ed.y)
        mp[nx][ny] = 0;
    }
    //初始化地图
    for (int i = 0; i <= ed.x;i++){
        for (int j = 0; j <= ed.y;j++){
            if(!mp[i][j]){
                //不能走
                continue;
            }
            int prex = i - 1;
            int prey = j - 1;
            if(prex>=0){
                if(dp[prex][j]&&mp[prex][j]){
                    dp[i][j] += dp[prex][j];
                }
            }
             if(prey>=0){
                if(dp[i][prey]&&mp[i][prey]){
                    dp[i][j] += dp[i][prey];
                }
            }
        }
    }
    cout << dp[ed.x][ed.y];
}