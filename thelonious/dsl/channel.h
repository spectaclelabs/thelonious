#ifndef THELONIOUS_DSL_CHANNEL_H
#define THELONIOUS_DSL_CHANNEL_H

#define CHANNEL_CHANNEL(op)                                         \
template <size_t N>                                                 \
Channel<N> operator op(const Channel<N> &a, const Channel<N> &b) {  \
    Channel<N> channel;                                             \
    for (uint32_t i=0; i<N; i++) {                                  \
        channel[i] = a[i] op b[i];                                  \
    }                                                               \
    return channel;                                                 \
}

#define CHANNEL_SAMPLE(op)                              \
template <size_t N>                                     \
Channel<N> operator op(const Channel<N> &a, Sample b) { \
    Channel<N> channel;                                 \
    for (uint32_t i=0; i<N; i++) {                      \
        channel[i] = a[i] op b;                         \
    }                                                   \
    return channel;                                     \
}

#define SAMPLE_CHANNEL(op)                              \
template <size_t N>                                     \
Channel<N> operator op(Sample a, const Channel<N> &b) { \
    Channel<N> channel;                                 \
    for (uint32_t i=0; i<N; i++) {                      \
        channel[i] = a op b[i];                         \
    }                                                   \
    return channel;                                     \
}

#define CHANNEL_CHANNEL_ASSIGN(op)                                      \
template <size_t N>                                                     \
Channel<N> & operator op ## =(Channel<N> &a, const Channel<N> &b) {     \
    for (uint32_t i=0; i<N; i++) {                                      \
       a[i] op ## = b[i];                                               \
    }                                                                   \
    return a;                                                           \
}

#define CHANNEL_SAMPLE_ASSIGN(op)                           \
template <size_t N>                                         \
Channel<N> & operator op ## =(Channel<N> &a, Sample b) {    \
    for (uint32_t i=0; i<N; i++) {                          \
        a[i] op ## = b;                                     \
    }                                                       \
    return a;                                               \
}

#define OPERATOR_LIST(function) \
function(+)                     \
function(-)                     \
function(*)                     \
function(/)                     \
function(%)

namespace thelonious {

OPERATOR_LIST(CHANNEL_CHANNEL)
OPERATOR_LIST(CHANNEL_SAMPLE)
OPERATOR_LIST(SAMPLE_CHANNEL)
OPERATOR_LIST(CHANNEL_CHANNEL_ASSIGN)
OPERATOR_LIST(CHANNEL_SAMPLE_ASSIGN)

} // namespace thelonious

#undef OPERATOR_LIST
#undef CHANNEL_CHANNEL
#undef CHANNEL_SAMPLE
#undef CHANNEL_CHANNEL_ASSIGN
#undef CHANNEL_SAMPLE_ASSIGN

#endif

