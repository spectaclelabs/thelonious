#ifndef THELONIOUS_UNIT_H
#define THELONIOUS_UNIT_H

#include "types.h"

namespace thelonious {

template <size_t M, size_t N>
class Unit {
public:
    virtual void tick(Block<M> &inputBlock, Block<N> &outputBlock) = 0;

};

} // namespace thelonious

#endif
