
# include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/ThreadSanitizer)

add_library(goocon STATIC 
        barrier.cc countdown_latch.cc debug.cc flex_barrier.cc latch.cc 
        mutable_thread.cc serial_executor.cc simple_thread_pool.cc stream_mutex.cc
)
target_include_directories(goocon PUBLIC ${CMAKE_SOURCE_DIR}/include)
# why flex_barrier_test.cc put in src?
