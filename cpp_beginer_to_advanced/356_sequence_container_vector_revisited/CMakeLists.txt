cmake_minimum_required(VERSION 3.5)

project(356_sequence_container_vector_revisited LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(356_sequence_container_vector_revisited main.cpp)


include(GNUInstallDirs)
install(TARGETS 356_sequence_container_vector_revisited
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
