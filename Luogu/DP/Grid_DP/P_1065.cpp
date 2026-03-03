#include <bits/stdc++.h>
//每个工件必须按工序顺序完成加工
//必须按安排顺序安排加工
//必须靠前插入
using namespace std;
int m; //机器数，即工序总数
int n; //工件数
int main() {
  cin >> m >> n;

  //安排顺序
  vector<int> shunxu(m * n);
  for (int i = 0; i < m * n; i++) {
    cin >> shunxu[i];
  }

  //每个工件的每个工序使用的机器编号
  vector<vector<int>> jiqi(m, vector<int>(n));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cin >> jiqi[i][j];
    }
  }

  //每个工件的每个工序所需时间
  vector<vector<int>> time(m, vector<int>(n));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cin >> time[i][j];
    }
  }

  //记录访问次数，即当前工序数，初始化为0工序
  vector<int> flag(n, 0);
  //记录每个工件的当前时间
  vector<int> worktime(n, 0);
  //记录每个机器在每个时间是否有事干,初始化为不在工作
  vector<vector<int>> isworking(m, vector<int>(1e4, 0));
  //每个机器的终点，初始化为0，输出结果用
  vector<int> end(m, 0);




  for (int i = 0; i < n * m; i++) {
   //获取信息：

    //当前工件
    int now = shunxu[i] - 1;
    //当前工序
    int num = (flag[now]++);
    //当前工件工序加工时间
    int nowtime = time[now][num];
    //当前工件工序所用机器
    int machine = jiqi[now][num] - 1;


    int k;
    int fflag = 0;


    for (k = worktime[now] + 1; k < 1e4; k++){
      //找到在前一个工序后的，最靠前的，足够长的空间
      
      for (int ii = k; ii < k + nowtime;ii++){
        if(isworking[machine][ii]){
          fflag = 1;
          break;
        }
          
      }
        if (!fflag)
        {
          for (int j = k; j < k + nowtime; j++)
          {
            isworking[machine][j] = 1;
          }
          end[machine] = max(k + nowtime - 1, end[machine]);
          break;
        }
        fflag = 0;
      }
        // 当前工件的最远时间更新
        worktime[now] =k+nowtime-1;
  }
  sort(end.begin(), end.end());
  
  cout << end[m - 1] << endl;
}