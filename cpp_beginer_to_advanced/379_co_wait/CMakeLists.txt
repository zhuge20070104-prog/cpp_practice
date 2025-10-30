cmake_minimum_required(VERSION 3.5)

project(379_co_wait LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(379_co_wait main.cpp)


include(GNUInstallDirs)
install(TARGETS 379_co_wait
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
