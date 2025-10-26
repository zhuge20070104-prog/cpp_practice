cmake_minimum_required(VERSION 3.5)

project(364_container_adapter_queue LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(364_container_adapter_queue main.cpp)


include(GNUInstallDirs)
install(TARGETS 364_container_adapter_queue
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
