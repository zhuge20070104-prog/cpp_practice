cmake_minimum_required(VERSION 3.5)

project(300_noexcept_specifier LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(300_noexcept_specifier main.cpp
)


include(GNUInstallDirs)
install(TARGETS 300_noexcept_specifier
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
