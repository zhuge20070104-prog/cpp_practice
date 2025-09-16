cmake_minimum_required(VERSION 3.5)

project(180_class_across_multiple_files LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/objects)

add_executable(180_class_across_multiple_files main.cpp
    objects/cylinder.cpp
)


include(GNUInstallDirs)
install(TARGETS 180_class_across_multiple_files
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
