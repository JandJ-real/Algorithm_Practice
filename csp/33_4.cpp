#include <bits/stdc++.h>
//我要和blg同时在那天获得胜利
using namespace std;
#define int long long
inline int read() {
  int x = 0, f = 1;      // x: 存储结果, f: 符号标志(1正数, -1负数)
  char ch = getchar();   // 读取第一个字符
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
int c;//长度
int m;//有水格子数
int n;//操作次数
int cur;//目前有水的格子数
unordered_map<int,int> arr;//记录几号格子对应的水滴数
queue<int> que;//用于bfs
set<int> st;//顺序存储有水滴的格子编号
int flag = 0; //指示当前应该向哪边拓展
//dfs改bfs会好起来吗
void bfs(int a) { 
    //爆了才进行搜索
    //思路是如果到了边界就直接一次性搜完，因为单向好搜，如果不是边界就向左右依次递归。
    
   
    cur--;
     
      que.push(a);
      
      while(!que.empty()){
          int num = que.front();
          cout <<"1:"<< num << endl;
          que.pop();
              auto it=st.find(num);
             
              if(it==st.begin()){
                auto itr = it;
                itr++;
                int r = *itr;
                st.erase(*(it));
                if (++arr[r] >= 5) {
                  que.push(r);
                  cur--;
                }
              }
              if (it == --st.end()) {
                auto itl = it;
                itl--;
                int l = *itl;
                st.erase(*(it));
                if (++arr[l] >= 5) {
                  que.push(l);
                  cur--;
                }
              }
              auto itl = it;
              auto itr = it;
              itl--, itr++;
              int l = *itl;
              int r = *itr;
              st.erase(*(it));
              if(++arr[l]==5){
                que.push(l);
                cur--;
              }
              if (++arr[r] == 5) {
                que.push(r);
                cur--;
              }
          
      }

    
}
signed main() {
    cin >> c >> m >> n;
   
    cur = m;
    int a, b;
    for (int i = 0; i < m;i++){
        a = read();
        b = read();
        arr[a] = b;
        st.insert(a);
    }
    //以上为输入
    
    for (int i = 1; i <= n;i++){
        //n次操作
        a = read();
        if(++arr[a]>=5)
        bfs(a);
        for (int j = 1; j <= 5;j++){
            cout << arr[j] << ' ';
        }
        cout << endl;
        cout << cur << endl;
    }
}