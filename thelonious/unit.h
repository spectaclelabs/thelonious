#ifndef THELONIOUS_UNIT_H
#define THELONIOUS_UNIT_H

#include <cstdint>
#include "types.h"

namespace thelonious {

// Static members
template <class Dummy>
struct UnitStatics {
    static uint32_t count;
};

template <class Dummy>
uint32_t UnitStatics<Dummy>::count = 0;


template <size_t M, size_t N>
class Unit : UnitStatics<void> {
public:
    Unit() : id(count) {
        count++;
    }
        
    virtual void tick(Block<M> &inputBlock, Block<N> &outputBlock) = 0;
    const uint32_t id;
};

} // namespace thelonious

#endif
