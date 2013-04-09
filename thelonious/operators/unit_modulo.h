#ifndef THELONIOUS_UNIT_MODULO_H
#define THELONIOUS_UNIT_MODULO_H

#include "thelonious/types.h"
#include "thelonious/unit.h"
#include "thelonious/source.h"
#include "thelonious/util.h"

namespace thelonious {
namespace operators {

template <class T, size_t N>
class UnitModuloN : public T {
public:
    UnitModuloN(Unit<N> &unitA, Unit<N> &unitB):
            unitA(&unitA), unitB(&unitB) {}

    void tick(Block<N> &block) {
        unitA->tick(block);

        Block<N> blockB;
        unitB->tick(blockB);

        block %= blockB;
    }

    Unit<N> *unitA;
    Unit<N> *unitB;
};

template <class T>
using UnitModulo = UnitModuloN<T, 1>;

template <size_t N>
UnitModuloN<Source<N>, N> operator%(Source<N> &a, Source<N> &b) {
    return UnitModuloN<Source<N>, N>(a, b);
}

template <size_t N>
UnitModuloN<Source<N>, N> operator%(Source<N> &a, Source<N> &&b) {
    return UnitModuloN<Source<N>, N>(a, b);
}

template <size_t N>
UnitModuloN<Source<N>, N> operator%(Source<N> &&a, Source<N> &b) {
    return UnitModuloN<Source<N>, N>(a, b);
}

template <size_t N>
UnitModuloN<Source<N>, N> operator%(Source<N> &&a, Source<N> &&b) {
    return UnitModuloN<Source<N>, N>(a, b);
}

} // namespace operators
} // namespace thelonious

#endif
