cmake_minimum_required(VERSION 3.24)
project(opengl_learn)

set(CMAKE_CXX_STANDARD 14)

include_directories(opengl-learn)

add_executable(opengl-learn src/Application.cpp)

find_package(glfw3 3.3 REQUIRED)
find_package(JPEG REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

target_include_directories(opengl-learn PRIVATE ${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIR} ${JPEG_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLM_INCLUDE_DIR})
target_link_libraries(opengl-learn glfw GLEW::GLEW ${JPEG_LIBRARIES} OpenGL::GL)
