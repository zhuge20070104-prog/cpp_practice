cmake_minimum_required(VERSION 3.5)

project(376_view_composition_and_pipe_operator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(376_view_composition_and_pipe_operator main.cpp)


include(GNUInstallDirs)
install(TARGETS 376_view_composition_and_pipe_operator
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
