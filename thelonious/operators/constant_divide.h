#ifndef THELONIOUS_CONSTANT_DIVIDE_H
#define THELONIOUS_CONSTANT_DIVIDE_H

#include "thelonious/types.h"
#include "thelonious/unit.h"

namespace thelonious {
namespace operators {

template <size_t N>
class ConstantDivideN : public Unit<N> {
public:
    ConstantDivideN(Unit<N> &unit, Sample value, bool inverse=false):
            unit(&unit), value(value), inverse(inverse) {}

    void tick(Block<N> &block) {
        unit->tick(block);

        if (!inverse) {
            block /= value;
        }
        else {
            block = value / block;
        }
    }

    Unit<N> *unit;
    Sample value;
    bool inverse;
};

typedef ConstantDivideN<1> ConstantDivide;

template <size_t N>
ConstantDivideN<N> operator/(Unit<N> &a, Sample b) {
    return ConstantDivideN<N>(a, b);
}

template <size_t N>
ConstantDivideN<N> operator/(Unit<N> &&a, Sample b) {
    return ConstantDivideN<N>(a, b);
}

template <size_t N>
ConstantDivideN<N> operator/(Sample a, Unit<N> &b) {
    return ConstantDivideN<N>(b, a, true);
}

template <size_t N>
ConstantDivideN<N> operator/(Sample a, Unit<N> &&b) {
    return ConstantDivideN<N>(b, a, true);
}

} // namespace operators
} // namespace thelonious

#endif
