cmake_minimum_required(VERSION 3.5)

project(245_type_conversions_recap LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(245_type_conversions_recap main.cpp
    car.cpp
    number.cpp
    point.cpp)


include(GNUInstallDirs)
install(TARGETS 245_type_conversions_recap
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
