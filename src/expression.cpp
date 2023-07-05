/**
 * @file expression.cpp
 * @brief Implementation file for expression class
 */

#include "../include/expression.h"

Expression::Expression(std::string value)
{
    this->value = value;
}

std::string Expression::getValue()
{
    return this->value;
}

bool Expression::hasLeft()
{
    return this->left != nullptr;
}

bool Expression::hasRight()
{
    return this->right != nullptr;
}

bool Expression::isBinary()
{
    return this->hasLeft() && this->hasRight();
}

bool Expression::isVar()
{
    // if the expression is a variable, it will be a single character from a-z
    return this->value.length() == 1 && std::islower(this->value[0]);
}

std::shared_ptr<Expression> Expression::getParent()
{
    return this->parent;
}

std::shared_ptr<Expression> Expression::getLeft()
{
    return this->left;
}

std::shared_ptr<Expression> Expression::getRight()
{
    return this->right;
}

void Expression::setLeft(std::shared_ptr<Expression> left, std::shared_ptr<Expression> parent)
{
    this->left = left;
    this->left->parent = parent;
}

void Expression::setRight(std::shared_ptr<Expression> right, std::shared_ptr<Expression> parent)
{
    this->right = right;
    this->right->parent = parent;
}

std::set<std::string> Expression::getVariables()
{
    std::set<std::string> variables;
    if (this->isVar())
        variables.insert(this->value);

    if (this->hasLeft())
    {
        std::set<std::string> leftVariables = this->getLeft()->getVariables();
        variables.insert(leftVariables.begin(), leftVariables.end());
    }

    if (this->hasRight())
    {
        std::set<std::string> rightVariables = this->getRight()->getVariables();
        variables.insert(rightVariables.begin(), rightVariables.end());
    }

    return variables;
}

std::shared_ptr<Expression> Expression::clone()
{
    std::shared_ptr<Expression> clonedExpression;

    clonedExpression = std::make_shared<Expression>(this->value);
    if (this->hasLeft())
        clonedExpression->setLeft(this->getLeft()->clone(), clonedExpression);
    if (this->hasRight())
        clonedExpression->setRight(this->getRight()->clone(), clonedExpression);

    return clonedExpression;
}