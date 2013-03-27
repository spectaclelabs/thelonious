#ifndef THELONIOUS_CONSTANT_MULTIPLY_H
#define THELONIOUS_CONSTANT_MULTIPLY_H

#include "thelonious/types.h"
#include "thelonious/unit.h"

namespace thelonious {
namespace operators {

template <size_t N>
class ConstantMultiplyN : public Unit<N> {
public:
    ConstantMultiplyN(Unit<N> &unit, Sample value): unit(&unit), value(value) {}

    void tick(Block<N> &block) {
        unit->tick(block);
        block *= value;
    }

    Unit<N> *unit;
    Sample value;
};

typedef ConstantMultiplyN<1> ConstantMultiply;

template <size_t N>
ConstantMultiplyN<N> operator*(Unit<N> &a, Sample b) {
    return ConstantMultiplyN<N>(a, b);
}

template <size_t N>
ConstantMultiplyN<N> operator*(Unit<N> &&a, Sample b) {
    return ConstantMultiplyN<N>(a, b);
}

template <size_t N>
ConstantMultiplyN<N> operator*(Sample a, Unit<N> &b) {
    return ConstantMultiplyN<N>(b, a);
}

template <size_t N>
ConstantMultiplyN<N> operator*(Sample a, Unit<N> &&b) {
    return ConstantMultiplyN<N>(b, a);
}

} // namespace operators
} // namespace thelonious

#endif
