### 生成 `next` 数组

#### 初始化

1. **变量定义**：
    - `k = -1`：用于记录当前子串的最长相等前后缀的长度。
    - `j = 0`：用于遍历模式串 `pattern`。
    - `n = pattern.size()`：模式串的长度。
    - `next`：一个大小为 `n` 的数组，用于存储 `next` 值。

2. **设置起始值**：
    - `next[0] = -1`：这是一个标记值，表示没有更小的可匹配前缀。

#### 循环生成

3. **开始循环**：`while (j < n - 1)` 循环用于遍历模式串，从第一个字符到倒数第二个字符。

#### 条件判断

4. **字符匹配或回溯到起点**：`if (k == -1 || pattern[k] == pattern[j])`
    - 当 `k == -1` 或者 `pattern[k]` 和 `pattern[j]` 相等时，执行以下操作：
        1. `k++`：增加最长相等前后缀的长度。
        2. `j++`：移动到模式串的下一个字符。
        3. `next[j] = k`：将 `k` 的值存储到 `next[j]`。

5. **字符不匹配**：`else`
    - 当字符不匹配时，执行 `k = next[k]`，即回溯到前一个可能的相等前后缀位置。

#### 循环结束

6. **完成生成**：当 `j` 达到 `n - 1` 时，`next` 数组就生成完成了。

这样，`next` 数组就动态地生成了出来。这个数组在 KMP 算法中用于优化字符串匹配，使得算法能够在不匹配时快速跳过一些字符。

### strStr()

