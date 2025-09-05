#include <algorithm>
#include <vector>

using namespace std;
//不停地从内部和末尾优化序列，而且是同时优化一堆序列
int longestNonDecreasingSubsequenceOptimized(vector<int> &nums) {
  vector<int> tails; // 存储各个长度不下降子序列的最小末尾值

  for (int num : nums) {
    // 找到第一个大于 num 的元素位置
    auto it = upper_bound(tails.begin(), tails.end(), num);

    if (it == tails.end()) {
      tails.push_back(num); // 可以扩展最长序列
    } else {
      *it = num; // 替换为更小的值，为后续扩展创造条件
    }
  }

  return tails.size();
}