#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <array>
#include <unordered_map>
#include "core/elec_quantity.h"

std::vector<std::string> ElecQuantity::tokenizer(const std::string &input){
    std::vector<std::string> tokenList;
    std::string token = "";
    bool numericToken = true;
    for(int i=0;i<input.size();i++){
        if(numericToken){
            if(isdigit(input[i])||input[i]=='.'){
                token+=input[i];
            }
            else{
                if(!token.empty()){
                    tokenList.push_back(token);
                }
                token="";
                if(isalpha(input[i])){
                    token+=input[i];
                }
                else{
                    tokenList={};
                    return tokenList;
                }
                numericToken=false;
            }
        }
        else{
            if(isalpha(input[i])){
                token+=input[i];
            }
            else{
                tokenList={};
                return tokenList;
            }
        }
    }
    if(!token.empty()){
        tokenList.push_back(token);
    }
    return tokenList;
}

ElecQuantity::ElecQuantity(std::string name, std::string unit):
qname(name),qvalue(0),known(false),valid(false),qunit(unit){}

double ElecQuantity::getValue() const{
    return qvalue;
}

bool ElecQuantity::isKnown() const{
    return known;
}
bool ElecQuantity::isValid() const{
    return valid;
}

void ElecQuantity::setValue(double value){
    qvalue=value;
    known=true;
    valid=true;
}

void ElecQuantity::print(){
    std::cout<<qname<<": "<<qvalue<<qunit<<'\n';
}

void ElecQuantity::validator(const std::vector<std::string> &tokenList){
    double mainValue, coefficient=1;
    std::string unit;
    static const std::unordered_map<char,double> coeffMap = {
        {'k',1e3},{'m',1e-3}
    };
    try{
        size_t pos;
        mainValue=stod(tokenList[0], &pos);
        if(pos!=tokenList[0].size()){
            throw std::invalid_argument("Error");
        }
        if(tokenList.size()==2){
            unit = tokenList[1];
            if(coeffMap.contains(unit[0])){
                coefficient=coeffMap.at(unit[0]);
                unit.erase(0,1);
            }
            if(unit!=qunit){
                throw std::invalid_argument("Error");
            }
        }
        this->setValue(mainValue*coefficient);
    }
    catch(...){
        std::cout<<"\nInvalid Input\n\n";
        return;
        }
}

void ElecQuantity::input(){
    std::cout<<"Enter "<<qname<<": ";
    std::string inp;
    std::getline(std::cin, inp);
    if(inp=="?"||inp.empty()||all_of(inp.begin(),inp.end(),[](unsigned char c){return isspace(c);})){
        valid=true;
    } 
    else{
        validator(tokenizer(inp));
    }
}