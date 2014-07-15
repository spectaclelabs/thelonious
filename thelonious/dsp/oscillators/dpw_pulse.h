#ifndef THELONIOUS_DPW_PULSE_H
#define THELONIOUS_DPW_PULSE_H

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
 * An alias-reduced pulse wave oscillator.
 */
template <size_t N>
class DPWPulseN : public Source<N> {
public:
    DPWPulseN(Sample frequency=440.0f, Sample width=0.5f) :
        frequency(frequency), width(width), positionA(0.5f), positionB(0.5f),
        lastValueA(0.0f), lastValueB(0.0f), lastFrequency(0.0f),
        lastPhase(0.0f), scaleFactor(0.0f) {}

    /**
     * Waveform is produced by subtracting two phase shifted DPW sawtooths.
     */
    void tick(Block<N> &block) {
        Chock frequencyChock = frequency.get();
        Chock widthChock = width.get();
        Chock &channel = block[0];

        for (uint32_t i=0; i<constants::BLOCK_SIZE; i++) {
            Sample frequency = frequencyChock[i];
            if (frequency != lastFrequency) {
                scaleFactor = 0.5f * constants::SAMPLE_RATE /
                              (4.0f * frequency);
                lastFrequency = frequency;
            }

            Sample phase = widthChock[i];
            positionB += phase - lastPhase;
            lastPhase = phase;

            positionA = wrapB(positionA, 1.0f);
            positionB = wrapB(positionB, 1.0f);

            Sample valueA = positionA * 2.0f - 1.0f;
            Sample valueB = positionB * 2.0f - 1.0f;
            valueA = valueA * valueA;
            valueB = valueB * valueB;
            channel[i] = ((valueA - lastValueA) -
                          (valueB - lastValueB)) * scaleFactor;
            lastValueA = valueA;
            lastValueB = valueB;

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
    Sample lastValueA;
    Sample lastValueB;
    Sample lastFrequency;
    Sample lastPhase;
    Sample scaleFactor;
};

typedef DPWPulseN<1> DPWPulse;

} // namespace oscillators
} // namespace dsp
} // namespace thelonious

#endif
