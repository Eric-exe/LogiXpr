#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <set>
#include <cctype>

#define AND "&"
#define OR "|"
#define NOT "!"
#define XOR "^"
#define IMPLIES "->"
#define IFF "<=>"
#define OPEN "("
#define CLOSE ")"
#define TRUE "T"
#define FALSE "F"

class Expression
{
    public:
        Expression(std::string);
        Expression(std::string, std::shared_ptr<Expression>, std::shared_ptr<Expression>);

        std::string getValue();

        bool hasLeft();
        bool hasRight();
        bool isBinary();
        bool isVar();

        std::shared_ptr<Expression> getLeft();
        std::shared_ptr<Expression> getRight();

        void setLeft(std::shared_ptr<Expression>);
        void setRight(std::shared_ptr<Expression>);

        std::set<std::string> getVariables();

        std::shared_ptr<Expression> clone();
    private:
        std::string value;
        std::shared_ptr<Expression> left;
        std::shared_ptr<Expression> right;
};
