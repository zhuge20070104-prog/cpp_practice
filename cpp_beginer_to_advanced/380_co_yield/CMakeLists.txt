cmake_minimum_required(VERSION 3.5)

project(380_co_yield LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(380_co_yield main.cpp)


include(GNUInstallDirs)
install(TARGETS 380_co_yield
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
