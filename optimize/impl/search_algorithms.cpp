#include "array_iterator.h" // std::size() function
#include "stopwatch11.h"
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

struct kv { // (key, value) pairs
    char const* key;
    unsigned value;
};

static kv test[] = {
    { "adam",     0 },	{ "boy",     0 },	{ "charles", 0 },	{ "david",   0 },
	{ "ebenezer", 0 },	{ "ferris",  0 },	{ "george",  0 },	{ "henry",   0 },
	{ "ida",      0 },	{ "john",	 0 },	{ "karl",    0 },	{ "laurence",0 },
	{ "mary",	  0 },	{ "nora",    0 },	{ "ocean",   0 },	{ "panda",   0 },
	{ "quakka",   0 },	{ "robert",  0 },	{ "sam",     0 },	{ "tangle",  0 },
	{ "unice",    0 },	{ "vassily", 0 },	{ "waldo",   0 },	{ "xavier",  0 },
	{ "yabba",    0 },	{ "zebra",   0 },	{ "zymergy", 0 }
	,
	{ "alpha",   1 },   { "bravo",   2 },   { "charlie", 3 },   { "delta",  4 },
    { "echo",    5 },   { "foxtrot", 6 },   { "golf",    7 },   { "hotel",  8 },
    { "india",   9 },   { "juliet", 10 },   { "kilo",   11 },   { "lima",   12 },
    { "mike",   13 },   { "november",14 },  { "oscar",  15 },   { "papa",   16 },
    { "quebec", 17 },   { "romeo",  18 },   { "sierra", 19 },   { "tango",  20 },
    { "uniform",21 },   { "victor", 22 },   { "whiskey",23 },   { "xray",   24 },
    { "yankee", 25 },   { "zulu",   26 }
};

static kv names[] = { // in alphabetical order
    { "alpha",   1 },   { "bravo",   2 },   { "charlie", 3 },   { "delta",  4 },
    { "echo",    5 },   { "foxtrot", 6 },   { "golf",    7 },   { "hotel",  8 },
    { "india",   9 },   { "juliet", 10 },   { "kilo",   11 },   { "lima",   12 },
    { "mike",   13 },   { "november",14 },  { "oscar",  15 },   { "papa",   16 },
    { "quebec", 16 },   { "romeo",  18 },   { "sierra", 19 },   { "tango",  20 },
    { "uniform",21 },   { "victor", 22 },   { "whiskey",23 },   { "xray",  24 },
    { "yankee", 25 },   { "zulu",   26 }
};


// needed for std::lower_bound
static inline bool operator<(kv const& n1, char const* key) {
    return strcmp(n1.key, key) < 0;
}

static inline bool operator<(char const* key, kv const& n2) {
    return strcmp(key, n2.key) < 0;
}

static inline bool operator<(kv const& n1, kv const& n2) {
    return strcmp(n1.key, n2.key) < 0;
}

// needed for std::find
static inline bool operator==(kv const& n1, char const* key) {
    return strcmp(n1.key, key) == 0;
}

static inline bool operator==(kv const& n1, kv const& n2) {
    return strcmp(n1.key, n2.key) == 0;
}


// find algorithm, 特化struct kv的版本
kv* find_unwrapped(kv* first, kv* last, char const* key) {
    while(first != last) {
        if(*first == key) {
            return first;
        }
        ++first;
    }
    return last;
}

// find 优化，当已知range是有序的时候
kv* find_sorted(kv* first, kv* last, char const* key) {
    while(first != last) {
        int rc = strcmp(first->key, key);
        if(rc < 0) {
            ++ first;
            continue;
        }

        if(rc == 0) {
            return first;
        }

        // 如果没有对应元素，处理rc > 0的情况
        break;
    }
    return last;
}

// binary search using strcmp() to divide range into 3 parts
kv* find_binary_3way_size(char const* key, kv* table, unsigned size) {
    unsigned mid;
    int rc;
    while(size > 0) {
        mid = size/2;
        rc = strcmp(key, table[mid].key);
        if(rc < 0) { // key < table[mid].key, search left half
            size = mid;
        } else if(rc > 0) { // key > table[mid].key, search right half
            table = &table[mid+1];
            size -= mid + 1; 
        } else { // rc = 0, key == table[mid]
            return &table[mid];
        }
    }

    return nullptr;
} 


// binary search using strcmp() to divide range into 3 parts, same API as find()
kv* find_binary_3way(kv* start, kv* end, char const* key) {
    auto stop = end;
    while(start < stop) {
        auto mid = start + (stop-start) / 2;
        auto rc = strcmp(mid->key, key);
        if(rc > 0) { // mid->key > key, 左边寻找
            stop = mid;
        } else if(rc < 0) { // mid->key < key, 右边寻找
            start = mid + 1;
        } else {
            return mid;
        }
    }

    return end;
}


