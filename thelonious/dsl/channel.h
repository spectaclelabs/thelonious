#ifndef THELONIOUS_DSL_CHANNEL_H
#define THELONIOUS_DSL_CHANNEL_H

#include <cstdint>

#include "thelonious/util.h"
#include "thelonious/operators/types.h"

#define CHANNEL_CHANNEL(name, uppername, op)                        \
template <size_t N>                                                 \
Channel<N> operator op(const Channel<N> &a, const Channel<N> &b) {  \
    Channel<N> channel;                                             \
    for (uint32_t i=0; i<N; i++) {                                  \
        channel[i] = a[i] op b[i];                                  \
    }                                                               \
    return channel;                                                 \
}

#define CHANNEL_SAMPLE(name, uppername, op)             \
template <size_t N>                                     \
Channel<N> operator op(const Channel<N> &a, Sample b) { \
    Channel<N> channel;                                 \
    for (uint32_t i=0; i<N; i++) {                      \
        channel[i] = a[i] op b;                         \
    }                                                   \
    return channel;                                     \
}

#define SAMPLE_CHANNEL(name, uppername, op)             \
template <size_t N>                                     \
Channel<N> operator op(Sample a, const Channel<N> &b) { \
    Channel<N> channel;                                 \
    for (uint32_t i=0; i<N; i++) {                      \
        channel[i] = a op b[i];                         \
    }                                                   \
    return channel;                                     \
}

#define CHANNEL_CHANNEL_ASSIGN(name, uppername, op)                     \
template <size_t N>                                                     \
Channel<N> & operator op ## =(Channel<N> &a, const Channel<N> &b) {     \
    for (uint32_t i=0; i<N; i++) {                                      \
       a[i] op ## = b[i];                                               \
    }                                                                   \
    return a;                                                           \
}

#define CHANNEL_SAMPLE_ASSIGN(name, uppername, op)          \
template <size_t N>                                         \
Channel<N> & operator op ## =(Channel<N> &a, Sample b) {    \
    for (uint32_t i=0; i<N; i++) {                          \
        a[i] op ## = b;                                     \
    }                                                       \
    return a;                                               \
}

#define CHANNEL_UNARY(name, uppername, op)              \
template <size_t N>                                     \
Channel<N> operator op(const Channel<N> &a) {           \
    Channel<N> channel;                                 \
    for (uint32_t i=0; i<N; i++) {                      \
        channel[i] = op a[i];                           \
    }                                                   \
    return channel;                                     \
}

namespace thelonious {

BINARY_OPERATOR_LIST_NO_MODULO(CHANNEL_CHANNEL)
BINARY_OPERATOR_LIST_NO_MODULO(CHANNEL_SAMPLE)
BINARY_OPERATOR_LIST_NO_MODULO(SAMPLE_CHANNEL)
BINARY_COMPOUND_OPERATOR_LIST_NO_MODULO(CHANNEL_CHANNEL_ASSIGN)
BINARY_COMPOUND_OPERATOR_LIST_NO_MODULO(CHANNEL_SAMPLE_ASSIGN)

UNARY_OPERATOR_LIST(CHANNEL_UNARY)

// Need to manually define these as we need to use the modulo function
template <size_t N>
Channel<N> operator %(const Channel<N> &a, const Channel<N> &b) {
    Channel<N> channel;
    for (uint32_t i=0; i<N; i++) {
        channel[i] = modulo(a[i], b[i]);
    }
    return channel;
}

template <size_t N>
Channel<N> operator %(const Channel<N> &a, Sample b) {
    Channel<N> channel;
    for (uint32_t i=0; i<N; i++) {
        channel[i] = modulo(a[i], b);
    }
    return channel;
}

template <size_t N>
Channel<N> operator %(Sample a, const Channel<N> &b) {
    Channel<N> channel;
    for (uint32_t i=0; i<N; i++) {
        channel[i] = modulo(a, b[i]);
    }
    return channel;
}

template <size_t N>
Channel<N> & operator %=(Channel<N> &a, const Channel<N> &b) {
    for (uint32_t i=0; i<N; i++) {
       a[i] = modulo(a[i], b[i]);
    }
    return a;
}

template <size_t N>
Channel<N> & operator %=(Channel<N> &a, Sample b) {
    for (uint32_t i=0; i<N; i++) {
        a[i] = modulo(a[i], b);
    }
    return a;
}


} // namespace thelonious

#undef CHANNEL_CHANNEL
#undef CHANNEL_SAMPLE
#undef CHANNEL_CHANNEL_ASSIGN
#undef CHANNEL_SAMPLE_ASSIGN
#undef CHANNEL_UNARY

#endif

