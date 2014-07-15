#ifndef THELONIOUS_PULSE_H
#define THELONIOUS_PULSE_H

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
 * A non-band-limited pulse oscillator, with a variable pulse width
 */
template <size_t N>
class PulseN : public Source<N> {
public:
    PulseN(Sample frequency=440.0f, Sample width=0.5f) :
        frequency(frequency), width(width), positionA(0.5f), 
        positionB(0.5f), lastPhase(0.0f) {}

    /**
     * Pulse is produced by subtracting two out-of-phase saw waves.  When the
     * waves are completely out of phase a square wave is formed.
     */
    void tick(Block<N> &block) {
        Chock frequencyChock = frequency.get();
        Chock widthChock = width.get();
        Chock &channel = block[0];

        for (uint32_t i=0; i<constants::BLOCK_SIZE; i++) {
            Sample frequency = frequencyChock[i];

            Sample phase = widthChock[i];
            positionB += phase - lastPhase;
            lastPhase = phase;

            positionA = wrapB(positionA, 1.0f);
            positionB = wrapB(positionB, 1.0f);

            channel[i] = (positionA - positionB);
            positionA += frequency * constants::INV_SAMPLE_RATE;
            positionB += frequency * constants::INV_SAMPLE_RATE;
        }

        auto it=block.begin() + 1;
        auto end = block.end();
        for (; it<end; it++) {
            std::copy(channel.begin(), channel.end(), (*it).begin());
        }
    }

    Parameter frequency;
    Parameter width;
private:
    Sample positionA;
    Sample positionB;
    Sample lastPhase;
};

typedef PulseN<1> Pulse;

} // namespace oscillators
} // namespace dsp
} // namespace thelonious

#endif
