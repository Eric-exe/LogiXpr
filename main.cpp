/**
 * @file main.cpp
 * @brief Main file
 */

#include <iostream>
#include <string>
#include <fstream>

#include "include/evaluator.h"
#include "include/parser.h"
#include "include/solver.h"

#define SUCCESS "[\033[32m+\033[0m] "
#define FAILURE "[\033[31m-\033[0m] "
#define ALERT "[\033[33m!\033[0m] "

int main() {
  std::cout << R"(  _              ___  __         
 | |   ___  __ _(_) \/ /_ __ _ _ 
 | |__/ _ \/ _` | |>  <| '_ \ '_|
 |____\___/\__, |_/_/\_\ .__/_|  
           |___/       |_|       
====================================================================)"
            << std::endl;

  std::cout << ALERT << "Reading config.ini..." << std::endl;
  // check if config.ini exists
  std::ifstream configFile("config.ini");
  if (!configFile.good()) {
    std::cout << FAILURE << "config.ini not found :(" << std::endl;
    return 1;
  }

  // read config.ini
  std::string line;
  int maxQueueSize = 0;
  int maxExprLength = 0;
  while (std::getline(configFile, line)) {
    if (line.find("MAX_QUEUE_SIZE") != std::string::npos) {
      maxQueueSize = std::stoi(line.substr(line.find("=") + 1));
    } else if (line.find("MAX_EXPRESSION_LENGTH") != std::string::npos) {
      maxExprLength = std::stoi(line.substr(line.find("=") + 1));
    }
  }

  // check if config.ini is valid
  if (maxQueueSize <= 0 || maxExprLength <= 0) {
    std::cout << FAILURE << "config.ini has bad values!" << std::endl;
    return 1;
  }

  std::cout << SUCCESS << "Read config.ini successfully!" << std::endl;
  std::cout << ALERT << "Setting config values... " << std::endl;

  // set config values
  MAX_QUEUE_SIZE = maxQueueSize;
  MAX_EXPRESSION_LENGTH = maxExprLength;

  std::string lhs;
  std::string rhs;

  std::cout << ALERT << "Enter the starting logical expression: ";
  std::getline(std::cin, lhs);
  std::cout << ALERT << "Enter the ending logical expression: ";
  std::getline(std::cin, rhs);

  std::cout << ALERT << "Parsing expressions..." << std::endl;

  std::shared_ptr<Expression> lhsTree;
  std::shared_ptr<Expression> rhsTree;

  if (parse(lhs, lhsTree)) {
    std::cout << SUCCESS << "Parsed left-hand side expression successfully!"
              << std::endl;
  } else {
    std::cout << FAILURE << "Failed to parse left-hand side expression :("
              << std::endl;
    return 1;
  }

  if (parse(rhs, rhsTree)) {
    std::cout << SUCCESS << "Parsed right-hand side expression successfully!"
              << std::endl;
  } else {
    std::cout << FAILURE << "Failed to parse right-hand side expression :("
              << std::endl;
    return 1;
  }

  std::cout << ALERT << "Removing unnecessary parentheses..." << std::endl;

  if (parse(lhsTree->toStringTree(), lhsTree)) {
    std::cout
        << SUCCESS
        << "Removed unnecessary parentheses from left-hand side expression!"
        << std::endl;
  } else {
    std::cout << FAILURE
              << "Failed to remove unnecessary parentheses from left-hand side "
                 "expression :("
              << std::endl;
    return 1;
  }

  if (parse(rhsTree->toStringTree(), rhsTree)) {
    std::cout
        << SUCCESS
        << "Removed unnecessary parentheses from right-hand side expression!"
        << std::endl;
  } else {
    std::cout << FAILURE
              << "Failed to remove unnecessary parentheses from right-hand "
                 "side expression :("
              << std::endl;
    return 1;
  }

  std::cout << ALERT << "Checking equivalence..." << std::endl;
  if (isEquivalent(lhsTree, rhsTree)) {
    std::cout << SUCCESS << "Expressions are equivalent!" << std::endl;
  } else {
    std::cout << FAILURE << "Expressions are not equivalent :(" << std::endl;
    return 1;
  }

  std::cout << ALERT << "Preprocessing expressions..." << std::endl;
  preprocess(lhsTree, rhsTree);

  std::cout << ALERT << "Proving equivalence..." << std::endl;
  std::cout
      << "===================================================================="
      << std::endl;
  std::vector<std::vector<std::string>> steps =
      proveEquivalence(lhsTree, rhsTree);

  // process the steps to make it aesthetically pleasing
  std::vector<std::vector<std::string>> processedSteps;
  int longestStrLen = 0;
  // check if the last step is not "Too many steps :("
  if (steps.back()[1] == "Too many steps :(") {
    std::cout << FAILURE << "Too many in queue :(. " << std::endl;
    std::cout << ALERT << "Tweak config ini by reducing logical expression length or increasing queue size" << std::endl;
    std::cout << ALERT << "Press any key to exit..." << std::endl;
    std::cin.get();
    return 1;
  }
  else if (steps.back()[1] == "Couldn't find a solution :(") {
    // check if the last step is not "Couldn't find a solution :("
    std::cout << FAILURE << "Couldn't find a solution :(. " << std::endl;
    std::cout << ALERT << "Tweak config ini by reducing logical expression length or increasing queue size" << std::endl;
    std::cout << ALERT << "Press any key to exit..." << std::endl;
    std::cin.get();
    return 1;
  }
  else {
    for (auto step : steps) {
    std::shared_ptr<Expression> currentStep;
    parse(step[0], currentStep);
    std::string processedStr = currentStep->toStringMinimal();
    if (processedStr.length() > longestStrLen) {
      longestStrLen = processedStr.length();
    }

    // sometimes, the laws don't actually change the expression once
    // unnecessary parentheses are removed, so we need to check for that
    if (processedSteps.size() == 0)
      processedSteps.push_back({processedStr, step[1]});
    else if (processedSteps.size() > 0 &&
             processedSteps.back()[0] != processedStr)
      processedSteps.push_back({processedStr, step[1]});
    }
  }

  // now add padding to the right side of the string to make it look nice
  longestStrLen += 4;
  for (auto &step : processedSteps) {
    step[0] += std::string(longestStrLen - step[0].length(), ' ');
  }

  // display steps
  // calculate padding to the right for headers
  std::string header = "Statement";
  int headerPadding = longestStrLen - header.length();
  std::cout << header << std::string(headerPadding, ' ') << "Justification"
            << std::endl;
  std::cout << std::endl;
  for (auto step : processedSteps) {
    std::cout << step[0] << step[1] << std::endl;
  }

  // wait for user to press to press any key to exit
  std::cout
      << "===================================================================="
      << std::endl;
  std::cout << ALERT << "Press any key to exit..." << std::endl;
  std::cin.get();

  return 0;
}