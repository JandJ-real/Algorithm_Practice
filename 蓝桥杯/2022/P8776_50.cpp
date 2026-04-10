#include <bits/stdc++.h>
using namespace std;
#define int long long
//最终的结果一定长这样：g[l] -- kkkkkkk -- f[r]
int n, k;
int arr[100005];
int f[100005], g[100005];
int ans;
// f:以i开头，最长不降子序列的长度
// g:以i结尾，最长不降子序列长度
signed main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    arr[n + 1] = INT_MAX;
    for (int i = 1; i <= n; i++) {
        g[i] = 1;
        for (int j = 1; j < i; j++) {
            if (arr[j] <= arr[i]) {
                g[i] = max(g[i], g[j] + 1);
            }
        }
        //cout << g[i] << endl;
    }
    for (int i = n; i >= 1; i--) {
        f[i]=1;
        for (int j = n; j > i; j--) {
            if (arr[j] >= arr[i]) {
                f[i] = max(f[i], f[j] + 1);
            }
        }
        //cout << f[i] << endl;
    }
    for (int i = 1; i + k - 1 <= n; i++) {
        int l = i - 1, r = i + k;
        if (arr[l] <= arr[r]) {
            ans = max(ans, f[r] + g[l] + k);
        }
    }
    cout << ans;
}