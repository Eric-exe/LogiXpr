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

    parse("p <-> F", expr);
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

    parse("p<->q", expr);
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

    parse("p<->q", expr);
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

    parse("p<->q", expr);
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

    parse("p<->q", expr);
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

    parse("p<->q", expr);
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

    parse("p<->q", expr);
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

    parse("(p|q)&(r|s)", expr);
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

    parse("p<->q", expr);
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

    parse("p<->q", expr);
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