#ifndef THELONIOUS_DOWNMIX_H
#define THELONIOUS_DOWNMIX_H

#include "thelonious/types.h"
#include "thelonious/constants/sizes.h"
#include "thelonious/processor.h"
#include "thelonious/parameter.h"
#include "thelonious/dsl/channel.h"

namespace thelonious {
namespace dsp {
namespace multichannel {

template <size_t M, size_t N>
class DownMixN: public Processor<M, N> {
public:
    void tick(Block<M> &inputBlock, Block<N> &outputBlock) {
        for (uint32_t i=0; i<M; i++) {
            if (i < N) {
                outputBlock[i] = inputBlock[i];
            }
            else {
                outputBlock[i % N] += inputBlock[i];
            }
        }
    }
};

typedef DownMixN<2, 1> DownMix;

} // namespace multichannel
} // namespace dsp
} // namespace thelonious

#endif
