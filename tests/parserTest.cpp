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
    bool result = parse(expression, root);
    EXPECT_FALSE(result);
}

TEST(ParserTest, ParseSingleVariable) {
    std::string expression = "p";
    std::shared_ptr<Expression> root;
    int result = parse(expression, root);
    EXPECT_TRUE(result);
    EXPECT_EQ("p", root->getValue());
}

TEST(ParserTest, ParseSingleOperator) {
    std::string expression = "&";
    std::shared_ptr<Expression> root;
    int result = parse(expression, root);
    EXPECT_FALSE(result);
}

TEST(ParserTest, ParseUnaryOperator) {
    std::string expression = "!p";
    std::shared_ptr<Expression> root;
    int result = parse(expression, root);
    EXPECT_TRUE(result);
    EXPECT_EQ("!", root->getValue());
    EXPECT_EQ("p", root->getLeft()->getValue());
}

TEST(ParserTest, ParseBinaryOperator) {
    std::string expression = "p & q";
    std::shared_ptr<Expression> root;
    int result = parse(expression, root);
    EXPECT_TRUE(result);
    EXPECT_EQ("&", root->getValue());
    EXPECT_EQ("p", root->getLeft()->getValue());
    EXPECT_EQ("q", root->getRight()->getValue());
}

TEST(ParserTest, ParseMixedExpression) {
    std::string expression = "p & !(q | r)";
    std::shared_ptr<Expression> root;
    int result = parse(expression, root);
    EXPECT_TRUE(result);
    EXPECT_EQ("&", root->getValue());
    EXPECT_EQ("p", root->getLeft()->getValue());
    EXPECT_EQ("!", root->getRight()->getValue());
    EXPECT_EQ("|", root->getRight()->getLeft()->getValue());
    EXPECT_EQ("q", root->getRight()->getLeft()->getLeft()->getValue());
    EXPECT_EQ("r", root->getRight()->getLeft()->getRight()->getValue());
}

TEST(ParserTest, ParsedMultipleNOTs) {
    std::string expression = "!p | !q";
    std::shared_ptr<Expression> root;

    int result = parse(expression, root);
    EXPECT_TRUE(result);

    EXPECT_EQ("|", root->getValue());
    EXPECT_EQ("!", root->getLeft()->getValue());
    EXPECT_EQ("p", root->getLeft()->getLeft()->getValue());
    EXPECT_EQ("!", root->getRight()->getValue());
    EXPECT_EQ("q", root->getRight()->getLeft()->getValue());

    std::string expression2 = "!!p";

    int result2 = parse(expression2, root);
    EXPECT_TRUE(result);

    EXPECT_EQ("!", root->getValue());
    EXPECT_EQ("!", root->getLeft()->getValue());
    EXPECT_EQ("p", root->getLeft()->getLeft()->getValue());

    std::string expression3 = "!!!(p & q)";
    int result3 = parse(expression3, root);
    EXPECT_TRUE(result);

    EXPECT_EQ("!", root->getValue());
    EXPECT_EQ("!", root->getLeft()->getValue());
    EXPECT_EQ("!", root->getLeft()->getLeft()->getValue());
    EXPECT_EQ("&", root->getLeft()->getLeft()->getLeft()->getValue());
    EXPECT_EQ("p", root->getLeft()->getLeft()->getLeft()->getLeft()->getValue());
    EXPECT_EQ("q", root->getLeft()->getLeft()->getLeft()->getRight()->getValue());

    std::string expression4 = "(!(!!p & !!q))";
    int result4 = parse(expression4, root);
    EXPECT_TRUE(result);

    EXPECT_EQ("!", root->getValue());
    EXPECT_EQ("&", root->getLeft()->getValue());
    EXPECT_EQ("!", root->getLeft()->getLeft()->getValue());
    EXPECT_EQ("!", root->getLeft()->getRight()->getValue());
    EXPECT_EQ("!", root->getLeft()->getLeft()->getLeft()->getValue());
    EXPECT_EQ("p", root->getLeft()->getLeft()->getLeft()->getLeft()->getValue());
    EXPECT_EQ("!", root->getLeft()->getRight()->getLeft()->getValue());
    EXPECT_EQ("q", root->getLeft()->getRight()->getLeft()->getLeft()->getValue());

}