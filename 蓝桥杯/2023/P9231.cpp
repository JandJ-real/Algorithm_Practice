#include <bits/stdc++.h>
using namespace std;
#define int long long
int l, r;
int ans;
//数学题一定要用数学
signed main() {
    cin >> l >> r;
    //数学分析：当且仅当 奇数和四的倍数 是平方差的结果
    for (int i = l; i <= r; i++) {
        if (i % 2 || !(i % 4))
            ans++;
    }
    cout << ans;
    return 0;
}
/*
                                MLE做法
    cin >> l >> r;
    vector<int> arr(r - l + 1, 0);
    for (int i = 1; i <= 40000; i++) {
        for (int j = i - 1; j >= 0; j--) {
            int num = (i + j) * (i - j);
            int index = num - l;
            if (num >= l && num <= r && !arr[index]) {
                arr[index]++;
                ans++;
            }
        }
    }
    cout << ans;
    return 0;

*/