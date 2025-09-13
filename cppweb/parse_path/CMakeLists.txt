cmake_minimum_required(VERSION 3.7)
project(parse_path)

set(CMAKE_CXX_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(Threads)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(parse_path main.cpp sqlite3.c sqllite_op.cc)
target_link_libraries(parse_path ${Boost_LIBRARIES} Threads::Threads dl)

add_executable(data_maker data_maker.cpp sqlite3.c sqllite_op.cc)
target_link_libraries(data_maker ${Boost_LIBRARIES} Threads::Threads dl)