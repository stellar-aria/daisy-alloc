cmake_minimum_required(VERSION 3.26)
cmake_policy(SET CMP0048 NEW)

# Fetch libDaisy
include(FetchContent)
FetchContent_Declare(daisy
  GIT_REPOSITORY https://github.com/stellar-aria/libDaisy
  GIT_TAG cmake-only
)
FetchContent_MakeAvailable(daisy)

# Our project declaration

project(daisytest VERSION 0.0.1)

set(FIRMWARE_NAME daisytest)
set(FIRMWARE_SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/src/demo.cpp
)
set(FIRMWARE_DEBUG_OPT_LEVEL -O0) # (optional) to customize Debug optimization level
set(FIRMWARE_RELEASE_OPT_LEVEL -O2) # (optional) to customize Release optimization level

# DaisyProject uses FIRMWARE_NAME and FIRMWARE_SOURCES to build a target called ${FIRMWARE_NAME}
include(DaisyProject)

target_include_directories(${FIRMWARE_NAME} PUBLIC include)

FetchContent_Declare(umm_malloc
  GIT_REPOSITORY https://github.com/rhempel/umm_malloc
  GIT_TAG master
)
FetchContent_MakeAvailable(umm_malloc)

add_library(umm_malloc STATIC
  ${umm_malloc_SOURCE_DIR}/src/umm_info.c
  ${umm_malloc_SOURCE_DIR}/src/umm_integrity.c
  ${umm_malloc_SOURCE_DIR}/src/umm_malloc.c
  ${umm_malloc_SOURCE_DIR}/src/umm_poison.c
)
target_include_directories(umm_malloc PUBLIC
  ${umm_malloc_SOURCE_DIR}/src
  lib/include
)

target_link_libraries(daisytest PRIVATE umm_malloc)

