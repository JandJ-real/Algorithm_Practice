#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, x;
// n-1个石头  2x次从左往右
int prefix[100005];
int ans;
signed main() {
    cin >> n >> x;
    int target = 2 * x;
    int num;
    for (int i = 1; i <= n - 1; i++) {
        cin >> num;
        prefix[i] = prefix[i - 1] + num;
    }
    int l = 1, r = n;
    while (l <= r) {
        int mid = (l + r) / 2;
        int flag = 1;
        for (int i = 1; i + mid - 1 <= n - 1; i++) {
            if (prefix[i + mid - 1] - prefix[i - 1] < target) {
                //不够
                flag = 0;
                break;
            }
        }
        if (flag) {
            r = mid - 1;
            ans = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << ans;
}