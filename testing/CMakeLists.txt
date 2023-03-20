# [google test readme](https://github.com/google/googletest/blob/main/googletest/README.md)
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
  #DOWNLOAD_NO_EXTRACT TRUE
#   DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
#[ Fix CMake documentation to prevent GoogleTest install #3486 ](https://github.com/google/googletest/issues/3486)
option(INSTALL_GTEST "Enable installation of googletest." OFF)
#[Disable install for FetchContent](https://stackoverflow.com/questions/65527126/disable-install-for-fetchcontent)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
# FetchContent_MakeAvailable(googletest)
# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})



#[CMake testing sources from different folder](https://stackoverflow.com/questions/13797224/cmake-testing-sources-from-different-folder)
#[CMake: How to setup unit testing of a library](https://stackoverflow.com/questions/39863228/cmake-how-to-setup-unit-testing-of-a-library)

#[How to include Google Mock in CMake downloading from Github](https://stackoverflow.com/questions/72868754/how-to-include-google-mock-in-cmake-downloading-from-github)
add_executable(lower_test
        barrier_test.cc flex_barrier_test.cc serial_executor_test.cc simple_thread_pool_test.cc 
        latch_test.cc mutable_thread_test.cc
)
target_link_libraries(lower_test
        gtest_main gmock_main goocon
)

add_executable(higher_test
        source_test.cc 
        iterator_queue_test.cc 
        stream_mutex_test.cc
        buffer_queue_test.cc 
)
target_link_libraries(higher_test
        gtest_main gmock_main goocon
)

add_executable(lock_free_buffer_queue_test lock_free_buffer_queue_test.cc)
target_link_libraries(lock_free_buffer_queue_test
        gtest_main gmock_main goocon
)

# not yet fully implement
# add_executable(map_reduce_test map_reduce_test.cc)
# target_link_libraries(map_reduce_test
#         gtest_main gmock_main goocon
# )

add_executable(pipeline_test pipeline_test.cc)
target_link_libraries(pipeline_test
        gtest_main gmock_main goocon
)

add_executable(queue_perf_test queue_perf_test.cc)
target_link_libraries(queue_perf_test
        gtest_main gmock_main goocon
)

add_executable(scoped_guard_test scoped_guard_test.cc)
target_link_libraries(scoped_guard_test
        gtest_main gmock_main goocon
)

#simple test
add_executable(counter_test counter_test.cc)
target_link_libraries(counter_test
        gtest_main gmock_main goocon
)

add_executable(dynarray_test dynarray_test.cc)
target_link_libraries(dynarray_test
        gtest_main gmock_main goocon
)

include(GoogleTest)
gtest_add_tests(TARGET lower_test )  #gtest_discover_tests doesn't work for crosscompile
gtest_add_tests(TARGET higher_test)
gtest_add_tests(TARGET lock_free_buffer_queue_test)
# gtest_discover_tests(map_reduce_test) #not yet accomplish
gtest_add_tests(TARGET pipeline_test)
# gtest_add_tests(TARGET queue_perf_test) #take lots of time
# gtest_discover_tests(queue_perf_test DISCOVERY_TIMEOUT  600)
gtest_add_tests(TARGET scoped_guard_test)
gtest_add_tests(TARGET counter_test)
gtest_add_tests(TARGET dynarray_test)
