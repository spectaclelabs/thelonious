#ifndef THELONIOUS_OPERATORS_BINARY_OPERATOR_H
#define THELONIOUS_OPERATORS_BINARY_OPERATOR_H

#include "thelonious/types.h"
#include "thelonious/processor.h"
#include "thelonious/parameter.h"
#include "thelonious/dsl/channel.h"
#include "types.h"

namespace thelonious {
namespace operators {

template <size_t N, Operator Op>
class BinaryOperatorN : public Processor<N, N> {
public:
    BinaryOperatorN(Sample value=0.0f): value(value) {}

    void tick(Block<N> &inputBlock, Block<N> &outputBlock) {
        Chock valueChock = value.get();

        for (uint32_t i=0; i<N; i++) {
            operate(inputBlock[i], outputBlock[i], valueChock);
        }
    }

    Parameter value;
private:

    void operate(Chock &inputChock, Chock &outputChock, Chock &valueChock) {
        OperatorType<Op> op;
        operate(inputChock, outputChock, valueChock);
    }

#define OPERATE_FUNCTION(name, uppername, op)                               \
    void operate(Chock &inputChock, Chock &outputChock, Chock &valueChock,  \
                 name ## Operator oper) {                                   \
        outputChock = inputChock op valueChock;                             \
    }

    BINARY_OPERATOR_LIST(OPERATE_FUNCTION)

#undef OPERATE_FUNCTION

};


#define BINARY_OPERATOR_ALIAS_N(name, uppername, op)                               \
template<size_t N>                                                          \
using name ## N = BinaryOperatorN<N, uppername>;

#define BINARY_OPERATOR_ALIAS(name, uppername, op)                                 \
typedef name ## N<1> name;

BINARY_OPERATOR_LIST(BINARY_OPERATOR_ALIAS_N)
BINARY_OPERATOR_LIST(BINARY_OPERATOR_ALIAS)

#undef BINARY_OPERATOR_ALIAS_N
#undef BINARY_OPERATOR_ALIAS

} // namespace operators
} // namespace thelonious

#endif
