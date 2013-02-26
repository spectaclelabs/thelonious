#ifndef LOW_PASS_FILTER_H
#define LOW_PASS_FILTER_H

#include <cmath>

#include "types.h"
#include "rates.h"
#include "biquad_filter.h"

namespace thelonious {

template <size_t N>
class LowPassFilter: public BiquadFilter<N> {
public:
    LowPassFilter(Sample frequency) : BiquadFilter<N>(frequency) {}

private:
    void calculateCoefficients(Sample frequency) {
        Sample w0 = 2.0f * M_PI * frequency * INV_SAMPLE_RATE;
        Sample cosw0 = cos(w0);
        Sample sinw0 = sin(w0);
        Sample alpha = sinw0 * M_SQRT2 / 2.0f;

        this->coefficients.b0 = (1.0f - cosw0) / 2.0f;
        this->coefficients.b1 = 1.0f - cosw0;
        this->coefficients.b2 = this->coefficients.b0;
        this->coefficients.a0 = 1.0f + alpha;
        this->coefficients.a1 = -2.0f * cosw0;
        this->coefficients.a2 = 1.0f - alpha; 
    }
};

}

#endif
