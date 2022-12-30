cmake_minimum_required(VERSION 3.23)
project(opengl_learn)

set(CMAKE_CXX_STANDARD 23)

include_directories(src)

add_executable(src src/main.cpp)

find_package(PkgConfig REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(JPEG REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(src glfw OpenGL::GL GLEW::GLEW ${JPEG_LIBRARIES} ${OPENGL_LIBRARIES})
target_include_directories(src PRIVATE ${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIR} ${JPEG_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLM_INCLUDE_DIR})
