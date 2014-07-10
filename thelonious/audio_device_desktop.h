#ifndef THELONIOUS_AUDIO_DEVICE_DESKTOP_H
#define THELONIOUS_AUDIO_DEVICE_DESKTOP_H

#ifndef THELONIOUS_NO_DEVICE

#include "RtAudio.h"

#include "types.h"
#include "source.h"
#include "sink.h"
#include "duplex.h"
#include "constants/sizes.h"
#include "constants/rates.h"

namespace thelonious {

template <size_t M, size_t N>
class AudioDeviceN : public Duplex<N, M> {
public:
    AudioDeviceN(int inputDevice=-1, int outputDevice=-1,
                 uint32_t numberOfBuffers=8) {
        RtAudio::StreamParameters inputParameters;
        inputParameters.deviceId = inputDevice == -1 ?
            device.getDefaultInputDevice() : inputDevice;
        inputParameters.nChannels = M;

        RtAudio::StreamParameters outputParameters;
        outputParameters.deviceId = outputDevice == -1 ?
            device.getDefaultOutputDevice() : outputDevice;
        outputParameters.nChannels = N;

        RtAudio::StreamOptions options;
        options.numberOfBuffers = numberOfBuffers;
        options.flags = RTAUDIO_NONINTERLEAVED;

        uint32_t bufferSize = constants::BLOCK_SIZE;

        try {
            device.openStream(N > 0 ? &outputParameters: NULL,
                              M > 0 ? &inputParameters : NULL,
                              RTAUDIO_FLOAT32,
                              thelonious::constants::SAMPLE_RATE, &bufferSize,
                              &AudioDeviceN::callback, (void *) this, &options);
        }
        catch (RtError& error) {
            error.printMessage();
            exit(0);
        }
    }

    ~AudioDeviceN() {
        if (device.isStreamRunning()) {
            device.stopStream();
        }
        if (device.isStreamOpen()) {
            device.closeStream();
        }
    }

    void start() {
        try {
            device.startStream();
        }
        catch (RtError& error) {
            error.printMessage();
            exit(0);
        }
    }

    void stop() {
       if (device.isStreamRunning()) {
            device.stopStream();
        }
    }

    void setInputBuffer(float *buffer) {
        inputBuffer = buffer;
    }

    void setOutputBuffer(float *buffer) {
        outputBuffer = buffer;
    }

    static int callback(void *outputSamples, void *inputSamples,
                 uint32_t nBufferFrames, double streamTime,
                 RtAudioStreamStatus status, void *device) {
        AudioDeviceN *castDevice = (AudioDeviceN *) device;
        castDevice->setInputBuffer((float *) inputSamples);
        castDevice->setOutputBuffer((float *) outputSamples);
        if (castDevice->onAudioCallback != nullptr) {
            (*(castDevice->onAudioCallback))();
        }
        return 0;
    }

    void onAudio(void (*onAudioCallback)()) {
        this->onAudioCallback = onAudioCallback;
    }

    void tickOut(Block<M> &block) {
        for (uint32_t i=0; i<M; i++) {
            Chock chock = block[i];
            // The start of the channel in the outputSamples buffer
            float *blockStart = inputBuffer + i * constants::BLOCK_SIZE;
            float *blockEnd = blockStart + constants::BLOCK_SIZE;
            std::copy(blockStart, blockEnd, chock.begin());
        }
    }

    void tickIn(Block<N> &block) {
        for (uint32_t i=0; i<N; i++) {
            Chock chock = block[i];
            // The start of the channel in the outputSamples buffer
            float *blockStart = outputBuffer + i * constants::BLOCK_SIZE;
            std::copy(chock.begin(), chock.end(), blockStart);
        }
    }

private:
    RtAudio device;

    void (*onAudioCallback)() = nullptr;

    float *inputBuffer;
    float *outputBuffer;
};

} // namespace

#endif // ifndef THELONIOUS_NO_DEVICE

#endif
