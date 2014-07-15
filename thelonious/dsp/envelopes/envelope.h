#ifndef THELONIOUS_ENVELOPE_H
#define THELONIOUS_ENVELOPE_H

#include <initializer_list>
#include <vector>
#include <algorithm>

#include "thelonious/types.h"
#include "thelonious/source.h"
#include "thelonious/parameter.h"
#include "thelonious/util.h"
#include "thelonious/constants/sizes.h"
#include "thelonious/constants/rates.h"

namespace thelonious {
namespace dsp {
namespace envelopes {

class EnvelopeSegment {
public:
    virtual Sample get(Sample startValue, Sample endValue, Sample position) {
        // Default to linear segments
        return linearInterpolate(startValue, endValue, position);
    }
};

// typedef allows us to create LinearSegments semantically
typedef EnvelopeSegment LinearSegment;

template <size_t N>
class EnvelopeN : public Source<N> {
public:
    EnvelopeN(Sample initialValue,
             std::vector<Sample> values,
             std::vector<Sample> durations, int releaseNode=-1) :
            gate(0.0f, NONE), values(values), durations(durations),
            segments(values.size()), releaseNode(releaseNode),
            value(initialValue), time(0.0f), segmentIndex(0u), playing(false),
            sustaining(false), canTrigger(true) {
    }

    void tick(Block<N> &block) {
        Chock gateChock = gate.get();
        for (uint32_t i=0; i<constants::BLOCK_SIZE; i++) {
            if (gateChock[i] && canTrigger) {
                firstSegment();
                playing = true;
                canTrigger = false;
            }

            if (!gateChock[i]) {
                sustaining = false;
                canTrigger = true;
            }

            while (playing && !sustaining && time >= duration) {
                if (duration == 0) {
                    value = segments[segmentIndex].get(startValue, endValue,
                                                       1.f);
                }

                nextSegment();
            }

            if (playing) {
                if (sustaining) {
                    // Don't increase the time when sustaining - it will just
                    // wait for the next segment
                    value = startValue;
                }
                else {
                    value = segments[segmentIndex].get(startValue, endValue,
                                                       time * invDuration);
                    time += constants::INV_SAMPLE_RATE;
                }
            }

            block[0][i] = value;
        }
    }

    Parameter gate;
    std::function<void()> onComplete;

private:
    void setSegmentVariables() {
        duration = durations[segmentIndex];
        invDuration = 1.0f / duration;
        startValue = value;
        endValue = values[segmentIndex];
    }

    void firstSegment() {
        segmentIndex = 0;
        setSegmentVariables();
        time = 0;
    }

    void nextSegment() {
        segmentIndex++;


        if (segmentIndex == segments.size()) {
            // We have reached the end of the last segment, so stop playing
            playing = false;
            if (onComplete) {
                onComplete();
            }
        }
        else {
            // Rather than set time = 0, we subtract the duration.  This means
            // that we can deal with changes falling on a sub-sample without
            // losing synchronization
            time -= duration;
            setSegmentVariables();

            if (segmentIndex == (uint32_t) releaseNode + 1) {
                // We have hit the sustain point, so start sustaining
                sustaining = true;
                // When we stop sustaining we don't need to correct for
                // sub-sample durations, so set time to zero
                time = 0;
            }

        }
    }

    std::vector<Sample> values;
    std::vector<Sample> durations;
    std::vector<EnvelopeSegment> segments;

    int releaseNode;

    Sample value;
    Sample time;

    Sample duration;
    Sample invDuration;
    Sample startValue;
    Sample endValue;

    uint32_t segmentIndex;
    bool playing;
    bool sustaining;
    bool canTrigger;
};

typedef EnvelopeN<1> Envelope;

} // namespace envelopes
} // namespace dsp
} // namespace thelonious

#endif
