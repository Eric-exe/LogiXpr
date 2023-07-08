#include "../include/parser.h"
#include <gtest/gtest.h>


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
  std::shared_ptr<Expression> root;
  EXPECT_TRUE(parse("!p", root));
  EXPECT_EQ("!", root->getValue());
  EXPECT_EQ("p", root->getLeft()->getValue());
}

TEST(ParserTest, ParseBinaryOperator) {
  std::shared_ptr<Expression> root;
  EXPECT_TRUE(parse("p & q", root));
  EXPECT_EQ("&", root->getValue());
  EXPECT_EQ("p", root->getLeft()->getValue());
  EXPECT_EQ(nullptr, root->getLeft()->getLeft());
  EXPECT_EQ(nullptr, root->getLeft()->getRight());
  EXPECT_EQ("q", root->getRight()->getValue());
  EXPECT_EQ(nullptr, root->getRight()->getLeft());
  EXPECT_EQ(nullptr, root->getRight()->getRight());
}

TEST(ParserTest, ParseMixedExpression) {
  std::shared_ptr<Expression> root;
  EXPECT_TRUE(parse("p & !(q | r)", root));
  EXPECT_EQ("&", root->getValue());
  EXPECT_EQ("p", root->getLeft()->getValue());
  EXPECT_EQ(nullptr, root->getLeft()->getLeft());
  EXPECT_EQ(nullptr, root->getLeft()->getRight());
  EXPECT_EQ("!", root->getRight()->getValue());
  EXPECT_EQ("|", root->getRight()->getLeft()->getValue());
  EXPECT_EQ(nullptr, root->getRight()->getRight());
  EXPECT_EQ("q", root->getRight()->getLeft()->getLeft()->getValue());
  EXPECT_EQ(nullptr, root->getRight()->getLeft()->getLeft()->getLeft());
  EXPECT_EQ(nullptr, root->getRight()->getLeft()->getLeft()->getRight());
  EXPECT_EQ("r", root->getRight()->getLeft()->getRight()->getValue());
  EXPECT_EQ(nullptr, root->getRight()->getLeft()->getRight()->getLeft());
  EXPECT_EQ(nullptr, root->getRight()->getLeft()->getRight()->getRight());
}

