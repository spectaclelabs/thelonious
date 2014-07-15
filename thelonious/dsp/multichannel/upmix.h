#ifndef THELONIOUS_UPMIX_H
#define THELONIOUS_UPMIX_H

#include "thelonious/types.h"
#include "thelonious/constants/sizes.h"
#include "thelonious/processor.h"
#include "thelonious/parameter.h"

namespace thelonious {
namespace dsp {
namespace multichannel {

template <size_t M, size_t N>
class UpMixN: public Processor<M, N> {
public:
    void tick(Block<M> &inputBlock, Block<N> &outputBlock) {
        for (uint32_t i=0; i<N; i++) {
            outputBlock[i] = inputBlock[i % M];
        }
    }
};

typedef UpMixN<1, 2> UpMix;

} // namespace multichannel
} // namespace dsp
} // namespace thelonious

#endif
