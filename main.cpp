/**
 * @file main.cpp
 * @brief Main file
 */

#include <iostream>
#include <string>

#include "include/expression.h"
#include "include/parser.h"
#include "include/evaluator.h"

int main() {

    std::string lhsStr = "(!(!!p & !!q))";
    std::shared_ptr<Expression> lhs;
    std::cout << parse(lhsStr, lhs) << std::endl;

    return 0;
}
