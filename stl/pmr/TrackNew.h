#pragma once
#include <cstdio>  // printf
#include <cstdlib> // malloc/aligned_alloc
#include <iostream>
#include <new>

// XXX: useful reading about alignment:
// https://zhuanlan.zhihu.com/p/417061548

class TrackNew {
public:
  static void reset() {
    numMalloc = 0;
    sumSize = 0;
  }

  static void *allocate(std::size_t size, std::size_t align, const char *call) {
    ++numMalloc;
    sumSize += size;
    void *p;
    if (align == 0) {
      p = std::malloc(size);
    } else {
      p = std::aligned_alloc(align, size); // c++17
    }
    return p;
  }

  static void status() {
    printf("%d allocations for %zu bytes\n", numMalloc, sumSize);
  }

private:
  static inline int numMalloc = 0;
  static inline size_t sumSize = 0;
};

[[nodiscard]] void *operator new(std::size_t size) {
  return TrackNew::allocate(size, 0, "::new");
}

[[nodiscard]] void *operator new(std::size_t size, std::align_val_t align) {
  return TrackNew::allocate(size, static_cast<size_t>(align), "::new aligned");
}

[[nodiscard]] void *operator new[](std::size_t size) {
  return TrackNew::allocate(size, 0, "::new[]");
}

[[nodiscard]] void *operator new[](std::size_t size, std::align_val_t align) {
  return TrackNew::allocate(size, static_cast<size_t>(align),
                            "::new[] aligned");
}

void operator delete(void *p) noexcept { std::free(p); }

void operator delete(void *p, std::size_t) noexcept { ::operator delete(p); }

void operator delete(void *p, std::align_val_t) noexcept {
  std::free(p); // c++17
}

void operator delete(void *p, std::size_t, std::align_val_t align) noexcept {
  ::operator delete(p, align);
}
