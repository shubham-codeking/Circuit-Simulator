#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <memory>
#include <set>
#include "circuit.h"
#include "components.h"
#include "shadowCircuit.h"
#include "battery.h"
#include "resistors.h"
#include "switch.h"
#include "node.h"
using namespace std;

static bool isPossibleDFS(Node* current, Node* target, set<Node*> &visited){
    if(current==target){
        return true;
    }
    visited.insert(current);
    for(auto& it: current->getConnections()){
        Component* comp = it.second;
        Node* next = comp->getOtherNode(current);
        if(!visited.contains(next)){
            if(isPossibleDFS(next, target, visited)){
                return true;
            }
        }
    }
    return false;
}

bool Circuit::hasPath(Node* start, Node* end){
    set<Node*> visited;
    return isPossibleDFS(start, end, visited);
}

Circuit::Circuit(const string &name):name(name){}

bool Circuit::hasComponent(const string &name){return components.contains(name);}

bool Circuit::hasNode(const string &name){return nodes.contains(name);}

void Circuit::addNode(const string &name){
    if(!hasNode(name)){nodes.insert({name, new Node(name)});}
}

void Circuit::addComponent(const string &type, const string &name, const string &node1, const string &node2, const string &value){
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


void Circuit::toggle(const string &name){
    if(hasComponent(name)){
        Component* comp = components.at(name);
        if(comp->getType()=="Switch"){
            static_cast<Switch*>(comp)->toggleSwitch(); 
        }
        else{
            cout<<name<<" is not a Switch!\n";
        }
    }
    else{
        cout<<"Switch "<<name<<" doesn't exist\n";
    }
}

unique_ptr<ShadowCircuit> Circuit::shadow() const{
    auto shadow = make_unique<ShadowCircuit>();
    for(const auto& [name, node]: nodes){
        shadow->addNode(name);
    }
    for(const auto& [name, comp]: components){
        shadow->addComponent(comp->getType(),
        name,
        comp->getNodes()[0],
        comp->getNodes()[1],
        comp->getValueString());
    }
    return shadow;
}
