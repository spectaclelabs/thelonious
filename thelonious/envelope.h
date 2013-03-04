#ifndef THELONIOUS_ENVELOPE_H
#define THELONIOUS_ENVELOPE_H

#include <initializer_list>
#include <algorithm>

#include "types.h"
#include "sizes.h"
#include "rates.h"
#include "unit.h"
#include "parameter.h"
#include "util.h"

namespace thelonious {
class EnvelopeSegment {
public:
    virtual Sample get(Sample startValue, Sample endValue,
                       Sample time, Sample duration) {
        // Default to linear segments
        return linearInterpolate(startValue, endValue, time / duration);
    }
};

// typedef allows us to create LinearSegments semantically
typedef EnvelopeSegment LinearSegment;

template <size_t N, size_t numberOfSegments>
class EnvelopeN : public Unit<N> {
public:
    EnvelopeN(Sample initialValue,
             std::array<Sample, numberOfSegments> values,
             std::array<Sample, numberOfSegments> durations) :
        gate(0.0f, NONE), values(values), durations(durations),
        value(initialValue), time(0.0f), segmentIndex(0u), playing(false),
        canTrigger(true) {
    }

    EnvelopeN(std::initializer_list<Sample> values,
             std::initializer_list<Sample> durations,
             std::initializer_list<Sample> segments) :
        EnvelopeN(values, durations) {
        int size = std::min(segments.size(), numberOfSegments);
        std::copy(segments.begin(), segments.begin() + size,
                  this->segments.begin());
    }

    void tick(Block<N> &block) {
        Chock gateChock = gate.get();
        for (uint32_t i=0; i<BLOCK_SIZE; i++) {
            if (gateChock[i] && canTrigger) {
                firstSegment();
                playing = true;
                canTrigger = false;
            }

            if (!gateChock[i]) {
                canTrigger = true;
            }

            while (playing && time > duration) {
                nextSegment();
            }

            if (playing) {
                value = segments[segmentIndex].get(startValue, endValue,
                                                   time, duration);
                time += INV_SAMPLE_RATE;
            }

            block[0][i] = value;
        }
    }

    Parameter gate;

private:
    void setSegmentVariables() {
        duration = durations[segmentIndex];
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

        if (segmentIndex == numberOfSegments) {
            playing = false;
        }
        else {
            time -= duration;
            setSegmentVariables();
        }
    }

    std::array<Sample, numberOfSegments> values;
    std::array<Sample, numberOfSegments> durations;
    std::array<EnvelopeSegment, numberOfSegments> segments;

    Sample value;
    Sample time;

    Sample duration;
    Sample startValue;
    Sample endValue;

    uint32_t segmentIndex;
    bool playing;
    bool canTrigger;
};

template <size_t numberOfSegments>
using Envelope = EnvelopeN<1, numberOfSegments>;

}
#endif
