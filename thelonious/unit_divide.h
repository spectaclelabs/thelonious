#ifndef THELONIOUS_UNIT_DIVIDE_H
#define THELONIOUS_UNIT_DIVIDE_H

#include "types.h"
#include "unit.h"

namespace thelonious {

template <size_t N>
class UnitDivideN : public Unit<N> {
public:
    UnitDivideN(Unit<N> &unitA, Unit<N> &unitB) :
        unitA(&unitA), unitB(&unitB) {}

    void tick(Block<N> &block) {
        unitA->tick(block);

        Block<N> blockB;
        unitB->tick(blockB);

        block /= blockB;
    }

    Unit<N> *unitA;
    Unit<N> *unitB;
};

typedef UnitDivideN<1> UnitDivide;

template <size_t N>
UnitDivideN<N> operator/(Unit<N> &a, Unit<N> &b) {
    return UnitDivideN<N>(a, b);
}

template <size_t N>
UnitDivideN<N> operator/(Unit<N> &a, Unit<N> &&b) {
    return UnitDivideN<N>(a, b);
}

template <size_t N>
UnitDivideN<N> operator/(Unit<N> &&a, Unit<N> &b) {
    return UnitDivideN<N>(a, b);
}

template <size_t N>
UnitDivideN<N> operator/(Unit<N> &&a, Unit<N> &&b) {
    return UnitDivideN<N>(a, b);
}

}

#endif
