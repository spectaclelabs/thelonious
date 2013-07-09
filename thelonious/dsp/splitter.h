#ifndef THELONIOUS_SPLITTER_H
#define THELONIOUS_SPLITTER_H

#include "thelonious/types.h"
#include "thelonious/duplex.h"

namespace thelonious {
namespace dsp {

template <size_t N>
class SplitterN : public Duplex<N, N> {
public:
    SplitterN() {}

    void tick(Block<0> &inputBlock, Block<N> &outputBlock) {
        outputBlock = this->block;
    }

    void tick(Block<N> &inputBlock, Block<0> &outputBlock) {
        this->block = inputBlock;
    }

private:
    Block<N> block;
};

typedef SplitterN<1> Splitter;

} // namespace dsp
} // namespace thelonious

#endif
