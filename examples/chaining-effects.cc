#include <iostream>

#include "thelonious.h"

using namespace thelonious;

// Create an audio device
auto device = AudioDevice();

// Create a 110Hz sawtooth wave generator
auto saw = Saw(110.0f);

// Create a percussive envelope, with a short attack and release phase
auto envelope = PercussiveEnvelope(0.05f, 0.05f);

// Create a low-pass filter, with a corner frequency of 220Hz
auto lpf = LowPassFilter(220.0f);

// Create a delay effect.  The empty template arguments (<>) mean that we
// use the default maximum delay time of 0.2 seconds.
auto delay = FeedbackDelay<>();

void onAudio() {
    // Apply the envelope to the sawtooth wave, pass it through the
    // filter and delay efects, and play it through the audio device
    saw * envelope >> lpf >> delay >> device;
}

int main() {
    // Trigger the envelope
    1.0f >> envelope.gate;

    // Call the onAudio function when the device needs audio generating
    device.onAudio(onAudio);
    // Start the audio playing
    device.start();

    // Wait for a keypress to exit
    std::cin.get();
}

