#pragma once

#include "expression.h"

// (p & T) = p, (p | F) = p
bool applyIdentity(std::shared_ptr<Expression>); 
bool applyIdentityReversed(std::shared_ptr<Expression>); 

// (p | T) = T, (p & F) = F
bool applyDomination(std::shared_ptr<Expression>); 
bool applyDominationReversed(std::shared_ptr<Expression>); 

// (p | p) = p, (p & p) = p
bool applyIdempotence(std::shared_ptr<Expression>); 
bool applyIdempotenceReversed(std::shared_ptr<Expression>); 

// !!p = p
bool applyDoubleNegation(std::shared_ptr<Expression>);
bool applyDoubleNegationReversed(std::shared_ptr<Expression>);

// p | q = q | p, p & q = q & p
bool applyCommutative(std::shared_ptr<Expression>);
bool applyCommutativeReversed(std::shared_ptr<Expression>);

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
bool applyNegationReversed(std::shared_ptr<Expression>);

// p -> q = !p | q
bool applyImplication0(std::shared_ptr<Expression>);
bool applyImplicationReversed0(std::shared_ptr<Expression>);

// p -> q = !q -> !p
bool applyImplication1(std::shared_ptr<Expression>);
bool applyImplicationReversed1(std::shared_ptr<Expression>);

// p | q = !p -> q
bool applyImplication2(std::shared_ptr<Expression>);
bool applyImplicationReversed2(std::shared_ptr<Expression>);

// p & q = !(p -> !q)
bool applyImplication3(std::shared_ptr<Expression>);
bool applyImplicationReversed3(std::shared_ptr<Expression>);

// !(p -> q) = p & !q
bool applyImplication4(std::shared_ptr<Expression>);
bool applyImplicationReversed4(std::shared_ptr<Expression>);

// (p -> q) & (p -> r) = p -> (q & r)
bool applyImplication5(std::shared_ptr<Expression>);
bool applyImplicationReversed5(std::shared_ptr<Expression>);

// (p -> q) & (q -> r) = (p | q) -> r
bool applyImplication6(std::shared_ptr<Expression>);
bool applyImplicationReversed6(std::shared_ptr<Expression>);

// (p -> q) | (p -> r) = p -> (q | r)
bool applyImplication7(std::shared_ptr<Expression>);
bool applyImplicationReversed7(std::shared_ptr<Expression>);

// (p -> q) | (r -> q) = (p & r) -> q
bool applyImplication8(std::shared_ptr<Expression>);
bool applyImplicationReversed8(std::shared_ptr<Expression>);

// p <-> q = (p -> q) & (q -> p)
bool applyBidirectionalImplication0(std::shared_ptr<Expression>);
bool applyBidirectionalImplicationReversed0(std::shared_ptr<Expression>);

// p <-> q = q <-> p
bool applyBidirectionalImplication1(std::shared_ptr<Expression>);
bool applyBidirectionalImplicationReversed1(std::shared_ptr<Expression>);

// p <-> q = !p <-> !q
bool applyBidirectionalImplication2(std::shared_ptr<Expression>);
bool applyBidirectionalImplicationReversed2(std::shared_ptr<Expression>);

// p <-> q = (p & q) | (!p & !q)
bool applyBidirectionalImplication3(std::shared_ptr<Expression>);
bool applyBidirectionalImplicationReversed3(std::shared_ptr<Expression>);

// !(p <-> q) = p <-> !q
bool applyBidirectionalImplication4(std::shared_ptr<Expression>);
bool applyBidirectionalImplicationReversed4(std::shared_ptr<Expression>);