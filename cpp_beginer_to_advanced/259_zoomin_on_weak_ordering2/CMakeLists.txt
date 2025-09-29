cmake_minimum_required(VERSION 3.5)

project(259_zoomin_on_weak_ordering2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(259_zoomin_on_weak_ordering2 main.cpp)


include(GNUInstallDirs)
install(TARGETS 259_zoomin_on_weak_ordering2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
