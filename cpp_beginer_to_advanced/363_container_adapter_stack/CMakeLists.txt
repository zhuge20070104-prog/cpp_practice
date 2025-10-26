cmake_minimum_required(VERSION 3.5)

project(363_container_adapter_stack LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(363_container_adapter_stack main.cpp)


include(GNUInstallDirs)
install(TARGETS 363_container_adapter_stack
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
