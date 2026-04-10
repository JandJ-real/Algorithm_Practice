#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m, x;
int arr[100005];
// map<int, int> mmap;
vector<int> prefix(100005, INT_MAX);

//这里因为仅仅用于查找，最好换成unordered_map find的复杂度为O(1)
//有序表map的find复杂度为O(logn)
map<int, int> mmap; //记录该值对应的最小下标

// 异或性质 + 哈希表

signed main() {
    cin >> n >> m >> x;
    int temp;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    for (int i = n - 1; i >= 1; i--) {
        int num = INT_MAX;
        temp = arr[i] ^ x;
        auto it = mmap.find(temp);
        if (it != mmap.end()) {
            num = it->second;
        }
        prefix[i] = min(prefix[i + 1], num);
        mmap[arr[i]] = i;// 更新即是最小下标
    }
    int l, r;
    while (m--) {
        cin >> l >> r;
        if (prefix[l] <= r) {
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
    }
}