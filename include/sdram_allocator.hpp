#pragma once
#include <cstddef>
#include <cstdint>

#include "heap.hpp"

extern heap sdram_heap;

template <typename T>
struct sdram_allocator {
  using value_type = T;
  T *allocate(std::size_t n) {
    return static_cast<T *>(sdram_heap.malloc(sizeof(T) * n));
  }
  void deallocate(T *p, std::size_t n) { sdram_heap.free(p); }

  T *allocate() { return static_cast<T *>(sdram_heap.malloc(sizeof(T))); }
  void deallocate(T *p) { sdram_heap.free(p); }
};

template <typename T, typename U>
constexpr bool operator==(const sdram_allocator<T> &,
                          const sdram_allocator<U> &) noexcept {
  return true;
}

template <typename T, typename U>
constexpr bool operator!=(const sdram_allocator<T> &,
                          const sdram_allocator<U> &) noexcept {
  return false;
}

inline void* sdram_alloc(size_t size) {
  return sdram_heap.malloc(size);
}

inline void sdram_dealloc(void* ptr) {
  sdram_heap.free(ptr);
}