TEST(ParserTest, ParsedMultipleNOTs) {
  std::shared_ptr<Expression> root;

  EXPECT_TRUE(parse("!p | !q", root));
  EXPECT_EQ("|", root->getValue());
  EXPECT_EQ("!", root->getLeft()->getValue());
  EXPECT_EQ(nullptr, root->getLeft()->getRight());
  EXPECT_EQ("p", root->getLeft()->getLeft()->getValue());
  EXPECT_EQ(nullptr, root->getLeft()->getLeft()->getLeft());
  EXPECT_EQ(nullptr, root->getLeft()->getLeft()->getRight());
  EXPECT_EQ("!", root->getRight()->getValue());
  EXPECT_EQ(nullptr, root->getRight()->getRight());
  EXPECT_EQ("q", root->getRight()->getLeft()->getValue());
  EXPECT_EQ(nullptr, root->getRight()->getLeft()->getLeft());
  EXPECT_EQ(nullptr, root->getRight()->getLeft()->getRight());

  EXPECT_TRUE(parse("!!p", root));
  EXPECT_EQ("!", root->getValue());
  EXPECT_EQ(nullptr, root->getRight());
  EXPECT_EQ("!", root->getLeft()->getValue());
  EXPECT_EQ(nullptr, root->getLeft()->getRight());
  EXPECT_EQ("p", root->getLeft()->getLeft()->getValue());
  EXPECT_EQ(nullptr, root->getLeft()->getLeft()->getLeft());
  EXPECT_EQ(nullptr, root->getLeft()->getLeft()->getRight());

  EXPECT_TRUE(parse("!!(!!p)", root));
  EXPECT_EQ("!", root->getValue());
  EXPECT_EQ(nullptr, root->getRight());
  EXPECT_EQ("!", root->getLeft()->getValue());
  EXPECT_EQ(nullptr, root->getLeft()->getRight());
  EXPECT_EQ("!", root->getLeft()->getLeft()->getValue());
  EXPECT_EQ(nullptr, root->getLeft()->getLeft()->getRight());
  EXPECT_EQ("!", root->getLeft()->getLeft()->getLeft()->getValue());
  EXPECT_EQ(nullptr, root->getLeft()->getLeft()->getLeft()->getRight());
  EXPECT_EQ("p", root->getLeft()->getLeft()->getLeft()->getLeft()->getValue());
  EXPECT_EQ(nullptr,
            root->getLeft()->getLeft()->getLeft()->getLeft()->getLeft());
  EXPECT_EQ(nullptr,
            root->getLeft()->getLeft()->getLeft()->getLeft()->getRight());

  EXPECT_TRUE(parse("!!!(p & q)", root));
  EXPECT_EQ("!", root->getValue());
  EXPECT_EQ(nullptr, root->getRight());
  EXPECT_EQ("!", root->getLeft()->getValue());
  EXPECT_EQ(nullptr, root->getLeft()->getRight());
  EXPECT_EQ("!", root->getLeft()->getLeft()->getValue());
  EXPECT_EQ(nullptr, root->getLeft()->getLeft()->getRight());
  EXPECT_EQ("&", root->getLeft()->getLeft()->getLeft()->getValue());
  EXPECT_EQ("p", root->getLeft()->getLeft()->getLeft()->getLeft()->getValue());
  EXPECT_EQ(nullptr,
            root->getLeft()->getLeft()->getLeft()->getLeft()->getLeft());
  EXPECT_EQ(nullptr,
            root->getLeft()->getLeft()->getLeft()->getLeft()->getRight());
  EXPECT_EQ("q", root->getLeft()->getLeft()->getLeft()->getRight()->getValue());
  EXPECT_EQ(nullptr,
            root->getLeft()->getLeft()->getLeft()->getRight()->getLeft());
  EXPECT_EQ(nullptr,
            root->getLeft()->getLeft()->getLeft()->getRight()->getRight());

  EXPECT_TRUE(parse("(!(!!p & !!q))", root));
  EXPECT_EQ("!", root->getValue());
  EXPECT_EQ(nullptr, root->getRight());
  EXPECT_EQ("&", root->getLeft()->getValue());
  EXPECT_EQ("!", root->getLeft()->getLeft()->getValue());
  EXPECT_EQ(nullptr, root->getLeft()->getLeft()->getRight());
  EXPECT_EQ("!", root->getLeft()->getRight()->getValue());
  EXPECT_EQ(nullptr, root->getLeft()->getRight()->getRight());
  EXPECT_EQ("!", root->getLeft()->getLeft()->getLeft()->getValue());
  EXPECT_EQ(nullptr, root->getLeft()->getLeft()->getLeft()->getRight());
  EXPECT_EQ("p", root->getLeft()->getLeft()->getLeft()->getLeft()->getValue());
  EXPECT_EQ(nullptr,
            root->getLeft()->getLeft()->getLeft()->getLeft()->getLeft());
  EXPECT_EQ(nullptr,
            root->getLeft()->getLeft()->getLeft()->getLeft()->getRight());
  EXPECT_EQ("!", root->getLeft()->getRight()->getLeft()->getValue());
  EXPECT_EQ(nullptr, root->getLeft()->getRight()->getLeft()->getRight());
  EXPECT_EQ("q", root->getLeft()->getRight()->getLeft()->getLeft()->getValue());
  EXPECT_EQ(nullptr,
            root->getLeft()->getRight()->getLeft()->getLeft()->getLeft());
  EXPECT_EQ(nullptr,
            root->getLeft()->getRight()->getLeft()->getLeft()->getRight());

  EXPECT_TRUE(parse("!!(!p | q) & (!(r | !s)) & !t", root));
  EXPECT_EQ("&", root->getValue());
  EXPECT_EQ("&", root->getLeft()->getValue());
  EXPECT_EQ("!", root->getLeft()->getLeft()->getValue());
  EXPECT_EQ(nullptr, root->getLeft()->getLeft()->getRight());
  EXPECT_EQ("!", root->getLeft()->getLeft()->getLeft()->getValue());
  EXPECT_EQ(nullptr, root->getLeft()->getLeft()->getLeft()->getRight());
  EXPECT_EQ("|", root->getLeft()->getLeft()->getLeft()->getLeft()->getValue());
  EXPECT_EQ(
      "!",
      root->getLeft()->getLeft()->getLeft()->getLeft()->getLeft()->getValue());
  EXPECT_EQ(
      nullptr,
      root->getLeft()->getLeft()->getLeft()->getLeft()->getLeft()->getRight());
  EXPECT_EQ("p", root->getLeft()
                     ->getLeft()
                     ->getLeft()
                     ->getLeft()
                     ->getLeft()
                     ->getLeft()
                     ->getValue());
  EXPECT_EQ(nullptr, root->getLeft()
                         ->getLeft()
                         ->getLeft()
                         ->getLeft()
                         ->getLeft()
                         ->getLeft()
                         ->getLeft());
  EXPECT_EQ(nullptr, root->getLeft()
                         ->getLeft()
                         ->getLeft()
                         ->getLeft()
                         ->getLeft()
                         ->getLeft()
                         ->getRight());
  EXPECT_EQ(
      "q",
      root->getLeft()->getLeft()->getLeft()->getLeft()->getRight()->getValue());
  EXPECT_EQ(
      nullptr,
      root->getLeft()->getLeft()->getLeft()->getLeft()->getRight()->getLeft());
  EXPECT_EQ(
      nullptr,
      root->getLeft()->getLeft()->getLeft()->getLeft()->getRight()->getRight());
  EXPECT_EQ("!", root->getLeft()->getRight()->getValue());
  EXPECT_EQ(nullptr, root->getLeft()->getRight()->getRight());
  EXPECT_EQ("|", root->getLeft()->getRight()->getLeft()->getValue());
  EXPECT_EQ("r", root->getLeft()->getRight()->getLeft()->getLeft()->getValue());
  EXPECT_EQ(nullptr,
            root->getLeft()->getRight()->getLeft()->getLeft()->getLeft());
  EXPECT_EQ(nullptr,
            root->getLeft()->getRight()->getLeft()->getLeft()->getRight());
  EXPECT_EQ("!",
            root->getLeft()->getRight()->getLeft()->getRight()->getValue());
  EXPECT_EQ(nullptr,
            root->getLeft()->getRight()->getLeft()->getRight()->getRight());
  EXPECT_EQ("s", root->getLeft()
                     ->getRight()
                     ->getLeft()
                     ->getRight()
                     ->getLeft()
                     ->getValue());
  EXPECT_EQ(
      nullptr,
      root->getLeft()->getRight()->getLeft()->getRight()->getLeft()->getLeft());
  EXPECT_EQ(nullptr, root->getLeft()
                         ->getRight()
                         ->getLeft()
                         ->getRight()
                         ->getLeft()
                         ->getRight());
  EXPECT_EQ("!", root->getRight()->getValue());
  EXPECT_EQ(nullptr, root->getRight()->getRight());
  EXPECT_EQ("t", root->getRight()->getLeft()->getValue());
  EXPECT_EQ(nullptr, root->getRight()->getLeft()->getLeft());
  EXPECT_EQ(nullptr, root->getRight()->getLeft()->getRight());
}