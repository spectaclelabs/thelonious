#ifndef THELONIOUS_UTIL_H
#define THELONIOUS_UTIL_H

#include <cmath>

#include "types.h"
#include "constants/rates.h"

namespace thelonious {

Sample modulo(Sample a, Sample b) {
    return a - std::floor(a / b) * b;
}

// Alias wrap to modulo, so we can use it semantically based on the application
constexpr auto &wrap = modulo;

// Should be quicker when a is unlikely to be outside b as we avoid the
// division and floating point compares are cheap
Sample moduloB(Sample a, Sample b) {
    while (a >= b) {
        a -= b;
    }

    while (a < 0.0f) {
        a += b;
    }
    return a;
}

constexpr auto &wrapB = moduloB;

constexpr uint32_t secondsToSamples(float seconds) {
    return seconds * constants::SAMPLE_RATE;
}

constexpr float samplesToSeconds(uint32_t samples) {
    return samples * constants::INV_SAMPLE_RATE;
}

Sample linearInterpolate(Sample start, Sample end, Sample position) {
    return start + position * (end - start);
}

} // namespace thelonious

#endif

