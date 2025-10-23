cmake_minimum_required(VERSION 3.5)

project(357_sequence_container_array_revisited LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(357_sequence_container_array_revisited main.cpp)


include(GNUInstallDirs)
install(TARGETS 357_sequence_container_array_revisited
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
