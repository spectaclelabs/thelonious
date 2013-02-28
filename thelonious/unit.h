#ifndef THELONIOUS_UNIT_H
#define THELONIOUS_UNIT_H

#include "types.h"

namespace thelonious {

template <size_t N>
class Unit {
public:
    virtual void tick(Block<N> &block) = 0;

};


template<size_t N>
Block<N> operator>>(Block<N> block, Unit<N> & unit) {
    unit.tick(block);
    return block;
}

template<size_t N>
Block<N> operator>>(Unit<N> & a, Unit<N> & b) {
    Block<N> block;
    a.tick(block);
    b.tick(block);
    return block;
}

}

#endif
