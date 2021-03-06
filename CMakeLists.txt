cmake_minimum_required(VERSION 3.0)
project(kekule_engine)

set(CMAKE_CXX_FLAGS "-Wall -O0 -g")

#define opengl library name
if (WIN32)  #for windows
    set(OGL opengl32)
elseif (UNIX AND NOT APPLE) #for linux
    set(OGL GL)
endif ()

#dependencies
set(GLFW_ROOT "${CMAKE_SOURCE_DIR}/deps/glfw")
set(GLEW_ROOT "${CMAKE_SOURCE_DIR}/deps/glew")

#to link glfw porperly
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${GLFW_ROOT})
add_subdirectory(${GLEW_ROOT})
include_directories("${GLFW_ROOT}/include")
include_directories("${GLEW_ROOT}/include")


#engine libs
add_subdirectory(src/graphics)
add_subdirectory(src/window)
add_subdirectory(src/maths)

add_executable(kekule_engine src/main.cpp)
target_link_libraries(kekule_engine window graphics kmath)

#engine #defines
target_compile_definitions(kekule_engine PUBLIC KEKULE_DEBUG)