#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m;
double ans=0;
vector<pair<int, int>> arr(1005);
bool mycompare(pair<int, int> a, pair<int, int> b) {
    if (a.first * b.second > a.second * b.first) {
        return true;
    } else {
        return false;
    }
}
signed main() {
    cin >> n >> m;
    int temp;
    // int prefix = 1;
    // int g = 0;
    // int g2;
    for (int i = 1; i <= n; i++) {
        cin >> temp;
        /*
        prefix *= temp;
        if (i == 1) {
            g = temp;
        } else {
            g2 = temp;
            g = gcd(g, g2);
        }
        */
        arr[i].second = temp;
    }
    // int index = prefix / g;
    for (int i = 1; i <= n; i++) {
        cin >> temp;
        arr[i].first = temp;
        // arr[i].first = (temp * index) / arr[i].second;
    }
    // int intans = 0;
    sort(arr.begin() + 1, arr.begin() + 1 + n, mycompare);

    for (int i = 1; i <= n; i++) {
        if (arr[i].second <= m && m) {
            // cout<<"ceshi:"<<arr[i].second<<' '<<"m:"<<m<<endl;
            ans += arr[i].first;
            m -= arr[i].second;
        } else {
            // cout << "ceshi:" << arr[i].second <<" m:"<<m<< endl;
            ans += (((double)arr[i].first) / arr[i].second) * m;
            m = 0;
            break;
        }
    }
    // ans = ((double)intans) / index;
    printf("%.2f", ans);
    return 0;
}