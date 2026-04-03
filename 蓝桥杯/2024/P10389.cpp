#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, k, t;
int arr[100005];
int ans = -1;
bool f(int a) {
    vector<int> brr(a + 1);
    vector<int> prebrr(a + 1);
    vector<int> prebrr2(a + 1);
    brr[0] = 0, prebrr[0] = 0, prebrr2[0] = 0;
    for (int i = 1; i <= a; i++) {
        brr[i] = arr[i];
    }

    sort(brr.begin(), brr.end());
    for (int i = 1; i <= a; i++) {
        prebrr[i] = prebrr[i - 1] + brr[i];

        prebrr2[i] = prebrr2[i - 1] + brr[i] * brr[i];
    }

    for (int i = 1; i + k - 1 <= a; i++) {
        double temp = ((double)(prebrr2[i + k - 1] - prebrr2[i - 1]) / k) - pow(((double)(prebrr[i + k - 1] - prebrr[i - 1]) / k), 2);
        //cout << prebrr2[i + k - 1] - prebrr2[i - 1] << endl;
        //cout << prebrr[i + k - 1] - prebrr[i - 1] << endl;
        //cout << a << ' ' << temp << endl;
        if (temp < (double)t) {
            return true;
        }
    }

    return false;
}
signed main() {
    cin >> n >> k >> t;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    // k~n
    //二分check
    int l = k, r = n;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (f(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans;
}