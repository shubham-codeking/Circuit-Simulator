#ifndef CIRCUITUTILITIES_H
#define CIRCUITUTILITIES_H
#include <vector>
#include <string>
#include "core/circuit.h"


std::vector<std::string> tokenize(const std::string &expression);
bool expressionValidator(const std::vector<std::string> &tokenList, Circuit* currentCircuit, bool displayError = false);
void executeExpression(const std::vector<std::string> &tokenList, Circuit* currentCircuit);

#endif