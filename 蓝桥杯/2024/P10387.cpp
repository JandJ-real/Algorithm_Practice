#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
int s;
int ans;
int m;  //最多次数
bool mycompare(pair<int, int> a, pair<int, int> b) {
    if (a.second < b.second) {
        return true;
    } else {
        return false;
    }
}
signed main() {
    cin >> n >> s;
    int a, b;
    vector<pair<int, int>> pc(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a >> b;
        pc[i].first = a;
        pc[i].second = b;
        m = max(m, b);
    }
    pc[0] = {0, 0};
    sort(pc.begin(), pc.end(), mycompare);
    ans = s * m;

    int temp;

    for (int i = n - 1; i >= 0; i--) {
        if (pc[i].second != pc[i + 1].second) {
            int num = pc[i].second;
            temp = s * num;
            // cout << temp << endl;
            for (int j = i + 1; j <= n; j++) {
                temp += pc[j].first * pc[j].second;
                temp -= (num * pc[j].first);
            }
            // cout << i << ' ' << temp << endl;
            ans = min(ans, temp);
        }
    }
    cout << ans;
    /*
        ans = s * m;
    // cout << ans << endl;
    for (int i = m - 1; i >= 0; i--) {
        int temp = ans - (m - i) * s;
        int cur = n;
        cout << i << ' ' << cur << endl;
        cout << (cur && ((pc[cur].second - i) > 0));
        while (cur && ((pc[cur].second - i) > 0)) {
            temp += (pc[cur].first * (pc[cur].second - i));
            cur--;
            cout << i << ' ' << cur << endl;
        }
        ans = min(ans, temp);
    }
    cout << ans;
    */
}