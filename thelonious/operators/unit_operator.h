#ifndef THELONIOUS_OPERATORS_UNIT_OPERATOR_H
#define THELONIOUS_OPERATORS_UNIT_OPERATOR_H

#include "thelonious/operators/types.h"
#include "thelonious/source.h"
#include "thelonious/types.h"

namespace thelonious {
namespace operators {

template <size_t N, Operator Op>
class UnitOperatorN : public Source<N> {
public:
    UnitOperatorN(AbstractSource<N> &unitA, AbstractSource<N> &unitB):
            unitA(&unitA), unitB(&unitB) {}

    void tick(Block<N> &blockA) {
        Block<0> tmp;
        unitA->tick(tmp, blockA);

        Block<N> blockB;
        unitB->tick(tmp, blockB);

        operate(blockA, blockB);
    }

private:
    void operate(Block<N> &blockA, Block<N> &blockB) {
        OperatorType<Op> op;
        operate(blockA, blockB, op);
    }

#define OPERATE_FUNCTION(name, uppername, op)                               \
    void operate(Block<N> &blockA, Block<N> &blockB,                        \
                 name ## Operator oper) {                                   \
        blockA = blockA op blockB;                                          \
    }

    OPERATOR_LIST(OPERATE_FUNCTION)

#undef OPERATE_FUNCTION

    AbstractSource<N> *unitA;
    AbstractSource<N> *unitB;
};

#define UNIT_OPERATOR_ALIAS(name, uppername, op)                            \
template<size_t N>                                                          \
using Unit ## name ## N = UnitOperatorN<N, uppername>;

OPERATOR_LIST(UNIT_OPERATOR_ALIAS)

#undef UNIT_OPERATOR_ALIAS

} // namespace operators
} // namespace thelonious

#endif
