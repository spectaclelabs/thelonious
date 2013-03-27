#ifndef THELONIOUS_UNIT_MODULO_H
#define THELONIOUS_UNIT_MODULO_H

#include "thelonious/types.h"
#include "thelonious/unit.h"
#include "thelonious/util.h"

namespace thelonious {
namespace operators {

template <size_t N>
class UnitModuloN : public Unit<N> {
public:
    UnitModuloN(Unit<N> &unitA, Unit<N> &unitB): unitA(&unitA), unitB(&unitB) {}

    void tick(Block<N> &block) {
        unitA->tick(block);

        Block<N> blockB;
        unitB->tick(blockB);

        block %= blockB;
    }

    Unit<N> *unitA;
    Unit<N> *unitB;
};

typedef UnitModuloN<1> UnitModulo;

template <size_t N>
UnitModuloN<N> operator%(Unit<N> &a, Unit<N> &b) {
    return UnitModuloN<N>(a, b);
}

template <size_t N>
UnitModuloN<N> operator%(Unit<N> &a, Unit<N> &&b) {
    return UnitModuloN<N>(a, b);
}

template <size_t N>
UnitModuloN<N> operator%(Unit<N> &&a, Unit<N> &b) {
    return UnitModuloN<N>(a, b);
}

template <size_t N>
UnitModuloN<N> operator%(Unit<N> &&a, Unit<N> &&b) {
    return UnitModuloN<N>(a, b);
}

} // namespace operators
} // namespace thelonious

#endif
