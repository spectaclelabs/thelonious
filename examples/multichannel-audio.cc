#include <iostream>

#include "thelonious.h"

using namespace thelonious;

// Create an audio device with no input channels and a stereo output
auto device = AudioDeviceN<0, 2>();

// Create a stereo 220Hz sine wave generator
auto sine = SineN<2>(220.0f);

void onAudio() {
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
