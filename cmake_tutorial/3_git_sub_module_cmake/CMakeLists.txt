cmake_minimum_required(VERSION 3.10.2)

project(OLAS)

find_package(Git QUIET)
if(GIT_FOUND)
# Update submodule as needed 
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive 
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_SUBMODULE_RESULT)
        
        if(NOT GIT_SUBMODULE_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update -init failed with ${GIT_SUBMODULE_RESULT}, please check the status") 
        endif()
    endif()
endif()

# Check all the submodules
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The gflw submodule was not downloaded! GIT_SUBMODULE was turned off or failed. Please check and try again")
endif()


link_directories(external/glfw/src)
add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME} PUBLIC external/glfw/include)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)