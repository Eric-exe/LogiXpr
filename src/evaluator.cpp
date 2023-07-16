/**
 * @file evaluator.cpp
 * @brief Implementation file for evaluator functions
 */

#include "../include/evaluator.h"

std::vector<std::unordered_map<std::string, bool>> getTruthTableInputs(std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> rhs)
{
  std::set<std::string> variables = lhs->getVariables();
  std::set<std::string> rhsVariables = rhs->getVariables();
  variables.insert(rhsVariables.begin(), rhsVariables.end());

  std::vector<std::unordered_map<std::string, bool>> inputs;

  for (int i = 0; i < pow(2, variables.size()); i++)
  {
    std::unordered_map<std::string, bool> input;
    int state = i;
    for (auto variable : variables)
    {
      input[variable] = state % 2;
      state /= 2;
    }
    inputs.push_back(input);
  }

  return inputs;
}

bool evaluateExpression(std::shared_ptr<Expression> expression, std::unordered_map<std::string, bool> inputs)
{
  if (expression == nullptr)
    return false;

  std::string value = expression->getValue();

  if (value == TRUE)
    return true;
  if (value == FALSE)
    return false;
  if (expression->isVar())
    return inputs[expression->getValue()]; // leaf node
  if (value == AND)
    return evaluateExpression(expression->getLeft(), inputs) && evaluateExpression(expression->getRight(), inputs);
  if (value == OR)
    return evaluateExpression(expression->getLeft(), inputs) || evaluateExpression(expression->getRight(), inputs);
  if (value == NOT)
    return !evaluateExpression(expression->getLeft(), inputs);
  if (value == XOR)
    return evaluateExpression(expression->getLeft(), inputs) != evaluateExpression(expression->getRight(), inputs);
  if (value == IMPLIES)
    return !evaluateExpression(expression->getLeft(), inputs) || evaluateExpression(expression->getRight(), inputs);
  if (value == IFF)
    return evaluateExpression(expression->getLeft(), inputs) == evaluateExpression(expression->getRight(), inputs);

  return false;
}

bool isEquivalent(std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> rhs)
{
  std::vector<std::unordered_map<std::string, bool>> inputs = getTruthTableInputs(lhs, rhs);

  for (auto input : inputs)
  {
    if (evaluateExpression(lhs, input) != evaluateExpression(rhs, input))
      return false;
  }

  return true;
}
