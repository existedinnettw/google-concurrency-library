
# include_directories(${CMAKE_SOURCE_DIR}/include)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_library(goocon  
        barrier.cc countdown_latch.cc debug.cc flex_barrier.cc latch.cc 
        mutable_thread.cc serial_executor.cc simple_thread_pool.cc stream_mutex.cc
)
target_include_directories(goocon PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(goocon PRIVATE Threads::Threads)
# why flex_barrier_test.cc put in src?

# cmake install doesn't work as expect
# make shure it install header and doesn't install gtest
install( TARGETS goocon
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/gcl #this not work
)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_PREFIX}/include/gcl)
