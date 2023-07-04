#include <gtest/gtest.h>
#include "../include/parser.h"

TEST(ParserTest, TokenizeSimple) {
    std::string expression = "p & q";
    std::vector<std::string> expectedTokens = {"p", "&", "q"};
    std::vector<std::string> actualTokens = tokenize(expression);
    EXPECT_EQ(expectedTokens, actualTokens);
}

TEST(ParserTest, TokenizeEmptyString) {
    std::string expression = "";
    std::vector<std::string> expectedTokens = {};
    std::vector<std::string> actualTokens = tokenize(expression);
    EXPECT_EQ(expectedTokens, actualTokens);
}

TEST(ParserTest, TokenizeMixedExpression) {
    std::string expression = "p & (q | r)";
    std::vector<std::string> expectedTokens = {"p", "&", "(", "q", "|", "r", ")"};
    std::vector<std::string> actualTokens = tokenize(expression);
    EXPECT_EQ(expectedTokens, actualTokens);
}

TEST(ParserTest, ParseEmptyString) {
    std::string expression = "";
    std::shared_ptr<Expression> root;
    int result = parse(expression, root);
    EXPECT_EQ(1, result);
}

TEST(ParserTest, ParseSingleVariable) {
    std::string expression = "p";
    std::shared_ptr<Expression> root;
    int result = parse(expression, root);
    EXPECT_EQ(0, result);
    EXPECT_EQ("p", root->getValue());
}

TEST(ParserTest, ParseSingleOperator) {
    std::string expression = "&";
    std::shared_ptr<Expression> root;
    int result = parse(expression, root);
    EXPECT_EQ(1, result);
}

TEST(ParserTest, ParseUnaryOperator) {
    std::string expression = "!p";
    std::shared_ptr<Expression> root;
    int result = parse(expression, root);
    EXPECT_EQ(0, result);
    EXPECT_EQ("!", root->getValue());
    EXPECT_EQ("p", root->getLeft()->getValue());
}

TEST(ParserTest, ParseBinaryOperator) {
    std::string expression = "p & q";
    std::shared_ptr<Expression> root;
    int result = parse(expression, root);
    EXPECT_EQ(0, result);
    EXPECT_EQ("&", root->getValue());
    EXPECT_EQ("p", root->getLeft()->getValue());
    EXPECT_EQ("q", root->getRight()->getValue());
}

TEST(ParserTest, ParseMixedExpression) {
    std::string expression = "p & !(q | r)";
    std::shared_ptr<Expression> root;
    int result = parse(expression, root);
    EXPECT_EQ(0, result);
    EXPECT_EQ("&", root->getValue());
    EXPECT_EQ("p", root->getLeft()->getValue());
    EXPECT_EQ("!", root->getRight()->getValue());
    EXPECT_EQ("|", root->getRight()->getLeft()->getValue());
    EXPECT_EQ("q", root->getRight()->getLeft()->getLeft()->getValue());
    EXPECT_EQ("r", root->getRight()->getLeft()->getRight()->getValue());
}