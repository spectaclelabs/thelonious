#ifndef THELONIOUS_AUDIO_DEVICE_H
#define THELONIOUS_AUDIO_DEVICE_H

#ifndef THELONIOUS_NO_DEVICE

#if defined(OF_VERSION_MAJOR) || defined(OF_VERSION_MINOR) ||\
    defined(OF_VERSION_PATCH)
#include "audio_device_ofx.h"
#else
#include "audio_device_desktop.h"
#endif

namespace thelonious {

typedef AudioDeviceN<1, 1> AudioDevice;

}

#endif // THELONIOUS_NO_DEVICE

#endif // Include guard

