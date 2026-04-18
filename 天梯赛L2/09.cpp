#include <bits/stdc++.h>
using namespace std;
#define int long long
//简单的模拟
int n;
struct nod {
    int num; //抢到的个数
    int id;
    int got; //净收入
};
vector<nod> arr(10005);
bool mycompare(nod a, nod b) {
    if (a.got > b.got) {
        return true;
    }
    if (a.got == b.got && a.num > b.num) {
        return true;
    }
    if (a.got == b.got && a.num == b.num && a.id < b.id) {
        return true;
    }
    return false;
}
signed main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        arr[i].id = i;
        arr[i].num = 0;
        arr[i].got = 0;
    }
    int k;
    for (int i = 1; i <= n; i++) {
        cin >> k;
        int people, value;
        int sum = 0;
        for (int j = 1; j <= k; j++) {
            cin >> people >> value;
            sum += value;
            arr[people].got += value;
            arr[people].num++;
        }
        arr[i].got -= sum;
    }
    sort(arr.begin() + 1, arr.begin() + n + 1, mycompare);
    for (int i = 1; i < n; i++) {
        cout << arr[i].id << ' ';
        printf("%.2f", (double)arr[i].got / 100);
        cout << endl;
    }
    cout << arr[n].id << ' ';
    printf("%.2f", (double)arr[n].got / 100);
}