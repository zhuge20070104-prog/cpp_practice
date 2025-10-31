cmake_minimum_required(VERSION 3.5)

project(382_custom_generator_coroutine_type LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(382_custom_generator_coroutine_type main.cpp)


include(GNUInstallDirs)
install(TARGETS 382_custom_generator_coroutine_type
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
