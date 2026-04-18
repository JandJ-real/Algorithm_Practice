#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m; //<=500  <=5000
int k;
//有环
//每次重新并查集  但是时间复杂度？  怎么计算
// for (auto& temp : arr)  没加引用是副本！！！！
int fa[505];
void init() {
    for (int i = 0; i < n; i++) {
        fa[i] = i;
    }
    return;
}
int find(int x) {
    if (fa[x] == x) {
        return x;
    }
    return fa[x] = find(fa[x]);
}
void merge(int x, int y) {
    if (find(x) == find(y)) {
        return;
    }
    x = find(x), y = find(y);
    fa[x] = y;
    return;
}
int count() {
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (fa[i] == i) {
            ans++;
        }
    }
    return ans;
}
struct edge {
    int x, y;
    bool flag = 1; //可用性(默认可用)
};
vector<edge> arr;
signed main() {
    cin >> n >> m;
    int u, v;
    init();
    for (int i = 1; i <= m; i++) {
        cin >> u >> v;
        edge temp;
        temp.x = u, temp.y = v;
        arr.push_back(temp);
        merge(u, v);
    }
    /*
    for (int i = 0; i < n; i++) {
        cout << fa[i] << endl;
    }
    for (int i = 0; i <= n; i++) {
        cout << fa[i] << endl;
    }
    */

    int landcount = count();
    // cout << "land:" << landcount << endl;
    cin >> k;
    int flag = 0;
    if (k == n) {
        flag = 1;
    }
    int x;
    while (k--) {
        cin >> x;
        init();
        for (auto& temp : arr) {
            if (!temp.flag || temp.x == x || temp.y == x) {
                temp.flag = 0;
                continue;
            }
            merge(temp.x, temp.y);
        }
        int nowlandcount = count();
        // cout <<"now:"<< nowlandcount << endl;
        /*
       for (int i = 0; i < n; i++) {
            cout << fa[i] << endl;
        }
        */

        if (nowlandcount >= landcount + 2) {
            cout << "Red Alert: City " << x << " is lost!";
        } else {
            cout << "City " << x << " is lost.";
        }
        landcount = nowlandcount;
        if (k >= 1) {
            cout << endl;
        }
    }

    if (flag) {
        cout << endl;
        cout << "Game Over." ;
    }
}