cmake_minimum_required(VERSION 3.5)

project(251_subscript_operator_for_collection_types LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(251_subscript_operator_for_collection_types main.cpp
    scores.cpp)


include(GNUInstallDirs)
install(TARGETS 251_subscript_operator_for_collection_types
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
