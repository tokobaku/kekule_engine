add_library(window window.cpp input.cpp logging.cpp)
target_link_libraries(window glfw glew opengl32)