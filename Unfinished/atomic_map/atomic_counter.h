#pragma once

#include <atomic>
#include <iostream>

namespace traceable {

class AtomicCounter {
 public:
  AtomicCounter(): count(0) {}
  AtomicCounter(const AtomicCounter& rhs): count(rhs.Get()) {}
  void operator=(const AtomicCounter& rhs) { count = rhs.Get(); }
  bool operator!=(const AtomicCounter& rhs) { return count != rhs.Get(); }
  void Reset() { count = 0; }
  void Serialize() { std::cout << "count=" << count << "\n"; }
  ~AtomicCounter() {}

  int Get() const { return count; }
  void Increment() {
    count++;
  }

 private:
  std::atomic_int count;
};

}  // namespace traceable