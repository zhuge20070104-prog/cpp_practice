#ifndef _FREDRIC_NET_COMMON_H_
#define _FREDRIC_NET_COMMON_H_
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>
#include <optional>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <type_traits>


#include <boost/asio.hpp>
#include <boost/system/system_error.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>
#endif