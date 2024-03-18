#include <daisy_seed.h>

#include <array>
#include <memory>
#include <vector>
#include "sdram_allocator.hpp"

daisy::DaisySeed hardware;

constexpr uint32_t sdram_address = 0xC0000000;  // 0x60000000; //
constexpr uint32_t sdram_size = 0x3FFFFFF;      // 64 * 1024 * 1024; // 64MiB
heap sdram_heap{(void*)sdram_address, sdram_size};

int main(void) {
  hardware.Init();
  sdram_heap.Init();

  bool led_state = true;
  while (true) {
    std::vector<int, sdram_allocator<int>> vector_on_sdram{};

    // unique_ptr with custom destructor ()
    using array_type = std::array<int, 20>;
    std::unique_ptr<array_type, void (*)(void*)> uniq_ptr_array_on_sdram(
        sdram_allocator<array_type>{}.allocate(), &sdram_dealloc);

    // probably the most correct way to do things
    std::unique_ptr<array_type, void (*)(array_type*)>
        alt_uniq_ptr_array_on_sdram(
            sdram_allocator<array_type>{}.allocate(), [](array_type* arr) {
              sdram_allocator<array_type>{}.deallocate(arr);
            });

    // Placement new example. Not recommended! (split destructor and free hard
    // to track)
    void* array_on_sdram_mem = sdram_heap.malloc(sizeof(array_type));
    array_type* alt_array_on_sdram = new (array_on_sdram_mem) array_type;
    alt_array_on_sdram->~array_type();
    sdram_heap.free(array_on_sdram_mem);

    hardware.SetLed(led_state);
    led_state = !led_state;

    daisy::System::Delay(500);
  }
}
