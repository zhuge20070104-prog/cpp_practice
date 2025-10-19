cmake_minimum_required(VERSION 3.5)

project(346_std_vector LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(346_std_vector main.cpp)


include(GNUInstallDirs)
install(TARGETS 346_std_vector
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
