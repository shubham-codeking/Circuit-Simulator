#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include "elec_quantity.h"
using namespace std;

ElecQuantity::ElecQuantity(string name){
    qname=name;
    qvalue=0;
    known=false;
    valid=false;
}

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