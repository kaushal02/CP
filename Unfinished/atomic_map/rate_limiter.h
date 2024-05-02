#pragma once

#include <chrono>

#include "atomic_counter.h"
#include "atomic_map.h"

namespace traceable {

// Rate limiter that rate limits based on how many times a key has been seen
// and how many total count of all keys have been seen in period.
class RateLimiter {
 public:
  RateLimiter(int64_t max_count_per_endpoint, int64_t max_count_global,
              const std::chrono::milliseconds& refresh_period,
              const std::chrono::milliseconds& key_expiration_period)
      : max_count_per_sample_bucket_(max_count_per_endpoint),
        max_count_global_(max_count_global),
        counts_("rate limiter", key_expiration_period, refresh_period)
        {}

  ~RateLimiter() {}
  bool Allow(const std::string& key);

 private:
  typedef AtomicCounter value_t;
  bool UpdateBucketCount(const std::string& key, value_t& counter);

  const int64_t max_count_per_sample_bucket_;
  const int64_t max_count_global_;
  AtomicMap<value_t> counts_;
};

bool RateLimiter::Allow(const std::string& key) {
  // check total count first as it's cheap
  value_t global_counter = counts_.GetGlobal();
  if (global_counter.Get() >= max_count_global_) {
    std::cout << key + " not sampled as total number of samples has "
              << "exceeded max in time window.\n";
    return false;
  }

  // may go over a bit if several threads get here but it's ok, trading off
  // accuracy over speed
  global_counter.Increment();

  // if key is empty, we cannot rate limit by bucket
  if (key.empty()) {
    return true;
  }

  value_t counter = counts_[key];
  return UpdateBucketCount(key, counter);
}

bool RateLimiter::UpdateBucketCount(const std::string& key, value_t& counter) {
  if (counter.Get() >= max_count_per_sample_bucket_) {
    std::cout << key + " not sampled as it has been seen "
              << "max number of times in time window.\n";
    return false;
  }
  counter.Increment();
  return true;
}

}  // namespace traceable