// binary search using only less relation
kv* find_binary_lessthan_size(char const* key, kv* table, unsigned size) {
    int mid;
    while(size > 1) {
        mid = size/2;
        if(strcmp(key, table[mid].key) < 0) { // key < table[mid].key, search left half
            size = mid;
        } else { // key >= table[mid].key, search right half
            table = &table[mid];
            size -= mid;
        }   
    }

    return strcmp(key, table->key)? nullptr: table;
}

// binary search using only "less" relation, same API as find
kv* find_binary_lessthan(kv* start, kv* end, char const* key) {
    auto stop = end;
    while(start < stop) {
        auto mid = start + (stop-start)/2;
        if(*mid < key) { // [mid + 1, stop)
            start = mid + 1;
        } else { // [start, mid]
            stop = mid;
        }
    }
    return (start==end || key < *start) ? end: start;
}

// 按照第一个字符的字母序分桶
// 不是字母的，分到第0个桶
unsigned hash(char const* key) {
    if(key[0] < 'a' || key[0] > 'z') {
        return 0;
    }
    return key[0] - 'a';
}

// 这个算法有局限性，hash函数分出来的桶必须是唯一只装了一个元素的
kv* find_hash(kv* first, kv* last, char const* key) {
    unsigned i = hash(key);
    return strcmp(first[i].key, key) ? last: first + i;
}

bool test_result(kv const* result,
                                kv const* end, 
                                kv const* test,
                                unsigned idx,
                                char const* name) {

    bool rc = true;
    if(result == end) {
        rc &= (test[idx].value == 0);
    } else {
        rc &= (strcmp(test[idx].key, result->key) == 0);
    }

    if(!rc) std::cout << name << " test " << idx << " failed" << std::endl;
    return rc;
}

