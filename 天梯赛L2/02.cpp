#include <bits/stdc++.h>
using namespace std;
#define int long long
//得：map 以 int作为键 比 string作为键 快得多
int n;
string str;
unordered_map<int, pair<int, int>> m;
unordered_map<int, pair<int, int>> m2;
unordered_map<int, int> prevnode;
int tong[10005];
int read(string str) {
    int len = str.length();
    len--;
    int index = 1;
    int ans = 0;
    for (; len > 0; len--) {
        ans += ((str[len] - '0') * index);
        index *= 10;
    }
    if (str[0] == '-') {
        return -ans;
    } else {
        return ans + index * (str[0] - '0');
    }
}
void tostr(int x) {
    if (x < 0) {
        cout << x;
        return;
    }
    if (x <= 9) {
        cout << "0000" << x;
        return;
    }
    if (x <= 99) {
        cout << "000" << x;
        return;
    }
    if (x <= 999) {
        cout << "00" << x;
        return;
    }
    if (x <= 9999) {
        cout << '0' << x;
        return;
    }
    cout<<x;
}
signed main() {

    cin >> str >> n;
    string temp1, temp2;
    int num;
    for (int i = 1; i <= n; i++) {
        cin >> temp1 >> num >> temp2;
        m[read(temp1)] = {num, read(temp2)};
        // cout << read(temp1) << ' ' << read(temp2)<<endl;
        //  cout << m[temp1].second << endl;
    }

    int start = read(str);
    int tp1, tp2;
    tp1 = read(str);
    // gop
    while (tp1 != -1) {
        tp2 = tp1;
        tp1 = m[tp1].second;
        prevnode[tp1] = tp2;
    }
    // cout << "ceshi" << endl;
    //记录新链表的头尾巴
    int head1 = start;
    int head = -1;
    int tail = -1;
    while (start != -1) {
        // cout << "ceshi" << endl;
        // cout << start << endl;
        int num = m[start].first;
        int next = m[start].second;
        if (tong[abs(num)]++) {
            // cout << tong[abs(m[start].first)] << endl;
            //已经有过了
            if (tail != -1) {
                m2[tail].second = start;
            } else {
                head = start;
            }
            m2[start] = {num, -1};
            tail = start;
            m[prevnode[start]].second = next;
            prevnode[next] = prevnode[start];
        }
        start = next;
    }
    // cout << head << endl;
    while (head1 != -1) {
        tostr(head1);
        cout << ' ' << m[head1].first << ' ';
        tostr(m[head1].second);
        cout << endl;
        head1 = m[head1].second;
    }
    // cout << endl;
    while (head != -1) {
        tostr(head);
        cout << ' ' << m2[head].first << ' ';
        tostr(m2[head].second);
        cout << endl;
        head = m2[head].second;
    }
}