cmake_minimum_required(VERSION 3.24)
project(learnOpenGL)

set(CMAKE_CXX_STANDARD 17)

find_library(GLFW3 libglfw.3.dylib PATHS Users/yuria20/CLionProjects/learnOpenGL/lib)
if (NOT GLFW3)
    message(FATAL_ERROR "GLFW3 library not found")
endif()

add_executable(learnOpenGL main.cpp glad.c)

target_include_directories(learnOpenGL PUBLIC include/GLAD/glad)
target_include_directories(learnOpenGL PUBLIC include/GLFW/GLFW)
target_include_directories(learnOpenGL PUBLIC include/GLM)
target_include_directories(learnOpenGL PUBLIC include/MYHEAD/include)

target_link_libraries(learnOpenGL ${GLFW3})



