#ifndef _FREDRIC_TEST_DRIVER_H_
#define _FREDRIC_TEST_DRIVER_H_
using test_func = int(*)(int, unsigned long);
// 调用多个 test_func类型的函数
void test_driver(test_func* flist, int argc=0, char** argv=0);

// 调用一个test_func类型的函数
void test_driver(test_func f, int argc=0, char** argv=0);
#endif
