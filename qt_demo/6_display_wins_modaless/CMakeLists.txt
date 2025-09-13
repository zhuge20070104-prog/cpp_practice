cmake_minimum_required(VERSION 3.5)

project(6_display_wins_modaless VERSION 0.1 LANGUAGES CXX)

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
        window.cpp
        window.h
        window.ui
        
        dialog.h
        dialog.cpp
        dialog.ui
)

add_executable(6_display_wins_modaless
            ${PROJECT_SOURCES}
        )

target_link_libraries(6_display_wins_modaless  Qt${QT_VERSION_MAJOR}::Widgets ${CONAN_LIBS})