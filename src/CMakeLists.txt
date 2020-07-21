project(print_lib)

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB HEADERS ${CMAKE_SOURCE_DIR}/include/*.h)
file(GLOB HEADER_DIR ${CMAKE_SOURCE_DIR}/include)

add_library(printlib STATIC ${SOURCES} ${HEADERS})
target_include_directories(printlib PUBLIC ${HEADER_DIR})

