# Min Version Requirement 
cmake_minimum_required(VERSION 3.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create Project
project(TestProject VERSION 1.0
                  DESCRIPTION "Practice Project"
                  LANGUAGES CXX)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW lib only" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )

add_subdirectory(vendor/glfw)
add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(Loglib)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} $(GLEW_INCLUDE_DIRS) )

# Define the executable
add_executable(TestProject main.cpp)
target_link_libraries(TestProject glfw GLEW::GLEW ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} printlib loglib)
