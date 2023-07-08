/**
 * @file equivLaws.h
 * @brief Header file for equivalence laws class
 */

#pragma once

#include <unordered_map>
#include "expression.h"

/**
 * @brief Class that handles equivalence laws
 */
class EquivLaws
{
public:

    /**
     * @brief Function pointer type for an equivalence law
     * 
     * @param expr the expression to apply the law to
     * 
     * @return bool of whether the law was applied
     */
    typedef bool (*EquivLaw)(std::shared_ptr<Expression>&);

    /**
     * @brief Map of equivalence laws to their string representations
     */
    static std::unordered_map<EquivLaw, std::string> laws;

    /**
     * @brief Map of implication equivalences to their string representations
     */
    static std::unordered_map<EquivLaw, std::string> implications;

    /**
     * @brief Map of biimplication equivalences to their string representations
     */
    static std::unordered_map<EquivLaw, std::string> bidirectionalImplications;

    /**
     * @brief Replace the current expression with the new expression
     * 
     * @param expression pointer to original expression
     * @param newExpression pointer to expression to replace with
     */
    static void replace(std::shared_ptr<Expression>& expression, std::shared_ptr<Expression> newExpression);
    
    /**
     * @brief Applies the identity law \n
     * (p & T) = p, (p | F) = p
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether the identity law was applied
     */
    static bool identity(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies the domination law \n
     * (p | T) = T, (p & F) = F
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether the domination law was applied
     */
    static bool domination(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies the idempotent law \n
     * (p | p) = p, (p & p) = p
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether the idempotence law was applied
     */
    static bool idempotent(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies the double negation law \n
     * !!p = p
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether the double negation law was applied
     */
    static bool doubleNegation(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies the commutative law \n
     * (p | q) = (q | p), (p & q) = (q & p)
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether the commutative law was applied
     */
    static bool commutative(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies the associative law \n
     * (p | q) | r = p | (q | r), (p & q) & r = p & (q & r)
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether the associative law was applied
     */
    static bool associative(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies associative() but reversed \n
     * p | (q | r) = (p | q) | r, p & (q & r) = (p & q) & r
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether the associative law was applied
     *
     * @see associative()
     */
    static bool associativeReversed(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies distributive law \n
     * p | (q & r) = (p | q) & (p | r), p & (q | r) = (p & q) | (p & r)
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether the distributive law was applied
     */
    static bool distributive(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies distributive() but reversed \n
     * (p | q) & (p | r) = p | (q & r), (p & q) | (p & r) = p & (q | r)
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether the distributive law was applied
     *
     * @see distributive()
     */
    static bool distributiveReversed(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies De Morgan's law \n
     * !(p | q) = !p & !q, !(p & q) = !p | !q
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether De Morgan's law was applied
     */
    static bool deMorgan(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies deMorgan() but reversed \n
     * !p & !q = !(p | q), !p | !q = !(p & q)
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether De Morgan's law was applied
     *
     * @see deMorgan()
     */
    static bool deMorganReversed(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies the absorption law \n
     * p | (p & q) = p, p & (p | q) = p
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether the absorption law was applied
     */
    static bool absorption(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies the negation law \n
     * p | !p = T, p & !p = F
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether the negation law was applied
     */
    static bool negation(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies implication: p -> q = !p | q
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether implication was applied
     */
    static bool implication0(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies implication0() but reversed \n
     * !p | q = p -> q
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether implication was applied
     *
     * @see implication0()
     */
    static bool implication0Reversed(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies implication: p -> q = !q -> !p
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether implication was applied
     */
    static bool implication1(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies implication1() but reversed \n
     * !q -> !p = p -> q
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether implication was applied
     */
    static bool implication1Reversed(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies implication: p | q = !p -> q
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether implication was applied
     */
    static bool implication2(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies implication2() but reversed \n
     * !p -> q = p | q
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether implication was applied
     *
     * @see implication2()
     */
    static bool implication2Reversed(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies implication: p & q = !(p -> !q)
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether implication was applied
     */
    static bool implication3(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies implication3() but reversed \n
     * !(p -> !q) = p & q
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether implication was applied
     *
     * @see implication3()
     */
    static bool implication3Reversed(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies implication: !(p -> q) = p & !q
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether implication was applied
     */
    static bool implication4(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies implication4() but reversed \n
     * p & !q = !(p -> q)
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether implication was applied
     *
     * @see implication4()
     */
    static bool implication4Reversed(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies implication: (p -> q) & (p -> r) = p -> (q & r)
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether implication was applied
     */
    static bool implication5(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies implication5() but reversed \n
     * p -> (q & r) = (p -> q) & (p -> r)
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether implication was applied
     *
     * @see implication5()
     */
    static bool implication5Reversed(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies implication: (p -> q) & (q -> r) = (p | q) -> r
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether implication was applied
     */
    static bool implication6(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies implication6() but reversed \n
     * (p | q) -> r = (p -> q) & (q -> r)
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether implication was applied
     *
     * @see implication6()
     */
    static bool implication6Reversed(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies implication: (p -> q) | (p -> r) = p -> (q | r)
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether implication was applied
     */
    static bool implication7(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies implication7() but reversed \n
     * p -> (q | r) = (p -> q) | (p -> r)
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether implication was applied
     *
     * @see implication7()
     */
    static bool implication7Reversed(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies implication: (p -> q) | (q -> r) = (p & q) -> r
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether implication was applied
     */
    static bool implication8(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies implication8() but reversed \n
     * (p & q) -> r = (p -> q) | (q -> r)
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether implication was applied
     *
     * @see implication8()
     */
    static bool implication8Reversed(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies bidirectional implication: p <-> q = (p -> q) & (q -> p)
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether implication was applied
     */
    static bool bidirectionalImplication0(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies bidirectionalImplication0() but reversed \n
     * (p -> q) & (q -> p) = p <-> q
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether implication was applied
     *
     * @see bidirectionalImplication0()
     */
    static bool bidirectionalImplication0Reversed(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies bidirectional implication: p <-> q = q <-> p
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether implication was applied
     */
    static bool bidirectionalImplication1(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies bidirectional implication: p <-> q = !p <-> !q
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether implication was applied
     */
    static bool bidirectionalImplication2(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies bidirectionalImplication2() but reversed \n
     * !p <-> !q = p <-> q
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether implication was applied
     *
     * @see bidirectionalImplication2()
     */
    static bool bidirectionalImplication2Reversed(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies bidirectional implication: p <-> q = (p & q) | (!p & !q)
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether implication was applied
     */
    static bool bidirectionalImplication3(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies bidirectionalImplication3() but reversed \n
     * (p & q) | (!p & !q) = p <-> q
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether implication was applied
     *
     * @see bidirectionalImplication3()
     */
    static bool bidirectionalImplication3Reversed(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies bidirectional implication: !(p <-> q) = p <-> !q
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether implication was applied
     */
    static bool bidirectionalImplication4(std::shared_ptr<Expression>& expression);

    /**
     * @brief Applies bidirectionalImplication4() but reversed \n
     * p <-> !q = !(p <-> q)
     *
     * @param expression pointer to the current expression
     *
     * @return bool of whether implication was applied
     *
     * @see bidirectionalImplication4()
     */
    static bool bidirectionalImplication4Reversed(std::shared_ptr<Expression>& expression);
};
