#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
    cin >> n;
    vector<vector<int>> area(n, vector<int>(n));
   
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> area[i][j];
            }
        }

        vector<vector<int>> prefix(n + 1, vector<int>(n + 1));
        for (int i = 0; i <= n; i++) {
          prefix[0][i] = 0;
          prefix[i][0] = 0;
        }
        for (int j = 1; j <= n;j++)
            for (int i = 1; i <= n; i++)
            {
                prefix[j][i] = prefix[j][i - 1] + area[j - 1][i - 1];
            }
        for (int j = 1; j <= n;j++){
            for (int i = 1; i <= n;i++){
                prefix[i][j] = prefix[i - 1][j] + prefix[i ][j ];
            }
        }
        /*
        for (int j = 0; j <= n; j++) {
          for (int i = 0; i <= n; i++) {
              cout << prefix[j][i] << ' ';
          }
          cout << endl;
        }*/
        int lx, rx, ly, ry;
        int ans = INT_MIN;
        for (lx = 1; lx <n;lx++){
            for (ly = 1; ly <n;ly++){
                for (rx = lx ; rx <= n;rx++){
                    for (ry = ly ; ry <= n;ry++){
                        ans = max(ans, prefix[rx][ry] + prefix[lx-1][ly-1] - prefix[lx-1][ry] - prefix[rx][ly-1]);
                    }
                }
            }
        }
        cout << ans << endl;
}