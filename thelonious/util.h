#ifndef THELONIOUS_UTIL_H
#define THELONIOUS_UTIL_H

#include <cmath>

#include "types.h"
#include "rates.h"

namespace thelonious {

Sample modulo(Sample a, Sample b) {
    return a - std::floor(a / b) * b;
}

// Alias wrap to modulo, so we can use it semantically based on the application
constexpr auto &wrap = modulo;

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

