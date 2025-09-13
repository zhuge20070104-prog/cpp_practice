cmake_minimum_required(VERSION 3.1)

project(164_qml_extend_bindings LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BINARY_DIR /home/fredric/code/cpp_practice/qt_demo/164_qml_extend_bindings/build)

add_definitions(-g)
#add_definitions(-DQT_QML_DEBUG)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

conan_basic_setup()

find_package(Qt5 COMPONENTS Core Quick QuickControls2 REQUIRED)

add_executable(${PROJECT_NAME} "main.cpp" "qml.qrc" "piechart.cpp")
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick Qt5::QuickControls2 ${CONAN_LIBS})
