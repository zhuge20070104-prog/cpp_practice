cmake_minimum_required(VERSION 3.5)

project(14_qlabel VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)



set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

conan_basic_setup()

set(PROJECT_SOURCES
        main.cpp     
        dialog.h
        dialog.cpp
        dialog.ui
)

SET(CMAKE_INCLUDE_PATH "${CMAKE_INCLUDE_PATH};${CMAKE_BINARY_DIR}/${PROJECT_NAME}_autogen/include") 

message(STATUS "include_path: ${CMAKE_INCLUDE_PATH}")



add_executable(14_qlabel
            ${PROJECT_SOURCES}
        )



target_link_libraries(14_qlabel  Qt${QT_VERSION_MAJOR}::Widgets ${CONAN_LIBS})



