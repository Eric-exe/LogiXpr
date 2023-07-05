/**
 * @file equivLaws.cpp
 * @brief Implementation file for equivalence laws functions
 */

#include "../include/equivLaws.h"

bool identity(std::shared_ptr<Expression> expression) {
    bool changed = false;
    if (expression->getValue() == AND) {
        if (expression->hasLeft() && expression->getLeft()->isVar() && expression->hasRight() && expression->getRight()->getValue() == TRUE) {
            // replace the current expression with the left
            expression = expression->getLeft();
            changed = true;
        }
    }
    else if (expression->getValue() == OR) {
        if (expression->getLeft()->isVar() && expression->getRight()->getValue() == FALSE) {
            // replace the current expression with the right
            expression = expression->getRight();
            changed = true;
        }
    }
    return changed;
}
