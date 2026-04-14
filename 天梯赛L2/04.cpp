#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
struct node {
    int l, r;
    int fa;
} arr[1005];
int point[1005];
bool ismirror = false;
void check(int root, int l, int r) {
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
}