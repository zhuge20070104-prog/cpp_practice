cmake_minimum_required(VERSION 3.5)

project(137_func_define_with_return_type_deduct LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(137_func_define_with_return_type_deduct main.cpp)

include(GNUInstallDirs)
install(TARGETS 137_func_define_with_return_type_deduct
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
