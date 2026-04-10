#include <bits/stdc++.h>
using namespace std;
#define int long long
string str;
int ans;
void judge(int l, int r) {
    while (l < r) {
        if (str[l] > str[r]) {
            ans++;
            return;
        } else if (str[l] < str[r]) {
            return;
        } else {
            l++, r--;
        }
    }
}
signed main() {
    cin >> str;
    int n = str.size();
    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len - 1 < n; l++) {
            judge(l, l + len - 1);
        }
    }
    cout << ans;
    return 0;
}