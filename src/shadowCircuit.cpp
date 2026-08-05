#include "shadowCircuit.h"
#include "battery.h"
#include "switch.h"

ShadowNode::ShadowNode(const string &name, Node* A, Node* B): Node(name), originals({A, B}){
    for(const auto& [name, comp]: A->getConnections()){
        this->createConnection(comp);
    }
    for(const auto& [name, comp]: B->getConnections()){
        this->createConnection(comp);
    }
}


ShadowResistor::ShadowResistor(string name, double value, vector<Resistor*> originals): 
    Resistor(name, value, "ShadowResistor"), originals(originals){}


ShadowCircuit::ShadowCircuit(){
}

void ShadowCircuit::addNode(const string& name){
    if(!currentNodes.contains(name)){currentNodes.insert({name, currentNodes.at(name)});}
}

void ShadowCircuit::addComponent(const string &type, const string &name, const string &node1, const string &node2, const string &value){
    Node* A = currentNodes.at(node1);
    Node* B = currentNodes.at(node2);
    if(type=="Resistor"){
        double SIValue = stod(value);
        Resistor* comp = new Resistor(name, SIValue);
        currentComponents.insert({name, comp});
        comp->connect(A,B);
    }
    else if(type=="Battery"){
        double SIValue = stod(value);
        Battery* comp = new Battery(name, SIValue);
        currentComponents.insert({name, comp});
        comp->connect(A, B);
    }
    else if(type=="Switch" && value=="ON"){
        string newName = generateShadowName();
        ShadowNode* newNode = new ShadowNode(newName, A, B);
        currentNodes.erase(node1);
        currentNodes.erase(node2);
        currentNodes.insert({newNode->getName(), newNode});
        A->setShadow(newNode);
        B->setShadow(newNode);
    }
}

string ShadowCircuit::generateShadowName(){
    string name;
    do{name = "__shadow_S" + to_string(counter++);}
    while (currentNodes.contains(name) || currentComponents.contains(name));
    return name;
}
