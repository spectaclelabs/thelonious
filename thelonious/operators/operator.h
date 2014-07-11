#ifndef THELONIOUS_OPERATORS_OPERATOR_H
#define THELONIOUS_OPERATORS_OPERATOR_H

#include "thelonious/types.h"
#include "thelonious/processor.h"
#include "thelonious/parameter.h"
#include "thelonious/dsl/channel.h"
#include "types.h"

namespace thelonious {
namespace operators {

template <size_t N, char Op>
class OperatorN : public Processor<N, N> {
public:
    OperatorN(Sample value=0.0f): value(value) {}

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

    void operate(Chock &inputChock, Chock &outputChock, Chock &valueChock,
                 AdditionOperator op) {
        outputChock = inputChock + valueChock;
    }

   void operate(Chock &inputChock, Chock &outputChock, Chock &valueChock,
                 SubtractionOperator op) {
        outputChock = inputChock - valueChock;
    }

    void operate(Chock &inputChock, Chock &outputChock, Chock &valueChock,
                 MultiplicationOperator op) {
        outputChock = inputChock * valueChock;
    }

    void operate(Chock &inputChock, Chock &outputChock, Chock &valueChock,
                 DivisionOperator op) {
        outputChock = inputChock / valueChock;
    }

    void operate(Chock &inputChock, Chock &outputChock, Chock &valueChock,
                 ModuloOperator op) {
        outputChock = inputChock % valueChock;
    } 
};


#define OPERATOR_ALIAS_N(name, op)                                          \
template<size_t N>                                                          \
using name ## N = OperatorN<N, op>;

#define OPERATOR_ALIAS(name, op)                                            \
typedef name ## N<1> name;

#define OPERATOR_LIST(function)     \
function(Add, ADDITION)             \
function(Subtract, SUBTRACTION)     \
function(Multiply, MULTIPLICATION)  \
function(Divide, DIVISION)          \
function(Modulo, MODULO)

OPERATOR_LIST(OPERATOR_ALIAS_N)
OPERATOR_LIST(OPERATOR_ALIAS)

#undef OPERATOR_LIST
#undef OPERATOR_ALIAS_N
#undef OPERATOR_ALIAS

} // namespace operators
} // namespace thelonious

#endif
