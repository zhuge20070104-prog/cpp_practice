cmake_minimum_required(VERSION 3.5)

project(324_class_templates_with_concept LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(324_class_templates_with_concept main.cpp)


include(GNUInstallDirs)
install(TARGETS 324_class_templates_with_concept
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
