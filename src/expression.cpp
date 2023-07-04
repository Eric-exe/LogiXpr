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

std::vector<std::string> Expression::getVariables() {
    std::vector<std::string> variables;
    if (this->isVar()) variables.push_back(this->value);

    if (this->hasLeft()) {
        std::vector<std::string> leftVariables = this->getLeft()->getVariables();
        variables.insert(variables.end(), leftVariables.begin(), leftVariables.end());
    }

    if (this->hasRight()) {
        std::vector<std::string> rightVariables = this->getRight()->getVariables();
        variables.insert(variables.end(), rightVariables.begin(), rightVariables.end());
    }
    return variables;
}