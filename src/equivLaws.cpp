/**
 * @file equivLaws.cpp
 * @brief Implementation file for equivalence laws functions
 */

#include "../include/equivLaws.h"

// (p & T) = p, (p | F) = p
bool applyIdentity(std::shared_ptr<Expression> expression) {
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

// (p | T) = T, (p & F) = F
bool applyDomination(std::shared_ptr<Expression>); 

// (p | p) = p, (p & p) = p
bool applyIdempotence(std::shared_ptr<Expression>); 

// !!p = p
bool applyDoubleNegation(std::shared_ptr<Expression>);

// p | q = q | p, p & q = q & p
bool applyCommutative(std::shared_ptr<Expression>);

// (p | q) | r = p | (q | r), (p & q) & r = p & (q & r)
bool applyAssociative(std::shared_ptr<Expression>);

// p | (q & r) = (p | q) & (p | r), p & (q | r) = (p & q) | (p & r)
bool applyDistributive(std::shared_ptr<Expression>);

// !(p | q) = !p & !q, !(p & q) = !p | !q
bool applyDeMorgan(std::shared_ptr<Expression>);

// p | (p & q) = p, p & (p | q) = p
bool applyAbsorption(std::shared_ptr<Expression>);

// p | !p = T, p & !p = F
bool applyNegation(std::shared_ptr<Expression>);

// p -> q = !p | q
bool applyImplication0(std::shared_ptr<Expression>);

// p -> q = !q -> !p
bool applyImplication1(std::shared_ptr<Expression>);

// p | q = !p -> q
bool applyImplication2(std::shared_ptr<Expression>);

// p & q = !(p -> !q)
bool applyImplication3(std::shared_ptr<Expression>);

// !(p -> q) = p & !q
bool applyImplication4(std::shared_ptr<Expression>);

// (p -> q) & (p -> r) = p -> (q & r)
bool applyImplication5(std::shared_ptr<Expression>);

// (p -> q) & (q -> r) = (p | q) -> r
bool applyImplication6(std::shared_ptr<Expression>);

// (p -> q) | (p -> r) = p -> (q | r)
bool applyImplication7(std::shared_ptr<Expression>);

// (p -> q) | (r -> q) = (p & r) -> q
bool applyImplication8(std::shared_ptr<Expression>);

// p <-> q = (p -> q) & (q -> p)
bool applyBidirectionalImplication0(std::shared_ptr<Expression>);

// p <-> q = q <-> p
bool applyBidirectionalImplication1(std::shared_ptr<Expression>);

// p <-> q = !p <-> !q
bool applyBidirectionalImplication2(std::shared_ptr<Expression>);

// p <-> q = (p & q) | (!p & !q)
bool applyBidirectionalImplication3(std::shared_ptr<Expression>);

// !(p <-> q) = p <-> !q
bool applyBidirectionalImplication4(std::shared_ptr<Expression>);