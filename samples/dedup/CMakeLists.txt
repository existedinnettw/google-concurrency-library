cmake_minimum_required(VERSION 3.11)
set(CMAKE_C_STANDARD 99)
find_package(OpenSSL REQUIRED)
find_package(ZLIB)
#find_package(Threads) #pthread
# include_directories(${CMAKE_SOURCE_DIR}/sample/dedup)
# add_executable(binheap binheap.c)
# add_executable(decoder decoder.c)
# target_link_libraries(binheap )
add_definitions(-DENABLE_PTHREADS -DENABLE_GZIP_COMPRESSION)
add_executable(dedup dedup.c encoder.c decoder.c util.c mbuffer.c sha.c hashtable.c queue.c rabin.c tree.c binheap.c )
# find_package(Threads REQUIRED)
# target_link_libraries(dedup PUBLIC Threads::Threads)
target_link_libraries(dedup PRIVATE
        m ZLIB::ZLIB 
        OpenSSL::SSL
        OpenSSL::Crypto
	pthread
)
#target_compile_options(dedup PUBLIC "-pthread")
