#include <gtest/gtest.h>
#include "../include/equivLaws.h"
# include "../include/parser.h"

TEST(EquivLawsTest, IdentityInvalid) {
    std::shared_ptr<Expression> expr;

    parse("p", expr);
    EXPECT_FALSE(EquivLaws::identity(expr));

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::identity(expr));

    parse("p -> T", expr);
    EXPECT_FALSE(EquivLaws::identity(expr));

    parse("p <=> F", expr);
    EXPECT_FALSE(EquivLaws::identity(expr));

    parse("q & F", expr);
    EXPECT_FALSE(EquivLaws::identity(expr));

    parse("q | T", expr);
    EXPECT_FALSE(EquivLaws::identity(expr));
}

TEST(EquivLawsTest, IdentitySimple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("p & T", expr);
    EXPECT_TRUE(EquivLaws::identity(expr));
    parse("p", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("p | F", expr);
    EXPECT_TRUE(EquivLaws::identity(expr));
    parse("p", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, IdentityComplex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p & T) | (q | F)", expr);
    EXPECT_FALSE(EquivLaws::identity(expr));
    EXPECT_TRUE(EquivLaws::identity(expr->getLeft()));
    parse("p | (q | F)", expected);
    EXPECT_TRUE(expr->compare(expected));
    EXPECT_FALSE(EquivLaws::identity(expr));
    EXPECT_TRUE(EquivLaws::identity(expr->getRight()));
    parse("p | q", expected);
    EXPECT_TRUE(expr->compare(expected));
    EXPECT_FALSE(EquivLaws::identity(expr));

    parse("(p & q) & T", expr);
    EXPECT_TRUE(EquivLaws::identity(expr));
    parse("p & q", expected);
    EXPECT_TRUE(expr->compare(expected));
    EXPECT_FALSE(EquivLaws::identity(expr));
}

TEST(EquivLawsTest, DominationInvalid) {
    std::shared_ptr<Expression> expr;

    parse("p", expr);
    EXPECT_FALSE(EquivLaws::domination(expr));

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::domination(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::domination(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::domination(expr));

    parse("p&q", expr);
    EXPECT_FALSE(EquivLaws::domination(expr));

    parse("p->T", expr);
    EXPECT_FALSE(EquivLaws::domination(expr));

    parse("p&T", expr);
    EXPECT_FALSE(EquivLaws::domination(expr));

    parse("p|F", expr);
    EXPECT_FALSE(EquivLaws::domination(expr));
}

TEST(EquivLawsTest, DominationSimple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("p|T", expr);
    EXPECT_TRUE(EquivLaws::domination(expr));
    parse("T", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("p&F", expr);
    EXPECT_TRUE(EquivLaws::domination(expr));
    parse("F", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("q|T", expr);
    EXPECT_TRUE(EquivLaws::domination(expr));
    parse("T", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("q&F", expr);
    EXPECT_TRUE(EquivLaws::domination(expr));
    parse("F", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, DominationComplex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p|T)&(q&F)", expr);
    EXPECT_FALSE(EquivLaws::domination(expr));
    EXPECT_TRUE(EquivLaws::domination(expr->getLeft()));
    parse("T&(q&F)", expected);
    EXPECT_TRUE(expr->compare(expected));
    EXPECT_FALSE(EquivLaws::domination(expr));
    EXPECT_TRUE(EquivLaws::domination(expr->getRight()));
    parse("T&F", expected);
    EXPECT_TRUE(expr->compare(expected));
    EXPECT_TRUE(EquivLaws::domination(expr));
    parse("F", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, IdempotentInvalid) {
    std::shared_ptr<Expression> expr;

    parse("p", expr);
    EXPECT_FALSE(EquivLaws::idempotent(expr));

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::idempotent(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::idempotent(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::idempotent(expr));

    parse("p&q", expr);
    EXPECT_FALSE(EquivLaws::idempotent(expr));

    parse("p->T", expr);
    EXPECT_FALSE(EquivLaws::idempotent(expr));

    parse("p&T", expr);
    EXPECT_FALSE(EquivLaws::idempotent(expr));

    parse("p|F", expr);
    EXPECT_FALSE(EquivLaws::idempotent(expr));

    parse("p&F", expr);
    EXPECT_FALSE(EquivLaws::idempotent(expr));
}

TEST(EquivLawsTest, IdempotentSimple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("p|p", expr);
    EXPECT_TRUE(EquivLaws::idempotent(expr));
    parse("p", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("r&r", expr);
    EXPECT_TRUE(EquivLaws::idempotent(expr));
    parse("r", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, IdempotentComplex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p|p)&(r&r)", expr);
    EXPECT_FALSE(EquivLaws::idempotent(expr));
    EXPECT_TRUE(EquivLaws::idempotent(expr->getLeft()));
    parse("p&(r&r)", expected);
    EXPECT_TRUE(expr->compare(expected));
    EXPECT_FALSE(EquivLaws::idempotent(expr));
    EXPECT_TRUE(EquivLaws::idempotent(expr->getRight()));
    parse("p&r", expected);
    EXPECT_TRUE(expr->compare(expected));
    EXPECT_FALSE(EquivLaws::idempotent(expr));

    parse("(p|p)&(p&p)", expr);
    EXPECT_FALSE(EquivLaws::idempotent(expr));
    EXPECT_TRUE(EquivLaws::idempotent(expr->getLeft()));
    parse("p&(p&p)", expected);
    EXPECT_TRUE(expr->compare(expected));
    EXPECT_FALSE(EquivLaws::idempotent(expr));
    EXPECT_TRUE(EquivLaws::idempotent(expr->getRight()));
    parse("p&p", expected);
    EXPECT_TRUE(expr->compare(expected));
    EXPECT_TRUE(EquivLaws::idempotent(expr));
    parse("p", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, DoubleNegationInvalid) {
    std::shared_ptr<Expression> expr;

    parse("p", expr);
    EXPECT_FALSE(EquivLaws::doubleNegation(expr));

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::doubleNegation(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::doubleNegation(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::doubleNegation(expr));

    parse("p&q", expr);
    EXPECT_FALSE(EquivLaws::doubleNegation(expr));

    parse("p->T", expr);
    EXPECT_FALSE(EquivLaws::doubleNegation(expr));

    parse("p&T", expr);
    EXPECT_FALSE(EquivLaws::doubleNegation(expr));

    parse("p|F", expr);
    EXPECT_FALSE(EquivLaws::doubleNegation(expr));

    parse("p&F", expr);
    EXPECT_FALSE(EquivLaws::doubleNegation(expr));
}

TEST(EquivLawsTest, DoubleNegationSimple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("!!p", expr);
    EXPECT_TRUE(EquivLaws::doubleNegation(expr));
    parse("p", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("!!(r)", expr);
    EXPECT_TRUE(EquivLaws::doubleNegation(expr));
    parse("r", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, DoubleNegationComplex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("!!(!!p)", expr);
    EXPECT_TRUE(EquivLaws::doubleNegation(expr));
    parse("!!p", expected);
    EXPECT_TRUE(expr->compare(expected));
    EXPECT_TRUE(EquivLaws::doubleNegation(expr));
    parse("p", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("(!!(!!p))", expr);
    EXPECT_TRUE(EquivLaws::doubleNegation(expr->getLeft()));
    parse("!!p", expected);
    EXPECT_TRUE(expr->compare(expected));
    EXPECT_TRUE(EquivLaws::doubleNegation(expr));
    parse("p", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("!!(r & !!p)", expr);
    EXPECT_TRUE(EquivLaws::doubleNegation(expr));
    parse("r & !!p", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, CommutativeInvalid) {
    std::shared_ptr<Expression> expr;

    parse("p", expr);
    EXPECT_FALSE(EquivLaws::commutative(expr));

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::commutative(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::commutative(expr));

    parse("p->q->r", expr);
    EXPECT_FALSE(EquivLaws::commutative(expr));
}

TEST(EquivsLawTest, CommutativeSimple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("p|q", expr);
    EXPECT_TRUE(EquivLaws::commutative(expr));
    parse("q|p", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("p&q", expr);
    EXPECT_TRUE(EquivLaws::commutative(expr));
    parse("q&p", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivsLawTest, CommutativeComplex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p&q)|(q&r)", expr);
    EXPECT_TRUE(EquivLaws::commutative(expr));
    parse("(q&r)|(p&q)", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("(p|q)&(q&r)", expr);
    EXPECT_TRUE(EquivLaws::commutative(expr->getLeft()));
    parse("(q|p)&(q&r)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, AssociativeInvalid) {
    std::shared_ptr<Expression> expr;

    parse("p", expr);
    EXPECT_FALSE(EquivLaws::associative(expr));

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::associative(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::associative(expr));

    parse("p->q->r", expr);
    EXPECT_FALSE(EquivLaws::associative(expr));
}

TEST(EquivsLawTest, AssociativeSimple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p|q)|r", expr);
    EXPECT_TRUE(EquivLaws::associative(expr));
    parse("p|(q|r)", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("(p&q)&r", expr);
    EXPECT_TRUE(EquivLaws::associative(expr));
    parse("p&(q&r)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivsLawTest, AssociativeComplex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("((p|q)&r)&s", expr);
    EXPECT_TRUE(EquivLaws::associative(expr));
    parse("(p|q)&(r&s)", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("((p&q)|r)|s", expr);
    EXPECT_TRUE(EquivLaws::associative(expr));
    parse("(p&q)|(r|s)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivsLawTest, AssociativeReversedInvalid) {
    std::shared_ptr<Expression> expr;
    
    parse("p", expr);
    EXPECT_FALSE(EquivLaws::associativeReversed(expr));

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::associativeReversed(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::associativeReversed(expr));

    parse("p->q->r", expr);
    EXPECT_FALSE(EquivLaws::associativeReversed(expr));
}

TEST(EquivsLawTest, AssociativeReversedSimple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("p|(q|r)", expr);
    EXPECT_TRUE(EquivLaws::associativeReversed(expr));
    parse("(p|q)|r", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("p&(q&r)", expr);
    EXPECT_TRUE(EquivLaws::associativeReversed(expr));
    parse("(p&q)&r", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivsLawTest, AssociativeReversedComplex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p|q)&(r&s)", expr);
    EXPECT_TRUE(EquivLaws::associativeReversed(expr));
    parse("((p|q)&r)&s", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("(p&q)|(r|s)", expr);
    EXPECT_TRUE(EquivLaws::associativeReversed(expr));
    parse("((p&q)|r)|s", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, DistributiveInvalid) {
    std::shared_ptr<Expression> expr;

    parse("p", expr);
    EXPECT_FALSE(EquivLaws::distributive(expr));

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::distributive(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::distributive(expr));

    parse("p->q->r", expr);
    EXPECT_FALSE(EquivLaws::distributive(expr));
}

TEST(EquivsLawTest, DistributiveSimple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("p&(q|r)", expr);
    EXPECT_TRUE(EquivLaws::distributive(expr));
    parse("(p&q)|(p&r)", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("p|(q&r)", expr);
    EXPECT_TRUE(EquivLaws::distributive(expr));
    parse("(p|q)&(p|r)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivsLawTest, DistributiveComplex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p|q)&(r|s)", expr);
    EXPECT_TRUE(EquivLaws::distributive(expr));
    parse("((p|q)&r)|((p|q)&s)", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("(p&q)|(r&s)", expr);
    EXPECT_TRUE(EquivLaws::distributive(expr));
    parse("((p&q)|r)&((p&q)|s)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivsLawTest, DistributiveReversedInvalid) {
    std::shared_ptr<Expression> expr;

    parse("p", expr);
    EXPECT_FALSE(EquivLaws::distributiveReversed(expr));

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::distributiveReversed(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::distributiveReversed(expr));

    parse("p->q->r", expr);
    EXPECT_FALSE(EquivLaws::distributiveReversed(expr));
}

TEST(EquivsLawTest, DistributiveReversedSimple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p&q)|(p&r)", expr);
    EXPECT_TRUE(EquivLaws::distributiveReversed(expr));
    parse("p&(q|r)", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("(p|q)&(p|r)", expr);
    EXPECT_TRUE(EquivLaws::distributiveReversed(expr));
    parse("p|(q&r)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivsLawTest, DistributiveReversedComplex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("((p|q)&r)|((p|q)&s)", expr);
    EXPECT_TRUE(EquivLaws::distributiveReversed(expr));
    parse("(p|q)&(r|s)", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("((p&q)|r)&((p&q)|s)", expr);
    EXPECT_TRUE(EquivLaws::distributiveReversed(expr));
    parse("(p&q)|(r&s)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, DeMorganInvalid) {
    std::shared_ptr<Expression> expr;

    parse("p", expr);
    EXPECT_FALSE(EquivLaws::deMorgan(expr));

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::deMorgan(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::deMorgan(expr));

    parse("p->q->r", expr);
    EXPECT_FALSE(EquivLaws::deMorgan(expr));
}

TEST(EquivsLawTest, DeMorganSimple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("!(p&q)", expr);
    EXPECT_TRUE(EquivLaws::deMorgan(expr));
    parse("!p|!q", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("!(p|q)", expr);
    EXPECT_TRUE(EquivLaws::deMorgan(expr));
    parse("!p&!q", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTestt, DeMorganComplex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("!((p|q)&(r|s))", expr);
    EXPECT_TRUE(EquivLaws::deMorgan(expr));
    parse("(!(p|q))|(!(r|s))", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("!((p&q)|(r&s))", expr);
    EXPECT_TRUE(EquivLaws::deMorgan(expr));
    parse("(!(p&q))&(!(r&s))", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, DeMorganReversedInvalid) {
    std::shared_ptr<Expression> expr;

    parse("p", expr);
    EXPECT_FALSE(EquivLaws::deMorganReversed(expr));

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::deMorganReversed(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::deMorganReversed(expr));

    parse("p->q->r", expr);
    EXPECT_FALSE(EquivLaws::deMorganReversed(expr));
}

TEST(EquivsLawTest, DeMorganReversedSimple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("!p|!q", expr);
    EXPECT_TRUE(EquivLaws::deMorganReversed(expr));
    parse("!(p&q)", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("!p&!q", expr);
    EXPECT_TRUE(EquivLaws::deMorganReversed(expr));
    parse("!(p|q)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, DeMorganReversedComplex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(!(p|q))|(!(r|s))", expr);
    EXPECT_TRUE(EquivLaws::deMorganReversed(expr));
    parse("!((p|q)&(r|s))", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("(!(p&q))&(!(r&s))", expr);
    EXPECT_TRUE(EquivLaws::deMorganReversed(expr));
    parse("!((p&q)|(r&s))", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, AbsorptionInvalid) {
    std::shared_ptr<Expression> expr;

    parse("p", expr);
    EXPECT_FALSE(EquivLaws::absorption(expr));

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::absorption(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::absorption(expr));

    parse("p->q->r", expr);
    EXPECT_FALSE(EquivLaws::absorption(expr));
}

TEST(EquivLawsTest, AbsorptionSimple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("p&(p|q)", expr);
    EXPECT_TRUE(EquivLaws::absorption(expr));
    parse("p", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("p|(p&q)", expr);
    EXPECT_TRUE(EquivLaws::absorption(expr));
    parse("p", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, AbsorptionComplex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p|q)|((p|q)&r)", expr);
    EXPECT_TRUE(EquivLaws::absorption(expr));
    parse("p|q", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("(p&q|s)&((p&q|s)|r)", expr);
    EXPECT_TRUE(EquivLaws::absorption(expr));
    parse("p&q|s", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, NegationInvalid) {
    std::shared_ptr<Expression> expr;

    parse("p", expr);
    EXPECT_FALSE(EquivLaws::negation(expr));

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::negation(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::negation(expr));

    parse("p->q->r", expr);
    EXPECT_FALSE(EquivLaws::negation(expr));
}

TEST(EquivLawsTest, NegationSimple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("p | !p", expr);
    EXPECT_TRUE(EquivLaws::negation(expr));
    parse("T", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("p & !p", expr);
    EXPECT_TRUE(EquivLaws::negation(expr));
    parse("F", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, NegationComplex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(q | p) | !(q | p)", expr);
    EXPECT_TRUE(EquivLaws::negation(expr));
    parse("T", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("(q & p) & !(q & p)", expr);
    EXPECT_TRUE(EquivLaws::negation(expr));
    parse("F", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("((q & p) & !(q & p)) & !((q & p) & !(q & p))", expr);
    EXPECT_TRUE(EquivLaws::negation(expr));
    parse("F", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication0Invalid) {
    std::shared_ptr<Expression> expr;

    parse("p", expr);
    EXPECT_FALSE(EquivLaws::implication0(expr));

    parse("p&q", expr);
    EXPECT_FALSE(EquivLaws::implication0(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::implication0(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::implication0(expr));

    parse("p<=>q<=>r", expr);
    EXPECT_FALSE(EquivLaws::implication0(expr));
}

TEST(EquivLawsTest, Implication0Simple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("p->q", expr);
    EXPECT_TRUE(EquivLaws::implication0(expr));
    parse("!p|q", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication0Complex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p->q)->r", expr);
    EXPECT_TRUE(EquivLaws::implication0(expr));
    parse("!(p->q)|r", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("((p->q)->r)->(s & t)", expr);
    EXPECT_TRUE(EquivLaws::implication0(expr));
    parse("!(p->q->r)|(s & t)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication0ReversedInvalid) {
    std::shared_ptr<Expression> expr;

    parse("p", expr);
    EXPECT_FALSE(EquivLaws::implication0Reversed(expr));

    parse("p&q", expr);
    EXPECT_FALSE(EquivLaws::implication0Reversed(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::implication0Reversed(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::implication0Reversed(expr));

    parse("p<=>q<=>r", expr);
    EXPECT_FALSE(EquivLaws::implication0Reversed(expr));
}

TEST(EquivLawsTest, Implication0ReversedSimple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("!p|q", expr);
    EXPECT_TRUE(EquivLaws::implication0Reversed(expr));
    parse("p->q", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication0ReversedComplex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("!(p->q)|r", expr);
    EXPECT_TRUE(EquivLaws::implication0Reversed(expr));
    parse("(p->q)->r", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("!(p->q->r)|(s & t)", expr);
    EXPECT_TRUE(EquivLaws::implication0Reversed(expr));
    parse("((p->q)->r)->(s & t)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication1Invalid) {
    std::shared_ptr<Expression> expr;

    parse("p", expr);
    EXPECT_FALSE(EquivLaws::implication1(expr));

    parse("p&q", expr);
    EXPECT_FALSE(EquivLaws::implication1(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::implication1(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::implication1(expr));

    parse("p<=>q<=>r", expr);
    EXPECT_FALSE(EquivLaws::implication1(expr));
}

TEST(EquivLawsTest, Implication1Simple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("p->q", expr);
    EXPECT_TRUE(EquivLaws::implication1(expr));
    parse("!q->!p", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication1Complex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p->q)->r", expr);
    EXPECT_TRUE(EquivLaws::implication1(expr));
    parse("!(r)->!(p->q)", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("((p->q)->r)->(s & t)", expr);
    EXPECT_TRUE(EquivLaws::implication1(expr));
    parse("!(s & t)->!((p->q)->r)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication1ReversedInvalid) {
    std::shared_ptr<Expression> expr;

    parse("p", expr);
    EXPECT_FALSE(EquivLaws::implication1Reversed(expr));

    parse("p&q", expr);
    EXPECT_FALSE(EquivLaws::implication1Reversed(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::implication1Reversed(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::implication1Reversed(expr));

    parse("p<=>q<=>r", expr);
    EXPECT_FALSE(EquivLaws::implication1Reversed(expr));
}

TEST(EquivLawsTest, Implication1ReversedSimple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("!q->!p", expr);
    EXPECT_TRUE(EquivLaws::implication1Reversed(expr));
    parse("p->q", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication1ReversedComplex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("!(r)->!(p->q)", expr);
    EXPECT_TRUE(EquivLaws::implication1Reversed(expr));
    parse("(p->q)->r", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("!(s & t)->!((p->q)->r)", expr);
    EXPECT_TRUE(EquivLaws::implication1Reversed(expr));
    parse("((p->q)->r)->(s & t)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication2Invalid) {
    std::shared_ptr<Expression> expr;

    parse("p", expr);
    EXPECT_FALSE(EquivLaws::implication2(expr));

    parse("p&q", expr);
    EXPECT_FALSE(EquivLaws::implication2(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::implication2(expr));

    parse("p<=>q<=>r", expr);
    EXPECT_FALSE(EquivLaws::implication2(expr));
}

TEST(EquivLawsTest, Implication2Simple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("p|q", expr);
    EXPECT_TRUE(EquivLaws::implication2(expr));
    parse("!p->q", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication2Complex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p->q)|r", expr);
    EXPECT_TRUE(EquivLaws::implication2(expr));
    parse("!(p->q)->r", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("((p->q)->r)|(s & t)", expr);
    EXPECT_TRUE(EquivLaws::implication2(expr));
    parse("!((p->q)->r)->(s & t)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication2ReversedInvalid) {
    std::shared_ptr<Expression> expr;

    parse("p", expr);
    EXPECT_FALSE(EquivLaws::implication2Reversed(expr));

    parse("p&q", expr);
    EXPECT_FALSE(EquivLaws::implication2Reversed(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::implication2Reversed(expr));

    parse("p<=>q<=>r", expr);
    EXPECT_FALSE(EquivLaws::implication2Reversed(expr));
}

TEST(EquivLawsTest, Implication2ReversedSimple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("!p->q", expr);
    EXPECT_TRUE(EquivLaws::implication2Reversed(expr));
    parse("p|q", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication2ReversedComplex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("!(p->q)->r", expr);
    EXPECT_TRUE(EquivLaws::implication2Reversed(expr));
    parse("(p->q)|r", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("!((p->q)->r)->(s & t)", expr);
    EXPECT_TRUE(EquivLaws::implication2Reversed(expr));
    parse("((p->q)->r)|(s & t)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication3Invalid) {
    std::shared_ptr<Expression> expr;

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::implication3(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::implication3(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::implication3(expr));

    parse("p<=>q<=>r", expr);
    EXPECT_FALSE(EquivLaws::implication3(expr));
}

TEST(EquivLawsTest, Implication3Simple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("p&q", expr);
    EXPECT_TRUE(EquivLaws::implication3(expr));
    parse("!(p->!q)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication3Complex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p->q)&r", expr);
    EXPECT_TRUE(EquivLaws::implication3(expr));
    parse("!((p->q)->!r)", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("((p->q)->r)&(s|t)", expr);
    EXPECT_TRUE(EquivLaws::implication3(expr));
    parse("!(((p->q)->r)->!(s|t))", expected);
}

TEST(EquivLawsTest, Implication3ReversedInvalid) {
    std::shared_ptr<Expression> expr;

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::implication3Reversed(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::implication3Reversed(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::implication3Reversed(expr));

    parse("p<=>q<=>r", expr);
    EXPECT_FALSE(EquivLaws::implication3Reversed(expr));
}

TEST(EquivLawsTest, Implication3ReversedSimple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("!(p->!q)", expr);
    EXPECT_TRUE(EquivLaws::implication3Reversed(expr));
    parse("p&q", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication3ReversedComplex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("!((p->q)->!r)", expr);
    EXPECT_TRUE(EquivLaws::implication3Reversed(expr));
    parse("(p->q)&r", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("!(((p->q)->r)->!(s|t))", expr);
    EXPECT_TRUE(EquivLaws::implication3Reversed(expr));
    parse("((p->q)->r)&(s|t)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication4Invalid) {
    std::shared_ptr<Expression> expr;

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::implication4(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::implication4(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::implication4(expr));

    parse("p<=>q<=>r", expr);
    EXPECT_FALSE(EquivLaws::implication4(expr));
}

TEST(EquivLawsTest, Implication4Simple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("!(p->q)", expr);
    EXPECT_TRUE(EquivLaws::implication4(expr));
    parse("p&!q", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication4Complex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("!((p->q)->r)", expr);
    EXPECT_TRUE(EquivLaws::implication4(expr));
    parse("(p->q)&!r", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("!(((p->q)->r)->(s|t))", expr);
    EXPECT_TRUE(EquivLaws::implication4(expr));
    parse("((p->q)->r)&!(s|t)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication4ReversedInvalid) {
    std::shared_ptr<Expression> expr;

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::implication4Reversed(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::implication4Reversed(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::implication4Reversed(expr));

    parse("p<=>q<=>r", expr);
    EXPECT_FALSE(EquivLaws::implication4Reversed(expr));
}

TEST(EquivLawsTest, Implication4ReversedSimple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("p&!q", expr);
    EXPECT_TRUE(EquivLaws::implication4Reversed(expr));
    parse("!(p->q)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTestt, Implication4ReversedComplex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p->q)&!r", expr);
    EXPECT_TRUE(EquivLaws::implication4Reversed(expr));
    parse("!((p->q)->r)", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("((p->q)->r)&!(s|t)", expr);
    EXPECT_TRUE(EquivLaws::implication4Reversed(expr));
    parse("!(((p->q)->r)->(s|t))", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication5Invalid) {
    std::shared_ptr<Expression> expr;

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::implication5(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::implication5(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::implication5(expr));

    parse("p<=>q<=>r", expr);
    EXPECT_FALSE(EquivLaws::implication5(expr));
}

TEST(EquivLawsTest, Implication5Simple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p->q)&(p->r)", expr);
    EXPECT_TRUE(EquivLaws::implication5(expr));
    parse("p->(q&r)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication5Complex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("((p->q)->r)&((p->q)->s)", expr);
    EXPECT_TRUE(EquivLaws::implication5(expr));
    parse("(p->q)->(r&s)", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("((p->q)->(r|t))&((p->q)->(s|u))", expr);
    EXPECT_TRUE(EquivLaws::implication5(expr));
    parse("(p->q)->((r|t)&(s|u))", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication5ReversedInvalid) {
    std::shared_ptr<Expression> expr;

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::implication5Reversed(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::implication5Reversed(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::implication5Reversed(expr));

    parse("p<=>q<=>r", expr);
    EXPECT_FALSE(EquivLaws::implication5Reversed(expr));
}

TEST(EquivLawsTest, Implication5ReversedSimple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("p->(q&r)", expr);
    EXPECT_TRUE(EquivLaws::implication5Reversed(expr));
    parse("(p->q)&(p->r)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication5ReversedComplex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p->q)->(r&s)", expr);
    EXPECT_TRUE(EquivLaws::implication5Reversed(expr));
    parse("((p->q)->r)&((p->q)->s)", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("(p->q)->((r|t)&(s|u))", expr);
    EXPECT_TRUE(EquivLaws::implication5Reversed(expr));
    parse("((p->q)->(r|t))&((p->q)->(s|u))", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication6Invalid) {
    std::shared_ptr<Expression> expr;

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::implication6(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::implication6(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::implication6(expr));

    parse("p<=>q<=>r", expr);
    EXPECT_FALSE(EquivLaws::implication6(expr));

    parse("(p->(r->s))&(r->t)", expr);
    EXPECT_FALSE(EquivLaws::implication6(expr));
}

TEST(EquivLawsTest, Implication6Simple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p->q)&(q->r)", expr);
    EXPECT_TRUE(EquivLaws::implication6(expr));
    parse("(p|q)->r", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication6Complex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("((p->q)->(r->s))&((r->s)->(t->u))", expr);
    EXPECT_TRUE(EquivLaws::implication6(expr));
    parse("((p->q)|(r->s))->(t->u)", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("(p->(r->s))&((r->s)->t)", expr);
    EXPECT_TRUE(EquivLaws::implication6(expr));
    parse("(p|(r->s))->t", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication6ReversedInvalid) {
    std::shared_ptr<Expression> expr;

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::implication6Reversed(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::implication6Reversed(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::implication6Reversed(expr));

    parse("p<=>q<=>r", expr);
    EXPECT_FALSE(EquivLaws::implication6Reversed(expr));

    parse("(p->q)&r", expr);
    EXPECT_FALSE(EquivLaws::implication6Reversed(expr));
}

TEST(EquivLawsTest, Implication6ReversedSimple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p|q)->r", expr);
    EXPECT_TRUE(EquivLaws::implication6Reversed(expr));
    parse("(p->q)&(q->r)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication6ReversedComplex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("((p->q)|(r->s))->(t->u)", expr);
    EXPECT_TRUE(EquivLaws::implication6Reversed(expr));
    parse("((p->q)->(r->s))&((r->s)->(t->u))", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("(p|(r->s))->t", expr);
    EXPECT_TRUE(EquivLaws::implication6Reversed(expr));
    parse("(p->(r->s))&((r->s)->t)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication7Invalid) {
    std::shared_ptr<Expression> expr;

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::implication7(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::implication7(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::implication7(expr));

    parse("p<=>q<=>r", expr);
    EXPECT_FALSE(EquivLaws::implication7(expr));

    parse("(p->(r->s))&(r->t)", expr);
    EXPECT_FALSE(EquivLaws::implication7(expr));
}

TEST(EquivLawsTest, Implication7Simple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p->q)|(p->r)", expr);
    EXPECT_TRUE(EquivLaws::implication7(expr));
    parse("p->(q|r)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication7Complex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("((p->q)->(r->s))|((p->q)->(r->u))", expr);
    EXPECT_TRUE(EquivLaws::implication7(expr));
    parse("(p->q)->((r->s)|(r->u))", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("(p->(r->s))|(p->((r->s)->t))", expr);
    EXPECT_TRUE(EquivLaws::implication7(expr));
    parse("p->((r->s)|((r->s)->t))", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication7ReversedInvalid) {
    std::shared_ptr<Expression> expr;

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::implication7Reversed(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::implication7Reversed(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::implication7Reversed(expr));

    parse("p<=>q<=>r", expr);
    EXPECT_FALSE(EquivLaws::implication7Reversed(expr));

    parse("(p->q)|(r->t)", expr);
    EXPECT_FALSE(EquivLaws::implication7Reversed(expr));
}

TEST(EquivLawsTest, Implication7ReversedSimple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("p->(q|r)", expr);
    EXPECT_TRUE(EquivLaws::implication7Reversed(expr));
    parse("(p->q)|(p->r)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication7ReversedComplex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p->q)->((r->s)|(r->u))", expr);
    EXPECT_TRUE(EquivLaws::implication7Reversed(expr));
    parse("((p->q)->(r->s))|((p->q)->(r->u))", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("p->((r->s)|((r->s)->t))", expr);
    EXPECT_TRUE(EquivLaws::implication7Reversed(expr));
    parse("(p->(r->s))|(p->((r->s)->t))", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication8Invalid) {
    std::shared_ptr<Expression> expr;

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::implication8(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::implication8(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::implication8(expr));

    parse("p<=>q<=>r", expr);
    EXPECT_FALSE(EquivLaws::implication8(expr));

    parse("(p->(r->s))|(t->(r->s))", expr);
    EXPECT_FALSE(EquivLaws::implication8(expr));
}

TEST(EquivLawsTest, Implication8Simple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p->q)|(q->r)", expr);
    EXPECT_TRUE(EquivLaws::implication8(expr));
    parse("(p&q)->r", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication8Complex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("((p->q)->(r->s))|((r->s)->(t->u))", expr);
    EXPECT_TRUE(EquivLaws::implication8(expr));
    parse("((p->q)&(r->s))->(t->u)", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("(p->(r->s))|((r->s)->(s->t))", expr);
    EXPECT_TRUE(EquivLaws::implication8(expr));
    parse("(p&(r->s))->(s->t)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication8ReversedInvalid) {
    std::shared_ptr<Expression> expr;

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::implication8Reversed(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::implication8Reversed(expr));

    parse("p<=>q", expr);
    EXPECT_FALSE(EquivLaws::implication8Reversed(expr));

    parse("p<=>q<=>r", expr);
    EXPECT_FALSE(EquivLaws::implication8Reversed(expr));

    parse("(p->q)|(r->t)", expr);
    EXPECT_FALSE(EquivLaws::implication8Reversed(expr));
}

TEST(EquivLawsTest, Implication8ReversedSimple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p&q)->r", expr);
    EXPECT_TRUE(EquivLaws::implication8Reversed(expr));
    parse("(p->q)|(q->r)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, Implication8ReversedComplex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("((p->q)&(r->s))->(t->u)", expr);
    EXPECT_TRUE(EquivLaws::implication8Reversed(expr));
    parse("((p->q)->(r->s))|((r->s)->(t->u))", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, BidirectionalImplication0Invalid) {
    std::shared_ptr<Expression> expr;

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication0(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication0(expr));

    parse("p&q", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication0(expr));

    parse("(p->q)|(r->t)", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication0(expr));
}

TEST(EquivLawsTest, BidirectionalImplication0Simple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("p<=>q", expr);
    EXPECT_TRUE(EquivLaws::bidirectionalImplication0(expr));
    parse("(p->q)&(q->p)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, BidirectionalImplication0Complex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p<=>q)<=>(r<=>s)", expr);
    EXPECT_TRUE(EquivLaws::bidirectionalImplication0(expr));
    parse("((p<=>q)->(r<=>s))&((r<=>s)->(p<=>q))", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("(p<=>(q<=>r))", expr);
    EXPECT_TRUE(EquivLaws::bidirectionalImplication0(expr));
    parse("(p->(q<=>r))&((q<=>r)->p)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, BidirectionalImplication0ReversedInvalid) {
    std::shared_ptr<Expression> expr;

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication0Reversed(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication0Reversed(expr));

    parse("p&q", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication0Reversed(expr));

    parse("(p->q)|(r->t)", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication0Reversed(expr));
}

TEST(EquivLawsTest, BidirectionalImplication0ReversedSimple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p->q)&(q->p)", expr);
    EXPECT_TRUE(EquivLaws::bidirectionalImplication0Reversed(expr));
    parse("p<=>q", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, BidirectionalImplication0ReversedComplex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("((p<=>q)->(r<=>s))&((r<=>s)->(p<=>q))", expr);
    EXPECT_TRUE(EquivLaws::bidirectionalImplication0Reversed(expr));
    parse("(p<=>q)<=>(r<=>s)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, BidirectionalImplication1Invalid) {
    std::shared_ptr<Expression> expr;

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication1(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication1(expr));

    parse("p&q", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication1(expr));

    parse("(p->q)|(r->t)", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication1(expr));
}

TEST(EquivLawsTest, BidirectionalImplication1Simple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("p<=>q", expr);
    EXPECT_TRUE(EquivLaws::bidirectionalImplication1(expr));
    parse("q<=>p", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, BidirectionalImplication1Complex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p<=>q)<=>(r<=>s)", expr);
    EXPECT_TRUE(EquivLaws::bidirectionalImplication1(expr));
    parse("(r<=>s)<=>(p<=>q)", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("(p<=>(q<=>r))", expr);
    EXPECT_TRUE(EquivLaws::bidirectionalImplication1(expr));
    parse("(q<=>r)<=>p", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, BidirectionalImplication2Invalid) {
    std::shared_ptr<Expression> expr;

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication2(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication2(expr));

    parse("p&q", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication2(expr));

    parse("(p->q)|(r->t)", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication2(expr));
}

TEST(EquivLawsTest, BidirectionalImplication2Simple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("p<=>q", expr);
    EXPECT_TRUE(EquivLaws::bidirectionalImplication2(expr));
    parse("!p<=>!q", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, BidirectionalImplication2Complex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p<=>q)<=>(r<=>s)", expr);
    EXPECT_TRUE(EquivLaws::bidirectionalImplication2(expr));
    parse("!(p<=>q)<=>!(r<=>s)", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("(p<=>(q<=>r))", expr);
    EXPECT_TRUE(EquivLaws::bidirectionalImplication2(expr));
    parse("(!p<=>!(q<=>r))", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, BidirectionalImplication2ReversedInvalid) {
    std::shared_ptr<Expression> expr;

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication2Reversed(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication2Reversed(expr));

    parse("p&q", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication2Reversed(expr));

    parse("(p->q)|(r->t)", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication2Reversed(expr));
}

TEST(EquivLawsTest, BidirectionalImplication2ReversedSimple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("!p<=>!q", expr);
    EXPECT_TRUE(EquivLaws::bidirectionalImplication2Reversed(expr));
    parse("p<=>q", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, BidirectionalImplication2ReversedComplex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("!(p<=>q)<=>!(r<=>s)", expr);
    EXPECT_TRUE(EquivLaws::bidirectionalImplication2Reversed(expr));
    parse("(p<=>q)<=>(r<=>s)", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("(!p<=>!(q<=>r))", expr);
    EXPECT_TRUE(EquivLaws::bidirectionalImplication2Reversed(expr));
    parse("(p<=>(q<=>r))", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, BidirectionalImplication3Invalid) {
    std::shared_ptr<Expression> expr;

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication3(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication3(expr));

    parse("p&q", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication3(expr));

    parse("(p->q)|(r->t)", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication3(expr));
}

TEST(EquivLawsTest, BidirectionalImplication3Simple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("p<=>q", expr);
    EXPECT_TRUE(EquivLaws::bidirectionalImplication3(expr));
    parse("(p&q)|(!p&!q)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, BidirectionalImplication3Complex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p<=>q)<=>(r<=>s)", expr);
    EXPECT_TRUE(EquivLaws::bidirectionalImplication3(expr));
    parse("((p<=>q)&(r<=>s))|(!(p<=>q)&!(r<=>s))", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("(p<=>(q<=>r))", expr);
    EXPECT_TRUE(EquivLaws::bidirectionalImplication3(expr));
    parse("(p&(q<=>r))|(!p&!(q<=>r))", expected);
}

TEST(EquivLawsTest, BidirectionalImplication3ReversedInvalid) {
    std::shared_ptr<Expression> expr;

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication3Reversed(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication3Reversed(expr));

    parse("p&q", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication3Reversed(expr));

    parse("(p->q)|(r->t)", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication3Reversed(expr));
}

TEST(EquivLawsTest, BidirectionalImplication3ReversedSimple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p&q)|(!p&!q)", expr);
    EXPECT_TRUE(EquivLaws::bidirectionalImplication3Reversed(expr));
    parse("p<=>q", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, BidirectionalImplication3ReversedComplex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("((p<=>q)&(r<=>s))|(!(p<=>q)&!(r<=>s))", expr);
    EXPECT_TRUE(EquivLaws::bidirectionalImplication3Reversed(expr));
    parse("(p<=>q)<=>(r<=>s)", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("(p&(q<=>r))|(!p&!(q<=>r))", expr);
    EXPECT_TRUE(EquivLaws::bidirectionalImplication3Reversed(expr));
    parse("(p<=>(q<=>r))", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, BidirectionalImplication4Invalid) {
    std::shared_ptr<Expression> expr;

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication4(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication4(expr));

    parse("p&q", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication4(expr));

    parse("(p->q)|(r->t)", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication4(expr));
}

TEST(EquivLawsTest, BidirectionImplication4Simple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("!(p<=>q)", expr);
    EXPECT_TRUE(EquivLaws::bidirectionalImplication4(expr));
    parse("p<=>!q", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, BidirectionalImplication4Complex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("!((p<=>q)<=>(r<=>s))", expr);
    EXPECT_TRUE(EquivLaws::bidirectionalImplication4(expr));
    parse("(p<=>q)<=>!(r<=>s)", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("!(p<=>(q<=>r))", expr);
    EXPECT_TRUE(EquivLaws::bidirectionalImplication4(expr));
    parse("(p<=>!(q<=>r))", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, BidirectionalImplication4ReversedInvalid) {
    std::shared_ptr<Expression> expr;

    parse("p->q", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication4Reversed(expr));

    parse("p|q", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication4Reversed(expr));

    parse("p&q", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication4Reversed(expr));

    parse("(p->q)|(r->t)", expr);
    EXPECT_FALSE(EquivLaws::bidirectionalImplication4Reversed(expr));
}

TEST(EquivLawsTest, BidirectionImplication4ReversedSimple) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("p<=>!q", expr);
    EXPECT_TRUE(EquivLaws::bidirectionalImplication4Reversed(expr));
    parse("!(p<=>q)", expected);
    EXPECT_TRUE(expr->compare(expected));
}

TEST(EquivLawsTest, BidirectionalImplication4ReversedComplex) {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<Expression> expected;

    parse("(p<=>q)<=>!(r<=>s)", expr);
    EXPECT_TRUE(EquivLaws::bidirectionalImplication4Reversed(expr));
    parse("!((p<=>q)<=>(r<=>s))", expected);
    EXPECT_TRUE(expr->compare(expected));

    parse("(p<=>!(q<=>r))", expr);
    EXPECT_TRUE(EquivLaws::bidirectionalImplication4Reversed(expr));
    parse("!(p<=>(q<=>r))", expected);
    EXPECT_TRUE(expr->compare(expected));
}