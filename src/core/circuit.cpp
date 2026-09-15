#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <memory>
#include <set>
#include "core/circuit.h"
#include "core/components.h"
#include "components/battery.h"
#include "components/resistors.h"
#include "components/switch.h"
#include "core/node.h"

Circuit::Circuit(const std::string &name):name(name){}

bool Circuit::hasComponent(const std::string &name){return components.contains(name);}

bool Circuit::hasNode(const std::string &name){return nodes.contains(name);}

void Circuit::addNode(const std::string &name){
    if(!hasNode(name)){nodes.insert({name, new Node(name)});}
}

void Circuit::addComponent(
    const std::string &type, 
    const std::string &name, 
    const std::string &node1, 
    const std::string &node2, 
    const std::string &value)
    {
    addNode(node1);
    addNode(node2);
    if(type=="Resistor"){
        double SIValue = stod(value);
        components.insert({name, new Resistor(name, SIValue)});
        components.at(name)->connect(nodes.at(node1),nodes.at(node2));
    }
    else if(type=="Battery"){
        double SIValue = stod(value);
        components.insert({name, new Battery(name, SIValue)});
        components.at(name)->connect(nodes.at(node1),nodes.at(node2));
    }
    else if(type=="Switch"){
        if(value=="ON"){components.insert({name, new Switch(name, SwitchState::Closed)});}
        else{components.insert({name, new Switch(name, SwitchState::Open)});}
        components.at(name)->connect(nodes.at(node1),nodes.at(node2));
    }
}

void Circuit::deleteComponent(const std::string &name){
    try{
        Component* C = components.at(name);
        C->disconnect();
        components.erase(name);
        delete C;
    }
    catch(const std::out_of_range){
        std::cout<<"\nComponent doesn't exist.\n\n";
    }
}

void Circuit::deleteNode(const std::string &name){
    try{
        Node* N = nodes.at(name);
        std::vector<Component*> toDelete = N->disconnectNode();
        for(auto& it: toDelete){
            deleteComponent(it->getName());
        }
        nodes.erase(name);
        delete N;
    }
    catch(const std::out_of_range){
        std::cout<<"\nNode doesn't exist.\n\n";
    }   
}

std::string Circuit::getName() const{
    return name;
}

void Circuit::changeName(const std::string &rename){
    name = rename;
}

void Circuit::save(){
    std::string path = "circuits/user/"+name+".circuit";
    std::ofstream file(path);
    if(!file){
        std::cout << "\nCould not save file.\n\n";
        return;
    }
    file<<name<<'\n';
    for(const auto& it: nodes){file<<"Node "<<it.first<<'\n';}
    for(const auto& it: components){
        Component* comp = it.second;
        file<<comp->getType()<<" "<<comp->getName()<<" "<<comp->getNodes()[0]<<" "<<comp->getNodes()[1]<<" "<<comp->getValueString()<<'\n';
    }
    file<<"Done";
    file.close();
    std::cout<<"\nSuccessfully saved!\n\n";
}


void Circuit::toggle(const std::string &name){
    if(hasComponent(name)){
        Component* comp = components.at(name);
        if(comp->getType()=="Switch"){
            static_cast<Switch*>(comp)->toggleSwitch(); 
        }
        else{
            std::cout<<name<<" is not a Switch!\n";
        }
    }
    else{
        std::cout<<"Switch "<<name<<" doesn't exist\n";
    }
}
