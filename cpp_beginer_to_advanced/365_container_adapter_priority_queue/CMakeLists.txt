cmake_minimum_required(VERSION 3.5)

project(365_container_adapter_priority_queue LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(365_container_adapter_priority_queue main.cpp)


include(GNUInstallDirs)
install(TARGETS 365_container_adapter_priority_queue
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
