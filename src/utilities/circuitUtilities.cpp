#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <memory>
#include <algorithm>
#include "utilities/circuitUtilities.h"
#include "core/components.h"
#include "core/circuit.h"
#include "core/node.h"

static const std::unordered_set<std::string> validTypes = {"Node", "Resistor", "Battery", "Switch"};
static const std::unordered_map<char,double> coeffMap = {{'k',1e3},{'m',1e-3}};

struct Expression
{
    std::string type;
    std::string name;
    std::string node1;
    std::string node2;
    std::string value;
};

std::vector<std::string> tokenize(const std::string &expression){
    std::vector<std::string> tokenList;
    std::string token;
    for(char a: expression){
        if(a==' ' && !token.empty()){
            tokenList.push_back(token);
            token="";
        }
        else{token += a;}
    }
    if(!token.empty()){tokenList.push_back(token);}
    return tokenList;
}

static std::vector<std::string> unitTokenizer(const std::string &input){
    std::vector<std::string> tokenList;
    std::string token = "";
    bool numericToken;
    try{
        if(isdigit(input.at(0))||(input[0]=='.'&&isdigit(input.at(1)))){numericToken = true;}
        else{return tokenList={};}
    }
    catch(const std::out_of_range &e){return tokenList={};}
    for(int i=0;i<input.size();i++){
        if(numericToken){
            if(isdigit(input[i])||input[i]=='.'){token+=input[i];}
            else{
                if(!token.empty()){tokenList.push_back(token);}
                token="";
                if(isalpha(input[i])){token+=input[i];}
                else{return {};}
                numericToken=false;
            }
        }
        else{
            if(isalpha(input[i])){token+=input[i];}
            else{return {};}
        }
    }
    if(!token.empty()){tokenList.push_back(token);}
    return tokenList;
}

static bool isValidValue(const std::string &value, const std::string &unit, bool displayError = false){
    std::vector<std::string> tokenList = unitTokenizer(value);
    if(!tokenList.empty()){
        double mainValue;      
        try{
            size_t pos;
            mainValue=stod(tokenList[0], &pos);
            if(pos!=tokenList[0].size()){throw std::invalid_argument("Invalid Number\n");}
            if(tokenList.size()==2){
                std::string valueUnit = tokenList[1];
                if(coeffMap.contains(valueUnit[0])){valueUnit.erase(0,1);}
                if(unit!=valueUnit){throw std::invalid_argument("Wrong unit\n");}
            }
        }
        catch(const std::invalid_argument& e){
            if(displayError){std::cout<<e.what()<<'\n';}
            return false;
        }
    }
    else{
        if(displayError){std::cout<<"No value found\n";}
        return false;
    }
    return true;
}

static std::string evaluateValue(std::string &value){
    std::vector<std::string> tokenList = unitTokenizer(value);
    double mainValue, coefficient = 1;
    mainValue = stod(tokenList[0]);
    if(tokenList.size()==2){
        if(coeffMap.contains(tokenList[1][0])){coefficient=coeffMap.at(tokenList[1][0]);}
    }
    return std::to_string(mainValue*coefficient);
}

bool expressionValidator(const std::vector<std::string> &tokenList, Circuit* currentCircuit, bool displayError){
    try{
        if(!tokenList.empty()){
            Expression exp;
            exp.type = tokenList[0];
            if(validTypes.contains(exp.type)){
                if(exp.type=="Node" && tokenList.size()!=2){
                    throw std::invalid_argument("Node takes only 1 name.\n");
                }
                else{
                    if(tokenList.size()==5){
                        exp.name = tokenList[1];
                        exp.node1 = tokenList[2];
                        exp.node2 = tokenList[3];
                        exp.value = tokenList[4];
                        if(currentCircuit->hasComponent(exp.name)){
                            throw std::invalid_argument("Component already exists\n");
                        }
                        if(exp.node1==exp.node2){
                            throw std::invalid_argument("Can't have same nodes\n");
                        }
                        std::string unit;
                        if(exp.type=="Resistor"){
                            unit = "ohm";
                            if(!isValidValue(exp.value, unit, displayError)){return false;}
                        }
                        else if(exp.type=="Battery"){
                            unit = "V";
                            if(!isValidValue(exp.value, unit, displayError)){return false;}
                        }
                        else{
                            if(exp.value!="ON"&&exp.value!="OFF"){
                                throw std::invalid_argument("Switch can only be ON or OFF.\n");
                            }
                        }
                    }
                    else if(exp.type!="Node"){throw std::invalid_argument("Expected 5 values for creating component.\n");}
                }
            }
            else{throw std::invalid_argument("Not a valid command!\n");}
        }
    }
    catch(const std::invalid_argument& error){
        if(displayError){std::cout<<error.what();} 
        return false;
    }
    return true;
}

void executeExpression(const std::vector<std::string> &tokenList, Circuit* currentCircuit){
    Expression exp;
    exp.type = tokenList[0];
    exp.name = tokenList[1];
    if(exp.type == "Node"){
        currentCircuit->addNode(exp.name);
    }
    else{
        exp.node1 = tokenList[2];
        exp.node2 = tokenList[3];
        exp.value = tokenList[4];
        if(exp.type!="Switch"){
            exp.value = evaluateValue(exp.value);
        }
        currentCircuit->addComponent(exp.type, exp.name, exp.node1, exp.node2, exp.value);
    }
}
