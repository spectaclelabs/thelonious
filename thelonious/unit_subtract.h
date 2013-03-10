#ifndef THELONIOUS_UNIT_SUBTRACT_H
#define THELONIOUS_UNIT_SUBTRACT_H

#include "types.h"
#include "unit.h"

namespace thelonious {

template <size_t N>
class UnitSubtractN : public Unit<N> {
public:
    UnitSubtractN(Unit<N> &unitA, Unit<N> &unitB):
        unitA(&unitA), unitB(&unitB) {}

    void tick(Block<N> &block) {
        unitA->tick(block);

        Block<N> blockB;
        unitB->tick(blockB);

        block -= blockB;
    }

    Unit<N> *unitA;
    Unit<N> *unitB;
};

typedef UnitSubtractN<1> UnitSubtract;

template <size_t N>
UnitSubtractN<N> operator-(Unit<N> &a, Unit<N> &b) {
    return UnitSubtractN<N>(std::move(a), std::move(b));
}

template <size_t N>
UnitSubtractN<N> operator-(Unit<N> &a, Unit<N> &&b) {
    return UnitSubtractN<N>(std::move(a), std::move(b));
}

template <size_t N>
UnitSubtractN<N> operator-(Unit<N> &&a, Unit<N> &b) {
    return UnitSubtractN<N>(std::move(a), std::move(b));
}

template <size_t N>
UnitSubtractN<N> operator-(Unit<N> &&a, Unit<N> &&b) {
    return UnitSubtractN<N>(std::move(a), std::move(b));
}

}

#endif
