#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include "circuit.h"
#include "node.h"
#include "circuitUtilities.h"
#include "menus.h"
#include "components.h"
#include "resistance.h"
#include "battery.h"
#include "switch.h"
using namespace std;


Circuit* addCircuit(){
    string circuitName;
    cout<<"Enter name of circuit: ";
    cin>>circuitName;
    cin.ignore();
    Circuit* circuit = new Circuit(circuitName);
    string expression;
    vector<string> tokenList;
    cout<<"Enter all Nodes and Components(type 'Done' to finish)\n";
    while(true){
        getline(cin, expression);
        if (expression=="Done"){break;}
        else{
            tokenList = tokenize(expression);
            if(expressionValidator(tokenList, circuit, true)){
                executeExpression(tokenList, circuit);
            }
        }
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
        vector<string> tokenList;
        while(getline(file, expression)){
            if (expression=="Done"){break;}
            else{
                tokenList = tokenize(expression);
                if(expressionValidator(tokenList, newCircuit)){
                    executeExpression(tokenList, newCircuit);
                }
                else{
                    delete newCircuit;
                    cout<<"\nCircuit can't be loaded.\nSave file corrupted.\n\n";
                    return nullptr;
                }
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

void modifyCircuit(Circuit* currentCircuit){
    cout<<"Enter expression: \n";
    string expression;
    getline(cin, expression);
    vector<string> tokenList = tokenize(expression);
    if(!tokenList.empty()){
        string keyword = tokenList[0];
        tokenList.erase(tokenList.begin());
        if(keyword=="toggle"&&tokenList.size()==1){
            string name = tokenList[0];
            currentCircuit->toggle(name);
        }
        else if(keyword=="add"&&tokenList.size()>1){
            if(expressionValidator(tokenList, currentCircuit, true)){
                executeExpression(tokenList, currentCircuit);
            }
        }
        else if(keyword=="remove"&&tokenList.size()==1){
            string name = tokenList[0];
            if(currentCircuit->hasNode(name)){
                currentCircuit->deleteNode(name);
            }
            else if(currentCircuit->hasComponent(name)){
                currentCircuit->deleteComponent(name);
            }
            else{
                cout<<name<<" does not exist!";
            }
        }
        else if(keyword=="update"){
            if(tokenList.size()==5){
                string name = tokenList[1];
                if(expressionValidator(tokenList, currentCircuit, true)&&currentCircuit->hasComponent(name)){
                    currentCircuit->deleteComponent(name);
                    executeExpression(tokenList, currentCircuit);
                }
            }
        }
        else if(keyword=="cancel"){
            return;
        }
        else{
            cout<<"Enter a valid keyword";
        }
    }
    else{
        cout<<"Please enter a valid expression.\n";
        return;
    }
}
