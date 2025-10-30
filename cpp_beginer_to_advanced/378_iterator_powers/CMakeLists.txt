cmake_minimum_required(VERSION 3.5)

project(378_iterator_powers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(378_iterator_powers main.cpp)


include(GNUInstallDirs)
install(TARGETS 378_iterator_powers
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
