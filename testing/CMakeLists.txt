cmake_minimum_required(VERSION 3.14) #cmake itself need 3.23 to support GTest::gmock. but with newer ver gtest, that's not need

find_package(GTest 
#   1.12.0...1.13.0 
  REQUIRED)
  
add_executable(
  lower_test barrier_test.cc flex_barrier_test.cc serial_executor_test.cc
             simple_thread_pool_test.cc latch_test.cc mutable_thread_test.cc)
# all should include, [[gtest] build
# failure](https://github.com/microsoft/vcpkg/issues/12105)
target_link_libraries(
  lower_test 
  GTest::gtest_main GTest::gtest GTest::gmock GTest::gmock_main
  # ${GTEST_BOTH_LIBRARIES} #this work, but not work for conan, not recommand.
  goocon)

add_executable(higher_test source_test.cc iterator_queue_test.cc
                           stream_mutex_test.cc buffer_queue_test.cc)
target_link_libraries(higher_test GTest::gtest_main GTest::gtest GTest::gmock GTest::gmock_main goocon)

add_executable(lock_free_buffer_queue_test lock_free_buffer_queue_test.cc)
target_link_libraries(lock_free_buffer_queue_test GTest::gtest_main GTest::gtest GTest::gmock GTest::gmock_main
                      goocon)

# not yet fully implement add_executable(map_reduce_test map_reduce_test.cc)
# target_link_libraries(map_reduce_test GTest::gtest_main GTest::gtest GTest::gmock GTest::gmock_main goocon )

add_executable(pipeline_test pipeline_test.cc)
target_link_libraries(pipeline_test GTest::gtest_main GTest::gtest GTest::gmock GTest::gmock_main goocon)

add_executable(queue_perf_test queue_perf_test.cc)
target_link_libraries(queue_perf_test GTest::gtest_main GTest::gtest GTest::gmock GTest::gmock_main goocon)

add_executable(scoped_guard_test scoped_guard_test.cc)
target_link_libraries(scoped_guard_test GTest::gtest_main GTest::gtest GTest::gmock GTest::gmock_main goocon)

# simple test
add_executable(counter_test counter_test.cc)
target_link_libraries(counter_test GTest::gtest_main GTest::gtest GTest::gmock GTest::gmock_main goocon)

add_executable(dynarray_test dynarray_test.cc)
target_link_libraries(dynarray_test GTest::gtest_main GTest::gtest GTest::gmock GTest::gmock_main goocon)

include(GoogleTest)
gtest_add_tests(TARGET lower_test) # gtest_discover_tests doesn't work for
                                   # crosscompile
gtest_add_tests(TARGET higher_test)
gtest_add_tests(TARGET lock_free_buffer_queue_test)
# gtest_discover_tests(map_reduce_test) #not yet accomplish
gtest_add_tests(TARGET pipeline_test)
# gtest_add_tests(TARGET queue_perf_test) #take lots of time
# gtest_discover_tests(queue_perf_test DISCOVERY_TIMEOUT  600)
gtest_add_tests(TARGET scoped_guard_test)
gtest_add_tests(TARGET counter_test)
gtest_add_tests(TARGET dynarray_test)
