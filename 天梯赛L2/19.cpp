#include <bits/stdc++.h>
using namespace std;
#define int long long
int n; //<=5000
int m; //<=10000
map<string, int> arr;
int aver;
vector<pair<string, int>> v;
string str;
vector<string> ans;
signed main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> str;
        arr[str] = 1;
    }
    cin >> m;
    string a;
    int b;
    for (int i = 1; i <= m; i++) {
        cin >> a >> b;
        aver += b;
        v.push_back({a, b});
    }
    for (auto x : v) {
        a = x.first;
        b = x.second;
        if (b * m > aver && arr.find(a) == arr.end()) {
            ans.push_back(a);
        }
    }
    if (ans.empty()) {
        cout << "Bing Mei You" << endl;
    } else {
        sort(ans.begin(), ans.end());
        for (auto s : ans) {
            cout << s << endl;
        }
    }
    return 0;
}