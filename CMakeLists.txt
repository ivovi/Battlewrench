cmake_minimum_required (VERSION 3.0)
project(GLFWtest)

set(CMAKE_C_STANDARD 99)

#GLFW additions
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/glfw)
include_directories(glad)

set(SOURCE_FILES src/main.c)

add_executable(engine
    ${SOURCE_FILES}
    lib/glad/src/glad.c
)

target_link_libraries(engine glfw ${GLFW_LIBRARIES})