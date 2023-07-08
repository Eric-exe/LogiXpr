/**
 * @file solver.h
 * @brief Header file for solver functions
 */

#pragma once

#include <vector>
#include <queue>
#include <utility>
#include "expression.h"
#include "equivLaws.h"

/**
 * @defgroup solver Solver functions
 * @brief Functions for solving expressions
 * @{
 */

/**
 * @brief Prove the expressions are equivalence using equivalence laws by solving the left hand side to the right hand side.
 * Required that the expressions are actually equivalent for this to work.
 * 
 * @param lhs pointer to left hand side expression
 * @param rhs pointer to right hand side expression
 * 
 * @return vector of vector of strings of the steps to prove the equivalence: {{lhs, law},...}
 *
 * @see isEquivalent
 */
std::vector<std::vector<std::string>> proveEquivalence(std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> rhs);

/**
 * @brief Generate the next expressions from the current expression.
 * Creates a new expression for each law that can be applied to the current expression
 * and adds it to the queue of steps to be processed if the expression has not already been visited.
 * 
 * @param expr pointer to the current expression
 * @param end pointer to the end expression to reach. If the expression is found, the function will return early.
 * @param found reference to a boolean that is set to true if the end expression is found
 * @param queue reference to the queue of expressions to be for new expressions to be added to
 * @param visited reference to the map of visited expressions. 
 * The key is the string representation of the new expression and the value is a pair of the string expression derived from and the law used to get to the expression
 */
void generateNextSteps(std::shared_ptr<Expression> expr, std::shared_ptr<Expression> end, bool& found, std::queue<std::shared_ptr<Expression>>& queue, std::unordered_map<std::string, std::pair<std::string, std::string>>& visited);
/** @} */