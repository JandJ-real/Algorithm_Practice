#include <bits/stdc++.h>
using namespace std;
#define int long long
//
int n, m;
int map[5][5];
int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int visited[5][5];
void dfs(int x, int y) {
    visited[x][y] = 1;
}
signed main() {
    cin >> n >> m;
    int arr[5][5];
}