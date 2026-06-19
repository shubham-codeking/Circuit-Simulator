#ifndef UTILITIES_H
#define UTILITIES_H
#include <vector>
#include <string>

bool zeroDivisionCheck(const double &quantity);
bool expressionValidator(const string &expression);
vector<string> tokenizer(string &expression);
bool tokenValidator(const vector<string> &tokens);

#endif