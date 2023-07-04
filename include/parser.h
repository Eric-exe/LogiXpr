#pragma once

#include <iostream>
#include <string>
#include <cctype>
#include <memory>
#include <stack>
#include <unordered_map>
#include "expression.h"

const static std::unordered_map<std::string, int> precedence = {
    {NOT, 5},
    {AND, 4},
    {OR, 3},
    {XOR, 2},
    {IMPLIES, 1},
    {IFF, 0}
};

std::vector<std::string> tokenize(std::string);
bool parse(std::string, std::shared_ptr<Expression>&);