#ifndef THELONIOUS_AUDIO_DEVICE_OFX_H
#define THELONIOUS_AUDIO_DEVICE_OFX_H

#ifndef THELONIOUS_NO_DEVICE
#if defined(OF_VERSION_MAJOR) || defined(OF_VERSION_MINOR) ||\
    defined(OF_VERSION_PATCH)

// Undef stupid ofx defines
#undef PI
#undef TWO_PI

#include "types.h"
#include "source.h"
#include "sink.h"
#include "duplex.h"
#include "constants/sizes.h"
#include "constants/rates.h"

namespace thelonious {

template <size_t M, size_t N>
class AudioDeviceN :
        public Duplex<N, M>, public ofBaseSoundInput,
        public ofBaseSoundOutput {
public:
    AudioDeviceN(int inputDevice=-1, int outputDevice=-1,
                 uint32_t numberOfBuffers=8) {
        soundStream.setDeviceID(inputDevice);
        soundStream.setup(N, M, constants::SAMPLE_RATE,
                          constants::BLOCK_SIZE, numberOfBuffers);
        soundStream.setInput(this);
        soundStream.setOutput(this);
    }

    void start() {
        soundStream.start();
    }

    void stop() {
        soundStream.stop();
    }

    void audioIn(float *samples, int bufferSize, int numberOfChannels) {
        inputBuffer = samples;
    }

    void audioOut(float *samples, int bufferSize, int numberOfChannels) {
        outputBuffer = samples;

        // Call the standard ofx audioOut callback
        ofBaseApp *app = ofGetAppPtr();
        // The app pointer is initialized after the audio device. We can
        // wait...
        if (app == nullptr) {
            return;
        }
        app->audioOut(nullptr, constants::BLOCK_SIZE, N);
    }

    void tickOut(Block<M> &block) {
        for (uint32_t i=0; i<M; i++) {
            Chock chock = block[i];
            for (uint32_t j=0; j<constants::BLOCK_SIZE; j++) {
                chock[j] = inputBuffer[j * M + i];
            }
        }
    }

    void tickIn(Block<N> &block) {
        for (uint32_t i=0; i<N; i++) {
            Chock chock = block[i];
            for (uint32_t j=0; j<constants::BLOCK_SIZE; j++) {
                outputBuffer[j * N + i] = chock[j];
            }
        }
    }

private:
    ofSoundStream soundStream;

    float *inputBuffer;
    float *outputBuffer;
};

} // namespace

#endif // ifdef OF_VERSION_*
#endif // ifndef THELONIOUS_NO_DEVICE

#endif
