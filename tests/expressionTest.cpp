#include <gtest/gtest.h>
#include "../include/expression.h"

TEST(ExpressionTest, GetValue) {
    std::shared_ptr<Expression> expr = std::make_shared<Expression>("p");
    EXPECT_EQ("p", expr->getValue());
}

TEST(ExpressionTest, HasLeft) {
    std::shared_ptr<Expression> expr = std::make_shared<Expression>("&");
    EXPECT_FALSE(expr->hasLeft());

    expr->setLeft(std::make_shared<Expression>("p"), expr);
    EXPECT_TRUE(expr->hasLeft());
}

TEST(ExpressionTest, HasRight) {
    std::shared_ptr<Expression> expr = std::make_shared<Expression>("&");
    EXPECT_FALSE(expr->hasRight());

    expr->setRight(std::make_shared<Expression>("q"), expr);
    EXPECT_TRUE(expr->hasRight());
}

TEST(ExpressionTest, IsBinary) {
    std::shared_ptr<Expression> expr1 = std::make_shared<Expression>("p");
    EXPECT_FALSE(expr1->isBinary());

    std::shared_ptr<Expression> expr2 = std::make_shared<Expression>("&");
    EXPECT_FALSE(expr2->isBinary());

    expr2->setLeft(std::make_shared<Expression>("p"), expr2);
    EXPECT_FALSE(expr2->isBinary());

    expr2->setRight(std::make_shared<Expression>("q"), expr2);
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

TEST(ExpressionTest, GetParent) {
    std::shared_ptr<Expression> expr1 = std::make_shared<Expression>("&");
    EXPECT_EQ(nullptr, expr1->getParent());

    std::shared_ptr<Expression> expr2 = std::make_shared<Expression>("&");
    std::shared_ptr<Expression> expr2Left = std::make_shared<Expression>("p");
    std::shared_ptr<Expression> expr2Right = std::make_shared<Expression>("q");
    expr2->setLeft(expr2Left, expr2);
    expr2->setRight(expr2Right, expr2);
    EXPECT_EQ(nullptr, expr2->getParent());
    EXPECT_EQ(expr2, expr2Left->getParent());
    EXPECT_EQ(expr2, expr2Right->getParent());
}

TEST(ExpressionTest, GetLeft) {
    std::shared_ptr<Expression> expr1 = std::make_shared<Expression>("&");
    EXPECT_EQ(nullptr, expr1->getLeft());

    std::shared_ptr<Expression> expr2 = std::make_shared<Expression>("&");
    std::shared_ptr<Expression> expr2Left = std::make_shared<Expression>("p");
    std::shared_ptr<Expression> expr2Right = std::make_shared<Expression>("q");
    expr2->setLeft(expr2Left, expr2);
    expr2->setRight(expr2Right, expr2);
    EXPECT_EQ("p", expr2->getLeft()->getValue());
}

TEST(ExpressionTest, GetRight) {
    std::shared_ptr<Expression> expr1 = std::make_shared<Expression>("&");
    EXPECT_EQ(nullptr, expr1->getRight());

    std::shared_ptr<Expression> expr2 = std::make_shared<Expression>("&");
    std::shared_ptr<Expression> expr2Left = std::make_shared<Expression>("p");
    std::shared_ptr<Expression> expr2Right = std::make_shared<Expression>("q");
    expr2->setLeft(expr2Left, expr2);
    expr2->setRight(expr2Right, expr2);
    EXPECT_EQ("q", expr2->getRight()->getValue());
}

TEST(ExpressionTest, SetLeft) {
    std::shared_ptr<Expression> expr1 = std::make_shared<Expression>("&");
    EXPECT_EQ(nullptr, expr1->getLeft());

    expr1->setLeft(std::make_shared<Expression>("p"), expr1);
    EXPECT_EQ("p", expr1->getLeft()->getValue());
}

TEST(ExpressionTest, SetRight) {
    std::shared_ptr<Expression> expr1 = std::make_shared<Expression>("&");
    EXPECT_EQ(nullptr, expr1->getRight());

    expr1->setRight(std::make_shared<Expression>("q"), expr1);
    EXPECT_EQ("q", expr1->getRight()->getValue());
}

TEST(ExpressionTest, SetParent) {
    std::shared_ptr<Expression> expr1 = std::make_shared<Expression>("&");
    EXPECT_EQ(nullptr, expr1->getParent());

    expr1->setParent(std::make_shared<Expression>("p"));
    EXPECT_EQ("p", expr1->getParent()->getValue());
}

TEST(ExpressionTest, GetVariables) {
    std::shared_ptr<Expression> expr1 = std::make_shared<Expression>("p");
    std::set<std::string> expectedVars1 = {"p"};
    EXPECT_EQ(expectedVars1, expr1->getVariables());

    std::shared_ptr<Expression> expr2 = std::make_shared<Expression>("&");
    expr2->setLeft(std::make_shared<Expression>("p"), expr2);
    expr2->setRight(std::make_shared<Expression>("q"), expr2);
    std::set<std::string> expectedVars2 = {"p", "q"};
    EXPECT_EQ(expectedVars2, expr2->getVariables());

    std::shared_ptr<Expression> expr3 = std::make_shared<Expression>("!");
    expr3->setLeft(std::make_shared<Expression>("p"), expr3);
    std::set<std::string> expectedVars3 = {"p"};
    EXPECT_EQ(expectedVars3, expr3->getVariables());
}

TEST(ExpressionTest, Clone) {
    std::shared_ptr<Expression> expr1 = std::make_shared<Expression>("p");
    std::shared_ptr<Expression> expr1Clone = expr1->clone();
    EXPECT_EQ(expr1->getValue(), expr1Clone->getValue());

    std::shared_ptr<Expression> expr2 = std::make_shared<Expression>("&");
    expr2->setLeft(std::make_shared<Expression>("p"), expr2);
    expr2->setRight(std::make_shared<Expression>("q"), expr2);
    std::shared_ptr<Expression> expr2Clone = expr2->clone();
    EXPECT_EQ(expr2->getValue(), expr2Clone->getValue());
    EXPECT_EQ(expr2->getLeft()->getValue(), expr2Clone->getLeft()->getValue());
    EXPECT_EQ(expr2->getRight()->getValue(), expr2Clone->getRight()->getValue());
}

TEST(ExpressionTest, Compare) {
    std::shared_ptr<Expression> expr1 = std::make_shared<Expression>("p");
    std::shared_ptr<Expression> expr2 = std::make_shared<Expression>("p");
    EXPECT_TRUE(expr1->compare(expr2));

    std::shared_ptr<Expression> expr3 = std::make_shared<Expression>("p");
    std::shared_ptr<Expression> expr4 = std::make_shared<Expression>("q");
    EXPECT_FALSE(expr3->compare(expr4));

    std::shared_ptr<Expression> expr5 = std::make_shared<Expression>("&");
    expr5->setLeft(std::make_shared<Expression>("p"), expr5);
    expr5->setRight(std::make_shared<Expression>("q"), expr5);
    std::shared_ptr<Expression> expr6 = std::make_shared<Expression>("&");
    expr6->setLeft(std::make_shared<Expression>("p"), expr6);
    expr6->setRight(std::make_shared<Expression>("q"), expr6);
    EXPECT_TRUE(expr5->compare(expr6));
}