/**
 * @file parser.h
 * @brief Header file for parser functions
 */

#pragma once

#include <iostream>
#include <string>
#include <cctype>
#include <memory>
#include <stack>
#include <unordered_map>
#include "expression.h"

/**
 * @brief Precedence of the operators
 */
const static std::unordered_map<std::string, int> precedence = {
    {NOT, 5},
    {AND, 4},
    {OR, 3},
    {XOR, 2},
    {IMPLIES, 1},
    {IFF, 0}};

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