#include <bits/stdc++.h>
using namespace std;
#define int long long
//实战一般直接暴力：拓扑排序+逐个节点对应的子树遍历，但是对于2e5的数据行不通
//所包含颜色的表达方式的优化？
//目前只是各个子树中每个颜色出现的桶，

//进阶（n,c:2x10^5） 重链剖分+启发式合并 见P9233.md
int n;
int arr[5005];
int fa[5005];
int d[5005];
int func[5005][5005];
void f(int cur) {
    func[cur][arr[cur]]++;
    int Fa = fa[cur];
    while (Fa != 0) {
        for (int i = 1; i <= 5000; i++) {
            func[Fa][i] += func[cur][i];
        }
        Fa = fa[Fa];
    }
    return;
}
int ans;
signed main() {
    cin >> n;
    ans = n;
    int a, b;
    for (int i = 1; i <= n; i++) {
        cin >> a >> b;
        arr[i] = a;
        func[i][a] = 1;
        fa[i] = b;
        d[b]++;
        d[i]++;
    }
    //拓扑排序！！！！
    queue<int> que;

    for (int i = 1; i <= n; i++) {
        if (d[i] == 1) {
            que.push(i);
        }
    }
    while (!que.empty()) {
        int num = que.front();
        que.pop();
        int Fa = fa[num];
        d[Fa]--;
        if (d[Fa] == 1) {
            que.push(Fa);
        }
        for (int i = 1; i <= 5000; i++) {
            func[Fa][i] += func[num][i];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 5000; j++) {
            if (func[i][j] != 0 && func[i][j] != func[i][arr[i]]) {
                // cout << i << ' ' << j << endl;
                ans--;
                break;
            }
        }
    }
    /*
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 3; j++) {
            cout << func[i][j] << ' ';
        }
        cout << endl;
    }
    */

    cout << ans;
    return 0;
}