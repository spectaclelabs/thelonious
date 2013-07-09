#ifndef THELONIOUS_SINK_H
#define THELONIOUS_SINK_H

#include "types.h"
#include "unit.h"

namespace thelonious {

template <size_t N>
class Sink : public Unit<N, 0> {
public:
    virtual void tick(Block<N> &inputBlock, Block<0> &outputBlock) {
        tick(inputBlock);
    }

    virtual void tick(Block<N> &block) = 0;
};

} // namespace thelonious

#endif




