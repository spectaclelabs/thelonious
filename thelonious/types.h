#ifndef THELONIOUS_TYPES_H
#define THELONIOUS_TYPES_H

#include <array>
#include "sizes.h"

namespace thelonious {

typedef float Sample;

template <size_t N>
using Channel = std::array<Sample, N>;

using Chock = Channel<BLOCK_SIZE>;

template <size_t M, size_t N>
using Buffer = std::array<Channel<N>, M>;

template <size_t M>
using Block = std::array<Chock, M>;

enum Interpolation {NONE, LINEAR, CUBIC};

}

#endif
