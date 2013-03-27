#ifndef THELONIOUS_UNIT_MULTIPLY_H
#define THELONIOUS_UNIT_MULTIPLY_H

#include "thelonious/types.h"
#include "thelonious/unit.h"

namespace thelonious {
namespace operators {

template <size_t N>
class UnitMultiplyN : public Unit<N> {
public:
    UnitMultiplyN(Unit<N> &unitA, Unit<N> &unitB) :
        unitA(&unitA), unitB(&unitB) {}

    void tick(Block<N> &block) {
        unitA->tick(block);

        Block<N> blockB;
        unitB->tick(blockB);

        block *= blockB;
    }

    Unit<N> *unitA;
    Unit<N> *unitB;
};

typedef UnitMultiplyN<1> UnitMultiply;

template <size_t N>
UnitMultiplyN<N> operator*(Unit<N> &a, Unit<N> &b) {
    return UnitMultiplyN<N>(a, b);
}

template <size_t N>
UnitMultiplyN<N> operator*(Unit<N> &a, Unit<N> &&b) {
    return UnitMultiplyN<N>(a, b);
}

template <size_t N>
UnitMultiplyN<N> operator*(Unit<N> &&a, Unit<N> &b) {
    return UnitMultiplyN<N>(a, b);
}

template <size_t N>
UnitMultiplyN<N> operator*(Unit<N> &&a, Unit<N> &&b) {
    return UnitMultiplyN<N>(a, b);
}

} // namespace operators
} // namespace thelonious
    
#endif
