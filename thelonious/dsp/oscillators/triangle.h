#ifndef THELONIOUS_TRIANGLE_H
#define THELONIOUS_TRIANGLE_H

#include <cmath>
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
 * A non-band-limited triangle wave oscillator.
 */
template <size_t N>
class TriangleN : public Source<N> {
public:
    TriangleN(Sample frequency=440.0f, Sample phase=0.0f) :
        frequency(frequency), phase(phase), position(0.0f), lastPhase(0.0f) {}
    
    /**
     * Triangle wave created by taking the abs value of a sawtooth wave,
     * and scaling and shifting the output.
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

            channel[i] = std::abs(position - 0.5) * 4 - 1;
            position += frequency * constants::INV_SAMPLE_RATE;
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

typedef TriangleN<1> Triangle;

} // namespace oscillators
} // namespace dsp
} // namespace thelonious

#endif
