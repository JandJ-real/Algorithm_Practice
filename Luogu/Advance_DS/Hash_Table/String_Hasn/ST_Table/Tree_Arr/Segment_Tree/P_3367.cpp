#include <bits/stdc++.h>
using namespace std;
int n;//元素
int m;//操作数
//注意：操作都是0-based
class UnionFind {
public:
  vector<int> parent; // 存储每个节点的父节点
  vector<int> rank;   // 用于按秩合并（可选优化）
  int count;          // 连通分量数量

  // 初始化并查集
  UnionFind(int n) : count(n) {
    parent.resize(n);
    rank.resize(n, 0);
    for (int i = 0; i < n; i++) {
      parent[i] = i; // 初始时每个元素都是自己的父节点
    }
  }

  // 查找根节点（路径压缩优化）
  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]); // 路径压缩
    }
    return parent[x];
  }

  // 合并两个集合
  void unionSet(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY)
      return; // 已经在同一集合中

    // 按秩合并（可选优化）
    if (rank[rootX] < rank[rootY]) {
      parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
      parent[rootY] = rootX;
    } else {
      parent[rootY] = rootX;
      rank[rootX]++;
    }
    count--; // 连通分量减少
  }

  // 判断两个元素是否连通
  bool connected(int x, int y) { return find(x) == find(y); }

  // 获取连通分量数量
  int getCount() { return count; }
};


int main(){
    cin >> n >> m;
    UnionFind uf(n);
    int a;
    int b;
    int c;
    string ans;
    for (int i = 1; i <= m;i++){
        cin >> a>>b>>c;
        if(a==1){
            uf.unionSet(b-1, c-1);
        }
        else{
            if(uf.connected(b-1, c-1)){
                ans += 'Y';
            }
            else{
                ans += 'N';
            }
        }
    }
    for (size_t i = 0; i < ans.length();i++){
        cout << ans[i] << endl;
    }
    return 0;
}