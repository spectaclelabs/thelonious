#ifndef THELONIOUS_ASR_ENVELOPE_H
#define THELONIOUS_ASR_ENVELOPE_H

#include "thelonious/types.h"
#include "envelope.h"

namespace thelonious {
namespace dsp {
namespace envelopes {

template <size_t N>
class ASREnvelopeN : public EnvelopeN<N> {
public:
    ASREnvelopeN(float attack, float sustain, float release) :
            EnvelopeN<N>(0.0f, {sustain, 0.0f},
                         {attack, release}, 0) {
    }
};

typedef ASREnvelopeN<1> ASREnvelope;

}
} // namespace dsp
} // namespace thelonious

#endif
