#include <bits/stdc++.h>
using namespace std;
#define int long long

//贪心练习较少，极为不敏感，能贪心就贪心

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
int sum;
int num;  //累计团练习次数
signed main() {
    cin >> n >> s;
    int a, b;
    vector<pair<int, int>> pc(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a >> b;
        sum += a;
        pc[i].first = a;
        pc[i].second = b;
        m = max(m, b);
    }
    pc[0] = {0, 0};
    sort(pc.begin(), pc.end(), mycompare);
    int index = 1;
    while (sum >= s) {
        num++;
        while (pc[index].second <= num) {
            sum -= pc[index].first;
            index++;
        }
    }
    ans = num * s;
    for (int i = index; i <= n; i++) {
        ans += pc[i].first * (pc[i].second - num);
    }
    cout<<ans;
}