#ifndef THELONIOUS_WHITE_NOISE_H
#define THELONIOUS_WHITE_NOISE_H

#include "dizzy.h"

#include "types.h"
#include "unit.h"

namespace thelonious {

template <size_t N>
class WhiteNoise : public Unit<N> {
public:
    WhiteNoise() {}

    void tick(Block<N> &block) {
        auto it=block.begin();
        auto end = block.end();
        for (; it!=end; it++) {
            dizzy::random(*it, -1.0f, 1.0f);
        }
    }
};

}

#endif