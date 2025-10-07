cmake_minimum_required(VERSION 3.5)

project(286_polymorphic_funcs_and_destructors LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(286_polymorphic_funcs_and_destructors main.cpp)


include(GNUInstallDirs)
install(TARGETS 286_polymorphic_funcs_and_destructors
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
