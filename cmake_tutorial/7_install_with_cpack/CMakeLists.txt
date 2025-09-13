cmake_minimum_required(VERSION 3.10.2)

project(OLAS VERSION 1.3)

configure_file(olas_config.h.in olas_config.h)

add_subdirectory(lib)

add_definitions(-g)

link_directories(${EXTRA_LINK_DIRS})

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC lib
    ${PROJECT_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} my_math)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/olas_config.h" DESTINATION include)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${OLAS_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${OLAS_VERSION_MINOR}")
include(CPack)