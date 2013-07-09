#ifndef THELONIOUS_SOURCE_H
#define THELONIOUS_SOURCE_H

#include "types.h"
#include "abstract_source.h"

namespace thelonious {

template <size_t N>
class Source : public AbstractSource<N> {
public:
    void tick(Block<0> &inputBlock, Block<N> &outputBlock) {
        tick(outputBlock);
    }

    virtual void tick(Block<N> &block) = 0;
};

} // namespace thelonious

#endif





