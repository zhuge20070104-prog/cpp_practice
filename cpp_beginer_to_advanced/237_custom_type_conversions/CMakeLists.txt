cmake_minimum_required(VERSION 3.5)

project(237_custom_type_conversions LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(237_custom_type_conversions main.cpp
    dog.cpp
    person.cpp)


include(GNUInstallDirs)
install(TARGETS 237_custom_type_conversions
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
