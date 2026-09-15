#ifndef UTILITIES_H
#define UTILITIES_H
#include <vector>
#include <string>

bool zeroDivisionCheck(const double &quantity);
bool expressionValidator(const std::string &expression);
std::vector<std::string> tokenizer(std::string &expression);
bool tokenValidator(const std::vector<std::string> &tokens);
std::vector<std::string> infixToPostfix(const std::vector<std::string> &tokens);
bool isOperand(const std::string &token);
bool isOperator(const std::string &token);

#endif