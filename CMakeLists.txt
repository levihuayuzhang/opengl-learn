cmake_minimum_required(VERSION 3.24)
project(opengl_learn)

set(CMAKE_CXX_STANDARD 14)

include_directories(opengl-learn)

add_executable(opengl-learn opengl-learn/main.cpp)

set(glm_DIR /usr/lib/cmake/glm/)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(JPEG REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(opengl-learn ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} ${JPEG_LIBRARIES} ${OPENGL_LIBRARIES})
target_include_directories(opengl-learn PRIVATE ${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIR} ${JPEG_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLM_INCLUDE_DIR})
