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

template<size_t N>
using AddN = OperatorN<N, '+'>;

typedef AddN<1> Add;

template<size_t N>
using SubtractN = OperatorN<N, '-'>;

typedef SubtractN<1> Subtract;

template<size_t N>
using MultiplyN = OperatorN<N, '*'>;

typedef MultiplyN<1> Multiply;

template<size_t N>
using DivideN = OperatorN<N, '/'>;

typedef DivideN<1> Divide;

template<size_t N>
using ModuloN = OperatorN<N, '%'>;

typedef ModuloN<1> Modulo;



} // namespace operators
} // namespace thelonious

#endif
