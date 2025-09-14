cmake_minimum_required(VERSION 3.5)

project(166_template_return_type_deduction_with_auto LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(166_template_return_type_deduction_with_auto main.cpp)

include(GNUInstallDirs)
install(TARGETS 166_template_return_type_deduction_with_auto
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
