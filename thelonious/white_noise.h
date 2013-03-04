#ifndef THELONIOUS_WHITE_NOISE_H
#define THELONIOUS_WHITE_NOISE_H

#include "dizzy.h"

#include "types.h"
#include "unit.h"

namespace thelonious {

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

}

#endif
