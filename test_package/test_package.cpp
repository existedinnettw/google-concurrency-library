#include "gcl/buffer_queue.h"
#include "gcl/countdown_latch.h"
#include "gcl/pipeline.h"
#include "gcl/source.h"
using namespace gcl;
int main() {
    simple_thread_pool pool;
    queue_object<buffer_queue<double>> queue(10);
    printf("gcl package create::test_package::success. \n");
}