cmake_minimum_required(VERSION 3.5)

project(233_creating_shared_ptr_from_unique_ptr LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(233_creating_shared_ptr_from_unique_ptr main.cpp
    dog.cpp)


include(GNUInstallDirs)
install(TARGETS 233_creating_shared_ptr_from_unique_ptr
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
