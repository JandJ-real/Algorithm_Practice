//总的来说，考试时没有想到对于每一个5x9区域，k的取值是一个区间，再将所有这些区间整合之后输出，而是一味的从0到L-1遍历k值
/*相比2号，使用差分整合区间，寻找k的范围时增加了剪枝优化，还有许多细节，总体来说优化了很多*/
//这差分整合区间也太优雅了吧
//所有的算法不是一个形式，而是一种思想
#include <bits/stdc++.h>

using namespace std;

const int N = 2e2 + 7, M = 6e6 + 7;

int n, L;//图像大小，灰度值范围
//灰度值范围为[0,L-1]
int A[N][N], diff[M];
//
bool st[5][9];

void init() {
    st[1][1] = st[1][2] = st[1][4] = st[1][5] = st[1][7] = true;
    st[2][1] = st[2][2] = st[2][8] = true;
    st[3][1] = st[3][2] = st[3][3] = st[3][4] = st[3][7] = st[3][8] = true;
    st[4][7] = st[4][8] = true;
}

int main() {
    init();
    cin >> n >> L;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> A[i][j];

    for (int i = 1; i <= n - 4; i++) {
        for (int j = 1; j <= n - 8; j++) {
            // 计算当前窗口的最小k值和最大k值
            int min_k = 0, max_k = L - 1;
            bool flag = true;
            
            // 计算最小k值（来自模板中为true的位置）
            for (int a = 0; a < 5; a++) 
                for (int b = 0; b < 9; b++) 
                    if (st[a][b]) 
                        min_k = max(min_k, A[i + a][j + b] + 1);
            
            // 计算最大k值（来自模板中为false的位置）
            //--------------此处退出for循环的方式是可以借鉴的，十分优雅
            for (int a = 0; a < 5 && flag; a++) {
                for (int b = 0; b < 9 && flag; b++) {
                    if (!st[a][b]) 
                    {
                        if (A[i + a][j + b] < min_k)
                        //当有一个应该是白色的位置比黑色位置的最大还要小，就废了 
                            flag = false;
                        else 
                            max_k = min(max_k, A[i + a][j + b]);
                    }
                }
            }
            
            if (flag && min_k <= max_k) 
                diff[min_k] ++, diff[max_k + 1] --; // 差分处理：[min_k, max_k]区间
        }
    }
    
    int cnt = 0;
    for (int k = 0; k < L; k++) {
        cnt += diff[k]; // 前缀和还原
        if (cnt > 0) 
            cout << k << endl;
    }
    return 0;
}
/* 2号朴素版本
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; int L;
    cin >> n >> L;
    vector<vector<int>> A(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) cin >> A[i][j];

    const vector<string> pat = {
        "111111111",
        "100100101",
        "100111110",
        "100001100",
        "111111100"
    };
    // 预计算白/黑相对于左上角点的偏移坐标
    vector<pair<int,int>> W, B;
    for (int r = 0; r < 5; ++r) {
        for (int c = 0; c < 9; ++c) {
            (pat[r][c] == '1' ? W : B).push_back({r, c});
        }
    }

    // 预留矩阵左上角点的空间，存的是以左上角点为起点的窗口符合条件的灰度值上下界
    vector<pair<int,int>> segs;
    segs.reserve((n-4)*(n-8));      
    for (int i = 0; i + 5 <= n; ++i) {
        for (int j = 0; j + 9 <= n; ++j) {
            int minW = INT_MAX;
            int maxB = INT_MIN;
            for (auto [dr, dc] : W) {          // 检查这个窗口内的应该是1的位置上的灰度的最小值
                int v = A[i+dr][j+dc];
                if (v < minW) minW = v;
            }
            for (auto [dr, dc] : B) {
                int v = A[i+dr][j+dc];
                if (v > maxB) maxB = v;
            }
            // 需要 maxB + 1 <= k <= minW，且 0 <= k <= L-1
            int lo = max(0, maxB + 1);
            int hi = min(minW, L - 1);
            if (lo <= hi) segs.push_back({lo, hi});
        }
    }

    // 合并区间并按要求逐个输出
    sort(segs.begin(), segs.end());     // 按左边界排序
    int curL = -1, curR = -2;
    for (auto [l, r] : segs) {
        if (l > curR + 1) {             // 注意这里是大于，并+1的，由于是整数，只有中间隔了一个数，才会另开一个区间
            for (int k = curL; k <= curR; ++k) cout << k << '\n';
            curL = l; curR = r;
        } else {
            curR = max(curR, r);
        }
    }
    for (int k = curL; k <= curR; ++k) cout << k << '\n';
    return 0;
}


*/
