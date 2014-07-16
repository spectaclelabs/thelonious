#ifndef THELONIOUS_OPERATORS_UNIT_UNARY_OPERATOR_H
#define THELONIOUS_OPERATORS_UNIT_UNARY_OPERATOR_H

#include "thelonious/operators/types.h"
#include "thelonious/source.h"
#include "thelonious/types.h"

namespace thelonious {
namespace operators {

template <size_t N, Operator Op>
class UnitUnaryOperatorN : public Source<N> {
public:
    UnitUnaryOperatorN(AbstractSource<N> &unit): unit(&unit) {}

    void tick(Block<N> &block) {
        Block<0> tmp;
        unit->tick(tmp, block);
        operate(block);
    }

private:
    void operate(Block<N> &block) {
        OperatorType<Op> op;
        operate(block, op);
    }

#define OPERATE_FUNCTION(name, uppername, op)                               \
    void operate(Block<N> &block, name ## Operator oper) {                  \
        block = op block;                                                   \
    }

    UNARY_OPERATOR_LIST(OPERATE_FUNCTION)

#undef OPERATE_FUNCTION

    AbstractSource<N> *unit;
};

#define UNIT_UNARY_OPERATOR_ALIAS(name, uppername, op)                            \
template<size_t N>                                                          \
using Unit ## name ## N = UnitUnaryOperatorN<N, uppername>;

UNARY_OPERATOR_LIST(UNIT_UNARY_OPERATOR_ALIAS)

#undef UNIT_UNARY_OPERATOR_ALIAS

} // namespace operators
} // namespace thelonious

#endif
