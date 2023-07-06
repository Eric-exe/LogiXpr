/**
 * @file equivLaws.cpp
 * @brief Implementation file for equivalence laws functions
 */

#include "../include/equivLaws.h"

void EquivLaws::replace(std::shared_ptr<Expression>& expression, std::shared_ptr<Expression> newExpression)
{
    std::shared_ptr<Expression> parent = expression->getParent();
    if (parent == nullptr) {
        // if the parent is null, then the current expression is the root
        // set the new expression as the root
        expression = newExpression;
        return;
    }

    // determine if the current expression is the left or right subexpression of the parent
    if (parent->getLeft() == expression)
        parent->setLeft(newExpression, parent);
    else
        parent->setRight(newExpression, parent);
}

bool EquivLaws::identity(std::shared_ptr<Expression>& expression)
{
    if (expression->getValue() == AND && expression->getRight()->getValue() == TRUE)
    {
        // replace the current expression with the left
        std::shared_ptr<Expression> parent = expression->getParent();
        std::shared_ptr<Expression> newExpression = expression->getLeft();

        replace(expression, newExpression);
        return true;
    }
    else if (expression->getValue() == OR && expression->getRight()->getValue() == FALSE)
    {
        // replace the current expression with the left
        std::shared_ptr<Expression> parent = expression->getParent();
        std::shared_ptr<Expression> newExpression = expression->getLeft();

        replace(expression, newExpression);
        return true;
    }
    return false;
}

