#include <cassert>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <string>
#include <map>
#include <set>
#include <deque>
#include <list>
#include <iomanip>


void myfunction(int i) {
    std::cout << " " << i;
}


/**
 * 
 * std::set 不能做swap_range
 * 
 * 编译错误的原因在于 `std::set` 的迭代器指向的元素是 `const` 的，这样保证了集合元素的不可修改性，因为 `std::set` 会自动对元素进行排序，修改元素可能会破坏其内部顺序结构。因此，`std::set<int>::iterator` 解引用后得到的是 `const int&`，无法进行修改操作。

`std::swap_ranges` 需要的是两个可修改的范围，这意味着两个范围的元素必须能够被 `swap`。但是由于 `s1` 是一个 `std::set`，其迭代器不允许修改指向的元素，因此无法直接对 `s1` 的元素进行交换。

要解决这个问题，可以先将 `s1` 的元素复制到一个可修改的容器（例如 `std::vector`）中，再进行交换操作。以下是改进后的代码示例：

```cpp
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

void myfunction(int i) {
    std::cout << i << " ";
}

int main() {
    int t[] = {10, 5, 9, 6, 2, 4, 7, 8, 3, 1};
    std::set<int> s1(t, t + 10);

    // 将 s1 的元素复制到一个可修改的容器中
    std::vector<int> v1(s1.rbegin(), s1.rend());
    std::vector<int> s1_copy(s1.begin(), s1.end());

    // 交换 s1_copy 和 v1 的元素
    std::swap_ranges(s1_copy.begin(), s1_copy.end(), v1.begin());

    // 输出 v1 和 s1_copy 中的结果
    std::for_each(v1.begin(), v1.end(), myfunction);
    std::cout << std::endl;
    std::for_each(s1_copy.begin(), s1_copy.end(), myfunction);

    return 0;
}
```

在这个示例中，我们将 `s1` 的元素复制到一个新的可修改容器 `s1_copy` 中，并在 `s1_copy` 和 `v1` 之间使用 `std::swap_ranges` 进行交换操作。
 */


int main(int argc, char* argv[]) {
    int t[] = {10, 5, 9, 6, 2, 4, 7, 8, 3, 1};

    std::set<int> s1(t, t + 10);

    std::vector<int> v1(s1.rbegin(), s1.rend());
    std::vector<int> s1_copy(s1.begin(), s1.end());

    std::swap_ranges(s1_copy.begin(), s1_copy.end(), v1.begin());
    
    // 1 2 3 4 5 6 7 8 9 10/ 1 2 3 4 5 6 7 8 9 10
    std::for_each(v1.begin(), v1.end(), myfunction);
    std::for_each(s1.begin(), s1.end(), myfunction);

    std::for_each(s1_copy.begin(), s1_copy.end(), myfunction);

    return EXIT_SUCCESS;
} 

