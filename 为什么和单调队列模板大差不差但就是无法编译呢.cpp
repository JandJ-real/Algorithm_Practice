#include<bits/stdc++.h>
//分析：初步断定复杂度为2n，通过取两次相反数的方式降到n，其实并非，依然是2n
#define int long long
using namespace std;

int n;
int k;

signed main() {
  
  cin >> n >> k;

  vector<int> arr(n);
  vector<int> arr1(n);
  vector<int> ans_min(n - k + 1);
  vector<int> ans_max(n - k + 1);
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
    arr1[i] = -arr[i];
  }
  //以上为输入
  cout << "ceshi1";
  //单调队列要求队头队尾都能出队，需要自定义。
  //注：队头出队用来控制窗口大小；队尾出队用来剔除不合适的元素
  //以下为单调队列模板

  //先找最小值
  int que[1000000];
  int head = 0;
  int tail = -1;
  cout << "ceshi2";
  for (int i = 0; i < n; i++) {
    //若队列中有元素且队尾元素大于待定元素,则从队尾出队
    while (head <= tail && que[tail] > arr[i]) {
      tail--;
    }
    //待定元素入队
    que[++tail] = arr[i];
    //若队列中有元素且元素个数大于区间长度，则从队头出队
    while (head <= tail && tail - head + 1 > k) {
      head++;
    }
    //第一次达到区间长度之后，每加一个元素出一次最值，此处是最小值
    if (i + 1 >= k)
      ans_min[i - k + 1] = que[head];
  }
  cout << "ceshi3";
  //接下来用取两次相反数的方法找出最大值
  head = 0;
  tail = -1;
  for (int i = 0; i < n; i++) {
    //若队列中有元素且队尾元素大于待定元素,则从队尾出队
    while (head <= tail && que[tail] > arr1[i]) {
      tail--;
    }
    //待定元素入队
    que[++tail] = arr1[i];
    //若队列中有元素且元素个数大于区间长度，则从队头出队
    while (head <= tail && tail - head + 1 > k) {
      head++;
    }

    //第一次达到区间长度之后，每加一个元素出一次最值，此处是最小值
    if (i + 1 >= k)
      ans_max[i - k + 1] = -que[head];
  }

  //以下是输出
  for (int i = 0; i < n - k + 1; i++) {
    cout << ans_min[i] << ' ';
  }
  cout << endl;
  for (int i = 0; i < n - k + 1; i++) {
    cout << ans_max[i] << ' ';
  }
  return 0;
}