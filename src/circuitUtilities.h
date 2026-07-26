#ifndef CIRCUITUTILITIES_H
#define CIRCUITUTILITIES_H
#include <vector>
#include <string>
#include "circuit.h"
using namespace std;

vector<string> tokenize(const string &expression);
bool expressionValidator(const vector<string> &tokenList, Circuit* currentCircuit, bool displayError = false);
void executeExpression(const vector<string> &tokenList, Circuit* currentCircuit);
unique_ptr<Circuit> optimizer(Circuit* currentCircuit);
#endif