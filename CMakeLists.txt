cmake_minimum_required(VERSION 3.24)
project(learnOpenGL)

set(CMAKE_CXX_STANDARD 17)

find_library(GLFW3a glfw3 PATHS C:/Users/user/CLionProjects/opengl/lib)
if (NOT GLFW3a)
    message(FATAL_ERROR "GLFW3a library not found")
endif()
find_library(GLFW3b libglfw3 PATHS C:/Users/user/CLionProjects/opengl/lib)
if (NOT GLFW3b)
    message(FATAL_ERROR "GLFW3b library not found")
endif()
find_library(GLFW3c libglfw3dll PATHS C:/Users/user/CLionProjects/opengl/lib)
if (NOT GLFW3c)
    message(FATAL_ERROR "GLFW3c library not found")
endif()

# assimp
find_library(ASSIMP libassimpd PATHS C:/Users/user/CLionProjects/opengl/lib)
if (NOT ASSIMP)
    message(FATAL_ERROR "ASSIMP library not found")
endif()




add_executable(opengl main.cpp glad.c )

target_include_directories(opengl PUBLIC include)
target_include_directories(opengl PUBLIC include/MYHEAD/include)

target_link_libraries(opengl ${GLFW3a})
target_link_libraries(opengl ${GLFW3b})
target_link_libraries(opengl ${GLFW3c})
target_link_libraries(opengl ${ASSIMP})
