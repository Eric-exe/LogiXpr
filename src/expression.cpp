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
    this->left->setParent(parent);
}

void Expression::setRight(std::shared_ptr<Expression> right, std::shared_ptr<Expression> parent)
{
    this->right = right;
    this->right->setParent(parent);
}

void Expression::setParent(std::shared_ptr<Expression> parent)
{
    this->parent = parent;
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

    clonedExpression = std::make_shared<Expression>(this->getValue());
    if (this->hasLeft())
        clonedExpression->setLeft(this->getLeft()->clone(), clonedExpression);
    if (this->hasRight())
        clonedExpression->setRight(this->getRight()->clone(), clonedExpression);

    return clonedExpression;
}

std::shared_ptr<Expression> Expression::cloneTree()
{
    if (!this->getParent())
        return this->clone();
    // keep going up the tree until we find the root
    std::shared_ptr<Expression> root = this->getParent();
    while (root->getParent())
        root = root->getParent();
    
    std::shared_ptr<Expression> clonedTree = root->clone();

    // now, go back down the tree and find the node we called from
    std::stack<std::shared_ptr<Expression>> stack;
    stack.push(clonedTree);

    while (!stack.empty())
    {
        std::shared_ptr<Expression> current = stack.top();
        stack.pop();

        if (this->compare(current))
            return current;

        if (current->hasLeft())
            stack.push(current->getLeft());
        if (current->hasRight())
            stack.push(current->getRight());
    }
    return nullptr;
}

bool Expression::compare(std::shared_ptr<Expression> other)
{
    // make sure the expressions don't have the same address
    if (this == other.get())
        return false;

    if (this->getValue() != other->getValue())
        return false;

    if (this->hasLeft() != other->hasLeft())
        return false;

    if (this->hasRight() != other->hasRight())
        return false;

    if (this->hasLeft() && !this->getLeft()->compare(other->getLeft()))
        return false;

    if (this->hasRight() && !this->getRight()->compare(other->getRight()))
        return false;
        
    return true;
}

bool Expression::compareTree(std::shared_ptr<Expression> other) {
    if (!this->getParent()) return this->compare(other);

    std::shared_ptr<Expression> root = this->getParent();
    while (root->getParent())
        root = root->getParent();
    
    return root->compare(other);
}

std::string Expression::toString()
{
    if (this->isVar() || this->getValue() == "T" || this->getValue() == "F") return this->getValue();

    std::string expressionString = "";
    if (this->getValue() == NOT) {
        expressionString += "!(" + this->getLeft()->toString() + ")";
    }
    else {
        expressionString += "(" + this->getLeft()->toString() + ")";
        expressionString += " " + this->getValue() + " ";
        expressionString += "(" + this->getRight()->toString() + ")";
    }
    return expressionString;
}

std::string Expression::toStringTree() {
    if (!this->getParent()) return this->toString();

    std::shared_ptr<Expression> root = this->getParent();
    while (root->getParent())
        root = root->getParent();

    std::string treeString = root->toString();
    return treeString; 
}

std::string Expression::toStringMinimal() {
    if (this->isVar() || this->getValue() == "T" || this->getValue() == "F") return this->getValue();

    std::string expressionString = "";

    if (this->getValue() == NOT) {
        // check if the left side is a variable or T or F
        if (this->getLeft()->isVar() || this->getLeft()->getValue() == "T" || this->getLeft()->getValue() == "F") {
            expressionString += this->getValue();
            expressionString += this->getLeft()->toStringMinimal();
        }
        else {
            expressionString += this->getValue();
            expressionString += "(" + this->getLeft()->toStringMinimal() + ")";
        }
    }
    else {
        std::string leftMinimal = this->getLeft()->toStringMinimal();
        std::string op = this->getValue();
        std::string rightMinimal = this->getRight()->toStringMinimal();

        // check if the left side is a variable or T or F
        if (!this->getLeft()->isVar() && this->getLeft()->getValue() != "T" && this->getLeft()->getValue() != "F") {
            // determine operator precedence
            if (precedence.at(this->getValue()) > precedence.at(this->getLeft()->getValue())) {
                leftMinimal = "(" + leftMinimal + ")";
            }
        }

        // check if the right side is a variable or T or F
        if (!this->getRight()->isVar() && this->getRight()->getValue() != "T" && this->getRight()->getValue() != "F") {
            // determine operator precedence
            if (precedence.at(this->getValue()) > precedence.at(this->getRight()->getValue())) {
                rightMinimal = "(" + rightMinimal + ")";
            }
        }

        expressionString += leftMinimal;
        expressionString += " " + op + " ";
        expressionString += rightMinimal;
    }
    return expressionString;
}