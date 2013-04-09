#ifndef THELONIOUS_CONSTANT_MULTIPLY_H
#define THELONIOUS_CONSTANT_MULTIPLY_H

#include "thelonious/types.h"
#include "thelonious/unit.h"

namespace thelonious {
namespace operators {

template <class T, size_t N>
class ConstantMultiplyN : public T {
public:
    ConstantMultiplyN(Unit<N> &unit, Sample value): unit(&unit), value(value) {}

    void tick(Block<N> &block) {
        unit->tick(block);
        block *= value;
    }

    Unit<N> *unit;
    Sample value;
};

template <class T>
using ConstantMultiply = ConstantMultiplyN<T, 1>;

template <size_t N>
ConstantMultiplyN<Source<N>, N> operator*(Source<N> &a, Sample b) {
    return ConstantMultiplyN<Source<N>, N>(a, b);
}

template <size_t N>
ConstantMultiplyN<Source<N>, N> operator*(Source<N> &&a, Sample b) {
    return ConstantMultiplyN<Source<N>, N>(a, b);
}

template <size_t N>
ConstantMultiplyN<Source<N>, N> operator*(Sample a, Source<N> &b) {
    return ConstantMultiplyN<Source<N>, N>(b, a);
}

template <size_t N>
ConstantMultiplyN<Source<N>, N> operator*(Sample a, Source<N> &&b) {
    return ConstantMultiplyN<Source<N>, N>(b, a);
}

template <size_t N>
ConstantMultiplyN<Processor<N>, N> operator*(Processor<N> &a, Sample b) {
    return ConstantMultiplyN<Processor<N>, N>(a, b);
}

template <size_t N>
ConstantMultiplyN<Processor<N>, N> operator*(Processor<N> &&a, Sample b) {
    return ConstantMultiplyN<Processor<N>, N>(a, b);
}

template <size_t N>
ConstantMultiplyN<Processor<N>, N> operator*(Sample a, Processor<N> &b) {
    return ConstantMultiplyN<Processor<N>, N>(b, a);
}

template <size_t N>
ConstantMultiplyN<Processor<N>, N> operator*(Sample a, Processor<N> &&b) {
    return ConstantMultiplyN<Processor<N>, N>(b, a);
}


} // namespace operators
} // namespace thelonious

#endif
