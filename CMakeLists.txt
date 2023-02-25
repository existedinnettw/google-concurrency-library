
cmake_minimum_required(VERSION 3.11)

project(gcl VERSION 0.9.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)
add_subdirectory(samples)
add_subdirectory(testing)