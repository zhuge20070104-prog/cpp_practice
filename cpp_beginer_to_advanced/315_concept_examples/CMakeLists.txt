cmake_minimum_required(VERSION 3.5)

project(315_concept_examples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(315_concept_examples main.cpp
)


include(GNUInstallDirs)
install(TARGETS 315_concept_examples
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
