#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
set<int> temp;
vector<pair<string, int>> arr;
map<string, double> aver;
bool mycompare(pair<string, int> a, pair<string, int> b) {
    if (a.second > b.second) {
        return true;
    } else if (a.second == b.second && aver[a.first] < aver[b.first]) {
        return true;
    }
    return false;
}
signed main() {
    cin >> n;
    string str;
    int k;
    for (int i = 1; i <= n; i++) {
        cin >> str;
        cin >> k;
        int num;
        int sum = 0;
        for (int j = 1; j <= k; j++) {
            cin >> num;
            sum += num;
            temp.insert(num);
        }
        aver[str] = (double)k / temp.size();
        arr.push_back({str, temp.size()});
        temp.clear();
    }
    sort(arr.begin(), arr.end(), mycompare);

    for (int i = 0; i < 3; i++) {
        if (i < n) {
            cout << arr[i].first;
        } else {
            cout << '-';
        }
        if (i < 2) {
            cout << ' ';
        }
    }

    return 0;
}