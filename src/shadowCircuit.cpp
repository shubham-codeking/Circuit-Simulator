#include "shadowCircuit.h"
#include "battery.h"
#include "switch.h"

ShadowNode::ShadowNode(Node* A, Node* B): Node(A->getName()+B->getName()+"shadow"), originals({A, B}){
    for(const auto& [name, comp]: A->getConnections()){
        this->createConnection(comp);
    }
    for(const auto& [name, comp]: B->getConnections()){
        this->createConnection(comp);
    }
}

ShadowResistor::ShadowResistor(string name, double value): Component(name, "ShadowResistor"), resistance(value){}

double ShadowResistor::getValue() const{
    return resistance;
}

void ShadowResistor::setValue(const double &newVal){
    resistance = newVal;
}

ShadowCircuit::ShadowCircuit(){
}

void ShadowCircuit::addNode(const string& name){
    if(!nodes.contains(name)){nodes.insert({name, nodes.at(name)});}
}

void ShadowCircuit::addComponent(const string &type, const string &name, const string &node1, const string &node2, const string &value){
    Node* A = nodes.at(node1);
    Node* B = nodes.at(node2);
    if(type=="Resistor"){
        double SIValue = stod(value);
        Resistor* comp = new Resistor(name, SIValue);
        components.insert({name, comp});
        comp->connect(A,B);
    }
    else if(type=="Battery"){
        double SIValue = stod(value);
        Battery* comp = new Battery(name, SIValue);
        components.insert({name, comp});
        comp->connect(A, B);
    }
    else if(type=="Switch" && value=="ON"){
       ShadowNode* newNode = new ShadowNode(A, B);
       A->setShadow(newNode);
       B->setShadow(newNode);
    }
}