#include "scanner.h"
#include "printer.h"
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
#include <list>
#include <iomanip>

class B {
    int val;
public:
    B(int v): val(v) {}

    int getV() const {
        return val;
    }
    
    bool operator< (B const& v) const {
        return val > v.val;
    }

    friend std::ostream& operator<<(std::ostream& out, B const& v) {
        out << v.getV();
        return out;
    }
};

template <class T>
struct Out {
    std::ostream& out;

    Out(std::ostream& o): out(o) {}

    void operator()(T const& val) {
        out << val << " "; 
    }
};

/**
 * 你的 `operator<<` 重载定义不正确，导致编译器报错。标准库要求 **输出运算符 `operator<<` 必须是一个非成员函数**，这样可以在左侧使用标准输出流对象（如 `std::ostream`）。而你的代码中将其定义为 `B` 类的成员函数，这会导致它额外带有一个 `this` 指针参数，因此编译器会提示只能有一个参数。

要正确实现 `operator<<` 重载，可以将其定义为 **友元函数** 或 **非成员函数**，这样可以使 `std::ostream` 对象作为第一个参数，`B` 类的实例作为第二个参数：

### 修正后的代码示例

```cpp
#include <iostream>

class B {
    int val;
public:
    B(int v): val(v) {}

    int getV() const {
        return val;
    }

    // 比较运算符重载
    bool operator< (B const& v) const {
        return val > v.val;
    }

    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& out, B const& v) {
        out << v.getV();
        return out;
    }
};

int main() {
    B b(10);
    std::cout << b << std::endl;  // 正确输出 B 对象的值
    return 0;
}
```

### 解释
1. **友元函数**：将 `operator<<` 定义为 `friend` 函数，使其访问 `B` 的私有成员。友元函数不是成员函数，因此没有隐含的 `this` 参数。
  
2. **参数要求**：在这种定义下，`operator<<` 接受两个参数：第一个是 `std::ostream&`，第二个是 `const B&`。
 */


int main(int argc, char* argv[]) {
    B t1[]={3,2,4,1,5};
    B t2[]={5,6,8,2,1};
    std::vector<B> v1(10,0);
    std::sort(t1, t1+5);
    std::sort(t2, t2+5);
    // Expect output 不用friend 会compilation error
    // 有friend 输出 5 2 1 0 0 0 0 0 0 0
    std::set_intersection(t1,t1+5,t2,t2+5,v1.begin());
    std::for_each(v1.begin(), v1.end(), Out<B>(std::cout));
    std::cout << std::endl;

    return EXIT_SUCCESS;
} 

