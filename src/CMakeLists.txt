cmake_minimum_required(VERSION 3.23)

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
find_package(Threads REQUIRED)

add_library(
  goocon
  barrier.cc
  countdown_latch.cc
  debug.cc
  flex_barrier.cc
  latch.cc
  mutable_thread.cc
  serial_executor.cc
  simple_thread_pool.cc
  stream_mutex.cc)
target_include_directories(goocon PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>  
        $<INSTALL_INTERFACE:include/gcl>  # <prefix>/include/gcl
)
target_link_libraries(goocon Threads::Threads)

# include(GNUInstallDirs)
# set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_INCLUDEDIR}/gcl CACHE PATH "Location of header files" )
set(INCLUDE_DIRS include/gcl CACHE PATH "Location of header files" )
# set(INSTALL_LIBRARIES ${CMAKE_INSTALL_LIBDIR}/libgoocon.a CACHE PATH "Location of libries." )
# set(LIBRARIES lib/goocon CACHE PATH "Location of libraries." ) #this not work.
set(LIB_DIR lib CACHE PATH "Location to place libraries.")

#==================create target file xxxTarget.cmake======================
# cmake install doesn't work as expect make shure it install header and doesn't
# install gtest
install(
  TARGETS goocon
  EXPORT gclTargets
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
#   PUBLIC_HEADER DESTINATION include #not yet set_target_property, I don't like glob
)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION
${CMAKE_INSTALL_PREFIX}/include/gcl) #prefer way to install header.

install(
  EXPORT gclTargets
  FILE gclTargets.cmake
  NAMESPACE gcl::
  DESTINATION lib/cmake/gcl)

