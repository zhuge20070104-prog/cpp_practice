cmake_minimum_required(VERSION 3.5)

project(289_abstract_classes_as_interface LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(289_abstract_classes_as_interface main.cpp
    stream_insertable.cpp
)


include(GNUInstallDirs)
install(TARGETS 289_abstract_classes_as_interface
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
