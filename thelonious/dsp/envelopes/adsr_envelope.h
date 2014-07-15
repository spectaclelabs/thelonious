#ifndef THELONIOUS_ADSR_ENVELOPE_H
#define THELONIOUS_ADSR_ENVELOPE_H

#include "thelonious/types.h"
#include "envelope.h"

namespace thelonious {
namespace dsp {
namespace envelopes {

template <size_t N>
class ADSREnvelopeN : public EnvelopeN<N> {
public:
    ADSREnvelopeN(float attack, float decay, float sustain, float release) :
            EnvelopeN<N>(0.0f, {1.0f, sustain, 0.0f},
                         {attack, decay, release}, 1) {
    }
};

typedef ADSREnvelopeN<1> ADSREnvelope;

}
} // namespace dsp
} // namespace thelonious

#endif
