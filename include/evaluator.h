#pragma once

#include <vector>
#include <unordered_map>
#include "expression.h"

std::vector<std::unordered_map<std::string, bool>> getTruthTableInputs(std::shared_ptr<Expression>, std::shared_ptr<Expression>);
bool evaluateExpression(std::shared_ptr<Expression>, std::unordered_map<std::string, bool>);
bool isEquivalent(std::shared_ptr<Expression>, std::shared_ptr<Expression>);