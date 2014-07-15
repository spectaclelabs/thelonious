#ifndef THELONIOUS_SILENCE_H
#define THELONIOUS_SILENCE_H

#include "thelonious/types.h"
#include "thelonious/source.h"
#include "thelonious/constants/sizes.h"

namespace thelonious {
namespace dsp {
namespace oscillators {

template <size_t N>
class SilenceN : public Source<N> {
public:
    void tick(Block<N> &block) {
        for (uint32_t i=0; i<constants::BLOCK_SIZE; i++) {
            block[i].fill(0);
        }
    }
};

typedef SilenceN<1> Silence;

} // namespace oscillators
} // namespace dsp
} // namespace thelonious

#endif
