#ifndef THELONIOUS_SIZES_H
#define THELONIOUS_SIZES_H

#include <cstddef>

namespace thelonious {
namespace constants {

constexpr size_t BLOCK_SIZE = 128;
constexpr float INV_BLOCK_SIZE = 1.0f / BLOCK_SIZE;
constexpr size_t MAX_CHANNELS = 8;

} // namespace constants
} // namespace thelonious

#endif
