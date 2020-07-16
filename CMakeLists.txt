cmake_minimum_required(VERSION 3.2)

project(TestProject VERSION 1.0
                  DESCRIPTION "Practice Project"
                  LANGUAGES CXX)

add_library(printfunction STATIC src/PrintFunction.cpp include/PrintFunction.h)
target_include_directories(printfunction PUBLIC include)

add_executable(Project main.cpp)
target_link_libraries(Project PUBLIC printfunction)
