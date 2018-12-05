add_library(graphics STATIC shader.cpp buffer_objects.cpp renderable.cpp graphics.cpp renderer.cpp camera.cpp)
target_link_libraries(graphics glew glfw opengl32)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})