#include "test_driver.h"
#include "stopwatch11.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <bitset>

struct Point {
    double x_, y_;
    static double epsilon;

    Point(double x, double y): x_(x), y_(y) {}

    bool operator==(Point const& that) const {
        return fabs(this->x_ - that.x_) < epsilon && fabs(this->y_ - that.y_) < epsilon;
    }
};

double Point::epsilon = 1e-10;

// 逆时针将某个点的坐标旋转theta弧度角
void rotate(std::vector<Point>& v, double theta) {
    for(std::size_t i=0; i<v.size(); ++i) {
        double x = v[i].x_, y = v[i].y_;
        v[i].x_ = cos(theta) * x - sin(theta) * y;
        v[i].y_ = sin(theta) * x  + cos(theta) * y;
    }
}

void rotate_invariant(std::vector<Point>& v, double theta) {
    double sin_theta = sin(theta);
    double cos_theta = cos(theta);

    for(std::size_t i=0; i<v.size(); ++i) {
        double x = v[i].x_, y = v[i].y_;
        v[i].x_ = cos_theta * x - sin_theta * y;
        v[i].y_ = sin_theta * x  + cos_theta * y;
    }
}

static inline unsigned part_size(unsigned& whole, unsigned& parts) {
    unsigned part_size = whole /parts;
    whole -= part_size;
    parts -= 1;
    return part_size;
}

void divide_into_parts(unsigned whole, unsigned parts) {
    if(parts == 0) return;
    std::cout << whole << " divided into " << parts << " parts has part sizes ";
    do {    
        std::cout << part_size(whole, parts) << " ";
    } while(parts > 0);
    std::cout << std::endl;
}

// 求小于当前数字的最大2的n次幂
static inline unsigned msb_iterative(unsigned x) {
    unsigned n = 0x10000000;
    if(x == 0) return 1;
    while(x < n) {
        n >>= 1;
    }
    return n;
}

// 只要最左边那位，求小于当前数字的最大2的n次幂
static inline unsigned msb_closed(unsigned x) {
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    return(x & ~(x >> 1));
}

// 是2的n次方迭代方式
inline bool is_power_2_iterative(unsigned n) {
    for(unsigned one_bits = 0; n!=0; n>>=1) {
        if((n&1)==1) {
            if(one_bits != 0) {
                return false;
            } else {
                one_bits += 1;
            }
        }
    }

    return true;
}

inline bool is_power_2_closed(unsigned n) {
    return (n!=0) && !(n&(n-1));
}

