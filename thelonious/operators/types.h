#ifndef THELONIOUS_OPERATORS_TYPES_H
#define THELONIOUS_OPERATORS_TYPES_H

#include <type_traits>

namespace thelonious {
namespace operators {

// Individual operators
// Arithmetic
#define ADD_OPERATOR(function) \
function(Add, ADD, +)

#define SUBTRACT_OPERATOR(function) \
function(Subtract, SUBTRACT, -)

#define MULTIPLY_OPERATOR(function) \
function(Multiply, MULTIPLY, *)

#define DIVIDE_OPERATOR(function) \
function(Divide, DIVIDE, /)

#define MODULO_OPERATOR(function) \
function(Modulo, MODULO, %)

#define EQUAL_TO_OPERATOR(function) \
function(EqualTo, EQUAL_TO, ==)

#define NOT_EQUAL_TO_OPERATOR(function) \
function(NotEqualTo, NOT_EQUAL_TO, !=)

#define NOT_EQUAL_TO_OPERATOR(function) \
function(NotEqualTo, NOT_EQUAL_TO, !=)

#define UNARY_PLUS_OPERATOR(function) \
function(UnaryPlus, UNARY_PLUS, +)

#define UNARY_MINUS_OPERATOR(function) \
function(UnaryMinus, UNARY_MINUS, -)

// Comparison
#define LESS_THAN_OPERATOR(function) \
function(LessThan, LESS_THAN, <)

#define GREATER_THAN_OPERATOR(function) \
function(GreaterThan, GREATER_THAN, >)

#define LESS_THAN_OR_EQUAL_TO_OPERATOR(function) \
function(LessThanOrEqualTo, LESS_THAN_OR_EQUAL_TO, <=)

#define GREATER_THAN_OR_EQUAL_TO_OPERATOR(function) \
function(GreaterThanOrEqualTo, GREATER_THAN_OR_EQUAL_TO, >=)

// Logical
#define LOGICAL_NOT_OPERATOR(function) \
function(LogicalNot, LOGICAL_NOT, !)

#define LOGICAL_AND_OPERATOR(function) \
function(LogicalAnd, LOGICAL_AND, &&)

#define LOGICAL_OR_OPERATOR(function) \
function(LogicalOr, LOGICAL_OR, ||)

#define OPERATOR_LIST(function)             \
ADD_OPERATOR(function)                      \
SUBTRACT_OPERATOR(function)                 \
MULTIPLY_OPERATOR(function)                 \
DIVIDE_OPERATOR(function)                   \
MODULO_OPERATOR(function)                   \
EQUAL_TO_OPERATOR(function)                 \
NOT_EQUAL_TO_OPERATOR(function)             \
UNARY_PLUS_OPERATOR(function)               \
UNARY_MINUS_OPERATOR(function)              \
LESS_THAN_OPERATOR(function)                \
GREATER_THAN_OPERATOR(function)             \
LESS_THAN_OR_EQUAL_TO_OPERATOR(function)    \
GREATER_THAN_OR_EQUAL_TO_OPERATOR(function) \
LOGICAL_NOT_OPERATOR(function)              \
LOGICAL_AND_OPERATOR(function)              \
LOGICAL_OR_OPERATOR(function)               \

#define BINARY_OPERATOR_LIST(function)      \
ADD_OPERATOR(function)                      \
SUBTRACT_OPERATOR(function)                 \
MULTIPLY_OPERATOR(function)                 \
DIVIDE_OPERATOR(function)                   \
MODULO_OPERATOR(function)                   \
EQUAL_TO_OPERATOR(function)                 \
NOT_EQUAL_TO_OPERATOR(function)             \
LESS_THAN_OPERATOR(function)                \
GREATER_THAN_OPERATOR(function)             \
LESS_THAN_OR_EQUAL_TO_OPERATOR(function)    \
GREATER_THAN_OR_EQUAL_TO_OPERATOR(function) \
LOGICAL_AND_OPERATOR(function)              \
LOGICAL_OR_OPERATOR(function)               \

#define UNARY_OPERATOR_LIST(function)   \
UNARY_PLUS_OPERATOR(function)           \
UNARY_MINUS_OPERATOR(function)          \
LOGICAL_NOT_OPERATOR(function)              \

#define COMMUTATIVE_OPERATOR_LIST(function) \
ADD_OPERATOR(function)                      \
MULTIPLY_OPERATOR(function)                 \
EQUAL_TO_OPERATOR(function)                 \
NOT_EQUAL_TO_OPERATOR(function)             \
LOGICAL_AND_OPERATOR(function)              \
LOGICAL_OR_OPERATOR(function)               \

#define NON_COMMUTATIVE_OPERATOR_LIST(function) \
SUBTRACT_OPERATOR(function)                     \
DIVIDE_OPERATOR(function)                       \
MODULO_OPERATOR(function)                       \
LESS_THAN_OPERATOR(function)                    \
GREATER_THAN_OPERATOR(function)                 \
LESS_THAN_OR_EQUAL_TO_OPERATOR(function)        \
GREATER_THAN_OR_EQUAL_TO_OPERATOR(function)     \

#define BINARY_COMPOUND_OPERATOR_LIST(function)     \
ADD_OPERATOR(function)                              \
SUBTRACT_OPERATOR(function)                         \
MULTIPLY_OPERATOR(function)                         \
DIVIDE_OPERATOR(function)                           \
MODULO_OPERATOR(function)                           \

#define BINARY_NON_COMPOUND_OPERATOR_LIST(function) \
LESS_THAN_OPERATOR(function)                \
GREATER_THAN_OPERATOR(function)             \
LESS_THAN_OR_EQUAL_TO_OPERATOR(function)    \
GREATER_THAN_OR_EQUAL_TO_OPERATOR(function) \
LOGICAL_AND_OPERATOR(function)              \
LOGICAL_OR_OPERATOR(function)               \

// Operator lists minus modulo, which we override for sample processing
#define BINARY_OPERATOR_LIST_NO_MODULO(function)    \
ADD_OPERATOR(function)                              \
SUBTRACT_OPERATOR(function)                         \
MULTIPLY_OPERATOR(function)                         \
DIVIDE_OPERATOR(function)                           \
EQUAL_TO_OPERATOR(function)                         \
NOT_EQUAL_TO_OPERATOR(function)                     \
LESS_THAN_OPERATOR(function)                        \
GREATER_THAN_OPERATOR(function)                     \
LESS_THAN_OR_EQUAL_TO_OPERATOR(function)            \
GREATER_THAN_OR_EQUAL_TO_OPERATOR(function)         \
LOGICAL_AND_OPERATOR(function)                      \
LOGICAL_OR_OPERATOR(function)                       \

#define BINARY_COMPOUND_OPERATOR_LIST_NO_MODULO(function)   \
ADD_OPERATOR(function)                                      \
SUBTRACT_OPERATOR(function)                                 \
MULTIPLY_OPERATOR(function)                                 \
DIVIDE_OPERATOR(function)                                   \

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
