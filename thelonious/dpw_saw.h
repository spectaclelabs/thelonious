#ifndef THELONIOUS_DPW_SAW_H
#define THELONIOUS_DPW_SAW_H

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
 * An alias-reduced sawtooth oscillator.
 */
template <size_t N>
class DPWSaw : public Unit<N> {
public:
    DPWSaw(Sample frequency=440.0f, Sample phase=0.0f) :
        frequency(frequency), phase(phase), position(0.5f), lastValue(0.0f),
        lastFrequency(0.0f), lastPhase(0.0f), scaleFactor(0.0f) {}

    /**
     * A differentiated parabolic wave oscillator.  Takes a simple sawtooth
     * wave, squares it to create a parabolic wave, and differentiates it to
     * convert back to a saw.  This is then scaled proportional frequency
     * of the oscillator.
     */
    void tick(Block<N> &block) {
        Chock frequencyChock = frequency.get();
        Chock phaseChock = phase.get();
        Chock &channel = block[0];

        for (uint32_t i=0; i<BLOCK_SIZE; i++) {
            Sample frequency = frequencyChock[i];
            if (frequency != lastFrequency) {
                scaleFactor = SAMPLE_RATE / (4.0f * frequency);
                lastFrequency = frequency;
            }

            Sample phase = phaseChock[i];
            position += phase - lastPhase;
            lastPhase = phase;

            position = wrapB(position, 1.0f);

            Sample value = position * 2 - 1;
            value = value * value;
            channel[i] = (value - lastValue) * scaleFactor;
            lastValue = value;

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
    Sample lastValue;
    Sample lastFrequency;
    Sample lastPhase;
    Sample scaleFactor;
};

}

#endif
