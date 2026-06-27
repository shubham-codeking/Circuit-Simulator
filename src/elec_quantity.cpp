#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <unordered_map>
#include "elec_quantity.h"
using namespace std;

vector<string> ElecQuantity::tokenizer(const string &input){
    vector<string> tokenList;
    string token = "";
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

ElecQuantity::ElecQuantity(string name, string unit):
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
    cout<<qname<<": "<<qvalue<<qunit<<endl;
}

void ElecQuantity::validator(const vector<string> &tokenList){
    double mainValue, coefficient=1;
    string unit;
    static const unordered_map<char,double> coeffMap = {
        {'k',1e3},{'m',1e-3}
    };
    try{
        size_t pos;
        mainValue=stod(tokenList[0], &pos);
        if(pos!=tokenList[0].size()){
            throw invalid_argument("Error");
        }
        if(tokenList.size()==2){
            unit = tokenList[1];
            if(coeffMap.contains(unit[0])){
                coefficient=coeffMap.at(unit[0]);
                unit.erase(0,1);
            }
            if(unit!=qunit){
                throw invalid_argument("Error");
            }
        }
        this->setValue(mainValue*coefficient);
    }
    catch(...){
        cout<<"\nInvalid Input\n\n";
        return;
        }
}

void ElecQuantity::input(){
    cout<<"Enter "<<qname<<": ";
    string inp;
    getline(cin, inp);
    if(inp=="?"||inp.empty()||all_of(inp.begin(),inp.end(),[](unsigned char c){return isspace(c);})){
        valid=true;
    } 
    else{
        validator(tokenizer(inp));
    }
}