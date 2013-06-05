#ifndef THELONIOUS_UTIL_H
#define THELONIOUS_UTIL_H

#include <cmath>

#include "types.h"
#include "constants/rates.h"

namespace thelonious {

inline Sample modulo(Sample a, Sample b) {
    return a - std::floor(a / b) * b;
}

inline Sample wrap(Sample a, Sample b) {
    return modulo(a, b);
}

// Should be quicker when a is unlikely to be outside b as we avoid the
// division and floating point compares are cheap
inline Sample moduloB(Sample a, Sample b) {
    while (a >= b) {
        a -= b;
    }

    while (a < 0.0f) {
        a += b;
    }
    return a;
}

inline Sample wrapB(Sample a, Sample b) {
    return moduloB(a, b);
}

inline constexpr uint32_t secondsToSamples(float seconds) {
    return seconds * constants::SAMPLE_RATE;
}

inline constexpr float samplesToSeconds(uint32_t samples) {
    return samples * constants::INV_SAMPLE_RATE;
}

inline Sample linearInterpolate(Sample start, Sample end, Sample position) {
    return start + position * (end - start);
}

} // namespace thelonious

#endif

