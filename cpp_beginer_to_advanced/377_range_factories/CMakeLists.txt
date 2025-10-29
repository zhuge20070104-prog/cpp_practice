cmake_minimum_required(VERSION 3.5)

project(377_range_factories LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(377_range_factories main.cpp)


include(GNUInstallDirs)
install(TARGETS 377_range_factories
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
