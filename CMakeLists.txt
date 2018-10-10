cmake_minimum_required(VERSION 3.0)
project(kekule_engine)

set(CMAKE_CXX_FLAGS "-Wall -g")

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

if(MSVC)
	add_executable(kekule_engine
		src/main.cpp
		src/window/window.cpp)
	target_link_libraries(kekule_engine glfw glew opengl32)
else()
#engine libs
add_subdirectory(src/window)

add_executable(kekule_engine src/main.cpp)
target_link_libraries(kekule_engine window)
endif()