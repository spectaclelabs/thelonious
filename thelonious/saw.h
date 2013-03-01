#ifndef THELONIOUS_SAW_H
#define THELONIOUS_SAW_H

#include <cmath>
#include <algorithm>

#include "types.h"
#include "rates.h"
#include "sizes.h"
#include "unit.h"
#include "parameter.h"
#include "util.h"

namespace thelonious {


/**
 * A non-band-limited sawtooth oscillator.
 */
template <size_t N>
class Saw : public Unit<N> {
public:
    Saw(Sample frequency=440.0f, Sample phase=0.0f) :
        frequency(frequency), phase(phase), position(0.5f), lastPhase(0.0f) {}

    /**
     * Uses an accumulator which wraps from 0 to +1, then scales to -1 to 1
     */
    void tick(Block<N> &block) {
        Chock frequencyChock = frequency.get();
        Chock phaseChock = phase.get();
        Chock &channel = block[0];

        for (uint32_t i=0; i<BLOCK_SIZE; i++) {
            Sample frequency = frequencyChock[i];

            Sample phase = phaseChock[i];
            position += phase - lastPhase;
            lastPhase = phase;

            position = wrapB(position, 1.0f);

            channel[i] = position * 2 - 1;
            position += frequency * INV_SAMPLE_RATE;
        }

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
    Sample lastPhase;
};

}

#endif
