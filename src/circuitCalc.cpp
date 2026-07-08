#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include "circuit.h"
#include "node.h"
#include "menus.h"
#include "components.h"
#include "resistance.h"
#include "battery.h"
#include "switch.h"
using namespace std;

static vector<string> tokenize(const string &expression){
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

static bool expressionParser(const string &expression, Circuit* circuit){
    vector<string> tokenList;
    static const vector<string> validTypes = {"Node", "Resistor", "Battery", "Switch"};
    tokenList = tokenize(expression);
    try{
        if(!tokenList.empty()){
            string type = tokenList[0];
            if(find(validTypes.begin(),validTypes.end(),type)!=validTypes.end()){
                if(type=="Node"){
                    if(tokenList.size()==2){
                        string name = tokenList[1];
                        circuit->addNode(name);
                    }
                    else{throw invalid_argument("Node takes only 1 name.\n");}
                }
                else{
                    if(tokenList.size()==5){
                        string name = tokenList[1];
                        string node1 = tokenList[2];
                        string node2 = tokenList[3];
                        string value = tokenList[4];
                        if(node1==node2){
                            throw invalid_argument("Can't have same nodes\n");
                        }
                        else{
                            circuit->addComponent(type, name, node1, node2, value);
                        }
                    }
                    else{throw invalid_argument("Expected 5 values for creating component.\n");}
                }
            }
            else{throw invalid_argument("Not a valid component type!\n");}
        }
    }
    catch(const invalid_argument& error){
        cout<<error.what();
        return false;
    }
    return true;
}

Circuit* addCircuit(){
    string circuitName;
    cout<<"Enter name of circuit: ";
    cin>>circuitName;
    cin.ignore();
    Circuit* circuit = new Circuit(circuitName);
    string expression;
    cout<<"Enter all Nodes and Components(type 'Done' to finish)\n";
    while(true){
        getline(cin, expression);
        if (expression=="Done"){break;}
        expressionParser(expression, circuit);
    }
    return  circuit;
}

void saveCircuit(Circuit* currentCircuit){
    filesystem::create_directories("circuits/user");
    string path = "circuits/user/"+currentCircuit->getName()+".circuit";
    if(filesystem::exists(path)){
        int choice = saveMenu();
        string rename;
        switch (choice){
        case 1:
            currentCircuit->save();
            break;
        case 2:
            cout<<"\nEnter new name: ";
            cin.ignore();
            getline(cin, rename);
            currentCircuit->changeName(rename);
            saveCircuit(currentCircuit);
            break;
        case 3:
            break;
        default:
            cout<<"\nEnter a valid input!\n\n";
            break;
        }
    }
    else{
        currentCircuit->save();
    }
}

Circuit* loadCircuit(){
    string name;
    cout<<"Enter name of circuit to load: ";
    cin>>name;
    cin.ignore();
    string path = "circuits/user/"+name+".circuit";
    if(filesystem::exists(path)){
        ifstream file(path);
        if(!file){
            cout<<"\nCircuit could not be loaded\n\n";
            return nullptr;
        }
        getline(file, name);
        Circuit* newCircuit = new Circuit(name);
        string expression;
        while(getline(file, expression)){
            if (expression=="Done"){break;}
            if(!expressionParser(expression, newCircuit)){
                delete newCircuit;
                cout<<"\nCircuit can't be loaded.\nSave file corrupted.\n\n";
                return nullptr;
            }
        }
        cout<<"\n"<<name<<" circuit loaded succesfully!\n\n";
        return newCircuit;
    }
    else{
        cout<<"\nNo such circuit exists.\n\n";
        return nullptr;
    }
}
