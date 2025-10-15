cmake_minimum_required(VERSION 3.1...3.9)
project(defer)
add_library(defer src/defer.c)
target_include_directories(defer PRIVATE include)
add_executable(main src/main.c)
target_include_directories(main PRIVATE include)
target_link_libraries(main PRIVATE defer)

