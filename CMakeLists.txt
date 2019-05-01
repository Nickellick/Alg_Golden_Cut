cmake_minimum_required(VERSION 3.14)
project(Alg_Golden_Cut C)

set(CMAKE_C_STANDARD 11)

add_executable(Alg_Golden_Cut main.c)
target_link_libraries(Alg_Golden_Cut quadmath)