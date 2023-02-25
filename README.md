The Google Concurrency Library (GCL) is an attempt to export several
internal C++ Google concurrency libraries in a form that the C++
standard committee may accept for TR2.


cd to the directory into which you've checked out the Google
Concurrency Library, and run:

  $ make
  $ make test


`make clean` will take you back to a pristine checkout.

---
I am trying make this project use on nowaday c++ development, the original project is already archieve.
# todo
1. able to compile by gcc11
2. cmake support

# do
for `make`
1. error: dynamic exception specifications are deprecated in C++11 [-Werror=deprecated]
  * [How to replace dynamic exception specifications: throw(...)](https://stackoverflow.com/questions/54239292/how-to-replace-dynamic-exception-specifications-throw)
  * comment out `/*throw (std::invalid_argument)*/;`
1.  error: catching polymorphic type ‘class std::invalid_argument’ by value [-Werror=catch-value=]
  * [What is this? catching polymorphic type X by value [-Wcatch-value=]](https://stackoverflow.com/questions/62030341/what-is-this-catching-polymorphic-type-x-by-value-wcatch-value)
  * `} catch (std::invalid_argument expected)` --> `} catch (std::invalid_argument& expected)`
  * `} catch (std::logic_error e)` --> `} catch (std::logic_error& e)`
  * `} catch (gcl::closed_error expected) {` -->`} catch (gcl::closed_error& expected) {`
1. error: moving a local object in a return statement prevents copy elision [-Werror=pessimizing-move]
  * [C++ 函数返回局部变量的std::move()问题？](https://www.zhihu.com/question/57048704)
  * `return std::move(elem);` --> `return elem;`
1. error: ‘dummy’ may be used uninitialized [-Werror=maybe-uninitialized]
  * ['dummy' may be used uninitialized](https://stackoverflow.com/questions/69935158/dummy-may-be-used-uninitialized)
  * [gtest-death-test.cc](https://github.com/google/googletest/blob/main/googletest/src/gtest-death-test.cc)
  * will directly specify gtest version by cmake in future. currently, just pass it.
1. error: result of ‘(2 << 31)’ requires 34 bits to represent, but ‘int’ only has 32 bits [-Werror=shift-overflow=]
  * `arr[j] = (double)random() / (double)((2 << 31) - 1);` --> `arr[j] = (double)random() / (double)(((unsigned long int)2 << 31) - 1);`

for `make test`

all the error from gtest
`inlined from ‘const char* testing::internal::posix::StrNCpy(char*, const char*, size_t)’ at ../third_party/googletest/include/gtest/internal/gtest-port.h:1610:17,`
1. error: ‘char* __builtin_strncpy(char*, const char*, long unsigned int)’ output truncated before terminating nul copying as many bytes from a string as its length [-Werror=stringop-truncation]
[gtest-port-arch.h](https://github.com/google/googletest/blob/main/googletest/include/gtest/internal/gtest-port-arch.h)
1. [Teaching googletest How to Print Your Values](http://google.github.io/googletest/advanced.html#teaching-googletest-how-to-print-your-values)
1. map_reduce_test.cc, `error: ‘class gcl::queue_wrapper<gcl::buffer_queue<int> >’ has no member named ‘begin’` , mr.run(input_wrap.begin(), input_wrap.end());
1. move `counter_test.cc`, `dynarray_test.cc`, `queue_pref_test.cc` to gtest, no need main() function.