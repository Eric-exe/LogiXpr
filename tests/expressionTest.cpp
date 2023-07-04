#include <gtest/gtest.h>
#include "../include/expression.h"

TEST(ExpressionTest, GetValue) {
    std::shared_ptr<Expression> expr = std::make_shared<Expression>("p");
    EXPECT_EQ("p", expr->getValue());
}

TEST(ExpressionTest, HasLeft) {
    std::shared_ptr<Expression> expr = std::make_shared<Expression>("&");
    EXPECT_FALSE(expr->hasLeft());

    expr->setLeft(std::make_shared<Expression>("p"));
    EXPECT_TRUE(expr->hasLeft());
}

TEST(ExpressionTest, HasRight) {
    std::shared_ptr<Expression> expr = std::make_shared<Expression>("&");
    EXPECT_FALSE(expr->hasRight());

    expr->setRight(std::make_shared<Expression>("q"));
    EXPECT_TRUE(expr->hasRight());
}

TEST(ExpressionTest, IsBinary) {
    std::shared_ptr<Expression> expr1 = std::make_shared<Expression>("p");
    EXPECT_FALSE(expr1->isBinary());

    std::shared_ptr<Expression> expr2 = std::make_shared<Expression>("&");
    EXPECT_FALSE(expr2->isBinary());

    expr2->setLeft(std::make_shared<Expression>("p"));
    EXPECT_FALSE(expr2->isBinary());

    expr2->setRight(std::make_shared<Expression>("q"));
    EXPECT_TRUE(expr2->isBinary());
}

TEST(ExpressionTest, IsVar) {
    std::shared_ptr<Expression> expr1 = std::make_shared<Expression>("p");
    EXPECT_TRUE(expr1->isVar());

    std::shared_ptr<Expression> expr2 = std::make_shared<Expression>("&");
    EXPECT_FALSE(expr2->isVar());

    std::shared_ptr<Expression> expr3 = std::make_shared<Expression>("P");
    EXPECT_FALSE(expr3->isVar());

    std::shared_ptr<Expression> expr4 = std::make_shared<Expression>("pq");
    EXPECT_FALSE(expr4->isVar());
}

TEST(ExpressionTest, GetLeft) {
    std::shared_ptr<Expression> expr1 = std::make_shared<Expression>("&");
    EXPECT_EQ(nullptr, expr1->getLeft());

    std::shared_ptr<Expression> expr2 = std::make_shared<Expression>("&", std::make_shared<Expression>("p"), std::make_shared<Expression>("q"));
    EXPECT_EQ("p", expr2->getLeft()->getValue());
}

TEST(ExpressionTest, GetRight) {
    std::shared_ptr<Expression> expr1 = std::make_shared<Expression>("&");
    EXPECT_EQ(nullptr, expr1->getRight());

    std::shared_ptr<Expression> expr2 = std::make_shared<Expression>("&", std::make_shared<Expression>("p"), std::make_shared<Expression>("q"));
    EXPECT_EQ("q", expr2->getRight()->getValue());
}

TEST(ExpressionTest, SetLeft) {
    std::shared_ptr<Expression> expr1 = std::make_shared<Expression>("&");
    EXPECT_EQ(nullptr, expr1->getLeft());

    expr1->setLeft(std::make_shared<Expression>("p"));
    EXPECT_EQ("p", expr1->getLeft()->getValue());
}

TEST(ExpressionTest, SetRight) {
    std::shared_ptr<Expression> expr1 = std::make_shared<Expression>("&");
    EXPECT_EQ(nullptr, expr1->getRight());

    expr1->setRight(std::make_shared<Expression>("q"));
    EXPECT_EQ("q", expr1->getRight()->getValue());
}

TEST(ExpressionTest, GetVariables) {
    std::shared_ptr<Expression> expr1 = std::make_shared<Expression>("p");
    std::set<std::string> expectedVars1 = {"p"};
    EXPECT_EQ(expectedVars1, expr1->getVariables());

    std::shared_ptr<Expression> expr2 = std::make_shared<Expression>("&", std::make_shared<Expression>("p"), std::make_shared<Expression>("q"));
    std::set<std::string> expectedVars2 = {"p", "q"};
    EXPECT_EQ(expectedVars2, expr2->getVariables());

    std::shared_ptr<Expression> expr3 = std::make_shared<Expression>("!", nullptr, std::make_shared<Expression>("p"));
    std::set<std::string> expectedVars3 = {"p"};
    EXPECT_EQ(expectedVars3, expr3->getVariables());
}