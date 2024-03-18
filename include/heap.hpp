#pragma once
#include <cstddef>
#include <cstdint>

#include "umm_malloc.h"

class heap {
 public:
  heap(void* address, size_t size) : address_(address), size_(size){}
  void Init() { umm_multi_init_heap(&heap_, address_, size_); }

  void* malloc(size_t size) { return umm_multi_malloc(&heap_, size); }
  void* calloc(size_t num, size_t size) { return umm_multi_calloc(&heap_, num, size); }
  void* realloc(void *ptr, size_t size) { return umm_multi_realloc(&heap_, ptr, size); }
  void free(void *ptr) { umm_multi_free(&heap_, ptr); }

 private:
  umm_heap heap_{};
  void* address_;
  size_t size_;
};

