#include <gtest/gtest.h>
#include "../include/evaluator.h"
# include "../include/parser.h"

TEST(EvaluatorTest, GetTruthTableInputsOneVarEach) {
    std::shared_ptr<Expression> lhs;
    parse("p", lhs);

    std::shared_ptr<Expression> rhs;
    parse("q", rhs);

    std::vector<std::unordered_map<std::string, bool>> expectedInputs = {
        {{"p", false}, {"q", false}},
        {{"p", true}, {"q", false}},
        {{"p", false}, {"q", true}},
        {{"p", true}, {"q", true}}
    };
    EXPECT_EQ(expectedInputs, getTruthTableInputs(lhs, rhs));
}

TEST(EvaluatorTest, GetTruthTableInputsTwoVarEach) {
    std::shared_ptr<Expression> lhs;
    parse("p & q", lhs);

    std::shared_ptr<Expression> rhs;
    parse("r & s", rhs);

    std::vector<std::unordered_map<std::string, bool>> expectedInputs = {
        {{"p", false}, {"q", false}, {"r", false}, {"s", false}},
        {{"p", true}, {"q", false}, {"r", false}, {"s", false}},
        {{"p", false}, {"q", true}, {"r", false}, {"s", false}},
        {{"p", true}, {"q", true}, {"r", false}, {"s", false}},
        {{"p", false}, {"q", false}, {"r", true}, {"s", false}},
        {{"p", true}, {"q", false}, {"r", true}, {"s", false}},
        {{"p", false}, {"q", true}, {"r", true}, {"s", false}},
        {{"p", true}, {"q", true}, {"r", true}, {"s", false}},
        {{"p", false}, {"q", false}, {"r", false}, {"s", true}},
        {{"p", true}, {"q", false}, {"r", false}, {"s", true}},
        {{"p", false}, {"q", true}, {"r", false}, {"s", true}},
        {{"p", true}, {"q", true}, {"r", false}, {"s", true}},
        {{"p", false}, {"q", false}, {"r", true}, {"s", true}},
        {{"p", true}, {"q", false}, {"r", true}, {"s", true}},
        {{"p", false}, {"q", true}, {"r", true}, {"s", true}},
        {{"p", true}, {"q", true}, {"r", true}, {"s", true}}
    };
    EXPECT_EQ(expectedInputs, getTruthTableInputs(lhs, rhs));
}

TEST(EvaluatorTest, GetTruthTableInputsMixedVars) {
    std::shared_ptr<Expression> lhs;
    parse("p & q", lhs);

    std::shared_ptr<Expression> rhs;
    parse("q | r", rhs);

    std::vector<std::unordered_map<std::string, bool>> expectedInputs = {
        {{"p", false}, {"q", false}, {"r", false}},
        {{"p", true}, {"q", false}, {"r", false}},
        {{"p", false}, {"q", true}, {"r", false}},
        {{"p", true}, {"q", true}, {"r", false}},
        {{"p", false}, {"q", false}, {"r", true}},
        {{"p", true}, {"q", false}, {"r", true}},
        {{"p", false}, {"q", true}, {"r", true}},
        {{"p", true}, {"q", true}, {"r", true}}
    };
    EXPECT_EQ(expectedInputs, getTruthTableInputs(lhs, rhs));
}

TEST(EvaluatorTest, EvaluateExpressionOneVar) {
    std::shared_ptr<Expression> expr;
    parse("p", expr);
    std::unordered_map<std::string, bool> inputs1 = {{"p", false}};
    std::unordered_map<std::string, bool> inputs2 = {{"p", true}};
    EXPECT_FALSE(evaluateExpression(expr, inputs1));
    EXPECT_TRUE(evaluateExpression(expr, inputs2));
}

TEST(EvaluatorTest, EvaluateExpressionTwoVars) {
    std::shared_ptr<Expression> expr;
    parse("p & q", expr);

    std::unordered_map<std::string, bool> inputs1 = {{"p", false}, {"q", false}};
    std::unordered_map<std::string, bool> inputs2 = {{"p", true}, {"q", false}};
    std::unordered_map<std::string, bool> inputs3 = {{"p", false}, {"q", true}};
    std::unordered_map<std::string, bool> inputs4 = {{"p", true}, {"q", true}};

    EXPECT_FALSE(evaluateExpression(expr, inputs1));
    EXPECT_FALSE(evaluateExpression(expr, inputs2));
    EXPECT_FALSE(evaluateExpression(expr, inputs3));
    EXPECT_TRUE(evaluateExpression(expr, inputs4));
}

TEST(EvaluatorTest, EvaluateExpressionComplex) {
    std::shared_ptr<Expression> expr;
    parse("p & (q | r)", expr);

    std::unordered_map<std::string, bool> inputs1 = {{"p", false}, {"q", false}, {"r", false}};
    std::unordered_map<std::string, bool> inputs2 = {{"p", true}, {"q", false}, {"r", false}};
    std::unordered_map<std::string, bool> inputs3 = {{"p", false}, {"q", true}, {"r", false}};
    std::unordered_map<std::string, bool> inputs4 = {{"p", true}, {"q", true}, {"r", false}};
    std::unordered_map<std::string, bool> inputs5 = {{"p", false}, {"q", false}, {"r", true}};
    std::unordered_map<std::string, bool> inputs6 = {{"p", true}, {"q", false}, {"r", true}};
    std::unordered_map<std::string, bool> inputs7 = {{"p", false}, {"q", true}, {"r", true}};
    std::unordered_map<std::string, bool> inputs8 = {{"p", true}, {"q", true}, {"r", true}};

    EXPECT_FALSE(evaluateExpression(expr, inputs1));
    EXPECT_FALSE(evaluateExpression(expr, inputs2));
    EXPECT_FALSE(evaluateExpression(expr, inputs3));
    EXPECT_TRUE(evaluateExpression(expr, inputs4));
    EXPECT_FALSE(evaluateExpression(expr, inputs5));
    EXPECT_TRUE(evaluateExpression(expr, inputs6));
    EXPECT_FALSE(evaluateExpression(expr, inputs7));
    EXPECT_TRUE(evaluateExpression(expr, inputs8));
}

TEST(EvaluatorTest, IsEquivalentSameVars) {
    std::shared_ptr<Expression> lhs;
    parse("p & q", lhs);

    std::shared_ptr<Expression> rhs;
    parse("q & p", rhs);
    EXPECT_TRUE(isEquivalent(lhs, rhs));
}

TEST(EvaluatorTest, IsEquivalentDeMorgansLaw) {
    std::shared_ptr<Expression> lhs;
    parse("!(p & q)", lhs);

    std::shared_ptr<Expression> rhs;
    parse("!p | !q", rhs);

    EXPECT_TRUE(isEquivalent(lhs, rhs));
}

TEST(EvaluatorTest, IsEquivalentContraposition) {
    std::shared_ptr<Expression> lhs;
    parse("p -> q", lhs);

    std::shared_ptr<Expression> rhs;
    parse("!q -> !p", rhs);

    EXPECT_TRUE(isEquivalent(lhs, rhs));
}