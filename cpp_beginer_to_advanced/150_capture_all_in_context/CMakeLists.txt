cmake_minimum_required(VERSION 3.5)

project(150_capture_all_in_context LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(150_capture_all_in_context main.cpp)

include(GNUInstallDirs)
install(TARGETS 150_capture_all_in_context
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
