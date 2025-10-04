cmake_minimum_required(VERSION 3.5)

project(273_base_class_access_specifiers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(273_base_class_access_specifiers main.cpp
    person.cpp    
    player.cpp
    nurse.cpp
    engineer.cpp)


include(GNUInstallDirs)
install(TARGETS 273_base_class_access_specifiers
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
