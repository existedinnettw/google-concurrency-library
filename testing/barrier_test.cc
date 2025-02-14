// Copyright 2010 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// This file is a test of the barrier class

#include <algorithm>
#include <string>

#include <atomic>
#include <thread>

#include "gmock/gmock.h"

#include "barrier.h"

using testing::_;

using gcl::barrier;

// TODO(alasdair): Update kNumCycles when the potential deadlock in
// arrive_and_drop has been fixed.
static int kNumCycles = 1;
static int kNumThreads = 5;
static int kInvalidCount = -1;

class BarrierTest : public testing::Test {
};

// Verifies that we cannot create a barrier with an illegal number of
// threads.
TEST_F(BarrierTest, InvalidConstructorArg) {
  try {
    barrier b(kInvalidCount);
    FAIL();
  } catch (std::invalid_argument& expected) {
  }
}

static void WaitForBarrier(barrier* b, int n_cycles) {
  for (int i = 0; i < n_cycles; ++i) {
    b->arrive_and_wait();
  }
}

static void Drop(barrier* b) {
  b->arrive_and_drop();
}

TEST_F(BarrierTest, ArriveAndWait) {
  barrier b(kNumThreads);
  std::thread* threads[kNumThreads];
  for (int i = 0; i < kNumThreads; i++) {
    threads[i] = new std::thread(std::bind(WaitForBarrier, &b, 1));
  }
  for (int i = 0; i < kNumThreads; i++) {
    threads[i]->join();
  }
  for (int i = 0; i < kNumThreads; i++) {
    delete threads[i];
  }
}

TEST_F(BarrierTest, ArriveAndWaitMultipleCycles) {
  barrier b(kNumThreads);
  std::thread* threads[kNumThreads];
  for (int i = 0; i < kNumThreads; i++) {
    threads[i] = new std::thread(std::bind(WaitForBarrier, &b, kNumCycles));
  }
  for (int i = 0; i < kNumThreads; i++) {
    threads[i]->join();
  }
  for (int i = 0; i < kNumThreads; i++) {
    delete threads[i];
  }
}

TEST_F(BarrierTest, ArriveAndDrop) {
  barrier b(kNumThreads);
  std::thread* threads[kNumThreads];
  for (int i = 0; i < kNumThreads; i++) {
    if (i % 2 == 0) {
      threads[i] = new std::thread(std::bind(WaitForBarrier, &b, kNumCycles));
    } else {
      threads[i] = new std::thread(std::bind(Drop, &b));
    }
  }
  for (int i = 0; i < kNumThreads; i++) {
    threads[i]->join();
  }
  for (int i = 0; i < kNumThreads; i++) {
    delete threads[i];
  }
}
