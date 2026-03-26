#include <bits/stdc++.h>
using namespace std;
#define int long long
int ans;
//>50:篮球
int arr[10] = {13, 1, 2, 3, 5, 4, 4, 2, 2, 2};
int month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};  //特别讨论闰年
int month2[5] = {0, 31, 29, 31, 13};
signed main() {
    for (int y = 2000; y <= 2024; y++) {
        int mmax;
        if (y == 2024) {
            mmax = 4;
        } else {
            mmax = 12;
        }
        for (int m = 1; m <= mmax; m++) {
            int dmax;
            if (m == 2 && (y == 2000 || y == 2004 || y == 2008 || y == 2012 || y == 2016 || y == 2020))
                dmax = 29;
            else if (y == 2024) {
                dmax = month2[m];
            } else
                dmax = month[m];
            for (int d = 1; d <= dmax; d++) {
                int temp = 0;
                temp += arr[y / 1000];
                temp += arr[(y % 1000) / 100];
                temp += arr[(y % 100) / 10];
                temp += arr[y % 10];
                temp += arr[m / 10];
                temp += arr[m % 10];
                temp += arr[d / 10];
                temp += arr[d % 10];
                if (temp > 50) {
                    ans++;
                    //cout<<y<<' '<<m<<' '<<d<<endl;
                }
            }
        }
    }
    cout << ans;
}



