#include <iostream>
#include <string>
#include <vector>

std::vector<int> getNextArray(const std::string& pattern);

int strStr(const std::string& haystack, const std::string& needle) {
  auto next = getNextArray(needle);  // 生成next数组
  int i = 0, j = 0;
  while (i < haystack.size() && j < needle.size()) {
    if (j == -1 || haystack[i] == needle[i]) {
      i++;
      j++;
    } else {
      j = next[j];
    }
  }

  if (j == needle.size()) {
    return i - j;
  }
  return -1;
}

std::vector<int> getNextArray(const std::string& pattern) {
  int k = -1;  // 记录公共前后缀长度
  int j = 0;   // 用于遍历pattern模式串
  int n = pattern.size();

  std::vector<int> next(n, 0);

  next[0] = -1;  // 这是一个标记值，表示没有需要处理的字符串。

  while (j < n - 1) {
    if (k == -1 || pattern[k] == pattern[j]) {
      k++;
      j++;
      next[j] = k;
    } else {
      k = next[k];  // 回溯
    }
  }

  return next;
}

int main() {
  std::string h = "leetcode";
  std::string n = "code";
  int res = strStr(h, n);
  std::cout << res << std::endl;
}