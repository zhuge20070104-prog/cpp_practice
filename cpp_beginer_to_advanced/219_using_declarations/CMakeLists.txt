cmake_minimum_required(VERSION 3.5)

project(219_using_declarations LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(219_using_declarations main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/classes/point.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/classes/line.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/classes/cylinder.cpp)


include(GNUInstallDirs)
install(TARGETS 219_using_declarations
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
