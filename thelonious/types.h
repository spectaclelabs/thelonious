#ifndef THELONIOUS_TYPES_H
#define THELONIOUS_TYPES_H

#include <array>
#include "sizes.h"
#include "fix16.hpp"

namespace thelonious {

typedef Fix16 Sample;

template <size_t N>
using Channel = std::array<Sample, N>;

using Chock = Channel<BLOCK_SIZE>;

template <size_t M, size_t N>
using Buffer = std::array<Channel<N>, M>;

template <size_t M>
using Block = std::array<Chock, M>;

enum Interpolation {NONE, LINEAR, CUBIC};

/**
 * Move an rvalue block into an lvalue block.
 * Usage example: void tick(Block<N> block) { oscillator >> effect >> block; }
 */
template <size_t N>
void operator>>(Block<N> &&blockA, Block<N> &blockB) {
    blockB = std::move(blockA);
}
    

}

#endif
