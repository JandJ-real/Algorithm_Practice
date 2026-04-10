#include <bits/stdc++.h>
using namespace std;
#define int long long
int ans = INT_MAX;
int n, m;
vector<int> arr;
int prefix[31];
//暴力搜索+剪枝
//改进：折半搜索:将n个分为 前n/2 和 后n/2
//（在n>=30时比暴力优，本题没必要，反而慢，一不注意就超时）
//统计出前的可能得到的结果和对应的count，m-可能的结果得到差值，再在后的可能结果中找，并实时更新总的count
bool mycompare(int a, int b) {
    if (a > b) {
        return true;
    }
    return false;
}
vector<pair<int, int>> qian;
map<int, int> hou;
void dfs_mid(int l, int r, int sum, int count, int flag) {
    if (sum > m) {
        //上界剪枝
        return;
    }

    if (flag && sum + prefix[n] - prefix[l] < m) {
        // qian的下界剪枝
        return;
    }
    if (!flag && sum + prefix[n / 2 + 1] + prefix[n] - prefix[l] < m) {
        // hou的下界剪枝
        return;
    }

    if (l > r) {
        if (flag) {
            int target = m - sum;
            auto a = hou.find(target);
            if (a != hou.end()) {
                ans = min(ans, count + a->second);
            }
        } else {
            if (hou.find(sum) != hou.end()) {
                hou[sum] = min(hou[sum], count);
            } else {
                hou[sum] = count;
            }
        }
        return;
    }
    dfs_mid(l + 1, r, sum + arr[l], count, flag);
    dfs_mid(l + 1, r, sum + arr[l] / 2, count + 1, flag);
    dfs_mid(l + 1, r, sum, count, flag);
    return;
}
void dfs(int cur, int sum, int count) {
    // cout << cur << ' ' << sum << ' ' << count << endl;
    if (sum + prefix[n] - prefix[cur] < m) {
        //关键剪枝
        // cout<<"ceshi"<<endl;
        return;
    }
    if (sum == m) {
        ans = min(ans, count);
        return;
    }
    if (sum > m) {
        return;
    }
    if (cur >= n) {
        return;
    }
    if ((arr[cur] / 2) > m - sum) {
        dfs(cur + 1, sum, count);
        return;
    }
    if (cur + 1 <= n) {
        dfs(cur + 1, sum + arr[cur] / 2, count + 1);
        dfs(cur + 1, sum + arr[cur], count);
        dfs(cur + 1, sum, count);
    }
    return;
}
signed main() {
    int a;
    cin >> n >> a;
    m = 2 * a;
    // cout << m;
    arr.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> a;
        arr[i] = 2 * a;
    }
    sort(arr.begin(), arr.end(), mycompare);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + arr[i]; // i之后：prefix[n]-prefix[i+1]
        // cout <<i+1<<':'<< prefix[i + 1] << endl;
    }

    //两种方法  如下：

    //暴力+剪枝
    /*
dfs(0, 0, 0);
    */

    //二分+剪枝

    dfs_mid(n / 2 + 1, n - 1, 0, 0, 0);
    dfs_mid(0, n / 2, 0, 0, 1);

    if (ans == INT_MAX) {
        cout << -1;
        return 0;
    }

    cout << ans;
}