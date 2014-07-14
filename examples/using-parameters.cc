#include <iostream>

#include "thelonious.h"

using namespace thelonious;

// Create an audio device
auto device = AudioDevice();

// Create a 220Hz sine wave generator
auto sine = Sine(220.0f);

// Create a 1Hz trigangle wave LFO for a vibrato effect
auto lfo = Triangle(1.0f);

void onAudio() {
    // Use the LFO to make the frequency of the sine wave oscillate
    // between 210Hz and 230Hz
    lfo * 10.0f + 220.0f >> sine.frequency;

    // Play the sine wave through the audio device
    sine >> device;
}

int main() {
    // Call the onAudio function when the device needs audio generating
    device.onAudio(onAudio);
    // Start the audio playing
    device.start();

    // Wait for a keypress to exit
    std::cin.get();
}

