cmake_minimum_required(VERSION 3.5)

project(139_introduce_std_optional LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(139_introduce_std_optional main.cpp)

include(GNUInstallDirs)
install(TARGETS 139_introduce_std_optional
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
