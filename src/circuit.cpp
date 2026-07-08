#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "circuit.h"
#include "components.h"
#include "battery.h"
#include "resistors.h"
#include "switch.h"
#include "node.h"
using namespace std;

static const unordered_map<char,double> coeffMap = {{'k',1e3},{'m',1e-3}};

static vector<string> unitTokenizer(const string &input){
    vector<string> tokenList;
    string token = "";
    bool numericToken;
    try{
        if(isdigit(input.at(0))||(input[0]=='.'&&isdigit(input.at(1)))){numericToken = true;}
        else{return tokenList={};}
    }
    catch(const out_of_range &e){return tokenList={};}
    for(int i=0;i<input.size();i++){
        if(numericToken){
            if(isdigit(input[i])||input[i]=='.'){token+=input[i];}
            else{
                if(!token.empty()){tokenList.push_back(token);}
                token="";
                if(isalpha(input[i])){token+=input[i];}
                else{
                    tokenList={};
                    return tokenList;
                }
                numericToken=false;
            }
        }
        else{
            if(isalpha(input[i])){token+=input[i];}
            else{
                tokenList={};
                return tokenList;
            }
        }
    }
    if(!token.empty()){tokenList.push_back(token);}
    return tokenList;
}

static bool isValidValue(const string &value, const string &unit){
    vector<string> tokenList = unitTokenizer(value);
    if(!tokenList.empty()){
        double mainValue;      
        try{
            size_t pos;
            mainValue=stod(tokenList[0], &pos);
            if(pos!=tokenList[0].size()){throw invalid_argument("Invalid Number\n");}
            if(tokenList.size()==2){
                string valueUnit = tokenList[1];
                if(coeffMap.contains(valueUnit[0])){valueUnit.erase(0,1);}
                if(unit!=valueUnit){throw invalid_argument("Wrong unit\n");}
            }
        }
        catch(const invalid_argument& e){
            cout<<e.what()<<endl;
            return false;
        }
    }
    else{
        cout<<"No value found\n";
        return false;
    }
    return true;
}

static double evaluateValue(string &value){
    vector<string> tokenList = unitTokenizer(value);
    double mainValue, coefficient = 1;
    mainValue = stod(tokenList[0]);
    if(tokenList.size()==2){
        if(coeffMap.contains(tokenList[1][0])){coefficient=coeffMap.at(tokenList[1][0]);}
    }
    return mainValue*coefficient;
}

Circuit::Circuit(const string &name):name(name){}

void Circuit::addNode(const string &name){
    if(!nodes.contains(name)){nodes.insert({name, new Node(name)});}
    else{cout<<"Node already exists\n";}
}

void Circuit::addComponent(const string &type, const string &name, const string &node1, const string &node2, string &value){
    if(!nodes.contains(node1)){addNode(node1);}
    if(!nodes.contains(node2)){addNode(node2);}
    if(!components.contains(name)){
        if(type=="Resistor"){
            string unit = "ohm";
            if(isValidValue(value, unit)){
                double SIValue = evaluateValue(value);
                components.insert({name, new Resistor(name, SIValue)});
                components.at(name)->connect(nodes.at(node1),nodes.at(node2));
            }
        }
        else if(type=="Battery"){
            string unit = "V";
            if(isValidValue(value, unit)){
                double SIValue = evaluateValue(value);
                components.insert({name, new Battery(name, SIValue)});
                components.at(name)->connect(nodes.at(node1),nodes.at(node2));
            }
        }
        else if(type=="Switch"){
            if(value=="ON"){components.insert({name, new Switch(name, SwitchState::Closed)});}
            else if(value=="OFF"){components.insert({name, new Switch(name, SwitchState::Open)});}
            else{cout<<"Switch can only have ON and OFF\n";}
            components.at(name)->connect(nodes.at(node1),nodes.at(node2));
        }
    }
    else{
        cout<<"Component with same name already exists.\n";
    }
}

void Circuit::deleteComponent(const string &name){
    try{
        Component* C = components.at(name);
        C->disconnect();
        components.erase(name);
        delete C;
    }
    catch(const out_of_range){
        cout<<"\nComponent doesn't exist.\n\n";
    }
}

void Circuit::deleteNode(const string &name){
    try{
        Node* N = nodes.at(name);
        vector<Component*> toDelete = N->disconnectNode();
        for(auto& it: toDelete){
            deleteComponent(it->getName());
        }
        nodes.erase(name);
        delete N;
    }
    catch(const out_of_range){
        cout<<"\nNode doesn't exist.\n\n";
    }   
}

string Circuit::getName() const{
    return name;
}

void Circuit::changeName(const string &rename){
    name = rename;
}

void Circuit::save(){
    string path = "circuits/user/"+name+".circuit";
    ofstream file(path);
    if(!file){
        cout << "\nCould not save file.\n\n";
        return;
    }
    file<<name<<endl;
    for(const auto& it: nodes){file<<"Node "<<it.first<<endl;}
    for(const auto& it: components){
        Component* comp = it.second;
        file<<comp->getType()<<" "<<comp->getName()<<" "<<comp->getNodes()[0]<<" "<<comp->getNodes()[1]<<" "<<comp->getValueString()<<endl;
    }
    file<<"Done";
    file.close();
    cout<<"\nSuccessfully saved!\n\n";
}
