#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "circuit.h"
#include "node.h"
#include "components.h"
#include "resistance.h"
#include "battery.h"
#include "switch.h"
using namespace std;

vector<string> tokenize(const string &expression){
    vector<string> tokenList;
    string token;
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

void initializeCircuit(Circuit* circuit){
    string expression;
    vector<string> tokenList;
    static const vector<string> validTypes = {"Node", "Resistor", "Battery", "Switch"};
    cout<<"Enter all Nodes and Components(type 'Done' to finish)\n";
    while(true){
        getline(cin, expression);
        if (expression=="Done"){break;}
        tokenList = tokenize(expression);
        if(!tokenList.empty()){
            string type = tokenList[0];
            if(find(validTypes.begin(),validTypes.end(),type)!=validTypes.end()){
                if(type=="Node"){
                    if(tokenList.size()==2){
                        string name = tokenList[1];
                        circuit->addNode(name);
                    }
                    else{cout<<"Node takes only 1 name.\n";}
                }
                else{
                    if(tokenList.size()==5){
                        string name = tokenList[1];
                        string node1 = tokenList[2];
                        string node2 = tokenList[3];
                        string value = tokenList[4];
                        //further validation
                    }
                    else{cout<<"Expected 5 values.\n";}
                }
            }
            else{cout<<"Not a valid component type!\n";}
        }
    }
}

void addCircuit(){
    string circuitName;
    cout<<"Enter name of circuit: ";
    cin>>circuitName;
    cin.ignore();
    Circuit* circuit = new Circuit(circuitName);
    initializeCircuit(circuit);
}