#ifndef THELONIOUS_UTIL_H
#define THELONIOUS_UTIL_H

#include <cmath>

#include "types.h"
#include "rates.h"

namespace thelonious {

Sample wrap(Sample value, Sample length) {
    return value - std::floor(value / length) * length;
}

constexpr uint32_t secondsToSamples(Sample seconds) {
    return seconds * SAMPLE_RATE;
}

constexpr Sample samplesToSeconds(uint32_t samples) {
    return samples * INV_SAMPLE_RATE;
}

Sample linearInterpolate(Sample start, Sample end, Sample position) {
    return start + position * (end - start);
}

}

#endif

