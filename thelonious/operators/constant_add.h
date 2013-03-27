#ifndef THELONIOUS_CONSTANT_ADD_H
#define THELONIOUS_CONSTANT_ADD_H

#include "thelonious/types.h"
#include "thelonious/unit.h"

namespace thelonious {
namespace operators {

template <size_t N>
class ConstantAddN : public Unit<N> {
public:
    ConstantAddN(Unit<N> &unit, Sample value): unit(&unit), value(value) {}

    void tick(Block<N> &block) {
        unit->tick(block);
        block += value;
    }

    Unit<N> *unit;
    Sample value;
};

typedef ConstantAddN<1> ConstantAdd;

template <size_t N>
ConstantAddN<N> operator+(Unit<N> &a, Sample b) {
    return ConstantAddN<N>(a, b);
}

template <size_t N>
ConstantAddN<N> operator+(Unit<N> &&a, Sample b) {
    return ConstantAddN<N>(a, b);
}

template <size_t N>
ConstantAddN<N> operator+(Sample a, Unit<N> &b) {
    return ConstantAddN<N>(b, a);
}

template <size_t N>
ConstantAddN<N> operator+(Sample a, Unit<N> &&b) {
    return ConstantAddN<N>(b, a);
}

} // namespace operators
} // namespace thelonious

#endif
