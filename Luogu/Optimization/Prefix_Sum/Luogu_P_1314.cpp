#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;//矿石个数
int m;//区间个数
int s;//标准值
int maxw=1;//最大质量
//int ans;//待求W
int target = LLONG_MAX; // 当前最小目标值
signed main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    cin >> n >> m >> s;
    vector<pair<int, int>> scale(m);
    vector<pair<int, int>> stone(n + 1); // 凑数
    int tempw;
    for (int i = 1; i <= n; i++)
    {
        // 重量和价值
        cin >> tempw >> stone[i].second;
        maxw = max(maxw, tempw);
        stone[i].first = tempw;
    }
    //保存区间
    for (int i = 0; i < m;i++){
        cin >> scale[i].first >> scale[i].second;
    }
        // 对每个W可能取值预处理
        vector<int> prefixnum(n + 1);
    vector<int> prefixv(n + 1);
    prefixnum[0] = 0;
    prefixv[0] = 0;
    //int flag[200001];
    //memset(flag, 0, sizeof(flag));
    
        int i ;
        int left = 1;
        int right = maxw;
        while(left<=right){
            i = (left + right) / 2;
            // each W
            for (int j = 1; j <= n; j++) {
              /*if (flag[j]) {
                prefixnum[j] = prefixnum[j - 1];
                prefixv[j] = prefixv[j - 1];
                continue;
              }*/
              if (stone[j].first >= i) {

                prefixnum[j] = prefixnum[j - 1] + 1;
                prefixv[j] = prefixv[j - 1] + stone[j].second;
              } else {
                //flag[j] = 1;
                prefixnum[j] = prefixnum[j - 1];
                prefixv[j] = prefixv[j - 1];
              }
            }
            /*
            //调试
            for (int ii = 0; ii <= n;ii++){
                cout << prefixnum[ii] << ' ' << prefixv[ii] << endl;

            }*/
            int l;
            int r;
            int temp = 0;
            for (int k = 0; k < m; k++) {
              l = scale[k].first;
              r = scale[k].second;
              temp += (prefixnum[r] - prefixnum[l - 1]) *
                      (prefixv[r] - prefixv[l - 1]);
            }
            if ((s - temp) > 0) {
              right = i - 1;
            } else {
              left = i + 1;
            }
            temp = abs(s - temp);

            if (temp < target) {

              target = temp;
              // ans = i;
            }
        }

        
    
    cout << target << endl;
}