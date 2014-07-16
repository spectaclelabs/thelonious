#ifndef THELONIOUS_DSL_UNIT_H
#define THELONIOUS_DSL_UNIT_H

#include "thelonious/operators/types.h"
#include "thelonious/operators/unit_binary_operator.h"
#include "thelonious/operators/unit_unary_operator.h"

#define LVALUE_LVALUE(name, uppername, op)                                  \
template <size_t N>                                                         \
operators::Unit ## name ## N<N> operator op(AbstractSource<N> &a,           \
                                            AbstractSource<N> &b) {         \
    return operators::Unit ## name ## N<N>(a, b);                           \
}

#define LVALUE_RVALUE(name, uppername, op)                                  \
template <size_t N>                                                         \
operators::Unit ## name ## N<N> operator op(AbstractSource<N> &a,           \
                                            AbstractSource<N> &&b) {        \
    return operators::Unit ## name ## N<N>(a, b);                           \
}

#define RVALUE_LVALUE(name, uppername, op)                                  \
template <size_t N>                                                         \
operators::Unit ## name ## N<N> operator op(AbstractSource<N> &&a,          \
                                            AbstractSource<N> &b) {         \
    return operators::Unit ## name ## N<N>(a, b);                           \
}


#define RVALUE_RVALUE(name, uppername, op)                                  \
template <size_t N>                                                         \
operators::Unit ## name ## N<N> operator op(AbstractSource<N> &&a,          \
                                            AbstractSource<N> &&b) {        \
    return operators::Unit ## name ## N<N>(a, b);                           \
}

#define UNARY_LVALUE(name, uppername, op)                                   \
template <size_t N>                                                         \
operators::Unit ## name ## N<N> operator op(AbstractSource<N> &a) {         \
    return operators::Unit ## name ## N<N>(a);                              \
}

#define UNARY_RVALUE(name, uppername, op)                                   \
template <size_t N>                                                         \
operators::Unit ## name ## N<N> operator op(AbstractSource<N> &&a) {        \
    return operators::Unit ## name ## N<N>(a);                              \
}

namespace thelonious {

BINARY_OPERATOR_LIST(LVALUE_LVALUE)
BINARY_OPERATOR_LIST(LVALUE_RVALUE)
BINARY_OPERATOR_LIST(RVALUE_LVALUE)
BINARY_OPERATOR_LIST(RVALUE_RVALUE)
UNARY_OPERATOR_LIST(UNARY_LVALUE)
UNARY_OPERATOR_LIST(UNARY_RVALUE)

} // namespace thelonious

#undef LVALUE_LVALUE
#undef LVALUE_RVALUE
#undef RVALUE_LVALUE
#undef RVALUE_RVALUE

#endif

