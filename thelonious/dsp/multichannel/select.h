#ifndef THELONIOUS_SELECT_H
#define THELONIOUS_SELECT_H

#include "thelonious/types.h"
#include "thelonious/constants/sizes.h"
#include "thelonious/processor.h"
#include "thelonious/parameter.h"

namespace thelonious {
namespace dsp {
namespace multichannel {

template <size_t M, size_t N>
class SelectN : public Processor<M, N> {
public:
    SelectN(float channel=0): channel(channel, NONE) {}

    void tick(Block<M> &inputBlock, Block<N> &outputBlock) {
        const Chock& channelChock = channel.get();

        for (uint32_t i=0; i<constants::BLOCK_SIZE; i++) {
            uint32_t channel = channelChock[i];
            for (uint32_t j=0; j<N; j++) {
                if (channel + j >= M) {
                    outputBlock[j][i] = 0.f;
                    continue;
                }
                outputBlock[j][i] = inputBlock[channel + j][i];
            }
        }
    }

    Parameter channel;
};

typedef SelectN<2, 1> Select;

} // namespace multichannel
} // namespace dsp
} // namespace thelonious

#endif
