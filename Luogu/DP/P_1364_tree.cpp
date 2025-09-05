#include <bits/stdc++.h>
using namespace std;
//只建一个医院，鉴定为邮局简化版

//数据规模不大，尝试打表解决
int n;
int ans = INT_MAX;
int temp = 0;
vector<int> arr(n + 1);
vector<int> dad(n + 1, 0);
vector<pair<int, int>> son(n + 1);

void dfs(int a,int step,vector<int>& flag){
  if (!flag[a]) {
    flag[a] = 1;
  } else {
    return;
  }
  temp += step * arr[a];
  int i = dad[a];
  int j = son[a].first;
  int k = son[a].second;

  if (i)
  {
      

      dfs(i, step + 1, flag);
  }
if(j){
    
    
    dfs(j, step + 1, flag);
}
if (k ) {
  
  
  dfs(k, step + 1, flag);
}
return;
}
signed main() {
    cin >> n;

    for(int i=1;i<=n;i++){
        cin >> arr[i] >> son[i].first >> son[i].second;
    }
    for(int i=1;i<=n;i++){
        int l = son[i].first;
        int r = son[i].second;
        if (l)
            dad[l] = i;
        if(r)
            dad[r] = i;
    }
    //以上为输入
    for (int i = 1; i <= n;i++)
{
    vector<int> flag(n+1, 0);
    dfs(i, 0, flag);
    ans = min(ans, temp);
    temp = 0;
}
cout << ans;
}