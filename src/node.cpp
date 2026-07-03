#include <iostream>
#include <string>
#include "components.h"
#include "node.h"
using namespace std;

Node::Node(const string &name): name(name), potential(0) {}

double Node::getPotential() const{
    return potential;
}

void Node::setPotential(const double &potential){
    this->potential=potential;
}

void Node::createConnection(Component* component){
    this->connections[component->getName()] = component;
}