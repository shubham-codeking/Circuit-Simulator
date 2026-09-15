#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include "core/circuit.h"
#include "core/node.h"
#include "utilities/circuitUtilities.h"
#include "ui/menus.h"
#include "core/components.h"
#include "calculations/resistance.h"
#include "components/battery.h"
#include "components/switch.h"

Circuit* addCircuit(){
    std::string circuitName;
    std::cout<<"Enter name of circuit: ";
    std::cin>>circuitName;
    std::cin.ignore();
    Circuit* circuit = new Circuit(circuitName);
    std::string expression;
    std::vector<std::string> tokenList;
    std::cout<<"Enter all Nodes and Components(type 'Done' to finish)\n";
    while(true){
        std::getline(std::cin, expression);
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
    std::filesystem::create_directories("circuits/user");
    std::string path = "circuits/user/"+currentCircuit->getName()+".circuit";
    if(std::filesystem::exists(path)){
        int choice = saveMenu();
        std::string rename;
        switch (choice){
        case 1:
            currentCircuit->save();
            break;
        case 2:
            std::cout<<"\nEnter new name: ";
            std::cin.ignore();
            std::getline(std::cin, rename);
            currentCircuit->changeName(rename);
            saveCircuit(currentCircuit);
            break;
        case 3:
            break;
        default:
            std::cout<<"\nEnter a valid input!\n\n";
            break;
        }
    }
    else{
        currentCircuit->save();
    }
}

Circuit* loadCircuit(){
    std::string name;
    std::cout<<"Enter name of circuit to load: ";
    std::cin>>name;
    std::cin.ignore();
    std::string path = "circuits/user/"+name+".circuit";
    if(std::filesystem::exists(path)){
        std::ifstream file(path);
        if(!file){
            std::cout<<"\nCircuit could not be loaded\n\n";
            return nullptr;
        }
        getline(file, name);
        Circuit* newCircuit = new Circuit(name);
        std::string expression;
        std::vector<std::string> tokenList;
        while(getline(file, expression)){
            if (expression=="Done"){break;}
            else{
                tokenList = tokenize(expression);
                if(expressionValidator(tokenList, newCircuit)){
                    executeExpression(tokenList, newCircuit);
                }
                else{
                    delete newCircuit;
                    std::cout<<"\nCircuit can't be loaded.\nSave file corrupted.\n\n";
                    return nullptr;
                }
            }
        }
        std::cout<<"\n"<<name<<" circuit loaded succesfully!\n\n";
        return newCircuit;
    }
    else{
        std::cout<<"\nNo such circuit exists.\n\n";
        return nullptr;
    }
}

void modifyCircuit(Circuit* currentCircuit){
    std::cout<<"Enter expression: \n";
    std::string expression;
    getline(std::cin, expression);
    std::vector<std::string> tokenList = tokenize(expression);
    if(!tokenList.empty()){
        std::string keyword = tokenList[0];
        tokenList.erase(tokenList.begin());
        if(keyword=="toggle"&&tokenList.size()==1){
            std::string name = tokenList[0];
            currentCircuit->toggle(name);
        }
        else if(keyword=="add"&&tokenList.size()>1){
            if(expressionValidator(tokenList, currentCircuit, true)){
                executeExpression(tokenList, currentCircuit);
            }
        }
        else if(keyword=="remove"&&tokenList.size()==1){
            std::string name = tokenList[0];
            if(currentCircuit->hasNode(name)){
                currentCircuit->deleteNode(name);
            }
            else if(currentCircuit->hasComponent(name)){
                currentCircuit->deleteComponent(name);
            }
            else{
                std::cout<<name<<" does not exist!";
            }
        }
        else if(keyword=="update"){
            if(tokenList.size()==5){
                std::string name = tokenList[1];
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
            std::cout<<"Enter a valid keyword";
        }
    }
    else{
        std::cout<<"Please enter a valid expression.\n";
        return;
    }
}
