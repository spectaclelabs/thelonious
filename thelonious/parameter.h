#ifndef THELONIOUS_PARAMETER_H
#define THELONIOUS_PARAMETER_H

#include <algorithm>

#include "types.h"
#include "duplex.h"
#include "util.h"
#include "thelonious/constants/sizes.h"

namespace thelonious {

class Parameter : public Duplex<1, 1> {
public:
    Parameter(Sample value=0.0f, Interpolation interpolation=LINEAR) :
        value(value), lastValue(value), interpolation(interpolation),
        isDynamic(false), isFilled(false) {}

    const Chock& get() {
        update();
        return block[0];
    }

    void tickOut(Block<1> &block) {
        update();
        block = this->block;
    }

    void tickIn(Block<1> &block) {
        this->block = block;
        isDynamic = true;
        isFilled = false;
    }

    void set(Sample value) {
        this->value = value;
        isFilled = false;
    }

    void setInterpolation(Interpolation interpolation) {
        this->interpolation = interpolation;
    }

    Interpolation getInterpolation() {
        return interpolation;
    }

private:
    void update() {
        if (isDynamic) {
            isDynamic = false;
            return;
        }

        if (value == lastValue && isFilled) {
            return;
        }

        bool canFill = (value == lastValue || interpolation == NONE);
        if (canFill) {
            std::fill(block[0].begin(), block[0].end(), value);
            isFilled = true;
            lastValue = value;
            return;
        }

        for (uint32_t i=0; i<constants::BLOCK_SIZE; i++) {
            block[0][i] = linearInterpolate(lastValue, value,
                                            i * constants::INV_BLOCK_SIZE);
        }
        lastValue = value;
    }

    Block<1> block;
    Sample value;
    Sample lastValue;
    Interpolation interpolation;

    bool isDynamic;
    bool isFilled;
};

/**
 * Set the parameter from a sample.
 * Usage example: 440.0f >> oscillator.frequency;
 */
inline void operator>>(Sample sample, Parameter &parameter) {
    parameter.set(sample);
}

} // namespace thelonious

#endif
