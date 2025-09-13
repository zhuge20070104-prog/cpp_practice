#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "log.hpp"
#include <utility>

#define BOOST_TEST_MODULE TimestampTest
#include "test.hpp"

// 23590231239405

struct NearestTime {
    std::string video_sub_dir;
    int min_index;
    uint64_t min_val;
    uint64_t frame_ts;

    friend std::ostream& operator<<(std::ostream& os, NearestTime const& n_time) {
        os << "Video sub dir: " << n_time.video_sub_dir << " min_index: " << n_time.min_index << " min_val: " << n_time.min_val
            << " frame_timestamp: " << n_time.frame_ts;
        return os;
    }
};

NearestTime find_nearest_time(std::string const& to_find_ts, std::vector<std::vector<unsigned long>> timestamps_list) {
    std::vector<NearestTime> nearest_times;
    uint64_t to_find_uint64;
    char* end;
    to_find_uint64 = strtoull( to_find_ts.c_str(), &end, 10);

    for(auto const& frame_timestamps: timestamps_list) {
        uint64_t min_val = std::numeric_limits<uint64_t>::max();
        int  min_idx = -1;
        uint64_t frame_ts = -1;

        for(int i=0; i<frame_timestamps.size(); ++i) {
            auto new_abs = std::llabs(frame_timestamps[i] - to_find_uint64);
            // 注意: 等于0的情况已经被handle过了， handle的套路是 frame_timestamps[i] == to_find_uint64
            if (new_abs > 0 && new_abs < min_val) {
                min_val = new_abs;
                min_idx = i;
                frame_ts = frame_timestamps[i];
            }
        }
        nearest_times.push_back(NearestTime{"extra_fake", min_idx, min_val, frame_ts});
    }

    NearestTime n_time = nearest_times[0];
    uint64_t min_val = nearest_times[0].min_val;

    for(auto const& nearest_time: nearest_times) {
        std::cout << "Current time: " << nearest_time << "\n";
        if(nearest_time.min_val < min_val) {
            n_time = nearest_time;
        }
    }
    return n_time;
}

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(TestTimestampSimple) {
    std::vector<std::vector<unsigned long>> timestamps_list {
        {1, 2, 3},
        {5, 6, 7},
        {8, 9, 10}};

    std::string to_find_ts {"4"};
    auto nearest_time = find_nearest_time(to_find_ts, timestamps_list);
    std::cout << "Nearest Time: " << nearest_time << "\n";
    BOOST_TEST(nearest_time.frame_ts == 3, "Frame timestamp not as expected");
}

BOOST_AUTO_TEST_CASE(TestTimestampProduction) {
    std::vector<std::vector<unsigned long>> timestamps_list {
            {23590231239405, 15086516836730, 15152236836730},
            {15065636836730, 15075836836730,  15055836836730},
            {15139836836730, 15129076836730, 15099355836730, 15118676836730}};

    std::string to_find_ts {"15099355836731"};
    auto nearest_time = find_nearest_time(to_find_ts, timestamps_list);
    std::cout << "Nearest Time: " << nearest_time << "\n";

    BOOST_TEST(nearest_time.frame_ts == (uint64_t)15099355836730, "Frame timestamp not as expected");
}

BOOST_AUTO_TEST_CASE(TestTimestampProduction2) {
    std::vector<std::vector<unsigned long>> timestamps_list {
            {23590231239405, 15086516836730, 15152236836730},
            {15065636836730, 15075836836730,  15055836836730},
            {15139836836730, 15129076836730, 15099355836730, 15118676836730}};

    std::string to_find_ts {"15074836836730"};
    auto nearest_time = find_nearest_time(to_find_ts, timestamps_list);
    std::cout << "Nearest Time: " << nearest_time << "\n";

    BOOST_TEST(nearest_time.frame_ts == (uint64_t)15075836836730, "Frame timestamp not as expected");
}
BOOST_AUTO_TEST_SUITE_END()
