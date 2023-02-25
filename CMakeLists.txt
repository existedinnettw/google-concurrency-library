project(gcl LANGUAGES CXX)
cmake_minimum_required(VERSION 3.11)


set (CMAKE_CXX_STANDARD 11)

add_subdirectory(src)
add_subdirectory(testing)