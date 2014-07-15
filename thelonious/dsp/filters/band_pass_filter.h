#ifndef THELONIOUS_BAND_PASS_FILTER_H
#define THELONIOUS_BAND_PASS_FILTER_H

#include <cmath>

#include "thelonious/types.h"
#include "thelonious/constants/rates.h"
#include "thelonious/constants/math.h"
#include "biquad_filter.h"

namespace thelonious {
namespace dsp {
namespace filters {

template <size_t N>
class BandPassFilterN: public BiquadFilter<N> {
public:
    BandPassFilterN(Sample frequency=440.0f,
                    Sample damping=2.0f*constants::ROOT_HALF) :
        BiquadFilter<N>(frequency, damping) {}

private:
    void calculateCoefficients(Sample frequency, Sample damping) {
        Sample w0 = constants::TWO_PI * frequency * constants::INV_SAMPLE_RATE;
        Sample cosw0 = std::cos(w0);
        Sample sinw0 = std::sin(w0);
        Sample alpha =  0.5f * sinw0 * damping;

        this->coefficients.b0 = alpha;
        this->coefficients.b1 = 0;
        this->coefficients.b2 = -alpha;
        this->coefficients.a0 = 1.0f + alpha;
        this->coefficients.a1 = -2.0f * cosw0;
        this->coefficients.a2 = 1.0f - alpha; 
    }
};

typedef BandPassFilterN<1> BandPassFilter;

} // namespace filters
} // namespace dsp
} // namespace thelonious

#endif
