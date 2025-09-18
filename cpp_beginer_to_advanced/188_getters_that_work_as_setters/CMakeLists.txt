cmake_minimum_required(VERSION 3.5)

project(188_getters_that_work_as_setters LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(188_getters_that_work_as_setters main.cpp)


include(GNUInstallDirs)
install(TARGETS 188_getters_that_work_as_setters
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
