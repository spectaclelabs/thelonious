#ifndef THELONIOUS_MULTISELECT_H
#define THELONIOUS_MULTISELECT_H

#include "thelonious/types.h"
#include "thelonious/constants/sizes.h"
#include "thelonious/processor.h"
#include "thelonious/parameter.h"

namespace thelonious {
namespace dsp {
namespace multichannel {

template <size_t M, size_t N>
class MultiSelectN : public Processor<M, N> {
public:
    MultiSelectN() {
        for (uint32_t i=0; i<N; i++) {
            channels[i].set(i);
            channels[i].setInterpolation(NONE);
        }
    }

    MultiSelectN(std::array<Parameter, N> channels): channels(channels) {
        for (uint32_t i=0; i<N; i++) {
            channels[i].setInterpolation(NONE);
        }
    }

    void tick(Block<M> &inputBlock, Block<N> &outputBlock) {
        for (uint32_t i=0; i<N; i++) {
            const Chock& channelChock = channels[i].get();
            for (uint32_t j=0; j<constants::BLOCK_SIZE; j++) {
                uint32_t channel = channelChock[j];
                if (channel >= M) {
                    outputBlock[i][j] = 0.f;
                    continue;
                }
                outputBlock[i][j] = inputBlock[channel][j];
            }
        }
    }

    std::array<Parameter, N> channels;
};

typedef MultiSelectN<2, 1> MultiSelect;

} // namespace multichannel
} // namespace dsp
} // namespace thelonious

#endif
