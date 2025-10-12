cmake_minimum_required(VERSION 3.5)

project(311_exceptions_as_class_objects_with_inheritance_hierarchies LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(311_exceptions_as_class_objects_with_inheritance_hierarchies main.cpp
)


include(GNUInstallDirs)
install(TARGETS 311_exceptions_as_class_objects_with_inheritance_hierarchies
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
