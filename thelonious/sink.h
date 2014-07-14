#ifndef THELONIOUS_SINK_H
#define THELONIOUS_SINK_H

#include "types.h"
#include "abstract_sink.h"

namespace thelonious {

template <size_t N>
class Sink : public AbstractSink<N> {
public:
    void tick(Block<N> &inputBlock, Block<0> &outputBlock) {
        tick(inputBlock);
    }

    virtual void tick(Block<N> &block) = 0;
};

} // namespace thelonious

#endif




