cmake_minimum_required(VERSION 3.5)

project(280_final_and_override LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(280_final_and_override main.cpp)


include(GNUInstallDirs)
install(TARGETS 280_final_and_override
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
