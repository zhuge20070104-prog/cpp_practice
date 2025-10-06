cmake_minimum_required(VERSION 3.5)

project(285_dynamic_casts LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(285_dynamic_casts main.cpp)


include(GNUInstallDirs)
install(TARGETS 285_dynamic_casts
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
