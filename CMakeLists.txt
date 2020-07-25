# Min Version Requirement 
cmake_minimum_required(VERSION 3.2)

set(CMAKE_MODULE_PATH /home/user/Libs/cmake)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create Project
project(TestProject VERSION 1.0
                  DESCRIPTION "Practice Project"
                  LANGUAGES CXX)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/imgui)
add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(Loglib)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLM REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS})

# Define the executable
add_executable(TestProject main.cpp)
target_link_libraries(TestProject glfw ${GLM_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} printlib loglib imgui)
