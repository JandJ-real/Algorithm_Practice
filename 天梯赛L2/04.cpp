#include <bits/stdc++.h>
using namespace std;
#define int long long
//得：边界条件的把握
int n;
int point[1005];
bool ismirror = false;
int flag = 1;
int hou[1005];
int in = 0;
void check(int root, int l, int r) {
    //本质上l永远=root+1
    //这里的边界条件怎么把握？
    /*
    if (l == r) {
        hou[in++] = point[root];
        hou[in++] = point[root + 1];
        return;
    }
    if (l > r || root > l || root > r) {
        hou[in++] = point[root];
        return;
    }
    */
    if (root > r) {
        return;
    }
    int l1, l2;
    int r1, r2;
    l1 = l, l2 = l;
    r2 = r, r1 = r;
    if (ismirror) {
        while (point[l2] >= point[root] && l2 <= r) {
            l2++;
        }
        while (point[r1] < point[root] && r1 >= l) {
            r1--;
        }
    } else {
        while (point[l2] < point[root] && l2 <= r) {
            l2++;
        }
        while (point[r1] >= point[root] && r1 >= l) {
            r1--;
        }
    }
    if (l2 - l1 + r2 - r1 != r - l + 1) {
        //不能完全覆盖，则不是
        flag = 0;
        return;
    }
    check(root + 1, l1 + 1, l2 - 1);
    check(r1 + 1, r1 + 2, r2);
    hou[in++] = point[root];
    return;
}
signed main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> point[i];
    }
    //找到第一个大于root的位置
    int index = 2;
    while (point[index] < point[1] && index <= n) {
        index++;
    }
    //如果这后面还有小于root的位置，如果要符合，只能是镜像
    for (; index <= n; index++) {
        if (point[index] < point[1]) {
            ismirror = true;
        }
    }

    check(1, 2, n);
    if (flag) {
        cout << "YES" << endl;
        for (int i = 0; i < n - 1; i++) {
            cout << hou[i] << ' ';
        }
        cout << hou[n - 1];
    } else {
        cout << "NO" << endl;
    }
}