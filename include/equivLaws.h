/**
 * @file equivLaws.h
 * @brief Header file for equivalence laws functions
 */

#pragma once

#include "expression.h"

// Equivalence Laws
// Only pass in a cloned copy of the expression as
// this will modify the expression tree

// (p & T) = p, (p | F) = p
bool applyIdentity(std::shared_ptr<Expression>); 

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
bool applyAssociativeReversed(std::shared_ptr<Expression>);

// p | (q & r) = (p | q) & (p | r), p & (q | r) = (p & q) | (p & r)
bool applyDistributive(std::shared_ptr<Expression>);
bool applyDistributiveReversed(std::shared_ptr<Expression>);

// !(p | q) = !p & !q, !(p & q) = !p | !q
bool applyDeMorgan(std::shared_ptr<Expression>);
bool applyDeMorganReversed(std::shared_ptr<Expression>);

// p | (p & q) = p, p & (p | q) = p
bool applyAbsorption(std::shared_ptr<Expression>);
bool applyAbsorptionReversed(std::shared_ptr<Expression>);

// p | !p = T, p & !p = F
bool applyNegation(std::shared_ptr<Expression>);

// p -> q = !p | q
bool applyImplication0(std::shared_ptr<Expression>);
bool applyImplicationReversed0(std::shared_ptr<Expression>);

// p -> q = !q -> !p
bool applyImplication1(std::shared_ptr<Expression>);
bool applyImplication1Reversed(std::shared_ptr<Expression>);

// p | q = !p -> q
bool applyImplication2(std::shared_ptr<Expression>);
bool applyImplication2Reversed(std::shared_ptr<Expression>);

// p & q = !(p -> !q)
bool applyImplication3(std::shared_ptr<Expression>);
bool applyImplication3Reversed(std::shared_ptr<Expression>);

// !(p -> q) = p & !q
bool applyImplication4(std::shared_ptr<Expression>);
bool applyImplication4Reversed(std::shared_ptr<Expression>);

// (p -> q) & (p -> r) = p -> (q & r)
bool applyImplication5(std::shared_ptr<Expression>);
bool applyImplication5Reversed(std::shared_ptr<Expression>);

// (p -> q) & (q -> r) = (p | q) -> r
bool applyImplication6(std::shared_ptr<Expression>);
bool applyImplication6Reversed(std::shared_ptr<Expression>);

// (p -> q) | (p -> r) = p -> (q | r)
bool applyImplication7(std::shared_ptr<Expression>);
bool applyImplication7Reversed(std::shared_ptr<Expression>);

// (p -> q) | (r -> q) = (p & r) -> q
bool applyImplication8(std::shared_ptr<Expression>);
bool applyImplication8Reversed(std::shared_ptr<Expression>);

// p <-> q = (p -> q) & (q -> p)
bool applyBidirectionalImplication0(std::shared_ptr<Expression>);
bool applyBidirectionalImplication0Reversed(std::shared_ptr<Expression>);

// p <-> q = q <-> p
bool applyBidirectionalImplication1(std::shared_ptr<Expression>);
bool applyBidirectionalImplication1Reversed(std::shared_ptr<Expression>);

// p <-> q = !p <-> !q
bool applyBidirectionalImplication2(std::shared_ptr<Expression>);
bool applyBidirectionalImplication2Reversed(std::shared_ptr<Expression>);

// p <-> q = (p & q) | (!p & !q)
bool applyBidirectionalImplication3(std::shared_ptr<Expression>);
bool applyBidirectionalImplication3Reversed(std::shared_ptr<Expression>);

// !(p <-> q) = p <-> !q
bool applyBidirectionalImplication4(std::shared_ptr<Expression>);
bool applyBidirectionalImplication4Reversed(std::shared_ptr<Expression>);