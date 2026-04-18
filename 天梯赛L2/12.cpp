#include <bits/stdc++.h>
using namespace std;
#define int long long
//从未见过
//push_heap  在vector上建堆，之前从未接触过（默认大顶堆）
//与priority_queue的区别：这个优先队列应该是只能用来每次找一个最小的元素
int n, m; //<=1000 <=20
// int arr[1005];
//构建小顶堆
/*
5 4
46 23 26 24 10
24 is the root
26 and 23 are siblings
46 is the parent of 23
23 is a child of 10
*/
// 10 23 26 46 24
int ma[20005];
signed main() {
    cin >> n >> m;
    //-10000~10000
    int temp;
    vector<int> arr;
    for (int i = 1; i <= n; i++) {
        cin >> temp;
        arr.push_back(temp);
        push_heap(arr.begin(), arr.end(), greater<int>());
    }
    for (int i = 0; i < n; i++) {
        ma[arr[i] + 10000] = i + 1;
    }

    int a, b;
    string str;
    while (m--) {
        cin >> a;
        cin >> str;
        if (str == "and") {
            cin >> b;
            a = ma[a + 10000], b = ma[b + 10000];
            if (a > b) {
                swap(a, b);
            }
            if (b - a == 1 && !(a % 2)) {
                cout << 'T' ;
            } else {
                cout << 'F' ;
            }
            getline(cin, str);
            // continue;
        } else {
            cin >> str;
            if (str == "a") {
                cin >> str;
                cin >> str;
                cin >> b;
                a = ma[a + 10000], b = ma[b + 10000];
                if (a == 2 * b || a == 2 * b + 1) {
                    cout << 'T' ;
                } else {
                    cout << 'F' ;
                }
                // continue;
            } else {
                cin >> str;
                if (str == "root") {
                    a = ma[a + 10000];
                    if (a == 1) {
                        cout << 'T' ;
                    } else {
                        cout << 'F' ;
                    }
                    // continue;
                } else {
                    cin >> str;
                    cin >> b;
                    a = ma[a + 10000], b = ma[b + 10000];
                    if (b / 2 == a) {
                        cout << 'T' ;
                    } else {
                        cout << 'F' ;
                    }
                    // continue;
                }
            }
        }
        if (m >= 1) {
            cout << endl;
        }
    }
}