int test_statements(int test_no, unsigned long multiplier) {
    bool rc = true;
    switch(test_no) {
        case 0: return 7;
        default: return -1;
        case 1: { // 验证算法的正确性
            double const pi = acos(-1.0);
            rc &= !(Point(0.0, 1.0) == Point(1.0, 0.0));
            std::vector<Point> v {Point{0.0, 0.0}}, w{Point{0.0, 0.0}};

            v[0] = w[0] = Point(0.0, 1.0);
            rotate(v, pi/2.0);
            rotate_invariant(w, pi/2.0);
            rc &= (v[0] == Point(-1.0, 0.0));
            rc &= (v[0] == w[0]);

            v[0] = w[0] = Point(1.0, 0.0);
            rotate(v, pi/3.0);
            rotate_invariant(w, pi/3.0);
            rc &= (v[0] == Point(0.5, sin(pi/3.0)));
            rc &= (v[0] == w[0]);

            v[0] = w[0] = Point(1.0, 0.0);
            rotate(v, pi/ 4.0);
            rotate_invariant(w, pi/ 4.0);
            rc &= (v[0] == Point(cos(pi/4.0), cos(pi/4.0)));
            rc &= (v[0] == w[0]);
        }
        break;

        case 2: { // string scan 效率测试，各种循环和缓存
            char s[] = "This string has many space (0x20) chars.";
            unsigned long iterations = 10000 * multiplier;
            {
                StopWatch sw("string scan with strlen() evaluated each char");
                for(unsigned long j=0; j<iterations; ++j) {
                    for(std::size_t i=0; i<strlen(s); ++i) {
                        if(s[i] == ' ') {
                            s[i] = ' ';
                        }
                    }
                }
            }

            {
                StopWatch sw("string scan with cached strlen()");
                for(unsigned long j=0; j<iterations; ++j) {
                    for(std::size_t i=0, len=strlen(s); i<len; ++i) {
                        if(s[i] == ' ') {
                            s[i] = ' ';
                        }
                    }
                }
            }

            {
                StopWatch sw("string scan with cached strlen() do loop");
                for(unsigned j=0; j<iterations; ++j) {
                    std::size_t len = strlen(s);
                    std::size_t i = 0;
                    do {
                        if(s[i] == ' ') {
                            s[i] = ' ';
                        }   
                        ++i;
                    } while(i < len);
                }
            }

            {
                StopWatch sw("string scan counting down");
                for(unsigned long j=0; j<iterations; ++j) {
                    for(int i=(int)strlen(s)-1; i>=0; --i) {
                        if(s[i] == ' ') {
                            s[i] = ' ';
                        }
                    }
                }
            }

            {
                StopWatch sw("string scan counting down, do loop");
                for(unsigned j=0; j<iterations; ++j) {
                    unsigned i = (unsigned) strlen(s);
                    do {
                        --i;
                        if(s[i] == ' ') {
                            s[i] = ' ';
                        }
                    } while(i>0);
                }
            }
    
        }
        break;

        case 3: { // rotate，变量和不变量测试
            double const pi = acos(-1.0);
            std::vector<Point> v {
                Point(1.0, 0.0),
                Point(7.0, 0.0),
                Point(6.0, 2.0),
                Point(7.0, 4.0),
                Point(6.0, 6.0),
                Point(7.0, 8.0),
                Point(6.0,10.0),
                Point(7.0,12.0),
                Point(6.0,14.0),
                Point(2.0,14.0),
                Point(1.0,12.0),
                Point(2.0,10.0),
                Point(1.0, 8.0),
                Point(2.0, 6.0),
                Point(1.0, 4.0),
                Point(2.0, 2.0),
            };

            std::vector<Point> w = v;

            {
                StopWatch sw("rotate");

                for(unsigned long i=0; i<100000*multiplier; ++i) {
                    rotate(v, pi/1000);
                }
            }

            {
                StopWatch sw("rotate invariant");
                for(unsigned long i=0; i<100000*multiplier; ++i) {
                    rotate_invariant(w, pi/1000);
                }
            }
        }
        break;

        case 4: { // 动态分块
            divide_into_parts(10, 3);
            divide_into_parts(17, 6);
            divide_into_parts(15, 5);
        }
        break;

        case 5: {
            {
                StopWatch sw("iterative fall - float");
                for(unsigned i=0; i<10000 * multiplier; ++i) {
                    float d, t, a = -9.8f, v0 = 0.0f, d0 = 100.0f;
					for (t = 0.0f; t < 3.01f; t += 0.1f) {
						d = a*t*t + v0*t + d0;
					}
                }
            }

            {
                StopWatch sw("iterative fall - double");
                 for (unsigned i = 0; i < 10000*multiplier; ++i) {
					double d, t, a = -9.8, v0 = 0.0, d0 = 100.0;
					for (t = 0.0; t < 3.01; t += 0.1) {
						d = a*t*t + v0*t + d0;
					}
				}
            }
        }

        break;

        case 6: { // 求最近邻的，比当前数小的2^n的数，就是取当前数二进制最大位为1，其他位为0
            unsigned iterations = 1000000 * multiplier;
            {
                StopWatch sw("find msb iterative");
                for(unsigned i=1; i<iterations; ++i) {
                    rc &= (msb_iterative(i) <= iterations);
                }
            }

            {
                StopWatch sw("find msb closed");
                for(unsigned i=1; i<iterations; ++i) {
                    rc &= (msb_closed(i) <= iterations);
                }
            }
        }

        break;

        case 7: { // 判断当前数是否是2^n
            unsigned iterations = 100000 * multiplier;
            {
                StopWatch sw("power of 2 iterative");
                for(unsigned i=0; i<iterations; ++i) {
                    is_power_2_iterative(i);
                }
            }

            {
                StopWatch sw("power of 2 closed form");
                for(unsigned i=0; i<iterations; ++i) {
                    is_power_2_closed(i);
                }
            }
        }

        break;
    }

    return rc ? 1: 0;
}

