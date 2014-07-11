#ifndef THELONIOUS_OPERATORS_TYPES_H
#define THELONIOUS_OPERATORS_TYPES_H

#include <type_traits>

namespace thelonious {
namespace operators {

// All of the operators
#define OPERATOR_LIST(function)                                 \
function(Add, ADD, +)                                           \
function(Subtract, SUBTRACT, -)                                 \
function(Multiply, MULTIPLY, *)                                 \
function(Divide, DIVIDE, /)                                     \
function(Modulo, MODULE, %)                                     \
function(EqualTo, EQUAL_TO, ==)                                 \
function(LessThan, LESS_THAN, <)                                \
function(GreaterThan, GREATER_THAN, >)                          \
function(LessThanOrEqualTo, LESS_THAN_OR_EQUAL_TO, <=)          \
function(GreaterThanOrEqualTo, GREATER_THAN_OR_EQUAL_TO, >=)

// The commutative operators
#define COMMUTATIVE_OPERATOR_LIST(function)                     \
function(Add, ADD, +)                                           \
function(Multiply, MULTIPLY, *)                                 \
function(EqualTo, EQUAL_TO, ==)\

// The non-commutative operators
#define NON_COMMUTATIVE_OPERATOR_LIST(function)                 \
function(Subtract, SUBTRACT, -)                                 \
function(Divide, DIVIDE, /)                                     \
function(Modulo, MODULE, %)                                     \
function(LessThan, LESS_THAN, <)                                \
function(GreaterThan, GREATER_THAN, >)                          \
function(LessThanOrEqualTo, LESS_THAN_OR_EQUAL_TO, <=)          \
function(GreaterThanOrEqualTo, GREATER_THAN_OR_EQUAL_TO, >=)

// The arithmetic operators
#define ARITHMETIC_OPERATOR_LIST(function)  \
function(Add, ADD, +)                       \
function(Subtract, SUBTRACT, -)             \
function(Multiply, MULTIPLY, *)             \
function(Divide, DIVIDE, /)                 \
function(Modulo, MODULE, %)

// The arithmetic operators minus modulo, which we override for sample
// processing
#define RAW_ARITHMETIC_OPERATOR_LIST(function)  \
function(Add, ADD, +)                       \
function(Subtract, SUBTRACT, -)             \
function(Multiply, MULTIPLY, *)             \
function(Divide, DIVIDE, /)

// The comparison operators
#define COMPARISON_OPERATOR_LIST(function)                      \
function(EqualTo, EQUAL_TO, ==)                                 \
function(LessThan, LESS_THAN, <)                                \
function(GreaterThan, GREATER_THAN, >)                          \
function(LessThanOrEqualTo, LESS_THAN_OR_EQUAL_TO, <=)          \
function(GreaterThanOrEqualTo, GREATER_THAN_OR_EQUAL_TO, >=)

// Create an enum containing the uppername of all of the operators
#define UPPERNAME(name, uppername, op) uppername,
enum Operator {
    OPERATOR_LIST(UPPERNAME)
};
#undef UPPERNAME

// An integral constant used to disambiguate between the operators
template <Operator value>
using OperatorType = std::integral_constant<Operator, value>;

// Simpler aliases for the integral constants
#define OPERATOR_ALIAS(name, uppername, op)                                 \
typedef OperatorType<uppername> name ## Operator;

OPERATOR_LIST(OPERATOR_ALIAS)

#undef OPERATOR_ALIAS

// Type identifying whether we should be doing the inverse operation for
// non-commutative operators
template <bool value>
using InverseType = std::integral_constant<bool, value>;

typedef InverseType<true> InverseOperator;
typedef InverseType<false> RegularOperator;


} // namespace operators
} // namespace thelonious

#endif
