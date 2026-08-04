#include "shadowCircuit.h"
#include "battery.h"
#include "switch.h"

ShadowResistor::ShadowResistor(string name, double value): Component(name, "ShadowResistor"), resistance(value){}

double ShadowResistor::getValue() const{
    return resistance;
}

void ShadowResistor::setValue(const double &newVal){
    resistance = newVal;
}

ShadowCircuit::ShadowCircuit(){
}

void ShadowCircuit::addNode(const string &name){
    if(!nodes.contains(name)){nodes.insert({name, new Node(name)});}
}

void ShadowCircuit::addComponent(const string &type, const string &name, const string &node1, const string &node2, const string &value){
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
    else if(type=="Switch" && value=="ON"){
        components.insert({name, new Switch(name, SwitchState::Closed)});
        components.at(name)->connect(nodes.at(node1),nodes.at(node2));
    }
}