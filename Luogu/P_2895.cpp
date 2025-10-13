#include <bits/stdc++.h>
// 1.long long
// 2.!=arr.end()
// 3.修改3000

//时隔多年终于解决，问题出在读题上，300是流星的范围，不是移动的边界
using namespace std;
#define int long long
int m;  //流星数目
#define x first
#define y second
int ans;
inline int read()
{
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

bool mycompare(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
    if (a.y <= b.y) {
        return true;
    } else {
        return false;
    }
}

bool rightpos(int x)
{
    if (x >= 0) {
        return true;
    } else
        return false;
}

vector<pair<pair<int, int>, int>> arr;
int mp[305][305];
int curmp[305][305];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
signed main()
{
    cin >> m;
    arr.resize(m);
    // tim.resize(m + 1);
    int a, b;
    for (int i = 0; i < m; i++) {
        a = read();
        b = read();
        //预处理最后能站的位置
        mp[a][b] = 1;
        for (int j = 0; j < 4; j++) {
            int nx = a + dx[j];
            int ny = b + dy[j];
            if (rightpos(nx) && rightpos(ny)) {
                mp[nx][ny] = 1;
            }
        }

        arr[i].x.x = a;
        arr[i].x.y = b;
        arr[i].y = read();
    }
    sort(arr.begin(), arr.end(), mycompare);
    /*    for (int i = 0; i < m;i++){
        cout << arr[i].x.x << ' ' << arr[i].x.y << ' ' << arr[i].y << '\n';
    }*/

    // 以上为输入
    queue<pair<int, int>> que;
    queue<int> quet;
    // bfs
    que.push({0, 0});
    quet.push(1);
    int t;  //计时器
    auto it = arr.begin();
    int flag = 1;
    while (!que.empty() && flag) {
        //更新地图
        t = quet.front();
        quet.pop();
        for (; (*it).y <= t && it != arr.end(); it++) {
            int a = (*it).x.x;
            int b = (*it).x.y;
            curmp[a][b] = 1;
            for (int j = 0; j < 4; j++) {
                int nx = a + dx[j];
                int ny = b + dy[j];
                if (rightpos(nx) && rightpos(ny)) {
                    curmp[nx][ny] = 1;
                }
            }
        }

        //模拟行动
        int curx = que.front().x;
        int cury = que.front().y;
        // cout << curx << ' ' << cury << endl;
        que.pop();

        for (int j = 0; j < 4; j++) {
            int nx = curx + dx[j];
            int ny = cury + dy[j];
            if (rightpos(nx) && rightpos(ny)) {
                // cout << "rightpos:" << nx << ' ' << ny << endl;
                if (!curmp[nx][ny]) {
                    // cout << "!curmp:" << nx << ' ' << ny << endl;
                    que.push({nx, ny});
                    quet.push(t + 1);
                    curmp[nx][ny] = 1;
                    if (!mp[nx][ny]) {
                        flag = 0;
                        ans = t;
                    }
                }
            }
        }
    }

    //输出
    if (flag) {
        cout << -1;
    } else {
        cout << ans;
    }
}