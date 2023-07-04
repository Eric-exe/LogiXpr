#include "../include/expression.h"

Expression::Expression(std::string value) {
    this->value = value;
}

Expression::Expression(std::string value, std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) {
    this->value = value;
    this->left = left;
    this->right = right;
}

std::string Expression::getValue() {
    return this->value;
}

bool Expression::hasLeft() {
    return this->left != nullptr;
}

bool Expression::hasRight() {
    return this->right != nullptr;
}

bool Expression::isBinary() {
    return this->hasLeft() && this->hasRight();
}

bool Expression::isVar() {
    // if the expression is a variable, it will be a single character from a-z
    return this->value.length() == 1 && std::islower(this->value[0]);
}

std::shared_ptr<Expression> Expression::getLeft() {
    return this->left;
}

std::shared_ptr<Expression> Expression::getRight() {
    return this->right;
}

void Expression::setLeft(std::shared_ptr<Expression> left) {
    this->left = left;
}

void Expression::setRight(std::shared_ptr<Expression> right) {
    this->right = right;
}

std::set<std::string> Expression::getVariables() {
    std::set<std::string> variables;
    if (this->isVar()) variables.insert(this->value);

    if (this->hasLeft()) {
        std::set<std::string> leftVariables = this->getLeft()->getVariables();
        variables.insert(leftVariables.begin(), leftVariables.end());
    }

    if (this->hasRight()) {
        std::set<std::string> rightVariables = this->getRight()->getVariables();
        variables.insert(rightVariables.begin(), rightVariables.end());
    }

    return variables;
}

std::shared_ptr<Expression> Expression::clone() {
    std::shared_ptr<Expression> clonedExpression;
    
    if (isBinary()) clonedExpression = std::make_shared<Expression>(value, left->clone(), right->clone());
    else if (hasLeft()) clonedExpression = std::make_shared<Expression>(value, left->clone(), nullptr);
    else clonedExpression = std::make_shared<Expression>(value);
    
    return clonedExpression;
}