#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
int arr[200005];
int prefix[200005];
int ans;
signed main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        prefix[i] = prefix[i - 1] + arr[i];
    }
    for (int i = 1; i < n; i++) {
        ans += (arr[i] * (prefix[n] - prefix[i]));
    }
    cout<<ans;
}