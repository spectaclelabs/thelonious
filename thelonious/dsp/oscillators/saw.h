#ifndef THELONIOUS_SAW_H
#define THELONIOUS_SAW_H

#include <algorithm>

#include "thelonious/types.h"
#include "thelonious/source.h"
#include "thelonious/parameter.h"
#include "thelonious/util.h"
#include "thelonious/constants/rates.h"
#include "thelonious/constants/sizes.h"

namespace thelonious {
namespace dsp {
namespace oscillators {

/**
 * A non-band-limited sawtooth oscillator.
 */
template <size_t N>
class SawN : public Source<N> {
public:
    SawN(Sample frequency=440.0f, Sample phase=0.0f) :
        frequency(frequency), phase(phase), position(0.5f), lastPhase(0.0f) {}

    /**
     * Uses an accumulator which wraps from 0 to +1, then scales to -1 to 1
     */
    void tick(Block<N> &block) {
        Chock frequencyChock = frequency.get();
        Chock phaseChock = phase.get();
        Chock &channel = block[0];

        for (uint32_t i=0; i<constants::BLOCK_SIZE; i++) {
            Sample frequency = frequencyChock[i];

            Sample phase = phaseChock[i];
            position += phase - lastPhase;
            lastPhase = phase;

            position = wrapB(position, 1.0f);

            channel[i] = position * 2.0f - 1.0f;
            position += frequency * constants::INV_SAMPLE_RATE;
        }

        auto it=block.begin() + 1u;
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

typedef SawN<1> Saw;

} // namespace oscillators
} // namespace dsp
} // namespace thelonious

#endif
