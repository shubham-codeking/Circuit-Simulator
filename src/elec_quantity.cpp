#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include "elec_quantity.h"
using namespace std;

vector<string> ElecQuantity::tokenizer(string input){
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
                token+=input[i];
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
    cout<<qname<<": "<<qvalue<<endl;
}

void ElecQuantity::input(){
    cout<<"Enter "<<qname<<": ";
    string inp;
    getline(cin, inp);
    if(inp=="?"||inp.empty()||all_of(inp.begin(),inp.end(),[](unsigned char c){return isspace(c);})){
        valid=true;
    } 
    else{
        try{
            setValue(stod(inp));
        }
        catch(...){
            cout<<"\nInvalid input\n\n";
        } 
    }
}