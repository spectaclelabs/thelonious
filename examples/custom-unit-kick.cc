#include <iostream>

#include "thelonious.h"

using namespace thelonious;

// Create the kick class as a subclass of Source
template <size_t N>
class KickN : public Source<N> {
public:
    // Constructor initializes the two envelopes
    // Amplitude envelope goes from 0->1 in 0.01s, and from 1->0 in 0.5s
    // Frequency envelope goes from 80Hz->1Hz in 0.5s
    KickN() :
        amplitudeEnvelope(0.0f, {1.f, 0.0f}, {0.01f, 0.5f}),
        frequencyEnvelope(80.0f, {80.0f, 1.0f}, {0.01f, 0.5f}) {}

    void tick(Block<N> &block) {
        // Fan allows us to use a single trigger parameter to trigger both of the
        // envelopes
        trigger >> fan;
        fan >> frequencyEnvelope.gate;
        fan >> amplitudeEnvelope.gate;

        // Use the frequency envelope to control the frequency of the sine wave
        frequencyEnvelope >> sine.frequency;
        // Tick the kick output into the block
        sine * amplitudeEnvelope >> block;
    }

    // A trigger for the kick
    Parameter trigger;
    Fan fan;

    // The base waveform for our kick
    SineN<N> sine;

    // An amplitude envelope
    EnvelopeN<N> amplitudeEnvelope;
    EnvelopeN<N> frequencyEnvelope;
};

// Typedef the single-channel variant
typedef KickN<1> Kick;


// Create the audio device
auto device = AudioDevice();

// Create the kick
auto kick = Kick();

// Create a sawtooth wave for triggering the kick every second
auto saw = Saw(2);

void onAudio() {
    // Trigger the kick when the sawtooth wave passes through zero
    (saw > 0) >> kick.trigger;
    // Play the kick through the output
    kick >> device;
}

int main() {
    // Call the onAudio function when the device needs audio generating
    device.onAudio(onAudio);
    // Start the audio playing
    device.start();

    // Wait for a keypress to exit
    std::cin.get();
}

