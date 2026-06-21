#ifndef UTILITIES_H
#define UTILITIES_H
#include <vector>
#include <string>
using namespace std;

bool zeroDivisionCheck(const double &quantity);
bool expressionValidator(const string &expression);
vector<string> tokenizer(string &expression);
bool tokenValidator(const vector<string> &tokens);
vector<string> infixToPostfix(const vector<string> &tokens);
bool isOperand(const string &token);
bool isOperator(const string &token);

#endif