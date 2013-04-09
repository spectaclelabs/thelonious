#ifndef THELONIOUS_CONSTANT_DIVIDE_H
#define THELONIOUS_CONSTANT_DIVIDE_H

#include "thelonious/types.h"
#include "thelonious/unit.h"

namespace thelonious {
namespace operators {

template <class T, size_t N>
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

template <class T>
using ConstantDivide = ConstantDivideN<T, 1>;

template <size_t N>
ConstantDivideN<Source<N>, N> operator/(Source<N> &a, Sample b) {
    return ConstantDivideN<Source<N>, N>(a, b);
}

template <size_t N>
ConstantDivideN<Source<N>, N> operator/(Source<N> &&a, Sample b) {
    return ConstantDivideN<Source<N>, N>(a, b);
}

template <size_t N>
ConstantDivideN<Source<N>, N> operator/(Sample a, Source<N> &b) {
    return ConstantDivideN<Source<N>, N>(b, a, true);
}

template <size_t N>
ConstantDivideN<Source<N>, N> operator/(Sample a, Source<N> &&b) {
    return ConstantDivideN<Source<N>, N>(b, a, true);
}

template <size_t N>
ConstantDivideN<Processor<N>, N> operator/(Processor<N> &a, Sample b) {
    return ConstantDivideN<Processor<N>, N>(a, b);
}

template <size_t N>
ConstantDivideN<Processor<N>, N> operator/(Processor<N> &&a, Sample b) {
    return ConstantDivideN<Processor<N>, N>(a, b);
}

template <size_t N>
ConstantDivideN<Processor<N>, N> operator/(Sample a, Processor<N> &b) {
    return ConstantDivideN<Processor<N>, N>(b, a, true);
}

template <size_t N>
ConstantDivideN<Processor<N>, N> operator/(Sample a, Processor<N> &&b) {
    return ConstantDivideN<Processor<N>, N>(b, a, true);
}

} // namespace operators
} // namespace thelonious

#endif
