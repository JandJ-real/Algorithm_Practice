#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
vector<int> arr(100005);
int prefix[100005];
int diff;
int outgoing;
int introverted;
/*
Outgoing #: N1
Introverted #: N2
Diff = N3
*/
signed main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    sort(arr.begin() + 1, arr.begin() + 1 + n);
    for (int i = 1; i <= n; i++) {
        prefix[i] = prefix[i - 1] + arr[i];
    }
    int mid = n / 2;
    if (!(n % 2)) {
        //偶数
        outgoing = mid;
        introverted = mid;
        diff = abs(prefix[mid] - prefix[0] - (prefix[n] - prefix[mid]));
    } else {
        int temp = prefix[mid] - prefix[0] - (prefix[n] - prefix[mid + 1]);
        if (abs(temp + arr[mid + 1]) > abs(temp - arr[mid + 1])) {
            outgoing = mid;
            introverted = mid + 1;
            diff = abs(temp + arr[mid + 1]);
        } else {
            outgoing = mid + 1;
            introverted = mid;
            diff = abs(temp - arr[mid + 1]);
        }
    }
    cout << "Outgoing #: " << outgoing << endl;

    cout << "Introverted #: " << introverted << endl;
    cout << "Diff = " << diff;
    return 0;
}