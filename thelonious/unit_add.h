#ifndef THELONIOUS_UNIT_ADD_H
#define THELONIOUS_UNIT_ADD_H

#include "types.h"
#include "unit.h"

namespace thelonious {

template <size_t N>
class UnitAddN : public Unit<N> {
public:
    UnitAddN(Unit<N> &unitA, Unit<N> &unitB): unitA(&unitA), unitB(&unitB) {}

    void tick(Block<N> &block) {
        unitA->tick(block);

        Block<N> blockB;
        unitB->tick(blockB);

        block += blockB;
    }

    Unit<N> *unitA;
    Unit<N> *unitB;
};

typedef UnitAddN<1> UnitAdd;

template <size_t N>
UnitAddN<N> operator+(Unit<N> &a, Unit<N> &b) {
    return UnitAddN<N>(a, b);
}

template <size_t N>
UnitAddN<N> operator+(Unit<N> &a, Unit<N> &&b) {
    return UnitAddN<N>(a, b);
}

template <size_t N>
UnitAddN<N> operator+(Unit<N> &&a, Unit<N> &b) {
    return UnitAddN<N>(a, b);
}

template <size_t N>
UnitAddN<N> operator+(Unit<N> &&a, Unit<N> &&b) {
    return UnitAddN<N>(a, b);
}



}

#endif
