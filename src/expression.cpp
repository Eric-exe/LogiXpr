#include "../include/expression.h"

Expression::Expression(std::string expression) {
    this->expression = expression;
}

Expression::Expression(std::string expression, std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) {
    this->expression = expression;
    this->left = left;
    this->right = right;
}

std::string Expression::getExpression() {
    return this->expression;
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