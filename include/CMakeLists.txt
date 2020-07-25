cmake_minimum_required(VERSION 3.2)
project(print_lib)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB HEADERS ${CMAKE_SOURCE_DIR}/include/*.h)
file(GLOB HEADER_DIR ${CMAKE_SOURCE_DIR}/include)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW lib only" FORCE)
#set(GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLM REQUIRED)

add_library(printlib STATIC ${SOURCES} ${HEADERS})
target_include_directories(printlib PUBLIC ${HEADER_DIR} ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS})
target_link_libraries(printlib glfw ${GLM_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} imgui)