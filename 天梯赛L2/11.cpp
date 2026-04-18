#include <bits/stdc++.h>
using namespace std;
#define int long long
//神人题目，说n<=30 ,但是键值不止30
// zhong qian
int n;
struct nod {
    int l = -1, r = -1;
};
vector<nod> arr(1005);
int zhong[1005];
int qian[1005];
int m[1005];
int root;
void dfs(int l1, int r1, int l2, int r2) {
    if (l1 >= r1 || l2 >= r2) {
        return;
    }
    int gen = qian[l2];
    int index = m[gen]; // zhong中根节点位置
    int lnum = index - l1;
    int rnum = r1-l1-lnum;
    if (lnum) {
        arr[gen].l = qian[l2 + 1];
        dfs(l1, index - 1, l2 + 1, l2 + lnum);
    }
    if (rnum) {
        arr[gen].r = qian[l2 + lnum + 1];
        dfs(index + 1, r1, l2 + lnum + 1, r2);
    }
    return;
}
signed main() {
    cin >> n;
    int x;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        zhong[i] = x;
        m[x] = i;
    }
    for (int i = 1; i <= n; i++) {
        cin >> qian[i];
    }
    root = qian[1];
    dfs(1, n, 1, n);
    queue<int> que;
    cout << root;
    que.push(arr[root].r);
    que.push(arr[root].l);
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        if (x == -1) {
            continue;
        } else {
            que.push(arr[x].r);
            que.push(arr[x].l);
            cout << ' ' << x;
        }
    }
    return 0;
}