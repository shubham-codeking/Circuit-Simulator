#include "utilities.h"
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

bool zeroDivisionCheck(const double &quantity){
    if (quantity==0){
        cout<<"\nCan't be zero!"<<endl<<endl;
        return true;
    }
    else{
        return false;
    }
}

static bool isOperator(const string &token){
    if(token=="+"||token=="||"){
        return true;
    }
    return false;
}

static bool isOperand(const string &token){
    if(token!="("&&token!=")"&&!isOperator(token)){
        return true;
    }
    return false;
}

bool expressionValidator(const string &expression){
    char operatorArray[] = {')','(','+','|'};
    if(expression.find("()")!=string::npos){
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


vector<string> tokenizer(string &expression){
    expression = "("+expression+")";
    string element = "";
    bool state = true, parallelState = true;
    vector<string> tokenArray = {};
    vector<char> operatorArray = {'(',')','+'};
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


bool tokenValidator(const vector<string> &tokens){
    string past = tokens[0];
    for(string current: tokens){
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
