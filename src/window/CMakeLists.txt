add_library(window window.cpp input.cpp)
target_link_libraries(window glfw glew opengl32)