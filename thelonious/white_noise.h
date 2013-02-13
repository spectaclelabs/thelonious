#ifndef WHITE_NOISE_H
#define WHITE_NOISE_H

namespace thelonious {

template <size_t N>
class WhiteNoise {
public:
    WhiteNoise() {}

    void tick(Block<N> &block) {
        auto it=block.begin();
        auto end = block.end();
        for (; it!=end; it++) {
            dizzy::random(*it, -1.0f, 1.0f);
        }
    }
};

}

#endif
