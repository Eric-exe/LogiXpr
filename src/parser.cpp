#include "../include/parser.h"

std::vector<std::string> tokenize(std::string expression) {
    std::vector<std::string> tokens;
    for (int i = 0; i < expression.length(); i++) {
        if (i + 1 < expression.length() && expression.substr(i, 2) == IMPLIES) {
            tokens.push_back(IMPLIES);
            i++;
        }
        else if (i + 2 < expression.length() && expression.substr(i, 3) == IFF) {
            tokens.push_back(IFF);
            i += 2;
        }
        else if (expression[i] != ' ') {
            tokens.push_back(std::string(1, expression[i]));
        }
    }
    return tokens;
}

int parse(std::string expression, std::shared_ptr<Expression> &root) {
    // implement the shunting yard algorithm to convert to abstract syntax tree

    std::stack<std::shared_ptr<Expression>> outputStack; // output queue
    std::stack<std::string> operatorStack; // operator stack

    std::vector<std::string> tokens = tokenize(expression);

    for (auto token : tokens) {
        if (token.length() == 1 && islower(token[0]) || token == TRUE || token == FALSE) {
            // This is a leaf node. It is either a variable or a constant (True or False)
            std::shared_ptr<Expression> leaf(new Expression(token));
            outputStack.push(leaf);
        }
        else if (token == NOT) {
            // Operator
            // special case - NOT is unary
            operatorStack.push(token);
        }
        else if (token == AND || token == OR || token == XOR || token == IFF || token == IMPLIES) {
            while (!operatorStack.empty() && operatorStack.top() != OPEN && precedence.at(operatorStack.top()) >= precedence.at(token)) {
                // This is where it differs from the original algorithm
                // Every time we pop an operator from the stack, we need to pop two operands from the output stack
                // and create a new expression with the operator and the operands as children
                std::string operatorStr = operatorStack.top();
                operatorStack.pop();

                std::shared_ptr<Expression> operatorPtr(new Expression(operatorStr));

                if (outputStack.size() < 2) return 1;
                std::shared_ptr<Expression> right = outputStack.top();
                outputStack.pop();

                std::shared_ptr<Expression> left = outputStack.top();
                outputStack.pop();

                operatorPtr->setLeft(left);
                operatorPtr->setRight(right);

                outputStack.push(operatorPtr);
            }
            operatorStack.push(token);
        }
        else if (token == OPEN) operatorStack.push(token);
        else if (token == CLOSE) {
            while (!operatorStack.empty() && operatorStack.top() != OPEN) {
                // Same as line 47
                std::string operatorStr = operatorStack.top();
                operatorStack.pop();

                std::shared_ptr<Expression> operatorPtr(new Expression(operatorStr));

                if (outputStack.size() < 2) return 1;

                std::shared_ptr<Expression> right = outputStack.top();
                outputStack.pop();

                std::shared_ptr<Expression> left = outputStack.top();
                outputStack.pop();

                operatorPtr->setLeft(left);
                operatorPtr->setRight(right);

                outputStack.push(operatorPtr);
            }
            operatorStack.pop();
        }
    }

    while (!operatorStack.empty()) {
        std::string operatorStr = operatorStack.top();
        operatorStack.pop();

        std::shared_ptr<Expression> operatorPtr(new Expression(operatorStr));

        if (outputStack.size() < 1) return 1;
        std::shared_ptr<Expression> right = outputStack.top();
        outputStack.pop();
        if (operatorStr == NOT) {
            operatorPtr->setLeft(right);
            outputStack.push(operatorPtr);
            continue;
        }

        if (outputStack.size() < 1) return 1;
        std::shared_ptr<Expression> left = outputStack.top();
        outputStack.pop();

        operatorPtr->setLeft(left);
        operatorPtr->setRight(right);

        outputStack.push(operatorPtr);
    }

    // assuming the expression is valid, there should be only one element in the output stack
    if (outputStack.size() != 1) return 1;
    root = outputStack.top();
    return 0;
}