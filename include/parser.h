/**
 * @file parser.h
 * @brief Header file for parser functions
 */

#pragma once

#include "expression.h"
#include <vector>

/**
 * @defgroup parser Parser functions
 * @brief Functions for parsing expressions
 * @{
 */

/**
 * @brief Tokenize the expression
 *
 * @param expression expression to be tokenized
 *
 * @return string vector of tokens
 */
std::vector<std::string> tokenize(std::string expression);

/**
 * @brief Parse the expression and convert it to an abstract syntax tree
 *
 * @param expression expression to be parsed
 * @param root to the root of the abstract syntax tree
 *
 * @return bool of whether the expression was parsed successfully
 */
bool parse(std::string expression, std::shared_ptr<Expression> &root);

/** @} */