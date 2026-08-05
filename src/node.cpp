#include <string>
#include <unordered_map>
#include <vector>
#include "shadowCircuit.h"
#include "components.h"
#include "node.h"
using namespace std;

Node::Node(const string &name): name(name), potential(0) {}

string Node::getName() const{
    return name;
}

double Node::getPotential() const{
    if(shadow){
        return shadow->getPotential();
    }
    return potential;
}

unordered_map<string, Component*> Node::getConnections() const{
    if(shadow){
        return shadow->getConnections();
    }
    return connections;
}

int Node::getDegree() const{
    if(shadow){
        return shadow->getDegree();
    }
    return connections.size();
}

void Node::setPotential(const double &potential){
    this->potential=potential;
    if(shadow){
        shadow->setPotential(potential);
    }
}

void Node::createConnection(Component* component){
    connections[component->getName()] = component;
}

void Node::removeConnection(Component* component){
    if(connections.contains(component->getName())){
        connections.erase(component->getName());
    }
}

void Node::setShadow(ShadowNode* shadow){
    this->shadow=shadow;
}

vector<Component*> Node::disconnectNode(){
    vector<Component*> toDelete;
    for(auto& it: connections){
        toDelete.push_back(it.second);
    }
    for(auto& it: toDelete){
        it->disconnect();
    }
    return toDelete;
}