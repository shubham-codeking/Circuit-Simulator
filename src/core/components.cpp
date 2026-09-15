#include <vector>
#include <string>
#include "core/components.h"
#include "core/node.h"

Component::Component(std::string name, std::string type):
    name(name),
    type(type), 
    n1(nullptr), 
    n2(nullptr), 
    status(ConnectionStatus::Disconnected){}

std::string Component::getName() const{
    return name;
}

Node* Component::getOtherNode(Node* current) const{
    if(n1==current){return n2;}
    else if(n2==current){return n1;}
    return nullptr;
}

std::string Component::getType() const{
    return type;
}

std::vector<std::string> Component::getNodes() const{
    if(this->isConnected()){
        return {n1->getName(),n2->getName()};
    }
    else{
        return {};
    }
}

void Component::connect(Node* n1, Node* n2){
    this->n1=n1;
    this->n2=n2;
    n1->createConnection(this);
    n2->createConnection(this);
    status=ConnectionStatus::Connected;
}

void Component::disconnect(){
    if(status==ConnectionStatus::Disconnected){
        return;
    }
    status=ConnectionStatus::Disconnected;
    n1->removeConnection(this);
    n2->removeConnection(this);
}

bool Component::isConnected() const{
    return status==ConnectionStatus::Connected;
}