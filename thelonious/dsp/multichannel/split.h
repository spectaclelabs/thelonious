#ifndef THELONIOUS_SPLIT_H
#define THELONIOUS_SPLIT_H

#include "thelonious/types.h"
#include "thelonious/duplex.h"

namespace thelonious {
namespace dsp {
namespace multichannel {

template <size_t M, size_t N>
class SplitN : public Duplex<M, N> {
public:
    SplitN() {}

    void tickOut(Block<N> &block) {
        for (uint32_t i=0; i<N; i++) {
            if (index >= M) {
                block[i].fill(0.f);
                continue;
            }

            block[i] = storedBlock[index];
            index += 1;
        }
    }

    void tickIn(Block<M> &block) {
        storedBlock = block;
        index = 0;
    }

private:
    Block<M> storedBlock;
    uint32_t index;
};

typedef SplitN<2, 1> Split;

} // namespace multichannel
} // namespace dsp
} // namespace thelonious

#endif
