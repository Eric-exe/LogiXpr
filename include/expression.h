#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
#include <string>
#include <memory>

#define AND "∧"
#define OR "∨"
#define NOT "¬"
#define IMPLIES "→"
#define IFF "↔"
#define OPEN "("
#define CLOSE ")"
#define TRUE "T"
#define FALSE "F"

class Expression
{
    public:
        Expression(std::string);
        Expression(std::string, std::shared_ptr<Expression>, std::shared_ptr<Expression>);

        std::string getExpression();

        bool hasLeft();
        bool hasRight();
        bool isBinary();

        std::shared_ptr<Expression> getLeft();
        std::shared_ptr<Expression> getRight();

        void setLeft(std::shared_ptr<Expression>);
        void setRight(std::shared_ptr<Expression>);
    
    private:
        std::string expression;
        std::shared_ptr<Expression> left;
        std::shared_ptr<Expression> right;

};

#endif