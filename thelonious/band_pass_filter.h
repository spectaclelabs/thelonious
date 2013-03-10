#ifndef THELONIOUS_BAND_PASS_FILTER_H
#define THELONIOUS_BAND_PASS_FILTER_H

#include <cmath>

#include "types.h"
#include "rates.h"
#include "constants.h"
#include "biquad_filter.h"

namespace thelonious {

template <size_t N>
class BandPassFilterN: public BiquadFilter<N> {
public:
    BandPassFilterN(Sample frequency, Sample damping=2.0f*T_SQRT1_2) :
        BiquadFilter<N>(frequency, damping) {}

private:
    void calculateCoefficients(Sample frequency, Sample damping) {
        Sample w0 = 2.0f * T_PI * frequency * INV_SAMPLE_RATE;
        Sample cosw0 = cos(w0);
        Sample sinw0 = sin(w0);
        Sample alpha =  0.5 * sinw0 * damping;

        this->coefficients.b0 = alpha;
        this->coefficients.b1 = 0;
        this->coefficients.b2 = -alpha;
        this->coefficients.a0 = 1.0f + alpha;
        this->coefficients.a1 = -2.0f * cosw0;
        this->coefficients.a2 = 1.0f - alpha; 
    }
};

typedef BandPassFilterN<1> BandPassFilter;

}

#endif
