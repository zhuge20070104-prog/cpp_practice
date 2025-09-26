cmake_minimum_required(VERSION 3.5)

project(236_weak_ptrs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(236_weak_ptrs main.cpp
    dog.cpp
    person.cpp)


include(GNUInstallDirs)
install(TARGETS 236_weak_ptrs
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
