cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)

find_package(gcl CONFIG REQUIRED)

add_executable(test_package test_package.cpp)
# target_link_libraries(test_package gcl::gcl) #conan defualt tweak all libs like this. (irrelevent to cmake settings)
target_link_libraries(test_package gcl::goocon)
