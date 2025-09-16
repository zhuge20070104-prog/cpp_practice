cmake_minimum_required(VERSION 3.5)

project(181_arrow_pointer_call_notation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(181_arrow_pointer_call_notation main.cpp)


include(GNUInstallDirs)
install(TARGETS 181_arrow_pointer_call_notation
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
