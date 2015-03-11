// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "content/common/discardable_shared_memory_heap.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>

#include "base/bind.h"
#include "base/callback_helpers.h"
#include "base/memory/discardable_shared_memory.h"
#include "base/memory/scoped_vector.h"
#include "base/process/process_metrics.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "testing/perf/perf_test.h"

namespace content {
namespace {

const int kTimeLimitMs = 2000;
const int kTimeCheckInterval = 8192;

TEST(DiscardableSharedMemoryHeapTest, SearchFreeLists) {
  size_t block_size = base::GetPageSize();
  DiscardableSharedMemoryHeap heap(block_size);

  const size_t kBlocks = 4096;
  const size_t kSegments = 16;
  size_t segment_size = block_size * kBlocks;

  for (size_t i = 0; i < kSegments; ++i) {
    scoped_ptr<base::DiscardableSharedMemory> memory(
        new base::DiscardableSharedMemory);
    ASSERT_TRUE(memory->CreateAndMap(segment_size));
    heap.MergeIntoFreeLists(heap.Grow(memory.Pass(), segment_size).Pass());
  }

  unsigned kSeed = 1;
  // Use kSeed as seed for random number generator.
  srand(kSeed);

  // Pre-compute random values.
  int random_span[kTimeCheckInterval];
  size_t random_blocks[kTimeCheckInterval];
  for (int i = 0; i < kTimeCheckInterval; ++i) {
    random_span[i] = std::rand();
    // Exponentially distributed block size.
    const double kLambda = 2.0;
    double v = static_cast<double>(std::rand()) / RAND_MAX;
    random_blocks[i] = 1 + log(1.0 - v) / -kLambda * kBlocks;
  }

  ScopedVector<base::ScopedClosureRunner> spans;

  base::TimeTicks start = base::TimeTicks::Now();
  base::TimeTicks end = start + base::TimeDelta::FromMilliseconds(kTimeLimitMs);
  base::TimeDelta accumulator;
  int count = 0;
  while (start < end) {
    for (int i = 0; i < kTimeCheckInterval; ++i) {
      // Search for a perfect fit if greater than kBlocks.
      size_t slack =
          random_blocks[i] < kBlocks ? kBlocks - random_blocks[i] : 0;
      scoped_ptr<DiscardableSharedMemoryHeap::Span> span =
          heap.SearchFreeLists(random_blocks[i], slack);
      if (span) {
        spans.push_back(new base::ScopedClosureRunner(
            base::Bind(&DiscardableSharedMemoryHeap::MergeIntoFreeLists,
                       base::Unretained(&heap), base::Passed(&span))));
      } else if (!spans.empty()) {
        // Merge a random span back into the free list.
        std::swap(spans[random_span[i] % spans.size()], spans.back());
        spans.pop_back();
      }

      ++count;
    }

    base::TimeTicks now = base::TimeTicks::Now();
    accumulator += now - start;
    start = now;
  }

  spans.clear();

  perf_test::PrintResult("search_free_list", "", "",
                         count / accumulator.InSecondsF(), "runs/s", true);
}

}  // namespace
}  // namespace content
