#pragma once

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string_view>
#include <thread>
#include <unordered_map>

namespace traceable {

template <typename T>
class AtomicMap {
 public:
  AtomicMap(const std::string& owner_name,
            const std::chrono::milliseconds& key_expiration_period,
            const std::chrono::milliseconds& refresh_period)
      : cached_keys_(
            std::make_shared<std::unordered_map<std::string_view, T>>()),
        owner_name_(owner_name),
        key_expiration_period_(key_expiration_period),
        window_reset_thread_([this, refresh_period]() {
          std::unique_lock<std::mutex> lock(ended_mutex_);
          while (!end_thread_.wait_until(
              lock, std::chrono::steady_clock::now() + refresh_period,
              [this]() { return ended_; })) {
            RebuildCache();
            ResetGlobalCount();
          }
          std::cout << "Exiting from window reset thread of "
                    << owner_name_  << ".\n";
        }) {}

  ~AtomicMap() {
    {
      std::lock_guard<std::mutex> lock(ended_mutex_);
      ended_ = true;
    }
    end_thread_.notify_one();
    window_reset_thread_.join();
  }

  T& operator[](const std::string& key) {
    std::shared_ptr<std::unordered_map<std::string_view, T>> cached_keys =
        std::atomic_load_explicit(&cached_keys_, std::memory_order_acquire);
    typename std::unordered_map<std::string_view, T>::iterator cached_keys_it =
        cached_keys->find(key);
    if (cached_keys_it != cached_keys->end()) {
      std::cout << key + " is cached by " + owner_name_ + ".\n";
      return cached_keys_it->second;
    }
    std::cout << key + " is not cached by " + owner_name_ + ".\n";

    // not in cache, this is unseen key, we're on slower path that needs sync
    std::lock_guard<std::mutex> lock(new_keys_mutex_);
    typename std::unordered_map<std::string, T>::iterator new_keys_it =
        new_keys_.find(key);
    if (new_keys_it == new_keys_.end()) {
      new_keys_it = new_keys_.emplace(key, T()).first;
    }
    return new_keys_it->second;
  }

  T& GetGlobal() { return global_value_; }

 private:
  void RebuildCache() {
    std::chrono::time_point<std::chrono::steady_clock> current_time =
        std::chrono::steady_clock::now();

    // update last seen for keys in cache that were hit
    std::shared_ptr<std::unordered_map<std::string_view, T>> cached_keys =
        std::atomic_load_explicit(&cached_keys_, std::memory_order_acquire);
    for (auto& p : *cached_keys) {
      if (T() != p.second) {
        std::string key(p.first);
        all_keys_[key] = current_time;
      }
    }

    // delete keys older than expiration period
    for (auto it = all_keys_.begin(); it != all_keys_.end();) {
      if (current_time - it->second >= key_expiration_period_) {
        std::cout << it->first + " has expired from " + owner_name_ + " cache.\n";
        it = all_keys_.erase(it);
      } else {
        ++it;
      }
    }

    // create a new cache
    std::shared_ptr<std::unordered_map<std::string_view, T>> new_cached_keys =
        std::make_shared<std::unordered_map<std::string_view, T>>();

    // insert all currently known keys with zero values
    for (const auto& p : all_keys_) {
      new_cached_keys->emplace(p.first, T());
    }

    {
      std::lock_guard<std::mutex> lock(new_keys_mutex_);
      for (auto& p : new_keys_) {
        // steal/move string from new_keys_ as it's going to be cleared
        // soon anyway
        auto it = all_keys_.emplace(std::move(p.first), current_time).first;
        // insert its string view into cache too
        new_cached_keys->emplace(it->first, T());
      }

      // clear new_keys_ as it's been transferred to cache
      new_keys_.clear();
    }

    // swap current cache with new cache
    std::atomic_store_explicit(&cached_keys_, new_cached_keys,
                               std::memory_order_release);
  }

  void ResetGlobalCount() { global_value_ = T(); }

  const std::string owner_name_;

  T global_value_;
  // shared_ptr is accessed by request processing threads and reset thread
  // but the unordered_map is immutable, only access to shared_ptr needs
  // to be synced
  std::shared_ptr<std::unordered_map<std::string_view, T>> cached_keys_;
  // only accessed by reset thread, no sync needed.
  // keeps track of all keys seen and last seen time.
  std::unordered_map<std::string,
                     std::chrono::time_point<std::chrono::steady_clock>>
      all_keys_;
  std::chrono::milliseconds key_expiration_period_;

  // unordered_map is accessed by request processing threads and reset thread
  // need to sync with mutex
  std::mutex new_keys_mutex_;
  std::unordered_map<std::string, T> new_keys_;

  // reset thread
  std::mutex ended_mutex_;
  bool ended_;
  std::condition_variable end_thread_;
  std::thread window_reset_thread_;
};

}  // namespace traceable