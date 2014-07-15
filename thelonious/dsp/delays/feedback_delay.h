#ifndef THELONIOUS_FEEDBACK_DELAY_H
#define THELONIOUS_FEEDBACK_DELAY_H

#include "thelonious/types.h"
#include "thelonious/processor.h"
#include "thelonious/parameter.h"
#include "thelonious/util.h"
#include "thelonious/constants/sizes.h"

namespace thelonious {
namespace dsp {
namespace delays {

template <size_t N, size_t bufferSize=secondsToSamples(0.2)>
class FeedbackDelayN : public Processor<N, N> {
public:
    FeedbackDelayN(Sample time=0.2f, Sample feedback=0.5f):
        time(time), feedback(feedback) {}

    void tick(Block<N> &inputBlock, Block<N> &outputBlock) {
        Chock timeChock = time.get();
        Chock feedbackChock = feedback.get();

        for (uint32_t i=0; i<constants::BLOCK_SIZE; i++) {
            for (uint32_t j=0; j<N; j++) {
                buffer[j][position] = buffer[j][position] * feedbackChock[i] +
                                      inputBlock[j][i];
                outputBlock[j][i] = buffer[j][position];
            }

            position += 1;
            if (position >= secondsToSamples(timeChock[i]) ||
                position >= bufferSize) {
                position = 0;
            }
        }
    }

    Parameter time;
    Parameter feedback;

private:
    Buffer<N, bufferSize> buffer;
    uint32_t position;
};

template <size_t bufferSize=secondsToSamples(0.2)>
using FeedbackDelay = FeedbackDelayN<1, bufferSize>;

} // namespace delays
} // namespace dsp
} // namespace thelonious

#endif
