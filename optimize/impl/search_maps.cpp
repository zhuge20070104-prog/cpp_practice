#include <iostream>
#include <string>
#include <map>
#include "charbuf.h"
#include "stopwatch11.h"

struct kv { // (key, value) pairs
    char const* key;
    unsigned value;
};

static kv names[] = {
	{ "alpha",   1 },   { "bravo",   2 },   { "charlie", 3 },   { "delta",  4 },
    { "echo",    5 },   { "foxtrot", 6 },   { "golf",    7 },   { "hotel",  8 },
    { "india",   9 },   { "juliet", 10 },   { "kilo",   11 },   { "lima",   12 },
    { "mike",   13 },   { "november",14 },  { "oscar",  15 },   { "papa",   16 },
    { "quebec", 17 },   { "romeo",  18 },   { "sierra", 19 },   { "tango",  20 },
    { "uniform",21 },   { "victor", 22 },   { "whiskey",23 },   { "xray",   24 },
    { "yankee", 25 },   { "zulu",   26 }
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

bool less_for_cstrings_free(char const* p1, char const* p2) {
    return strcmp(p1, p2) < 0;
}

int test_maps(int test_no, unsigned long multiplier) {
    bool rc = true;
    switch (test_no) {
    case 1: {

    }
        break;
    case 2: { // map
        {
            std::map<std::string, unsigned> kvmap;
            using value_type = std::map<std::string, unsigned>::value_type;
            for(auto it=names; it!=names + std::size(names); ++it) {
                kvmap.insert(value_type(it->key, it->value));
            }

            StopWatch sw("map<std::string> std::less");
            for(unsigned j=0; j<multiplier; ++j) {
                for(unsigned i=0; i<std::size(test); ++i) {
                    auto it = kvmap.find(test[i].key);
                    rc &= (it==kvmap.end() || it->second < 27);
                }
            }
        }

        // std::map charbuf<>
        {
            std::map<charbuf<>, unsigned> kvmap;
            using value_type = std::map<charbuf<>, unsigned>::value_type;
            for(auto it=names; it!=names+std::size(names); ++it) {
                kvmap.insert(value_type(it->key, it->value));
            }

            StopWatch sw("map<charbuf>");
            for(unsigned long j=0; j<multiplier; ++j) {
                for(unsigned i=0; i<std::size(test); ++i) {
                    auto it = kvmap.find(test[i].key);
                    rc &= (it==kvmap.end() || it->second < 27);
                }
            }
        }

        // std::map<char*, unsigned, free_function>
        {
            std::map<char const*, unsigned, bool(*)(char const*, char const*)> kvmap(less_for_cstrings_free);
            using value_type = std::map<char const*, unsigned, bool(*)(char const*, char const*)>::value_type;
            for(auto it=names; it!=names+std::size(names); ++it) {
                kvmap.insert(value_type(it->key, it->value));
            }

            StopWatch sw("map<char*> free function");
            for(unsigned long j=0; j<multiplier; ++j) {
                for(unsigned i=0; i<std::size(test); ++i) {
                    auto it = kvmap.find(test[i].key);
                    rc &= (it==kvmap.end() || it->second < 27);
                }
            }
        }

        // std::map<char*> function object
        {
            struct less_for_c_strings {
                bool operator()(char const* p1, char const* p2) const {
                    return strcmp(p1, p2) < 0;
                }
            };

            std::map<char const*, unsigned, less_for_c_strings> kvmap;
            using value_type =  std::map<char const*, unsigned, less_for_c_strings>::value_type;
            for(auto it=names; it!=names+std::size(names); ++it) {
                kvmap.insert(value_type(it->key, it->value));
            }

            StopWatch sw("map<char*> function-object");
            for(unsigned long j=0; j<multiplier; ++j) {
                for(unsigned i=0; i<std::size(test); ++i) {
                    auto it = kvmap.find(test[i].key);
                    rc &= (it==kvmap.end() || it->second < 27);
                }
            }
        }

        // std::map<char*> lambda
        {
            auto cmp = [](char const* p1, char const* p2) {
                return strcmp(p1, p2) < 0;
            };

            std::map<char const*, unsigned, decltype(cmp)> kvmap(cmp);
            using value_type = std::map<char const*, unsigned, decltype(cmp)>::value_type;
            for (auto it = names; it != names + std::size(names); ++it) {
				kvmap.insert(value_type(it->key, it->value));
            }

            StopWatch sw("map<char*> lambda");
            for(unsigned long j=0; j<multiplier; ++j) {
                for(unsigned i=0; i<std::size(test); ++i) {
                    auto it = kvmap.find(test[i].key);
                    rc &= (it==kvmap.end() || it->second < 27);
                }
            }
        }
    }
        break;
    
    case 0:
        return 2;
    default:
        return -1;
    }

    return (rc) ? 1: 0;
}