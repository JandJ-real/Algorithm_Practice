
//以下为求解所用程序，因为是结果填空题，不考虑速度，直接搜索即可
/*
#include <bits/stdc++.h>
using namespace std;
#define int long long
int num;
bool judge(int a) {
    int arr[9];
    int index = 0;
    int sum = 0;
    while (a != 0) {
        int num = a % 10;
        arr[index] = num;
        sum += num;
        a /= 10;
        index++;
    }
    if (index % 2 != 0)
        return false;
    int qian = 0, hou = 0;
    for (int i = 0; i < (index / 2); i++) {
        qian += arr[i];
    }
    hou = sum - qian;
    if (qian != hou)
        return false;
    return true;
}
int ans;
void dfs(int cur, int score) {
    if (score == 70)
        ans++; //停止
    if (score == 100 || cur == 31)
        return;
    dfs(cur + 1, score + 10); //答对
    dfs(cur + 1, 0);          //答错
    return;
}
signed main() {
    // 1~1e8
    for (int i = 1; i <= 100000000; i++) {
        if (judge(i))
            num++;
    }
    cout << num << endl; // 4430091
    dfs(1, 0);
    cout << ans; // 8335366
    return 0;
}
*/
#include <bits/stdc++.h>
using namespace std;

char pid;
int main() {
    cin >> pid;
    if (pid == 'A')
        puts("4430091");
    else
        puts("8335366");
    return 0;
}
