#ifndef THELONIOUS_UNIT_MULTIPLY_H
#define THELONIOUS_UNIT_MULTIPLY_H

#include "thelonious/types.h"
#include "thelonious/unit.h"
#include "thelonious/source.h"

namespace thelonious {
namespace operators {

template <class T, size_t N>
class UnitMultiplyN : public T {
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

template <class T>
using UnitMultiply = UnitMultiplyN<T, 1>;

template <size_t N>
UnitMultiplyN<Source<N>, N> operator*(Source<N> &a, Source<N> &b) {
    return UnitMultiplyN<Source<N>, N>(a, b);
}

template <size_t N>
UnitMultiplyN<Source<N>, N> operator*(Source<N> &a, Source<N> &&b) {
    return UnitMultiplyN<Source<N>, N>(a, b);
}

template <size_t N>
UnitMultiplyN<Source<N>, N> operator*(Source<N> &&a, Source<N> &b) {
    return UnitMultiplyN<Source<N>, N>(a, b);
}

template <size_t N>
UnitMultiplyN<Source<N>, N> operator*(Source<N> &&a, Source<N> &&b) {
    return UnitMultiplyN<Source<N>, N>(a, b);
}

} // namespace operators
} // namespace thelonious
    
#endif
