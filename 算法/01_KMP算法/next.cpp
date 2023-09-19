#include <iostream>
#include <string>
#include <vector>

std::vector<int> getNextArray(const std::string& pattern) {
  int n = pattern.size();
  std::vector<int> next(n, 0);
  int j = 0;   // 用于遍历pattern模式串
  int k = -1;  // 用于记录当前位置之前的最长公共前后缀长度
  next[0] = -1;  // 这是一个标记值，表示没有更小的可匹配前缀。

  while (j < n - 1) {
    // k == -1表示没有可匹配的前缀，pattern[j] ==
    // pattern[k]表示找到了可匹配的前缀
    if (k == -1 || pattern[j] == pattern[k]) {
      ++j;
      ++k;
      next[j] = k;  // next[j]表示pattern[0...j]的最长公共前后缀长度
    } else {
      k = next[k];  // 回溯
    }
  }
  return next;
}

int main() {
  std::string pattern = "abcababca";
  std::vector<int> next = getNextArray(pattern);
  for (int i = 0; i < next.size(); ++i) {
    std::cout << next[i] << " ";
  }
  std::cout << std::endl;
  return 0;
}