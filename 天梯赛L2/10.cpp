#include <bits/stdc++.h>
using namespace std;
#define int long long
//简单的并查集+enemy数组
/*
这里假设朋友的朋友也是朋友。但敌人的敌人并不一定就是朋友，朋友的敌人也不一定是敌人。只有单纯直接的敌对关系才是绝对不能同席的。
*/
/*
对每个查询输出一行结果：
如果两位宾客之间是朋友，且没有敌对关系，则输出No
problem；
如果他们之间并不是朋友，但也不敌对，则输出OK；
如果他们之间有敌对，然而也有共同的朋友，则输出OK
but...；
如果他们之间只有敌对关系，则输出No way。
*/
int n, m, k; // 人数 关系数 查询数
int fa[105];
int enemy[105][105];
int find(int x) {
    if (fa[x] == x) {
        return x;
    }
    return fa[x] = find(fa[x]);
}
void merge(int a, int b) {
    if (find(a) == find(b)) {
        return;
    }
    int aa = find(a);
    int bb = find(b);
    fa[aa] = bb;
    return;
}
void check(int a, int b) {
    if (find(a) == find(b)) {
        if (enemy[a][b]) {
            cout << "OK but...";
        } else {
            cout << "No problem";
        }
    } else {
        if (enemy[a][b]) {
            cout << "No way";
        } else {
            cout << "OK";
        }
    }
    return;
}
signed main() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    int a, b, x;
    for (int i = 1; i <= m; i++) {
        cin >> a >> b >> x;
        if (x == 1) {
            merge(a, b);
        } else {
            enemy[a][b] = 1;
            enemy[b][a] = 1;
        }
    }
    while (k-- != 1) {
        cin >> a >> b;
        check(a, b);
        cout << endl;
    }
    cin >> a >> b;
    check(a, b);
}