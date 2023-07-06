/**
 * @file evaluator.h
 * @brief Header file for evaluator functions
 */

#pragma once

#include <vector>
#include <unordered_map>
#include "expression.h"

/**
 * @defgroup evaluator Evaluator functions
 * @brief Functions for evaluating expressions
 * @{
 */

/**
 * @brief Generate the truth table inputs for the given expressions
 *
 * @param lhs pointer to left hand side expression
 * @param rhs pointer to right hand side expression
 * 
 * @return vector of maps of input variables
 */
std::vector<std::unordered_map<std::string, bool>> getTruthTableInputs(std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> rhs);

/**
 * @brief Evaluate the expression with the given inputs
 *
 * @param expression pointer to expression to evaluate
 * @param inputs map of variable inputs
 *
 * @return bool of whether the expression is true or false
 */
bool evaluateExpression(std::shared_ptr<Expression> expression, std::unordered_map<std::string, bool> inputs);

/**
 * @brief Check if two expressions are equivalent
 *
 * @param lhs pointer to left hand side expression
 * @param rhs pointer to right hand side expression
 *
 * @return bool of whether the expressions are equivalent
 */
bool isEquivalent(std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> rhs);

/** @} */