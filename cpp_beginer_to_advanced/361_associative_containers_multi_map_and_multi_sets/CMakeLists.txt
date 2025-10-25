cmake_minimum_required(VERSION 3.5)

project(361_associative_containers_multi_map_and_multi_sets LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(361_associative_containers_multi_map_and_multi_sets main.cpp)


include(GNUInstallDirs)
install(TARGETS 361_associative_containers_multi_map_and_multi_sets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
