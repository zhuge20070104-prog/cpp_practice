cmake_minimum_required(VERSION 3.7)
project(query_sql)

set(CMAKE_CXX_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(Threads)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(query_sql main.cpp sqlite3.c sqllite_op.cc)
target_link_libraries(query_sql ${Boost_LIBRARIES} Threads::Threads dl)

add_executable(data_maker data_maker.cpp sqlite3.c sqllite_op.cc)
target_link_libraries(data_maker ${Boost_LIBRARIES} Threads::Threads dl)