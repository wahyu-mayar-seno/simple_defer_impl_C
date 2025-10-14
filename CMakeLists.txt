cmake_minimum_required(VERSION 3.1...3.9)
project(defer)
add_executable(main src/main.c)
target_include_directories(main PRIVATE include)
