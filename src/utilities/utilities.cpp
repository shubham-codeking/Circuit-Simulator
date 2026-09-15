#include "utilities/utilities.h"
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <cctype>
#include <stack>

bool zeroDivisionCheck(const double &quantity){
    if (quantity<1e-9){
        std::cout<<"\nCan't be zero!\n\n";
        return true;
    }
    else{
        return false;
    }
}

bool isOperator(const std::string &token){
    if(token=="+"||token=="||"){
        return true;
    }
    return false;
}

bool isOperand(const std::string &token){
    if(token!="("&&token!=")"&&!isOperator(token)){
        return true;
    }
    return false;
}

static int operatorPrecedence(const std::string &token){
    if(token=="||") return 2;
    if(token=="+") return 1;
    return 0;
}

bool expressionValidator(const std::string &expression){
    char operatorArray[] = {')','(','+','|'};
    if(expression.find("()")!=std::string::npos){
        return false;
    }
    for(int i=0;i<expression.length();i++){
        bool skip = false;
        if(isalnum(expression[i])||expression[i]==' '){
            continue;
        }
        for(char a: operatorArray){
            if(expression[i]==a){
                skip = true;
                break;
            }
        }
        if (skip){continue;}
        return false;
    }
    int parenthesisCount = 0;
    for(int i=0;i<expression.length();i++){
        if(expression[i]=='('){
            parenthesisCount += 1;
        }
        else if(expression[i]==')'){
            parenthesisCount -= 1;
        }
        if(parenthesisCount<0){
            return false;
        }
    }
    if(parenthesisCount!=0){
        return false;
    }
    return true;
}

std::vector<std::string> tokenizer(std::string &expression){
    expression = "("+expression+")";
    std::string element = "";
    bool state = true, parallelState = true;
    std::vector<std::string> tokenArray = {};
    std::vector<char> operatorArray = {'(',')','+'};
    for(int i=0; i<expression.length(); i++){
        if(state){
            element="";
        }
        if(!parallelState&&expression[i]!='|'){
            tokenArray={};
            return tokenArray;
        }
        if(expression[i]=='|'){
            if(parallelState){
                parallelState = false;
            }
            else{
                tokenArray.push_back("||");
                parallelState = true;
            }
            if(!state){
                tokenArray.push_back(element);
                state=true;
            }
            continue;
        }
        for(char op: operatorArray){
            if(expression[i]==op){
                if(!state){
                    tokenArray.push_back(element);
                }
                element=op;
                tokenArray.push_back(element);
                state = true;
                break;
            }
        }
        if(isalnum(expression[i])){
            element+=expression[i];
            if(state){
                state = false;
            }
            continue;
        }
    }
    if(!parallelState){
        tokenArray={};
        return tokenArray;
    }
    return tokenArray;
}

bool tokenValidator(const std::vector<std::string> &tokens){
    std::string past = tokens[0];
    for(std::string current: tokens){
        if(current=="("&&(past==")"||isOperand(past))){
            return false;    
        }
        else if(current==")"&&isOperator(past)){
            return false;
        }
        else if(isOperator(current)&&(past=="("||isOperator(past))){
            return false;
        }
        else if(isOperand(current)&&past==")"){
            return false;
        }
        past=current;
    }
    return true;
}

std::vector<std::string> infixToPostfix(const std::vector<std::string> &tokens){
    std::vector<std::string> postfixTokens;
    std::stack<std::string> operators;
    for(std::string token:tokens){
        if(token=="(") operators.push(token);
        else if(isOperand(token)) postfixTokens.push_back(token);
        else if(token==")"){
            while(true){
                if(operators.top()=="("){
                    operators.pop();
                    break;
                } 
                else{
                    postfixTokens.push_back(operators.top());
                    operators.pop();
                }
            }
        }
        else if(isOperator(token)){
            while(operatorPrecedence(token)<=operatorPrecedence(operators.top())){
                postfixTokens.push_back(operators.top());
                operators.pop();
                
            } 
            operators.push(token);
        }
    }
    return postfixTokens;
}
