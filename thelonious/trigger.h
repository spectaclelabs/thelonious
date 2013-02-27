#ifndef THELONIOUS_TRIGGER_H
#define THELONIOUS_TRIGGER_H

#include <algorithm>

#include "types.h"
#include "unit.h"
#include "parameter.h"

namespace thelonious {

template <size_t N>
class Trigger : public Unit<N> {
public:
    Trigger(Sample trigger=0.0f) : trigger(trigger, NONE) {}

    void tick(Block<N> &block) {
        Chock triggerChock = trigger.get();
        Chock &channel = block[0];

        std::fill(channel.begin(), channel.end(), 0.0f);
        if (triggerChock[0]) {
            channel[0] = triggerChock[0];
        }

        trigger.set(0.0f);

        auto it=block.begin() + 1;
        auto end = block.end();
        for (; it<end; it++) {
            std::copy(channel.begin(), channel.end(), (*it).begin());
        }
    }

    Parameter trigger;
};

}

#endif
