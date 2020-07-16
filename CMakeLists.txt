cmake_minimum_required(VERSION 3.2)

project(TestProject VERSION 1.0
                  DESCRIPTION "Practice Project"
                  LANGUAGES CXX)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)

add_library(printfunction STATIC src/PrintFunction.cpp include/PrintFunction.h)
target_include_directories(printfunction PUBLIC include)

add_executable(Project main.cpp ${sources} ${headers})
target_link_libraries(Project PUBLIC printfunction)
