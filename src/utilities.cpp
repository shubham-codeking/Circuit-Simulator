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

vector<string> tokenizer(string &expression){
    expression = "("+expression+")";
    string element = "";
    bool state = true;
    vector<string> tokenArray = {};
    vector<char> operatorArray = {'(',')','+'};
    for(int i=0; i<expression.length(); i++){
        if(state){
            element="";
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
        else if(expression[i]=='|'){
            if(state){
                element+=expression[i];
                state = false;
            }
            else{
                if(element=="|"){
                    tokenArray.push_back("||");
                    state = true;
                }
                else{
                    tokenArray.push_back(element);
                    element="";
                    element+=expression[i];
                }
            }
        }
    }
    return tokenArray;
}