#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

int main(int argc, char** argv) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

