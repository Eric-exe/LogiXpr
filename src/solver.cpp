/**
 * @file solver.cpp
 * @brief Implementation file for solver functions
 */

#include "../include/solver.h"

std::unordered_map<EquivLaws::EquivLaw, std::string> equivalences = {};

void preprocess(std::shared_ptr<Expression> lhs,
                std::shared_ptr<Expression> rhs) {
  // include laws
  equivalences.clear();
  equivalences.insert(EquivLaws::laws.begin(), EquivLaws::laws.end());

  // convert lhs and rhs to strings
  std::string lhsString = lhs->toStringTree();
  std::string rhsString = rhs->toStringTree();

  if (lhsString.find("->") != std::string::npos ||
      rhsString.find("->") != std::string::npos) {
    equivalences.insert(EquivLaws::implications.begin(),
                        EquivLaws::implications.end());
  }

  if (lhsString.find("<=>") != std::string::npos ||
      rhsString.find("<=>") != std::string::npos) {
    equivalences.insert(EquivLaws::bidirectionalImplications.begin(),
                        EquivLaws::bidirectionalImplications.end());
  }
}

std::vector<std::vector<std::string>>
proveEquivalence(std::shared_ptr<Expression> lhs,
                 std::shared_ptr<Expression> rhs) {
  if (lhs->compare(rhs))
    return {{"", "Given"}};

  std::vector<std::vector<std::string>> steps;

  std::queue<std::shared_ptr<Expression>> queue;
  std::unordered_map<std::string, std::pair<std::string, std::string>> visited;

  queue.push(lhs);
  visited[lhs->toStringTree()] = {"", "Given"};

  bool found = false;

  while (!queue.empty()) {
    std::shared_ptr<Expression> expr = queue.front();
    queue.pop();

    if (expr->compare(rhs)) {
      // found the rhs, now backtrack the visited map to get the steps
      std::string currentExprString = expr->toStringTree();
      while (currentExprString != "") {
        steps.push_back({currentExprString, visited[currentExprString].second});
        currentExprString = visited[currentExprString].first;
      }
      std::reverse(steps.begin(), steps.end());
      break;
    }

    generateNextSteps(expr, rhs, found, queue, visited);
  }
  return steps;
}

void generateNextSteps(
    std::shared_ptr<Expression> expr, std::shared_ptr<Expression> end,
    bool &found, std::queue<std::shared_ptr<Expression>> &queue,
    std::unordered_map<std::string, std::pair<std::string, std::string>>
        &visited) {
  for (auto equiv : equivalences) {
    if (found)
      return;

    auto funct = equiv.first;
    auto lawName = equiv.second;

    std::shared_ptr<Expression> newExpr = expr->cloneTree();

    if (funct(newExpr)) {
      std::string newExprString = newExpr->toStringTree();
      if (newExprString.length() > 50)
        continue;
      // ignore extremely long expressions

      if (visited.find(newExprString) == visited.end()) {
        visited[newExprString] = {expr->toStringTree(), lawName};
        if (newExpr->compareTree(end))
          found = true;
        while (newExpr->getParent())
          newExpr = newExpr->getParent();
        queue.push(newExpr);
      }
    }
  }

  if (!found) {
    if (expr->getLeft() && !expr->getLeft()->isVar())
      generateNextSteps(expr->getLeft(), end, found, queue, visited);
    if (expr->getRight() && !expr->getRight()->isVar())
      generateNextSteps(expr->getRight(), end, found, queue, visited);
  }
}
