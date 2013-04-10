#ifndef THELONIOUS_AUDIO_DEVICE_H
#define THELONIOUS_AUDIO_DEVICE_H

#include <thread>
#include <condition_variable>
#include <mutex>

#include "RtAudio.h"

#include "types.h"
#include "source.h"
#include "sink.h"
#include "constants/sizes.h"
#include "constants/rates.h"

namespace thelonious {

template <size_t N>
class AudioDeviceInput : public Source<N> {
public:
    AudioDeviceInput(uint32_t blocksPerBuffer) :
            blocksPerBuffer(blocksPerBuffer),
            bufferSize(blocksPerBuffer * constants::BLOCK_SIZE),
            blockIndex(blocksPerBuffer) {}

    void tick(Block<N> &block) {
        std::unique_lock<std::mutex> lock(mutex);
        if (blockIndex == blocksPerBuffer) {
            haveSamples.wait(lock);
        }

        for (uint32_t i=0; i<N; i++) {
            Chock chock = block[i];
            // The start of the channel in the outputSamples buffer
            float *channelStart = buffer + i * bufferSize;
            // The start of the block we are interested in
            float *blockStart = channelStart + blockIndex *
                                constants::BLOCK_SIZE;
            float *blockEnd = blockStart + constants::BLOCK_SIZE;
            std::copy(blockStart, blockEnd, chock.begin());
        }

        blockIndex++;
    }

    void setBuffer(float *buffer) {
        std::lock_guard<std::mutex> lock(mutex);
        this->buffer = buffer;
        blockIndex = 0;
        haveSamples.notify_one();
    }

private:
    float *buffer;
    uint32_t blocksPerBuffer;
    size_t bufferSize;
    uint32_t blockIndex;
    std::mutex mutex;
    std::condition_variable haveSamples;
};

template <size_t N>
class AudioDeviceOutput : public Sink<N> {
public:
    AudioDeviceOutput(uint32_t blocksPerBuffer) :
            blocksPerBuffer(blocksPerBuffer),
            bufferSize(blocksPerBuffer * constants::BLOCK_SIZE),
            blockIndex(blocksPerBuffer) {}

    void tick(Block<N> &block) {
        std::unique_lock<std::mutex> lock(mutex);
        if (blockIndex == blocksPerBuffer) {
            haveSamples.wait(lock);
        }

        for (uint32_t i=0; i<N; i++) {
            Chock chock = block[i];
            // The start of the channel in the outputSamples buffer
            float *channelStart = buffer + i * bufferSize;
            // The start of the block we are interested in
            float *blockStart = channelStart + blockIndex *
                                thelonious::constants::BLOCK_SIZE;
            std::copy(chock.begin(), chock.end(), blockStart);
        }

        blockIndex++;
    }

    void setBuffer(float *buffer) {
        std::lock_guard<std::mutex> lock(mutex);    
        this->buffer = buffer;
        blockIndex = 0;
        haveSamples.notify_one();
    }
         

private:
    float *buffer;
    uint32_t blocksPerBuffer;
    size_t bufferSize;
    uint32_t blockIndex;
    std::mutex mutex;
    std::condition_variable haveSamples;
};


template <size_t inputChannels, size_t outputChannels>
class AudioDeviceN {
public:
    AudioDeviceN(int inputDevice=-1, int outputDevice=-1,
                 uint32_t blocksPerBuffer=2) :
            input(blocksPerBuffer), output(blocksPerBuffer) {
        RtAudio::StreamParameters inputParameters;
        inputParameters.deviceId = inputDevice == -1 ?
            device.getDefaultInputDevice() : inputDevice;
        inputParameters.nChannels = inputChannels;

        RtAudio::StreamParameters outputParameters;
        outputParameters.deviceId = outputDevice == -1 ?
            device.getDefaultOutputDevice() : outputDevice;
        outputParameters.nChannels = outputChannels;

        RtAudio::StreamOptions options;
        options.flags = RTAUDIO_NONINTERLEAVED;

        uint32_t bufferSize = blocksPerBuffer * constants::BLOCK_SIZE;

        try {
            device.openStream(outputChannels > 0 ? &outputParameters: NULL,
                              inputChannels > 0 ? &inputParameters : NULL,
                              RTAUDIO_FLOAT32,
                              thelonious::constants::SAMPLE_RATE, &bufferSize,
                              &AudioDeviceN::callback, (void *) this, &options);
            device.startStream();
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

    static int callback(void *outputSamples, void *inputSamples,
                 uint32_t nBufferFrames, double streamTime,
                 RtAudioStreamStatus status, void *device) {
        AudioDeviceN *castDevice = (AudioDeviceN *) device;
        castDevice->input.setBuffer((float *) inputSamples);
        castDevice->output.setBuffer((float *) outputSamples);
        return 0;
    }

    AudioDeviceInput<inputChannels> input;
    AudioDeviceOutput<outputChannels> output;

private:
    RtAudio device;
};

typedef AudioDeviceN<1, 1> AudioDevice;

}

#endif
