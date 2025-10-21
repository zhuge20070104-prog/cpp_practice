cmake_minimum_required(VERSION 3.5)

project(352_std_begin_std_end LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(352_std_begin_std_end main.cpp)


include(GNUInstallDirs)
install(TARGETS 352_std_begin_std_end
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
