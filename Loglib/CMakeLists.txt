project(log_lib)

add_library(loglib STATIC LogFunc.cpp LogFunc.h Logger.h)
target_include_directories(printlib PUBLIC ${CMAKE_SOURCE_DIR}/Loglib)