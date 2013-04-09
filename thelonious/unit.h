#ifndef THELONIOUS_UNIT_H
#define THELONIOUS_UNIT_H

#include "types.h"

namespace thelonious {

template <size_t N>
class Unit {
public:
    virtual void tick(Block<N> &block) = 0;

};

} // namespace thelonious

#endif
