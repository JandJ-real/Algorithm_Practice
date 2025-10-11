#include <bits/stdc++.h>
using namespace std;
//优化
//1.对tep和ans这两个路径数组使用reserve预分配内存，对于大数据量可减少vector的反复扩容
//2.
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
int n;//结点数目
vector<int> ans;
vector<int> tep;
vector<int> arr;
vector<vector<int>> adj;
int Max = 0;
void dfs(vector<int>& tep,int cur,int curpos){
    //cout << "curpos:" << curpos << endl;
    tep.push_back(curpos);
    cur += arr[curpos];
    if(!adj[curpos].size()){
        if(cur>Max){
            Max = cur;
            ans = tep;
            /* for (size_t i = 0; i < ans.size();i++){
                    cout << ans[i] << ' ';
    }
    cout << endl;*/
               
        }
        return;
    }
    for (size_t i = 0; i < adj[curpos].size();i++){
        dfs(tep, cur, adj[curpos][i]);
    }
}
signed main() {
    cin >> n;
    arr.resize(n);
    adj.resize(n);
    for (int i = 0; i < n;i++){
        arr[i] = read();
    }
    for (int i = 0; i < n - 1;i++){
        int j = i;
        while((++j)<=n-1){
int temp = read();
if(temp){
    adj[i].push_back(j);//认为是单向的
}
        }
    }
    /*   for (int i = 0; i < n;i++){
        for (size_t j = 0; j < adj[i].size();j++){
            cout << adj[i][j] << ' ';
        }
        cout << endl;
    }*/
 
        // 以上为输入
        // 如何记录路径，并在维护最大值的同时维护路径
        for (int i = 0; i < n; i++)
            dfs(tep, 0, i);

    for (size_t i = 0; i < ans.size(); i++)
    {
        cout << ans[i]+1 << ' ';
    }
            cout << endl;
            cout << Max;
}