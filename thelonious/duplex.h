#ifndef THELONIOUS_DUPLEX_H
#define THELONIOUS_DUPLEX_H

#include "thelonious/types.h"
#include "thelonious/abstract_source.h"
#include "thelonious/abstract_sink.h"

namespace thelonious {

template <size_t M, size_t N>
class Duplex : public AbstractSource<N>, public AbstractSink<M> {
public:
    virtual void tickIn(Block<M> &block) = 0;

    virtual void tickOut(Block<N> &block) = 0;

    void tick(Block<0> &inputBlock, Block<N> &outputBlock) {
        tickOut(outputBlock);
    };

    void tick(Block<M> &inputBlock, Block<0> &outputBlock) {
        tickIn(inputBlock);
    };
};

} // namespace thelonious

#endif
