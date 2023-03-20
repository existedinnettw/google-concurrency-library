
cmake_minimum_required(VERSION 3.11)

project(gcl VERSION 0.9.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "/usr/local" CACHE PATH "default install path" FORCE)
endif()

enable_testing() #to let `make test` work, need to enable it here.

add_subdirectory(src)
add_subdirectory(samples)
add_subdirectory(testing)