#include <bits/stdc++.h>
using namespace std;
#define int long long
int gb(int a, int b) { return a * b / gcd(a, b); }
vector<int> arr(2050, INT_MAX);
void dfs(int cur) {
    if (cur == 2021) {
        return;
    }
    for (int i = 1; i <= 21; i++) {
        if (cur + i <= 2021) {
            arr[cur + i] = min(arr[i] + gb(cur + i, cur), arr[cur + i]);
        }
        dfs(cur + i);
    }
    return;
}
signed main() {

    /*
    // 2位数：1组0~9->1个0~9
    int arr[10];
    for (int i = 0; i <= 9; i++) {
        arr[i] = 2021;
    }
    int cur = 0, flag = 1;
    cout << "ceshi1" << endl;
    while (flag) {
        cur++;
        cout << cur << endl;
        int temp = cur;
        while (temp) {
            int next = temp % 10;
            if (!(--arr[next]))
                flag = 0;
            temp /= 10;
        }
    }
    cout << cur; //3181
    */

    /*
    set<pair<pair<int, int>, int>> m;
    vector<pair<int, int>> arr;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 21; j++) {
            arr.push_back({i, j});
        }
    }
    for (auto it = arr.begin(); it != arr.end(); it++) {
        for (auto it2 = it + 1; it2 != arr.end(); it2++) {
            int a, b, c;
            a = (it2->second - it->second);
            b = (it->first - it2->first);
            c = it2->first * it->second - it->first * it2->second;
            if (a < 0 || (a == 0 && b < 0)) {
                a = -a, b = -b, c = -c;
            }
            int g = gcd(gcd(abs(a), abs(b)), abs(c));

            m.insert({{a / g, b / g}, c / g});
        }
    }
    cout << m.size();  //40257
    */

    /*
    int n = 2021041820210418;
    int ans = 0;
    vector<int> arr;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            arr.push_back(i);
            if (n / i != i) {
                arr.push_back(n / i);
            }
        }
    }
    for (int i : arr) {
        for (int j : arr) {
            if ((n / i) % j == 0) {
                ans++;
            }
        }
    }
    cout << ans; // 2430
    */

    //最小公倍数？
    // a * b/ gcd(a.b)
    arr[1] = 0;
    dfs(1);
    cout << arr[2021];
}