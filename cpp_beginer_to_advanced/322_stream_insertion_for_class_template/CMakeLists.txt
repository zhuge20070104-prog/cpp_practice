cmake_minimum_required(VERSION 3.5)

project(322_stream_insertion_for_class_template LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(322_stream_insertion_for_class_template main.cpp)


include(GNUInstallDirs)
install(TARGETS 322_stream_insertion_for_class_template
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
