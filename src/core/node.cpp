#include <string>
#include <unordered_map>
#include <vector>
#include "core/components.h"
#include "core/node.h"

Node::Node(const std::string &name): name(name), potential(0) {}

std::string Node::getName() const{
    return name;
}

double Node::getPotential() const{
    return potential;
}

std::unordered_map<std::string, Component*> Node::getConnections() const{
    return connections;
}

int Node::getDegree() const{
    return connections.size();
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

std::vector<Component*> Node::disconnectNode(){
    std::vector<Component*> toDelete;
    for(auto& it: connections){
        toDelete.push_back(it.second);
    }
    for(auto& it: toDelete){
        it->disconnect();
    }
    return toDelete;
}