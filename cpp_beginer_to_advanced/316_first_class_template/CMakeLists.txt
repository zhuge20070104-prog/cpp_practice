cmake_minimum_required(VERSION 3.5)

project(316_first_class_template LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(316_first_class_template main.cpp)


include(GNUInstallDirs)
install(TARGETS 316_first_class_template
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
