cmake_minimum_required(VERSION 3.5)

project(381_co_return LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(381_co_return main.cpp)


include(GNUInstallDirs)
install(TARGETS 381_co_return
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
