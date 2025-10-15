cmake_minimum_required(VERSION 3.5)

project(323_type_traits_and_static_assets LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(323_type_traits_and_static_assets main.cpp)


include(GNUInstallDirs)
install(TARGETS 323_type_traits_and_static_assets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