bool EquivLaws::domination(std::shared_ptr<Expression>& expression)
{
    // p & F = F, p | T = T
    if (expression->getValue() == AND && expression->getRight()->getValue() == FALSE)
    {
        // replace the current expression with the right
        std::shared_ptr<Expression> parent = expression->getParent();
        std::shared_ptr<Expression> newExpression = expression->getRight();

        replace(expression, newExpression);

        return true;
    }
    else if (expression->getValue() == OR && expression->getRight()->getValue() == TRUE)
    {
        // replace the current expression with the right
        std::shared_ptr<Expression> parent = expression->getParent();
        std::shared_ptr<Expression> newExpression = expression->getRight();

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::idempotent(std::shared_ptr<Expression>& expression)
{
    if (expression->getValue() == AND || expression->getValue() == OR)
    {
        // p & p = p, p | p = p
        std::shared_ptr<Expression> left = expression->getLeft();
        std::shared_ptr<Expression> right = expression->getRight();

        if (!left->compare(right))
            return false;

        // replace the current expression with the left
        std::shared_ptr<Expression> parent = expression->getParent();
        std::shared_ptr<Expression> newExpression = expression->getLeft();

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::doubleNegation(std::shared_ptr<Expression>& expression)
{
    // !!p = p
    if (expression->getValue() == NOT && expression->getLeft()->getValue() == NOT)
    {
        // replace the current expression with the left
        std::shared_ptr<Expression> parent = expression->getParent();
        std::shared_ptr<Expression> newExpression = expression->getLeft()->getLeft();

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::commutative(std::shared_ptr<Expression>& expression)
{
    if (expression->getValue() == AND || expression->getValue() == OR)
    {
        // p & q = q & p, p | q = q | p
        std::shared_ptr<Expression> left = expression->getLeft();
        std::shared_ptr<Expression> right = expression->getRight();

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(expression->getValue());
        newExpression->setLeft(right, newExpression);
        newExpression->setRight(left, newExpression);

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::associative(std::shared_ptr<Expression>& expression)
{
    // (p | q) | r = p | (q | r), (p & q) & r = p & (q & r)
    if (expression->getValue() == AND || expression->getValue() == OR && expression->getLeft()->getValue() == expression->getValue())
    {
        std::shared_ptr<Expression> left1 = expression->getLeft()->getLeft();
        std::shared_ptr<Expression> left2 = expression->getLeft()->getRight();
        std::shared_ptr<Expression> right = expression->getRight();

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(expression->getValue());
        newExpression->setLeft(left1, newExpression);
        newExpression->setRight(std::make_shared<Expression>(expression->getValue()), newExpression);
        newExpression->getRight()->setLeft(left2, newExpression->getRight());
        newExpression->getRight()->setRight(right, newExpression->getRight());

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::associativeReversed(std::shared_ptr<Expression>& expression)
{
    // p | (q | r) = (p | q) | r, p & (q & r) = (p & q) & r
    if (expression->getValue() == AND || expression->getValue() == OR && expression->getRight()->getValue() == expression->getValue())
    {
        std::shared_ptr<Expression> left = expression->getLeft();
        std::shared_ptr<Expression> right1 = expression->getRight()->getLeft();
        std::shared_ptr<Expression> right2 = expression->getRight()->getRight();

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(expression->getValue());
        newExpression->setLeft(std::make_shared<Expression>(expression->getValue()), newExpression);
        newExpression->getLeft()->setLeft(left, newExpression->getLeft());
        newExpression->getLeft()->setRight(right1, newExpression->getLeft());
        newExpression->setRight(right2, newExpression);

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::distributive(std::shared_ptr<Expression>& expression)
{
    // p | (q & r) = (p | q) & (p | r), p & (q | r) = (p & q) | (p & r)
    if (expression->getValue() == AND && expression->getRight()->getValue() == OR)
    {
        std::shared_ptr<Expression> left = expression->getLeft();
        std::shared_ptr<Expression> right1 = expression->getRight()->getLeft();
        std::shared_ptr<Expression> right2 = expression->getRight()->getRight();

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(OR);
        newExpression->setLeft(std::make_shared<Expression>(AND), newExpression);
        newExpression->getLeft()->setLeft(left, newExpression->getLeft());
        newExpression->getLeft()->setRight(right1, newExpression->getLeft());
        newExpression->setRight(std::make_shared<Expression>(AND), newExpression);
        newExpression->getRight()->setLeft(left, newExpression->getRight());
        newExpression->getRight()->setRight(right2, newExpression->getRight());

        replace(expression, newExpression);

        return true;
    }
    else if (expression->getValue() == OR && expression->getRight()->getValue() == AND)
    {
        std::shared_ptr<Expression> left = expression->getLeft();
        std::shared_ptr<Expression> right1 = expression->getRight()->getLeft();
        std::shared_ptr<Expression> right2 = expression->getRight()->getRight();

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(AND);
        newExpression->setLeft(std::make_shared<Expression>(OR), newExpression);
        newExpression->getLeft()->setLeft(left, newExpression->getLeft());
        newExpression->getLeft()->setRight(right1, newExpression->getLeft());
        newExpression->setRight(std::make_shared<Expression>(OR), newExpression);
        newExpression->getRight()->setLeft(left, newExpression->getRight());
        newExpression->getRight()->setRight(right2, newExpression->getRight());

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::deMorgan(std::shared_ptr<Expression>& expression)
{
    // !(p | q) = !p & !q, !(p & q) = !p | !q
    if (expression->getValue() == NOT)
    {
        if (expression->getLeft()->getValue() == OR)
        {
            std::shared_ptr<Expression> left = expression->getLeft()->getLeft();
            std::shared_ptr<Expression> right = expression->getLeft()->getRight();

            // create a new expression
            std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(AND);
            newExpression->setLeft(std::make_shared<Expression>(NOT), newExpression);
            newExpression->getLeft()->setLeft(left, newExpression->getLeft());
            newExpression->setRight(std::make_shared<Expression>(NOT), newExpression);
            newExpression->getRight()->setLeft(right, newExpression->getRight());

            replace(expression, newExpression);

            return true;
        }
        else if (expression->getLeft()->getValue() == AND)
        {
            std::shared_ptr<Expression> left = expression->getLeft()->getLeft();
            std::shared_ptr<Expression> right = expression->getLeft()->getRight();

            // create a new expression with the left and right subexpressions swapped
            std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(OR);
            newExpression->setLeft(std::make_shared<Expression>(NOT), newExpression);
            newExpression->getLeft()->setLeft(left, newExpression->getLeft());
            newExpression->setRight(std::make_shared<Expression>(NOT), newExpression);
            newExpression->getRight()->setLeft(right, newExpression->getRight());

            replace(expression, newExpression);

            return true;
        }
    }
    return false;
}

bool EquivLaws::deMorganReversed(std::shared_ptr<Expression>& expression)
{
    // !p & !q = !(p | q), !p | !q = !(p & q)
    if (expression->getValue() == AND)
    {
        if (expression->getLeft()->getValue() == NOT && expression->getRight()->getValue() == NOT)
        {
            std::shared_ptr<Expression> left = expression->getLeft()->getLeft();
            std::shared_ptr<Expression> right = expression->getRight()->getLeft();

            // create a new expression
            std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(NOT);
            newExpression->setLeft(std::make_shared<Expression>(OR), newExpression);
            newExpression->getLeft()->setLeft(left, newExpression->getLeft());
            newExpression->getLeft()->setRight(right, newExpression->getLeft());

            replace(expression, newExpression);

            return true;
        }
    }
    else if (expression->getValue() == OR)
    {
        if (expression->getLeft()->getValue() == NOT && expression->getRight()->getValue() == NOT)
        {
            std::shared_ptr<Expression> left = expression->getLeft()->getLeft();
            std::shared_ptr<Expression> right = expression->getRight()->getLeft();

            // create a new expression
            std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(NOT);
            newExpression->setLeft(std::make_shared<Expression>(AND), newExpression);
            newExpression->getLeft()->setLeft(left, newExpression->getLeft());
            newExpression->getLeft()->setRight(right, newExpression->getLeft());

            replace(expression, newExpression);

            return true;
        }
    }
    return false;
}

bool EquivLaws::absorption(std::shared_ptr<Expression>& expression)
{
    // p | (p & q) = p & (p | q) = p
    if (expression->getValue() == OR && expression->getRight()->getValue() == AND || expression->getValue() == AND && expression->getRight()->getValue() == OR)
    {

        replace(expression, expression->getLeft());

        return true;
    }
    return false;
}

bool EquivLaws::negation(std::shared_ptr<Expression>& expression)
{
    // p | !p = T, p & !p = F
    if (expression->getValue() == OR && expression->getRight()->getValue() == NOT)
    {
        std::shared_ptr<Expression> left = expression->getLeft();
        std::shared_ptr<Expression> right = expression->getRight()->getLeft();
        if (!left->compare(right))
            return false;

        // replace the current expression with T
        replace(expression, std::make_shared<Expression>(TRUE));

        return true;
    }
    else if (expression->getValue() == AND && expression->getRight()->getValue() == NOT)
    {
        std::shared_ptr<Expression> left = expression->getLeft();
        std::shared_ptr<Expression> right = expression->getRight()->getLeft();
        if (!left->compare(right))
            return false;

        // replace the current expression with F
        replace(expression, std::make_shared<Expression>(FALSE));

        return true;
    }
    return false;
}

bool EquivLaws::implication0(std::shared_ptr<Expression>& expression)
{
    // p -> q = !p | q
    if (expression->getValue() == IMPLIES)
    {
        std::shared_ptr<Expression> left = expression->getLeft();
        std::shared_ptr<Expression> right = expression->getRight();

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(OR);
        newExpression->setLeft(std::make_shared<Expression>(NOT), newExpression);
        newExpression->getLeft()->setLeft(left, newExpression->getLeft());
        newExpression->setRight(right, newExpression);

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::implication0Reversed(std::shared_ptr<Expression>& expression)
{
    // !p | q = p -> q
    if (expression->getValue() == OR && expression->getLeft()->getValue() == NOT)
    {
        std::shared_ptr<Expression> left = expression->getLeft()->getLeft();
        std::shared_ptr<Expression> right = expression->getRight();

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(IMPLIES);
        newExpression->setLeft(left, newExpression);
        newExpression->setRight(right, newExpression);

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::implication1(std::shared_ptr<Expression>& expression)
{
    // p -> q = !q -> !p
    if (expression->getValue() == IMPLIES)
    {
        std::shared_ptr<Expression> left = expression->getLeft();
        std::shared_ptr<Expression> right = expression->getRight();

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(IMPLIES);
        newExpression->setLeft(std::make_shared<Expression>(NOT), newExpression);
        newExpression->getLeft()->setLeft(right, newExpression->getLeft());
        newExpression->setRight(std::make_shared<Expression>(NOT), newExpression);
        newExpression->getRight()->setLeft(left, newExpression->getRight());

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::implication1Reversed(std::shared_ptr<Expression>& expression)
{
    // !q -> !p = p -> q
    if (expression->getValue() == IMPLIES && expression->getLeft()->getValue() == NOT && expression->getRight()->getValue() == NOT)
    {
        std::shared_ptr<Expression> left = expression->getLeft()->getLeft();
        std::shared_ptr<Expression> right = expression->getRight()->getLeft();

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(IMPLIES);
        newExpression->setLeft(right, newExpression);
        newExpression->setRight(left, newExpression);

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::implication2(std::shared_ptr<Expression>& expression)
{
    // p | q = !p -> q
    if (expression->getValue() == OR)
    {
        std::shared_ptr<Expression> left = expression->getLeft();
        std::shared_ptr<Expression> right = expression->getRight();
        
        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(IMPLIES);
        newExpression->setLeft(std::make_shared<Expression>(NOT), newExpression);
        newExpression->getLeft()->setLeft(left, newExpression->getLeft());
        newExpression->setRight(right, newExpression);

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::implication2Reversed(std::shared_ptr<Expression>& expression)
{
    // !p -> q = p | q
    if (expression->getValue() == IMPLIES && expression->getLeft()->getValue() == NOT)
    {
        std::shared_ptr<Expression> left = expression->getLeft()->getLeft();
        std::shared_ptr<Expression> right = expression->getRight();

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(OR);
        newExpression->setLeft(left, newExpression);
        newExpression->setRight(right, newExpression);

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::implication3(std::shared_ptr<Expression>& expression)
{
    // p & q = !(p -> !q)
    if (expression->getValue() == AND)
    {
        std::shared_ptr<Expression> left = expression->getLeft();
        std::shared_ptr<Expression> right = expression->getRight();

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(NOT);
        newExpression->setLeft(std::make_shared<Expression>(IMPLIES), newExpression);
        newExpression->getLeft()->setLeft(left, newExpression->getLeft());
        newExpression->getLeft()->setRight(std::make_shared<Expression>(NOT), newExpression->getLeft());
        newExpression->getLeft()->getRight()->setLeft(right, newExpression->getLeft()->getRight());

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::implication3Reversed(std::shared_ptr<Expression>& expression)
{
    // !(p -> !q) = p & q
    if (expression->getValue() == NOT && expression->getLeft()->getValue() == IMPLIES && expression->getLeft()->getRight()->getValue() == NOT)
    {
        std::shared_ptr<Expression> left = expression->getLeft()->getLeft();
        std::shared_ptr<Expression> right = expression->getLeft()->getRight()->getLeft();

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(AND);
        newExpression->setLeft(left, newExpression);
        newExpression->setRight(right, newExpression);

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::implication4(std::shared_ptr<Expression>& expression)
{
    // !(p -> q) = p & !q
    if (expression->getValue() == NOT && expression->getLeft()->getValue() == IMPLIES)
    {
        std::shared_ptr<Expression> left = expression->getLeft()->getLeft();
        std::shared_ptr<Expression> right = expression->getLeft()->getRight();

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(AND);
        newExpression->setLeft(left, newExpression);
        newExpression->setRight(std::make_shared<Expression>(NOT), newExpression);
        newExpression->getRight()->setLeft(right, newExpression->getRight());

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::implication4Reversed(std::shared_ptr<Expression>& expression)
{
    // p & !q = !(p -> q)
    if (expression->getValue() == AND && expression->getRight()->getValue() == NOT)
    {
        std::shared_ptr<Expression> left = expression->getLeft();
        std::shared_ptr<Expression> right = expression->getRight()->getLeft();

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(NOT);
        newExpression->setLeft(std::make_shared<Expression>(IMPLIES), newExpression);
        newExpression->getLeft()->setLeft(left, newExpression->getLeft());
        newExpression->getLeft()->setRight(right, newExpression->getLeft());

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::implication5(std::shared_ptr<Expression>& expression)
{
    // (p -> q) & (p -> r) = p -> (q & r)
    if (expression->getValue() == AND && expression->getLeft()->getValue() == IMPLIES && expression->getRight()->getValue() == IMPLIES)
    {
        std::shared_ptr<Expression> left1 = expression->getLeft()->getLeft();
        std::shared_ptr<Expression> left2 = expression->getLeft()->getRight();
        std::shared_ptr<Expression> right1 = expression->getRight()->getLeft();
        std::shared_ptr<Expression> right2 = expression->getRight()->getRight();

        // check if the p's are the same
        if (!left1->compare(right1))
            return false;

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(IMPLIES);
        newExpression->setLeft(left1, newExpression);
        newExpression->setRight(std::make_shared<Expression>(AND), newExpression);
        newExpression->getRight()->setLeft(left2, newExpression->getRight());
        newExpression->getRight()->setRight(right2, newExpression->getRight());

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::implication5Reversed(std::shared_ptr<Expression>& expression)
{
    // p -> (q & r) = (p -> q) & (p -> r)
    if (expression->getValue() == IMPLIES && expression->getRight()->getValue() == AND)
    {
        std::shared_ptr<Expression> left = expression->getLeft();
        std::shared_ptr<Expression> right1 = expression->getRight()->getLeft();
        std::shared_ptr<Expression> right2 = expression->getRight()->getRight();
        
        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(AND);
        newExpression->setLeft(std::make_shared<Expression>(IMPLIES), newExpression);
        newExpression->getLeft()->setLeft(left, newExpression->getLeft());
        newExpression->getLeft()->setRight(right1, newExpression->getLeft());
        newExpression->setRight(std::make_shared<Expression>(IMPLIES), newExpression);
        newExpression->getRight()->setLeft(left, newExpression->getRight());
        newExpression->getRight()->setRight(right2, newExpression->getRight());

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::implication6(std::shared_ptr<Expression>& expression)
{
    // (p -> q) & (q -> r) = (p | q) -> r
    if (expression->getValue() == AND && expression->getLeft()->getValue() == IMPLIES && expression->getRight()->getValue() == IMPLIES)
    {
        std::shared_ptr<Expression> left1 = expression->getLeft()->getLeft();
        std::shared_ptr<Expression> left2 = expression->getLeft()->getRight();
        std::shared_ptr<Expression> right1 = expression->getRight()->getLeft();
        std::shared_ptr<Expression> right2 = expression->getRight()->getRight();

        // check if the q's are the same
        if (!left2->compare(right1))
            return false;

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(IMPLIES);
        newExpression->setLeft(std::make_shared<Expression>(OR), newExpression);
        newExpression->getLeft()->setLeft(left1, newExpression->getLeft());
        newExpression->getLeft()->setRight(left2, newExpression->getLeft());
        newExpression->setRight(right2, newExpression);

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::implication6Reversed(std::shared_ptr<Expression>& expression)
{
    // (p | q) -> r = (p -> q) & (q -> r)
    if (expression->getValue() == IMPLIES && expression->getLeft()->getValue() == OR)
    {
        std::shared_ptr<Expression> left1 = expression->getLeft()->getLeft();
        std::shared_ptr<Expression> left2 = expression->getLeft()->getRight();
        std::shared_ptr<Expression> right = expression->getRight();

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(AND);
        newExpression->setLeft(std::make_shared<Expression>(IMPLIES), newExpression);
        newExpression->getLeft()->setLeft(left1, newExpression->getLeft());
        newExpression->getLeft()->setRight(left2, newExpression->getLeft());
        newExpression->setRight(std::make_shared<Expression>(IMPLIES), newExpression);
        newExpression->getRight()->setLeft(left2, newExpression->getRight());
        newExpression->getRight()->setRight(right, newExpression->getRight());

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::implication7(std::shared_ptr<Expression>& expression)
{
    // (p -> q) | (p -> r) = p -> (q | r)
    if (expression->getValue() == OR && expression->getLeft()->getValue() == IMPLIES && expression->getRight()->getValue() == IMPLIES)
    {
        std::shared_ptr<Expression> left1 = expression->getLeft()->getLeft();
        std::shared_ptr<Expression> left2 = expression->getLeft()->getRight();
        std::shared_ptr<Expression> right1 = expression->getRight()->getLeft();
        std::shared_ptr<Expression> right2 = expression->getRight()->getRight();

        // check if the p's are the same
        if (!left1->compare(right1))
            return false;

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(IMPLIES);
        newExpression->setLeft(left1, newExpression);
        newExpression->setRight(std::make_shared<Expression>(OR), newExpression);
        newExpression->getRight()->setLeft(left2, newExpression->getRight());
        newExpression->getRight()->setRight(right2, newExpression->getRight());

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::implication7Reversed(std::shared_ptr<Expression>& expression)
{
    // p -> (q | r) = (p -> q) | (p -> r)
    if (expression->getValue() == IMPLIES && expression->getRight()->getValue() == OR)
    {
        std::shared_ptr<Expression> left = expression->getLeft();
        std::shared_ptr<Expression> right1 = expression->getRight()->getLeft();
        std::shared_ptr<Expression> right2 = expression->getRight()->getRight();

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(OR);
        newExpression->setLeft(std::make_shared<Expression>(IMPLIES), newExpression);
        newExpression->getLeft()->setLeft(left, newExpression->getLeft());
        newExpression->getLeft()->setRight(right1, newExpression->getLeft());
        newExpression->setRight(std::make_shared<Expression>(IMPLIES), newExpression);
        newExpression->getRight()->setLeft(left, newExpression->getRight());
        newExpression->getRight()->setRight(right2, newExpression->getRight());

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::implication8(std::shared_ptr<Expression>& expression)
{
    // (p -> q) | (q -> r) = (p & q) -> r
    if (expression->getValue() == OR && expression->getLeft()->getValue() == IMPLIES && expression->getRight()->getValue() == IMPLIES)
    {
        std::shared_ptr<Expression> left1 = expression->getLeft()->getLeft();
        std::shared_ptr<Expression> left2 = expression->getLeft()->getRight();
        std::shared_ptr<Expression> right1 = expression->getRight()->getLeft();
        std::shared_ptr<Expression> right2 = expression->getRight()->getRight();

        // check if the q's are the same
        if (!left2->compare(right1))
            return false;
        
        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(IMPLIES);
        newExpression->setLeft(std::make_shared<Expression>(AND), newExpression);
        newExpression->getLeft()->setLeft(left1, newExpression->getLeft());
        newExpression->getLeft()->setRight(left2, newExpression->getLeft());
        newExpression->setRight(right2, newExpression);

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::implication8Reversed(std::shared_ptr<Expression>& expression)
{
    // (p & q) -> r = (p -> q) | (q -> r)
    if (expression->getValue() == IMPLIES && expression->getLeft()->getValue() == AND)
    {
        std::shared_ptr<Expression> left1 = expression->getLeft()->getLeft();
        std::shared_ptr<Expression> left2 = expression->getLeft()->getRight();
        std::shared_ptr<Expression> right = expression->getRight();

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(OR);
        newExpression->setLeft(std::make_shared<Expression>(IMPLIES), newExpression);
        newExpression->getLeft()->setLeft(left1, newExpression->getLeft());
        newExpression->getLeft()->setRight(left2, newExpression->getLeft());
        newExpression->setRight(std::make_shared<Expression>(IMPLIES), newExpression);
        newExpression->getRight()->setLeft(left2, newExpression->getRight());
        newExpression->getRight()->setRight(right, newExpression->getRight());

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::bidirectionalImplication0(std::shared_ptr<Expression>& expression) {
    // p <-> q = (p -> q) & (q -> p)
    if (expression->getValue() == IFF) {
        std::shared_ptr<Expression> left = expression->getLeft();
        std::shared_ptr<Expression> right = expression->getRight();

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(AND);
        newExpression->setLeft(std::make_shared<Expression>(IMPLIES), newExpression);
        newExpression->getLeft()->setLeft(left, newExpression->getLeft());
        newExpression->getLeft()->setRight(right, newExpression->getLeft());
        newExpression->setRight(std::make_shared<Expression>(IMPLIES), newExpression);
        newExpression->getRight()->setLeft(right, newExpression->getRight());
        newExpression->getRight()->setRight(left, newExpression->getRight());

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::bidirectionalImplication0Reversed(std::shared_ptr<Expression>& expression) {
    // (p -> q) & (q -> p) = p <-> q
    if (expression->getValue() == AND && expression->getLeft()->getValue() == IMPLIES && expression->getRight()->getValue() == IMPLIES) {
        std::shared_ptr<Expression> left1 = expression->getLeft()->getLeft();
        std::shared_ptr<Expression> left2 = expression->getLeft()->getRight();
        std::shared_ptr<Expression> right1 = expression->getRight()->getLeft();
        std::shared_ptr<Expression> right2 = expression->getRight()->getRight();

        // check if the q's are the same
        if (!left2->compare(right1))
            return false;

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(IFF);
        newExpression->setLeft(left1, newExpression);
        newExpression->setRight(left2, newExpression);

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::bidirectionalImplication1(std::shared_ptr<Expression>& expression) {
    // p <-> q = q <-> p
    if (expression->getValue() == IFF) {
        std::shared_ptr<Expression> left = expression->getLeft();
        std::shared_ptr<Expression> right = expression->getRight();

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(IFF);
        newExpression->setLeft(right, newExpression);
        newExpression->setRight(left, newExpression);

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::bidirectionalImplication2(std::shared_ptr<Expression>& expression) {
    // p <-> q = !p <-> !q
    if (expression->getValue() == IFF) {
        std::shared_ptr<Expression> left = expression->getLeft();
        std::shared_ptr<Expression> right = expression->getRight();

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(IFF);
        newExpression->setLeft(std::make_shared<Expression>(NOT), newExpression);
        newExpression->getLeft()->setLeft(left, newExpression->getLeft());
        newExpression->setRight(std::make_shared<Expression>(NOT), newExpression);
        newExpression->getRight()->setLeft(right, newExpression->getRight());

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::bidirectionalImplication2Reversed(std::shared_ptr<Expression>& expression) {
    // !p <-> !q = p <-> q
    if (expression->getValue() == IFF && expression->getLeft()->getValue() == NOT && expression->getRight()->getValue() == NOT) {
        std::shared_ptr<Expression> left = expression->getLeft()->getLeft();
        std::shared_ptr<Expression> right = expression->getRight()->getLeft();

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(IFF);
        newExpression->setLeft(left, newExpression);
        newExpression->setRight(right, newExpression);

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::bidirectionalImplication3(std::shared_ptr<Expression>& expression) {
    // p <-> q = (p & q) | (!p & !q)
    if (expression->getValue() == IFF) {
        std::shared_ptr<Expression> left = expression->getLeft();
        std::shared_ptr<Expression> right = expression->getRight();

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(OR);
        newExpression->setLeft(std::make_shared<Expression>(AND), newExpression);
        newExpression->getLeft()->setLeft(left, newExpression->getLeft());
        newExpression->getLeft()->setRight(right, newExpression->getLeft());
        newExpression->setRight(std::make_shared<Expression>(AND), newExpression);
        newExpression->getRight()->setLeft(std::make_shared<Expression>(NOT), newExpression->getRight());
        newExpression->getRight()->getLeft()->setLeft(left, newExpression->getRight()->getLeft());
        newExpression->getRight()->setRight(std::make_shared<Expression>(NOT), newExpression->getRight());
        newExpression->getRight()->getRight()->setLeft(right, newExpression->getRight()->getRight());

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::bidirectionalImplication3Reversed(std::shared_ptr<Expression>& expression) {
    // (p & q) | (!p & !q) = p <-> q
    if (expression->getValue() == OR && expression->getLeft()->getValue() == AND && expression->getRight()->getValue() == AND) {
        std::shared_ptr<Expression> left1 = expression->getLeft()->getLeft();
        std::shared_ptr<Expression> left2 = expression->getLeft()->getRight();
        std::shared_ptr<Expression> right1 = expression->getRight()->getLeft()->getLeft();
        std::shared_ptr<Expression> right2 = expression->getRight()->getRight()->getLeft();

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(IFF);
        newExpression->setLeft(left1, newExpression);
        newExpression->setRight(left2, newExpression);

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::bidirectionalImplication4(std::shared_ptr<Expression>& expression) {
    // !(p <-> q) = p <-> !q
    if (expression->getValue() == NOT && expression->getLeft()->getValue() == IFF) {
        std::shared_ptr<Expression> left = expression->getLeft()->getLeft();
        std::shared_ptr<Expression> right = expression->getLeft()->getRight();

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(IFF);
        newExpression->setLeft(left, newExpression);
        newExpression->setRight(std::make_shared<Expression>(NOT), newExpression);
        newExpression->getRight()->setLeft(right, newExpression->getRight());

        replace(expression, newExpression);

        return true;
    }
    return false;
}

bool EquivLaws::bidirectionalImplication4Reversed(std::shared_ptr<Expression>& expression) {
    // p <-> !q = !(p <-> q)
    if (expression->getValue() == IFF && expression->getRight()->getValue() == NOT) {
        std::shared_ptr<Expression> left = expression->getLeft();
        std::shared_ptr<Expression> right = expression->getRight()->getLeft();

        // create a new expression
        std::shared_ptr<Expression> newExpression = std::make_shared<Expression>(NOT);
        newExpression->setLeft(std::make_shared<Expression>(IFF), newExpression);
        newExpression->getLeft()->setLeft(left, newExpression->getLeft());
        newExpression->getLeft()->setRight(right, newExpression->getLeft());

        replace(expression, newExpression);

        return true;
    }
    return false;
}