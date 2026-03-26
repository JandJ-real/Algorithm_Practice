

#include <bits/stdc++.h>
using namespace std;
#define int long long
// 0：13  1：12
int arr[26];
int ans;
void judge() {
    if (!((arr[1] + arr[2] + arr[3] + arr[4] + arr[5]) % 5))
        return;
    if (!((arr[6] + arr[7] + arr[8] + arr[9] + arr[10]) % 5))
        return;
    if (!((arr[11] + arr[12] + arr[13] + arr[14] + arr[15]) % 5))
        return;
    if (!((arr[16] + arr[17] + arr[18] + arr[19] + arr[20]) % 5))
        return;
    if (!((arr[21] + arr[22] + arr[23] + arr[24] + arr[25]) % 5))
        return;
    if (!((arr[1] + arr[6] + arr[11] + arr[16] + arr[21]) % 5))
        return;
    if (!((arr[2] + arr[7] + arr[12] + arr[17] + arr[22]) % 5))
        return;
    if (!((arr[3] + arr[8] + arr[13] + arr[18] + arr[23]) % 5))
        return;
    if (!((arr[4] + arr[9] + arr[14] + arr[19] + arr[24]) % 5))
        return;
    if (!((arr[5] + arr[10] + arr[15] + arr[20] + arr[25]) % 5))
        return;
    if (!((arr[1] + arr[7] + arr[13] + arr[19] + arr[25]) % 5))
        return;
    if (!((arr[5] + arr[9] + arr[13] + arr[17] + arr[21]) % 5))
        return;
    ans++;
    return;
}
void dfs(int cur, int w, int b) {
    if (cur > 25) {
        judge();
        return;
    }
    if (w < 13) {
        arr[cur] = 0;
        dfs(cur + 1, w + 1, b);
    }
    if (b < 12) {
        arr[cur] = 1;
        dfs(cur + 1, w, b + 1);
    }
}
signed main() {
    dfs(1, 0, 0);
    cout << ans;
}