int test_algorithms(int test_no, unsigned long multiplier) {
    bool rc = true;
    kv* volatile kp;
    switch (test_no) {
    case 1:{  // basic functionality test
        for(unsigned i=0; i<std::size(test); ++i) {
            auto kp = std::find(std::begin(names), std::end(names), test[i].key);
            rc &= test_result(kp, std::end(names), test, i, "std::find()");
        }

        for(unsigned i=0; i<std::size(test); ++i) {
            auto kp = find_unwrapped(std::begin(names), std::end(names), test[i].key);
            rc &= test_result(kp, std::end(names), test, i, "find_unwrapped()");
        }

        for(unsigned i=0; i<std::size(test); ++i) {
            auto kp = find_sorted(std::begin(names), std::end(names), test[i].key);
            rc &= test_result(kp, std::end(names), test, i, "find_sorted()");
        }

        for(unsigned i=0; i<std::size(test); ++i) {
            auto kp = find_binary_3way(std::begin(names), std::end(names), test[i].key);
            rc &= test_result(kp, std::end(names), test, i, "find_binary_3way()");
        }

        for(unsigned i=0; i<std::size(test); ++i) {
            auto kp = find_binary_lessthan(std::begin(names), std::end(names), test[i].key);
            rc &= test_result(kp, std::end(names), test, i, "find_binary_lessthan()");
        }

        for(unsigned i=0; i<std::size(test); ++i) {
            auto kp = find_binary_3way_size(test[i].key, names, std::size(names));
            rc &= test_result(kp, nullptr, test, i, "find_binary_3way_size()");
        }

        for(unsigned i=0; i<std::size(test); ++i) {
            auto kp = find_binary_lessthan_size(test[i].key, names, std::size(names));
            rc &= test_result(kp, nullptr, test, i, "find_binary_lessthan_size()");
        }

        // lower_bound 第一个小于等于key值的位置
        for(unsigned i=0; i<std::size(test); ++i) {
            auto kp = std::lower_bound(std::begin(names), std::end(names), test[i].key);
            if((kp < std::end(names)) && (test[i] < kp->key)) {
                kp = std::end(names);
            }

            rc &= test_result(kp, std::end(names), test, i, "std::lower_bound()");
        }

        // lower_bound() + upper_bound
        // lower_bound返回第一个 <= key的值，upper_bound返回第一个大于key的值
        // 所以如果值存在， 那么lower_bound != upper_bound
        for(unsigned i=0; i<std::size(test); ++i) {
            kp = std::lower_bound(std::begin(names), std::end(names), test[i].key);
            auto kp2= std::upper_bound(std::begin(names), std::end(names), test[i].key);
            if(kp == kp2) {
                kp = std::end(names);
            }

            rc &= test_result(kp, std::end(names), test, i, "lower_bound/upper_bound 1");
        }

        // 换了一下upper_bound的起始点
        for (unsigned i = 0; i < std::size(test); ++i) {
            kp       = std::lower_bound(std::begin(names), std::end(names), test[i].key);
            auto kp2 = std::upper_bound(kp, std::end(names), test[i].key);
            if (kp == kp2)
                kp = std::end(names);

            rc &= test_result(kp, std::end(names), test, i, "lower_bound/upper_bound 2");
        }

        // std::equal_range 这个函数的返回值是包含当前元素值的范围的迭代器，返回值包左，不包右
        // 例如 [10, 10, 10,20, 20, 30] 将会返回 [20, 20, 30]，left iterator = 20, right iterator = 30
        // 所以如果有值，equal_range的两个迭代器，肯定是不相等的
        for(unsigned i=0; i<std::size(test); ++i) {
            auto res = std::equal_range(std::begin(names), std::end(names), test[i].key);
            if(res.first == res.second) {
                res.first = std::end(names);
            }
            rc &= test_result(res.first, std::end(names), test, i, "std::equal_range()");
        }

        for(unsigned i=0; i<std::size(test); ++i) {
            kp = find_hash(std::begin(names), std::end(names), test[i].key);
            rc &= test_result(kp, std::end(names), test, i, "find_hash()");
        }
    }
        break;
    case 2: {
        // linear search using std::find TODO:
        {
            StopWatch sw("std::find()");
            for(unsigned long j=0; j<multiplier; ++j) {
                for(unsigned i=0; i<std::size(test); ++i) {
                    kp = std::find(std::begin(names), std::end(names), test[i].key);
                }
            }
        }

        // linear search using the find algorithm
        {   
            StopWatch sw("find_unwrapped()");
            for(unsigned long j=0; j<multiplier; ++j) {
                for(unsigned i=0; i<std::size(test); ++i) {
                    kp = find_unwrapped(std::begin(names), std::end(names), test[i].key);
                }
            }
        }

        // linear search of sorted table
        {
            StopWatch sw("find_sorted()");
            for(unsigned long j=0; j<multiplier; ++j) {
                for(unsigned i=0; i<std::size(test); ++i) {
                    kp = find_sorted(std::begin(names), std::end(names), test[i].key);
                }
            }
        }
    }
        break;
    case 3:{
        	{// std::binary_search
            StopWatch st("std::binary_search()");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i) {
					auto res = std::binary_search(std::begin(names), std::end(names), test[i].key);
					kp = &names[res ? 0 : 1];
				}
		}
		{//	std::equal_range for binary search.
            StopWatch st("std::equal_range()");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i) {
					auto res = std::equal_range(std::begin(names), std::end(names), test[i].key);
					kp = (res.first == res.second) ? std::end(names) : res.first;
				}
		}
		{//	std::lower_bound / std::upper_bound for binary search.
            StopWatch st("std::lower_bound / std::upper_bound test 1");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i) {
					kp       = std::lower_bound(std::begin(names), std::end(names), test[i].key);
					auto kp2 = std::upper_bound(std::begin(names), std::end(names), test[i].key);
					kp = (kp == kp2) ? std::end(names) : kp;
				}
		}
		{//	std::lower_bound / std::upper_bound for binary search.
            StopWatch st("std::lower_bound / std::upper_bound test 2");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i) {
					kp       = std::lower_bound(std::begin(names), std::end(names), test[i].key);
					auto kp2 = std::upper_bound(kp,    std::end(names), test[i].key);
					kp = (kp == kp2) ? std::end(names) : kp;
				}
		}
		{//	std::lower_bound for binary search.
            StopWatch st("std::lower_bound()");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i) {
					kp = std::lower_bound(std::begin(names), std::end(names), test[i].key);
					if (kp != std::end(names) && test[i] < kp->key)
						kp = std::end(names);
				}
		}
		{//	custom binary search using <
            StopWatch st("find_binary_lessthan()");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i)
					kp = find_binary_lessthan(std::begin(names), std::end(names), test[i].key);
		}
		{//	custom binary search using strcmp().
            StopWatch st("find_binary_3way()");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i)
					kp = find_binary_3way(std::begin(names), std::end(names), test[i].key);
		}
        {
            StopWatch st("find_binary_lessthan_size()");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i)
                    kp = find_binary_lessthan_size(test[i].key, names, std::size(names));
        }
        {
            StopWatch sw("find_binary_3way_size()");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i)
                    kp = find_binary_3way_size(test[i].key, names, std::size(names));
        }
    }
        break;
    case 4:
    	{
            StopWatch st("find_hash");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i)
                    kp = find_hash(std::begin(names), std::end(names), test[i].key);
		}
        break;
    case 0:
        return 4;
        break;
    default:
        return -1;
        break;
    }
    return (rc)? 1: 0;
}