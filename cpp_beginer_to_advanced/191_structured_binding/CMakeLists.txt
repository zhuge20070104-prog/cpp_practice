cmake_minimum_required(VERSION 3.5)

project(191_structured_binding LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(191_structured_binding main.cpp)


include(GNUInstallDirs)
install(TARGETS 191_structured_binding
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
