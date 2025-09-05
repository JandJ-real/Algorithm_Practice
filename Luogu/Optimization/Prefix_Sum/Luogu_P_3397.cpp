#include<bits/stdc++.h>
using namespace std;
int n;//地毯大小
int m;//地毯个数
int main(){
    cin >> n >> m;
    vector<vector<int>> prefix(n+1, vector<int>(n+1,0));
    pair<int, int> l;
    pair<int, int> r;
    //差分预处理
    for (int i = 0; i < m;i++){
        cin >> l.first >> l.second >> r.first >> r.second;
        prefix[l.first - 1][l.second - 1] += 1;
        prefix[r.first][r.second] += 1;
        prefix[l.first - 1][r.second] -= 1;
        prefix[r.first][l.second - 1]-=1;
    }
//前缀和输出
    for (int i = 0; i < n;i++){
        for (int j = 1; j < n;j++){
            prefix[j][i] += prefix[j - 1][i];
        }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 1; j < n; j++) {
        prefix[i][j] += prefix[i][j-1];
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
          cout << prefix[i][j] << ' ';
      }
      cout << endl;
    }
}
