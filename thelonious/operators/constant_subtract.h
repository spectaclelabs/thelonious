#ifndef THELONIOUS_CONSTANT_SUBTRACT_H
#define THELONIOUS_CONSTANT_SUBTRACT_H

#include "thelonious/types.h"
#include "thelonious/unit.h"

namespace thelonious {
namespace operators {

template <size_t N>
class ConstantSubtractN : public Unit<N> {
public:
    ConstantSubtractN(Unit<N> &unit, Sample value, bool inverse=false):
            unit(&unit), value(value), inverse(inverse) {}

    void tick(Block<N> &block) {
        unit->tick(block);

        if (!inverse) {
            block -= value;
        }
        else {
            block = value - block;
        }
    }

    Unit<N> *unit;
    Sample value;
    bool inverse;
};

typedef ConstantSubtractN<1> ConstantSubtract;

template <size_t N>
ConstantSubtractN<N> operator-(Unit<N> &a, Sample b) {
    return ConstantSubtractN<N>(a, b);
}

template <size_t N>
ConstantSubtractN<N> operator-(Unit<N> &&a, Sample b) {
    return ConstantSubtractN<N>(a, b);
}

template <size_t N>
ConstantSubtractN<N> operator-(Sample a, Unit<N> &b) {
    return ConstantSubtractN<N>(b, a, true);
}

template <size_t N>
ConstantSubtractN<N> operator-(Sample a, Unit<N> &&b) {
    return ConstantSubtractN<N>(b, a, true);
}

} // namespace operators
} // namespace thelonious

#endif
