#ifndef PARAMETER_H
#define PARAMETER_H

#include "dizzy.h"
#include "types.h"

namespace thelonious {

class Parameter {
public:
    Parameter(Sample value=0, bool interpolate=true) :
        value(value), lastValue(value), interpolate(interpolate) {}

    const Chock& get() {
        if (value == lastValue || !interpolate) {
            std::fill(buffer.begin(), buffer.end(), value);
        }
        else {
            dizzy::ramp(buffer, lastValue, value);
            lastValue = value;
        }

        if (dynamicBuffer != nullptr) {
            dizzy::add(buffer, buffer, *dynamicBuffer);
        }
        return buffer;
    }

    void setDynamic(Chock& chock) {
        dynamicBuffer = &chock;
    }

    void setDynamic(Block<1> &block) {
        dynamicBuffer = &block[0];
    }

    void unsetDynamic() {
        dynamicBuffer = nullptr;

        // De-zipper removal of the dynamic buffer.
        // TODO: Work out whether this should happen!
        /*
        if (interpolate) {
            lastValue = buffer.back();
        }
        */
    }

    void set(Sample value) {
        this->value = value;
    }

    void setInterpolate(bool interpolate) {
        this->interpolate = interpolate;
    }

    bool getInterpolate() {
        return interpolate;
    }

private:
    Sample value;
    Sample lastValue;

    Chock buffer;
    Chock *dynamicBuffer=nullptr;

    bool interpolate;
};

}

#endif
