cmake_minimum_required(VERSION 3.5)

project(340_function_point_type_aliases_with_template LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(340_function_point_type_aliases_with_template main.cpp)


include(GNUInstallDirs)
install(TARGETS 340_function_point_type_aliases_with_template
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
