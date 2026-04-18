#include <bits/stdc++.h>
using namespace std;
#define int long long
//map 容器 1.理解他的本质：键值对数组 2.55*1e9为啥不爆 3.基础函数的使用
int n, k;
int arr[55][10005];
int num[55]; //第i组有效元素个数
double ans;
map<int, bool> m[55];
//  交集/并集
signed main() {
    cin >> n;
    int tempa, tempb;
    for (int i = 1; i <= n; i++) {
        cin >> tempa;

        for (int j = 1; j <= tempa; j++) {
            cin >> tempb;
            arr[i][j] = tempb; // 0~1e9
            if (m[i].find(tempb) == m[i].end()) {
                m[i][tempb] = true;
                num[i]++;
            }
        }
    }
    cin >> k;
    int a, b;
    while (k--) {
        cin >> a >> b;
        //每一组：都为一
        int jiao = 0;
        for (auto it = m[a].begin(); it != m[a].end(); it++) {
            int x = it->first;
            if (m[b].find(x) != m[b].end()) {
                jiao++;
            }
        }
        ans = (double)jiao * 100 / (num[a] + num[b]-jiao);
        printf("%.2f", ans);
        cout << '%' << endl;
    }
}