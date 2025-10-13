cmake_minimum_required(VERSION 3.5)

project(314_box_container_practicing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(314_box_container_practicing main.cpp
    stream_insertable.cpp
    box_container.cpp
)


include(GNUInstallDirs)
install(TARGETS 314_box_container_practicing
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
