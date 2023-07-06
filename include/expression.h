/**
 * @file expression.h
 * @brief Header file for expression class
 */

#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <set>
#include <cctype>

/**
 * @defgroup stringMacros String macros
 * @brief Macros for string expressions and operators
 * @{
 */
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
/** @} */

/**
 * @brief Abstract syntax tree for logic expressions
 */
class Expression
{
public:
    /**
     * @brief Construct a new Expression object
     *
     * @param value the current expression
     */
    Expression(std::string value);

    /**
     * @brief Get the value of the current expression
     *
     * @return the value of the current expression
     */
    std::string getValue();

    /**
     * @brief Check if the current expression has a left subexpression
     *
     * @return bool of whether the current expression has a left subexpression
     */
    bool hasLeft();

    /**
     * @brief Check if the current expression has a right subexpression
     *
     * @return bool of whether the current expression has a right subexpression
     */
    bool hasRight();

    /**
     * @brief Check if the current expression is a binary expression
     *
     * @return bool of whether the current expression is a binary expression
     */
    bool isBinary();

    /**
     * @brief Check if the current expression is a variable
     *
     * @return bool of whether the current expression is a variable
     */
    bool isVar();

    /**
     * @brief Get the parent expression of the current expression
     *
     * @return pointer to parent expression
     */
    std::shared_ptr<Expression> getParent();

    /**
     * @brief Get the left subexpression of the current expression
     *
     * @return pointer to left subexpression
     */
    std::shared_ptr<Expression> getLeft();

    /**
     * @brief Get the right subexpression of the current expression
     *
     * @return pointer to right subexpression
     */
    std::shared_ptr<Expression> getRight();

    /**
     * @brief Sets the left child expression of this expression
     * 
     * @param left pointer to expression to be set as the left child
     * @param parent pointer to current expression
     */
    void setLeft(std::shared_ptr<Expression> left, std::shared_ptr<Expression> parent);

    /**
    @brief Sets the right child expression of this expression
    @param right pointer to expression to be set as the right child
    @param parent pointer to current expression
    */
    void setRight(std::shared_ptr<Expression> right, std::shared_ptr<Expression> parent);

    /**
     * @brief Sets the parent node expression of this expression
     * 
     * @param parent pointer to expression to be set as the parent
     */
    void setParent(std::shared_ptr<Expression> parent);

    /**
     * @brief Get all the variables in the current expression and subexpressions
     *
     * @return set of strings of all the variables in the current expression and subexpressions
     */
    std::set<std::string> getVariables();

    /**
     * @brief Create a clone of the current expression and subexpressions
     *
     * @return pointer to cloned expression
     */
    std::shared_ptr<Expression> clone();

    /**
     * @brief Compare the current expression to another expression
     * 
     * @param other pointer to other expression to compare to
     * 
     * @return bool of whether the current expression is equal to the other expression
     */
    bool compare(std::shared_ptr<Expression> other);

private:
    /**
     * @brief The current expression
     */
    std::string value;

    /**
     * @brief pointer to parent expression
     */
    std::shared_ptr<Expression> parent;

    /**
     * @brief pointer to left subexpression
     */
    std::shared_ptr<Expression> left;

    /**
     * @brief pointer to right subexpression
     */
    std::shared_ptr<Expression> right;
};
