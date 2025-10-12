cmake_minimum_required(VERSION 3.5)

project(307_handling_exceptions_at_different_levels LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(307_handling_exceptions_at_different_levels main.cpp
)


include(GNUInstallDirs)
install(TARGETS 307_handling_exceptions_at_different_levels
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
