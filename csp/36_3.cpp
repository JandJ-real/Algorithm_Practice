#include<bits/stdc++.h>
// n个缓存行 为一组  有N组
//每个内存块可以恰好存储在一个缓存行中
//编号为k的内存块仅可以存在编号为k/n的组中的任意一个缓存行中
//读：未命中：满了就替换最久未被使用的缓存行，若该缓存行被修改过，还需将修改数据写入内存；没满就尾插
//    命中：直接读
//写：未命中：先从内存读(回到读的规则)，再写入；命中：直接写

//注意：记录最近一次操作时间，记录是否修改

//如何找到最久未使用的元素 高效 用deque？ 并非，用list(双向链表)

//改了很久的bug是：命中时，如果已经是修改过的状态，再读取后依然是修改过的状态(一定要在脑子里预演代码的各种情况，不能想当然)

//然后tle了，优化是用set存储，便于logn的遍历而不是n，，，但是维护又是个麻烦事，，，，实际看下来在我用数组先后顺序来表示时间先后的基础上，set的作用是快速判断出未命中的情况，但是确实提高了效率，ac了
using namespace std;
#define int long long

inline int read() {
  int x = 0, f = 1;    // x: 存储结果, f: 符号标志(1正数, -1负数)
  char ch = getchar(); // 读取第一个字符

  while (!isdigit(ch)) { // 跳过非数字字符
    if (ch == '-')
      f = -1;       // 遇到负号，设置符号为负
    ch = getchar(); // 继续读取下一个字符
  }

  while (isdigit(ch)) {    // 处理数字部分
    x = x * 10 + ch - '0'; // 将字符转换为数字并累加
    ch = getchar();        // 读取下一个字符
  }

  return x * f; // 返回结果（考虑符号）
}

int n;//路数
int N;//组数
int q;//指令数量
vector<list<pair<int,int>>> arr;//缓存区域
vector<set<int>> sch;
void rw(int zu,int num,int m){
    auto& group = arr[zu];
    
    
        if(sch[zu].count(num)){
            //命中
            for (auto it = group.begin(); it != group.end();it++){
                if((*it).first==num){
                  int ff = (*it).second;
                  group.erase(it);

                  if (m || ff) {
                    //标记已修改
                    group.push_back({num, 1});
                    return;
                  }
                  group.push_back({num, 0});
                  return;
                }
             
            }
             
        }
    
    //未命中
   
    if((int)group.size()<n){
        //未满
        cout << 0 << ' ' << num << endl;
        sch[zu].insert(num);
        if(m){
          group.push_back({num, 1});
          //标记已修改
          return;
        }
        group.push_back({num, 0});
        return;
    }
    else{
        //满了
        //找出最久未使用的,也即头元素，替换他
        auto it = group.begin();
        if((*it).second){
          // 如果曾经修改过，还得写入他
          cout << 1 << ' ' << (*it).first << endl;
          
        }
        group.erase(it);
        sch[zu].erase(sch[zu].find((*it).first));
        cout << 0 << ' ' << num << endl;
        sch[zu].insert(num);
        if (m) {
          
          //标记已修改
          group.push_back({num, 1});
          return;
        }
        group.push_back({num, 0});
        return;
    }
}
signed main() {
  cin >> n >> N >> q;

  arr.resize(N);
  sch.resize(N);
  int a, b, zu;
  while(q--){
    a = read(); //读或写
    b = read(); //内存块
    zu = (b / n)%N;
    rw(zu, b, a);
  }

}
