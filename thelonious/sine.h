#ifndef THELONIOUS_SINE_H
#define THELONIOUS_SINE_H

#include <cmath>
#include <algorithm>

#include "types.h"
#include "rates.h"
#include "sizes.h"
#include "constants.h"
#include "unit.h"
#include "parameter.h"
#include "util.h"

namespace thelonious {
template <size_t N>
class SineN : public Unit<N> {
public:
    SineN(Sample frequency=440.0f, Sample phase=0.0f) :
        frequency(frequency), phase(phase) {}

    void tick(Block<N> &block) {
        Chock frequencyChock = frequency.get();
        Chock phaseChock = phase.get();

        Chock &channel = block[0];

        for (uint32_t i=0; i<BLOCK_SIZE; i++) {
            channel[i] = sin(position + phaseChock[i]);
            position += 2 * T_PI * INV_AUDIO_RATE * frequencyChock[i];
        }

        position = wrap(position, 2 * T_PI);

        auto it=block.begin() + 1;
        auto end = block.end();
        for (; it<end; it++) {
            std::copy(channel.begin(), channel.end(), (*it).begin());
        }
    }

    Parameter frequency;
    Parameter phase;
private:
    Sample position;
};

typedef SineN<1> Sine;

}

#endif
