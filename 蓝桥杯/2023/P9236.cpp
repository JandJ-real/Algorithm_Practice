#include <bits/stdc++.h>
using namespace std;
#define int long long
//异或->逐位异或，每一位bit位单独计算，使用前缀和，复杂度为n^2*20

//不再单独拎处每一个子段，而是计算每一个bit位置的贡献度((count0+1)*count1)(表示该bit位前缀异或和不同的两两组合数，因为只有不同的两两组合得出的子串才会在该处得出1个2^i贡献)
//复杂度为n*20

/*
  关键思维

  所有方法的共同本质是：
  ▎ 不枚举子段，而是枚举"变化事件"

  - 前缀型：变化发生在两个前缀值的配对
  - 值域压缩型：变化发生在 GCD/AND 值跳变时（每次跳变只有 $O(\log V)$ 次）
  - 单调栈型：变化发生在"最值的统治范围边界"处
  - 分治型：变化发生在跨越分割点时
*/
int n;
int arr[100005];
// int func[100005][21];
int prefix[100005][21]; // prefix[i][j] 数字1~i 第j个二进制位 异或的结果（0/1）
int count0[21];
int count1[21];
int ans;
signed main() {
    cin >> n;
    int num;
    for (int i = 1; i <= n; i++) {
        cin >> num;
        arr[i] = num;
        for (int j = 0; j <= 20; j++) {
            prefix[i][j] = prefix[i - 1][j] + num % 2;
            prefix[i][j] %= 2;
            if (prefix[i][j]) {
                //cout << i << ' ' << j << ' ' << prefix[i][j] << endl;
                count1[j]++;
            } else {
                count0[j]++;
            }
            num /= 2;
        }
    }
    int index = 1;
    for (int i = 0; i <= 20; i++) {
        //cout << count1[i] << ' ' << count0[i] << endl;
        ans += index * count1[i] * (count0[i]+1);
        index *= 2;
    }
    /*
        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                int temp = 0;
                int index = 1;
                for (int k = 0; k <= 20; k++) {
                    int num = prefix[j][k] - prefix[i - 1][k];
                    num %= 2;
                    temp += num * index;
                    index *= 2;
                }
                ans += temp;
            }
        }
    */

    cout << ans;
}
