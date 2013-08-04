#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "thelonious/audio_device.h"

int main(int argc, char** argv) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
