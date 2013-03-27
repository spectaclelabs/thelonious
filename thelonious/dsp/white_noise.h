#ifndef THELONIOUS_WHITE_NOISE_H
#define THELONIOUS_WHITE_NOISE_H

#include "dizzy.h"

#include "thelonious/types.h"
#include "thelonious/unit.h"

namespace thelonious {
namespace dsp {

template <size_t N>
class WhiteNoiseN : public Unit<N> {
public:
    WhiteNoiseN() {}

    void tick(Block<N> &block) {
        auto it=block.begin();
        auto end = block.end();
        for (; it!=end; it++) {
            dizzy::random(*it, -1.0f, 1.0f);
        }
    }
};

typedef WhiteNoiseN<1> WhiteNoise;

} // namespace dsp
} // namespace thelonious

#endif
