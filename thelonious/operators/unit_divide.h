#ifndef THELONIOUS_UNIT_DIVIDE_H
#define THELONIOUS_UNIT_DIVIDE_H

#include "thelonious/types.h"
#include "thelonious/unit.h"
#include "thelonious/source.h"

namespace thelonious {
namespace operators {

template <class T, size_t N>
class UnitDivideN : public T {
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

template <class T>
using UnitDivide = UnitDivideN<T, 1>;

template <size_t N>
UnitDivideN<Source<N>, N> operator/(Source<N> &a, Source<N> &b) {
    return UnitDivideN<Source<N>, N>(a, b);
}

template <size_t N>
UnitDivideN<Source<N>, N> operator/(Source<N> &a, Source<N> &&b) {
    return UnitDivideN<Source<N>, N>(a, b);
}

template <size_t N>
UnitDivideN<Source<N>, N> operator/(Source<N> &&a, Source<N> &b) {
    return UnitDivideN<Source<N>, N>(a, b);
}

template <size_t N>
UnitDivideN<Source<N>, N> operator/(Source<N> &&a, Source<N> &&b) {
    return UnitDivideN<Source<N>, N>(a, b);
}

} // namespace operators
} // namespace thelonious

#endif
