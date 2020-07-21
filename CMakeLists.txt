# Min Version Requirement 
cmake_minimum_required(VERSION 3.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create Project
project(TestProject VERSION 1.0
                  DESCRIPTION "Practice Project"
                  LANGUAGES CXX)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/glfw)
add_subdirectory(src)
add_subdirectory(include)

find_package(OpenGL REQUIRED)

# Define the executable
add_executable(TestProject main.cpp)
target_link_libraries(TestProject glfw ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES} printlib)
