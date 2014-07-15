#ifndef THELONIOUS_HIGH_PASS_FILTER_H
#define THELONIOUS_HIGH_PASS_FILTER_H

#include <cmath>

#include "thelonious/types.h"
#include "thelonious/constants/rates.h"
#include "thelonious/constants/math.h"
#include "biquad_filter.h"

namespace thelonious {
namespace dsp {
namespace filters {

template <size_t N>
class HighPassFilterN: public BiquadFilter<N> {
public:
    HighPassFilterN(Sample frequency=440.0f,
                    Sample damping=2.0f*constants::ROOT_HALF) :
        BiquadFilter<N>(frequency, damping) {}

private:
    void calculateCoefficients(Sample frequency, Sample damping) {
        Sample w0 = constants::TWO_PI * frequency * constants::INV_SAMPLE_RATE;
        Sample cosw0 = std::cos(w0);
        Sample sinw0 = std::sin(w0);
        Sample alpha = 0.5 * sinw0 * damping;

        this->coefficients.b0 = (1.0f + cosw0) / 2.0f;
        this->coefficients.b1 = - (1.0f + cosw0);
        this->coefficients.b2 = this->coefficients.b0;
        this->coefficients.a0 = 1.0f + alpha;
        this->coefficients.a1 = -2.0f * cosw0;
        this->coefficients.a2 = 1.0f - alpha; 
    }
};

typedef HighPassFilterN<1> HighPassFilter;

} // namespace filters
} // namespace dsp
} // namespace thelonious

#endif
