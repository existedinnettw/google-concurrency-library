
cmake_minimum_required(VERSION 3.11)

project(gcl VERSION 0.9.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 14) #new gtest nolonger support c++11
set(CMAKE_CXX_STANDARD_REQUIRED True)

# if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
#     set (CMAKE_INSTALL_PREFIX "/usr/local" CACHE PATH "default install path" FORCE)
# endif()

add_subdirectory(src)
add_subdirectory(samples EXCLUDE_FROM_ALL)
if (NOT BUILD_TESTING STREQUAL OFF)
    enable_testing() #to let `make test` work, need to enable it here.
    add_subdirectory(testing)
endif()

include(GNUInstallDirs)
set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_INCLUDEDIR}/gcl CACHE PATH "Location of header files" )
# set(SYSCONFIG_INSTALL_DIR ${CMAKE_INSTALL_SYSCONFDIR}/gcl
#     CACHE PATH "Location of configuration files" ) #have no set file
set(INSTALL_LIBRARIES ${CMAKE_INSTALL_LIBDIR}/libgoocon.a CACHE PATH "Location of libries." )
# set(INSTALL_LIBRARIES "/usr/local/lib/libgoocon.a" CACHE PATH "Location of libries." )
#...
include(CMakePackageConfigHelpers)
configure_package_config_file(gclConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/gclConfig.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/gcl
  PATH_VARS INCLUDE_INSTALL_DIR 
#   SYSCONFIG_INSTALL_DIR
  INSTALL_LIBRARIES
)

# install(FILES "gclConfig.cmake"
#         #       "${CMAKE_CURRENT_BINARY_DIR}/gclConfigVersion.cmake"
#         DESTINATION lib/cmake/gcl)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/gclConfig.cmake
            #   ${CMAKE_CURRENT_BINARY_DIR}/FooConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/gcl )
