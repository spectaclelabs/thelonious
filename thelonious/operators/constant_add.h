#ifndef THELONIOUS_CONSTANT_ADD_H
#define THELONIOUS_CONSTANT_ADD_H

#include "thelonious/types.h"
#include "thelonious/unit.h"

namespace thelonious {
namespace operators {

template <class T, size_t N>
class ConstantAddN : public T {
public:
    ConstantAddN(Unit<N> &unit, Sample value): unit(&unit), value(value) {}

    void tick(Block<N> &block) {
        unit->tick(block);
        block += value;
    }

    Unit<N> *unit;
    Sample value;
};

template <class T>
using ConstantAdd = ConstantAddN<T, 1>;

template <size_t N>
ConstantAddN<Source<N>, N> operator+(Source<N> &a, Sample b) {
    return ConstantAddN<Source<N>, N>(a, b);
}

template <size_t N>
ConstantAddN<Source<N>, N> operator+(Source<N> &&a, Sample b) {
    return ConstantAddN<Source<N>, N>(a, b);
}

template <size_t N>
ConstantAddN<Source<N>, N> operator+(Sample a, Source<N> &b) {
    return ConstantAddN<Source<N>, N>(b, a);
}

template <size_t N>
ConstantAddN<Source<N>, N> operator+(Sample a, Source<N> &&b) {
    return ConstantAddN<Source<N>, N>(b, a);
}

template <size_t N>
ConstantAddN<Processor<N>, N> operator+(Processor<N> &a, Sample b) {
    return ConstantAddN<Processor<N>, N>(a, b);
}

template <size_t N>
ConstantAddN<Processor<N>, N> operator+(Processor<N> &&a, Sample b) {
    return ConstantAddN<Processor<N>, N>(a, b);
}

template <size_t N>
ConstantAddN<Processor<N>, N> operator+(Sample a, Processor<N> &b) {
    return ConstantAddN<Processor<N>, N>(b, a);
}

template <size_t N>
ConstantAddN<Processor<N>, N> operator+(Sample a, Processor<N> &&b) {
    return ConstantAddN<Processor<N>, N>(b, a);
}


} // namespace operators
} // namespace thelonious

#endif
