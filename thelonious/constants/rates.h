#ifndef THELONIOUS_RATES_H
#define THELONIOUS_RATES_H

#include "sizes.h"

namespace thelonious {
namespace constants {

constexpr float AUDIO_RATE = 44100.0f;
constexpr float SAMPLE_RATE = AUDIO_RATE;
constexpr float CONTROL_RATE = AUDIO_RATE / BLOCK_SIZE;
constexpr float INV_AUDIO_RATE = 1.0f / AUDIO_RATE;
constexpr float INV_SAMPLE_RATE = INV_AUDIO_RATE;
constexpr float INV_CONTROL_RATE = 1.0f / CONTROL_RATE;

} // namespace constants
} // namespace thelonious


#endif
