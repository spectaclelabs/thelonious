#ifndef THELONIOUS_PROCESSOR_H
#define THELONIOUS_PROCESSOR_H

#include "types.h"
#include "unit.h"

namespace thelonious {

template <size_t M, size_t N>
class Processor : public Unit<M, N> {
};

} // namespace thelonious

#endif

