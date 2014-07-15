#ifndef THELONIOUS_SINE_H
#define THELONIOUS_SINE_H

#include <cmath>
#include <algorithm>

#include "thelonious/types.h"
#include "thelonious/source.h"
#include "thelonious/parameter.h"
#include "thelonious/util.h"
#include "thelonious/constants/rates.h"
#include "thelonious/constants/sizes.h"
#include "thelonious/constants/math.h"

namespace thelonious {
namespace dsp {
namespace oscillators {

template <size_t N>
class SineN : public Source<N> {
public:
    SineN(Sample frequency=440.0f, Sample phase=0.0f) :
        frequency(frequency), phase(phase) {}

    void tick(Block<N> &block) {
        Chock frequencyChock = frequency.get();
        Chock phaseChock = phase.get();

        Chock &channel = block[0];

        for (uint32_t i=0; i<constants::BLOCK_SIZE; i++) {
            channel[i] = std::sin(position + phaseChock[i]);
            position += constants::TWO_PI * constants::INV_AUDIO_RATE *
                        frequencyChock[i];
        }

        position = wrap(position, constants::TWO_PI);

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
};

typedef SineN<1> Sine;

} // namespace oscillators
} // namespace dsp
} // namespace thelonious

#endif
