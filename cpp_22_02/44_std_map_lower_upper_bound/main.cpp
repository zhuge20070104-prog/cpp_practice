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
#include <stack>
#include <forward_list>
#include <iomanip>

class A {
  int a;
public:
  A(int a): a(a) {}
  int getA() const {
    return a;
  }

  bool operator<(A const& b) const {
    return a < b.a;
  }
};

struct R {
  bool operator()(A const& a, A const& b) const {
    return a.getA() < b.getA();
  }
};

int main(int argc, char* argv[]) {
    /**
     * map lower_bound >=2
     * map upper_bound > 7
     */

    /**
     * 
     * erase 或者其他迭代器范围操作的时候是左闭右开 区间
     * [start, end)
     */
    /**
     * 以上是本题主要考察点
     * 
     * std::map自定义比较器需要支持 < 操作符重载
     * 如果你希望在 `std::map` 中使用自定义类型 `A` 作为键，并且支持 `lower_bound` 和 `upper_bound`，需要为类型 `A` 提供严格弱序关系的比较规则。通常，这是通过实现 **`operator<`** 来完成的。

---

### **必要操作符**
为了支持排序，`std::map` 默认依赖键的 `<` 操作符来确定元素的顺序。因此，你需要为你的自定义类型 `A` 实现以下操作：

1. **`operator<`**：
   - 定义严格弱序（strict weak ordering）。
   - `std::map` 会使用它来对键排序。

### **示例：实现 `operator<`**
```cpp
#include <iostream>
#include <map>

class A {
public:
    int x;
    int y;

    A(int x, int y) : x(x), y(y) {}

    // 实现 operator<，根据 x 和 y 的顺序进行比较
    bool operator<(const A& other) const {
        if (x != other.x)
            return x < other.x;
        return y < other.y;
    }
};

int main() {
    std::map<A, int> m;

    // 插入一些数据
    m[A(1, 2)] = 10;
    m[A(1, 3)] = 20;
    m[A(2, 1)] = 30;

    // 遍历并输出 map 内容
    for (const auto& [key, value] : m) {
        std::cout << "Key: (" << key.x << ", " << key.y << "), Value: " << value << "\n";
    }

    // 使用 lower_bound 和 upper_bound
    auto lb = m.lower_bound(A(1, 2));
    if (lb != m.end()) {
        std::cout << "Lower bound: (" << lb->first.x << ", " << lb->first.y << "), Value: " << lb->second << "\n";
    }

    auto ub = m.upper_bound(A(1, 2));
    if (ub != m.end()) {
        std::cout << "Upper bound: (" << ub->first.x << ", " << ub->first.y << "), Value: " << ub->second << "\n";
    }

    return 0;
}
```

---

### **输出**
```
Key: (1, 2), Value: 10
Key: (1, 3), Value: 20
Key: (2, 1), Value: 30
Lower bound: (1, 2), Value: 10
Upper bound: (1, 3), Value: 20
```

---

### **解释**
1. **排序规则**：
   - `operator<` 决定了键在 `std::map` 中的排序。
   - 示例中的实现按 `x` 进行主排序，若 `x` 相等，则按 `y` 进行次排序。

2. **`lower_bound` 和 `upper_bound`**：
   - `lower_bound(A(1, 2))`：找到第一个 `key >= A(1, 2)` 的元素。
   - `upper_bound(A(1, 2))`：找到第一个 `key > A(1, 2)` 的元素。

---

### **可选：使用自定义比较器**
如果不想直接修改 `operator<`，也可以为 `std::map` 提供自定义的比较器：

```cpp
struct Compare {
    bool operator()(const A& a, const A& b) const {
        if (a.x != b.x)
            return a.x < b.x;
        return a.y < b.y;
    }
};

std::map<A, int, Compare> m;
```

这样就可以将排序逻辑封装在比较器中，而无需修改类的定义。

---

### **总结**
- 必须实现 **`operator<`** 或提供自定义比较器，确保 `std::map` 能根据键排序。
- `lower_bound` 和 `upper_bound` 的功能依赖于 `std::map` 的排序规则，因此它们需要键支持严格弱序关系。
     * 
     */

    int t[] = {3, 4, 2, 1, 6, 5, 7, 9, 8, 10};
    std::string s[] = {"three", "four", "two", "one", "six","five", "seven", "nine","eight","ten"};

    // Method 1:
    // std::map<A, std::string> m;
    // Method 2:
    std::map<A, std::string, R> m;
    for(int i=0; i<10; i++) {
      m.insert(std::pair<A, std::string>(A(t[i]), s[i]));
    }

    m.erase(m.lower_bound(2), m.upper_bound(7));

    // std::map<A, std::string>::iterator i = m.begin();

    std::map<A, std::string, R>::iterator i = m.begin();
    
    for(;i!=m.end(); i++) {
      std::cout << i->second << " ";
    }
    std::cout << std::endl;
    return EXIT_SUCCESS;
} 

