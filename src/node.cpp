#include <string>
#include <vector>
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
    connections[component->getName()] = component;
}

void Node::removeConnection(Component* component){
    if(connections.contains(component->getName())){
        connections.erase(component->getName());
    }
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