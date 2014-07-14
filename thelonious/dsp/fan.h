#ifndef THELONIOUS_FAN_H
#define THELONIOUS_FAN_H

#include "thelonious/types.h"
#include "thelonious/duplex.h"

namespace thelonious {
namespace dsp {

template <size_t N>
class FanN : public Duplex<N, N> {
public:
    FanN() {}

    void tick(Block<0> &inputBlock, Block<N> &outputBlock) {
        outputBlock = this->block;
    }

    void tick(Block<N> &inputBlock, Block<0> &outputBlock) {
        this->block = inputBlock;
    }

private:
    Block<N> block;
};

typedef FanN<1> Fan;

} // namespace dsp
} // namespace thelonious

#endif
