#include <iostream>

#include "thelonious.h"

using namespace thelonious;

// Create an audio device
AudioDevice device;

// Create a 220Hz sine wave generator
Sine sine(220.0f);

// Create a 1Hz trigangle wave LFO for a vibrato effect
Triangle lfo(1.0f);

// Create a percussive envelope, with a half-second attack phase and a 1
// second release phase
PercussiveEnvelope envelope(0.5f, 1.0f);

void onAudio() {
    // Use the LFO to make the frequency of the sine wave oscillate
    // between 215Hz and 225Hz
    lfo * 10.0f + 220.0f >> sine.frequency;

    // Apply the envelope to the sine wave, and play it through the audio
    // device
    sine * envelope >> device;
}

int main() {
    // Trigger the envelope
    1.0 >> envelope.gate;

    // Call the onAudio function when the device needs audio generating
    device.onAudio(onAudio);
    // Start the audio playing
    device.start();

    // Wait for a keypress to exit
    std::cin.get();
}

