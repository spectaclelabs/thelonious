#include <iostream>

#include "thelonious.h"

using namespace thelonious;

// A four-bit crusher
// Receives N channels, and outputs the same number of channels.
template <size_t N>
class FourBitN : public Processor<N, N> {
public:
    void tick(Block<N> &inputBlock, Block<N> &outputBlock) {
        // Loop through each channel
        for (uint32_t i=0; i<N; i++) {
            // Loop through each sample
            for (uint32_t j=0; j<constants::BLOCK_SIZE; j++) {
                // Scale the input to an integer between -8 and +8
                int8_t asFourBit = inputBlock[i][j] * 8;
                // Convert it back to a float send it to the output
                outputBlock[i][j] = asFourBit / 8.f;
            }
        }
    }
};

// Typedef the single-channel variant
typedef FourBitN<1> FourBit;


// Create the audio device
auto device = AudioDevice();

// A 220Hz sine wave
auto sine = Sine(220.f);

// The bit crusher
auto crusher = FourBit();

void onAudio() {
    // Bit crush the sine wave
    sine >> crusher >> device;
}

int main() {
    // Call the onAudio function when the device needs audio generating
    device.onAudio(onAudio);
    // Start the audio playing
    device.start();

    // Wait for a keypress to exit
    std::cin.get();
}
