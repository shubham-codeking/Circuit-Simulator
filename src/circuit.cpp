#include <unordered_map>
#include <string>
#include <vector>
#include "circuit.h"
#include "components.h"
#include "node.h"
using namespace std;

Circuit::Circuit(const string &name):name(name){}

void Circuit::addNode(const string &name){
    nodes.insert({name, new Node(name)});
}

void Circuit::addComponent(const string &expression){
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

void Circuit::saveCircuit(){}
