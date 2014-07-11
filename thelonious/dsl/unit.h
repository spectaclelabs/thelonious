#ifndef THELONIOUS_DSL_UNIT_H
#define THELONIOUS_DSL_UNIT_H

#include "thelonious/operators/types.h"
#include "thelonious/operators/unit_operator.h"

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


namespace thelonious {

OPERATOR_LIST(LVALUE_LVALUE)
OPERATOR_LIST(LVALUE_RVALUE)
OPERATOR_LIST(RVALUE_LVALUE)
OPERATOR_LIST(RVALUE_RVALUE)

} // namespace thelonious

#undef LVALUE_LVALUE
#undef LVALUE_RVALUE
#undef RVALUE_LVALUE
#undef RVALUE_RVALUE

#endif

