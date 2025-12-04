#include <bits/stdc++.h>

using namespace std;
#define int long long

inline int read() {
    int x = 0, f = 1;     // x: 存储结果, f: 符号标志(1正数, -1负数)
    char ch = getchar();  // 读取第一个字符

    while (!isdigit(ch)) {  // 跳过非数字字符
        if (ch == '-')
            f = -1;      // 遇到负号，设置符号为负
        ch = getchar();  // 继续读取下一个字符
    }

    while (isdigit(ch)) {       // 处理数字部分
        x = x * 10 + ch - '0';  // 将字符转换为数字并累加
        ch = getchar();         // 读取下一个字符
    }

    return x * f;  // 返回结果（考虑符号）
}

int l, n, m;
int arr[50005];
int judge(int x) {
    int tim = 0;
    int Min = l + 1;
    int i = 1;  //下一块石头
    int cur = 0;
    while (i <= n + 1) {
        int dist = arr[i] - arr[cur];
        if (dist < x) {
            tim++;
            i++;
        } else {
            Min = min(Min, dist);
            cur = i;
            i++;
        }
    }
    if (tim > m) {
        //没这么大
        return 0;
    } else if (tim < m&&Min>x) {
        //还能更大
        return 1;
    }else if(tim<m&&Min==x){
        //可能是也可能更大
        return 2;
    } else if (Min == x&&tim==m) {
        // x就是了
        return -1;
    } else {
        //还能更大
        return 1;
    }
}
signed main() {
    cin >> l >> n >> m;
    arr[0] = 0, arr[n + 1] = l;
    for (int i = 1; i <= n; i++) {
        arr[i] = read();
    }
    int left = 0, right = l;
    int ans=0;
    while (left <= right) {
        int mid = (left + right) >> 1;
        int flag = judge(mid);
        if (!flag) {
            right = mid - 1;
        } else if (flag == 1) {
            left = mid + 1;
        } else if (flag == 2) {
            ans=max(mid,ans);
            left = mid+1;
        } else {
            ans=max(ans,mid);
            break;
        }
    }
    cout<<ans<<endl;
}
