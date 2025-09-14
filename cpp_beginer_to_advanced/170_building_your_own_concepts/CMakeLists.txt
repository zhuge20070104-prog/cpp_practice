cmake_minimum_required(VERSION 3.5)

project(170_building_your_own_concepts LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(170_building_your_own_concepts main.cpp)

include(GNUInstallDirs)
install(TARGETS 170_building_your_own_concepts
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
